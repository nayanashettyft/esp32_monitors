#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266Ping.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress graphiteIP;
WiFiUDP Udp;
WiFiClient client;

char* ssid = "<WIFI name>";
char* password = "<WIFI password>";
const char* remote_host = "www.google.com";
const char* graphiteHost = "GRAPHITE-SERVER FQDN"
unsigned int graphitePort = 2003;  //graphite server port
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

  send_metrics("UUID.ping.avg", rttavg, metric_time);
  send_metrics("UUID.ping.min", rttmin, metric_time);
  send_metrics("UUID.ping.max", rttmax, metric_time);
  send_metrics("UUID.ping.loss", loss, metric_time);
  send_metrics("UUID.ping.rssi", rssi, metric_time);

  delay(5000);
}

void send_metrics(const char* metric, const int value, const unsigned long timestamp) {
  if (client.connect(graphiteHost, graphitePort)) {
    Serial.println("connected");
    // Send metrics:
    client.print(metric);
    client.write(" ");
    client.print(value);
    client.write(" ");
    client.println(timestamp);
  }
  else{
    Serial.println("Error :(");
  }

  Serial.print(metric);
  Serial.write(" ");
  Serial.print(value);
  Serial.write(" ");
  Serial.println(timestamp);
}