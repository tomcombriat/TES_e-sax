#ifndef _arpegio_mono_
#define _arpegio_mono_



/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3


      This is the include file for the class managing arpegiators
*/




class arpegio_mono
{
  public:
    arpegio_mono();
    arpegio_mono(unsigned int N, float * times, int * notes);
    arpegio_mono(unsigned int N, float * times, int * notes, char _name);
    void set_notes(unsigned int N, float * times, int * notes);
    void set_notes(unsigned int N, float * times, int * notes, char _name);
    void set_notes(unsigned int N, float * times, int * notes, char _name, String * l_name);
    void set_tempo(unsigned long _tempo);
    void set_sustain_scaling(int _sustain_scaling);
    int next();
    int previous();
    void start();
    void stop();
    bool change(byte current_note);
    bool is_started();
    char get_name();
    String * get_long_name();
    bool is_paused();
    void pause();
    int get_duration_scaling();
    unsigned int get_N_notes();
    int * get_notes();


  private:
    int duration_scaling = 1;  // for arp last more than one measure for instance
    unsigned int  N_note_arp;
    float *  times_arp;
    int * notes_arp;
    unsigned int  next_index = 0;
    bool started  = false;
    unsigned long start_time = 0, duration = 500, next_event_time = 0, next_silent_time = 0;
    char arp_name;
    String * long_name;
    short next_note;
    short previous_note;
    bool paused;
    int sustain_scaling = 127; // for shutting down the note before its real end (very electro): 127: full length, 0: no length.
};





#define N_ARP 11



const int arp0_N = 4;
float arp0_times[arp0_N] = {0.0, 0.25, 0.5, 0.75};
int arp0_notes[arp0_N] = {0, 7, 19, 12};
char arp0_name = 'C';
String arp0_long_name = "Classic";

const int arp1_N = 4;
float arp1_times[arp1_N] = {0.0, 0.25, 0.5, 0.75};
int arp1_notes[arp1_N] = {0, 4, 7, 4};
char arp1_name = 'M';
String arp1_long_name = "Maj";


const int arp2_N = 4;
float arp2_times[arp2_N] = {0.0, 0.25, 0.5, 0.75};
int arp2_notes[arp2_N] = {0, 3, 7, 3};
char arp2_name = 'm';
String arp2_long_name = "min";


const int arp3_N = 3;
float arp3_times[arp3_N] = {0.0, 0.5, 0.75};
int arp3_notes[arp3_N] = {0, 7, 12};
char arp3_name = 'T';
String arp3_long_name = "F/o";


const int arp4_N = 8;
float arp4_times[arp4_N] = {0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875};
int arp4_notes[arp4_N] = {0, -255, 0, -255, 0, -255, 0, -255};
char arp4_name = '4';
String arp4_long_name = "4";

const int arp5_N = 4;
float arp5_times[arp5_N] = {0.0, 0.25, 0.5, 0.75};
int arp5_notes[arp5_N] = {0, -255, 0, -255};
char arp5_name = '2';
String arp5_long_name = "2";

const int arp6_N = 2;
float arp6_times[arp6_N] = {0.0, 0.5};
int arp6_notes[arp6_N] = {0, -255};
char arp6_name = '1';
String arp6_long_name = "1";

const int arp7_N = 6;
float arp7_times[arp7_N] = {0.0, 1. / 6, 1. / 3, 0.5, 2. / 3, 5. / 6};
int arp7_notes[arp7_N] = {0, -255, 0, -255, 0, -255};
char arp7_name = '3';
String arp7_long_name = "3";

const int arp8_N = 4;
float arp8_times[arp8_N] = {0.0, 0.25, 0.5, 0.75};
int arp8_notes[arp8_N] = {0, 7, -5, 12};
char arp8_name = 'F';
String arp8_long_name = "Fifth";

const int arp9_N = 15;
float arp9_times[arp9_N] = {0.0, 0.15, 0.25, 0.4, 0.5, 0.65, 0.75, 1., 1.15, 1.25, 1.40, 1.50, 1.65, 1.75, 1.9};
int arp9_notes[arp9_N] = {0, -255, 0,  -255, 0, -255, 0, 3, -255, 2, -255, -5, -255, -2, -255};
char arp9_name = 'S';
String arp9_long_name = "Amb";

const int arp10_N = 8;
float arp10_times[arp10_N] = {0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75};
int arp10_notes[arp10_N] = {0, 7, 3, 10, 0, 7, 5, 10};
char arp10_name = 'P';
String arp10_long_name = "Penta";


// Really need to find another to do this, while being statically allocated...

float * arp_times[N_ARP] = {arp0_times, arp1_times, arp2_times, arp3_times, arp4_times, arp7_times, arp5_times, arp6_times, arp8_times, arp9_times, arp10_times};
int * arp_notes[N_ARP] = {arp0_notes, arp1_notes, arp2_notes, arp3_notes, arp4_notes, arp7_notes, arp5_notes, arp6_notes, arp8_notes, arp9_notes, arp10_notes};
char arp_name[N_ARP] = {arp0_name, arp1_name, arp2_name, arp3_name, arp4_name, arp7_name, arp5_name, arp6_name, arp8_name, arp9_name, arp10_name};
int arp_N[N_ARP] = {arp0_N, arp1_N, arp2_N, arp3_N, arp4_N, arp7_N, arp5_N, arp6_N, arp8_N, arp9_N, arp10_N};
String * arp_long_names[N_ARP] = {&arp0_long_name, &arp1_long_name, &arp2_long_name, &arp3_long_name, &arp4_long_name, &arp7_long_name, &arp5_long_name, &arp6_long_name, &arp8_long_name, &arp9_long_name, &arp10_long_name};




/*
  float arp3_times[4] = {0.0,0.25,0.5,0.75};
  int arp3_notes[4] = {0,12,-7,7};
  char arp3_name = 'W';
*/




#endif
