#include <ESP8266WiFi.h> //library Wifi NodeMCU ESP8266
#include <WiFiClient.h> //library client
#include <DHT.h> //library DHT
#include <ThingSpeak.h> //library platform thingspeak

#define DHTPIN D5 // mendefinisikan pin 0 sebagai pin DHT
#define DHTTYPE DHT22 //mendefinisikan type dari DHT
DHT dht(DHTPIN, DHTTYPE); //mengatur pin DHT dan type DHT

const char *ssid = "allagan"; //setting nama wifi router
const char *password = "allagankingdom"; //password wifi router
WiFiClient client; //mengecek jika client sudah terhubung

unsigned long myChannelNumber = 1705247; //ID akun ThingSpeak
const char * myWriteAPIKey = "4GGBII6CV5VB88Z3"; //memasukan apikey
uint8_t temperature, humidity; //temperature dan humidity dengan tipe unsigned 8-bit.

void setup() {
  Serial.begin(115200); //memulai komunikasi serial dengan baud rate 115200
  dht.begin(); //memulai sensor DHT.
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //menghubungkan dengan wifi router
  while (WiFi.status() != WL_CONNECTED) //Cek koneksi Wifi.
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client); //melakukan inisialisasi ke thingspeak
}

void loop()
{
  temperature = dht.readTemperature(); //membaca suhu pada sensor DHT11
  humidity = dht.readHumidity(); //membaca kelembaban sensor DHT11
  Serial.print("Temperature Value is :");
  Serial.print(temperature);
  Serial.println("C");

  Serial.print("Humidity Value is :");
  Serial.print(humidity);
  Serial.println("%");
  
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey); 
  //data akan tampilkan pada thingspeak sesuai dengan akun yang dihubungkan
  delay(1000);
}