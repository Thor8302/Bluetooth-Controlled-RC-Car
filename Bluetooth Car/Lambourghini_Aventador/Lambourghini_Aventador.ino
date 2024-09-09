/*
      Lamourghini Aventador 30/5/2021
      ghini updated , angle more precise, motor speed more precise and decreased battery drainage hopefully when speed not full
*/
#include<Servo.h>
char t;
int m = 0, n = 0, mtrdrv = 0, mtrcnt = 0, fcnt = 0, flght = 0, sgnlcnt = 0, sgnl = 0, angle=24,remotelock=0,once=0;
int s = 0, speed = 0;
Servo steer;
void setup() {
  steer.attach(4);
  pinMode(5, OUTPUT);  //forward
  pinMode(3, OUTPUT);  // reverse
  pinMode(11, OUTPUT); //accelerator
  pinMode(A1, INPUT);   //from motordrive to switch on bluetooth
  pinMode(6, OUTPUT);  //bluetooth on/off
  pinMode(8, OUTPUT);  //front light on/off
  Serial.begin(9600);

}

void loop() {
  t = 'A';
  if (Serial.available()) {
    t = Serial.read();
    s = int (t);
    Serial.println(t);
    Serial.println(s);
    //Serial.println(langle);
    //Serial.println(rangle);
    once=0;
  }
   
 
  

if(t=='K')
remotelock=1;

 if(remotelock==1){                                       ///  from here
 if((s>=89)&&(s<=113))
 {
   angle=map(s,89,113,1,25);             // angle setting column 
 }
 
  }                                              //// to here


  if(remotelock==0){
  if (t == 'q')              // from here ....
  {
    speed = 255;
  }                          //this is speed setting column for phone
  
  if ((s >= 48) && (s <= 57))
  {
    s = s - 48;
    speed = (25.5 * s);

  }                               // to here ....
  
}                              // from here 
if(remotelock==1)
{
  if((s>=32)&&(s<=64))
  {                                // this is speed setting column for remote
    speed=map(s,32,64,0,255);
  }
}                                    // to here



  if (t == 'F') {          //move forward


    steer.write(111);
    digitalWrite(11, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(8, HIGH);
    fcnt = 0;
    flght = 1;
    m = 0;
    n = 0;
    sgnl = 0;

    if (speed == 255)
      digitalWrite(5, 1);
    else
      analogWrite(5, speed);
  }

  else if (t == 'B') {    //move reverse


    steer.write(111);
    digitalWrite(11, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
    fcnt = 100;
    sgnl = 0;


    flght = 0;
    m = 0;
    n = 0;
    if (speed == 255)
      digitalWrite(3, 1);
    else
      analogWrite(3, speed);
  }

  else if (t == 'L') {       //left
    digitalWrite(11, m);
    steer.write(111+angle);
    //digitalWrite(8,LOW);
    m = 0;

    n = 0;

  }

  else if (t == 'R') {       //right
    digitalWrite(11, m);
    steer.write(111-angle);
    //digitalWrite(8,LOW);
    m = 0;

    n = 0;

  }

  else if (t == 'G') {  //forward left
    digitalWrite(11, HIGH);
    digitalWrite(3, LOW);
    steer.write(111+angle);
    digitalWrite(8, HIGH);
    fcnt = 0;
    sgnl = 0;
    flght = 1;
    m = 0;
    n = 0;

    if (speed == 255)
      digitalWrite(5, 1);
    else
      analogWrite(5, speed);
  }
  else if (t == 'I') { //forward right
    digitalWrite(3, LOW);
    digitalWrite(11, HIGH);
    steer.write(111-angle);
    digitalWrite(8, HIGH);
    fcnt = 0;
    sgnl = 0;
    flght = 1;
    m = 0;
    n = 0;
    if (speed == 255)
      digitalWrite(5, 1);
    else
      analogWrite(5, speed);
  }
  else if (t == 'H') { //backward left
    digitalWrite(11, HIGH);
    digitalWrite(5, LOW);
    steer.write(111+angle);
    digitalWrite(8, LOW);
    fcnt = 100;
    sgnl = 0;
    flght = 0;
    m = 0;
    n = 0;
    if (speed == 555)
      digitalWrite(3, 1);
    else
      analogWrite(3, speed);
  }
  else if (t == 'J') { //backward right
    steer.write(111-angle);
    digitalWrite(11, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(8, LOW);
    fcnt = 100;
    sgnl = 0;
    flght = 0;
    m = 0;
    n = 0;
    if (speed == 255)
      digitalWrite(3, 1);
    else
      analogWrite(3, speed);
  }



  else if (t == 'S') {    //STOP (all motors stop)
    digitalWrite(11, m);
    digitalWrite(8, flght);
    steer.write(111);
    angle = 25;
    
    n = 0;

  }
  else if (t == 'W') { //lights on
    
    digitalWrite(5, 1);
    digitalWrite(3, 1);
    flght = 1;
    m = 1;
    sgnl = 0;
    n = 0;
  }
  else if (t == 'w') { // lights off
    
    digitalWrite(5, 0);
    digitalWrite(3, 0);
    flght = 0;
    sgnl = 0;
    m = 0;
    n = 0;
  }
  else if (t == 'X') { // parking lights on
   
    sgnl = 1;
  }
  else if (t == 'x') {
   
    sgnl = 0;         // parking lights off
  }
  else if (t == 'V' || t == 'v') { // emergency all off
    digitalWrite(5, LOW);
    digitalWrite(3, LOW);
    steer.write(111);
    digitalWrite(8, LOW);
    n = 0;
    m = 0;
    sgnl = 0;

    digitalWrite(11, 0);
  }
  else if (t == 'A') { // no signal then off
 
    n = n + 1;
    if (n >= 20) {
      n = 0;
      m = 0;

      if (sgnl == 0)
      {
        digitalWrite(5, LOW);
        digitalWrite(3, LOW);
        digitalWrite(11, 1);
        digitalWrite(8, 0);
      }
      steer.write(111);
        if(once==0)
   {
     digitalWrite(6,0);
     delay(10);
     digitalWrite(6,1);
     once=1;
   }  
    }
  }


  if (fcnt <= 100)                // from here ....
  {
    fcnt = fcnt + 1;
    if (fcnt >= 100)             //this is timer portocol for headlight while motion.
    {
      flght = m;
    }
  }
  else
  {
    flght = m;
  }                            //to here ....
  mtrdrv = analogRead(A1); //reading input at A1 coming from motordrive's 5volt   from here .....
  if (mtrdrv <= 100)        //if <=200 switch off bluetooth on count of 100
  {
    mtrcnt = mtrcnt + 1;
    if (mtrcnt >= 1000)
    {
      digitalWrite(6, 0);
      mtrcnt == 0;
    }
  }                       //if >=200 stay on                                process for switching bluetooth on/off
  else if (mtrdrv >= 200)
  {
    digitalWrite(6, 1);   // purpose:-to establish wired connection with laptop
    mtrcnt == 0;          // without opening car                                   to here .....
  }
  if (sgnl == 1) {             // from here
    sgnlcnt = sgnlcnt + 1;
    if ((sgnlcnt >= 50) && (sgnlcnt < 1000)) {
      digitalWrite(8, 0);
      digitalWrite(5, 0);
      digitalWrite(3, 0);
      digitalWrite(11, 0);
      m = 0;                    // parking light blinking function
      flght = 0;
      sgnlcnt = 1000;
    }
    if (sgnlcnt >= 1200) {
      digitalWrite(8, 1);
      digitalWrite(5, 1);
      digitalWrite(3, 1);
      digitalWrite(11, 1);
      flght = 1;
      m = 1;
      sgnlcnt = 0;
    }
  }                           // to here



  delay(5);
}