macro_line|#ifndef _ASM_PARISC_UNALIGNED_H_
DECL|macro|_ASM_PARISC_UNALIGNED_H_
mdefine_line|#define _ASM_PARISC_UNALIGNED_H_
multiline_comment|/* parisc can&squot;t handle unaligned accesses. */
multiline_comment|/* copied from asm-sparc/unaligned.h */
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/* Use memmove here, so gcc does not insert a __builtin_memcpy. */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memmove(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memmove((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
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
