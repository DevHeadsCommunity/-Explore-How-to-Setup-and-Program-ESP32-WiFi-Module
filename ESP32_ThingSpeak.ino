#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" 

char ssid[] = SECRET_SSID;   
char pass[] = SECRET_PASS;   
int keyIndex = 0;            
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int lux = 0;

void setup() {
  Serial.begin(115200);  
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); 
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  lux = analogRead(34);  // LDR connected to Pin D34
  
  // Write to ThingSpeak
  int x = ThingSpeak.writeField(myChannelNumber, 1, lux, myWriteAPIKey);
  
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000); 
}
