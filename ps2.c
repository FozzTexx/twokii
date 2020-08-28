#include "ps2.h"
#include "gpio.h"

#include <time.h>
#include <sys/time.h>

#define CLKFULL		40

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

int ps2waitfordata()
{
  struct timeval begin, now;
  long long elapsed;
  int clk, dat;


  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DAT, INPUT);
  gettimeofday(&begin, NULL);
  for (;;) {
    clk = digitalRead(PIN_CLK);
    dat = digitalRead(PIN_DAT);
    if (clk == 1 && dat == 0)
      return 1;
    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - begin.tv_sec) * 1000000LL +
      now.tv_usec - begin.tv_usec;
    if (elapsed > 60)
      return 0;
  }

  return 0;
}

int ps2clockout(int bit)
{
  int clk;

  
  clk = digitalRead(PIN_CLK);
  pinMode(PIN_DAT, !bit);
  ps2usleep(CLKFULL / 2);
  pinMode(PIN_CLK, OUTPUT);
  ps2usleep(CLKFULL);
  pinMode(PIN_CLK, INPUT);
  ps2usleep(CLKFULL / 2);
  return clk;
}

int ps2clockin()
{
  ps2usleep(CLKFULL / 2);
  pinMode(PIN_CLK, OUTPUT);
  ps2usleep(CLKFULL);
  pinMode(PIN_CLK, INPUT);
  ps2usleep(CLKFULL / 2);
  return digitalRead(PIN_DAT);
}

int ps2read()
{
  int data = 0, parity = 1;
  int parity_host;
  int idx, bit;
  int clk, dat;
  struct timeval begin, now;
  long long elapsed;
  
  
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DAT, INPUT);
  gettimeofday(&begin, NULL);
  for (;;) {
    clk = digitalRead(PIN_CLK);
    dat = digitalRead(PIN_DAT);
    if (clk == 1 && dat == 0)
      break;
    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - begin.tv_sec) * 1000000LL +
      now.tv_usec - begin.tv_usec;
    if (elapsed > 1000)
      return -1;
  }

  for (idx = 0; idx < 8; idx++) {
    bit = ps2clockin();
    parity ^= bit;
    data = (data >> 1) | (bit << 7);
  }

  parity_host = ps2clockin();

  // stop bit
  ps2clockin();
  // ack
  ps2clockout(0);
  pinMode(PIN_DAT, INPUT);

  // FIXME - check parity
  return data;
}

int ps2writebyte(int data)
{
  int clk, dat;
  int bit, parity = 1;
  int idx;


  clk = digitalRead(PIN_CLK);
  if (clk == 0 && ps2waitfordata()) {
    printf("Blocked\r\n");
    return 0;
  }

  ps2usleep(BYTEWAIT);
  clk = ps2clockout(0);
  if (!clk)
    return 0;

  for (idx = 0; idx < 8; idx++) {
    bit = data & 0x01;
    clk = ps2clockout(bit);
    if (!clk) {
      printf("Bit blocked\r\n");
      return 0;
    }
    parity ^= bit;
    data >>= 1;
  }

  clk = ps2clockout(parity);
  if (!clk) {
    printf("Stop blocked\r\n");
    return 0;
  }

  // stop bit
  ps2clockout(1);
  ps2usleep(BYTEWAIT);

  return 1;
}

void ps2write(unsigned char *data, unsigned int len)
{
  unsigned int idx;
  int done = 0, sent;
  int c;


  while (!done) {
    done = 1;
    for (idx = 0; idx < len; idx++) {
      sent = ps2writebyte(data[idx]);
      if (!sent) {
	c = ps2read();
	ps2received(c);
	done = 0;
	break;
      }
    }
  }

  return;
}

void ps2keydown(scancode *sc)
{
  unsigned char data[10], *p;


  if (sc->shift) {
    data[0] = 0x12; /* Left shift */
    ps2write(data, 1);
  }
  if (sc->control) {
    data[0] = 0x14; /* Left ctrl */
    ps2write(data, 1);
  }

  p = data;
  if (sc->extended) {
    *p = 0xE0;
    p++;
  }
  *p = sc->code;
  p++;
  ps2write(data, p - data);

  return;
}

void ps2keyup(scancode *sc)
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
  ps2write(data, p - data);

  if (sc->shift) {
    data[0] = 0xF0;
    data[1] = 0x12; /* Left shift */
    ps2write(data, 2);
  }
  if (sc->control) {
    data[0] = 0xF0;
    data[1] = 0x14; /* Left ctrl */
    ps2write(data, 2);
  }

  return;
}

void ps2ack()
{
  char buf[1] = {0xFA};


  ps2write(buf, 1);
}

void ps2received(int data)
{
  unsigned char buf[10];
  int val;
  

  if (data < 0)
    return;
  
  printf("Read: 0x%02x\r\n", data);

  switch (data) {
  case 0xED: /* LEDs */
    ps2ack();
    printf("Sent ack\r\n");
    val = ps2read();
    if (val >= 0) {
      ps2ack();
      printf("LEDs: 0x%02x\r\n", val);
    }
    else {
      printf("No LEDs\r\n");
    }
    break;

  case 0xF0: /* Get/change scancode set */
    ps2ack();
    val = ps2read();
    if (val >= 0) {
      ps2ack();
      printf("Scancode: 0x%02x\r\n", val);
      if (val == 0) {
	buf[0] == 0x02;
	ps2write(buf, 1);
      }
    }
    else {
      printf("No LEDs\r\n");
    }
    break;    
    
  case 0xF2: /* Get device ID */
    ps2ack();
    buf[0] = 0xAB;
    buf[1] = 0x83;
    ps2write(buf, 2);
    break;

  case 0xF3: /* Set typematic rate */
    ps2ack();
    val = ps2read();
    if (val >= 0) {
      ps2ack();
      printf("Rate: 0x%02x\r\n", val);
    }
    else {
      printf("No rate\r\n");
    }
    break;
    
  case 0xF4: /* Enable sending keys */
    ps2ack();
    break;

  case 0xF5: /* Disable sending keys */
    ps2ack();
    break;

  case 0xF6: /* Set defaults */
    ps2ack();
    break;

  case 0xFF: /* Reset */
    buf[0] = 0xAA;
    ps2write(buf, 1);
    break;

  default:
    break;
  }

  return;
}

