multiline_comment|/* defines for inline arch setup functions */
macro_line|#include &lt;asm/voyager.h&gt;
DECL|function|do_timer_interrupt_hook
r_static
r_inline
r_void
id|do_timer_interrupt_hook
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|voyager_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|do_timer_overflow
r_static
r_inline
r_int
id|do_timer_overflow
c_func
(paren
r_int
id|count
)paren
(brace
multiline_comment|/* can&squot;t read the ISR, just assume 1 tick&n;&t;   overflow */
r_if
c_cond
(paren
id|count
OG
id|LATCH
op_logical_or
id|count
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;VOYAGER PROBLEM: count is %d, latch is %d&bslash;n&quot;
comma
id|count
comma
id|LATCH
)paren
suffix:semicolon
id|count
op_assign
id|LATCH
suffix:semicolon
)brace
id|count
op_sub_assign
id|LATCH
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
eof
