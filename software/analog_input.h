#ifndef _analog_
#define _analog_


class analog_input
{
  public:
    analog_input();
    analog_input(int _pin, int _biais = 0 , unsigned long _response_time = 0, int _biais_offset = 0, float _scaling_factor = 1);
    
    bool update();
    int value();
    void calibrate();
    void set_biais(int _biais);
    void set_scaling_factor(float _scaling_factor);
    bool has_changed();
    void set_min_max(int _min, int _max);
    int up_down();

  private:
    int pin;
    int previous_raw_value;
    float scaling_factor;
    int min_value, max_value;
    int biais;
    int biais_offset;
    bool changed = false;
    unsigned long response_time;
    unsigned long last_read_time = 0;
    int up = 0;


};



#endif
