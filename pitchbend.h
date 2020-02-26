#ifndef _pitchbend_
#define _pitchbend_

#define AVERAGE 256


class pitchbend
{
  public:
    pitchbend();
    bool has_changed();
    void update();
    void set_value(int PB);
    int get_value();

  private:
    unsigned int last_event_time;
    int value, previous_value;
    int values[AVERAGE];
    int rolling = 0;
    bool changed;
};



#endif
