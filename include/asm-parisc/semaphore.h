macro_line|#ifndef _ASM_PARISC_SEMAPHORE_H
DECL|macro|_ASM_PARISC_SEMAPHORE_H
mdefine_line|#define _ASM_PARISC_SEMAPHORE_H
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores.&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * PA-RISC version by Matthew Wilcox&n; *&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * The `count&squot; is initialised to the number of people who are allowed to&n; * take the lock.  (Normally we want a mutex, so this is `1&squot;).  if&n; * `count&squot; is positive, the lock can be taken.  if it&squot;s 0, no-one is&n; * waiting on it.  if it&squot;s -1, at least one task is waiting.&n; */
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|sentry
id|spinlock_t
id|sentry
suffix:semicolon
DECL|member|count
r_int
id|count
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
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ SPIN_LOCK_UNLOCKED, count, __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) &bslash;&n;&t;__SEMAPHORE_INITIALIZER(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count) &bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name) __DECLARE_SEMAPHORE_GENERIC(name,1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name) __DECLARE_SEMAPHORE_GENERIC(name,0)
DECL|function|sema_init
r_extern
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
(paren
op_star
id|sem
)paren
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
DECL|function|sem_getcount
r_static
r_inline
r_int
id|sem_getcount
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_return
id|sem-&gt;count
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
multiline_comment|/* Semaphores can be `tried&squot; from irq context.  So we have to disable&n; * interrupts while we&squot;re messing with the semaphore.  Sorry.&n; */
DECL|function|down
r_extern
id|__inline__
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
id|spin_lock_irq
c_func
(paren
op_amp
id|sem-&gt;sentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;count
OG
l_int|0
)paren
(brace
id|sem-&gt;count
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|__down
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|sem-&gt;sentry
)paren
suffix:semicolon
)brace
DECL|function|down_interruptible
r_extern
id|__inline__
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
id|spin_lock_irq
c_func
(paren
op_amp
id|sem-&gt;sentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;count
OG
l_int|0
)paren
(brace
id|sem-&gt;count
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|__down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|sem-&gt;sentry
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * down_trylock returns 0 on success, 1 if we failed to get the lock.&n; * May not sleep, but must preserve irq state&n; */
DECL|function|down_trylock
r_extern
id|__inline__
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
id|flags
comma
id|count
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;sentry
comma
id|flags
)paren
suffix:semicolon
id|count
op_assign
id|sem-&gt;count
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
l_int|0
)paren
id|sem-&gt;count
op_assign
id|count
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;sentry
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|count
OL
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; */
DECL|function|up
r_extern
id|__inline__
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
r_int
id|flags
suffix:semicolon
macro_line|#if WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;sentry
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sem-&gt;count
OL
l_int|0
)paren
(brace
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_else
(brace
id|sem-&gt;count
op_increment
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;sentry
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_PARISC_SEMAPHORE_H */
eof
