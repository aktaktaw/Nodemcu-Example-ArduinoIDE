//ESP8266 Deep Sleep + DHT 11 Temperature Sensor
#include <DHT.h>

float humid =0.0;
float temp= 0.0;
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(2000);
  
  //Wait for serial to initialize
  while(!Serial){}

  dht.begin();
  humid = dht.readHumidity();
  temp = dht.readTemperature();
  
  //Deep sleep for 30 sec
  Serial.print("\n DHT 11 Deep Sleep, \n Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humid);
  ESP.deepSleep(30e6);
}

void loop(){}
