macro_line|#include &lt;stdio.h&gt;
DECL|function|print_head
r_void
id|print_head
c_func
(paren
r_void
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;/*&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; * Generated by mk_constants&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; */&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#ifndef __UM_CONSTANTS_H&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define __UM_CONSTANTS_H&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|print_constant_str
r_void
id|print_constant_str
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|value
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define %s &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|name
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|print_constant_int
r_void
id|print_constant_int
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|value
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define %s %d&bslash;n&quot;
comma
id|name
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|print_tail
r_void
id|print_tail
c_func
(paren
r_void
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#endif&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
