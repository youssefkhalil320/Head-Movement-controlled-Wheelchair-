
#include <SoftwareSerial.h>

# define Trigger_Right 11
# define Echo_Right 12
# define Trigger_Left 6
# define Echo_Left 7
# define Trigger_Front 14
# define Echo_Front 15
# define Max_Distance 200
int pin1=2;
int pin2=3;
int pin3=4;
int pin4=5;
int en1=9;
int en2=10;
int Read_Right;
int Read_Left;
int Read_Front;
int Mode =1;
int Min_Distance_front = 20;
char r;
SoftwareSerial mSerail (1,0);


// Ultrasonic Configrations



void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
  //Start Serial Monitor
  
  Serial.begin(9600);
  mSerail.begin(9600);
}

//Function to return the biggest number of three values

int Maximum (int x , int y, int z)
{
  int max;
   max = x ;
   if (y>max){max = y;}
   if (z>max){max = z;}
return max ;
}

//Functions to direct the car

void moveBackward (){
  analogWrite(en1,250);
  analogWrite(en2,250);
  digitalWrite(pin1,1);
  digitalWrite(pin2,0);
  digitalWrite(pin3,0);
  digitalWrite(pin4,1);
 }
 void moveForward(){
  analogWrite(en1,250);
  analogWrite(en2,250);
  digitalWrite(pin1,0);
  digitalWrite(pin2,1);
  digitalWrite(pin3,1);
  digitalWrite(pin4,0);
 }
 
  void turnRight(){
  analogWrite(en1,250);
  analogWrite(en2,250);
  digitalWrite(pin1,0);
  digitalWrite(pin2,1);
  digitalWrite(pin3,0);
  digitalWrite(pin4,1);
 }
 void turnLeft(){
  analogWrite(en1,250);
  analogWrite(en2,250);
  digitalWrite(pin1,1);
  digitalWrite(pin2,0);
  digitalWrite(pin3,1);
  digitalWrite(pin4,0);
 }
  
 void forwardRight(){
  analogWrite(en1,100);
  analogWrite(en2,60);
  digitalWrite(pin1,0);
  digitalWrite(pin2,1);
  digitalWrite(pin3,0);
  digitalWrite(pin4,1);
  }

  void forwardLeft(){
    analogWrite(en1,100);
    analogWrite(en2,60);
  digitalWrite(pin1,0);
  digitalWrite(pin2,1);
  digitalWrite(pin3,0);
  digitalWrite(pin4,1);
    }
  
 void stopNow(){
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
 }

void loop(){
  
//Get readings from Ultrasonics then store it in variables
  while (Serial.available()>0){ 
      serIn=Serial.read();}
  }
  if (Serial.available()>0) {
  serIn=Serial.read()
           if(SerIn == 'F') {
        moveForward();
        Serial.print("forward");
      } else if(SerIn == 'B') {
        moveBackward();
        Serial.print("backward");
      } else if(SerIn == 'L') {
        turnLeft();
      } else if(SerIn == 'R') {
        turnRight();
           
      }
  
  if(Serial.available()>0) {
    
    //Set a variable to take orders from Bluetooth
    r=(Serial.read());
    // A condition to switch between the tow MOdes "Mobile Control mode"&"Auto_drive mode"
    if(r == 'W')
         {Mode = 2;} 
         Serial.println(r);  
  }
// Mobile Control mode
  if (Mode == 1)
  {
    if(Serial.available()>0) {
    r=(Serial.read());
         
          if(r == 'F') {
        moveForward();
        Serial.print("forward");
      } else if(r == 'B') {
        moveBackward();
        Serial.print("backward");
      } else if(r == 'L') {
        turnLeft();
      } else if(r == 'R') {
        turnRight();
      } else if(r == 'S') {
        stopNow();
      }else if(r== 'I'){
        forwardRight();
      }else if(r=='G'){
        forwardLeft();
        }
    
    
    }
    }

//Auto Drive mode
    if (Mode == 2)
    {
      if(Serial.available()>0) {
      r=(Serial.read());
      if(r == 'W')
      {Mode = 1;}
      int Max_Reading = Maximum (Read_Right,Read_Left,Read_Front);
      if (Max_Reading==Read_Right && Read_Front <Min_Distance_front )
      {
      turnRight();
      }
      else if (Max_Reading==Read_Left && Read_Front < Min_Distance_front)
      {       
       turnLeft ();
      }
      else if (Max_Reading==Read_Front)
      moveForward();
           
    }
    }
    
}





  
