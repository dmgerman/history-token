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
macro_line|#if WAITQUEUE_DEBUG
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
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___atomic_sub
id|add
op_mod
op_mod
id|o7
comma
l_int|8
comma
op_mod
op_mod
id|o7
id|tst
op_mod
op_mod
id|g2
id|bl
l_float|2f
id|nop
l_int|1
suffix:colon
dot
id|subsection
l_int|2
l_int|2
suffix:colon
id|save
op_mod
op_mod
id|sp
comma
op_minus
l_int|64
comma
op_mod
op_mod
id|sp
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|l1
id|mov
op_mod
op_mod
id|g5
comma
op_mod
op_mod
id|l5
id|call
op_mod
l_int|3
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|o0
id|mov
op_mod
op_mod
id|l1
comma
op_mod
op_mod
id|g1
id|ba
l_int|1
id|b
id|restore
op_mod
op_mod
id|l5
comma
op_mod
op_mod
id|g0
comma
op_mod
op_mod
id|g5
dot
id|previous
"&bslash;"
id|n
"&quot;"
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
macro_line|#if WAITQUEUE_DEBUG
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
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___atomic_sub
id|add
op_mod
op_mod
id|o7
comma
l_int|8
comma
op_mod
op_mod
id|o7
id|tst
op_mod
op_mod
id|g2
id|bl
l_float|2f
id|clr
op_mod
op_mod
id|g2
l_int|1
suffix:colon
dot
id|subsection
l_int|2
l_int|2
suffix:colon
id|save
op_mod
op_mod
id|sp
comma
op_minus
l_int|64
comma
op_mod
op_mod
id|sp
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|l1
id|mov
op_mod
op_mod
id|g5
comma
op_mod
op_mod
id|l5
id|call
op_mod
l_int|3
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|o0
id|mov
op_mod
op_mod
id|l1
comma
op_mod
op_mod
id|g1
id|mov
op_mod
op_mod
id|l5
comma
op_mod
op_mod
id|g5
id|ba
l_int|1
id|b
id|restore
op_mod
op_mod
id|o0
comma
op_mod
op_mod
id|g0
comma
op_mod
op_mod
id|g2
dot
id|previous
"&bslash;"
id|n
"&quot;"
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
macro_line|#if WAITQUEUE_DEBUG
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
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___atomic_sub
id|add
op_mod
op_mod
id|o7
comma
l_int|8
comma
op_mod
op_mod
id|o7
id|tst
op_mod
op_mod
id|g2
id|bl
l_float|2f
id|clr
op_mod
op_mod
id|g2
l_int|1
suffix:colon
dot
id|subsection
l_int|2
l_int|2
suffix:colon
id|save
op_mod
op_mod
id|sp
comma
op_minus
l_int|64
comma
op_mod
op_mod
id|sp
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|l1
id|mov
op_mod
op_mod
id|g5
comma
op_mod
op_mod
id|l5
id|call
op_mod
l_int|3
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|o0
id|mov
op_mod
op_mod
id|l1
comma
op_mod
op_mod
id|g1
id|mov
op_mod
op_mod
id|l5
comma
op_mod
op_mod
id|g5
id|ba
l_int|1
id|b
id|restore
op_mod
op_mod
id|o0
comma
op_mod
op_mod
id|g0
comma
op_mod
op_mod
id|g2
dot
id|previous
"&bslash;"
id|n
"&quot;"
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
macro_line|#if WAITQUEUE_DEBUG
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
"&quot;"
id|mov
op_mod
op_mod
id|o7
comma
op_mod
op_mod
id|g4
id|call
id|___atomic_add
id|add
op_mod
op_mod
id|o7
comma
l_int|8
comma
op_mod
op_mod
id|o7
id|tst
op_mod
op_mod
id|g2
id|ble
l_float|2f
id|nop
l_int|1
suffix:colon
dot
id|subsection
l_int|2
l_int|2
suffix:colon
id|save
op_mod
op_mod
id|sp
comma
op_minus
l_int|64
comma
op_mod
op_mod
id|sp
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|l1
id|mov
op_mod
op_mod
id|g5
comma
op_mod
op_mod
id|l5
id|call
op_mod
l_int|3
id|mov
op_mod
op_mod
id|g1
comma
op_mod
op_mod
id|o0
id|mov
op_mod
op_mod
id|l1
comma
op_mod
op_mod
id|g1
id|ba
l_int|1
id|b
id|restore
op_mod
op_mod
id|l5
comma
op_mod
op_mod
id|g0
comma
op_mod
op_mod
id|g5
dot
id|previous
"&bslash;"
id|n
"&quot;"
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
