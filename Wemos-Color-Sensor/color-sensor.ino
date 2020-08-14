//define for color sensor
const int s0 = D1;
const int s1 = D2;
const int s2 = D3;
const int s3 = D4;
int output = D5;

int red=0, green=0, blue=0, redInput=0, blueInput=0, greenInput=0;

void setup(){
  Serial.begin(115200);
  Serial.println("Testing Color Sensor v1.0");
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  
  pinMode(output, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1,HIGH);
}

void loop(){
  ReadRed();
  ReadGreen();
  ReadBlue();

  if(red > green && red > blue)
    Serial.println("Red");
  else if(green > red && green > blue)
    Serial.println("Green");
  else if(blue > red && blue > green)
    Serial.println("Blue");
  
  delay(3000);
}
 


void ReadRed(){
  //Read for Red Filter photodiodes
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redInput = pulseIn(output, LOW);
  //remapping the value color to RGB model 0 to 255
  red = map(redInput, 25, 72, 255, 0);
  delay(100);
}

void ReadBlue(){
  //Read for Blue Filter photodiodes
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blueInput = pulseIn(output, LOW);
  //remapping the value color to RGB model 0 to 255
  blue = map(blueInput, 25, 70, 255, 0);
  delay(100);
}

void ReadGreen(){
   //Read for Green Filter photodiodes
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  greenInput = pulseIn(output, LOW);
  //remapping the value color to RGB model 0 to 255
  green = map(greenInput, 30, 90, 255, 0);
  delay(100);  
}
