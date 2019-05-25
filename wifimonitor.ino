#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266Ping.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress address;

char* ssid = "<WIFI name>";
char* password = "<WIFI password>";
const char* remote_host = "www.google.com";
unsigned int remotePort = 2003;  //graphite server port
unsigned int localPort = 2003;

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
  WiFi.hostByName("GRAPHITE-SERVER", address);
  Serial.println("Host IP");
  Serial.println(address);
  timeClient.begin();
}

void loop()
{
  timeClient.update();
  unsigned long metric_time = timeClient.getEpochTime();
  Serial.println(metric_time);
  
  Serial.println("Pinging host ");
  Serial.println(remote_host);
  if(Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }

  delay(1000);
}
