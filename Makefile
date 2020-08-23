CFLAGS=-I/opt/vc/include
LIBS=-lbcm_host -lncurses
LDFLAGS=-L/opt/vc/lib $(LIBS)

ps2key: ps2key.o
ps2key.o: ps2key.c scancodes.h
