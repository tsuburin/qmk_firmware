/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "keyball61.h"

enum my_keycodes {
    BALL_MOVED = KEYBALL_SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_right_ball(
    KC_GRV   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                   KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                   KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_LBRC  ,
    KC_CAPS  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                   KC_H     , KC_J     , KC_K     , KC_L     , LT(2,KC_SCLN), KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , TO(0)    ,             MO(1)    , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , TO(1)    ,
    TO(0)    , KC_LGUI  , MO(2)    , KC_LALT  , TO(0)    , KC_SPC   , KC_DEL   ,             KC_BSPC  , KC_ENT   ,                                  TO(3)    , MO(2)
  ),

  [1] = LAYOUT_right_ball(
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                   XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_EQL   ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                   XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_RBRC  ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                   KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , XXXXXXX  , KC_BSLS  ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  ,             TO(0)    , KC_END   , KC_PGDN  , KC_PGUP  , KC_HOME  , XXXXXXX  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,             _______  , _______  ,                                  _______  , _______
  ),

  [2] = LAYOUT_right_ball(
    KC_ESC   , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                   KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                   XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_F12   ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                   XXXXXXX  , KC_BTN1  , KC_BTN3  , KC_BTN2  , SCRL_MO  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  ,             _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,             _______  , _______  ,                                  _______  , _______
  ),

  [3] = LAYOUT_right_ball(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                   RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                   RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                   CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , _______  ,             _______  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , _______  , _______  , _______  , _______  , _______  ,             _______  , KC_BSPC                                   , _______  , QK_BOOT
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(2, KC_SCLN): {
            if (!record->tap.count) {
                // Intercept hold function to enable scroll mode
                keyball_set_scroll_mode(record -> event.pressed);
                return true;
            }
        }
    }

    return true;
}

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true); // always required before the auto mouse feature will work
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // スクロール方向逆転
    mouse_report.v = -mouse_report.v;
    mouse_report.h = -mouse_report.h;

    return mouse_report;
}
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LT(2, KC_SCLN):
            return true;
        default:
            return false;
    }
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CPI_I100:
        case CPI_D100:
        case CPI_I1K:
        case CPI_D1K:
        case SCRL_MO:
            return true;
    }

    return false;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
