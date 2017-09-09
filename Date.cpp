#ifdef ESP8266
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif
#include "Date.h"

static const int8_t daysInMonth[] PROGMEM = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static const char weekdayNames[][4] PROGMEM = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
static const char monthNames[][4] PROGMEM = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

const uint16_t EPOCH_TIME_2000 = 10957; // Days from 01.01.1970 to 01.01.2000
const uint16_t EPOCH_TIME_2017 = 17167; // Days from 01.01.1970 to 01.01.2017

const char dateSeparator = '.';
const char timeSeparator = ':';

bool isLeapYear(int16_t year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

int8_t lastDayOfMonth(int8_t month, int16_t year) {
  int8_t result = pgm_read_byte(daysInMonth + month - 1);
  if ((month == 2) && isLeapYear(year))
    result++;

  return result;
}

void parseUnixTime(uint32_t unixtime, int8_t& hour, int8_t& minute, int8_t& second, uint8_t& weekday, int8_t& day, int8_t& month, int16_t& year) {
  second = unixtime % 60;
  unixtime /= 60;
  minute = unixtime % 60;
  unixtime /= 60;
  hour = unixtime % 24;
  uint16_t days = unixtime / 24;
  weekday = (days % 7) + 3; // 1 Jan 1970 is Thursday
  bool leap;
  if (days >= EPOCH_TIME_2017) {
    year = 2017;
    days -= EPOCH_TIME_2017;
  } else if (days >= EPOCH_TIME_2000) {
    year = 2000;
    days -= EPOCH_TIME_2000;
  } else
    year = 1970;
  for (; ; year++) {
    leap = isLeapYear(year);
    if (days < 365 + leap)
      break;
    days -= 365 + leap;
  }
  for (month = 1; ; month++) {
    uint8_t daysPerMonth = pgm_read_byte(daysInMonth + month - 1);
    if (leap && (month == 2))
      daysPerMonth++;
    if (days < daysPerMonth)
      break;
    days -= daysPerMonth;
  }
  day = days + 1;
}

uint32_t combineUnixTime(int8_t hour, int8_t minute, int8_t second, int8_t day, int8_t month, int16_t year) {
  uint16_t days = day - 1;
  int16_t y;

  if (year >= 2017) {
    days += EPOCH_TIME_2017;
    y = 2017;
  } else if (year >= 2000) {
    days += EPOCH_TIME_2000;
    y = 2000;
  } else
    y = 1970;
  for (; y < year; y++)
    days += 365 + isLeapYear(y);
  for (y = 1; y < month; y++)
    days += pgm_read_byte(daysInMonth + y - 1);
  if ((month > 2) && isLeapYear(year))
    days++;

  return (((uint32_t)days * 24 + hour) * 60 + minute) * 60 + second;
}

String timeToStr(int8_t hour, int8_t minute, int8_t second) {
  String result;

  if (hour >= 0) {
    if (hour < 10)
      result += '0';
    result += String(hour);
  }
  if (minute >= 0) {
    result += timeSeparator;
    if (minute < 10)
      result += '0';
    result += String(minute);
  }
  result += timeSeparator;
  if (second < 10)
    result += '0';
  result += String(second);

  return result;
}

String timeToStr(uint32_t unixtime) {
  int8_t hh, mm, ss;
  uint8_t wd;
  int8_t d, m;
  int16_t y;

  parseUnixTime(unixtime, hh, mm, ss, wd, d, m, y);

  return timeToStr(hh, mm, ss);
}

String dateToStr(int8_t day, int8_t month, int16_t year) {
  String result;

  if (day < 10)
    result += '0';
  result += String(day);
  result += dateSeparator;
  if (month < 10)
    result += '0';
  result += String(month);
  result += dateSeparator;
  result += String(year);

  return result;
}

String dateToStr(uint32_t unixtime) {
  int8_t hh, mm, ss;
  uint8_t wd;
  int8_t d, m;
  int16_t y;

  parseUnixTime(unixtime, hh, mm, ss, wd, d, m, y);

  return dateToStr(d, m, y);
}

String timeDateToStr(int8_t hour, int8_t minute, int8_t second, int8_t day, int8_t month, int16_t year) {
  return timeToStr(hour, minute, second) + ' ' + dateToStr(day, month, year);
}

String timeDateToStr(uint32_t unixtime) {
  int8_t hh, mm, ss;
  uint8_t wd;
  int8_t d, m;
  int16_t y;

  parseUnixTime(unixtime, hh, mm, ss, wd, d, m, y);

  return timeDateToStr(hh, mm, ss, d, m, y);
}

String dateTimeToStr(int8_t day, int8_t month, int16_t year, int8_t hour, int8_t minute, int8_t second) {
  return dateToStr(day, month, year) + ' ' + timeToStr(hour, minute, second);
}

String dateTimeToStr(uint32_t unixtime) {
  int8_t hh, mm, ss;
  uint8_t wd;
  int8_t d, m;
  int16_t y;

  parseUnixTime(unixtime, hh, mm, ss, wd, d, m, y);

  return dateTimeToStr(d, m, y, hh, mm, ss);
}

String weekdayName(uint8_t weekday) {
  String result;

  if (weekday < 7)
    result = FPSTR(weekdayNames[weekday]);

  return result;
}

String monthName(int8_t month) {
  String result;

  if ((month >= 1) && (month <= 12))
    result = FPSTR(monthNames[month - 1]);

  return result;
}
