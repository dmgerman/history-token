macro_line|#ifndef _ASM_PARISC_UNALIGNED_H_
DECL|macro|_ASM_PARISC_UNALIGNED_H_
mdefine_line|#define _ASM_PARISC_UNALIGNED_H_
macro_line|#include &lt;asm-parisc/unaligned.h&gt;
macro_line|#ifdef __KERNEL__
r_struct
id|pt_regs
suffix:semicolon
r_void
id|handle_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|check_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_PARISC_UNALIGNED_H_ */
eof
