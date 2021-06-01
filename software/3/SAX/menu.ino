#include "menu.h"


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the file for the class managing the menu
*/





int N_entry = 17;
int current_entry = 0;
String transpose_notes[12] = {":C", ":C#", ":D", ":D#", ":E", ":F", ":F#", ":G", ":G#", ":A", ":A#", ":B"};
//char arp_mode[4] = {'N', 'A', 'C', 'R'};







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
    modifier_sub_up.update();
    modifier_sub_down.update();
    up_menu.update();
    down_menu.update();
    left_menu.update();
    right_menu.update();
    octave.update();



    int up = 0;

    if (!joy_SW.is_pressed()) up = joy_Y.up_down() + up_menu.has_been_pressed() - down_menu.has_been_pressed();



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
        ssd.draw_title_value("Br. sens.", breath.get_sensitivity());
        //breath_sensitivity += up;
        breath.set_sensitivity(breath.get_sensitivity() + up);
        //breath.set_scaling_factor(((breath_sensitivity * 0.1) + 1) * 127 / 2000.);
        break;


      case 3:
        ssd.draw_title_value("Br. curv.", breath.get_curvature());
        //breath_sensitivity += up;
        breath.set_curvature(breath.get_curvature() + up);
        //breath.set_scaling_factor(((breath_sensitivity * 0.1) + 1) * 127 / 2000.);
        break;


      case 4:
        ssd.draw_title_value("MIDI chan", midi_channel);
        midi_channel += up;
        if (midi_channel > 16) midi_channel = 0;
        if (midi_channel == 0) midi_channel = 16;
        break;

      case 5:
        if (X_CC.get_control() > 128) X_CC.set_control(128);
        ssd.draw_title_value("X CC", X_CC.get_control());
        X_CC.set_control(X_CC.get_control() + up);
        break;

      case 6:
        if (Y_CC.get_control() > 128) Y_CC.set_control(128);
        ssd.draw_title_value("Y CC", Y_CC.get_control());
        Y_CC.set_control(Y_CC.get_control() + up);
        break;

      case 7:
        if (breath_CC.get_control() > 128) breath_CC.set_control(128);
        ssd.draw_title_value("Breath CC", breath_CC.get_control());
        breath_CC.set_control(breath_CC.get_control() + up);
        break;

      case 8:
        if (pitchbend_amp_CC.get_control() > 128) pitchbend_amp_CC.set_control(128);
        ssd.draw_title_value("PB amp CC", pitchbend_amp_CC.get_control());
        pitchbend_amp_CC.set_control(pitchbend_amp_CC.get_control() + up);
        break;

      case 9:
        ssd.draw_title_value("PB O/1", pitchbend_enable);
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

      case 10:
        {
          int current_value = pitchbend_amp_CC.get_value();
          ssd.draw_title_value("PitchB Amp", current_value);
          if (up != 0)
          {
            current_value += up;
            pitchbend_amp_CC.set_value(current_value);
            pitchbend_amp_CC.update();
          }
          break;
        }


      case 11:
        ssd.draw_title_value("Dyn. Vel.", dynamic_velocity);
        dynamic_velocity += up;
        break;


      case 12:
        ssd.draw_title_value("Global Mode", global_modes[global_mode]);
        global_mode += up;
        if (global_mode > 4) global_mode = 0;
        if (global_mode < 0) global_mode = 4;
        break;

      case 13:
        ssd.draw_title_value("Save Pt", current_preset);
        current_preset += up;
        if (current_preset >= N_presets) current_preset = 0;
        if (current_preset < 0) current_preset = N_presets - 1;

        if (joy_SW.has_been_released())
        {
          preset_save(current_preset);
          ssd.draw_single_value("OK");
          ssd.force_update();
          delay(1000);
        }
        break;

      case 14:
        ssd.draw_title_value("Recall Pt", current_preset);
        current_preset += up;
        if (current_preset >= N_presets) current_preset = 0;
        if (current_preset < 0) current_preset = N_presets - 1;

        if (joy_SW.has_been_released())
        {
          preset_recall(current_preset);
          ssd.draw_single_value("OK");
          ssd.force_update();
          delay(1000);
        }
        break;

      case 15:
        ssd.draw_title_value("Tempo", (int) tap.get_tempo());
        tap.set_tempo(tap.get_tempo() + up);
        break;

      case 16:
        ssd.draw_title_value("Crazy tempo", "?!");
        if (up != 0) tap.set_tempo(400);
        break;


      case 17:
        switch (global_mode)
        {
          case MODE_ARPEGIO:
            ssd.draw_title_value("ARP 0", arp[0].get_long_name(), arp[0].get_N_notes(), arp[0].get_notes(), arp[0].get_duration_scaling());
            selected_arp[0] += up;
            if (selected_arp[0] >= N_ARP) selected_arp[0] = 0;
            if (selected_arp[0] < 0) selected_arp[0] = N_ARP - 1;
            arp[0].set_notes(arp_N[selected_arp[0]], arp_times[selected_arp[0]], arp_notes[selected_arp[0]], arp_name[selected_arp[0]], arp_long_names[selected_arp[0]]);
            break;
          case MODE_ARPEGIO_RAND:
            ssd.draw_title_value("ARP 0", arp[0].get_long_name(), arp[0].get_N_notes(), arp[0].get_notes(), arp[0].get_duration_scaling());
            selected_arp[0] += up;
            if (selected_arp[0] >= N_ARP) selected_arp[0] = 0;
            if (selected_arp[0] < 0) selected_arp[0] = N_ARP - 1;
            arp[0].set_notes(arp_N[selected_arp[0]], arp_times[selected_arp[0]], arp_notes[selected_arp[0]], arp_name[selected_arp[0]], arp_long_names[selected_arp[0]]);
            break;
          case MODE_EWI:
            ssd.draw_title_value("Mod UP", normal_up_modifier);
            normal_up_modifier += up;
            break;
          case MODE_CHORD:
            //ssd.draw_title_value("CHORD 0", chords[0].get_name());
            ssd.draw_title_value("CHORD 0", chords[0].get_long_name(), chords[0].get_N_notes(), chords[0].get_notes());
            selected_chord[0] += up;
            if (selected_chord[0] >= N_CHORD) selected_chord[0] = 0;
            if (selected_chord[0] < 0) selected_chord[0] = N_CHORD - 1;
            chords[0].set_notes(chord_N[selected_chord[0]],  chord_notes[selected_chord[0]], chord_name[selected_chord[0]], chord_long_names[selected_chord[0]]);
            break;
        }
        break;

      case 18:
        switch (global_mode)
        {
          case MODE_ARPEGIO:
            ssd.draw_title_value("ARP 1", arp[1].get_long_name(), arp[1].get_N_notes(), arp[1].get_notes(), arp[1].get_duration_scaling());
            selected_arp[1] += up;
            if (selected_arp[1] >= N_ARP) selected_arp[1] = 0;
            if (selected_arp[1] < 0) selected_arp[1] = N_ARP - 1;
            arp[1].set_notes(arp_N[selected_arp[1]], arp_times[selected_arp[1]], arp_notes[selected_arp[1]], arp_name[selected_arp[1]], arp_long_names[selected_arp[1]]);
            break;
          case MODE_ARPEGIO_RAND:
            ssd.draw_title_value("ARP 1", arp[1].get_long_name(), arp[1].get_N_notes(), arp[1].get_notes(), arp[1].get_duration_scaling());
            selected_arp[1] += up;
            if (selected_arp[1] >= N_ARP) selected_arp[1] = 0;
            if (selected_arp[1] < 0) selected_arp[1] = N_ARP - 1;
            arp[1].set_notes(arp_N[selected_arp[1]], arp_times[selected_arp[1]], arp_notes[selected_arp[1]], arp_name[selected_arp[1]], arp_long_names[selected_arp[1]]);
            break;
          case MODE_EWI:
            ssd.draw_title_value("Mod MID", normal_mid_modifier);
            normal_mid_modifier += up;
            break;
          case MODE_CHORD:
            ssd.draw_title_value("CHORD 1", chords[1].get_long_name(), chords[1].get_N_notes(), chords[1].get_notes());
            selected_chord[1] += up;
            if (selected_chord[1] >= N_CHORD) selected_chord[1] = 0;
            if (selected_chord[1] < 0) selected_chord[1] = N_CHORD - 1;
            chords[1].set_notes(chord_N[selected_chord[1]],  chord_notes[selected_chord[1]], chord_name[selected_chord[1]], chord_long_names[selected_chord[1]]);
            break;
        }
        break;

      case 19:
        switch (global_mode)
        {
          case MODE_ARPEGIO:
            ssd.draw_title_value("ARP 2", arp[2].get_long_name(), arp[2].get_N_notes(), arp[2].get_notes(), arp[2].get_duration_scaling());
            selected_arp[2] += up;
            if (selected_arp[2] >= N_ARP) selected_arp[2] = 0;
            if (selected_arp[2] < 0) selected_arp[2] = N_ARP - 1;
            arp[2].set_notes(arp_N[selected_arp[2]], arp_times[selected_arp[2]], arp_notes[selected_arp[2]], arp_name[selected_arp[2]], arp_long_names[selected_arp[2]]);
            break;
          case MODE_ARPEGIO_RAND:
            ssd.draw_title_value("ARP 2", arp[2].get_long_name(), arp[2].get_N_notes(), arp[2].get_notes(), arp[2].get_duration_scaling());
            selected_arp[2] += up;
            if (selected_arp[2] >= N_ARP) selected_arp[2] = 0;
            if (selected_arp[2] < 0) selected_arp[2] = N_ARP - 1;
            arp[2].set_notes(arp_N[selected_arp[2]], arp_times[selected_arp[2]], arp_notes[selected_arp[2]], arp_name[selected_arp[2]], arp_long_names[selected_arp[2]]);
            break;
          case MODE_EWI:
            ssd.draw_title_value("Mod DWN", normal_down_modifier);
            normal_down_modifier += up;
            break;
          case MODE_CHORD:
            ssd.draw_title_value("CHORD 2", chords[2].get_long_name(), chords[2].get_N_notes(), chords[2].get_notes());
            selected_chord[2] += up;
            if (selected_chord[2] >= N_CHORD) selected_chord[2] = 0;
            if (selected_chord[2] < 0) selected_chord[2] = N_CHORD - 1;
            chords[2].set_notes(chord_N[selected_chord[2]],  chord_notes[selected_chord[2]], chord_name[selected_chord[2]], chord_long_names[selected_chord[2]]);
            break;
        }
        break;
    }


    int inc_current_entry = joy_X.up_down() + right_menu.has_been_pressed() - left_menu.has_been_pressed();
    /*
        current_entry += joy_X.up_down();
        current_entry += right_menu.has_been_pressed() - left_menu.has_been_pressed();*/
    if (inc_current_entry != 0)
    {
      current_entry += inc_current_entry;
    }


    if (global_mode == MODE_NORMAL) N_entry = 15;
    else N_entry = 20;

    if (current_entry < 0) current_entry = N_entry - 1;
    if (current_entry >= N_entry) current_entry = 0;
    joy_SW.update();
    if (joy_SW.has_been_released_after_long_press()) exit = true;

    if (octave.is_pressed()) current_entry = 0;
    if (global_mode != MODE_NORMAL)
    {
      if (modifier_up.has_been_released()) current_entry = 17;
      if (modifier_mid.has_been_released()) current_entry = 18;
      if (modifier_down.has_been_released()) current_entry = 19;

    }
    else if (modifier_up.has_been_released() || modifier_mid.has_been_released() || modifier_down.has_been_released()) current_entry = 12;

    if (modifier_sub_up.has_been_released()) current_entry = 13;
    if (modifier_sub_down.has_been_released()) current_entry = 14;

  }




  ssd.clear();
  ssd.draw_standby_screen(midi_octave, midi_transpose, global_mode, delta_mode, X_CC.get_value(), Y_CC.get_value(), tap.get_tempo());
  ssd.force_update();

}
