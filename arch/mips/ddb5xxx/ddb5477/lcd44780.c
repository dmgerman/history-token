multiline_comment|/*&n; * lcd44780.c&n; * Simple &quot;driver&quot; for a memory-mapped 44780-style LCD display.&n; *&n; * Copyright 2001 Bradley D. LaRonde &lt;brad@ltc.com&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
DECL|macro|LCD44780_COMMAND
mdefine_line|#define LCD44780_COMMAND   ((volatile unsigned char *)0xbe020000)
DECL|macro|LCD44780_DATA
mdefine_line|#define LCD44780_DATA      ((volatile unsigned char *)0xbe020001)
DECL|macro|LCD44780_4BIT_1LINE
mdefine_line|#define LCD44780_4BIT_1LINE        0x20
DECL|macro|LCD44780_4BIT_2LINE
mdefine_line|#define LCD44780_4BIT_2LINE        0x28
DECL|macro|LCD44780_8BIT_1LINE
mdefine_line|#define LCD44780_8BIT_1LINE        0x30
DECL|macro|LCD44780_8BIT_2LINE
mdefine_line|#define LCD44780_8BIT_2LINE        0x38
DECL|macro|LCD44780_MODE_DEC
mdefine_line|#define LCD44780_MODE_DEC          0x04
DECL|macro|LCD44780_MODE_DEC_SHIFT
mdefine_line|#define LCD44780_MODE_DEC_SHIFT    0x05
DECL|macro|LCD44780_MODE_INC
mdefine_line|#define LCD44780_MODE_INC          0x06
DECL|macro|LCD44780_MODE_INC_SHIFT
mdefine_line|#define LCD44780_MODE_INC_SHIFT    0x07
DECL|macro|LCD44780_SCROLL_LEFT
mdefine_line|#define LCD44780_SCROLL_LEFT       0x18
DECL|macro|LCD44780_SCROLL_RIGHT
mdefine_line|#define LCD44780_SCROLL_RIGHT      0x1e
DECL|macro|LCD44780_CURSOR_UNDERLINE
mdefine_line|#define LCD44780_CURSOR_UNDERLINE  0x0e
DECL|macro|LCD44780_CURSOR_BLOCK
mdefine_line|#define LCD44780_CURSOR_BLOCK      0x0f
DECL|macro|LCD44780_CURSOR_OFF
mdefine_line|#define LCD44780_CURSOR_OFF        0x0c
DECL|macro|LCD44780_CLEAR
mdefine_line|#define LCD44780_CLEAR             0x01
DECL|macro|LCD44780_BLANK
mdefine_line|#define LCD44780_BLANK             0x08
DECL|macro|LCD44780_RESTORE
mdefine_line|#define LCD44780_RESTORE           0x0c  
singleline_comment|// Same as CURSOR_OFF
DECL|macro|LCD44780_HOME
mdefine_line|#define LCD44780_HOME              0x02
DECL|macro|LCD44780_LEFT
mdefine_line|#define LCD44780_LEFT              0x10
DECL|macro|LCD44780_RIGHT
mdefine_line|#define LCD44780_RIGHT             0x14
DECL|function|lcd44780_wait
r_void
id|lcd44780_wait
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
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
l_int|400
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|10000
suffix:semicolon
id|j
op_increment
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|lcd44780_command
r_void
id|lcd44780_command
c_func
(paren
r_int
r_char
id|c
)paren
(brace
op_star
id|LCD44780_COMMAND
op_assign
id|c
suffix:semicolon
id|lcd44780_wait
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|lcd44780_data
r_void
id|lcd44780_data
c_func
(paren
r_int
r_char
id|c
)paren
(brace
op_star
id|LCD44780_DATA
op_assign
id|c
suffix:semicolon
id|lcd44780_wait
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|lcd44780_puts
r_void
id|lcd44780_puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|pos
op_assign
l_int|0
suffix:semicolon
id|lcd44780_command
c_func
(paren
id|LCD44780_CLEAR
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
)paren
(brace
id|lcd44780_data
c_func
(paren
op_star
id|s
)paren
suffix:semicolon
id|s
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_eq
l_int|8
)paren
(brace
multiline_comment|/* We must write 32 of spaces to get cursor to 2nd line */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|32
suffix:semicolon
id|j
op_increment
)paren
(brace
id|lcd44780_data
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pos
op_eq
l_int|16
)paren
(brace
multiline_comment|/* We have filled all 16 character positions, so stop&n;&t;&t;     outputing data */
r_break
suffix:semicolon
)brace
)brace
macro_line|#ifdef LCD44780_PUTS_PAUSE
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|2000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lcd44780_wait
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|lcd44780_init
r_void
id|lcd44780_init
c_func
(paren
r_void
)paren
(brace
singleline_comment|// The display on the RockHopper is physically a single
singleline_comment|// 16 char line (two 8 char lines concatenated).  bdl
id|lcd44780_command
c_func
(paren
id|LCD44780_8BIT_2LINE
)paren
suffix:semicolon
id|lcd44780_command
c_func
(paren
id|LCD44780_MODE_INC
)paren
suffix:semicolon
id|lcd44780_command
c_func
(paren
id|LCD44780_CURSOR_BLOCK
)paren
suffix:semicolon
id|lcd44780_command
c_func
(paren
id|LCD44780_CLEAR
)paren
suffix:semicolon
)brace
eof
