#include QMK_KEYBOARD_H

/* this keymap is to provide a basic keyboard layout for testing the matrix
 * for more practical and complicated keymap refer to other keymaps in the same folder
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    KC_PAUS, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  MO(2),   MO(1),    KC_RGUI, MO(3), _______
  ),
  [1] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______,
    KC_TAB,  KC_MINS, KC_EQL,  KC_BSLS, KC_SLSH, KC_GRV,  KC_BSPC, KC_QUOT, KC_SCLN, KC_LBRC, KC_RBRC, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [2] = LAYOUT(
    KC_PMNS, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
    KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, KC_BSPC, _______, _______, _______, _______, _______, _______,
    _______, KC_P0,   KC_P0,   _______, _______, _______, _______, _______, _______, _______
  ),
  [3] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KB_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP,
    _______, _______, _______, _______, _______, _______, KC_SPC, _______, _______, _______
  ),
};


// Ctrl + ; = Enter
const key_override_t enter_key_override = ko_make_basic(MOD_MASK_CTRL, KC_SEMICOLON, KC_ENT);

// Ctrl + b = Backspace
const key_override_t backspace_key_override = ko_make_basic(MOD_MASK_CTRL, KC_B, KC_BACKSPACE);

// Ctrl + h = left_arrow
const key_override_t ctrl_h_key_override = ko_make_basic(MOD_MASK_CTRL, KC_H, KC_LEFT);
// Ctrl + l = right_arrow
const key_override_t ctrl_l_key_override = ko_make_basic(MOD_MASK_CTRL, KC_L, KC_RIGHT);
// Ctrl + j = down_arrow
const key_override_t ctrl_j_key_override = ko_make_basic(MOD_MASK_CTRL, KC_J, KC_DOWN);
// Ctrl + k = up_arrow
const key_override_t ctrl_k_key_override = ko_make_basic(MOD_MASK_CTRL, KC_K, KC_UP);

// CMD + Q = CMD (to prevent accidental quit)
const key_override_t cmd_q_key_override = ko_make_basic(MOD_BIT(KC_LGUI), KC_Q, KC_LGUI);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&enter_key_override,
	&backspace_key_override,
	&ctrl_h_key_override,
	&ctrl_l_key_override,
	&ctrl_j_key_override,
	&ctrl_k_key_override,
	&cmd_q_key_override,
	NULL // Null terminate the array of overrides!
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case KC_ESC:
        if (get_mods() == MOD_BIT(KC_LGUI) || get_mods() == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            // Do not let QMK process the keycode further
            return false;
        }
        // Else, let QMK process the KC_ESC keycode as usual
        unregister_code(KC_TAB);
        return true;
    }
    return true;
};
