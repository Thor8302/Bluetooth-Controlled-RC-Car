/*
               GHINI REMOTE PROTOCOL 30/5/2021
               ghini remote updated angle description improved , motion description improved
               and also the light values are initialized automatically
*/

int mtrspeed, steer, light, park, strangleint, parkkey, lightkey;
char mtrvalue, strvalue, strangle, parkvalue = 'x', lightvalue = 'w',mtrspeedchar;
void setup() {
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A2, INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
}

void loop() {
  mtrspeed = analogRead(A6);
  steer = analogRead(A7);
  light = analogRead(A4);
  park = analogRead(A2);
  if (mtrspeed > 700) {         //  check for forward
    mtrvalue = 'F';                       // and speed accordingly
    mtrspeed = map(mtrspeed, 700, 1015, 32, 64);
  }
  else if (mtrspeed < 400) {    //check for backward
    mtrvalue = 'B';                         // and speed accordingly
    mtrspeed = map(mtrspeed, 5, 400, 64, 32);
  }
  else {
    mtrvalue = 'S';                      // else speed
    mtrspeed = 32;
  }
    if(mtrspeed>64)
    mtrspeed=64;
    if(mtrspeed<32)
    mtrspeed=32;
    mtrspeedchar= char(mtrspeed);
    Serial.println(mtrspeedchar);               // sending motor speed

  if (steer >= 630) {                  //check for right
    strvalue = 'R';
    strangleint = map(steer, 630, 950, 89, 113); //and angle int value
  }
  else if (steer <= 320) {              // check for left
    strvalue = 'L';
    strangleint = map(steer, 0, 320, 113, 89); // and angle int value
  }
  else {
    strvalue = 'S';
    strangleint = 75;
  }


  if ((strangleint < 89)&&(strangleint!=75))
    strangleint = 89;
  else if (strangleint == 75)
    strangleint = 75;
 
  else if (strangleint > 113)
    strangleint = 113;
  strangle = char (strangleint);
  Serial.println(strangle);             // and sending angle value in char



  if ((mtrvalue == 'F') && (strvalue == 'S')) { // from here
    Serial.println('F');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'F') && (strvalue == 'R')) {
    Serial.println('I');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'F') && (strvalue == 'L')) {
    Serial.println('G');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'B') && (strvalue == 'L')) {
    Serial.println('H');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'B') && (strvalue == 'R')) { //  sending mode values
    Serial.println('J');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'B') && (strvalue == 'S')) {
    Serial.println('B');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'S') && (strvalue == 'L')) {
    Serial.println('L');
    parkvalue='x';
    lightvalue='w';
  }
  else if ((mtrvalue == 'S') && (strvalue == 'R')) {
    Serial.println('R');
    parkvalue='x';
    lightvalue='w';
  }                                             //  to here
  else
    Serial.println('S');



  if (park > 60)
    parkkey = 1;                          // creating key for switch so that use signal only once.
  if (parkkey == 1) {
    if (park < 60) {
      if (parkvalue == 'x') {
        Serial.println('X');             // if off then on
        parkvalue = 'X';
      }
      else {
        Serial.println('x');              // if on then off
        parkvalue = 'x';
      }
      parkkey = 0;
    }
  }

  if (light > 60)
    lightkey = 1;                        // creating ey for switch so that use signal only once.
  if (lightkey == 1) {
    if (light < 60) {
      if (lightvalue == 'w') {
        Serial.println('W');             // if off then on
        lightvalue = 'W';
      }
      else {
        Serial.println('w');
        lightvalue = 'w';                 // if on then off
      }
      lightkey = 0;
    }
  }
 
  delay(69);
}