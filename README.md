# ESP8266 NodeMCU monitors

This repo contains code and instructions to setup a ESP8266 NodeMCU for monitoring "things" using graphite and grafana.

## WifiMonitor

We use basic ESP8266 client, ping and ntpclient modules to ping google.com at regular intervals and sent the results to graphite. We then visualise the data on grafana.

## Referance documentation

* Use https://learn.acrobotic.com/tutorials/post/esp8266-getting-started if you are new to programming with ardino and ESP8266
* https://www.youtube.com/watch?v=m2fEXhl70OY this video is also a good 1 to try before going off on your own
* Library documentation for usage: https://www.arduino.cc/en/Reference/Libraries