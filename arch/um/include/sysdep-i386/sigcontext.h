multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYS_SIGCONTEXT_I386_H
DECL|macro|__SYS_SIGCONTEXT_I386_H
mdefine_line|#define __SYS_SIGCONTEXT_I386_H
macro_line|#include &quot;sc.h&quot;
DECL|macro|IP_RESTART_SYSCALL
mdefine_line|#define IP_RESTART_SYSCALL(ip) ((ip) -= 2)
DECL|macro|SC_RESTART_SYSCALL
mdefine_line|#define SC_RESTART_SYSCALL(sc) IP_RESTART_SYSCALL(SC_IP(sc))
DECL|macro|SC_SET_SYSCALL_RETURN
mdefine_line|#define SC_SET_SYSCALL_RETURN(sc, result) SC_EAX(sc) = (result)
DECL|macro|SC_FAULT_ADDR
mdefine_line|#define SC_FAULT_ADDR(sc) SC_CR2(sc)
DECL|macro|SC_FAULT_TYPE
mdefine_line|#define SC_FAULT_TYPE(sc) SC_ERR(sc)
DECL|macro|FAULT_WRITE
mdefine_line|#define FAULT_WRITE(err) (err &amp; 2)
DECL|macro|TO_SC_ERR
mdefine_line|#define TO_SC_ERR(is_write) ((is_write) ? 2 : 0)
DECL|macro|SC_FAULT_WRITE
mdefine_line|#define SC_FAULT_WRITE(sc) (FAULT_WRITE(SC_ERR(sc)))
DECL|macro|SC_TRAP_TYPE
mdefine_line|#define SC_TRAP_TYPE(sc) SC_TRAPNO(sc)
multiline_comment|/* ptrace expects that, at the start of a system call, %eax contains&n; * -ENOSYS, so this makes it so.&n; */
DECL|macro|SC_START_SYSCALL
mdefine_line|#define SC_START_SYSCALL(sc) do SC_EAX(sc) = -ENOSYS; while(0)
multiline_comment|/* These are General Protection and Page Fault */
DECL|macro|SEGV_IS_FIXABLE
mdefine_line|#define SEGV_IS_FIXABLE(trap) ((trap == 13) || (trap == 14))
DECL|macro|SC_SEGV_IS_FIXABLE
mdefine_line|#define SC_SEGV_IS_FIXABLE(sc) (SEGV_IS_FIXABLE(SC_TRAPNO(sc)))
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
