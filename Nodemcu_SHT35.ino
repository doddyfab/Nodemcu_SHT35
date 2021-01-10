/*
  Sonde de température connectée pour piscine
  avec : 
     - NodeMCU
     - SHT35

 Cablage DS18B20 :
 VCC - 3V
 GND - GND 
 i2c DATA - D2
 i2c CLOCK - D1

  
  Source :     https://www.sla99.fr
  Date : 2021-01-10

  Changelog : 
  10/01/2020  v1    version initiale

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <WEMOS_SHT3X.h>

SHT3X sht30(0x44);
/*
#include <Adafruit_SHT31.h>

Adafruit_SHT31 sht31 = Adafruit_SHT31(); 
*/

const char* ssid = "RIBOTRAIN";
const char* password = "1598741230";
char server[] = "192.168.1.2";  
WiFiClient client;
String KEY_WS="134567654345670012";



void setup() {
  Serial.begin(9600);
    delay(10);
   
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());   
  Serial.println(WiFi.macAddress());
 
  //démarrage SHT35
  /*
  if (! sht31.begin(0x44)) { 
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }*/
  if(sht30.get()==0){
    double temp = sht30.cTemp;
    Serial.print("Temperature in Celsius : ");
    Serial.println(temp);
    double hum = sht30.humidity;
    Serial.print("Relative Humidity : ");
    Serial.println(hum);
    Serial.println();
  
  
 /*
  double temp = sht31.readTemperature();
  double hum = sht31.readHumidity();
  Serial.print("Temp : ");
  Serial.println(temp);
  Serial.print("Hum : ");
  Serial.println(hum);*/

  String url = "/stationmeteo/sht35.php?key="+KEY_WS+"&temp="+String(temp)+"&hum="+String(hum);
 
  HTTPClient http;  
  String Link = "http://192.168.1.2:81"+url;
   
  http.begin(Link); 
   
  int httpCode = http.GET();          
  String payload = http.getString();  
  
  Serial.println(httpCode);   
  Serial.println(payload);  
  
  http.end(); 
  }
  else
  {
    Serial.println("Error!");
  }
   
  Serial.println("Going into deep sleep for 60 seconds");
  ESP.deepSleep(60e6); 
  }
  
void loop() {


}
