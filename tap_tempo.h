#ifndef _tempo_
#define _tempo_


#include "button.h"




class tap_tempo
{
  public:
    tap_tempo();

    void re_init_tap_tempo();
    void add_tap();
    unsigned long get_tempo_time();
    unsigned long get_tempo();
    void set_tempo(unsigned long);
    bool has_change();

  private:
    int N_tap = 0, last_entered = 0;
    static const int N_tap_max = 20;
    unsigned long taps[N_tap_max];
    unsigned long delay_before_reinit = 2000;
    unsigned long bounce_time = 50;
    unsigned long tap_time = 500;
    unsigned long previous_tap_time = 0;
    unsigned long tempo = 120;




};


#endif
