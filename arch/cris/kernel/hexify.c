macro_line|#include &lt;stdio.h&gt;
DECL|function|main
r_void
id|main
c_func
(paren
)paren
(brace
r_int
id|c
suffix:semicolon
r_int
id|comma
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
id|getchar
c_func
(paren
)paren
)paren
op_ne
id|EOF
)paren
(brace
r_int
r_char
id|x
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|comma
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
r_else
id|comma
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|8
)paren
(brace
id|count
op_assign
l_int|0
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;0x%02X&quot;
comma
id|c
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
