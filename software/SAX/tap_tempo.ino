#include "tap_tempo.h"


tap_tempo::tap_tempo()
{
  for (int i = 0; i < N_tap_max; i++) taps[i] = 0;
  last_entered = 0;
}



void tap_tempo::re_init_tap_tempo()
{
  for (int i = 0; i < N_tap_max; i++) taps[i] = 0;
  last_entered = 0;
}


void tap_tempo::add_tap()
{

  unsigned long current_time = millis();
  if (current_time - taps[last_entered] > bounce_time)
  {
    if (current_time - taps[last_entered] < delay_before_reinit) last_entered += 1;
    else re_init_tap_tempo();

    if (last_entered == N_tap_max) last_entered = 0;
    taps[last_entered] = current_time;



    int N = 0, second_ind, first_ind;
    unsigned long new_tap_time = 0;
    for (int i = 0 ; i < N_tap_max - 1; i++)
    {
      first_ind = last_entered - i;
      second_ind = last_entered - (i + 1);
      if (first_ind < 0) first_ind += N_tap_max;
      if (second_ind < 0) second_ind += N_tap_max;

      if (taps[second_ind] != 0)
      {
        N += 1;
        new_tap_time += taps[first_ind] - taps[second_ind];
      }
      else break;
    }

    if (N != 0)
    {
      new_tap_time /= N;
      tap_time = new_tap_time;
    }

  }
}

unsigned long tap_tempo::get_tempo_time()
{
  return tap_time;
}

unsigned long tap_tempo::get_tempo()
{
  return tempo;
}

void tap_tempo::set_tempo(unsigned long tempo)
{
  tap_time = 60000 / tempo;
}

bool tap_tempo::has_change()
{
  if (tap_time != previous_tap_time)
  {
    tempo =  60000 / tap_time ;
    previous_tap_time = tap_time;
    return true;
  }
  return false;
}

