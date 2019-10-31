/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can send/receive any data using WidgetTerminal object.

  App project setup:
    Terminal widget attached to Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial



#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YOUR BLYNK KEY FROM THE EMAIL";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR SSID"; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char pass[] = "YOUR WIFI PASSWORD";


DHTesp dht;
BlynkTimer timer;



BLYNK_READ(V2)
{
  int rssi = WiFi.RSSI();
  Blynk.virtualWrite(2, rssi);
}

void readClimate(){
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Blynk.virtualWrite(3, temperature);
  Blynk.virtualWrite(4, humidity);
  Serial.print(dht.getStatusString());
  Serial.println("temperature is ");
  Serial.println(temperature);
  Serial.print("Humidity is ");
  Serial.println(humidity);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Serial.println("init");
  Blynk.begin(auth, ssid, pass);

  dht.setup(4, DHTesp::DHT22);
  timer.setInterval(5000, readClimate);
  Serial.println("setup complete");
}

void loop()
{
  Blynk.run();
  timer.run();
}