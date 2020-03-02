#ifndef _note_manager_
#define _note_manager_

#define POLYPHONY 4


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing the mapping between keys and notes
*/


class note_manager
{
  public:
    note_manager();
    bool update();
    byte * get_note();
    byte * get_previous_note();
    int get_up_down();
    int get_right_left();



  private:
    unsigned int previous_touch_no_mod = 0;
    int up_down = 0;
    int right_left = 0;




};



#endif
