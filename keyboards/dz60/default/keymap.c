#include "kyleterry.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_wrapper(
  KC_GRV,         NUMBER_LEFT________________________________, NUMBER_RIGHT_______________________________, KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,
  KC_TAB,         QWERTY_1______________________________________________________________________________,   KC_LBRC, KC_RBRC, KC_BSLS,
  CTRLE,          QWERTY_2______________________________________________________________________________,   KC_QUOT,          KC_ENT,
  KC_LSFT, KC_NO, QWERTY_3______________________________________________________________________________,           SFT_EQL,        KC_VOLU,
  KC_LCTL, KC_LGUI, KC_LALT,            KC_SPC,        MO(_RAISE),         KC_SPC,          OS_LGUI, OS_SGUI, MO(_RAISE), MO(_LOWER), KC_VOLD),

[_RAISE] = LAYOUT_wrapper(
  ______, FUNC_LEFT_6_________________________________________, FUNC_RIGHT_6________________________________________, KC_NO, KC_DEL,
  ______, TO(_QWERTY), ______, ______, ______, ______, ______, KC_PAUS, KC_INS, ______, KC_PSCR, ______, ______, RESET,
  BLANK_6_____________________________________________, BLANK_6_____________________________________________, ______,
  ______, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, ______, ______, TD(TD_MD),
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MNXT),

[_LOWER] = LAYOUT_wrapper(
  ______, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), KC_NO, KC_DEL,
  ______, ______, KC_UP, ______, ______, ______, ______, KC_PAUS, KC_INS, ______, KC_PSCR, ______, ______, ______,
  ______, KC_LEFT, KC_DOWN, KC_RGHT, ______, ______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, ______, ______, ______,
  ______, KC_NO, BLANK_6_____________________________________________, BLANK______________________________________, KC_MPLY,
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MNXT),
};
