macro_line|#ifndef _ASM_GENERIC_UNALIGNED_H_
DECL|macro|_ASM_GENERIC_UNALIGNED_H_
mdefine_line|#define _ASM_GENERIC_UNALIGNED_H_
multiline_comment|/*&n; * For the benefit of those who are trying to port Linux to another&n; * architecture, here are some C-language equivalents. &n; */
macro_line|#include &lt;asm/string.h&gt;
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memcpy(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memcpy((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
macro_line|#endif /* _ASM_GENERIC_UNALIGNED_H */
eof
