# Escalera Inteligente

Maqueta de escaleras con iluminacion LED inteligente controlada por Arduino Uno.

## Descripcion

Sistema de iluminacion automatica para escaleras que detecta el movimiento de personas
y enciende los LEDs de forma secuencial en la direccion del desplazamiento.

## Componentes

- 1x Arduino Uno
- 8x LED blanco (1 por escalon)
- 8x Resistencia 220 ohm
- 2x LED emisor infrarrojo
- 2x Resistencia 100 ohm
- 2x Fototransistor receptor infrarrojo
- 2x Resistencia 10k ohm (pull-up)
- Cables jumper
- Protoboard

## Comportamiento

### Subiendo (deteccion inferior)
1. Sensor inferior detecta presencia
2. LEDs se encienden desde escalon 1 hasta 8 (300ms cada uno)
3. Espera 5 segundos
4. LEDs se apagan desde escalon 1 hasta 8 (300ms cada uno)

### Bajando (deteccion superior)
1. Sensor superior detecta presencia
2. LEDs se encienden desde escalon 8 hasta 1 (300ms cada uno)
3. Espera 5 segundos
4. LEDs se apagan desde escalon 8 hasta 1 (300ms cada uno)

## Documentacion

- [Circuito](circuito.md)
- [Logica del programa](logica.md)

## Licencia

[MIT](../LICENSE)
