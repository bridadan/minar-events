#include "mbed-drivers/mbed.h"
#include "minar-events/timeout.h"

DigitalOut led1(LED1);

minar::events::Timeout timeoutInterrupt;

void cancelCallback() {
  printf("Canceling\r\n");
  timeoutInterrupt.detach();
}

void flip3() {
  led1 = !led1;
  printf("Shouldn't get here\r\n");
}

void flip2() {
  led1 = !led1;
  printf("Flip2\r\n");
  timeoutInterrupt.attach(&flip3, 1.0);
  timeoutInterrupt.attach(&cancelCallback, 0.5);
}

void flip1() {
  led1 = !led1;
  printf("Flip\r\n");
  timeoutInterrupt.attach_ms(&flip2, 5);
}

void app_start(int, char *[])
{
  printf("app_start\r\n");
  timeoutInterrupt.attach(&flip1, 1.0);
}