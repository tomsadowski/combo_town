// tomsadowski
// keymap for split_3x5_2 keyboards

#include "action_layer.h"
#include "process_combo.h"
#include QMK_KEYBOARD_H
#include "action.h"
#include "keycodes.h"
#include "quantum_keycodes.h"

#define MAX_HOLD 8

enum my_keycodes {CAPS_ON = SAFE_RANGE, KEY_TRAP, ALPHA_ON_CAPS_OFF};
typedef enum {CLOSED, HOLD, STANDBY, FREE} key_trap_state;
typedef struct {
    key_trap_state state;
    uint16_t held_keys[MAX_HOLD];
    uint16_t free_key;
    unsigned short size;
}
key_trap;
static key_trap trap = {CLOSED, {0}, KC_NO, 0};

enum layers {ALPHA_LAYER, GAME_LAYER, GME2_LAYER, LNAV_LAYER, NMBR_LAYER, MOUS_LAYER,
             MO_ALP_LYR, MO_MAL_LYR, MO_MNM_LYR, MO_NMB_LYR, MO_MSE_LYR};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALPHA_LAYER] = LAYOUT_split_3x5_2( // ALPHA: Alphabet, punctuation, editing
        KC_X,    KC_C,    KC_H,    KC_B,    KC_Q,            KC_Z,    KC_Y,    KC_W,    KC_P,    KC_J,
        KC_A,    KC_S,    KC_R,    KC_T,    KC_COMMA,        KC_DOT,  KC_E,    KC_I,    KC_O,    KC_N,
        KC_V,    KC_F,    KC_L,    KC_D,    KC_MINS,         KC_EQL,  KC_U,    KC_M,    KC_G,    KC_K,
                                  KC_BSPC, LT(MO_MSE_LYR, KC_SPC),       LT(MO_NMB_LYR, KC_SPC),            KC_DEL),
    [GAME_LAYER] = LAYOUT_split_3x5_2( // GAME: Base sans combos and hold-tap features
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
                                               _______, KC_SPC,          KC_0,    _______),
    [GME2_LAYER] = LAYOUT_split_3x5_2( // GAME 2: Reserved for games without key remapping. animal well, for instance
        KC_A,    KC_W,   KC_S,     KC_D,    KC_F,            KC_G,    KC_H,     KC_J,   KC_K,    KC_L,
        KC_LEFT, KC_UP,  KC_DOWN,  KC_RGHT, _______,         _______, KC_SPC,   KC_Z,   KC_X,    KC_C,
        KC_4,    KC_5,   KC_6,     KC_7,    KC_8,            KC_9,    KC_0,     KC_1,   KC_2,    KC_3,
                                               _______, KC_LSFT,         KC_V,    _______),
    [LNAV_LAYER] = LAYOUT_split_3x5_2( // LEFT NAVIGATION: Navigation on the left, useful when flashing
        KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,         _______, _______, _______, _______, _______,
        KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, _______,         _______, _______, _______, _______, _______,
        _______, KC_WH_U, KC_WH_D, _______, _______,         _______, _______, _______, _______, _______,
                                               KC_BTN2, KC_BTN1,         KC_SPC,  _______),
    [NMBR_LAYER] = LAYOUT_split_3x5_2( // NUMBER: digits, navigation keys, and symbols
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_BSLS, KC_SLSH, KC_QUOT, KC_SCLN, _______,         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        _______, KC_GRV,  KC_LBRC, KC_RBRC, _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                               _______, _______,         LT(MO_ALP_LYR, KC_SPC),            _______),
    [MOUS_LAYER] = LAYOUT_split_3x5_2( // MOUSE: Mouse and function keys
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_ACL1, KC_ACL0, _______,         _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        _______, _______, _______, KC_ACL2, _______,         _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                                  _______, LT(MO_MAL_LYR, KC_SPC),       KC_BTN1, KC_BTN2),
    [MO_ALP_LYR] = LAYOUT_split_3x5_2( // MOMENTARY ALPHA: Accessed from NUMBER
        KC_X,   KC_C,     KC_H,    KC_B,    KC_Q,            KC_Z,    KC_Y,    KC_W,    KC_P,    KC_J,
        KC_A,   KC_S,     KC_R,    KC_T,    _______,         _______, KC_E,    KC_I,    KC_O,    KC_N,
        KC_V,   KC_F,     KC_L,    KC_D,    _______,         _______, KC_U,    KC_M,    KC_G,    KC_K,
                                               _______, KC_SPC,          _______, _______),
    [MO_MAL_LYR] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE ALPHA: accessed from MOUSE
        KC_X,   KC_C,     KC_H,    KC_B,    KC_Q,            KC_Z,    KC_Y,    KC_W,    KC_P,     KC_J,
        KC_A,   KC_S,     KC_R,    KC_T,    _______,         _______, KC_E,    KC_I,    KC_O,     KC_N,
        KC_V,   KC_F,     KC_L,    KC_D,    _______,         _______, KC_U,    KC_M,    KC_G,     KC_K,
                                               _______, _______,         LT(MO_MNM_LYR, KC_SPC),            KC_DEL),
    [MO_MNM_LYR] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE NUMBER: accessed from MOMENTARY MOUSE ALPHA
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_BSLS, KC_SLSH, KC_QUOT, KC_SCLN, _______,         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        _______, KC_GRV,  KC_LBRC, KC_RBRC, _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                  _______, LT(MO_MAL_LYR, KC_SPC),       _______, _______),
    [MO_NMB_LYR] = LAYOUT_split_3x5_2( // MOMENTARY NUMBER: accessed from ALPHA
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_BSLS, KC_SLSH, KC_QUOT, KC_SCLN, _______,         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        _______, KC_GRV,  KC_LBRC, KC_RBRC, _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                               _______, KC_SPC,          _______, _______),
    [MO_MSE_LYR] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE: accessed from ALPHA
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_ACL1, KC_ACL0, _______,         _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        _______, _______, KC_SCLN, KC_ACL2, _______,         _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                                               _______, _______,         KC_BTN1, KC_BTN2),
};

enum combos {
  /*   |___|   |XXX|   |XXX|   |___|   |___|      |___|   |___|   |XXX|   |XXX|   |___|   */
                    SPC_COMBO_L,                               TAB_COMBO_R,
                    SFT_COMBO_L,                               SFT_COMBO_R,
                    CAP_COMBO_L,                               ALP_COMBO_R,
  /*   |XXX|   |___|   |___|   |XXX|   |___|      |___|   |XXX|   |___|   |___|   |XXX|   */
                    ALT_COMBO_L,                               ALT_COMBO_R,
                    CTL_COMBO_L,                               CTL_COMBO_R,
                    LNV_COMBO_L,                               MSE_COMBO_R,
  /*   |___|   |___|   |___|   |XXX|   |XXX|      |XXX|   |XXX|   |___|   |___|   |___|   */
                    PSC_COMBO_L,                               PSC_COMBO_R,
                    ESC_COMBO_L,                               ENT_COMBO_R,
                    GUI_COMBO_L,                               GUI_COMBO_R,
  /*   |XXX|   |___|   |___|   |___|   |XXX|      |XXX|   |___|   |___|   |___|   |XXX|   */
                    KTP_COMBO_L,                               KTP_COMBO_R,
                    GME_COMBO_L,                               NMB_COMBO_R,
                    GM2_COMBO_L,
};

//                                          L:  -  X  X  -  -
const uint16_t PROGMEM spc_combo_l[] = {KC_C,   KC_H,     COMBO_END};
const uint16_t PROGMEM sft_combo_l[] = {KC_S,   KC_R,     COMBO_END};
const uint16_t PROGMEM cap_combo_l[] = {KC_F,   KC_L,     COMBO_END};
//                                          L:  X  -  -  X  -
const uint16_t PROGMEM alt_combo_l[] = {KC_X,   KC_B,     COMBO_END};
const uint16_t PROGMEM ctl_combo_l[] = {KC_A,   KC_T,     COMBO_END};
const uint16_t PROGMEM lnv_combo_l[] = {KC_V,   KC_D,     COMBO_END};
//                                          L:  -  -  -  X  X
const uint16_t PROGMEM psc_combo_l[] = {KC_B,   KC_Q,     COMBO_END};
const uint16_t PROGMEM esc_combo_l[] = {KC_T,   KC_COMMA, COMBO_END};
const uint16_t PROGMEM gui_combo_l[] = {KC_D,   KC_MINS,  COMBO_END};
//                                          L:  X  -  -  -  X
const uint16_t PROGMEM ktp_combo_l[] = {KC_X,   KC_Q,     COMBO_END};
const uint16_t PROGMEM gme_combo_l[] = {KC_A,   KC_COMM,  COMBO_END};
const uint16_t PROGMEM gm2_combo_l[] = {KC_V,   KC_MINS,  COMBO_END};
//                                          R:  -  -  X  X  -
const uint16_t PROGMEM tab_combo_r[] = {KC_W,   KC_P,     COMBO_END};
const uint16_t PROGMEM sft_combo_r[] = {KC_I,   KC_O,     COMBO_END};
const uint16_t PROGMEM alp_combo_r[] = {KC_M,   KC_G,     COMBO_END};
//                                          R:  -  X  -  -  X
const uint16_t PROGMEM alt_combo_r[] = {KC_Y,   KC_J,     COMBO_END};
const uint16_t PROGMEM ctl_combo_r[] = {KC_E,   KC_N,     COMBO_END};
const uint16_t PROGMEM mse_combo_r[] = {KC_U,   KC_K,     COMBO_END};
//                                          R:  X  X  -  -  -
const uint16_t PROGMEM psc_combo_r[] = {KC_Z,   KC_Y,     COMBO_END};
const uint16_t PROGMEM ent_combo_r[] = {KC_DOT, KC_E,     COMBO_END};
const uint16_t PROGMEM gui_combo_r[] = {KC_EQL, KC_U,     COMBO_END};
//                                          R:  X  -  -  -  X
const uint16_t PROGMEM ktp_combo_r[] = {KC_Z,   KC_J,     COMBO_END};
const uint16_t PROGMEM nmb_combo_r[] = {KC_DOT, KC_N,     COMBO_END};

combo_t key_combos[] = {
  /*   |___|   |XXX|   |XXX|   |___|   |___|               |___|   |___|   |XXX|   |XXX|   |___|   */
  [SPC_COMBO_L] = COMBO(spc_combo_l, KC_SPC),          [TAB_COMBO_R] = COMBO(tab_combo_r, KC_TAB),
  [SFT_COMBO_L] = COMBO(sft_combo_l, KC_LSFT),         [SFT_COMBO_R] = COMBO(sft_combo_r, KC_RSFT),
  [CAP_COMBO_L] = COMBO(cap_combo_l, CAPS_ON),         [ALP_COMBO_R] = COMBO(alp_combo_r, ALPHA_ON_CAPS_OFF),
  /*   |XXX|   |___|   |___|   |XXX|   |___|               |___|   |XXX|   |___|   |___|   |XXX|   */
  [ALT_COMBO_L] = COMBO(alt_combo_l, KC_LALT),         [ALT_COMBO_R] = COMBO(alt_combo_r, KC_RALT),
  [CTL_COMBO_L] = COMBO(ctl_combo_l, KC_LCTL),         [CTL_COMBO_R] = COMBO(ctl_combo_r, KC_RCTL),
  [LNV_COMBO_L] = COMBO(lnv_combo_l, TO(LNAV_LAYER)),  [MSE_COMBO_R] = COMBO(mse_combo_r, TO(MOUS_LAYER)),
  /*   |___|   |___|   |___|   |XXX|   |XXX|               |XXX|   |XXX|   |___|   |___|   |___|   */
  [PSC_COMBO_L] = COMBO(psc_combo_l, KC_PSCR),         [PSC_COMBO_R] = COMBO(psc_combo_r, KC_PSCR),
  [ESC_COMBO_L] = COMBO(esc_combo_l, KC_ESC),          [ENT_COMBO_R] = COMBO(ent_combo_r, KC_ENT),
  [GUI_COMBO_L] = COMBO(gui_combo_l, KC_LGUI),         [GUI_COMBO_R] = COMBO(gui_combo_r, KC_RGUI),
  /*   |XXX|   |___|   |___|   |___|   |XXX|               |XXX|   |___|   |___|   |___|   |XXX|   */
  [KTP_COMBO_L] = COMBO(ktp_combo_l, KEY_TRAP),        [KTP_COMBO_R] = COMBO(ktp_combo_r, KEY_TRAP),
  [GME_COMBO_L] = COMBO(gme_combo_l, TO(GAME_LAYER)),  [NMB_COMBO_R] = COMBO(nmb_combo_r, TO(NMBR_LAYER)),
  [GM2_COMBO_L] = COMBO(gm2_combo_l, TO(GME2_LAYER)),

};

// Exclude some combos from game layers
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(GAME_LAYER) ||
        layer_state_is(GME2_LAYER)) {
        switch (combo_index) {
            case ESC_COMBO_L:
            case ENT_COMBO_R:
            case GME_COMBO_L:
            case GM2_COMBO_L:
            case LNV_COMBO_L:
            case ALP_COMBO_R:
            case MSE_COMBO_R:
            case NMB_COMBO_R:
                return true;
            default: return false;
        }
    }
    return true;
}

// Shorten combo term when in game layers
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    if (layer_state_is(GAME_LAYER) ||
        layer_state_is(GME2_LAYER))
        return 6;
    return COMBO_TERM;
}

// Switching to non-alpha layers breaks capsword
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case GAME_LAYER ... MOUS_LAYER:
            caps_word_off(); break;
        default: break;
    }
  return state;
}

// Space does not break capsword
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        // Escape, and modifiers break capsword
        case KC_ESC:
        case KC_LCTL:
        case KC_LALT:
        case KC_LGUI:
        case KC_RCTL:
        case KC_RALT:
        case KC_RGUI: return false;
        // Everything else lets capsword continue.
        default: return true;
    }
}
// prevent user from accidentally triggering F keys
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(MO_MSE_LYR, KC_SPC):
            return true;
        default:
            return false;
    }
}
// common symbols like apostrophe can be accessed without breaking flow
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(MO_NMB_LYR, KC_SPC):
            return true;
        default:
            return false;
    }
}
// Define behavior of custom keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALPHA_ON_CAPS_OFF:
            caps_word_off();
            layer_move(ALPHA_LAYER);
            return true;

        case KEY_TRAP:
            if (record->event.pressed)
                trap.state = HOLD;
            else if (trap.free_key == KC_NO)
                trap.state = STANDBY;
            else
                trap.state = FREE;
            return false;

        case KC_A ... KC_RGUI:
            if (trap.state == CLOSED)
                return true;
            if (record->event.pressed) {
                if (trap.state != FREE)
                    trap.free_key = keycode;
                if (trap.state == STANDBY)
                    trap.state = FREE;
                return true;
            }
            if (trap.state == HOLD && trap.size < MAX_HOLD) {
                if (keycode == trap.free_key)
                    trap.free_key = KC_NO;
                trap.held_keys[trap.size] = keycode;
                trap.size++;
                return false;
            }
            if (trap.state == HOLD || trap.free_key == keycode) {
                for (int i = 0; i < trap.size; i++) {
                    unregister_code(trap.held_keys[i]);
                    trap.held_keys[i] = KC_NO;
                }
                trap.size = 0;
                trap.free_key = KC_NO;
                trap.state = CLOSED;
            }
            return true;

        case CAPS_ON:
            caps_word_on();
            return false;

        default: return true;
    }
}
