#include <Servo.h>

Servo clawLeft;  // create servo object to control a servo 
Servo clawRight;  // create servo object to control a servo 
Servo spool;


void setup()
{
 // pinMode(button1, INPUT);
 // digitalWrite(button1, HIGH);      //enable pullups to make pin high
 pinMode(A0, INPUT);
 digitalWrite(A0, LOW);
 for(int x = 2;x<13;x++)
 {
  pinMode(x, OUTPUT);
 }
  clawLeft.attach(6);           // attaches the servo on pin 9 to the servo object 
  clawRight.attach(5);          // attaches the servo on pin 9 to the servo object 
  spool.attach(3);
  Serial.begin(9600);
  Serial.println("Begin Game");

}

 
int pos = 0; // variable to store the servo position 

void dir(int sign, int axis) {
  switch (sign) {
    case '0':
      switch (axis) {
        case 8:
          digitalWrite(axis, HIGH);
          break;
        case 9:
          digitalWrite(axis, LOW);
          break;
      }
      break;
    case '1':
      switch (axis) {
        case 8:
          digitalWrite(axis, LOW);
          break;
        case 9:
          digitalWrite(axis, HIGH);
          break;
      }
      break;
  }
  delay(1);
}

void moov(int input, int aEN, int aST, int aDI, int sign) { //mispelled move on purpose because move is an reserved word
  //int in = input.toInt();
  if (input > 50) {
    digitalWrite(aEN, HIGH);
    delay(1);
    dir(sign, aDI);
    analogWrite(aST, 127);
  } else {
    digitalWrite(aEN, LOW);
    analogWrite(aST, 0);
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
    clawRight.write(80);    // was 60
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

int xDir = 8;
int xEn = 12;
int xStep = 10;

int yDir = 9;
int yEn = 13;
int yStep = 11;
int timeDiff;
 

// BEGIN ROUTINE

Serial.println("Begin Game");
// # ### Open The CLAW ### #
Serial.println("Open the claw");
delay(1000);
unsigned long startTime = millis();       // assign startTime comparison value
unsigned long stopTime = millis();        // assign stopTime value
timeDiff = stopTime-startTime;
while(timeDiff<3000)        // while will run for 3 seconds
{
  openGrabber();                // open grabber
  timeDiff = millis()-startTime;              // new time comparison value
}

// # ### ### #
//
//
// # ### Drop THE CLAW ### #

Serial.println("Drop the Claw");
delay(1000);
startTime = millis();             // new time comparison value
stopTime = millis();
timeDiff = (stopTime-startTime);
while(timeDiff<5000)        // while runs for 5 seconds
{
  lowerSpool();                 // lower the claw
  timeDiff = millis()-startTime;              // new time comparison value
}
stopSpool();                  // stops moving the spool

// # ### ### #
//
//
// # ### Close The CLAW ### #

Serial.println("Close the Claw");
delay(1000);
long grab = random(0,1);
long endTime = 0;
if (grab>0.75)
{
  startTime = millis();
  stopTime = millis();
  timeDiff = (stopTime-startTime);

  while(timeDiff<3500)
  {
   closeGrabberCompletely();
   timeDiff = millis()-startTime; 
  }
  stopSpool();
  endTime = 3500;
}
else
{
  startTime = millis();
  stopTime = millis();
  timeDiff = (stopTime-startTime);
  while(timeDiff<1000)
  {
   closeGrabberPartially();
   timeDiff = millis()-startTime; 
  }
  stopSpool();
  endTime = 1000;
}

// # ### ### #
//
//
// # ### Raise The CLAW ### #

Serial.println("Raise the Claw");
delay(1000);
startTime = millis();
stopTime = millis();
timeDiff = (stopTime-startTime);
while(timeDiff<5000)
{
  raiseSpool();
  timeDiff = millis()-startTime; 
}
stopSpool();

// # ### ### #
//
//
// # ### Return X Axis ### #

Serial.println("Return X");
delay(1000);
while(analogRead(0)<900)          // while switch is open (5V will read 1024)
{
Serial.println(analogRead(0));
moov(255,12,10,8,1);
}


// # ### ### #
//
//
// # ### Return Y Axis ### #

Serial.println("Return Y");
delay(1000);
while(analogRead(1)<700)          // while switch is open
{
moov(255,13,11,9,0);
}


// # ### ### #
//
//
// # ### Open Claw ### #

Serial.println("Open Claw");
delay(1000);
startTime = millis();

while((stopTime - startTime)<endTime)
{
  openGrabber();
  stopTime = millis();
}
stopSpool();

//# ### ### #
//
//
// # ### Close Claw ### #

Serial.println("Close Claw");
delay(1000);
startTime = millis();

while((stopTime - startTime)<5000)
{
  closeGrabberCompletely();
  stopTime = millis();
}
stopSpool();

 
}
