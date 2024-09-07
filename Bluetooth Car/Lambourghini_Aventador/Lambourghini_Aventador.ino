//                    ghini 30/11/2020 :- front led better , bluetooth fixed for wired connection from outside the car , hc-05 name and password changed.
char t;
int m=0,n=0,mtrdrv=0,mtrcnt=0,fcnt=0,flght=0;
int s=0,speed=0; 
void setup() {
pinMode(2,OUTPUT);   //left motors forward
pinMode(3,OUTPUT);   //left motors reverse
pinMode(4,OUTPUT);   //right motors forward
pinMode(5,OUTPUT);   //right motors reverse
pinMode(10,OUTPUT);  //accelerator
pinMode(6,INPUT);    //from motordrive to switch on bluetooth
pinMode(7,OUTPUT);   //bluetooth on/off
pinMode(8,OUTPUT);   //front light on/off
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
  analogWrite(10,speed);
}
 
else if(t == 'L'){//turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  //digitalWrite(8,LOW);
  m=0;
  n=0;
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  //digitalWrite(8,LOW);
  m=0;
  n=0;
}

else if(t == 'G'){    
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
  fcnt=0;
  flght=1;
  m=0;
  n=0;
  analogWrite(10,speed);
}
else if(t == 'I'){
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(8,HIGH);
  fcnt=0;
  flght=1;
  m=0;
  n=0;
  analogWrite(10,speed);
}
 else if(t=='H'){
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   digitalWrite(4,HIGH);
   digitalWrite(5,LOW);
   digitalWrite(8,LOW);
   fcnt=100;
   flght=0;
   m=0;
   n=0;
   analogWrite(10,speed);
 }
 else if(t=='J'){
   digitalWrite(5,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   digitalWrite(8,LOW);
   fcnt=100;
   flght=0;
   m=0;
   n=0;
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
else if(t=='W'){
  flght=1;
  m=1;
  n=0;
  analogWrite(10,255);
}
else if(t=='w'){
  flght=0;
  m=0;
  n=0;
  analogWrite(10,0);
}
else if(t=='V'||t=='v'){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  n=0;
  m=0;
  analogWrite(10,0);
}
else if(t=='a'){
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
mtrdrv=digitalRead(6);  //reading input at 6 coming from motordrive's 5volt
if(mtrdrv==0)           //if yes switch on bluetooth 
{
  mtrcnt=mtrcnt+1;
  if(mtrcnt>=10)
  {
    digitalWrite(7,0);
    mtrcnt==0;
  }
}                       //if 0 coninuously then off 
else if(mtrdrv!=0)
{
  digitalWrite(7,1);    // purpose:-to establish wired connection with laptop 
  mtrcnt==0;            // without opening car
}
delay(10);
}