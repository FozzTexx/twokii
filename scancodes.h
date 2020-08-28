#ifndef SCANCODES_H
#define SCANCODES_H 1

#include <ncurses.h>

enum {
  KEY_TAB = KEY_MAX + 1,
  KEY_ESC,
  KEY_DELETE,
  KEY_CAPSLOCK,
  KEY_NUMLOCK,
  KEY_SCRLOCK,
  KEY_LSHIFT,
  KEY_RSHIFT,
  KEY_LCTRL,
  KEY_RCTRL,
  KEY_LALT,
  KEY_RALT,
  KEY_LWIN,
  KEY_RWIN,
  KEY_MENU,
  KEY_KP0,
  KEY_KP1,
  KEY_KP2,
  KEY_KP3,
  KEY_KP4,
  KEY_KP5,
  KEY_KP6,
  KEY_KP7,
  KEY_KP8,
  KEY_KP9,
  KEY_KPDOT,
  KEY_KPADD,
  KEY_KPSUB,
  KEY_KPMULT,
  KEY_KPDIV,
  KEY_KPENTER,
};  
  
typedef struct {
  int code;
  int c;
  unsigned int shift:1;
  unsigned int control:1;
  unsigned int extended:1;
} scancode;

extern scancode set2[];

#endif /* SCANCODES_H */
