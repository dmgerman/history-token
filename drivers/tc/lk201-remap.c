multiline_comment|/*&n; * Keyboard mappings for DEC LK201/401/501 keyboards&n; * &n; * 17.05.99 Michael Engel (engel@unix-ag.org)&n; *&n; * DEC US keyboards generate keycodes in the range 0x55 - 0xfb&n; *&n; * This conflicts with Linux scancode conventions which define &n; * 0x00-0x7f as &quot;normal&quot; and 0x80-0xff as &quot;shifted&quot; scancodes, so we&n; * have to remap the keycodes to 0x00-0x7f with the scancodeRemap&n; * array. The generated scancode is simply the number of the key counted&n; * from the left upper to the right lower corner of the keyboard ...&n; *&n; * These scancodes are then being remapped (I hope ;-)) with the &n; * lk501*map[] arrays which define scancode -&gt; Linux code mapping&n; *&n; * Oh man is this horrible ;-)&n; *&n; * Scancodes with dual labels exist for keyboards as follows:&n; *&n; * code:  left label          / right label&n; *&n; * 0x73:  LKx01, LK421        / LK443, LK444&n; * 0x74:  LKx01, LK421        / LK443, LK444&n; * 0x7c:  LKx01, LK421        / LK443, LK444&n; * 0x8a:  LKx01, LK421        / LK443, LK444&n; * 0x8b:  LKx01, LK421        / LK443, LK444&n; * 0x8c:  LKx01, LK421        / LK443, LK444&n; * 0x8d:  LKx01, LK421        / LK443, LK444&n; * 0x8e:  LKx01, LK421        / LK443, LK444&n; * 0x8f:  LKx01, LK421        / LK443, LK444&n; * 0x9c:  LKx01, LK421        / LK443, LK444&n; * 0xa1:  LKx01, LK421        / LK443, LK444&n; * 0xa2:  LKx01, LK421        / LK443, LK444&n; * 0xa3:  LKx01, LK421        / LK443, LK444&n; * 0xa4:  LKx01, LK421        / LK443, LK444&n; * 0xad:         LK421        / LK443, LK444&n; * 0xc9:  LKx01, LK421, LK443 /        LK444&n; * 0xf7:  LKx01,        LK443 /        LK444&n; */
DECL|variable|scancodeRemap
r_int
r_char
id|scancodeRemap
(braket
l_int|256
)braket
op_assign
(brace
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*  0 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*  4 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*  8 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*  c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 10 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 14 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 18 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 1c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 20 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 24 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 28 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 2c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 30 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 34 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 38 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 3c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 40 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 44 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 48 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 4c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 50 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t; &t;ESC&t;&t;F1&t;&t;F2 &t;&t;*/
multiline_comment|/* 54 */
l_int|0
comma
l_int|0
comma
l_int|0x01
comma
l_int|0x02
comma
multiline_comment|/* ----- F3&t;&t;F4&t;&t;F5&t;&t;&t;&t;*/
multiline_comment|/* 58 */
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 5c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 60 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- F6&t;&t;F7&t;&t;F8&t;&t;F9&t;&t;*/
multiline_comment|/* 64 */
l_int|0x06
comma
l_int|0x07
comma
l_int|0x08
comma
l_int|0x09
comma
multiline_comment|/* ----- F10&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 68 */
l_int|0x0a
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 6c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;F11   &t;&t;F12&t;&t;F13/PRNT SCRN&t;*/
multiline_comment|/* 70 */
l_int|0
comma
l_int|0x0b
comma
l_int|0x0c
comma
l_int|0x0d
comma
multiline_comment|/* ----- F14/SCRL LCK&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 74 */
l_int|0x0e
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 78 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- HELP/PAUSE&t;DO&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 7c */
l_int|0x0f
comma
l_int|0x10
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- F17&t;&t;F18&t;&t;F19&t;&t;F20&t;&t;*/
multiline_comment|/* 80 */
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
l_int|0x14
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* 84 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;FIND/INSERT&t;INSERT/HOME&t;*/
multiline_comment|/* 88 */
l_int|0
comma
l_int|0
comma
l_int|0x23
comma
l_int|0x24
comma
multiline_comment|/* ----- REMOVE/PG UP&t;SELECT/DELETE&t;PREVIOUS/END&t;NEXT/PG DN&t;*/
multiline_comment|/* 8c */
l_int|0x25
comma
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3a
comma
multiline_comment|/* ----- &t;&t;&t;&t;KP 0&t;&t;&t;&t;*/
multiline_comment|/* 90 */
l_int|0
comma
l_int|0
comma
l_int|0x6b
comma
l_int|0
comma
multiline_comment|/* ----- KP .&t;&t;KP ENTER&t;KP 1&t;&t;KP 2&t;&t;*/
multiline_comment|/* 94 */
l_int|0x6c
comma
l_int|0x65
comma
l_int|0x62
comma
l_int|0x63
comma
multiline_comment|/* ----- KP 3&t;&t;KP 4&t;&t;KP 5&t;&t;KP 6&t;&t;*/
multiline_comment|/* 98 */
l_int|0x64
comma
l_int|0x4e
comma
l_int|0x4f
comma
l_int|0x50
comma
multiline_comment|/* ----- KP ,/KP +&t;KP 7&t;&t;KP 8&t;&t;KP 9&t;&t;*/
multiline_comment|/* 9c */
l_int|0x51
comma
l_int|0x3b
comma
l_int|0x3c
comma
l_int|0x3d
comma
multiline_comment|/* ----- KP -&t;&t;KP F1/NUM LCK&t;KP F2/KP /&t;KP F3/KP *&t;*/
multiline_comment|/* a0 */
l_int|0x3e
comma
l_int|0x26
comma
l_int|0x27
comma
l_int|0x28
comma
multiline_comment|/* ----- KP F4/KP -&t;&t;&t;&t;&t;LEFT&t;&t;*/
multiline_comment|/* a4 */
l_int|0x29
comma
l_int|0
comma
l_int|0
comma
l_int|0x5f
comma
multiline_comment|/* ----- RIGHT&t;&t;DOWN&t;&t;UP&t;&t;SHIFT Rt&t;*/
multiline_comment|/* a8 */
l_int|0x61
comma
l_int|0x60
comma
l_int|0x4d
comma
l_int|0x5e
comma
multiline_comment|/* ----- ALT&t;&t;COMP Rt/CTRL Rt&t;SHIFT&t;&t;CONTROL&t;&t;*/
multiline_comment|/* ac */
l_int|0
comma
l_int|0
comma
l_int|0x52
comma
l_int|0x3f
comma
multiline_comment|/* ----- CAPS&t;&t;COMPOSE&t;&t;ALT Rt&t;&t;&t;&t;*/
multiline_comment|/* b0 */
l_int|0x40
comma
l_int|0x67
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* b4 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* b8 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ----- BKSP&t;&t;RET&t;&t;TAB&t;&t;`&t;&t;*/
multiline_comment|/* bc */
l_int|0x22
comma
l_int|0x37
comma
l_int|0x2a
comma
l_int|0x15
comma
multiline_comment|/* ----- 1&t;&t;q&t;&t;a&t;&t;z&t;&t;*/
multiline_comment|/* c0 */
l_int|0x16
comma
l_int|0x2b
comma
l_int|0x41
comma
l_int|0x54
comma
multiline_comment|/* ----- &t;&t;2&t;&t;w&t;&t;s&t;&t;*/
multiline_comment|/* c4 */
l_int|0
comma
l_int|0x17
comma
l_int|0x2c
comma
l_int|0x42
comma
multiline_comment|/* ----- x&t;&t;&lt;/&bslash;&bslash;&t;&t;&t;&t;3&t;&t;*/
multiline_comment|/* c8 */
l_int|0x55
comma
l_int|0x53
comma
l_int|0
comma
l_int|0x18
comma
multiline_comment|/* ----- e&t;&t;d&t;&t;c&t;&t;&t;&t;*/
multiline_comment|/* cc */
l_int|0x2d
comma
l_int|0x43
comma
l_int|0x56
comma
l_int|0
comma
multiline_comment|/* ----- 4&t;&t;r&t;&t;f&t;&t;v&t;&t;*/
multiline_comment|/* d0 */
l_int|0x19
comma
l_int|0x2e
comma
l_int|0x44
comma
l_int|0x57
comma
multiline_comment|/* ----- SPACE&t;&t;&t;&t;5&t;&t;t&t;&t;*/
multiline_comment|/* d4 */
l_int|0x68
comma
l_int|0
comma
l_int|0x1a
comma
l_int|0x2f
comma
multiline_comment|/* ----- g&t;&t;b&t;&t;&t;&t;6&t;&t;*/
multiline_comment|/* d8 */
l_int|0x45
comma
l_int|0x58
comma
l_int|0
comma
l_int|0x1b
comma
multiline_comment|/* ----- y&t;&t;h&t;&t;n&t;&t;&t;&t;*/
multiline_comment|/* dc */
l_int|0x30
comma
l_int|0x46
comma
l_int|0x59
comma
l_int|0
comma
multiline_comment|/* ----- 7&t;&t;u&t;&t;j&t;&t;m&t;&t;*/
multiline_comment|/* e0 */
l_int|0x1c
comma
l_int|0x31
comma
l_int|0x47
comma
l_int|0x5a
comma
multiline_comment|/* ----- &t;&t;8&t;&t;i&t;&t;k&t;&t;*/
multiline_comment|/* e4 */
l_int|0
comma
l_int|0x1d
comma
l_int|0x32
comma
l_int|0x48
comma
multiline_comment|/* ----- ,&t;&t;&t;&t;9&t;&t;o&t;&t;*/
multiline_comment|/* e8 */
l_int|0x5b
comma
l_int|0
comma
l_int|0x1e
comma
l_int|0x33
comma
multiline_comment|/* ----- l&t;&t;.&t;&t;&t;&t;0&t;&t;*/
multiline_comment|/* ec */
l_int|0x49
comma
l_int|0x5c
comma
l_int|0
comma
l_int|0x1f
comma
multiline_comment|/* ----- p&t;&t;&t;&t;;&t;&t;/&t;&t;*/
multiline_comment|/* f0 */
l_int|0x34
comma
l_int|0
comma
l_int|0x4a
comma
l_int|0x5d
comma
multiline_comment|/* ----- &t;&t;=&t;&t;]&t;&t;&bslash;&bslash;/&bslash;&squot;&t;&t;*/
multiline_comment|/* f4 */
l_int|0
comma
l_int|0x21
comma
l_int|0x36
comma
l_int|0x4c
comma
multiline_comment|/* ----- &t;&t;-&t;&t;[&t;&t;&bslash;&squot;&t;&t;*/
multiline_comment|/* f8 */
l_int|0
comma
l_int|0x20
comma
l_int|0x35
comma
l_int|0x4b
comma
multiline_comment|/* ----- &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* fc */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
eof
