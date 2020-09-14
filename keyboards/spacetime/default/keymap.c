/* Copyright 2019 Kyle Terry
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
#include "kyleterry.h"

#if defined(RGBLIGHT_ENABLE)
extern rgblight_config_t rgblight_config;
bool has_initialized;
#endif

#ifdef RGBLIGHT_ENABLE
void rgblight_sethsv_default_helper(uint8_t index) {
    rgblight_sethsv_at(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, index);
}
#endif // RGBLIGHT_ENABLE

/*  layer template:
 *  [_LAYER] = LAYOUT(
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
 *    _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
 *    _______,                            _______, _______, _______,   _______, _______, _______,                            _______
 *  ),
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    _________________QWERTY_L1_6________________________, KC_LCTL,   T_C,     _________________QWERTY_R1_6________________________,
    _________________QWERTY_L2_6________________________, KC_LALT,   KC_LEAD, _________________QWERTY_R2_6________________________,
    _________________QWERTY_L3_6________________________, NUM,       OS_LGUI, _________________QWERTY_R3_6________________________,
    KC_LCTL,                            OS_LGUI, KC_SPC, LOWER,      RAISE,   KC_SPC,  KC_ENT,                             KC_RALT
  ),

  [_LOWER] = LAYOUT_wrapper(
    _________________LOWER_L1_6_________________________, KC_LPRN,   T_PN,    _________________LOWER_R1_6_________________________,
    _________________LOWER_L2_6_________________________, KC_LBRC,   T_SB,    _________________LOWER_R2_6_________________________,
    _________________LOWER_L3_6_________________________, KC_LCBR,   T_CB,    _________________LOWER_R3_6_________________________,
    _______,                            _______, _______, _______,   _______, _______, _______,                            _______
  ),

  [_RAISE] = LAYOUT_wrapper(
    _________________RAISE_L1_6_________________________, T_MD,      KC_VOLU, _________________RAISE_R1_6_________________________,
    _________________RAISE_L2_6_________________________, KC_MNXT,   KC_VOLD, _________________RAISE_R2_6_________________________,
    _________________RAISE_L3_6_________________________, _______,   _______, _________________RAISE_R3_6_________________________,
    _______,                            _______, _______, _______,   _______, _______, _______,                            _______
  ),

  [_ADJUST] = LAYOUT_wrapper(
    _________________FUNC_LEFT_6________________________, SQWER,     _______, _________________FUNC_RIGHT_6_______________________,
    ___________________BLANK_6__________________________, _______,   _______, ___________________BLANK_6__________________________,
    ___________________BLANK_6__________________________, _______,   _______, ___________________BLANK_6__________________________,
    _______,                            _______, _______, _______,   _______, _______, _______,                            _______
  ),

  [_NUM] = LAYOUT_wrapper(
    ___________________BLANK_6__________________________, _______,   _______, _______, _________________NUM_R1____________________,
    ___________________BLANK_6__________________________, _______,   _______, _______, _________________NUM_R2____________________,
    _______, RGB_MOD, RGB_TOG, _______, _______, _______, _______,   _______, _______, _________________NUM_R3____________________,
    _______,                            _______, _______, _______,   _______, _______, _______,                               KC_0
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#define KEYLOG_LEN 5
char keylog_str[KEYLOG_LEN] = {};
uint8_t keylogs_str_idx = 0;
uint16_t log_timer = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {  add_keylog(keycode); }
#endif
  return true;
}

void matrix_init_user(void) {
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
  }
}

void led_set_user(uint8_t usb_led) {
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  oled_on();
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("raise\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("lower\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }
}
#endif
