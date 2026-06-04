# Layout reference — keymap `valian` (Sofle RGB)

The authoritative, always-up-to-date visual is [`keymap.svg`](keymap.svg) (regenerated from `keymap.c` with keymap-drawer). This page describes the intent of each layer.

![Keymap](keymap.svg)

## Layers

| # | Layer | Access | Purpose |
|---|-------|--------|---------|
| 0 | `_BASE` | default | QWERTY + dedicated number row |
| 1 | `_LOWER` | hold left thumb (`LOWER`) | symbols not reachable elsewhere |
| 2 | `_RAISE` | hold right thumb (`RAISE`) | F-keys + arrows + navigation + edit keys |
| 3 | `_NUMPAD` | **tri-layer** (`LOWER`+`RAISE`) | lights/config (left) + numpad (right) |

`_NUMPAD` is enabled via `update_tri_layer(_LOWER, _RAISE, _NUMPAD)` — hold both layer keys.

## Modifiers (identical on every layer)

- **Shift** → home-row left pinky · **Ctrl** → bottom-row left pinky · **right Shift** → bottom-row right pinky.
- Thumbs: **GUI / Alt / Ctrl** (inherited from base on every layer).
- Right thumb is **AltGr** (Right Alt) for US-International: `AltGr + n = ñ`. Left thumb is normal Alt (e.g. paste images in Claude Code).
- **Caps Lock** = `RAISE + A` (the key next to the left Shift). There is no tap-dance, so Caps never triggers by accident.

## `_BASE`

QWERTY with `Esc` top-left and numbers `1-0` on the dedicated top row (handy for games). Backtick `` ` `` lives on `_LOWER`.

## `_LOWER` — symbols not reachable elsewhere

Keeps only the symbols you can't reach any other way, all on the home row: `[ ] { } |` (left) and `` \ ` ~ - _ `` (right). The shifted-number symbols (`! @ # $ %  ^ & * ( )`) are **not** here — they're already `Shift` + the number row on the base, and `=`/`+` live on the base too. The number row stays transparent (you keep `1-0`).

## `_RAISE` — F-keys + navigation + edit keys

F1-F12 on the number row; **inverted-T arrows** on the right hand (`I`=↑, `J`=←, `K`=↓, `L`=→) with `Home/End/PgUp/PgDn` around them. `Caps Lock` sits next to the left Shift. Edit keys: `Del` (forward delete) on the Backspace key, and `Snip` (`Win+Shift+S`, Windows Snipping Tool) on `S`.

## `_NUMPAD` — lights/config + numpad

- **Right hand:** 10-key numpad (`7-8-9 / 4-5-6 / 1-2-3`, `0` next to `3`).
- **Left hand:** RGB/keyboard controls — toggle, hue/sat/val, effect mode/speed, `Boot` (jump to bootloader), `EEclr` (clear EEPROM).

## Encoders

The left and right encoders differ on the base layer; on the other layers both rotate the same. Clicks are inherited from the base on every layer (left = Snip, right = Mute).

| Layer | Left rotate | Right rotate | Left click | Right click |
|-------|-------------|--------------|------------|-------------|
| `_BASE` | mouse scroll | volume ↑/↓ | Snip (`Win+Shift+S`) | Mute |
| `_LOWER` | PgUp / PgDn | PgUp / PgDn | Snip | Mute |
| `_RAISE` | Ctrl+Tab / Ctrl+Shift+Tab | Ctrl+Tab / Ctrl+Shift+Tab | Snip | Mute |

## Per-layer RGB

`_BASE` dynamic hue (Hue+/Hue- on `_NUMPAD`) · `_LOWER` red · `_RAISE` green · `_NUMPAD` blue · Caps Lock on → gold (priority).

## OLED

- **Master:** dog animation (reacts to mods/caps) + active layer + HSV values.
- **Slave:** cat animation (continuous).
- Each half turns its OLED off after 60s without local key activity, back on with any keypress.

## Regenerate the diagram

```bash
export PYTHONUTF8=1
qmk c2json -kb sofle/rev1 -km valian --no-cpp -o sofle.json
keymap parse -q sofle.json > docs/keymap.yaml
keymap draw docs/keymap.yaml > docs/keymap.svg
```
