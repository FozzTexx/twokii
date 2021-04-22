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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <bcm_host.h>

#include "gpio.h"

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

