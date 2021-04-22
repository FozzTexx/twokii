/* Copyright 2021 by Chris Osborn <fozztexx@fozztexx.com>
 *
 * This file is part of twokii.
 *
 * twokii is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * twokii is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with twokii; see the file COPYING. If not see
 * <http://www.gnu.org/licenses/>.
 */

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

extern scancode *scancodeForKey(scancode set[], int key);

#endif /* SCANCODES_H */
