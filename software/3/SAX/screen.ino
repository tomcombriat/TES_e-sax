#include "screen.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing the screen
*/



screen::screen() {};

void screen::draw_title_value(String _title, int _value)
{
  int keyprint = _title.length() + 2 * _value;
  if (keyprint != previous_keyprint || _title != previous_title)
  {
    previous_keyprint = keyprint;
    previous_title = _title;
    changed = true;
    display.clearDisplay();
    display.fillRect(0, 0, 128, 20, 1);
    display.setTextSize(2);
    display.setTextColor(0);
    display.setCursor((128 - (_title.length()) * 12) / 2, 3);
    display.print(_title);
    display.setTextSize(4);
    display.setTextColor(1);
    if (_value < 10 && _value >= 0) display.setCursor(52, 34);
    else if (_value < 0 && _value > -10) display.setCursor(40 , 34);
    else if (_value > 9)  display.setCursor(40 , 34);
    else display.setCursor(28 , 34);
    display.print(_value);
  }
}

void screen::draw_title_value(String _title)
{
  int keyprint = _title.length() *2;
  if (keyprint != previous_keyprint || _title != previous_title)
  {
    previous_keyprint = keyprint;
    previous_title = _title;
    changed = true;
    display.clearDisplay();
    display.fillRect(0, 0, 128, 20, 1);
    display.setTextSize(2);
    display.setTextColor(0);
    display.setCursor((128 - (_title.length()) * 12) / 2, 3);
    display.print(_title);
    display.setTextColor(1);
  }
}


void screen::draw_title_value(String _title, String _value, int sub_value)
{
  int keyprint = _title.length() + 2 * _value.length() + 3 * sub_value;

  if (keyprint != previous_keyprint || _value != previous_value || _title != previous_title)
  {
    previous_title = _title;
    previous_keyprint = keyprint;
    previous_value = _value;
    changed = true;
    display.clearDisplay();
    display.fillRect(0, 0, 128, 20, 1);
    display.setTextSize(2);
    display.setTextColor(0);
    display.setCursor((128 - (_title.length()) * 12) / 2, 3);
    display.print(_title);
    display.setTextSize(4);
    display.setTextColor(1);
    display.setCursor((128 - (_value.length()) * 24) / 2, 34);
    display.print(_value);
    if (sub_value != 0)
    {
      display.setCursor(80, 40);
      display.setTextSize(2);
      display.print(sub_value);
    }
  }
}

void screen::draw_title_value(String _title, char _value, int sub_value)
{
  draw_title_value(_title, (String) _value, sub_value);
}

void screen::draw_low_batt()
{
  display.clearDisplay();
  display.setTextSize(2);
  changed = true;
  display.setTextColor(1);
  display.setCursor((128 - (11) * 12) / 2, 28);
  display.print("Low Battery");
}


void screen::draw_title_value(String _title, String * value, int N, int * _values , int sub_value)
{
  String _value = *value;
  int keyprint = _title.length() + 3 * sub_value + _values[N - 1] - N;

  if (keyprint != previous_keyprint || _value != previous_value || _title != previous_title)
  {
    previous_keyprint = keyprint;
    previous_value = _value;
    previous_title = _title;
    changed = true;
    display.clearDisplay();
    display.fillRect(0, 0, 128, 20, 1);
    display.setTextSize(2);
    display.setTextColor(0);
    display.setCursor((128 - (_title.length()) * 12) / 2, 3);
    display.print(_title);
    display.setTextSize(2);
    display.setTextColor(1);
    display.setCursor((128 - (_value.length()) * 12) / 2, 28);
    display.print(_value);
    if (sub_value != 0)
    {
      display.setCursor(110, 30);
      display.setTextSize(2);
      display.print(sub_value);
    }
    String enum_notes = String(_values[0]);
    for (int i = 1; i < N; i++)
    {
      enum_notes += String(' ');
      enum_notes += String(_values[i]);
    }
    display.setTextSize(1);
    display.setCursor((128 - (enum_notes.length()) * 6) / 2, 49);
    display.print(enum_notes);
  }
}

void screen::draw_title_value(String _title, char  value, int N, int * _values , int sub_value)
{
  String _value = String(value);
  int keyprint = _title.length() + 3 * sub_value + _values[N - 1] - N;

  if (keyprint != previous_keyprint || _value != previous_value || _title != previous_title)
  {
    previous_keyprint = keyprint;
    previous_value = _value;
    previous_title = _title;
    changed = true;
    display.clearDisplay();
    display.fillRect(0, 0, 128, 20, 1);
    display.setTextSize(2);
    display.setTextColor(0);
    display.setCursor((128 - (_title.length()) * 12) / 2, 3);
    display.print(_title);
    display.setTextSize(3);
    display.setTextColor(1);
    display.setCursor((128 - (_value.length()) * 18) / 2, 24);
    display.print(_value);
    if (sub_value != 0)
    {
      display.setCursor(75, 30);
      display.setTextSize(2);
      display.print(sub_value);
    }
    String enum_notes = String(_values[0]);
    for (int i = 1; i < N; i++)
    {
      enum_notes += String(' ');
      enum_notes += String(_values[i]);
    }
    display.setTextSize(1);
    display.setCursor((128 - (enum_notes.length()) * 6) / 2, 49);
    display.print(enum_notes);
  }
}





void screen::draw_single_value(String _value)
{
  int keyprint = _value.length();

  if (keyprint != previous_keyprint || _value != previous_value)
  {
    previous_keyprint = keyprint;
    previous_value = _value;
    changed = true;
    display.clearDisplay();
    display.setTextSize(5);
    display.setTextColor(1);
    display.setCursor((128 - (_value.length()) * 30) / 2, 15);
    display.print(_value);
  }
}

void screen::draw_standby_screen(int& _octave, int& _transpose, byte _global_mode, bool _delta_mode, byte _joystick, byte _joystick_bis, unsigned int  _tempo)
{
  //Serial.print(_octave);
  //Serial.print(" ");
  //Serial.println(octave);
  if (_octave != octave)
  {
    changed = true;
    octave = _octave;
  }
  if (_transpose != transpose)
  {
    changed = true;
    transpose = _transpose;
  }
  if (_global_mode != global_mode)
  {
    changed = true;
    global_mode = _global_mode;
  }
  if (_delta_mode != delta_mode)
  {
    changed = true;
    delta_mode = _delta_mode;
  }
  if (_joystick != joystick)
  {
    changed = true;
    joystick = _joystick;
  }
  if (_joystick_bis != joystick_bis)
  {
    changed = true;
    joystick_bis = _joystick_bis;
  }
  if (_tempo != tempo)
  {
    changed = true;
    tempo = _tempo;
  }
  if (changed)
  {
    previous_keyprint = 666;

    display.clearDisplay();
    display.drawFastHLine(0, 63, 128, 1);
    display.drawFastHLine(0, 53, 128, 1);
    display.drawFastVLine(0, 53, 10, 1);
    display.drawFastVLine(127, 53, 10, 1);
    display.fillRect(0, 53, joystick, 5, 1);
    display.fillRect(0, 58, joystick_bis, 5, 1);

    if (delta_mode)
    {
      display.setCursor(0, 0);
      display.setTextSize(6);
      display.print("D");
    }
    display.setTextSize(2);
    display.setCursor(100, 5);
    display.print(octave);
    display.setCursor(100, 30);
    display.print(transpose);

    if (global_mode == MODE_ARPEGIO)
    {
      display.setCursor(50, 0);
      display.print(tempo);
      display.setTextSize(2);
      display.setCursor(60, 20);
      display.print(arp[0].get_name());  // getting out of my logic… bah.
      display.setCursor(75, 28);
      display.print(arp[1].get_name());
      display.setCursor(60, 36);
      display.print(arp[2].get_name());
    }

    if (global_mode == MODE_ARPEGIO_RAND)
    {
      display.setCursor(50, 0);
      display.print(tempo);
      display.setTextSize(2);
      display.setCursor(60, 20);
      display.print(arp[0].get_name());  // getting out of my logic… bah.
      display.setCursor(75, 28);
      display.print(arp[1].get_name());
      display.setCursor(60, 36);
      display.print(arp[2].get_name());
    }

    else if (global_mode == MODE_EWI)
    {
      display.setTextSize(1);
      display.setCursor(60, 20);
      display.print(normal_up_modifier);  // getting out of my logic… bah.
      display.setCursor(68, 28);
      display.print(normal_mid_modifier);
      display.setCursor(60, 36);
      display.print(normal_down_modifier);
    }

    else if (global_mode == MODE_CHORD)
    {
      display.setTextSize(2);
      display.setCursor(60, 20);
      display.print(chords[0].get_name());  // getting out of my logic… bah.
      display.setCursor(75, 28);
      display.print(chords[1].get_name());
      display.setCursor(60, 36);
      display.print(chords[2].get_name());
    }


    display.setTextSize(3);
    display.setCursor(40, 25);
    display.print(global_modes[global_mode]);
  }
}

void screen::draw_progress_bar(byte val)
{
  display.clearDisplay();
  display.drawFastHLine(0, 63, 128, 1);
  display.drawFastHLine(0, 53, 128, 1);
  display.drawFastVLine(0, 53, 10, 1);
  display.drawFastVLine(127, 53, 10, 1);
  display.fillRect(0, 53, val, 10, 1);
  changed = true;
}





void screen::clear()
{
  if (previous_keyprint != 0)
  {
    previous_keyprint = 0;
    changed = true;
    display.clearDisplay();
  }
}

void screen::update()
{
  if (millis() - last_update_time > SCREEN_UPDATE_TIME && changed)
  {
    last_update_time = millis();
    display.display();
    changed = false;
  }
}

void screen::force_update()
{
  changed = true;
  update();
}

