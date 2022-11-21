#ifndef _presets_
#define _presets_


/*
      Combriat 2018, 2019, 2020, 2021
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing presets
*/



#include <EEPROM.h>


#define N_presets 20
#define N_presets_parameters 24
#define EEPROM_SIZE 2048
int current_preset = 0,current_preset_loaded = 0;

void eeprom_init();
void preset_save(byte i);
void preset_recall(byte i);

void increment_preset(int &preset, int inc) {
  preset += inc;
  if (preset < 0) preset = N_presets - 1;
  if (preset == N_presets) preset = 0;
}

#endif
