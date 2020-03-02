#ifndef _midi_cc_
#define _midi_cc_

class midi_cc
{
  public:
    midi_cc();
    midi_cc(byte control, int _biais=0);
    int get_value();
    void set_value(int _value);
    void increment_biais(int increment);
    void set_control(byte _control);
    byte get_control();
    void update();
    bool has_changed();

  private:
    int value, previous_value;
    int biais;
    byte control;
    bool changed;
    float max_accessible_range = 127;
    unsigned long last_biais_time, last_event_time;
};



#endif

