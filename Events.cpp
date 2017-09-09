#include <stdlib.h>
#include "Events.h"

Events::event_t *Events::peekEvent() {
  if (! _length)
    return NULL;

  return &_events[_top];
}

Events::event_t *Events::getEvent() {
  if (! _length)
    return NULL;

  Events::event_t *result = &_events[_top];
  if (++_top >= QUEUE_SIZE)
    _top = 0;
  --_length;

  return result;
}

bool Events::postEvent(Events::eventtype_t type, uint8_t data) {
  if (_length >= QUEUE_SIZE)
    return false;

  uint8_t index = (_top + _length) % QUEUE_SIZE;
  _events[index].type = type;
  _events[index].data = data;
  ++_length;

  return true;
}
