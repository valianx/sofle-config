# rules.mk for the "valian" keymap on the Sofle RGB (sofle/rev1).
# Pure-code keymap, no VIA. AVR build (Pro Micro / atmega32u4).

# ---- Enabled features ----
OLED_ENABLE     = yes
OLED_DRIVER     = ssd1306    # 0.91" OLED on both halves
RGBLIGHT_ENABLE = yes        # underglow via rgblight (NOT RGB Matrix)
ENCODER_ENABLE  = yes        # EC11 rotary encoders
TAP_DANCE_ENABLE = no        # Shift is plain KC_LSFT on every layer (no caps tap-dance)
EXTRAKEY_ENABLE = yes        # KC_MUTE / KC_VOLU / KC_VOLD
WPM_ENABLE      = no         # not used (cat animates continuously)

# ---- VIA: explicitly disabled (pure-code keymap) ----
VIA_ENABLE      = no

# ---- Flash: the Pro Micro is very tight (~28KB) ----
LTO_ENABLE      = yes        # link-time optimization; shrinks the .hex a lot

# ---- Features disabled to save flash ----
MOUSEKEY_ENABLE     = no
CONSOLE_ENABLE      = no
COMMAND_ENABLE      = no
NKRO_ENABLE         = no
BACKLIGHT_ENABLE    = no
AUDIO_ENABLE        = no
SPACE_CADET_ENABLE  = no
GRAVE_ESC_ENABLE    = no
MAGIC_ENABLE        = no
