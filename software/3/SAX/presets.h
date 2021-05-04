#ifndef _presets_
#define _presets_


/*
      Combriat 2018, 2019, 2020, 2021
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the class file for the class managing presets
*/



#include <EEPROM.h>


#define N_presets 2
#define N_presets_parameters 25
int current_preset = 0;

void eeprom_init();
void preset_save(byte i);
void preset_recall(byte i);


#endif
