multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;uml-config.h&quot;
macro_line|#include &quot;syscall_user.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;skas.h&quot;
DECL|function|handle_syscall
r_void
id|handle_syscall
c_func
(paren
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_int
id|result
suffix:semicolon
macro_line|#if UML_CONFIG_SYSCALL_DEBUG
r_int
id|index
suffix:semicolon
id|index
op_assign
id|record_syscall_start
c_func
(paren
id|UPT_SYSCALL_NR
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
macro_line|#endif
id|syscall_trace
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|result
op_assign
id|execute_syscall_skas
c_func
(paren
id|regs
)paren
suffix:semicolon
id|REGS_SET_SYSCALL_RETURN
c_func
(paren
id|regs-&gt;skas.regs
comma
id|result
)paren
suffix:semicolon
id|syscall_trace
c_func
(paren
id|regs
comma
l_int|1
)paren
suffix:semicolon
macro_line|#if UML_CONFIG_SYSCALL_DEBUG
id|record_syscall_end
c_func
(paren
id|index
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
