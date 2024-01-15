/*
  ControlInterrupt.h - A library for handling multiple buttons using a single interrupt.
                       This is done by using an interrupt pin effectively as the ground,
                       eliminating the need for additional components.
  Authors: Svizel_pritula 05/05/2019
           TheCodeGeek 01/13/2024
*/
#ifndef ControlInterrupt_h
#define ControlInterrupt_h
#include <Arduino.h>
class ControlInterrupt
{
public:
  ControlInterrupt(int commonPin, int arrLength, int buttonPins[]);
  void begin();
  void configureCommon();
  void configureDistinct();
  void press(int button);

private:
  int _commonPin;
  int _arrLength;
  int _buttonPins[];
  void pressInterrupt();
};
#endif