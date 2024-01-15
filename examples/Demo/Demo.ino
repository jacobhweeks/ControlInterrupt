#include <ControlInterrupt.h>

const int commonPin = 2;
const int buttonPins[] = {7,8,9,10,11,12,13};

ControlInterrupt controlInterrupt(commonPin, sizeof(buttonPins)/sizeof(int), buttonPins);

void setup() {
  // put your setup code here, to run once:
  controlInterrupt.begin();
}

void loop() {
  // Empty
}
