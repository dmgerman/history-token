multiline_comment|/* kernel/perfmon.c&n; * PPC 32 Performance Monitor Infrastructure&n; *&n; * Author: Andy Fleming&n; * Copyright (c) 2004 Freescale Semiconductor, Inc&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/prctl.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/xmon.h&gt;
multiline_comment|/* A lock to regulate grabbing the interrupt */
DECL|variable|perfmon_lock
id|spinlock_t
id|perfmon_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#ifdef CONFIG_FSL_BOOKE
DECL|function|dummy_perf
r_static
r_void
id|dummy_perf
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pmgc0
op_assign
id|mfpmr
c_func
(paren
id|PMRN_PMGC0
)paren
suffix:semicolon
id|pmgc0
op_and_assign
op_complement
id|PMGC0_PMIE
suffix:semicolon
id|mtpmr
c_func
(paren
id|PMRN_PMGC0
comma
id|pmgc0
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Ensure exceptions are disabled */
DECL|function|dummy_perf
r_static
r_void
id|dummy_perf
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|mmcr0
op_assign
id|mfspr
c_func
(paren
id|SPRN_MMCR0
)paren
suffix:semicolon
id|mmcr0
op_and_assign
op_complement
id|MMCR0_PMXE
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_MMCR0
comma
id|mmcr0
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|perf_irq
r_void
(paren
op_star
id|perf_irq
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
op_assign
id|dummy_perf
suffix:semicolon
multiline_comment|/* Grab the interrupt, if it&squot;s free.&n; * Returns 0 on success, -1 if the interrupt is taken already */
DECL|function|request_perfmon_irq
r_int
id|request_perfmon_irq
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|perfmon_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|perf_irq
op_eq
id|dummy_perf
)paren
id|perf_irq
op_assign
id|handler
suffix:semicolon
r_else
(brace
id|pr_info
c_func
(paren
l_string|&quot;perfmon irq already handled by %p&bslash;n&quot;
comma
id|perf_irq
)paren
suffix:semicolon
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|perfmon_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|free_perfmon_irq
r_void
id|free_perfmon_irq
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|perfmon_lock
)paren
suffix:semicolon
id|perf_irq
op_assign
id|dummy_perf
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|perfmon_lock
)paren
suffix:semicolon
)brace
DECL|variable|perf_irq
id|EXPORT_SYMBOL
c_func
(paren
id|perf_irq
)paren
suffix:semicolon
DECL|variable|request_perfmon_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_perfmon_irq
)paren
suffix:semicolon
DECL|variable|free_perfmon_irq
id|EXPORT_SYMBOL
c_func
(paren
id|free_perfmon_irq
)paren
suffix:semicolon
eof
