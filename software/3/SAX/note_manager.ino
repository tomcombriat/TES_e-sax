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
  /* Serial.println(current_touch, BIN);
    delay(100);*/

  // Getting modifying touches
  octave.manual_input( bool(current_touch & 0b000000010000000000000000)); //mouhahahah
  modifier_up.manual_input( bool(current_touch & 0b010000000000000000000000)); //mouhahahahaha
  modifier_mid.manual_input( bool(current_touch & 0b000000000000000000000100));
  modifier_down.manual_input( bool(current_touch & 0b000000000000100000000000));
  modifier_sub_down.manual_input( bool(current_touch & 0b000010000000000000000000));
  modifier_sub_up.manual_input( bool(current_touch & 0b000000000000000000001000));


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

  /*  Serial.println(current_touch_no_mod);
    delay(100);*/

    switch (current_touch_no_mod)
    {


      case 8389120:   //A# bass
        note[0] = 46;;
        break;

      case 8389152:
        note[0] = 47;  //B
        break;

      case 8393248:  //C bass
        note[0] = 48;
        break;

      case 8393250: //C# bass
        note[0] = 49;
        break;

      case 8655392: //D
        note[0] = 50;
        break;

      case 8655393: //D#
        note[0] = 51;
        break;

      case 8655520: //E
        note[0] = 52;
        break;

      case 8656544: //F
        note[0] = 53;
        break;

      case 8688288: //F#
        note[0] = 54;
        break;

       case 9180832: //F# (sub down)
         note[0] = 54;
         break;

      case 8689312: //G
        note[0] = 55;
        break;

      case 10786464: //G#
        note[0] = 56;
        break;

      case 10786466: //G# (C#)
        note[0] = 56;
        break;

      case 8689314: //G# (C#)
        note[0] = 56;
        break;

      case 10782368: //G# (B)
        note[0] = 56;
        break;

      case 10782336: //G#  (Bb)
        note[0] = 56;
        break;

      case 10786468: //G#  (Bb)
        note[0] = 56;
        break;

      case 8697504: //A
        note[0] = 57;
        break;

      case 8664736: //A (F)
        note[0] = 57;
        break;

      case 8696480: //A (F#)
        note[0] = 57;
        break;

      case 8663712: //A (E)
        note[0] = 57;
        break;

      case 8663584: //A (D)
        note[0] = 57;
        break;

      case 8828576: //A# (std)
        note[0] = 58;
        break;

      case 8699552: //A# (mod down)
        note[0] = 58;
        break;
        
      case 8795808: //A# (F)
        note[0] = 58;
        break;

      case 8827808: //A# (F#)
        note[0] = 58;
        break;

      case 8794784: //A# (E)
        note[0] = 58;
        break;

      case 8794656: //A# (D)
        note[0] = 58;
        break;

      case 8820640: //A# (G)
        note[0] = 58;
        break;

      case 8828832: //B
        note[0] = 59;
        left_menu.manual_input(1);
        break;

      case 8697520: //C
        note[0] = 60;
        right_menu.manual_input(1);
        break;

      case 8689328: //C (G)
        note[0] = 60;
        break;

      case 8664752: //C (F)
        note[0] = 60;
        break;

      case 8696496: //C (F#)
        note[0] = 60;
        break;

      case 8663728: //C (E)
        note[0] = 60;
        break;

      case 8663600: //C (D)
        note[0] = 60;
        break;

      case 8828836: //C (mod mid)
        note[0] = 60;
        break;

    /*  case 15754009: //C
        note[0] = 60;
        break;
*/

      case 8828848: //C#
        note[0] = 61;
        break;

      case 8795824: //C# (F)
        up_menu.manual_input(1);
        note[0] = 61;
        break;

      case 8827824: //C# (F#)
        down_menu.manual_input(1);
        note[0] = 61;
        break;

      case 8794800: //C# (E)
        note[0] = 61;
        break;

      case 8794672: //C# (D)
        note[0] = 61;
        break;
/*
      case 9852034: //C#
        note[0] = 61;
        break;

      case 15756313:  //C#
        note[0] = 61;
        break;
*/

      case 9877424:  //D
        note[0] = 62;
        break;

      case 9877488:  //D#
        note[0] = 63;
        break;

      case 14071792:  //E
        note[0] = 64;
        break;

 /*     case 16706841:  //E
        note[0] = 64;
        break;
*/
      case 14088176:  //F
        note[0] = 65;
        break;

      case 14088184:  //F#
        note[0] = 66;
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

    unsigned int current_touch_no_mod = current_touch & (0b101101101111011111110011);  //haha (removing modifiers)
    /*
        Serial.println(current_touch_no_mod);
        delay(100);
    */

    switch (current_touch_no_mod)
    {
      case 9893872:   //E up
        note[0] = 64;
        break;
      case 9877488:  //D# up
        note[0] = 63;
        break;
      case 9877424:  // D up
        note[0] = 62;
        break;
      case 8828848:  // C#
        note[0] = 61;
        break;
      case 8795824:  // C#
        note[0] = 61;
        up_menu.manual_input(1);
        break;
      case 8827824:  // C#
        note[0] = 61;
        down_menu.manual_input(1);
        break;
      case 8794672:  // C#
        note[0] = 61;
        break;
      case 8794800:  // C#
        note[0] = 61;
        break;
      case 8697520:  // C
        note[0] = 60;
        right_menu.manual_input(1);
        break;
      case 398464: //C
        note[0] = 60;
        break;
      case 8664752: //C
        note[0] = 60;
        break;
      case 8663728: //C (E)
        note[0] = 60;
        break;
      case 8696496: //C (F#)
        note[0] = 60;
        break;
      case 8663600: //C (D)
        note[0] = 60;
        break;
      case 8689328: //C
        note[0] = 60;
        break;
      case 8828832:  // B
        note[0] = 59;
        left_menu.manual_input(1);
        break;
      case 8795808:  // A# (F)
        note[0] = 58;
        break;
      case 8827808:  // A# (F#)
        note[0] = 58;
        break;
      case 8794784:  // A# (E)
        note[0] = 58;
        break;
      case 8794656:  // A# (D)
        note[0] = 58;
        break;
      case 8828576:  // A#  (std)
        note[0] = 58;
        break;
      case 8697504:  // A
        note [0] = 57;
        break;
      case 8664736:  // A (F)
        note [0] = 57;
        break;
      case 8696480:  // A (F#)
        note [0] = 57;
        break;
      case 8663712:  // A (E)
        note [0] = 57;
        break;
      case 8663584:  // A
        note [0] = 57;
        break;
      case 10786464:  // G#
        note[0] = 56;
        break;
      case 8689312:  // G
        note[0] = 55;
        break;
      case 8688288:  // F#
        note[0] = 54;
        break;
      case 8656544:  // F
        note[0] = 53;
        break;
      case 8655520:  // E
        note [0] = 52;
        break;
      case 8655393:  // D#
        note[0] = 51;
        break;
      case 8655392:  // D
        note[0] = 50;
        break;
      case 8393248:  // C-1
        note[0] = 48;
        break;
      case 8393250:  // C#-1
        note[0] = 49;
        break;
      case 8389152:  // B-1
        note[0] = 47;
        break;
      case 8389120:  // Bb-1
        note[0] = 46;
        break;


      case 8820272:  // TAP
        if (previous_touch_no_mod != 8820272) tap.add_tap();
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


