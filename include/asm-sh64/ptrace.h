macro_line|#ifndef __ASM_SH64_PTRACE_H
DECL|macro|__ASM_SH64_PTRACE_H
mdefine_line|#define __ASM_SH64_PTRACE_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/ptrace.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
multiline_comment|/*&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|pc
r_int
r_int
r_int
id|pc
suffix:semicolon
DECL|member|sr
r_int
r_int
r_int
id|sr
suffix:semicolon
DECL|member|syscall_nr
r_int
r_int
r_int
id|syscall_nr
suffix:semicolon
DECL|member|regs
r_int
r_int
r_int
id|regs
(braket
l_int|63
)braket
suffix:semicolon
DECL|member|tregs
r_int
r_int
r_int
id|tregs
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pad
r_int
r_int
r_int
id|pad
(braket
l_int|2
)braket
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
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD     0x00000001
macro_line|#endif /* __ASM_SH64_PTRACE_H */
eof
