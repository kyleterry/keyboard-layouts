#include "kyleterry.h"

#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ct/es|   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Ctl  | Alt  | GUI  |      |Lower |Space |Space |Raise |      | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_wrapper( \
      NUMBER_LEFT_6_______________________________________,                   NUMBER_RIGHT_6______________________________________, \
      QWERTY_L1_6_________________________________________,                   QWERTY_R1_6_________________________________________, \
      QWERTY_L2_6_________________________________________,                   QWERTY_R2_6_________________________________________, \
      QWERTY_L3_6_________________________________________, KC_LBRC, KC_RBRC, QWERTY_R3_6_________________________________________, \
      _______,  KC_LCTL, KC_LALT, KC_LGUI, _______, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |      |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  F6  |  F7  |  F8  |  F9  |  F10 |  (   |   )  |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_wrapper( \
      _________________LOWER_L1_6_________________________,                   _________________LOWER_R1_6_________________________, \
      ___________________BLANK_6__________________________,                   ___________________BLANK_6__________________________, \
      _________________LOWER_L2_6_________________________,                   _________________LOWER_R2_6_________________________, \
      _________________LOWER_L3_6_________________________, KC_LPRN, KC_RPRN, ___________________BLANK_6__________________________, \
      ___________________BLANK_6__________________________, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_wrapper( \
      _________________RAISE_L1_6_________________________,                   _________________RAISE_R1_6_________________________, \
      ___________________BLANK_6__________________________,                   ___________________BLANK_6__________________________, \
      _________________RAISE_L2_6_________________________,                   _________________RAISE_R2_6_________________________, \
      _________________RAISE_L3_6_________________________, _______, _______, _________________RAISE_R3_6_________________________, \
      ___________________BLANK_6__________________________, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff|      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT_wrapper( \
      _________________FUNC_LEFT_6________________________,                   _________________FUNC_RIGHT_6_______________________, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   ___________________BLANK___________________, KC_DEL,  \
      _______, _______, _______, AU_ON,   AU_OFF,  _______,                   ___________________BLANK_6__________________________, \
      ___________________BLANK_6__________________________, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      ___________________BLANK_6__________________________, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD  \
      )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
      startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {
  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}}};
  matrix_write_P(matrix, os_logo[0][0]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write_P(matrix, os_logo[0][1]);

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
