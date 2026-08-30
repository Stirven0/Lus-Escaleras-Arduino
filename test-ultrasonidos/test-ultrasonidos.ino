/*
 * Test de Sensores Ultrasonicos HC-SR04
 * Muestra las distancias del sensor inferior y superior por Serial
 *
 * Conexiones:
 *   Sensor superior (parte alta): Trig=D10, Echo=D11
 *   Sensor inferior (parte baja): Trig=D12, Echo=D13
 *   VCC a 5V, GND a GND
 */

const int TRIG_SUPERIOR = 10;
const int ECHO_SUPERIOR = 11;
const int TRIG_INFERIOR = 12;
const int ECHO_INFERIOR = 13;

float medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  long duracion = pulseIn(pinEcho, HIGH, 30000);
  if (duracion == 0) return -1.0;
  return duracion * 0.034 / 2.0;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_SUPERIOR, OUTPUT);
  pinMode(ECHO_SUPERIOR, INPUT);
  pinMode(TRIG_INFERIOR, OUTPUT);
  pinMode(ECHO_INFERIOR, INPUT);

  digitalWrite(TRIG_SUPERIOR, LOW);
  digitalWrite(TRIG_INFERIOR, LOW);

  Serial.println("=== Test Sensores Ultrasonicos ===");
  Serial.println("Sup (D10/11) | Inf (D12/13)");
  Serial.println("Las distancias se muestran en cm");
  Serial.println();
}

void loop() {
  float distInferior = medirDistancia(TRIG_INFERIOR, ECHO_INFERIOR);
  float distSuperior = medirDistancia(TRIG_SUPERIOR, ECHO_SUPERIOR);

  Serial.print("Inferior: ");
  if (distInferior < 0) {
    Serial.print("sin objeto");
  } else {
    Serial.print(distInferior);
    Serial.print(" cm");
  }

  Serial.print("  |  Superior: ");
  if (distSuperior < 0) {
    Serial.print("sin objeto");
  } else {
    Serial.print(distSuperior);
    Serial.print(" cm");
  }

  Serial.println();
  delay(300);
}