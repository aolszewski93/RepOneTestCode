/*
Author: Albert Michael Olszewski
Company: RepOne
Date: 12/13/2019

This code is meant to be run with the spooling rig to spool the RepOne Sensor.
Firmware is to be sent to the Photon Particle microcontroller via WiFi connection.
The firmware waits for the user to press a button, and then it spools the device a predetermined amount of rotations.

*/

//
#include <AccelStepperSpark.h>

// Define a stepper and the pins it will use
AccelStepperSpark stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

int button = D0; //set pin for the button

int rev = 200; //set number of steps to spool (200 per revolution)

void setup()
{
    stepper.setMaxSpeed(200.0); // set speed
    stepper.setAcceleration(100.0); // set acceleration
    pinMode(button, INPUT); //define button pin as input to recieve data
}

void loop()
{
    int spoolNow = digitalRead(button); //check if button has been pushed
    if(spoolNow == 1) {
      stepper.runToNewPosition(rev); // move to next position
      rev = rev + 200; // increment position to prep for next spooling.
      // stepper.runToNewPosition(0);
    }


}
