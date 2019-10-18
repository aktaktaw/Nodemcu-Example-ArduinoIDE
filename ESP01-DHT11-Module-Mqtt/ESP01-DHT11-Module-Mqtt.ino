#include <DHT.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//WiFi Setup
const char* ssid="Tertiary";
const char* pswd="tertiary888";

//MQTT Server
const char* mqtt_server="192.168.0.163";
const int mqtt_port=1883;

//Init value
float humid, temp;

//Timer var
long now=millis();
long lastMeasure=0;

//Define DHT Sensor
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi(){
  delay(10);
  WiFi.begin(ssid,pswd);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void mqtt_connect(){
  Serial.println("Attempting MQTT Connection");
  if(client.connect("ESP8266Client")){
    Serial.println("MQTT Connected");
  }
  else{
    Serial.print("MQTT Connection failed, rc=");
    Serial.print(client.state());
    Serial.println("Reconnect in 5s");
    delay(5000);
  }
}

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  dht.begin();
}

void loop(){
  if(!client.connected()){
    mqtt_connect();
  }

  if(!client.loop())
    client.connect("ESPClient8266");


  now= millis();
  if(now -lastMeasure > 10000){
    humid = dht.readHumidity();
    temp = dht.readTemperature();

    if(isnan(humid) || isnan(temp)){
      Serial.println("Failed to read sensor");
      client.publish("/sensor1/readSensor", "Failed to read sensor");
    }

  static char temperatureTemp[7];
  dtostrf(temp, 6, 2, temperatureTemp);

  static char humidityTemp[7];
  dtostrf(humid, 6, 2, humidityTemp);

  client.publish("/sensor1/temperature", temperatureTemp);
  client.publish("/sensor1/humidity", humidityTemp);

  Serial.print("Temp/Humid: ");
  Serial.print(temp);
  Serial.print(" / ");
  Serial.println(humid);

  delay(3000);
  }
}
