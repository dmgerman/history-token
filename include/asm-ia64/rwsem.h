multiline_comment|/*&n; * asm-ia64/rwsem.h: R/W semaphores for ia64&n; *&n; * Copyright (C) 2003 Ken Chen &lt;kenneth.w.chen@intel.com&gt;&n; * Copyright (C) 2003 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; *&n; * Based on asm-i386/rwsem.h and other architecture implementation.&n; *&n; * The MSW of the count is the negated number of active writers and&n; * waiting lockers, and the LSW is the total number of active locks.&n; *&n; * The lock count is initialized to 0 (no active and no waiting lockers).&n; *&n; * When a writer subtracts WRITE_BIAS, it&squot;ll get 0xffff0001 for the case&n; * of an uncontended lock. Readers increment by 1 and see a positive value&n; * when uncontended, negative if there are writers (and maybe) readers&n; * waiting (in which case it goes to sleep).&n; */
macro_line|#ifndef _ASM_IA64_RWSEM_H
DECL|macro|_ASM_IA64_RWSEM_H
mdefine_line|#define _ASM_IA64_RWSEM_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/*&n; * the semaphore definition&n; */
DECL|struct|rw_semaphore
r_struct
id|rw_semaphore
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|wait_lock
id|spinlock_t
id|wait_lock
suffix:semicolon
DECL|member|wait_list
r_struct
id|list_head
id|wait_list
suffix:semicolon
macro_line|#if RWSEM_DEBUG
DECL|member|debug
r_int
id|debug
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|RWSEM_UNLOCKED_VALUE
mdefine_line|#define RWSEM_UNLOCKED_VALUE&t;&t;0x00000000
DECL|macro|RWSEM_ACTIVE_BIAS
mdefine_line|#define RWSEM_ACTIVE_BIAS&t;&t;0x00000001
DECL|macro|RWSEM_ACTIVE_MASK
mdefine_line|#define RWSEM_ACTIVE_MASK&t;&t;0x0000ffff
DECL|macro|RWSEM_WAITING_BIAS
mdefine_line|#define RWSEM_WAITING_BIAS&t;&t;(-0x00010000)
DECL|macro|RWSEM_ACTIVE_READ_BIAS
mdefine_line|#define RWSEM_ACTIVE_READ_BIAS&t;&t;RWSEM_ACTIVE_BIAS
DECL|macro|RWSEM_ACTIVE_WRITE_BIAS
mdefine_line|#define RWSEM_ACTIVE_WRITE_BIAS&t;&t;(RWSEM_WAITING_BIAS + RWSEM_ACTIVE_BIAS)
multiline_comment|/*&n; * initialization&n; */
macro_line|#if RWSEM_DEBUG
DECL|macro|__RWSEM_DEBUG_INIT
mdefine_line|#define __RWSEM_DEBUG_INIT      , 0
macro_line|#else
DECL|macro|__RWSEM_DEBUG_INIT
mdefine_line|#define __RWSEM_DEBUG_INIT&t;/* */
macro_line|#endif
DECL|macro|__RWSEM_INITIALIZER
mdefine_line|#define __RWSEM_INITIALIZER(name) &bslash;&n;&t;{ RWSEM_UNLOCKED_VALUE, SPIN_LOCK_UNLOCKED, &bslash;&n;&t;  LIST_HEAD_INIT((name).wait_list) &bslash;&n;&t;  __RWSEM_DEBUG_INIT }
DECL|macro|DECLARE_RWSEM
mdefine_line|#define DECLARE_RWSEM(name) &bslash;&n;&t;struct rw_semaphore name = __RWSEM_INITIALIZER(name)
r_extern
r_struct
id|rw_semaphore
op_star
id|rwsem_down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|rwsem_down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|rwsem_downgrade_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|init_rwsem
id|init_rwsem
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
macro_line|#if RWSEM_DEBUG
id|sem-&gt;debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * lock for reading&n; */
r_static
r_inline
r_void
DECL|function|__down_read
id|__down_read
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;fetchadd4.acq %0=[%1],1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
id|rwsem_down_read_failed
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * lock for writing&n; */
r_static
r_inline
r_void
DECL|function|__down_write
id|__down_write
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|old
comma
r_new
suffix:semicolon
r_do
(brace
id|old
op_assign
id|sem-&gt;count
suffix:semicolon
r_new
op_assign
id|old
op_plus
id|RWSEM_ACTIVE_WRITE_BIAS
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_acq
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_ne
l_int|0
)paren
id|rwsem_down_write_failed
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unlock after reading&n; */
r_static
r_inline
r_void
DECL|function|__up_read
id|__up_read
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;fetchadd4.rel %0=[%1],-1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
op_logical_and
(paren
op_decrement
id|result
op_amp
id|RWSEM_ACTIVE_MASK
)paren
op_eq
l_int|0
)paren
id|rwsem_wake
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unlock after writing&n; */
r_static
r_inline
r_void
DECL|function|__up_write
id|__up_write
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|old
comma
r_new
suffix:semicolon
r_do
(brace
id|old
op_assign
id|sem-&gt;count
suffix:semicolon
r_new
op_assign
id|old
op_minus
id|RWSEM_ACTIVE_WRITE_BIAS
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_rel
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
OL
l_int|0
op_logical_and
(paren
r_new
op_amp
id|RWSEM_ACTIVE_MASK
)paren
op_eq
l_int|0
)paren
id|rwsem_wake
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * trylock for reading -- returns 1 if successful, 0 if contention&n; */
r_static
r_inline
r_int
DECL|function|__down_read_trylock
id|__down_read_trylock
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tmp
op_assign
id|sem-&gt;count
)paren
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tmp
op_eq
id|cmpxchg_acq
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|tmp
comma
id|tmp
op_plus
l_int|1
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * trylock for writing -- returns 1 if successful, 0 if contention&n; */
r_static
r_inline
r_int
DECL|function|__down_write_trylock
id|__down_write_trylock
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|tmp
op_assign
id|cmpxchg_acq
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|RWSEM_UNLOCKED_VALUE
comma
id|RWSEM_ACTIVE_WRITE_BIAS
)paren
suffix:semicolon
r_return
id|tmp
op_eq
id|RWSEM_UNLOCKED_VALUE
suffix:semicolon
)brace
multiline_comment|/*&n; * downgrade write lock to read lock&n; */
r_static
r_inline
r_void
DECL|function|__downgrade_write
id|__downgrade_write
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|old
comma
r_new
suffix:semicolon
r_do
(brace
id|old
op_assign
id|sem-&gt;count
suffix:semicolon
r_new
op_assign
id|old
op_minus
id|RWSEM_WAITING_BIAS
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg_rel
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|old
comma
r_new
)paren
op_ne
id|old
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
OL
l_int|0
)paren
id|rwsem_downgrade_wake
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Implement atomic add functionality.  These used to be &quot;inline&quot; functions, but GCC v3.1&n; * doesn&squot;t quite optimize this stuff right and ends up with bad calls to fetchandadd.&n; */
DECL|macro|rwsem_atomic_add
mdefine_line|#define rwsem_atomic_add(delta, sem)&t;atomic_add(delta, (atomic_t *)(&amp;(sem)-&gt;count))
DECL|macro|rwsem_atomic_update
mdefine_line|#define rwsem_atomic_update(delta, sem)&t;atomic_add_return(delta, (atomic_t *)(&amp;(sem)-&gt;count))
macro_line|#endif /* _ASM_IA64_RWSEM_H */
eof
