multiline_comment|/* &n; * arch/sh/boards/saturn/smp.c&n; *&n; * SMP support for the Sega Saturn.&n; *&n; * Copyright (c) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/saturn/smpc.h&gt;
r_extern
r_void
id|start_secondary
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__smp_send_ipi
r_void
id|__smp_send_ipi
c_func
(paren
r_int
r_int
id|cpu
comma
r_int
r_int
id|action
)paren
(brace
multiline_comment|/* Nothing here yet .. */
)brace
DECL|function|__smp_probe_cpus
r_int
r_int
id|__smp_probe_cpus
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * This is just a straightforward master/slave configuration,&n;&t; * and probing isn&squot;t really supported..&n;&t; */
r_return
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n; * We&squot;re only allowed to do byte-access to SMPC registers. In&n; * addition to which, we treat them as write-only, since&n; * reading from them will return undefined data.&n; */
DECL|function|smpc_slave_stop
r_static
r_inline
r_void
id|smpc_slave_stop
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
id|smpc_barrier
c_func
(paren
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|SMPC_STATUS
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|SMPC_CMD_SSHOFF
comma
id|SMPC_COMMAND
)paren
suffix:semicolon
id|smpc_barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smpc_slave_start
r_static
r_inline
r_void
id|smpc_slave_start
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
id|ctrl_outb
c_func
(paren
l_int|1
comma
id|SMPC_STATUS
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
id|SMPC_CMD_SSHON
comma
id|SMPC_COMMAND
)paren
suffix:semicolon
id|smpc_barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__smp_slave_init
r_void
id|__smp_slave_init
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_register
r_int
r_int
id|vbr
suffix:semicolon
r_void
op_star
op_star
id|entry
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;stc vbr, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|vbr
)paren
)paren
suffix:semicolon
id|entry
op_assign
(paren
r_void
op_star
op_star
)paren
(paren
id|vbr
op_plus
l_int|0x310
op_plus
l_int|0x94
)paren
suffix:semicolon
id|smpc_slave_stop
c_func
(paren
id|cpu
)paren
suffix:semicolon
op_star
(paren
r_void
op_star
op_star
)paren
id|entry
op_assign
(paren
r_void
op_star
)paren
id|start_secondary
suffix:semicolon
id|smpc_slave_start
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
eof
