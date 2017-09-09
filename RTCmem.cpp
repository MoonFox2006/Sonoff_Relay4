#include "RTCmem.h"

static const uint16_t RTC_MEM_SIZE = 512;

uint8_t RTCmemory::read(uint16_t index) {
  if (index < RTC_MEM_SIZE) {
    uint8_t b[4];

    ESP.rtcUserMemoryRead(index / 4, (uint32_t*)b, sizeof(b));
    return b[index % 4];
  } else
    return 0;
}

void RTCmemory::read(uint16_t index, uint8_t* buf, uint16_t len) {
  if (len && (index + len <= RTC_MEM_SIZE)) {
    uint8_t b[4];
    uint16_t l;

    if (index % 4) { // partial dword at start of buf
      l = 4 - index % 4;
      if (l > len)
        l = len;
      ESP.rtcUserMemoryRead(index / 4, (uint32_t*)b, sizeof(b));
      if (l > 2)
        *buf++ = b[1];
      if (l > 1)
        *buf++ = b[2];
      *buf++ = b[3];
      index = (index + 4) / 4 * 4;
      len -= l;
    }
    if (len >= 4) { // whole dword(s) inside buf
      l = len / 4;
      ESP.rtcUserMemoryRead(index / 4, (uint32_t*)buf, l * 4);
      index += (l * 4);
      len -= (l * 4);
      buf += (l * 4);
    }
    if (len) { // partial dword at end of buf
      l = len;
      ESP.rtcUserMemoryRead(index / 4, (uint32_t*)b, sizeof(b));
      *buf++ = b[0];
      if (l > 1)
        *buf++ = b[1];
      if (l > 2)
        *buf++ = b[2];
    }
  }
}

void RTCmemory::write(uint16_t index, uint8_t data) {
  if (index < RTC_MEM_SIZE) {
    uint8_t b[4];

    ESP.rtcUserMemoryRead(index / 4, (uint32_t*)b, sizeof(b));
    if (b[index % 4] != data) {
      b[index % 4] = data;
      ESP.rtcUserMemoryWrite(index / 4, (uint32_t*)b, sizeof(b));
    }
  }
}

void RTCmemory::write(uint16_t index, const uint8_t* buf, uint16_t len) {
  if (len && (index + len <= RTC_MEM_SIZE)) {
    uint8_t b[4];
    uint16_t l;

    if (index % 4) { // partial dword at start of buf
      l = 4 - index % 4;
      if (l > len)
        l = len;
      ESP.rtcUserMemoryRead(index / 4, (uint32_t*)b, sizeof(b));
      if (l > 2)
        b[1] = *buf++;
      if (l > 1)
        b[2] = *buf++;
      b[3] = *buf++;
      ESP.rtcUserMemoryWrite(index / 4, (uint32_t*)b, sizeof(b));
      index = (index + 4) / 4 * 4;
      len -= l;
    }
    if (len >= 4) { // whole dword(s) inside buf
      l = len / 4;
      ESP.rtcUserMemoryWrite(index / 4, (uint32_t*)buf, l * 4);
      index += (l * 4);
      len -= (l * 4);
      buf += (l * 4);
    }
    if (len) { // partial dword at end of buf
      l = len;
      ESP.rtcUserMemoryRead(index / 4, (uint32_t*)b, sizeof(b));
      b[0] = *buf++;
      if (l > 1)
        b[1] = *buf++;
      if (l > 2)
        b[2] = *buf++;
      ESP.rtcUserMemoryWrite(index / 4, (uint32_t*)b, sizeof(b));
    }
  }
}

RTCmemory RTCmem;
