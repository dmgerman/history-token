multiline_comment|/* &n; * Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/types.h&quot;
macro_line|#include &quot;linux/utime.h&quot;
macro_line|#include &quot;linux/sys.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/stat.h&quot;
macro_line|#include &quot;sysdep/syscalls.h&quot;
macro_line|#include &quot;kern_util.h&quot;
r_extern
id|syscall_handler_t
op_star
id|sys_call_table
(braket
)braket
suffix:semicolon
DECL|function|execute_syscall_tt
r_int
id|execute_syscall_tt
c_func
(paren
r_void
op_star
id|r
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|r
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
id|syscall
suffix:semicolon
id|current-&gt;thread.nsyscalls
op_increment
suffix:semicolon
id|nsyscalls
op_increment
suffix:semicolon
id|syscall
op_assign
id|UPT_SYSCALL_NR
c_func
(paren
op_amp
id|regs-&gt;regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|syscall
op_ge
id|NR_syscalls
)paren
op_logical_or
(paren
id|syscall
OL
l_int|0
)paren
)paren
(brace
id|res
op_assign
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_else
id|res
op_assign
id|EXECUTE_SYSCALL
c_func
(paren
id|syscall
comma
id|regs
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
