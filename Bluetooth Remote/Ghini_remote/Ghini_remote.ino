/*
               GHINI REMOTE PROTOCOL 2/12/2021
               ghini remote : recalibrated
*/

int mtrspeed, steer, light, park, strangleint, parkkey, lightkey;
char mtrvalue, strvalue, strangle, parkvalue = 'x', lightvalue = 'w', mtrspeedchar;
void setup() {
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(A3, 1);
  Serial.begin(9600);
}

void loop() {

  mtrspeed = analogRead(A6);
  steer = analogRead(A7);
  light = analogRead(A4);
  park = analogRead(A2);
  /*  Serial.print("mtr :");
    Serial.println(mtrspeed);
    Serial.print("steer");
    Serial.println(steer);
    
  */
  if (mtrspeed >= 710) {         //  check for forward
    mtrvalue = 'F';                       // and speed accordingly
    mtrspeed = map(mtrspeed, 710, 1015, 32, 64);
  }
  else if (mtrspeed <= 335) {    //check for backward
    mtrvalue = 'B';                         // and speed accordingly
    mtrspeed = map(mtrspeed, 0, 335, 64, 32);
  }
  else {
    mtrvalue = 'S';                      // else speed
    mtrspeed = 32;
  }
  if (mtrspeed > 64)
    mtrspeed = 64;
  if (mtrspeed < 32)
    mtrspeed = 32;
  mtrspeedchar = char(mtrspeed);
  Serial.println(mtrspeedchar);               // sending motor speed
 // Serial.print("steer=");
  //Serial.println(steer);
  if (steer >= 420) {                  //check for right
    strvalue = 'R';
    strangleint = map(steer, 420, 665, 89, 113); //and angle int value
  }
  else if (steer <= 225) {              // check for left
    strvalue = 'L';
    strangleint = map(steer, 0, 225, 113, 89); // and angle int value
  }
  else {
    strvalue = 'S';
    strangleint = 75;
  }


  if ((strangleint < 89) && (strangleint != 75))
    strangleint = 89;
  else if (strangleint == 75)
    strangleint = 75;

  else if (strangleint > 113)
    strangleint = 113;
  strangle = char (strangleint);
  Serial.println(strangle);             // and sending angle value in char



  if ((mtrvalue == 'F') && (strvalue == 'S')) { // from here
    Serial.println('F');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'F') && (strvalue == 'R')) {
    Serial.println('I');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'F') && (strvalue == 'L')) {
    Serial.println('G');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'B') && (strvalue == 'L')) {
    Serial.println('H');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'B') && (strvalue == 'R')) { //  sending mode values
    Serial.println('J');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'B') && (strvalue == 'S')) {
    Serial.println('B');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'S') && (strvalue == 'L')) {
    Serial.println('L');
    parkvalue = 'x';
    lightvalue = 'w';
  }
  else if ((mtrvalue == 'S') && (strvalue == 'R')) {
    Serial.println('R');
    parkvalue = 'x';
    lightvalue = 'w';
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

if((park<60)&&(light<60))
digitalWrite(A3,0);
else
digitalWrite(A3,1);
  delay(69);
}