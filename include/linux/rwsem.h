multiline_comment|/* rwsem.h: R/W semaphores, public interface&n; *&n; * Written by David Howells (dhowells@redhat.com).&n; * Derived from asm-i386/semaphore.h&n; *&n; *&n; * The MSW of the count is the negated number of active writers and waiting&n; * lockers, and the LSW is the total number of active locks&n; *&n; * The lock count is initialized to 0 (no active and no waiting lockers).&n; *&n; * When a writer subtracts WRITE_BIAS, it&squot;ll get 0xffff0001 for the case of an&n; * uncontended lock. This can be determined because XADD returns the old value.&n; * Readers increment by 1 and see a positive value when uncontended, negative&n; * if there are writers (and maybe) readers waiting (in which case it goes to&n; * sleep).&n; *&n; * The value of WAITING_BIAS supports up to 32766 waiting processes. This can&n; * be extended to 65534 by manually checking the whole MSW rather than relying&n; * on the S flag.&n; *&n; * The value of ACTIVE_BIAS supports up to 65535 active processes.&n; *&n; * This should be totally fair - if anything is waiting, a process that wants a&n; * lock will go to the back of the queue. When the currently active lock is&n; * released, if there&squot;s a writer at the front of the queue, then that and only&n; * that will be woken up; if there&squot;s a bunch of consequtive readers at the&n; * front, then they&squot;ll all be woken up, but no other readers will be.&n; */
macro_line|#ifndef _LINUX_RWSEM_H
DECL|macro|_LINUX_RWSEM_H
mdefine_line|#define _LINUX_RWSEM_H
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|RWSEM_DEBUG
mdefine_line|#define RWSEM_DEBUG 0
DECL|macro|RWSEM_DEBUG_MAGIC
mdefine_line|#define RWSEM_DEBUG_MAGIC 0
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#ifdef CONFIG_RWSEM_GENERIC_SPINLOCK
macro_line|#include &lt;linux/rwsem-spinlock.h&gt; /* use a generic implementation */
macro_line|#else
macro_line|#include &lt;asm/rwsem.h&gt; /* use an arch-specific implementation */
macro_line|#endif
multiline_comment|/* defined contention handler functions for the generic case&n; * - these are also used for the exchange-and-add based algorithm&n; */
macro_line|#if defined(CONFIG_RWSEM_GENERIC) || defined(CONFIG_RWSEM_XCHGADD_ALGORITHM)
multiline_comment|/* we use FASTCALL convention for the helpers */
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_down_read_failed
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
id|rwsem_down_write_failed
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
id|rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef rwsemtrace
macro_line|#if RWSEM_DEBUG
macro_line|#include &lt;asm/current.h&gt;
DECL|macro|rwsemtrace
mdefine_line|#define rwsemtrace(SEM,FMT) do { if ((SEM)-&gt;debug) printk(&quot;[%d] &quot;FMT&quot;(count=%08lx)&bslash;n&quot;,current-&gt;pid,(SEM)-&gt;count); } while(0)
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
macro_line|#if RWSEM_DEBUG_MAGIC
r_if
c_cond
(paren
id|sem-&gt;__magic
op_ne
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__down_read
c_func
(paren
id|sem
)paren
suffix:semicolon
macro_line|#if RWSEM_DEBUG_MAGIC
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if RWSEM_DEBUG_MAGIC
r_if
c_cond
(paren
id|sem-&gt;__magic
op_ne
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__down_write
c_func
(paren
id|sem
)paren
suffix:semicolon
macro_line|#if RWSEM_DEBUG_MAGIC
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if RWSEM_DEBUG_MAGIC
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if RWSEM_DEBUG_MAGIC
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;readers
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
op_ne
l_int|1
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sem-&gt;writers
)paren
suffix:semicolon
macro_line|#endif
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
