multiline_comment|/*&n; *  arch/ppc64/lib/e2a.c&n; *&n; *  EBCDIC to ASCII conversion&n; *&n; * This function moved here from arch/ppc64/kernel/viopath.c&n; *&n; * (C) Copyright 2000-2004 IBM Corporation&n; *&n; * This program is free software;  you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) anyu later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
DECL|function|e2a
r_int
r_char
id|e2a
c_func
(paren
r_int
r_char
id|x
)paren
(brace
r_switch
c_cond
(paren
id|x
)paren
(brace
r_case
l_int|0xF0
suffix:colon
r_return
l_char|&squot;0&squot;
suffix:semicolon
r_case
l_int|0xF1
suffix:colon
r_return
l_char|&squot;1&squot;
suffix:semicolon
r_case
l_int|0xF2
suffix:colon
r_return
l_char|&squot;2&squot;
suffix:semicolon
r_case
l_int|0xF3
suffix:colon
r_return
l_char|&squot;3&squot;
suffix:semicolon
r_case
l_int|0xF4
suffix:colon
r_return
l_char|&squot;4&squot;
suffix:semicolon
r_case
l_int|0xF5
suffix:colon
r_return
l_char|&squot;5&squot;
suffix:semicolon
r_case
l_int|0xF6
suffix:colon
r_return
l_char|&squot;6&squot;
suffix:semicolon
r_case
l_int|0xF7
suffix:colon
r_return
l_char|&squot;7&squot;
suffix:semicolon
r_case
l_int|0xF8
suffix:colon
r_return
l_char|&squot;8&squot;
suffix:semicolon
r_case
l_int|0xF9
suffix:colon
r_return
l_char|&squot;9&squot;
suffix:semicolon
r_case
l_int|0xC1
suffix:colon
r_return
l_char|&squot;A&squot;
suffix:semicolon
r_case
l_int|0xC2
suffix:colon
r_return
l_char|&squot;B&squot;
suffix:semicolon
r_case
l_int|0xC3
suffix:colon
r_return
l_char|&squot;C&squot;
suffix:semicolon
r_case
l_int|0xC4
suffix:colon
r_return
l_char|&squot;D&squot;
suffix:semicolon
r_case
l_int|0xC5
suffix:colon
r_return
l_char|&squot;E&squot;
suffix:semicolon
r_case
l_int|0xC6
suffix:colon
r_return
l_char|&squot;F&squot;
suffix:semicolon
r_case
l_int|0xC7
suffix:colon
r_return
l_char|&squot;G&squot;
suffix:semicolon
r_case
l_int|0xC8
suffix:colon
r_return
l_char|&squot;H&squot;
suffix:semicolon
r_case
l_int|0xC9
suffix:colon
r_return
l_char|&squot;I&squot;
suffix:semicolon
r_case
l_int|0xD1
suffix:colon
r_return
l_char|&squot;J&squot;
suffix:semicolon
r_case
l_int|0xD2
suffix:colon
r_return
l_char|&squot;K&squot;
suffix:semicolon
r_case
l_int|0xD3
suffix:colon
r_return
l_char|&squot;L&squot;
suffix:semicolon
r_case
l_int|0xD4
suffix:colon
r_return
l_char|&squot;M&squot;
suffix:semicolon
r_case
l_int|0xD5
suffix:colon
r_return
l_char|&squot;N&squot;
suffix:semicolon
r_case
l_int|0xD6
suffix:colon
r_return
l_char|&squot;O&squot;
suffix:semicolon
r_case
l_int|0xD7
suffix:colon
r_return
l_char|&squot;P&squot;
suffix:semicolon
r_case
l_int|0xD8
suffix:colon
r_return
l_char|&squot;Q&squot;
suffix:semicolon
r_case
l_int|0xD9
suffix:colon
r_return
l_char|&squot;R&squot;
suffix:semicolon
r_case
l_int|0xE2
suffix:colon
r_return
l_char|&squot;S&squot;
suffix:semicolon
r_case
l_int|0xE3
suffix:colon
r_return
l_char|&squot;T&squot;
suffix:semicolon
r_case
l_int|0xE4
suffix:colon
r_return
l_char|&squot;U&squot;
suffix:semicolon
r_case
l_int|0xE5
suffix:colon
r_return
l_char|&squot;V&squot;
suffix:semicolon
r_case
l_int|0xE6
suffix:colon
r_return
l_char|&squot;W&squot;
suffix:semicolon
r_case
l_int|0xE7
suffix:colon
r_return
l_char|&squot;X&squot;
suffix:semicolon
r_case
l_int|0xE8
suffix:colon
r_return
l_char|&squot;Y&squot;
suffix:semicolon
r_case
l_int|0xE9
suffix:colon
r_return
l_char|&squot;Z&squot;
suffix:semicolon
)brace
r_return
l_char|&squot; &squot;
suffix:semicolon
)brace
DECL|variable|e2a
id|EXPORT_SYMBOL
c_func
(paren
id|e2a
)paren
suffix:semicolon
eof
