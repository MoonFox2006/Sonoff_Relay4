#ifndef __EVENTS_H
#define __EVENTS_H

#include <inttypes.h>

class Events {
public:
  static const uint8_t QUEUE_SIZE = 32;

  enum eventtype_t : uint8_t { EVT_BTNPRESSED, EVT_BTNCLICK, EVT_BTNDBLCLICK, EVT_BTNLONGPRESSED, EVT_BTNLONGCLICK, EVT_MOTION };
  struct event_t {
    eventtype_t type : 3;
    uint8_t data : 5;
  };

  Events() : _top(0), _length(0) {}

  uint8_t getCount() const {
    return _length;
  }
  event_t *peekEvent();
  event_t *getEvent();
  bool postEvent(eventtype_t type, uint8_t data = 0);

protected:
  event_t _events[QUEUE_SIZE];
  volatile uint8_t _top, _length;
};

#endif
