multiline_comment|/* CPU control.&n; * (C) 2001 Rusty Russell&n; * This code is licenced under the GPL.&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/* This protects CPUs going up and down... */
DECL|variable|cpucontrol
id|DECLARE_MUTEX
c_func
(paren
id|cpucontrol
)paren
suffix:semicolon
DECL|variable|cpu_chain
r_static
r_struct
id|notifier_block
op_star
id|cpu_chain
suffix:semicolon
multiline_comment|/* Need to know about CPUs going up/down? */
DECL|function|register_cpu_notifier
r_int
id|register_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
r_return
id|notifier_chain_register
c_func
(paren
op_amp
id|cpu_chain
comma
id|nb
)paren
suffix:semicolon
)brace
DECL|function|unregister_cpu_notifier
r_void
id|unregister_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
id|notifier_chain_unregister
c_func
(paren
op_amp
id|cpu_chain
comma
id|nb
)paren
suffix:semicolon
)brace
DECL|function|cpu_up
r_int
id|__devinit
id|cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_int
id|ret
suffix:semicolon
r_void
op_star
id|hcpu
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|cpu
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|down_interruptible
c_func
(paren
op_amp
id|cpucontrol
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|notifier_call_chain
c_func
(paren
op_amp
id|cpu_chain
comma
id|CPU_UP_PREPARE
comma
id|hcpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|NOTIFY_BAD
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: attempt to bring up CPU %u failed&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|cpu
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_notify
suffix:semicolon
)brace
multiline_comment|/* Arch-specific enabling code. */
id|ret
op_assign
id|__cpu_up
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_goto
id|out_notify
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Now call notifier in preparation. */
id|printk
c_func
(paren
l_string|&quot;CPU %u IS NOW UP!&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|notifier_call_chain
c_func
(paren
op_amp
id|cpu_chain
comma
id|CPU_ONLINE
comma
id|hcpu
)paren
suffix:semicolon
id|out_notify
suffix:colon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
id|notifier_call_chain
c_func
(paren
op_amp
id|cpu_chain
comma
id|CPU_UP_CANCELED
comma
id|hcpu
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|cpucontrol
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
