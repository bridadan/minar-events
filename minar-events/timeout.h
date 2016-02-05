#ifndef MINAR_EVENTS_TIMEOUT_H
#define MINAR_EVENTS_TIMEOUT_H

#include "mbed-drivers/mbed.h"

namespace minar {
namespace events {
class Timeout {
public:
  Timeout() {
  }

  void attach(void(*fptr)(void), float t) {
    _fptr.attach(fptr);
    _timeout.attach(this, &Timeout::callback, t);
  }

  template<typename T>
  void attach(T *tptr, void(T::*mptr)(void), float t){
    _fptr.attach(tptr, mptr);
    _timeout.attach(this, &Timeout::callback, t);
  }

  void attach_ms(void(*fptr)(void), uint32_t t) {
    _fptr.attach(fptr);
    _timeout.attach_us(this, &Timeout::callback, t * 1000);
  }

  template<typename T>
  void attach_ms(T *tptr, void(T::*mptr)(void), uint32_t t){
    _fptr.attach(tptr, mptr);
    _timeout.attach_us(this, &Timeout::callback, t * 1000);
  }

  void detach() {
    _timeout.detach();

    if (_handle) {
      minar::Scheduler::cancelCallback(_handle);
      _handle = NULL;
    }
  }

private:
  void callback() {
    _handle = minar::Scheduler::postCallback(_fptr).getHandle();
  }

  mbed::util::FunctionPointer0<void> _fptr;
  minar::callback_handle_t _handle;
  mbed::Timeout _timeout;
};
}
}

#endif
