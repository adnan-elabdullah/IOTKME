/*
  IOTKME.h - Library for flashing IOTKME code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef IOTKME_h
#define IOTKME_h
#include "ArduinoJson.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Arduino.h"
#include <ESP8266WiFiMulti.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>

class IOTKME
{
  public:
    IOTKME(int pin);
        void connect(String SSID, String PASS);
       void server();
              void recupdate(String url);
              void EepromWifi( String pass, String ssid  );
            void Servermode();
            String WifiPass();
            String WifiSsid();
            String Deviceid();
 String Kmegetvalue(String Value,String response);

  private:
    int _pin;
};

#endif