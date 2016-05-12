#include <SoftwareSerial.h>
#include <Servo.h>

Servo serv;

#include "common/definitions.h"

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  serv.attach(SERVO_PIN);
  Serial.println("Hallo Welt");
  pinMode(13, OUTPUT);
    serv.write(0);
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(add<10,3>::value, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);              // wait for a second
  //digitalWrite(add<10,3>::value, LOW);    // turn the LED off by making the voltage LOW

  //int hall = digitalRead(HALL_SENSOR));
  
  digitalWrite(GREEN_LED, digitalRead(HALL_SENSOR) && digitalRead(PHOTO_SENSOR));
  
  /* Serial.println(digitalRead(HALL_SENSOR));
  serv.write(20);
  delay(1000);
  serv.write(0);
  delay(1000); */
  
}
