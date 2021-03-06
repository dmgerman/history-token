macro_line|#ifndef _M68K_SEMAPHORE_H
DECL|macro|_M68K_SEMAPHORE_H
mdefine_line|#define _M68K_SEMAPHORE_H
DECL|macro|RW_LOCK_BIAS
mdefine_line|#define RW_LOCK_BIAS&t;&t; 0x01000000
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * Interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; *&n; * m68k version by Andreas Schwab&n; */
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|waking
id|atomic_t
id|waking
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name, n)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(n),&t;&t;&t;&t;&bslash;&n;&t;.waking&t;&t;= ATOMIC_INIT(0),&t;&t;&t;&t;&bslash;&n;&t;.wait&t;&t;= __WAIT_QUEUE_HEAD_INITIALIZER((name).wait)&t;&bslash;&n;}
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
r_extern
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic down operation&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%0, %%a1&bslash;n&bslash;t&quot;
l_string|&quot;lea&t;%%pc@(1f), %%a0&bslash;n&bslash;t&quot;
l_string|&quot;subql&t;#1, %%a1@&bslash;n&bslash;t&quot;
l_string|&quot;jmi __down_failed&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;g&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;%a0&quot;
comma
l_string|&quot;%a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|down_interruptible
r_extern
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
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic down operation&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%1, %%a1&bslash;n&bslash;t&quot;
l_string|&quot;lea&t;%%pc@(1f), %%a0&bslash;n&bslash;t&quot;
l_string|&quot;subql&t;#1, %%a1@&bslash;n&bslash;t&quot;
l_string|&quot;jmi __down_failed_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;clrl&t;%%d0&bslash;n&quot;
l_string|&quot;1: movel&t;%%d0, %0&bslash;n&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;%d0&quot;
comma
l_string|&quot;%a0&quot;
comma
l_string|&quot;%a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|down_trylock
r_extern
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
r_struct
id|semaphore
op_star
id|sem1
id|__asm__
(paren
l_string|&quot;%a1&quot;
)paren
op_assign
id|sem
suffix:semicolon
r_register
r_int
id|result
id|__asm__
(paren
l_string|&quot;%d0&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic down trylock operation&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1@&bslash;n&bslash;t&quot;
l_string|&quot;jmi 2f&bslash;n&bslash;t&quot;
l_string|&quot;clrl %0&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;.even&bslash;n&quot;
l_string|&quot;2:&bslash;tpea 1b&bslash;n&bslash;t&quot;
l_string|&quot;jbra __down_failed_trylock&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|sem1
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Note! This is subtle. We jump to wake people up only if&n; * the semaphore was negative (== somebody was waiting on it).&n; * The default case (no contention) will result in NO&n; * jumps for both down() and up().&n; */
DECL|function|up
r_extern
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;| atomic up operation&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%0, %%a1&bslash;n&bslash;t&quot;
l_string|&quot;lea&t;%%pc@(1f), %%a0&bslash;n&bslash;t&quot;
l_string|&quot;addql&t;#1, %%a1@&bslash;n&bslash;t&quot;
l_string|&quot;jle __up_wakeup&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;g&quot;
(paren
id|sem
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;%a0&quot;
comma
l_string|&quot;%a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
