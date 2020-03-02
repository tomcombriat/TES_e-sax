#include "analog_input.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the class file for the class managing analog_inputs
*/




analog_input::analog_input() {};


analog_input::analog_input(int _pin, int _biais, unsigned long _response_time, int _biais_offset , float _scaling_factor)
{
  pin = _pin;
  biais = _biais;
  response_time = _response_time;
  pinMode(pin, INPUT);
  biais_offset = _biais_offset;
  scaling_factor = _scaling_factor;
  min_value = -10000;
  max_value = 10000;
}

bool analog_input::has_changed()
{
  return changed;
}

bool analog_input::update()
{
  changed = false;
  if (millis() - last_read_time > response_time)
  {
    last_read_time = millis();
    int value = analogRead(pin);
    value = (value - (biais + biais_offset))*scaling_factor;
    if (value > max_value) value = max_value;
    else if (value < min_value) value = min_value;

    if (value != previous_raw_value)
    {
      if (previous_raw_value >100 && value <100) up = 1;
      else if (previous_raw_value < -100 && value > -100) up = -1;
      else up = 0;
      previous_raw_value = value;
      changed = true;   
    }
  }
  return changed;
}

int analog_input::value()
{
  return previous_raw_value;
}

void analog_input::calibrate()
{
  biais = analogRead(pin);
}

void analog_input::set_biais(int _biais)
{
  biais = _biais;
}

void analog_input::set_scaling_factor(float _scaling_factor)
{
  scaling_factor = _scaling_factor;
}

void analog_input::set_min_max(int min, int max)
{
  min_value = min;
  max_value = max;
}



int analog_input::up_down()
{
  int prev_up = up;
  up = 0;
  return prev_up;
}

