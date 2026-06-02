# ⌨️ sofle-config

**QMK** configuration for the **Sofle RGB** keyboard (keymap `valian`) — pure code, no VIA.
Ported from my [Corne config](https://github.com/valianx/corne-config) to the Sofle, which adds a dedicated number row, 5 thumb keys per hand and rotary encoders.

![Keymap](docs/keymap.svg)

> The diagram above is generated from `keymap.c` with [keymap-drawer](https://github.com/caksoylar/keymap-drawer). To regenerate it, see [How to iterate](#-how-to-iterate).

---

## 🔩 Hardware

| | |
|---|---|
| **Keyboard** | Sofle RGB (58 keys, split, MX hot-swap, TRRS) |
| **Controllers** | Pro Micro (AVR atmega32u4) — ~28KB flash, very tight → `LTO_ENABLE` |
| **OLED** | 0.91" SSD1306 on both halves (270° rotation) |
| **RGB** | underglow (bottom LEDs, not per-key) → `RGBLIGHT`, not RGB Matrix |
| **Encoders** | 2 rotary EC11 (one per hand) |

**QMK target:** `sofle/rev1` · keymap `valian`

---

## 🗂️ Layers

Four layers. `LOWER` and `RAISE` are momentary (active while held). **`NUMPAD` is a tri-layer**: activated by holding **LOWER + RAISE at the same time**.

### `_BASE` — QWERTY + number row (gaming-friendly)

```
,-----------------------------------------.                ,-----------------------------------------.
|  `  |  1  |  2  |  3  |  4  |  5  |                      |  6  |  7  |  8  |  9  |  0  |  =  |
| Tab |  Q  |  W  |  E  |  R  |  T  |                      |  Y  |  U  |  I  |  O  |  P  | Bsp |
| Ctrl|  A  |  S  |  D  |  F  |  G  |                      |  H  |  J  |  K  |  L  |  ;  |  '  |
| TDsf|  Z  |  X  |  C  |  V  |  B  |Mute |          |Mute |  N  |  M  |  ,  |  .  |  /  |Shift|
            | GUI | Alt | Ctrl|LOWER|Enter|          |Space|RAISE| Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- **TDsf** = tap-dance: 1 tap = `Shift`, 2 taps = `Caps Lock`.
- Numbers 1-0 live on the top row (handy for games).
- **Encoder:** rotate = volume ↑/↓ · press = `Mute`.

### `_LOWER` — standard symbols (same as the Corne)

```
,-----------------------------------------.                ,-----------------------------------------.
|     |     |     |     |     |     |                      |     |     |     |     |     |     |
| Tab |  !  |  @  |  #  |  $  |  %  |                      |  ^  |  &  |  *  |  (  |  )  | Bsp |
| Ctrl|  [  |  ]  |  {  |  }  |  |  |                      |  _  |  -  |  +  |  =  |  \  |  `  |
|Shift|     |     |     |     |     |Mute |          |Mute |     |     |     |     |  ~  |     |
            | GUI | Alt | Ctrl|     |Enter|          |Space|RAISE| Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- The top row matches a US keyboard: it's **the number row with Shift, in order** (`! @ # $ %  ^ & * ( )`). Nothing new to learn.
- Only the "awkward" symbols are relocated to the home row: `[ ] { } |` and `_ - + = \ \``.
- The number row stays transparent → you still get 1-0 from the base.
- **Encoder:** rotate = `PgUp` / `PgDn`.

### `_RAISE` — F1-F12 + inverted-T arrows (I/J/K/L)

```
,-----------------------------------------.                ,-----------------------------------------.
|     | F1  | F2  | F3  | F4  | F5  |                      | F6  | F7  | F8  | F9  | F10 | F11 |
|     |     |     |     |     |     |                      |PgUp |Home |  ↑  | End | F12 | Bsp |
| Ctrl|     |     |     |     |     |                      |PgDn |  ←  |  ↓  |  →  |     |     |
|Shift|     |     |     |     |     |Mute |          |Mute |     |     |     |     |     |     |
            | GUI | Alt | Ctrl|LOWER|Enter|          |Space|     | Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- **Inverted-T** arrows on the right hand: `I` = ↑, `J` = ←, `K` = ↓, `L` = →.
- F-keys sit on the number row, so they don't collide with `I/J/K/L`.
- RGB / light controls were moved to the 4th layer (`_NUMPAD`, left hand).
- **Encoder:** rotate = `Ctrl+Tab` / `Ctrl+Shift+Tab` (switch tab/track).

### `_NUMPAD` — lights/config (left) + 10-key numpad (right) · tri-layer

```
,-----------------------------------------.                ,-----------------------------------------.
|     |     |     |     |     |     |                      |     |     |     |     |     |     |
|     |Tog  |Mode+|Hue+ |Sat+ |Val+ |                      |     |  7  |  8  |  9  |     |     |
|     |Boot |Mode-|Hue- |Sat- |Val- |                      |     |  4  |  5  |  6  |     |     |
|     |EEclr|     |Spd- |Spd+ |     |Mute |          |Mute |     |  1  |  2  |  3  |  0  |     |
            | GUI | Alt | Ctrl|LOWER|Enter|          |Space|RAISE| Ctrl| Alt | GUI |
            `-----------------------------'          `-----------------------------'
```

- **Right hand:** 10-key numpad (`7-8-9 / 4-5-6 / 1-2-3`, with `0` next to `3`). Fast number entry without leaving the mouse.
- **Left hand:** keyboard / light controls — `Tog` RGB on/off, `Hue±`, `Sat±`, `Val±` (brightness), `Mode±` (effect), `Spd±` (speed), `Boot` (jump to bootloader for flashing), `EEclr` (clear EEPROM).

---

## 🌈 Per-layer RGB

The underglow color changes with the active layer (`rgblight`):

| Layer | Color |
|---|---|
| `_BASE` | dynamic hue (adjust with Hue+/Hue- on `_NUMPAD`) |
| `_LOWER` | red |
| `_RAISE` | green |
| `_NUMPAD` | blue |
| Caps Lock on | gold (takes priority) |

> The full per-layer reference (positions, keycodes, design rationale) lives in [`docs/layout.md`](docs/layout.md).

## 🖥️ OLED

- **Master:** **dog** animation (96px — Caps→barks, Ctrl→sneaks, GUI→walks, RAlt→runs, Space→jumps) + active layer + HSV values.
- **Slave:** **cat** animation (320px — idle vs. tap based on WPM) + WPM counter.
- Turns itself off after 60s of inactivity.

---

## 🔁 How to iterate

The flow to change the keyboard is: **edit → compile → redraw → flash**.

```bash
# 1. Edit the layout
#    keyboards/sofle/keymaps/valian/keymap.c

# 2. Compile (builds the .hex and checks it fits the Pro Micro)
qmk compile -kb sofle/rev1 -km valian

# 3. Regenerate the README diagram
export PYTHONUTF8=1
qmk c2json -kb sofle/rev1 -km valian --no-cpp -o sofle.json
keymap parse -q sofle.json > docs/keymap.yaml
keymap draw docs/keymap.yaml > docs/keymap.svg

# 4. Flash (RESET each half when prompted)
qmk flash -kb sofle/rev1 -km valian
```

### Putting each half into bootloader (RESET)

The Pro Micro has no software reset by default:

1. Plug in **one** half via USB.
2. Double-tap the RESET button quickly (or short `RST`↔`GND` twice in a row).
3. It enters bootloader (~8s) → `qmk flash` writes it.
4. Repeat with the **other** half. Both halves carry the same firmware.

> Tip: the `Boot` key on `_NUMPAD` (left hand) jumps to the bootloader without touching the physical RESET.

---

## ⚙️ Toolchain setup

This repo is a **QMK external userspace** (it does not contain the QMK firmware, only the keymap).

```bash
# QMK CLI + firmware
pip install qmk           # or: uv tool install qmk
qmk setup                 # clones qmk_firmware + submodules

# Point the CLI at this userspace (from the repo root)
qmk config user.overlay_dir="$(pwd)"
```

For AVR (Pro Micro) you need `avr-gcc` + `make`. On Linux/Mac `qmk setup` is enough.

> **⚠️ Windows note (git-bash / MSYS):** the native `make` bundled with `avr-gcc` corrupts long recipes when handing them to the MSYS `sh`, and the build fails with `unexpected EOF ... matching '`. Fix: use an **MSYS2/cygwin `make`** (GNU Make 4.4.1 "Built for x86_64-pc-cygwin") and put it on `PATH` **before** the `avr-gcc` bin. Simpler alternative: use **[QMK MSYS](https://msys.qmk.fm/)**, which ships a consistent toolchain.

---

## 💾 Prebuilt firmware

A ready-to-flash build is committed at [`firmware/sofle_rev1_valian.hex`](firmware/sofle_rev1_valian.hex), so you can flash without recompiling (e.g. from a machine without the toolchain):

```bash
# With the QMK CLI (auto-detects the bootloader):
qmk flash firmware/sofle_rev1_valian.hex

# Or directly with avrdude (replace COMx with the port shown in bootloader):
avrdude -c avr109 -p atmega32u4 -P COMx -U flash:w:firmware/sofle_rev1_valian.hex:i
```

Flash each half (put it in bootloader first — see above). Keep this `.hex` in sync when you change the keymap.

## ✅ Status

Builds for `sofle/rev1` (Pro Micro): **25414 / 28672 bytes (88%, 3258 free)** — with animated OLED, per-layer RGB, encoders and tap-dance, no cuts.

### VIA backup

[`via-backup/sofle_v1.layout.json`](via-backup/sofle_v1.layout.json) holds the previous VIA layout backup, in case you want to revert or re-import it into the [VIA app](https://usevia.app).

## 📄 License

GPL v2 or later (same as QMK).
