multiline_comment|/**&n; * @file timer_int.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &quot;oprof.h&quot;
DECL|function|timer_notify
r_static
r_int
id|timer_notify
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|oprofile_add_sample
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|timer_start
r_static
r_int
id|timer_start
c_func
(paren
r_void
)paren
(brace
r_return
id|register_timer_hook
c_func
(paren
id|timer_notify
)paren
suffix:semicolon
)brace
DECL|function|timer_stop
r_static
r_void
id|timer_stop
c_func
(paren
r_void
)paren
(brace
id|unregister_timer_hook
c_func
(paren
id|timer_notify
)paren
suffix:semicolon
)brace
DECL|function|oprofile_timer_init
r_void
id|__init
id|oprofile_timer_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
id|ops
)paren
(brace
id|ops-&gt;start
op_assign
id|timer_start
suffix:semicolon
id|ops-&gt;stop
op_assign
id|timer_stop
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
l_string|&quot;timer&quot;
suffix:semicolon
)brace
eof
