/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the main program
*/




#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306_STM32.h>

#include <MIDI.h>



#include "analog_input.h"
#include "button.h"
#include "read_shift_reg.h"
#include "note_manager.h"
#include "midi_cc.h"
#include "screen.h"
#include "menu.h"
#include "tap_tempo.h"
#include "arpegio_mono.h"
#include "chord.h"
#include "pitchbend.h"



/***************************/
/******* DEFINE ************/
/***************************/

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define MODIFIER_RESPONSE_TIME 15
#define JOYSTICK_RESPONSE_TIME 10
#define BREATH_RESPONSE_TIME 1
#define CC_DELTA_TIME 40
#define CC_MIN_TIME 5
#define PITCHBEND_MIN_TIME 10
#define SCREEN_UPDATE_TIME 20
#define SCREEN_IDLE_WAITING_TIME 400
#define MODE_NORMAL 0
#define MODE_ARPEGIO 1
#define MODE_CHORD 2

#define JOY_BASE_SCALING 0.065
#define JOY_PB_SCALING 4.2



/***************************/
/****** ANALOG INPUTS ******/
/***************************/
analog_input joy_Y(PA7, 0, JOYSTICK_RESPONSE_TIME);
analog_input joy_X(PB0, 0, JOYSTICK_RESPONSE_TIME);
analog_input breath(PA1, 0, BREATH_RESPONSE_TIME, 20);


/***************************/
/********* BUTTONS *********/
/***************************/
button joy_SW(PA0, false, JOYSTICK_RESPONSE_TIME);
button octave(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_up(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_mid(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_down(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_sub_up(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_sub_down(-1, true, MODIFIER_RESPONSE_TIME);
button up_menu(-1, true, MODIFIER_RESPONSE_TIME);
button down_menu(-1, true, MODIFIER_RESPONSE_TIME);
button right_menu(-1, true, MODIFIER_RESPONSE_TIME);
button left_menu(-1, true, MODIFIER_RESPONSE_TIME);


//mettre up down et right left


/*************************/
/****** NOTE MANAGER *****/
/************************/
note_manager manager;




/*************************/
/***** SCREEN ************/
/*************************/
screen ssd;
unsigned long stop_played_time = 0;


/****************************/
/******* MIDI ***************/
/****************************/
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
byte midi_channel = 2;
int midi_transpose = 0;
int midi_octave = 0;




/****************************/
/******* STATE **************/
/****************************/
bool delta_mode = true;
byte arpegio_mode = MODE_NORMAL;
bool played = false;
int breath_sensitivity = 0;
bool pitchbend_enable = false;



/************************/
/***** MIDI CC **********/
/************************/
midi_cc X_CC(71, 64);
midi_cc Y_CC(1, 64);
midi_cc breath_CC(74);


/************************/
/****** TEMPO ***********/
/************************/
tap_tempo tap;



/************************/
/******** ARPS **********/
/************************/
arpegio_mono arp[N_ARP];
int selected_arp[3] = {0, 1, 2};



/************************/
/****** CHORD ***********/
/************************/
chord chords[N_ARP];



/************************/
/****** pITCHBEND *******/
/************************/
pitchbend PB;



/****************************/
/** NORMAL MODE MODIFIERS ***/
/****************************/
int normal_up_modifier = +1;
int normal_mid_modifier = -1;
int normal_down_modifier = +7;


void setup() {

  //Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setCursor(30, 15);
  display.setTextColor(1, 0);
  display.setTextSize(4);
  display.print("TES");
  display.setCursor(35, 50);

  for (int i = 0; i < N_ARP; i++) arp[i].set_notes(arp_N[i], arp_times[i], arp_notes[i], arp_name[i]);
  /*
    arp[0].set_notes(4, arp0_times, arp0_notes);
    arp[1].set_notes(4, arp1_times, arp1_notes);
    arp[2].set_notes(4, arp2_times, arp2_notes);
  */
  chords[0].set_notes(chord_N0, chord_notes0);
  chords[1].set_notes(chord_N1, chord_notes1);
  chords[2].set_notes(chord_N2, chord_notes2);


  display.setTextSize(2);
  display.print("e-Sax");
  display.display();
  joy_X.calibrate();
  joy_Y.calibrate();
  breath.calibrate();
  breath.set_scaling_factor(((breath_sensitivity * 0.1) + 1) * 127 / 2000.);
  breath.set_min_max(0, 127);
  joy_X.set_scaling_factor(JOY_BASE_SCALING);
  joy_Y.set_scaling_factor(JOY_BASE_SCALING);
  joy_X.set_min_max(-127, 127);
  joy_Y.set_min_max(-127, 127);
  display.setRotation(2);


  MIDI.begin(MIDI_CHANNEL_OMNI);

}

void loop() {

  joy_SW.update();
  octave.update();
  modifier_up.update();
  modifier_mid.update();
  modifier_down.update();
  modifier_sub_up.update();
  modifier_sub_down.update();
  breath.update();
  joy_X.update();
  joy_Y.update();
  breath_CC.update();

  if (!played && millis() - stop_played_time > SCREEN_IDLE_WAITING_TIME)
  {
    ssd.draw_standby_screen(midi_octave, midi_transpose, arpegio_mode, delta_mode, X_CC.get_value(),Y_CC.get_value(), tap.get_tempo());
    ssd.update();
  }


  



  if (arpegio_mode == MODE_ARPEGIO && tap.has_change())  for (byte i = 0; i < N_ARP; i++)  arp[i].set_tempo(tap.get_tempo_time());   // update tempo of arpegiators



  /***********************************
     NEW NOTE
   ***********************************/
  if (manager.update())   // different note has been detected
  {
    if (manager.get_previous_note()[0] != 0 && played)    //already played but different note -> shutdown previous note
    {
      for (byte i = 0; i < POLYPHONY; i++)
      {
        if (manager.get_previous_note()[i] != 0 && manager.get_previous_note()[i] != manager.get_note()[i]) 
        {
          MIDI.sendNoteOff(manager.get_previous_note()[i], 0, midi_channel);
        }

      }
      played = false;
      stop_played_time = millis();
    }

    if (manager.get_note()[0] != 0 && breath.value() > 0)   // new note is playable  -> play it
    {
      played = true;
      for (byte i = 0; i < POLYPHONY; i++)
      {
        if (manager.get_note()[i] != 0 && manager.get_previous_note()[i] != manager.get_note()[i]) 
        {
          MIDI.sendNoteOn(manager.get_note()[i], breath.value(), midi_channel);
        }
       
      }
    }
  }  // end of   «if (manager.update())»


  if (breath.value() > 0 && !played && manager.get_note()[0] != 0)    // breath is loud enough to play note
  {
    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (manager.get_note()[i] != 0) MIDI.sendNoteOn(manager.get_note()[i], breath.value(), midi_channel);
      else break;
    }
    played = true;

    if (modifier_up.is_pressed()) arp[0].start();
    if (modifier_mid.is_pressed()) arp[1].start();
    if (modifier_down.is_pressed()) arp[2].start();
  }


  if (breath.value() == 0 && played)    // breath is low enough to stop note
  {
    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (manager.get_note()[i] != 0) MIDI.sendNoteOff(manager.get_note()[i], 0, midi_channel);
      else break;
    }
    played = false;
    stop_played_time = millis();
    if (arpegio_mode == MODE_ARPEGIO)
    {
      for (byte i = 0; i < N_ARP; i++) arp[i].stop();
    }
  }








  /*********************************
      JOYSTICK
  */
  if (!delta_mode)
  {
    if (joy_X.has_changed()) X_CC.set_value(joy_X.value());
    if (!pitchbend_enable)
    {
      if (joy_Y.has_changed()) Y_CC.set_value(joy_Y.value());
    }
    else PB.set_value(joy_Y.value());
  }
  else
  {
    X_CC.increment_biais(joy_X.value() >> 4);
    if (!pitchbend_enable) Y_CC.increment_biais(joy_Y.value() >> 4);
    else PB.set_value(joy_Y.value());
  }

  X_CC.update();
  if (pitchbend_enable) PB.update();
  else Y_CC.update();



  /*
    if (X_CC.has_changed())  MIDI.sendControlChange(X_CC.get_control(), X_CC.get_value(), midi_channel);
    if (!pitchbend) if (Y_CC.has_changed())  MIDI.sendControlChange(Y_CC.get_control(), Y_CC.get_value(), midi_channel);
  */

  /************************
      BREATH
  */
  if (breath.has_changed())
  {
    breath_CC.set_value(breath.value());
  }
  if (played)  breath_CC.update();  // update to see if there is a change

  // if (breath_CC.has_changed() && played) MIDI.sendControlChange(breath_CC.get_control(), breath_CC.get_value(), midi_channel);







  /****************************
            ARPS
  */
  if (arpegio_mode == MODE_ARPEGIO)
  {
    if (modifier_up.has_been_released()) arp[0].stop();
    if (modifier_mid.has_been_released()) arp[1].stop();
    if (modifier_down.has_been_released()) arp[2].stop();

    if (modifier_up.has_been_pressed() && !arp[0].is_started()) arp[0].start();
    if (modifier_mid.has_been_pressed() && !arp[1].is_started()) arp[1].start();
    if (modifier_down.has_been_pressed() && !arp[2].is_started()) arp[2].start();
  }


  /*****************************
        MENU
  */
  if (modifier_sub_up.has_been_released()) midi_octave -= 1;
  if (modifier_sub_down.has_been_released()) midi_octave += 1;
  else if (joy_SW.has_been_released() && !joy_SW.has_been_released_after_long_press())
  {
    delta_mode = !delta_mode;

    /*
      if (delta_mode) ssd.draw_single_value("D");
      else ssd.clear();*/
  }
  if (joy_SW.has_been_released_after_long_press()) menu();
  // if (modifier_sub_up.is_pressed() && modifier_sub_down.is_pressed()) menu();


}
