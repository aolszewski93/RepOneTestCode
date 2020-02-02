/*
 * Author: Albert Michael Olszewski
 * Company: RepOne
 * Date: 01/26/2020
  Stepper Motor with Proximity Sensor for durability tests on the RepOne Strength unit.
  The test fixture this code programs uses a NEMA 17 stepper motor from stepper online,
  a DM542T Digital Stepping Driver, a Twidec 10mm Proximity Sensor, and an Arduino Uno. 

  The proximity sensor is pulled up to 5V via a 10k Resistor. 

  When the user runs this program, it should pull the tether of the RepOne Sensor around 7ft, 
  release the tether, and then retrieve it. 

*/

// Include Dependencies
#include <AccelStepper.h>

 
// Define pins
 
int proxSensor = 2;  // Proximity Sensor pin
int driverPUL = 7;    // PUL- pin
int driverDIR = 6;    // DIR- pin
int switchPin = 4;    // input for the switch pin
int slidePin = 10;   // input for the slide switch that selects what type of program we run
 
// Variables

unsigned long lastTrigger;
unsigned long timeBetween;
int pd = 200;       // Pulse Delay period
boolean setdir = LOW; // Set Direction
int stepsPerRev = 800; // this is set on the digital stepper driver
int driverPosition = (stepsPerRev * 4) ; // set the number of steps the motor has to make to return to RepOne sensor.
int lifePosition = (stepsPerRev * 3.45) ; // set distance to return to life testing 
// 
// Define Objects
AccelStepper stepper(1,7,6);
 

void tetherFishing(int numReps, int i = 0){
  
  while(i < numReps){
    // read the proximity sensor
    int val = digitalRead(proxSensor); 
    //Serial.println(val);
  
    // check if the proximity sensor is triggered.
    if(val != 1){
      i++;
      Serial.println("Return to Base.");  //print what program is doing
      Serial.print("Cycle: "); 
      Serial.println(i);
      delay(500);
      // run a for loop that steps the motor to where the module being tested is.
      for(int steps = 0; steps < driverPosition; steps++){
        digitalWrite(driverDIR,!setdir); //change direction of the motor
        digitalWrite(driverPUL,HIGH);
        delayMicroseconds(pd);
        digitalWrite(driverPUL,LOW);
        delayMicroseconds(pd);
      }
      
  //    delay(100000000);
    }
    else{
  //    Serial.println("Keep Pulling!"); //print what program is doing
    }
        // set the direction of the motor and git the driver a pulse.
        digitalWrite(driverDIR,setdir);
        digitalWrite(driverPUL,HIGH);
        delayMicroseconds(pd);
        digitalWrite(driverPUL,LOW);
        delayMicroseconds(pd);
      // if sensor is 0 have it return to initial value. 
  }
  
}


void lifeTestingAccelStep(int numReps, int i = 0){
    
    lastTrigger = millis(); //set an initial value for last trigger
    
    while(i < numReps){
    // read the proximity sensor
    int val = digitalRead(proxSensor); 

    timeBetween = millis() - lastTrigger;
    // check time since last trigger
    if(timeBetween > 6000){
        Serial.println("Motor Jam Interrupt");
        userCheck();
        lastTrigger = millis(); //reset last trigger
      }
      
    // check if the proximity sensor is triggered.
    if(val != 1){
      lastTrigger = millis(); // set variable to log when the proximity sensor was triggered
      i++;
      stepper.setCurrentPosition(0); // set current position as 0
      Serial.println("Return to Base.");  //print what program is doing
      Serial.print("Cycle: "); 
      Serial.println(i);
      delay(100);
      stepper.runToNewPosition(lifePosition);  //move stepper to the base
      delay(100);
      stepper.runToNewPosition(30); // move close to the proximity sensor
      digitalWrite(driverDIR,setdir); // set the direction of the stepper to pull up
    }
      // set the direction of the motor and git the driver a pulse.
      digitalWrite(driverPUL,HIGH);
      delayMicroseconds(pd*4);
      digitalWrite(driverPUL,LOW);
      delayMicroseconds(pd*4);
      // if sensor is 0 have it return to initial value. 
  }
  
}

void lifeTesting(int numReps, int i = 0){
  
  while(i < numReps){
    // read the proximity sensor
    int val = digitalRead(proxSensor); 
  
    // check if the proximity sensor is triggered.
    if(val != 1){
      i++;
      Serial.println("Return to Base.");  //print what program is doing
      Serial.print("Cycle: "); 
      Serial.println(i);
      delay(500);
      // run a for loop that steps the motor to where the module being tested is.
      for(int steps = 0; steps < lifePosition; steps++){
        digitalWrite(driverDIR,!setdir); //change direction of the motor
        digitalWrite(driverPUL,HIGH);
        delayMicroseconds(pd);
        digitalWrite(driverPUL,LOW);
        delayMicroseconds(pd);
      }
      delay(500);
    }
        // set the direction of the motor and git the driver a pulse.
        digitalWrite(driverDIR,setdir);
        digitalWrite(driverPUL,HIGH);
        delayMicroseconds(pd);
        digitalWrite(driverPUL,LOW);
        delayMicroseconds(pd);
        
      // if sensor is 0 have it return to initial value. 
  }
  
}

void userCheck(){
  int j = 0;
  Serial.println("Waiting for user check.");
  while(j == 0){
    
    j = digitalRead(switchPin);
  }
  Serial.println(j);
  delay(200);

}



void setup() {
  Serial.begin(9600); // set up serial object to print to a monitor
  Serial.println("The motor will make: ");
  Serial.print(driverPosition);
  pinMode(proxSensor, INPUT); // set the proximity sensor as an input
  pinMode (driverPUL, OUTPUT); // pulse pin as output
  pinMode (driverDIR, OUTPUT); // direction pin as output
  pinMode(switchPin, INPUT); // sets switch pin as input
  pinMode(slidePin, INPUT); // set slide pin as input


  stepper.setMaxSpeed(4000);
  stepper.setAcceleration(4000);
  
  
}
 
void loop() {
  int prog = digitalRead(slidePin); // reads status of the switch

  //if switch returns 1 run drop test else run lift test
  if(prog == 1){
    // run drop test with user checks at 10, 50, 200, and 500 reps
    Serial.println("Running Drop Test");
    tetherFishing(1); //run 1 test rep
    userCheck();
    tetherFishing(2); //run 2 test rep
    userCheck();
//    tetherFishing(10);
//    userCheck();
//    tetherFishing(50);
//    userCheck();
//    tetherFishing(200);
//    userCheck();
//    tetherFishing(500);
    delay(500);
  }
  else{
    // run life testing with checks after 1000, 20000, 100000, and 300000 reps
    Serial.println("Running Life Test");
    lifeTestingAccelStep(2);
    userCheck();
    lifeTestingAccelStep(1000);
    userCheck();
    lifeTestingAccelStep(20000);
    userCheck();
    lifeTestingAccelStep(100000);
    userCheck();
    lifeTestingAccelStep(300000);
    Serial.println("Done with Life Test");
    userCheck();

  }
  

  
  
}
