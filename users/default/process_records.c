#include "kyleterry.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(!( process_record_keymap(keycode, record)
#ifdef POINTING_DEVICE_ENABLE
        && process_record_pointing(keycode, record)
#endif
        && true)) {
    return false;
  }

  switch (keycode) {
  case M_SCRL:
    if(record->event.pressed){
      userspace_config.is_scrolling = true;
    } else{
      userspace_config.is_scrolling = false;
    }

    break;
  }

  return true;
}
