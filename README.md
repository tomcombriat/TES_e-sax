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
This gives some guidelines in order to allow people to make such an E-sax themselves. It precludes that the PCB is already printed and drilled.

Note: no 3D parts are included in this repo for now. Except for the beak, every part usually need to be redesigned for a different saxophone. Do not hesitate to contact me on that.


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
- 10 magnets (10x4x2mm^3) (optionnal)

### Wiring the saxophone

The controller needs to know what keys are pressed at any given time in order to be able to generate the correct MidiNote for a synthesizer. In order for the behavior to be as close as possible to a real saxophone, the sensors are positionned on the pads and not on the keys: if a key closing a pad is not pressed enough to close the pad the controller will consider it "open" just like it would be for a real saxophone. All the wires for the pads are going through the sax body.

The saxophone is a complex instrument and not every pad can be dismounted "alone": it is usual that some of them need other to be removed first in order to be dismounted.

#### Dismounting
This is why it is usually easier to dismount all the keys first and wire them on remounting.
Note: take some notes about which keys did you dismounted first: as the order matters they will need to be remounted in the _reverse order_. My personnal way of doing it is to write on every part a number and a letter (the latter only if this is a pad): the number denotes the order of dismounting (first dismounted part will be labelled "1", second "2"…) and the letter denotes the hole the pad is covering. I also write the same letter next to, or in, the hole which is covered by the pad. This way, upon remounting, one can start by the part with highest number, spot its hole (if any) and remount it.

#### Wiring the pads

The pads can be wired upon remounting. All pads need to be wired except the one which is just above the left hand forefinger which is not independant from the pad located under the left hand forefinger.

The sensor is composed of a thin copper layer glued to the pad and wire to the PCB. Using a push-up resistor, and by placing the whole sax body at GND the pad will behave as a switch:

- closed, the potential of the copper part will be at GND as it is in contact with the body
- open, the potential will be at 3.3V, thanks to a push-up resistor.

The copper tape needs to be glued to the pad:

- cut a piece of copper tape that matches more or less the dimension of the pad. The exact size of this piece is not critical but:
  - it need to cover some of the parts of the pad which are in contact with the body when closed. If possible at two different locations meaning that the length of this copper part should be at least be equal to the diameter of the hole covered by the pad.
  - it should not be too long either in order not to touch the metallic part of the key.
- apply a thin layer of neopren glue on the **tape** side of the copper, it should cover it all. Beware not to put some glue on the "clear" part of the copper
- apply a thin layer of neopren on the pad, it should match the dimensions of the piece of copper.
- wait from 10 to 15 minutes
- apply the copper, glue side of the tape facing the glue side of the pad, it should stick immediatly so the first attempt should be well positionned.
- using a soldering iron, add some solder at **the middle of the pad**, it should not touch the part where the pad touches the body.
- soldier a flexible wire long enough to go from the corresponding hole to the bell plus 5cm to it.
- put the wire in the hole and make it go to the bell throught the body (this can be hard for some keys) and tape it to the bell.
- remount the key on its hole.
- if done correctly, the key should action seemlessly and feel as natural as before.
- start again for all the other keys.






