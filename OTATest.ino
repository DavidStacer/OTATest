// Very simple program to test Homie OTA updates.

#include <Homie.h>
const int INTERVAL = 20;  
unsigned long lastTimeSent = 0;
int count = 0;        // change the default value so you can see that the program updated.

HomieNode NotifyNode("Count", "level");

void loopHandler() {
    if (millis() - lastTimeSent >= INTERVAL * 1000UL || lastTimeSent == 0 ) {
       Homie.setNodeProperty(NotifyNode, "Count", String(count), true);     // just something to send to show activity
       Serial.print("Sending count: ");Serial.println(count);
       count++;
       lastTimeSent = millis();
    }

}

void setup() {
     Homie.setLedPin(2, HIGH); // before Homie.setup(); -- 2nd param is the state when the LED is on
     Homie.setFirmware("OTATest", "1.0.0");     // program name and version  OTA bin file muse be OTAT-1.0.0.bin   
     Homie.enableLogging(true);
     delay(50);    // if you have a Wemous D1-mini to keep it from going into configu mode on reboot
     Homie.setLoopFunction(loopHandler);
     Homie.setup();
     byte mac[6];                     // the MAC address of your Wifi - needed for server script
     WiFi.macAddress(mac);
     Serial.print("MAC: ");
     Serial.print(mac[0],HEX);Serial.print(":");Serial.print(mac[1],HEX);Serial.print(":");Serial.print(mac[2],HEX);Serial.print(":");Serial.print(mac[3],HEX);
     Serial.print(":");Serial.print(mac[4],HEX);  Serial.print(":");  Serial.println(mac[5],HEX);
}

void loop() {
  Homie.loop();
}
