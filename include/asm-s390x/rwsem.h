macro_line|#ifndef _S390X_RWSEM_H
DECL|macro|_S390X_RWSEM_H
mdefine_line|#define _S390X_RWSEM_H
multiline_comment|/*&n; *  include/asm-s390x/rwsem.h&n; *&n; *  S390 version&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Based on asm-alpha/semaphore.h and asm-i386/rwsem.h&n; */
multiline_comment|/*&n; *&n; * The MSW of the count is the negated number of active writers and waiting&n; * lockers, and the LSW is the total number of active locks&n; *&n; * The lock count is initialized to 0 (no active and no waiting lockers).&n; *&n; * When a writer subtracts WRITE_BIAS, it&squot;ll get 0xffff0001 for the case of an&n; * uncontended lock. This can be determined because XADD returns the old value.&n; * Readers increment by 1 and see a positive value when uncontended, negative&n; * if there are writers (and maybe) readers waiting (in which case it goes to&n; * sleep).&n; *&n; * The value of WAITING_BIAS supports up to 32766 waiting processes. This can&n; * be extended to 65534 by manually checking the whole MSW rather than relying&n; * on the S flag.&n; *&n; * The value of ACTIVE_BIAS supports up to 65535 active processes.&n; *&n; * This should be totally fair - if anything is waiting, a process that wants a&n; * lock will go to the back of the queue. When the currently active lock is&n; * released, if there&squot;s a writer at the front of the queue, then that and only&n; * that will be woken up; if there&squot;s a bunch of consequtive readers at the&n; * front, then they&squot;ll all be woken up, but no other readers will be.&n; */
macro_line|#ifndef _LINUX_RWSEM_H
macro_line|#error please dont include asm/rwsem.h directly, use linux/rwsem.h instead
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|rwsem_waiter
suffix:semicolon
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
)paren
suffix:semicolon
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
)brace
suffix:semicolon
DECL|macro|RWSEM_UNLOCKED_VALUE
mdefine_line|#define RWSEM_UNLOCKED_VALUE&t;0x0000000000000000L
DECL|macro|RWSEM_ACTIVE_BIAS
mdefine_line|#define RWSEM_ACTIVE_BIAS&t;0x0000000000000001L
DECL|macro|RWSEM_ACTIVE_MASK
mdefine_line|#define RWSEM_ACTIVE_MASK&t;0x00000000ffffffffL
DECL|macro|RWSEM_WAITING_BIAS
mdefine_line|#define RWSEM_WAITING_BIAS&t;(-0x0000000100000000L)
DECL|macro|RWSEM_ACTIVE_READ_BIAS
mdefine_line|#define RWSEM_ACTIVE_READ_BIAS&t;RWSEM_ACTIVE_BIAS
DECL|macro|RWSEM_ACTIVE_WRITE_BIAS
mdefine_line|#define RWSEM_ACTIVE_WRITE_BIAS&t;(RWSEM_WAITING_BIAS + RWSEM_ACTIVE_BIAS)
multiline_comment|/*&n; * initialisation&n; */
DECL|macro|__RWSEM_INITIALIZER
mdefine_line|#define __RWSEM_INITIALIZER(name) &bslash;&n;{ RWSEM_UNLOCKED_VALUE, SPIN_LOCK_UNLOCKED, LIST_HEAD_INIT((name).wait_list) }
DECL|macro|DECLARE_RWSEM
mdefine_line|#define DECLARE_RWSEM(name) &bslash;&n;&t;struct rw_semaphore name = __RWSEM_INITIALIZER(name)
DECL|function|init_rwsem
r_static
r_inline
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
multiline_comment|/*&n; * lock for reading&n; */
DECL|function|__down_read
r_static
r_inline
r_void
id|__down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|old
comma
r_new
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lg   %0,0(%2)&bslash;n&quot;
l_string|&quot;0: lgr  %1,%0&bslash;n&quot;
l_string|&quot;   aghi %1,%3&bslash;n&quot;
l_string|&quot;   csg  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;   jl   0b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_ACTIVE_READ_BIAS
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
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
DECL|function|__down_write
r_static
r_inline
r_void
id|__down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|tmp
suffix:semicolon
id|tmp
op_assign
id|RWSEM_ACTIVE_WRITE_BIAS
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lg   %0,0(%2)&bslash;n&quot;
l_string|&quot;0: lgr  %1,%0&bslash;n&quot;
l_string|&quot;   ag   %1,%3&bslash;n&quot;
l_string|&quot;   csg  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;   jl   0b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;m&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
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
DECL|function|__up_read
r_static
r_inline
r_void
id|__up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|old
comma
r_new
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lg   %0,0(%2)&bslash;n&quot;
l_string|&quot;0: lgr  %1,%0&bslash;n&quot;
l_string|&quot;   aghi %1,%3&bslash;n&quot;
l_string|&quot;   csg  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;   jl   0b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|RWSEM_ACTIVE_READ_BIAS
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
OL
l_int|0
)paren
r_if
c_cond
(paren
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
multiline_comment|/*&n; * unlock after writing&n; */
DECL|function|__up_write
r_static
r_inline
r_void
id|__up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|old
comma
r_new
comma
id|tmp
suffix:semicolon
id|tmp
op_assign
op_minus
id|RWSEM_ACTIVE_WRITE_BIAS
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lg   %0,0(%2)&bslash;n&quot;
l_string|&quot;0: lgr  %1,%0&bslash;n&quot;
l_string|&quot;   ag   %1,%3&bslash;n&quot;
l_string|&quot;   csg  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;   jl   0b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;m&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
OL
l_int|0
)paren
r_if
c_cond
(paren
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
multiline_comment|/*&n; * implement atomic add functionality&n; */
DECL|function|rwsem_atomic_add
r_static
r_inline
r_void
id|rwsem_atomic_add
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
r_int
id|old
comma
r_new
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lg   %0,0(%2)&bslash;n&quot;
l_string|&quot;0: lgr  %1,%0&bslash;n&quot;
l_string|&quot;   agr  %1,%3&bslash;n&quot;
l_string|&quot;   csg  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;   jl   0b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;d&quot;
(paren
id|delta
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * implement exchange and add functionality&n; */
DECL|function|rwsem_atomic_update
r_static
r_inline
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
r_int
id|old
comma
r_new
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lg   %0,0(%2)&bslash;n&quot;
l_string|&quot;0: lgr  %1,%0&bslash;n&quot;
l_string|&quot;   agr  %1,%3&bslash;n&quot;
l_string|&quot;   csg  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;   jl   0b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count
)paren
comma
l_string|&quot;d&quot;
(paren
id|delta
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _S390X_RWSEM_H */
eof
