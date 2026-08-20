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
int ledActual = 0;
bool LEDsEncendidos[NUM_LEDS];

bool estadoAnteriorInferior = LOW;
bool estadoAnteriorSuperior = LOW;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
    LEDsEncendidos[i] = false;
  }

  pinMode(SENSOR_INFERIOR, INPUT);
  pinMode(SENSOR_SUPERIOR, INPUT);

  estadoAnteriorInferior = digitalRead(SENSOR_INFERIOR);
  estadoAnteriorSuperior = digitalRead(SENSOR_SUPERIOR);

  Serial.println("=== Escalera Inteligente ===");
  Serial.print("Sensor inferior inicial: ");
  Serial.println(estadoAnteriorInferior);
  Serial.print("Sensor superior inicial: ");
  Serial.println(estadoAnteriorSuperior);
}

bool detectarFlanco(int pin, bool &estadoAnterior) {
  bool estadoActual = digitalRead(pin);
  bool flanco = (estadoAnterior == LOW && estadoActual == HIGH);
  estadoAnterior = estadoActual;
  return flanco;
}

void loop() {
  bool flancoInferior = detectarFlanco(SENSOR_INFERIOR, estadoAnteriorInferior);
  bool flancoSuperior = detectarFlanco(SENSOR_SUPERIOR, estadoAnteriorSuperior);

  Serial.print("Inf: ");
  Serial.print(digitalRead(SENSOR_INFERIOR));
  Serial.print(" | Sup: ");
  Serial.print(digitalRead(SENSOR_SUPERIOR));
  Serial.print(" | Estado: ");
  Serial.println(estadoActual);

  switch (estadoActual) {

    case ESPERANDO:
      if (flancoInferior) {
        estadoActual = SUBIENDO;
        ledActual = 0;
        Serial.println(">>> Deteccion inferior - SUBIENDO");
      } else if (flancoSuperior) {
        estadoActual = BAJANDO;
        ledActual = NUM_LEDS - 1;
        Serial.println(">>> Deteccion superior - BAJANDO");
      }
      break;

    case SUBIENDO:
      encenderLed(ledActual);
      Serial.print("Encendiendo LED ");
      Serial.println(ledActual);
      ledActual++;
      if (ledActual >= NUM_LEDS) {
        estadoActual = ESPERANDO_APAGADO_SUBIR;
        tiempoInicioEspera = millis();
        Serial.println("Todos encendidos, esperando 5s...");
      }
      delay(VELOCIDAD_TRANSICION);
      break;

    case BAJANDO:
      encenderLed(ledActual);
      Serial.print("Encendiendo LED ");
      Serial.println(ledActual);
      ledActual--;
      if (ledActual < 0) {
        estadoActual = ESPERANDO_APAGADO_BAJAR;
        tiempoInicioEspera = millis();
        Serial.println("Todos encendidos, esperando 5s...");
      }
      delay(VELOCIDAD_TRANSICION);
      break;

    case ESPERANDO_APAGADO_SUBIR:
      if (millis() - tiempoInicioEspera >= TIEMPO_ESPERA) {
        estadoActual = APAGANDO_SUBIR;
        ledActual = 0;
        Serial.println("Iniciando apagado...");
      }
      break;

    case ESPERANDO_APAGADO_BAJAR:
      if (millis() - tiempoInicioEspera >= TIEMPO_ESPERA) {
        estadoActual = APAGANDO_BAJAR;
        ledActual = NUM_LEDS - 1;
        Serial.println("Iniciando apagado...");
      }
      break;

    case APAGANDO_SUBIR:
      apagarLed(ledActual);
      Serial.print("Apagando LED ");
      Serial.println(ledActual);
      ledActual++;
      if (ledActual >= NUM_LEDS) {
        estadoActual = ESPERANDO;
        Serial.println("=== Ciclo completo ===");
      }
      delay(VELOCIDAD_TRANSICION);
      break;

    case APAGANDO_BAJAR:
      apagarLed(ledActual);
      Serial.print("Apagando LED ");
      Serial.println(ledActual);
      ledActual--;
      if (ledActual < 0) {
        estadoActual = ESPERANDO;
        Serial.println("=== Ciclo completo ===");
      }
      delay(VELOCIDAD_TRANSICION);
      break;
  }
}

void encenderLed(int index) {
  if (index >= 0 && index < NUM_LEDS) {
    digitalWrite(LED_PINS[index], HIGH);
    LEDsEncendidos[index] = true;
  }
}

void apagarLed(int index) {
  if (index >= 0 && index < NUM_LEDS) {
    digitalWrite(LED_PINS[index], LOW);
    LEDsEncendidos[index] = false;
  }
}

void apagarTodos() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
    LEDsEncendidos[i] = false;
  }
}
