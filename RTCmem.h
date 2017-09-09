#ifndef __RTCMEM_H
#define __RTCMEM_H

#include <Arduino.h>

class RTCmemory {
public:
  static uint8_t read(uint16_t index);
  static void read(uint16_t index, uint8_t* buf, uint16_t len);
  static void write(uint16_t index, uint8_t data);
  static void write(uint16_t index, const uint8_t* buf, uint16_t len);
  template<typename T> static T& get(uint16_t index, T& t) {
    read(index, (uint8_t*)&t, sizeof(T));
    return t;
  }
  template<typename T> static const T& put(uint16_t index, const T& t) {
    write(index, (const uint8_t*)&t, sizeof(T));
    return t;
  }
};

extern RTCmemory RTCmem;

#endif
