multiline_comment|/*&n; *  Copyright (C) 2004 by Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&n; */
multiline_comment|/*&n; * LK keyboard driver for Linux, based on sunkbd.c (C) by Vojtech Pavlik&n; */
multiline_comment|/*&n; * DEC LK201 and LK401 keyboard driver for Linux (primary for DECstations&n; * and VAXstations, but can also be used on any standard RS232 with an&n; * adaptor).&n; *&n; * DISCLAIMER: This works for _me_. If you break anything by using the&n; * information given below, I will _not_ be liable!&n; *&n; * RJ11 pinout:&t;&t;To DE9:&t;&t;Or DB25:&n; * &t;1 - RxD &lt;----&gt;&t;Pin 3 (TxD) &lt;-&gt;&t;Pin 2 (TxD)&n; * &t;2 - GND &lt;----&gt;&t;Pin 5 (GND) &lt;-&gt;&t;Pin 7 (GND)&n; * &t;4 - TxD &lt;----&gt;&t;Pin 2 (RxD) &lt;-&gt;&t;Pin 3 (RxD)&n; * &t;3 - +12V (from HDD drive connector), DON&squot;T connect to DE9 or DB25!!!&n; *&n; * Pin numbers for DE9 and DB25 are noted on the plug (quite small:). For&n; * RJ11, it&squot;s like this:&n; *&n; *      __=__&t;Hold the plug in front of you, cable downwards,&n; *     /___/|&t;nose is hidden behind the plug. Now, pin 1 is at&n; *    |1234||&t;the left side, pin 4 at the right and 2 and 3 are&n; *    |IIII||&t;in between, of course:)&n; *    |    ||&n; *    |____|/&n; *      ||&t;So the adaptor consists of three connected cables&n; *      ||&t;for data transmission (RxD and TxD) and signal ground.&n; *&t;&t;Additionally, you have to get +12V from somewhere.&n; * Most easily, you&squot;ll get that from a floppy or HDD power connector.&n; * It&squot;s the yellow cable there (black is ground and red is +5V).&n; *&n; * The keyboard and all the commands it understands are documented in&n; * &quot;VCB02 Video Subsystem - Technical Manual&quot;, EK-104AA-TM-001. This&n; * document is LK201 specific, but LK401 is mostly compatible. It comes&n; * up in LK201 mode and doesn&squot;t report any of the additional keys it&n; * has. These need to be switched on with the LK_CMD_ENABLE_LK401&n; * command. You&squot;ll find this document (scanned .pdf file) on MANX,&n; * a search engine specific to DEC documentation. Try&n; * http://www.vt100.net/manx/details?pn=EK-104AA-TM-001;id=21;cp=1&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * email or by paper mail:&n; * Jan-Benedict Glaw, Lilienstra&#xfffd;e 16, 33790 H&#xfffd;rste (near Halle/Westf.),&n; * Germany.&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;LK keyboard driver&quot;
id|MODULE_AUTHOR
(paren
l_string|&quot;Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&quot;
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Known parameters:&n; *&t;bell_volume&n; *&t;keyclick_volume&n; *&t;ctrlclick_volume&n; *&n; * Please notice that there&squot;s not yet an API to set these at runtime.&n; */
DECL|variable|bell_volume
r_static
r_int
id|bell_volume
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* % */
id|module_param
(paren
id|bell_volume
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|bell_volume
comma
l_string|&quot;Bell volume (in %). default is 100%&quot;
)paren
suffix:semicolon
DECL|variable|keyclick_volume
r_static
r_int
id|keyclick_volume
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* % */
id|module_param
(paren
id|keyclick_volume
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|keyclick_volume
comma
l_string|&quot;Keyclick volume (in %), default is 100%&quot;
)paren
suffix:semicolon
DECL|variable|ctrlclick_volume
r_static
r_int
id|ctrlclick_volume
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* % */
id|module_param
(paren
id|ctrlclick_volume
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|ctrlclick_volume
comma
l_string|&quot;Ctrlclick volume (in %), default is 100%&quot;
)paren
suffix:semicolon
DECL|variable|lk201_compose_is_alt
r_static
r_int
id|lk201_compose_is_alt
op_assign
l_int|0
suffix:semicolon
id|module_param
(paren
id|lk201_compose_is_alt
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|lk201_compose_is_alt
comma
l_string|&quot;If set non-zero, LK201&squot; Compose key &quot;
l_string|&quot;will act as an Alt key&quot;
)paren
suffix:semicolon
DECL|macro|LKKBD_DEBUG
macro_line|#undef LKKBD_DEBUG
macro_line|#ifdef LKKBD_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk (x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...) do {} while (0)
macro_line|#endif
multiline_comment|/* LED control */
DECL|macro|LK_LED_WAIT
mdefine_line|#define LK_LED_WAIT&t;&t;0x81
DECL|macro|LK_LED_COMPOSE
mdefine_line|#define LK_LED_COMPOSE&t;&t;0x82
DECL|macro|LK_LED_SHIFTLOCK
mdefine_line|#define LK_LED_SHIFTLOCK&t;0x84
DECL|macro|LK_LED_SCROLLLOCK
mdefine_line|#define LK_LED_SCROLLLOCK&t;0x88
DECL|macro|LK_CMD_LED_ON
mdefine_line|#define LK_CMD_LED_ON&t;&t;0x13
DECL|macro|LK_CMD_LED_OFF
mdefine_line|#define LK_CMD_LED_OFF&t;&t;0x11
multiline_comment|/* Mode control */
DECL|macro|LK_MODE_DOWN
mdefine_line|#define LK_MODE_DOWN&t;&t;0x80
DECL|macro|LK_MODE_AUTODOWN
mdefine_line|#define LK_MODE_AUTODOWN&t;0x82
DECL|macro|LK_MODE_UPDOWN
mdefine_line|#define LK_MODE_UPDOWN&t;&t;0x86
DECL|macro|LK_CMD_SET_MODE
mdefine_line|#define LK_CMD_SET_MODE(mode,div)&t;((mode) | ((div) &lt;&lt; 3))
multiline_comment|/* Misc commands */
DECL|macro|LK_CMD_ENABLE_KEYCLICK
mdefine_line|#define LK_CMD_ENABLE_KEYCLICK&t;0x1b
DECL|macro|LK_CMD_DISABLE_KEYCLICK
mdefine_line|#define LK_CMD_DISABLE_KEYCLICK&t;0x99
DECL|macro|LK_CMD_DISABLE_BELL
mdefine_line|#define LK_CMD_DISABLE_BELL&t;0xa1
DECL|macro|LK_CMD_SOUND_BELL
mdefine_line|#define LK_CMD_SOUND_BELL&t;0xa7
DECL|macro|LK_CMD_ENABLE_BELL
mdefine_line|#define LK_CMD_ENABLE_BELL&t;0x23
DECL|macro|LK_CMD_DISABLE_CTRCLICK
mdefine_line|#define LK_CMD_DISABLE_CTRCLICK&t;0xb9
DECL|macro|LK_CMD_ENABLE_CTRCLICK
mdefine_line|#define LK_CMD_ENABLE_CTRCLICK&t;0xbb
DECL|macro|LK_CMD_SET_DEFAULTS
mdefine_line|#define LK_CMD_SET_DEFAULTS&t;0xd3
DECL|macro|LK_CMD_POWERCYCLE_RESET
mdefine_line|#define LK_CMD_POWERCYCLE_RESET&t;0xfd
DECL|macro|LK_CMD_ENABLE_LK401
mdefine_line|#define LK_CMD_ENABLE_LK401&t;0xe9
DECL|macro|LK_CMD_REQUEST_ID
mdefine_line|#define LK_CMD_REQUEST_ID&t;0xab
multiline_comment|/* Misc responses from keyboard */
DECL|macro|LK_STUCK_KEY
mdefine_line|#define LK_STUCK_KEY&t;&t;0x3d
DECL|macro|LK_SELFTEST_FAILED
mdefine_line|#define LK_SELFTEST_FAILED&t;0x3e
DECL|macro|LK_ALL_KEYS_UP
mdefine_line|#define LK_ALL_KEYS_UP&t;&t;0xb3
DECL|macro|LK_METRONOME
mdefine_line|#define LK_METRONOME&t;&t;0xb4
DECL|macro|LK_OUTPUT_ERROR
mdefine_line|#define LK_OUTPUT_ERROR&t;&t;0xb5
DECL|macro|LK_INPUT_ERROR
mdefine_line|#define LK_INPUT_ERROR&t;&t;0xb6
DECL|macro|LK_KBD_LOCKED
mdefine_line|#define LK_KBD_LOCKED&t;&t;0xb7
DECL|macro|LK_KBD_TEST_MODE_ACK
mdefine_line|#define LK_KBD_TEST_MODE_ACK&t;0xb8
DECL|macro|LK_PREFIX_KEY_DOWN
mdefine_line|#define LK_PREFIX_KEY_DOWN&t;0xb9
DECL|macro|LK_MODE_CHANGE_ACK
mdefine_line|#define LK_MODE_CHANGE_ACK&t;0xba
DECL|macro|LK_RESPONSE_RESERVED
mdefine_line|#define LK_RESPONSE_RESERVED&t;0xbb
DECL|macro|LK_NUM_KEYCODES
mdefine_line|#define LK_NUM_KEYCODES&t;&t;256
DECL|macro|LK_NUM_IGNORE_BYTES
mdefine_line|#define LK_NUM_IGNORE_BYTES&t;6
DECL|typedef|lk_keycode_t
r_typedef
id|u_int16_t
id|lk_keycode_t
suffix:semicolon
DECL|variable|lkkbd_keycode
r_static
id|lk_keycode_t
id|lkkbd_keycode
(braket
id|LK_NUM_KEYCODES
)braket
op_assign
(brace
(braket
l_int|0x56
)braket
op_assign
id|KEY_F1
comma
(braket
l_int|0x57
)braket
op_assign
id|KEY_F2
comma
(braket
l_int|0x58
)braket
op_assign
id|KEY_F3
comma
(braket
l_int|0x59
)braket
op_assign
id|KEY_F4
comma
(braket
l_int|0x5a
)braket
op_assign
id|KEY_F5
comma
(braket
l_int|0x64
)braket
op_assign
id|KEY_F6
comma
(braket
l_int|0x65
)braket
op_assign
id|KEY_F7
comma
(braket
l_int|0x66
)braket
op_assign
id|KEY_F8
comma
(braket
l_int|0x67
)braket
op_assign
id|KEY_F9
comma
(braket
l_int|0x68
)braket
op_assign
id|KEY_F10
comma
(braket
l_int|0x71
)braket
op_assign
id|KEY_F11
comma
(braket
l_int|0x72
)braket
op_assign
id|KEY_F12
comma
(braket
l_int|0x73
)braket
op_assign
id|KEY_F13
comma
(braket
l_int|0x74
)braket
op_assign
id|KEY_F14
comma
(braket
l_int|0x7c
)braket
op_assign
id|KEY_F15
comma
(braket
l_int|0x7d
)braket
op_assign
id|KEY_F16
comma
(braket
l_int|0x80
)braket
op_assign
id|KEY_F17
comma
(braket
l_int|0x81
)braket
op_assign
id|KEY_F18
comma
(braket
l_int|0x82
)braket
op_assign
id|KEY_F19
comma
(braket
l_int|0x83
)braket
op_assign
id|KEY_F20
comma
(braket
l_int|0x8a
)braket
op_assign
id|KEY_FIND
comma
(braket
l_int|0x8b
)braket
op_assign
id|KEY_INSERT
comma
(braket
l_int|0x8c
)braket
op_assign
id|KEY_DELETE
comma
(braket
l_int|0x8d
)braket
op_assign
id|KEY_SELECT
comma
(braket
l_int|0x8e
)braket
op_assign
id|KEY_PAGEUP
comma
(braket
l_int|0x8f
)braket
op_assign
id|KEY_PAGEDOWN
comma
(braket
l_int|0x92
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|0x94
)braket
op_assign
id|KEY_KPDOT
comma
(braket
l_int|0x95
)braket
op_assign
id|KEY_KPENTER
comma
(braket
l_int|0x96
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|0x97
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|0x98
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|0x99
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|0x9a
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|0x9b
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|0x9c
)braket
op_assign
id|KEY_KPCOMMA
comma
(braket
l_int|0x9d
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|0x9e
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|0x9f
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|0xa0
)braket
op_assign
id|KEY_KPMINUS
comma
(braket
l_int|0xa1
)braket
op_assign
id|KEY_PROG1
comma
(braket
l_int|0xa2
)braket
op_assign
id|KEY_PROG2
comma
(braket
l_int|0xa3
)braket
op_assign
id|KEY_PROG3
comma
(braket
l_int|0xa4
)braket
op_assign
id|KEY_PROG4
comma
(braket
l_int|0xa7
)braket
op_assign
id|KEY_LEFT
comma
(braket
l_int|0xa8
)braket
op_assign
id|KEY_RIGHT
comma
(braket
l_int|0xa9
)braket
op_assign
id|KEY_DOWN
comma
(braket
l_int|0xaa
)braket
op_assign
id|KEY_UP
comma
(braket
l_int|0xab
)braket
op_assign
id|KEY_RIGHTSHIFT
comma
(braket
l_int|0xac
)braket
op_assign
id|KEY_LEFTALT
comma
(braket
l_int|0xad
)braket
op_assign
id|KEY_COMPOSE
comma
multiline_comment|/* Right Compose, that is. */
(braket
l_int|0xae
)braket
op_assign
id|KEY_LEFTSHIFT
comma
multiline_comment|/* Same as KEY_RIGHTSHIFT on LK201 */
(braket
l_int|0xaf
)braket
op_assign
id|KEY_LEFTCTRL
comma
(braket
l_int|0xb0
)braket
op_assign
id|KEY_CAPSLOCK
comma
(braket
l_int|0xb1
)braket
op_assign
id|KEY_COMPOSE
comma
multiline_comment|/* Left Compose, that is. */
(braket
l_int|0xb2
)braket
op_assign
id|KEY_RIGHTALT
comma
(braket
l_int|0xbc
)braket
op_assign
id|KEY_BACKSPACE
comma
(braket
l_int|0xbd
)braket
op_assign
id|KEY_ENTER
comma
(braket
l_int|0xbe
)braket
op_assign
id|KEY_TAB
comma
(braket
l_int|0xbf
)braket
op_assign
id|KEY_ESC
comma
(braket
l_int|0xc0
)braket
op_assign
id|KEY_1
comma
(braket
l_int|0xc1
)braket
op_assign
id|KEY_Q
comma
(braket
l_int|0xc2
)braket
op_assign
id|KEY_A
comma
(braket
l_int|0xc3
)braket
op_assign
id|KEY_Z
comma
(braket
l_int|0xc5
)braket
op_assign
id|KEY_2
comma
(braket
l_int|0xc6
)braket
op_assign
id|KEY_W
comma
(braket
l_int|0xc7
)braket
op_assign
id|KEY_S
comma
(braket
l_int|0xc8
)braket
op_assign
id|KEY_X
comma
(braket
l_int|0xc9
)braket
op_assign
id|KEY_102ND
comma
(braket
l_int|0xcb
)braket
op_assign
id|KEY_3
comma
(braket
l_int|0xcc
)braket
op_assign
id|KEY_E
comma
(braket
l_int|0xcd
)braket
op_assign
id|KEY_D
comma
(braket
l_int|0xce
)braket
op_assign
id|KEY_C
comma
(braket
l_int|0xd0
)braket
op_assign
id|KEY_4
comma
(braket
l_int|0xd1
)braket
op_assign
id|KEY_R
comma
(braket
l_int|0xd2
)braket
op_assign
id|KEY_F
comma
(braket
l_int|0xd3
)braket
op_assign
id|KEY_V
comma
(braket
l_int|0xd4
)braket
op_assign
id|KEY_SPACE
comma
(braket
l_int|0xd6
)braket
op_assign
id|KEY_5
comma
(braket
l_int|0xd7
)braket
op_assign
id|KEY_T
comma
(braket
l_int|0xd8
)braket
op_assign
id|KEY_G
comma
(braket
l_int|0xd9
)braket
op_assign
id|KEY_B
comma
(braket
l_int|0xdb
)braket
op_assign
id|KEY_6
comma
(braket
l_int|0xdc
)braket
op_assign
id|KEY_Y
comma
(braket
l_int|0xdd
)braket
op_assign
id|KEY_H
comma
(braket
l_int|0xde
)braket
op_assign
id|KEY_N
comma
(braket
l_int|0xe0
)braket
op_assign
id|KEY_7
comma
(braket
l_int|0xe1
)braket
op_assign
id|KEY_U
comma
(braket
l_int|0xe2
)braket
op_assign
id|KEY_J
comma
(braket
l_int|0xe3
)braket
op_assign
id|KEY_M
comma
(braket
l_int|0xe5
)braket
op_assign
id|KEY_8
comma
(braket
l_int|0xe6
)braket
op_assign
id|KEY_I
comma
(braket
l_int|0xe7
)braket
op_assign
id|KEY_K
comma
(braket
l_int|0xe8
)braket
op_assign
id|KEY_COMMA
comma
(braket
l_int|0xea
)braket
op_assign
id|KEY_9
comma
(braket
l_int|0xeb
)braket
op_assign
id|KEY_O
comma
(braket
l_int|0xec
)braket
op_assign
id|KEY_L
comma
(braket
l_int|0xed
)braket
op_assign
id|KEY_DOT
comma
(braket
l_int|0xef
)braket
op_assign
id|KEY_0
comma
(braket
l_int|0xf0
)braket
op_assign
id|KEY_P
comma
(braket
l_int|0xf2
)braket
op_assign
id|KEY_SEMICOLON
comma
(braket
l_int|0xf3
)braket
op_assign
id|KEY_SLASH
comma
(braket
l_int|0xf5
)braket
op_assign
id|KEY_EQUAL
comma
(braket
l_int|0xf6
)braket
op_assign
id|KEY_RIGHTBRACE
comma
(braket
l_int|0xf7
)braket
op_assign
id|KEY_BACKSLASH
comma
(braket
l_int|0xf9
)braket
op_assign
id|KEY_MINUS
comma
(braket
l_int|0xfa
)braket
op_assign
id|KEY_LEFTBRACE
comma
(braket
l_int|0xfb
)braket
op_assign
id|KEY_APOSTROPHE
comma
)brace
suffix:semicolon
DECL|macro|CHECK_LED
mdefine_line|#define CHECK_LED(LED, BITS) do {&t;&t;&bslash;&n;&t;if (test_bit (LED, lk-&gt;dev.led))&t;&bslash;&n;&t;&t;leds_on |= BITS;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&bslash;&n;&t;&t;leds_off |= BITS;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Per-keyboard data&n; */
DECL|struct|lkkbd
r_struct
id|lkkbd
(brace
DECL|member|keycode
id|lk_keycode_t
id|keycode
(braket
id|LK_NUM_KEYCODES
)braket
suffix:semicolon
DECL|member|ignore_bytes
r_int
id|ignore_bytes
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
(braket
id|LK_NUM_IGNORE_BYTES
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|tq
r_struct
id|work_struct
id|tq
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|bell_volume
r_int
id|bell_volume
suffix:semicolon
DECL|member|keyclick_volume
r_int
id|keyclick_volume
suffix:semicolon
DECL|member|ctrlclick_volume
r_int
id|ctrlclick_volume
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Calculate volume parameter byte for a given volume.&n; */
r_static
r_int
r_char
DECL|function|volume_to_hw
id|volume_to_hw
(paren
r_int
id|volume_percent
)paren
(brace
r_int
r_char
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
OL
l_int|0
)paren
id|volume_percent
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
OG
l_int|100
)paren
id|volume_percent
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|0
)paren
id|ret
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|13
)paren
multiline_comment|/* 12.5 */
id|ret
op_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|25
)paren
id|ret
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|38
)paren
multiline_comment|/* 37.5 */
id|ret
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|50
)paren
id|ret
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|63
)paren
multiline_comment|/* 62.5 */
id|ret
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* This is the default volume */
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|75
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|volume_percent
op_ge
l_int|88
)paren
multiline_comment|/* 87.5 */
id|ret
op_assign
l_int|0
suffix:semicolon
id|ret
op_or_assign
l_int|0x80
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|lkkbd_detection_done
id|lkkbd_detection_done
(paren
r_struct
id|lkkbd
op_star
id|lk
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Reset setting for Compose key. Let Compose be KEY_COMPOSE.&n;&t; */
id|lk-&gt;keycode
(braket
l_int|0xb1
)braket
op_assign
id|KEY_COMPOSE
suffix:semicolon
multiline_comment|/*&n;&t; * Print keyboard name and modify Compose=Alt on user&squot;s request.&n;&t; */
r_switch
c_cond
(paren
id|lk-&gt;id
(braket
l_int|4
)braket
)paren
(brace
r_case
l_int|1
suffix:colon
id|sprintf
(paren
id|lk-&gt;name
comma
l_string|&quot;DEC LK201 keyboard&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lk201_compose_is_alt
)paren
id|lk-&gt;keycode
(braket
l_int|0xb1
)braket
op_assign
id|KEY_LEFTALT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|sprintf
(paren
id|lk-&gt;name
comma
l_string|&quot;DEC LK401 keyboard&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
(paren
id|lk-&gt;name
comma
l_string|&quot;Unknown DEC keyboard&quot;
)paren
suffix:semicolon
id|printk
(paren
id|KERN_ERR
l_string|&quot;lkkbd: keyboard on %s is unknown, &quot;
l_string|&quot;please report to Jan-Benedict Glaw &quot;
l_string|&quot;&lt;jbglaw@lug-owl.de&gt;&bslash;n&quot;
comma
id|lk-&gt;phys
)paren
suffix:semicolon
id|printk
(paren
id|KERN_ERR
l_string|&quot;lkkbd: keyboard ID&squot;ed as:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|LK_NUM_IGNORE_BYTES
suffix:semicolon
id|i
op_increment
)paren
id|printk
(paren
l_string|&quot; 0x%02x&quot;
comma
id|lk-&gt;id
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;lkkbd: keyboard on %s identified as: %s&bslash;n&quot;
comma
id|lk-&gt;phys
comma
id|lk-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Report errors during keyboard boot-up.&n;&t; */
r_switch
c_cond
(paren
id|lk-&gt;id
(braket
l_int|2
)braket
)paren
(brace
r_case
l_int|0x00
suffix:colon
multiline_comment|/* All okay */
r_break
suffix:semicolon
r_case
id|LK_STUCK_KEY
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;lkkbd: Stuck key on keyboard at &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|lk-&gt;phys
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_SELFTEST_FAILED
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;lkkbd: Selftest failed on keyboard &quot;
l_string|&quot;at %s, keyboard may not work &quot;
l_string|&quot;properly&bslash;n&quot;
comma
id|lk-&gt;phys
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;lkkbd: Unknown error %02x on &quot;
l_string|&quot;keyboard at %s&bslash;n&quot;
comma
id|lk-&gt;id
(braket
l_int|2
)braket
comma
id|lk-&gt;phys
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Try to hint user if there&squot;s a stuck key.&n;&t; */
r_if
c_cond
(paren
id|lk-&gt;id
(braket
l_int|2
)braket
op_eq
id|LK_STUCK_KEY
op_logical_and
id|lk-&gt;id
(braket
l_int|3
)braket
op_ne
l_int|0
)paren
id|printk
(paren
id|KERN_ERR
l_string|&quot;Scancode of stuck key is 0x%02x, keycode &quot;
l_string|&quot;is 0x%04x&bslash;n&quot;
comma
id|lk-&gt;id
(braket
l_int|3
)braket
comma
id|lk-&gt;keycode
(braket
id|lk-&gt;id
(braket
l_int|3
)braket
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * lkkbd_interrupt() is called by the low level driver when a character&n; * is received.&n; */
r_static
id|irqreturn_t
DECL|function|lkkbd_interrupt
id|lkkbd_interrupt
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|lkkbd
op_star
id|lk
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got byte 0x%02x&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lk-&gt;ignore_bytes
OG
l_int|0
)paren
(brace
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Ignoring a byte on %s&bslash;n&quot;
comma
id|lk-&gt;name
)paren
suffix:semicolon
id|lk-&gt;id
(braket
id|LK_NUM_IGNORE_BYTES
op_minus
id|lk-&gt;ignore_bytes
op_decrement
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|lk-&gt;ignore_bytes
op_eq
l_int|0
)paren
id|lkkbd_detection_done
(paren
id|lk
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
id|LK_ALL_KEYS_UP
suffix:colon
id|input_regs
(paren
op_amp
id|lk-&gt;dev
comma
id|regs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
(paren
id|lkkbd_keycode
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|lk-&gt;keycode
(braket
id|i
)braket
op_ne
id|KEY_RESERVED
)paren
id|input_report_key
(paren
op_amp
id|lk-&gt;dev
comma
id|lk-&gt;keycode
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
id|input_sync
(paren
op_amp
id|lk-&gt;dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_METRONOME
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_METRONOME and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_OUTPUT_ERROR
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_OUTPUT_ERROR and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_INPUT_ERROR
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_INPUT_ERROR and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_KBD_LOCKED
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_KBD_LOCKED and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_KBD_TEST_MODE_ACK
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_KBD_TEST_MODE_ACK and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_PREFIX_KEY_DOWN
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_PREFIX_KEY_DOWN and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_MODE_CHANGE_ACK
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_MODE_CHANGE_ACK and ignored &quot;
l_string|&quot;it properly...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LK_RESPONSE_RESERVED
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got LK_RESPONSE_RESERVED and don&squot;t &quot;
l_string|&quot;know how to handle...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Got 0x01, scheduling re-initialization&bslash;n&quot;
)paren
suffix:semicolon
id|lk-&gt;ignore_bytes
op_assign
id|LK_NUM_IGNORE_BYTES
suffix:semicolon
id|lk-&gt;id
(braket
id|LK_NUM_IGNORE_BYTES
op_minus
id|lk-&gt;ignore_bytes
op_decrement
)braket
op_assign
id|data
suffix:semicolon
id|schedule_work
(paren
op_amp
id|lk-&gt;tq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|lk-&gt;keycode
(braket
id|data
)braket
op_ne
id|KEY_RESERVED
)paren
(brace
id|input_regs
(paren
op_amp
id|lk-&gt;dev
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
(paren
id|lk-&gt;keycode
(braket
id|data
)braket
comma
id|lk-&gt;dev.key
)paren
)paren
id|input_report_key
(paren
op_amp
id|lk-&gt;dev
comma
id|lk-&gt;keycode
(braket
id|data
)braket
comma
l_int|1
)paren
suffix:semicolon
r_else
id|input_report_key
(paren
op_amp
id|lk-&gt;dev
comma
id|lk-&gt;keycode
(braket
id|data
)braket
comma
l_int|0
)paren
suffix:semicolon
id|input_sync
(paren
op_amp
id|lk-&gt;dev
)paren
suffix:semicolon
)brace
r_else
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: Unknown key with &quot;
l_string|&quot;scancode 0x%02x on %s.&bslash;n&quot;
comma
id|__FILE__
comma
id|data
comma
id|lk-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * lkkbd_event() handles events from the input module.&n; */
r_static
r_int
DECL|function|lkkbd_event
id|lkkbd_event
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|lkkbd
op_star
id|lk
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_char
id|leds_on
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|leds_off
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_LED
suffix:colon
id|CHECK_LED
(paren
id|LED_CAPSL
comma
id|LK_LED_SHIFTLOCK
)paren
suffix:semicolon
id|CHECK_LED
(paren
id|LED_COMPOSE
comma
id|LK_LED_COMPOSE
)paren
suffix:semicolon
id|CHECK_LED
(paren
id|LED_SCROLLL
comma
id|LK_LED_SCROLLLOCK
)paren
suffix:semicolon
id|CHECK_LED
(paren
id|LED_SLEEP
comma
id|LK_LED_WAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|leds_on
op_ne
l_int|0
)paren
(brace
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_LED_ON
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|leds_on
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|leds_off
op_ne
l_int|0
)paren
(brace
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_LED_OFF
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|leds_off
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|EV_SND
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|SND_CLICK
suffix:colon
r_if
c_cond
(paren
id|value
op_eq
l_int|0
)paren
(brace
id|DBG
(paren
l_string|&quot;%s: Deactivating key clicks&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_DISABLE_KEYCLICK
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_DISABLE_CTRCLICK
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG
(paren
l_string|&quot;%s: Activating key clicks&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_ENABLE_KEYCLICK
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|volume_to_hw
(paren
id|lk-&gt;keyclick_volume
)paren
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_ENABLE_CTRCLICK
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|volume_to_hw
(paren
id|lk-&gt;ctrlclick_volume
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|SND_BELL
suffix:colon
r_if
c_cond
(paren
id|value
op_ne
l_int|0
)paren
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_SOUND_BELL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;%s (): Got unknown type %d, code %d, value %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * lkkbd_reinit() sets leds and beeps to a state the computer remembers they&n; * were in.&n; */
r_static
r_void
DECL|function|lkkbd_reinit
id|lkkbd_reinit
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|lkkbd
op_star
id|lk
op_assign
id|data
suffix:semicolon
r_int
id|division
suffix:semicolon
r_int
r_char
id|leds_on
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|leds_off
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Ask for ID */
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_REQUEST_ID
)paren
suffix:semicolon
multiline_comment|/* Reset parameters */
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_SET_DEFAULTS
)paren
suffix:semicolon
multiline_comment|/* Set LEDs */
id|CHECK_LED
(paren
id|LED_CAPSL
comma
id|LK_LED_SHIFTLOCK
)paren
suffix:semicolon
id|CHECK_LED
(paren
id|LED_COMPOSE
comma
id|LK_LED_COMPOSE
)paren
suffix:semicolon
id|CHECK_LED
(paren
id|LED_SCROLLL
comma
id|LK_LED_SCROLLLOCK
)paren
suffix:semicolon
id|CHECK_LED
(paren
id|LED_SLEEP
comma
id|LK_LED_WAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|leds_on
op_ne
l_int|0
)paren
(brace
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_LED_ON
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|leds_on
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|leds_off
op_ne
l_int|0
)paren
(brace
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_LED_OFF
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|leds_off
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Try to activate extended LK401 mode. This command will&n;&t; * only work with a LK401 keyboard and grants access to&n;&t; * LAlt, RAlt, RCompose and RShift.&n;&t; */
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_ENABLE_LK401
)paren
suffix:semicolon
multiline_comment|/* Set all keys to UPDOWN mode */
r_for
c_loop
(paren
id|division
op_assign
l_int|1
suffix:semicolon
id|division
op_le
l_int|14
suffix:semicolon
id|division
op_increment
)paren
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_SET_MODE
(paren
id|LK_MODE_UPDOWN
comma
id|division
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable bell and set volume */
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_ENABLE_BELL
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|volume_to_hw
(paren
id|lk-&gt;bell_volume
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable/disable keyclick (and possibly set volume) */
r_if
c_cond
(paren
id|test_bit
(paren
id|SND_CLICK
comma
id|lk-&gt;dev.snd
)paren
)paren
(brace
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_ENABLE_KEYCLICK
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|volume_to_hw
(paren
id|lk-&gt;keyclick_volume
)paren
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_ENABLE_CTRCLICK
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|volume_to_hw
(paren
id|lk-&gt;ctrlclick_volume
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_DISABLE_KEYCLICK
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_DISABLE_CTRCLICK
)paren
suffix:semicolon
)brace
multiline_comment|/* Sound the bell if needed */
r_if
c_cond
(paren
id|test_bit
(paren
id|SND_BELL
comma
id|lk-&gt;dev.snd
)paren
)paren
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_SOUND_BELL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lkkbd_connect() probes for a LK keyboard and fills the necessary structures.&n; */
r_static
r_void
DECL|function|lkkbd_connect
id|lkkbd_connect
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_struct
id|lkkbd
op_star
id|lk
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_TYPE
)paren
op_ne
id|SERIO_RS232
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_PROTO
)paren
op_ne
id|SERIO_LKKBD
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lk
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|lkkbd
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
(paren
id|lk
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|lkkbd
)paren
)paren
suffix:semicolon
id|init_input_dev
(paren
op_amp
id|lk-&gt;dev
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_KEY
comma
id|lk-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_LED
comma
id|lk-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_SND
comma
id|lk-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_REP
comma
id|lk-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|LED_CAPSL
comma
id|lk-&gt;dev.ledbit
)paren
suffix:semicolon
id|set_bit
(paren
id|LED_SLEEP
comma
id|lk-&gt;dev.ledbit
)paren
suffix:semicolon
id|set_bit
(paren
id|LED_COMPOSE
comma
id|lk-&gt;dev.ledbit
)paren
suffix:semicolon
id|set_bit
(paren
id|LED_SCROLLL
comma
id|lk-&gt;dev.ledbit
)paren
suffix:semicolon
id|set_bit
(paren
id|SND_BELL
comma
id|lk-&gt;dev.sndbit
)paren
suffix:semicolon
id|set_bit
(paren
id|SND_CLICK
comma
id|lk-&gt;dev.sndbit
)paren
suffix:semicolon
id|lk-&gt;serio
op_assign
id|serio
suffix:semicolon
id|INIT_WORK
(paren
op_amp
id|lk-&gt;tq
comma
id|lkkbd_reinit
comma
id|lk
)paren
suffix:semicolon
id|lk-&gt;bell_volume
op_assign
id|bell_volume
suffix:semicolon
id|lk-&gt;keyclick_volume
op_assign
id|keyclick_volume
suffix:semicolon
id|lk-&gt;ctrlclick_volume
op_assign
id|ctrlclick_volume
suffix:semicolon
id|lk-&gt;dev.keycode
op_assign
id|lk-&gt;keycode
suffix:semicolon
id|lk-&gt;dev.keycodesize
op_assign
r_sizeof
(paren
id|lk_keycode_t
)paren
suffix:semicolon
id|lk-&gt;dev.keycodemax
op_assign
id|LK_NUM_KEYCODES
suffix:semicolon
id|lk-&gt;dev.event
op_assign
id|lkkbd_event
suffix:semicolon
id|lk-&gt;dev
dot
r_private
op_assign
id|lk
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|lk
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
(paren
id|serio
comma
id|drv
)paren
)paren
(brace
id|kfree
(paren
id|lk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
(paren
id|lk-&gt;name
comma
l_string|&quot;DEC LK keyboard&quot;
)paren
suffix:semicolon
id|sprintf
(paren
id|lk-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|memcpy
(paren
id|lk-&gt;keycode
comma
id|lkkbd_keycode
comma
r_sizeof
(paren
id|lk_keycode_t
)paren
op_star
id|LK_NUM_KEYCODES
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|LK_NUM_KEYCODES
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
(paren
id|lk-&gt;keycode
(braket
id|i
)braket
comma
id|lk-&gt;dev.keybit
)paren
suffix:semicolon
id|lk-&gt;dev.name
op_assign
id|lk-&gt;name
suffix:semicolon
id|lk-&gt;dev.phys
op_assign
id|lk-&gt;phys
suffix:semicolon
id|lk-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|lk-&gt;dev.id.vendor
op_assign
id|SERIO_LKKBD
suffix:semicolon
id|lk-&gt;dev.id.product
op_assign
l_int|0
suffix:semicolon
id|lk-&gt;dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|lk-&gt;dev.dev
op_assign
op_amp
id|serio-&gt;dev
suffix:semicolon
id|input_register_device
(paren
op_amp
id|lk-&gt;dev
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s, initiating reset&bslash;n&quot;
comma
id|lk-&gt;name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|lk-&gt;serio-&gt;write
(paren
id|lk-&gt;serio
comma
id|LK_CMD_POWERCYCLE_RESET
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lkkbd_disconnect() unregisters and closes behind us.&n; */
r_static
r_void
DECL|function|lkkbd_disconnect
id|lkkbd_disconnect
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|lkkbd
op_star
id|lk
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
(paren
op_amp
id|lk-&gt;dev
)paren
suffix:semicolon
id|serio_close
(paren
id|serio
)paren
suffix:semicolon
id|kfree
(paren
id|lk
)paren
suffix:semicolon
)brace
DECL|variable|lkkbd_drv
r_static
r_struct
id|serio_driver
id|lkkbd_drv
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;lkkbd&quot;
comma
)brace
comma
dot
id|description
op_assign
id|DRIVER_DESC
comma
dot
id|connect
op_assign
id|lkkbd_connect
comma
dot
id|disconnect
op_assign
id|lkkbd_disconnect
comma
dot
id|interrupt
op_assign
id|lkkbd_interrupt
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for insering/removing us as a module.&n; */
r_int
id|__init
DECL|function|lkkbd_init
id|lkkbd_init
(paren
r_void
)paren
(brace
id|serio_register_driver
c_func
(paren
op_amp
id|lkkbd_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__exit
DECL|function|lkkbd_exit
id|lkkbd_exit
(paren
r_void
)paren
(brace
id|serio_unregister_driver
c_func
(paren
op_amp
id|lkkbd_drv
)paren
suffix:semicolon
)brace
DECL|variable|lkkbd_init
id|module_init
(paren
id|lkkbd_init
)paren
suffix:semicolon
DECL|variable|lkkbd_exit
id|module_exit
(paren
id|lkkbd_exit
)paren
suffix:semicolon
eof
