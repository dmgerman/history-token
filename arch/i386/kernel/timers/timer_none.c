macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
DECL|function|init_none
r_static
r_int
id|__init
id|init_none
c_func
(paren
r_char
op_star
id|override
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mark_offset_none
r_static
r_void
id|mark_offset_none
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing needed */
)brace
DECL|function|get_offset_none
r_static
r_int
r_int
id|get_offset_none
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|monotonic_clock_none
r_static
r_int
r_int
r_int
id|monotonic_clock_none
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|delay_none
r_static
r_void
id|delay_none
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
r_int
id|d0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 2f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %0&bslash;n&bslash;tjns 2b&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|d0
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* tsc timer_opts struct */
DECL|variable|timer_none
r_struct
id|timer_opts
id|timer_none
op_assign
(brace
dot
id|init
op_assign
id|init_none
comma
dot
id|mark_offset
op_assign
id|mark_offset_none
comma
dot
id|get_offset
op_assign
id|get_offset_none
comma
dot
id|monotonic_clock
op_assign
id|monotonic_clock_none
comma
dot
id|delay
op_assign
id|delay_none
comma
)brace
suffix:semicolon
eof
