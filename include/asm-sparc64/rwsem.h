multiline_comment|/* $Id: rwsem.h,v 1.5 2001/11/18 00:12:56 davem Exp $&n; * rwsem.h: R/W semaphores implemented using CAS&n; *&n; * Written by David S. Miller (davem@redhat.com), 2001.&n; * Derived from asm-i386/rwsem.h&n; */
macro_line|#ifndef _SPARC64_RWSEM_H
DECL|macro|_SPARC64_RWSEM_H
mdefine_line|#define _SPARC64_RWSEM_H
macro_line|#ifndef _LINUX_RWSEM_H
macro_line|#error &quot;please don&squot;t include asm/rwsem.h directly, use linux/rwsem.h instead&quot;
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|rwsem_waiter
suffix:semicolon
DECL|struct|rw_semaphore
r_struct
id|rw_semaphore
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|macro|RWSEM_UNLOCKED_VALUE
mdefine_line|#define RWSEM_UNLOCKED_VALUE&t;&t;0x00000000
DECL|macro|RWSEM_ACTIVE_BIAS
mdefine_line|#define RWSEM_ACTIVE_BIAS&t;&t;0x00000001
DECL|macro|RWSEM_ACTIVE_MASK
mdefine_line|#define RWSEM_ACTIVE_MASK&t;&t;0x0000ffff
DECL|macro|RWSEM_WAITING_BIAS
mdefine_line|#define RWSEM_WAITING_BIAS&t;&t;0xffff0000
DECL|macro|RWSEM_ACTIVE_READ_BIAS
mdefine_line|#define RWSEM_ACTIVE_READ_BIAS&t;&t;RWSEM_ACTIVE_BIAS
DECL|macro|RWSEM_ACTIVE_WRITE_BIAS
mdefine_line|#define RWSEM_ACTIVE_WRITE_BIAS&t;&t;(RWSEM_WAITING_BIAS + RWSEM_ACTIVE_BIAS)
DECL|member|wait_lock
id|spinlock_t
id|wait_lock
suffix:semicolon
DECL|member|wait_list
r_struct
id|list_head
id|wait_list
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__RWSEM_INITIALIZER
mdefine_line|#define __RWSEM_INITIALIZER(name) &bslash;&n;{ RWSEM_UNLOCKED_VALUE, SPIN_LOCK_UNLOCKED, LIST_HEAD_INIT((name).wait_list) }
DECL|macro|DECLARE_RWSEM
mdefine_line|#define DECLARE_RWSEM(name) &bslash;&n;&t;struct rw_semaphore name = __RWSEM_INITIALIZER(name)
DECL|function|init_rwsem
r_static
id|__inline__
r_void
id|init_rwsem
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|sem-&gt;count
op_assign
id|RWSEM_UNLOCKED_VALUE
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sem-&gt;wait_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|sem-&gt;wait_list
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_int
id|__down_read_trylock
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_void
id|__down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_int
id|__down_write_trylock
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_void
id|__up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_void
id|__up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_void
id|__downgrade_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
DECL|function|rwsem_atomic_update
r_static
id|__inline__
r_int
id|rwsem_atomic_update
c_func
(paren
r_int
id|delta
comma
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|tmp
op_assign
id|delta
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;tlduw&t;[%2], %%g1&bslash;n&bslash;t&quot;
l_string|&quot;add&t;&t;%%g1, %1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%2], %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; membar&t;#StoreLoad | #StoreStore&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g7, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;r&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|tmp
op_plus
id|delta
suffix:semicolon
)brace
DECL|macro|rwsem_atomic_add
mdefine_line|#define rwsem_atomic_add rwsem_atomic_update
DECL|function|rwsem_cmpxchgw
r_static
id|__inline__
id|__u16
id|rwsem_cmpxchgw
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
id|__u16
id|__old
comma
id|__u16
id|__new
)paren
(brace
id|u32
id|old
op_assign
(paren
id|sem-&gt;count
op_amp
l_int|0xffff0000
)paren
op_or
(paren
id|u32
)paren
id|__old
suffix:semicolon
id|u32
r_new
op_assign
(paren
id|old
op_amp
l_int|0xffff0000
)paren
op_or
(paren
id|u32
)paren
id|__new
suffix:semicolon
id|u32
id|prev
suffix:semicolon
id|again
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cas&t;[%2], %3, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar&t;#StoreLoad | #StoreStore&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
r_new
)paren
comma
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;r&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* To give the same semantics as x86 cmpxchgw, keep trying&n;&t; * if only the upper 16-bits changed.&n;&t; */
r_if
c_cond
(paren
id|prev
op_ne
id|old
op_logical_and
(paren
(paren
id|prev
op_amp
l_int|0xffff
)paren
op_eq
(paren
id|old
op_amp
l_int|0xffff
)paren
)paren
)paren
r_goto
id|again
suffix:semicolon
r_return
id|prev
op_amp
l_int|0xffff
suffix:semicolon
)brace
DECL|function|rwsem_cmpxchg
r_static
id|__inline__
r_int
r_int
id|rwsem_cmpxchg
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
comma
r_int
r_int
id|old
comma
r_int
r_int
r_new
)paren
(brace
r_return
id|cmpxchg
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC64_RWSEM_H */
eof
