/* Copyright 2018 Carlos Filoteo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#ifdef LED_ENABLE
  #include "protocol/serial.h"
#endif

#define LT3_TAB         LT(3, KC_TAB)
#define MT_RSFT_ENT     MT(MOD_RSFT, KC_ENT)
#define CTRL_ESC        CTL_T(KC_ESC) // hold for ctrl tap for escape
#define OS_SGUI         OSM (MOD_LGUI | MOD_LSFT) // tap for LGUI + LSHIFT
#define OS_LGUI         OSM (MOD_LGUI)
#define OS_LCTL         OSM (MOD_LCTL)

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
    LED_CHG
};

enum ut47_layers {
  _QWERTY,
  _L1,
  _L2,
  _L3
};

enum {
  /* tap dance shortcuts for media keys */
  TD_MD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY Layer
   * ,-------------------------------------------------------------------------.
   * | Tab |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * |ct/es |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  Ent |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  '  |
   * |-------------------------------------------------------------------------+
   * | L3  | Gui | Alt | Ctl |  L2  |   Space   |  L1  | OSGUI|OSCTL| VUp|VDOWN|
   * `-------------------------------------------------------------------------'
   */
[_QWERTY] = LAYOUT(
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  CTRL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
  MO(_L3),  KC_LGUI, KC_LALT, KC_LCTL, MO(_L2),      KC_SPC,      MO(_L1), OS_LGUI, OS_LCTL, KC_VOLU, KC_VOLD
),

  /* Layer 1
   * ,-------------------------------------------------------------------------.
   * | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |  -  |  =  |  [  |  ]  |  \   |
   * |-------------------------------------------------------------------------+
   * |       | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       | Home| PgDn| PgUp| End |
   * `-------------------------------------------------------------------------'
   */
[_L1] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
  _______, _______, _______, _______, _______,     _______,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

  /* Layer 2
   * ,-------------------------------------------------------------------------.
   * |   ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |Delete|
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |  _  |  +  |  { |  }  |   |   |
   * |-------------------------------------------------------------------------+
   * |       | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       | Nxt| Stop| pl/mt| Prv |
   * `-------------------------------------------------------------------------'
   */
[_L2] = LAYOUT(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, _______, _______, _______, _______,     _______,      _______, KC_MPRV, KC_MSTP, TD(TD_MD), KC_MNXT
),

  /* Layer 3
   * ,-------------------------------------------------------------------------.
   * |     |     |     |     |     |     |     |     | Ins |     |PrtSc|       |
   * |-------------------------------------------------------------------------+
   * |      |     |     |     |     |     |     |     |     |     |     |      |
   * |-------------------------------------------------------------------------+
   * |       |     |     |     |     |     |     |     |     |     |     |     |
   * |-------------------------------------------------------------------------+
   * |     |     |     |     |      |          |       |MousL|MousD|MousU|MousR|
   * `-------------------------------------------------------------------------'
   */

[_L3] = LAYOUT(
  _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  _______, KC_PSCR, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______,
  _______, _______, _______, _______, _______,     _______,      _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
),
};

//LED keymap functions
 #ifdef LED_ENABLE
void led_chmode(void) {
  serial_send(101);
}

void led_toggle(void) {
  serial_send(100);
}
#endif

void tap_key(uint16_t keycode) {
  register_code  (keycode);
  unregister_code(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case LED_TOG:
        #ifdef LED_ENABLE
        led_toggle();
        #endif
        return false;
      case LED_CHG:
        #ifdef LED_ENABLE
        led_chmode();
        #endif
        return false;
    }
  }
  return true;
};

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
  [TD_MD] = ACTION_TAP_DANCE_FN(dance_media)
};

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_setrgb_teal();
  #endif
};

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);

  switch(layer) {
    case _QWERTY:
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb_teal();
      #endif
      break;
    case _L1:
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb_orange();
      #endif
      break;
    case _L2:
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb_magenta();
      #endif
      break;
    case _L3:
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb_green();
      #endif
      break;
  }

  return state;
};
