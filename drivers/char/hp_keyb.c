multiline_comment|/*&n; * linux/drivers/char/hp_keyb.c&n; * helper-functions for the keyboard/psaux driver for HP-PARISC workstations&n; *&n; * based on pc_keyb.c by Geert Uytterhoeven &amp; Martin Mares&n; *&n; * 2000/10/26&t;Debacker Xavier &lt;debackex@esiee.fr&gt;&n; *&t;&t;Marteau Thomas &lt;marteaut@esiee.fr&gt;&n; *&t;&t;Djoudi Malek &lt;djoudim@esiee.fr&gt;&n; * - fixed some keysym defines &n; *&n; * 2001/04/28&t;Debacker Xavier &lt;debackex@esiee.fr&gt;&n; * - scancode translation rewritten in handle_at_scancode()&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|KBD_REPORT_ERR
mdefine_line|#define KBD_REPORT_ERR
DECL|macro|KBD_REPORT_UNKN
mdefine_line|#define KBD_REPORT_UNKN
DECL|macro|KBD_ESCAPEE0
mdefine_line|#define KBD_ESCAPEE0&t;0xe0&t;&t;/* in */
DECL|macro|KBD_ESCAPEE1
mdefine_line|#define KBD_ESCAPEE1&t;0xe1&t;&t;/* in */
DECL|macro|ESCE0
mdefine_line|#define ESCE0(x)&t;(0xe000|(x))
DECL|macro|ESCE1
mdefine_line|#define ESCE1(x)&t;(0xe100|(x))
DECL|macro|KBD_BAT
mdefine_line|#define KBD_BAT&t;&t;0xaa&t;&t;/* in */
DECL|macro|KBD_SETLEDS
mdefine_line|#define KBD_SETLEDS&t;0xed&t;&t;/* out */
DECL|macro|KBD_ECHO
mdefine_line|#define KBD_ECHO&t;0xee&t;&t;/* in/out */
DECL|macro|KBD_BREAK
mdefine_line|#define KBD_BREAK&t;0xf0&t;&t;/* in */
DECL|macro|KBD_TYPRATEDLY
mdefine_line|#define KBD_TYPRATEDLY&t;0xf3&t;&t;/* out */
DECL|macro|KBD_SCANENABLE
mdefine_line|#define KBD_SCANENABLE&t;0xf4&t;&t;/* out */
DECL|macro|KBD_DEFDISABLE
mdefine_line|#define KBD_DEFDISABLE&t;0xf5&t;&t;/* out */
DECL|macro|KBD_DEFAULT
mdefine_line|#define KBD_DEFAULT&t;0xf6&t;&t;/* out */
DECL|macro|KBD_ACK
mdefine_line|#define KBD_ACK&t;&t;0xfa&t;&t;/* in */
DECL|macro|KBD_DIAGFAIL
mdefine_line|#define KBD_DIAGFAIL&t;0xfd&t;&t;/* in */
DECL|macro|KBD_RESEND
mdefine_line|#define KBD_RESEND&t;0xfe&t;&t;/* in/out */
DECL|macro|KBD_RESET
mdefine_line|#define KBD_RESET&t;0xff&t;&t;/* out */
DECL|macro|CODE_BREAK
mdefine_line|#define CODE_BREAK&t;1
DECL|macro|CODE_ESCAPEE0
mdefine_line|#define CODE_ESCAPEE0&t;2
DECL|macro|CODE_ESCAPEE1
mdefine_line|#define CODE_ESCAPEE1&t;4
DECL|macro|CODE_ESCAPE12
mdefine_line|#define CODE_ESCAPE12&t;8
DECL|macro|K_NONE
mdefine_line|#define K_NONE&t;&t;0x7f
DECL|macro|K_ESC
mdefine_line|#define K_ESC&t;&t;0x01
DECL|macro|K_F1
mdefine_line|#define K_F1&t;&t;0x3b
DECL|macro|K_F2
mdefine_line|#define K_F2&t;&t;0x3c
DECL|macro|K_F3
mdefine_line|#define K_F3&t;&t;0x3d
DECL|macro|K_F4
mdefine_line|#define K_F4&t;&t;0x3e
DECL|macro|K_F5
mdefine_line|#define K_F5&t;&t;0x3f
DECL|macro|K_F6
mdefine_line|#define K_F6&t;&t;0x40
DECL|macro|K_F7
mdefine_line|#define K_F7&t;&t;0x41
DECL|macro|K_F8
mdefine_line|#define K_F8&t;&t;0x42
DECL|macro|K_F9
mdefine_line|#define K_F9&t;&t;0x43
DECL|macro|K_F10
mdefine_line|#define K_F10&t;&t;0x44
DECL|macro|K_F11
mdefine_line|#define K_F11&t;&t;0x57
DECL|macro|K_F12
mdefine_line|#define K_F12&t;&t;0x58
DECL|macro|K_PRNT
mdefine_line|#define K_PRNT&t;&t;0x54
DECL|macro|K_SCRL
mdefine_line|#define K_SCRL&t;&t;0x46
DECL|macro|K_BRK
mdefine_line|#define K_BRK&t;&t;0x77
DECL|macro|K_AGR
mdefine_line|#define K_AGR&t;&t;0x29
DECL|macro|K_1
mdefine_line|#define K_1&t;&t;0x02
DECL|macro|K_2
mdefine_line|#define K_2&t;&t;0x03
DECL|macro|K_3
mdefine_line|#define K_3&t;&t;0x04
DECL|macro|K_4
mdefine_line|#define K_4&t;&t;0x05
DECL|macro|K_5
mdefine_line|#define K_5&t;&t;0x06
DECL|macro|K_6
mdefine_line|#define K_6&t;&t;0x07
DECL|macro|K_7
mdefine_line|#define K_7&t;&t;0x08
DECL|macro|K_8
mdefine_line|#define K_8&t;&t;0x09
DECL|macro|K_9
mdefine_line|#define K_9&t;&t;0x0a
DECL|macro|K_0
mdefine_line|#define K_0&t;&t;0x0b
DECL|macro|K_MINS
mdefine_line|#define K_MINS&t;&t;0x0c
DECL|macro|K_EQLS
mdefine_line|#define K_EQLS&t;&t;0x0d
DECL|macro|K_BKSP
mdefine_line|#define K_BKSP&t;&t;0x0e
DECL|macro|K_INS
mdefine_line|#define K_INS&t;&t;0x6e
DECL|macro|K_HOME
mdefine_line|#define K_HOME&t;&t;0x66
DECL|macro|K_PGUP
mdefine_line|#define K_PGUP&t;&t;0x68
DECL|macro|K_NUML
mdefine_line|#define K_NUML&t;&t;0x45
DECL|macro|KP_SLH
mdefine_line|#define KP_SLH&t;&t;0x62
DECL|macro|KP_STR
mdefine_line|#define KP_STR&t;&t;0x37
DECL|macro|KP_MNS
mdefine_line|#define KP_MNS&t;&t;0x4a
DECL|macro|K_TAB
mdefine_line|#define K_TAB&t;&t;0x0f
DECL|macro|K_Q
mdefine_line|#define K_Q&t;&t;0x10
DECL|macro|K_W
mdefine_line|#define K_W&t;&t;0x11
DECL|macro|K_E
mdefine_line|#define K_E&t;&t;0x12
DECL|macro|K_R
mdefine_line|#define K_R&t;&t;0x13
DECL|macro|K_T
mdefine_line|#define K_T&t;&t;0x14
DECL|macro|K_Y
mdefine_line|#define K_Y&t;&t;0x15
DECL|macro|K_U
mdefine_line|#define K_U&t;&t;0x16
DECL|macro|K_I
mdefine_line|#define K_I&t;&t;0x17
DECL|macro|K_O
mdefine_line|#define K_O&t;&t;0x18
DECL|macro|K_P
mdefine_line|#define K_P&t;&t;0x19
DECL|macro|K_LSBK
mdefine_line|#define K_LSBK&t;&t;0x1a
DECL|macro|K_RSBK
mdefine_line|#define K_RSBK&t;&t;0x1b
DECL|macro|K_ENTR
mdefine_line|#define K_ENTR&t;&t;0x1c
DECL|macro|K_DEL
mdefine_line|#define K_DEL&t;&t;111
DECL|macro|K_END
mdefine_line|#define K_END&t;&t;0x6b
DECL|macro|K_PGDN
mdefine_line|#define K_PGDN&t;&t;0x6d
DECL|macro|KP_7
mdefine_line|#define KP_7&t;&t;0x47
DECL|macro|KP_8
mdefine_line|#define KP_8&t;&t;0x48
DECL|macro|KP_9
mdefine_line|#define KP_9&t;&t;0x49
DECL|macro|KP_PLS
mdefine_line|#define KP_PLS&t;&t;0x4e
DECL|macro|K_CAPS
mdefine_line|#define K_CAPS&t;&t;0x3a
DECL|macro|K_A
mdefine_line|#define K_A&t;&t;0x1e
DECL|macro|K_S
mdefine_line|#define K_S&t;&t;0x1f
DECL|macro|K_D
mdefine_line|#define K_D&t;&t;0x20
DECL|macro|K_F
mdefine_line|#define K_F&t;&t;0x21
DECL|macro|K_G
mdefine_line|#define K_G&t;&t;0x22
DECL|macro|K_H
mdefine_line|#define K_H&t;&t;0x23
DECL|macro|K_J
mdefine_line|#define K_J&t;&t;0x24
DECL|macro|K_K
mdefine_line|#define K_K&t;&t;0x25
DECL|macro|K_L
mdefine_line|#define K_L&t;&t;0x26
DECL|macro|K_SEMI
mdefine_line|#define K_SEMI&t;&t;0x27
DECL|macro|K_SQOT
mdefine_line|#define K_SQOT&t;&t;0x28
DECL|macro|K_HASH
mdefine_line|#define K_HASH&t;&t;K_NONE
DECL|macro|KP_4
mdefine_line|#define KP_4&t;&t;0x4b
DECL|macro|KP_5
mdefine_line|#define KP_5&t;&t;0x4c
DECL|macro|KP_6
mdefine_line|#define KP_6&t;&t;0x4d
DECL|macro|K_LSFT
mdefine_line|#define K_LSFT&t;&t;0x2a
DECL|macro|K_BSLH
mdefine_line|#define K_BSLH&t;&t;0x2b
DECL|macro|K_Z
mdefine_line|#define K_Z&t;&t;0x2c
DECL|macro|K_X
mdefine_line|#define K_X&t;&t;0x2d
DECL|macro|K_C
mdefine_line|#define K_C&t;&t;0x2e
DECL|macro|K_V
mdefine_line|#define K_V&t;&t;0x2f
DECL|macro|K_B
mdefine_line|#define K_B&t;&t;0x30
DECL|macro|K_N
mdefine_line|#define K_N&t;&t;0x31
DECL|macro|K_M
mdefine_line|#define K_M&t;&t;0x32
DECL|macro|K_COMA
mdefine_line|#define K_COMA&t;&t;0x33
DECL|macro|K_DOT
mdefine_line|#define K_DOT&t;&t;0x34
DECL|macro|K_FSLH
mdefine_line|#define K_FSLH&t;&t;0x35
DECL|macro|K_RSFT
mdefine_line|#define K_RSFT&t;&t;0x36
DECL|macro|K_UP
mdefine_line|#define K_UP&t;&t;0x67
DECL|macro|KP_1
mdefine_line|#define KP_1&t;&t;0x4f
DECL|macro|KP_2
mdefine_line|#define KP_2&t;&t;0x50
DECL|macro|KP_3
mdefine_line|#define KP_3&t;&t;0x51
DECL|macro|KP_ENT
mdefine_line|#define KP_ENT&t;&t;0x60
DECL|macro|K_LCTL
mdefine_line|#define K_LCTL&t;&t;0x1d
DECL|macro|K_LALT
mdefine_line|#define K_LALT&t;&t;0x38
DECL|macro|K_SPCE
mdefine_line|#define K_SPCE&t;&t;0x39
DECL|macro|K_RALT
mdefine_line|#define K_RALT&t;&t;0x64
DECL|macro|K_RCTL
mdefine_line|#define K_RCTL&t;&t;0x61
DECL|macro|K_LEFT
mdefine_line|#define K_LEFT&t;&t;0x69
DECL|macro|K_DOWN
mdefine_line|#define K_DOWN&t;&t;0x6c
DECL|macro|K_RGHT
mdefine_line|#define K_RGHT&t;&t;0x6a
DECL|macro|KP_0
mdefine_line|#define KP_0&t;&t;0x52
DECL|macro|KP_DOT
mdefine_line|#define KP_DOT&t;&t;0x53
DECL|variable|keycode_translate
r_static
r_int
r_char
id|keycode_translate
(braket
l_int|256
)braket
op_assign
(brace
multiline_comment|/* 00 */
id|K_NONE
comma
id|K_F9
comma
id|K_NONE
comma
id|K_F5
comma
id|K_F3
comma
id|K_F1
comma
id|K_F2
comma
id|K_F12
comma
multiline_comment|/* 08 */
id|K_NONE
comma
id|K_F10
comma
id|K_F8
comma
id|K_F6
comma
id|K_F4
comma
id|K_TAB
comma
id|K_AGR
comma
id|K_NONE
comma
multiline_comment|/* 10 */
id|K_NONE
comma
id|K_LALT
comma
id|K_LSFT
comma
id|K_NONE
comma
id|K_LCTL
comma
id|K_Q
comma
id|K_1
comma
id|K_NONE
comma
multiline_comment|/* 18 */
id|K_NONE
comma
id|K_NONE
comma
id|K_Z
comma
id|K_S
comma
id|K_A
comma
id|K_W
comma
id|K_2
comma
id|K_NONE
comma
multiline_comment|/* 20 */
id|K_NONE
comma
id|K_C
comma
id|K_X
comma
id|K_D
comma
id|K_E
comma
id|K_4
comma
id|K_3
comma
id|K_NONE
comma
multiline_comment|/* 28 */
id|K_NONE
comma
id|K_SPCE
comma
id|K_V
comma
id|K_F
comma
id|K_T
comma
id|K_R
comma
id|K_5
comma
id|K_NONE
comma
multiline_comment|/* 30 */
id|K_NONE
comma
id|K_N
comma
id|K_B
comma
id|K_H
comma
id|K_G
comma
id|K_Y
comma
id|K_6
comma
id|K_NONE
comma
multiline_comment|/* 38 */
id|K_NONE
comma
id|K_NONE
comma
id|K_M
comma
id|K_J
comma
id|K_U
comma
id|K_7
comma
id|K_8
comma
id|K_NONE
comma
multiline_comment|/* 40 */
id|K_NONE
comma
id|K_COMA
comma
id|K_K
comma
id|K_I
comma
id|K_O
comma
id|K_0
comma
id|K_9
comma
id|K_NONE
comma
multiline_comment|/* 48 */
id|K_NONE
comma
id|K_DOT
comma
id|K_FSLH
comma
id|K_L
comma
id|K_SEMI
comma
id|K_P
comma
id|K_MINS
comma
id|K_NONE
comma
multiline_comment|/* 50 */
id|K_NONE
comma
id|K_NONE
comma
id|K_SQOT
comma
id|K_NONE
comma
id|K_LSBK
comma
id|K_EQLS
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* 58 */
id|K_CAPS
comma
id|K_RSFT
comma
id|K_ENTR
comma
id|K_RSBK
comma
id|K_NONE
comma
id|K_BSLH
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* 60 */
id|K_NONE
comma
id|K_HASH
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_BKSP
comma
id|K_NONE
comma
multiline_comment|/* 68 */
id|K_NONE
comma
id|KP_1
comma
id|K_NONE
comma
id|KP_4
comma
id|KP_7
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* 70 */
id|KP_0
comma
id|KP_DOT
comma
id|KP_2
comma
id|KP_5
comma
id|KP_6
comma
id|KP_8
comma
id|K_ESC
comma
id|K_NUML
comma
multiline_comment|/* 78 */
id|K_F11
comma
id|KP_PLS
comma
id|KP_3
comma
id|KP_MNS
comma
id|KP_STR
comma
id|KP_9
comma
id|K_SCRL
comma
id|K_PRNT
comma
multiline_comment|/* 80 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_F7
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* 88 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* 90 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* 98 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* a0 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* a8 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* b0 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* b8 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* c0 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* c8 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* d0 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* d8 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* e0 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* e8 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* f0 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
multiline_comment|/* f8 */
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|K_NONE
comma
id|KBD_RESEND
comma
id|K_NONE
)brace
suffix:semicolon
multiline_comment|/* ----- the following code stolen from pc_keyb.c */
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|hp_ps2kbd_sysrq_xlate
r_int
r_char
id|hp_ps2kbd_sysrq_xlate
(braket
l_int|128
)braket
op_assign
l_string|&quot;&bslash;000&bslash;0331234567890-=&bslash;177&bslash;t&quot;
multiline_comment|/* 0x00 - 0x0f */
l_string|&quot;qwertyuiop[]&bslash;r&bslash;000as&quot;
multiline_comment|/* 0x10 - 0x1f */
l_string|&quot;dfghjkl;&squot;`&bslash;000&bslash;&bslash;zxcv&quot;
multiline_comment|/* 0x20 - 0x2f */
l_string|&quot;bnm,./&bslash;000*&bslash;000 &bslash;000&bslash;201&bslash;202&bslash;203&bslash;204&bslash;205&quot;
multiline_comment|/* 0x30 - 0x3f */
l_string|&quot;&bslash;206&bslash;207&bslash;210&bslash;211&bslash;212&bslash;000&bslash;000789-456+1&quot;
multiline_comment|/* 0x40 - 0x4f */
l_string|&quot;230&bslash;177&bslash;000&bslash;000&bslash;213&bslash;214&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&quot;
multiline_comment|/* 0x50 - 0x5f */
l_string|&quot;&bslash;r&bslash;000/&quot;
suffix:semicolon
multiline_comment|/* 0x60 - 0x6f */
macro_line|#endif
multiline_comment|/*&n; * Translation of escaped scancodes to keycodes.&n; * This is now user-settable.&n; * The keycodes 1-88,96-111,119 are fairly standard, and&n; * should probably not be changed - changing might confuse X.&n; * X also interprets scancode 0x5d (KEY_Begin).&n; *&n; * For 1-88 keycode equals scancode.&n; */
DECL|macro|E0_KPENTER
mdefine_line|#define E0_KPENTER 96
DECL|macro|E0_RCTRL
mdefine_line|#define E0_RCTRL   97
DECL|macro|E0_KPSLASH
mdefine_line|#define E0_KPSLASH 98
DECL|macro|E0_PRSCR
mdefine_line|#define E0_PRSCR   99
DECL|macro|E0_RALT
mdefine_line|#define E0_RALT    100
DECL|macro|E0_BREAK
mdefine_line|#define E0_BREAK   101&t;/* (control-pause) */
DECL|macro|E0_HOME
mdefine_line|#define E0_HOME    102
DECL|macro|E0_UP
mdefine_line|#define E0_UP      103
DECL|macro|E0_PGUP
mdefine_line|#define E0_PGUP    104
DECL|macro|E0_LEFT
mdefine_line|#define E0_LEFT    105
DECL|macro|E0_RIGHT
mdefine_line|#define E0_RIGHT   106
DECL|macro|E0_END
mdefine_line|#define E0_END     107
DECL|macro|E0_DOWN
mdefine_line|#define E0_DOWN    108
DECL|macro|E0_PGDN
mdefine_line|#define E0_PGDN    109
DECL|macro|E0_INS
mdefine_line|#define E0_INS     110
DECL|macro|E0_DEL
mdefine_line|#define E0_DEL     111
DECL|macro|E1_PAUSE
mdefine_line|#define E1_PAUSE   119
multiline_comment|/*&n; * The keycodes below are randomly located in 89-95,112-118,120-127.&n; * They could be thrown away (and all occurrences below replaced by 0),&n; * but that would force many users to use the `setkeycodes&squot; utility, where&n; * they needed not before. It does not matter that there are duplicates, as&n; * long as no duplication occurs for any single keyboard.&n; */
DECL|macro|SC_LIM
mdefine_line|#define SC_LIM 89&t;&t;/* 0x59 == 89 */
DECL|macro|FOCUS_PF1
mdefine_line|#define FOCUS_PF1 85&t;&t;/* actual code! */
DECL|macro|FOCUS_PF2
mdefine_line|#define FOCUS_PF2 89
DECL|macro|FOCUS_PF3
mdefine_line|#define FOCUS_PF3 90
DECL|macro|FOCUS_PF4
mdefine_line|#define FOCUS_PF4 91
DECL|macro|FOCUS_PF5
mdefine_line|#define FOCUS_PF5 92
DECL|macro|FOCUS_PF6
mdefine_line|#define FOCUS_PF6 93
DECL|macro|FOCUS_PF7
mdefine_line|#define FOCUS_PF7 94
DECL|macro|FOCUS_PF8
mdefine_line|#define FOCUS_PF8 95
DECL|macro|FOCUS_PF9
mdefine_line|#define FOCUS_PF9 120
DECL|macro|FOCUS_PF10
mdefine_line|#define FOCUS_PF10 121
DECL|macro|FOCUS_PF11
mdefine_line|#define FOCUS_PF11 122
DECL|macro|FOCUS_PF12
mdefine_line|#define FOCUS_PF12 123
DECL|macro|JAP_86
mdefine_line|#define JAP_86     124
multiline_comment|/* tfj@olivia.ping.dk:&n; * The four keys are located over the numeric keypad, and are&n; * labelled A1-A4. It&squot;s an rc930 keyboard, from&n; * Regnecentralen/RC International, Now ICL.&n; * Scancodes: 59, 5a, 5b, 5c.&n; */
DECL|macro|RGN1
mdefine_line|#define RGN1 124
DECL|macro|RGN2
mdefine_line|#define RGN2 125
DECL|macro|RGN3
mdefine_line|#define RGN3 126
DECL|macro|RGN4
mdefine_line|#define RGN4 127
DECL|variable|high_keys
r_static
r_int
r_char
id|high_keys
(braket
l_int|128
op_minus
id|SC_LIM
)braket
op_assign
(brace
id|RGN1
comma
id|RGN2
comma
id|RGN3
comma
id|RGN4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x59-0x5f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x60-0x67 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|FOCUS_PF11
comma
l_int|0
comma
id|FOCUS_PF12
comma
multiline_comment|/* 0x68-0x6f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|FOCUS_PF2
comma
id|FOCUS_PF9
comma
l_int|0
comma
l_int|0
comma
id|FOCUS_PF3
comma
multiline_comment|/* 0x70-0x77 */
id|FOCUS_PF4
comma
id|FOCUS_PF5
comma
id|FOCUS_PF6
comma
id|FOCUS_PF7
comma
multiline_comment|/* 0x78-0x7b */
id|FOCUS_PF8
comma
id|JAP_86
comma
id|FOCUS_PF10
comma
l_int|0
multiline_comment|/* 0x7c-0x7f */
)brace
suffix:semicolon
multiline_comment|/* BTC */
DECL|macro|E0_MACRO
mdefine_line|#define E0_MACRO   112
multiline_comment|/* LK450 */
DECL|macro|E0_F13
mdefine_line|#define E0_F13     113
DECL|macro|E0_F14
mdefine_line|#define E0_F14     114
DECL|macro|E0_HELP
mdefine_line|#define E0_HELP    115
DECL|macro|E0_DO
mdefine_line|#define E0_DO      116
DECL|macro|E0_F17
mdefine_line|#define E0_F17     117
DECL|macro|E0_KPMINPLUS
mdefine_line|#define E0_KPMINPLUS 118
multiline_comment|/*&n; * My OmniKey generates e0 4c for  the &quot;OMNI&quot; key and the&n; * right alt key does nada. [kkoller@nyx10.cs.du.edu]&n; */
DECL|macro|E0_OK
mdefine_line|#define E0_OK&t;124
multiline_comment|/*&n; * New microsoft keyboard is rumoured to have&n; * e0 5b (left window button), e0 5c (right window button),&n; * e0 5d (menu button). [or: LBANNER, RBANNER, RMENU]&n; * [or: Windows_L, Windows_R, TaskMan]&n; */
DECL|macro|E0_MSLW
mdefine_line|#define E0_MSLW&t;125
DECL|macro|E0_MSRW
mdefine_line|#define E0_MSRW&t;126
DECL|macro|E0_MSTM
mdefine_line|#define E0_MSTM&t;127
DECL|variable|e0_keys
r_static
r_int
r_char
id|e0_keys
(braket
l_int|128
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x00-0x07 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x08-0x0f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x10-0x17 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_KPENTER
comma
id|E0_RCTRL
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x18-0x1f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x20-0x27 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x28-0x2f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_KPSLASH
comma
l_int|0
comma
id|E0_PRSCR
comma
multiline_comment|/* 0x30-0x37 */
id|E0_RALT
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_F13
comma
id|E0_F14
comma
id|E0_HELP
comma
multiline_comment|/* 0x38-0x3f */
id|E0_DO
comma
id|E0_F17
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_BREAK
comma
id|E0_HOME
comma
multiline_comment|/* 0x40-0x47 */
id|E0_UP
comma
id|E0_PGUP
comma
l_int|0
comma
id|E0_LEFT
comma
id|E0_OK
comma
id|E0_RIGHT
comma
id|E0_KPMINPLUS
comma
id|E0_END
comma
multiline_comment|/* 0x48-0x4f */
id|E0_DOWN
comma
id|E0_PGDN
comma
id|E0_INS
comma
id|E0_DEL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x50-0x57 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_MSLW
comma
id|E0_MSRW
comma
id|E0_MSTM
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x58-0x5f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x60-0x67 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|E0_MACRO
comma
multiline_comment|/* 0x68-0x6f */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0x70-0x77 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
multiline_comment|/* 0x78-0x7f */
)brace
suffix:semicolon
DECL|function|pckbd_setkeycode
r_int
id|pckbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
(brace
r_if
c_cond
(paren
id|scancode
template_param
l_int|255
op_logical_or
id|keycode
OG
l_int|127
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|scancode
OL
l_int|128
)paren
id|high_keys
(braket
id|scancode
op_minus
id|SC_LIM
)braket
op_assign
id|keycode
suffix:semicolon
r_else
id|e0_keys
(braket
id|scancode
op_minus
l_int|128
)braket
op_assign
id|keycode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pckbd_getkeycode
r_int
id|pckbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
(brace
r_return
(paren
id|scancode
template_param
l_int|255
)paren
ques
c_cond
op_minus
id|EINVAL
suffix:colon
(paren
id|scancode
OL
l_int|128
)paren
ques
c_cond
id|high_keys
(braket
id|scancode
op_minus
id|SC_LIM
)braket
suffix:colon
id|e0_keys
(braket
id|scancode
op_minus
l_int|128
)braket
suffix:semicolon
)brace
DECL|function|pckbd_translate
r_int
id|pckbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
(brace
r_static
r_int
id|prev_scancode
suffix:semicolon
multiline_comment|/* special prefix scancodes.. */
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0xe0
op_logical_or
id|scancode
op_eq
l_int|0xe1
)paren
(brace
id|prev_scancode
op_assign
id|scancode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 0xFF is sent by a few keyboards, ignore it. 0x00 is error */
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0x00
op_logical_or
id|scancode
op_eq
l_int|0xff
)paren
(brace
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|scancode
op_and_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|prev_scancode
)paren
(brace
multiline_comment|/*&n;&t;   * usually it will be 0xe0, but a Pause key generates&n;&t;   * e1 1d 45 e1 9d c5 when pressed, and nothing when released&n;&t;   */
r_if
c_cond
(paren
id|prev_scancode
op_ne
l_int|0xe0
)paren
(brace
r_if
c_cond
(paren
id|prev_scancode
op_eq
l_int|0xe1
op_logical_and
id|scancode
op_eq
l_int|0x1d
)paren
(brace
id|prev_scancode
op_assign
l_int|0x100
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|prev_scancode
op_eq
l_int|0x100
op_logical_and
id|scancode
op_eq
l_int|0x45
)paren
(brace
op_star
id|keycode
op_assign
id|E1_PAUSE
suffix:semicolon
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef KBD_REPORT_UNKN
r_if
c_cond
(paren
op_logical_neg
id|raw_mode
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unknown e1 escape sequence&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|prev_scancode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;       *  The keyboard maintains its own internal caps lock and&n;&t;       *  num lock statuses. In caps lock mode E0 AA precedes make&n;&t;       *  code and E0 2A follows break code. In num lock mode,&n;&t;       *  E0 2A precedes make code and E0 AA follows break code.&n;&t;       *  We do our own book-keeping, so we will just ignore these.&n;&t;       */
multiline_comment|/*&n;&t;       *  For my keyboard there is no caps lock mode, but there are&n;&t;       *  both Shift-L and Shift-R modes. The former mode generates&n;&t;       *  E0 2A / E0 AA pairs, the latter E0 B6 / E0 36 pairs.&n;&t;       *  So, we should also ignore the latter. - aeb@cwi.nl&n;&t;       */
r_if
c_cond
(paren
id|scancode
op_eq
l_int|0x2a
op_logical_or
id|scancode
op_eq
l_int|0x36
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|e0_keys
(braket
id|scancode
)braket
)paren
op_star
id|keycode
op_assign
id|e0_keys
(braket
id|scancode
)braket
suffix:semicolon
r_else
(brace
macro_line|#ifdef KBD_REPORT_UNKN
r_if
c_cond
(paren
op_logical_neg
id|raw_mode
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unknown scancode e0 %02x&bslash;n&quot;
comma
id|scancode
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|scancode
op_ge
id|SC_LIM
)paren
(brace
multiline_comment|/* This happens with the FOCUS 9000 keyboard&n;&t;       Its keys PF1..PF12 are reported to generate&n;&t;       55 73 77 78 79 7a 7b 7c 74 7e 6d 6f&n;&t;       Moreover, unless repeated, they do not generate&n;&t;       key-down events, so we have to zero up_flag below */
multiline_comment|/* Also, Japanese 86/106 keyboards are reported to&n;&t;       generate 0x73 and 0x7d for &bslash; - and &bslash; | respectively. */
multiline_comment|/* Also, some Brazilian keyboard is reported to produce&n;&t;       0x73 and 0x7e for &bslash; ? and KP-dot, respectively. */
op_star
id|keycode
op_assign
id|high_keys
(braket
id|scancode
op_minus
id|SC_LIM
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|keycode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|raw_mode
)paren
(brace
macro_line|#ifdef KBD_REPORT_UNKN
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unrecognized scancode (%02x)&quot;
l_string|&quot; - ignored&bslash;n&quot;
comma
id|scancode
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
op_star
id|keycode
op_assign
id|scancode
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ----- end of stolen part ------ */
DECL|function|kbd_reset_setup
r_void
id|kbd_reset_setup
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|handle_at_scancode
r_void
id|handle_at_scancode
c_func
(paren
r_int
id|keyval
)paren
(brace
r_static
r_int
id|brk
suffix:semicolon
r_static
r_int
id|esc0
suffix:semicolon
r_static
r_int
id|esc1
suffix:semicolon
r_int
id|scancode
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|keyval
)paren
(brace
r_case
id|KBD_BREAK
suffix:colon
multiline_comment|/* sets the &quot;release_key&quot; bit when a key is &n;&t;&t;&t;   released. HP keyboard send f0 followed by &n;&t;&t;&t;   the keycode while AT keyboard send the keycode&n;&t;&t;&t;   with this bit set. */
id|brk
op_assign
l_int|0x80
suffix:semicolon
r_return
suffix:semicolon
r_case
id|KBD_ESCAPEE0
suffix:colon
multiline_comment|/* 2chars sequence, commonly used to differenciate &n;&t;&t;&t;   the two ALT keys and the two ENTER keys and so &n;&t;&t;&t;   on... */
id|esc0
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* e0-xx are 2 chars */
id|scancode
op_assign
id|keyval
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KBD_ESCAPEE1
suffix:colon
multiline_comment|/* 3chars sequence, only used by the Pause key. */
id|esc1
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* e1-xx-xx are 3 chars */
id|scancode
op_assign
id|keyval
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
id|KBD_RESEND
suffix:colon
multiline_comment|/* dunno what to do when it happens. RFC */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: KBD_RESEND received.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif
r_case
l_int|0x14
suffix:colon
multiline_comment|/* translate e1-14-77-e1-f0-14-f0-77 to &n;&t;&t;&t;   e1-1d-45-e1-9d-c5 (the Pause key) */
r_if
c_cond
(paren
id|esc1
op_eq
l_int|2
)paren
id|scancode
op_assign
id|brk
op_or
l_int|0x1d
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x77
suffix:colon
r_if
c_cond
(paren
id|esc1
op_eq
l_int|1
)paren
id|scancode
op_assign
id|brk
op_or
l_int|0x45
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x12
suffix:colon
multiline_comment|/* an extended key is e0-12-e0-xx e0-f0-xx-e0-f0-12&n;&t;&t;&t;   on HP, while it is e0-2a-e0-xx e0-(xx|80)-f0-aa &n;&t;&t;&t;   on AT. */
r_if
c_cond
(paren
id|esc0
op_eq
l_int|1
)paren
id|scancode
op_assign
id|brk
op_or
l_int|0x2a
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* translates HP scancodes to AT scancodes */
r_if
c_cond
(paren
op_logical_neg
id|scancode
)paren
id|scancode
op_assign
id|brk
op_or
id|keycode_translate
(braket
id|keyval
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scancode
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;keyboard: unexpected key code %02x&bslash;n&quot;
comma
id|keyval
)paren
suffix:semicolon
multiline_comment|/* now behave like an AT keyboard */
id|handle_scancode
c_func
(paren
id|scancode
comma
op_logical_neg
(paren
id|scancode
op_amp
l_int|0x80
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esc0
)paren
id|esc0
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|esc1
)paren
id|esc1
op_decrement
suffix:semicolon
multiline_comment|/* release key bit must be unset for the next key */
id|brk
op_assign
l_int|0
suffix:semicolon
)brace
eof
