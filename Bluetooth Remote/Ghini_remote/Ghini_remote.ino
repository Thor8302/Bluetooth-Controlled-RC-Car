/*
Ghini remote
21/5/2021
*/
int t=0,a;
char b,c='S';
void setup() {
    pinMode(A7,INPUT);
    //pinMode(11,OUTPUT);
    //digitalWrite(11,1);
    //pinMode(10,OUTPUT);
    //digitalWrite(10,0);
    Serial.begin(9600);
}

void loop() {
    t=analogRead(A7);
    if((t>550)&&(650)){
    a=0;
    b='S';
    }
    if(t>650){
      a=map(t,650,1020,0,10);
      b='F';
    }
    if(t<550){
      a=map(t,1,550,10,0);
      b='B';
    }
    if(a<10)
    Serial.println(a);
    
    Serial.println(b);
    if(a>=10)
    Serial.println('q');
    c=t;
  delay(65);
}