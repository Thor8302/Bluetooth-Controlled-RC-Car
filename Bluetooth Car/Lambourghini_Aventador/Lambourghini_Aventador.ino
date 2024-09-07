//there were some errors visible in ghini ( lost connection frequently)
//so took base of last used code as it has some other updates also in comment section and removed all new functions related steering.
//👇 ghini : 28/12/2020 12:59 a.m
char t;
int m=0,n=0,mtrdrv=0,mtrcnt=0,fcnt=0,flght=0;
int s=0,speed=0; 
void setup() {
pinMode(2,OUTPUT);   //forward
pinMode(3,OUTPUT);   // reverse
pinMode(4,OUTPUT);   //right motors forward
pinMode(5,OUTPUT);   //right motors reverse
pinMode(10,OUTPUT);  //accelerator
pinMode(6,OUTPUT);   //steering power manupulator
pinMode(A1,INPUT);    //from motordrive to switch on bluetooth
pinMode(7,OUTPUT);   //bluetooth on/off
pinMode(8,OUTPUT);   //front light on/off
digitalWrite(6,1);   //steering power on
Serial.begin(9600);
 
}
 
void loop() {
  t='a';
if(Serial.available()){
  t = Serial.read();
  s = int (t);
  Serial.println(t);
  Serial.println(s);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
   

  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(8,HIGH);
  fcnt=0;
  flght=1;
  m=0;
  n=0;
  
  
  if(speed==255)
  digitalWrite(10,1);
  else
  analogWrite(10,speed);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  
 
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(8,LOW);
  fcnt=100;
 

  flght=0;
  m=0;
  n=0;
  if(speed==255)
  digitalWrite(10,1);
  else
  analogWrite(10,speed);
}
 
else if(t == 'L'){ //left
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  //digitalWrite(8,LOW);
  m=0;
 
  n=0;
  
}
 
else if(t == 'R'){  //right    
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  //digitalWrite(8,LOW);
  m=0;
  
  n=0;
  
}

else if(t == 'G'){    //forward left
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
  fcnt=0;
  
  flght=1;
  m=0;
  n=0;

  if(speed==255)
  digitalWrite(10,1);
  else
  analogWrite(10,speed);
}
else if(t == 'I'){  //forward right
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(8,HIGH);
  fcnt=0;

  flght=1;
  m=0;
  n=0;
  if(speed==255)
  digitalWrite(10,1);
  else
  analogWrite(10,speed);
}
 else if(t=='H'){   //backward left
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   digitalWrite(4,HIGH);
   digitalWrite(5,LOW);
   digitalWrite(8,LOW);
   fcnt=100;

   flght=0;
   m=0;
   n=0;
   if(speed==255)
  digitalWrite(10,1);
  else
  analogWrite(10,speed);
 }
 else if(t=='J'){   //backward right
   digitalWrite(5,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   digitalWrite(8,LOW);
   fcnt=100;

   flght=0;
   m=0;
   n=0;
   if(speed==255)
  digitalWrite(10,1);
  else
  analogWrite(10,speed);
 }
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(8,flght);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  n=0;

}
else if(t=='W'){   //lights on
  flght=1;
  m=1;
 
  n=0;
  analogWrite(10,255);
}
else if(t=='w'){   // lights off
  flght=0;

  m=0;
  n=0;
  analogWrite(10,0);
}
else if(t=='V'||t=='v'){  // emergency all off
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  n=0;
  m=0;

  digitalWrite(10,0);
}
else if(t=='a'){   // no signal then off
  n=n+1;
  if(n>=20){
    n=0;
    m=0;

    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    analogWrite(10,0);
    
  }
}
else if(t=='q')
{
  speed=255;
  
}
if((s>=48)&&(s<=57))
{
  s=s-48;
  speed=(25.5*s);
  
}
if(fcnt<=100)
{
  fcnt=fcnt+1;
  if(fcnt>=100)
  {
    flght=m;
  }
}
else
{
  flght=m;
}
mtrdrv=analogRead(A1);  //reading input at A1 coming from motordrive's 5volt
if(mtrdrv<=100)           //if <=200 switch off bluetooth on count of 100
{
  mtrcnt=mtrcnt+1;
  if(mtrcnt>=10)
  {
    digitalWrite(7,0);
    mtrcnt==0;
  }
}                       //if >=200 stay on 
else if(mtrdrv>=200)
{
  digitalWrite(7,1);    // purpose:-to establish wired connection with laptop 
  mtrcnt==0;            // without opening car
}

delay(10);
}