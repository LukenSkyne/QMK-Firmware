/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "raw_hid.h"
//#include "print.h"

enum custom_keycodes {
    NX_DOKI = SAFE_RANGE,
    NX_SVLD,
    NX_SVLU,
    NX_SPRV,
    NX_SNXT,
    NX_SPLY,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
//      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          NX_SPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, _______, _______,  _______, _______, _______, _______, _______, _______, _______,                KC_MUTE,
        _______, RGB_TOG, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, QK_BOOT,                _______,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,                         KC_MPRV,
        _______, _______, _______, RGB_SAD, RGB_SAI, _______, NX_DOKI,  _______, _______, _______, _______, _______, _______, _______,                KC_MNXT,
        _______, _______, _______, _______, _______, _______, _______,  NK_TOGG, _______, _______, _______, _______,          _______,    KC_MS_UP,   _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT
    ),

    [2] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(NX_SVLD, NX_SVLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

/*
 * USER SPACE
 */

#define NX_RED 0xFF, 0x22, 0x22

static uint32_t nx_blink_time = 0;
static uint32_t nx_heartbeat_time = 0;

uint16_t get_blink_delta(void) {
    uint32_t current_time = timer_read32();
    uint32_t delta = current_time - nx_blink_time;

    if (delta >= 1000) {
        delta = 0;
        nx_blink_time = current_time;
    }

    if (delta < 500) {
        delta = 500 - delta;
    } else {
        delta -= 500;
    }

    return (uint16_t)delta;
}

void layer_default(uint8_t index, uint16_t keycode) {
    switch (keycode) {
    case KC_CAPS:
    case KC_LSFT:
    case KC_RSFT:
        if (host_keyboard_led_state().caps_lock) {
            uint16_t delta = get_blink_delta() + 100;
            uint8_t v = (0xFF * delta) / 600;
            rgb_matrix_set_color(index, v, v, v);
            break;
        }
    default:
        break;
    }
}

void layer_fn(uint8_t index, uint16_t keycode) {
    if (keycode <= KC_TRNS) {
        return;
    }

    switch (keycode) {
    case QK_BOOT: {
        uint16_t delta = get_blink_delta() + 100;
        uint8_t r = (0xFF * delta) / 600;
        uint8_t gb = (0x22 * delta) / 600;
        rgb_matrix_set_color(index, r, gb, gb);
        break;
    }
    case MO(1):
    case MO(2):
        rgb_matrix_set_color(index, RGB_WHITE);
        break;
    case NK_TOGG:
        if (!keymap_config.nkro) {
            rgb_matrix_set_color(index, NX_RED);
            break;
        }
    default:
        rgb_matrix_set_color(index, RGB_WHITE);
    }
}

/*
 * Overrides
 */

// setup
void keyboard_post_init_user(void) {
    //debug_enable = true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}

// hid receive callback
bool via_command_kb(uint8_t *data, uint8_t length) {
    if (length > 3 && data[0] == 0x42 && data[1] == 0x42 && data[2] == 0x42 && data[3] == 0x42) {
        nx_heartbeat_time = timer_read32();
        #ifdef CONSOLE_ENABLE
        printf("received heartbeat: %lu\n", nx_heartbeat_time);
        #endif

        return true;
    }

    return false;
}

// hotkey callback
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif

    uint32_t heartbeat_delta = timer_read32() - nx_heartbeat_time;

    if (keycode >= NX_SVLD && keycode <= NX_SPLY && heartbeat_delta < 20000) {
        if (!record->event.pressed) {
            return true;
        }

        uint8_t data[32] = { 0 };
        data[0] = 0x42;
        data[1] = 0x42;
        data[2] = 0x42;
        data[3] = 0x42;
        data[4] = keycode - NX_SVLD + 1;
        raw_hid_send(data, sizeof(data));

        return true;
    }

    switch (keycode) {
    case NX_DOKI: {
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_P3) SS_UP(X_P3) SS_UP(X_LALT));
        }
    } break;
    case NX_SPRV: {
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_MPRV));
        }
    } break;
    case NX_SNXT: {
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_MNXT));
        }
    } break;
    case NX_SPLY: {
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_MPLY));
        }
    } break;
    }

    return true;
}

// rgb adjustment
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    static uint8_t layer_prev = 0;
    static uint8_t v_prev = 255;

    // decrease brightness (value) by half when a layer is active
    if (layer_prev != layer) {
        #ifdef CONSOLE_ENABLE
        dprintf("Layer: %u", layer);
        #endif

        if (layer_prev == 0) {
            v_prev = rgb_matrix_config.hsv.v;
        }

        if (layer < 2) {
            rgb_matrix_config.hsv.v = v_prev;
        } else if (layer == 2) {
            rgb_matrix_config.hsv.v = 0;
            nx_blink_time = timer_read32();
        }

        layer_prev = layer;
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED) {
                uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});

                if (layer == 0) {
                    layer_default(index, keycode);
                } else {
                    layer_fn(index, keycode);
                }
            }
        }
    }

    return false;
}
