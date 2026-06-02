/* Copyright 2023 valianx
 *
 * config.h del keymap "mario" para Sofle RGB (sofle/rev1).
 * Keymap puro por codigo, sin VIA. Portado desde valianx/corne-config.
 *
 * Software libre bajo GNU GPL v2 o posterior.
 */

#pragma once

/* ---- Split ---- */
#define SPLIT_USB_DETECT
// La mitad conectada por USB se considera master; la otra, slave.

/* ---- Tap dance ---- */
#define TAPPING_TERM 200
// Ventana para el doble pulso del tap dance (shift/caps).
// El Corne usaba 400; se baja a 200 porque 400 hace sentir el shift lento al usarlo.

/* ---- OLED ---- */
#define OLED_BRIGHTNESS 120
// El timeout de OLED se maneja a mano en oled_task_user (apaga tras 60s sin tipeo).

/* ---- RGB underglow (rgblight) ---- */
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 110
    // Maximo Value (brillo) en HSV — protege el consumo por USB del Pro Micro.

    #define RGBLIGHT_HUE_STEP 5
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    #define RGBLIGHT_EFFECT_BREATHING
    // Unico efecto incluido (ahorra flash frente a habilitar todos).
    // Si qmk reporta overflow de flash, este es el primer recorte (ver README).

    // RGBLED_NUM / RGBLED_SPLIT NO se redefinen aqui: se usan los valores que
    // el propio teclado (sofle/rev1) declara para su cadena underglow. Redefinirlos
    // a un numero incorrecto (p. ej. el 54 del Corne) rompe el split del RGB.
#endif

/* ---- Ahorro de flash (Pro Micro, ~28KB) ---- */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// Compatibles con LTO_ENABLE; reducen tamaño del binario.
