#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "gpio.h"
#include "ps2.h"

int main(int argc, char *argv[])
{
  int c, idx;
  WINDOW *w;
  scancode *sc;
  

  init_gpio();

  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DAT, INPUT);
  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_DAT, LOW);

  putenv("ESCDELAY=10");
  w = initscr();
  keypad(w, TRUE);
  noecho();

  for (;;) {
    c = getch();
    
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
    if (c == 27)
      c = KEY_ESC;

    if (c == 30)
      c = KEY_CAPSLOCK;
    
    printf("Key: 0x%02x", c);
    if (c > ' ' && c <= '~')
      printf(" %c", c);
    printf("\r\n");

    if (c > 0x7f) {
      for (idx = 0x80; set2[idx].code >= 0; idx++) {
	if (set2[idx].c == c)
	  break;
      }

      /* No matching scancode found, ignore key */
      if (set2[idx].code == -1)
	continue;

      c = idx;
    }
    
    sc = &set2[c];
    printf("Scancode %02x s:%i c:%i x:%i\r\n", sc->code, sc->shift, sc->control, sc->extended);
    ps2keydown(sc);
    usleep(BYTEWAIT * 10);
    ps2keyup(sc);

    while (digitalRead(PIN_DAT) == LOW) {
      c = ps2read();
      ps2received(c);
    }
  }

  endwin();
  
  exit(0);
}
