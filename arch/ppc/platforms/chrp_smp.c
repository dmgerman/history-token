multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * Smp support for CHRP machines.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great&n; * deal of code from the sparc and intel versions.&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
r_extern
r_int
r_int
id|smp_chrp_cpu_nr
suffix:semicolon
r_static
r_int
id|__init
DECL|function|smp_chrp_probe
id|smp_chrp_probe
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smp_chrp_cpu_nr
OG
l_int|1
)paren
id|openpic_request_IPIs
c_func
(paren
)paren
suffix:semicolon
r_return
id|smp_chrp_cpu_nr
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|smp_chrp_kick_cpu
id|smp_chrp_kick_cpu
c_func
(paren
r_int
id|nr
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|KERNELBASE
op_assign
id|nr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;dcbf 0,%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|KERNELBASE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|smp_chrp_setup_cpu
id|smp_chrp_setup_cpu
c_func
(paren
r_int
id|cpu_nr
)paren
(brace
r_static
id|atomic_t
id|ready
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_static
r_volatile
r_int
id|frozen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpu_nr
op_eq
l_int|0
)paren
(brace
multiline_comment|/* wait for all the others */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|ready
)paren
OL
id|smp_num_cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ready
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* freeze the timebase */
id|call_rtas
c_func
(paren
l_string|&quot;freeze-time-base&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|frozen
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* XXX assumes this is not a 601 */
id|set_tb
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|last_jiffy_stamp
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|ready
)paren
OL
id|smp_num_cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* thaw the timebase again */
id|call_rtas
c_func
(paren
l_string|&quot;thaw-time-base&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|frozen
op_assign
l_int|0
suffix:semicolon
id|smp_tb_synchronized
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|atomic_inc
c_func
(paren
op_amp
id|ready
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|frozen
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|set_tb
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|last_jiffy_stamp
c_func
(paren
l_int|0
)paren
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|ready
)paren
suffix:semicolon
r_while
c_loop
(paren
id|frozen
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|OpenPIC_Addr
)paren
id|do_openpic_setup_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* CHRP with openpic */
DECL|variable|__chrpdata
r_struct
id|smp_ops_t
id|chrp_smp_ops
id|__chrpdata
op_assign
(brace
id|smp_openpic_message_pass
comma
id|smp_chrp_probe
comma
id|smp_chrp_kick_cpu
comma
id|smp_chrp_setup_cpu
comma
)brace
suffix:semicolon
eof