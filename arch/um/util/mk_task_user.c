macro_line|#include &lt;stdio.h&gt;
DECL|function|print
r_void
id|print
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|type
comma
r_int
id|offset
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define %s(task) *((%s *) &amp;(((char *) (task))[%d]))&bslash;n&quot;
comma
id|name
comma
id|type
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|print_ptr
r_void
id|print_ptr
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|type
comma
r_int
id|offset
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;#define %s(task) ((%s *) &amp;(((char *) (task))[%d]))&bslash;n&quot;
comma
id|name
comma
id|type
comma
id|offset
)paren
suffix:semicolon
)brace
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
l_string|&quot; * Generated by mk_task&bslash;n&quot;
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
l_string|&quot;#ifndef __TASK_H&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;#define __TASK_H&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
