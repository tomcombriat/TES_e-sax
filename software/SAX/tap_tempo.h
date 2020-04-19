#ifndef _tempo_
#define _tempo_


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing the tap_tempo
*/




#include "button.h"

#define N_tap_max 20


class tap_tempo
{
  public:
    tap_tempo();

    void re_init_tap_tempo();
    void add_tap();
    unsigned long get_tempo_time();
    unsigned int get_tempo();
    void set_tempo(unsigned int);
    bool has_change();

  private:
    int N_tap = 0, last_entered = 0;
    //static const int N_tap_max = 20;
    unsigned long taps[N_tap_max];
    unsigned const long delay_before_reinit = 3000;
    unsigned long bounce_time = 50;
    unsigned long tap_time = 500;
    unsigned long previous_tap_time = 0;
    unsigned int tempo = 120;




};


#endif
