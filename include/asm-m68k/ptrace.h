macro_line|#ifndef _M68K_PTRACE_H
DECL|macro|_M68K_PTRACE_H
mdefine_line|#define _M68K_PTRACE_H
DECL|macro|PT_D1
mdefine_line|#define PT_D1&t;   0
DECL|macro|PT_D2
mdefine_line|#define PT_D2&t;   1
DECL|macro|PT_D3
mdefine_line|#define PT_D3&t;   2
DECL|macro|PT_D4
mdefine_line|#define PT_D4&t;   3
DECL|macro|PT_D5
mdefine_line|#define PT_D5&t;   4
DECL|macro|PT_D6
mdefine_line|#define PT_D6&t;   5
DECL|macro|PT_D7
mdefine_line|#define PT_D7&t;   6
DECL|macro|PT_A0
mdefine_line|#define PT_A0&t;   7
DECL|macro|PT_A1
mdefine_line|#define PT_A1&t;   8
DECL|macro|PT_A2
mdefine_line|#define PT_A2&t;   9
DECL|macro|PT_A3
mdefine_line|#define PT_A3&t;   10
DECL|macro|PT_A4
mdefine_line|#define PT_A4&t;   11
DECL|macro|PT_A5
mdefine_line|#define PT_A5&t;   12
DECL|macro|PT_A6
mdefine_line|#define PT_A6&t;   13
DECL|macro|PT_D0
mdefine_line|#define PT_D0&t;   14
DECL|macro|PT_USP
mdefine_line|#define PT_USP&t;   15
DECL|macro|PT_ORIG_D0
mdefine_line|#define PT_ORIG_D0 16
DECL|macro|PT_SR
mdefine_line|#define PT_SR&t;   17
DECL|macro|PT_PC
mdefine_line|#define PT_PC&t;   18
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* this struct defines the way the registers are stored on the&n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|d1
r_int
id|d1
suffix:semicolon
DECL|member|d2
r_int
id|d2
suffix:semicolon
DECL|member|d3
r_int
id|d3
suffix:semicolon
DECL|member|d4
r_int
id|d4
suffix:semicolon
DECL|member|d5
r_int
id|d5
suffix:semicolon
DECL|member|a0
r_int
id|a0
suffix:semicolon
DECL|member|a1
r_int
id|a1
suffix:semicolon
DECL|member|a2
r_int
id|a2
suffix:semicolon
DECL|member|d0
r_int
id|d0
suffix:semicolon
DECL|member|orig_d0
r_int
id|orig_d0
suffix:semicolon
DECL|member|stkadj
r_int
id|stkadj
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|format
r_int
id|format
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* frame format specifier */
DECL|member|vector
r_int
id|vector
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* vector offset */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the extended stack used by signal handlers and the context&n; * switcher: it&squot;s pushed after the normal &quot;struct pt_regs&quot;.&n; */
DECL|struct|switch_stack
r_struct
id|switch_stack
(brace
DECL|member|d6
r_int
r_int
id|d6
suffix:semicolon
DECL|member|d7
r_int
r_int
id|d7
suffix:semicolon
DECL|member|a3
r_int
r_int
id|a3
suffix:semicolon
DECL|member|a4
r_int
r_int
id|a4
suffix:semicolon
DECL|member|a5
r_int
r_int
id|a5
suffix:semicolon
DECL|member|a6
r_int
r_int
id|a6
suffix:semicolon
DECL|member|retpc
r_int
r_int
id|retpc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS            12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS            13
DECL|macro|PTRACE_GETFPREGS
mdefine_line|#define PTRACE_GETFPREGS          14
DECL|macro|PTRACE_SETFPREGS
mdefine_line|#define PTRACE_SETFPREGS          15
macro_line|#ifdef __KERNEL__
macro_line|#ifndef PS_S
DECL|macro|PS_S
mdefine_line|#define PS_S  (0x2000)
DECL|macro|PS_M
mdefine_line|#define PS_M  (0x1000)
macro_line|#endif
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!((regs)-&gt;sr &amp; PS_S))
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
macro_line|#endif /* _M68K_PTRACE_H */
eof
