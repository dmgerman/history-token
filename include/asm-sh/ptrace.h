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
DECL|macro|REG_FPREG0
mdefine_line|#define REG_FPREG0&t;23
DECL|macro|REG_FPREG15
mdefine_line|#define REG_FPREG15&t;38
DECL|macro|REG_XFREG0
mdefine_line|#define REG_XFREG0&t;39
DECL|macro|REG_XFREG15
mdefine_line|#define REG_XFREG15&t;54
DECL|macro|REG_FPSCR
mdefine_line|#define REG_FPSCR&t;55
DECL|macro|REG_FPUL
mdefine_line|#define REG_FPUL&t;56
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
multiline_comment|/*&n; * This struct defines the way the DSP registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; */
DECL|struct|pt_dspregs
r_struct
id|pt_dspregs
(brace
DECL|member|a1
r_int
r_int
id|a1
suffix:semicolon
DECL|member|a0g
r_int
r_int
id|a0g
suffix:semicolon
DECL|member|a1g
r_int
r_int
id|a1g
suffix:semicolon
DECL|member|m0
r_int
r_int
id|m0
suffix:semicolon
DECL|member|m1
r_int
r_int
id|m1
suffix:semicolon
DECL|member|a0
r_int
r_int
id|a0
suffix:semicolon
DECL|member|x0
r_int
r_int
id|x0
suffix:semicolon
DECL|member|x1
r_int
r_int
id|x1
suffix:semicolon
DECL|member|y0
r_int
r_int
id|y0
suffix:semicolon
DECL|member|y1
r_int
r_int
id|y1
suffix:semicolon
DECL|member|dsr
r_int
r_int
id|dsr
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:semicolon
DECL|member|mod
r_int
r_int
id|mod
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PTRACE_GETDSPREGS
mdefine_line|#define&t;PTRACE_GETDSPREGS&t;55
DECL|macro|PTRACE_SETDSPREGS
mdefine_line|#define&t;PTRACE_SETDSPREGS&t;56
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
