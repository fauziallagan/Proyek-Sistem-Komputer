
# Proyek Sistem Komputer Universitas Gunadarma

"Sistem Parameter Lingkungan Tanaman Cabai Pada Rumah Kaca Dan Notifikasi Kerusakan Dini Berbasis IoT"


## Documentation

#### NodeMCU ESP-8266

```http
  -
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `-` | `-` | - |
#### Sensor LDR Pinout

```C++
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
```

| Parameter | Type     | Description                       |
| :-------- | :------- | :-------------------------------- |
| `-`      | `-` | - |


#### Sensor DHT Pinout

```c++
  DHT dht(D5, DHT22);
  int ldrSensors = A0;           // LDR instance named ldr, A0
  int ledTesting = D6;          // declare LED for testing
  int nilai;                   // count LDR
```

| Parameter | Description                |
| :-------- | :------------------------- |
| `DHT` |dht(pin,type)|


#### Get all items

```http
  -
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `-` | `-` | - |
