/*
  ControlInterrupt.h - A library for handling multiple buttons using a single interrupt.
                       This is done by using an interrupt pin effectively as the ground,
                       eliminating the need for additional components.
  Authors: Svizel_pritula 05/05/2019
           TheCodeGeek 01/13/2024
*/
#include <Arduino.h>
#include <ControlInterrupt.h>

unsigned long lastFire;

ControlInterrupt::ControlInterrupt(int commonPin, int arrLength, int buttonPins[])
{
  _commonPin = commonPin;
  _arrLength = arrLength;
  _buttonPins[arrLength] = buttonPins;

  lastFire = 0;
}

void ControlInterrupt::begin()
{
  configureCommon(); // Setup pins for  interrupt
  attachInterrupt(digitalPinToInterrupt(_commonPin), this->pressInterrupt, FALLING);
  Serial.begin(9600);
}

void ControlInterrupt::pressInterrupt()
{ // ISR
  if (millis() - lastFire < 200)
  { // Debounce
    return;
  }
  lastFire = millis();

  configureDistinct(); // Setup  pins for testing individual buttons
//for (int i = 0; i < sizeof(_buttonPins) / sizeof(int); i++)
  for (int i = 0; i < _arrLength; i++)
  { // Test each button for press
    if (!digitalRead(_buttonPins[i]))
    {
      press(i);
    }
  }

  configureCommon(); // Return to original  state
}

void ControlInterrupt::configureCommon()
{
  pinMode(_commonPin, INPUT_PULLUP);

  for (int i = 0; i < _arrLength; i++)
  {
    pinMode(_buttonPins[i], OUTPUT);
    digitalWrite(_buttonPins[i], LOW);
  }
}

void ControlInterrupt::configureDistinct()
{
  pinMode(_commonPin, OUTPUT);
  digitalWrite(_commonPin, LOW);

  for (int i = 0; i < _arrLength; i++)
  {
    pinMode(_buttonPins[i], INPUT_PULLUP);
  }
}

void ControlInterrupt::press(int button)
{ // Our handler
  String label; // This stores the string to print when controls are used

  Serial.print(button + 1);
  Serial.print(": ");
  switch (button)
  {
  case 0:
    // statement
    label = "UP";
    break;
  case 1:
    // statement
    label = "DOWN";
    break;
  case 2:
    // statement
    label = "CLEAR";
    break;
  case 3:
    // statement
    label = "BACK";
    break;
  case 4:
    // statement
    label = "LEFT";
    break;
  case 5:
    // statement
    label = "ENTER";
    break;
  case 6:
    // statement
    label = "RIGHT";
    break;
  default:
    // statement
    break;
  }
  Serial.println(label);
}