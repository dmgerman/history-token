macro_line|#ifndef _H8300_PTRACE_H
DECL|macro|_H8300_PTRACE_H
mdefine_line|#define _H8300_PTRACE_H
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PT_ER1
mdefine_line|#define PT_ER1&t;   0
DECL|macro|PT_ER2
mdefine_line|#define PT_ER2&t;   1
DECL|macro|PT_ER3
mdefine_line|#define PT_ER3&t;   2
DECL|macro|PT_ER4
mdefine_line|#define PT_ER4&t;   3
DECL|macro|PT_ER5
mdefine_line|#define PT_ER5&t;   4
DECL|macro|PT_ER6
mdefine_line|#define PT_ER6&t;   5
DECL|macro|PT_ER0
mdefine_line|#define PT_ER0&t;   6
DECL|macro|PT_ORIG_ER0
mdefine_line|#define PT_ORIG_ER0&t;   7
DECL|macro|PT_CCR
mdefine_line|#define PT_CCR&t;   8
DECL|macro|PT_PC
mdefine_line|#define PT_PC&t;   9
DECL|macro|PT_USP
mdefine_line|#define PT_USP&t;   10
multiline_comment|/* this struct defines the way the registers are stored on the&n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|retpc
r_int
id|retpc
suffix:semicolon
DECL|member|er4
r_int
id|er4
suffix:semicolon
DECL|member|er5
r_int
id|er5
suffix:semicolon
DECL|member|er6
r_int
id|er6
suffix:semicolon
DECL|member|er3
r_int
id|er3
suffix:semicolon
DECL|member|er2
r_int
id|er2
suffix:semicolon
DECL|member|er1
r_int
id|er1
suffix:semicolon
DECL|member|orig_er0
r_int
id|orig_er0
suffix:semicolon
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
DECL|member|er0
r_int
id|er0
suffix:semicolon
DECL|member|vector
r_int
id|vector
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_H8S)
DECL|member|exr
r_int
r_int
id|exr
suffix:semicolon
macro_line|#endif
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|2
)paren
comma
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS            12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS            13
macro_line|#ifdef __KERNEL__
macro_line|#ifndef PS_S
DECL|macro|PS_S
mdefine_line|#define PS_S  (0x10)
macro_line|#endif
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!((regs)-&gt;ccr &amp; PS_S))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;pc)
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _H8300_PTRACE_H */
eof
