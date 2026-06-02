/* Copyright 2023 valianx
 *
 * config.h for the "valian" keymap on the Sofle RGB (sofle/rev1).
 * Pure-code keymap, no VIA. Ported from valianx/corne-config.
 *
 * Free software under the GNU GPL v2 or later.
 */

#pragma once

/* ---- Split ---- */
#define SPLIT_USB_DETECT
// The USB-connected half becomes master; the other one, slave.

/* ---- Tap dance ---- */
#define TAPPING_TERM 200
// Window for the tap-dance double tap (shift/caps).
// The Corne used 400; lowered to 200 because 400 makes shift feel sluggish.

/* ---- OLED ---- */
#define OLED_BRIGHTNESS 120
// The OLED timeout is handled manually in oled_task_user (off after 60s idle).

/* ---- RGB underglow (rgblight) ---- */
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 110
    // Max HSV Value (brightness) — protects the Pro Micro's USB power budget.

    #define RGBLIGHT_HUE_STEP 5
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    #define RGBLIGHT_EFFECT_BREATHING
    // Only effect included (saves flash vs enabling all of them).
    // If qmk reports a flash overflow, this is the first thing to trim (see README).

    // RGBLED_NUM / RGBLED_SPLIT are NOT redefined here: we use the values the
    // keyboard (sofle/rev1) declares for its underglow chain. Redefining them to
    // a wrong number (e.g. the Corne's 54) breaks the RGB split.
#endif

/* ---- Flash savings (Pro Micro, ~28KB) ---- */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// Compatible with LTO_ENABLE; reduce the binary size.
