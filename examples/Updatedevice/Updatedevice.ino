#include <IOTKME.h>
#define updatepin 4 
int relaypin=13;
const char* ss     = "wifissid";
const char* sp = "password";
IOTKME IOTKME(relaypin);
void setup() {
IOTKME.connect(ss,sp);
//rest device and press on update but for update your device
if(digitalRead(updatepin)==false){
IOTKME.recupdate("BIN FILE URL HERE");
}
}

void loop() {

}
