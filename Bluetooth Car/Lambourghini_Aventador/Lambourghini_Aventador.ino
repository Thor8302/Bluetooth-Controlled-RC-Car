/*
           Lambourghini Aventador
           induction brakes applied when connection suddenly lost while driving
           22/5/2021
*/
#include<Servo.h>
char t;
int m=0,n=0,mtrdrv=0,mtrcnt=0,fcnt=0,flght=0,sgnlcnt=0,sgnl=0,rangle=87,langle=136;
int s=0,speed=0; 
Servo steer;
void setup() {
steer.attach(4);  
pinMode(2,OUTPUT);   //forward
pinMode(3,OUTPUT);   // reverse
pinMode(11,OUTPUT);  //accelerator
pinMode(A1,INPUT);    //from motordrive to switch on bluetooth
pinMode(7,OUTPUT);   //bluetooth on/off
pinMode(8,OUTPUT);   //front light on/off
Serial.begin(9600);
 
}
 
void loop() {
  t='A';
if(Serial.available()){
  t = Serial.read();
  s = int (t);
  Serial.println(t);
  Serial.println(s);
  //Serial.println(langle);
  //Serial.println(rangle);
}
 
 
 
                                    ///  from here
 //Serial.println(s);
  if((s>=32)&&(s<=47))
  langle=map(s,32,47,136,113);
                                                     /// angle setting from remote
  if((s>=97)&&(s<=112))
  rangle=map(s,97,112,111,87);
//Serial.println(langle);
//Serial.print(rangle);
                                     //// to here


if(t=='q')                 // from here ....    
{
  speed=255;
                                 //this is speed setting column.
}
if((s>=48)&&(s<=57))
{
  s=s-48;
  speed=(25.5*s);
  
}                               // to here ....

 
 
 
if(t == 'F'){            //move forward
   

  steer.write(112);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(8,HIGH);
  fcnt=0;
  flght=1;
  m=0;
  n=0;
  sgnl=0;
  
  if(speed==255)
  digitalWrite(11,1);
  else
  analogWrite(11,speed);
}
 
else if(t == 'B'){      //move reverse 
  
 
  steer.write(112);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(8,LOW);
  fcnt=100;
  sgnl=0;
 

  flght=0;
  m=0;
  n=0;
  if(speed==255)
  digitalWrite(11,1);
  else
  analogWrite(11,speed);
}
 
else if(t == 'L'){         //left
  digitalWrite(11,m);
  steer.write(langle);
  //digitalWrite(8,LOW);
  m=0;

  n=0;
  
}
 
else if(t == 'R'){         //right    
  digitalWrite(11,m);
  steer.write(rangle);
  //digitalWrite(8,LOW);
  m=0;
  
  n=0;
  
}

else if(t == 'G'){    //forward left
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  steer.write(langle);
  digitalWrite(8,HIGH);
  fcnt=0;
  sgnl=0;  
  flght=1;
  m=0;
  n=0;

  if(speed==255)
  digitalWrite(11,1);
  else
  analogWrite(11,speed);
}
else if(t == 'I'){  //forward right
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  steer.write(rangle);
  digitalWrite(8,HIGH);
  fcnt=0;
  sgnl=0;
  flght=1;
  m=0;
  n=0;
  if(speed==255)
  digitalWrite(11,1);
  else
  analogWrite(11,speed);
}
 else if(t=='H'){   //backward left
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   steer.write(langle);
   digitalWrite(8,LOW);
   fcnt=100;
   sgnl=0;
   flght=0;
   m=0;
   n=0;
   if(speed==255)
  digitalWrite(11,1);
  else
  analogWrite(11,speed);
 }
 else if(t=='J'){   //backward right
   steer.write(rangle);
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   digitalWrite(8,LOW);
   fcnt=100;
   sgnl=0;
   flght=0;
   m=0;
   n=0;
   if(speed==255)
  digitalWrite(11,1);
  else
  analogWrite(11,speed);
 }

 
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(11,m);
  digitalWrite(8,flght);
  steer.write(112);
  langle=136;
  rangle=87;
  n=0;

}
else if(t=='W'){   //lights on
  digitalWrite(2,1);
  digitalWrite(3,1);
  flght=1;
  m=1;
  sgnl=0;
  n=0;
}
else if(t=='w'){   // lights off
  digitalWrite(2,0);
  digitalWrite(3,0);
  flght=0;
  sgnl=0;
  m=0;
  n=0;
}
else if(t=='X'){   // parking lights on
  sgnl=1;
}
else if(t=='x'){
  sgnl=0;           // parking lights off
}
else if(t=='V'||t=='v'){  // emergency all off
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  steer.write(112);
  digitalWrite(8,LOW);
  n=0;
  m=0;
  sgnl=0;

  digitalWrite(11,0);
}
else if(t=='A'){   // no signal then off
  n=n+1;
  if(n>=20){
    n=0;
    m=0;

    if(sgnl==0)
    {
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(11,1);
    digitalWrite(8,0);
    }
    steer.write(112);
  }
}


if(fcnt<=100)                   // from here ....
{
  fcnt=fcnt+1;
  if(fcnt>=100)                //this is timer portocol for headlight while motion.
  {
    flght=m;
  }
}                              
else
{
  flght=m;
}                            //to here ....
mtrdrv=analogRead(A1);  //reading input at A1 coming from motordrive's 5volt   from here .....
if(mtrdrv<=100)           //if <=200 switch off bluetooth on count of 100
{
  mtrcnt=mtrcnt+1;
  if(mtrcnt>=1000)
  {
    digitalWrite(7,1);
    mtrcnt==0;
  }
}                       //if >=200 stay on                                process for switching bluetooth on/off
else if(mtrdrv>=200)
{
  digitalWrite(7,0);    // purpose:-to establish wired connection with laptop 
  mtrcnt==0;            // without opening car                                   to here .....
}
if(sgnl==1){                 // from here 
  sgnlcnt=sgnlcnt+1;
  if((sgnlcnt>=50)&&(sgnlcnt<1000)){
  digitalWrite(8,0);
  digitalWrite(2,0);
  digitalWrite(3,0);
  digitalWrite(11,0);
  m=0;                      // parking light blinking function
  flght=0;
  sgnlcnt=1000;
  }
  if(sgnlcnt>=1200){
    digitalWrite(8,1);
    digitalWrite(2,1);
    digitalWrite(3,1);
    digitalWrite(11,1);
    flght=1;
    m=1;
    sgnlcnt=0;
  }
}                           // to here



delay(5);           
}