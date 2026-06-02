# rules.mk del keymap "valian" para Sofle RGB (sofle/rev1).
# Keymap puro por codigo, sin VIA. Build AVR (Pro Micro / atmega32u4).

# ---- Features activadas ----
OLED_ENABLE     = yes
OLED_DRIVER     = ssd1306    # OLED 0.91" en ambas mitades
RGBLIGHT_ENABLE = yes        # underglow via rgblight (NO RGB Matrix)
ENCODER_ENABLE  = yes        # rotary encoders EC11
TAP_DANCE_ENABLE = yes       # shift / caps (TD_CAPLOCK)
EXTRAKEY_ENABLE = yes        # KC_MUTE / KC_VOLU / KC_VOLD
WPM_ENABLE      = yes        # get_current_wpm() para las animaciones OLED

# ---- VIA: explicitamente desactivado (keymap puro por codigo) ----
VIA_ENABLE      = no

# ---- Flash: el Pro Micro es muy ajustado (~28KB) ----
LTO_ENABLE      = yes        # link-time optimization; reduce mucho el .hex

# ---- Features desactivadas para ahorrar flash ----
MOUSEKEY_ENABLE     = no
CONSOLE_ENABLE      = no
COMMAND_ENABLE      = no
NKRO_ENABLE         = no
BACKLIGHT_ENABLE    = no
AUDIO_ENABLE        = no
SPACE_CADET_ENABLE  = no
GRAVE_ESC_ENABLE    = no
MAGIC_ENABLE        = no
