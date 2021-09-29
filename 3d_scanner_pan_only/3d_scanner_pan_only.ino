#include <Servo.h>

// senseValance Sensor Setup
unsigned long senseVal = 0;

// Servo Setup
Servo panServo;  // create servo object to control a servo
Servo tiltServo;

int panPos = 0;    // variable to store the servo position
int tiltPos = 43;

int panMin = 0;
int panMax = 70;
int panStep = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:
  panServo.attach(10);  // attaches the servo on pin 10 to the servo object
  tiltServo.attach(9);  // attaches the servo on pin 9 to the servo object


}

void loop() {
  // put your main code here, to run repeatedly:
  tiltServo.write(tiltPos);
  
//  Serial.println(0);
  for (panPos = panMin; panPos <= panMax; panPos += panStep) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    panServo.write(panPos);              // tell servo to go to position in variable 'panPos'
    delay(500);                       // waits 15 ms for the servo to reach the position
    
    unsigned long senseVal = analogRead(A0); 
    Serial.print(panPos);    Serial.print(",");
    Serial.print(tiltPos);    Serial.print(",");
    Serial.println(senseVal);
      
    panPos += panStep;

  }
  Serial.println(1);
}
