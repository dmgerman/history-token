multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYS_SIGCONTEXT_I386_H
DECL|macro|__SYS_SIGCONTEXT_I386_H
mdefine_line|#define __SYS_SIGCONTEXT_I386_H
DECL|macro|IP_RESTART_SYSCALL
mdefine_line|#define IP_RESTART_SYSCALL(ip) ((ip) -= 2)
DECL|macro|SC_RESTART_SYSCALL
mdefine_line|#define SC_RESTART_SYSCALL(sc) IP_RESTART_SYSCALL(SC_IP(sc))
DECL|macro|SC_SET_SYSCALL_RETURN
mdefine_line|#define SC_SET_SYSCALL_RETURN(sc, result) do SC_EAX(sc) = (result) ; while(0)
DECL|macro|SC_FAULT_ADDR
mdefine_line|#define SC_FAULT_ADDR(sc) SC_CR2(sc)
DECL|macro|SC_FAULT_WRITE
mdefine_line|#define SC_FAULT_WRITE(sc) (SC_ERR(sc) &amp; 2)
multiline_comment|/* ptrace expects that, at the start of a system call, %eax contains&n; * -ENOSYS, so this makes it so.&n; */
DECL|macro|SC_START_SYSCALL
mdefine_line|#define SC_START_SYSCALL(sc) do SC_EAX(sc) = -ENOSYS; while(0)
multiline_comment|/* These are General Protection and Page Fault */
DECL|macro|SEGV_IS_FIXABLE
mdefine_line|#define SEGV_IS_FIXABLE(sc) ((SC_TRAPNO(sc) == 13) || (SC_TRAPNO(sc) == 14))
multiline_comment|/* XXX struct sigcontext needs declaring by now */
DECL|function|sc_to_regs
r_static
r_inline
r_void
id|sc_to_regs
c_func
(paren
r_struct
id|uml_pt_regs
op_star
id|regs
comma
r_struct
id|sigcontext
op_star
id|sc
comma
r_int
r_int
id|syscall
)paren
(brace
id|regs-&gt;syscall
op_assign
id|syscall
suffix:semicolon
id|regs-&gt;args
(braket
l_int|0
)braket
op_assign
id|SC_EBX
c_func
(paren
id|sc
)paren
suffix:semicolon
id|regs-&gt;args
(braket
l_int|1
)braket
op_assign
id|SC_ECX
c_func
(paren
id|sc
)paren
suffix:semicolon
id|regs-&gt;args
(braket
l_int|2
)braket
op_assign
id|SC_EDX
c_func
(paren
id|sc
)paren
suffix:semicolon
id|regs-&gt;args
(braket
l_int|3
)braket
op_assign
id|SC_ESI
c_func
(paren
id|sc
)paren
suffix:semicolon
id|regs-&gt;args
(braket
l_int|4
)braket
op_assign
id|SC_EDI
c_func
(paren
id|sc
)paren
suffix:semicolon
id|regs-&gt;args
(braket
l_int|5
)braket
op_assign
id|SC_EBP
c_func
(paren
id|sc
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
op_star
id|sc_sigmask
c_func
(paren
r_void
op_star
id|sc_ptr
)paren
suffix:semicolon
r_extern
r_int
id|sc_get_fpregs
c_func
(paren
r_int
r_int
id|buf
comma
r_void
op_star
id|sc_ptr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
