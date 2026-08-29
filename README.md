# Escalera Inteligente con Arduino Uno

Maqueta de escaleras con iluminación LED inteligente controlada por **Arduino Uno**.

---

## 📌 Descripción

Sistema de iluminación automática para escaleras de **8 escalones**. Utiliza dos
sensores de **ultrasonido HC-SR04** (parte inferior y superior) para detectar la
posición de la persona y encender los LEDs de forma dinámica: el sensor inferior
ilumina progresivamente mientras la persona se acerca, y el sensor superior sigue
a la persona con un foco de luz mientras sube o baja.

---

## 🛠️ Componentes Hardware

| Cantidad | Componente | Conexión |
|:--------:|------------|----------|
| 1 | Arduino Uno | Alimentación por USB |
| 8 | LED Blanco (Escalones 1 al 8) | Pines D2 a D9 |
| 8 | Resistencia 220 Ω | En serie con cada LED |
| 2 | Sensor Ultrasonido HC-SR04 | Superior Trig/echo D10/D11, Inferior Trig/echo D12/D13 |
| — | Protoboard y Jumpers | Interconexión de componentes |

---

## 🔄 Funcionamiento

### 🚶 Acercamiento (Sensor Inferior, 0-20 cm)
El sensor inferior apunta hacia afuera de la escalera. Mientras la persona se
acerca, los LEDs se encienden progresivamente desde abajo (a menor distancia,
más escalones iluminados).

### 🧗 En la Escalera (Sensor Superior, 5-50 cm)
El sensor superior apunta hacia abajo de la escalera y mapea la distancia a la
posición de la persona. Un **foco de 3 LEDs** sigue a la persona en tiempo real
mientras sube o baja, encendiendo los escalones cercanos y apagando los que quedan atrás.

- Distancia 5 cm → escalón 8 (parte alta)
- Distancia 50 cm → escalón 1 (parte baja)

### ⏱️ Sin Contacto
Si el sensor superior deja de detectar a la persona durante **2 segundos**, todos
los LEDs se apagan y el sistema vuelve al estado de espera.

---

## 💻 Compilar y Cargar

```bash
# Compilar el código
arduino-cli compile --fqbn arduino:avr:uno Lus-Escaleras-Arduino.ino

# Cargar al Arduino Uno (ajustar puerto según corresponda)
arduino-cli upload --fqbn arduino:avr:uno --port /dev/ttyACM0 Lus-Escaleras-Arduino.ino
```

---

## 📊 Diagramas y Documentación

Toda la documentación detallada está disponible en las páginas del proyecto y en el directorio `docs/`:

- 📐 **[Circuito y Conexiones](docs/circuito.md)** (Esquema de pines y Diagrama EPS)
- ⚙️ **[Lógica del Programa](docs/logica.md)** (Máquina de Estados, Diagrama de Flujo y Diagrama de Procesos)

---

## 📄 Licencia

Este proyecto está bajo la Licencia [MIT](LICENSE).