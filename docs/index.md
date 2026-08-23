# Escalera Inteligente

Maqueta de escaleras con iluminación LED inteligente controlada por **Arduino Uno**.

## Descripción del Proyecto

Sistema de iluminación automática para escaleras que detecta el movimiento de personas mediante sensores infrarrojos (IR) y enciende los LEDs de forma secuencial según la dirección de desplazamiento (subiendo o bajando).

---

## ⚡ Simulación Virtual

Puedes interactuar con el circuito virtualmente en Tinkercad:

🔗 **[Abrir Simulación en Tinkercad](https://www.tinkercad.com/things/0pheYHJu6yR/editel?sharecode=S3InYTMaIszsQmBVlUAJu1_tCbUvaevH3J8RIkOQQLU)**

![Esquema de Simulación en Tinkercad](imagenes/Lus%20Escaleras%20Arduino.png)

---

## Componentes del Hardware

| Cantidad | Componente | Función | Conexión Arduino |
|:--------:|------------|---------|------------------|
| 1 | **Arduino Uno** | Microcontrolador principal | Puerto USB (Alimentación 5V) |
| 8 | **LED blanco** | Iluminación de cada escalón (1 a 8) | Pines D2 a D9 |
| 8 | **Resistencia 220 Ω** | Protección y limitación de corriente para LEDs | En serie con ánodo de los LEDs |
| 2 | **LED emisor IR** | Fuente de luz infrarroja continua | Alimentación 5V con res. 100 Ω |
| 2 | **Fototransistor receptor IR** | Detección de presencia física por corte de haz | Pines D10 (Inferior) y D11 (Superior) |
| 2 | **Resistencia 10k Ω** | Pull-up para fototransistores receptores | Conectadas a 5V en receptores |
| — | **Cables Jumper y Protoboard** | Interconexiones del circuito | — |

---

## Comportamiento del Sistema

### 🧗 Subiendo (Detección por Sensor Inferior en Pin D10)
1. El sensor inferior detecta el corte del haz infrarrojo.
2. Los LEDs se encienden secuencialmente del escalón 1 al 8 (**300 ms** entre cada uno).
3. Permanece la escalera totalmente iluminada durante **5 segundos**.
4. Los LEDs se apagan secuencialmente del escalón 1 al 8 (**300 ms** entre cada uno).

### 🚶 Bajando (Detección por Sensor Superior en Pin D11)
1. El sensor superior detecta el corte del haz infrarrojo.
2. Los LEDs se encienden secuencialmente del escalón 8 al 1 (**300 ms** entre cada uno).
3. Permanece la escalera totalmente iluminada durante **5 segundos**.
4. Los LEDs se apagan secuencialmente del escalón 8 al 1 (**300 ms** entre cada uno).

---

## Guía de Documentación y Diagramas

- 📐 **[Esquema de Circuito y Conexiones](circuito.md):** Tabla completa de pines, resistencias, simulación y Diagrama EPS.
- ⚙️ **[Lógica del Programa y Diagramas](logica.md):** Máquina de estados finitos, Diagrama de Flujo y Diagrama de Procesos.

---

## Licencia

Este proyecto se distribuye bajo la licencia [MIT](../LICENSE).
