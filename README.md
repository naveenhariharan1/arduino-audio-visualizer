# Arduino Audio Visualizer / Music Visualiser 

## Intro
Arduino based audio/music visualiser that uses FastLED library and MAX4466 microphone module.

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
### circuit diagram
![alt text](https://github.com/naveenhariharan1/arduino-audio-visualizer/blob/main/images/circuit%20diagram.png 'circuit')

## How it Works

<p>Arduino constanly samples the analog signal from the microphone module through A0 and and finds peak amplitude and average over 45 cycles and changes the display height accordingly.It also has 5 modes by which you could change with the press of a button ,it would change the percentage of peak and average blending.</p>
1. Mode 0-100% average(indicated with led 13 ON)
2. Mode 1-75% average and 25% peak
3. Mode 2-50% average and 50% peak
4. Mode 3-25% average and 75% peak
5. Mode 4-100% peak

## Installation
1. Install the FastLED library.
2. Open `src/main.cpp` in the Arduino IDE.
3. Select the correct board and COM port.
4. Upload the code.

## Future Improvements

1.Auto gain control
2.Line level signal
3.Different visualisation modes
4.Music frequency analysis(FFT)


##
