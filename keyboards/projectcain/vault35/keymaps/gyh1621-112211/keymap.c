
 /* Copyright 2021 projectcain
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

// =================== MACROS ===================

enum custom_keycodes {
    SPOTLIGHT = SAFE_RANGE,
    CTRL_Z,  // zsh: move current process to background
    ALT_L,  // vim copilot: auto complete
    CTRL_A,  // wezterm: leader key
    CTRL_S,  // tmux: leader key
    CTRL_LEFT,  // macos: previous desktop
    CTRL_RIGHT,  // macos: next desktop
};

// =================== COMBOS ===================

enum combos {
    AS_CTRL_COMBO,
    QW_ESC_COMBO,
};

const uint16_t PROGMEM as_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
  [AS_CTRL_COMBO] = COMBO(as_combo, KC_LCTL),
  [QW_ESC_COMBO] = COMBO(qw_combo, KC_ESC),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPOTLIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(" "));
            }
            break;
        case CTRL_Z:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("z"));
            }
            break;
        case ALT_L:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("l"));
            }
            break;
        case CTRL_A:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("a"));
            }
            break;
        case CTRL_S:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("s"));
            }
            break;
        case CTRL_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
            }
            break;
        case CTRL_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RGHT)));
            }
            break;
    }
    return true;
}

// =================== KEY OVERRIDES ===================

// Ctrl + h = left_arrow
const key_override_t ctrl_h_key_override = ko_make_basic(MOD_MASK_CTRL, KC_H, KC_LEFT);
// Ctrl + l = right_arrow
const key_override_t ctrl_l_key_override = ko_make_basic(MOD_MASK_CTRL, KC_L, KC_RIGHT);
// Ctrl + j = down_arrow
const key_override_t ctrl_j_key_override = ko_make_basic(MOD_MASK_CTRL, KC_J, KC_DOWN);
// Ctrl + k = up_arrow
const key_override_t ctrl_k_key_override = ko_make_basic(MOD_MASK_CTRL, KC_K, KC_UP);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&ctrl_h_key_override,
	&ctrl_l_key_override,
	&ctrl_j_key_override,
	&ctrl_k_key_override,
	NULL // Null terminate the array of overrides!
};

// =================== LAYERS ===================

enum layers{
  BASE,
  NUM,
  SYM,
  META
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_4space(
    KC_Q,             KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_A,             KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENTER,
    LSFT_T(KC_Z),     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  MO(2),
            KC_LALT, KC_LGUI,       KC_SPACE, MO(1),     KC_RGUI, KC_RALT
  ),

  [NUM] = LAYOUT_split_4space(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB, KC_MINUS, KC_EQL,  KC_BSLS, KC_SLSH, KC_GRV,   KC_QUOT, KC_SCLN, KC_LBRC, KC_RBRC,
    KC_LSFT, CTRL_Z,   ALT_L,   CTRL_A,  KC_BSPC, CTRL_S,   KC_NO,   KC_NO,   KC_NO,   OSM(MOD_RSFT),
            QK_CAPS_WORD_TOGGLE, SPOTLIGHT,       KC_TAB, KC_TAB,     KC_TRNS, KC_TRNS
  ),

  [SYM] = LAYOUT_split_4space(
    KC_ESC,    KC_F7,  KC_F8,  KC_F9,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_UP,    CTRL_LEFT,  CTRL_RIGHT,  KC_TRNS,
    KC_TAB,    KC_F4,  KC_F5,  KC_F6,  KC_TRNS,  KC_TRNS,  KC_LEFT,  KC_RIGHT, KC_TRNS,  KC_TRNS,
    KC_LSFT,   KC_F1,  KC_F2,  KC_F3,  KC_KB_VOLUME_DOWN,  KC_KB_VOLUME_UP,  KC_DOWN,  KC_PGDN,  KC_PGUP,  KC_TRNS,
            KC_LALT,   KC_LGUI,         KC_TRNS, KC_TRNS,    AC_TOGG, QK_BOOT
  ),
};
