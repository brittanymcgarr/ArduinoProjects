//////////////////////////////////////////////////////////////////
// LaunchPad v1.1                                               //
// Program for managing input and actuator positions for tilted //
// launch pad for the Reno Air Races Demo. Preloaded keystrokes //
// for automatic positioning macros.                            //
//                                                              //
// Instructions:                                                //
// Upload to Arduino and configure actuator or servo. Launch in //
// PuTTY or Arduino serial monitor. Send commands by single     //
// character keystroke and wait for actuators to move into      //
// position. For safety, do not configure macros for positions  //
// above 99% or below 1%.                                       //
// 'w' = North actuator increment/decrement 10%                 //
// 's' = South actuator increment/decrement 10%                 //
// 'd' = East actuator increment/decrement 10%                  //
// 'a' = West actuator increment/decrement 10%                  //
// 't' = test servo increment/decrement 10*                     //
// '-' = turn on decreasing direction                           //
// '=' = turn off decreasing direciton                          //
// '0' '1' '2' '9' = macro functions                            //
//                                                              //
// Brittany McGarr                                              //
// September 9, 2015                                            //
//////////////////////////////////////////////////////////////////


#include <Servo.h>

// Global Variables
// Servo/Actuator values for the corners of the platform
Servo NORTH;
Servo SOUTH;
Servo EAST;
Servo WEST;
Servo TEST;

// Servo/Actuator position values
int northPos = 1;
int southPos = 1;
int eastPos = 1;
int westPos = 1;
int testPos = 1;

// Key reading load and store values
int keyPressed = 0;
int reverse = 0;
const int STEP = 10;
const int DELAY = 1000; // wait time for positioning

// Initializing function for servo/actuators
void setup() {
    NORTH.attach(5);
    SOUTH.attach(6);
    EAST.attach(10);
    WEST.attach(11); 
    TEST.attach(9);
    
    // Setup serial IO from keyboard
    Serial.begin(9600);
    
    // Initialize stroke to 50% on all
    keyPressed = 119;
    northPos = 50;
    moveStrokePercentage(50);
    
    keyPressed = 115;
    southPos = 50;
    moveStrokePercentage(50);
    
    keyPressed = 100;
    eastPos = 50;
    moveStrokePercentage(50);
    
    keyPressed = 97;
    westPos = 50;
    moveStrokePercentage(50);
    
    keyPressed = 0;
}

// Function Declarations
// Actuator Stroke by percentage
void moveStrokePercentage(float strokePercentage) {
    // Check for values between 1-99% (giving 1% buffer on each to prevent stripping
    if(strokePercentage >= 1.0 && strokePercentage <= 99.0) {
        int usec = 1000 + strokePercentage * (2000 - 1000) / 100.0;
        // Switch motor based on key press record
        switch(keyPressed) {
             case 119: // 119 => 'w'
                 NORTH.writeMicroseconds(usec);
                 keyPressed = 0;
                 delay(DELAY);
                 break;
             case 115: // 115 => 's'
                 SOUTH.writeMicroseconds(usec);
                 keyPressed = 0;
                 delay(DELAY);
                 break;
             case 100: // 100 => 'd'
                 EAST.writeMicroseconds(usec);
                 keyPressed = 0;
                 delay(DELAY);
                 break;
             case 97: // 97 => 'a'
                 WEST.writeMicroseconds(usec);
                 keyPressed = 0;
                 delay(DELAY);
                 break;
             default:
                 keyPressed = 0;
                 break;
        }
    } 
}

// Actuator Stroke by millimeter
void moveStrokeMillimeter(int strokeLength, int strokeMax) {
    // Gathers stroke length and sends as percentage for movement
    if(strokeLength < strokeMax) {
        moveStrokePercentage((float)strokeLength / strokeMax);
    } 
}

// Preset function 0: Neutral position
void preset0() {
    keyPressed = 119;
    moveStrokePercentage(50.0);
    northPos = 50;
    keyPressed = 115;
    moveStrokePercentage(50.0);
    southPos = 50;
    keyPressed = 97;
    moveStrokePercentage(50.0);
    eastPos = 50;
    keyPressed = 100;
    moveStrokePercentage(50.0);
    westPos = 50; 
}

// Preset function 1: North tilt upmost, South down
void preset1() {
    keyPressed = 119;
    moveStrokePercentage(90.0);
    northPos = 90;
    keyPressed = 115;
    moveStrokePercentage(15.0);
    southPos = 15;
    keyPressed = 97;
    moveStrokePercentage(50.0);
    eastPos = 50;
    keyPressed = 100;
    moveStrokePercentage(50.0);
    westPos = 50;
}

// Preset function 2: South tilt upmost, North down
void preset2() {
    keyPressed = 115;
    moveStrokePercentage(90.0);
    southPos = 90;
    keyPressed = 119;
    moveStrokePercentage(15.0); 
    northPos = 15;
    keyPressed = 97;
    moveStrokePercentage(50.0);
    eastPos = 50;
    keyPressed = 100;
    moveStrokePercentage(50.0);
    westPos = 50;
    northPos = 90;
    keyPressed = 115;
    moveStrokePercentage(15.0);
}

// Preset Test: Manipulate Servo to 180
void preset9() {
    TEST.write(180);
    keyPressed = 0; 
}

// Main Loop
void loop() {
    // Response based on serial IO command
    if(Serial.available() > 0) {
         keyPressed = Serial.read();
         
         // Handle key press action and manage positions
         switch(keyPressed) {
             case 119:
                 // Check for reverse direction value or over
                 // safe buffer zone and increment/decrement 10%
                 if(reverse || northPos > 95) {
                     northPos -= STEP;
                     if(northPos < 1) {
                         northPos = 1; 
                     }
                 } else {
                     northPos += STEP;
                 }
                 moveStrokePercentage(northPos);
                 break;
             case 115:
                 if(reverse || southPos > 95) {
                     southPos -= STEP;
                     if(southPos < 1) {
                         southPos = 1; 
                     }
                 } else {
                     southPos += STEP;
                 }
                 moveStrokePercentage(southPos);
                 break;
             case 100:
                 if(reverse || eastPos > 95) {
                     eastPos -= STEP;
                     if(eastPos < 1) {
                         eastPos = 1; 
                     }
                 } else {
                     eastPos += STEP;
                 }
                 moveStrokePercentage(eastPos);
                 break;
             case 97:
                 if(reverse || westPos > 95) {
                     westPos -= STEP;
                     if(westPos < 1) {
                         westPos = 1; 
                     }
                 } else {
                     westPos += STEP;
                 }
                 moveStrokePercentage(westPos);
                 break;
             case 116: // Test case => 't' Servo
                 if(reverse || testPos > 350) {
                     testPos -= STEP; 
                     if(testPos < 10) {
                         testPos = 10; 
                     }
                 } else {
                     testPos += STEP; 
                 }
                 TEST.write(testPos);
                 keyPressed = 0;
                 break;
             case 45: // Reverse direction => '-'
                 reverse = 1;
                 keyPressed = 0;
                 break;
             case 61: // Undo Reverse direction => '='
                 reverse = 0;
                 keyPressed = 0;
                 break;
             case 48: // 48 => '0'
                 preset0();
                 break;
             case 49: // 49 => '1'
                 preset1();
                 break;
             case 50: // 50 => '2'
                 preset2();
                 break;
             case 57: // 57 => '9'
                 preset9();
                 break;
             default:
                 keyPressed = 0;
                 break;
         }
    }
}
