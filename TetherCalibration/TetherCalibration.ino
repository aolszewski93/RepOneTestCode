/*
 * Author: Albert Michael Olszewski
 * Company: RepOneStrength
 * Date: 02/06/2020
  Stepper Motor with Proximity Sensor for calibration of the RepOneStrength unit.
  The test fixture this code programs uses a NEMA 17 stepper motor from stepper online,
  a DM542T Digital Stepping Driver, a Twidec 10mm Proximity Sensor, and an Arduino Uno.
  This is the same test fixture used for life tests and drop tests. 

  The proximity sensor is pulled up to 5V via a 10k Resistor. 

  When the user runs this program, it should pull the tether of the RepOne Sensor up to
  the proximity sensor to designate a 0 position.  It will then run reps at consistent timing
  from the base of the unit to just below the proximity sensor. 

*/

// Include Dependencies
#include <AccelStepper.h>

int proxSensor = 2;  // Proximity Sensor pin
int driverPUL = 7;    // PUL- pin
int driverDIR = 6;    // DIR- pin
int switchPin = 4;    // input for the switch pin

int pd = 200;       // Pulse Delay period
boolean setdir = LOW; // Set Direction
int stepsPerRev = 800; // this is set on the digital stepper driver
int driverPosition = (stepsPerRev * 3.75) ; // set the number of steps the motor has to make to return to RepOne sensor.

// Define Objects
AccelStepper stepper(1,7,6);


// create a function to initialize zero position of the motor
void setZero(int i = 0){
  while(i<1){
    int val = digitalRead(proxSensor); //read the proximitiy sensor

    if(val !=1){
      stepper.setCurrentPosition(0); // set current position as 0
      Serial.println("Zero Position Set...");
      i++;
    }

    // set the direction of the motor and git the driver a pulse.
    digitalWrite(driverPUL,HIGH);
    delayMicroseconds(pd*4);
    digitalWrite(driverPUL,LOW);
    delayMicroseconds(pd*4);
  }
}

//create a function to have system wait for user to begin next step
void userCheck(){
  int j = 0;
  Serial.println("Waiting for user check.");
  while(j == 0){
    
    j = digitalRead(switchPin);
  }
  Serial.println(j);
  delay(200);

}

//create a function that runs calibration repetitions
void calibrate(int numReps, int i = 0){
  Serial.println("Running Calibration: ");
  while(i < numReps){
    stepper.runToNewPosition(driverPosition); //move tether to base
    delay(100);
    stepper.runToNewPosition(45); //move tether to just below the proximity sensor
    delay(100);
    i++;
    Serial.print(i);
  }
  Serial.println("");
  Serial.println("Done Calibrating...");
}

void setup() {
  Serial.begin(9600); // set up serial object to print to a monitor
  pinMode(proxSensor, INPUT); // set the proximity sensor as an input
  pinMode (driverPUL, OUTPUT); // pulse pin as output
  pinMode (driverDIR, OUTPUT); // direction pin as output
  pinMode(switchPin, INPUT); // sets switch pin as input

  stepper.setMaxSpeed(4000);
  stepper.setAcceleration(4000);
  
}

void loop() {
  Serial.println("Initializing Calibration Reps...");
  setZero();
  userCheck();
  calibrate(20);
  userCheck();
  
  
}
