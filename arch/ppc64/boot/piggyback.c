multiline_comment|/*&n; * Copyright 2001 IBM Corp &n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
r_extern
r_int
id|ce_exec_config
(braket
)braket
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_int
id|i
comma
id|cnt
comma
id|pos
comma
id|len
suffix:semicolon
r_int
r_int
id|cksum
comma
id|val
suffix:semicolon
r_int
r_char
op_star
id|lp
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|8192
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s name &lt;in-file &gt;out-file&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;#&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;# Miscellaneous data structures:&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;# WARNING - this file is automatically generated!&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;#&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;&bslash;t.data&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;&bslash;t.globl %s_data&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;%s_data:&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
id|cksum
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|len
op_assign
id|read
c_func
(paren
l_int|0
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OG
l_int|0
)paren
(brace
id|cnt
op_assign
l_int|0
suffix:semicolon
id|lp
op_assign
(paren
r_int
r_char
op_star
)paren
id|buf
suffix:semicolon
id|len
op_assign
(paren
id|len
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Round up to longwords */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|cnt
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;&bslash;t.long&bslash;t&quot;
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;0x%02X%02X%02X%02X&quot;
comma
id|lp
(braket
l_int|0
)braket
comma
id|lp
(braket
l_int|1
)braket
comma
id|lp
(braket
l_int|2
)braket
comma
id|lp
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|val
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|lp
suffix:semicolon
id|cksum
op_xor_assign
id|val
suffix:semicolon
id|lp
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
op_eq
l_int|4
)paren
(brace
id|cnt
op_assign
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot; # %x &bslash;n&quot;
comma
id|pos
op_plus
id|i
op_minus
l_int|12
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cnt
)paren
(brace
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pos
op_add_assign
id|len
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;&bslash;t.globl %s_len&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stdout
comma
l_string|&quot;%s_len:&bslash;t.long&bslash;t0x%x&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
id|pos
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cksum = %x&bslash;n&quot;
comma
id|cksum
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
