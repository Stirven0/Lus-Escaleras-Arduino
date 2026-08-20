# Logica del Programa

## Diagrama de Flujo

![Diagrama de Flujo](imagenes/diagrama-flujo.png)

## Diagrama de Procesos

![Diagrama de Procesos](imagenes/diagrama-procesos.png)

## Estados del Sistema

El programa utiliza una maquina de estados con 7 estados:

| Estado | Descripcion |
|--------|-------------|
| ESPERANDO | Sin deteccion, esperando señal de sensor |
| SUBIENDO | Encendiendo LEDs de abajo hacia arriba (1→8) |
| BAJANDO | Encendiendo LEDs de arriba hacia abajo (8→1) |
| ESPERANDO_APAGADO_SUBIR | Todos encendidos, esperando 5s antes de apagar |
| ESPERANDO_APAGADO_BAJAR | Todos encendidos, esperando 5s antes de apagar |
| APAGANDO_SUBIR | Apagando LEDs de abajo hacia arriba (1→8) |
| APAGANDO_BAJAR | Apagando LEDs de arriba hacia abajo (8→1) |

## Tiempos

- **Transicion**: 300 milisegundos por escalon
- **Espera**: 5 segundos con todos los LEDs encendidos
- **Ciclo completo**: ~10 segundos (encendido + espera + apagado)

## Deteccion de Direccion

- **Sensor inferior (D10) activo**: Persona detectada abajo → secuencia SUBIR
- **Sensor superior (D11) activo**: Persona detectada arriba → secuencia BAJAR

Los sensores IR funcionan por ruptura de haz: el emisor siempre esta encendido
y el receptor detecta la luz infrarroja. Cuando un objeto interrumpe el haz,
el receptor cambia de estado.

La deteccion se realiza por flanco ascendente (cambio de LOW a HIGH), lo que
evita falsos positivos por fluctuaciones de la señal.

## Interrupcion durante Apagado

Durante la secuencia de apagado (APAGANDO_SUBIR/APAGANDO_BAJAR) y la espera
antes de apagar (ESPERANDO_APAGADO_SUBIR/ESPERANDO_APAGADO_BAJAR), el sistema
lee constantemente los sensores IR.

Si se detecta un nuevo movimiento:
- Los LEDs que aun estan encendidos permanecen encendidos (no se apagan)
- Los LEDs que ya se apagaron se prenden de nuevo secuencialmente
- Se inicia la nueva secuencia de encendido en la direccion correspondiente
- Cada LED respeta los 300ms de transicion

## Codigo Fuente

El codigo completo esta en `Lus-Escaleras-Arduino.ino`.
