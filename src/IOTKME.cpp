
#include "Arduino.h"
#include "IOTKME.h"
#include "ArduinoJson.h"
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

String IOTKME::SENDREQ(int v1,int v2,String autoremp,String temp,String relay ,String id)
{
    

}
void IOTKME::connect(String SSID, String PASS)
{
    
    delay(500);
int trytoconn=0;
 WiFi.begin(SSID, PASS);
  Serial.println("https://kmetechnology.com/");
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
void IOTKME::sendpush(int v1,int v2,int push ,String id)
{

 

}
void IOTKME::server()
{


 
 

}

void IOTKME::PUSHNOTI( )
{
 
  
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
	WiFi.softAP("adnan elabdullah", "aaaaaaaa");

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
String IOTKME::emptyeep()
{
      EEPROM.begin(512);

  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
   EEPROM.end();
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
String IOTKME::Kmegetvalue(String Value,String response)
{
  StaticJsonDocument<1024> doc;

DeserializationError error = deserializeJson(doc, response);

if (error)
{
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
 
}
 String root_0_temp = doc[0][Value]; 
return root_0_temp;
}
float IOTKME::Currency(String type)
{
   String my_char="";
 byte myArray[]  ={0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x61,0x70,0x69,0x61,0x70,0x70,0x73,0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x6C,0x65,0x72,0x2E,0x6B,0x6D,0x65,0x74,0x65,0x63,0x68,0x6E,0x6F,0x6C,0x6F,0x67,0x79,0x2E,0x63,0x6F,0x6D,0x2F,0x63,0x75,0x72,0x2E,0x70,0x68,0x70,0x3F,0x69,0x64,0x3D};
for(int i=0;i<=sizeof(myArray)-1;i++){
   my_char =my_char+ String((char)myArray[i] ); 
  }
  String serverName = my_char+type;

 WiFiClient client;
      HTTPClient http;
  http.begin(client, serverName.c_str());
      int code = http.GET();
      
      if (code>0) {
  
        String data = http.getString();
   
         StaticJsonDocument<1500> doc;

DeserializationError error = deserializeJson(doc, data);

if (error)
{
  Serial.print(F("type not found "));
  Serial.println(data);
}
 float root_0_temp = doc[0][type]; // "55"
 return root_0_temp;
      }
      else{

return 0;

      }
 

}
