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
  Serial.println(current_touch, BIN);

  // Getting modifying touches
  octave.manual_input( bool(current_touch & 0b000000010000000000000000)); //mouhahahah
  modifier_up.manual_input( bool(current_touch & 0b000000000000000010000000)); //mouhahahahaha
  modifier_mid.manual_input( bool(current_touch & 0b000000000001000000000000));
  modifier_down.manual_input( bool(current_touch & 0b000000000000000000000010));
  //modifier_sub_up.manual_input( bool(current_touch & 0b000000000000000001000000));


  down_menu.manual_input(0);
  right_menu.manual_input(0);
  left_menu.manual_input(0);
  up_menu.manual_input(0);



  for (byte i = 0; i < POLYPHONY; i++)
  {
    previous_note[i] = note[i];
    note[i] = 0;
  }





  /*****************************
      MODE NORMAL: like a real sax, no more, no less
  */

  if (global_mode == MODE_NORMAL)
  {

    unsigned int current_touch_no_mod = current_touch & (0b111111101111111111111111);  //haha (removing modifiers)


    switch (current_touch_no_mod)
    {


      case 0:   //A# bass
        note[0] = 46;;
        break;

      case 128:
        note[0] = 47;  //B
        break;

      case 262272:  //C bass
        note[0] = 48;
        break;

      case 262528: //C# bass
        note[0] = 49;
        break;

      case 263296: //D
        note[0] = 50;
        break;

      case 265344: //D#
        note[0] = 51;
        break;

      case 1311872: //E
        note[0] = 52;
        break;

      case 9700480: //F
        note[0] = 53;
        break;

      case 1312392: //F#
        note[0] = 54;
        break;

      case 9700512: //F#
        note[0] = 54;
        break;

      case 9701000: //G
        note[0] = 55;
        break;

      case 11798152: //G#
        note[0] = 56;
        break;

      case 11536008: //G#
        note[0] = 56;
        break;

      case 11798408: //G#
        note[0] = 56;
        break;

      case 11535880: //G#
        note[0] = 56;
        break;

      case 9832072: //A
        note[0] = 57;
        break;

      case 9840264: //A#
        note[0] = 58;
        break;

      case 9848456: //A#
        note[0] = 58;
        break;

      case 9847936: //A#
        note[0] = 58;
        break;

      case 1459848: //A#
        note[0] = 58;
        break;

      case 1459328: //A#
        note[0] = 58;
        break;

      case 410752: //A#
        note[0] = 58;
        break;

      case 9848472: //B
        note[0] = 59;
        left_menu.manual_input(1);
        break;

      case 9836168: //C
        note[0] = 60;
        right_menu.manual_input(1);
        break;

      case 9881240: //C
        note[0] = 60;
        break;

      case 11802248: //C
        note[0] = 60;
        break;

      case 9852570: //C#
        note[0] = 61;
        break;

      case 283778: //C#
        note[0] = 61;
        break;

      case 9721498: //C#
        note[0] = 61;
        break;

      case 414850: //C#
        note[0] = 61;
        break;

      case 1463426: //C#
        note[0] = 61;
        break;

      case 9852034: //C#
        note[0] = 61;
        up_menu.manual_input(1);
        break;

      case 1463946: //C#
        note[0] = 61;
        down_menu.manual_input(1);
        break;

      case 9852066:  //C#
        note[0] = 61;
        break;

      case 14046874:  //D
        note[0] = 62;
        break;

      case 10360456:  //D
        note[0] = 62;
        break;

      case 10372764:  //D
        note[0] = 62;
        break;

      case 14571162:  //D#
        note[0] = 63;
        break;

      case 14603930:  //E
        note[0] = 64;
        break;

      case 10409626:  //E
        note[0] = 64;
        break;

      case 9848473:  //E
        note[0] = 64;
        break;

      case 14603931:  //F
        note[0] = 65;
        break;

      case 9832073:  //F
        note[0] = 65;
        break;



    }
    previous_touch_no_mod = current_touch_no_mod;



    if (note[0] != 0)
    {
      note[0] += midi_transpose;
      note[0] += midi_octave * 12;
      if (octave.is_pressed()) note[0] += 12;
    }

  }






  /**************************************************
     MODE EWI/CHORD/ARP which share common keyings
   **************************************************/

  else
  {
    unsigned int current_touch_no_mod = current_touch & (0b111111101110111101111101);  //haha (removing modifiers)
    Serial.println(current_touch_no_mod);
    delay(100);


    switch (current_touch_no_mod)
    {
      case 16706905:   //E up
        note[0] = 64;
        break;
      case 16674137:  //D# up
        note[0] = 63;
        break;
      case 16411993:  // D up
        note[0] = 62;
        break;
      case 15887705:  // C#
        note[0] = 61;
        break;
      case 15740185:  // C#
        note[0] = 61;
        up_menu.manual_input(1);
        break;
      case 15756553:  // C#
        note[0] = 61;
        down_menu.manual_input(1);
        break;
      case 15740169:  // C#
        note[0] = 61;
        break;
      case 15739913:  // C#
        note[0] = 61;
        break;
      case 15754585:  // C
        note[0] = 60;
        right_menu.manual_input(1);
        break;
      case 398464: //C
        note[0] = 60;
        break;
      case 15738137: //C
        note[0] = 60;
        break;
      case 15753561: //C
        note[0] = 60;
        break;
      case 15754505: //C
        note[0] = 60;
        break;
      case 15738121: //C
        note[0] = 60;
        break;
      case 15737865: //C
        note[0] = 60;
        break;
      case 15887704:  // B
        note[0] = 59;
        left_menu.manual_input(1);
        break;
      case 15756632:  // A#
        note[0] = 58;
        break;
      case 15740184:  // A#
        note[0] = 58;
        break;
      case 15756552:  // A#
        note[0] = 58;
        break;
      case 15740168:  // A#
        note[0] = 58;
        break;
      case 15739912:  // A#
        note[0] = 58;
        break;
      case 15754584:  // A
        note [0] = 57;
        break;
      case 15738136:  // A
        note [0] = 57;
        break;
      case 15754504:  // A
        note [0] = 57;
        break;
      case 15738120:  // A
        note [0] = 57;
        break;
      case 15737864:  // A
        note [0] = 57;
        break;
      case 15754072:  // G#
        note[0] = 56;
        break;
      case 15753560:  // G
        note[0] = 55;
        break;
      case 15753480:  // F#
        note[0] = 54;
        break;
      case 15737112:  // F
        note[0] = 53;
        break;
      case 15737096:  // E
        note [0] = 52;
        break;
      case 15736844:  // D#
        note[0] = 51;
        break;
      case 15736840:  // D
        note[0] = 50;
        break;
      case 15728648:  // C-1
        note[0] = 48;
        break;
      case 15728680:  // C#-1
        note[0] = 49;
        break;
      case 15728640:  // B-1
        note[0] = 47;
        break;


      case 15755289:  // TAP
        if (previous_touch_no_mod != 15755289) tap.add_tap();
        break;
    }  // end of switch case






    previous_touch_no_mod = current_touch_no_mod;



    if (note[0] != 0)
    {
      note[0] += midi_transpose;
      note[0] += midi_octave * 12;
      if (octave.is_pressed()) note[0] += 12;
    }




    if (note[0] != 0)
    {
      /********* NORMAL */
      if (global_mode == MODE_EWI)
      {
        if (modifier_up.is_pressed()) note[0] += normal_up_modifier;
        if (modifier_mid.is_pressed()) note[0] += normal_mid_modifier;
        if (modifier_down.is_pressed()) note[0] += normal_down_modifier;
      }


      /****** ARPEGIO */
      if (global_mode == MODE_ARPEGIO || global_mode == MODE_ARPEGIO_RAND)
      {
        for (byte i = 0; i < 3; i++)
        {
          if (arp[i].is_started())
          {
            arp[i].change(note[0]);  //2 microsS for S2 ARP
            note[0] = arp[i].next();
          }
        }
      }

      /********* CHORDS **/
      if (global_mode == MODE_CHORD)
      {
        if (modifier_up.is_pressed()) chords[0].apply(note);
        if (modifier_mid.is_pressed()) chords[1].apply(note);
        if (modifier_down.is_pressed()) chords[2].apply(note);


        if (modifier_up.has_been_pressed() || modifier_mid.has_been_pressed() || modifier_down.has_been_pressed())         return true;
        if (modifier_up.has_been_released() || modifier_mid.has_been_released() || modifier_down.has_been_released())        return true;
      }
    }
  }  // end of non-normal mode









  if (previous_note[0] != note[0])
  {
    return true;
  }
  return false;
}


