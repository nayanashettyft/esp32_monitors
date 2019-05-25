# ESP8266 NodeMCU monitors

This repo contains code and instructions to setup a ESP8266 NodeMCU for monitoring "things" using graphite and grafana.

## WifiMonitor

We use basic ESP8266 client, ping and ntpclient modules to ping google.com at regular intervals and sent the results to graphite. We then visualise the data on grafana.

Library documentation for usage: https://www.arduino.cc/en/Reference/Libraries