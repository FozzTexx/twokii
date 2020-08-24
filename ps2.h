#ifndef PS2_H
#define PS2_H 1

#include "scancodes.h"

#define PIN_CLK		17
#define PIN_DAT		27

#define BYTEWAIT	1000

extern int ps2clockout(int bit);
extern int ps2clockin();
extern int ps2read();
extern int ps2writebyte(int data);
extern void ps2write(unsigned char *data, unsigned int len);
extern void ps2keydown(scancode *sc);
extern void ps2keyup(scancode *sc);
extern void ps2received(int data);

#endif /* PS2_H */
