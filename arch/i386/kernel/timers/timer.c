macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
multiline_comment|/* list of externed timers */
macro_line|#ifndef CONFIG_X86_TSC
r_extern
r_struct
id|timer_opts
id|timer_pit
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|timer_opts
id|timer_tsc
suffix:semicolon
multiline_comment|/* list of timers, ordered by preference */
DECL|variable|timers
r_struct
id|timer_opts
op_star
id|timers
(braket
)braket
op_assign
(brace
op_amp
id|timer_tsc
macro_line|#ifndef CONFIG_X86_TSC
comma
op_amp
id|timer_pit
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|NR_TIMERS
mdefine_line|#define NR_TIMERS (sizeof(timers)/sizeof(timers[0]))
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
suffix:semicolon
multiline_comment|/* find most preferred working timer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_TIMERS
suffix:semicolon
id|i
op_increment
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
)paren
)paren
(brace
r_return
id|timers
(braket
id|i
)braket
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;select_timer: Cannot find a suitable timer&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
