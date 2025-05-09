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

 /*Serial.println(current_touch, BIN);
     delay(100);*/

  // Getting modifying touches
  octave.manual_input( bool(current_touch & 0b000000010000000000000000)); //mouhahahah
  modifier_up.manual_input( bool(current_touch & 0b000000000000000100000000)); //mouhahahahaha
  modifier_mid.manual_input( bool(current_touch & 0b000000000000000010000000));
  modifier_down.manual_input( bool(current_touch & 0b000000001000000000000000));
  modifier_sub_down.manual_input( bool(current_touch & 0b000000000000000000100000));
  //modifier_sub_up.manual_input( bool(current_touch & 0b000000000000000000001000));


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

    unsigned int current_touch_no_mod = current_touch & (0b111110101111111111111111);  //haha (removing modifiers)

   /* Serial.println(current_touch_no_mod);
    delay(100);*/

    switch (current_touch_no_mod)
    {


      case 2621440:   //A# bass
        note[0] = 46;;
        break;

      case 2622464:
        note[0] = 47;  //B
        break;

      case 2622528:  //C bass
        note[0] = 48;
        break;

      case 2622532:  //C bass (G#)
        note[0] = 48;
        break;

      case 2622529: //C# bass
        note[0] = 49;
        break;

      case 2622536: //D
        note[0] = 50;
        break;

      case 2622540: //D  (G#)
        note[0] = 50;
        break;
      case 2638920: //D#
        note[0] = 51;
        break;

      case 2638924: //D# (G#)
        note[0] = 51;
        break;

      case 3671112: //E
        note[0] = 52;
        break;

      case 3671116: //E  (G#)
        note[0] = 52;
        break;

      case 3675208: //F
        note[0] = 53;
        break;

      case 3675212: //F (G#)
        note[0] = 53;
        break;

      case 3671128: //F#
        note[0] = 54;
        break;

      case 3671132: //F#  (G#)
        note[0] = 54;
        break;

      case 3675240: //F# (sub down)
        note[0] = 54;
        break;

      case 3675244: //F# (sub down) (G#)
        note[0] = 54;
        break;

      case 3675224: //G
        note[0] = 55;
        break;

      case 3675228: //G#
        note[0] = 56;
        break;

      case 3675225: //G# (C#)
        note[0] = 56;
        break;

      case 3675229: //G# (C#)
        note[0] = 56;
        break;

      case 3675160: //G# (B)
        note[0] = 56;
        break;

      case 3675164: //G# (B)
        note[0] = 56;
        break;

      case 3674136: //G#  (Bb)
        note[0] = 56;
        break;

      /* case 10786468: //G#  (Bb)
         note[0] = 56;
         break;*/

      case 12063832: //A
        note[0] = 57;
        break;

      /*  case 8697760: //A
          note[0] = 57;
          break;*/

      case 12063816: //A (F)
        note[0] = 57;
        break;

      case 12059736: //A (F#)
        note[0] = 57;
        break;

      case 12059720: //A (E)
        note[0] = 57;
        break;

      case 11011144: //A (D)
        note[0] = 57;
        break;

      case 12064344: //A# (std)
        note[0] = 58;
        break;

      /*   case 8699552: //A# (mod down)
           note[0] = 58;
           break;*/

      case 12064328: //A# (F)
        note[0] = 58;
        break;

      /* case 8796064: //A# (F)
         note[0] = 58;
         break;*/

      case 12060248: //A# (F#)
        note[0] = 58;
        break;

      /*  case 8827808: //A# (F#)
          note[0] = 58;
          break;*/

      case 12060232: //A# (E)
        note[0] = 58;
        break;

      /*  case 8795040: //A# (E)
          note[0] = 58;
          break;*/

      case 11011656: //A# (D)
        note[0] = 58;
        break;

      /* case 8794912: //A# (D)
         note[0] = 58;
         break;*/

      case 3675736: //A# (G)
        note[0] = 58;
        break;

      case 16258648: //B
        note[0] = 59;
        left_menu.manual_input(1);
        break;

      case 12072024: //C
        note[0] = 60;
        right_menu.manual_input(1);
        break;

      case 3683416: //C (G)
        note[0] = 60;
        break;

      case 12072008: //C (F)
        note[0] = 60;
        break;

      case 12067928: //C (F#)
        note[0] = 60;
        break;

      case 12067912: //C (E)
        note[0] = 60;
        break;

      case 11019336: //C (D)
        note[0] = 60;
        break;

      case 16258776: //C (mod mid)
        note[0] = 60;
        break;

      /*  case 15754009: //C
          note[0] = 60;
          break;
      */

      case 16266840: //C#
        note[0] = 61;
        break;

      /*  case 8828592: //C#
          note[0] = 61;
          break;*/

      case 12072520: //C# (F)
        up_menu.manual_input(1);
        note[0] = 61;
        break;

      /* case 8796080: //C# (F)
         note[0] = 61;
         break;*/

      /* case 8827824: //C# (F#)
         note[0] = 61;
         break;*/

      case 12068440: //C# (F#)
        down_menu.manual_input(1);
        note[0] = 61;
        break;



      case 12068424: //C# (E)
        note[0] = 61;
        break;

      /*  case 8795056: //C# (E)
          note[0] = 61;
          break;
      */


      case 11019848: //C# (D)
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

      case 16268888:  //D
        note[0] = 62;
        break;

      case 16268890:  //D#
        note[0] = 63;
        break;

      case 16269146:  //E
        note[0] = 64;
        break;

      /*     case 16706841:  //E
             note[0] = 64;
             break;
      */
      case 16400218:  //F
        note[0] = 65;
        break;

      /*  case 14088184:  //F#
          note[0] = 66;
          break;*/



      case 7894616:
        up_preset.manual_input(1);
        break;
      case 7878224:
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
                                                             0b000000010000000000000000
                                                             0b000000000000000100000000
                                                             0b000000000000000010000000
                                                             0b000000001000000000000000
                                                             0b000000000000000000100000
    */
    unsigned int current_touch_no_mod = current_touch & (0b111110100111111001011111);  //haha (removing modifiers)

    /*Serial.println(current_touch_no_mod);
    delay(100);*/


    switch (current_touch_no_mod)
    {
      case 16399962:   //E up
        note[0] = 64;
        break;
      case 16268890:  //D# up
        note[0] = 63;
        break;
      case 16268888:  // D up
        note[0] = 62;
        break;
      case 16266840:  // C#
        note[0] = 61;
        break;

      case 12072536:  // C# (Bb)
        note[0] = 61;
        break;

      case 12072520:  // C# (F)
        note[0] = 61;
        up_menu.manual_input(1);
        break;

      /*   case 8796080:  // C# (F)
           note[0] = 61;
           break;*/

      case 12068440:  // C# (F#)
        note[0] = 61;
        down_menu.manual_input(1);
        break;

      /*   case 8827824:  // C# (F#)
           note[0] = 61;
           break;*/

      case 12068424:  // C# (E)
        note[0] = 61;
        break;

      /* case 8794800:  // C# (E)
         note[0] = 61;
         break;*/

      case 11019848:  // C# (D)
        note[0] = 61;
        break;

      /*  case 8794672:  // C# (D)
          note[0] = 61;
          break;*/

      case 12072024:  // C
        note[0] = 60;
        right_menu.manual_input(1);
        break;
      /* case 398464: //C
         note[0] = 60;
         break;*/
      case 12072008: //C (F)
        note[0] = 60;
        break;
      case 12067912: //C (E)
        note[0] = 60;
        break;
      case 12067928: //C (F#)
        note[0] = 60;
        break;
      case 11019336: //C (D)
        note[0] = 60;
        break;
      /* case 8689328: //C
         note[0] = 60;
         break;*/
      case 16258648:  // B
        note[0] = 59;
        left_menu.manual_input(1);
        break;
      case 12064328:  // A# (F)
        note[0] = 58;
        break;

      /*  case 12064344:  // A# (F)
          note[0] = 58;
          break;*/

      case 12060248:  // A# (F#)
        note[0] = 58;
        break;

      /*  case 8827552:  // A# (F#)
          note[0] = 58;
          break;*/

      case 12060232:  // A# (E)
        note[0] = 58;
        break;
      /*
            case 8795040:  // A# (E)
              note[0] = 58;
              break;*/

      case 11011656:  // A# (D)
        note[0] = 58;
        break;

      /*  case 8794912:  // A# (D)
          note[0] = 58;
          break;*/

      case 12064344:  // A#  (std)
        note[0] = 58;
        break;
      case 12063832:  // A
        note [0] = 57;
        break;
      /* case 8697760:  // A
         note [0] = 57;
         break;*/
      case 12063816:  // A (F)
        note [0] = 57;
        break;
      case 12059736:  // A (F#)
        note [0] = 57;
        break;
      case 12059720:  // A (E)
        note [0] = 57;
        break;
      case 11011144:  // A (D)
        note [0] = 57;
        break;
      case 11027528:  // A (D#)
        note [0] = 57;
        break;
      case 11011136:  // A (C)
        note [0] = 57;
        break;

      /*   case 8663584:  // A
           note [0] = 57;
           break;*/
      case 3675228:  // G#
        note[0] = 56;
        break;
      case 3675224:  // G
        note[0] = 55;
        break;
      case 3671128:  // F#
        note[0] = 54;
        break;
      case 3671132:  // F# (G#)
        note[0] = 54;
        break;
      case 3675208:  // F
        note[0] = 53;
        break;
      case 3675212:  // F (G#)
        note[0] = 53;
        break;
      case 3671112:  // E
        note [0] = 52;
        break;
      case 3671116:  // E (G#)
        note [0] = 52;
        break;
      case 2638920:  // D#
        note[0] = 51;
        break;
      case 2638924:  // D# (G#)
        note[0] = 51;
        break;
      case 2622536:  // D
        note[0] = 50;
        break;
      case 2622540:  // D (G#)
        note[0] = 50;
        break;
      case 2622528:  // C-1
        note[0] = 48;
        break;
      case 2622532:  // C-1 (G#)
        note[0] = 48;
        break;
      case 2622529:  // C#-1
        note[0] = 49;
        break;
      case 2622464:  // B-1
        note[0] = 47;
        break;
      case 2621440:  // Bb-1
        note[0] = 46;
        break;

      case 7894616:
        up_preset.manual_input(1);
        break;
      case 7878224:
        down_preset.manual_input(1);
        break;



      case 6829656:  // TAP
        if (previous_touch_no_mod != 6829656) tap.add_tap();
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
