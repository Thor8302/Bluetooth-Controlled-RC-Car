/*
       Lamourghini Aventador 30/7/2021
       GHINI UPDATE : SERVO ON 6 , BLUE = 9,10 ; ACC =11 
       REMEMBER WHEN USING SERVO LIBRARY PIN 9,10 CANNOT GIVE PWM SIGNALS.
*/
#include<Servo.h>
char t;
int m = 1, n = 0, mtrdrv = 0, mtrcnt = 0, fcnt = 0, flght = 0, sgnlcnt = 0, sgnl = 0, angle = 245  , remotelock = 0;
int s = 0, speed = 0, blu = 0, center = 1653;
Servo steer;
void setup() {
  steer.attach(6);
  pinMode(5, OUTPUT);  //forward
  pinMode(3, OUTPUT);  // reverse
  pinMode(11, OUTPUT); //accelerator
  pinMode(9, OUTPUT);   //bluetooth
  pinMode(10, OUTPUT);   //bluetooth
  pinMode(8, OUTPUT);  //front light on/off
  pinMode(7, OUTPUT);  //front light on/off BOTH FOR BETTER GRND
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  Serial.begin(9600);

}

void loop() {
  t = 'A';
  if (Serial.available()) {
    t = Serial.read();
    s = int (t);
    //Serial.println( readVcc(), DEC );
    //Serial.println( readTemp(), DEC );
    //Serial.println(t);
    //Serial.println(s);
    //Serial.println(langle);
    //Serial.println(rangle);

  }

  if (t != 'A')
    blu = 1;        // means bluetooth was once connected.


  if (t == 'K')
    remotelock = 1;

  if (remotelock == 1) {                                   ///  from here
    if ((s >= 89) && (s <= 113))
    {
      angle = map(s, 89, 113, 1, 245  );       // angle setting column
    }

  }                                              //// to here


  if (remotelock == 0) {
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
  if (remotelock == 1)
  {
    if ((s >= 32) && (s <= 64))
    { // this is speed setting column for remote
      speed = map(s, 32, 64, 0, 255);
    }
  }                                    // to here



  if (t == 'F') {          //move forward


    if (speed == 255)
    {
      digitalWrite(11, 1);
    }
    else
    {
      analogWrite(11, speed);
    }

    steer.writeMicroseconds(center);
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(8, 0);
    digitalWrite(7, 0);
    fcnt = 0;
    flght = 0;
    m = 1;
    n = 0;
    sgnl = 0;


  }

  else if (t == 'B') {    //move reverse

    if (speed == 255)
    {
      digitalWrite(11, 1);

    }
    else
    {
      analogWrite(11, speed);
    }

    steer.writeMicroseconds(center);
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    //  digitalWrite(8, LOW);
    // fcnt = 100;
    sgnl = 0;


    // flght = 0;
    m = 1;
    n = 0;
  }

  else if (t == 'L') {       //left
    if (m == 1)
      digitalWrite(11, 0);
    if (m == 0)
      digitalWrite(11, 1);
    steer.writeMicroseconds( center + angle);
    //digitalWrite(8,LOW);
    m = 1;
    n = 0;

  }

  else if (t == 'R') {       //right
    if (m == 1)
      digitalWrite(11, 0);
    if (m == 0)
      digitalWrite(11, 1);
    steer.writeMicroseconds(  center - angle);
    //digitalWrite(8,LOW);
    m = 1;
    n = 0;

  }

  else if (t == 'G') {  //forward left

    if (speed == 255)
    {
      digitalWrite(11, 1);

    }
    else
    {
      analogWrite(11, speed);
    }
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    steer.writeMicroseconds(  center + angle);
    digitalWrite(8, 0);
    digitalWrite(7, 0);
    fcnt = 0;
    sgnl = 0;
    flght = 0;
    m = 1;
    n = 0;

  }
  else if (t == 'I') { //forward right

    if (speed == 255)
    {
      digitalWrite(11, 1);

    }
    else
    {
      analogWrite(11, speed);
    }
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
    steer.writeMicroseconds(  center - angle);
    digitalWrite(8, 0);
    digitalWrite(7, 0);
    fcnt = 0;
    sgnl = 0;
    flght = 0;
    m = 1;
    n = 0;
  }
  else if (t == 'H') { //backward left
    if (speed == 255)
    {
      digitalWrite(11, 1);

    }
    else
    {
      analogWrite(11, speed);
    }

    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    steer.writeMicroseconds(  center + angle);
    //  digitalWrite(8, LOW);
    // fcnt = 100;
    sgnl = 0;
    //  flght = 0;
    m = 1;
    n = 0;
  }
  else if (t == 'J') { //backward right
    if (speed == 255)
    {
      digitalWrite(11, 1);

    }
    else
    {
      analogWrite(11, speed);
    }

    steer.writeMicroseconds(  center - angle);
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
    //  digitalWrite(8, LOW);
    // fcnt = 100;
    sgnl = 0;
    // flght = 0;
    m = 1;
    n = 0;
  }



  else if (t == 'S') {    //STOP (all motors stop)
    if (m == 0)
      digitalWrite(11, 1);
    if (m == 1)
      digitalWrite(11, 0);
    digitalWrite(8, flght);
    digitalWrite(7, flght);
    steer.writeMicroseconds(  center);
    // angle = 25;

    n = 0;

  }
  else if (t == 'W') { //lights on

    digitalWrite(5, 1);
    digitalWrite(3, 1);
    flght = 0;
    m = 0;
    sgnl = 0;
    n = 0;
  }
  else if (t == 'w') { // lights off

    digitalWrite(5, 0);
    digitalWrite(3, 0);
    flght = 1;
    sgnl = 0;
    m = 1;
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
    steer.writeMicroseconds(  center);
    digitalWrite(8, 1);
    digitalWrite(7, 1);
    n = 0;
    m = 1;
    sgnl = 0;

    digitalWrite(11, 0);
  }
  else if (t == 'A') { // no signal then off
    n = n + 1;
    if ((n >= 20) && (n <= 22)) {
      //n = 0;
      m = 1;

      if (blu == 1)
      {
        blu = 0;
        digitalWrite(9, 1);
        digitalWrite(10, 1);
        
        delay(10);
        digitalWrite(9, 0);
        digitalWrite(10, 0);
        
      }


      if (sgnl == 0)
      {



        digitalWrite(5, LOW);
        digitalWrite(3, LOW);
        digitalWrite(11, 1);
        digitalWrite(8, 1);
        digitalWrite(7, 1);
        angle = 25;
      }
      steer.writeMicroseconds(  center);

    }
  }


  if (fcnt <= 250)                // from here ....
  {
    fcnt = fcnt + 1;
    if (fcnt >= 250)             //this is timer portocol for headlight while motion.
    {
      flght = m;
      digitalWrite(8, m);
      digitalWrite(7, m);
    }
  }
  else
  {
    flght = m;
  }                            //to here ....
  if (sgnl == 1) {             // from here
    sgnlcnt = sgnlcnt + 1;
    if ((sgnlcnt >= 25 ) && (sgnlcnt < 1000)) {
      digitalWrite(8, 1);
      digitalWrite(7, 1);
      digitalWrite(5, 0);
      digitalWrite(3, 0);
      digitalWrite(11, 0);
      m = 1;                    // parking light blinking function
      flght = 1;
      sgnlcnt = 1000;
    }
    if ((sgnlcnt >= 1200) && (sgnlcnt < 1225)) {
      digitalWrite(8, 0);
      digitalWrite(7, 0);
      digitalWrite(5, 0);
      digitalWrite(3, 0);
      digitalWrite(11, 0);
      flght = 0;
      m = 0;
    }
    if ((sgnlcnt >= 1225) && (sgnlcnt < 1250)) {
      digitalWrite(8, 1);
      digitalWrite(7, 1);
      digitalWrite(5, 0);
      digitalWrite(3, 0);
      digitalWrite(11, 0);
      flght = 1;
      m = 1;
    }
    if ((sgnlcnt >= 1250) && (sgnlcnt < 1275)) {
      digitalWrite(8, 0);
      digitalWrite(7, 0);
      digitalWrite(5, 0);
      digitalWrite(3, 0);
      digitalWrite(11, 0);
      flght = 0;
      m = 0;
    }
    if ((sgnlcnt >= 1275) && (sgnlcnt < 1300)) {
      digitalWrite(8, 1);
      digitalWrite(7, 1);
      digitalWrite(5, 1);
      digitalWrite(3, 1);
      digitalWrite(11, 1);
      flght = 1;
      m = 1;
      // sgnlcnt = 0;
    }
    if ((sgnlcnt >= 1300) && (sgnlcnt < 1325)) {
      digitalWrite(8, 1);
      digitalWrite(7, 1);
      digitalWrite(5, 0);
      digitalWrite(3, 0);
      digitalWrite(11, 0);
      flght = 1;
      m = 1;
      //  sgnlcnt = 0;
    }
    if (sgnlcnt >= 1325) {
      digitalWrite(8, 1);
      digitalWrite(7, 1);
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