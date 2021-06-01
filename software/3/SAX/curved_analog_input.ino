#include "curved_analog_input.h"



curved_analog_input::curved_analog_input() {}

curved_analog_input::curved_analog_input(int _pin, short _global_max , int _biais , unsigned long _response_time, float _scaling_factor)
{
  pin = _pin;
  pinMode(pin, INPUT);
  global_max = _global_max;
  biais = biais;
  response_time = _response_time;
  scaling_factor = _scaling_factor;
  min_output = 0;
  max_output = 127;
  calibrate();
}


bool curved_analog_input::update()
{
  changed = false;
  if (millis() - last_read_time > response_time)
  {
    last_read_time = millis();
    int value = analogRead(pin) - biais;

    if (value != previous_raw_value)
    {
      previous_raw_value = value;
      int tamp_output_value = scaling_factor * (value + curvature * value * (value - current_max));
      if (tamp_output_value > max_output) tamp_output_value = max_output;
      if (tamp_output_value < min_output) tamp_output_value = min_output;
      if (tamp_output_value != output_value) {
        changed = true;
        output_value = tamp_output_value;
      }
    }
  }
}


int curved_analog_input::value()
{
  return output_value;
}

void curved_analog_input::calibrate()
{
  biais = analogRead(pin);
  compute_coef();
}


void curved_analog_input::set_sensitivity(short _sensitivity)
{
  sensitivity = _sensitivity;
  if (sensitivity > 10) sensitivity = 10;
  if (sensitivity < -10) sensitivity = -10;
  compute_coef();
}

short curved_analog_input::get_sensitivity() {
  return sensitivity;
}

void curved_analog_input::set_curvature(short _curvature_index)
{
  curvature_index = _curvature_index;
  if (curvature_index > 10) curvature_index = 10;
  if (curvature_index < -10) curvature_index = -10;

  compute_coef();
}

short curved_analog_input::get_curvature() {
  return curvature_index;
}

bool curved_analog_input::has_changed() {
  return changed;
}

void curved_analog_input::set_min_max(short _min, short _max)
{
  max_output = _max;
  min_output = _min;
}


void curved_analog_input::compute_coef()
{
  current_max = (global_max - biais) - 1.*(global_max - biais) * sensitivity / 10;
  scaling_factor = 1.*max_output / current_max;
  curvature = 1.*curvature_index / (10 * current_max);
}



