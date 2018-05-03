#include "DHT.h"
#include "RS485.h"

#define BIT_PENANDA1 0xFF
#define BIT_PENANDA2 0xFE
#define ID_DEVICE 111 // id pengirim
#define ID_MASTER 101 // receive / master/ tujuan
#define BIT_END 0xFA//bit akhir penanda 

#define DHTPIN 7
#define DHTTYPE 22
DHT dht(DHTPIN, DHTTYPE);

int data_length = 0; // panjang data dari variabel

char strdata[15] = "start"; // isi command apa yang mau di excute



void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
float variabel = temperature();
protocol_suhu(variabel);
 //menyimpan nilai Humidity pada variabel kelembaban

}



int baca_data_suhu(float par_variabel){
  String buff = String(par_variabel); // melakukan parsing dari float ke string
  unsigned int lastStringLength = buff.length(); // mencari panjang data
  return lastStringLength;
}

int checksumdata(float par_variabel){
  int checksum;
  char buff[256];
  //sprintf( buff, "%d %d %f %c",ID_MASTER,ID_DEVICE,variabel,strdata );

  checksum =   sprintf( buff, "%d%d%5.f%s",ID_MASTER,ID_DEVICE,par_variabel,strdata )%256;
//  Serial.println(checksum);
  return checksum;
}

void protocol_suhu(float variabel_par){
  char String_var[8];
//  sprintf(String_var, "%5.f", variabel_par);
  
  dtostrf(variabel_par, 5, 2, String_var);

  
  int data_pjg  = baca_data_suhu(variabel_par);
  int checksum = checksumdata(variabel_par);
  int panjang_id_rev = sizeof(ID_MASTER);
  Serial.write(BIT_PENANDA1);
  Serial.write(BIT_PENANDA2);

  Serial.write(data_pjg);
  Serial.write(ID_MASTER);
  Serial.write(ID_DEVICE);
  Serial.write(String_var);
  Serial.write(strdata);
  Serial.write(checksum);

  Serial.write(BIT_END);
  //Serial.write('test');
  delay(2000);
}

float humidity(){
  return dht.readHumidity();
}
float temperature(){
  return dht.readTemperature();
}





