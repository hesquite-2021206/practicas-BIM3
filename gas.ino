#include <LedControl.h>
#include <Ticker.h>

#define DATO_PIN 12
#define CLK_PIN 11
#define CS_PIN 10
void Lectura_GAS(void);
LedControl ledMatrix = LedControl(DATO_PIN,CLK_PIN,CS_PIN,1);
Ticker ISR_GAS(Lectura_GAS, 5000);
#define gasSensorPin  A0

const int ancho_matriz = 8; 
const int alto_matriz = 8; 
int gasValue;
int prom;

byte alerta1[8] = {
B00000000,
B00010000,
B00001000,
B00001100,
B00011100,
B10111101,
B01111110,
B00111110
};
byte alerta2[8] = {
B00000000,
B00000100,
B00001100,
B01001100,
B01111000,
B00111101,
B01111110,
B00111110
};
byte copo [8] = {
B10100101,
B01000010,
B10100101,
B00011000,
B00011000,
B10100101,
B01000010,
B10100101
};

void setup() {
  ledMatrix.shutdown(0, false); 
  ledMatrix.setIntensity(0, 15); 
  ledMatrix.clearDisplay(0); 
  pinMode(gasSensorPin, INPUT); 
  ISR_GAS.start();
  Serial.begin(9600);
}

void loop() {
  // Leer el valor del sensor de gas
 ISR_GAS.update();
  if (prom > 60) {
    alerta_fuego();
  } else {
    for (int i = 0; i < alto_matriz; i++) {
    ledMatrix.setColumn(0, i, copo[i]);
  }
  }
  delay(1000);
}
void Lectura_GAS(){
  int suma =0;
  for(int i = 0; i < 5; i++){
  gasValue = map(analogRead(gasSensorPin),0,1023,0,100);
  suma = suma + gasValue;
  delay(100);
  }
  prom = suma/5;
  Serial.println(gasValue);
}
void alerta_fuego() {
  ledMatrix.clearDisplay(0);
for(int t = 0; t<5;t++){
  for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, alerta1[i]);
  }
  delay(500);
  
  for (int i = alto_matriz; i > 0; i--) {
    ledMatrix.setColumn(0, i, alerta2[i]);
  }
  delay(500);
}
}
