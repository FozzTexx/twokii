#ifndef PS2_H
#define PS2_H 1

#include "scancodes.h"

#define BYTEWAIT	1000

enum {
  PS2_KEYBOARD,
  PS2_MOUSE,
};
  
typedef struct {
  int type;
  int clock, data, fd;
} ps2port;

extern void ps2init(ps2port *port, int type, int clock, int data);
extern int ps2clockout(ps2port *port, int bit);
extern int ps2clockin(ps2port *port);
extern int ps2read(ps2port *port);
extern int ps2writebyte(ps2port *port, int data);
extern void ps2write(ps2port *port, unsigned char *data, unsigned int len);
extern void ps2keydown(ps2port *port, scancode *sc);
extern void ps2keyup(ps2port *port, scancode *sc);
extern void ps2received(ps2port *port, int data);

#endif /* PS2_H */
