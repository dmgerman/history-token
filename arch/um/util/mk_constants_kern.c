macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/stringify.h&quot;
macro_line|#include &quot;asm/page.h&quot;
r_extern
r_void
id|print_head
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|print_tail
c_func
(paren
r_void
)paren
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
op_star
id|argv
)paren
(brace
id|print_head
c_func
(paren
)paren
suffix:semicolon
id|print_constant_int
c_func
(paren
l_string|&quot;UM_KERN_PAGE_SIZE&quot;
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_EMERG&quot;
comma
id|KERN_EMERG
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_ALERT&quot;
comma
id|KERN_ALERT
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_CRIT&quot;
comma
id|KERN_CRIT
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_ERR&quot;
comma
id|KERN_ERR
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_WARNING&quot;
comma
id|KERN_WARNING
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_NOTICE&quot;
comma
id|KERN_NOTICE
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_INFO&quot;
comma
id|KERN_INFO
)paren
suffix:semicolon
id|print_constant_str
c_func
(paren
l_string|&quot;UM_KERN_DEBUG&quot;
comma
id|KERN_DEBUG
)paren
suffix:semicolon
id|print_tail
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
