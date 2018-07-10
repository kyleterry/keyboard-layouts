#include QMK_KEYBOARD_H

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define CTRL_ESC CTL_T(KC_ESC) // hold for ctrl tap for escape
#define ______ KC_TRNS
#define OS_SGUI  OSM (MOD_LGUI | MOD_LSFT) // tap for LGUI + LSHIFT
#define OS_LGUI  OSM (MOD_LGUI)
#define OS_LCTL  OSM (MOD_LCTL)

enum keyboard_layers {
  _QWERTY,
  _FN1,
  _FN2
};

enum {
  TD_GO = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
  CTRL_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
  KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TD(TD_GO), KC_VOLU,
  KC_LGUI, KC_LALT, OS_LCTL, KC_SPC, MO(_FN2), KC_SPC, OS_LGUI, MO(_FN2), OS_SGUI, MO(_FN1), KC_VOLD),

[_FN1] = LAYOUT(
  ______, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), ______, KC_DEL,
  ______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ______, ______, ______, ______, RESET,
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
  ______, ______, ______, ______, BL_DEC, BL_TOGG, BL_INC, BL_STEP, ______, ______, ______, ______, ______, ______,
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______),

[_FN2] = LAYOUT(
  ______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ______, KC_DEL,
  ______, ______, KC_UP, ______, ______, ______, ______, KC_PAUS, KC_INS, ______, KC_PSCR, ______, ______, ______,
  ______, KC_LEFT, KC_DOWN, KC_RGHT, ______, ______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, ______, ______, ______,
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MPLY,
  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, KC_MNXT),
};

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

void go_shortcuts (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 2:
      SEND_STRING (" := ");
      reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GO] = ACTION_TAP_DANCE_FN(go_shortcuts)
};
