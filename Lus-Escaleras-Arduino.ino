/*
 * Escalera Inteligente con LEDs y Sensores IR
 * Arduino Uno - 8 escalones, 2 sensores IR
 *
 * Circuito:
 *   LEDs escalon 1-8 en pines D2-D9 (con resistencia 220 ohm)
 *   Sensor IR inferior receptor en D10 (con pull-up 10k ohm)
 *   Sensor IR superior receptor en D11 (con pull-up 10k ohm)
 *   Emisores IR conectados a 5V con resistencia 100 ohm (siempre encendidos)
 */

const int LED_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int NUM_LEDS = 8;

const int SENSOR_INFERIOR = 10;
const int SENSOR_SUPERIOR = 11;

const unsigned long TIEMPO_ESPERA = 5000;
const unsigned long VELOCIDAD_TRANSICION = 300;

enum Estado {
  ESPERANDO,
  SUBIENDO,
  BAJANDO,
  ESPERANDO_APAGADO_SUBIR,
  ESPERANDO_APAGADO_BAJAR,
  APAGANDO_SUBIR,
  APAGANDO_BAJAR
};

Estado estadoActual = ESPERANDO;
unsigned long tiempoInicioEspera = 0;
unsigned long ultimoPasoApagado = 0;
int ledActual = 0;

bool estadoAnteriorInferior = LOW;
bool estadoAnteriorSuperior = LOW;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  pinMode(SENSOR_INFERIOR, INPUT);
  pinMode(SENSOR_SUPERIOR, INPUT);

  estadoAnteriorInferior = digitalRead(SENSOR_INFERIOR);
  estadoAnteriorSuperior = digitalRead(SENSOR_SUPERIOR);
}

bool detectarFlanco(int pin, bool &estadoAnterior) {
  bool actual = digitalRead(pin);
  bool flanco = (estadoAnterior == LOW && actual == HIGH);
  estadoAnterior = actual;
  return flanco;
}

bool ledEncendido(int index) {
  return digitalRead(LED_PINS[index]) == HIGH;
}

void loop() {
  bool flancoInferior = detectarFlanco(SENSOR_INFERIOR, estadoAnteriorInferior);
  bool flancoSuperior = detectarFlanco(SENSOR_SUPERIOR, estadoAnteriorSuperior);

  switch (estadoActual) {

    case ESPERANDO:
      if (flancoInferior) {
        estadoActual = SUBIENDO;
        ledActual = 0;
      } else if (flancoSuperior) {
        estadoActual = BAJANDO;
        ledActual = NUM_LEDS - 1;
      }
      break;

    case SUBIENDO:
      digitalWrite(LED_PINS[ledActual], HIGH);
      ledActual++;
      if (ledActual >= NUM_LEDS) {
        estadoActual = ESPERANDO_APAGADO_SUBIR;
        tiempoInicioEspera = millis();
      }
      delay(VELOCIDAD_TRANSICION);
      break;

    case BAJANDO:
      digitalWrite(LED_PINS[ledActual], HIGH);
      ledActual--;
      if (ledActual < 0) {
        estadoActual = ESPERANDO_APAGADO_BAJAR;
        tiempoInicioEspera = millis();
      }
      delay(VELOCIDAD_TRANSICION);
      break;

    case ESPERANDO_APAGADO_SUBIR:
      if (flancoInferior) {
        estadoActual = SUBIENDO;
        ledActual = 0;
      } else if (flancoSuperior) {
        estadoActual = BAJANDO;
        ledActual = NUM_LEDS - 1;
      } else if (millis() - tiempoInicioEspera >= TIEMPO_ESPERA) {
        estadoActual = APAGANDO_SUBIR;
        ledActual = 0;
        ultimoPasoApagado = millis();
      }
      break;

    case ESPERANDO_APAGADO_BAJAR:
      if (flancoInferior) {
        estadoActual = SUBIENDO;
        ledActual = 0;
      } else if (flancoSuperior) {
        estadoActual = BAJANDO;
        ledActual = NUM_LEDS - 1;
      } else if (millis() - tiempoInicioEspera >= TIEMPO_ESPERA) {
        estadoActual = APAGANDO_BAJAR;
        ledActual = NUM_LEDS - 1;
        ultimoPasoApagado = millis();
      }
      break;

    case APAGANDO_SUBIR:
      if (flancoInferior) {
        estadoActual = SUBIENDO;
        ledActual = 0;
      } else if (flancoSuperior) {
        estadoActual = BAJANDO;
        ledActual = NUM_LEDS - 1;
      } else if (millis() - ultimoPasoApagado >= VELOCIDAD_TRANSICION) {
        digitalWrite(LED_PINS[ledActual], LOW);
        ledActual++;
        ultimoPasoApagado = millis();
        if (ledActual >= NUM_LEDS) {
          estadoActual = ESPERANDO;
        }
      }
      break;

    case APAGANDO_BAJAR:
      if (flancoInferior) {
        estadoActual = SUBIENDO;
        ledActual = 0;
      } else if (flancoSuperior) {
        estadoActual = BAJANDO;
        ledActual = NUM_LEDS - 1;
      } else if (millis() - ultimoPasoApagado >= VELOCIDAD_TRANSICION) {
        digitalWrite(LED_PINS[ledActual], LOW);
        ledActual--;
        ultimoPasoApagado = millis();
        if (ledActual < 0) {
          estadoActual = ESPERANDO;
        }
      }
      break;
  }
}
