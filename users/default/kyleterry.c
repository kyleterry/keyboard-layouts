#include "kyleterry.h"

userspace_config_t userspace_config;

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef RGBLIGHT_ENABLE
  state = layer_state_set_rgb(state);
#endif

  return layer_state_set_keymap(state);
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_setrgb_purple();
#endif

  keyboard_post_init_keymap();
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
    case _MOUSE:
      rgblight_set_hsv_and_mode(HSV_RED, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    default:
      rgblight_set_hsv_and_mode(HSV_PURPLE, RGBLIGHT_MODE_STATIC_LIGHT);
      break;
  }
#endif

  return state;
}


#ifdef ENCODER_ENABLE
__attribute__((weak)) void encoder_update_keymap(uint8_t index, bool clockwise) {}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (layer_state_is(_RAISE)) {
    if (clockwise) {
        tap_code(KC_PGUP);
    } else {
        tap_code(KC_PGDN);
    }
  } else {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
  }

  encoder_update_keymap(index, clockwise);
  return true;
}
#endif

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {
  pimoroni_trackball_set_rgbw(255,128,0,0);
}

__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (userspace_config.is_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = mouse_report.y = 0; 
    }

    return pointing_device_task_keymap(mouse_report);
}

bool process_record_pointing(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_BTN1:
    if (userspace_config.is_scrolling) {
      trackball_register_button(record->event.pressed, MOUSE_BTN2);
    }

    break;
  }

  return true;
}

void trackball_register_button(bool pressed, enum mouse_buttons button) {
    report_mouse_t currentReport = pointing_device_get_report();
    if (pressed) {
        currentReport.buttons |= button;
    } else {
        currentReport.buttons &= ~button;
    }
    pointing_device_set_report(currentReport);
}
#endif
