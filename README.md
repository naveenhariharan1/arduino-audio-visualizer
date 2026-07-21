# Arduino Audio Visualizer / Music Visualiser 

## Intro
Arduino based audio/music visualiser that uses FastLED library.

## Materials
- Arduino Uno
- MAX4466 Microphone Module
- SM16703 addressable led strip(or any other addressable led strip)
- Momentary push button(eg:Elcom MS-1)
- External power supply to power the led strip 

## Code 
-[open](https://github.com/naveenhariharan1/arduino-audio-visualizer/blob/main/src/main.cpp) this on your arduino code editor.

## Connections
| Connection | Connected To |
|------------|--------------|
| LED Data | Arduino D6 → LED Strip DIN |
| Push Button | Arduino D2 |
| Audio Input | Arduino A0 |
| External Power (+5V) | Arduino 5V and LED Strip +5V |
| External Power (GND) | Arduino GND and LED Strip GND |
### circuit 


