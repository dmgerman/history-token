multiline_comment|/* ptrace.c */
multiline_comment|/* By Ross Biro 1/23/92 */
multiline_comment|/*&n; * Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/audit.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/debugreg.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/* determines which flags the user has access to. */
multiline_comment|/* 1 = access 0 = no access */
DECL|macro|FLAG_MASK
mdefine_line|#define FLAG_MASK 0x00044dd5
multiline_comment|/* set&squot;s the trap flag. */
DECL|macro|TRAP_FLAG
mdefine_line|#define TRAP_FLAG 0x100
multiline_comment|/*&n; * Offset of eflags on child stack..&n; */
DECL|macro|EFL_OFFSET
mdefine_line|#define EFL_OFFSET ((EFL-2)*4-sizeof(struct pt_regs))
multiline_comment|/*&n; * this routine will get a word off of the processes privileged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
DECL|function|get_stack_long
r_static
r_inline
r_int
id|get_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task-&gt;thread.esp0
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
r_return
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|stack
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine will put a word on the processes privileged stack. &n; * the offset is how far from the base addr as stored in the TSS.  &n; * this routine assumes that all the privileged stacks are in our&n; * data space.&n; */
DECL|function|put_stack_long
r_static
r_inline
r_int
id|put_stack_long
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|offset
comma
r_int
r_int
id|data
)paren
(brace
r_int
r_char
op_star
id|stack
suffix:semicolon
id|stack
op_assign
(paren
r_int
r_char
op_star
)paren
id|task-&gt;thread.esp0
suffix:semicolon
id|stack
op_add_assign
id|offset
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|stack
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|putreg
r_static
r_int
id|putreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|regno
comma
r_int
r_int
id|value
)paren
(brace
r_switch
c_cond
(paren
id|regno
op_rshift
l_int|2
)paren
(brace
r_case
id|FS
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.fs
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|GS
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|child-&gt;thread.gs
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|DS
suffix:colon
r_case
id|ES
suffix:colon
r_if
c_cond
(paren
id|value
op_logical_and
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|value
op_and_assign
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SS
suffix:colon
r_case
id|CS
suffix:colon
r_if
c_cond
(paren
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|value
op_and_assign
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EFL
suffix:colon
id|value
op_and_assign
id|FLAG_MASK
suffix:semicolon
id|value
op_or_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_amp
op_complement
id|FLAG_MASK
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regno
OG
id|GS
op_star
l_int|4
)paren
id|regno
op_sub_assign
l_int|2
op_star
l_int|4
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|regno
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|getreg
r_static
r_int
r_int
id|getreg
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|regno
)paren
(brace
r_int
r_int
id|retval
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_switch
c_cond
(paren
id|regno
op_rshift
l_int|2
)paren
(brace
r_case
id|FS
suffix:colon
id|retval
op_assign
id|child-&gt;thread.fs
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GS
suffix:colon
id|retval
op_assign
id|child-&gt;thread.gs
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DS
suffix:colon
r_case
id|ES
suffix:colon
r_case
id|SS
suffix:colon
r_case
id|CS
suffix:colon
id|retval
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|regno
OG
id|GS
op_star
l_int|4
)paren
id|regno
op_sub_assign
l_int|2
op_star
l_int|4
suffix:semicolon
id|regno
op_assign
id|regno
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|retval
op_and_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|regno
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; *&n; * Make sure the single step bit is not set.&n; */
DECL|function|ptrace_disable
r_void
id|ptrace_disable
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SINGLESTEP
)paren
suffix:semicolon
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform get_thread_area on behalf of the traced child.&n; */
r_static
r_int
DECL|function|ptrace_get_thread_area
id|ptrace_get_thread_area
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|idx
comma
r_struct
id|user_desc
id|__user
op_star
id|user_desc
)paren
(brace
r_struct
id|user_desc
id|info
suffix:semicolon
r_struct
id|desc_struct
op_star
id|desc
suffix:semicolon
multiline_comment|/*&n; * Get the current Thread-Local Storage area:&n; */
DECL|macro|GET_BASE
mdefine_line|#define GET_BASE(desc) ( &bslash;&n;&t;(((desc)-&gt;a &gt;&gt; 16) &amp; 0x0000ffff) | &bslash;&n;&t;(((desc)-&gt;b &lt;&lt; 16) &amp; 0x00ff0000) | &bslash;&n;&t;( (desc)-&gt;b        &amp; 0xff000000)   )
DECL|macro|GET_LIMIT
mdefine_line|#define GET_LIMIT(desc) ( &bslash;&n;&t;((desc)-&gt;a &amp; 0x0ffff) | &bslash;&n;&t; ((desc)-&gt;b &amp; 0xf0000) )
DECL|macro|GET_32BIT
mdefine_line|#define GET_32BIT(desc)&t;&t;(((desc)-&gt;b &gt;&gt; 22) &amp; 1)
DECL|macro|GET_CONTENTS
mdefine_line|#define GET_CONTENTS(desc)&t;(((desc)-&gt;b &gt;&gt; 10) &amp; 3)
DECL|macro|GET_WRITABLE
mdefine_line|#define GET_WRITABLE(desc)&t;(((desc)-&gt;b &gt;&gt;  9) &amp; 1)
DECL|macro|GET_LIMIT_PAGES
mdefine_line|#define GET_LIMIT_PAGES(desc)&t;(((desc)-&gt;b &gt;&gt; 23) &amp; 1)
DECL|macro|GET_PRESENT
mdefine_line|#define GET_PRESENT(desc)&t;(((desc)-&gt;b &gt;&gt; 15) &amp; 1)
DECL|macro|GET_USEABLE
mdefine_line|#define GET_USEABLE(desc)&t;(((desc)-&gt;b &gt;&gt; 20) &amp; 1)
r_if
c_cond
(paren
id|idx
template_param
id|GDT_ENTRY_TLS_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|desc
op_assign
id|child-&gt;thread.tls_array
op_plus
id|idx
op_minus
id|GDT_ENTRY_TLS_MIN
suffix:semicolon
id|info.entry_number
op_assign
id|idx
suffix:semicolon
id|info.base_addr
op_assign
id|GET_BASE
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.limit
op_assign
id|GET_LIMIT
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.seg_32bit
op_assign
id|GET_32BIT
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.contents
op_assign
id|GET_CONTENTS
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.read_exec_only
op_assign
op_logical_neg
id|GET_WRITABLE
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.limit_in_pages
op_assign
id|GET_LIMIT_PAGES
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.seg_not_present
op_assign
op_logical_neg
id|GET_PRESENT
c_func
(paren
id|desc
)paren
suffix:semicolon
id|info.useable
op_assign
id|GET_USEABLE
c_func
(paren
id|desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|user_desc
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform set_thread_area on behalf of the traced child.&n; */
r_static
r_int
DECL|function|ptrace_set_thread_area
id|ptrace_set_thread_area
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|idx
comma
r_struct
id|user_desc
id|__user
op_star
id|user_desc
)paren
(brace
r_struct
id|user_desc
id|info
suffix:semicolon
r_struct
id|desc_struct
op_star
id|desc
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|user_desc
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|idx
template_param
id|GDT_ENTRY_TLS_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|desc
op_assign
id|child-&gt;thread.tls_array
op_plus
id|idx
op_minus
id|GDT_ENTRY_TLS_MIN
suffix:semicolon
r_if
c_cond
(paren
id|LDT_empty
c_func
(paren
op_amp
id|info
)paren
)paren
(brace
id|desc-&gt;a
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;b
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|desc-&gt;a
op_assign
id|LDT_entry_a
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
id|desc-&gt;b
op_assign
id|LDT_entry_b
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_ptrace
id|asmlinkage
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_struct
id|user
op_star
id|dummy
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
r_int
r_int
id|__user
op_star
id|datap
op_assign
(paren
r_int
r_int
id|__user
op_star
)paren
id|data
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|security_ptrace
c_func
(paren
id|current-&gt;parent
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|get_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* you may not mess with init */
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
id|ret
op_assign
id|ptrace_attach
c_func
(paren
id|child
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|ret
op_assign
id|ptrace_check_attach
c_func
(paren
id|child
comma
id|request
op_eq
id|PTRACE_KILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_tsk
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/* when I and D space are separate, these will need to be fixed. */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|copied
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
id|datap
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* read the word at location addr in the USER area. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_break
suffix:semicolon
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default return condition */
r_if
c_cond
(paren
id|addr
OL
id|FRAME_SIZE
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|tmp
op_assign
id|getreg
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
op_logical_and
id|addr
op_le
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|7
)braket
)paren
(brace
id|addr
op_sub_assign
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
id|tmp
op_assign
id|child-&gt;thread.debugreg
(braket
id|addr
)braket
suffix:semicolon
)brace
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
id|datap
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* when I and D space are separate, this will have to be fixed. */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|data
comma
r_sizeof
(paren
id|data
)paren
comma
l_int|1
)paren
op_eq
r_sizeof
(paren
id|data
)paren
)paren
r_break
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the word at location addr in the USER area */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|3
)paren
op_logical_or
id|addr
template_param
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
l_int|3
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|FRAME_SIZE
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|ret
op_assign
id|putreg
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* We need to be very careful here.  We implicitly&n;&t;&t;   want to modify a portion of the task_struct, and we&n;&t;&t;   have to be selective about what portions we allow someone&n;&t;&t;   to modify. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
op_logical_and
id|addr
op_le
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|7
)braket
)paren
(brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|4
)braket
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|5
)braket
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
OL
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|4
)braket
op_logical_and
(paren
(paren
r_int
r_int
)paren
id|data
)paren
op_ge
id|TASK_SIZE
op_minus
l_int|3
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr
op_eq
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
(braket
l_int|7
)braket
)paren
(brace
id|data
op_and_assign
op_complement
id|DR_CONTROL_RESERVED
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
l_int|0x5f54
op_rshift
(paren
(paren
id|data
op_rshift
(paren
l_int|16
op_plus
l_int|4
op_star
id|i
)paren
)paren
op_amp
l_int|0xf
)paren
)paren
op_amp
l_int|1
)paren
r_goto
id|out_tsk
suffix:semicolon
)brace
id|addr
op_sub_assign
(paren
r_int
)paren
op_amp
id|dummy-&gt;u_debugreg
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
id|child-&gt;thread.debugreg
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
(brace
multiline_comment|/* restart after signal. */
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
(brace
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
)brace
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SINGLESTEP
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * make the child exit.  Best I can do is send it a sigkill. &n; * perhaps it should be put in the status that it wants to &n; * exit.&n; */
r_case
id|PTRACE_KILL
suffix:colon
(brace
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
multiline_comment|/* already dead */
r_break
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SINGLESTEP
)paren
suffix:semicolon
multiline_comment|/* make sure the single step bit is not set. */
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_amp
op_complement
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SINGLESTEP
suffix:colon
(brace
multiline_comment|/* set the trap flag. */
r_int
id|tmp
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Spurious delayed TF traps may occur */
id|child-&gt;ptrace
op_or_assign
id|PT_DTRACE
suffix:semicolon
)brace
id|tmp
op_assign
id|get_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
)paren
op_or
id|TRAP_FLAG
suffix:semicolon
id|put_stack_long
c_func
(paren
id|child
comma
id|EFL_OFFSET
comma
id|tmp
)paren
suffix:semicolon
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SINGLESTEP
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* give it a chance to run. */
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_DETACH
suffix:colon
multiline_comment|/* detach a process that was attached. */
id|ret
op_assign
id|ptrace_detach
c_func
(paren
id|child
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_GETREGS
suffix:colon
(brace
multiline_comment|/* Get all gp regs from the child. */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|datap
comma
id|FRAME_SIZE
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FRAME_SIZE
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|__put_user
c_func
(paren
id|getreg
c_func
(paren
id|child
comma
id|i
)paren
comma
id|datap
)paren
suffix:semicolon
id|datap
op_increment
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETREGS
suffix:colon
(brace
multiline_comment|/* Set all gp regs in the child. */
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|datap
comma
id|FRAME_SIZE
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|FRAME_SIZE
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|__get_user
c_func
(paren
id|tmp
comma
id|datap
)paren
suffix:semicolon
id|putreg
c_func
(paren
id|child
comma
id|i
comma
id|tmp
)paren
suffix:semicolon
id|datap
op_increment
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_GETFPREGS
suffix:colon
(brace
multiline_comment|/* Get the child FPU state. */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|datap
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;used_math
)paren
id|init_fpu
c_func
(paren
id|child
)paren
suffix:semicolon
id|get_fpregs
c_func
(paren
(paren
r_struct
id|user_i387_struct
id|__user
op_star
)paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPREGS
suffix:colon
(brace
multiline_comment|/* Set the child FPU state. */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|datap
comma
r_sizeof
(paren
r_struct
id|user_i387_struct
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|child-&gt;used_math
op_assign
l_int|1
suffix:semicolon
id|set_fpregs
c_func
(paren
id|child
comma
(paren
r_struct
id|user_i387_struct
id|__user
op_star
)paren
id|data
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_GETFPXREGS
suffix:colon
(brace
multiline_comment|/* Get the child extended FPU state. */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|datap
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;used_math
)paren
id|init_fpu
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
id|get_fpxregs
c_func
(paren
(paren
r_struct
id|user_fxsr_struct
id|__user
op_star
)paren
id|data
comma
id|child
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_SETFPXREGS
suffix:colon
(brace
multiline_comment|/* Set the child extended FPU state. */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|datap
comma
r_sizeof
(paren
r_struct
id|user_fxsr_struct
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|child-&gt;used_math
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|set_fpxregs
c_func
(paren
id|child
comma
(paren
r_struct
id|user_fxsr_struct
id|__user
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PTRACE_GET_THREAD_AREA
suffix:colon
id|ret
op_assign
id|ptrace_get_thread_area
c_func
(paren
id|child
comma
id|addr
comma
(paren
r_struct
id|user_desc
id|__user
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_SET_THREAD_AREA
suffix:colon
id|ret
op_assign
id|ptrace_set_thread_area
c_func
(paren
id|child
comma
id|addr
comma
(paren
r_struct
id|user_desc
id|__user
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|ptrace_request
c_func
(paren
id|child
comma
id|request
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out_tsk
suffix:colon
id|put_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* notification of system call entry/exit&n; * - triggered by current-&gt;work.syscall_trace&n; */
id|__attribute__
c_func
(paren
(paren
id|regparm
c_func
(paren
l_int|3
)paren
)paren
)paren
DECL|function|do_syscall_trace
r_void
id|do_syscall_trace
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|entryexit
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|current-&gt;audit_context
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|entryexit
)paren
id|audit_syscall_entry
c_func
(paren
id|current
comma
id|regs-&gt;orig_eax
comma
id|regs-&gt;ebx
comma
id|regs-&gt;ecx
comma
id|regs-&gt;edx
comma
id|regs-&gt;esi
)paren
suffix:semicolon
r_else
id|audit_syscall_exit
c_func
(paren
id|current
comma
id|regs-&gt;eax
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_SYSCALL_TRACE
)paren
op_logical_and
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_SINGLESTEP
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* the 0x80 provides a way for the tracing parent to distinguish&n;&t;   between a syscall stop and SIGTRAP delivery */
id|ptrace_notify
c_func
(paren
id|SIGTRAP
op_or
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYSGOOD
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|current-&gt;exit_code
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
