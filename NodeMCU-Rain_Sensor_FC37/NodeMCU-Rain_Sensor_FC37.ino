/*NodeMCU Rain Sensor FC-37*/
/*Version 1.0*/
/*Credit to : https://techtutorialsx.com/2016/12/23/esp8266-detecting-rain-drops/*/

/*Declare Const*/
const byte interruptPin = 13; //NodeMCU Pin
volatile boolean checkInterrupt = false;
int numberOfInterrupts = 0;

unsigned long debounceTime = 1000;
unsigned long lastDebounce = 0;


void setup() {
  Serial.begin(115200);
  pinMode(interruptPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

}

void handleInterrupt(){
  checkInterrupt = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(checkInterrupt == true && ( (millis()-lastDebounce) > debounceTime) ){
    lastDebounce = millis();
    checkInterrupt = false;
    numberOfInterrupts++;

    Serial.print("Water Detected..");
    Serial.println(numberOfInterrupts);
  }else {
    checkInterrupt = false;
  }

}
