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

void chord::apply(byte * note)
{
  for (unsigned int i=0;i<N_notes;i++)
  {
    note[i]=note[0]+notes[i];
  }
}

