multiline_comment|/*&n; * linux/include/asm-arm/semaphore.h&n; */
macro_line|#ifndef __ASM_ARM_SEMAPHORE_H
DECL|macro|__ASM_ARM_SEMAPHORE_H
mdefine_line|#define __ASM_ARM_SEMAPHORE_H
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/locks.h&gt;
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
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INIT
mdefine_line|#define __SEMAPHORE_INIT(name, cnt)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;= ATOMIC_INIT(cnt),&t;&t;&t;&t;&bslash;&n;&t;.wait&t;= __WAIT_QUEUE_HEAD_INITIALIZER((name).wait),&t;&bslash;&n;}
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) __SEMAPHORE_INIT(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count)&t;&bslash;&n;&t;struct semaphore name = __SEMAPHORE_INIT(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name)&t;&t;__DECLARE_SEMAPHORE_GENERIC(name,1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name)&t;__DECLARE_SEMAPHORE_GENERIC(name,0)
DECL|function|sema_init
r_static
r_inline
r_void
id|sema_init
c_func
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
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|init_MUTEX
r_static
r_inline
r_void
id|init_MUTEX
c_func
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
c_func
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
DECL|function|sema_count
r_static
r_inline
r_int
id|sema_count
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * special register calling convention&n; */
id|asmlinkage
r_void
id|__down_failed
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_interruptible_failed
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_int
id|__down_trylock_failed
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_void
id|__up_wakeup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
r_extern
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
r_extern
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
r_extern
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
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;__down&quot; is the actual routine that waits...&n; */
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|__down_op
c_func
(paren
id|sem
comma
id|__down_failed
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is ugly, but we want the default case to fall through.&n; * &quot;__down_interruptible&quot; is the actual routine that waits...&n; */
DECL|function|down_interruptible
r_static
r_inline
r_int
id|down_interruptible
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
r_return
id|__down_op_ret
c_func
(paren
id|sem
comma
id|__down_interruptible_failed
)paren
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
r_return
id|__down_op_ret
c_func
(paren
id|sem
comma
id|__down_trylock_failed
)paren
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
id|__up_op
c_func
(paren
id|sem
comma
id|__up_wakeup
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
