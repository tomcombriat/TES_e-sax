#ifndef _screen_
#define _screen_

class screen
{
  public:
    screen();
    void draw_title_value(String title, int value);
    void draw_title_value(String title, String value);
    void draw_title_value(String title, char value);
    void draw_single_value(String value);
    void draw_standby_screen(int & _octave, int & _transpose, byte _global_mode, bool _delta_mode, byte _joystick, byte _joystick_bis, unsigned long tempo);
    void draw_progress_bar(byte value);

    void clear();
    void update();
    void force_update();

  private:
    unsigned long last_update_time = 0;
    int previous_keyprint = 0;
    String previous_value = "aaaa";
    bool changed = false;

    int octave = 0;
    int transpose = 0;
    byte global_mode = 0;
    bool delta_mode = 0;
    byte joystick = 0;
    byte joystick_bis = 0;
    unsigned long tempo = 120;
};

char global_modes[3] = {'N', 'A', 'C'};



#endif
