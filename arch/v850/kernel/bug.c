multiline_comment|/*&n; * arch/v850/kernel/bug.c -- Bug reporting functions&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/current.h&gt;
multiline_comment|/* We should use __builtin_return_address, but it doesn&squot;t work in gcc-2.90&n;   (which is currently our standard compiler on the v850).  */
DECL|macro|ret_addr
mdefine_line|#define ret_addr() ({ register u32 lp asm (&quot;lp&quot;); lp; })
DECL|macro|stack_addr
mdefine_line|#define stack_addr() ({ register u32 sp asm (&quot;sp&quot;); sp; })
DECL|function|__bug
r_void
id|__bug
(paren
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;kernel BUG at PC 0x%x (SP ~0x%x)!&bslash;n&quot;
comma
id|ret_addr
c_func
(paren
)paren
op_minus
l_int|4
comma
multiline_comment|/* - 4 for `jarl&squot; */
id|stack_addr
c_func
(paren
)paren
)paren
suffix:semicolon
id|machine_halt
(paren
)paren
suffix:semicolon
)brace
DECL|function|bad_trap
r_int
id|bad_trap
(paren
r_int
id|trap_num
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;unimplemented trap %d called at 0x%08lx, pid %d!&bslash;n&quot;
comma
id|trap_num
comma
id|regs-&gt;pc
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|debug_trap
r_int
id|debug_trap
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;debug trap at 0x%08lx!&bslash;n&quot;
comma
id|regs-&gt;pc
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_RESET_GUARD
DECL|function|unexpected_reset
r_void
id|unexpected_reset
(paren
r_int
r_int
id|ret_addr
comma
r_int
r_int
id|kmode
comma
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|sp
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;unexpected reset in %s mode, pid %d&quot;
l_string|&quot; (ret_addr = 0x%lx, sp = 0x%lx)&bslash;n&quot;
comma
id|kmode
ques
c_cond
l_string|&quot;kernel&quot;
suffix:colon
l_string|&quot;user&quot;
comma
id|task
ques
c_cond
id|task-&gt;pid
suffix:colon
op_minus
l_int|1
comma
id|ret_addr
comma
id|sp
)paren
suffix:semicolon
id|machine_halt
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_RESET_GUARD */
eof
