macro_line|#include &lt;linux/string.h&gt;
DECL|function|strstr
r_char
op_star
id|strstr
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
)paren
(brace
r_int
id|d0
comma
id|d1
suffix:semicolon
r_register
r_char
op_star
id|__res
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl %6,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;repne&bslash;n&bslash;t&quot;
l_string|&quot;scasb&bslash;n&bslash;t&quot;
l_string|&quot;notl %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;decl %%ecx&bslash;n&bslash;t&quot;
multiline_comment|/* NOTE! This also sets Z if searchstring=&squot;&squot; */
l_string|&quot;movl %%ecx,%%edx&bslash;n&quot;
l_string|&quot;1:&bslash;tmovl %6,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movl %%esi,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;repe&bslash;n&bslash;t&quot;
l_string|&quot;cmpsb&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
multiline_comment|/* also works for empty string, see above */
l_string|&quot;xchgl %%eax,%%esi&bslash;n&bslash;t&quot;
l_string|&quot;incl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;cmpb $0,-1(%%eax)&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&bslash;t&quot;
l_string|&quot;xorl %%eax,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|__res
)paren
comma
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d1
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;1&quot;
(paren
l_int|0xffffffff
)paren
comma
l_string|&quot;2&quot;
(paren
id|cs
)paren
comma
l_string|&quot;g&quot;
(paren
id|ct
)paren
suffix:colon
l_string|&quot;dx&quot;
comma
l_string|&quot;di&quot;
)paren
suffix:semicolon
r_return
id|__res
suffix:semicolon
)brace
eof
