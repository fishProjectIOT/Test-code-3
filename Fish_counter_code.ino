#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;



 
int ledPin = 7;                // choose the pin for the LED
int inputPin = 4;               // choose the input pin (for PIR sensor)
const int buttonPin = 6;        //Button Pin
const int TouchPin=5;           //Touch Sensor
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 8;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
int fishCounter = 0;
int quota =0; 
int buttonState = 0; 

char dtaUart[15];
char dtaLen = 0;


void setup() {
  
  digitalWrite(ledPin, HIGH);    // turn LED ON
  pinMode(ledPin,OUTPUT);
  pinMode(TouchPin, INPUT);     // declare sensor as input
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);

    //Startup message
    lcd.setRGB(0, 255, 0);
    lcd.setCursor(0, 0);
    lcd.print("Fish Counter v1");
    lcd.setCursor(0, 1);
    lcd.print("Initialising..");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    playTone(10, 40);
    lcd.print("Set Quota: ");
    lcd.setRGB(255, 255, 255);
    
}

void loop()
{
  int sensorValue = digitalRead(TouchPin);
  
      if(sensorValue==1)
    {
      lcd.setRGB(255, 255, 255);
      lcd.clear();
      digitalWrite(ledPin,HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Set Quota: ");
      quota++;
      delay(500);
      lcd.print(quota);
      digitalWrite(ledPin,HIGH);
       
    }

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    lcd.setRGB(255, 255, 255);
    lcd.clear();
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(300);
    digitalWrite(ledPin, LOW); //Turn Led OFF
    delay(300);
    digitalWrite(ledPin, HIGH);  // turn LED ON
    playTone(10, 40);
    delay(250);
    playTone(10, 100);
    lcd.setCursor(0, 0);
    lcd.print("Resetting");
    lcd.setCursor(0,1) ;
    lcd.print("Counter... ");
    delay(2500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Quota: ");
    fishCounter = 0;
    quota =0;



  }
  else {
          val = digitalRead(inputPin);  // read input value
         
            if (val == HIGH) 
            {            // check if the input is HIGH
              lcd.setRGB(255, 255, 255);
              lcd.clear();
              digitalWrite(ledPin, LOW); //Turn Led OFF
                playTone(10, 160);
                fishCounter ++;
                lcd.print("Count: ");
                lcd.print(fishCounter);
                lcd.setCursor(0, 1);
                lcd.print("Quota: ");
                lcd.print(quota);
                delay(2500);
                digitalWrite(ledPin, HIGH);  // turn LED ON
                
                if (fishCounter == quota)
                { 
                  lcd.clear();
                  playTone(500, 160);
                  digitalWrite(ledPin, LOW);
                  lcd.setCursor(0, 0);
                  lcd.print("Quota Reached!");
                  lcd.setRGB(255, 0, 0);
                  delay(500);
                  lcd.setRGB(255, 255, 255);
                  delay(500);
                  lcd.setRGB(255, 0, 0);
                  delay(500);
                  lcd.setRGB(255, 255, 255);
                  delay(500);
                  lcd.setRGB(255, 0, 0);
                  
                }
            }
    
  }
}


void playTone(long duration, int freq) 
{
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) 
    {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }    
}
