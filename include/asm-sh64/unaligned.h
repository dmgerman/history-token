macro_line|#ifndef __ASM_SH64_UNALIGNED_H
DECL|macro|__ASM_SH64_UNALIGNED_H
mdefine_line|#define __ASM_SH64_UNALIGNED_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/unaligned.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/* Use memmove here, so gcc does not insert a __builtin_memcpy. */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;  ({ __typeof__(*(ptr)) __tmp; memmove(&amp;__tmp, (ptr), sizeof(*(ptr))); __tmp; })
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr)&t;&t;&t;&t;&bslash;&n;  ({ __typeof__(*(ptr)) __tmp = (val);&t;&t;&t;&bslash;&n;     memmove((ptr), &amp;__tmp, sizeof(*(ptr)));&t;&t;&bslash;&n;     (void)0; })
macro_line|#endif /* __ASM_SH64_UNALIGNED_H */
eof
