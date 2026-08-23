# Escalera Inteligente con Arduino Uno

Maqueta de escaleras con iluminación LED inteligente controlada por **Arduino Uno**.

---

## 📌 Descripción

Sistema de iluminación automática para escaleras de **8 escalones**. Utiliza sensores infrarrojos (IR) en la parte inferior y superior para detectar la presencia de personas y encender los LEDs en secuencia según la dirección de desplazamiento.

---

## ⚡ Simulación Interactiva en Tinkercad

Puedes probar el circuito y el funcionamiento de las luces directamente desde tu navegador:

🔗 **[Ver Simulación en Tinkercad](https://www.tinkercad.com/things/0pheYHJu6yR/editel?sharecode=S3InYTMaIszsQmBVlUAJu1_tCbUvaevH3J8RIkOQQLU)**

![Simulación del Circuito Tinkercad](docs/imagenes/Lus%20Escaleras%20Arduino.png)

---

## 🛠️ Componentes Hardware

| Cantidad | Componente | Conexión |
|:--------:|------------|----------|
| 1 | Arduino Uno | Alimentación por USB |
| 8 | LED Blanco (Escalones 1 al 8) | Pines D2 a D9 |
| 8 | Resistencia 220 Ω | En serie con cada LED |
| 2 | LED Emisor Infrarrojo | Conectados a 5V con resistencia 100 Ω |
| 2 | Fototransistor Receptor IR | Pines D10 (Inferior) y D11 (Superior) con pull-up 10k Ω |
| — | Protoboard y Jumpers | Interconexión de componentes |

---

## 🔄 Funcionamiento

* **Subiendo (Sensor Inferior en Pin D10):**
  * Encendido secuencial: Escalón 1 $\rightarrow$ 8 (300 ms por escalón).
  * Pausa: 5 segundos encendidos.
  * Apagado no bloqueante: Escalón 1 $\rightarrow$ 8 (300 ms por escalón).

* **Bajando (Sensor Superior en Pin D11):**
  * Encendido secuencial: Escalón 8 $\rightarrow$ 1 (300 ms por escalón).
  * Pausa: 5 segundos encendidos.
  * Apagado no bloqueante: Escalón 8 $\rightarrow$ 1 (300 ms por escalón).

---

## 💻 Compilar y Cargar

Para compilar y subir el programa mediante `arduino-cli`:

```bash
# Compilar el código
arduino-cli compile --fqbn arduino:avr:uno Lus-Escaleras-Arduino.ino

# Cargar al Arduino Uno (ajustar puerto según corresponda)
arduino-cli upload --fqbn arduino:avr:uno --port /dev/ttyACM0 Lus-Escaleras-Arduino.ino
```

---

## 📊 Diagramas y Documentación

Toda la documentación detallada está disponible en las páginas del proyecto y en el directorio `docs/`:

* 📐 **[Circuito y Conexiones](docs/circuito.md)** (Esquema de pines, simulación en Tinkercad y Diagrama EPS)
* ⚙️ **[Lógica del Programa](docs/logica.md)** (Máquina de Estados, Diagrama de Flujo y Diagrama de Procesos)

---

## 📄 Licencia

Este proyecto está bajo la Licencia [MIT](LICENSE).
