#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//WiFi Setup 
const char* ssid="ungkunor66@unifi";
const char* pswd="awan9135";

const char* mqtt_server="192.168.0.14";
#define mqtt_port 1883

const int vSensor=13;
const int led=5;
long measurement;
long now = millis();
long lastMeasure=0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi(){
  delay(10);
  WiFi.begin(ssid,pswd);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
}

void mqtt_conn(){
  Serial.print("Attempting MQTT Connection");
  if(client.connect("ESP8266Client")){
    Serial.println("MQTT Connected");
  }
  else{
    Serial.print("MQTT Connection failed, rc=");
    Serial.print(client.state());
    Serial.println("Reconnect in 5 seconds");
    delay(5000);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);
  pinMode(vSensor,INPUT);
  pinMode(led,OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server,mqtt_port);
  Serial.println("Vibartion Measurement: ");
}

void loop() {
  if(!client.connected()){
    mqtt_conn();
  }

  if(!client.loop())
    client.connect("ESP8266Client");


  now=millis();
  if(now-lastMeasure>10000){
    measurement=TP_init();
    if(measurement>1000){
      //Serial.println(measurement);
      digitalWrite(led,HIGH);
    }
    else{
      digitalWrite(led,LOW);
    }

    if(isnan(measurement)){
      Serial.println("Failed to read sensor");
      return;
    }
  }

  static char vibrationTemp[7];
  dtostrf(measurement, 6, 2, vibrationTemp);
  client.publish("sensor1/vibration",vibrationTemp);

  Serial.print("Vibration occured, ");
  Serial.println(measurement);
  delay(3000);
  
}

long TP_init(){
  delay(10);
  long measurement = pulseIn(vSensor,HIGH);
  return measurement;
}
