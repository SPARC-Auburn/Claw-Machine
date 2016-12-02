#include <Servo.h>

Servo clawLeft;  // create servo object to control a servo 
Servo clawRight;  // create servo object to control a servo 
Servo spool;

int button1 = 4; //button pin, connect to ground to move servo
int press1 = 0;
 
int pos = 0; // variable to store the servo position 

void setup()
{
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);			//enable pullups to make pin high
  clawLeft.attach(6);				    // attaches the servo on pin 9 to the servo object 
  clawRight.attach(5);					// attaches the servo on pin 9 to the servo object 
  spool.attach(3);
  for (int i = 0; i<200; i++) 
  {
	openGrabber();
  }
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
    clawLeft.write(40);         // was 60
    clawRight.write(80);		// was 60
    delay(15); 
}
void openGrabber()
{
    clawLeft.write(100);
    clawRight.write(20);
    delay(15); 
}

void loop() 
{
// SET VARIABLES
  // VALUES
   int frequency = 6;
   int enable = 1;
   int direkshunX = 0;
   int direkshunY = 0;
  // PINS
  // pins (signals)
     int xStepPin = 10;
     int yStepPin = 11;
     int clawPin = 3;
     int heightPin = 5;
  // pins (states)
     int xDirPin = 6;
     int yDirPin = 7;
     int xEnablePin = 8;
     int yEnablePin = 9;
     int direkshunXPin = 10;
     int direkshunYPin = 11;
 

// BEGIN ROUTINE


// # ### Open The CLAW ### #
unsigned long startTime = millis();				// assign startTime comparison value
for(int i=0,10,i++)								// kill some time so stopTime=/=startTime
{
}		
unsigned long stopTime = millis();				// assign stopTime value
while((stopTime - startTime)<3000)				// while will run for 3 seconds
{
  openGrabber();								// open grabber
  stopTime = millis();							// new time comparison value
}

// # ### ### #
//
//
// # ### Drop THE CLAW ### #

startTime = millis();							// new time comparison value
while((stopTime-startTime)<5000)				// while runs for 5 seconds
{
  lowerSpool();									// lower the claw
  stopTime = millis();							// new time comparison value
}
stopSpool();									// stops moving the spool

// # ### ### #
//
//
// # ### Close The CLAW ### #

long grab = random(0,1);
long endTime = 0;
if (grab>0.75)
{
  startTime = millis();
  closeGrabberCompletely();
  while((stopTime-startTime<3500)
  {
   delay(500);
   stopTime = millis(); 
  }

  endTime = 3500;
}
else if
{
  startTime = millis();
  while((stopTime-startTime<1000)
  {
   closeGrabberPartially();
   stopTime = millis(); 
  }

  endTime = 1000;
}

// # ### ### #
//
//
// # ### Raise The CLAW ### #

startTime = millis();
while((stopTime-startTime)<5000)
{
  raiseSpool();
  stopTime = millis();
}
stopSpool();
// # ### ### #
//
//
// # ### Return X Axis ### #
while(analogRead(0)<500)
{
moov(255,12,10,8,1);
}


// # ### ### #
//
//
// # ### Return Y Axis ### #
while(analogRead(1)<500)
{
moov(255,13,11,9,0);
}


// # ### ### #
//
//
// # ### Open Claw ### #
startTime = millis();

while((stopTime - startTime)<endTime)
{
	openGrabber();
  stopTime = millis();
}

//# ### ### #
//
//
// # ### Close Claw ### #
startTime = millis();

while((stopTime - startTime)<5000)s
{
	closeGrabberCompletely();
  stopTime = millis();
}
analogWrite(clawPin, 0);




 
}
