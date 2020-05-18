#include "arpegio_mono.h"



/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing arpegiators
*/



arpegio_mono::arpegio_mono() {}

arpegio_mono::arpegio_mono(unsigned int N, float * times, int * notes)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  duration_scaling = int (times[N - 1] + 1);
}

arpegio_mono::arpegio_mono(unsigned int N, float * times, int * notes, char _name)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  arp_name = _name;
  duration_scaling = int (times[N - 1] + 1);
}

void arpegio_mono::set_notes(unsigned int N, float * times, int * notes)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  duration_scaling = int (times[N - 1] + 1);
}

void arpegio_mono::set_notes(unsigned int N, float * times, int * notes, char _name)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  arp_name = _name;
  duration_scaling = int (times[N - 1] + 1);

}

void arpegio_mono::set_notes(unsigned int N, float * times, int * notes, char _name, String * l_name)
{
  N_note_arp = N;
  times_arp = times;
  notes_arp = notes;
  arp_name = _name;
  long_name = l_name;
  duration_scaling = int (times[N - 1] + 1);
}


void arpegio_mono::set_tempo(unsigned long temp)
{
  duration = temp;
}


/*
  bool arpegio_mono::change(byte current_note) //could be optimized by checking only the next note, instead of a for loop. That is only 50micros for a 15 length arp so…
  {
  if (current_note != 0)
  {
    if (current_note != previous_note) // restart on changing note
    {
      previous_note = current_note;
      start();
    }

    float time_in_arp = ((millis() - start_time) % (duration * duration_scaling)) / (duration * 1.0); // compute fraction of time into loop (maybe better not to use floats ?)
    for (unsigned int i = 0; i < N_note_arp - 1; i++)
    {
      if (time_in_arp > times_arp[i] && time_in_arp < times_arp[i + 1] && notes_arp[i] != next_note - current_note )
      {
        if (notes_arp[i] != -255)
        {
          next_note = notes_arp[i] + current_note;
          return true;
        }
        else if (next_note != 0)
        {
          next_note = 0;
          return true;
        }
      }
    }
    if (time_in_arp > times_arp[N_note_arp - 1] && notes_arp[N_note_arp - 1] != next_note - current_note) // roll back to beginning
    {
      if (notes_arp[N_note_arp - 1] != -255)
      {
        next_note = notes_arp[N_note_arp - 1] + current_note;
        return true;
      }
      else if (next_note != 0)
      {
        next_note = 0;
        return true;
      }
    }
  }  // if (started)
  else {
    previous_note = 0;
    next_note = 0;
  }
  return false;  // arp not started
  }
*/

bool arpegio_mono::change(byte current_note) //Now 2micros!
{

  if (current_note != 0)
  {
    if (current_note != previous_note) // restart on changing note
    {
      previous_note = current_note;
      start();
    }

    //float time_in_arp = ((millis() - start_time) % (duration * duration_scaling)) / (duration * 1.0); // compute fraction of time into loop (maybe better not to use floats ?)
    if (millis() >= next_event_time)
    {
      float next_duration = 0.;
      

      if (next_index + 1 == N_note_arp) next_duration = duration_scaling  + times_arp[0] - times_arp[next_index]; //rollback
      else next_duration = times_arp[next_index + 1] - times_arp[next_index];

      if (notes_arp[next_index] != -255)   next_note = notes_arp[next_index] + current_note;
      else next_note = 0;  //silent note

      next_event_time += duration * next_duration ;
      next_index += 1;
      if (next_index == N_note_arp) next_index = 0; //rollback
      return true;
    }
  }  // if (current_note !=0)
  else {
    previous_note = 0;
    next_note = 0;
  }
  return false;  // arp not started
}



int arpegio_mono::next()
{
  return next_note;
}

int arpegio_mono::previous()
{
  return previous_note;
}

void arpegio_mono::start()
{
  start_time = millis();
  next_index = 0;
  next_event_time = start_time;
  started = true;
  paused = false;
}

void arpegio_mono::stop()
{
  next_note = 0;
  started = false;
}

char arpegio_mono::get_name()
{
  return arp_name;
}

String * arpegio_mono::get_long_name()
{
  return long_name;
}

bool arpegio_mono::is_started()
{
  return started;
}

void arpegio_mono::pause()
{
  next_note = 0;
  paused = true;
}

bool arpegio_mono::is_paused()
{
  return paused;
}

int arpegio_mono::get_duration_scaling()
{
  return duration_scaling;
}

unsigned int arpegio_mono::get_N_notes()
{
  return N_note_arp;
}

int * arpegio_mono::get_notes()
{
  return notes_arp;
}

