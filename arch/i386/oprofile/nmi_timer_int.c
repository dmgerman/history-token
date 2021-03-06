multiline_comment|/**&n; * @file nmi_timer_int.c&n; *&n; * @remark Copyright 2003 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author Zwane Mwaikambo &lt;zwane@linuxpower.ca&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|function|nmi_timer_callback
r_static
r_int
id|nmi_timer_callback
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|cpu
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
l_int|1
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
id|disable_timer_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
id|set_nmi_callback
c_func
(paren
id|nmi_timer_callback
)paren
suffix:semicolon
r_return
l_int|0
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
id|enable_timer_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
id|unset_nmi_callback
c_func
(paren
)paren
suffix:semicolon
id|synchronize_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|nmi_timer_init
r_int
id|__init
id|nmi_timer_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
id|ops
)paren
(brace
r_extern
r_int
id|nmi_active
suffix:semicolon
r_if
c_cond
(paren
id|nmi_active
op_le
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using NMI timer interrupt.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
