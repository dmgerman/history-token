multiline_comment|/* rwsem.c: Don&squot;t inline expand these suckers all over the place.&n; *&n; * Written by David S. Miller (davem@redhat.com), 2001.&n; * Derived from asm-i386/rwsem.h&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_down_read_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_down_write_failed
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|rw_semaphore
op_star
id|FASTCALL
c_func
(paren
id|rwsem_downgrade_wake
c_func
(paren
r_struct
id|rw_semaphore
op_star
)paren
)paren
suffix:semicolon
DECL|function|__down_read
r_void
id|__sched
id|__down_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __down_read&bslash;n&quot;
l_string|&quot;1:&bslash;tlduw&t;[%0], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;add&t;&t;%%g5, 1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%0], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; add&t;&t;%%g7, 1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g7, 0&bslash;n&bslash;t&quot;
l_string|&quot;bl,pn&t;&t;%%icc, 3f&bslash;n&bslash;t&quot;
l_string|&quot; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection&t;2&bslash;n&quot;
l_string|&quot;3:&bslash;tmov&t;%0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;save&t;&t;%%sp, -160, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g1, %%l1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g2, %%l2&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g3, %%l3&bslash;n&bslash;t&quot;
l_string|&quot;call&t;&t;%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;%%g5, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%l1, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%l2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ba,pt&t;&t;%%xcc, 2b&bslash;n&bslash;t&quot;
l_string|&quot; restore&t;%%l3, %%g0, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;! ending __down_read&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|rwsem_down_read_failed
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
DECL|variable|__down_read
id|EXPORT_SYMBOL
c_func
(paren
id|__down_read
)paren
suffix:semicolon
DECL|function|__down_read_trylock
r_int
id|__down_read_trylock
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __down_read_trylock&bslash;n&quot;
l_string|&quot;1:&bslash;tlduw&t;[%1], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;add&t;&t;%%g5, 1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g7, 0&bslash;n&bslash;t&quot;
l_string|&quot;bl,pn&t;&t;%%icc, 2f&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;0, %0&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%1], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;1, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar&t;&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;! ending __down_read_trylock&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
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
id|result
suffix:semicolon
)brace
DECL|variable|__down_read_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_read_trylock
)paren
suffix:semicolon
DECL|function|__down_write
r_void
id|__sched
id|__down_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __down_write&bslash;n&bslash;t&quot;
l_string|&quot;sethi&t;&t;%%hi(%2), %%g1&bslash;n&bslash;t&quot;
l_string|&quot;or&t;&t;%%g1, %%lo(%2), %%g1&bslash;n&quot;
l_string|&quot;1:&bslash;tlduw&t;[%0], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;add&t;&t;%%g5, %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%0], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; cmp&t;&t;%%g7, 0&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 3f&bslash;n&bslash;t&quot;
l_string|&quot; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection&t;2&bslash;n&quot;
l_string|&quot;3:&bslash;tmov&t;%0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;save&t;&t;%%sp, -160, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g2, %%l2&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g3, %%l3&bslash;n&bslash;t&quot;
l_string|&quot;call&t;&t;%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;%%g5, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%l2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ba,pt&t;&t;%%xcc, 2b&bslash;n&bslash;t&quot;
l_string|&quot; restore&t;%%l3, %%g0, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;! ending __down_write&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|rwsem_down_write_failed
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_ACTIVE_WRITE_BIAS
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
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
DECL|variable|__down_write
id|EXPORT_SYMBOL
c_func
(paren
id|__down_write
)paren
suffix:semicolon
DECL|function|__down_write_trylock
r_int
id|__down_write_trylock
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __down_write_trylock&bslash;n&bslash;t&quot;
l_string|&quot;sethi&t;&t;%%hi(%2), %%g1&bslash;n&bslash;t&quot;
l_string|&quot;or&t;&t;%%g1, %%lo(%2), %%g1&bslash;n&quot;
l_string|&quot;1:&bslash;tlduw&t;[%1], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, 0&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 2f&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;0, %0&bslash;n&bslash;t&quot;
l_string|&quot;add&t;&t;%%g5, %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%1], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;1, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar&t;&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;! ending __down_write_trylock&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_ACTIVE_WRITE_BIAS
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
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
id|result
suffix:semicolon
)brace
DECL|variable|__down_write_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_write_trylock
)paren
suffix:semicolon
DECL|function|__up_read
r_void
id|__up_read
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __up_read&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;tlduw&t;[%0], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;&t;%%g5, 1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%0], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; cmp&t;&t;%%g7, 0&bslash;n&bslash;t&quot;
l_string|&quot;bl,pn&t;&t;%%icc, 3f&bslash;n&bslash;t&quot;
l_string|&quot; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection&t;2&bslash;n&quot;
l_string|&quot;3:&bslash;tsethi&t;%%hi(%2), %%g1&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;&t;%%g7, 1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;or&t;&t;%%g1, %%lo(%2), %%g1&bslash;n&bslash;t&quot;
l_string|&quot;andcc&t;&t;%%g7, %%g1, %%g0&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 2b&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;%0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;save&t;&t;%%sp, -160, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g2, %%l2&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g3, %%l3&bslash;n&bslash;t&quot;
l_string|&quot;call&t;&t;%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;%%g5, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%l2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ba,pt&t;&t;%%xcc, 2b&bslash;n&bslash;t&quot;
l_string|&quot; restore&t;%%l3, %%g0, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;! ending __up_read&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|rwsem_wake
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_ACTIVE_MASK
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
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
DECL|variable|__up_read
id|EXPORT_SYMBOL
c_func
(paren
id|__up_read
)paren
suffix:semicolon
DECL|function|__up_write
r_void
id|__up_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __up_write&bslash;n&bslash;t&quot;
l_string|&quot;sethi&t;&t;%%hi(%2), %%g1&bslash;n&bslash;t&quot;
l_string|&quot;or&t;&t;%%g1, %%lo(%2), %%g1&bslash;n&quot;
l_string|&quot;1:&bslash;tlduw&t;[%0], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;&t;%%g5, %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%0], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; sub&t;&t;%%g7, %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g7, 0&bslash;n&bslash;t&quot;
l_string|&quot;bl,pn&t;&t;%%icc, 3f&bslash;n&bslash;t&quot;
l_string|&quot; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&bslash;tmov&t;%0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;save&t;&t;%%sp, -160, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g2, %%l2&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g3, %%l3&bslash;n&bslash;t&quot;
l_string|&quot;call&t;&t;%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;%%g5, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%l2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ba,pt&t;&t;%%xcc, 2b&bslash;n&bslash;t&quot;
l_string|&quot; restore&t;%%l3, %%g0, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;! ending __up_write&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|rwsem_wake
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_ACTIVE_WRITE_BIAS
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
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
DECL|variable|__up_write
id|EXPORT_SYMBOL
c_func
(paren
id|__up_write
)paren
suffix:semicolon
DECL|function|__downgrade_write
r_void
id|__downgrade_write
c_func
(paren
r_struct
id|rw_semaphore
op_star
id|sem
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;! beginning __downgrade_write&bslash;n&bslash;t&quot;
l_string|&quot;sethi&t;&t;%%hi(%2), %%g1&bslash;n&bslash;t&quot;
l_string|&quot;or&t;&t;%%g1, %%lo(%2), %%g1&bslash;n&quot;
l_string|&quot;1:&bslash;tlduw&t;[%0], %%g5&bslash;n&bslash;t&quot;
l_string|&quot;sub&t;&t;%%g5, %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cas&t;&t;[%0], %%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g5, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;bne,pn&t;&t;%%icc, 1b&bslash;n&bslash;t&quot;
l_string|&quot; sub&t;&t;%%g7, %%g1, %%g7&bslash;n&bslash;t&quot;
l_string|&quot;cmp&t;&t;%%g7, 0&bslash;n&bslash;t&quot;
l_string|&quot;bl,pn&t;&t;%%icc, 3f&bslash;n&bslash;t&quot;
l_string|&quot; membar&t;#StoreLoad | #StoreStore&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.subsection 2&bslash;n&quot;
l_string|&quot;3:&bslash;tmov&t;%0, %%g5&bslash;n&bslash;t&quot;
l_string|&quot;save&t;&t;%%sp, -160, %%sp&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g2, %%l2&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%g3, %%l3&bslash;n&bslash;t&quot;
l_string|&quot;call&t;&t;%1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;&t;%%g5, %%o0&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;&t;%%l2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ba,pt&t;&t;%%xcc, 2b&bslash;n&bslash;t&quot;
l_string|&quot; restore&t;%%l3, %%g0, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;! ending __up_write&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|sem
)paren
comma
l_string|&quot;i&quot;
(paren
id|rwsem_downgrade_wake
)paren
comma
l_string|&quot;i&quot;
(paren
id|RWSEM_WAITING_BIAS
)paren
suffix:colon
l_string|&quot;g1&quot;
comma
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
DECL|variable|__downgrade_write
id|EXPORT_SYMBOL
c_func
(paren
id|__downgrade_write
)paren
suffix:semicolon
eof
