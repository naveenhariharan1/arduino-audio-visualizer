#include <FastLED.h>
#define ledPin 6
#define buttonPin 2
#define NUMofLEDS 64
CRGB leds[NUMofLEDS];// to create array with size of 64 to store the color data for each LED
int currentheight=0;
int previousheight=0;
int displayheight=0;
int currentbuttonstate=HIGH;
int previousbuttonstate=HIGH;
int mode=0;
unsigned long lastDebounceTime=0;
unsigned long debounceDelay=40;

float buttonstate(){
  unsigned long currentTime = millis();
  if(currentTime-lastDebounceTime>debounceDelay) {  // button debounce to prevent multiple presses being registered 
    lastDebounceTime=currentTime;                   //when the button is pressed once
    currentbuttonstate=digitalRead(buttonPin);
    if (currentbuttonstate==LOW && previousbuttonstate==HIGH){// rising edge detection
      mode++;
      if (mode>4){// to cycle through 5 modes
        mode=0;
     }  
    }
    if (mode==0){// to indicate mode 0 with led 13 on
      digitalWrite(13,HIGH);
    } 
    else{
      digitalWrite(13,LOW);
    }
    previousbuttonstate=currentbuttonstate;
  }
  return mode*0.25;// returns 0.0,0.25,0.5,0.75 and 1.0 depending on the mode
}
    
int audio_and_displayheight(float coef){
  int peak=0;
  int sum=0;
  for(int r=0;r<45;r++){// to find peak and avg over 45 interval
    int ar=analogRead(A0);// to read audio input from microphone
    int currentpeak=abs(ar-512);
    sum+=currentpeak;
    if (currentpeak>peak){
      peak=currentpeak;// to find the peak value over 45 interval
    }
  }
  int avg=sum/45;// to find the average value over 45 interval
  currentheight=min(((coef*peak)+(1-coef)*(avg))/8,63);// to blend peak and avg for different types of music based on coef
  if( currentheight<previousheight){
   displayheight=previousheight-1;// to make the display height fall by 1 led per loop
  }
  else if (previousheight<currentheight){   
    if (currentheight-previousheight>3){
    displayheight=min(previousheight+3,63);}// to make the display height rise by at most 3 leds per loop
    else{
      displayheight=currentheight;
    }
  }
  else {
   displayheight=currentheight;
  }
  previousheight=displayheight;
  return displayheight;
}

void display(int displayheight){
  for (int i=0;i<=displayheight;i++){
    leds[i]=CHSV(95-i*1.5,255,255);// creates a gradient from green to red based on the display height
  }                                 // also to create a gradient from cyan to red use 126-2*i 
  for (int i=displayheight+1;i<NUMofLEDS;i++){
    leds[i]=CRGB::Black;//to turn off the leds above the display height
  }
  FastLED.show();// display the leds based on the color data stored in the leds array
}
  
void setup() {
  FastLED.addLeds<SM16703,ledPin,GRB>(leds,NUMofLEDS).setCorrection(TypicalLEDStrip);// to ensure smoother colour blending 
  FastLED.setBrightness(128);                                                        //and more accurate color representation
  pinMode(A0,INPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(13,OUTPUT);
}

void loop() {
  float coef=buttonstate();
  displayheight=audio_and_displayheight(coef);
  display(displayheight);
}