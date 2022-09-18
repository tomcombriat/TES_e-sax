#include "LEDstrand.h"
#include "note_manager.h"

LEDstrand::LEDstrand(){};

void LEDstrand::update()
{
  if (millis() - last_update > STRAND_RESPONSE_TIME)
  {
    
    for (int i=0; i<NUM_LEDS;i++) strip.setPixelColor(i,strip.gamma32(strip.ColorHSV(manager.get_note()[0]<<10)));
    if (manager.get_note()[0] != 0) strip.setBrightness((byte) breath.MSB()<<1);
    else strip.setBrightness(0);
    strip.show();
    last_update = millis();
  }
}
