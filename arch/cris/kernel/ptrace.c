multiline_comment|/*&n; *  linux/arch/cris/kernel/ptrace.c&n; *&n; * Parts taken from the m68k port.&n; * &n; * Copyright (c) 2000, 2001, 2002 Axis Communications AB&n; *&n; * Authors:   Bjorn Wesen&n; *&n; * $Log: ptrace.c,v $&n; * Revision 1.9  2003/07/04 12:56:11  tobiasa&n; * Moved arch-specific code to arch-specific files.&n; *&n; * Revision 1.8  2003/04/09 05:20:47  starvik&n; * Merge of Linux 2.5.67&n; *&n; * Revision 1.7  2002/11/27 08:42:34  starvik&n; * Argument to user_regs() is thread_info*&n; *&n; * Revision 1.6  2002/11/20 11:56:11  starvik&n; * Merge of Linux 2.5.48&n; *&n; * Revision 1.5  2002/11/18 07:41:19  starvik&n; * Removed warning&n; *&n; * Revision 1.4  2002/11/11 12:47:28  starvik&n; * SYSCALL_TRACE has been moved to thread flags&n; *&n; * Revision 1.3  2002/02/05 15:37:18  bjornw&n; * * Add do_notify_resume (replaces do_signal in the callchain)&n; * * syscall_trace is now do_syscall_trace&n; * * current-&gt;ptrace flag PT_TRACESYS -&gt; PT_SYSCALLTRACE&n; * * Keep track of the current-&gt;work.syscall_trace counter&n; *&n; * Revision 1.2  2001/12/18 13:35:20  bjornw&n; * Applied the 2.4.13-&gt;2.4.16 CRIS patch to 2.5.1 (is a copy of 2.4.15).&n; *&n; * Revision 1.8  2001/11/12 18:26:21  pkj&n; * Fixed compiler warnings.&n; *&n; * Revision 1.7  2001/09/26 11:53:49  bjornw&n; * PTRACE_DETACH works more simple in 2.4.10&n; *&n; * Revision 1.6  2001/07/25 16:08:47  bjornw&n; * PTRACE_ATTACH bulk moved into arch-independent code in 2.4.7&n; *&n; * Revision 1.5  2001/03/26 14:24:28  orjanf&n; * * Changed loop condition.&n; * * Added comment documenting non-standard ptrace behaviour.&n; *&n; * Revision 1.4  2001/03/20 19:44:41  bjornw&n; * Use the user_regs macro instead of thread.esp0&n; *&n; * Revision 1.3  2000/12/18 23:45:25  bjornw&n; * Linux/CRIS first version&n; *&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * Get contents of register REGNO in task TASK.&n; */
DECL|function|get_reg
r_inline
r_int
id|get_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
)paren
(brace
multiline_comment|/* USP is a special case, it&squot;s not in the pt_regs struct but&n;&t; * in the tasks thread struct&n;&t; */
r_if
c_cond
(paren
id|regno
op_eq
id|PT_USP
)paren
r_return
id|task-&gt;thread.usp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
id|PT_MAX
)paren
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|user_regs
c_func
(paren
id|task-&gt;thread_info
)paren
)paren
(braket
id|regno
)braket
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write contents of register REGNO in task TASK.&n; */
DECL|function|put_reg
r_inline
r_int
id|put_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
comma
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
id|regno
op_eq
id|PT_USP
)paren
id|task-&gt;thread.usp
op_assign
id|data
suffix:semicolon
r_else
r_if
c_cond
(paren
id|regno
OL
id|PT_MAX
)paren
(paren
(paren
r_int
r_int
op_star
)paren
id|user_regs
c_func
(paren
id|task-&gt;thread_info
)paren
)paren
(braket
id|regno
)braket
op_assign
id|data
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* notification of userspace execution resumption&n; * - triggered by current-&gt;work.notify_resume&n; */
r_extern
r_int
id|do_signal
c_func
(paren
r_int
id|canrestart
comma
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|do_notify_resume
r_void
id|do_notify_resume
c_func
(paren
r_int
id|canrestart
comma
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u32
id|thread_info_flags
)paren
(brace
multiline_comment|/* deal with pending signal delivery */
r_if
c_cond
(paren
id|thread_info_flags
op_amp
id|_TIF_SIGPENDING
)paren
id|do_signal
c_func
(paren
id|canrestart
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
)brace
eof
