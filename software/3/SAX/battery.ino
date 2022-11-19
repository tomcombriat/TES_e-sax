/*
      Combriat 2018, 2019, 2020, 2021
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the include file for the class managing the battery
*/

#include "battery.h"
#include "screen.h"

battery::battery(int _pin, int _min_val, int _max_val, unsigned long _response_time)
{
  pin = _pin;
  min_val = _min_val;
  max_val = _max_val;
  response_time = _response_time;
  last_read_time = millis();
  
}

void battery::update()
{
  if (millis() - last_read_time > response_time)
  {
    last_read_time = millis();
    value = ((analogRead(pin)-min_val)<<8)/(max_val-min_val);
    if (value >255) value = 255;
    else if (value <0) value = 0;
  }

}


int battery::get_value()
{
return value;
}
