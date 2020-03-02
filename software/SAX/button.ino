#include "button.h"



/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the cluss file for the class managing buttons (modifiers and joystick)
*/





/*

       LOGIC : 0 = PRESSED

*/
button::button() {};

button::button(int _pin, bool inverse, unsigned long _response_time)
{
  if (_pin != -1)
  {
    pinMode(_pin, INPUT_PULLUP);
    delay(20);
    pin = _pin;
    previous_state = digitalRead(pin);
  }
  else 
  {
    manual = true;
    last_manual_input = !inverse;
    
  }
  been_pressed = false;
  been_released = false;
  response_time = _response_time;
  inverse_logic = inverse;
  

}

bool button::is_pressed()
{
  return pressed;
}

bool button::has_been_pressed()
{
  if (been_pressed)
  {
    //been_pressed = false;
    return true;
  }
  return false;
}


bool button::has_been_released()
{
  if (been_released)
  {
    //been_released = false;
    return true;
  }
  return false;
}

void button::manual_input(bool _input)
{
  last_manual_input = _input;
}

void button::update()
{
  pressed = false;
  been_pressed = false;
  been_released = false;
  been_released_after_long_press = false;
  been_long_pressed = false;
  if (millis() - last_event_time > response_time)
  {
    bool state;
    if (!manual) state = digitalRead(pin);
    else state = last_manual_input;
    if (inverse_logic) state = !state;

    if (state != previous_state)     last_event_time = millis();
    if (!state)  // is pressed
    {
      pressed = true;
      if (previous_state) //not pressed before
      {
        been_pressed = true;
        last_press_time = millis();
      }
      been_released = false;

      if (!previous_state && (millis() - last_press_time > 1000))
      {
        been_long_pressed = true;  //pressed before and still pressed for 1sec
      }
    }
    else   //not pressed
    {
      pressed = false;
      if (!previous_state) //pressed before
      {
        been_released = true;
        if (millis() - last_press_time > 1000) been_released_after_long_press = true;
      }
      else
      {
        been_released = false;
      }
      been_pressed = false;
      //been_long_pressed = false;

    }
    previous_state = state;
  }
}

void button::set_pin(int _pin)
{
  pin = _pin;
  pinMode(_pin, INPUT_PULLUP);
  delay(20);
  previous_state = digitalRead(pin);
  been_pressed = false;
  been_released = false;
}

bool button::has_been_long_pressed()
{
  if (been_long_pressed)
  {
    //been_long_pressed = false;
    return true;
  }
  return false;
}

bool button::has_been_released_after_long_press()
{
  return been_released_after_long_press;
}

