#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266Ping.h>
#include <HX711_ADC.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress graphiteIP;
WiFiClient client;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D2;
const int LOADCELL_SCK_PIN = D3;
HX711_ADC LoadCell(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

char* ssid = "<WIFI name>";
char* password = "<WIFI password>";
unsigned int remotePort = 2003;  //graphite server port
unsigned int localPort = 2003;
const char* graphiteHost = "GRAPHITE-SERVER FQDN"

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

  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(402.0); // calibration factor for load cell => strongly dependent on your individual setup
}

void loop()
{
  int success = 0;
  
  timeClient.update();
  unsigned long metric_time = timeClient.getEpochTime();
  Serial.println(metric_time);
  
  LoadCell.update(); // retrieves data from the load cell
  long reading = LoadCell.getData(); // get output value
  Serial.print("HX711 reading: ");
  Serial.println(reading);
  
  //send data to graphite
  send_metrics_client("biscuit-tin.weight", reading, metric_time);
  delay(5000);
  
}

void send_metrics_client(const char* metric, const int value, const unsigned long timestamp) {
 if (client.connect(graphiteHost, remotePort)) {
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