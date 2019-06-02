#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <HX711_ADC.h>
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress graphiteIP;
WiFiClient client;

#define EAP_IDENTITY "usename" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_PASSWORD "password" //your Eduroam password
const char* ssid = "lanID"; // Eduroam SSID
int counter = 0;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 23;
const int LOADCELL_SCK_PIN = 22;
HX711_ADC LoadCell(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

unsigned int remotePort = 2003;  //graphite server port
unsigned int localPort = 2003;
const char* graphiteHost = "GRAPHITE-SERVER";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  
  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
  esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
  WiFi.begin(ssid); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: "); 
  Serial.println(WiFi.localIP()); //print LAN IP
  
  timeClient.begin();

  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(200.0); // calibration factor for load cell
}

void loop() {
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
