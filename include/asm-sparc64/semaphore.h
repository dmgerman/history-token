macro_line|#ifndef _SPARC64_SEMAPHORE_H
DECL|macro|_SPARC64_SEMAPHORE_H
mdefine_line|#define _SPARC64_SEMAPHORE_H
multiline_comment|/* These are actually reasonable on the V9. */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
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
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;{ ATOMIC_INIT(count), ATOMIC_INIT(0), __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) &bslash;&n;&t;__SEM_DEBUG_INIT(name) }
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;1:&t;lduw&t;[%0], %%g5&bslash;n&quot;
l_string|&quot;&t;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cas&t;[%0], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t;&t; membar&t;#StoreStore&bslash;n&quot;
l_string|&quot;&t;2:&bslash;n&quot;
l_string|&quot;&t;&t;.subsection 2&bslash;n&quot;
l_string|&quot;&t;3:&t;mov&t;%0, %%g5&bslash;n&quot;
l_string|&quot;&t;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;&t;call&t;%1&bslash;n&quot;
l_string|&quot;&t;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t;&t; restore %%l3, %%g0, %%g3&bslash;n&quot;
l_string|&quot;&t;&t;.previous&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down
)paren
suffix:colon
l_string|&quot;g5&quot;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;1:&t;lduw&t;[%2], %%g5&bslash;n&quot;
l_string|&quot;&t;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cas&t;[%2], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t;&t; membar&t;#StoreStore&bslash;n&quot;
l_string|&quot;&t;2:&bslash;n&quot;
l_string|&quot;&t;&t;.subsection 2&bslash;n&quot;
l_string|&quot;&t;3:&t;mov&t;%2, %%g5&bslash;n&quot;
l_string|&quot;&t;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;&t;call&t;%3&bslash;n&quot;
l_string|&quot;&t;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l3, %%g3&bslash;n&quot;
l_string|&quot;&t;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t;&t; restore %%o0, %%g0, %0&bslash;n&quot;
l_string|&quot;&t;&t;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down_interruptible
)paren
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;1:&t;lduw&t;[%2], %%g5&bslash;n&quot;
l_string|&quot;&t;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cas&t;[%2], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t;&t; membar&t;#StoreStore&bslash;n&quot;
l_string|&quot;&t;2:&bslash;n&quot;
l_string|&quot;&t;&t;.subsection 2&bslash;n&quot;
l_string|&quot;&t;3:&t;mov&t;%2, %%g5&bslash;n&quot;
l_string|&quot;&t;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;&t;call&t;%3&bslash;n&quot;
l_string|&quot;&t;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l3, %%g3&bslash;n&quot;
l_string|&quot;&t;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t;&t; restore %%o0, %%g0, %0&bslash;n&quot;
l_string|&quot;&t;&t;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__down_trylock
)paren
suffix:colon
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
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
l_string|&quot;&t;&t;membar&t;#StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;&t;1:&t;lduw&t;[%0], %%g5&bslash;n&quot;
l_string|&quot;&t;&t;add&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cas&t;[%0], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t;&t; addcc&t;%%g7, 1, %%g0&bslash;n&quot;
l_string|&quot;&t;&t;ble,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t;&t; nop&bslash;n&quot;
l_string|&quot;&t;2:&bslash;n&quot;
l_string|&quot;&t;&t;.subsection 2&bslash;n&quot;
l_string|&quot;&t;3:&t;mov&t;%0, %%g5&bslash;n&quot;
l_string|&quot;&t;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;&t;call&t;%1&bslash;n&quot;
l_string|&quot;&t;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t;&t; restore %%l3, %%g0, %%g3&bslash;n&quot;
l_string|&quot;&t;&t;.previous&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|__up
)paren
suffix:colon
l_string|&quot;g5&quot;
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
macro_line|#endif /* !(_SPARC64_SEMAPHORE_H) */
eof
