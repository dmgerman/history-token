macro_line|#include &lt;asm/timer.h&gt;
DECL|function|init_none
r_static
r_int
id|init_none
c_func
(paren
r_void
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
)brace
suffix:semicolon
eof
