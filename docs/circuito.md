# Circuito Eléctrico y Conexiones

Este documento detalla la distribución de componentes, el esquema de conexión y el diagrama EPS del proyecto **Escalera Inteligente**.

---

## 1. Esquema de Conexión de LEDs (Escalones 1 al 8)

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

## 2. Esquema de Sensores de Ultrasonido HC-SR04

El sistema utiliza **2 sensores de ultrasonido HC-SR04** (4 pines cada uno) para medir la distancia de la persona:

| Sensor | Pin Arduino | Esquema de Conexión Eléctrica |
|--------|:-----------:|--------------------------------|
| **Superior** (parte alta de la escalera, apunta hacia abajo) | `Trig=D10`, `Echo=D11` | VCC $\rightarrow$ 5V, Trig $\rightarrow$ D10, Echo $\rightarrow$ D11, GND $\rightarrow$ GND |
| **Inferior** (pie de la escalera, apunta hacia afuera) | `Trig=D12`, `Echo=D13` | VCC $\rightarrow$ 5V, Trig $\rightarrow$ D12, Echo $\rightarrow$ D13, GND $\rightarrow$ GND |

> **Nota:** El sensor inferior mide hasta **20 cm** (zona de acercamiento). El sensor superior mide de **5 a 50 cm** sobre la escalera. Rangos superiores se ignoran para evitar falsos positivos.

---

## 3. Especificación de Resistencias

- **$220\,\Omega$** *(Marrón - Rojo - Marrón)*: Limitador de corriente para LEDs blancos de cada escalón.

---

## 4. Alimentación

El Arduino se alimenta exclusivamente por **puerto USB**. Los sensores HC-SR04 reciben 5V desde los pines del Arduino (`VCC`) y comparten masa (`GND`) con el resto del circuito.

---

## 5. Diagrama EPS (Entrada - Proceso - Salida)

![Diagrama EPS](imagenes/diagrama-eps.png)