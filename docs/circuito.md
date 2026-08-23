# Circuito Eléctrico y Conexiones

Este documento detalla la distribución de componentes, el código de resistencias, el diagrama EPS y la simulación interactiva del proyecto **Escalera Inteligente**.

---

## 1. Simulación Interactiva en Tinkercad

Puedes explorar y probar el circuito en tiempo real a través de Tinkercad:

🔗 **[Ver Simulación Interactiva en Tinkercad](https://www.tinkercad.com/things/0pheYHJu6yR/editel?sharecode=S3InYTMaIszsQmBVlUAJu1_tCbUvaevH3J8RIkOQQLU)**

![Simulación del Circuito en Tinkercad](imagenes/Lus%20Escaleras%20Arduino.png)

---

## 2. Esquema de Conexión de LEDs (Escalones 1 al 8)

Cada escalón posee un LED blanco con su respectiva resistencia limitadora de corriente de $220\,\Omega$.

| Escalón | Pin Arduino | Tipo de Conexión |
|:-------:|:-----------:|------------------|
| **1 (Inferior)** | `D2` | Pin D2 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **2** | `D3` | Pin D3 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **3** | `D4` | Pin D4 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **4** | `D5` | Pin D5 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **5** | `D6` | Pin D6 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **6** | `D7` | Pin D7 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **7** | `D8` | Pin D8 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |
| **8 (Superior)** | `D9` | Pin D9 $\rightarrow$ Resistencia $220\,\Omega$ $\rightarrow$ Ánodo LED $\rightarrow$ Cátodo LED $\rightarrow$ GND |

---

## 3. Esquema de Sensores Infrarrojos (IR)

El sistema utiliza 2 pares de infrarrojos (emisor + receptor) para detectar la llegada de usuarios:

| Componente | Pin Arduino | Esquema de Conexión Eléctrica |
|------------|:-----------:|--------------------------------|
| **Emisor IR Inferior** | — | 5V $\rightarrow$ Resistencia $100\,\Omega$ $\rightarrow$ Ánodo LED IR $\rightarrow$ Cátodo $\rightarrow$ GND |
| **Receptor IR Inferior** | `D10` | 5V $\rightarrow$ Resistencia Pull-Up $10\,\mathrm{k}\Omega$ $\rightarrow$ Colector Fototransistor (Pin D10 a Colector), Emisor $\rightarrow$ GND |
| **Emisor IR Superior** | — | 5V $\rightarrow$ Resistencia $100\,\Omega$ $\rightarrow$ Ánodo LED IR $\rightarrow$ Cátodo $\rightarrow$ GND |
| **Receptor IR Superior** | `D11` | 5V $\rightarrow$ Resistencia Pull-Up $10\,\mathrm{k}\Omega$ $\rightarrow$ Colector Fototransistor (Pin D11 a Colector), Emisor $\rightarrow$ GND |

---

## 4. Especificación de Resistencias

- **$220\,\Omega$** *(Marrón - Rojo - Marrón)*: Limitador de corriente para LEDs blancos de cada escalón.
- **$100\,\Omega$** *(Marrón - Negro - Marrón)*: Limitador de corriente para los LEDs emisores de luz infrarroja.
- **$10\,\mathrm{k}\Omega$** *(Marrón - Negro - Naranja)*: Resistencia de pull-up para estabilizar la señal de los fototransistores receptores.

---

## 5. Diagrama EPS (Entrada - Proceso - Salida)

![Diagrama EPS](imagenes/diagrama-eps.png)
