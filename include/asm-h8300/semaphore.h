macro_line|#ifndef _H8300_SEMAPHORE_H
DECL|macro|_H8300_SEMAPHORE_H
mdefine_line|#define _H8300_SEMAPHORE_H
DECL|macro|RW_LOCK_BIAS
mdefine_line|#define RW_LOCK_BIAS&t;&t; 0x01000000
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * Interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * H8/300 version by Yoshinori Sato&n; */
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|sleepers
r_int
id|sleepers
suffix:semicolon
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
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC_INIT(count), 0, __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
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
op_star
id|sem
op_assign
(paren
r_struct
id|semaphore
)paren
id|__SEMAPHORE_INITIALIZER
c_func
(paren
op_star
id|sem
comma
id|val
)paren
suffix:semicolon
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
id|__down_failed
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_failed_interruptible
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_failed_trylock
c_func
(paren
r_void
multiline_comment|/* params in registers */
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up_wakeup
c_func
(paren
r_void
multiline_comment|/* special register calling convention */
)paren
suffix:semicolon
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
r_extern
id|spinlock_t
id|semaphore_wake_lock
suffix:semicolon
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;down_failed&quot; is a special asm handler that calls the C&n; * routine that actually waits. See arch/m68k/lib/semaphore.S&n; */
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
r_register
id|atomic_t
op_star
id|count
id|asm
c_func
(paren
l_string|&quot;er0&quot;
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|count
op_assign
op_amp
(paren
id|sem-&gt;count
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc ccr,r3l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0, er1&bslash;n&bslash;t&quot;
l_string|&quot;dec.l #1,er1&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er1,%0&bslash;n&bslash;t&quot;
l_string|&quot;bpl 1f&bslash;n&bslash;t&quot;
l_string|&quot;ldc r3l,ccr&bslash;n&bslash;t&quot;
l_string|&quot;jsr @___down&bslash;n&bslash;t&quot;
l_string|&quot;bra 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;ldc r3l,ccr&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|count
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
comma
l_string|&quot;er3&quot;
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
r_register
id|atomic_t
op_star
id|count
id|asm
c_func
(paren
l_string|&quot;er0&quot;
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|count
op_assign
op_amp
(paren
id|sem-&gt;count
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc ccr,r1l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1, er2&bslash;n&bslash;t&quot;
l_string|&quot;dec.l #1,er2&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er2,%1&bslash;n&bslash;t&quot;
l_string|&quot;bpl 1f&bslash;n&bslash;t&quot;
l_string|&quot;ldc r1l,ccr&bslash;n&bslash;t&quot;
l_string|&quot;jsr @___down_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;bra 2f&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;ldc r1l,ccr&bslash;n&bslash;t&quot;
l_string|&quot;sub.l %0,%0&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|count
)paren
comma
l_string|&quot;+m&quot;
(paren
op_star
id|count
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
comma
l_string|&quot;er3&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|count
suffix:semicolon
)brace
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
r_register
id|atomic_t
op_star
id|count
id|asm
c_func
(paren
l_string|&quot;er0&quot;
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|count
op_assign
op_amp
(paren
id|sem-&gt;count
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc ccr,r3l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0,er2&bslash;n&bslash;t&quot;
l_string|&quot;dec.l #1,er2&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er2,%0&bslash;n&bslash;t&quot;
l_string|&quot;bpl 1f&bslash;n&bslash;t&quot;
l_string|&quot;ldc r3l,ccr&bslash;n&bslash;t&quot;
l_string|&quot;jmp @3f&bslash;n&bslash;t&quot;
id|LOCK_SECTION_START
c_func
(paren
l_string|&quot;.align 2&bslash;n&bslash;t&quot;
)paren
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;jsr @___down_trylock&bslash;n&bslash;t&quot;
l_string|&quot;jmp @2f&bslash;n&bslash;t&quot;
id|LOCK_SECTION_END
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;ldc r3l,ccr&bslash;n&bslash;t&quot;
l_string|&quot;sub.l %1,%1&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|count
)paren
comma
l_string|&quot;=r&quot;
(paren
id|count
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
comma
l_string|&quot;er3&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; * The default case (no contention) will result in NO&n; * jumps for both down() and up().&n; */
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
r_register
id|atomic_t
op_star
id|count
id|asm
c_func
(paren
l_string|&quot;er0&quot;
)paren
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|count
op_assign
op_amp
(paren
id|sem-&gt;count
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc ccr,r3l&bslash;n&bslash;t&quot;
l_string|&quot;orc #0x80,ccr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %0,er1&bslash;n&bslash;t&quot;
l_string|&quot;inc.l #1,er1&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ldc r3l,ccr&bslash;n&bslash;t&quot;
l_string|&quot;sub.l er2,er2&bslash;n&bslash;t&quot;
l_string|&quot;cmp.l er2,er1&bslash;n&bslash;t&quot;
l_string|&quot;bgt 1f&bslash;n&bslash;t&quot;
l_string|&quot;jsr @___up&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|count
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
comma
l_string|&quot;er3&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
