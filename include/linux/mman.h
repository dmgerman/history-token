macro_line|#ifndef _LINUX_MMAN_H
DECL|macro|_LINUX_MMAN_H
mdefine_line|#define _LINUX_MMAN_H
macro_line|#include &lt;asm/mman.h&gt;
DECL|macro|MREMAP_MAYMOVE
mdefine_line|#define MREMAP_MAYMOVE&t;1
DECL|macro|MREMAP_FIXED
mdefine_line|#define MREMAP_FIXED&t;2
r_extern
r_int
id|vm_enough_memory
c_func
(paren
r_int
id|pages
)paren
suffix:semicolon
r_extern
r_void
id|vm_unacct_memory
c_func
(paren
r_int
id|pages
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_MMAN_H */
eof
