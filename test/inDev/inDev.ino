#include <IRremoteESP8266.h>
#include <IRsend.h>

//Declare consts and shit
const int BUTTON = 4;
const int OnBoard_LED = 2;
const int IR_LED = 14;
const int IR_SENSOR = 36;
int led_stat = 0;

IRsend irsend(IR_LED);

// ----------------- Function prototypes
void readButton();
void volumeUp();
void readIR();

// ------------------------- MAINs --------------------------
void setup() {
  irsend.begin();
  Serial.begin(115200); // DEBUGGING remove later
  pinMode(BUTTON, INPUT);
  pinMode(OnBoard_LED, OUTPUT);
  pinMode(IR_SENSOR, INPUT);
  pinMode(IR_SENSOR, INPUT);      
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    volumeUp();
  }
}

// ---------------------------- Function definitions
void readButton() {
  if (digitalRead(BUTTON) == LOW) { //low is read because I am using external pull-up
    Serial.println("BUTTON PRESSED.");
    if (led_stat == 0) {
      digitalWrite(OnBoard_LED, HIGH);
      led_stat = 1;
      Serial.println("Set LED ON");
    }
    else {
      digitalWrite(OnBoard_LED, LOW);
      led_stat = 0;
      Serial.println("Set LED OFF");
    }
  }
  delay(400);
}

void volumeUp() { // should be the NEC protocol volume up, no idea lets hope
  digitalWrite(OnBoard_LED, HIGH);
  Serial.println("Sending NEC colume up..."); // DEBUGGING REMOVE LATER
  irsend.sendSamsung36(0xE0E0E01F, 32); // maybe volume up for samsing NEC tv, not sure LOL
  readIR();
  delay(500);
  digitalWrite(OnBoard_LED, LOW);
  Serial.println("IR finished sending");
  readIR();
}

void readIR() {
  int sensorValue = analogRead(IR_SENSOR);
  Serial.println(sensorValue);
}
