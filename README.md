# ESP8266 NodeMCU monitors

This repo contains code and instructions to setup a ESP8266 NodeMCU for monitoring "things" using graphite and grafana.

## WifiMonitor

We use basic ESP8266 client, ping and ntpclient modules to ping `google.com` at regular intervals and send the results to `graphite`. We then visualise the data on `grafana`.

## WeightMonitor

We use a load cell, HX711 load cell amplifier and a ESP8266 for the measuring the height of a "thing". We then use the ESP8266 client to connect to a graphite server and send the weight of the "thing" to graphite. Alerts and visualisation is on grafana.

## Referance documentation

* Use https://learn.acrobotic.com/tutorials/post/esp8266-getting-started if you are new to programming with ardino and ESP8266
* https://www.youtube.com/watch?v=m2fEXhl70OY this video is also a good 1 to try before going off on your own
* ESP8266 spec and installation details https://www.handsontec.com/pdf_learn/esp8266-V10.pdf
* Library documentation for usage: https://www.arduino.cc/en/Reference/Libraries