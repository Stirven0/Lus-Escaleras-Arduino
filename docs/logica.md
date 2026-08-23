# Lógica del Programa

El sistema de control de la escalera inteligente está diseñado mediante una **máquina de estados finitos** implementada en C++ para Arduino. Garantiza un encendido/apagado progresivo, temporización no bloqueante e interrupción inmediata si ingresa un nuevo usuario.

---

## 1. Máquina de Estados Finitos

El programa consta de **7 estados principales** que controlan el flujo de operación de la escalera:

![Diagrama de Estados](imagenes/diagrama-estados.png)

### Resumen de Estados del Sistema (`EstadoSistema`)

| Nombre del Estado | Descripción del Comportamiento |
|-------------------|--------------------------------|
| `ESPERANDO_PERSONA` | **Reposo:** Luces apagadas, monitoreo constante de sensores IR. |
| `SUBIENDO_ENCENDIENDO` | Encendido secuencial de LEDs del escalón 1 al 8 (300 ms/escalón). |
| `BAJANDO_ENCENDIENDO` | Encendido secuencial de LEDs del escalón 8 al 1 (300 ms/escalón). |
| `ESPERANDO_APAGADO_SUBIR` | Todos los LEDs encendidos; temporizador no bloqueante de 5 segundos. |
| `ESPERANDO_APAGADO_BAJAR` | Todos los LEDs encendidos; temporizador no bloqueante de 5 segundos. |
| `APAGANDO_SUBIR` | Apagado secuencial del escalón 1 al 8 mediante `millis()` (300 ms/escalón). |
| `APAGANDO_BAJAR` | Apagado secuencial del escalón 8 al 1 mediante `millis()` (300 ms/escalón). |

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

### Detección por Flanco Ascendente (`detectarPasoPersona`)
Para evitar lecturas falsas o múltiples disparos cuando una persona se queda parada frente al sensor, la función evalúa la transición digital de **LOW $\rightarrow$ HIGH**:
```cpp
bool personaDetectada = (estadoAnterior == LOW && lecturaActual == HIGH);
```

### Temporización No Bloqueante con `millis()`
Durante las etapas de apagado y pausa de 5 segundos, se utiliza la función nativa `millis()` en lugar de `delay()`. Esto permite al Arduino continuar leyendo los sensores digitales en tiempo real.

### Interrupción durante el Apagado
Si durante el estado `APAGANDO_SUBIR` o `APAGANDO_BAJAR` una persona activa cualquiera de los dos sensores IR, el sistema interrumpe inmediatamente el apagado y revierte la dirección a encendido secuencial.

---

## 5. Parámetros de Tiempo

- **Pausa de la escalera encendida (`TIEMPO_PAUSA_MS`):** 5000 ms (5 segundos).
- **Velocidad de transición por escalón (`VELOCIDAD_TRANSICION_MS`):** 300 ms.
- **Duración total aproximada del ciclo:** ~9.8 segundos (Encendido 2.4s + Pausa 5.0s + Apagado 2.4s).
