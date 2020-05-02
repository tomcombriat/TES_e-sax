#ifndef _chord_
#define _chord_



class chord
{
  public:
    chord();
    chord(unsigned int N, int * _notes);
    void  set_notes(unsigned int N, int * _notes);
    void  set_notes(unsigned int N, int * _notes, char _name);
    void apply(byte * note);
    char get_name();
    unsigned int get_N_notes();
    int * get_notes();

  private:
    char chord_name;
    int * notes;
    unsigned int N_notes;
};


#define N_CHORD 5


const unsigned int chord0_N = 3;
int chord0_notes[chord0_N] = {0, 7, 12};
char chord0_name = 'P';

const unsigned int chord1_N = 4;
int chord1_notes[chord1_N] = {0, 7, 9, 12};
char chord1_name = '7';

const unsigned int chord2_N = 4;
int chord2_notes[chord2_N] = {0, 7, 12, -12};
char chord2_name = 'B';

const unsigned int chord3_N = 3;
int chord3_notes[chord3_N] = {0, 3, 7};
char chord3_name = 'm';

const unsigned int chord4_N = 3;
int chord4_notes[chord4_N] = {0, 4, 7};
char chord4_name = 'M';


int * chord_notes[N_CHORD] = {chord0_notes, chord1_notes, chord2_notes, chord3_notes, chord4_notes};
char chord_name[N_CHORD] = {chord0_name, chord1_name, chord2_name, chord3_name, chord4_name};
int chord_N[N_CHORD] = {chord0_N, chord1_N, chord2_N, chord3_N, chord4_N};



#endif
