multiline_comment|/*&n; * FR-V MB93093 Power Management Routines&n; *&n; * Copyright (c) 2004 Red Hat, Inc.&n; *&n; * Written by: msalter@redhat.com&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mb86943a.h&gt;
macro_line|#include &quot;local.h&quot;
DECL|variable|imask
r_static
r_int
r_int
id|imask
suffix:semicolon
multiline_comment|/*&n; * Setup interrupt masks, etc to enable wakeup by power switch&n; */
DECL|function|mb93093_power_switch_setup
r_static
r_void
id|mb93093_power_switch_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* mask all but FPGA interrupt sources. */
id|imask
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfeff9820
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfeff9820
op_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|IRQ_XIRQ2_LEVEL
op_plus
l_int|16
)paren
)paren
op_amp
l_int|0xfffe0000
suffix:semicolon
)brace
multiline_comment|/*&n; * Cleanup interrupt masks, etc after wakeup by power switch&n; */
DECL|function|mb93093_power_switch_cleanup
r_static
r_void
id|mb93093_power_switch_cleanup
c_func
(paren
r_void
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfeff9820
op_assign
id|imask
suffix:semicolon
)brace
multiline_comment|/*&n; * Return non-zero if wakeup irq was caused by power switch&n; */
DECL|function|mb93093_power_switch_check
r_static
r_int
id|mb93093_power_switch_check
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize power interface&n; */
DECL|function|mb93093_pm_init
r_static
r_int
id|__init
id|mb93093_pm_init
c_func
(paren
r_void
)paren
(brace
id|__power_switch_wake_setup
op_assign
id|mb93093_power_switch_setup
suffix:semicolon
id|__power_switch_wake_check
op_assign
id|mb93093_power_switch_check
suffix:semicolon
id|__power_switch_wake_cleanup
op_assign
id|mb93093_power_switch_cleanup
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mb93093_pm_init
id|__initcall
c_func
(paren
id|mb93093_pm_init
)paren
suffix:semicolon
eof
