const int PINES_LEDS[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int CANTIDAD_LEDS = 8;

const int PIN_SENSOR_INFERIOR = 10;
const int PIN_SENSOR_SUPERIOR = 11;

const unsigned long TIEMPO_PAUSA_MS = 5000;
const unsigned long VELOCIDAD_TRANSICION_MS = 300;

enum EstadoSistema {
  ESPERANDO_PERSONA,
  SUBIENDO_ENCENDIENDO,
  BAJANDO_ENCENDIENDO,
  ESPERANDO_APAGADO_SUBIR,
  ESPERANDO_APAGADO_BAJAR,
  APAGANDO_SUBIR,
  APAGANDO_BAJAR
};

EstadoSistema estadoActual = ESPERANDO_PERSONA;

unsigned long tiempoInicioPausa = 0;
unsigned long tiempoUltimoApagado = 0;
int escalonActual = 0;

bool lecturaAnteriorInferior = LOW;
bool lecturaAnteriorSuperior = LOW;

bool detectarPasoPersona(int pinSensor, bool &estadoAnterior) {
  bool lecturaActual = digitalRead(pinSensor);
  bool personaDetectada = (estadoAnterior == LOW && lecturaActual == HIGH);
  estadoAnterior = lecturaActual;
  return personaDetectada;
}

void setup() {
  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    pinMode(PINES_LEDS[i], OUTPUT);
    digitalWrite(PINES_LEDS[i], LOW);
  }

  pinMode(PIN_SENSOR_INFERIOR, INPUT);
  pinMode(PIN_SENSOR_SUPERIOR, INPUT);

  lecturaAnteriorInferior = digitalRead(PIN_SENSOR_INFERIOR);
  lecturaAnteriorSuperior = digitalRead(PIN_SENSOR_SUPERIOR);
}

void loop() {
  bool personaEnInferior = detectarPasoPersona(PIN_SENSOR_INFERIOR, lecturaAnteriorInferior);
  bool personaEnSuperior = detectarPasoPersona(PIN_SENSOR_SUPERIOR, lecturaAnteriorSuperior);

  switch (estadoActual) {

    case ESPERANDO_PERSONA:
      if (personaEnInferior) {
        estadoActual = SUBIENDO_ENCENDIENDO;
        escalonActual = 0;
      } else if (personaEnSuperior) {
        estadoActual = BAJANDO_ENCENDIENDO;
        escalonActual = CANTIDAD_LEDS - 1;
      }
      break;

    case SUBIENDO_ENCENDIENDO:
      digitalWrite(PINES_LEDS[escalonActual], HIGH);
      escalonActual++;
      if (escalonActual >= CANTIDAD_LEDS) {
        estadoActual = ESPERANDO_APAGADO_SUBIR;
        tiempoInicioPausa = millis();
      }
      delay(VELOCIDAD_TRANSICION_MS);
      break;

    case BAJANDO_ENCENDIENDO:
      digitalWrite(PINES_LEDS[escalonActual], HIGH);
      escalonActual--;
      if (escalonActual < 0) {
        estadoActual = ESPERANDO_APAGADO_BAJAR;
        tiempoInicioPausa = millis();
      }
      delay(VELOCIDAD_TRANSICION_MS);
      break;

    case ESPERANDO_APAGADO_SUBIR:
      if (personaEnInferior) {
        estadoActual = SUBIENDO_ENCENDIENDO;
        escalonActual = 0;
      } else if (personaEnSuperior) {
        estadoActual = BAJANDO_ENCENDIENDO;
        escalonActual = CANTIDAD_LEDS - 1;
      } else if (millis() - tiempoInicioPausa >= TIEMPO_PAUSA_MS) {
        estadoActual = APAGANDO_SUBIR;
        escalonActual = 0;
        tiempoUltimoApagado = millis();
      }
      break;

    case ESPERANDO_APAGADO_BAJAR:
      if (personaEnInferior) {
        estadoActual = SUBIENDO_ENCENDIENDO;
        escalonActual = 0;
      } else if (personaEnSuperior) {
        estadoActual = BAJANDO_ENCENDIENDO;
        escalonActual = CANTIDAD_LEDS - 1;
      } else if (millis() - tiempoInicioPausa >= TIEMPO_PAUSA_MS) {
        estadoActual = APAGANDO_BAJAR;
        escalonActual = CANTIDAD_LEDS - 1;
        tiempoUltimoApagado = millis();
      }
      break;

    case APAGANDO_SUBIR:
      if (personaEnInferior) {
        estadoActual = SUBIENDO_ENCENDIENDO;
        escalonActual = 0;
      } else if (personaEnSuperior) {
        estadoActual = BAJANDO_ENCENDIENDO;
        escalonActual = CANTIDAD_LEDS - 1;
      } else if (millis() - tiempoUltimoApagado >= VELOCIDAD_TRANSICION_MS) {
        digitalWrite(PINES_LEDS[escalonActual], LOW);
        escalonActual++;
        tiempoUltimoApagado = millis();
        if (escalonActual >= CANTIDAD_LEDS) {
          estadoActual = ESPERANDO_PERSONA;
        }
      }
      break;

    case APAGANDO_BAJAR:
      if (personaEnInferior) {
        estadoActual = SUBIENDO_ENCENDIENDO;
        escalonActual = 0;
      } else if (personaEnSuperior) {
        estadoActual = BAJANDO_ENCENDIENDO;
        escalonActual = CANTIDAD_LEDS - 1;
      } else if (millis() - tiempoUltimoApagado >= VELOCIDAD_TRANSICION_MS) {
        digitalWrite(PINES_LEDS[escalonActual], LOW);
        escalonActual--;
        tiempoUltimoApagado = millis();
        if (escalonActual < 0) {
          estadoActual = ESPERANDO_PERSONA;
        }
      }
      break;
  }
}
