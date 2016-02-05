#include "mbed-drivers/mbed.h"
#include "minar-events/ticker.h"

DigitalOut led1(D0);
DigitalOut led2(D1);

minar::events::Ticker tickerInterrupt;
int count = 0;

void flip() {
  if (count >= 20) {
    tickerInterrupt.detach();
  } else if (count == 10) {
    tickerInterrupt.detach();
    tickerInterrupt.attach_us(&flip, 50000);
  }

  led1 = !led1;

  printf("Flip %d\r\n", count++);


}

void app_start(int, char *[])
{
  printf("app_start\r\n");
  tickerInterrupt.attach(&flip, 0.1);
}