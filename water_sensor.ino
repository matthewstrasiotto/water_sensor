#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>
#include "consts.h"


#ifndef _SSID
#define _SSID "ENTER HERE"      // Your WiFi SSID
#endif

#ifndef _PASSWORD
#define _PASSWORD "ENTER HERE"  // Your WiFi Password
#endif

#ifndef KEY
#define KEY "ENTER HERE"        // Webhooks Key
#endif

#ifndef EVENT
#define EVENT "ENTER HERE"      // Webhooks Event Name
#endif

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
const int tenMinutes = 600;

int timer = 0;

// Between 0 - 1023
const int threshhold = 100;

Webhook webhook(KEY, EVENT);    // Create an object.

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  Serial.print("Using webhook: ");
  Serial.println(EVENT);
  Serial.print("With key: ");
  Serial.println(KEY);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

//================================================================//
//================================================================//




}

void loop() {

  delay(1000);
  
  int sensorValue = 0;

  sensorValue = analogRead(analogInPin);

  if ( timer > 0 ) {
    timer--;
    Serial.print("Waiting ");
    Serial.print(timer);
    Serial.println(" Seconds");

    return;
  } 

  if (sensorValue > threshhold) {
    timer = tenMinutes;
    // Trigger without any value and get response.
    int response = webhook.trigger();
    if(response == 200)
      Serial.println("OK");
     else
      Serial.println("Failed");
        
    }

  

  
  
}
