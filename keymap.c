// tomsadowski
// keymap for split_3x5_2 keyboards

#include "action_layer.h"
#include "process_combo.h"
#include QMK_KEYBOARD_H
#include "action.h"
#include "keycodes.h"
#include "quantum_keycodes.h"

// constants
#define MAX_BLOCK 8
#define SHORT_COMBO_TERM 6

// keycodes
enum my_keycodes {
    CAPS_ON = SAFE_RANGE,
    ALPHA_ON_CAPS_OFF,
    RELEASE_GATE
};
bool press_caps_on(void);
bool press_alpha_on_caps_off(void);
bool press_release_gate(void);
bool release_release_gate(void);
bool press_key_with_release_gate(uint16_t);
bool release_key_with_release_gate(uint16_t);

// layers
enum layers {
    ALPHA_LAYER,
    NUMBER_LAYER,
    MOUSE_LAYER,
    LEFT_NUMBER_LAYER,
    LEFT_MOUSE_LAYER,
    GAME_LAYER,
    MOMENTARY_ALPHA_LAYER,
    MOMENTARY_MOUSEALPHA_LAYER,
    MOMENTARY_NUMBER_LAYER,
    MOMENTARY_MOUSE_LAYER
};
static bool in_momentary_layer = false;

// release_gate
typedef enum {
    BLOCK,
    WATCH,
    LEND,
    SUSPEND,
    NONE
} release_gate_state_t;
typedef struct {
    release_gate_state_t state;
    uint16_t lever;
    uint16_t blocked_keys[MAX_BLOCK];
    unsigned short size;
} release_gate_t;

static release_gate_t release_gate = {NONE, KC_NO, {0}, 0};

// layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALPHA_LAYER] = LAYOUT_split_3x5_2( // ALPHA: Alphabet, punctuation, editing
        KC_X,    KC_C,    KC_H,    KC_B,    KC_Q,            KC_Z,    KC_Y,    KC_W,    KC_P,    KC_J,
        KC_A,    KC_S,    KC_R,    KC_T,    KC_COMMA,        KC_DOT,  KC_E,    KC_I,    KC_O,    KC_N,
        KC_V,    KC_F,    KC_L,    KC_D,    KC_MINS,         KC_QUOT, KC_U,    KC_M,    KC_G,    KC_K,
                     KC_BSPC, LT(MOMENTARY_MOUSE_LAYER, KC_SPC),         LT(MOMENTARY_NUMBER_LAYER, KC_SPC), KC_DEL),
    [NUMBER_LAYER] = LAYOUT_split_3x5_2( // NUMBER: digits, navigation keys, and symbols
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_GRV,  KC_BSLS, KC_SLSH, KC_SCLN, _______,         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        _______, KC_LBRC, KC_RBRC, KC_EQL,  _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                               _______, _______,         LT(MOMENTARY_ALPHA_LAYER, KC_SPC), _______),
    [MOUSE_LAYER] = LAYOUT_split_3x5_2( // MOUSE: Mouse and function keys
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_PSCR, KC_ACL2, KC_ACL1, KC_ACL0, _______,         _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  _______,         _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                                  _______, LT(MOMENTARY_MOUSEALPHA_LAYER, KC_SPC),       KC_BTN1, KC_BTN2),
    [LEFT_NUMBER_LAYER] = LAYOUT_split_3x5_2( // LEFT NUMBER
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,         _______, KC_SCLN, KC_SLSH, KC_BSLS, KC_GRV,
        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______,         _______, KC_EQL,  KC_LBRC, KC_RBRC, _______,
                                               _______, KC_SPC,          KC_SPC,  _______),
    [LEFT_MOUSE_LAYER] = LAYOUT_split_3x5_2( // LEFT MOUSE
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, _______,         _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_PSCR,
        KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, _______,         _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,
                                               KC_BTN2, KC_BTN1,         KC_SPC,  _______),
    [GAME_LAYER] = LAYOUT_split_3x5_2( // GAME: Base sans combos and hold-tap features
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
                                               _______, KC_SPC,          KC_0,    _______),
    [MOMENTARY_ALPHA_LAYER] = LAYOUT_split_3x5_2( // MOMENTARY ALPHA: Accessed from NUMBER
        KC_X,   KC_C,     KC_H,    KC_B,    KC_Q,            KC_Z,    KC_Y,    KC_W,    KC_P,    KC_J,
        KC_A,   KC_S,     KC_R,    KC_T,    _______,         _______, KC_E,    KC_I,    KC_O,    KC_N,
        KC_V,   KC_F,     KC_L,    KC_D,    _______,         _______, KC_U,    KC_M,    KC_G,    KC_K,
                                               _______, KC_SPC,          _______, _______),
    [MOMENTARY_MOUSEALPHA_LAYER] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE ALPHA: accessed from MOUSE
        KC_X,   KC_C,     KC_H,    KC_B,    KC_Q,            KC_Z,    KC_Y,    KC_W,    KC_P,     KC_J,
        KC_A,   KC_S,     KC_R,    KC_T,    _______,         _______, KC_E,    KC_I,    KC_O,     KC_N,
        KC_V,   KC_F,     KC_L,    KC_D,    _______,         _______, KC_U,    KC_M,    KC_G,     KC_K,
                                               _______, _______,         LT(MOMENTARY_NUMBER_LAYER, KC_SPC), KC_DEL),
    [MOMENTARY_NUMBER_LAYER] = LAYOUT_split_3x5_2( // MOMENTARY NUMBER: accessed from ALPHA
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_GRV,  KC_BSLS, KC_SLSH, KC_SCLN, _______,         _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        _______, KC_LBRC, KC_RBRC, KC_EQL,  _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                               _______, KC_SPC,          _______, _______),
    [MOMENTARY_MOUSE_LAYER] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE: accessed from ALPHA
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_PSCR, KC_ACL2, KC_ACL1, KC_ACL0, _______,         _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  _______,         _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                                               _______, _______,         KC_BTN1, KC_BTN2),
};

enum combos {
  /*   |___|   |XXX|   |XXX|   |___|   |___|      |___|   |___|   |XXX|   |XXX|   |___|   */
                    SPACE_COMBO_L,                             TAB_COMBO_R,
                    SHIFT_COMBO_L,                             SHIFT_COMBO_R,
                    CAPS_COMBO_L,                              ALPHA_COMBO_R,
  /*   |XXX|   |___|   |___|   |XXX|   |___|      |___|   |XXX|   |___|   |___|   |XXX|   */
                    ALT_COMBO_L,                               ALT_COMBO_R,
                    CONTROL_COMBO_L,                           CONTROL_COMBO_R,
                    LEFT_MOUSE_COMBO_L,                        MOUSE_COMBO_R,
  /*   |XXX|   |___|   |___|   |___|   |XXX|      |XXX|   |___|   |___|   |___|   |XXX|   */
                    RELEASE_GATE_COMBO_L,                      RELEASE_GATE_COMBO_R,
                    LEFT_NUMBER_COMBO_L,                       NUMBER_COMBO_R,
  /*   |111|   |___|   |___|   |222|   |___|      |___|   |222|   |___|   |___|   |111|   */
                    GUI_COMBO_L,                               GUI_COMBO_R,
  /*   |___|   |___|   |___|   |111|   |222|      |222|   |111|   |___|   |___|   |___|   */
                    ESCAPE_COMBO_L,                            ENTER_COMBO_R,
};

const uint16_t PROGMEM space_combo_l[] = {KC_C,   KC_H,     COMBO_END};
const uint16_t PROGMEM shift_combo_l[] = {KC_S,   KC_R,     COMBO_END};
const uint16_t PROGMEM caps_combo_l[] = {KC_F,   KC_L,     COMBO_END};
const uint16_t PROGMEM alt_combo_l[] = {KC_X,   KC_B,     COMBO_END};
const uint16_t PROGMEM control_combo_l[] = {KC_A,   KC_T,     COMBO_END};
const uint16_t PROGMEM left_mouse_combo_l[] = {KC_V,   KC_D,     COMBO_END};
const uint16_t PROGMEM gui_combo_l[] = {KC_T,   KC_X,     COMBO_END};
const uint16_t PROGMEM escape_combo_l[] = {KC_B,   KC_COMMA, COMBO_END};
const uint16_t PROGMEM release_gate_combo_l[] = {KC_X,   KC_Q,     COMBO_END};
const uint16_t PROGMEM left_number_combo_l[] = {KC_A,   KC_COMM,  COMBO_END};
const uint16_t PROGMEM tab_combo_r[] = {KC_W,   KC_P,     COMBO_END};
const uint16_t PROGMEM shift_combo_r[] = {KC_I,   KC_O,     COMBO_END};
const uint16_t PROGMEM alpha_combo_r[] = {KC_M,   KC_G,     COMBO_END};
const uint16_t PROGMEM alt_combo_r[] = {KC_Y,   KC_J,     COMBO_END};
const uint16_t PROGMEM control_combo_r[] = {KC_E,   KC_N,     COMBO_END};
const uint16_t PROGMEM mouse_combo_r[] = {KC_U,   KC_K,     COMBO_END};
const uint16_t PROGMEM gui_combo_r[] = {KC_E,   KC_J,     COMBO_END};
const uint16_t PROGMEM enter_combo_r[] = {KC_DOT, KC_Y,     COMBO_END};
const uint16_t PROGMEM release_gate_combo_r[] = {KC_Z,   KC_J,     COMBO_END};
const uint16_t PROGMEM number_combo_r[] = {KC_DOT, KC_N,     COMBO_END};

combo_t key_combos[] = {
           //    |___|   |XXX|   |XXX|   |___|   |___|    ------------
           [SPACE_COMBO_L] = COMBO(      space_combo_l, KC_SPACE               ),
           [SHIFT_COMBO_L] = COMBO(      shift_combo_l, KC_LEFT_SHIFT          ),
            [CAPS_COMBO_L] = COMBO(       caps_combo_l, CAPS_ON                ),

           //    |XXX|   |___|   |___|   |XXX|   |___|    ------------
             [ALT_COMBO_L] = COMBO(        alt_combo_l, KC_LEFT_ALT            ),
         [CONTROL_COMBO_L] = COMBO(    control_combo_l, KC_LEFT_CTRL           ),
      [LEFT_MOUSE_COMBO_L] = COMBO( left_mouse_combo_l, TO(LEFT_MOUSE_LAYER)   ),

           //    |XXX|   |___|   |___|   |___|   |XXX|    ------------
    [RELEASE_GATE_COMBO_L] = COMBO(release_gate_combo_l, RELEASE_GATE          ),
     [LEFT_NUMBER_COMBO_L] = COMBO( left_number_combo_l, TO(LEFT_NUMBER_LAYER) ),


           //    |111|   |___|   |___|   |222|   |___|    ------------
             [GUI_COMBO_L] = COMBO(         gui_combo_l, KC_LEFT_GUI           ),


           //    |___|   |___|   |___|   |111|   |222|    -------------
          [ESCAPE_COMBO_L] = COMBO(      escape_combo_l, KC_ESCAPE             ),


           //------------    |___|   |___|   |XXX|   |XXX|   |___|
             [TAB_COMBO_R] = COMBO(        tab_combo_r, KC_TAB                 ),
           [SHIFT_COMBO_R] = COMBO(      shift_combo_r, KC_RIGHT_SHIFT         ),
           [ALPHA_COMBO_R] = COMBO(      alpha_combo_r, ALPHA_ON_CAPS_OFF      ),

           //------------    |___|   |XXX|   |___|   |___|   |XXX|
             [ALT_COMBO_R] = COMBO(        alt_combo_r, KC_RIGHT_ALT           ),
         [CONTROL_COMBO_R] = COMBO(    control_combo_r, KC_RIGHT_CTRL          ),
           [MOUSE_COMBO_R] = COMBO(      mouse_combo_r, TO(MOUSE_LAYER)        ),

           //------------    |XXX|   |___|   |___|   |___|   |XXX|
    [RELEASE_GATE_COMBO_R] = COMBO(release_gate_combo_r, RELEASE_GATE          ),
          [NUMBER_COMBO_R] = COMBO(      number_combo_r, TO(NUMBER_LAYER)      ),


           //------------    |___|   |222|   |___|   |___|   |111|
           [GUI_COMBO_R] = COMBO(         gui_combo_r, KC_RIGHT_GUI            ),


           //------------    |222|   |111|   |___|   |___|   |___|
         [ENTER_COMBO_R] = COMBO(       enter_combo_r, KC_ENTER                ),
};

// Exclude some combos from game layers
bool combo_should_trigger(uint16_t combo_index, combo_t* combo, uint16_t keycode, keyrecord_t* record) {
    if (layer_state_is(GAME_LAYER)) {
        switch (combo_index) {
            case ESCAPE_COMBO_L:
            case ENTER_COMBO_R:
            case SPACE_COMBO_L:
            case LEFT_NUMBER_COMBO_L:
            case LEFT_MOUSE_COMBO_L:
            case ALPHA_COMBO_R:
            case MOUSE_COMBO_R:
            case NUMBER_COMBO_R:
                return true;
            default: return false;
        }
    }
    return true;
}

// Shorten combo term when in game layers
uint16_t get_combo_term(uint16_t index, combo_t* combo) {
    if (layer_state_is(GAME_LAYER))
        return SHORT_COMBO_TERM;
    else
        return COMBO_TERM;
}

// Switching to non-alpha layers breaks capsword
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case ALPHA_LAYER:
            in_momentary_layer = false;
            break;
        case MOUSE_LAYER ... GAME_LAYER:
            in_momentary_layer = false;
            caps_word_off();
            break;
        case MOMENTARY_ALPHA_LAYER ... MOMENTARY_MOUSE_LAYER:
            in_momentary_layer = true;
            break;
        default: break;
    }
    return state;
}

// Space does not break capsword
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LEFT_SHIFT));
            return true;
        // Escape, and modifiers break capsword
        case KC_ESCAPE:
        case KC_LEFT_CTRL:
        case KC_LEFT_ALT:
        case KC_LEFT_GUI:
        case KC_RIGHT_CTRL:
        case KC_RIGHT_ALT:
        case KC_RIGHT_GUI: return false;
        // Everything else lets capsword continue.
        default: return true;
    }
}
// lower risk of accidentally triggering keys in the momentary mouse layer
bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    if (LT(MOMENTARY_MOUSE_LAYER, KC_SPC))
        return true;
    else
        return false;
}
// common symbols like apostrophe can be accessed without breaking flow
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t* record) {
    if (LT(MOMENTARY_NUMBER_LAYER, KC_SPC))
        return true;
    else
        return false;
}
// Handle all the custom keys
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_A ... KC_RGUI:
            if (release_gate.state == NONE)
                return true;
            else if (record->event.pressed)
                return press_key_with_release_gate(keycode);
            else
                return release_key_with_release_gate(keycode);

        case CAPS_ON:
            if (record->event.pressed)
                return press_caps_on();
            else
                return false;

        case ALPHA_ON_CAPS_OFF:
            if (record->event.pressed)
                return press_alpha_on_caps_off();
            else
                return false;

        case RELEASE_GATE:
            if (record->event.pressed)
                return press_release_gate();
            else
                return release_release_gate();

        default: return true;
    }
}
bool press_caps_on() {
    caps_word_on();
    return false;
}
bool press_alpha_on_caps_off() {
    caps_word_off();
    if (!in_momentary_layer)
        layer_move(ALPHA_LAYER);
    return false;
}
bool press_release_gate() {
    release_gate.state = BLOCK;
    return false;
}
bool release_release_gate() {
    if (release_gate.lever == KC_NO)
        release_gate.state = WATCH;
    else
        release_gate.state = LEND;
    return false;
}
bool press_key_with_release_gate(uint16_t keycode) {
    if (release_gate.state == BLOCK) {
        release_gate.lever = keycode;
    }
    else if (release_gate.state == WATCH) {
        release_gate.lever = keycode;
        release_gate.state = SUSPEND;
    }
    return true;
}
bool release_key_with_release_gate(uint16_t keycode) {
    switch (release_gate.state) {
        case BLOCK:
            if (release_gate.size < MAX_BLOCK) {
                release_gate.blocked_keys[release_gate.size] = keycode;
                release_gate.size++;
            }
            if (release_gate.lever == keycode)
                release_gate.lever = KC_NO;
            return false;
        case LEND:
            if (release_gate.size < MAX_BLOCK) {
                release_gate.blocked_keys[release_gate.size] = keycode;
                release_gate.size++;
            }
            if (release_gate.lever == keycode) {
                release_gate.lever = KC_NO;
                release_gate.state = WATCH;
            }
            return false;
        case SUSPEND:
            if (release_gate.lever == keycode) {
                release_gate.lever = KC_NO;
                release_gate.state = NONE;
                for (int i = 0; i < release_gate.size; i++) {
                    unregister_code(release_gate.blocked_keys[i]);
                    release_gate.blocked_keys[i] = KC_NO;
                }
            }
            return true;
        default: return true; // shouldn't get here
    }
}
