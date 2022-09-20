#include "LEDstrand.h"
#include "note_manager.h"

LEDstrand::LEDstrand(){};

void LEDstrand::update()
{
  if (millis() - last_update > STRAND_RESPONSE_TIME)
  {
    int32_t color = strip.gamma32(strip.ColorHSV(((manager.get_note()[0])<<10) + ((PB.get_value()*pitchbend_amp_CC.get_value())>>3)));
    for (int i=0; i<NUM_LEDS;i++) strip.setPixelColor(i,color);
    if (manager.get_note()[0] != 0) strip.setBrightness((byte) breath.MSB()<<1);
    else strip.setBrightness(0);
    strip.show();
    last_update = millis();
  }
}

void LEDstrand::splash()
{
    //strip.setBrightness(255);
  strip.rainbow(0, 1);

  for (int i=255;i>0; i--)
  {
    strip.setBrightness(strip.gamma8(i));
      strip.show();
      delay(3);

  }
}
