multiline_comment|/*&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996  Linus Torvalds&n; * Copyright (C) 1998, 1999, 2000  Ralf Baechle&n; * Copyright (C) 1999, 2000  Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SEMAPHORE_H
DECL|macro|_ASM_SEMAPHORE_H
mdefine_line|#define _ASM_SEMAPHORE_H
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
DECL|struct|semaphore
r_struct
id|semaphore
(brace
macro_line|#ifdef __MIPSEB__
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|waking
id|atomic_t
id|waking
suffix:semicolon
macro_line|#else
id|atomic_t
id|waking
suffix:semicolon
id|atomic_t
id|count
suffix:semicolon
macro_line|#endif
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name) &bslash;&n;&t;&t;, (long)&amp;(name).__magic
macro_line|#else
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name)
macro_line|#endif
macro_line|#ifdef __MIPSEB__
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC_INIT(count), ATOMIC_INIT(0), __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
macro_line|#else
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC_INIT(0), ATOMIC_INIT(count), __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
macro_line|#endif
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) &bslash;&n;&t;__SEMAPHORE_INITIALIZER(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count) &bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name) __DECLARE_SEMAPHORE_GENERIC(name,1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name) __DECLARE_SEMAPHORE_GENERIC(name,0)
DECL|function|sema_init
r_static
r_inline
r_void
id|sema_init
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_int
id|val
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|val
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;waking
comma
l_int|0
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|sem-&gt;__magic
op_assign
(paren
r_int
)paren
op_amp
id|sem-&gt;__magic
suffix:semicolon
macro_line|#endif
)brace
DECL|function|init_MUTEX
r_static
r_inline
r_void
id|init_MUTEX
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sema_init
c_func
(paren
id|sem
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|init_MUTEX_LOCKED
r_static
r_inline
r_void
id|init_MUTEX_LOCKED
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|sema_init
c_func
(paren
id|sem
comma
l_int|0
)paren
suffix:semicolon
)brace
id|asmlinkage
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
DECL|function|down
r_static
r_inline
r_void
id|down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
OL
l_int|0
)paren
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
DECL|function|down_interruptible
r_static
r_inline
r_int
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
OL
l_int|0
)paren
id|ret
op_assign
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * down_trylock returns 0 on success, 1 if we failed to get the lock.&n; *&n; * We must manipulate count and waking simultaneously and atomically.&n; * Here, we this by using ll/sc on the pair of 32-bit words.&n; *&n; * Pseudocode:&n; *&n; *   Decrement(sem-&gt;count)&n; *   If(sem-&gt;count &gt;=0) {&n; *&t;Return(SUCCESS)&t;&t;&t;// resource is free&n; *   } else {&n; *&t;If(sem-&gt;waking &lt;= 0) {&t;&t;// if no wakeup pending&n; *&t;   Increment(sem-&gt;count)&t;// undo decrement&n; *&t;   Return(FAILURE)&n; *      } else {&n; *&t;   Decrement(sem-&gt;waking)&t;// otherwise &quot;steal&quot; wakeup&n; *&t;   Return(SUCCESS)&n; *&t;}&n; *   }&n; */
DECL|function|down_trylock
r_static
r_inline
r_int
id|down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
comma
id|tmp
comma
id|tmp2
comma
id|sub
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
dot
id|set
id|mips3
l_int|0
suffix:colon
id|lld
op_mod
l_int|1
comma
op_mod
l_int|4
id|dli
op_mod
l_int|3
comma
l_int|0x0000000100000000
id|dsubu
op_mod
l_int|1
comma
op_mod
l_int|3
id|li
op_mod
l_int|0
comma
l_int|0
id|bgez
op_mod
l_int|1
comma
l_float|2f
id|sll
op_mod
l_int|2
comma
op_mod
l_int|1
comma
l_int|0
id|blez
op_mod
l_int|2
comma
l_float|1f
id|daddiu
op_mod
l_int|1
comma
op_mod
l_int|1
comma
op_minus
l_int|1
id|b
l_float|2f
l_int|1
suffix:colon
id|daddu
op_mod
l_int|1
comma
op_mod
l_int|1
comma
op_mod
l_int|3
id|li
op_mod
l_int|0
comma
l_int|1
l_int|2
suffix:colon
id|scd
op_mod
l_int|1
comma
op_mod
l_int|4
id|beqz
op_mod
l_int|1
comma
l_int|0
id|b
dot
id|set
id|mips0
"&quot;"
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|sub
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|sem
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; */
DECL|function|up
r_static
r_inline
r_void
id|up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|atomic_inc_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
op_le
l_int|0
)paren
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SEMAPHORE_H */
eof
