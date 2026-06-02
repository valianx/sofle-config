# sofle-config

Configuración QMK del teclado **Sofle RGB** (keymap `mario`), puro por código, sin VIA.
Portado desde mi config del Corne (https://github.com/valianx/corne-config) al Sofle, que suma fila numérica dedicada, 5 thumbs por mano y rotary encoders.

## Hardware

- **Teclado:** Sofle RGB (58 teclas, split, hot-swap, TRRS).
- **Controladores:** Pro Micro (AVR atmega32u4). Flash ~28KB, muy ajustado → se usa `LTO_ENABLE`.
- **OLED:** 0.91" SSD1306 en ambas mitades.
- **RGB:** underglow (LEDs abajo, no per-key) → `RGBLIGHT`, no RGB Matrix.
- **Encoders:** 2 rotary EC11 (uno por mano).

## Target

- Keyboard: `sofle/rev1`
- Keymap: `mario`

## Estructura

```
sofle-config/
├── qmk.json                                  # registra el build target como external userspace
├── keyboards/sofle/keymaps/mario/
│   ├── config.h                              # tapping term, OLED, rgblight, ahorro de flash
│   ├── rules.mk                              # features (LTO, RGBLIGHT, ENCODER, OLED), VIA off
│   └── keymap.c                              # 3 capas, tap-dance, encoder, OLED (perro/gato), RGB por capa
├── .gitignore
└── README.md
```

### Nota sobre external userspace

Este repo es un **QMK external userspace**: no contiene el firmware de QMK, solo el keymap.
QMK moderno permite compilar un keymap que vive fuera del árbol de `qmk_firmware`.

1. Tener `qmk_firmware` clonado y el CLI de QMK instalado (`python3 -m pip install qmk`, luego `qmk setup`).
2. Apuntar el CLI a este userspace:
   ```
   qmk config user.overlay_dir="$(realpath .)"
   ```
   (ejecutado desde la raíz de este repo).
3. Compilar/flashear normalmente con el target `sofle/rev1 -km mario`.

Alternativa sin overlay: copiar `keyboards/sofle/keymaps/mario/` dentro de tu clon de `qmk_firmware` en la misma ruta y compilar desde ahí.

## Compilar y flashear

```
# Compilar (genera el .hex)
qmk compile -kb sofle/rev1 -km mario

# Flashear (entra en modo flash y graba)
qmk flash -kb sofle/rev1 -km mario
```

### Poner cada mitad en bootloader (RESET)

El Pro Micro no tiene reset por software por defecto, así que se hace por hardware:

1. Conectá **una** mitad por USB.
2. Puenteá los pines **RST** y **GND** del Pro Micro **dos veces seguidas, rápido** (doble toque), o presioná el botón de reset si tu PCB lo trae.
3. La placa entra en modo bootloader (~8s) — ahí `qmk flash` la graba.
4. Repetí con la **otra mitad** (conectála por USB y volvé a hacer el doble reset).

> Ambas mitades llevan el **mismo** firmware. `SPLIT_USB_DETECT` hace que la mitad conectada por USB sea la master automáticamente.

## Capas

Tres capas: `_BASE`, `_LOWER`, `_RAISE`. `LOWER` y `RAISE` son momentáneas (se activan mientras se mantiene la tecla).

### Capa 0 — _BASE (QWERTY + fila numérica, pensada para gaming)

```
,-----------------------------------------.                    ,-----------------------------------------.
|  `  |  1  |  2  |  3  |  4  |  5  |                          |  6  |  7  |  8  |  9  |  0  |  =  |
|-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----|
| Tab |  Q  |  W  |  E  |  R  |  T  |                          |  Y  |  U  |  I  |  O  |  P  | Bsp |
|-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----|
| Ctrl|  A  |  S  |  D  |  F  |  G  |                          |  H  |  J  |  K  |  L  |  ;  |  '  |
|-----+-----+-----+-----+-----+-----+-----.        ,-----+-----+-----+-----+-----+-----+-----+-----|
| TDsf|  Z  |  X  |  C  |  V  |  B  |Mute |        |Mute |  N  |  M  |  ,  |  .  |  /  |Shift|
`-----------------+-----+-----+-----+-----+-----.  ,-----+-----+-----+-----+-----------------------'
                  | GUI | Alt | Ctrl|LOWER|Enter|  |Space|RAISE| Ctrl| Alt | GUI |
                  `-----------------------------'  `-----------------------------'
```

- **TDsf** = tap-dance: 1 pulso = `Shift`, 2 pulsos = `Caps Lock`.
- Los `! @ # $ % ^ & * ( )` salen con `Shift` + número.
- **Encoder (base):** girar = volumen ↑/↓. Push de encoder = `Mute`.

### Capa 1 — _LOWER (numpad 10-key izq + símbolos de programación der)

```
,-----------------------------------------.                    ,-----------------------------------------.
|     |     |  7  |  8  |  9  |     |                          |  ^  |  &  |  *  |  (  |  )  | Bsp |
|-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----|
|     |     |  4  |  5  |  6  |     |                          |  -  |  =  |  [  |  ]  |  \  |  |  |
|-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----|
|     |  0  |  1  |  2  |  3  |     |                          |  {  |  }  |  ?  |  '  |  "  |     |
|-----+-----+-----+-----+-----+-----+-----.        ,-----+-----+-----+-----+-----+-----+-----+-----|
|     |     |     |     |     |     |     |        |     |     |     |     |     |     |     |
`-----------------+-----+-----+-----+-----+-----.  ,-----+-----+-----+-----------------------------'
                  |     |     |     |     |Enter|  |Space|RAISE|     |     |     |
                  `-----------------------------'  `-----------------------------'
```

- Numpad sobre las columnas W-E-R / S-D-F / X-C-V de la mano izquierda.
- **Encoder (lower):** girar = `PgUp` / `PgDn` (scroll de página).

### Capa 2 — _RAISE (F-keys en fila numérica + flechas inverted-T)

```
,-----------------------------------------.                    ,-----------------------------------------.
|     | F1  | F2  | F3  | F4  | F5  |                          | F6  | F7  | F8  | F9  | F10 | F11 |
|-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----|
|     |     |     |     |     |     |                          |PgUp |Home |  ↑  |End  | F12 | Bsp |
|-----+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+-----|
| Ctrl| HUI | HUD |RGBtg|     |     |                          |PgDn |  ←  |  ↓  |  →  |     |     |
|-----+-----+-----+-----+-----+-----+-----.        ,-----+-----+-----+-----+-----+-----+-----+-----|
|Shift|     |     |     |     |     |     |        |     |     |     |     |     |     |     |
`-----------------+-----+-----+-----+-----+-----.  ,-----+-----+-----+-----------------------------'
                  |     |     |     |LOWER|Enter|  |Space|     |     |     |     |
                  `-----------------------------'  `-----------------------------'
```

- Flechas **inverted-T** en la mano derecha: `I` = ↑, `J` = ←, `K` = ↓, `L` = →.
  Las F-keys van en la fila numérica (fila 0), por eso no chocan con `I/J/K/L` (filas 1-2).
- `HUI` / `HUD` = subir / bajar el hue del RGB. `RGBtg` = encender/apagar el RGB.
- **Encoder (raise):** girar = `Ctrl+Tab` / `Ctrl+Shift+Tab` (siguiente / anterior pestaña o track).

## RGB por capa

El color del underglow cambia según la capa activa (vía `rgblight`):

| Capa    | Color                         |
|---------|-------------------------------|
| _BASE   | hue dinámico (ajustable con HUI/HUD) |
| _LOWER  | rojo                          |
| _RAISE  | verde                         |
| Caps Lock activo | oro (dorado), tiene prioridad |

## OLED

- **Master:** animación de **perro** (96px, reacciona a Caps→ladra, Ctrl→sneak, GUI→camina, RAlt→corre, Space→salta) + indicador de capa + valores HSV.
- **Slave:** animación de **gato** (320px, idle vs. tap según WPM) + contador de WPM.
- Rotación 270 en ambas. Se apaga sola tras 60s sin tipeo.

## Estado de compilación

> **Pendiente de verificación del operador.** `qmk` no estaba instalado en la máquina donde se generó este repo, así que el firmware **no fue compilado** todavía. Ejecutá `qmk compile -kb sofle/rev1 -km mario` para validar que entra en el Pro Micro.

### Trade-off de flash (Pro Micro, ~28KB)

El binario está al límite: rgblight + encoder + tap-dance + WPM + OLED driver + arte del perro (96px×10 frames) + arte del gato (320px×3 frames). El gato es el mayor consumidor de PROGMEM.

Si `qmk compile` reporta **overflow de flash**, recortar en este orden (de menor a mayor pérdida funcional):

1. **Quitar el efecto breathing del RGB:** borrar `#define RGBLIGHT_EFFECT_BREATHING` en `config.h`.
2. **Reemplazar el gato (320px) por arte estático chico** (una "luna" ~32px) o eliminar `render_cat()` y dejar solo el WPM en el slave.
3. **Quitar el perro** y dejar solo texto de capa + WPM en ambas pantallas.

El orden de prioridad de la config es: **keymap > encoder > RGB por capa > OLED animado**. El keymap y el encoder nunca se recortan.

## Licencia

GPL v2 o posterior (igual que QMK).
