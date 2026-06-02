# ⌨️ sofle-config

Configuración **QMK** del teclado **Sofle RGB** (keymap `mario`) — pura por código, sin VIA.
Portada desde mi [config del Corne](https://github.com/valianx/corne-config) al Sofle, que suma fila numérica dedicada, 5 thumbs por mano y rotary encoders.

![Keymap](docs/keymap.svg)

> El diagrama de arriba se genera con [keymap-drawer](https://github.com/caksoylar/keymap-drawer) a partir del propio `keymap.c`. Para regenerarlo, ver [Cómo iterar](#-cómo-iterar).

---

## 🔩 Hardware

| | |
|---|---|
| **Teclado** | Sofle RGB (58 teclas, split, hot-swap MX, TRRS) |
| **Controladores** | Pro Micro (AVR atmega32u4) — flash ~28KB, muy ajustado → `LTO_ENABLE` |
| **OLED** | 0.91" SSD1306 en ambas mitades (rotación 270) |
| **RGB** | underglow (LEDs abajo, no per-key) → `RGBLIGHT`, no RGB Matrix |
| **Encoders** | 2 rotary EC11 (uno por mano) |

**Target QMK:** `sofle/rev1` · keymap `mario`

---

## 🗂️ Capas

Cuatro capas. `LOWER` y `RAISE` son momentáneas (mientras mantenés la tecla). **`NUMPAD` es tri-layer**: se activa apretando **LOWER + RAISE a la vez**.

### `_BASE` — QWERTY + fila numérica (pensada para gaming)

```
,-----------------------------------------.                ,-----------------------------------------.
|  `  |  1  |  2  |  3  |  4  |  5  |                      |  6  |  7  |  8  |  9  |  0  |  =  |
| Tab |  Q  |  W  |  E  |  R  |  T  |                      |  Y  |  U  |  I  |  O  |  P  | Bsp |
| Ctrl|  A  |  S  |  D  |  F  |  G  |                      |  H  |  J  |  K  |  L  |  ;  |  '  |
| TDsf|  Z  |  X  |  C  |  V  |  B  |Mute |          |Mute |  N  |  M  |  ,  |  .  |  /  |Shift|
            | GUI | Alt | Ctrl|LOWER|Enter|          |Space|RAISE| Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- **TDsf** = tap-dance: 1 pulso = `Shift`, 2 pulsos = `Caps Lock`.
- Los números 1-0 están en la fila de arriba (cómodo para juegos).
- **Encoder:** girar = volumen ↑/↓ · push = `Mute`.

### `_LOWER` — símbolos estándar (igual que el Corne)

```
,-----------------------------------------.                ,-----------------------------------------.
|     |     |     |     |     |     |                      |     |     |     |     |     |     |
| Tab |  !  |  @  |  #  |  $  |  %  |                      |  ^  |  &  |  *  |  (  |  )  | Bsp |
| Ctrl|  [  |  ]  |  {  |  }  |  |  |                      |  _  |  -  |  +  |  =  |  \  |  `  |
|Shift|     |     |     |     |     |Mute |          |Mute |     |     |     |     |  ~  |     |
            | GUI | Alt | Ctrl|     |Enter|          |Space|RAISE| Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- La fila de arriba respeta el teclado US: es **la fila de números con Shift, en orden** (`! @ # $ %  ^ & * ( )`). Nada que reaprender.
- Solo los símbolos "raros" se reubican en la fila home: `[ ] { } |` y `_ - + = \ \``.
- La fila numérica queda transparente → seguís teniendo 1-0 de la base.
- **Encoder:** girar = `PgUp` / `PgDn`.

### `_RAISE` — F1-F12 + flechas inverted-T (I/J/K/L)

```
,-----------------------------------------.                ,-----------------------------------------.
|     | F1  | F2  | F3  | F4  | F5  |                      | F6  | F7  | F8  | F9  | F10 | F11 |
|     |     |     |     |     |     |                      |PgUp |Home |  ↑  | End | F12 | Bsp |
| Ctrl| HUI | HUD |RGBtg|     |     |                      |PgDn |  ←  |  ↓  |  →  |     |     |
|Shift|     |     |     |     |     |Mute |          |Mute |     |     |     |     |     |     |
            | GUI | Alt | Ctrl|LOWER|Enter|          |Space|     | Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- Flechas **inverted-T** en la mano derecha: `I` = ↑, `J` = ←, `K` = ↓, `L` = →.
- Las F-keys van en la fila numérica, por eso no chocan con `I/J/K/L`.
- `HUI` / `HUD` = subir / bajar el hue del RGB · `RGBtg` = on/off del RGB.
- **Encoder:** girar = `Ctrl+Tab` / `Ctrl+Shift+Tab` (cambiar pestaña/track).

### `_NUMPAD` — numpad 10-key (tri-layer: LOWER + RAISE)

```
,-----------------------------------------.                ,-----------------------------------------.
|     |     |     |     |     |     |                      |     |     |     |     |     |     |
|     |     |  7  |  8  |  9  |     |                      |     |     |     |     |     |     |
|     |     |  4  |  5  |  6  |     |                      |     |     |     |     |     |     |
|     |  0  |  1  |  2  |  3  |     |Mute |          |Mute |     |     |     |     |     |     |
            | GUI | Alt | Ctrl|LOWER|Enter|          |Space|RAISE| Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- Numpad 10-key sobre la mano izquierda (`7-8-9 / 4-5-6 / 1-2-3`, el `0` en el pinky).
- Para entrada rápida de cifras con una sola mano, sin soltar el mouse.

---

## 🌈 RGB por capa

El color del underglow cambia según la capa activa (`rgblight`):

| Capa | Color |
|---|---|
| `_BASE` | hue dinámico (ajustable con HUI/HUD) |
| `_LOWER` | rojo |
| `_RAISE` | verde |
| `_NUMPAD` | azul |
| Caps Lock activo | oro (prioridad sobre todo) |

## 🖥️ OLED

- **Master:** animación de **perro** (96px — Caps→ladra, Ctrl→sneak, GUI→camina, RAlt→corre, Space→salta) + capa activa + valores HSV.
- **Slave:** animación de **gato** (320px — idle vs. tap según WPM) + contador de WPM.
- Se apaga sola tras 60s sin tipeo.

---

## 🔁 Cómo iterar

El flujo para cambiar el teclado es: **editar → compilar → redibujar → flashear**.

```bash
# 1. Editar el layout
#    keyboards/sofle/keymaps/mario/keymap.c

# 2. Compilar (genera el .hex y valida que entre en el Pro Micro)
qmk compile -kb sofle/rev1 -km mario

# 3. Regenerar el diagrama del README
export PYTHONUTF8=1
qmk c2json -kb sofle/rev1 -km mario --no-cpp -o sofle.json
keymap parse -q sofle.json > docs/keymap.yaml
keymap draw docs/keymap.yaml > docs/keymap.svg

# 4. Flashear (RESET en cada mitad cuando lo pida)
qmk flash -kb sofle/rev1 -km mario
```

### Poner cada mitad en bootloader (RESET)

El Pro Micro no tiene reset por software por defecto:

1. Conectá **una** mitad por USB.
2. Doble toque rápido al botón RESET (o puenteá `RST`↔`GND` dos veces seguidas).
3. Entra en bootloader (~8s) → ahí `qmk flash` la graba.
4. Repetí con la **otra** mitad. Ambas llevan el mismo firmware.

---

## ⚙️ Setup del toolchain

Este repo es un **QMK external userspace** (no contiene el firmware de QMK, solo el keymap).

```bash
# CLI de QMK + firmware
pip install qmk           # o: uv tool install qmk
qmk setup                 # clona qmk_firmware + submódulos

# Apuntar el CLI a este userspace (desde la raíz del repo)
qmk config user.overlay_dir="$(pwd)"
```

Para AVR (Pro Micro) hace falta `avr-gcc` + `make`. En Linux/Mac alcanza con `qmk setup`.

> **⚠️ Nota Windows (git-bash / MSYS):** el `make` nativo que trae `avr-gcc` corrompe recetas largas al pasarlas al `sh` de MSYS y la compilación falla con `unexpected EOF ... matching '`. Solución: usar un **`make` de MSYS2/cygwin** (GNU Make 4.4.1 "Built for x86_64-pc-cygwin") y ponerlo en el `PATH` **antes** del bin de `avr-gcc`. Alternativa más simple: usar **[QMK MSYS](https://msys.qmk.fm/)**, que ya trae todo el toolchain consistente.

---

## ✅ Estado

Compila para `sofle/rev1` (Pro Micro): **25414 / 28672 bytes (88%, 3258 libres)** — con OLED animado, RGB por capa, encoders y tap-dance, sin recortes.

### Backup VIA

En [`via-backup/sofle_v1.layout.json`](via-backup/sofle_v1.layout.json) está el respaldo del layout VIA anterior, por si querés revertir o reimportarlo en la [app de VIA](https://usevia.app).

## 📄 Licencia

GPL v2 o posterior (igual que QMK).
