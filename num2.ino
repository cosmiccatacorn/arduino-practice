#include<Servo.h>

Servo garageDoor;

#include <dht.h>
int tempLedPin = 2;
int t = 0;
dht DHT;

#define DHT11_PIN 

const int trigPin = 6;
const int echoPin = 7;
const int minDist = 10;
const int maxDist = 50;


const int rainPin = A0;
const int ledRainPin = 4;
int value = 0;


int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  garageDoor.attach(8);
  garageDoor.write(0);
  pinMode(ledRainPin, OUTPUT);
  pinMode(tempLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  DHT.read11(DHT11_PIN);
  t = DHT.temperature;
  Serial.print("Temperatura: ");
  Serial.print(t);
  if (t > 15) {
    digitalWrite(tempLedPin, true);
  } else {
    digitalWrite(tempLedPin, false);
  }
  value = analogRead(rainPin);
  Serial.println(value);
  delay(100);
  if (value < 950){
    digitalWrite(ledRainPin, true);   
  }  else {
    digitalWrite(ledRainPin, false);
  }
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(6, 7);
  Serial.print(cm);
  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
  
  if (cm > minDist && cm < maxDist){
    garageDoor.write(90);
    Serial.println("Puerta abierta");
    delay(1000);
    }
  else {
    garageDoor.write(0);
    Serial.println("Puerta cerrada");
    
  }
}
