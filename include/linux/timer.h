macro_line|#ifndef _LINUX_TIMER_H
DECL|macro|_LINUX_TIMER_H
mdefine_line|#define _LINUX_TIMER_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
r_struct
id|tvec_t_base_s
suffix:semicolon
multiline_comment|/*&n; * Timers may be dynamically created and destroyed, and should be initialized&n; * by a call to init_timer() upon creation.&n; *&n; * The &quot;data&quot; field enables use of a common timeout function for several&n; * timeouts. You can use this field to distinguish between the different&n; * invocations.&n; */
DECL|struct|timer_list
r_typedef
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
DECL|member|base
r_struct
id|tvec_t_base_s
op_star
id|base
suffix:semicolon
DECL|typedef|timer_t
)brace
id|timer_t
suffix:semicolon
r_extern
r_void
id|add_timer
c_func
(paren
id|timer_t
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_int
id|del_timer
c_func
(paren
id|timer_t
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
id|timer_t
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_void
id|sync_timers
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|timer_enter
mdefine_line|#define timer_enter(base, t) do { base-&gt;running_timer = t; mb(); } while (0)
DECL|macro|timer_exit
mdefine_line|#define timer_exit(base) do { base-&gt;running_timer = NULL; } while (0)
DECL|macro|timer_is_running
mdefine_line|#define timer_is_running(base,t) (base-&gt;running_timer == t)
DECL|macro|timer_synchronize
mdefine_line|#define timer_synchronize(base,t) while (timer_is_running(base,t)) barrier()
macro_line|#else
DECL|macro|del_timer_sync
mdefine_line|#define del_timer_sync(t)&t;del_timer(t)
DECL|macro|sync_timers
mdefine_line|#define sync_timers()&t;&t;do { } while (0)
DECL|macro|timer_enter
mdefine_line|#define timer_enter(base,t)          do { } while (0)
DECL|macro|timer_exit
mdefine_line|#define timer_exit(base)            do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * mod_timer is a more efficient way to update the expire field of an&n; * active timer (if the timer is inactive it will be activated)&n; * mod_timer(a,b) is equivalent to del_timer(a); a-&gt;expires = b; add_timer(a).&n; * If the timer is known to be not pending (ie, in the handler), mod_timer&n; * is less efficient than a-&gt;expires = b; add_timer(a).&n; */
r_int
id|mod_timer
c_func
(paren
id|timer_t
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
r_extern
r_void
id|init_timers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|run_local_timers
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_timer
r_static
r_inline
r_void
id|init_timer
c_func
(paren
id|timer_t
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
id|timer-&gt;base
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|timer_pending
r_static
r_inline
r_int
id|timer_pending
c_func
(paren
r_const
id|timer_t
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
