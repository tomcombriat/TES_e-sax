# TES - e-sax

More infos: https://t-e-s.frama.site/en/tesaxophone

The E-sax is an EWI made out of a real sax. It outputs MIDI signals that can be used to generate sounds using a synthesizer for instance the [10k synth](https://github.com/tomcombriat/TES_10-knobs-synth). It is design to provide saxophone players a digital instrument to which they can transition easily. Additionnaly from the "standard" behavior it also have features that are allowed by a digital instrument:

- EWI mode which tries to give a more ergonomic keying (E mode)
- chords (C mode)
- arpegiators (A and R modes)


## What is in this repo?
The [hardware](hardware/) folder contains the kicad project for the PCB used in the e-sax alongside with the Cu and Fab masks. It is single sided in order to make its construction possible for an hobbyist. Note that the isolations and the routes are fairly small (around 200 microns) so you will need to have a fairly optimized setup to be able to make this PCB correctly.

The [software](software/) folder contains the embedded program that is embedded in the chip. Note that it will need some configurations for any particular saxophone.

The main MCU is a cheap BluePill STM32, programmed using the [Arduino STM32 library](https://github.com/stm32duino/Arduino_Core_STM32) and a FTDI.


## Making

### Bill of Materials 

- 24 resistors 1-10k, noted R on the PCB
- 1 resistor 33
- 2 resistors 22k (optionnal)
- 1 resistor 10
- 1 BluePill
- 1 FTDI chip to program the BluePill
- 3 74HC165 Parallel-to-Serial shift registers
- enough header
- 1 SSD1306 Oled screen (*I2C*)
- 1 MPX5010 differential pressure sensor
- 1 joystick with a click
- a good amount of flexible thin wire (around 26 AWG, silicon cover)
- Dupond cables
- a good amount of copper tape
- 1 3-AA battery holder
- 1 MIDI female to solder
- 1 switch (non-momentary)
- 2 pairs (male and female) of JST connectors 3 pins
- 1 pair of JST connectors 5 pins

### Wiring the 







