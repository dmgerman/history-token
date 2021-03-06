macro_line|#ident &quot;$Id: mktables.c,v 1.2 2002/12/12 22:41:27 hpa Exp $&quot;
multiline_comment|/* ----------------------------------------------------------------------- *&n; *&n; *   Copyright 2002 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 53 Temple Place Ste 330,&n; *   Bostom MA 02111-1307, USA; either version 2 of the License, or&n; *   (at your option) any later version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * mktables.c&n; *&n; * Make RAID-6 tables.  This is a host user space program to be run at&n; * compile time.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;inttypes.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;time.h&gt;
DECL|function|gfmul
r_static
r_uint8
id|gfmul
c_func
(paren
r_uint8
id|a
comma
r_uint8
id|b
)paren
(brace
r_uint8
id|v
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|b
)paren
(brace
r_if
c_cond
(paren
id|b
op_amp
l_int|1
)paren
id|v
op_xor_assign
id|a
suffix:semicolon
id|a
op_assign
(paren
id|a
op_lshift
l_int|1
)paren
op_xor
(paren
id|a
op_amp
l_int|0x80
ques
c_cond
l_int|0x1d
suffix:colon
l_int|0
)paren
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|v
suffix:semicolon
)brace
DECL|function|gfpow
r_static
r_uint8
id|gfpow
c_func
(paren
r_uint8
id|a
comma
r_int
id|b
)paren
(brace
r_uint8
id|v
op_assign
l_int|1
suffix:semicolon
id|b
op_mod_assign
l_int|255
suffix:semicolon
r_if
c_cond
(paren
id|b
OL
l_int|0
)paren
id|b
op_add_assign
l_int|255
suffix:semicolon
r_while
c_loop
(paren
id|b
)paren
(brace
r_if
c_cond
(paren
id|b
op_amp
l_int|1
)paren
id|v
op_assign
id|gfmul
c_func
(paren
id|v
comma
id|a
)paren
suffix:semicolon
id|a
op_assign
id|gfmul
c_func
(paren
id|a
comma
id|a
)paren
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|v
suffix:semicolon
)brace
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
id|j
comma
id|k
suffix:semicolon
r_uint8
id|v
suffix:semicolon
r_uint8
id|exptbl
(braket
l_int|256
)braket
comma
id|invtbl
(braket
l_int|256
)braket
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#include &bslash;&quot;raid6.h&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Compute multiplication table */
id|printf
c_func
(paren
l_string|&quot;&bslash;nconst u8  __attribute__((aligned(256)))&bslash;n&quot;
l_string|&quot;raid6_gfmul[256][256] =&bslash;n&quot;
l_string|&quot;{&bslash;n&quot;
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t{&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|256
suffix:semicolon
id|j
op_add_assign
l_int|8
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t&bslash;t&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|8
suffix:semicolon
id|k
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;0x%02x, &quot;
comma
id|gfmul
c_func
(paren
id|i
comma
id|j
op_plus
id|k
)paren
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t},&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;};&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Compute power-of-2 table (exponent) */
id|v
op_assign
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;nconst u8 __attribute__((aligned(256)))&bslash;n&quot;
l_string|&quot;raid6_gfexp[256] =&bslash;n&quot;
l_string|&quot;{&bslash;n&quot;
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
l_int|256
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|exptbl
(braket
id|i
op_plus
id|j
)braket
op_assign
id|v
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;0x%02x, &quot;
comma
id|v
)paren
suffix:semicolon
id|v
op_assign
id|gfmul
c_func
(paren
id|v
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
l_int|1
)paren
id|v
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* For entry 255, not a real entry */
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;};&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Compute inverse table x^-1 == x^254 */
id|printf
c_func
(paren
l_string|&quot;&bslash;nconst u8 __attribute__((aligned(256)))&bslash;n&quot;
l_string|&quot;raid6_gfinv[256] =&bslash;n&quot;
l_string|&quot;{&bslash;n&quot;
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
l_int|256
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|invtbl
(braket
id|i
op_plus
id|j
)braket
op_assign
id|v
op_assign
id|gfpow
c_func
(paren
id|i
op_plus
id|j
comma
l_int|254
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;0x%02x, &quot;
comma
id|v
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;};&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Compute inv(2^x + 1) (exponent-xor-inverse) table */
id|printf
c_func
(paren
l_string|&quot;&bslash;nconst u8 __attribute__((aligned(256)))&bslash;n&quot;
l_string|&quot;raid6_gfexi[256] =&bslash;n&quot;
l_string|&quot;{&bslash;n&quot;
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
l_int|256
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;0x%02x, &quot;
comma
id|invtbl
(braket
id|exptbl
(braket
id|i
op_plus
id|j
)braket
op_xor
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;};&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
