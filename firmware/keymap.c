/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

// ---------------------------------------------------------------------------
// Capas
// ---------------------------------------------------------------------------
enum layers {
    _BASE = 0,  // QWERTY
    _NAV,       // 1 - navegacion / flechas
    _SYM,       // 2 - simbolos
    _NUM,       // 3 - numpad + media
    _ADJUST     // 4 - RGB / F-keys / boot (tri-layer SYM+NUM)
};

// ---------------------------------------------------------------------------
// Aliases (contenido base tomado de renzoqc/renzodev-corne-keyboard)
// ---------------------------------------------------------------------------
#define CMD_C      LGUI(KC_C)                     // Cmd + C
#define CMD_V      LGUI(KC_V)                     // Cmd + V
#define ALT_SHIFT  MT(MOD_LALT | MOD_LSFT, KC_NO) // Alt + Shift
#define CTRL_SHFT  MT(MOD_LCTL | MOD_LSFT, KC_NO) // Ctrl + Shift

// Pulgares del usuario. Orden del macro LAYOUT_split_3x6_3:
//   [ Lout, Lmid, Lin,  Rin,  Rmid, Rout ]
#define TH_LOUT    KC_LALT          // Opt (izq. externo)
#define TH_LMID    KC_LGUI          // Cmd (izq. medio)
#define TH_LIN     LT(_SYM, KC_SPC) // tap Espacio / hold SYM
#define TH_RIN     MO(_NAV)         // acceso a NAV
#define TH_RMID    KC_LCTL          // Ctrl
#define TH_ROUT    LT(_NUM, KC_ENT) // tap Enter / hold NUM

// NOTA: los simbolos de SYM/NUM estan en posiciones US/ANSI. El usuario los
// afinara en vivo en Vial bajo su layout LatinoPer (Latinoamerica). La Mac
// traduce los codigos US a espanol; por eso KC_SCLN produce la "n" (enie).

// ---------------------------------------------------------------------------
// Keymaps
// ---------------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // BASE (QWERTY) -----------------------------------------------------------
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   OSM(MOD_LALT),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, RALT_T(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   OSM(MOD_LSFT),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   TH_LOUT, TH_LMID, TH_LIN,    TH_RIN, TH_RMID, TH_ROUT
                                      //`--------------------------'  `--------------------------'
  ),

  // NAV ---------------------------------------------------------------------
  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX, XXXXXXX,   CMD_C,   CMD_V, XXXXXXX,                      XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_LSFT, KC_LALT, KC_LGUI, KC_LCTL, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, ALT_SHIFT,CTRL_SHFT,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   _______, _______, _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // SYM ---------------------------------------------------------------------
  [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_AT, KC_EXLM, KC_LPRN, KC_RPRN, KC_PERC,                       KC_EQL, KC_PLUS, KC_ASTR, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_LSFT, KC_LALT, KC_LCBR, KC_RCBR, KC_MINS,                      KC_EXLM, KC_HASH, KC_SLSH, KC_BSLS, KC_PIPE,  KC_DLR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_UNDS,                      KC_COLN,  KC_GRV, KC_CIRC,   KC_AT, KC_AMPR, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   _______, _______, _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // NUM (numpad + media) ----------------------------------------------------
  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,                      KC_PPLS,    KC_1,    KC_2,    KC_3, KC_MINS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_LSFT, KC_LALT, KC_MPRV, KC_MPLY, KC_MNXT,                      KC_PAST,    KC_4,    KC_5,    KC_6, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU,                         KC_0,    KC_7,    KC_8,    KC_9, KC_PERC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   _______, _______, _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // ADJUST (RGB / F-keys / boot) -- tri-layer SYM+NUM -----------------------
  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      XXXXXXX,   KC_F4,   KC_F5,   KC_F6, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX,   KC_F7,   KC_F8,   KC_F9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   _______, _______, _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

// ---------------------------------------------------------------------------
// Tri-layer: mantener SYM(2) + NUM(3) -> ADJUST(4)
// ---------------------------------------------------------------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NUM, _ADJUST);
}

// ---------------------------------------------------------------------------
// OLED
// ---------------------------------------------------------------------------
#ifdef OLED_ENABLE
#include <stdio.h>
#include "boost_logo.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // slave: invierte 180 (orientacion de la base)
    }
    return rotation;               // master: rotacion vertical por defecto del crkbd
}

// Tabla keycode -> caracter. Indice = keycode (HID). KC_SCLN (0x33) -> 'N'
// para representar la enie del layout LatinoPer.
static const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'E', 'E', 'B', 'T', ' ', '-', '=', '[', ']', '\\',
    '#', 'N', '\'', '`', ',', '.', '/', ' ', ' ', ' '};
//                ^ indice 51 = KC_SCLN -> 'N' (enie)

static char last_key_char = ' ';

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    // Enmascarar mod-tap / layer-tap para quedarnos con el keycode base.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }
    if (keycode < 60) {
        last_key_char = code_to_name[keycode];
    } else {
        last_key_char = ' ';
    }
}

// Nombre de capa (max 5 chars utiles por el ancho del OLED vertical).
static const char *layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:   return "BASE ";
        case _NAV:    return "NAV  ";
        case _SYM:    return "SYM  ";
        case _NUM:    return "NUM  ";
        case _ADJUST: return "ADJ  ";  // "ADJUST" no entra en 5 cols
        default:      return "???  ";
    }
}

// OLED del crkbd = landscape 128x32 = 21 columnas x 4 filas.
static void render_master(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    char buf[22];

    // Fila 0: capa actual
    oled_set_cursor(0, 0);
    snprintf(buf, sizeof(buf), "Capa: %s", layer_name());
    oled_write(buf, false);

    // Fila 1: ultima tecla (como letra) + WPM
    oled_set_cursor(0, 1);
    snprintf(buf, sizeof(buf), "Tecla:%c   WPM:%u", last_key_char, get_current_wpm());
    oled_write(buf, false);

    // Fila 2: modificadores activos (S C A G)
    oled_set_cursor(0, 2);
    snprintf(buf, sizeof(buf), "Mods: %c %c %c %c",
             (mods & MOD_MASK_SHIFT) ? 'S' : '-',
             (mods & MOD_MASK_CTRL)  ? 'C' : '-',
             (mods & MOD_MASK_ALT)   ? 'A' : '-',
             (mods & MOD_MASK_GUI)   ? 'G' : '-');
    oled_write(buf, false);

    // Fila 3: firma
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("kchipanach"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master();
    } else {
        // Slave: logo "boost" en orientacion nativa del panel.
        // oled_write_raw_P ignora la rotacion de texto (escribe el framebuffer
        // crudo). Si en hardware se ve rotado, regenerar boost_logo.h con el
        // PNG rotado 90/180 (ver gen_logo.py en el scratchpad).
        oled_write_raw_P(boost_logo, sizeof(boost_logo));
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}
#endif // OLED_ENABLE
