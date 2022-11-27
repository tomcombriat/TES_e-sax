#ifndef _LEDstrand_
#define _LEDstrand_


/*
      Combriat 2018, 2019, 2020
      This file is part of the OS embedded in the e-sax - TES
      This code is under GPL3

      
      This is the include file for the class managing the lep strand (NeoPixel)
*/

#define NUM_LEDS 20

class LEDstrand
{
  public:
  LEDstrand();
  void splash();
  void update();


  private:
unsigned last_update = 0;
};




#endif
