#include ESP8266WiFi.h       Esp8266 kütüphanemizi ekledik
#include FirebaseArduino.h   Firebase kütüphanemizi ekledik
#include DHTesp.h            DHT kütüphanemiz

#define FIREBASE_HOST "kendilinkini.firebaseio.com"     Bu kısım Firebase Database Real Database kısmındaki linkinizi girin
#define FIREBASE_AUTH "token gir"                    Proje ayarları Hizmet kısmındaki size özel tokeni girin
#define WIFI_SSID "Wifi adınızı Girin"              
#define WIFI_PASSWORD "Wifi şifrenizi girin"    

String path = "/nem_sicaklik";
        
DHTesp dht;

void setup() {
Serial.begin(9600);     kendi modelinizin baudrate özelliğine göre değiştirin. yoksa serial printte manyak olursunuz
  
dht.setup(D4, DHTespDHT11);   Ben DHT11 sensörümü D4 pinine  bağladım.  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print(connecting);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(.);
    delay(500);
  }
  Serial.println();
  Serial.print(connected );
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

int hum = dht.getHumidity();   
int tem=dht.getTemperature();  

Serial.print(hum ); Serial.println(hum);  nem değerimizi serial printe bastırıyoruz
Serial.print(tem ); Serial.println(tem);  sıcaklık değerimizi bastırıyoruz

Firebase.setInt(path + "/Humidity/Data", hum);
  if (Firebase.failed()) {   buna gerek yok aslında ama patlarsak haberimiz olsun diye yazdım             
      Serial.print(setting hum failed);
      Serial.println(Firebase.error()); 
      }

Firebase.setInt( path + "/Temperature/Data", tem);
  if (Firebase.failed()) {
      Serial.print(setting tem failed);
      Serial.println(Firebase.error()); 
    }
  }
