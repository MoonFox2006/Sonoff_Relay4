#ifndef __DS1820_H
#define __DS1820_H

#include <OneWire.h>

class DS1820 {
public:
  static const uint32_t MEASURE_TIME = 750;

  DS1820(int8_t pinDS) : _internalOW(true), _ow(new OneWire(pinDS)) {}
  DS1820(const OneWire& ow) : _internalOW(false), _ow((OneWire*)&ow) {}
  ~DS1820() {
    if (_internalOW)
      delete _ow;
  }
  bool find();
  void update();
  float readTemperature();

protected:
  bool _internalOW;
  OneWire* _ow;
  uint8_t _addr[8];
};

#endif
