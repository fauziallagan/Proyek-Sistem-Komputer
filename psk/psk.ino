// ** Import Library ** //
#include "DHT.h"                // DHT Sensor
#include <ESP8266WiFi.h>        //EPS8266WIFI module library
#include <BlynkSimpleEsp8266.h> // Blynk library

// ** Connection to Blynk ** //
// IMPORTANT! PLEASE EDIT THIS VARIABLE BELOW
char auth[] = "iOmI-1Nom7_plCZikYn5Q5mvmTx06xMx"; // Auth blynk Account
// char authLocal[] = "M4XIeWMTxn1YffCaG1t-Lb33YZ7L-abg"; // auth local server  * Do not Use! *
char ssid[] = "allagan";        // SSID WIFI
char pass[] = "allagankingdom"; // Password WIFI

// ** Declaration Variabel Sensor ** //
DHT dht(D5, DHT22); // DHT instance named dht, D5 and sensor type

// Global Declaratio
int ldrSensors = A0; // LDR instance named ldrSensors, A0
int ldr;             // count LDR

// **  if relay ready, uncomment variabel below  ** //
#define relay1 D6 // relay module IN 1
#define relay2 D7 // relay module IN 2

void setup()
{
  Serial.begin(115200);          // serial boundrate 115200
  Blynk.begin(auth, ssid, pass); // Connecting to blynk
  // Blynk.begin(authLocal, ssid, pass, IPAddress(192, 168, 1, 110), 8080); //  blynk local server fix problem  * Do not Use! if not blynk local server *
  dht.begin(); // Starting  DHT-22
  // pinMode(ledTesting, OUTPUT);           // declare LED
  pinMode(relay1, OUTPUT); // set relay1 for output Kipas
  pinMode(relay2, OUTPUT); // set relay2 for output Lampu
}

void loop()
{
  Blynk.run();
  // dhtSensors(); // call function DHT
  //  ldrSensor();  // call function LDR
  sensorStarted(); //  100 milisecond
  delay(1000);
  //
  // ** Call Function Testing Component ** //
  // relaySensorTesting(); // use if relay not working!
  // dhtTesting();          // use if dht working!
  // ldrSensor(); // use if ldr not working!
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
  // statement :
  /*
jika temp kurang dari 21 derajat celcius maka lampu on dan kipas off
jika temp lebih dari 21 atau dibawah 28 maka lampu off kipas on
   */
  if (temp <= 21)
  {
    // Code here!
    digitalWrite(relay2, LOW);
    digitalWrite(relay1, HIGH);
    Serial.println("Lampu ON & kipas Off");
  }
  else if (temp <= 28)
  {
    // Code Here!
    digitalWrite(relay2, HIGH);
    //     digitalWrite(relay1, LOW);
    Serial.println("Lampu OFF & kipas On");
  }
  else if (temp == 255 || hum == 255)
  {
    Serial.println("Warning!. The Device Something Wrong!. Please checking the sensors!");
    Blynk.notify("Alat Tidak Bekerja");
  }
  else
  {
    Serial.println("Sensor bekerja");
  }
}

void relaySensorTesting()
{
  // Example Code Relay Here!
  digitalWrite(relay1, LOW); // Menyalakan relay Kipas
  Serial.println("LOW");
  delay(1000);               // Jeda 1 Detik
  digitalWrite(relay2, LOW); // Menyalakan relay lampu
  Serial.println("LOW");
}

void ldrSensor()
{
  //  Code LDR here!
  ldr = analogRead(ldrSensors);
  Blynk.virtualWrite(V2, ldr); // Set Virtual Pin 2 (V2) frequency to  in Blynk app
  Serial.print("LDR Value : ");
  Serial.println(ldr); // print variable nilai

  // Condition LDR
  if (ldr < 100)
  {
    //   over 500
    digitalWrite(relay2, HIGH);
    Serial.println("Fan OFF");
  }
  else if (ldr > 600)
  {
    //    under 500
    digitalWrite(relay2, LOW);

    Serial.println("Fan ON");
  }
}

void sensorStarted()
{
  byte hum = dht.readHumidity();     // temp and  are celsius and humidity readings
  byte temp = dht.readTemperature(); // from DHT/A

  if (temp <= 70 && ldrSensors <= 1000) // true or true = true
  {
    Serial.println("Alat Bekerja!");
    dhtSensors(); // call function dht

    ldrSensor(); // call function LDR
    Serial.println("\n=======================================================================\n");
    delay(100);
  }
  else
  {
    //  do nothing
  }
  while (temp == 100)
  {
    Serial.println("Peringatan!. Sensor DHT  :");
    Serial.print(temp);
  }
  Blynk.notify("Alat mengalami msaalah!, Sensor Tidak Bekerja");
  Serial.println("Sensor Tidak bekerja");
}

// ** TESTING Component ** //
// ** Use This function For Testing Component ** //

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
  ldr = analogRead(ldrSensors);
  ldr = ldr / 10;
  Serial.println(ldr); // print variable ldr
}
