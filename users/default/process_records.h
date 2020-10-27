#pragma once

#define ______      KC_TRNS
#define LOWER       MO(_LOWER)
#define RAISE       MO(_RAISE)
#define NUM         MO(_NUM)
#define MOUSE       TG(_MOUSE)
#define OS_LGUI     OSM (MOD_LGUI)
#define OS_SGUI     OSM (MOD_LGUI | MOD_LSFT) // tap for LGUI + LSHIFT
#define OS_LCTL     OSM (MOD_LCTL)
#define OS_LSFT     OSM(MOD_LSFT)
#define OS_RSFT     OSM(MOD_RSFT)
#define SQWER       TO(_QWERTY)
#define CTRLE       CTL_T(KC_ESC)  // hold for ctrl; tap for escape
#define ALTT        ALT_T(KC_TAB)  // hold for alt; tap for tab
#define SFT_EQL     RSFT_T(KC_EQL) // hold for r shift; tap for =
#define RALTQ       RALT_T(KC_QUOT)
