#include "kyleterry.h"

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef RGBLIGHT_ENABLE
  state = layer_state_set_rgb(state);
#endif

  return layer_state_set_keymap(state);
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_setrgb_teal();
#endif
}

// borrowed from drashna: https://github.com/qmk/qmk_firmware/blob/master/users/drashna/rgb_stuff.c#L153
void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
#ifdef RGBLIGHT_ENABLE
  rgblight_sethsv_noeeprom(hue, sat, val);
  wait_us(175);  // Add a slight delay between color and mode to ensure it's processed correctly
  rgblight_mode_noeeprom(mode);
#endif
}

layer_state_t layer_state_set_rgb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
  switch (get_highest_layer(state)) {
    case _RAISE:
      rgblight_set_hsv_and_mode(HSV_GREEN, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    case _LOWER:
      rgblight_set_hsv_and_mode(HSV_YELLOW, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    case _ADJUST:
      rgblight_set_hsv_and_mode(HSV_BLUE, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    case _NUM:
      rgblight_set_hsv_and_mode(HSV_ORANGE, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    default:
      rgblight_set_hsv_and_mode(HSV_PURPLE, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
  }
#endif

  return state;
}
