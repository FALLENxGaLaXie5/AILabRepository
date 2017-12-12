
// Code tuned for robot 4
// modified: 10/03/2017, Joshua
// COMP 590

#include <Servo.h>
// #define ROTATION 663 // According to manual
#define fullRight 1317
#define fullLeft 1319
#define ROTATION 280  // According to tests?
#define forward 'f'
#define turn 't'


//int state = 1;
//int state = 2;
//int state = 3;

/*
void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) 
  {
    
    incomingByte = Serial.read(); // read the incoming byte:
    //Serial.println(incomingByte);
    
    if(incomingByte == forward)
    {
      Serial.print(" I received:");
      Serial.println(incomingByte);
    }
    else if(incomingByte == turn)
    {
      Serial.print(" I received:");
      Serial.println(incomingByte);
    }
    
    
  }
}
*/


// encoder variables:
const byte encoder0pinA = 2;//2;//A pin -> the interrupt pin 2
const byte encoder0pinB = 3;//3;//B pin -> the digital pin 3
byte encoder0PinALast;

const byte encoder1pinA = 18;//18;//A pin -> the interrupt pin 18
const byte encoder1pinB = 19;//19;//B pin -> the digital pin 19
byte encoder1PinALast;

int loopCnt=0;
int Ts = 1; //1ms

float desiredTurns = 2;

long duration0;// size of long = 32 bits = 2^32= 4294967296
// number of counts per rotation of the wheels = 1300
boolean Direction0;//the rotation Direction0 

boolean record;
boolean recordRotate;
boolean moveAgain;

long duration1;//the number of the pulses

long currentPosLeft;
long currentPosRight;
boolean Direction1;//the rotation Direction0 
char incomingByte = 0;

#define CIRC 136 * PI
#define PIP_DIST (CIRC) / ROTATION

int power0, power1;

Servo ST1, ST2; 
void setup()
{
  record = true;
  recordRotate = false;
  moveAgain = false;
  ST1.attach( 10, 1000, 2000);
  ST2.attach(9, 1000, 2000);

  currentPosLeft = 0;
  currentPosRight = 0;
  power0 = 90;
  power1 = 90;
  Serial.begin (9600);
  
  Direction0 = true;//default -> Forward
  Direction1 = true;//default -> Forward   
  record = true;
  pinMode(encoder0pinB,INPUT);
  pinMode(encoder1pinB,INPUT);  
  attachInterrupt(digitalPinToInterrupt(encoder0pinA), wheelSpeed0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder1pinA), wheelSpeed1, CHANGE);

}

void loop()
{
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();

    if(incomingByte == forward)
    {
      Serial.print("I received: ");
      Serial.print(incomingByte);
    }
    else if(incomingByte == turn)
    {
      Serial.print("I received: ");
      Serial.print(incomingByte);
    }
  }

  
  
  if (loopCnt%10 == 0)
  {
    //duration0 is right wheel
    //duration1 is left wheel
    Serial.println(duration0);
    Serial.println(duration1);
    currentPosLeft = duration1;
    currentPosRight = duration0;
    Serial.println(currentPosLeft);
    Serial.println(currentPosRight);
    //Serial.println(loopCnt);


    
  }

  if(record)
    {
      moveRot(5);
    }
  if(recordRotate)
  {
    moveTurn(3);
  }
  if(moveAgain)
  {
    moveRot(5);
  }
  
  //Serial.println(currentPosLeft);
  //Serial.println(currentPosRight);
 // duration0 = 0;
 // duration1 = 0;
  if (loopCnt<100)
  {
    //power0 = 90;
    //power1 = 90;
  }
  else
  {
    //power0 =90;
  }

  
  ST1.write(power0);
  ST2.write(power1); 
  
  delay(10);
  loopCnt+=1;
}

void moveForward(int distance, int durationPip)
{
  while(durationPip <= distance)
  {
    power0=95; //Wheel 1, left wheel
    power1=78; //Wheel 2, right wheel
  }

  //Stop
  power0 = 90;
  power1 = 90;      
}

void initializeRot(int numRotations)
{
  currentPosLeft = 0;
  currentPosRight = 0;
  record = true;
}

void moveTurn(int numRotations)
{
  int rotRight = currentPosRight/fullRight;
  //int rotLeft = currentPosLeft/fullLeft;
  if(rotRight < numRotations)
  {
    power0 = 90;
    power1 = 75;
  }
  if(rotRight >= numRotations)
  {
    power0 = 90;
    power1 = 90;
    recordRotate = false;
    moveAgain = true;
    duration0 = 0;
    duration1 = 0;
    currentPosRight = 0;
    currentPosLeft = 0;
  }
}

void moveRot(int numRotations)
{
  //power1 = 130;
  //power0 = 130;
  int rotRight = currentPosRight/fullRight;
  int rotLeft = currentPosLeft/fullLeft;
  /*
  if(rotRight < numRotations && rotLeft < numRotations && rotRight < rotLeft)
  {
    power1 = 60;
    power0 = 110;
  }
  else if(rotRight < numRotations && rotLeft < numRotations && rotRight > rotLeft)
  {
    power1 = 70;
    power0 = 110;
  }
  else if(rotRight < numRotations && rotLeft < numRotations && rotRight == rotLeft)
  {
    power1 = 60;
    power0 = 110;
  }
  else if(rotRight < numRotations && rotLeft >= numRotations)
  {
    power1 = 60;
    power0 = 90;
  }
  else if(rotLeft < numRotations && rotRight >= numRotations)
  {
    power1 = 90;
    power0 = 110;
  }
  */
  if(rotRight < numRotations && rotLeft < numRotations)
  {
    power1 = 65;
    power0 = 109;
  }
  if(rotLeft >= numRotations)
  {
   
    power0 = 90;
    //record = false;
  }
  if(rotRight >= numRotations)
  {
    power1 = 90;
  }
  if(rotRight >= numRotations && rotLeft >= numRotations)
  {
    record = false;
    recordRotate = true;
    duration0 = 0;
    duration1 = 0;
    currentPosRight = 0;
    currentPosLeft = 0;
  }
  //power0 = 70;
  //power1 = 70;
}

void moveBackward()
{
  
}

void turningLeft()
{
  
}

void turningRight()
{
  
}

void wheelSpeed0()
{
  int Lstate0 = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate0==HIGH)
  {
    int val0 = digitalRead(encoder0pinB);
    if(val0 == LOW && Direction0)
      Direction0 = false; //Reverse
    else if(val0 == HIGH && !Direction0)
      Direction0 = true;  //Forward
  }
  encoder0PinALast = Lstate0;
  
  if(!Direction0)  duration0++;
  else  duration0--;

}

void wheelSpeed1()
{
  int Lstate1 = digitalRead(encoder1pinA);
  if((encoder1PinALast == LOW) && Lstate1==HIGH)
  {
    int val1 = digitalRead(encoder1pinB);
    if(val1 == LOW && Direction1)
      Direction1 = false; //Reverse
    else if(val1 == HIGH && !Direction1)
      Direction1 = true;  //Forward
  }
  encoder1PinALast = Lstate1;
  
  if(!Direction1)  duration1++;
  else  duration1--;
   
}


