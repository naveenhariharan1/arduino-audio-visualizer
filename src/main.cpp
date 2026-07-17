#include <FastLED.h>
#define ledPin 6
#define buttonPin 2
#define NUMofLEDS 64
CRGB leds[NUMofLEDS];
int currentheight=0;
int previousheight=0;
int displayheight=0;
int currentbuttonstate=HIGH;
int previousbuttonstate=HIGH;
int mode=0;

float buttonstate(){
  currentbuttonstate=digitalRead(buttonPin);
  if (currentbuttonstate==LOW && previousbuttonstate==HIGH){
    mode++;
    if (mode>5){
      mode=0;
    }}
  if (mode==0){
  digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(13,LOW);
  }
    previousbuttonstate=currentbuttonstate;
    return mode*0.25;} 
    
int audio_and_displayheight(float coef){
  int peak=0;
  int sum=0;
  for(int r=0;r<60;r++){// peak and avg over 60 interval
    int ar=analogRead(A0);
    int currentpeak=abs(ar-512);
    sum+=currentpeak;
    if (currentpeak>peak){
      peak=currentpeak;
    }
  }
  int avg=sum/60;
  currentheight=((coef*peak)+(1-coef)*(avg))/8;
  if( currentheight<previousheight){
   displayheight=previousheight-(previousheight-currentheight)/5;
   }
  else if (previousheight<currentheight){
    displayheight=min(previousheight+(currentheight-previousheight)/3,64);
  }
  else {
   displayheight=currentheight;
  }
  previousheight=displayheight;
  return displayheight;
}

void display(int displayheight){
  for (int i=0;i<displayheight;i++){
    leds[i]=CHSV(95-i*1.5,255,255);
  }
  for (int i=displayheight;i<NUMofLEDS;i++){
    leds[i]=CRGB::Black;
  }
  FastLED.show();
}
  

void setup() {
  FastLED.addLeds<SM16703,ledPin,GRB>(leds,NUMofLEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(128);
  pinMode(A0,INPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(13,OUTPUT);
}

void loop() {
  float coef=buttonstate();
  displayheight=audio_and_displayheight(coef);
  display(displayheight);
}