/*
               GHINI REMOTE PROTOCOL
               aur remote for left 47->32 aur right ke liye 97->112 use karta hai
               20/5/2021
*/

int mtrspeed,steer,light,park,strangleint,parkkey,lightkey;
char mtrvalue,strvalue,strangle,parkvalue='x',lightvalue='w';
void setup() {
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  pinMode(A2,INPUT);
  pinMode(A4,INPUT);
  Serial.begin(9600);
}

void loop() {
    mtrspeed=analogRead(A6);
    steer=analogRead(A7);
    light=analogRead(A4);
    park=analogRead(A2);
    if(mtrspeed>700){             //  check for forward 
      mtrvalue='F';                         // and speed accordingly
      mtrspeed=map(mtrspeed,700,1015,0,10);
    }
    else if(mtrspeed<400){        //check for backward
      mtrvalue='B';                           // and speed accordingly
      mtrspeed=map(mtrspeed,5,400,10,0);
    }
    else{
      mtrvalue='S';                        // else speed 
      mtrspeed=0;
    }
    if(mtrspeed==10)
    Serial.println('q');                  // and sending motor speed
    else
    Serial.println(mtrspeed);

if(steer>=630){                      //check for right
  strvalue='R';
  strangleint=map(steer,630,950,97,112);//and angle int value
}
else if(steer<=320){                  // check for left
  strvalue='L';
  strangleint=map(steer,0,320,32,47); // and angle int value
}
else{
  strvalue='S';
  strangleint=75;
}


if(strangleint<32)
strangleint=32;
else if (strangleint==75)
strangleint=75;
else if((strangleint<97)&&(strangleint>72))
strangleint=97;
else if((strangleint<72)&&(strangleint>47))
strangleint=47;
else if(strangleint>112)
strangleint=112;
strangle= char (strangleint);
Serial.println(strangle);             // and sending angle value in char



if((mtrvalue=='F')&&(strvalue=='S')){      // from here 
  Serial.println('F');
}
else if((mtrvalue=='F')&&(strvalue=='R')){
  Serial.println('I');
}
else if((mtrvalue=='F')&&(strvalue=='L')){
  Serial.println('G');
}
else if((mtrvalue=='B')&&(strvalue=='L')){
  Serial.println('H');
}
else if((mtrvalue=='B')&&(strvalue=='R')){      //  sending mode values
  Serial.println('J');
}
else if((mtrvalue=='B')&&(strvalue=='S')){
  Serial.println('B');
}
else if((mtrvalue=='S')&&(strvalue=='L')){
  Serial.println('L');
}
else if((mtrvalue=='S')&&(strvalue=='R')){
  Serial.println('R');
}                                             //  to here
else 
Serial.println('S');



if(park>60)
parkkey=1;                            // creating key for switch so that use signal only once.
if(parkkey==1){
if(park<60){
  if(parkvalue=='x'){
    Serial.println('X');             // if off then on
    parkvalue='X';
  }
  else{
    Serial.println('x');              // if on then off
    parkvalue='x';
  }
  parkkey=0;
}
}

if(light>60)
lightkey=1;                          // creating ey for switch so that use signal only once.
if(lightkey==1){
if(light<60){
  if(lightvalue=='w'){
    Serial.println('W');             // if off then on
    lightvalue='W';
  }
  else{
    Serial.println('w');
    lightvalue='w';                   // if on then off
  }
  lightkey=0;
}
}
  delay(69);
}