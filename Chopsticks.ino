/*
Chopstick Program
Code Made By: SacredAntwon

Tweaking:
-To change close ditance, modify the "trigerDistance" variable to
distance you prefer (in mm).
-To change the open and close angle, modify the "openAngle" and 
"closeAngle" variable to the angle you prefer (in Degrees).

Pin Setup:
VL53L0X Pin  Arduino Pin
VCC         5V
GND         GND
SDA         A4 or SDA if available
SCL         A5 or SCL if available
GPIO1       leave it unconnected
XSHUT       D12 (digital 12 or pin 12)

LED Pin      Arduino Pin
Green Pin   D2
Red Pin     D4
Ground Pin  GND

Servo Pin    Arduino Pin
Red Wire    5V
Black Wire  GND
Signal Wire D8
*/

#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>

VL53L0X sensor;

int redPin = 4;
int greenPin = 2;

Servo servo;
int openAngle = 0;
int closedAngle = 23;

int trigerDistance = 109;
void setup()
{
  servo.attach(8);
  
  pinMode(12,INPUT_PULLUP);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  Serial.print("TEST");
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Wire.begin();

  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, LOW);

  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  int distance =sensor.readRangeContinuousMillimeters();

  //Print out the info on a serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("mm");
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  if(distance <= trigerDistance)
  {
      servo.write(closedAngle);
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
  }
  
  else if(distance > trigerDistance)
  {
      servo.write(openAngle);
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
  }

  Serial.println();
  delay(100);
} 
