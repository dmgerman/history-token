multiline_comment|/* Never include this file directly.  Include &lt;linux/compiler.h&gt; instead.  */
macro_line|#ifdef __ECC
multiline_comment|/* Some compiler specific definitions are overwritten here&n; * for Intel ECC compiler&n; */
macro_line|#include &lt;asm/intrinsics.h&gt;
multiline_comment|/* Intel ECC compiler doesn&squot;t support gcc specific asm stmts.&n; * It uses intrinsics to do the equivalent things.&n; */
DECL|macro|barrier
macro_line|#undef barrier
DECL|macro|RELOC_HIDE
macro_line|#undef RELOC_HIDE
DECL|macro|barrier
mdefine_line|#define barrier() __memory_barrier()
DECL|macro|RELOC_HIDE
mdefine_line|#define RELOC_HIDE(ptr, off)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __ptr;&t;&t;&t;&t;&t;&bslash;&n;     __ptr = (unsigned long) (ptr);&t;&t;&t;&t;&bslash;&n;    (typeof(ptr)) (__ptr + (off)); })
macro_line|#endif
eof
