
#include <DHT.h> //library DHT


#define DHTPIN D5 // mendefinisikan pin 0 sebagai pin DHT
#define DHTTYPE DHT22 //mendefinisikan type dari DHT
DHT dht(DHTPIN, DHTTYPE); //mengatur pin DHT dan type DHT



// Global Variable
int count;
float suhu,dingin,sejuk,normal,panas,sangatPanas,uMember,sangatSedikit,sedikit,sedang,banyak,sangatBanyak,N_suhu[5], N_orang[5],kondisiSuhu, kondisiOrang, Min[25], Keluaran;
String OutputFuzzy;


void setup() {
  Serial.begin(115200); //memulai komunikasi serial dengan baud rate 115200
  dht.begin(); //memulai sensor DHT.
  

  // fuzzy
  temp();
}

void loop()
{

 
  fuzzyfi();
  defuzzifikasi();
  Output();
  delay(1000);

  // fuzzy
  
}
float temp(){
  float temperature = dht.readTemperature(); //membaca suhu pada sensor DHT11
  float hum = dht.readHumidity(); //membaca kelembaban sensor DHT11
  if(isnan(temperature)&& isnan(hum)){
    Serial.println("Failed To read DHT Sensors");
  }else{
    Serial.print("temp : ");
    Serial.println(temperature);
    Serial.print("hum : ");
    Serial.println(hum);
  }
  return temperature, hum;
}
void hitungMember(int pilih, float Nilai, float A, float B,float C){
  switch (pilih)
  {
  case 1:
    if((Nilai >= A) &&(Nilai <= B)) uMember = 1;
    if((Nilai > B)&&(Nilai < C)) uMember = 1;
    if(Nilai >= C) uMember = 0;
    break;
  case 2:
    if ((Nilai <= A)||(Nilai >= C)) uMember = 0;
    if ((Nilai > A)&&(Nilai <B)) uMember= (Nilai - A)/(B-A);
    if ((Nilai > B)&&(Nilai < C))uMember=(C - Nilai)/(C-B);
    if(Nilai == B) uMember = 1;
    break;
   case 3:
      if (Nilai <= A) uMember = 0;
      if ((Nilai > A) && (Nilai < B)) uMember = (Nilai - A) / (B - A);
      if (Nilai >= B) uMember = 1;    
  default:
    break;
  }

}

void fuzzyfi(){
  uMember = 0;
  hitungMember(1, temp(), 0, 24, 26);
  dingin = uMember;
  hitungMember(2, temp(), 24, 26, 29);
  sejuk = uMember;
  hitungMember(2, temp(), 26, 29, 32);
  normal = uMember;
  hitungMember(2, temp(), 29, 32, 35);
  panas = uMember;
  hitungMember(3, temp(), 32, 35, 35);
  sangatPanas = uMember;

  // Some People
  uMember = 0;
  hitungMember(1, count, 0, 5, 10);
  sangatSedikit = uMember;
  hitungMember(2, count, 5, 10, 20);
  sedikit = uMember;
  hitungMember(2, count, 10, 20, 30);
  sedang = uMember;
  hitungMember(2, count, 20, 30, 40);
  banyak = uMember;
  hitungMember(3, count, 30, 40, 40);
  sangatBanyak = uMember;
}

int fuzzy_set[5][5] = {
  //|vLow|Low|Med|High|vHigh
  {20, 20, 40,  40,  60},  //| Cold
  {20, 40, 40,  60,  80},  //| Cool
  {40, 40, 60,  80,  100}, //| Normal
  {60, 60, 80,  100, 100}, //| Hot
  {80, 80, 100, 100, 100}  //| Very hot
};

 void defuzzifikasi() {
  float pembil = 0, penyeb = 0, centre_of_area = 0;
  N_suhu[5] = {};
  N_orang[5] = {};
 
  for (int set = 0; set < 25;) {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        float data_uSuhu[5] = {dingin, sejuk, normal, panas, sangatPanas};
        N_suhu[i] = data_uSuhu[i];
        float data_uOrang[5] = {sangatSedikit, sedikit, sedang, banyak, sangatBanyak};
        N_orang[j] = data_uOrang[j];
 
        kondisiSuhu = max(N_suhu[i], kondisiSuhu);
        kondisiOrang = max(N_orang[j], kondisiOrang);
 
        /* Metode COA (Centre Of Area)*/
        Min[set] = min(N_suhu[i], N_orang[j]);
        pembil  += Min[set] * fuzzy_set[i][j];
        penyeb  += Min[set];
        delay(5);
        set ++;
      }
    }
  }
  centre_of_area = pembil / penyeb;
  Keluaran = centre_of_area;
}

void basis_Aturan_output() {
  if (kondisiSuhu == dingin && kondisiOrang == sangatSedikit)OutputFuzzy = "Vslow";
  else if (kondisiSuhu == dingin && kondisiOrang == sedikit)OutputFuzzy = "Vslow";
  else if (kondisiSuhu == dingin && kondisiOrang == sedang)OutputFuzzy = "Slow";
  else if (kondisiSuhu == dingin && kondisiOrang == banyak)OutputFuzzy = "Slow";
  else if (kondisiSuhu == dingin && kondisiOrang == sangatBanyak)OutputFuzzy = "Med";
 
  else if (kondisiSuhu == sejuk && kondisiOrang == sangatSedikit)OutputFuzzy = "Vslow";
  else if (kondisiSuhu == sejuk && kondisiOrang == sedikit)OutputFuzzy = "Slow";
  else if (kondisiSuhu == sejuk && kondisiOrang == sedang)OutputFuzzy = "Slow";
  else if (kondisiSuhu == sejuk && kondisiOrang == banyak)OutputFuzzy = "Med";
  else if (kondisiSuhu == sejuk && kondisiOrang == sangatBanyak)OutputFuzzy = "Fast";
 
  else if (kondisiSuhu == normal && kondisiOrang == sangatSedikit)OutputFuzzy = "Slow";
  else if (kondisiSuhu == normal && kondisiOrang == sedikit)OutputFuzzy = "Slow";
  else if (kondisiSuhu == normal && kondisiOrang == sedang)OutputFuzzy = "Med";
  else if (kondisiSuhu == normal && kondisiOrang == banyak)OutputFuzzy = "Fast";
  else if (kondisiSuhu == normal && kondisiOrang == sangatBanyak)OutputFuzzy = "Vfast";
 
  else if (kondisiSuhu == panas && kondisiOrang == sangatSedikit)OutputFuzzy = "Med";
  else if (kondisiSuhu == panas && kondisiOrang == sedikit)OutputFuzzy = "Med";
  else if (kondisiSuhu == panas && kondisiOrang == sedang)OutputFuzzy = "Fast";
  else if (kondisiSuhu == panas && kondisiOrang == banyak)OutputFuzzy = "Vfast";
  else if (kondisiSuhu == panas && kondisiOrang == sangatBanyak)OutputFuzzy = "Vfast";
 
  else if (kondisiSuhu == sangatPanas && kondisiOrang == sangatSedikit)OutputFuzzy = "Fast";
  else if (kondisiSuhu == sangatPanas && kondisiOrang == sedikit)OutputFuzzy = "Fast";
  else if (kondisiSuhu == sangatPanas && kondisiOrang == sedang)OutputFuzzy = "Vfast";
  else if (kondisiSuhu == sangatPanas && kondisiOrang == banyak)OutputFuzzy = "Vfast";
  else if (kondisiSuhu == sangatPanas && kondisiOrang == sangatBanyak)OutputFuzzy = "Vfast";
}
 void Output() {
  //uMember_suhu_count();
  basis_Aturan_output();
  Tampil_Serial();
  // Tampil_LCD();
}

void Tampil_Serial() {
  //Tampil Serial
  Serial.print(" Temp : ");
  Serial.print(temp());
  Serial.print(" *C ");
  Serial.print(" ");
  tampil_member_suhu();
  if (kondisiSuhu == N_suhu[0])Serial.println("Cold");
  else if (kondisiSuhu == N_suhu[1])Serial.println("Cool");
  else if (kondisiSuhu == N_suhu[2])Serial.println("Normal");
  else if (kondisiSuhu == N_suhu[3])Serial.println("Hot");
  else if (kondisiSuhu == N_suhu[4])Serial.println("Very Hot");
 
  Serial.print(" | Count : ");
  Serial.print(count);
  Serial.print(" ");
  tampil_member_count();
  if (kondisiOrang == N_orang[0])Serial.println("Very Low");
  else if (kondisiOrang == N_orang[1])Serial.println("Low");
  else if (kondisiOrang == N_orang[2])Serial.println("Medium");
  else if (kondisiOrang == N_orang[3])Serial.println("High");
  else if (kondisiOrang == N_orang[4])Serial.println("Very High");
 
  Serial.print(" | ");
  if (OutputFuzzy == "Vslow")     Serial.println("Fan : Very Slow");
  else if (OutputFuzzy == "Slow") Serial.println("Fan : Slow");
  else if (OutputFuzzy == "Med")  Serial.println("Fan : Medium");
  else if (OutputFuzzy == "Fast") Serial.println("Fan : Fast");
  else if (OutputFuzzy == "Vfast")Serial.println("Fan : Very Fast");
  Serial.println(" LV : ");
  Serial.println(Keluaran);
  Serial.println("%");
  Serial.println(" PWM : ");

}

void uMember_suhu_count() {
  Serial.println(" Temp : ");
  Serial.print(temp());
  Serial.print(" *C ");
  Serial.print(" ");
  Serial.println("Cold:");
  Serial.print(dingin);
  Serial.println(" Cool:");
  Serial.print(sejuk);
  Serial.print(" Nor:");
  Serial.print(normal);
  Serial.println(" Hot:");
  Serial.print(panas);
  Serial.println(" VHot:");
  Serial.print(sangatPanas);
  Serial.print(" ");
 
  Serial.println(" | Count : ");
  Serial.print(count);
  Serial.print(" ");
  Serial.println("VLow:");
  Serial.print(sangatSedikit);
  Serial.println(" Low:");
  Serial.print(sedikit);
  Serial.println(" Med:");
  Serial.print(sedang);
  Serial.println(" High:");
  Serial.print(banyak);
  Serial.println(" VHigh:");
  Serial.println(sangatBanyak);
}
 
void tampil_member_suhu() {
  //if (uDingin != 0.00) {
    Serial.println("Cold:");
    Serial.print(dingin);
  //}
  //if (uSejuk != 0.00) {
    Serial.println(" Cool:");
    Serial.print(sejuk);
  //}
  //if (uNormal != 0.00) {
    Serial.println(" Nor:");
    Serial.print(normal);
  //}
  //if (uPanas != 0.00) {
    Serial.println(" Hot:");
    Serial.print(panas);
  //}
  //if (uSangatPanas != 0.00) {
    Serial.println(" VHot:");
    Serial.print(sangatPanas);
  //}
  Serial.print(" ");
}
 
void tampil_member_count() {
  //if (uSangatSedikit != 0.00) {
    Serial.println("VLow:");
    Serial.print(sangatSedikit);
  //}
  //if (uSedikit != 0.00) {
    Serial.println(" Low:");
    Serial.print(sedikit);
  //}
  //if (uSedang != 0.00) {
    Serial.println(" Med:");
    Serial.print(sedang);
  //}
  //if (uBanyak != 0.00) {
    Serial.println(" High:");
    Serial.print(banyak);
  //}
  //if (uSangatBanyak != 0.00) {
    Serial.println(" VHigh:");
    Serial.print(sangatBanyak);
  //}
  Serial.print(" ");
}