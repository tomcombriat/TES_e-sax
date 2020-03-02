#include "pitchbend.h"


pitchbend::pitchbend() {};

void pitchbend::update()
{
  changed = false;
  if (millis() - last_event_time > PITCHBEND_MIN_TIME)
  {
    last_event_time = millis();
    value = 0;
    for (int i=0;i<AVERAGE;i++) value += values[i];
    value = value >>8;
    if (abs(value) <15) value = 0;
    if (abs(value - previous_value) > 30)
    {
      changed = true;
      previous_value = value;
      MIDI.sendPitchBend(value, midi_channel);
    }
  }
}

bool pitchbend::has_changed()
{
  return changed;
}


void pitchbend::set_value(int _value)
{
  values[rolling] = _value;
  rolling++;
  if (rolling >= AVERAGE) rolling = 0;

}

int pitchbend::get_value()
{
  return value;
}


