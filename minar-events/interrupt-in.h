#ifndef MINAR_EVENTS_INTERRUPT_IN_H
#define MINAR_EVENTS_INTERRUPT_IN_H

#include "mbed-drivers/mbed.h"

namespace minar {
namespace events {
class InterruptIn {
public:
  InterruptIn(PinName pin) : _interrupt(pin) {
  }

  void rise(void(*fptr)(void)) {
    this->_fptr.attach(fptr);
    _interrupt.rise(this, &InterruptIn::callback);
  }

  template<typename T>
  void rise(T *tptr, void(T::*mptr)(void)){
    this->_fptr.attach(tptr, mptr);
    _interrupt.rise(tptr, mptr);
  }

  void fall(void(*fptr)(void)) {
    this->_fptr.attach(fptr);
    _interrupt.fall(this, &InterruptIn::callback);
  }

  template<typename T>
  void fall(T *tptr, void(T::*mptr)(void)){
    this->_fptr.attach(tptr, mptr);
    _interrupt.fall(tptr, mptr);
  }

private:
  void callback() {
    minar::Scheduler::postCallback(_fptr);
  }

  mbed::InterruptIn _interrupt;
  mbed::util::FunctionPointer0<void> _fptr;
};
}
}
#endif
