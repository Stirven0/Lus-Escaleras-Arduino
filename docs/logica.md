# Logica del Programa

## Diagrama de Flujo

![Diagrama de Flujo](imagenes/diagrama-flujo.png)

## Diagrama de Procesos

![Diagrama de Procesos](imagenes/diagrama-procesos.png)

## Estados del Sistema

El programa utiliza una maquina de estados con 5 estados:

| Estado | Descripcion |
|--------|-------------|
| ESPERANDO | Sin deteccion, esperando señal de sensor |
| SUBIENDO | Encendiendo LEDs de abajo hacia arriba (1→8) |
| BAJANDO | Encendiendo LEDs de arriba hacia abajo (8→1) |
| ESPERANDO_APAGADO_SUBIR | Todos encendidos, esperando 5s antes de apagar |
| ESPERANDO_APAGADO_BAJAR | Todos encendidos, esperando 5s antes de apagar |

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

## Codigo Fuente

El codigo completo esta en `Lus-Escaleras-Arduino.ino`.
