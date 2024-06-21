#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";     

int sensor_pin= 2;
boolean sensor_state = 0;


void setup() 
{
pinMode(sensor_pin, INPUT);
radio.begin();
                 
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MIN);  
radio.stopListening();  
}


void loop()
{
sensor_state = digitalRead(sensor_pin);
if(sensor_state == HIGH)
{
const char text[] = "Your Sensor see move!";
radio.write(&text, sizeof(text));                
}
else
{
const
  char text[] = "Nothing";
radio.write(&text, sizeof(text));
  
}
radio.write(&sensor_state, sizeof(sensor_state)); 
delay(1000);
}
