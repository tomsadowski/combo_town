// tomsadowski
// keymap for ferris sweep

#include QMK_KEYBOARD_H
#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include "quantum_keycodes.h"

// DATA: MOD-BUILDER

#define MAX_MBQ 8

enum my_keycodes {MBQ = SAFE_RANGE};
typedef struct   {bool registered;
                  bool terminal;
                  bool active;
                  unsigned short last_size;
                  unsigned short size;
                  uint16_t queue[MAX_MBQ];
                 } mod_builder_queue;
static mod_builder_queue mbq = {false, false, false, 0, 0, {0}};

// DATA: TAPDANCE

enum td_keycodes {NMBR_CW};
typedef enum {UNKNOWN, SINGLE_TAP, SINGLE_HLD, DOUBLE_TAP} td_state_t;
static td_state_t td_nmb_cw_state = UNKNOWN; // MO_NMB_LAYER when held, CAPSWORD when tapped
void td_nmb_cw_finished (tap_dance_state_t*, void*);
void td_nmb_cw_reset (tap_dance_state_t*, void*);
td_state_t td_get_state (tap_dance_state_t*);
tap_dance_action_t tap_dance_actions[] = {
    [NMBR_CW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_nmb_cw_finished, td_nmb_cw_reset),
};

// DATA: LAYERS

enum layers {ALPHA_LAYER, GM2D_LAYER, G3D1_LAYER, G3D2_LAYER, NMBR_LAYER, MOUS_LAYER,
             MO_ALP_LYR, MO_MAL_LYR, MO_NMB_LYR, MO_MSE_LYR};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ALPHA_LAYER] = LAYOUT_split_3x5_2( // ALPHA: Alphabet, punctuation, editing
        KC_X,    KC_C,    KC_H,    KC_B,    KC_Q,        KC_Z,    KC_Y,    KC_W,    KC_P,    KC_J,
        KC_A,    KC_S,    KC_R,    KC_T,    KC_COMMA,    KC_DOT,  KC_E,    KC_I,    KC_O,    KC_N,
        KC_V,    KC_F,    KC_L,    KC_D,    KC_MINS,     KC_EQL,  KC_U,    KC_M,    KC_G,    KC_K,
                 KC_BSPC, LT(MO_MSE_LYR, KC_SPC),        TD(NMBR_CW), KC_DEL),
    [GM2D_LAYER] = LAYOUT_split_3x5_2( // GAME 2D: Base sans hold-tap features
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
                                   _______, KC_SPC,      KC_0,    _______),
    [G3D1_LAYER] = LAYOUT_split_3x5_2( // GAME 3D: Game 2d but with mouse
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        _______, _______, _______, _______, _______,     _______, _______, KC_WH_D, KC_WH_U, _______,
                                   _______, KC_SPC,      KC_BTN1, KC_BTN2),
    [G3D2_LAYER] = LAYOUT_split_3x5_2( // GAME 3D: Game 2d but with an augmented mouse layout
        _______, _______, _______, _______, _______,     _______, _______, KC_MS_U, _______, _______,
        _______, _______, _______, _______, _______,     _______, KC_MS_L, KC_MS_D, _______, KC_MS_R,
        _______, _______, _______, _______, _______,     _______, _______, KC_WH_D, KC_WH_U, _______,
                                   _______, KC_SPC,      KC_BTN1, KC_BTN2),
    [NMBR_LAYER] = LAYOUT_split_3x5_2( // NUMBER: digits, navigation keys, and all symbols not covered by combos and base
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LBRC, KC_RBRC, KC_BSLS, KC_SLSH, _______,     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
        _______, _______, _______, KC_GRV,  _______,     _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                   _______, _______,     MO(MO_ALP_LYR), _______),
    [MOUS_LAYER] = LAYOUT_split_3x5_2( // MOUSE: Mouse and function keys
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_ACL1, KC_ACL0, _______,     _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        _______, _______, _______, KC_ACL2, _______,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                 _______, LT(MO_MAL_LYR, KC_SPC),        KC_BTN1, KC_BTN2),
    [MO_ALP_LYR] = LAYOUT_split_3x5_2( // MOMENTARY ALPHA: Accessed from NUMBER
        KC_X,   KC_C,     KC_H,    KC_B,    KC_Q,        KC_Z,    KC_Y,    KC_W,    KC_P,    KC_J,
        KC_A,   KC_S,     KC_R,    KC_T,    _______,     _______, KC_E,    KC_I,    KC_O,    KC_N,
        KC_V,   KC_F,     KC_L,    KC_D,    _______,     _______, KC_U,    KC_M,    KC_G,    KC_K,
                                   _______, KC_SPC,      _______, _______),
    [MO_MAL_LYR] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE ALPHA: accessed from MOUSE
        KC_X,   KC_C,     KC_H,    KC_B,    KC_Q,        KC_Z,    KC_Y,    KC_W,    KC_P,     KC_J,
        KC_A,   KC_S,     KC_R,    KC_T,    _______,     _______, KC_E,    KC_I,    KC_O,     KC_N,
        KC_V,   KC_F,     KC_L,    KC_D,    _______,     _______, KC_U,    KC_M,    KC_G,     KC_K,
                                   _______, _______,     TD(NMBR_CW), KC_DEL),
    [MO_NMB_LYR] = LAYOUT_split_3x5_2( // MOMENTARY NUMBER: accessed from ALPHA and MOMENTARY MOUSE ALPHA
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LBRC, KC_RBRC, KC_BSLS, KC_SLSH, _______,     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
        _______, _______, _______, KC_GRV,  _______,     _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                   _______, KC_SPC,      _______, _______),
    [MO_MSE_LYR] = LAYOUT_split_3x5_2( // MOMENTARY MOUSE: accessed from ALPHA
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_ACL1, KC_ACL0, _______,     _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
        _______, _______, _______, KC_ACL2, _______,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
                                   _______, _______,     KC_BTN1, KC_BTN2),
};

// DATA: COMBO NAMES

enum combos {
  /*   |___|   |XXX|   |XXX|   |___|   |___|      |___|   |___|   |XXX|   |XXX|   |___|   */
                    SPC_COMBO_L,                               TAB_COMBO_R,
                    SFT_COMBO_L,                               SFT_COMBO_R,
                    G2D_COMBO_L,                               ALP_COMBO_R,
  /*   |XXX|   |___|   |___|   |XXX|   |___|      |___|   |XXX|   |___|   |___|   |XXX|   */
                    ALT_COMBO_L,                               ALT_COMBO_R,
                    CTL_COMBO_L,                               CTL_COMBO_R,
                    G31_COMBO_L,                               MSE_COMBO_R,
  /*   |___|   |___|   |___|   |XXX|   |XXX|      |XXX|   |XXX|   |___|   |___|   |___|   */
                    PSC_COMBO_L,                               PSC_COMBO_R,
                    ESC_COMBO_L,                               ENT_COMBO_R,
                    GUI_COMBO_L,                               GUI_COMBO_R,
  /*   |XXX|   |___|   |___|   |___|   |XXX|      |XXX|   |___|   |___|   |___|   |XXX|   */
                    MBQ_COMBO_L,                               MBQ_COMBO_R,
                    QTE_COMBO_L,                               SCL_COMBO_R,
                    G32_COMBO_L,                               NMB_COMBO_R,
};

// DATA: COMBO KEYS
//                                          L:  -  X  X  -  -
const uint16_t PROGMEM spc_combo_l[] = {KC_C,   KC_H,     COMBO_END};
const uint16_t PROGMEM sft_combo_l[] = {KC_S,   KC_R,     COMBO_END};
const uint16_t PROGMEM g2d_combo_l[] = {KC_F,   KC_L,     COMBO_END};
//                                          L:  X  -  -  X  -
const uint16_t PROGMEM alt_combo_l[] = {KC_X,   KC_B,     COMBO_END};
const uint16_t PROGMEM ctl_combo_l[] = {KC_A,   KC_T,     COMBO_END};
const uint16_t PROGMEM g31_combo_l[] = {KC_V,   KC_D,     COMBO_END};
//                                          L:  -  -  -  X  X
const uint16_t PROGMEM psc_combo_l[] = {KC_B,   KC_Q,     COMBO_END};
const uint16_t PROGMEM esc_combo_l[] = {KC_T,   KC_COMMA, COMBO_END};
const uint16_t PROGMEM gui_combo_l[] = {KC_D,   KC_MINS,  COMBO_END};
//                                          L:  X  -  -  -  X
const uint16_t PROGMEM mbq_combo_l[] = {KC_X,   KC_Q,     COMBO_END};
const uint16_t PROGMEM qte_combo_l[] = {KC_A,   KC_COMMA, COMBO_END};
const uint16_t PROGMEM g32_combo_l[] = {KC_V,   KC_MINS,  COMBO_END};
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
const uint16_t PROGMEM mbq_combo_r[] = {KC_Z,   KC_J,     COMBO_END};
const uint16_t PROGMEM scl_combo_r[] = {KC_DOT, KC_N,     COMBO_END};
const uint16_t PROGMEM nmb_combo_r[] = {KC_EQL, KC_K,     COMBO_END};

// DATA: COMBO ASSIGNMENTS

combo_t key_combos[] = {
  /*   |___|   |XXX|   |XXX|   |___|   |___|               |___|   |___|   |XXX|   |XXX|   |___|   */
  [SPC_COMBO_L] = COMBO(spc_combo_l, KC_SPC),          [TAB_COMBO_R] = COMBO(tab_combo_r, KC_TAB),
  [SFT_COMBO_L] = COMBO(sft_combo_l, KC_LSFT),         [SFT_COMBO_R] = COMBO(sft_combo_r, KC_RSFT),
  [G2D_COMBO_L] = COMBO(g2d_combo_l, TO(GM2D_LAYER)),  [ALP_COMBO_R] = COMBO(alp_combo_r, TO(ALPHA_LAYER)),
  /*   |XXX|   |___|   |___|   |XXX|   |___|               |___|   |XXX|   |___|   |___|   |XXX|   */
  [ALT_COMBO_L] = COMBO(alt_combo_l, KC_LALT),         [ALT_COMBO_R] = COMBO(alt_combo_r, KC_RALT),
  [CTL_COMBO_L] = COMBO(ctl_combo_l, KC_LCTL),         [CTL_COMBO_R] = COMBO(ctl_combo_r, KC_RCTL),
  [G31_COMBO_L] = COMBO(g31_combo_l, TO(G3D1_LAYER)),  [MSE_COMBO_R] = COMBO(mse_combo_r, TO(MOUS_LAYER)),
  /*   |___|   |___|   |___|   |XXX|   |XXX|               |XXX|   |XXX|   |___|   |___|   |___|   */
  [PSC_COMBO_L] = COMBO(psc_combo_l, KC_PSCR),         [PSC_COMBO_R] = COMBO(psc_combo_r, KC_PSCR),
  [ESC_COMBO_L] = COMBO(esc_combo_l, KC_ESC),          [ENT_COMBO_R] = COMBO(ent_combo_r, KC_ENT),
  [GUI_COMBO_L] = COMBO(gui_combo_l, KC_LGUI),         [GUI_COMBO_R] = COMBO(gui_combo_r, KC_RGUI),
  /*   |XXX|   |___|   |___|   |___|   |XXX|               |XXX|   |___|   |___|   |___|   |XXX|   */
  [MBQ_COMBO_L] = COMBO(mbq_combo_l, MBQ),             [MBQ_COMBO_R] = COMBO(mbq_combo_r, MBQ),
  [QTE_COMBO_L] = COMBO(qte_combo_l, KC_QUOTE),        [SCL_COMBO_R] = COMBO(scl_combo_r, KC_SCLN),
  [G32_COMBO_L] = COMBO(g32_combo_l, TO(G3D2_LAYER)),  [NMB_COMBO_R] = COMBO(nmb_combo_r, TO(NMBR_LAYER)),
};

// FUNCTION: COMBO
// Permit a subset of combos while in game layers
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(GM2D_LAYER)) {
        if (combo_index != ESC_COMBO_L &&
            combo_index != G31_COMBO_L &&
            combo_index != G32_COMBO_L &&
            combo_index != MSE_COMBO_R &&
            combo_index != NMB_COMBO_R &&
            combo_index != ALP_COMBO_R &&
            combo_index != TAB_COMBO_R &&
            combo_index != ENT_COMBO_R)
            return false;
    }
    else if (layer_state_is(G3D1_LAYER)) {
        if (combo_index != ESC_COMBO_L &&
            combo_index != G2D_COMBO_L &&
            combo_index != G32_COMBO_L &&
            combo_index != SFT_COMBO_R &&
            combo_index != CTL_COMBO_R &&
            combo_index != MSE_COMBO_R &&
            combo_index != NMB_COMBO_R &&
            combo_index != ALP_COMBO_R &&
            combo_index != ENT_COMBO_R)
            return false;
    }
    else if (layer_state_is(G3D2_LAYER)) {
        if (combo_index != ESC_COMBO_L &&
            combo_index != G2D_COMBO_L &&
            combo_index != G31_COMBO_L &&
            combo_index != CTL_COMBO_R &&
            combo_index != MSE_COMBO_R &&
            combo_index != NMB_COMBO_R &&
            combo_index != ALP_COMBO_R &&
            combo_index != ENT_COMBO_R)
            return false;
    }
    return true;
}

// FUNCTION: CAPSWORD
// Space does not break capsword
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Only letters are affected by capsword.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        // Escape and modifiers break capsword
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
// Switching to MOUS_LAYER or NMBR_LAYER breaks capsword
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case MOUS_LAYER:
        if (is_caps_word_on()) caps_word_off(); break;
    case NMBR_LAYER:
        if (is_caps_word_on()) caps_word_off(); break;
    default:
        break;
    }
  return state;
}

// FUNCTION: TAPDANCE
// Return tapdance state as an enum value
td_state_t td_get_state(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return SINGLE_TAP;
        else return SINGLE_HLD;
    }
    if (state->count == 2)
        return DOUBLE_TAP;
    else return UNKNOWN;
}
// Sets keyboard state from MO_NMBR_LAYER/CAPSWORD tapdance state
void td_nmb_cw_finished(tap_dance_state_t *state, void *user_data) {
    td_nmb_cw_state = td_get_state(state);
    switch (td_nmb_cw_state) {
        case SINGLE_TAP:
            if (is_caps_word_on()) caps_word_off(); break;
        case SINGLE_HLD:
            layer_on(MO_NMB_LYR); break;
        case DOUBLE_TAP:
            if (!is_caps_word_on()) caps_word_on(); break;
        default: break;
    }
}
// Resets keyboard state for MO_NMBR_LAYER/CAPSWORD tapdance
void td_nmb_cw_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_nmb_cw_state) {
        case SINGLE_TAP: break;
        case SINGLE_HLD:
            layer_off(MO_NMB_LYR); break;
        case DOUBLE_TAP: break;
        default: break;
    }
}

// FUNCTION: MOD-BUILDER
// Updates mbq state. State of mbq alters default keycode processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MBQ:
            // Ignore this key when registered
            if (mbq.registered) return false;

            // DEDUCTION: Queue not registered

            // Open the queue when pressed
            if (record->event.pressed) {
                mbq.terminal = false;
                mbq.active = true;
                mbq.last_size = mbq.size;
            }
            // Assume terminal state when released
            else {
                mbq.terminal = true;
                // Close queue if nothing added since last pressed
                if (mbq.last_size == mbq.size) {
                    mbq.active = false;
                    mbq.size = mbq.last_size = 0;
                    memset(mbq.queue, 0, sizeof(mbq.queue));
                }
            }
            return false;
        case KC_A ... KC_RGUI:
            // Process key normally when queue not active
            if (!mbq.active) return true;

            // DEDUCTION: Queue is active

            // Process key normally when key pressed and queue registered
            if (mbq.registered && record->event.pressed) return true;
            // Do nothing when queue not registered and key released
            if (!mbq.registered && !record->event.pressed) return false;

            // DEDUCTION: Queue is registered xor key pressed and queue active

            // Unregister queue when registered and key released
            if (mbq.registered) {
                for (unsigned short i = 0; i < mbq.size; i++)
                    unregister_code(mbq.queue[i]);
                mbq.active = false;
                mbq.registered = false;
                mbq.size = mbq.last_size = 0;
                memset(mbq.queue, 0, sizeof(mbq.queue));
                return true;
            }

            // DEDUCTION: Key pressed and queue active but not registered

            // See if keycode is in queue
            bool in_queue = false;
            for (unsigned short i = 0; i < mbq.size; i++)
                if (mbq.queue[i] == keycode) {
                    in_queue = true;
                    break;
                }
            // Do nothing when key is nonterminal and in queue
            if (!mbq.terminal && in_queue) return false;

            // DEDUCTION: Key nonterminal and not in queue, or key terminal

            // Add key to queue
            if (!mbq.terminal || !in_queue) {
                mbq.queue[mbq.size] = keycode;
                mbq.size += 1;
            }
            // Register queue
            if (mbq.terminal || mbq.size == MAX_MBQ) {
                mbq.registered = true;
                for (unsigned short i = 0; i < mbq.size; i++)
                    register_code(mbq.queue[i]);
            }
            return false;
        default: return true;
    }
}
