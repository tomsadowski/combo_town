#pragma once

#undef  LOCKING_SUPPORT_ENABLE
#undef  LOCKING_RESYNC_ENABLE

#define NO_ACTION_ONESHOT

// Layery
#define LAYER_STATE_16BIT
// Mousery
#define MK_COMBINED
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_MOVE_DELTA 7
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 8
#define MOUSEKEY_TIME_TO_MAX 48
// Mousewheelery
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_MOVE_DELTA 1
#define MOUSEKEY_WHEEL_INTERVAL 64
#define MOUSEKEY_WHEEL_MAX_SPEED 42
#define MOUSEKEY_WHEEL_TIME_TO_MAX 128
// Splittery
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500
// Combory
#define EXTRA_SHORT_COMBOS
#define COMBO_SHOULD_TRIGGER
#define COMBO_TERM_PER_COMBO
#define COMBO_STRICT_TIMER
#define COMBO_TERM 31
#define COMBO_ONLY_FROM_LAYER 0
// Capswordery
#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 0
// Tappery
#define PERMISSIVE_HOLD
#define TAPPING_TERM 250
