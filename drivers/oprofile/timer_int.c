multiline_comment|/**&n; * @file timer_int.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|function|timer_notify
r_static
r_int
id|timer_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|data
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|eip
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|oprofile_add_sample
c_func
(paren
id|eip
comma
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
comma
l_int|0
comma
id|cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|timer_notifier
r_static
r_struct
id|notifier_block
id|timer_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|timer_notify
comma
)brace
suffix:semicolon
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
id|register_profile_notifier
c_func
(paren
op_amp
id|timer_notifier
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
id|unregister_profile_notifier
c_func
(paren
op_amp
id|timer_notifier
)paren
suffix:semicolon
)brace
DECL|variable|timer_ops
r_static
r_struct
id|oprofile_operations
id|timer_ops
op_assign
(brace
dot
id|start
op_assign
id|timer_start
comma
dot
id|stop
op_assign
id|timer_stop
comma
dot
id|cpu_type
op_assign
l_string|&quot;timer&quot;
)brace
suffix:semicolon
DECL|function|timer_init
r_void
id|__init
id|timer_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
(brace
op_star
id|ops
op_assign
op_amp
id|timer_ops
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using timer interrupt.&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
