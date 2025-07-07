#include <SoftwareSerial.h>

#define IR_SENSOR_PIN 2  // IR receiver connected to digital pin 2
#define BT_TX 10         // Bluetooth module TX
#define BT_RX 11         // Bluetooth module RX

SoftwareSerial bluetooth(BT_TX, BT_RX);  // Create a software serial for Bluetooth

volatile bool isTap = false;

void detectTap() {
    isTap = true;
}

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    pinMode(IR_SENSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), detectTap, FALLING);
}

void loop() {
    if (isTap) {
        Serial.println("Tap detected");
        bluetooth.println("Tap detected");  // Send message to smartphone
        isTap = false;
        delay(500);  // Debounce delay to prevent multiple detections
    }
}