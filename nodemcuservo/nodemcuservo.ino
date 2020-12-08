#include <ESP8266WiFi.h>  
#include <IRremoteESP8266.h>  //  bu konu ile alakası olmayan kütüphane 
#include <IRsend.h>          //   bu konu ile alakası yok 
#include<Servo.h> 


WiFiServer wifiServer(80);  
const char* ssid = "Network Name";  
const char* password = "Network Pasword"; 

Servo servomotor;                                       


void setup() {  


  Serial.begin(9600); 


  delay(1000);  
  servomotor.attach(5);  //5 numaralı pin çıkışına bağlıyoruz servo motoru
  servomotor.write(0);  

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);  
    Serial.println("Connecting.."); 
  } 

  Serial.print("Connected to WiFi. IP:"); 
  Serial.println(WiFi.localIP()); 

  wifiServer.begin(); 


} 

void loop() { 

  WiFiClient client = wifiServer.available(); 
  String command = "";  

  if (client) { 

    while (client.connected()) {  

      while (client.available()>0) {  
        char c = client.read(); 
        if (c == '\n') {  
          break;  
        } 
        command += c; 
        Serial.write(c);  
      } 

      if (command == "kapı_Ac") {      
        servomotor.write(90); 



        Serial.println(" \n Kapı Açıldı");  
      } 
      if (command == "FAN") { 
        servomotor.write(0);  



        Serial.println(" \n Kapı Kapandı"); 
      } 

      command = ""; 
      delay(10);  
    } 

    client.stop();  
    Serial.println("Client disconnected");  

  } 
}
