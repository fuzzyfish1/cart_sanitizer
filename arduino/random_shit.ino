/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "YOBZ";
const char* password = "chochotrainez";

ESP8266WebServer server(80);

String weboff = "<h1>CartSanitizer</h1><a href = \"on\" ><button>ON</button></a><a href = \"off\"><button style = \"background-color: rgb(255,0,0);\">OFF</button></a>";
String webon = "<h1>CartSanitizer</h1><a href = \"on\" style = \"background-color: rgb(0,255,0);\"><button> ON</button></a><a href=\"off\"><button>OFF</button></a>";

bool relayon = false;

//int redledpin = 14;
int greenledpin = 13; // low turns it on high is off
int relaypin = 12; // high is on Low is off
int buttonpin = 0; // low is pushed HIGH is unpushed

//int baud = 115200;

void setup(void){

  pinMode(greenledpin, OUTPUT);
  //pinMode(redledpin, OUTPUT);
  pinMode(relaypin, OUTPUT);
  pinMode(buttonpin, INPUT);

  digitalWrite(greenledpin, HIGH);
  //digitalWrite(redledpin, HIGH);
  digitalWrite(relaypin, LOW);

  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    digitalWrite(greenledpin, LOW);
    delay(500);
    digitalWrite(greenledpin, HIGH);
    delay(500);
  }

  //webPage += "<h1>SONOFF Web Server</h1><p><a href=\"on\"><button>ON</button></a>&nbsp;<a href=\"off\"><button>OFF</button></a></p>";
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    //Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webon);
  });
  server.on("/on", [](){
    server.send(200, "text/html", webon);
    turnon();
  });
  server.on("/off", [](){
    server.send(200, "text/html", weboff);
    turnoff();
  });
  server.begin();
}
 
void loop(void){
  
  server.handleClient();
}

void turnon(){
  digitalWrite(greenledpin, LOW);
  digitalWrite(relaypin,HIGH);
}

void turnoff(){
  digitalWrite(greenledpin, HIGH);
  digitalWrite(relaypin,LOW);
}
