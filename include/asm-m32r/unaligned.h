macro_line|#ifndef _ASM_M32R_UNALIGNED_H
DECL|macro|_ASM_M32R_UNALIGNED_H
mdefine_line|#define _ASM_M32R_UNALIGNED_H
multiline_comment|/* $Id$ */
multiline_comment|/* orig : generic 2.4.18 */
multiline_comment|/*&n; * For the benefit of those who are trying to port Linux to another&n; * architecture, here are some C-language equivalents.&n; */
macro_line|#include &lt;asm/string.h&gt;
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memmove(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memmove((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
macro_line|#endif  /* _ASM_M32R_UNALIGNED_H */
eof
