multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PTRACE_GENERIC_H
DECL|macro|__UM_PTRACE_GENERIC_H
mdefine_line|#define __UM_PTRACE_GENERIC_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &quot;linux/config.h&quot;
DECL|macro|pt_regs
mdefine_line|#define pt_regs pt_regs_subarch
DECL|macro|show_regs
mdefine_line|#define show_regs show_regs_subarch
macro_line|#include &quot;asm/arch/ptrace.h&quot;
DECL|macro|pt_regs
macro_line|#undef pt_regs
DECL|macro|show_regs
macro_line|#undef show_regs
DECL|macro|user_mode
macro_line|#undef user_mode
DECL|macro|instruction_pointer
macro_line|#undef instruction_pointer
macro_line|#include &quot;sysdep/ptrace.h&quot;
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|regs
r_union
id|uml_pt_regs
id|regs
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EMPTY_REGS
mdefine_line|#define EMPTY_REGS { regs : EMPTY_UML_PT_REGS }
DECL|macro|PT_REGS_IP
mdefine_line|#define PT_REGS_IP(r) UPT_IP(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_SP
mdefine_line|#define PT_REGS_SP(r) UPT_SP(&amp;(r)-&gt;regs)
DECL|macro|PT_REG
mdefine_line|#define PT_REG(r, reg) UPT_REG(&amp;(r)-&gt;regs, reg)
DECL|macro|PT_REGS_SET
mdefine_line|#define PT_REGS_SET(r, reg, val) UPT_SET(&amp;(r)-&gt;regs, reg, val)
DECL|macro|PT_REGS_SET_SYSCALL_RETURN
mdefine_line|#define PT_REGS_SET_SYSCALL_RETURN(r, res) &bslash;&n;&t;UPT_SET_SYSCALL_RETURN(&amp;(r)-&gt;regs, res)
DECL|macro|PT_REGS_RESTART_SYSCALL
mdefine_line|#define PT_REGS_RESTART_SYSCALL(r) UPT_RESTART_SYSCALL(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_SYSCALL_NR
mdefine_line|#define PT_REGS_SYSCALL_NR(r) UPT_SYSCALL_NR(&amp;(r)-&gt;regs)
DECL|macro|PT_REGS_SC
mdefine_line|#define PT_REGS_SC(r) UPT_SC(&amp;(r)-&gt;regs)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) PT_REGS_IP(regs)
r_struct
id|task_struct
suffix:semicolon
r_extern
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
id|regno
)paren
suffix:semicolon
r_extern
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
id|regno
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
id|get_fpregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
r_extern
r_int
id|set_fpregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
r_extern
r_int
id|get_fpxregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|child
)paren
suffix:semicolon
r_extern
r_int
id|set_fpxregs
c_func
(paren
r_int
r_int
id|buf
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
