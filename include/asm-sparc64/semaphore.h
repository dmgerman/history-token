macro_line|#ifndef _SPARC64_SEMAPHORE_H
DECL|macro|_SPARC64_SEMAPHORE_H
mdefine_line|#define _SPARC64_SEMAPHORE_H
multiline_comment|/* These are actually reasonable on the V9.&n; *&n; * See asm-ppc/semaphore.h for implementation commentary,&n; * only sparc64 specific issues are commented here.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
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
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__SEMAPHORE_INITIALIZER
mdefine_line|#define __SEMAPHORE_INITIALIZER(name, count) &bslash;&n;&t;{ ATOMIC_INIT(count), &bslash;&n;&t;  __WAIT_QUEUE_HEAD_INITIALIZER((name).wait) }
DECL|macro|__MUTEX_INITIALIZER
mdefine_line|#define __MUTEX_INITIALIZER(name) &bslash;&n;&t;__SEMAPHORE_INITIALIZER(name, 1)
DECL|macro|__DECLARE_SEMAPHORE_GENERIC
mdefine_line|#define __DECLARE_SEMAPHORE_GENERIC(name, count) &bslash;&n;&t;struct semaphore name = __SEMAPHORE_INITIALIZER(name,count)
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(name)&t;&t;__DECLARE_SEMAPHORE_GENERIC(name, 1)
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(name)&t;__DECLARE_SEMAPHORE_GENERIC(name, 0)
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
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count - 1;&n;&t; *&t;sem-&gt;count = new_val;&n;&t; *&t;if (old_val &lt; 1)&n;&t; *&t;&t;__down(sem);&n;&t; *&n;&t; * The (old_val &lt; 1) test is equivalent to&n;&t; * the more straightforward (new_val &lt; 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! down sem(%0)&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%0], %%g5&bslash;n&quot;
l_string|&quot;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cas&t;[%0], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t; membar&t;#StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;mov&t;%0, %%g5&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;call&t;%1&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t; restore %%l3, %%g0, %%g3&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
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
r_static
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
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count - 1;&n;&t; *&t;sem-&gt;count = new_val;&n;&t; *&t;if (old_val &lt; 1)&n;&t; *&t;&t;ret = __down_interruptible(sem);&n;&t; *&n;&t; * The (old_val &lt; 1) test is equivalent to&n;&t; * the more straightforward (new_val &lt; 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! down_interruptible sem(%2) ret(%0)&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%2], %%g5&bslash;n&quot;
l_string|&quot;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cas&t;[%2], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; cmp&t;%%g7, 1&bslash;n&quot;
l_string|&quot;&t;bl,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t; membar&t;#StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;mov&t;%2, %%g5&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;call&t;%3&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l3, %%g3&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t; restore %%o0, %%g0, %0&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
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
r_static
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
id|ret
suffix:semicolon
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count - 1;&n;&t; *&t;if (old_val &lt; 1) {&n;&t; *&t;&t;ret = 1;&n;&t; *&t;} else {&n;&t; *&t;&t;sem-&gt;count = new_val;&n;&t; *&t;&t;ret = 0;&n;&t; *&t;}&n;&t; *&n;&t; * The (old_val &lt; 1) test is equivalent to&n;&t; * the more straightforward (new_val &lt; 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! down_trylock sem(%1) ret(%0)&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%1], %%g5&bslash;n&quot;
l_string|&quot;&t;sub&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, 1&bslash;n&quot;
l_string|&quot;&t;bl,pn&t;%%icc, 2f&bslash;n&quot;
l_string|&quot;&t; mov&t;1, %0&bslash;n&quot;
l_string|&quot;&t;cas&t;[%1], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; mov&t;0, %0&bslash;n&quot;
l_string|&quot;&t;membar&t;#StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
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
r_static
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
multiline_comment|/* This atomically does:&n;&t; * &t;old_val = sem-&gt;count;&n;&t; *&t;new_val = sem-&gt;count + 1;&n;&t; *&t;sem-&gt;count = new_val;&n;&t; *&t;if (old_val &lt; 0)&n;&t; *&t;&t;__up(sem);&n;&t; *&n;&t; * The (old_val &lt; 0) test is equivalent to&n;&t; * the more straightforward (new_val &lt;= 0),&n;&t; * but it is easier to test the former because&n;&t; * of how the CAS instruction works.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;! up sem(%0)&bslash;n&quot;
l_string|&quot;&t;membar&t;#StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;[%0], %%g5&bslash;n&quot;
l_string|&quot;&t;add&t;%%g5, 1, %%g7&bslash;n&quot;
l_string|&quot;&t;cas&t;[%0], %%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;cmp&t;%%g5, %%g7&bslash;n&quot;
l_string|&quot;&t;bne,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; addcc&t;%%g7, 1, %%g0&bslash;n&quot;
l_string|&quot;&t;ble,pn&t;%%icc, 3f&bslash;n&quot;
l_string|&quot;&t; nop&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;&t;.subsection 2&bslash;n&quot;
l_string|&quot;3:&t;mov&t;%0, %%g5&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -160, %%sp&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&bslash;n&quot;
l_string|&quot;&t;call&t;%1&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g5, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g2&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;%%xcc, 2b&bslash;n&quot;
l_string|&quot;&t; restore %%l3, %%g0, %%g3&bslash;n&quot;
l_string|&quot;&t;.previous&bslash;n&quot;
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
