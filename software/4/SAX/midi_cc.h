#ifndef _midi_cc_
#define _midi_cc_


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class MIDI control changes
*/


class midi_cc
{
  public:
    midi_cc();
    midi_cc(byte control, byte _biais=0);
    int get_value();
    void set_value(int _value);
    byte get_biais();
    void set_biais(byte _biais);
    void increment_biais(int increment);
    void set_control(byte _control);
    byte get_control();
    bool update();
    bool has_changed();

  private:
    int value, previous_value;
    byte biais;
    byte control;
    bool changed;
    float max_accessible_range = 127;
    unsigned long last_biais_time, last_event_time;
};



#endif
