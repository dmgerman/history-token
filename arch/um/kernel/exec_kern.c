multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/smp_lock.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/tlbflush.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;tlb.h&quot;
macro_line|#include &quot;2_5compat.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;time_user.h&quot;
multiline_comment|/* See comment above fork_tramp for why sigstop is defined and used like&n; * this&n; */
DECL|variable|sigstop
r_static
r_int
id|sigstop
op_assign
id|SIGSTOP
suffix:semicolon
DECL|function|exec_tramp
r_static
r_int
id|exec_tramp
c_func
(paren
r_void
op_star
id|sig_stack
)paren
(brace
r_int
id|sig
op_assign
id|sigstop
suffix:semicolon
id|init_new_thread
c_func
(paren
id|sig_stack
comma
l_int|NULL
)paren
suffix:semicolon
id|kill
c_func
(paren
id|os_getpid
c_func
(paren
)paren
comma
id|sig
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|stack
suffix:semicolon
r_int
id|new_pid
suffix:semicolon
id|stack
op_assign
id|alloc_stack
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stack
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;flush_thread : failed to allocate temporary stack&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
id|new_pid
op_assign
id|start_fork_tramp
c_func
(paren
(paren
r_void
op_star
)paren
id|current-&gt;thread.kernel_stack
comma
id|stack
comma
l_int|0
comma
id|exec_tramp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;flush_thread : new thread failed, errno = %d&bslash;n&quot;
comma
op_minus
id|new_pid
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;thread_info-&gt;cpu
op_eq
l_int|0
)paren
(brace
id|forward_interrupts
c_func
(paren
id|new_pid
)paren
suffix:semicolon
)brace
id|current-&gt;thread.request.op
op_assign
id|OP_EXEC
suffix:semicolon
id|current-&gt;thread.request.u.exec.pid
op_assign
id|new_pid
suffix:semicolon
id|unprotect_stack
c_func
(paren
(paren
r_int
r_int
)paren
id|current-&gt;thread_info
)paren
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|enable_timer
c_func
(paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|stack
)paren
suffix:semicolon
id|protect
c_func
(paren
id|uml_reserved
comma
id|high_physmem
op_minus
id|uml_reserved
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|task_protections
c_func
(paren
(paren
r_int
r_int
)paren
id|current-&gt;thread_info
)paren
suffix:semicolon
id|force_flush_all
c_func
(paren
)paren
suffix:semicolon
id|unblock_signals
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|start_thread
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|eip
comma
r_int
r_int
id|esp
)paren
(brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
id|PT_REGS_IP
c_func
(paren
id|regs
)paren
op_assign
id|eip
suffix:semicolon
id|PT_REGS_SP
c_func
(paren
id|regs
)paren
op_assign
id|esp
suffix:semicolon
id|PT_FIX_EXEC_STACK
c_func
(paren
id|esp
)paren
suffix:semicolon
)brace
DECL|function|execve1
r_static
r_int
id|execve1
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|env
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|file
comma
id|argv
comma
id|env
comma
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|set_cmdline
c_func
(paren
id|current_cmd
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|um_execve
r_int
id|um_execve
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|env
)paren
(brace
r_if
c_cond
(paren
id|execve1
c_func
(paren
id|file
comma
id|argv
comma
id|env
)paren
op_eq
l_int|0
)paren
(brace
id|do_longjmp
c_func
(paren
id|current-&gt;thread.jmp
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|sys_execve
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|env
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
id|file
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|execve1
c_func
(paren
id|filename
comma
id|argv
comma
id|env
)paren
suffix:semicolon
id|putname
c_func
(paren
id|filename
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
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
