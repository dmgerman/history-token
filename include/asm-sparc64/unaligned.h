macro_line|#ifndef _ASM_SPARC64_UNALIGNED_H_
DECL|macro|_ASM_SPARC64_UNALIGNED_H_
mdefine_line|#define _ASM_SPARC64_UNALIGNED_H_
multiline_comment|/* Sparc can&squot;t handle unaligned accesses. */
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/* Use memmove here, so gcc does not insert a __builtin_memcpy. */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memmove(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memmove((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
macro_line|#endif /* _ASM_SPARC64_UNALIGNED_H */
eof
