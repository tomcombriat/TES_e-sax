#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include <TES_Button.h>
#include "config.h"

/*
TODO:
 - midi
*/




Adafruit_SSD1306 display(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS);
TES_Button joyButton(JOY_BUTTON_PIN, false, JOY_RESPONSE_TIME);

void setup() {
  // Simple things
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //analogReadResolution(12);

  // SPI
  SPI.setRX(SPI_RX);  // or setMISO()
  SPI.setSCK(SPI_CLK);
  SPI.setTX(SPI_TX);  // or setMOSI()

  // SPI1
  SPI1.setRX(SPI1_RX);  // or setMISO()
  SPI1.setSCK(SPI1_CLK);
  SPI1.setTX(SPI1_TX);  // or setMOSI()

  // Screen
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setCursor(30, 15);
  display.setTextColor(1, 0);
  display.setTextSize(4);
  display.print("TES");
  display.setCursor(35, 50);
  display.setTextSize(2);
  display.print("e-Sax");
  display.display();


  // Joystick
  pinMode(JOYX_PIN, INPUT);
  pinMode(JOYY_PIN, INPUT);
  pinMode(SR_LOAD_PIN, OUTPUT);


  // Shiht reg
  SPI1.begin();
  SPI1.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));





  Serial.begin(115200);
}

void loop() {
  // JOY Test
  Serial.print(analogRead(JOYX_PIN));
  Serial.print(" ");
  Serial.print(analogRead(JOYY_PIN));
  Serial.println();

  joyButton.update();
  if (joyButton.is_pressed()) Serial.println("Pressed!");


  //Shift registers
  digitalWrite(SR_LOAD_PIN, LOW);
  digitalWrite(SR_LOAD_PIN, HIGH);
  uint32_t srRes = 0;
  for (byte i = 0; i < N_SHIFT_REG; i++) srRes += SPI1.transfer(0) << (8 * i);
  Serial.print("    ");
  Serial.println(srRes, BIN);

  delay(100);
}
