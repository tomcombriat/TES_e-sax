#include "chord.h"
#include "note_manager.h"


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

void chord::set_notes(unsigned int N, int * _notes, char _name, String * _long_name)
{
  N_notes = N;
  notes = _notes;
  chord_name = _name;
  long_name = _long_name;
}

void chord::apply(byte * note)
{
  for (unsigned int i = 1; i < N_notes; i++)
  {
    bool common = false;
    for (byte j = 1; j < POLYPHONY; j++) // search for a common note
    {
      if (previous_note[j] == note[0] + notes[i])
      {

        common = true;
        note[j] = note[0] + notes[i];
        break;
      }
    }
    if (!common) // no common note for chord found, take the first slot available
    {
      for (byte j = 1; j < POLYPHONY; j++)
      {
        if (previous_note[j] == 0 && note[j] == 0)
        {
          note[j] = note[0] + notes[i];
          break;
        }
      }
    }
  }
}

char chord::get_name()
{
  return chord_name;
}

String * chord::get_long_name()
{
  return long_name;
}

unsigned int chord::get_N_notes()
{
  return N_notes;
}

int * chord::get_notes()
{
  return notes;
}
