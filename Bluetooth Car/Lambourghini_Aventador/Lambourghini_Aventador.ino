//                                                ghini:-10/11/2020
//                                                accelerator added
char t;
int m=0,n=0;
int s=0,speed=0; 
void setup() {
pinMode(2,OUTPUT);   //left motors forward
pinMode(3,OUTPUT);   //left motors reverse
pinMode(4,OUTPUT);   //right motors forward
pinMode(5,OUTPUT);   //right motors reverse
pinMode(10,OUTPUT);
pinMode(13,OUTPUT);
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
  m=0;
  n=0;
  analogWrite(10,speed);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  m=0;
  n=0;
  analogWrite(10,speed);
}
 
else if(t == 'L'){//turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  m=0;
  n=0;
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  m=0;
  n=0;
}

else if(t == 'G'){    
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  m=0;
  n=0;
  analogWrite(10,speed);
}
else if(t == 'I'){
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  m=0;
  n=0;
  analogWrite(10,speed);
}
 else if(t=='H'){
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   digitalWrite(4,HIGH);
   digitalWrite(5,LOW);
   m=0;
   n=0;
   analogWrite(10,speed);
 }
 else if(t=='J'){
   digitalWrite(5,HIGH);
   digitalWrite(4,LOW);
   digitalWrite(3,HIGH);
   digitalWrite(2,LOW);
   m=0;
   n=0;
   analogWrite(10,speed);
 }
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(2,m);
  digitalWrite(3,m);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  n=0;
}
else if(t=='W'){
  m=1;
  n=0;
  analogWrite(10,255);
}
else if(t=='w'){
  m=0;
  n=0;
  analogWrite(10,0);
}
else if(t=='V'||t=='v'){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  n=0;
  m=0;
  analogWrite(10,0);
}
else if(t=='a'){
  n=n+1;
  if(n>=10){
    n=0;
    m=0;
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    analogWrite(10,0);
  }
}
else if(t=='q'){
  speed=255;}
if((s>=48)&&(s<=57)){
  s=s-48;
  speed=(25.5*s);}
delay(10);
}