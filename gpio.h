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
