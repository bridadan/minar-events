#include "mbed-drivers/mbed.h"
#include "minar-events/interrupt-in.h"

class MyClass {
public:
  MyClass(PinName pin, const char* msg)
  : led(pin), msg(msg) {
  }

  void func() {
    led = !led;
    printf(msg);
  }

private:
  DigitalOut led;
  const char* msg;
};

DigitalOut led1(LED1);

int count = 0;

minar::events::InterruptIn buttonInterrupt(SW2);
MyClass myClass(LED2, "Button pressed!\r\n");

void periodicTask() {
  led1 = !led1;
  printf("Periodic task %d.\r\n", count++);
}

void app_start(int, char *[])
{
  buttonInterrupt.rise(&myClass, &MyClass::func);
  minar::Scheduler::postCallback(periodicTask)
                    .period(minar::milliseconds(1000));
}