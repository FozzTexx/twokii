CFLAGS=-g -I/opt/vc/include
LIBS=-lbcm_host -lncurses
LDFLAGS=-L/opt/vc/lib $(LIBS)

ps2key: ps2key.o gpio.o ps2.o scancodes.o
ps2key.o: ps2key.c scancodes.h gpio.h ps2.h
ps2.o: ps2.c ps2.h gpio.h
gpio.o: gpio.h gpio.c
scancodes.o: scancodes.h scancodes.c
