#pragma once

//#define LEADER_PER_KEY_TIMING
//#define LEADER_TIMEOUT 250
#undef  SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D2
#define SERIAL_USE_MULTI_TRANSACTION
#define RGB_DI_PIN D3
#define RGBLED_NUM 50
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 25, 25 }
#define DRIVER_LED_TOTAL 50
#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }

#define TAPPING_TERM 250
//#define PERMISSIVE_HOLD
