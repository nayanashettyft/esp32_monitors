#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266Ping.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress graphiteip;

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
  WiFi.hostByName("GRAPHITE-SERVER", graphiteip);
  Serial.println("Graphite IP");
  Serial.println(graphiteip);
  timeClient.begin();
}

void loop()
{
  int success = 0;
  int rttmax = 0;
  int rttmin = -1;
  int rtttotal = 0;
  
  timeClient.update();
  unsigned long metric_time = timeClient.getEpochTime();
  Serial.println(metric_time);

  // Get the avg round trip time
  for (int i=0;i < 10;i++) {
    if (Ping.ping(remote_host)) {
      success++;
      int rtt = Ping.averageTime();
      if (rtt > rttmax) {
        rttmax = rtt;
      }
      if (rttmin == -1 or rtt < rttmin) {
        rttmin = rtt;
      }
      rtttotal += rtt;
      Serial.println("Success!!");
    } else {
      Serial.println("Error :(");
    }
  }

  int rttavg = -1;
  if (success > 0) {
    rttavg = int(rtttotal / success);
  }

  int loss = (10 - success) * 10;
  float rssi = WiFi.RSSI();

  Serial.println(success);
  Serial.println(rttavg);
  Serial.println(rttmin);
  Serial.println(rttmax);
  Serial.println(loss);
  Serial.println(rssi);

  delay(1000);
}
