
#include <Servo_ESP32.h>

static const int servo1Pin = 15; 

Servo_ESP32 servo1;
int servo_selector = 1;
int servo1Angle =90;  //Incial
int servo1Step = 20;  //incremento
int servo1Angle_in_percent;

int servo1AngleMin =0;
int servo1AngleMax = 180;

#include "01-SimpleServo_Wifi_page.h"



  
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "CASA";
const char *password = "Estaeslapassdem1w1f1";

WebServer server(80);

const int led = 13;

void handleRoot() {
String HTML_page = pageHeader_1; 
servo1Angle_in_percent = map(servo1Angle, servo1AngleMin, servo1AngleMax, 0, 100); 
 HTML_page.concat(".bar1 {width: " + String(servo1Angle_in_percent)  + "%;}\n");
 HTML_page.concat(pageHeader_2 );
 HTML_page.concat(servo1Control_p1);
 HTML_page.concat("Angle: " + String(servo1Angle) +" ");  
 HTML_page.concat(servo1Control_p2);
 HTML_page.concat("</body>\n</html>");
 
  server.send(200, "text/html", HTML_page);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}


void setup() {
    Serial.begin(115200);
    servo1.attach(servo1Pin);
	

  //Servo control using ESP32 from Robojax.com

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
    
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if (MDNS.begin("192.168.1.76")) {
    Serial.print("MDNS responder started at http://");
    Serial.println("192.168.1.76");
  }

  server.on("/", handleRoot);
  server.on("/servo", HTTP_GET, handleServo);  
  server.on("/move", HTTP_GET, handleServoAngle);  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started"); 	
}

void loop() {
	server.handleClient();

        servo1.write(servo1Angle);
        Serial.println(servo_selector);
        delay(20);

}


void handleServo() {
  if(server.arg("do") == "s1less" )
  {
    servo1Angle -=servo1Step;
    
      if(servo1Angle <= servo1AngleMin)
      {
        servo1Angle = servo1AngleMin;
      }
  }else 
  {
    servo1Angle +=servo1Step;   
     
      if(servo1Angle >= servo1AngleMax)
      {
        servo1Angle =servo1AngleMax;
      } 
  }
  handleRoot();
}//handleServo() end


void handleServoAngle() {



  int servoAngle =server.arg("angle").toInt();
   

  if(servoAngle >=0 || servoAngle <=180)
  {
    servo1Angle =servoAngle;
   
  }

  
    
  handleRoot();
}//handleServoAngle() end


void handleSelector() {
  
  int selector = server.arg("selec").toInt();
  if(selector >=0 || selector <=4){
    servo_selector = selector;
     Serial.println(servo_selector);
    }
  handleRoot();
}//handleServo() end
