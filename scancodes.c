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

#include "scancodes.h"

scancode set2[] = {
   /* Control keys */
   {0x1E, 0x00, 1, 1, 0},
   {0x1C, 0x01, 0, 1, 0},
   {0x32, 0x02, 0, 1, 0},
   {0x21, 0x03, 0, 1, 0},
   {0x23, 0x04, 0, 1, 0},
   {0x24, 0x05, 0, 1, 0},
   {0x2B, 0x06, 0, 1, 0},
   {0x34, 0x07, 0, 1, 0},
   {0x33, 0x08, 0, 1, 0},
   {0x43, 0x09, 0, 1, 0},
   {0x3B, 0x0a, 0, 1, 0},
   {0x42, 0x0b, 0, 1, 0},
   {0x4B, 0x0c, 0, 1, 0},
   {0x3A, 0x0d, 0, 1, 0},
   {0x31, 0x0e, 0, 1, 0},
   {0x44, 0x0f, 0, 1, 0},
   {0x4D, 0x10, 0, 1, 0},
   {0x15, 0x11, 0, 1, 0},
   {0x2D, 0x12, 0, 1, 0},
   {0x1B, 0x13, 0, 1, 0},
   {0x2C, 0x14, 0, 1, 0},
   {0x3C, 0x15, 0, 1, 0},
   {0x2A, 0x16, 0, 1, 0},
   {0x1D, 0x17, 0, 1, 0},
   {0x22, 0x18, 0, 1, 0},
   {0x35, 0x19, 0, 1, 0},
   {0x1A, 0x1a, 0, 1, 0},
   {0x54, 0x1b, 0, 1, 0},
   {0x5D, 0x1c, 0, 1, 0},
   {0x5B, 0x1d, 0, 1, 0},
   {0x36, 0x1e, 1, 1, 0},
   {0x4E, 0x1f, 1, 1, 0},
   
   {0x29, ' ', 0, 0, 0},
   {0x16, '!', 1, 0, 0},
   {0x52, '"', 1, 0, 0},
   {0x26, '#', 1, 0, 0},
   {0x25, '$', 1, 0, 0},
   {0x2E, '%', 1, 0, 0},
   {0x3D, '&', 1, 0, 0},
   {0x52, '\'', 0, 0, 0},
   {0x46, '(', 1, 0, 0},
   {0x45, ')', 1, 0, 0},
   {0x3E, '*', 1, 0, 0},
   {0x55, '+', 1, 0, 0},
   {0x41, ',', 0, 0, 0},
   {0x4E, '-', 0, 0, 0},
   {0x49, '.', 0, 0, 0},
   {0x4A, '/', 0, 0, 0},
   {0x45, '0', 0, 0, 0},
   {0x16, '1', 0, 0, 0},
   {0x1E, '2', 0, 0, 0},
   {0x26, '3', 0, 0, 0},
   {0x25, '4', 0, 0, 0},
   {0x2E, '5', 0, 0, 0},
   {0x36, '6', 0, 0, 0},
   {0x3D, '7', 0, 0, 0},
   {0x3E, '8', 0, 0, 0},
   {0x46, '9', 0, 0, 0},
   {0x4C, ':', 1, 0, 0},
   {0x4C, ';', 0, 0, 0},
   {0x41, '<', 1, 0, 0},
   {0x55, '=', 0, 0, 0},
   {0x49, '>', 1, 0, 0},
   {0x4A, '?', 1, 0, 0},
   
   {0x1E, '@', 1, 0, 0},
   {0x1C, 'A', 1, 0, 0},
   {0x32, 'B', 1, 0, 0},
   {0x21, 'C', 1, 0, 0},
   {0x23, 'D', 1, 0, 0},
   {0x24, 'E', 1, 0, 0},
   {0x2B, 'F', 1, 0, 0},
   {0x34, 'G', 1, 0, 0},
   {0x33, 'H', 1, 0, 0},
   {0x43, 'I', 1, 0, 0},
   {0x3B, 'J', 1, 0, 0},
   {0x42, 'K', 1, 0, 0},
   {0x4B, 'L', 1, 0, 0},
   {0x3A, 'M', 1, 0, 0},
   {0x31, 'N', 1, 0, 0},
   {0x44, 'O', 1, 0, 0},
   {0x4D, 'P', 1, 0, 0},
   {0x15, 'Q', 1, 0, 0},
   {0x2D, 'R', 1, 0, 0},
   {0x1B, 'S', 1, 0, 0},
   {0x2C, 'T', 1, 0, 0},
   {0x3C, 'U', 1, 0, 0},
   {0x2A, 'V', 1, 0, 0},
   {0x1D, 'W', 1, 0, 0},
   {0x22, 'X', 1, 0, 0},
   {0x35, 'Y', 1, 0, 0},
   {0x1A, 'Z', 1, 0, 0},
   {0x54, '[', 0, 0, 0},
   {0x5D, '\\', 0, 0, 0},
   {0x5B, ']', 0, 0, 0},
   {0x36, '^', 1, 0, 0},
   {0x4E, '_', 1, 0, 0},

   {0x0E, '`', 0, 0, 0},
   {0x1C, 'a', 0, 0, 0},
   {0x32, 'b', 0, 0, 0},
   {0x21, 'c', 0, 0, 0},
   {0x23, 'd', 0, 0, 0},
   {0x24, 'e', 0, 0, 0},
   {0x2B, 'f', 0, 0, 0},
   {0x34, 'g', 0, 0, 0},
   {0x33, 'h', 0, 0, 0},
   {0x43, 'i', 0, 0, 0},
   {0x3B, 'j', 0, 0, 0},
   {0x42, 'k', 0, 0, 0},
   {0x4B, 'l', 0, 0, 0},
   {0x3A, 'm', 0, 0, 0},
   {0x31, 'n', 0, 0, 0},
   {0x44, 'o', 0, 0, 0},
   {0x4D, 'p', 0, 0, 0},
   {0x15, 'q', 0, 0, 0},
   {0x2D, 'r', 0, 0, 0},
   {0x1B, 's', 0, 0, 0},
   {0x2C, 't', 0, 0, 0},
   {0x3C, 'u', 0, 0, 0},
   {0x2A, 'v', 0, 0, 0},
   {0x1D, 'w', 0, 0, 0},
   {0x22, 'x', 0, 0, 0},
   {0x35, 'y', 0, 0, 0},
   {0x1A, 'z', 0, 0, 0},
   {0x54, '{', 1, 0, 0},
   {0x5D, '|', 1, 0, 0},
   {0x5B, '}', 1, 0, 0},
   {0x0E, '~', 1, 0, 0},
   {0x71, 0x7f, 0, 0, 1},

   /* non-ascii keys */

   {0x66, KEY_BACKSPACE, 0, 0, 0},
   {0x0D, KEY_TAB, 0, 0, 0},
   {0x0D, KEY_BTAB, 1, 0, 0},
   {0x5A, KEY_ENTER, 0, 0, 0},
   {0x76, KEY_ESC, 0, 0, 0},
   
   {0x58, KEY_CAPSLOCK, 0, 0},
   {0x77, KEY_NUMLOCK, 0, 0},
   {0x7E, KEY_SCRLOCK, 0, 0},

   {0x12, KEY_LSHIFT, 0, 0},
   {0x59, KEY_RSHIFT, 0, 0},
   {0x14, KEY_LCTRL, 0, 0},
   {0x11, KEY_LALT, 0, 0},
   {0x11, KEY_RALT, 0, 0, 1},
   {0x14, KEY_RCTRL, 0, 0, 1},
   {0x1f, KEY_LWIN, 0, 0, 1},
   {0x27, KEY_RWIN, 0, 0, 1},
   {0x2f, KEY_MENU, 0, 0, 1},

   {0x72, KEY_DOWN, 0, 0, 1},
   {0x75, KEY_UP, 0, 0, 1},
   {0x6B, KEY_LEFT, 0, 0, 1},
   {0x74, KEY_RIGHT, 0, 0, 1},
   {0x7D, KEY_PPAGE, 0, 0, 1},
   {0x7A, KEY_NPAGE, 0, 0, 1},
   {0x6C, KEY_HOME, 0, 0, 1},
   {0x69, KEY_END, 0, 0, 1},
   {0x70, KEY_IC, 0, 0, 1},
   {0x71, KEY_DC, 0, 0, 1},
   
   {0x70, KEY_KP0, 0, 0},
   {0x69, KEY_KP1, 0, 0},
   {0x72, KEY_KP2, 0, 0},
   {0x7A, KEY_KP3, 0, 0},
   {0x6B, KEY_KP4, 0, 0},
   {0x73, KEY_KP5, 0, 0},
   {0x74, KEY_KP6, 0, 0},
   {0x6C, KEY_KP7, 0, 0},
   {0x75, KEY_KP8, 0, 0},
   {0x7D, KEY_KP9, 0, 0},
   {0x71, KEY_KPDOT, 0, 0},
   {0x79, KEY_KPADD, 0, 0},
   {0x7B, KEY_KPSUB, 0, 0},
   {0x7C, KEY_KPMULT, 0, 0},
   {0x4A, KEY_KPDIV, 0, 0, 1},
   {0x5A, KEY_KPENTER, 0, 0, 1},
   
   {0x05, KEY_F(1), 0, 0},
   {0x06, KEY_F(2), 0, 0},
   {0x04, KEY_F(3), 0, 0},
   {0x0C, KEY_F(4), 0, 0},
   {0x03, KEY_F(5), 0, 0},
   {0x0B, KEY_F(6), 0, 0},
   {0x83, KEY_F(7), 0, 0},
   {0x0A, KEY_F(8), 0, 0},
   {0x01, KEY_F(9), 0, 0},
   {0x09, KEY_F(10), 0, 0},
   {0x78, KEY_F(11), 0, 0},
   {0x07, KEY_F(12), 0, 0},
   /*
   {[0xE0, 0x12, 0xE0, 0x7C; 0xE0, 0xF0, 0x7C, 0xE0, 0xF0, 0x12], KEY_PRINT, 0, 0},
   {[0xE1, 0x14, 0x77; 0xE1, 0xF0, 0x14, 0xF0, 0x77], KEY_BREAK, 0, 0}, // immediate release
   */

   {-1, -1, 0, 0, 0},
  };

scancode *scancodeForKey(scancode set[], int key)
{
  int idx;
  
  for (idx = 0; set[idx].code >= 0; idx++) {
    if (set[idx].c == key)
      return &set[idx];
  }

  /* No matching scancode found, ignore key */
  return NULL;
}
