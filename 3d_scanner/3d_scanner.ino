#include <Servo.h>

// Distance Sensor Setup
unsigned long dist = 0;

// Servo Setup
Servo panServo;  // create servo object to control a servo
Servo tiltServo;  // create servo object to control a servo

int panPos = 0;    // variable to store the servo position
int tiltPos = 0;    // variable to store the servo position
int rotPos = 0;
int moveSpeedDir = 2;

//int tiltMin;
//int tiltMax;
//int tiltStep;
//int panMin;
//int panMax;
//int panStep;

int tiltMin = 0;
int tiltMax = 170;
int tiltStep = 10;
int panMin = 0;
int panMax = 170;
int panStep = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:
  panServo.attach(9);  // attaches the servo on pin 9 to the servo object
  tiltServo.attach(10);  // attaches the servo on pin 10 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:
  
//  Serial.println(0);
  for (tiltPos = tiltMin; tiltPos <= tiltMax; tiltPos += tiltStep) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    tiltServo.write(tiltPos);              // tell servo to go to position in variable 'tiltPos'
    delay(500);                       // waits 15 ms for the servo to reach the position
    for (panPos = panMin; panPos <= panMax; panPos += panStep) { // goes from 180 degrees to 0 degrees
      panServo.write(panPos);              // tell servo to go to position in variable 'panPos'
      delay(50);                       // waits 50 ms for the servo to reach the position

      unsigned long dist = analogRead(A0); 
      Serial.print(panPos);    Serial.print(",");
      Serial.print(tiltPos);    Serial.print(",");
      Serial.print(rotPos);    Serial.print(",");
      Serial.println(dist);
      
    }
    tiltPos += tiltStep;
    tiltServo.write(tiltPos);              // tell servo to go to position in variable 'tiltPos'
    delay(500); 
    for (panPos = panMax; panPos >= panMin; panPos -= panStep) { // goes from 180 degrees to 0 degrees
      panServo.write(panPos);              // tell servo to go to position in variable 'panPos'
      delay(50);                       // waits 50 ms for the servo to reach the position

      unsigned long dist = analogRead(A0); 
      Serial.print(panPos);    Serial.print(",");
      Serial.print(tiltPos);    Serial.print(",");
      Serial.print(rotPos);    Serial.print(",");
      Serial.println(dist);
      
    }

  }
  Serial.println(1);
}
