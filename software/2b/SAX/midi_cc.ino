#include "midi_cc.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class MIDI control changes
*/




midi_cc::midi_cc() {};

midi_cc::midi_cc(byte _control, byte _biais) {
  value = 0;
  control = _control;
  previous_value = -1;
  biais = _biais;
  last_biais_time = 0;
  last_event_time = 0;
}

int midi_cc::get_value()
{
  return previous_value;
}

void midi_cc::set_value(int _value)
{
  value = _value;
}

byte midi_cc::get_biais()
{
  return biais;
}

void midi_cc::set_biais(byte _biais)
{
  biais = _biais;
}

void midi_cc::increment_biais(int increment)
{
  if (millis() - last_biais_time > CC_DELTA_TIME)  // just to limit increase in delta mode (not limited by analog_input timer)
  {
    int tamp_biais = biais + increment;
    if (tamp_biais > 127) tamp_biais = 127;
    if (tamp_biais < 0) tamp_biais = 0;
    biais = tamp_biais;
    last_biais_time = millis();
  }
}

void midi_cc::set_control(byte _control)
{
  control = _control;
}

byte midi_cc::get_control()
{
  return control;
}

bool midi_cc::update()
{
  changed = false;
  if (millis() - last_event_time > CC_MIN_TIME)
  {

    max_accessible_range = max((int) 127 - biais,(int) biais);
    int return_value = value * max_accessible_range / 127. + biais;
    if (return_value > 127) return_value = 127;
    if (return_value < 0) return_value = 0;
    


    if (return_value != previous_value)
    {
      last_event_time = millis();
      changed = true;
      previous_value = return_value;
      MIDI.sendControlChange(control, return_value, midi_channel);
      return true;
    }
  }
}

bool midi_cc::has_changed()
{
  return changed;
}
