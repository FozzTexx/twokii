#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <fcntl.h>

#include "gpio.h"
#include "ps2.h"

#define PIN_MCLK	17
#define PIN_MDAT	27
#define PIN_KCLK	24
#define PIN_KDAT	23

int main(int argc, char *argv[])
{
  int c, idx;
  WINDOW *w;
  scancode *sc;
  ps2port keyboard, mouse;
  int fdmax;
  fd_set readfds, exceptfds;
  int sawESC, sawKeypad;
  scancode *keyset = set2;
  scancode *keyShift, *keyCtrl, *keyAlt, *keyESC;
  unsigned char buf[10];
  

  init_gpio();

  ps2init(&keyboard, PS2_KEYBOARD, PIN_KCLK, PIN_KDAT);
  ps2init(&mouse, PS2_MOUSE, PIN_MCLK, PIN_MDAT);
  buf[0] = 0xAA;
  buf[1] = 0x00;
  ps2write(&mouse, buf, 2);
  
  putenv("ESCDELAY=10");
  w = initscr();
  keypad(w, TRUE);
  noecho();
  nodelay(w, TRUE);

  keyShift = scancodeForKey(keyset, KEY_LSHIFT);
  keyCtrl = scancodeForKey(keyset, KEY_LCTRL);
  keyAlt = scancodeForKey(keyset, KEY_LALT);
  keyESC = scancodeForKey(keyset, KEY_ESC);

  fdmax = keyboard.fd;
  if (mouse.fd > fdmax)
    fdmax = mouse.fd;
  
  for (;;) {
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_ZERO(&exceptfds);
    FD_SET(keyboard.fd, &exceptfds);
    FD_SET(mouse.fd, &exceptfds);
    select(fdmax+1, &readfds, NULL, &exceptfds, NULL);
    if (FD_ISSET(keyboard.fd, &exceptfds)) {
      lseek(keyboard.fd, 0, SEEK_SET);
      read(keyboard.fd, buf, sizeof(buf));
      c = ps2read(&keyboard);
      ps2received(&keyboard, c);
    }

    if (FD_ISSET(mouse.fd, &exceptfds)) {
      //printf("Mouse interrupt\r\n");
      lseek(mouse.fd, 0, SEEK_SET);
      read(mouse.fd, buf, sizeof(buf));
      c = ps2read(&mouse);
      ps2received(&mouse, c);
    }

    if (FD_ISSET(0, &readfds)) {
      sawESC = sawKeypad = 0;
      for (;;) {
	c = wgetch(w);
	if (c < 0)
	  break;

	if (c == 27) {
	  if (sawESC) {
	    ps2keydown(&keyboard, keyESC);
	    usleep(BYTEWAIT * 10);
	    ps2keyup(&keyboard, keyESC);
	  }
	  sawESC = 1;
	  continue;
	}

	if (c == 'O' && sawESC) {
	  sawKeypad = 1;
	  continue;
	}

	if (sawKeypad) {
	  sawKeypad = sawESC = 0;
	  switch (c) {
	  case 'l':
	    c = KEY_KPADD;
	    break;

	  case 'm':
	    c = KEY_KPSUB;
	    break;

	  case 'n':
	    c = KEY_KPDOT;
	    break;

	  case 'p':
	    c = KEY_KP0;
	    break;

	  case 'q':
	    c = KEY_KP1;
	    break;

	  case 'r':
	    c = KEY_KP2;
	    break;

	  case 's':
	    c = KEY_KP3;
	    break;

	  case 't':
	    c = KEY_KP4;
	    break;

	  case 'u':
	    c = KEY_KP5;
	    break;

	  case 'v':
	    c = KEY_KP6;
	    break;

	  case 'w':
	    c = KEY_KP7;
	    break;

	  case 'x':
	    c = KEY_KP8;
	    break;

	  case 'y':
	    c = KEY_KP9;
	    break;
	  }
	}
	
	/* Remap delete to backspace */
	if (c == 0x7f)
	  c = KEY_BACKSPACE;
	/* Remap control characters to dedicated keys */
	if (c == '\n')
	  c = KEY_ENTER;
	if (c == '\t')
	  c = KEY_TAB;
	if (c == '\b')
	  c = KEY_BACKSPACE;

	if (c == 30)
	  c = KEY_CAPSLOCK;
    
	printf("Key: 0x%02x 0o%03o", c, c);
	if (c > ' ' && c <= '~')
	  printf(" %c", c);
	printf("\r\n");

	if (c >= KEY_KP0 && c <= KEY_KPENTER) {
	  /* Mouse emulation */
	  int x, y;
	  static int bl = 0, br = 0;
	  unsigned char m[3];


	  x = y = 0;
	  switch (c) {
	  case KEY_KP4:
	    x -= 10;
	    break;

	  case KEY_KP6:
	    x += 10;
	    break;

	  case KEY_KP8:
	    y += 10;
	    break;

	  case KEY_KP2:
	    y -= 10;
	    break;

	  case KEY_KP7:
	    x -= 10;
	    y += 10;
	    break;

	  case KEY_KP9:
	    x += 10;
	    y += 10;
	    break;

	  case KEY_KP1:
	    x -= 10;
	    y -= 10;
	    break;

	  case KEY_KP3:
	    x += 10;
	    y -= 10;
	    break;

	  case KEY_KP5:
	    bl = !bl;
	    break;

	  case KEY_KPDOT:
	    br = !br;
	    break;
	  }

	  m[0] = 0x08
	    | ((y & 0x100) >> 3)
	    | ((x & 0x100) >> 4)
	    | bl | (br << 1);
	  m[1] = x & 0xFF;
	  m[2] = y & 0xFF;
	  printf("Sending mouse %i %i 0x%02x 0x%02x 0x%02x\r\n",
		 x, y, m[0], m[1], m[2]);
	  ps2write(&mouse, m, 3);
	}
	else {
	  sc = scancodeForKey(keyset, c);
	  if (sc == NULL)
	    continue;
	
	  printf("Scancode %02x s:%i c:%i x:%i a:%i kp:%i\r\n",
		 sc->code, sc->shift, sc->control, sc->extended, sawESC, sawKeypad);
	  if (sawESC)
	    ps2keydown(&keyboard, keyAlt);
	  ps2keydown(&keyboard, sc);
	  usleep(BYTEWAIT * 10);
	  ps2keyup(&keyboard, sc);
	  if (sawESC)
	    ps2keyup(&keyboard, keyAlt);
	  sawESC = sawKeypad = 0;
	}
      }

      if (sawESC) {
	ps2keydown(&keyboard, keyESC);
	usleep(BYTEWAIT * 10);
	ps2keyup(&keyboard, keyESC);
      }
    }

    while (digitalRead(keyboard.data) == LOW) {
      c = ps2read(&keyboard);
      ps2received(&keyboard, c);
    }
    while (digitalRead(mouse.data) == LOW) {
      c = ps2read(&mouse);
      ps2received(&mouse, c);
    }
  }

  endwin();
  
  exit(0);
}
