#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ledPin 3 
#define Temp 4
#define bluetoothTx 10 
#define bluetoothRx 11 

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); 
OneWire oneWire(Temp);
DallasTemperature sensors(&oneWire);



void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  bluetooth.begin(9600); 
  sensors.begin();
}

void loop() {
  if (bluetooth.available()) { 
    char command = bluetooth.read(); 
    
    if (command == '2') { 
      encenderLed(); 
    } else if (command == '1') { 
      apagarLed(); 
    }
  }
  
 sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  bluetooth.print(temperatura);
  bluetooth.println("°C");

}


void encenderLed() {
  digitalWrite(ledPin, HIGH); 
}

void apagarLed() {
  digitalWrite(ledPin, LOW); 
}
