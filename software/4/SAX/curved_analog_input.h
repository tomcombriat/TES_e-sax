#ifndef _curved_analog_
#define _curved_analog_


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the include file for the class managing "curved" analog input: mainly for the breath sensor
*/



class curved_analog_input
{
  public:
    curved_analog_input();
    curved_analog_input(int _pin, short _global_max , int _biais  , unsigned long _response_time, short _N_bits_low, short _N_bits_high);

    bool update();
    int MSB(), LSB();
    void calibrate();
    void set_sensitivity(short _sensitivity);
    short get_sensitivity();
    void set_curvature(short _curvature_index);
    short get_curvature();
    bool has_changed();
    void set_min_max(short _min, short _max);


  private:
    int pin;
    int previous_raw_value=0;
    int output_value = 0 ;
    float scaling_factor, curvature;
    short min_output=0, max_output=127;
    short biais, current_max, sensitivity=0, curvature_index=0,global_max;
    bool changed = false;
    unsigned long response_time;
    unsigned long last_read_time = 0;
    void compute_coef();
    short N_bits_low, N_bits_high;




};



#endif
