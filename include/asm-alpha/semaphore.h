macro_line|#ifndef _ALPHA_SEMAPHORE_H
DECL|macro|_ALPHA_SEMAPHORE_H
mdefine_line|#define _ALPHA_SEMAPHORE_H
multiline_comment|/*&n; * SMP- and interrupt-safe semaphores..&n; *&n; * (C) Copyright 1996 Linus Torvalds&n; * (C) Copyright 1996, 2000 Richard Henderson&n; */
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
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
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name, n)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;= ATOMIC_INIT(n),&t;&t;&t;&t;&bslash;&n;  &t;.wait&t;= __WAIT_QUEUE_HEAD_INITIALIZER((name).wait),&t;&bslash;&n;}
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name)&t;&t;&t;&bslash;&n;&t;__SEMAPHORE_INITIALIZER(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count)&t;&t;&bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name,count)
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
multiline_comment|/*&n;&t; * Logically, &n;&t; *   *sem = (struct semaphore)__SEMAPHORE_INITIALIZER((*sem),val);&n;&t; * except that gcc produces better initializing by parts yet.&n;&t; */
id|atomic_set
c_func
(paren
op_amp
id|sem-&gt;count
comma
id|val
)paren
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
id|down
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__down_failed
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
r_extern
r_int
id|down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__down_failed_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
r_extern
r_int
id|down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
r_extern
r_void
id|up
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__up_wakeup
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Hidden out of line code is fun, but extremely messy.  Rely on newer&n; * compilers to do a respectable job with this.  The contention cases&n; * are handled out of line in arch/alpha/kernel/semaphore.c.&n; */
DECL|function|__down
r_static
r_inline
r_void
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|count
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|count
op_assign
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|count
OL
l_int|0
)paren
)paren
id|__down_failed
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
DECL|function|__down_interruptible
r_static
r_inline
r_int
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|count
suffix:semicolon
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
id|count
op_assign
id|atomic_dec_return
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|count
OL
l_int|0
)paren
)paren
r_return
id|__down_failed_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * down_trylock returns 0 on success, 1 if we failed to get the lock.&n; */
DECL|function|__down_trylock
r_static
r_inline
r_int
id|__down_trylock
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
multiline_comment|/* &quot;Equivalent&quot; C:&n;&n;&t;   do {&n;&t;&t;ret = ldl_l;&n;&t;&t;--ret;&n;&t;&t;if (ret &lt; 0)&n;&t;&t;&t;break;&n;&t;&t;ret = stl_c = ret;&n;&t;   } while (ret == 0);&n;&t;*/
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;subl&t;%0,1,%0&bslash;n&quot;
l_string|&quot;&t;blt&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;beq&t;%0,3f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=m&quot;
(paren
id|sem-&gt;count
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|sem-&gt;count
)paren
)paren
suffix:semicolon
r_return
id|ret
OL
l_int|0
suffix:semicolon
)brace
DECL|function|__up
r_static
r_inline
r_void
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
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
)paren
id|__up_wakeup
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
macro_line|#if !defined(CONFIG_DEBUG_SEMAPHORE)
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
id|__down
c_func
(paren
id|sem
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
r_return
id|__down_interruptible
c_func
(paren
id|sem
)paren
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
r_return
id|__down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
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
id|__up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
