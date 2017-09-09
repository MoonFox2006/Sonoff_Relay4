#include <Arduino.h>
#include "Button.h"

void Button::update() {
  if (digitalRead(btnPin) == btnLevel) { // Button pressed
    if (_tickPressed < 65535) {
      ++_tickPressed;
      if (_tickPressed == DEBOUNCE_TIME / TICKER_TIME) {
        doCallback(BTN_PRESSED);
      } else if (_tickPressed == LONG_TIME / TICKER_TIME) {
        doCallback(BTN_LONGPRESSED);
      }
    }
  } else { // Button released
    if (_tickDouble)
      --_tickDouble;
    if (_tickPressed) { // Was pressed
      if (_tickPressed >= LONG_TIME / TICKER_TIME) {
        doCallback(BTN_LONGCLICK);
        _tickDouble = 0;
      } else if (_tickPressed >= DEBOUNCE_TIME / TICKER_TIME) {
        if (_tickDouble) {
          doCallback(BTN_DBLCLICK);
          _tickDouble = 0;
        } else {
          doCallback(BTN_CLICK);
          _tickDouble = DOUBLE_TIME / TICKER_TIME;
        }
      } else {
        doCallback(BTN_RELEASED);
        _tickDouble = 0;
      }
      _tickPressed = 0;
    }
  }
}

Button::buttonstate_t Button::getState() {
  buttonstate_t result = BTN_RELEASED;

  if (digitalRead(btnPin) == btnLevel) { // Button pressed
    if (_tickPressed >= LONG_TIME / TICKER_TIME)
      result = BTN_LONGPRESSED;
    else if (_tickPressed >= DEBOUNCE_TIME / TICKER_TIME)
      result = BTN_PRESSED;
  } else { // Button released
    if (_tickPressed) {
      if (_tickPressed >= LONG_TIME / TICKER_TIME)
        result = BTN_LONGCLICK;
      else if (_tickPressed >= DEBOUNCE_TIME / TICKER_TIME) {
        if (_tickDouble)
          result = BTN_DBLCLICK;
        else
          result = BTN_CLICK;
      }
    }
  }

  return result;
}

void Button::tickerProc(Button *_this) {
  _this->update();
}
