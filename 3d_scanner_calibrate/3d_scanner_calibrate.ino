#include <Servo.h>

// Distance Sensor Setup
unsigned long dist = 0;

// Servo Setup
Servo panServo;  // create servo object to control a servo
Servo tiltServo;  // create servo object to control a servo

int panPos = 90;    // variable to store the servo position
int tiltPos = 90;    // variable to store the servo position

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:
  panServo.attach(9);  // attaches the servo on pin 9 to the servo object
  tiltServo.attach(10);  // attaches the servo on pin 10 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:
  
      unsigned long dist = analogRead(A0); 
      Serial.println(dist);
      
}
