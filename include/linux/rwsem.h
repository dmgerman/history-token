multiline_comment|/* rwsem.h: R/W semaphores, public interface&n; *&n; * Written by David Howells (dhowells@redhat.com).&n; * Derived from asm-i386/semaphore.h&n; */
macro_line|#ifndef _LINUX_RWSEM_H
DECL|macro|_LINUX_RWSEM_H
mdefine_line|#define _LINUX_RWSEM_H
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|RWSEM_DEBUG
mdefine_line|#define RWSEM_DEBUG 0
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_struct
id|rw_semaphore
suffix:semicolon
macro_line|#ifdef CONFIG_RWSEM_GENERIC_SPINLOCK
macro_line|#include &lt;linux/rwsem-spinlock.h&gt; /* use a generic implementation */
macro_line|#else
macro_line|#include &lt;asm/rwsem.h&gt; /* use an arch-specific implementation */
macro_line|#endif
macro_line|#ifndef rwsemtrace
macro_line|#if RWSEM_DEBUG
r_extern
r_void
id|FASTCALL
c_func
(paren
id|rwsemtrace
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_const
r_char
op_star
id|str
)paren
)paren
suffix:semicolon
macro_line|#else
DECL|macro|rwsemtrace
mdefine_line|#define rwsemtrace(SEM,FMT)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * lock for reading&n; */
DECL|function|down_read
r_static
r_inline
r_void
id|down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering down_read&quot;
)paren
suffix:semicolon
id|__down_read
c_func
(paren
id|sem
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving down_read&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lock for writing&n; */
DECL|function|down_write
r_static
r_inline
r_void
id|down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering down_write&quot;
)paren
suffix:semicolon
id|__down_write
c_func
(paren
id|sem
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving down_write&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * release a read lock&n; */
DECL|function|up_read
r_static
r_inline
r_void
id|up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering up_read&quot;
)paren
suffix:semicolon
id|__up_read
c_func
(paren
id|sem
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving up_read&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * release a write lock&n; */
DECL|function|up_write
r_static
r_inline
r_void
id|up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Entering up_write&quot;
)paren
suffix:semicolon
id|__up_write
c_func
(paren
id|sem
)paren
suffix:semicolon
id|rwsemtrace
c_func
(paren
id|sem
comma
l_string|&quot;Leaving up_write&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_RWSEM_H */
eof
