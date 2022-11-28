#include "note_manager.h"
#include "read_shift_reg.h"
#include "button.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing the mapping between keys and notes, and managing the shift registers
*/






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
  modifier_up.manual_input( bool(current_touch & 0b000000000100000000000000)); //mouhahahahaha
  modifier_mid.manual_input( bool(current_touch & 0b010000000000000000000000));
  modifier_down.manual_input( bool(current_touch & 0b000000000000001000000000));
  modifier_sub_down.manual_input( bool(current_touch & 0b000000000000010000000000));
  modifier_sub_up.manual_input( bool(current_touch & 0b000000100000000000000000));


  down_menu.manual_input(0);
  right_menu.manual_input(0);
  left_menu.manual_input(0);
  up_menu.manual_input(0);
  up_preset.manual_input(0);
  down_preset.manual_input(0);




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

    unsigned int current_touch_no_mod = current_touch & (0b111111101101111111111111);  //haha (removing modifiers) and dead valves (first right hand)

  /*  Serial.println(current_touch_no_mod);
    delay(100);*/

    switch (current_touch_no_mod)
    {


      case 1048576:   //A# bass
        note[0] = 46;;
        break;

      case 1048580:
        note[0] = 47;  //B
        break;

      case 1048581:  //C bass
        note[0] = 48;
        break;

      /* case 2622532:  //C bass (G#)
         note[0] = 48;
         break;*/

      case 1048589: //C# bass
        note[0] = 49;
        break;

      case 1050629: //D
        note[0] = 50;
        break;

      /* case 2622540: //D  (G#)
         note[0] = 50;
         break;*/

      case 1050645: //D#
        note[0] = 51;
        break;

      /* case 2638924: //D# (G#)
         note[0] = 51;
         break;*/

      case 1083397: //E
        note[0] = 52;
        break;

      /*case 3671116: //E  (G#)
        note[0] = 52;
        break;*/

      case 9472005: //F
        note[0] = 53;
        break;

      /*case 3675212: //F (G#)
        note[0] = 53;
        break;*/

      case 1083399: //F#
        note[0] = 54;
        break;

      /* case 3671132: //F#  (G#)
         note[0] = 54;
         break;*/

      case 9473029: //F# (sub down)
        note[0] = 54;
        break;

      /* case 3675244: //F# (sub down) (G#)
         note[0] = 54;
         break;*/

      case 9472007: //G
        note[0] = 55;
        break;

      case 9996295: //G#
        note[0] = 56;
        break;

      case 9996303: //G# (C#)
        note[0] = 56;
        break;

      /* case 10004495: //G# (C#)
         note[0] = 56;
         break;*/

      case 9996294: //G# (B)
        note[0] = 56;
        break;

      /* case 3675164: //G# (B)
         note[0] = 56;
         break;*/

      case 9996290: //G#  (Bb)
        note[0] = 56;
        break;

      /* case 10786468: //G#  (Bb)
         note[0] = 56;
         break;*/

      case 9472135: //A
        note[0] = 57;
        break;

      case 9472133: //A (F)
        note[0] = 57;
        break;

      case 1083527: //A (F#)
        note[0] = 57;
        break;

      case 1083525: //A (E)
        note[0] = 57;
        break;

      case 1050757: //A (D)
        note[0] = 57;
        break;

      case 1050773: //A (D#)
        note[0] = 57;
        break;

      case 1048709: //A (C)
        note[0] = 57;
        break;

      case 9734279: //A# (std)
        note[0] = 58;
        break;

      case 9472647: //A# (mod down)
        note[0] = 58;
        break;

      case 9734277: //A# (F)
        note[0] = 58;
        break;

      case 1345927: //A# (F#)
        note[0] = 58;
        break;



      case 1345925: //A# (E)
        note[0] = 58;
        break;

      case 1345669: //A# (E)
        note[0] = 58;
        break;


      case 1313157: //A# (D)
        note[0] = 58;
        break;

      case 1312901: //A# (D)
        note[0] = 58;
        break;

      /* case 8794912: //A# (D)
         note[0] = 58;
         break;*/

      /* case 3675736: //A# (G)
         note[0] = 58;
         break;*/

      case 9734535: //B
        note[0] = 59;
        left_menu.manual_input(1);
        break;

      case 11569287: //C
        note[0] = 60;
        right_menu.manual_input(1);
        break;

      case 11569159: //C (G)
        note[0] = 60;
        break;

      case 11569285: //C (F)
        note[0] = 60;
        break;

      case 11569157: //C (F (G)))
        note[0] = 60;
        break;

      case 3180679: //C (F#)
        note[0] = 60;
        break;

      case 3180551: //C (F# (G))
        note[0] = 60;
        break;

      case 3180677: //C (E)
        note[0] = 60;
        break;

      case 3180549: //C (E (G))
        note[0] = 60;
        break;

      case 3147909: //C (D)
        note[0] = 60;
        break;

      case 3147781: //C (D (G))
        note[0] = 60;
        break;

      case 13928839: //C (mod mid)
        note[0] = 60;
        break;

      /*  case 15754009: //C
          note[0] = 60;
          break;
      */

      case 11831687: //C#
        note[0] = 61;
        break;

      /*  case 8828592: //C#
          note[0] = 61;
          break;*/

      case 11831429: //C# (F)
        up_menu.manual_input(1);
        note[0] = 61;
        break;

      /* case 8796080: //C# (F)
         note[0] = 61;
         break;*/

      /* case 8827824: //C# (F#)
         note[0] = 61;
         break;*/

      case 3442823: //C# (F#)
        down_menu.manual_input(1);
        note[0] = 61;
        break;



      case 3442821: //C# (E)
        note[0] = 61;
        break;

      /*  case 8795056: //C# (E)
          note[0] = 61;
          break;
      */


      case 3410053: //C# (D)
        note[0] = 61;
        break;

      /*  case 8794928: //C# (D)
          note[0] = 61;
          break;*/
      /*
            case 9852034: //C#
              note[0] = 61;
              break;

            case 15756313:  //C#
              note[0] = 61;
              break;
      */

      case 11835783:  //D
        note[0] = 62;
        break;

      case 11835815:  //D#
        note[0] = 63;
        break;

      case 11852199:  //E
        note[0] = 64;
        break;

      /*     case 16706841:  //E
             note[0] = 64;
             break;
      */
      case 11852263:  //F
        note[0] = 65;
        break;

      case 11983335:  //F#
        note[0] = 66;
        break;



      case 11831575:
        up_preset.manual_input(1);
        break;
      case 11829511:
        down_preset.manual_input(1);
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
    /*
                                                             0b000000000100000000000000
                                                             0b010000000000000000000000
                                                             0b000000000000001000000000
                                                             0b000000000000010000000000
                                                             0b000000100000000000000000
                                                             0b101111001001100111111111
    */
    unsigned int current_touch_no_mod = current_touch & (0b101111001001100111111111);  //haha (removing modifiers)

  /*  Serial.println(current_touch_no_mod);
    delay(100);*/


    switch (current_touch_no_mod)
    {
      case 11835879:   //E up
        note[0] = 64;
        break;
      case 11835815:  //D# up
        note[0] = 63;
        break;
      case 11835783:  // D up
        note[0] = 62;
        break;
      case 11831687:  // C#
        note[0] = 61;
        break;

     /* case 12072536:  // C# (Bb)
        note[0] = 61;
        break;*/

      case 11831429:  // C# (F)
        note[0] = 61;
        up_menu.manual_input(1);
        break;

      /*   case 8796080:  // C# (F)
           note[0] = 61;
           break;*/

      case 3442823:  // C# (F#)
        note[0] = 61;
        down_menu.manual_input(1);
        break;

      /*   case 8827824:  // C# (F#)
           note[0] = 61;
           break;*/

      case 3442821:  // C# (E)
        note[0] = 61;
        break;

      /* case 8794800:  // C# (E)
         note[0] = 61;
         break;*/

      case 3410053:  // C# (D)
        note[0] = 61;
        break;

      /*  case 8794672:  // C# (D)
          note[0] = 61;
          break;*/

      case 11569287:  // C
        note[0] = 60;
        right_menu.manual_input(1);
        break;
      /* case 398464: //C
         note[0] = 60;
         break;*/
      case 11569285: //C (F)
        note[0] = 60;
        break;
      case 3180677: //C (E)
        note[0] = 60;
        break;
      case 318067: //C (F#)
        note[0] = 60;
        break;
      case 3147909: //C (D)
        note[0] = 60;
        break;
      /* case 8689328: //C
         note[0] = 60;
         break;*/
      case 9734535:  // B
        note[0] = 59;
        left_menu.manual_input(1);
        break;
      case 9734277:  // A# (F)
        note[0] = 58;
        break;

      /*  case 12064344:  // A# (F)
          note[0] = 58;
          break;*/

      case 1345671:  // A# (F#)
        note[0] = 58;
        break;

      /*  case 8827552:  // A# (F#)
          note[0] = 58;
          break;*/

      case 1345669:  // A# (E)
        note[0] = 58;
        break;
      /*
            case 8795040:  // A# (E)
              note[0] = 58;
              break;*/

      case 1312901:  // A# (D)
        note[0] = 58;
        break;

      /*  case 8794912:  // A# (D)
          note[0] = 58;
          break;*/

      case 9734279:  // A#  (std)
        note[0] = 58;
        break;
      case 9472135:  // A
        note [0] = 57;
        break;
      /* case 8697760:  // A
         note [0] = 57;
         break;*/
      case 9472133:  // A (F)
        note [0] = 57;
        break;
      case 1083527:  // A (F#)
        note [0] = 57;
        break;
      case 1083525:  // A (E)
        note [0] = 57;
        break;
      case 1050757:  // A (D)
        note [0] = 57;
        break;
      case 1050773:  // A (D#)
        note [0] = 57;
        break;
      case 1048709:  // A (C)
        note [0] = 57;
        break;

      /*   case 8663584:  // A
           note [0] = 57;
           break;*/
      case 9996295:  // G#
        note[0] = 56;
        break;
      case 9472007:  // G
        note[0] = 55;
        break;
      case 1083399:  // F#
        note[0] = 54;
        break;
     /* case 3671132:  // F# (G#)
        note[0] = 54;
        break;*/
      case 9472005:  // F
        note[0] = 53;
        break;
     /* case 3675212:  // F (G#)
        note[0] = 53;
        break;*/
      case 1083397:  // E
        note [0] = 52;
        break;
    /*  case 3671116:  // E (G#)
        note [0] = 52;
        break;*/
      case 1050645:  // D#
        note[0] = 51;
        break;
     /* case 2638924:  // D# (G#)
        note[0] = 51;
        break;*/
      case 1050629:  // D
        note[0] = 50;
        break;
     /* case 2622540:  // D (G#)
        note[0] = 50;
        break;*/
      case 1048581:  // C-1
        note[0] = 48;
        break;
     /* case 2622532:  // C-1 (G#)
        note[0] = 48;
        break;*/
      case 1048589:  // C#-1
        note[0] = 49;
        break;
      case 1048580:  // B-1
        note[0] = 47;
        break;
      case 1048576:  // Bb-1
        note[0] = 46;
        break;

      case 11831575:
        up_preset.manual_input(1);
        break;
      case 11829511:
        down_preset.manual_input(1);
        break;



      case 11798791:  // TAP
        if (previous_touch_no_mod != 11798791) tap.add_tap();
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
        if (replacing_chord == true)
        {
          int last_in_chord = -1;
          unsigned long last_time = 0;
          for (byte i = 0; i < 3; i++)
          {
            if (modifiers[i]->is_pressed() && modifiers[i]->get_last_press_time() > last_time)
            {
              last_time = modifiers[i]->get_last_press_time();
              last_in_chord = i;
            }
          }
          if (last_in_chord != -1) chords[last_in_chord].apply(note);
        }
        else
        {
          if (modifier_up.is_pressed()) chords[0].apply(note);
          if (modifier_mid.is_pressed()) chords[1].apply(note);
          if (modifier_down.is_pressed()) chords[2].apply(note);
        }


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
