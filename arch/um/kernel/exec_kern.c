multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/smp_lock.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
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
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;mode_kern.h&quot;
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
id|CHOOSE_MODE
c_func
(paren
id|flush_thread_tt
c_func
(paren
)paren
comma
id|flush_thread_skas
c_func
(paren
)paren
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
id|CHOOSE_MODE_PROC
c_func
(paren
id|start_thread_tt
comma
id|start_thread_skas
comma
id|regs
comma
id|eip
comma
id|esp
)paren
suffix:semicolon
)brace
r_extern
r_void
id|log_exec
c_func
(paren
r_char
op_star
op_star
id|argv
comma
r_void
op_star
id|tty
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_TTY_LOG
id|log_exec
c_func
(paren
id|argv
comma
id|current-&gt;tty
)paren
suffix:semicolon
macro_line|#endif
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
id|task_lock
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|task_unlock
c_func
(paren
id|current
)paren
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
r_int
id|err
suffix:semicolon
id|err
op_assign
id|execve1
c_func
(paren
id|file
comma
id|argv
comma
id|env
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|do_longjmp
c_func
(paren
id|current-&gt;thread.exec_buf
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|err
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
