#include "mbed-drivers/mbed.h"
#include "minar-events/interrupt-in.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);

int count = 0;

minar::events::InterruptIn buttonInterrupt(SW2);

void buttonPressedTask() {
  led2 = !led2;
  printf("Button pressed!\r\n");
}

void periodicTask() {
  led1 = !led1;
  printf("Periodic task %d.\r\n", count++);
}

void app_start(int, char *[])
{
  buttonInterrupt.rise(buttonPressedTask);
  minar::Scheduler::postCallback(periodicTask)
                    .period(minar::milliseconds(1000));
}