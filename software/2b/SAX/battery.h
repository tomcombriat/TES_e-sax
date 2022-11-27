#ifndef _battery_
#define _battery_

/*
      Combriat 2018, 2019, 2020, 2021
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the include file for the class managing the battery
*/


class battery
{
  public:
    battery(int _pin, int _min_val, int _max_val, unsigned long _response_time);
    void update();
    int get_value();
    

  private:
    int pin, min_val, max_val;
    unsigned long response_time, last_read_time;
    int value;

};



#endif
