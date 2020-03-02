#ifndef _chord_
#define _chord_



class chord
{
  public:
    chord();
    chord(unsigned int N, int * _notes);
    void  set_notes(unsigned int N, int * _notes);
    void apply(byte * note);

  private:
    int * notes;
    unsigned int N_notes;
};


unsigned int chord_N0 = 3;
int chord_notes0[3] = {0, 7, 12};

unsigned int chord_N1 = 4;
int chord_notes1[4] = {0, 7, 9, 12};

unsigned int chord_N2 = 4;
int chord_notes2[4] = {0, 7, 12, -12};




#endif
