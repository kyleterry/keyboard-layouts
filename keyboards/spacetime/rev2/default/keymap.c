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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    QWERTY_1_14,
    QWERTY_2_14,
    QWERTY_3_14,
    QWERTY_4_ST
  ),

  [_LOWER] = LAYOUT_wrapper(
    LOWER_1_14,
    LOWER_2_14,
    LOWER_3_14,
    LOWER_4_ST
  ),

  [_RAISE] = LAYOUT_wrapper(
    RAISE_1_14,
    RAISE_2_14,
    RAISE_3_14,
    RAISE_4_ST
  ),

  [_ADJUST] = LAYOUT_wrapper(
    _________________FUNC_LEFT_6________________________, SQWER,     _______, _________________FUNC_RIGHT_6_______________________,
    ___________________BLANK_6__________________________, _______,   _______, ___________________BLANK_6__________________________,
    ___________________BLANK_6__________________________, _______,   _______, ___________________BLANK_6__________________________,
    _______,                            _______, _______, _______,   _______, _______, _______,                            _______
  ),

  [_NUM] = LAYOUT_wrapper(
    ___________________BLANK_6__________________________, _______,   _______, _______, _______________NUM_PAD_R1__________________,
    ___________________BLANK_6__________________________, _______,   _______, _______, _______________NUM_PAD_R2__________________,
    _______, RGB_MOD, RGB_TOG, _______, _______, _______, _______,   _______, _______, _______________NUM_PAD_R3__________________,
    _______,                            _______, _______, _______,   _______, _______, _______,                               KC_0
  ),

  [_MOUSE] = LAYOUT_wrapper(
    MOUSE_1_14,
    MOUSE_2_14,
    MOUSE_3_14,
    MOUSE_4_ST
  )
};
