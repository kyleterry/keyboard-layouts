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
#include "kyleterry.h"

#ifdef LED_ENABLE
  #include "protocol/serial.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY Layer
   * ,-------------------------------------------------------------------------.
   * | Tab |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bspace |
   * |-------------------------------------------------------------------------+
   * |ct/es |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  Ent |
   * |-------------------------------------------------------------------------+
   * | Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  '  |
   * |-------------------------------------------------------------------------+
   * | Ctl | Alt | Gui |Adj  |Lowr  |   Space   |Rais  | OSGUI|OSCTL| VUp|VDOWN|
   * `-------------------------------------------------------------------------'
   */
[_QWERTY] = LAYOUT_wrapper(
  KC_TAB,  QWERTY_1______________________________________________________________________________, KC_BSPC,
  CTRLE,   QWERTY_2______________________________________________________________________________, KC_ENT,
  KC_LSFT, QWERTY_3______________________________________________________________________________, KC_QUOT,
  KC_LCTL, KC_LALT, KC_LGUI, ADJUST, LOWER,        KC_SPC,       RAISE, OS_RGUI, OS_RCTL, KC_VOLU, KC_VOLD
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
[_RAISE] = LAYOUT_wrapper(
  RAISE_L1_6__________________________________________, RAISE_R1_6__________________________________________,
  RAISE_L2_6__________________________________________, RAISE_R2_6__________________________________________,
  RAISE_L3_6__________________________________________, RAISE_R3_6__________________________________________,
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
[_LOWER] = LAYOUT_wrapper(
  LOWER_L1_6__________________________________________, LOWER_R1_6__________________________________________,
  LOWER_L2_6__________________________________________, LOWER_R2_6__________________________________________,
  LOWER_L3_6__________________________________________, LOWER_R3_6__________________________________________,
  _______, _______, _______, _______, _______,     _______,      _______, KC_MPRV, KC_MSTP, T_MD,    KC_MNXT
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

[_ADJUST] = LAYOUT_wrapper(
  ADJUST_L1_6_________________________________________, ADJUST_R1_6_________________________________________,
  ADJUST_L2_6_________________________________________, ADJUST_R2_6_________________________________________,
  ADJUST_L3_6_________________________________________, ADJUST_R3_6_________________________________________,
  _______, _______, _______, _______, _______,     _______,      _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
),
};
