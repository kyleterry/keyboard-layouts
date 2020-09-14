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
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUM,
  _FUN
};

layer_state_t layer_state_set_rgb(layer_state_t state);
