#pragma once
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "rows.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#  include "tap_dance.h"
#endif

enum userspace_layers {
  _QWERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUM,
  _MOUSE
};

layer_state_t  layer_state_set_rgb(layer_state_t state);

#ifdef POINTING_DEVICE_ENABLE
report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report);
bool           process_record_pointing(uint16_t keycode, keyrecord_t* record);
void           trackball_register_button(bool pressed, enum mouse_buttons button);
#endif

typedef union {
    struct {
        bool is_scrolling :1;
    };
} userspace_config_t;

extern userspace_config_t userspace_config;
