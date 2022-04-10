 #include "DHT.h"                              // DHT Sensor
 #include <ESP8266WiFi.h>           //EPS8266WIFI module library
 #include <BlynkSimpleEsp8266.h>    // Blynk library

char auth[] = "iOmI-1Nom7_plCZikYn5Q5mvmTx06xMx"; // Auth blynk Account 
char ssid[] = "allagan";  // SSID WIFI
char pass[] = "allagankingdom"; // Password WIFI
DHT dht(D5, DHT22);                           // DHT instance named dht, D5 and sensor type

// Global Declaration
int ldrSensors = A0;                          // LDR instance named ldr, A0
int ledTesting = D6;          // declare LED for testing
int nilai;  // count LDR

/*
//if relay ready, uncomment variabel below
int relay1 = D6;  //relay module IN 1
int relay2 = D7;  // relay module IN 2
*/

void setup() {
  Serial.begin(115200);                       //serial boundrate 115200
  Blynk.begin(auth, ssid, pass);              // Connecting to blynk
  dht.begin();                               // Starting  DHT-22
  pinMode(ledTesting, OUTPUT);              // declare LED
}

void loop() {
  Blynk.run();
  dhtSensors();                           // manggil fungsi dht
  ldrSensor();                            // manggil fungsi LDR
  delay(100);                                //  100 milisecond
}

void dhtSensors() {
    byte hum = dht.readHumidity();            // f1 and h1 are celsius and humidity readings
    // byte t1 = dhtA.readTemperature(true);  // for temperature in farenheits
    byte temp = dht.readTemperature();         // from DHT/A
    Blynk.virtualWrite(V0, temp);               //  Set Virtual Pin 0 (V0) frequency to in Blynk app
    Blynk.virtualWrite(V1, hum);               //  Set Virtual Pin 1 (V1)frequency to  in Blynk app
}

void ldrSensor(){
//  Code LDR here!
  nilai =  analogRead(ldrSensors);
  Blynk.virtualWrite(V2, nilai); //Set Virtual Pin 2 (V2) frequency to  in Blynk app
  Serial.println(nilai); //print variable nilai

  // Condition LDR
  if(nilai > 500){
//   over 500 
  digitalWrite(ledTesting, HIGH);
  }else{
//    under 500
  digitalWrite(ledTesting, LOW);
  }
}

void relaySensor(){
  // Code Relay Here!
}