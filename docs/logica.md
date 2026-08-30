# Lógica del Programa

El sistema de control de la escalera inteligente está diseñado mediante una **máquina de estados finitos** implementada en C++ para Arduino. La lógica es dinámica: las luces responden en tiempo real a la posición de la persona medida por los sensores de ultrasonido HC-SR04.

---

## 1. Máquina de Estados Finitos

El programa consta de **3 estados principales** que controlan el flujo de operación de la escalera:

![Diagrama de Estados](imagenes/diagrama-estados.png)

| Nombre del Estado | Descripción del Comportamiento |
|-------------------|--------------------------------|
| `ESPERANDO` | **Reposo:** Luces apagadas, monitoreo constante de sensores. |
| `ACERCAMIENTO` | El sensor inferior (0-20 cm) ilumina LEDs progresivamente mientras la persona se acerca. |
| `EN_ESCALERA` | El sensor superior (5-50 cm) mapea la distancia a un escalón y enciende un **foco de 3 LEDs** que sigue a la persona. |

### Transiciones

```
ESPERANDO ──(inferior detecta 0-20cm)──▶ ACERCAMIENTO ──(superior detecta 5-50cm)──▶ EN_ESCALERA
   ▲                                                                                  │
   └──────────────────────(sin contacto > 2s)──────────────────────────────────────────┘
```

- Si el sensor superior ve un objeto, tiene prioridad y pasa directo a `EN_ESCALERA`.
- La transición de regreso a `ESPERANDO` ocurre tras 2 segundos sin contacto con el sensor superior.

---

## 2. Diagrama de Flujo del Programa

Muestra la lógica de decisiones que toma el programa en cada iteración del bucle `loop()`:

![Diagrama de Flujo](imagenes/diagrama-flujo.png)

---

## 3. Diagrama de Procesos

Describe la interacción entre el hardware físico (sensores), el microcontrolador Arduino y las salidas digitales (LEDs):

![Diagrama de Procesos](imagenes/diagrama-procesos.png)

---

## 4. Conceptos Clave de Implementación

### Medición de Distancia (`medirDistancia`)
Función básica para HC-SR04: emite pulso de Trigger (10 µs), mide el ancho del pulso en Echo con `pulseIn()` (timeout de 10 ms) y convierte a centímetros:
```cpp
long duracion = pulseIn(pinEcho, HIGH, 10000);
if (duracion == 0) return -1.0;      // sin eco (objeto fuera de rango)
return duracion * 0.034 / 2.0;       // cm
```

### Filtrado por Mediana (`medirDistanciaFiltrada`)
Para evitar lecturas erráticas producidas por ruido acústico o reflexiones, se toman 3 muestras consecutivas (separadas por 40 ms) y se obtiene la mediana ordenando el arreglo:
```cpp
float medirDistanciaFiltrada(int pinTrig, int pinEcho) {
  float muestras[CANTIDAD_MUESTRAS];
  for (int i = 0; i < CANTIDAD_MUESTRAS; i++) {
    muestras[i] = medirDistancia(pinTrig, pinEcho);
    if (i < CANTIDAD_MUESTRAS - 1) delayMicroseconds(40000);
  }
  // Ordenamiento para seleccionar la mediana
  ...
  return muestras[CANTIDAD_MUESTRAS / 2];
}
```

### Ramp Up por Acercamiento (`encenderRango`)
Mientras la persona se acerca (distancia de 20 cm a 0 cm en sensor inferior), se encienden progresivamente los LEDs desde la base:
```cpp
int cantidadLEDs = map(distanciaInferior, DIST_INFERIOR_MAX, 0, 1, CANTIDAD_LEDS);
cantidadLEDs = constrain(cantidadLEDs, 1, CANTIDAD_LEDS);
encenderRango(cantidadLEDs);
```

### Mapeo Distancia → Escalón (Sensor Superior)
La distancia medida por el sensor superior se convierte en el índice del escalón donde se encuentra la persona:
```cpp
int escalonActual = map(distanciaSuperior, DIST_SUPERIOR_MIN, DIST_SUPERIOR_MAX, CANTIDAD_LEDS - 1, 0);  // 5cm=arriba (7), 50cm=abajo (0)
escalonActual = constrain(escalonActual, 0, CANTIDAD_LEDS - 1);
```

### Foco Móvil de 3 LEDs (`encenderFoco`)
Se encienden el escalón actual y sus vecinos adyacentes (`radio = 1`); el resto de escalones se mantienen apagados, logrando que el foco lumínico acompañe dinámicamente el desplazamiento:
```cpp
void encenderFoco(int centro, int radio) {
  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    bool activar = (i >= centro - radio && i <= centro + radio);
    digitalWrite(PINES_LEDS[i], activar ? HIGH : LOW);
  }
}
```

### Timeout sin Contacto
Si el sensor superior no detecta presencia durante más de 2000 ms (`TIEMPO_SIN_CONTACTO_MAX`), se invoca `apagarTodos()` y el sistema retorna al estado `ESPERANDO`.

---

## 5. Parámetros del Sistema

| Parámetro | Constante | Valor | Descripción |
|-----------|-----------|:-----:|-------------|
| Cantidad de LEDs | `CANTIDAD_LEDS` | 8 | Un LED por escalón (D2 a D9) |
| Alcance inferior | `DIST_INFERIOR_MAX` | 20.0 cm | Distancia de activación para acercamiento |
| Alcance superior mín. | `DIST_SUPERIOR_MIN` | 5.0 cm | Distancia correspondiente al escalón superior (8) |
| Alcance superior máx. | `DIST_SUPERIOR_MAX` | 50.0 cm | Distancia correspondiente al escalón inferior (1) |
| Timeout sin contacto | `TIEMPO_SIN_CONTACTO_MAX` | 2000 ms | Tiempo de espera antes de apagar luces |
| Muestras de filtro | `CANTIDAD_MUESTRAS` | 3 | Lecturas para cálculo de mediana |

---

## 6. Probar en Simulador

Puedes validar y observar el comportamiento de la máquina de estados en el simulador interactivo:

🔗 **[Abrir Simulación en Tinkercad](https://www.tinkercad.com/things/0pheYHJu6yR-lus-escaleras-arduino/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=S3InYTMaIszsQmBVlUAJu1_tCbUvaevH3J8RIkOQQLU)**