multiline_comment|/* rwsem.h: R/W semaphores based on spinlocks&n; *&n; * Written by David Howells (dhowells@redhat.com).&n; *&n; * Derived from asm-i386/semaphore.h&n; */
macro_line|#ifndef _I386_RWSEM_H
DECL|macro|_I386_RWSEM_H
mdefine_line|#define _I386_RWSEM_H
macro_line|#ifndef _LINUX_RWSEM_H
macro_line|#error please dont include asm/rwsem.h directly, use linux/rwsem.h instead
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|__HAVE_ARCH_SPECIFIC_RWSEM_IMPLEMENTATION
mdefine_line|#define __HAVE_ARCH_SPECIFIC_RWSEM_IMPLEMENTATION 1
macro_line|#ifdef CONFIG_X86_XADD
macro_line|#include &lt;asm/rwsem-xadd.h&gt; /* use XADD based semaphores if possible */
macro_line|#else
macro_line|#include &lt;asm/rwsem-spin.h&gt; /* use optimised spinlock based semaphores otherwise */
macro_line|#endif
multiline_comment|/* we use FASTCALL convention for the helpers */
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|__rwsem_down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|__rwsem_down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|__rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I386_RWSEM_H */
eof
