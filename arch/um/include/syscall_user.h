multiline_comment|/* &n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYSCALL_USER_H__
DECL|macro|__SYSCALL_USER_H__
mdefine_line|#define __SYSCALL_USER_H__
macro_line|#include &lt;asm/sigcontext.h&gt;
r_extern
r_void
id|syscall_handler
c_func
(paren
r_int
id|sig
comma
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|exit_kernel
c_func
(paren
r_int
id|pid
comma
r_void
op_star
id|task
)paren
suffix:semicolon
r_extern
r_int
id|do_syscall
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
