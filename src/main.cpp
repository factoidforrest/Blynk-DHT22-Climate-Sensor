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
#define uS_TO_SECONDS_FACTOR 1000000  


#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "BLYNK CODE FROM THE EMAIL";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR NETWORK SSID"; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char pass[] = "YOUR PASSWORD";


DHTesp dht;
BlynkTimer timer;




void readClimate(){
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  int rssi = WiFi.RSSI();

  Blynk.virtualWrite(3, temperature);
  Blynk.virtualWrite(4, humidity);
  Blynk.virtualWrite(2, rssi);

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
  Serial.println("setup complete");
  Blynk.run();
  readClimate();
  Serial.println("GOING TO SLEEP");
  esp_sleep_enable_timer_wakeup(600 * uS_TO_SECONDS_FACTOR);
  esp_deep_sleep_start();
}

void loop()
{
  Serial.println("Reached Loop in error");
}