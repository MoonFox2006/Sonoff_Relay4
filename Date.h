#ifndef __DATE_H
#define __DATE_H

#include <WString.h>

bool isLeapYear(int16_t year); // Високосный ли год?
int8_t lastDayOfMonth(int8_t month, int16_t year); // Число последнего дня месяца

void parseUnixTime(uint32_t unixtime, int8_t& hour, int8_t& minute, int8_t& second, uint8_t& weekday, int8_t& day, int8_t& month, int16_t& year); // Разобрать время в формате UNIX-time (количество секунд с 01.01.1970)
uint32_t combineUnixTime(int8_t hour, int8_t minute, int8_t second, int8_t day, int8_t month, int16_t year); // Собрать время в формат UNIX-time

String timeToStr(int8_t hour, int8_t minute, int8_t second); // Время в строку
String timeToStr(uint32_t unixtime); // Время в формате UNIX-time в строку
String dateToStr(int8_t day, int8_t month, int16_t year); // Дата в строку
String dateToStr(uint32_t unixtime); // Дата в формате UNIX-time в строку
String timeDateToStr(int8_t hour, int8_t minute, int8_t second, int8_t day, int8_t month, int16_t year); // Время и дата в строку
String timeDateToStr(uint32_t unixtime); // Время и дата в формате UNIX-time в строку
String dateTimeToStr(int8_t day, int8_t month, int16_t year, int8_t hour, int8_t minute, int8_t second); // Дата и время в строку
String dateTimeToStr(uint32_t unixtime); // Дата и время в формате UNIX-time в строку

String weekdayName(uint8_t weekday); // Название дня недели (3 буквы, английский язык, 0..6 - понедельник..воскресенье)
String monthName(int8_t month); // Название месяца (3 буквы, английский язык)

#endif
