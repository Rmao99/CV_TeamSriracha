#include <NewPing.h>
#include <RPiRecieve.cpp>

#include <Servo.h>
#define SONAR_NUM 2
class FRCMotor
{ 
  private:
  int pin;
  int position;
  Servo motor;
  boolean myPolarity;
  boolean GoThroughWhile;
  
  public: 
  
void init(int pin)
{
    motor.attach(pin);
}

void setPolarity(boolean polarity)
{
  myPolarity = polarity;
}

void setSpeed(int speed)
{ 
  if (myPolarity == false )
    position = (speed + 100)* 0.9; // this is the one where you put it 100 and it goes backwards, inverted, left (checked)
  else
    position =(100 - speed) * 0.9; //this is the one where you put in 100 and it goes forward, normal,right (checked)

    motor.write(position);
}
};


int tooCloseWall = 29;
int tooFarWall = 33;
int tooCloseFront = 17;

RPiRecieve reciever;
FRCMotor left;
FRCMotor right;
unsigned int rangeFront;
unsigned int rangeSide;
boolean GoThroughWhile;

//NewPing sonar[SONAR_NUM]= 
NewPing sonar(3,4,400);
NewPing sonar2(11,12,400); //random
//assigns (trig pin, echo pin) of ultrasonic

//NewPing sonar(,);}

void CheckDistance() {
Serial.begin(115200);
rangeFront = sonar.ping_cm();
rangeSide = sonar2.ping_cm();
Serial.print("rangeFront:");
Serial.print(rangeFront);
Serial.println(" ");
Serial.print("rangeSide:");
Serial.print(rangeSide);
Serial.println(" ");
Serial.print("done");
Serial.println(" ");
}

void setup() {
reciever.rpiInit();
left.init(10);
right.init(9);
left.setPolarity(true); //this means left is the true to statement
right.setPolarity(false); //this means right is the inverted
boolean GoThroughWhile = true;
delay(50);
CheckDistance(); }


void loop() {
CheckDistance();
      while (GoThroughWhile = true) {
CheckDistance();
  while (rangeFront > tooCloseFront){
    rangeFront = sonar.ping_cm();
    if (rangeSide < tooCloseWall){
CheckDistance(); 
//rangeSide = sonar2.ping_cm();
left.setSpeed(15);
right.setSpeed(30);
    }
    if (rangeSide > tooFarWall){
//rangeSide = sonar2.ping_cm();
CheckDistance();
left.setSpeed(30);
right.setSpeed(15);
    }
    else {
//rangeSide = sonar2.ping_cm();
CheckDistance();
left.setSpeed(30);
right.setSpeed(30);
    }
    }
  while (rangeFront < tooCloseFront){
  CheckDistance();
      left.setSpeed(0); 
      right.setSpeed(0);
      delay(1000);
      right.setSpeed(25);
      delay(3000);
      right.setSpeed(25);
      left.setSpeed(25);
      delay(3000);
      GoThroughWhile = false;   
  }
  
    
  }
  
  /////////////////PUT THIS INTO YOUR CODE SOMEWHERE AND HOPE IT RUNS
left.setSpeed(30);
right.setSpeed(30);
while(/*not close to the front wall*/)
{
    reciever.rpiRead();
    if(reciever.foundGoal())
    {
           
        left.setSpeed(15);
        right.setSpeed(15);
        while(reciever.goalGetAzimuth() > 0.5)
        {
            reciever.rpiRead();
        }
        left.setSpeed(0);
        right.setSpeed(0); 
        //SHOOT          
    }
}

left.setSpeed(-30);
right.setSpeed(-30);
while(/*maximum distance from the far wall*/)
{
    reciever.rpiRead();
    if(reciever.foundCross())
    {
        left.setSpeed(-15);
        right.setSpeed(-15);
        while(reciever.goalGetAzimuth() > 0.5)
        {
            reciever.rpiRead();
        }
        left.setSpeed(0);
        right.setSpeed(0); 
        //turn left 90 degrees and drive straight into the goal
    }
}
  
  
}
  
  



