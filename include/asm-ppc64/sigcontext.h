macro_line|#ifndef _ASM_PPC64_SIGCONTEXT_H
DECL|macro|_ASM_PPC64_SIGCONTEXT_H
mdefine_line|#define _ASM_PPC64_SIGCONTEXT_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|signal
r_int
id|signal
suffix:semicolon
DECL|member|_pad0
r_int
id|_pad0
suffix:semicolon
DECL|member|handler
r_int
r_int
id|handler
suffix:semicolon
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
DECL|member|gp_regs
id|elf_gregset_t
id|gp_regs
suffix:semicolon
DECL|member|fp_regs
id|elf_fpregset_t
id|fp_regs
suffix:semicolon
multiline_comment|/*&n; * To maintain compatibility with current implementations the sigcontext is &n; * extended by appending a pointer (v_regs) to a quadword type (elf_vrreg_t) &n; * followed by an unstructured (vmx_reserve) field of 69 doublewords.  This &n; * allows the array of vector registers to be quadword aligned independent of &n; * the alignment of the containing sigcontext or ucontext. It is the &n; * responsibility of the code setting the sigcontext to set this pointer to &n; * either NULL (if this processor does not support the VMX feature) or the &n; * address of the first quadword within the allocated (vmx_reserve) area.&n; *&n; * The pointer (v_regs) of vector type (elf_vrreg_t) is type compatible with &n; * an array of 34 quadword entries (elf_vrregset_t).  The entries with &n; * indexes 0-31 contain the corresponding vector registers.  The entry with &n; * index 32 contains the vscr as the last word (offset 12) within the &n; * quadword.  This allows the vscr to be stored as either a quadword (since &n; * it must be copied via a vector register to/from storage) or as a word.  &n; * The entry with index 33 contains the vrsave as the first word (offset 0) &n; * within the quadword.&n; */
DECL|member|v_regs
id|elf_vrreg_t
op_star
id|v_regs
suffix:semicolon
DECL|member|vmx_reserve
r_int
id|vmx_reserve
(braket
id|ELF_NVRREG
op_plus
id|ELF_NVRREG
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PPC64_SIGCONTEXT_H */
eof
