#include <EEPROM.h>
#define numSKETCH 3




#include <Servo_ESP32.h>

//Servos
static const int servo1Pin = 15;
static const int servo2Pin = 2;
static const int servo3Pin =0;
static const int servo4Pin = 4;;


//Potenciometros
static const int potentiometerPin1 = 34;
static const int potentiometerPin2 = 35;
static const int potentiometerPin3 = 33;
static const int potentiometerPin4 = 32;

//Lecturas Analogicos
int servoPosition1;
int servoPosition2;
int servoPosition3;
int servoPosition4;

//Valores auxiliares
int servoAngle1Aux = 0;
int servoAngle2Aux= 0;
int servoAngle3Aux = 180;
int servoAngle4Aux = 0;
//Servos
Servo_ESP32 servo1;
Servo_ESP32 servo2;
Servo_ESP32 servo3;
Servo_ESP32 servo4;


int control_remoto;
int servo1Angle =90;
int servo1Step = 20;
int servo1Angle_in_percent;
int servo_selector = 1;
int servo1AngleMin =0;
int servo1AngleMax = 180;

#include "01-SimpleServo_Wifi_page.h"



  
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "CASA";
const char *password = "Estaeslapassdem1w1f1";

IPAddress ip(192,168,1,76);  
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0); 
WebServer server(80);

//const int led = 13;

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
  //digitalWrite(led, 1);
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
  //digitalWrite(led, 0);
}





void setup() {


    Serial.begin(115200);
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
	  servo3.attach(servo3Pin);
   servo4.attach(servo4Pin);

 

    WiFi.mode(WIFI_STA);
    WiFi.config(ip,gateway,subnet);
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


    if (MDNS.begin("")) {
      Serial.print("MDNS responder started at http://");
      Serial.println("robojaxESP32");
    }

    server.on("/", handleRoot);
    server.on("/servo", HTTP_GET, handleServo);  
    server.on("/move", HTTP_GET, handleServoAngle);  
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started"); 	
  }

 void loop() {

  
 //Serial.println(servo_selector);
     server.handleClient();  
   if(control_remoto == 1){
    
       if(servo_selector == 1){
          servo1.write(servo1Angle);
          servoAngle1Aux = servo1Angle;
          delay(20);
        }
       if(servo_selector == 2){
          servo2.write(servo1Angle);
          servoAngle2Aux = servo1Angle;
          delay(20);
        }
  
        if(servo_selector == 3){
          servo3.write(servo1Angle);
          servoAngle3Aux = servo1Angle;
          delay(20);
        }
      
        if(servo_selector == 4){
          servo4.write(servo1Angle);
          servoAngle4Aux = servo1Angle;
          delay(20);
      
        }
   }else{
    
       servoPosition1 = map(analogRead(potentiometerPin1), 0, 4096, 0, 180);
       servo1.write(servoPosition1);
      // delay(20);
     
       servoPosition2 = map(analogRead(potentiometerPin2), 0, 4096, 0, 180);
       servo2.write(servoPosition2);
       //delay(20);

       servoPosition3 = map(analogRead(potentiometerPin3), 0, 4096, 0, 180);
       servo3.write(servoPosition3);
       //delay(20);

       servoPosition4 = map(analogRead(potentiometerPin4), 0, 4096, 0, 180);
       servo4.write(servoPosition4);
       //delay(20);
   }
       
      
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
 delay(100);
}//handleServo() end


void handleServoAngle() {

  int servoAngle =server.arg("angle").toInt();
  if(servoAngle >=0 || servoAngle <=180)
  {
    servo1Angle =servoAngle;
   
  }
  if(servoAngle == 200){
    servo_selector =1;
    servo1Angle =  servoAngle1Aux;
    }
  if(servoAngle == 300){
    servo_selector =2;
    servo1Angle =  servoAngle2Aux;
    } 
   if(servoAngle == 400){
    servo_selector = 3;
    servo1Angle = servoAngle3Aux;
    } 
    if(servoAngle == 500){
      servo_selector = 4;
      servo1Angle = servoAngle4Aux;
      }

  if(servoAngle == 1000){
    control_remoto = 0;
    }  
  if(servoAngle == 2000){
    control_remoto = 1;
    }  
    
  Serial.println(servoAngle);
  
     
  handleRoot();
}//handleServoAngle() end
