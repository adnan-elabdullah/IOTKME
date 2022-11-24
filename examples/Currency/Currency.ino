#include <IOTKME.h>
#define updatepin 4 
int relaypin=13;

const char* ss     = "FiberHGW_TPC808_2.4GHz";
const char* sp = "rrpCj7XP";
IOTKME IOTKME(relaypin);
void setup() {
IOTKME.connect(ss,sp);
}
void loop() {
//rest device and press on update but for update your device
float usd=IOTKME.Currency("USD");
Serial.println(usd);
float KWD=IOTKME.Currency("KWD");
Serial.println(KWD);
}
