macro_line|#ifndef _LINUX_TIMER_H
DECL|macro|_LINUX_TIMER_H
mdefine_line|#define _LINUX_TIMER_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * In Linux 2.4, static timers have been removed from the kernel.&n; * Timers may be dynamically created and destroyed, and should be initialized&n; * by a call to init_timer() upon creation.&n; *&n; * The &quot;data&quot; field enables use of a common timeout function for several&n; * timeouts. You can use this field to distinguish between the different&n; * invocations.&n; */
DECL|struct|timer_list
r_struct
id|timer_list
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|function
r_void
(paren
op_star
id|function
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|add_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_int
id|del_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
id|del_timer_sync
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
suffix:semicolon
macro_line|#else
DECL|macro|del_timer_sync
mdefine_line|#define del_timer_sync(t)&t;del_timer(t)
macro_line|#endif
multiline_comment|/*&n; * mod_timer is a more efficient way to update the expire field of an&n; * active timer (if the timer is inactive it will be activated)&n; * mod_timer(a,b) is equivalent to del_timer(a); a-&gt;expires = b; add_timer(a).&n; * If the timer is known to be not pending (ie, in the handler), mod_timer&n; * is less efficient than a-&gt;expires = b; add_timer(a).&n; */
r_int
id|mod_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
comma
r_int
r_int
id|expires
)paren
suffix:semicolon
r_extern
r_void
id|it_real_fn
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|init_timer
r_static
r_inline
r_void
id|init_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
(brace
id|timer-&gt;list.next
op_assign
id|timer-&gt;list.prev
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|timer_pending
r_static
r_inline
r_int
id|timer_pending
(paren
r_const
r_struct
id|timer_list
op_star
id|timer
)paren
(brace
r_return
id|timer-&gt;list.next
op_ne
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
