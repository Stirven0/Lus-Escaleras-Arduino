# Escalera Inteligente

Maqueta de escaleras con iluminacion LED inteligente controlada por Arduino Uno.

## Descripcion

Sistema de iluminacion automatica que detecta movimiento mediante sensores infrarrojos
y enciende 8 LEDs de forma secuencial segun la direccion de desplazamiento.

## Componentes

| Cantidad | Componente |
|----------|------------|
| 1 | Arduino Uno |
| 8 | LED blanco |
| 8 | Resistencia 220 ohm |
| 2 | LED emisor infrarrojo |
| 2 | Resistencia 100 ohm |
| 2 | Fototransistor receptor IR |
| 2 | Resistencia 10k ohm |
| — | Cables jumper y protoboard |

## Comportamiento

**Subiendo** (sensor inferior detecta):
LEDs 1→2→3→4→5→6→7→8 encendidos → espera 5s → apagados 1→2→3→4→5→6→7→8

**Bajando** (sensor superior detecta):
LEDs 8→7→6→5→4→3→2→1 encendidos → espera 5s → apagados 8→7→6→5→4→3→2→1

Transicion: 300ms por escalon.

## Cableado

```
LEDs:      D2-D9 → 220 ohm → LED → GND
Sensor IR: 5V → 100 ohm → Emisor → GND
Receptor:  5V → 10k ohm → Colector (D10/D11), Emisor → GND
```

## Compilar y cargar

```bash
# Compilar
arduino-cli compile --fqbn arduino:avr:uno Lus-Escaleras-Arduino.ino

# Cargar
arduino-cli upload --fqbn arduino:avr:uno --port /dev/ttyACM0 Lus-Escaleras-Arduino.ino
```

## Documentacion

Visita la [pagina del proyecto](https://tu-usuario.github.io/Lus-Escaleras-Arduino/)
para ver diagramas de flujo, procesos y EPS.

## Licencia

[MIT](LICENSE)
