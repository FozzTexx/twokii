#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include <sched.h>
#include <bcm_host.h>
#include <ncurses.h>

#include "scancodes.h"

#define PIN_CLK		17
#define PIN_DAT		27

#define BYTEWAIT	1000
#define CLKFULL		40

#define BLOCK_SIZE	(4*1024)

#define INPUT		0
#define OUTPUT		1
#define LOW		0
#define HIGH		1

#define digitalRead(pin)        ({int _p = (pin) & 31; (*(gpio + 13) & (1 << _p)) >> _p;})
#define digitalWrite(pin, val)  ({int _p = (pin) & 31, _v = !!(val);    \
      *(gpio + 7 + ((_v) ? 0 : 3)) = 1 << _p;})
#define pinMode(pin, mode)      ({int _p = (pin) & 31, _m = !!(mode);   \
  *(gpio + _p / 10) = (*(gpio + _p / 10) &          \
		       ~(7 << (_p % 10) * 3)) |     \
    (_m << (_p % 10) * 3);})

volatile unsigned *gpio;

void init_gpio()
{
  int mem_fd;
  void *gpio_map;
  
  
  if ((mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC) ) < 0) {
    printf("can't open /dev/gpiomem \n");
    exit(1);
  }

  gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED,
		  mem_fd, bcm_host_get_peripheral_address() + 0x200000);

  close(mem_fd); //No need to keep mem_fd open after mmap

  if (gpio_map == MAP_FAILED) {
    printf("mmap error %d\n", (int) gpio_map);
    exit(1);
  }

  // Always use volatile pointer!
  gpio = (volatile unsigned *) gpio_map;
  return;
}

static inline void my_usleep(double usec)
{
  struct timespec ts, rem;
  long long elapsed;
  struct timeval begin, now;


  if (usec > 1000) {
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

int ps2clockout(int bit)
{
  int clk;

  
  clk = digitalRead(PIN_CLK);
  pinMode(PIN_DAT, !bit);
  my_usleep(CLKFULL / 2);
  pinMode(PIN_CLK, OUTPUT);
  my_usleep(CLKFULL);
  pinMode(PIN_CLK, INPUT);
  my_usleep(CLKFULL / 2);
  return clk;
}

int ps2clockin()
{
  my_usleep(CLKFULL / 2);
  pinMode(PIN_CLK, OUTPUT);
  my_usleep(CLKFULL);
  pinMode(PIN_CLK, INPUT);
  my_usleep(CLKFULL / 2);
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
    if (elapsed > 100000)
      return -1;
  }

  for (idx = 0; idx < 8; idx++) {
    bit = ps2clockin();
    parity ^= bit;
    data = (data << 1) | bit;
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
  if (clk == 0)
    return 0;

  my_usleep(BYTEWAIT);
  clk = ps2clockout(0);
  if (!clk)
    return 0;

  for (idx = 0; idx < 8; idx++) {
    bit = data & 0x01;
    clk = ps2clockout(bit);
    if (!clk)
      return 0;
    parity ^= bit;
    data >>= 1;
  }

  clk = ps2clockout(parity);
  if (!clk)
    return 0;

  // stop bit
  ps2clockout(1);
  my_usleep(BYTEWAIT);

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
	printf("Read: %i\n", c);
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

int main(int argc, char *argv[])
{
  struct sched_param p;
  int c;
  WINDOW *w;
  scancode *sc;
  

  init_gpio();

  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DAT, INPUT);
  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_DAT, LOW);

  p.sched_priority = 99;
  if (sched_setscheduler(0, SCHED_FIFO, &p) != 0) {
    printf("Failed to set the scheduler\n");
  }

  w = initscr();
  noecho();

  for (;;) {
    c = getch();
    if (c > 0x7f)
      continue;
    
    /* Remap delete to backspace */
    if (c == 0x7f)
      c = 0x08;
    printf("Key: %02x", c);
    if (c > ' ' && c <= '~')
      printf(" %c", c);
    printf("\r\n");
    sc = &set2[c];
    printf("Scancode %02x s:%i c:%i x:%i\r\n", sc->code, sc->shift, sc->control, sc->extended);
    ps2keydown(sc);
    usleep(BYTEWAIT * 10);
    ps2keyup(sc);
  }

  endwin();
  
  exit(0);
}
