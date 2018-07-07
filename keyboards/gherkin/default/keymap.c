#include QMK_KEYBOARD_H

enum gamepad_layers {
  _QWERTY,
  _RAISE,
  _LOWER,
  _PUBG,
  _OVERWATCH,
  _ADJUST
};

enum gamepad_keycodes {
  QWERTY = SAFE_RANGE,
  PUBG,
  OVERWATCH,
  BACKLIT
};

#define ESC_CTRL CTL_T(KC_ESC)
#define Z_SHFT SFT_T(KC_Z)
#define BS_SHFT SFT_T(KC_BSPC)
#define FN_ENT LT(_ADJUST, KC_ENT)
/* #define RAISE LT(_RAISE, KC_V) */
/* #define LOWER LT(_LOWER, KC_B) */
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------+------+------+------+------+-------------+------+------+------+
   * |  Q   |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |  P   |
   * |------+------+------+------+------+------|------+------+------+------+
   * |  A   |   S  |   D  |   F  |   G  |   H  |   J  |   K  |  L   |  ENT |
   * |------+------+------+------+------+------+------+------+------+------+
   * |  Z   |   X  |   C  |   V  |  BSP |  SPC |   B  |   N  |  M   |  ESC |
   * `----------------------------------------------------------------------
   */
  [_QWERTY] = LAYOUT_ortho_3x10(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    FN_ENT,
      Z_SHFT,  KC_X,    KC_C,    LT(_RAISE, KC_V),   BS_SHFT, KC_SPC,  LT(_LOWER, KC_B),   KC_N,    KC_M,    ESC_CTRL),

  [_RAISE] = LAYOUT_ortho_3x10(
      KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
      KC_TAB,   KC_A,     KC_S,    KC_D,    KC_F,    KC_V,    KC_3,    KC_4,    KC_F2,   KC_NO,
      _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______),

  [_LOWER] = LAYOUT_ortho_3x10(
      KC_TILD,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,
      KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_V,    KC_3,    KC_4,    KC_F2,   KC_NO,
      _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______),

  /* PUBG
   * ,------+------+------+------+------+-------------+------+------+------+
   * | TAB  |   Q  |   W  |   E  |   R  |   5  |   6  |   V  |  F3  |  P   |
   * |------+------+------+------+------+------|------+------+------+------+
   * | ESC  |   A  |   S  |   D  |   F  |   3  |   4  |   B  |  F2  |  LS  |
   * |------+------+------+------+------+------+------+------+------+------+
   * | SHFT |   Z  |   X  |   C  |  SPC |   1  |   2  |   M  |  F1  |  ENT |
   * `----------------------------------------------------------------------
   */
  [_PUBG] = LAYOUT_ortho_3x10(
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_5,   KC_6,   KC_V,   KC_F3,   KC_P,
      ESC_CTRL, KC_A,   KC_S,   KC_D,   KC_F,   KC_3,   KC_4,   KC_B,   KC_F2,   FN_ENT,
      KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_SPC, KC_1,   KC_2,   KC_M,   KC_F1,   KC_ESC),

  /* OVERWATCH
   * ,------+------+------+------+------+-------------+------+------+------+
   * | TAB  |   Q  |   W  |   E  |   R  |   5  |   6  |   V  |  F3  |  P   |
   * |------+------+------+------+------+------|------+------+------+------+
   * | ESC  |   A  |   S  |   D  |   F  |   3  |   4  |   B  |  F2  |  LS  |
   * |------+------+------+------+------+------+------+------+------+------+
   * | SHFT |   Z  |   X  |   C  |  SPC |   1  |   2  |   M  |  F1  |  ENT |
   * `----------------------------------------------------------------------
   */
  [_OVERWATCH] = LAYOUT_ortho_3x10(
      KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_5,   KC_6,   KC_V,   KC_F3,   KC_P,
      ESC_CTRL, KC_A,   KC_S,   KC_D,   KC_F,   KC_3,   KC_4,   KC_B,   KC_F2,   FN_ENT,
      KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_SPC, KC_1,   KC_2,   KC_M,   KC_F1,   KC_ESC),

  /* Qwerty
   * ,------+------+------+------+------+-------------+------+------+------+
   * | TAB  |   Q  |   W  |   E  |   R  |   5  |   6  |   V  |  F3  |  P   |
   * |------+------+------+------+------+------|------+------+------+------+
   * | ESC  |   A  |   S  |   D  |   F  |   3  |   4  |   B  |  F2  |  LS  |
   * |------+------+------+------+------+------+------+------+------+------+
   * | SHFT |   Z  |   X  |   C  |  SPC |   1  |   2  |   M  |  F1  |  ENT |
   * `----------------------------------------------------------------------
   */
  [_ADJUST] = LAYOUT_ortho_3x10(
      QWERTY,  PUBG,  OVERWATCH, KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    _______,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_BSPC, KC_SPC,  BACKLIT,    KC_N,    KC_M,    KC_ESC)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case OVERWATCH:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_OVERWATCH);
      }
      return false;
      break;
    case PUBG:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PUBG);
      }
      return false;
      break;
    /* case LOWER: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_LOWER); */
    /*     update_tri_layer(_LOWER, _RAISE, _ADJUST); */
    /*   } else { */
    /*     layer_off(_LOWER); */
    /*     update_tri_layer(_LOWER, _RAISE, _ADJUST); */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case RAISE: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_RAISE); */
    /*     update_tri_layer(_LOWER, _RAISE, _ADJUST); */
    /*   } else { */
    /*     layer_off(_RAISE); */
    /*     update_tri_layer(_LOWER, _RAISE, _ADJUST); */
    /*   } */
    /*   return false; */
    /*   break; */
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        rgblight_toggle();
        rgblight_step();
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }

  return true;
}
