multiline_comment|/*&n; * linux/kernel/ptrace.c&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; *&n; * Common interfaces for &quot;ptrace()&quot; which we do not want&n; * to continually duplicate across every architecture.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * ptrace a task: make the debugger its new parent and&n; * move it to the ptrace list.&n; *&n; * Must be called with the tasklist lock write-held.&n; */
DECL|function|__ptrace_link
r_void
id|__ptrace_link
c_func
(paren
id|task_t
op_star
id|child
comma
id|task_t
op_star
id|new_parent
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|child-&gt;ptrace_list
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;parent
op_eq
id|new_parent
)paren
r_return
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|child-&gt;ptrace_list
comma
op_amp
id|child-&gt;parent-&gt;ptrace_children
)paren
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;parent
op_assign
id|new_parent
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unptrace a task: move it back to its original parent and&n; * remove it from the ptrace list.&n; *&n; * Must be called with the tasklist lock write-held.&n; */
DECL|function|__ptrace_unlink
r_void
id|__ptrace_unlink
c_func
(paren
id|task_t
op_star
id|child
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;ptrace
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|child-&gt;ptrace
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|child-&gt;ptrace_list
)paren
)paren
r_return
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|child-&gt;ptrace_list
)paren
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;parent
op_assign
id|child-&gt;real_parent
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_TRACED
)paren
(brace
multiline_comment|/*&n;&t;&t; * Turn a tracing stop into a normal stop now,&n;&t;&t; * since with no tracer there would be no way&n;&t;&t; * to wake it up with SIGCONT or SIGKILL.&n;&t;&t; */
id|child-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check that we have indeed attached to the thing..&n; */
DECL|function|ptrace_check_attach
r_int
id|ptrace_check_attach
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|kill
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
multiline_comment|/*&n;&t; * We take the read lock around doing both checks to close a&n;&t; * possible race where someone else was tracing our child and&n;&t; * detached between these two checks.  After this locked check,&n;&t; * we are sure that this is our traced child and that can only&n;&t; * be changed by us so it&squot;s not changing right after this.&n;&t; */
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
op_logical_and
id|child-&gt;parent
op_eq
id|current
)paren
id|ret
op_assign
l_int|0
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
id|ret
op_logical_and
op_logical_neg
id|kill
)paren
(brace
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_TRACED
)paren
r_return
op_minus
id|ESRCH
suffix:semicolon
id|wait_task_inactive
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
multiline_comment|/* All systems go.. */
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ptrace_attach
r_int
id|ptrace_attach
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_int
id|retval
suffix:semicolon
id|task_lock
c_func
(paren
id|task
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;pid
op_le
l_int|1
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|task
op_eq
id|current
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|task-&gt;mm
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|current-&gt;uid
op_ne
id|task-&gt;euid
)paren
op_logical_or
(paren
id|current-&gt;uid
op_ne
id|task-&gt;suid
)paren
op_logical_or
(paren
id|current-&gt;uid
op_ne
id|task-&gt;uid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|task-&gt;egid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|task-&gt;sgid
)paren
op_logical_or
(paren
id|current-&gt;gid
op_ne
id|task-&gt;gid
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
(brace
r_goto
id|bad
suffix:semicolon
)brace
id|rmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|task-&gt;mm-&gt;dumpable
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
r_goto
id|bad
suffix:semicolon
multiline_comment|/* the same process cannot be attached many times */
r_if
c_cond
(paren
id|task-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|bad
suffix:semicolon
id|retval
op_assign
id|security_ptrace
c_func
(paren
id|current
comma
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|bad
suffix:semicolon
multiline_comment|/* Go */
id|task-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_PTRACE
)paren
)paren
id|task-&gt;ptrace
op_or_assign
id|PT_PTRACE_CAP
suffix:semicolon
id|task_unlock
c_func
(paren
id|task
)paren
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|__ptrace_link
c_func
(paren
id|task
comma
id|current
)paren
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|force_sig_specific
c_func
(paren
id|SIGSTOP
comma
id|task
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad
suffix:colon
id|task_unlock
c_func
(paren
id|task
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ptrace_detach
r_int
id|ptrace_detach
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
r_int
id|data
)paren
(brace
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
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Architecture-specific hardware disable .. */
id|ptrace_disable
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/* .. re-parent .. */
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|__ptrace_unlink
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/* .. and wake it up. */
r_if
c_cond
(paren
id|child-&gt;state
op_ne
id|TASK_ZOMBIE
)paren
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Access another process&squot; address space.&n; * Source/target buffer must be kernel space, &n; * Do not walk the page table directly, use get_user_pages&n; */
DECL|function|access_process_vm
r_int
id|access_process_vm
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_void
op_star
id|old_buf
op_assign
id|buf
suffix:semicolon
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_return
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* ignore errors, just check how much was sucessfully transfered */
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
id|bytes
comma
id|ret
comma
id|offset
suffix:semicolon
r_void
op_star
id|maddr
suffix:semicolon
id|ret
op_assign
id|get_user_pages
c_func
(paren
id|tsk
comma
id|mm
comma
id|addr
comma
l_int|1
comma
id|write
comma
l_int|1
comma
op_amp
id|page
comma
op_amp
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|bytes
op_assign
id|len
suffix:semicolon
id|offset
op_assign
id|addr
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bytes
OG
id|PAGE_SIZE
op_minus
id|offset
)paren
id|bytes
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
id|flush_cache_page
c_func
(paren
id|vma
comma
id|addr
)paren
suffix:semicolon
id|maddr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
)paren
(brace
id|copy_to_user_page
c_func
(paren
id|vma
comma
id|page
comma
id|addr
comma
id|maddr
op_plus
id|offset
comma
id|buf
comma
id|bytes
)paren
suffix:semicolon
id|set_page_dirty_lock
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|copy_from_user_page
c_func
(paren
id|vma
comma
id|page
comma
id|addr
comma
id|buf
comma
id|maddr
op_plus
id|offset
comma
id|bytes
)paren
suffix:semicolon
)brace
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|len
op_sub_assign
id|bytes
suffix:semicolon
id|buf
op_add_assign
id|bytes
suffix:semicolon
id|addr
op_add_assign
id|bytes
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
r_return
id|buf
op_minus
id|old_buf
suffix:semicolon
)brace
DECL|function|ptrace_readdata
r_int
id|ptrace_readdata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|src
comma
r_char
id|__user
op_star
id|dst
comma
r_int
id|len
)paren
(brace
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|this_len
comma
id|retval
suffix:semicolon
id|this_len
op_assign
(paren
id|len
OG
r_sizeof
(paren
id|buf
)paren
)paren
ques
c_cond
r_sizeof
(paren
id|buf
)paren
suffix:colon
id|len
suffix:semicolon
id|retval
op_assign
id|access_process_vm
c_func
(paren
id|tsk
comma
id|src
comma
id|buf
comma
id|this_len
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_if
c_cond
(paren
id|copied
)paren
r_break
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|buf
comma
id|retval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|copied
op_add_assign
id|retval
suffix:semicolon
id|src
op_add_assign
id|retval
suffix:semicolon
id|dst
op_add_assign
id|retval
suffix:semicolon
id|len
op_sub_assign
id|retval
suffix:semicolon
)brace
r_return
id|copied
suffix:semicolon
)brace
DECL|function|ptrace_writedata
r_int
id|ptrace_writedata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_char
id|__user
op_star
id|src
comma
r_int
r_int
id|dst
comma
r_int
id|len
)paren
(brace
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|this_len
comma
id|retval
suffix:semicolon
id|this_len
op_assign
(paren
id|len
OG
r_sizeof
(paren
id|buf
)paren
)paren
ques
c_cond
r_sizeof
(paren
id|buf
)paren
suffix:colon
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|src
comma
id|this_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|retval
op_assign
id|access_process_vm
c_func
(paren
id|tsk
comma
id|dst
comma
id|buf
comma
id|this_len
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_if
c_cond
(paren
id|copied
)paren
r_break
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|copied
op_add_assign
id|retval
suffix:semicolon
id|src
op_add_assign
id|retval
suffix:semicolon
id|dst
op_add_assign
id|retval
suffix:semicolon
id|len
op_sub_assign
id|retval
suffix:semicolon
)brace
r_return
id|copied
suffix:semicolon
)brace
DECL|function|ptrace_setoptions
r_static
r_int
id|ptrace_setoptions
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|data
)paren
(brace
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_TRACE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACESYSGOOD
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACESYSGOOD
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACEFORK
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACE_FORK
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACEVFORK
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACE_VFORK
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACECLONE
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACE_CLONE
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACEEXEC
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACE_EXEC
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACEVFORKDONE
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACE_VFORK_DONE
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|PTRACE_O_TRACEEXIT
)paren
id|child-&gt;ptrace
op_or_assign
id|PT_TRACE_EXIT
suffix:semicolon
r_return
(paren
id|data
op_amp
op_complement
id|PTRACE_O_MASK
)paren
ques
c_cond
op_minus
id|EINVAL
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_getsiginfo
r_static
r_int
id|ptrace_getsiginfo
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
id|siginfo_t
id|__user
op_star
id|data
)paren
(brace
id|BUG_ON
c_func
(paren
id|child-&gt;last_siginfo
op_eq
l_int|NULL
)paren
suffix:semicolon
r_return
id|copy_siginfo_to_user
c_func
(paren
id|data
comma
id|child-&gt;last_siginfo
)paren
suffix:semicolon
)brace
DECL|function|ptrace_setsiginfo
r_static
r_int
id|ptrace_setsiginfo
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
id|siginfo_t
id|__user
op_star
id|data
)paren
(brace
id|BUG_ON
c_func
(paren
id|child-&gt;last_siginfo
op_eq
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|child-&gt;last_siginfo
comma
id|data
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_request
r_int
id|ptrace_request
c_func
(paren
r_struct
id|task_struct
op_star
id|child
comma
r_int
id|request
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
macro_line|#ifdef PTRACE_OLDSETOPTIONS
r_case
id|PTRACE_OLDSETOPTIONS
suffix:colon
macro_line|#endif
r_case
id|PTRACE_SETOPTIONS
suffix:colon
id|ret
op_assign
id|ptrace_setoptions
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
id|PTRACE_GETEVENTMSG
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|child-&gt;ptrace_message
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_GETSIGINFO
suffix:colon
id|ret
op_assign
id|ptrace_getsiginfo
c_func
(paren
id|child
comma
(paren
id|siginfo_t
id|__user
op_star
)paren
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_SETSIGINFO
suffix:colon
id|ret
op_assign
id|ptrace_setsiginfo
c_func
(paren
id|child
comma
(paren
id|siginfo_t
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
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
