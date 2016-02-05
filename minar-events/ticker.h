#ifndef MINAR_EVENTS_TICKER_H
#define MINAR_EVENTS_TICKER_H

#include "mbed-drivers/mbed.h"

namespace minar {
namespace events {
class Ticker {
public:
  Ticker() {
  }

  void attach(void(*fptr)(void), float t) {
    _fptr.attach(fptr);
    _ticker.attach(this, &Ticker::callback, t);
  }

  template<typename T>
  void attach(T *tptr, void(T::*mptr)(void), float t){
    _fptr.attach(tptr, mptr);
    _ticker.attach(this, &Ticker::callback, t);
  }

  void attach_us(void(*fptr)(void), uint32_t t) {
    _fptr.attach(fptr);
    _ticker.attach_us(this, &Ticker::callback, t);
  }

  template<typename T>
  void attach_us(T *tptr, void(T::*mptr)(void), uint32_t t){
    _fptr.attach(tptr, mptr);
    _ticker.attach_us(this, &Ticker::callback, t);
  }

  void detach() {
    _ticker.detach();
    minar::Scheduler::cancelCallback(_handle);
    _handle = NULL;
  }

private:
  void callback() {
    _handle = minar::Scheduler::postCallback(_fptr).getHandle();
  }

  mbed::util::FunctionPointer0<void> _fptr;
  minar::callback_handle_t _handle;
  mbed::Ticker _ticker;
};
}
}

#endif
