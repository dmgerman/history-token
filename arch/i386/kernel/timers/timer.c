macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
multiline_comment|/* list of timers, ordered by preference, NULL terminated */
DECL|variable|timers
r_static
r_struct
id|timer_opts
op_star
id|timers
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_X86_CYCLONE_TIMER
op_amp
id|timer_cyclone
comma
macro_line|#endif
op_amp
id|timer_tsc
comma
op_amp
id|timer_pit
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|clock_override
(braket
l_int|10
)braket
id|__initdata
suffix:semicolon
DECL|function|clock_setup
r_static
r_int
id|__init
id|clock_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|str
)paren
id|strlcpy
c_func
(paren
id|clock_override
comma
id|str
comma
r_sizeof
(paren
id|clock_override
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;clock=&quot;
comma
id|clock_setup
)paren
suffix:semicolon
multiline_comment|/* iterates through the list of timers, returning the first &n; * one that initializes successfully.&n; */
DECL|function|select_timer
r_struct
id|timer_opts
op_star
id|select_timer
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* find most preferred working timer */
r_while
c_loop
(paren
id|timers
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|timers
(braket
id|i
)braket
op_member_access_from_pointer
id|init
)paren
r_if
c_cond
(paren
id|timers
(braket
id|i
)braket
op_member_access_from_pointer
id|init
c_func
(paren
id|clock_override
)paren
op_eq
l_int|0
)paren
r_return
id|timers
(braket
id|i
)braket
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;select_timer: Cannot find a suitable timer&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
eof
