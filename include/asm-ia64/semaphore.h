macro_line|#ifndef _ASM_IA64_SEMAPHORE_H
DECL|macro|_ASM_IA64_SEMAPHORE_H
mdefine_line|#define _ASM_IA64_SEMAPHORE_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
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
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name, n)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(n),&t;&t;&t;&t;&bslash;&n;&t;.sleepers&t;= 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.wait&t;&t;= __WAIT_QUEUE_HEAD_INITIALIZER((name).wait)&t;&bslash;&n;}
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name)&t;__SEMAPHORE_INITIALIZER(name,1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name,count)&t;&t;&t;&t;&t;&bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name, count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name)&t;&t;__DECLARE_SEMAPHORE_GENERIC(name, 1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name)&t;__DECLARE_SEMAPHORE_GENERIC(name, 0)
r_static
r_inline
r_void
DECL|function|sema_init
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
r_static
r_inline
r_void
DECL|function|init_MUTEX
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
r_static
r_inline
r_void
DECL|function|init_MUTEX_LOCKED
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
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
suffix:semicolon
multiline_comment|/*&n; * Atomically decrement the semaphore&squot;s count.  If it goes negative,&n; * block the calling thread in the TASK_UNINTERRUPTIBLE state.&n; */
r_static
r_inline
r_void
DECL|function|down
id|down
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
multiline_comment|/*&n; * Atomically decrement the semaphore&squot;s count.  If it goes negative,&n; * block the calling thread in the TASK_INTERRUPTIBLE state.&n; */
r_static
r_inline
r_int
DECL|function|down_interruptible
id|down_interruptible
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
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
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
r_static
r_inline
r_int
DECL|function|down_trylock
id|down_trylock
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
id|__down_trylock
c_func
(paren
id|sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|up
id|up
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
macro_line|#endif /* _ASM_IA64_SEMAPHORE_H */
eof
