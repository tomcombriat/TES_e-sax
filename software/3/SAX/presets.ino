#include "presets.h"
#include "arpegio_mono.h"
#include "chord.h"
#include "midi_cc.h"

/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing presets
*/



/* Parameters to save:
    byte midi_channel = 2;
    int midi_transpose = 0;
    int midi_octave = 0;     3

    int global_mode = MODE_NORMAL;
    int breath_sensitivity = 3;     5

    bool pitchbend_enable = false;
    bool dynamic_velocity = true;
    bool delta_mode = true;     6 (grouped)


    int normal_up_modifier = +1;
    int normal_mid_modifier = -1;
    int normal_down_modifier = +7;      9

    int selected_chord[3] = {0, 1, 2};    12

    int selected_arp[3] = {0, 1, 2};      15

  byte  midi_cc X_CC(71, 64);
  byte midi_cc Y_CC(1, 64);
  byte midi_cc breath_CC(74);
  byte midi_cc pitchbend_amp_CC(5);   21

  int pitchbend_amp_CC get_value() / set_value()
  int X_CC get_value() / set_value()      23

*/




void eeprom_init()
{
  EEPROM.init();
  delay(100);
  uint16 data;
  EEPROM.read(EEPROM.PageBase0, &data);
  if (data == 65535)
  {
    for (byte i = 0; i < N_presets; i++)
    {
      preset_save(i);
    }
  }
}


void preset_save(byte i)
{
  if (i < 5)
  {
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters, static_cast<uint16> (midi_channel));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 1, static_cast<uint16> (midi_transpose));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 2, static_cast<uint16> (midi_octave));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 3, static_cast<uint16> (global_mode));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 4, static_cast<uint16> (breath.get_sensitivity()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 5, static_cast<uint16> (pitchbend_enable + (dynamic_velocity << 1) + (delta_mode << 2) + (HQ_breath << 3)));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 6, static_cast<uint16> (normal_up_modifier));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 7, static_cast<uint16> (normal_mid_modifier));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 8, static_cast<uint16> (normal_down_modifier));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 9, static_cast<uint16> (selected_chord[0]));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 10, static_cast<uint16> (selected_chord[1]));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 11, static_cast<uint16> (selected_chord[2]));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 12, static_cast<uint16> (selected_arp[0]));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 13, static_cast<uint16> (selected_arp[1]));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 14, static_cast<uint16> (selected_arp[2]));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 15, static_cast<uint16> (X_CC.get_control()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 16, static_cast<uint16> (Y_CC.get_control()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 17, static_cast<uint16> (breath_CC.get_control()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 18, static_cast<uint16> (pitchbend_amp_CC.get_control()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 19, static_cast<uint16> (X_CC.get_biais()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 20, static_cast<uint16> (Y_CC.get_biais()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 21, static_cast<uint16> (pitchbend_amp_CC.get_value()));
    EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 22, static_cast<uint16> (breath.get_curvature()));
  }
  else
  {
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters, static_cast<uint16> (midi_channel));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 1, static_cast<uint16> (midi_transpose));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 2, static_cast<uint16> (midi_octave));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 3, static_cast<uint16> (global_mode));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 4, static_cast<uint16> (breath.get_sensitivity()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 5, static_cast<uint16> (pitchbend_enable + (dynamic_velocity << 1) + (delta_mode << 2)+ (HQ_breath << 3)));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 6, static_cast<uint16> (normal_up_modifier));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 7, static_cast<uint16> (normal_mid_modifier));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 8, static_cast<uint16> (normal_down_modifier));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 9, static_cast<uint16> (selected_chord[0]));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 10, static_cast<uint16> (selected_chord[1]));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 11, static_cast<uint16> (selected_chord[2]));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 12, static_cast<uint16> (selected_arp[0]));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 13, static_cast<uint16> (selected_arp[1]));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 14, static_cast<uint16> (selected_arp[2]));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 15, static_cast<uint16> (X_CC.get_control()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 16, static_cast<uint16> (Y_CC.get_control()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 17, static_cast<uint16> (breath_CC.get_control()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 18, static_cast<uint16> (pitchbend_amp_CC.get_control()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 19, static_cast<uint16> (X_CC.get_biais()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 20, static_cast<uint16> (Y_CC.get_biais()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 21, static_cast<uint16> (pitchbend_amp_CC.get_value()));
    EEPROM.write(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 22, static_cast<uint16> (breath.get_curvature()));

    /* EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 22, static_cast<uint16> (X_CC.get_value()));
      EEPROM.write(EEPROM.PageBase0 + i * N_presets_parameters + 23, static_cast<uint16> (Y_CC.get_value()));*/
  }
}

void preset_recall(byte i)
{
  if (i < 5)
  {
    uint16 data;
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters, &data);
    midi_channel = static_cast<byte>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 1, &data);
    midi_transpose = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 2, &data);
    midi_octave = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 3, &data);
    global_mode = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 4, &data);
    breath.set_sensitivity(static_cast<short>(data));
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 5, &data);
    pitchbend_enable = bool(data & 0b1);
    dynamic_velocity = bool(data & 0b10);
    delta_mode = bool(data & 0b100);
    HQ_breath = bool (data & 0b1000);

    if (!pitchbend_enable)
    {
      joy_Y.compute_scaling_factor(JOY_BASE_TARGET_RANGE);
      joy_Y.set_min_max(-JOY_BASE_TARGET_RANGE, JOY_BASE_TARGET_RANGE);
    }
    else
    {
      joy_Y.set_min_max(-JOY_PB_TARGET_RANGE, JOY_PB_TARGET_RANGE - 1);
      joy_Y.compute_scaling_factor(JOY_PB_TARGET_RANGE);
    }
    joy_X.compute_scaling_factor(JOY_BASE_TARGET_RANGE);

    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 6, &data);
    normal_up_modifier = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 7, &data);
    normal_mid_modifier = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 8, &data);
    normal_down_modifier = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 9, &data);
    selected_chord[0] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 10, &data);
    selected_chord[1] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 11, &data);
    selected_chord[2] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 12, &data);
    selected_arp[0] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 13, &data);
    selected_arp[1] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 14, &data);
    selected_arp[2] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 15, &data);
    X_CC.set_control(static_cast<byte>(data));
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 16, &data);
    Y_CC.set_control(static_cast<byte>(data));
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 17, &data);
    breath_CC.set_control(static_cast<byte>(data));
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 18, &data);
    pitchbend_amp_CC.set_control(static_cast<byte>(data));
    /*  EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 19, &data);
      pitchbend_amp_CC.set_value(static_cast<int16>(data));
        pitchbend_amp_CC.update();*/
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 19, &data);
    X_CC.set_biais(static_cast<int16>(data));
    X_CC.update();
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 20, &data);
    Y_CC.set_biais(static_cast<int16>(data));
    Y_CC.update();
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 21, &data);
    pitchbend_amp_CC.set_value(static_cast<int16>(data));
    pitchbend_amp_CC.update();
    EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 22, &data);
    breath.set_curvature(static_cast<short>(data));

    /*  EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 22, &data);
      X_CC.set_value(static_cast<int16>(data));
      X_CC.update();
      EEPROM.read(EEPROM.PageBase0 + i * N_presets_parameters + 23, &data);
      Y_CC.set_value(static_cast<int16>(data));
      Y_CC.update();
    */
  }
  else
  {
    uint16 data;
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters, &data);
    midi_channel = static_cast<byte>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 1, &data);
    midi_transpose = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 2, &data);
    midi_octave = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 3, &data);
    global_mode = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 4, &data);
    breath.set_sensitivity(static_cast<short>(data));
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 5, &data);
    pitchbend_enable = bool(data & 0b1);
    dynamic_velocity = bool(data & 0b10);
    delta_mode = bool(data & 0b100);
    HQ_breath = bool (data & 0b1000);

    if (!pitchbend_enable)
    {
      joy_Y.compute_scaling_factor(JOY_BASE_TARGET_RANGE);
      joy_Y.set_min_max(-JOY_BASE_TARGET_RANGE, JOY_BASE_TARGET_RANGE);
    }
    else
    {
      joy_Y.set_min_max(-JOY_PB_TARGET_RANGE, JOY_PB_TARGET_RANGE - 1);
      joy_Y.compute_scaling_factor(JOY_PB_TARGET_RANGE);
    }
    joy_X.compute_scaling_factor(JOY_BASE_TARGET_RANGE);

    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 6, &data);
    normal_up_modifier = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 7, &data);
    normal_mid_modifier = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 8, &data);
    normal_down_modifier = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 9, &data);
    selected_chord[0] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 10, &data);
    selected_chord[1] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 11, &data);
    selected_chord[2] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 12, &data);
    selected_arp[0] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 13, &data);
    selected_arp[1] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 14, &data);
    selected_arp[2] = static_cast<int16>(data);
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 15, &data);
    X_CC.set_control(static_cast<byte>(data));
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 16, &data);
    Y_CC.set_control(static_cast<byte>(data));
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 17, &data);
    breath_CC.set_control(static_cast<byte>(data));
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 18, &data);
    pitchbend_amp_CC.set_control(static_cast<byte>(data));
    /*  EEPROM.read(EEPROM.PageBase1 + (i-10) * N_presets_parameters + 19, &data);
      pitchbend_amp_CC.set_value(static_cast<int16>(data));
        pitchbend_amp_CC.update();*/
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 19, &data);
    X_CC.set_biais(static_cast<int16>(data));
    X_CC.update();
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 20, &data);
    Y_CC.set_biais(static_cast<int16>(data));
    Y_CC.update();
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 21, &data);
    pitchbend_amp_CC.set_value(static_cast<int16>(data));
    pitchbend_amp_CC.update();
    EEPROM.read(EEPROM.PageBase1 + (i - 5) * N_presets_parameters + 22, &data);
    breath.set_curvature(static_cast<short>(data));
  }

  for (int j = 0; j < 3; j++) arp[j].set_notes(arp_N[selected_arp[j]], arp_times[selected_arp[j]], arp_notes[selected_arp[j]], arp_name[selected_arp[j]], arp_long_names[selected_arp[j]]);
  for (int j = 0; j < 3; j++) chords[j].set_notes(chord_N[selected_chord[j]],  chord_notes[selected_chord[j]], chord_name[selected_chord[j]], chord_long_names[selected_chord[j]]);
  //breath.set_scaling_factor(((breath_sensitivity * 0.1) + 1) * 127 / 2000.);
}

void get_joy_input_ranges()
{
  uint16 data;
  EEPROM.read(EEPROM.PageBase1 + (N_presets) * N_presets_parameters + 23, &data);
  joy_X.set_input_range(static_cast<int16>(data));
  EEPROM.read(EEPROM.PageBase1 + (N_presets) * N_presets_parameters + 24, &data);
  joy_Y.set_input_range(static_cast<int16>(data));

  if (!pitchbend_enable)
  {
    joy_Y.compute_scaling_factor(JOY_BASE_TARGET_RANGE);
    joy_Y.set_min_max(-JOY_BASE_TARGET_RANGE, JOY_BASE_TARGET_RANGE);
  }
  else
  {
    joy_Y.set_min_max(-JOY_PB_TARGET_RANGE, JOY_PB_TARGET_RANGE - 1);
    joy_Y.compute_scaling_factor(JOY_PB_TARGET_RANGE);
  }
  joy_X.compute_scaling_factor(JOY_BASE_TARGET_RANGE);
}


int save_joy_input_ranges()
{
  EEPROM.write(EEPROM.PageBase1 + (N_presets) * N_presets_parameters + 23, static_cast<uint16> (joy_X.get_input_range()));
  EEPROM.write(EEPROM.PageBase1 + (N_presets) * N_presets_parameters + 24, static_cast<uint16> (joy_Y.get_input_range()));
}


