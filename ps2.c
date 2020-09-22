#include "ps2.h"
#include "gpio.h"

#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#define CLKFULL		40

#define kms(x) (x->type == PS2_KEYBOARD ? "keyboard" : "mouse")

void ps2init(ps2port *port, int type, int clock, int data)
{
  char buf[128];
  FILE *file;


  port->type = type;
  port->clock = clock;
  port->data = data;
  
  pinMode(port->clock, INPUT);
  pinMode(port->data, INPUT);
  digitalWrite(port->clock, LOW);
  digitalWrite(port->data, LOW);

  file = fopen("/sys/class/gpio/export", "w");
  fprintf(file, "%i\n", port->data);
  fclose(file);
  snprintf(buf, sizeof(buf) - 1, "/sys/class/gpio/gpio%i/direction", port->data);
  file = fopen(buf, "w");
  fprintf(file, "in\n");
  fclose(file);
  snprintf(buf, sizeof(buf) - 1, "/sys/class/gpio/gpio%i/edge", port->data);
  file = fopen(buf, "w");
  fprintf(file, "falling\n");
  fclose(file);
  
  snprintf(buf, sizeof(buf) - 1, "/sys/class/gpio/gpio%i/value", port->data);
  port->fd = open(buf, O_RDONLY);

  return;
}

static inline void ps2usleep(double usec)
{
  struct timespec ts, rem;
  long long elapsed;
  struct timeval begin, now;


  if (usec > 500) {
    ts.tv_sec = 0;
    ts.tv_nsec = usec * 1000;
    nanosleep(&ts, &rem);
  }
  else {
    gettimeofday(&begin, NULL);
    for (;;) {
      gettimeofday(&now, NULL);
      elapsed = (now.tv_sec - begin.tv_sec) * 1000000LL +
	now.tv_usec - begin.tv_usec;
      if (elapsed >= usec)
	break;
    }
  }
  
  return;
}

int ps2waitfordata(ps2port *port)
{
  struct timeval begin, now;
  long long elapsed;
  int clk, dat;


  pinMode(port->clock, INPUT);
  pinMode(port->data, INPUT);
  gettimeofday(&begin, NULL);
  for (;;) {
    clk = digitalRead(port->clock);
    dat = digitalRead(port->data);
    if (clk == 1 && dat == 0)
      return 1;
    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - begin.tv_sec) * 1000000LL +
      now.tv_usec - begin.tv_usec;
    if (elapsed > 1000)
      return 0;
  }

  return 0;
}

int ps2clockout(ps2port *port, int bit)
{
  int clk;

  
  clk = digitalRead(port->clock);
  if (clk) {
    pinMode(port->data, !bit);
    ps2usleep(CLKFULL / 2);
    pinMode(port->clock, OUTPUT);
    ps2usleep(CLKFULL);
    pinMode(port->clock, INPUT);
    ps2usleep(CLKFULL / 2);
  }

  return clk;
}

int ps2clockin(ps2port *port)
{
  ps2usleep(CLKFULL / 2);
  pinMode(port->clock, OUTPUT);
  ps2usleep(CLKFULL);
  pinMode(port->clock, INPUT);
  ps2usleep(CLKFULL / 2);
  return digitalRead(port->data);
}

int ps2read(ps2port *port)
{
  int data = 0, parity = 1;
  int parity_host;
  int idx, bit;
  int clk, dat;
  struct timeval begin, now;
  long long elapsed;
  char buf[128];


  pinMode(port->clock, INPUT);
  pinMode(port->data, INPUT);
  gettimeofday(&begin, NULL);
  for (;;) {
    clk = digitalRead(port->clock);
    dat = digitalRead(port->data);
    if (clk == 1 && dat == 0)
      break;
    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - begin.tv_sec) * 1000000LL +
      now.tv_usec - begin.tv_usec;
    if (elapsed > 1000)
      return -1;
  }

  for (idx = 0; idx < 8; idx++) {
    bit = ps2clockin(port);
    parity ^= bit;
    data = (data >> 1) | (bit << 7);
  }

  parity_host = ps2clockin(port);

  // stop bit
  ps2clockin(port);
  // ack
  ps2clockout(port, 0);
  pinMode(port->data, INPUT);

  // FIXME - check parity
  return data;
}

int ps2waitread(ps2port *port)
{
  int data;


  do {
    data = ps2read(port);
  } while (data < 0);

  return data;
}

int ps2writebyte(ps2port *port, int data)
{
  int clk, dat;
  int bit, parity = 1;
  int idx;
  int sent = 0;


  clk = digitalRead(port->clock);
  if (clk == 0 && ps2waitfordata(port)) {
    printf("%s Start blocked\r\n", kms(port));
    return 0;
  }

  ps2usleep(BYTEWAIT);
  clk = ps2clockout(port, 0);
  if (!clk)
    return 0;
  sent++;

  for (idx = 0; idx < 8; idx++) {
    bit = data & 0x01;
    clk = ps2clockout(port, bit);
    if (!clk) {
      printf("%s Bit blocked\r\n", kms(port));
      return 0;
    }
    parity ^= bit;
    data >>= 1;
    sent++;
  }

  ps2clockout(port, parity);
  if (!clk) {
    printf("%s Parity blocked\r\n", kms(port));
    return 0;
  }
  sent++;

  // stop bit
  clk = ps2clockout(port, 1);
  if (!clk) {
    printf("%s Stop blocked\r\n", kms(port));
    return 0;
  }
  sent++;
  ps2usleep(BYTEWAIT);

  printf("%s wrote %i bits\r\n", kms(port), sent);
  return 1;
}

void ps2write(ps2port *port, unsigned char *data, unsigned int len)
{
  unsigned int idx;
  int sent;
  int c;


  for (idx = 0; idx < len; idx++) {
    sent = ps2writebyte(port, data[idx]);
    if (!sent) {
      idx--;
      c = ps2read(port);
      ps2received(port, c);
    }
  }

  return;
}

void ps2keydown(ps2port *port, scancode *sc)
{
  unsigned char data[10], *p;


  if (sc->shift) {
    data[0] = 0x12; /* Left shift */
    ps2write(port, data, 1);
  }
  if (sc->control) {
    data[0] = 0x14; /* Left ctrl */
    ps2write(port, data, 1);
  }

  p = data;
  if (sc->extended) {
    *p = 0xE0;
    p++;
  }
  *p = sc->code;
  p++;
  ps2write(port, data, p - data);

  return;
}

void ps2keyup(ps2port *port, scancode *sc)
{
  unsigned char data[10], *p;


  p = data;
  if (sc->extended) {
    *p = 0xE0;
    p++;
  }
  *p = 0xF0;
  p++;
  *p = sc->code;
  p++;
  ps2write(port, data, p - data);

  if (sc->shift) {
    data[0] = 0xF0;
    data[1] = 0x12; /* Left shift */
    ps2write(port, data, 2);
  }
  if (sc->control) {
    data[0] = 0xF0;
    data[1] = 0x14; /* Left ctrl */
    ps2write(port, data, 2);
  }

  return;
}

void ps2ack(ps2port *port)
{
  char buf[1] = {0xFA};


  ps2write(port, buf, 1);
}

void ps2keyboardreceived(ps2port *port, int data)
{
  unsigned char buf[10];
  int val;
  

  switch (data) {
  case 0xED: /* LEDs */
    ps2ack(port);
    printf("%s Sent ack\r\n", kms(port));
    val = ps2waitread(port);
    if (val >= 0) {
      ps2ack(port);
      printf("%s LEDs: 0x%02x\r\n", kms(port), val);
    }
    else {
      printf("%s No LEDs\r\n", kms(port));
    }
    break;

  case 0xF0: /* Get/change scancode set */
    ps2ack(port);
    val = ps2waitread(port);
    if (val >= 0) {
      ps2ack(port);
      printf("%s Scancode: 0x%02x\r\n", kms(port), val);
      if (val == 0) {
	buf[0] == 0x02;
	ps2write(port, buf, 1);
      }
    }
    break;    
    
  case 0xF2: /* Get device ID */
    ps2ack(port);
    buf[0] = 0xAB;
    buf[1] = 0x83;
    ps2write(port, buf, 2);
    break;

  case 0xF3: /* Set typematic rate */
    ps2ack(port);
    val = ps2waitread(port);
    if (val >= 0) {
      ps2ack(port);
      printf("%s Rate: 0x%02x\r\n", kms(port), val);
    }
    else {
      printf("%s No rate\r\n", kms(port));
    }
    break;
    
  case 0xF4: /* Enable sending keys */
    ps2ack(port);
    break;

  case 0xF5: /* Disable sending keys */
    ps2ack(port);
    break;

  case 0xF6: /* Set defaults */
    ps2ack(port);
    break;

  case 0xFF: /* Reset */
    buf[0] = 0xAA;
    ps2write(port, buf, 1);
    break;

  default:
    break;
  }

  return;
}

void ps2mousereceived(ps2port *port, int data)
{
  unsigned char buf[10];
  int val;
  

  switch (data) {
  case 0xE6: /* Set scaling 1:1 */
    ps2ack(port);
    break;

  case 0xE7: /* Set scaling 2:1 */
    ps2ack(port);
    break;
    
  case 0xE8: /* Set resolution */
    ps2ack(port);
    val = ps2waitread(port);
    ps2ack(port);
    printf("%s resolution: 0x%02x\r\n", kms(port), val);
    break;

  case 0xE9: /* Status request */
    ps2ack(port);
    buf[0] = 0x00;
    buf[1] = 0x02;
    buf[2] = 100;
    ps2write(port, buf, 3);
    break;

  case 0xEA: /* Set stream mode */
    ps2ack(port);
    break;

  case 0xEB: /* Read data */
    ps2ack(port);
    buf[0] = 0x08;
    buf[1] = 0x00;
    buf[2] = 0x00;
    ps2write(port, buf, 3);
    break;

  case 0xEC: /* Reset wrap mode */
    ps2ack(port);
    printf("%s end wrap\r\n", kms(port));
    break;

  case 0xEE: /* Set wrap mode */
    ps2ack(port);
    printf("%s WRAP MODE\r\n", kms(port));
    break;

  case 0xF0: /* Set remote mode */
    ps2ack(port);
    break;    
    
  case 0xF2: /* Get device ID */
    ps2ack(port);
    buf[0] = 0x00;
    ps2write(port, buf, 1);
    break;

  case 0xF3: /* Set sample rate */
    ps2ack(port);
    val = ps2waitread(port);
    ps2ack(port);
    printf("%s Sample rate: 0x%02x\r\n", kms(port), val);
    break;
    
  case 0xF4: /* Enable data reporting */
    ps2ack(port);
    break;

  case 0xF5: /* Disable data reporting */
    ps2ack(port);
    break;

  case 0xF6: /* Set defaults */
    ps2ack(port);
    break;

  case 0xFF: /* Reset */
    if (port->type == PS2_KEYBOARD) {
      buf[0] = 0xAA;
      ps2write(port, buf, 1);
    }
    else if (port->type == PS2_MOUSE) {
      buf[0] = 0xFA;
      buf[1] = 0xAA;
      buf[2] = 0x00;
      ps2write(port, buf, 3);
    }
    break;

  default:
    break;
  }

  return;
}

void ps2received(ps2port *port, int data)
{
  if (data < 0)
    return;
  
  printf("%s Read: 0x%02x\r\n", kms(port), data);

  if (port->type == PS2_KEYBOARD)
    ps2keyboardreceived(port, data);
  else if (port->type == PS2_MOUSE)
    ps2mousereceived(port, data);
  return;
}
