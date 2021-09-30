#include <Servo.h>

// distance sensor setup
unsigned long senseVal = 0;

// servo setup
Servo panServo;  // create servo object to control the panning servo
Servo tiltServo;  // create servo object to control the tilting servo

int tiltPos = 0;    // variable to store the servo position
int panPos = 0;    // variable to store the servo position

// set parameters for pan and tilt behavior of the mechanism
// make sure these values match those in the 3d_scanner_jupyter.ipynb file
int panMin = 0;
int panMax = 50;
int panStep = 1;
int tiltMin = 0;
int tiltMax = 60;
int tiltStep = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // open the serial port at 9600 bps:
  tiltServo.attach(9);  // attaches the servo on pin 9 to the tilt servo object
  panServo.attach(10);  // attaches the servo on pin 10 to the pan servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (panPos = panMin; panPos <= panMax; panPos += panStep) {
    panServo.write(panPos);              // tell servo to go to position in variable 'panPos'
    delay(500);                       // waits 0.5s for the servo to reach the position
    
    for (tiltPos = tiltMin; tiltPos <= tiltMax; tiltPos += tiltStep) { // goes from 180 degrees to 0 degrees
      tiltServo.write(tiltPos);              // tell servo to go to position in variable 'tiltPos'
      delay(50);                       // waits 50 ms for the servo to reach the position

      unsigned long senseVal = analogRead(A0); // read the analog input from the distance sensor

      // print to the serial at the Arduino's COM port for the python program to read
      Serial.print(panPos);    Serial.print(",");
      Serial.print(tiltPos);    Serial.print(",");
      Serial.println(senseVal);
    }
  }
  
  Serial.println(1); // send a short line to tell the python program that this scan is done
}
