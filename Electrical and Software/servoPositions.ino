/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo clawLeft;  // create servo object to control a servo 
Servo clawRight;  // create servo object to control a servo 
Servo spool;

int button1 = 4; //button pin, connect to ground to move servo
int press1 = 0;
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH); //enable pullups to make pin high
  clawLeft.attach(6);  // attaches the servo on pin 9 to the servo object 
  clawRight.attach(5);  // attaches the servo on pin 9 to the servo object 
  spool.attach(3);
  for (int i = 0; i<200; i++) {
     openGrabber();
  }
} 
 
void loop() 
{ 

  raiseSpool();
  delay(2800);
  stopSpool();
  delay(4000);
  for (int i = 0; i<100; i++) {
     openGrabber();
  }
  lowerSpool();
  delay(1800);
  stopSpool();
  for (int i = 0; i<100; i++) {
     closeGrabberPartially();
  }
  delay(2000);
//  openGrabber();
//  delay(1000);
//  closeGrabberPartially();
//  delay(2000);
} 

void lowerSpool()
{
    spool.write(40);
    delay(15);  
}

void stopSpool()
{
    spool.write(97);
    delay(15);  
}

void raiseSpool()
{
    spool.write(180);
    delay(15); 
}
void closeGrabberCompletely()
{
    clawLeft.write(40);
    clawRight.write(80);
    delay(15); 
}
void closeGrabberPartially()
{
    clawLeft.write(60);
    clawRight.write(60);
    delay(15); 
}
void openGrabber()
{
    clawLeft.write(100);
    clawRight.write(20);
    delay(15); 
}
