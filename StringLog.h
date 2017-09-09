#ifndef __STRINGLOG_H
#define __STRINGLOG_H

#include <stddef.h>
#include <Print.h>
#include <Stream.h>
#include <WString.h>

const uint16_t maxLogSize = 2048 - 1; // Maximum size of log in characters

class StringLog : public Print {
public:
  StringLog(const Stream* duplicate = NULL, bool prealloc = true) : Print(), _log() {
    if (prealloc)
      _log.reserve(maxLogSize);
    _duplicate = (Stream*)duplicate;
  }
  void clear() {
    _log = "";
  }
  uint16_t lines();
  const String& text() const {
    return _log;
  }
  String line(uint16_t index);
  String operator[](uint16_t index) {
    return line(index);
  }
  static String encodeStr(const String& str);

  using Print::write;
  size_t write(uint8_t ch) override;
protected:
  String _log;
  Stream* _duplicate;
};

#endif
