#include "tap_dance.h"

void td_common(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      /* this case handles ctrl+o which is my tmux prefix
       */
      tap_code16(C(KC_O));
      reset_tap_dance(state);
      break;
    case 2:
      /* this case handles shift+insert which is a common way
       * for me to paste text in linux
       */
      tap_code16(S(KC_INS));
      reset_tap_dance(state);
      break;
  }
}

void td_media(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_MPLY);
      reset_tap_dance(state);
      break;
    case 2:
      tap_code16(KC_MUTE);
      reset_tap_dance(state);
      break;
  }
}

void td_parens(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_RPRN);
      break;
    case 2:
      SEND_STRING("()");
      break;
    case 3:
      SEND_STRING("()");
      tap_code(KC_LEFT);
      break;
  }

  reset_tap_dance(state);
}

void td_square(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code(KC_RBRC);
      break;
    case 2:
      SEND_STRING("[]");
      break;
    case 3:
      SEND_STRING("[]");
      tap_code(KC_LEFT);
      break;
  }

  reset_tap_dance(state);
}

void td_curly(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_RCBR);
      break;
    case 2:
      SEND_STRING("{}");
      break;
    case 3:
      SEND_STRING("{}");
      tap_code(KC_LEFT);
      break;
  }

  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_C]  = ACTION_TAP_DANCE_FN(td_common),
  [TD_MD] = ACTION_TAP_DANCE_FN(td_media),
  [TD_PN] = ACTION_TAP_DANCE_FN(td_parens),
  [TD_SB] = ACTION_TAP_DANCE_FN(td_square),
  [TD_CB] = ACTION_TAP_DANCE_FN(td_curly),
};

