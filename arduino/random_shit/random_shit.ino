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
String webon = "<h1>CartSanitizer</h1><a href = \"on\"><button style = \"background-color: rgb(0,255,0);\"> ON</button></a><a href=\"off\"><button>OFF</button></a>";

bool manual = false;
bool manualspraying = false;
int count = 0;
bool lastread = false;
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
  manual = false;
  manualspraying = false;
  count = 0;
  server.begin();
}

void loop(void){
  
  bool currentread = digitalRead(buttonpin);
  
  if(!manual){ 
    // if notmanual
    if(currentread==LOW){
      // if button pushed emergency stop and turn on manual
      turnoff();
      blinkled(500);
      manual = true;
      manualspraying = false;
    }else{
      server.handleClient();  
    }
  } else {
    
    if(currentread == LOW){
    
      unsigned long elapsed = 0;
      unsigned long StartTime = millis();
      
      while(currentread==LOW){
        currentread = digitalRead(buttonpin);
        lastread = currentread;
        delay(1);
      }
      elapsed = millis() - StartTime;
      
      if(elapsed >= 3000){// button held for more than 3 seconds
        turnoff();
        manualspraying = false;
        manual = false;
        blinkled(100);
      }else if(elapsed <=3000){// when released toggle the spray
        
        manualspraying = !manualspraying;
        if(manualspraying){
          turnon();
        }else if(!manualspraying){
          turnoff();
        }
     }
    }
    
  }

  

  
}

void turnon(){
  digitalWrite(greenledpin, LOW);
  digitalWrite(relaypin,HIGH);
}

void turnoff(){
  digitalWrite(greenledpin, HIGH);
  digitalWrite(relaypin,LOW);
}
void blinkled(int delaytime){
  for(int i = 0;i<20;i++){
    digitalWrite(greenledpin, LOW);
    delay(delaytime);
    digitalWrite(greenledpin, HIGH);
    delay(delaytime);
  }
  
}
