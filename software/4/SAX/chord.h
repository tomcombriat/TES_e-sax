#ifndef _chord_
#define _chord_




class chord
{
  public:
    chord();
    chord(unsigned int N, int * _notes);
    void  set_notes(unsigned int N, int * _notes);
    void  set_notes(unsigned int N, int * _notes, char _name);
    void  set_notes(unsigned int N, int * _notes, char _name, String * _long_name);
    void apply(byte * note);
    char get_name();
    String * get_long_name();
    unsigned int get_N_notes();
    int * get_notes();

  private:
    char chord_name;
    String * long_name;
    int * notes;
    unsigned int N_notes;
};


#define N_CHORD 12


const unsigned int chord0_N = 2;
int chord0_notes[chord0_N] = {0, 7};
char chord0_name = 'P';
String chord0_long_name = "Power";

const unsigned int chord1_N = 4;
int chord1_notes[chord1_N] = {0, 7, 9, 12};
char chord1_name = '7';
String chord1_long_name = "7th";

const unsigned int chord2_N = 4;
int chord2_notes[chord2_N] = {0, 7, 12, -12};
char chord2_name = 'B';
String chord2_long_name = "Full B";

const unsigned int chord3_N = 3;
int chord3_notes[chord3_N] = {0, 3, 7};
char chord3_name = 'm';
String chord3_long_name = "min";

const unsigned int chord4_N = 3;
int chord4_notes[chord4_N] = {0, 4, 7};
char chord4_name = 'M';
String chord4_long_name = "Maj";

const unsigned int chord5_N = 4;
int chord5_notes[chord5_N] = {0, 4, 7, 11};
char chord5_name = '7';
String chord5_long_name = "Maj7";

const unsigned int chord6_N = 4;
int chord6_notes[chord6_N] = {0, 4, 7, 10};
char chord6_name = '7';
String chord6_long_name = "dom7";

const unsigned int chord7_N = 4;
int chord7_notes[chord7_N] = {0, 3, 7, 10};
char chord7_name = '7';
String chord7_long_name = "m7";


const unsigned int chord8_N = 3;
int chord8_notes[chord8_N] = {0, 2, 7};
char chord8_name = '2';
String chord8_long_name = "sus2";


const unsigned int chord9_N = 3;
int chord9_notes[chord9_N] = {0, 5, 7};
char chord9_name = '4';
String chord9_long_name = "sus4";

const unsigned int chord10_N = 3;
int chord10_notes[chord10_N] = {0, 4, 9};
char chord10_name = '6';
String chord10_long_name = "maj6no5";

const unsigned int chord11_N = 2;
int chord11_notes[chord11_N] = {0, 5};
char chord11_name = '5';
String chord11_long_name = "d5";



int * chord_notes[N_CHORD] = {chord0_notes, chord1_notes, chord2_notes, chord3_notes, chord4_notes, chord5_notes, chord6_notes, chord7_notes, chord8_notes, chord9_notes, chord10_notes, chord11_notes};
char chord_name[N_CHORD] = {chord0_name, chord1_name, chord2_name, chord3_name, chord4_name, chord5_name, chord6_name, chord7_name, chord8_name, chord9_name, chord10_name, chord11_name};
int chord_N[N_CHORD] = {chord0_N, chord1_N, chord2_N, chord3_N, chord4_N, chord5_N, chord6_N, chord7_N, chord8_N, chord9_N, chord10_N, chord11_N};
String * chord_long_names[N_CHORD] = {&chord0_long_name, &chord1_long_name, &chord2_long_name, &chord3_long_name, &chord4_long_name, &chord5_long_name, &chord6_long_name, &chord7_long_name, &chord8_long_name, &chord9_long_name, &chord10_long_name, &chord11_long_name};



#endif
