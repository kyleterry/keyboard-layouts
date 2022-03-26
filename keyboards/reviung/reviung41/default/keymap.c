#include "kyleterry.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_reviung41_wrapper(
    QWERTY_1_12,
    QWERTY_2_12,
    QWERTY_3_12,
    QWERTY_4_R41
  ),
  [_RAISE] = LAYOUT_reviung41_wrapper(
    RAISE_1_12,
    RAISE_2_12,
    RAISE_3_12,
    RAISE_4_R41
  ),
  [_LOWER] = LAYOUT_reviung41_wrapper(
    LOWER_1_12,
    LOWER_2_12,
    LOWER_3_12,
    LOWER_4_R41
  ),
  [_ADJUST] = LAYOUT_reviung41_wrapper(
    ADJUST_L1_6_________________________________________,          ADJUST_R1_6_________________________________________,
    ADJUST_L2_6_________________________________________,          ADJUST_R2_6_________________________________________,
    ADJUST_L3_6_________________________________________,          ADJUST_R3_6_________________________________________,
                                        _______, _______, _______, _______, _______
  ),
};
