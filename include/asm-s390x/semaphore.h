multiline_comment|/*&n; *  include/asm-s390x/semaphore.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *&n; *  Derived from &quot;include/asm-i386/semaphore.h&quot;&n; *    (C) Copyright 1996 Linus Torvalds&n; */
macro_line|#ifndef _S390_SEMAPHORE_H
DECL|macro|_S390_SEMAPHORE_H
mdefine_line|#define _S390_SEMAPHORE_H
macro_line|#include &lt;asm/system.h&gt;
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
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name,count) &bslash;&n;&t;{ ATOMIC_INIT(count), __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) }
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
id|old_val
comma
id|new_val
suffix:semicolon
multiline_comment|/*&n;&t; * This inline assembly atomically implements the equivalent&n;&t; * to the following C code:&n;&t; *   old_val = sem-&gt;count.counter;&n;&t; *   if ((new_val = old_val) &gt; 0)&n;&t; *       sem-&gt;count.counter = --new_val;&n;&t; * In the ppc code this is called atomic_dec_if_positive.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;   l    %0,0(%3)&bslash;n&quot;
l_string|&quot;0: ltr  %1,%0&bslash;n&quot;
l_string|&quot;   jle  1f&bslash;n&quot;
l_string|&quot;   ahi  %1,-1&bslash;n&quot;
l_string|&quot;   cs   %0,%1,0(%3)&bslash;n&quot;
l_string|&quot;   jl   0b&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old_val
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|new_val
)paren
comma
l_string|&quot;+m&quot;
(paren
id|sem-&gt;count.counter
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|sem-&gt;count.counter
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|old_val
op_le
l_int|0
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
macro_line|#endif
eof
