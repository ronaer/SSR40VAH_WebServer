/*
 * Dr.TRonik / YouTube / ARALIK 2023 / İzmir / Türkiye 
 * ESP8266 NodeMcu ile, microservo+pot kullanılarak SSR 40VA-H dimmer rölenin Local WebServer ile konrolü...
 * Derleme ve karta yükleme öncesi, tüm kütüphaneler ile kart platformları arduino ide'sine yüklenmiş olmalıdır...
 * YouTube: 
 * Bağlantılar: https://github.com/ronaer/SSR40VAH_WebServer/blob/main/ssr-40-va-h_bb.jpg
 * Bağlantılar: https://github.com/ronaer/SSR40VAH_WebServer/blob/main/servo_nodemcu_bb.png
*/
/********************************************************************
  GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___
 ********************************************************************/
//ESP & WebServer
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);  // 80 nolu port ayarı

//PageIndex dosyası PageIndex.h olarak aynı çalışma klasöründe bulunmalı...
#include "PageIndex.h";

//Servo
#include <Servo.h>  // Servo donanmsal kütüphane...
Servo myservo;      // myservo adında bir servo objesi ıoluşturuldu...

//SSID,Şifre ve diğer tanımlamalar...
#define STA_SSID "SSID"
#define STA_PASSWORD "password"

bool connected = false;
String servoState = "OFF";

/********************************************************************
  VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs__VOIDs
********************************************************************/
void handleRoot() {
  String s = MAIN_page;              //HTML içeriği okur...
  server.send(200, "text/html", s);  // Web sayfası olarak istemciye gönderir...
}

//Handling servo control...
void handleServo() {
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  myservo.write(pos);
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plane", "");
}

void controlServo() {
  String t_state = server.arg("servoState");
  Serial.println(t_state);
  int pos;
  if (t_state == "1") {
    servoState = pos;
    control_pilotLed();
    for (pos = 0; pos <= 180; pos += 1) {  // Servo açısı 0'dan 180'e...
      // in steps of 1 degree
      myservo.write(pos);
      delay(15);
    }
    control_pilotLed();
    for (pos = 180; pos >= 0; pos -= 1) {  // Servo açısı 180'den 0'a...
      myservo.write(pos);
      delay(15);
    }
    control_pilotLed();
  } else if (t_state == "2") {
    servoState = pos;
    myservo.write(70);
    control_pilotLed();
  } else if (t_state == "3") {
    servoState = pos;
    myservo.write(105);
    control_pilotLed();
  } else if (t_state == "4") {
    servoState = pos;
    myservo.write(180);
    control_pilotLed();
  } else if (t_state == "5") {
    servoState = pos;
    myservo.write(0);
    control_pilotLed();
  } else {
    servoState = "OFF";
  }
  server.send(200, "text/plane", servoState);
}

void statusServo() {
  server.send(200, "text/plane", servoState);
}

void control_pilotLed() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(400);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(400);
}

/********************************************************************
  SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___
 ********************************************************************/
void setup() {
  Serial.begin(115200);
  delay(500);
  myservo.attach(5, 400, 2500);  // Servo veri pini GPIO 14'de, alt ve üst limitler tanımlandı...
  myservo.write(0);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.setAutoReconnect(true);
  WiFi.begin(STA_SSID, STA_PASSWORD);

  //Webserver başlat ve gelen veriyi servo pozisyonu için ayarlayan fonksiyonlara bağla...
  server.on("/", handleRoot);  //PageIndex.h ile tanımlanan root/açılış web sayfası
  server.on("/setPOS", handleServo);
  server.on("/setSERVO", controlServo);
  server.on("/readSERVO", statusServo);
  server.begin();

  Serial.println("HTTP server started");
}

/********************************************************************
  LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__
********************************************************************/
void loop() {

  server.handleClient();

  if (WiFi.status() == WL_CONNECTED) {
    if (!connected) {
      connected = true;
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(STA_SSID);
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }
  } else {
    if (connected) {
      connected = false;
      Serial.print("Disonnected from ");
      Serial.println(STA_SSID);
    }
  }
}

/* ___İletişim:
e-posta: bilgi@ronaer.com
https://www.instagram.com/dr.tronik2023/   
YouTube: Dr.TRonik: https://www.youtube.com/@DrTRonik
PCBWay: https://www.pcbway.com/project/member/shareproject/?bmbno=A0E12018-0BBC-4C
*/
