#include <Servo.h> 
Servo servo;
#define trigPin 9
#define echoPin 8
#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7
#define Enr 3
#define Enl 11
void stop();
int dist();
void setup() {
  pinMode(MLa,OUTPUT);    
  pinMode(MLb,OUTPUT);
  pinMode(MRa,OUTPUT);
  pinMode(MRb,OUTPUT);
  pinMode(Enr,OUTPUT);
  pinMode(Enl,OUTPUT);
  pinMode(trigPin,OUTPUT);       
  pinMode(echoPin,INPUT);        
  servo.attach(10);
  Serial.begin(9600);
}
void loop() 
{
  unsigned long duration[3], distance[3];
  servo.write(89);
  delay(375);
  
  distance[0] = dist();
  
  if(distance[0]>18)
  {
   Serial.println("Move forward");
   digitalWrite(MLb,HIGH);//forward
   digitalWrite(MLa,LOW);
   digitalWrite(MRb,HIGH);
   digitalWrite(MRa,LOW);
   analogWrite(Enr,50);
   analogWrite(Enl,50);
   Serial.println("PWM 60");
   delay(10);
  }

  else if((distance[0]<=18)&&(distance[0]>=0))
  {
   stop();
  //  delay(450);
   for(int i=90;i<=180;i+=5)
    {
      servo.write(i);
      delay(45);
    }// serveo facing left
    delay(20);
   distance[1] = dist();
    delay(20);
   for(int i=180;i>=90;i-=5)
    {
      servo.write(i);
      delay(45);
    }
    
   for(int i=90;i>=0;i-=5)
   {
     servo.write(i);
     delay(45);
   }// serveo facing right
    delay(20);
   distance[2] = dist();
    delay(20);
   for(int i=0;i<=90;i+=5)
   {
     servo.write(i);
     delay(45);
   }

   if ((distance[1]>distance[2])&&(distance[1]>=18) )
   {
     Serial.println("Turn left");
     digitalWrite(MLb,HIGH);//left turn
     digitalWrite(MLa,LOW);
     digitalWrite(MRb,LOW);
     digitalWrite(MRa,HIGH);
     analogWrite(Enr,53);
     analogWrite(Enl,53);
     Serial.println("PWM 53");
     delay(400);
     stop();
     
    }
   
   else if ((distance[1]<distance[2])&&(distance[2]<=18) )
    {
      Serial.println("Turn right");
      digitalWrite(MLb,LOW);//right turn
      digitalWrite(MLa,HIGH);
      digitalWrite(MRb,HIGH);
      digitalWrite(MRa,LOW);
      analogWrite(Enr,53);
      analogWrite(Enl,53);
      Serial.println("PWM 53");
      delay(400);
      stop();
    }
   else 
   {
     digitalWrite(MLb,LOW);//reverse out
     digitalWrite(MLa,HIGH);
     digitalWrite(MRb,LOW);
     digitalWrite(MRa,HIGH);
     analogWrite(Enr,50);
     analogWrite(Enl,50);
     Serial.println("reverse");
     Serial.println("PWM 50");
     delay(500);
     stop();
     digitalWrite(MLb,LOW);//U turn
     digitalWrite(MLa,HIGH);
     digitalWrite(MRb,HIGH);
     digitalWrite(MRa,LOW);
     analogWrite(Enr,50);
     analogWrite(Enl,50);
     Serial.println("U Turn");
     Serial.println("PWM 50");
     delay(750);
     stop();
   }
  }

  else //
  {
    stop();
  }
}
void stop()
{
   digitalWrite(MLb,LOW);//stop
   digitalWrite(MLa,LOW);
   digitalWrite(MRb,LOW);
   digitalWrite(MRa,LOW);
   analogWrite(Enr,0);
   analogWrite(Enl,0); 
   Serial.println("Stop");
   Serial.println("PWM 0");
   delay(450);
}
int dist()
{ 
  long distance , dur;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin,LOW);
  
  dur = pulseIn(echoPin,HIGH);
  distance = dur/29/2;
  Serial.println(distance);
  return distance;
}
