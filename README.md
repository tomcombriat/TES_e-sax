# TES - e-sax

More infos: https://t-e-s.frama.site/en/tesaxophone

The E-sax is an EWI made out of a real sax. It outputs MIDI signals that can be used to generate sounds using a synthesizer for instance the [10k synth](https://github.com/tomcombriat/TES_10-knobs-synth). It is design to provide saxophone players a digital instrument to which they can transition easily. Additionnaly from the "standard" behavior it also have features that are allowed by a digital instrument:

- EWI mode which tries to give a more ergonomic keying
- chords
- arpegiators…


## What is in this repo?
The [hardware](hardware/) folder contains the kicad project for the PCB used in the e-sax alongside with the Cu and Fab masks. It is single sided in order to make its construction possible for an hobbyist. Note that the isolations and the routes are fairly small (around 200 microns) so you will need to have a fairly optimized setup to be able to make this PCB correctly.

The [software](software/) folder contains the embedded program that is embedded in the chip. Note that it will need some configurations for any particular saxophone.

The main MCU is a cheap BluePill STM32, programmed using the [Arduino STM32 library](https://github.com/stm32duino/Arduino_Core_STM32).




