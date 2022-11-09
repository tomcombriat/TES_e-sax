/*
      Combriat 2018, 2019, 2020, 2021
      This file is part of the OS embedded in the e-sax SN4 - TES
      This code is under GPL3
      This is the main program. To be compiled in O2
*/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
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
#include "presets.h"
#include "battery.h"
#include "curved_analog_input.h"
#include "LEDstrand.h"




/***************************/
/******* DEFINE ************/
/***************************/

// Screen
#define OLED_DC     6
#define OLED_CS     4
#define OLED_RESET  12

// Strand
#define DATA_PIN 23

#define SUB_MODIFIER_RESPONSE_TIME 20
#define MODIFIER_RESPONSE_TIME 20
#define JOYSTICK_RESPONSE_TIME 10
#define JOYSTICK_SAFETY 30
#define BATTERY_RESPONSE_TIME 3000
#define BREATH_RESPONSE_TIME 1
#define CC_DELTA_TIME 40
#define CC_MIN_TIME 5
#define PITCHBEND_MIN_TIME 10
#define SCREEN_UPDATE_TIME 20
#define SCREEN_IDLE_WAITING_TIME 400
#define STRAND_RESPONSE_TIME 20
#define BATT_PIN A7
#define BREATH_THRESHOLD 1.1




Adafruit_SSD1306 display(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);


/*
  #define MODE_EWI 0
  #define MODE_ARPEGIO 1
  #define MODE_CHORD 2
  #define MODE_ARPEGIO_RAND 3*/

enum modes {MODE_NORMAL, MODE_EWI, MODE_ARPEGIO, MODE_CHORD, MODE_ARPEGIO_RAND};
enum chord_modes {REPLACE, STACK};
char global_modes[5] = {'N', 'E', 'A', 'C', 'R'};


#define JOY_BASE_TARGET_RANGE 127
#define JOY_PB_TARGET_RANGE 8192



/***************************/
/****** ANALOG INPUTS ******/
/***************************/
analog_input joy_Y(A4, 0, JOYSTICK_RESPONSE_TIME);
analog_input joy_X(A3, 0, JOYSTICK_RESPONSE_TIME);
//analog_input breath(PA1, 0, BREATH_RESPONSE_TIME, 20);
curved_analog_input breath(A5, 4055 * 2, 0, BREATH_RESPONSE_TIME, 7, 7);


/***************************/
/********* BUTTONS *********/
/***************************/
button joy_SW(16, false, JOYSTICK_RESPONSE_TIME);
button octave(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_up(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_mid(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_down(-1, true, MODIFIER_RESPONSE_TIME);
button modifier_sub_up(-1, true, SUB_MODIFIER_RESPONSE_TIME);
button modifier_sub_down(-1, true, SUB_MODIFIER_RESPONSE_TIME);
button up_menu(-1, true, SUB_MODIFIER_RESPONSE_TIME);
button down_menu(-1, true, SUB_MODIFIER_RESPONSE_TIME);
button right_menu(-1, true, SUB_MODIFIER_RESPONSE_TIME);
button left_menu(-1, true, SUB_MODIFIER_RESPONSE_TIME);


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
int8_t midi_transpose = 0;
int8_t midi_octave = 0;




/****************************/
/******* STATE **************/
/****************************/
bool delta_mode = true;
byte global_mode = MODE_NORMAL;
bool played = false;
bool pitchbend_enable = false;
bool dynamic_velocity = true;
bool HQ_breath = false;
byte chord_mode = STACK;
bool LED_mode = true;





/************************/
/***** MIDI CC **********/
/************************/
midi_cc X_CC(71, 64);
midi_cc Y_CC(1, 64);
midi_cc breath_CC(74);
midi_cc breath_LSB_CC(75);
midi_cc pitchbend_amp_CC(5);


/************************/
/****** TEMPO ***********/
/************************/
tap_tempo tap;



/************************/
/******** ARPS **********/
/************************/
arpegio_mono arp[3];
uint8_t selected_arp[3] = {0, 1, 2};



/************************/
/****** CHORD ***********/
/************************/
chord chords[3];
uint8_t selected_chord[3] = {0, 1, 2};


/************************/
/****** PITCHBEND *******/
/************************/
pitchbend PB;



/****************************/
/** NORMAL MODE MODIFIERS ***/
/****************************/
int8_t normal_up_modifier = +1;
int8_t normal_mid_modifier = -1;
int8_t normal_down_modifier = +7;





/*****************************/
/**** BATTERY ****************/
/*****************************/
battery batt(BATT_PIN, 2110, 2360, BATTERY_RESPONSE_TIME);

/*****************************
   STRAND
*/
LEDstrand strand;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);

  analogReadResolution(12);
  //Serial.begin(115200);


  pinMode(BATT_PIN, INPUT);

  display.clearDisplay();
  display.setCursor(30, 15);
  display.setTextColor(1, 0);
  display.setTextSize(4);
  display.print("TES");
  display.setCursor(35, 50);
  display.setTextSize(2);
  display.print("e-Sax");
  display.display();
  strip.begin();  // initialize strip (required!)
  strand.splash();
  //delay(200);
  for (int i = 0; i < 3; i++) arp[i].set_notes(arp_N[i], arp_times[i], arp_notes[i], arp_name[i], arp_long_names[i]);
  for (int i = 0; i < 3; i++) chords[i].set_notes(chord_N[i], chord_notes[i], chord_name[i], chord_long_names[i]);


  //joy_X.set_invert(true);
  //joy_Y.set_invert(true);
  joy_X.calibrate();
  joy_Y.calibrate();
  breath.calibrate();
  get_joy_input_ranges();
  joy_X.set_min_max(-127, 127);
  joy_Y.set_min_max(-127, 127);
  breath.set_min_max(0, 16383);

  display.setRotation(2);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  pitchbend_amp_CC.set_value(2);
  pitchbend_amp_CC.update();


  batt.update();
  batt.display_percentage();
  //eeprom_init();
  preset_recall(0);
  delay(500);
  joy_X.calibrate();
  joy_Y.calibrate();
  breath.calibrate();
  //MIDI.sendRealTime(midi::Clock);

  //for (int i=0; i<NUM_LEDS;i++) strip.setPixelColor(i,strip.ColorHSV(47000));
  // strip.show();


}

void loop() {


  if ((!played && millis() - stop_played_time > SCREEN_IDLE_WAITING_TIME) )
  {
    ssd.draw_standby_screen(midi_octave, midi_transpose, global_mode, delta_mode, X_CC.get_value(), Y_CC.get_value(), tap.get_tempo());
    ssd.update();
  }

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
  if (LED_mode)  strand.update();

  /*
    Serial.print(analogRead(A4));
    Serial.print(" ");
    Serial.print(joy_Y.up_down());
    Serial.print(" ");
    Serial.print(joy_X.up_down());
    Serial.print(" ");
    Serial.println(analogRead(A3));
  */

  // Serial.println(breath.value());
  if ((global_mode == MODE_ARPEGIO || global_mode == MODE_ARPEGIO_RAND) && tap.has_change())  for (byte i = 0; i < 3; i++)  arp[i].set_tempo(tap.get_tempo_time());   // update tempo of arpegiators


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
          if (i) MIDI.sendNoteOff(manager.get_previous_note()[i], 0, midi_channel + 1);
          else MIDI.sendNoteOff(manager.get_previous_note()[i], 0, midi_channel);
        }
      }
      played = false;
      stop_played_time = millis();
    }

    if (manager.get_note()[0] != 0 && breath.value() > 0)   // new note is playable  -> play it
    {
      byte vel = 127;
      if (dynamic_velocity) vel = breath.MSB();
      played = true;
      for (byte i = 0; i < POLYPHONY; i++)
      {
        if (manager.get_note()[i] != 0 && manager.get_previous_note()[i] != manager.get_note()[i])
        {
          if (i) MIDI.sendNoteOn(manager.get_note()[i], vel, midi_channel + 1);
          else MIDI.sendNoteOn(manager.get_note()[i], vel, midi_channel);
        }

      }
    }
  }  // end of   «if (manager.update())»





  if (breath.value() > 0 && !played && manager.get_note()[0] != 0)    // breath is loud enough to play note
  {
    byte vel = 127;
    if (dynamic_velocity) vel = breath.MSB();

    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (manager.get_note()[i] != 0)
      {
        if (i) MIDI.sendNoteOn(manager.get_note()[i], vel, midi_channel + 1);
        else MIDI.sendNoteOn(manager.get_note()[i], vel, midi_channel);
      }
      //else break;
    }
    played = true;
    if (global_mode == MODE_ARPEGIO || global_mode == MODE_ARPEGIO_RAND)
    {
      if (modifier_up.is_pressed()) arp[0].start();
      if (modifier_mid.is_pressed()) arp[1].start();
      if (modifier_down.is_pressed()) arp[2].start();
    }
  }



  if (breath.value() == 0 && played)    // breath is low enough to stop note
  {
    for (byte i = 0; i < POLYPHONY; i++)
    {
      if (manager.get_note()[i] != 0)
      {
        if (i) MIDI.sendNoteOff(manager.get_note()[i], 0, midi_channel + 1);
        else MIDI.sendNoteOff(manager.get_note()[i], 0, midi_channel);
      }
      //else break;
    }
    played = false;
    stop_played_time = millis();
  }


  if (global_mode == MODE_ARPEGIO || global_mode == MODE_ARPEGIO_RAND) // NEW: to catch that, sometimes, arp stops on a silent note (arp 1, 2, 3, 4)
  {
    if (breath.value() == 0)
    {
      for (byte i = 0; i < 3; i++) arp[i].stop();
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
    breath_CC.set_value(breath.MSB());
    if (HQ_breath) breath_LSB_CC.set_value(breath.LSB());
  }
  /*if (played)
  {*/
    breath_CC.update();  // update to see if there is a change
    if (HQ_breath)  breath_LSB_CC.update();
  //}

  // if (breath_CC.has_changed() && played) MIDI.sendControlChange(breath_CC.get_control(), breath_CC.get_value(), midi_channel);







  /****************************
            ARPS
  */
  if (global_mode == MODE_ARPEGIO || global_mode == MODE_ARPEGIO_RAND)
  {
    if (modifier_up.has_been_released()) arp[0].stop();
    if (modifier_mid.has_been_released()) arp[1].stop();
    if (modifier_down.has_been_released()) arp[2].stop();

    if (played)  // Just been pressed
    {
      if (modifier_up.has_been_pressed() && !arp[0].is_started()) arp[0].start();
      if (modifier_mid.has_been_pressed() && !arp[1].is_started()) arp[1].start();
      if (modifier_down.has_been_pressed() && !arp[2].is_started()) arp[2].start();
    }
  }

  if (global_mode != MODE_NORMAL)
  {
    /* if (modifier_sub_up.has_been_released())
      {
       midi_octave += 1;
      }*/
    if (modifier_sub_down.has_been_released())
    {
      if (octave.is_pressed()) midi_octave += 1;
      else midi_octave -= 1;
    }
  }


  /*****************************
        MENU
  */
  if (joy_SW.has_been_released() && !joy_SW.has_been_released_after_long_press())  //else ???
  {
    delta_mode = !delta_mode;
  }
  if (joy_SW.has_been_released_after_long_press())
  {
    joy_SW.reset();
    menu();
  }
  //if (joy_SW.has_been_pressed()) delta_mode = !delta_mode;
  // if (modifier_sub_up.is_pressed() && modifier_sub_down.is_pressed()) menu();


}
