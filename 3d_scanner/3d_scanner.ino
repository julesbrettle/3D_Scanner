#include <Servo.h>

// senseValance Sensor Setup
unsigned long senseVal = 0;

// Servo Setup
Servo panServo;  // create servo object to control the panning servo
Servo tiltServo;  // create servo object to control the tilting servo

int tiltPos = 0;    // variable to store the servo position
int panPos = 0;    // variable to store the servo position


int panMin = 10;
int panMax = 40;
int panStep = 1;
int tiltMin = 15;
int tiltMax = 50;
int tiltStep = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:
  tiltServo.attach(9);  // attaches the servo on pin 9 to the servo object
  panServo.attach(10);  // attaches the servo on pin 10 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (panPos = panMin; panPos <= panMax; panPos += panStep) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    panServo.write(panPos);              // tell servo to go to position in variable 'panPos'
    delay(500);                       // waits 0.5s for the servo to reach the position
    for (tiltPos = tiltMin; tiltPos <= tiltMax; tiltPos += tiltStep) { // goes from 180 degrees to 0 degrees
      tiltServo.write(tiltPos);              // tell servo to go to position in variable 'tiltPos'
      delay(50);                       // waits 50 ms for the servo to reach the position

      unsigned long senseVal = analogRead(A0); 
      Serial.print(tiltPos);    Serial.print(",");
      Serial.print(panPos);    Serial.print(",");
      Serial.println(senseVal);
      
    }

  }
  Serial.println(1); // send a short line to tell python that this scan is done
}
