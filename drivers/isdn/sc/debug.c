multiline_comment|/* $Id: debug.c,v 1.5.6.1 2001/09/23 22:24:59 kai Exp $&n; *&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|variable|dbg_level
r_int
id|dbg_level
op_assign
l_int|0
suffix:semicolon
DECL|variable|dbg_funcname
r_static
r_char
id|dbg_funcname
(braket
l_int|255
)braket
suffix:semicolon
DECL|function|dbg_endfunc
r_void
id|dbg_endfunc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|dbg_level
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&lt;-- Leaving function %s&bslash;n&quot;
comma
id|dbg_funcname
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dbg_funcname
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|dbg_func
r_void
id|dbg_func
c_func
(paren
r_char
op_star
id|func
)paren
(brace
id|strcpy
c_func
(paren
id|dbg_funcname
comma
id|func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dbg_level
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;--&gt; Entering function %s&bslash;n&quot;
comma
id|dbg_funcname
)paren
suffix:semicolon
)brace
)brace
DECL|function|pullphone
r_inline
r_void
id|pullphone
c_func
(paren
r_char
op_star
id|dn
comma
r_char
op_star
id|str
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|dn
(braket
id|i
)braket
op_ne
l_char|&squot;,&squot;
)paren
(brace
id|str
(braket
id|i
)braket
op_assign
id|dn
(braket
id|i
)braket
comma
id|i
op_increment
suffix:semicolon
)brace
id|str
(braket
id|i
)braket
op_assign
l_int|0x0
suffix:semicolon
)brace
eof
