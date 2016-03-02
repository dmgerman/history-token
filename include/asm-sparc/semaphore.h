macro_line|#ifndef _SPARC_SEMAPHORE_H
DECL|macro|_SPARC_SEMAPHORE_H
mdefine_line|#define _SPARC_SEMAPHORE_H
multiline_comment|/* Dinky, good for nothing, just barely irq safe, Sparc semaphores. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
DECL|struct|semaphore
r_struct
id|semaphore
(brace
DECL|member|count
id|atomic24_t
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
macro_line|#ifdef WAITQUEUE_DEBUG
DECL|member|__magic
r_int
id|__magic
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name) &bslash;&n;&t;&t;, (long)&amp;(name).__magic
macro_line|#else
DECL|macro|__SEM_DEBUG_INIT
macro_line|# define __SEM_DEBUG_INIT(name)
macro_line|#endif
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC24_INIT(count), 0, __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
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
id|atomic24_set
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
macro_line|#ifdef WAITQUEUE_DEBUG
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
r_volatile
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|increment
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|ptr
op_assign
op_amp
(paren
id|sem-&gt;count.counter
)paren
suffix:semicolon
id|increment
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___atomic24_sub&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&bslash;t&quot;
l_string|&quot;tst&t;%%g2&bslash;n&bslash;t&quot;
l_string|&quot;bl&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;save&t;%%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g1, %%l1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g5, %%l5&bslash;n&bslash;t&quot;
l_string|&quot;call&t;%3&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%%g1, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%l1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;ba&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; restore %%l5, %%g0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|increment
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|increment
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
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
r_volatile
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|increment
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|ptr
op_assign
op_amp
(paren
id|sem-&gt;count.counter
)paren
suffix:semicolon
id|increment
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___atomic24_sub&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&bslash;t&quot;
l_string|&quot;tst&t;%%g2&bslash;n&bslash;t&quot;
l_string|&quot;bl&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; clr&t;%%g2&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;save&t;%%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g1, %%l1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g5, %%l5&bslash;n&bslash;t&quot;
l_string|&quot;call&t;%3&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%%g1, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%l1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%l5, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ba&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; restore %%o0, %%g0, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|increment
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|increment
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down_interruptible
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|increment
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
r_volatile
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|increment
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|ptr
op_assign
op_amp
(paren
id|sem-&gt;count.counter
)paren
suffix:semicolon
id|increment
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___atomic24_sub&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&bslash;t&quot;
l_string|&quot;tst&t;%%g2&bslash;n&bslash;t&quot;
l_string|&quot;bl&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; clr&t;%%g2&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;save&t;%%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g1, %%l1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g5, %%l5&bslash;n&bslash;t&quot;
l_string|&quot;call&t;%3&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%%g1, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%l1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%l5, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;ba&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; restore %%o0, %%g0, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|increment
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|increment
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down_trylock
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|increment
suffix:semicolon
)brace
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
r_volatile
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
id|increment
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
macro_line|#ifdef WAITQUEUE_DEBUG
id|CHECK_MAGIC
c_func
(paren
id|sem-&gt;__magic
)paren
suffix:semicolon
macro_line|#endif
id|ptr
op_assign
op_amp
(paren
id|sem-&gt;count.counter
)paren
suffix:semicolon
id|increment
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___atomic24_add&bslash;n&bslash;t&quot;
l_string|&quot; add&t;%%o7, 8, %%o7&bslash;n&bslash;t&quot;
l_string|&quot;tst&t;%%g2&bslash;n&bslash;t&quot;
l_string|&quot;ble&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;save&t;%%sp, -64, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g1, %%l1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%g5, %%l5&bslash;n&bslash;t&quot;
l_string|&quot;call&t;%3&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;%%g1, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%%l1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;ba&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; restore %%l5, %%g0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|increment
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|increment
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;i&quot;
(paren
id|__up
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC_SEMAPHORE_H) */
eof
