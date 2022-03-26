#include "kyleterry.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    KC_ESC,         NUMBER_LEFT________________________________, NUMBER_RIGHT_______________________________, KC_MINS, KC_EQL,  KC_NO, KC_BSPC,
    KC_TAB,         QWERTY_L1__________________________________, QWERTY_R1__________________________________, KC_LBRC, KC_RBRC,        KC_BSLS,
    KC_CAPS,        QWERTY_L2__________________________________, QWERTY_R2__________________________________, KC_QUOT,                 KC_ENT,
    KC_LSFT, KC_NO, QWERTY_L3__________________________________, QWERTY_R3__________________________________,        KC_RSFT,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,            KC_SPC,        KC_SPC,         KC_SPC,          KC_RCTL, MO(_RAISE), KC_LEFT, KC_RGHT,       KC_DOWN
  ),
  [_RAISE] = LAYOUT_wrapper(
    ______, FUNC_LEFT_6_________________________________________, FUNC_RIGHT_6________________________________________, KC_NO, KC_DEL,
    ______, TO(_QWERTY), ______, ______, ______, ______, ______, KC_PAUS, KC_INS, ______, KC_PSCR, ______, ______,             RESET,
    BLANK_6_____________________________________________, KC_HOME, KC_PGDN, KC_PGUP, KC_END, ______, ______, ______,
    ______, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, ______, ______,             KC_VOLU,
    ______, ______, ______,               ______, ______, ______,                              ______, ______, TD(TD_MD), KC_MNXT, KC_VOLD
  ),
};
