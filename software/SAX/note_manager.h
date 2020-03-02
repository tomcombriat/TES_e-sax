#ifndef _note_manager_
#define _note_manager_

#define POLYPHONY 4


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
