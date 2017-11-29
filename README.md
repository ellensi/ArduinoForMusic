# ArduinoForMusic

## Improviser-Theremin
Use an ultrasound sensor to make music that can be heard from a little buzzer. There are two modes: *Improviser* mode and *Theremin* mode. In order to switch the modes, simply detach and re-attach the buzzer to pins 2-4 for Improviser or pins 5-7 for Theremin.

What you'll need:
* Arduino Uno
* HC-SR04 ultrasound sensor
* Three-legged 8 ohm buzzer
* Jumper wires and a mini-USB cable connection to the computer
* [`Tone.h`](https://github.com/bhagman/Tone) Arduino library

Modes:
1. ***Improviser mode* (buzzer at pins 2-4):** Put your hand in front of the sensor and it will generate a low-pitched diatonic melody. Move your hand slowly away from the sensor, and the melody will go up in pitch. Each note will take 200 milliseconds (5 notes per second).

2. ***Theremin mode* (buzzer at pins 5-7):** Have the sensor face a wall at the distance of 50–100 cm, and it will generate a steady pitch. Get it closer to the wall and the pitch will increase. Get it further away from the wall and the pitch will decrease.

## BowSaber 2.0
Control a WS2812B LED strip so that it flashes rainbow color (better than a lightsaber) and blinks when a tilt sensor receives a fast physical movement.

What you'll need:
* Arduino Nano
* WS2812B LED strip (individually-addressable and programmable)
* Three-legged tilt sensor
* Jumper wires and a micro-USB cable connection to the computer
* [`FastLED.h`](https://github.com/FastLED/FastLED) Arduino library
