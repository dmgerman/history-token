macro_line|#ifndef _LINUX_TIMER_H
DECL|macro|_LINUX_TIMER_H
mdefine_line|#define _LINUX_TIMER_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|tvec_t_base_s
suffix:semicolon
DECL|struct|timer_list
r_struct
id|timer_list
(brace
DECL|member|entry
r_struct
id|list_head
id|entry
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
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
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|base
r_struct
id|tvec_t_base_s
op_star
id|base
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TIMER_MAGIC
mdefine_line|#define TIMER_MAGIC&t;0x4b87ad6e
multiline_comment|/***&n; * init_timer - initialize a timer.&n; * @timer: the timer to be initialized&n; *&n; * init_timer() must be done to a timer prior calling *any* of the&n; * other timer functions.&n; */
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
id|timer-&gt;base
op_assign
l_int|NULL
suffix:semicolon
id|timer-&gt;magic
op_assign
id|TIMER_MAGIC
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|timer-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/***&n; * timer_pending - is a timer pending?&n; * @timer: the timer in question&n; *&n; * timer_pending will tell whether a given timer is currently pending,&n; * or not. Callers must ensure serialization wrt. other operations done&n; * to this timer, eg. interrupt contexts, or other CPUs on SMP.&n; *&n; * return value: 1 if the timer is pending, 0 if not.&n; */
DECL|function|timer_pending
r_static
r_inline
r_int
id|timer_pending
c_func
(paren
r_const
r_struct
id|timer_list
op_star
id|timer
)paren
(brace
r_return
id|timer-&gt;base
op_ne
l_int|NULL
suffix:semicolon
)brace
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
r_void
id|add_timer_on
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
comma
r_int
id|cpu
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
r_extern
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
macro_line|#if CONFIG_SMP
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
macro_line|# define del_timer_sync(t) del_timer(t)
macro_line|#endif
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
r_extern
r_void
id|it_real_fn
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
