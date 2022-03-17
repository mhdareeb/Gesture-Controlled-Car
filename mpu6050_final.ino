//Measure Angle with a MPU-6050(GY-521)

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double xval;
double yval;
double zval;

int xPin=A4;
int yPin=A5;

int out1=9;     //output1 for HT12E IC
int out2=10;     //output1 for HT12E IC
int out3=11;    //output1 for HT12E IC
int out4=12;    //output1 for HT12E IC



void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);

  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);

       xval= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
       yval= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       zval= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  

     if ((xval>350 || xval<10) && (yval>350 || yval<10)) //stop
  {
  Serial.println("stop");
    digitalWrite(out1,LOW);  
    digitalWrite(out2,LOW);   
    digitalWrite(out3,LOW);   
    digitalWrite(out4,LOW);
  } 

  else 
  { 
    if (xval>10 && xval<90)// && (yval>294 && yval<340)) //forward
   {
    
     Serial.println("forward");
     digitalWrite(out1,HIGH);  
     digitalWrite(out2,LOW);   
     digitalWrite(out3,HIGH);  
     digitalWrite(out4,LOW);
      
    }
    if (xval>270 && xval<350)// && (yval>294 && yval<340)) //backward
  {
    
    Serial.println("backward");
   digitalWrite(out1,LOW);   
   digitalWrite(out2,HIGH);  
   digitalWrite(out3,LOW);   
   digitalWrite(out4,HIGH);
      
    }   

    if (yval>270 && yval<350) //left(xval>294 && xval<340)
    {
     
    Serial.println("left");    
      digitalWrite(out1,HIGH);  
      digitalWrite(out2,LOW);   
      digitalWrite(out3,LOW);   
      digitalWrite(out4,LOW);
     }


    if (yval>10 && yval<90)//right  (xval>294 && xval<340) &&
    {
      
        Serial.println("right");   
      digitalWrite(out1,LOW);  
      digitalWrite(out2,LOW);   
      digitalWrite(out3,HIGH);   
      digitalWrite(out4,LOW);
      
    }
  }
  
     Serial.print("AngleX= ");
     Serial.println(xval);

     Serial.print("AngleY= ");
     Serial.println(yval);

     Serial.print("AngleZ= ");
     Serial.println(zval);
     Serial.println("-----------------------------------------");
     delay(400);
}
