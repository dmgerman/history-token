multiline_comment|/*&n; * Idle daemon for PowerPC.  Idle daemon will handle any action&n; * that needs to be taken when the system becomes idle.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu).  Subsequently hacked&n; * on by Tom Rini, Armin Kuster, Paul Mackerras and others.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_void
(paren
op_star
id|powersave
)paren
(paren
r_void
)paren
suffix:semicolon
id|powersave
op_assign
id|ppc_md.power_save
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|powersave
op_ne
l_int|NULL
)paren
id|powersave
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
macro_line|#ifdef CONFIG_SMP
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
macro_line|#else
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The body of the idle task.&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
r_if
c_cond
(paren
id|ppc_md.idle
op_ne
l_int|NULL
)paren
id|ppc_md
dot
id|idle
c_func
(paren
)paren
suffix:semicolon
r_else
id|default_idle
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SYSCTL) &amp;&amp; defined(CONFIG_6xx)
multiline_comment|/*&n; * Register the sysctl to set/clear powersave_nap.&n; */
r_extern
r_int
r_int
id|powersave_nap
suffix:semicolon
DECL|variable|powersave_nap_ctl_table
r_static
id|ctl_table
id|powersave_nap_ctl_table
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|powersave_nap_sysctl_root
r_static
id|ctl_table
id|powersave_nap_sysctl_root
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
l_string|&quot;kernel&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0755
comma
id|powersave_nap_ctl_table
comma
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|register_powersave_nap_sysctl
id|register_powersave_nap_sysctl
c_func
(paren
r_void
)paren
(brace
id|register_sysctl_table
c_func
(paren
id|powersave_nap_sysctl_root
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|register_powersave_nap_sysctl
id|__initcall
c_func
(paren
id|register_powersave_nap_sysctl
)paren
suffix:semicolon
macro_line|#endif
eof
