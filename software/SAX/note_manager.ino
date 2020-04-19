#include "note_manager.h"
#include "read_shift_reg.h"
#include "button.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing the mapping between keys and notes, and managing the shift registers
*/



byte note[POLYPHONY] = {0};
byte previous_note[POLYPHONY] = {0};


note_manager::note_manager() {
  pinMode(ploadPin, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
}

byte * note_manager::get_note()
{
  return note;
}

byte * note_manager::get_previous_note()
{
  return previous_note;
}


bool note_manager::update()
{
  unsigned int current_touch = read_shift_regs();
  unsigned int current_touch_no_mod = current_touch & (0b111111100101111110010001);  //haha (removing modifiers)

  for (byte i = 0; i < POLYPHONY; i++)
  {
    previous_note[i] = note[i];
    note[i] = 0;
  }

  // Getting modifying touches
  octave.manual_input( bool(current_touch & 0b000000010000000000000000)); //mouhahahah
  modifier_up.manual_input( bool(current_touch & 0b000000001000000000000000)); //mouhahahahaha
  modifier_mid.manual_input( bool(current_touch & 0b000000000000000000000100));
  modifier_down.manual_input( bool(current_touch & 0b000000000010000000000000));
  //modifier_sub_up.manual_input( bool(current_touch & 0b000000000000000001000000));
  modifier_sub_up.manual_input( bool(current_touch & 0b000000000000000000100000));
  modifier_sub_down.manual_input( bool(current_touch & 0b000000000000000001000000));


  /*
    up_down = 0;
    right_left = 0;
  */



  down_menu.manual_input(0);
  right_menu.manual_input(0);
  left_menu.manual_input(0);
  up_menu.manual_input(0);



  switch (current_touch_no_mod)
  {
    case 14571153:   //E up
      note[0] = 64;
      break;
    case 14571152:  //D# up
      note[0] = 63;
      break;
    case 14046864:  // D up
      note[0] = 62;
      break;
    case 9852560:  // C#
      note[0] = 61;
      break;
    case 9836160:  // C
      note[0] = 60;
      right_menu.manual_input(1);
      break;
    case 9848464:  // B
      note[0] = 59;
      left_menu.manual_input(1);
      break;
    case 9832064:  // A
      note [0] = 57;
      break;
    case 9848448:  // A#
      note[0] = 58;
      break;
    case 11798144:  // G#
      note[0] = 56;
      break;
    case 9700992:  // G
      note[0] = 55;
      break;
    case 1312384:  // F#
      note[0] = 54;
      break;
    case 9700480:  // F
      note[0] = 53;
      break;
    case 1311872:  // E
      note [0] = 52;
      break;
    case 265344:  // D#
      note[0] = 51;
      break;
    case 263296:  // D
      note[0] = 50;
      break;
    case 262272:  // C-1
      note[0] = 48;
      break;

    case 262528:  // C#-1
      note[0] = 49;
      break;

    case 128:  // B-1
      note[0] = 47;
      break;

    case 0:  // A#-1
      note[0] = 46;
      break;

    case 1463952:
      down_menu.manual_input(1);
      break;

    case 9852048:
      up_menu.manual_input(1);
      break;

    case 8672912:  // TAP
      if (previous_touch_no_mod != 8672912) tap.add_tap();
      break;
  }  // end of switch case





  /********** OCTAVE */
  previous_touch_no_mod = current_touch_no_mod;
  for (byte i = 0; i < POLYPHONY; i++)
  {
    if (note[i] != 0)
    {
      note[i] += midi_transpose;
      note[i] += midi_octave * 12;
      if (octave.is_pressed()) note[i] += 12;
    }
  }



  if (note[0] != 0)
  {
    /********* NORMAL */
    if (arpegio_mode == MODE_NORMAL)
    {
      if (modifier_up.is_pressed()) note[0] += normal_up_modifier;
      if (modifier_mid.is_pressed()) note[0] += normal_mid_modifier;
      if (modifier_down.is_pressed()) note[0] += normal_down_modifier;
    }


    /****** ARPEGIO */
    if (arpegio_mode == MODE_ARPEGIO)
    {
      for (byte i = 0; i < 3; i++)
      {
        if (arp[i].is_started())
        {
          arp[i].change(note[0]);
          note[0] = arp[i].next();
        }
      }
    }

    /********* CHORDS **/
    if (arpegio_mode == MODE_CHORD)
    {
      if (modifier_up.is_pressed()) chords[0].apply(note);
      if (modifier_mid.is_pressed()) chords[1].apply(note);
      if (modifier_down.is_pressed()) chords[2].apply(note);


      if (modifier_up.has_been_pressed() || modifier_mid.has_been_pressed() || modifier_down.has_been_pressed())         return true;
      if (modifier_up.has_been_released() || modifier_mid.has_been_released() || modifier_down.has_been_released())        return true;
    }
  }
  //if (previous_note[0] != note[0] && note[0]!= 0)
  if (previous_note[0] != note[0])
  {
    return true;
  }
  return false;
}


