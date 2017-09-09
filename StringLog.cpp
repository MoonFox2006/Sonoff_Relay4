#include "StringLog.h"

uint16_t StringLog::lines() {
  uint16_t result = 0;
  uint16_t len = _log.length();

  for (uint16_t i = 0; i < len; ++i) {
    if (_log[i] == '\n')
      ++result;
  }
  if ((len > 0) && (_log[len - 1] != '\n')) // Counting last line if it is not empty
    ++result;

  return result;
}

String StringLog::line(uint16_t index) {
  String result;
  uint16_t len = _log.length();
  uint16_t startPos, endPos;

  startPos = 0;
  while (index > 0) { // Skip (index - 1) lines
    while ((startPos < len) && (_log[startPos] != '\n')) // Find new line character
      ++startPos;
    if (startPos < len) { // Found new line character
      ++startPos; // First character on new line
      --index;
    } else
      break;
  }
  if (startPos < len) {
    endPos = startPos;
    while ((endPos < len) && (_log[endPos] != '\n')) // Find next new line character
      ++endPos;
    result = _log.substring(startPos, endPos);
  }

  return result;
}

String StringLog::encodeStr(const String& str) {
  String result;

  for (uint16_t i = 0; i < str.length(); ++i) {
    char ch = str[i];
    if (ch == '"')
      result += F("&quot;");
    else if (ch == '<')
      result += F("&lt;");
    else if (ch == '>')
      result += F("&gt;");
    else
      result += ch;
  }

  return result;
}

size_t StringLog::write(uint8_t ch) {
  if ((ch == '\t') || (ch == '\n') || (ch >= ' ')) { // Ignore control characters except tab and new line
    uint16_t len = _log.length();

    if (len >= maxLogSize) { // Compacting log by removing first line or half of log
      uint16_t i = 0;

      while ((i < len) && (_log[i] != '\n')) // Find first new line character
        ++i;
      ++i;
      if (i < len)
        _log.remove(0, i);
      else
        _log.remove(0, maxLogSize / 2);
    }

    _log += (char)ch;
  }

  if (_duplicate)
    _duplicate->write(ch);

  return sizeof(ch);
}
