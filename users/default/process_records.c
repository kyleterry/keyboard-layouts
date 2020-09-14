#include "kyleterry.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_DRIVER_ENABLE
    if (record->event.pressed) {  add_keylog(keycode); }
#endif

  return true;
}
