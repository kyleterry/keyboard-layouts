#include "kyleterry.h"

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

/* enum crkbd_keycodes { RGBRST = NEW_SAFE_RANGE }; */

/*
 * The `LAYOUT_crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    ALTT,  K01,    K02,     K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
    CTRLE, K11,    K12,     K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A, RALT_T(KC_QUOT), \
    OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,                        K26,     K27,     K28,     K29, RCTL_T(K2A), SFT_EQL, \
                                        OS_LGUI,  LOWER, KC_SPC, KC_SPC,  RAISE, KC_ENT                                      \
  )
#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_base_wrapper(
    QWERTY_1______________________________________________________________________________,
    QWERTY_2______________________________________________________________________________,
    QWERTY_3______________________________________________________________________________,
  ),

  [_LOWER] = LAYOUT_wrapper( \
    LOWER_L1_6__________________________________________,                    LOWER_R1_6__________________________________________,
    LOWER_L2_6__________________________________________,                    LOWER_R2_6__________________________________________,
    LOWER_L3_6__________________________________________,                    LOWER_R3_6__________________________________________,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper( \
    RAISE_L1_6__________________________________________,                    RAISE_R1_6__________________________________________,
    RAISE_L2_6__________________________________________,                    RAISE_R2_6__________________________________________,
    RAISE_L3_6__________________________________________,                    RAISE_R3_6__________________________________________,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    ADJUST_L1_6_________________________________________,                    ADJUST_R1_6_________________________________________,
    ADJUST_L2_6_________________________________________,                    ADJUST_R2_6_________________________________________,
    ADJUST_L3_6_________________________________________,                    ADJUST_R3_6_________________________________________,
                                     _______, _______, _______,        _______, _______, _______
  )
};
