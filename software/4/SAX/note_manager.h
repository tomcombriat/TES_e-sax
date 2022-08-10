#ifndef _note_manager_
#define _note_manager_

#define POLYPHONY 12


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing the mapping between keys and notes
*/


byte note[POLYPHONY] = {0};
byte previous_note[POLYPHONY] = {0};

class note_manager
{
  public:
    note_manager();
    bool update();
    byte * get_note();
    byte * get_previous_note();




  private:
    unsigned int previous_touch_no_mod = 0;





};



#endif
