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
macro_line|#ifdef CONFIG_SMP
r_else
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
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
)brace
macro_line|#endif
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
r_int
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
r_return
l_int|0
suffix:semicolon
)brace
eof
