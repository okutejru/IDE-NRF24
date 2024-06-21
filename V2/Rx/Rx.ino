#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

boolean sensor_state = 0;
int  buzzer_pin = 3; //3,5,6 pin


void setup() 
{
pinMode(buzzer_pin, OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0,  address); 
radio.setPALevel(RF24_PA_MIN);       
radio.startListening();              
}



void  loop()
{
if (radio.available())            
{
char text[32] = "";                 
radio.read(&text, sizeof(text)); 
radio.read(&sensor_state,  sizeof(sensor_state));   
if(sensor_state == HIGH)
{
tone(buzzer_pin, 400);
Serial.println(text);
}
else
{
noTone(buzzer_pin);
Serial.println(text);}
}
delay(5);
}
