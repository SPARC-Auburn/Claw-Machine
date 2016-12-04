/*
  processSerialData
  Author: Shane Williams, Eric Van Horn, and Jacob Van Horn
  Author Contact: smw0031@auburn.edu
  Last Edit: 16 November 2016 by Eric Van Horn

  Description:
    processSerialData is a preliminary Arduino sketch used for the S.C.O.R.E. crane machine project.
    Ultimately, this program's purpose is to make the Arduino read serial input from a
    Raspberry Pi or computer, and interpret that serial data as values used to drive digital output pins. The digital output pins shall be connected to motor controllers and servos
    to drive the crane machine.

  Present State of Development:
    Currently, functions are being developed to convert data received from the serial port into a form that can
    be used to control digital ouput pins.
    Future points of development for the arduino side of the code include:
      --Verify ability to make claw move up/down...left/right...open/close
      ----Axes' values will need to be converted to frequency (based on magnitude) and direction (based on sign)
      ------in order to tell the stepper motors "what to do"
      ------We will also need to keep track of the claw's x/y position (motors step every 2 pulses of square wave)
      ------
      --Using button to "Start" game mode
      --Using button command to make claw DROP, GRAB, RISE, and RETURN HOME
      --Setting limits of claw's range of motion
  = === NOTES === =
  FOR LOOPS   https://www.arduino.cc/en/Reference/For
  SWITCH CASE   https://www.arduino.cc/en/Reference/SwitchCase
  digitalWrite()   https://www.arduino.cc/en/Reference/DigitalWrite
  Pwm frequency http://playground.arduino.cc/Code/PwmFrequency
*/

#include <Servo.h> 
 
Servo clawLeft;  // create servo object to control a servo 
Servo clawRight;  // create servo object to control a servo 
Servo spool;
int button1 = 4; //button pin, connect to ground to move servo
int press1 = 0;

int pos = 0; // variable to store the servo position

int xDir = 8;
int xEn = 12;
int xStep = 10;

int yDir = 9;
int yEn = 13;
int yStep = 11;

int freqDivisor = 31250;

int analogLimit = 900;

int analogThreshold = 100;

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if (pin == 3 || pin == 11) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setup() {
  //lcd.begin(16,2);        // set up the LCD's number of columns and rows
  Serial.begin(9600);     // open serial port. Baud rate is 9600
  for (int i = 8; i <= 13; i++) // loop to initialize pins
  {
    pinMode(i, OUTPUT);
  }
  setPwmFrequency(xStep, freqDivisor);
  setPwmFrequency(yStep, freqDivisor);
  clawLeft.attach(6);  // attaches the servo on pin 9 to the servo object 
  clawRight.attach(5);  // attaches the servo on pin 9 to the servo object 
  spool.attach(3);
  Serial.setTimeout(100);
  /*pinMode(button1, INPUT);
    digitalWrite(button1, HIGH);      //enable pullups to make pin high
    
    for (int i = 0; i < 200; i++)
    {
    openGrabber();
    }*/
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
  // int limit = analogRead(1);
  // if (limit < analogLimit && input > analogThreshold) {
  if (input > 50) {
    digitalWrite(aEN, HIGH);
    delay(3);
    dir(sign, aDI);
    delay(3);
    analogWrite(aST, 127);
  } else {
    digitalWrite(aEN, LOW);
    delay(3);
    analogWrite(aST, 0);
  }
}

void theChosenOne() 
{
  int timeDiff;
   
  //
  //
  // # ### BEGIN ROUTINE ### #
  
  
  stopSpool();
  //Serial.println("Begin Game");
  
  // # ### OPEN THE CLAW ### #
  //Serial.println("Open the claw");
  delay(1000);
  
  unsigned long startTime = millis();       // assign startTime comparison value
  unsigned long stopTime = millis();        // assign stopTime value
  timeDiff = stopTime-startTime;
  while(timeDiff<1000)        // while will run for 1 seconds
    {
      openGrabber();                // open grabber
      timeDiff = millis()-startTime;              // new time comparison value
    }
  
  // # ### ### #
  //
  //
  // # ### DROP THE CLAW ### #
  
  //Serial.println("Drop the Claw");
  delay(1000);
  startTime = millis();             // new time comparison value
  stopTime = millis();
  timeDiff = (stopTime-startTime);
  while(timeDiff<1700)        // while runs for 1.5 seconds
    {
      lowerSpool();                 // lower the claw
      timeDiff = millis()-startTime;              // new time comparison value
    }
  stopSpool();                  // stops moving the spool
  
  // # ### ### #
  //
  //
  // # ### CLOSE The CLAW ### #
  //Serial.println("Close the Claw");
  delay(1000);
  
  long grab = random(0,1);
  int endTime = 0;
  if (grab>0.75)
    {
      startTime = millis();
      stopTime = millis();
      timeDiff = (stopTime-startTime);
    
      while(timeDiff<1000)
      {
       closeGrabberCompletely();
       timeDiff = millis()-startTime; 
      }
      stopSpool();
      endTime = 1000;
    }
  else
    {
      startTime = millis();
      stopTime = millis();
      timeDiff = (stopTime-startTime);
      while(timeDiff<700)
      {
       closeGrabberPartially();
       timeDiff = millis()-startTime; 
      }
      stopSpool();
      endTime = 700;
    }
  
  // # ### ### #
  //
  //
  // # ### Raise The CLAW ### #
  
  //Serial.println("Raise the Claw");
  delay(1000);
  startTime = millis();
  stopTime = millis();
  timeDiff = (stopTime-startTime);
  while(timeDiff<2500)
  {
    raiseSpool();
    timeDiff = millis()-startTime; 
  }
  stopSpool();
  
  // # ### ### #
  //
  //
  // # ### Return X Axis ### #
  
  /*Serial.println("Return X");
  delay(1000);
  int a=255; int b=12; int c = 10; int d = 8; int e = 1;
  while(analogRead(1)<950)          // while switch is open (5V will read 1024)
  {
  Serial.println(analogRead(1));
  moov(a,b,c,d,e);
  }
  moov(0,b,c,d,e);
  */
  
  // # ### ### #
  //
  //
  // # ### Return Y Axis ### #
  
  //Serial.println("Return Y");
  delay(1000);
   int a=255; int b=13; int c = 11; int d = 9; int e = 0;
   delay(200);
  while(analogRead(3)<950)          // while switch is open
  {
  moov(255,13,11,9,0);
  //Serial.println(analogRead(3));
  }
  moov(0,13,11,9,0);
  
  // # ### ### #
  //
  //
  // # ### Open Claw ### #
  
  //Serial.println("Open Claw");
  delay(1000);
  startTime = millis();
  stopTime= millis();
  while((stopTime - startTime)<endTime)
  {
    openGrabber();
    stopTime = millis();
  }
  
  
  //# ### ### #
  //
  //
  // # ### Close Claw ### #
  
  //Serial.println("Close Claw");
  delay(1000);
  startTime = millis();
  stopTime = millis();
  while((stopTime - startTime)<1000)
  {
    closeGrabberCompletely();
    stopTime = millis();
  } 
  return;
}


void loop() {
  stopSpool();
  String input;
  int sign;
  int button;
  int value;
  int axis;
  int aEnab;
  int aStep;
  int aDirxn;
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n'); // reads specific number of bytes to buttons buffer
    if (input.length() > 0) {             // only calls function if bytes have been read
      switch (input.charAt(0)) {
        case 'a':
          switch (input.charAt(1)) {
            case '0':
              axis = 0;
              break;
            case '1':
              axis = 1;
              break;
          }
          break;
        case 'b':
          button = input.substring(1, 3).toInt();
          value = input.substring(3, 4).toInt();
          if (button==1 && value==1)
          {
            sign = 0; aEnab=13; aStep=11; aDirxn=9;
            theChosenOne();
            button=0;
            value=0;
          // digitalWrite(button, value);  // passes buffer (char array) to function for parsing
          }
          break;
      }
      sign = int(input.charAt(2));
      aEnab = xEn + axis;
      aStep = xStep + axis;
      aDirxn = xDir + axis;
      value = input.substring(3, input.length()).toInt();
      moov(value, aEnab, aStep, aDirxn, sign);

    }
  }
}
