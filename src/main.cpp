#include <FastLED.h>
#define ledPin 6
#define buttonPin 2
#define NUMofLEDS 64
CRGB leds[NUMofLEDS];
int currentheight=0;
int previousheight=0;
int currentbuttonstate=HIGH;
int previousbuttonstate=HIGH;
int mode=0;

float buttonstate(){
  currentbuttonstate=digitalRead(buttonPin);
  if (currentbuttonstate==LOW && previousbuttonstate==HIGH){
    mode++;
    if (mode>10){
      mode=0;
    }}
  if (mode==0){
  digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(13,LOW);
  }
    previousbuttonstate=currentbuttonstate;
    return mode/10.0;}  

void setup() {
  FastLED.addLeds<SM16703,ledPin,GRB>(leds,NUMofLEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(128);
  pinMode(A0,INPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(13,OUTPUT);
}

void loop() {// peak over 15interval
  int peak=0;
  int sum=0;
  float coef=buttonstate();
  for(int r=0;r<60;r++){
    int ar=analogRead(A0);
    int currentpeak=abs(ar-512);
    sum+=currentpeak;
    if (currentpeak>peak){
      peak=currentpeak;
    }
  }
  currentheight=((coef*peak)+(1-coef)*(sum/60))/8;
  if( currentheight<previousheight){
   previousheight=previousheight-1;
   }
  else if (previousheight<currentheight){
    previousheight=previousheight+2;
  }
  else {
   previousheight=currentheight;
  }
  for (int i=0;i<=previousheight;i++){
    leds[i]=CHSV(96-i*1.5,255,255);
  }
  for (int i=previousheight+1;i<NUMofLEDS;i++){
    leds[i]=CRGB::Black;
  }
  FastLED.show();
}