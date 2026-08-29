/*
 * Escalera Inteligente con Sensores Ultrasonicos HC-SR04
 * Arduino Uno - 8 escalones, 2 sensores de ultrasonido
 *
 * Circuito:
 *   LEDs escalon 1-8 en pines D2-D9 (con resistencia 220 ohm)
 *   Sensor ultrasonido superior (parte alta): Trig=D10, Echo=D11
 *   Sensor ultrasonido inferior (parte baja): Trig=D12, Echo=D13
 *   VCC de sensores a 5V, GND a GND
 *
 * Comportamiento:
 *   Inferior (0-20cm, apunta hacia afuera): activa LEDs progresivamente
 *     mientras la persona se acerca (ramp up desde abajo).
 *   Superior (5-50cm, apunta hacia abajo de la escalera): sigue a la
 *     persona con un foco de 3 LEDs segun su posicion.
 */

const int PINES_LEDS[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int CANTIDAD_LEDS = 8;

const int TRIG_SUPERIOR = 10;
const int ECHO_SUPERIOR = 11;
const int TRIG_INFERIOR = 12;
const int ECHO_INFERIOR = 13;

const float DIST_INFERIOR_MAX = 20.0;
const float DIST_SUPERIOR_MIN = 5.0;
const float DIST_SUPERIOR_MAX = 50.0;

const unsigned long TIEMPO_SIN_CONTACTO_MAX = 2000;

enum EstadoSistema {
  ESPERANDO,
  ACERCAMIENTO,
  EN_ESCALERA
};

EstadoSistema estadoActual = ESPERANDO;

float distanciaSuperiorAnterior = -1.0;
unsigned long tiempoUltimoContacto = 0;

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

void apagarTodos() {
  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    digitalWrite(PINES_LEDS[i], LOW);
  }
}

void encenderFoco(int centro, int radio) {
  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    bool activar = (i >= centro - radio && i <= centro + radio);
    digitalWrite(PINES_LEDS[i], activar ? HIGH : LOW);
  }
}

void encenderRango(int ultimoEncendido) {
  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    digitalWrite(PINES_LEDS[i], (i < ultimoEncendido) ? HIGH : LOW);
  }
}

void setup() {
  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    pinMode(PINES_LEDS[i], OUTPUT);
    digitalWrite(PINES_LEDS[i], LOW);
  }

  pinMode(TRIG_SUPERIOR, OUTPUT);
  pinMode(ECHO_SUPERIOR, INPUT);
  pinMode(TRIG_INFERIOR, OUTPUT);
  pinMode(ECHO_INFERIOR, INPUT);

  digitalWrite(TRIG_SUPERIOR, LOW);
  digitalWrite(TRIG_INFERIOR, LOW);
}

void loop() {
  float distanciaInferior = medirDistancia(TRIG_INFERIOR, ECHO_INFERIOR);
  float distanciaSuperior = medirDistancia(TRIG_SUPERIOR, ECHO_SUPERIOR);

  bool objetoInferior = (distanciaInferior >= 0 && distanciaInferior <= DIST_INFERIOR_MAX);
  bool objetoSuperior = (distanciaSuperior >= DIST_SUPERIOR_MIN && distanciaSuperior <= DIST_SUPERIOR_MAX);

  switch (estadoActual) {

    case ESPERANDO:
      if (objetoSuperior) {
        estadoActual = EN_ESCALERA;
        distanciaSuperiorAnterior = distanciaSuperior;
        tiempoUltimoContacto = millis();
      } else if (objetoInferior) {
        estadoActual = ACERCAMIENTO;
      }
      break;

    case ACERCAMIENTO:
      if (objetoSuperior) {
        estadoActual = EN_ESCALERA;
        distanciaSuperiorAnterior = distanciaSuperior;
        tiempoUltimoContacto = millis();
      } else if (objetoInferior) {
        int cantidadLEDs = map(distanciaInferior, DIST_INFERIOR_MAX, 0, 1, CANTIDAD_LEDS);
        cantidadLEDs = constrain(cantidadLEDs, 1, CANTIDAD_LEDS);
        encenderRango(cantidadLEDs);
      } else {
        apagarTodos();
        estadoActual = ESPERANDO;
      }
      break;

    case EN_ESCALERA:
      if (objetoSuperior) {
        tiempoUltimoContacto = millis();

        int escalonActual = map(distanciaSuperior, DIST_SUPERIOR_MIN, DIST_SUPERIOR_MAX, CANTIDAD_LEDS - 1, 0);
        escalonActual = constrain(escalonActual, 0, CANTIDAD_LEDS - 1);

        encenderFoco(escalonActual, 1);
        distanciaSuperiorAnterior = distanciaSuperior;
      } else if (millis() - tiempoUltimoContacto >= TIEMPO_SIN_CONTACTO_MAX) {
        apagarTodos();
        estadoActual = ESPERANDO;
      }
      break;
  }
}