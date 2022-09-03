
#include "Arduino.h"
#include "IOTKME.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <ESP8266WiFiMulti.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>
#define locationcountid 302
#define locationcountpass 301
#define locationcountssid 300
IOTKME::IOTKME(int pin)
{
  pinMode(pin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

  _pin = pin;
    Serial.begin(115200);


}


void IOTKME::connect(String SSID, String PASS)
{
      Serial.println("Please upgrade the firmware");
    delay(500);
int trytoconn=0;
 WiFi.begin(SSID, PASS);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
trytoconn++;
if(trytoconn>=30){
return;
}
  }
  Serial.println("connected");
 

}

void IOTKME::server()
{
/*   IPAddress    apIP(42, 42, 42, 42); 

  ESP8266WebServer serverb(80);

   WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  /* WiFi.softAP("a", "aaaaaaaa");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP); */

 
 

}


void rootsend() {
IPAddress    apIP(42, 42, 42, 42);  
ESP8266WebServer server(80);
    EEPROM.begin(512);
char charBuf[100];
  char charBuf2[100];
  char charBuf3[100];

int tp;
int ts;
int ti;
String passeep="";
String ssideep="";
String ideep="";
int a;
  digitalWrite (LED_BUILTIN, 0); 
delay(500);
    digitalWrite (LED_BUILTIN, 1); 
delay(500);
    digitalWrite (LED_BUILTIN, 0); 
delay(500);
    digitalWrite (LED_BUILTIN, 1); 
delay(500);
  String ssidt=server.arg("ssid");
String passt=server.arg("pass");
String id=server.arg("id");

Serial.println(passt);
Serial.println(ssidt);
Serial.println(id);

  ts=ssidt.length();

    tp=passt.length();
        ti=id.length();

    EEPROM.write(locationcountssid, ts);
    EEPROM.write(locationcountpass,tp);
    EEPROM.write(locationcountid,ti);

   passt.toCharArray(charBuf, 100);
   ssidt.toCharArray(charBuf2, 100);
   id.toCharArray(charBuf3, 100);
  Serial.println();

for( a=0;a<=tp;a++){
    EEPROM.write(a, charBuf[a]);

  }
  for( a=60;a<=60+ts;a++){
    EEPROM.write(a,charBuf2[a-60]);

  }
   for( a=130;a<=130+ti;a++){
    EEPROM.write(a,charBuf3[a-130]);

  }
    EEPROM.commit(); 
   
  }
void update_started() {
  Serial.println("KMEIOT DEVICE:   START");
}

void update_finished() {
  Serial.println("KMEIOT DEVICE:  upload finished");
}

void update_progress(int cur, int total) {
  Serial.printf("KMEIOT DEVICE:  upload process at %d of %d bytes...\n", cur, total);
}

void update_error(int err) {
  Serial.printf("KMEIOT DEVICE:  upload fatal error code %d\n", err);
}
void IOTKME::recupdate(String url )
{
  ESP8266WiFiMulti WiFiMulti;

  
 if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

   
    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

    // Add optional callback notifiers
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);

    t_httpUpdate_return ret = ESPhttpUpdate.update(client, url);
    // Or:
    //t_httpUpdate_return ret = ESPhttpUpdate.update(client, "server", 80, "file.bin");

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
  }
  
  }
  void IOTKME::Servermode( )
{
 IPAddress    apIP(42, 42, 42, 42);  
ESP8266WebServer server(80);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
	
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP("adnan", "aaaaaaaa");

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
  server.on ( "/",rootsend);
	server.begin();
	Serial.println("HTTP server started");
  while(1){server.handleClient();}


}
void IOTKME::EepromWifi( String passt, String ssidt)
{
    EEPROM.begin(512);

  int relaypin=13,ts,tp,ti;
char charBuf[100];
char charBuf2[100];
char charBuf3[100];

String passeep="";
String ssideep="";
String ideep="";
int a;
 Serial.println(passt);
  Serial.println(ssidt);

  ts=ssidt.length();

    tp=passt.length();

    EEPROM.write(locationcountssid, ts);
    EEPROM.write(locationcountpass,tp);

   passt.toCharArray(charBuf, 100);
   ssidt.toCharArray(charBuf2, 100);

for( a=0;a<=tp;a++){
    EEPROM.write(a, charBuf[a]);

  }
  for( a=60;a<=60+ts;a++){
    EEPROM.write(a,charBuf2[a-60]);

  }
 
    EEPROM.commit();


}
String IOTKME::WifiPass()
{
      EEPROM.begin(512);

 int a=0;
    String passeep="";

  for(a=0;a<=EEPROM.read(locationcountpass);a++){

  //Serial.print(char(EEPROM.read(a)));
 passeep=passeep+char(EEPROM.read(a));
    }
return passeep;
}
String IOTKME::WifiSsid()
{
      EEPROM.begin(512);

   int a=0;
  String ssideep="";
 for(int t=0;t<=EEPROM.read(locationcountssid);t++){
a=60+t;
 //Serial.print(char(EEPROM.read(a)));
  ssideep=ssideep+char(EEPROM.read(a));

   }


return ssideep;
}
String IOTKME::Deviceid()
{
      EEPROM.begin(512);

  int a=0;
  String ideep="";
 for(int t=0;t<=EEPROM.read(locationcountid);t++){
a=130+t;
// Serial.print(char(EEPROM.read(a)));
  ideep=ideep+char(EEPROM.read(a));

   }
  
return ideep;
}