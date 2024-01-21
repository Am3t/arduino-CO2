#include "SoftwareSerial.h"
SoftwareSerial T66_Serial(12,13); 
byte readCO2[] = {0xFF, 0XFE,2,2,3};

byte response[] = {0,0,0,0,0};

void setup()
{
 Serial.begin(19200);
 T66_Serial.begin(19200);
 Serial.println("    Interface for measuring CO2 levels");
 Serial.print("\n");
}

void loop()
{
 sendRequest(readCO2);
 
 unsigned long valCO2 = getValue(response);
 Serial.print("Sensor response:   ");
 for(int i=0;i<5;i++)
 {
  Serial.print(response[i],HEX);
  Serial.print(" ");
 }
 Serial.print("    Co2 ppm = ");
 Serial.println(valCO2);
delay(2000);
}

void sendRequest(byte packet[])
{
 while(!T66_Serial.available())
 {
 T66_Serial.write(readCO2,5);
 delay(50);
 delay(1000);
 }
 int timeout=0;
 while(T66_Serial.available() < 5 )
 {
 timeout++;
 if(timeout > 10)
 Serial.print("Timeout");
 {
 while(T66_Serial.available())
 T66_Serial.read();

 break; 
 }
 delay(50);
 }
  for (int i=0; i < 5; i++) response[i] = T66_Serial.read();
}

unsigned long getValue(byte packet[])
{
 int high = packet[3]; 
 int low = packet[4]; 
 unsigned long val = high*256 + low; 
 return val;
}
