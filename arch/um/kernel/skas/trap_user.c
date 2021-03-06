multiline_comment|/* &n; * Copyright (C) 2002 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;task.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
DECL|function|sig_handler_common_skas
r_void
id|sig_handler_common_skas
c_func
(paren
r_int
id|sig
comma
r_void
op_star
id|sc_ptr
)paren
(brace
r_struct
id|sigcontext
op_star
id|sc
op_assign
id|sc_ptr
suffix:semicolon
r_struct
id|skas_regs
op_star
id|r
suffix:semicolon
r_struct
id|signal_info
op_star
id|info
suffix:semicolon
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
r_int
id|save_user
suffix:semicolon
multiline_comment|/* This is done because to allow SIGSEGV to be delivered inside a SEGV&n;&t; * handler.  This can happen in copy_user, and if SEGV is disabled,&n;&t; * the process will die.&n;&t; * XXX Figure out why this is better than SA_NODEFER&n;&t; */
r_if
c_cond
(paren
id|sig
op_eq
id|SIGSEGV
)paren
(brace
id|change_sig
c_func
(paren
id|SIGSEGV
comma
l_int|1
)paren
suffix:semicolon
)brace
id|r
op_assign
op_amp
id|TASK_REGS
c_func
(paren
id|get_current
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|skas
suffix:semicolon
id|save_user
op_assign
id|r-&gt;is_user
suffix:semicolon
id|r-&gt;is_user
op_assign
l_int|0
suffix:semicolon
id|r-&gt;fault_addr
op_assign
id|SC_FAULT_ADDR
c_func
(paren
id|sc
)paren
suffix:semicolon
id|r-&gt;fault_type
op_assign
id|SC_FAULT_TYPE
c_func
(paren
id|sc
)paren
suffix:semicolon
id|r-&gt;trap_type
op_assign
id|SC_TRAP_TYPE
c_func
(paren
id|sc
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGUSR1
comma
l_int|1
)paren
suffix:semicolon
id|info
op_assign
op_amp
id|sig_info
(braket
id|sig
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;is_irq
)paren
(brace
id|unblock_signals
c_func
(paren
)paren
suffix:semicolon
)brace
(paren
op_star
id|info-&gt;handler
)paren
(paren
id|sig
comma
(paren
r_union
id|uml_pt_regs
op_star
)paren
id|r
)paren
suffix:semicolon
id|errno
op_assign
id|save_errno
suffix:semicolon
id|r-&gt;is_user
op_assign
id|save_user
suffix:semicolon
)brace
DECL|function|user_signal
r_void
id|user_signal
c_func
(paren
r_int
id|sig
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|signal_info
op_star
id|info
suffix:semicolon
id|regs-&gt;skas.is_user
op_assign
l_int|1
suffix:semicolon
id|regs-&gt;skas.fault_addr
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;skas.fault_type
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;skas.trap_type
op_assign
l_int|0
suffix:semicolon
id|info
op_assign
op_amp
id|sig_info
(braket
id|sig
)braket
suffix:semicolon
(paren
op_star
id|info-&gt;handler
)paren
(paren
id|sig
comma
id|regs
)paren
suffix:semicolon
id|unblock_signals
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
