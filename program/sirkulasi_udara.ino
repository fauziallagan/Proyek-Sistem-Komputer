// ** Import Library ** //
#include "DHT.h"                // DHT Sensor
#include <ESP8266WiFi.h>        //EPS8266WIFI module library
#include <BlynkSimpleEsp8266.h> // Blynk library

// ** Connection to Blynk ** //
// IMPORTANT! PLEASE EDIT THIS VARIABLE BELOW
char auth[] = "YOUR AUTHENTICATION BLYNK"; // Auth blynk Account
// char authLocal[] = "YOUR AUTHENTICATION BLYNK FOR LOCAL SERVER"; // auth local server  * Do not Use! this Experimental *
char ssid[] = "YOUR SSID WIFI";        // SSID WIFI
char pass[] = "YOUR PASSWORD WIFI"; // Password WIFI

// ** Declaration Variabel Sensor ** //
DHT dht(D5, DHT22); // DHT instance named dht, D5 and sensor type
// Global Declaration
int ldrSensors = A0; // LDR instance named ldrSensors, A0
int nilai;           // count LDR

// **  if relay ready, uncomment variabel below  ** //
#define relay1 D6 // relay module IN 1
#define relay2 D7 // relay module IN 2

void setup()
{
  Serial.begin(115200);          // serial boundrate 115200
  Blynk.begin(auth, ssid, pass); // Connecting to blynk
  // Blynk.begin(authLocal, IPAddress(192,168,1,9), 8080); //  blynk local server * Do not Use! *
  dht.begin(); // Starting  DHT-22
  // pinMode(ledTesting, OUTPUT);              // declare LED
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop()
{
  Blynk.run();
  dhtSensors(); // call function DHT
  ldrSensor();  // call function LDR
  delay(100);
  decisionSensors(); //  100 milisecond

  // ** Call Function Testing Component ** //
  // relaySensorTesting();  // use if relay not working!
  // dhtTesting();          // use if dht working!
  // ldrTesting();          // use if ldr not working!
}

void dhtSensors()
{
  byte hum = dht.readHumidity();     // temp and  are celsius and humidity readings
  byte temp = dht.readTemperature(); // from DHT/A

  Blynk.virtualWrite(V0, temp); //  Set Virtual Pin 0 (V0) frequency to in Blynk app
  Blynk.virtualWrite(V1, hum);  //  Set Virtual Pin 1 (V1)frequency to  in Blynk app
  Serial.print("Temperature  : ");
  Serial.println(temp);
  Serial.print("Humadity  : ");
  Serial.println(hum);

  // ** example statement
  // Condition DHT
  // if(hum >= ... && temp >= ...){
  //   // Code here!
  // }else if(hum <= ... && temp <= ...){
  //   // Code Here!

  // }else{
  //   Serial.println("Sensor DHT Not Detected!");
  //   digitalWrite(relay1, LOW);
  //   digitalWrite(relay2, LOW);
  // }
}

void ldrSensor()
{
  //  Code LDR here!
  nilai = analogRead(ldrSensors);
  Blynk.virtualWrite(V2, nilai); // Set Virtual Pin 2 (V2) frequency to  in Blynk app
  Serial.println(nilai);         // print variable nilai

  // Condition LDR
  if (nilai >= 500)
  {
    //   over 500
    digitalWrite(relay1, HIGH);
    Serial.println("Fan ON");
  }
  else if (nilai <= 500)
  {
    //    under 500
    digitalWrite(relay1, LOW);
    Serial.println("Fan OFF");
  }
  else
  {
    Serial.println("LDR Not Detected!");
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }
}

void decisionSensors()
{
  byte hum = dht.readHumidity();     // temp and  are celsius and humidity readings
  byte temp = dht.readTemperature(); // from DHT/A

  if (hum >= 80 && temp >= 30 || ldrSensors >= 1000)
  {
    Blynk.notify("LED ON && Fan ON");
    Serial.println("Alat Bekerja!");
    dhtSensors(); // call function dht
    ldrSensor();  // call function LDR
    delay(10000);
  }
  if (hum >= 100 || temp >= 100 || ldrSensors >= 1024)
  {
    Blynk.notify("Peringatan!. Sensor Tidak Sedang Baik Baik Saja");
    dhtSensors(); // call function dht
    ldrSensor();  // call function LDR
    delay(100);
    if (temp > 100)
    {
      Blynk.notify("Masalah pada Sensor DHT bagian temperatur");
      Serial.println("Masalah pada Sensor DHT bagian temperatur");
      dhtSensors(); // call function dht
      ldrSensor();  // call function LDR
    }
    else if (hum > 100)
    {
      Blynk.notify("Masalah pada Sensor DHT bagian humadity");
      Serial.println("Masalah pada Sensor DHT bagian humadity");
      dhtSensors(); // call function dht
      ldrSensor();  // call function LDR
    }
    else if (ldrSensors >= 1024)
    {
      Blynk.notify("Masalah pada Sensor LDR");
      Serial.println("Masalah Pada Sensor LDR");
      dhtSensors(); // call function dht
      ldrSensor();  // call function LDR
    }
  }
  else
  {
    // Blynk.notify("Device not Working");
  }
}

// ** TESTING Component ** //
// ** Use This function For Testing Component ** //

void relaySensorTesting()
{
  // Example Code Relay Here!
  digitalWrite(relay1, HIGH); // Menyalakan relay
  delay(1000);                // Jeda 1 Detik
  digitalWrite(relay1, LOW);
  delay(1000);
  digitalWrite(relay2, HIGH);
  delay(1000);
  digitalWrite(relay2, LOW);
}

void dhtTesting()
{
  byte hum = dht.readHumidity();     // temp and  are celsius and humidity readings
  byte temp = dht.readTemperature(); // from DHT/A

  Serial.print("Temperature  : ");
  Serial.println(temp);
  Serial.print("Humadity  : ");
  Serial.println(hum);
}

void ldrTesting()
{
  nilai = analogRead(ldrSensors);
  nilai = nilai / 10;
  Serial.println(nilai); // print variable nilai
}