multiline_comment|/*&n; * include/asm-v850/processor.h&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_PROCESSOR_H__
DECL|macro|__V850_PROCESSOR_H__
mdefine_line|#define __V850_PROCESSOR_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__ /* &lt;linux/thread_info.h&gt; is not asm-safe.  */
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/entry.h&gt;
multiline_comment|/* Some code expects `segment&squot; stuff to be defined here.  */
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * The only places this is used seem to be horrible bletcherous kludges,&n; * so we just define it to be as large as possible.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xFFFFFFFF)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.  We won&squot;t be using it.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;0
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Default implementation of macro that returns current&n; * instruction pointer (&quot;program counter&quot;).&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr()&t;({ __label__ _l; _l: &amp;&amp;_l;})
multiline_comment|/* If you change this, you must change the associated assembly-languages&n;   constants defined below, THREAD_*.  */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/* kernel stack pointer (must be first field in structure) */
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD { sizeof init_stack + (unsigned long)init_stack }
multiline_comment|/* Do necessary setup to start up a newly executed thread.  */
DECL|function|start_thread
r_extern
r_inline
r_void
id|start_thread
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|usp
)paren
(brace
id|regs-&gt;pc
op_assign
id|pc
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
op_assign
id|usp
suffix:semicolon
id|regs-&gt;kernel_mode
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Free all resources held by a thread. */
DECL|function|release_thread
r_extern
r_inline
r_void
id|release_thread
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
)brace
multiline_comment|/* Prepare to copy thread state - unlazy all lazy status */
DECL|macro|prepare_to_copy
mdefine_line|#define prepare_to_copy(tsk)&t;do { } while (0)
r_extern
r_int
id|kernel_thread
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Free current thread data structures etc.  */
DECL|function|exit_thread
r_static
r_inline
r_void
id|exit_thread
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Return the registers saved during context-switch by the currently&n;   not-running thread T.  Note that this only includes some registers!&n;   See entry.S for details.  */
DECL|macro|thread_saved_regs
mdefine_line|#define thread_saved_regs(t) &bslash;&n;   ((struct pt_regs*)((t)-&gt;thread.ksp + STATE_SAVE_PT_OFFSET))
multiline_comment|/* Return saved (kernel) PC of a blocked thread.  Actually, we return the&n;   LP register, because the thread is actually blocked in switch_thread,&n;   and we&squot;re interested in the PC it will _return_ to.  */
DECL|macro|thread_saved_pc
mdefine_line|#define thread_saved_pc(t)   (thread_saved_regs(t)-&gt;gpr[GPR_LP])
r_int
r_int
id|get_wchan
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* Return some info about the user process TASK.  */
DECL|macro|task_tos
mdefine_line|#define task_tos(task)&t;((unsigned long)(task)-&gt;thread_info + THREAD_SIZE)
DECL|macro|task_regs
mdefine_line|#define task_regs(task) ((struct pt_regs *)task_tos (task) - 1)
DECL|macro|task_sp
mdefine_line|#define task_sp(task)&t;(task_regs (task)-&gt;gpr[GPR_SP])
DECL|macro|task_pc
mdefine_line|#define task_pc(task)&t;(task_regs (task)-&gt;pc)
multiline_comment|/* Grotty old names for some.  */
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(task)&t;task_pc (task)
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(task)&t;task_sp (task)
DECL|macro|cpu_relax
mdefine_line|#define cpu_relax()    ((void)0)
macro_line|#else /* __ASSEMBLY__ */
DECL|macro|THREAD_KSP
mdefine_line|#define THREAD_KSP&t;0
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_PROCESSOR_H__ */
eof
