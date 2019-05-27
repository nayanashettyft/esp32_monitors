# ESP8266 NodeMCU monitors

This repo contains code and instructions to setup a ESP8266 NodeMCU for monitoring "things" using graphite and grafana.

## WifiMonitor

We use basic ESP8266 client, ping and ntpclient modules to ping `google.com` at regular intervals and send the results to `graphite`. We then visualise the data on `grafana`.

## WeightMonitor

We use a `load cell`, `HX711 load cell amplifier` and a `ESP8266 NodeMCU` for measuring the weight of a "thing". We then use the ESP8266 client to connect to a graphite server and send the weight of the "thing" to `graphite`. Alerts and visualisation is on `grafana`.

## Referance documentation

* Use https://learn.acrobotic.com/tutorials/post/esp8266-getting-started if you are new to programming with ardino and ESP8266
* https://www.youtube.com/watch?v=m2fEXhl70OY this video is also a good 1 to try before going off on your own
* ESP8266 spec and installation details https://www.handsontec.com/pdf_learn/esp8266-V10.pdf
* Library documentation for usage: https://www.arduino.cc/en/Reference/Libraries
* To buy a ESP8266, https://www.amazon.co.uk/HiLetgo-Internet-Development-Wireless-Micropython/dp/B0791FJB62/ref=sr_1_3?crid=OLIBHT3YPAYW&keywords=esp8266+nodemcu&qid=1558790100&s=gateway&sprefix=esp8266%2Caps%2C145&sr=8-3
* To buy a load cell and HX711, https://www.amazon.co.uk/Innovateking-EU-Converter-Breakout-Portable-Electronic/dp/B07GRGT3C3/ref=sr_1_5?crid=12QVGUFAB0E52&keywords=weight+sensor&qid=1558724401&s=gateway&sprefix=weight+senso%2Caps%2C137&sr=8-5
