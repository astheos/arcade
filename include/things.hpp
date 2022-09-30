#include "canvas.hpp"
#include "devices.hpp"

#ifndef THINGS_HPP
#define THINGS_HPP

namespace things {
  const int inputScreenPin = 2;
  const int clockScreenPin = 3;
  const int loadScreenPin = 4;

  const int inputDisplayPin = 6;
  const int clockDisplayPin = 7;
  const int timeDisplayValue = 10;

  const int levelPin = A0;
  const int brightPin = A1;
  const int firstPin = A2;
  const int secondPin = A3;

  const int leftPin = 10;
  const int rightPin = 11;
  const int topPin = 12;
  const int bottomPin = 13;

  const int period = 25;

  devices::screen screen(
    inputScreenPin,
    clockScreenPin,
    loadScreenPin
  );

  devices::display display(
    inputDisplayPin,
    clockDisplayPin,
    timeDisplayValue
  );

  devices::knob level(levelPin);
  devices::knob bright(brightPin);
  devices::knob first(firstPin);
  devices::knob second(secondPin);

  devices::button left(leftPin);
  devices::button right(rightPin);
  devices::button top(topPin);
  devices::button bottom(bottomPin);

  canvas::frame frame;
  canvas::layer layer;
}

#endif