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
  current_percentage = (analogRead(BATT_PIN) - min_val) / (max_val - min_val) * 100;
  if (current_percentage > 100) current_percentage = 100;
  if (current_percentage < 0) current_percentage = 0;
}

bool battery::update()
{
  if (millis() - last_read_time > response_time)
  {
    last_read_time = millis();
    current_percentage = (analogRead(BATT_PIN) - min_val) / (max_val - min_val) * 100;
    if (current_percentage > 100) current_percentage = 100;
    if (current_percentage < 0) current_percentage = 0;
    if (current_percentage < 10)
    {
      ssd.draw_low_batt();
      return true;
    }
  }
  return false;
}


int battery::display_percentage()
{
  display.clearDisplay();
  display.setCursor(30, 05);
  display.setTextSize(3);
  display.print("BATT");
  display.setCursor(30, 40);
  display.setTextSize(2);
  display.print(current_percentage);
  display.print("%");
  display.display();
}

