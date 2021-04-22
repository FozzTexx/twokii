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

#ifndef GPIO_H
#define GPIO_H 1

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

extern volatile unsigned *gpio;

extern void init_gpio();

#endif /* GPIO_H */
