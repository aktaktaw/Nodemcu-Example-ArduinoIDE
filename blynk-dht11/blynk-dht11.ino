#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h> https://github.com/blynkkk/blynk-library
#include <ESP8266WiFi.h>
#include <SimpleTimer.h> https://github.com/jfturcot/SimpleTimer
#include <DHT.h>


//WiFi & Blynk Configuration
const char* ssid ="your_ssid";
const char* pswd = "your_ssid_password";
const char* auth = "your_blynk_auth";

#define DHTPIN D7
//#define DHTTYPE DHT22 //for sensor dht22
#define DHTTYPE DHT11 //for sensor dht11


DHT dht(DHTPIN, DHTTYPE);
float temperature, humidity;

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pswd);
  dht.begin();
}

void loop(){
  Blynk.run();
  readSensor();
  delay(5000);
}

void readSensor(){
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.print("Humidity = ");
  Serial.println(humidity);
}
