// blink.h

#ifndef BLINK_H
#define BLINK_H


#include "DHT.h"

#define DHTPin 4
#define FlashRed 18
#define FlashGreen 19
#define FlashBlue 21
#define DHTTYPE DHT11

float temperature = 0;
unsigned long flashdelay = 0;
unsigned long updatedelay = 2500;
unsigned long datawritedelay = 20000;
unsigned long currentdatadelay = 0;
unsigned long currentdelay = 0;
unsigned long currentMillis = 0;
unsigned long ledtime = 0;
boolean ledstate = false;
String tempdata = "";

DHT dht(DHTPin, DHTTYPE);


void MySetup() {
  pinMode(FlashRed, OUTPUT);
  pinMode(FlashGreen, OUTPUT);
  pinMode(FlashBlue, OUTPUT);
  dht.begin();

  // initialise all the timers
  currentMillis = millis();
  currentdelay = currentMillis;
  currentdatadelay = currentMillis;
  ledtime = currentMillis;

}

void flashLed(int LedPin, unsigned long timeflash) {
  if (currentMillis - ledtime >= timeflash) {
    ledstate = !ledstate;
    digitalWrite(LedPin, ledstate);
    ledtime = currentMillis;
  }
}

void MyLoop() {
  currentMillis = millis();
  if (currentMillis - currentdelay >= updatedelay) {
    temperature = dht.readTemperature();
    currentdelay = currentMillis;
  }


  // Determine the appropriate LED and flash delay based on temperature
  if (temperature < 10) {
    flashdelay = map(temperature, 1, 10, 200, 1000);
    digitalWrite(FlashRed, LOW);
    digitalWrite(FlashGreen, LOW);
    flashLed(FlashBlue, flashdelay);
  } else if (temperature < 20) {
    flashdelay = map(temperature, 10, 20, 200, 1000);
    digitalWrite(FlashRed, LOW);
    digitalWrite(FlashBlue, LOW);
    flashLed(FlashGreen, flashdelay);
  } else {
    flashdelay = map(temperature, 20, 40, 200, 1000);
    digitalWrite(FlashGreen, LOW);
    digitalWrite(FlashBlue, LOW);
    flashLed(FlashRed, flashdelay);
  }

}

#endif
