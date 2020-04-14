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

  private:
    char chord_name;
    int * notes;
    unsigned int N_notes;
};


#define N_CHORD 3


unsigned int chord0_N = 3;
int chord0_notes[3] = {0, 7, 12};
char chord0_name = 'P';

unsigned int chord1_N = 4;
int chord1_notes[4] = {0, 7, 9, 12};
char chord1_name = '7';

unsigned int chord2_N = 4;
int chord2_notes[4] = {0, 7, 12, -12};
char chord2_name = 'B';



int * chord_notes[N_CHORD] = {chord0_notes, chord1_notes, chord2_notes};
char chord_name[N_CHORD] = {chord0_name, chord1_name, chord2_name};
int chord_N[N_CHORD] = {chord0_N, chord1_N, chord2_N};



#endif
