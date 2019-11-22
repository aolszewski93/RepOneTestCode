/*
  Stepper Motor with Proximity Sensor for durability tests on the RepOne Strength unit.
  The test fixture this code programs uses a NEMA 17 stepper motor from stepper online,
  a DM542T Digital Stepping Driver, a Twidec 10mm Proximity Sensor, and an Arduino Uno. 

  The proximity sensor is pulled up to 5V via a 10k Resistor. 

  When the user runs this program, it should pull the tether of the RepOne Sensor around 7ft, 
  release the tether, and then retrieve it. 
*/
 
// Define pins
 
int proxSensor = 2;  // Proximity Sensor pin
int driverPUL = 7;    // PUL- pin
int driverDIR = 6;    // DIR- pin
 
// Variables
 
int pd = 500;       // Pulse Delay period
boolean setdir = LOW; // Set Direction
int driverPosition = 3500; // set the number of steps the motor has to make to return to RepOne sensor. 
 
 
void setup() {
  Serial.begin(9600); // set up serial object to print to a monitor
  pinMode(proxSensor, INPUT); // set the proximity sensor as an input
  pinMode (driverPUL, OUTPUT); // pulse pin as output
  pinMode (driverDIR, OUTPUT); // direction pin as output
  
}
 
void loop() {

  // read the proximity sensor
  int val = digitalRead(proxSensor); 
  Serial.println(val);

  // check if the proximity sensor is triggered.
  if(val != 1){
    
    Serial.println("Return to Base.");  //print what program is doing

    // run a for loop that steps the motor to where the module being tested is.
    for(int steps = 0; steps < 3500; steps++){
      digitalWrite(driverDIR,!setdir); //change direction of the motor
      digitalWrite(driverPUL,HIGH);
      delayMicroseconds(pd);
      digitalWrite(driverPUL,LOW);
      delayMicroseconds(pd);
    }
    
  }
  else{
    Serial.println("Keep Pulling!"); //print what program is doing
  }
      // set the direction of the motor and git the driver a pulse.
      digitalWrite(driverDIR,setdir);
      digitalWrite(driverPUL,HIGH);
      delayMicroseconds(pd);
      digitalWrite(driverPUL,LOW);
      delayMicroseconds(pd);
    // if sensor is 0 have it return to initial value. 
 
}
