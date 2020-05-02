#include "chord.h"

chord::chord() {};

chord::chord(unsigned int N, int * _notes)
{
  N_notes = N;
  notes = _notes;
}

void chord::set_notes(unsigned int N, int * _notes)
{
  N_notes = N;
  notes = _notes;
}

void chord::set_notes(unsigned int N, int * _notes, char _name)
{
  N_notes = N;
  notes = _notes;
  chord_name = _name;
}

void chord::apply(byte * note)
{
  for (unsigned int i=1;i<N_notes;i++)
  {
    note[i]=note[0]+notes[i];
  }
}

char chord::get_name()
{
  return chord_name;
}

unsigned int chord::get_N_notes()
{
  return N_notes;
}

int * chord::get_notes()
{
  return notes;
}


