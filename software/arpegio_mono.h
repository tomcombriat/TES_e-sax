#ifndef _arpegio_mono_
#define _arpegio_mono_

class arpegio_mono
{
  public:
    arpegio_mono();
    arpegio_mono(unsigned int N, float * times, int * notes);
    arpegio_mono(unsigned int N, float * times, int * notes,char _name);
    void set_notes(unsigned int N, float * times, int * notes);
    void set_notes(unsigned int N, float * times, int * notes,char _name);
    void set_tempo(unsigned long _tempo);
    int next();
    int previous();
    void start();
    void stop();
    bool change(byte current_note);  //
    bool is_started();
    char get_name();
    bool is_paused();
    void pause();


  private:
    unsigned int  N_note_arp;
    float *  times_arp;
    int * notes_arp;
    int  N_played = 0;
    bool started  = false;
    unsigned long start_time = 0, duration = 500;
    char arp_name;
    short next_note;
    short previous_note;
    bool paused;
};





#define N_ARP 5



 





const int arp0_N = 4;
float arp0_times[arp0_N] = {0.0,0.25,0.5,0.75};
int arp0_notes[arp0_N] = {0,7,19,12};
char arp0_name = 'C';

const int arp1_N = 4;
float arp1_times[arp1_N] = {0.0,0.25,0.5,0.75};
int arp1_notes[arp1_N] = {0,4,7,4};
char arp1_name = 'M';


const int arp2_N = 4;
float arp2_times[arp2_N] = {0.0,0.25,0.5,0.75};
int arp2_notes[arp2_N] = {0,3,7,3};
char arp2_name = 'm';


const int arp3_N = 3;
float arp3_times[arp3_N] = {0.0,0.5,0.75};
int arp3_notes[arp3_N] = {0,7,12};
char arp3_name = 'T';

const int arp4_N = 8;
float arp4_times[arp4_N] = {0.0,0.125,0.25,0.375,0.5,0.625,0.75,0.875};
int arp4_notes[arp4_N] = {0,-255,0,-255,0,-255,0,-255};
char arp4_name = '4';


float * arp_times[N_ARP] = {arp0_times, arp1_times,arp2_times,arp3_times,arp4_times};
int * arp_notes[N_ARP] = {arp0_notes, arp1_notes,arp2_notes,arp3_notes,arp4_notes};
char arp_name[N_ARP] = {arp0_name,arp1_name,arp2_name,arp3_name,arp4_name};
int arp_N[N_ARP] = {arp0_N,arp1_N,arp2_N,arp3_N,arp4_N};




/*
float arp3_times[4] = {0.0,0.25,0.5,0.75};
int arp3_notes[4] = {0,12,-7,7};
char arp3_name = 'W';
*/




#endif
