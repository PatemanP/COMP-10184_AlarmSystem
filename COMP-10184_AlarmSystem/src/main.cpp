/**COMP 10184 Mohawk College
 * Alarm System
 * This version of the program has completed up to stage 4.
 * 
 * @author Philip Pateman
 * @id 000778803
 * 
 * I created this work and I have not shared it with anyone
 * 
*/
#include <Arduino.h>

void collectInputs();
void ledSequence();
void resetAlarm();

// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6

// The different states of the alarm system
#define ALARM_ACTIVE 1
#define ALARM_DISABLED 2
#define ALARM_BUZZER 3

//the current state the alarm is in
int iAlarmState;

void setup() {
  // put your setup code here, to run once:
  // configure the USB serial monitor 
  Serial.begin(115200); 
  analogWriteRange(1023);
 
  // configure the LED output 
  pinMode(LED_BUILTIN, OUTPUT); 
 
  // PIR sensor is an INPUT 
  pinMode(PIN_PIR, INPUT); 
 
  // Button is an INPUT 
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  iAlarmState = ALARM_ACTIVE;
}

void loop() {
  
  switch (iAlarmState)
  {
  case ALARM_ACTIVE:
    digitalWrite(LED_BUILTIN, HIGH);
    collectInputs();
    break;
  case ALARM_BUZZER:
    iAlarmState = ALARM_DISABLED;
    ledSequence();    
    break;
  default:    
    break;
  } 
  
}

/**
 * Checks to see if the motion senor sees any motion
*/
void collectInputs() {
  bool bPIR; 
  bPIR = digitalRead(PIN_PIR);  
  if(bPIR){
    iAlarmState = ALARM_BUZZER;
  }
}

/**
 * Does the LED flashing and checks to see if the button was pressed to reset the alarm
*/
void ledSequence(){
  int iButton; 
  
  for(int i = 0; i < 40; i++){
    if (iAlarmState == ALARM_ACTIVE){
      break;
    }
    for ( int j=1024; j>750; j--) { 
      // set the PWM pulse width 
      analogWrite(D4, j);
      iButton = digitalRead(D6);
      if(iButton == 0){
       resetAlarm();
       break;
      }
    }
  }
}

/**
 * Resets the alarm to active state and turns of the LED
*/
void resetAlarm(){
  iAlarmState = ALARM_ACTIVE;
  digitalWrite(LED_BUILTIN, HIGH);
}