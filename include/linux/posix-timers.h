macro_line|#ifndef _linux_POSIX_TIMERS_H
DECL|macro|_linux_POSIX_TIMERS_H
mdefine_line|#define _linux_POSIX_TIMERS_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/* POSIX.1b interval timer structure. */
DECL|struct|k_itimer
r_struct
id|k_itimer
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* free/ allocate list */
DECL|member|it_lock
id|spinlock_t
id|it_lock
suffix:semicolon
DECL|member|it_clock
id|clockid_t
id|it_clock
suffix:semicolon
multiline_comment|/* which timer type */
DECL|member|it_id
id|timer_t
id|it_id
suffix:semicolon
multiline_comment|/* timer id */
DECL|member|it_overrun
r_int
id|it_overrun
suffix:semicolon
multiline_comment|/* overrun on pending signal  */
DECL|member|it_overrun_last
r_int
id|it_overrun_last
suffix:semicolon
multiline_comment|/* overrun on last delivered signal */
DECL|member|it_requeue_pending
r_int
id|it_requeue_pending
suffix:semicolon
multiline_comment|/* waiting to requeue this timer */
DECL|member|it_sigev_notify
r_int
id|it_sigev_notify
suffix:semicolon
multiline_comment|/* notify word of sigevent struct */
DECL|member|it_sigev_signo
r_int
id|it_sigev_signo
suffix:semicolon
multiline_comment|/* signo word of sigevent struct */
DECL|member|it_sigev_value
id|sigval_t
id|it_sigev_value
suffix:semicolon
multiline_comment|/* value word of sigevent struct */
DECL|member|it_incr
r_int
r_int
id|it_incr
suffix:semicolon
multiline_comment|/* interval specified in jiffies */
DECL|member|it_process
r_struct
id|task_struct
op_star
id|it_process
suffix:semicolon
multiline_comment|/* process to send signal to */
DECL|member|it_timer
r_struct
id|timer_list
id|it_timer
suffix:semicolon
DECL|member|sigq
r_struct
id|sigqueue
op_star
id|sigq
suffix:semicolon
multiline_comment|/* signal queue entry. */
DECL|member|abs_timer_entry
r_struct
id|list_head
id|abs_timer_entry
suffix:semicolon
multiline_comment|/* clock abs_timer_list */
DECL|member|wall_to_prev
r_struct
id|timespec
id|wall_to_prev
suffix:semicolon
multiline_comment|/* wall_to_monotonic used when set */
)brace
suffix:semicolon
DECL|struct|k_clock_abs
r_struct
id|k_clock_abs
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|k_clock
r_struct
id|k_clock
(brace
DECL|member|res
r_int
id|res
suffix:semicolon
multiline_comment|/* in nano seconds */
DECL|member|abs_struct
r_struct
id|k_clock_abs
op_star
id|abs_struct
suffix:semicolon
DECL|member|clock_set
r_int
(paren
op_star
id|clock_set
)paren
(paren
r_struct
id|timespec
op_star
id|tp
)paren
suffix:semicolon
DECL|member|clock_get
r_int
(paren
op_star
id|clock_get
)paren
(paren
r_struct
id|timespec
op_star
id|tp
)paren
suffix:semicolon
DECL|member|timer_create
r_int
(paren
op_star
id|timer_create
)paren
(paren
r_int
id|which_clock
comma
r_struct
id|sigevent
id|__user
op_star
id|timer_event_spec
comma
id|timer_t
id|__user
op_star
id|created_timer_id
)paren
suffix:semicolon
DECL|member|nsleep
r_int
(paren
op_star
id|nsleep
)paren
(paren
r_int
id|which_clock
comma
r_int
id|flags
comma
r_struct
id|timespec
op_star
id|t
)paren
suffix:semicolon
DECL|member|timer_set
r_int
(paren
op_star
id|timer_set
)paren
(paren
r_struct
id|k_itimer
op_star
id|timr
comma
r_int
id|flags
comma
r_struct
id|itimerspec
op_star
id|new_setting
comma
r_struct
id|itimerspec
op_star
id|old_setting
)paren
suffix:semicolon
DECL|member|timer_del
r_int
(paren
op_star
id|timer_del
)paren
(paren
r_struct
id|k_itimer
op_star
id|timr
)paren
suffix:semicolon
DECL|member|timer_get
r_void
(paren
op_star
id|timer_get
)paren
(paren
r_struct
id|k_itimer
op_star
id|timr
comma
r_struct
id|itimerspec
op_star
id|cur_setting
)paren
suffix:semicolon
)brace
suffix:semicolon
r_void
id|register_posix_clock
c_func
(paren
r_int
id|clock_id
comma
r_struct
id|k_clock
op_star
id|new_clock
)paren
suffix:semicolon
multiline_comment|/* Error handlers for timer_create, nanosleep and settime */
r_int
id|do_posix_clock_notimer_create
c_func
(paren
r_int
id|which_clock
comma
r_struct
id|sigevent
id|__user
op_star
id|time_event_spec
comma
id|timer_t
id|__user
op_star
id|created_timer_id
)paren
suffix:semicolon
r_int
id|do_posix_clock_nonanosleep
c_func
(paren
r_int
id|which_clock
comma
r_int
id|flags
comma
r_struct
id|timespec
op_star
id|t
)paren
suffix:semicolon
r_int
id|do_posix_clock_nosettime
c_func
(paren
r_struct
id|timespec
op_star
id|tp
)paren
suffix:semicolon
DECL|struct|now_struct
r_struct
id|now_struct
(brace
DECL|member|jiffies
r_int
r_int
id|jiffies
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|posix_get_now
mdefine_line|#define posix_get_now(now) (now)-&gt;jiffies = jiffies;
DECL|macro|posix_time_before
mdefine_line|#define posix_time_before(timer, now) &bslash;&n;                      time_before((timer)-&gt;expires, (now)-&gt;jiffies)
DECL|macro|posix_bump_timer
mdefine_line|#define posix_bump_timer(timr, now)&t;&t;&t;&t;&t;&bslash;&n;         do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;              long delta, orun;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;      delta = now.jiffies - (timr)-&gt;it_timer.expires;&t;&t;&bslash;&n;              if (delta &gt;= 0) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;           orun = 1 + (delta / (timr)-&gt;it_incr);&t;&t;&bslash;&n;&t;          (timr)-&gt;it_timer.expires += orun * (timr)-&gt;it_incr;&t;&bslash;&n;                  (timr)-&gt;it_overrun += orun;&t;&t;&t;&t;&bslash;&n;              }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;            }while (0)
macro_line|#endif
eof
