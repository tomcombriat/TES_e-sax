#include "menu.h"

const int N_entry = 15;
int current_entry = 0;
String transpose_notes[12] = {":C", ":C#", ":D", ":D#", ":E", ":F", ":F#", ":G", ":G#", ":A", ":A#", ":B"};
String arp_mode[3] = {"N", "A", "C"};



void menu()
{

  bool exit = false;
  while (!exit)
  {
    joy_X.update();
    joy_Y.update();
    ssd.update();
    manager.update();
    modifier_up.update();
    modifier_mid.update();
    modifier_down.update();
    up_menu.update();
    down_menu.update();
    left_menu.update();
    right_menu.update();

    int up = joy_Y.up_down() + up_menu.has_been_pressed() - down_menu.has_been_pressed();


    switch (current_entry)
    {
      case 0:
        ssd.draw_title_value("octave", midi_octave);
        midi_octave += up;
        break;

      case 1:
        {
          int ranged_midi_transpose = midi_transpose;
          if (ranged_midi_transpose < 0) ranged_midi_transpose += 12;
          ranged_midi_transpose = ranged_midi_transpose % 12;
          ssd.draw_title_value("transpose", String (midi_transpose) + transpose_notes[ranged_midi_transpose]);
          midi_transpose += up;

          break;
        }

      case 2:
        ssd.draw_title_value("Br. sens.", breath_sensitivity);
        breath_sensitivity += up;
        if (breath_sensitivity > 10) breath_sensitivity = 10;
        else if (breath_sensitivity < -9) breath_sensitivity = -9;
        breath.set_scaling_factor(((breath_sensitivity * 0.1) + 1) * 127 / 2000.);
        break;

      case 3:
        ssd.draw_title_value("MIDI chan", midi_channel);
        midi_channel += up;
        if (midi_channel > 16) midi_channel = 16;
        if (midi_channel == 0) midi_channel = 16;
        break;

      case 4:
        if (X_CC.get_control() > 128) X_CC.set_control(128);
        ssd.draw_title_value("X CC", X_CC.get_control());
        X_CC.set_control(X_CC.get_control() + up);
        break;

      case 5:
        if (Y_CC.get_control() > 128) Y_CC.set_control(128);
        ssd.draw_title_value("Y CC", Y_CC.get_control());
        Y_CC.set_control(Y_CC.get_control() + up);
        break;

      case 6:
        ssd.draw_title_value("Arp Mode", arp_mode[arpegio_mode]);
        arpegio_mode += up;
        if (arpegio_mode > 2) arpegio_mode = 0;
        break;

      case 7:
        ssd.draw_title_value("Tempo", (int) tap.get_tempo());
        tap.set_tempo(tap.get_tempo() + up);
        break;

      case 8:
        ssd.draw_title_value("ARP 0", arp[0].get_name());
        selected_arp[0] += up;
        if (selected_arp[0] >= N_ARP) selected_arp[0] = 0;
        if (selected_arp[0] < 0) selected_arp[0] = N_ARP - 1;
        arp[0].set_notes(arp_N[selected_arp[0]], arp_times[selected_arp[0]], arp_notes[selected_arp[0]], arp_name[selected_arp[0]]);
        break;


      case 9:
        ssd.draw_title_value("ARP 1", arp[1].get_name());
        selected_arp[1] += up;
        if (selected_arp[1] >= N_ARP) selected_arp[1] = 0;
        if (selected_arp[1] < 0) selected_arp[1] = N_ARP - 1;
        arp[1].set_notes(arp_N[selected_arp[1]], arp_times[selected_arp[1]], arp_notes[selected_arp[1]], arp_name[selected_arp[1]]);
        break;

      case 10:
        ssd.draw_title_value("ARP 2", arp[2].get_name());
        selected_arp[2] += up;
        if (selected_arp[2] >= N_ARP) selected_arp[2] = 0;
        if (selected_arp[2] < 0) selected_arp[2] = N_ARP - 1;
        arp[2].set_notes(arp_N[selected_arp[2]], arp_times[selected_arp[2]], arp_notes[selected_arp[2]], arp_name[selected_arp[2]]);
        break;

      case 11:
        ssd.draw_title_value("Mod UP", normal_up_modifier);
        normal_up_modifier += up;
        break;

      case 12:
        ssd.draw_title_value("Mod MID", normal_mid_modifier);
        normal_mid_modifier += up;
        break;

      case 13:
        ssd.draw_title_value("Mod DWN", normal_down_modifier);
        normal_down_modifier += up;
        break;

      case 14:
        ssd.draw_title_value("Pitchbend", pitchbend_enable);
        pitchbend_enable += up;
        if (!pitchbend_enable)
        {
          joy_Y.set_scaling_factor(JOY_BASE_SCALING);
          joy_Y.set_min_max(-127, 127);
        }
        else
        {
          joy_Y.set_min_max(-8192, 8191);
          joy_Y.set_scaling_factor(JOY_PB_SCALING);
        }
        break;

    }

    current_entry += joy_X.up_down();
    current_entry += right_menu.has_been_pressed() - left_menu.has_been_pressed();
    if (current_entry < 0) current_entry = N_entry - 1;
    if (current_entry == N_entry) current_entry = 0;
    joy_SW.update();
    if (joy_SW.has_been_released_after_long_press()) exit = true;


#define MODE_NORMAL 0
#define MODE_ARPEGIO 1
#define MODE_CHORD 2
    if (arpegio_mode == MODE_ARPEGIO)
    {
      if (modifier_up.has_been_released()) current_entry = 8;
      if (modifier_mid.has_been_released()) current_entry = 9;
      if (modifier_down.has_been_released()) current_entry = 10;
    }
    else if (arpegio_mode == MODE_NORMAL)
    {
      if (modifier_up.has_been_released()) current_entry = 11;
      if (modifier_mid.has_been_released()) current_entry = 12;
      if (modifier_down.has_been_released()) current_entry = 13;
    }
  }
  ssd.clear();
  ssd.draw_standby_screen(midi_octave, midi_transpose, arpegio_mode, delta_mode, X_CC.get_value(),Y_CC.get_value(), tap.get_tempo());
  ssd.force_update();
}