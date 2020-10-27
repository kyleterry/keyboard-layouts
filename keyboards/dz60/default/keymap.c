#include "kyleterry.h"

enum keyboard_layers {
  _QWERTY,
  _GAMING,
  _FN1,
  _FN2
};

enum {
  /* tap dance shortcuts for go programming */
  TD_GO,
  /* tap dance shortcuts for overwatch voicelines */
  TD_OW,
  /* tap dance shortcuts for media keys */
  TD_MD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_wrapper(
  KC_GRV,         ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________, KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,
  KC_TAB,         _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_LBRC, KC_RBRC, KC_BSLS,
  CTRLE,          _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT, KC_NO, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,          TD(TD_GO),        KC_VOLU,
  KC_LGUI, KC_LALT, KC_LCTL,            KC_SPC,        MO(_RAISE),         KC_SPC,          OS_LGUI, OS_SGUI, MO(_RAISE), MO(_LOWER), KC_VOLD),

[_GAMING] = LAYOUT(
  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_F8, KC_F9, KC_F10, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
  CTRLE, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TD(TD_GO), KC_VOLU,
  KC_LGUI, KC_LALT, KC_LCTL, KC_SPC, TD(TD_OW), KC_SPC, OS_LGUI, OS_SGUI, MO(_RAISE), MO(_LOWER), KC_VOLD),

[_RAISE] = LAYOUT_wrapper(
  ______, _________________FUNC_LEFT_6________________________, _________________FUNC_RIGHT_6_______________________, KC_NO, KC_DEL,
  ______, TO(_QWERTY), TO(_GAMING), ______, ______, ______, ______, KC_PAUS, KC_INS, ______, KC_PSCR, ______, ______, RESET,
  ___________________BLANK_6__________________________, ___________________BLANK_6__________________________, ______,
  ______, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, ______, ______, TD(TD_MD),
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MNXT),

[_LOWER] = LAYOUT_wrapper(
  ______, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), KC_NO, KC_DEL,
  ______, ______, KC_UP, ______, ______, ______, ______, KC_PAUS, KC_INS, ______, KC_PSCR, ______, ______, ______,
  ______, KC_LEFT, KC_DOWN, KC_RGHT, ______, ______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, ______, ______, ______,
  ______, KC_NO, ___________________BLANK_6__________________________, ___________________BLANK___________________, KC_MPLY,
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MNXT),

};

void tap_key(uint16_t keycode) {
  register_code  (keycode);
  unregister_code(keycode);
}

void shift_key(uint16_t keycode) {
  register_code  (KC_LSFT);
  tap_key        (keycode);
  unregister_code(KC_LSFT);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
    switch (id) {
    case 1:
        return MACRO( D(LGUI), T(PAUS), U(LGUI), T(L), END );
      break;
    }
  }

  return MACRO_NONE;
}

void dance_go(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 2:
      SEND_STRING (":=");
      reset_tap_dance (state);
  }
}

void dance_ow(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_key(KC_7);
      reset_tap_dance (state);
      break;
    case 2:
      tap_key(KC_8);
      reset_tap_dance (state);
      break;
    case 3:
      tap_key(KC_9);
      reset_tap_dance (state);
      break;
    case 4:
      tap_key(KC_0);
      reset_tap_dance (state);
      break;
  }
}

void dance_media(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_key(KC_MPLY);
      reset_tap_dance(state);
      break;
    case 2:
      tap_key(KC_MUTE);
      reset_tap_dance(state);
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GO] = ACTION_TAP_DANCE_FN(dance_go),
  [TD_OW] = ACTION_TAP_DANCE_FN(dance_ow),
  [TD_MD] = ACTION_TAP_DANCE_FN(dance_media)
};
