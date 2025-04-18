#ifndef _analog_
#define _analog_

/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing analog_inputs
*/



class analog_input
{
  public:
    analog_input();
    analog_input(int _pin, int _biais = 0 , unsigned long _response_time = 0, int _biais_offset = 0, float _scaling_factor = 1.);
    
    bool update();
    int value();
    void calibrate();
    void set_biais(int _biais);
    void set_invert(bool _inverted);
    void set_scaling_factor(float _scaling_factor);
    void compute_scaling_factor(int target);
    bool has_changed();
    void set_min_max(int _min, int _max);
    int up_down();
    void calibrate_min_max();
    void precalibrate_min_max();
    void set_input_range(int ir);
    int get_input_range();

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
    bool inverted = false;
    int biased_min = 0, biased_max = 0,input_range = 0;
    int target_output = 0;
    
    


};



#endif
