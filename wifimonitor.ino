#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266Ping.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
char* ssid = "<WIFI address>";
char* password = "<WIFI password>";
const char* remote_host = "www.google.com";

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to WiFI");
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Pinging host ");
  Serial.println(remote_host);
  if(Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
  timeClient.begin();
}

void loop()
{
  timeClient.update();
    Serial.println("Pinging host ");
  Serial.println(remote_host);
  if(Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
  
  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
