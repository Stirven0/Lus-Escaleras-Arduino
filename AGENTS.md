# AGENTS.md - Instrucciones para Agentes IA

## Qué es este proyecto

Maqueta de escaleras inteligentes con iluminación LED controlada por Arduino Uno.
Proyecto universitario: 8 escalones con LEDs blancos, 2 sensores IR (arriba/abajo),
alimentación por USB del Arduino.

## Compilar y cargar

```bash
# Compilar
arduino-cli compile --fqbn arduino:avr:uno Lus-Escaleras-Arduino.ino

# Cargar al Arduino (ajustar puerto)
arduino-cli upload --fqbn arduino:avr:uno --port /dev/ttyACM0 Lus-Escaleras-Arduino.ino
```

## Estructura

```
Lus-Escaleras-Arduino.ino    # Código principal
diagramas/                    # Fuentes PlantUML
docs/                         # Documentación GitHub Pages
```

## Diagramas PlantUML

Para renderizar PNGs:
```bash
java -jar /home/stirven/Compyler/doc/plantuml-mit-1.2026.6.jar -tpng diagramas/*.puml -o ../docs/imagenes/
```

## Convenciones

- Código en español (nombres de variables, funciones, comentarios)
- Sin librerías externas, solo Arduino core
- Resistencias: 220 ohm para LEDs blancos, 100 ohm para IR emisor, 10k ohm pull-up para IR receptor
- Pinout fijo: LEDs en D2-D9, sensores en D10 (inferior) y D11 (superior)
- Transición: 300ms por escalón, 5 segundos de pausa
