# AGENTS.md - Instrucciones para Agentes IA

## Qué es este proyecto

Maqueta de escaleras inteligentes con iluminación LED controlada por Arduino Uno.
Proyecto universitario: 8 escalones con LEDs blancos, 2 sensores de ultrasonido
HC-SR04 (arriba/abajo), alimentación por USB del Arduino.

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
test-ultrasonidos/            # Sketch de prueba de sensores (con Serial)
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
- Sin debug Serial en producción
- Resistencias: 220 ohm para LEDs blancos
- Pinout fijo:
  - LEDs en D2-D9
  - Ultrasonido superior: Trig D10, Echo D11
  - Ultrasonido inferior: Trig D12, Echo D13
  - VCC/GND de sensores a 5V/GND
- Sensor inferior (0-20cm): ramp up de LEDs mientras la persona se acerca
- Sensor superior (5-50cm): foco de 3 LEDs que sigue la posición de la persona
- Mapeo distancia→escalón: superior 5cm=escalón 8, 50cm=escalón 1
- Timeout 2s sin contacto para volver a ESPERANDO