
#include <Servo_ESP32.h>

static const int servoPin = 15; // pin printed as G14
static const int potentiometerPin = 12;// pin printed as G12

Servo_ESP32 servo1;

void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
}

void loop() {
	
    int servoPosition = map(analogRead(potentiometerPin), 0, 4096, 0, 180);
   
    servo1.write(servoPosition);
    Serial.println(servoPosition);
    delay(20);
}
