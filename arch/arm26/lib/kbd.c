macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
singleline_comment|//#include &lt;linux/kbd_ll.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
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
mdefine_line|#define E0_BREAK   101&t;&t;/* (control-pause) */
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
multiline_comment|/* for USB 106 keyboard */
DECL|macro|E0_YEN
mdefine_line|#define E0_YEN         124
DECL|macro|E0_BACKSLASH
mdefine_line|#define E0_BACKSLASH   89
DECL|macro|E1_PAUSE
mdefine_line|#define E1_PAUSE   119
multiline_comment|/*&n; * The keycodes below are randomly located in 89-95,112-118,120-127.&n; * They could be thrown away (and all occurrences below replaced by 0),&n; * but that would force many users to use the `setkeycodes&squot; utility, where&n; * they needed not before. It does not matter that there are duplicates, as&n; * long as no duplication occurs for any single keyboard.&n; */
DECL|macro|SC_LIM
mdefine_line|#define SC_LIM 89
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
mdefine_line|#define E0_OK  124
multiline_comment|/*&n; * New microsoft keyboard is rumoured to have&n; * e0 5b (left window button), e0 5c (right window button),&n; * e0 5d (menu button). [or: LBANNER, RBANNER, RMENU]&n; * [or: Windows_L, Windows_R, TaskMan]&n; */
DECL|macro|E0_MSLW
mdefine_line|#define E0_MSLW        125
DECL|macro|E0_MSRW
mdefine_line|#define E0_MSRW        126
DECL|macro|E0_MSTM
mdefine_line|#define E0_MSTM        127
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
singleline_comment|//0, 0, 0, 0, 0, 0, 0, 0,                          /* 0x70-0x77 */
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
id|E0_BACKSLASH
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
id|E0_YEN
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
DECL|function|gen_setkeycode
r_static
r_int
id|gen_setkeycode
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
DECL|function|gen_getkeycode
r_static
r_int
id|gen_getkeycode
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
r_static
r_int
DECL|function|gen_translate
id|gen_translate
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
op_assign
l_int|0
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
multiline_comment|/*&n;&t;&t; * usually it will be 0xe0, but a Pause key generates&n;&t;&t; * e1 1d 45 e1 9d c5 when pressed, and nothing when released&n;&t;&t; */
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
multiline_comment|/*&n;&t;&t;&t; *  The keyboard maintains its own internal caps lock and&n;&t;&t;&t; *  num lock statuses. In caps lock mode E0 AA precedes make&n;&t;&t;&t; *  code and E0 2A follows break code. In num lock mode,&n;&t;&t;&t; *  E0 2A precedes make code and E0 AA follows break code.&n;&t;&t;&t; *  We do our own book-keeping, so we will just ignore these.&n;&t;&t;&t; */
multiline_comment|/*&n;&t;&t;&t; *  For my keyboard there is no caps lock mode, but there are&n;&t;&t;&t; *  both Shift-L and Shift-R modes. The former mode generates&n;&t;&t;&t; *  E0 2A / E0 AA pairs, the latter E0 B6 / E0 36 pairs.&n;&t;&t;&t; *  So, we should also ignore the latter. - aeb@cwi.nl&n;&t;&t;&t; */
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
multiline_comment|/* This happens with the FOCUS 9000 keyboard&n;&t;&t;   Its keys PF1..PF12 are reported to generate&n;&t;&t;   55 73 77 78 79 7a 7b 7c 74 7e 6d 6f&n;&t;&t;   Moreover, unless repeated, they do not generate&n;&t;&t;   key-down events, so we have to zero up_flag below */
multiline_comment|/* Also, Japanese 86/106 keyboards are reported to&n;&t;&t;   generate 0x73 and 0x7d for &bslash; - and &bslash; | respectively. */
multiline_comment|/* Also, some Brazilian keyboard is reported to produce&n;&t;&t;   0x73 and 0x7e for &bslash; ? and KP-dot, respectively. */
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
DECL|function|gen_unexpected_up
r_static
r_char
id|gen_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
(brace
multiline_comment|/* unexpected, but this can happen: maybe this was a key release for a&n;&t;   FOCUS 9000 PF key; if we want to see it, we have to clear up_flag */
r_if
c_cond
(paren
id|keycode
op_ge
id|SC_LIM
op_logical_or
id|keycode
op_eq
l_int|85
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|0200
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the default mappings&n; */
DECL|variable|k_setkeycode
r_int
(paren
op_star
id|k_setkeycode
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
op_assign
id|gen_setkeycode
suffix:semicolon
DECL|variable|k_getkeycode
r_int
(paren
op_star
id|k_getkeycode
)paren
(paren
r_int
r_int
)paren
op_assign
id|gen_getkeycode
suffix:semicolon
DECL|variable|k_translate
r_int
(paren
op_star
id|k_translate
)paren
(paren
r_int
r_char
comma
r_int
r_char
op_star
comma
r_char
)paren
op_assign
id|gen_translate
suffix:semicolon
DECL|variable|k_unexpected_up
r_char
(paren
op_star
id|k_unexpected_up
)paren
(paren
r_int
r_char
)paren
op_assign
id|gen_unexpected_up
suffix:semicolon
DECL|variable|k_leds
r_void
(paren
op_star
id|k_leds
)paren
(paren
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/* Simple translation table for the SysRq keys */
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|gen_sysrq_xlate
r_static
r_int
r_char
id|gen_sysrq_xlate
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
DECL|variable|k_sysrq_xlate
r_int
r_char
op_star
id|k_sysrq_xlate
op_assign
id|gen_sysrq_xlate
suffix:semicolon
DECL|variable|k_sysrq_key
r_int
id|k_sysrq_key
op_assign
l_int|0x54
suffix:semicolon
macro_line|#endif
eof
