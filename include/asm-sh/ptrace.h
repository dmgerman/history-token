macro_line|#ifndef __ASM_SH_PTRACE_H
DECL|macro|__ASM_SH_PTRACE_H
mdefine_line|#define __ASM_SH_PTRACE_H
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ubc.h&gt;
multiline_comment|/*&n; * Copyright (C) 1999, 2000  Niibe Yutaka&n; *&n; */
multiline_comment|/*&n; * GCC defines register number like this:&n; * -----------------------------&n; *&t; 0 - 15 are integer registers&n; *&t;17 - 22 are control/special registers&n; *&t;24 - 39 fp registers&n; *&t;40 - 47 xd registers&n; *&t;48 -    fpscr register&n; * -----------------------------&n; *&n; * We follows above, except:&n; *&t;16 --- program counter (PC)&n; *&t;22 --- syscall #&n; *&t;23 --- floating point communication register&n; */
DECL|macro|REG_REG0
mdefine_line|#define REG_REG0&t; 0
DECL|macro|REG_REG15
mdefine_line|#define REG_REG15&t;15
DECL|macro|REG_PC
mdefine_line|#define REG_PC&t;&t;16
DECL|macro|REG_PR
mdefine_line|#define REG_PR&t;&t;17
DECL|macro|REG_SR
mdefine_line|#define REG_SR&t;&t;18
DECL|macro|REG_GBR
mdefine_line|#define REG_GBR      &t;19
DECL|macro|REG_MACH
mdefine_line|#define REG_MACH&t;20
DECL|macro|REG_MACL
mdefine_line|#define REG_MACL&t;21
DECL|macro|REG_SYSCALL
mdefine_line|#define REG_SYSCALL&t;22
DECL|macro|REG_FPUL
mdefine_line|#define REG_FPUL&t;23
DECL|macro|REG_FPREG0
mdefine_line|#define REG_FPREG0&t;24
DECL|macro|REG_FPREG15
mdefine_line|#define REG_FPREG15&t;39
DECL|macro|REG_XDREG0
mdefine_line|#define REG_XDREG0&t;40
DECL|macro|REG_XDREG14
mdefine_line|#define REG_XDREG14&t;47
DECL|macro|REG_FPSCR
mdefine_line|#define REG_FPSCR&t;48
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD     0x00000001
multiline_comment|/*&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|gbr
r_int
r_int
id|gbr
suffix:semicolon
DECL|member|mach
r_int
r_int
id|mach
suffix:semicolon
DECL|member|macl
r_int
r_int
id|macl
suffix:semicolon
DECL|member|tra
r_int
id|tra
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;sr &amp; 0x40000000)==0)
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
macro_line|#endif
macro_line|#endif /* __ASM_SH_PTRACE_H */
eof
