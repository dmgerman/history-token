macro_line|#ifndef _LINUX_MMAN_H
DECL|macro|_LINUX_MMAN_H
mdefine_line|#define _LINUX_MMAN_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
DECL|macro|MREMAP_MAYMOVE
mdefine_line|#define MREMAP_MAYMOVE&t;1
DECL|macro|MREMAP_FIXED
mdefine_line|#define MREMAP_FIXED&t;2
r_extern
r_int
id|sysctl_overcommit_memory
suffix:semicolon
r_extern
r_int
id|sysctl_overcommit_ratio
suffix:semicolon
r_extern
id|atomic_t
id|vm_committed_space
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|vm_acct_memory
c_func
(paren
r_int
id|pages
)paren
suffix:semicolon
macro_line|#else
DECL|function|vm_acct_memory
r_static
r_inline
r_void
id|vm_acct_memory
c_func
(paren
r_int
id|pages
)paren
(brace
id|atomic_add
c_func
(paren
id|pages
comma
op_amp
id|vm_committed_space
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|vm_unacct_memory
r_static
r_inline
r_void
id|vm_unacct_memory
c_func
(paren
r_int
id|pages
)paren
(brace
id|vm_acct_memory
c_func
(paren
op_minus
id|pages
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_MMAN_H */
eof
