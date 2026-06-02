# Layout documentation — keymap `valian` (Sofle RGB)

Detailed reference for the 4 layers, encoders, RGB and OLED. The full visual diagram is in [`keymap.svg`](keymap.svg) (regenerated from `keymap.c` with keymap-drawer).

![Keymap](keymap.svg)

## Layer model

| # | Layer | Access | Purpose |
|---|-------|--------|---------|
| 0 | `_BASE` | default | QWERTY + number row + mods |
| 1 | `_LOWER` | hold left thumb (`LOWER`) | standard symbols |
| 2 | `_RAISE` | hold right thumb (`RAISE`) | F-keys + arrows + navigation |
| 3 | `_NUMPAD` | **tri-layer**: `LOWER` + `RAISE` together | lights/config (left) + numpad (right) |

The tri-layer is implemented with `update_tri_layer(_LOWER, _RAISE, _NUMPAD)` in `process_record_user`: when layers 1 and 2 are active at the same time, layer 3 turns on.

Table conventions: `▽` = transparent (falls through to the layer below), `·` = unassigned (`XXXXXXX`).

---

## Layer 0 — `_BASE`

Standard QWERTY with the Sofle's dedicated number row on top (comfortable for games — no need to go to a layer for numbers).

| Zone | Keys |
|------|------|
| Number row | `` ` `` 1 2 3 4 5 — 6 7 8 9 0 = |
| Top row | Tab Q W E R T — Y U I O P Bksp |
| Home row | Ctrl A S D F G — H J K L `;` `'` |
| Bottom row | **TDsf** Z X C V B — N M `,` `.` `/` Shift |
| Left thumbs | GUI · Alt · Ctrl · **LOWER** · Enter |
| Right thumbs | Space · **RAISE** · Ctrl · Alt · GUI |

- **TDsf** (`TD(TD_CAPLOCK)`): tap-dance — 1 tap = `Left Shift`, 2 taps = `Caps Lock`.
- **Encoder:** rotate = volume ↑/↓ · press (both) = `Mute`.

---

## Layer 1 — `_LOWER` (symbols)

Same symbol layout as the Corne, designed so there is **nothing new to learn**: the top row is exactly the number row with Shift, in order.

| Zone | Keys |
|------|------|
| Number row | ▽ ▽ ▽ ▽ ▽ ▽ — ▽ ▽ ▽ ▽ ▽ ▽ |
| Top row | Tab `!` `@` `#` `$` `%` — `^` `&` `*` `(` `)` Bksp |
| Home row | Ctrl `[` `]` `{` `}` `\|` — `_` `-` `+` `=` `\` `` ` `` |
| Bottom row | Shift · · · · · — · · · · `~` · |
| Thumbs | ▽ (except `RAISE` on the right, to reach the tri-layer) |

**Design:**
- Left = `! @ # $ %` (Shift+1..5) · Right = `^ & * ( )` (Shift+6..0). It's the full number row with Shift.
- Only the "awkward" symbols are relocated to the home row: brackets (`[ ] { }`), pipe (`|`), and operators (`_ - + = \` and backtick).
- The number row stays transparent: you still get `1..0` from base without leaving the layer.
- **Encoder:** rotate = `PgUp` / `PgDn`.

---

## Layer 2 — `_RAISE` (F-keys + navigation)

| Zone | Keys |
|------|------|
| Number row | · F1 F2 F3 F4 F5 — F6 F7 F8 F9 F10 F11 |
| Top row | · · · · · · — PgUp Home **↑** End F12 Bksp |
| Home row | Ctrl · · · · · — PgDn **←** **↓** **→** · · |
| Bottom row | Shift · · · · · — · · · · · · |
| Thumbs | ▽ (except `LOWER` on the left, for the tri-layer) |

**Design:**
- **Inverted-T** arrows on the right hand: `I` = ↑, `J` = ←, `K` = ↓, `L` = →. Around them: `Home`/`End`/`PgUp`/`PgDn` for full one-handed navigation.
- F1-F12 live on the number row, so they **don't collide** with the arrows (rows 1-2).
- **Encoder:** rotate = `Ctrl+Tab` / `Ctrl+Shift+Tab` (next / previous tab or track).

---

## Layer 3 — `_NUMPAD` (lights/config + numpad) · tri-layer

Entered by holding `LOWER` + `RAISE` together.

| Zone | Left (lights/config) | Right (numpad) |
|------|----------------------|----------------|
| Top row | `Tog` `Mode+` `Hue+` `Sat+` `Val+` | · `7` `8` `9` · |
| Home row | `Boot` `Mode-` `Hue-` `Sat-` `Val-` | · `4` `5` `6` · |
| Bottom row | `EEclr` · `Spd-` `Spd+` · | · `1` `2` `3` `0` |

**Right hand — 10-key numpad:** `7-8-9` over U-I-O, `4-5-6` over J-K-L, `1-2-3` over M-,-. and `0` next to `3`. Fast one-handed number entry.

**Left hand — keyboard controls:**

| Key | Keycode | Function |
|-----|---------|----------|
| Tog | `UG_TOGG` | toggle RGB underglow on/off |
| Hue+ / Hue- | `HUI` / `HUD` | raise/lower hue (feeds the `_BASE` dynamic hue) |
| Sat+ / Sat- | `UG_SATU` / `UG_SATD` | saturation |
| Val+ / Val- | `UG_VALU` / `UG_VALD` | brightness |
| Mode+ / Mode- | `UG_NEXT` / `UG_PREV` | RGB animation effect |
| Spd+ / Spd- | `UG_SPDU` / `UG_SPDD` | effect speed |
| Boot | `QK_BOOT` | jump to bootloader (flash without touching the physical RESET) |
| EEclr | `EE_CLR` | clear EEPROM (reset stored settings) |

> `HUI`/`HUD` are custom keycodes (not the standard `UG_HUE*`) because they feed the dynamic hue that `_BASE` remembers across layers.

---

## Per-layer RGB

The underglow color changes with the highest active layer (`layer_state_set_user` → `rgblight_sethsv_noeeprom`):

| Layer | Color |
|-------|-------|
| `_BASE` | dynamic hue (adjustable with Hue+/Hue-) |
| `_LOWER` | red |
| `_RAISE` | green |
| `_NUMPAD` | blue |
| Caps Lock on | gold — takes priority over the layer |

## OLED

| Half | Content |
|------|---------|
| Master | **dog** animation (96px) + active layer (`BASE`/`LOWER`/`RAISE`/`NUMPD`) + HSV values |
| Slave | **cat** animation (320px, idle vs. tap based on WPM) + WPM counter |

The dog reacts to modifiers: `Caps`→barks, `Ctrl`→sneaks, `GUI`→walks, `RAlt`→runs, `Space`→jumps. Both screens rotate 270° and turn off after 60s of inactivity.

---

## Regenerating the diagram

```bash
export PYTHONUTF8=1
qmk c2json -kb sofle/rev1 -km valian --no-cpp -o sofle.json
keymap parse -q sofle.json > docs/keymap.yaml
keymap draw docs/keymap.yaml > docs/keymap.svg
```
