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

