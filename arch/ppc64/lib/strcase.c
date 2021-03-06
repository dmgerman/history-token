multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/ctype.h&gt;
DECL|function|strcasecmp
r_int
id|strcasecmp
c_func
(paren
r_const
r_char
op_star
id|s1
comma
r_const
r_char
op_star
id|s2
)paren
(brace
r_int
id|c1
comma
id|c2
suffix:semicolon
r_do
(brace
id|c1
op_assign
id|tolower
c_func
(paren
op_star
id|s1
op_increment
)paren
suffix:semicolon
id|c2
op_assign
id|tolower
c_func
(paren
op_star
id|s2
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c1
op_eq
id|c2
op_logical_and
id|c1
op_ne
l_int|0
)paren
suffix:semicolon
r_return
id|c1
op_minus
id|c2
suffix:semicolon
)brace
DECL|function|strncasecmp
r_int
id|strncasecmp
c_func
(paren
r_const
r_char
op_star
id|s1
comma
r_const
r_char
op_star
id|s2
comma
r_int
id|n
)paren
(brace
r_int
id|c1
comma
id|c2
suffix:semicolon
r_do
(brace
id|c1
op_assign
id|tolower
c_func
(paren
op_star
id|s1
op_increment
)paren
suffix:semicolon
id|c2
op_assign
id|tolower
c_func
(paren
op_star
id|s2
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_decrement
id|n
OG
l_int|0
)paren
op_logical_and
id|c1
op_eq
id|c2
op_logical_and
id|c1
op_ne
l_int|0
)paren
suffix:semicolon
r_return
id|c1
op_minus
id|c2
suffix:semicolon
)brace
eof
