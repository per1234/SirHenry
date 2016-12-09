/*
  SirHenry.cpp - Library file allowing rudimentary use of the robot known as SirHenry, developed by Sirkits Pty Ltd.
  Written by J.D Retief and J.C Truter 12/2016

  ## todo - add explanations of each function:
  ## todo - document functions properly

  Functions:
    *void moveForeward(int dist);
    *void moveBackward(int dist);
    *void turnLeft();
    *void turnRight();
    *void colourEye(uint8_t red, uint8_t blue, uint8_t green);
    *int getDist();
    *void rotateHead();

  Setup Details:
    * Left Bumper is connected to pin A0
    * Front Bumper is connected to pin A1
    * Right bumper is connected to pin A2
    * Back bumper is connected to pin A3
    * 
*/
// Necessary Includes:
#include "Arduino.h"
#include "SirHenry.h"
#include <NewPing.h>
#include "Servo.h"

// Defining Pin Connections:

#define redPin 6
#define bluePin 5
#define greenPin 3
#define servoPin 9
#define MotorABrakePin 10
#define MotorBBrakePin 11
#define MotorADirectionPin 12
#define MotorBDirectionPin 13
#define triggerPin A5
#define echoPin A4
#define leftPin A0
#define frontPin A1
#define rightPin A2
#define hindPin A3


// todo - do this in a cleaner manner, if there is one.

// globally accessible objects; 
Servo myServo;
NewPing sonar(triggerPin,echoPin, 300); //Trigger, Echo, maxDist(cm)


SirHenry::SirHenry(void)
{
  // Setting up pin modes:
  
    // RGB LED pins:
      pinMode(redPin, OUTPUT); // red pin
      pinMode(bluePin, OUTPUT); // blue pin
      pinMode(greenPin, OUTPUT); //green pin
      
    // Motor Control pins:
      
      pinMode(MotorABrakePin,OUTPUT);       //Channel A Brake Pin
      pinMode(MotorBBrakePin,OUTPUT);       //Channel B Brake Pin
      pinMode(MotorADirectionPin,OUTPUT);      //Channel A Direction Pin
      pinMode(MotorBDirectionPin,OUTPUT);      //Channel B Direction Pin
      
    // Bumper pins:
      pinMode(leftPin,INPUT);
      pinMode(frontPin,INPUT);
      pinMode(rightPin,INPUT);
      pinMode(hindPin,INPUT);

   // Servo:
      pinMode(servoPin,OUTPUT);
}


void SirHenry::motorA(uint8_t dir)
{
  if(dir == 0)
  {
    // dir = 0 - backwards
    //  therefore direction pin (Mn = low)
    // then write pwm signal to En pin

    digitalWrite(MotorADirectionPin,LOW); 
    analogWrite(MotorABrakePin,255);
  }

  else{
    //something
    digitalWrite(MotorADirectionPin,HIGH);
    analogWrite(MotorABrakePin,255);
  }

  delay(800);
  analogWrite(MotorABrakePin,0);
}
void SirHenry::motorB(uint8_t dir)
{
  if(dir == 0)
  {
    // dir = 0 - backwards
    //  therefore direction pin (Mn = low)
    // then write pwm signal to En pin

    digitalWrite(MotorBDirectionPin,LOW);
    analogWrite(MotorBBrakePin,255);
  }

  else{
    //something
    digitalWrite(MotorBDirectionPin,HIGH);
    analogWrite(MotorBBrakePin,255);
  }

  delay(800);
  analogWrite(MotorBBrakePin,0);
}
void SirHenry::motorAB(uint8_t dir)
{
  if(dir==0)
  {
    digitalWrite(MotorADirectionPin,LOW); 
    analogWrite(MotorABrakePin,255);

    digitalWrite(MotorBDirectionPin,LOW);
    analogWrite(MotorBBrakePin,255);
  }

  else
  {
    digitalWrite(MotorADirectionPin,HIGH);
    analogWrite(MotorABrakePin,255);

    digitalWrite(MotorBDirectionPin,HIGH);
    analogWrite(MotorBBrakePin,255);
  }

  delay(800);
  analogWrite(MotorABrakePin,0);
  analogWrite(MotorBBrakePin,0);
}
void SirHenry::moveForeward(int dist)
{
  for(uint8_t i = 0; i<dist;i++)
  {
    motorAB(1);
  }
}
void SirHenry::moveBackward(int dist)
{
  for(uint8_t i = 0; i<dist;i++)
  {
    motorAB(0);
  }
}
void SirHenry::turnLeft(void)
{
  motorA(1);
}
void SirHenry::turnRight(void)
{
  motorB(1);
}


void SirHenry::colourEye(uint8_t red, uint8_t green, uint8_t blue){
	
	/* 	This function controls the RGB LED of the robot.
	 *  A desired RGB tuple has to be passed to the function in the following format: (R, G, B)
	 * 	The function then sets the values of the individual pins on the LED module
	 * 	
	 * 	Params:
	 * 		uint8_t red: Red value of RGB tuple
	 * 		uint8_t green: Green value of RGB tuple
	 * 		uint8_t blue: Blue value of RGB tuple
	 * 	
	 * 	Output: 
	 * 		None
	 * 
	 * 	Some RGB combinations:
	 * 							191,191,191 -white
								0,0,0       - OFF
                                0,255,0     -pure green
                                255,0,0     -pure red
								0,0,255     -pure blue
							
	  							232,32,32   -pink
                                28,200,28   -nice green
                                191,64,191  -light purple
                                255,128,0   -bright yellow
                                255,0,128   -bright purple
                                0,255,128   -cyan
                                0,128,255   -light blue
                                128,0,255   -bluish-purple
                                64,0,255    -violet-ish
                                0,64,128    -light-cyan
                                128,64,64   -purplish-silver
	 */
		
	  // Setting the corresponding pins' values
	  // 255-value since LED module's colours are 'inverted'
	  
	  if((red>=0)&&(red<=255)){
			analogWrite(redPin,255-red);
	  }
  
	  if((green>=0)&&(green<=255)){
			analogWrite(greenPin,255-green);
	  }

	  if((blue>=0)&&(blue<=255)){
			analogWrite(bluePin,255-blue);
	  }
}

void SirHenry::rotateHead(int angle)
{
  int actual = 90;
  myServo.attach(servoPin);

  if((angle>=-85)&&(angle<=85))
  {
    actual = 90+angle;
  }

  myServo.write(actual);
  delay(200);
}
int SirHenry::getDist()
{
  int echo = sonar.ping_median(5);
  int dist = sonar.convert_cm(echo);
  
  return dist;
}

uint8_t SirHenry::detect(uint8_t num)
{
 uint8_t measurement = -1; //returns -1 if error
 int value = 0;
 
  if(num == 1)
  {
    value = digitalRead(frontPin);
    if(value == HIGH)
    {
      measurement = 0;
    }
    else
    {
      measurement = 1;
    }
  }
  else if(num==2)
  {
    value = digitalRead(leftPin);
    if(value == HIGH)
    {
      measurement = 0;
    }
    else
    {
      measurement = 1;
    }
  }
  else if(num==3)
  {
    value = digitalRead(hindPin);
    if(value == HIGH)
    {
      measurement = 0;
    }
    else
    {
      measurement = 1;
    }
  }
  else if(num==4)
  {
    value = digitalRead(rightPin);
    if(value == HIGH)
    {
      measurement = 0;
    }
    else
    {
      measurement = 1;
    }
  }
  else
  {
    // do nothing, error value has already been set up  
  }

  return measurement;
}
