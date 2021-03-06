multiline_comment|/*&n; *  arch/s390/kernel/vtime.c&n; *    Virtual cpu timer based timer functions.&n; *&n; *  S390 version&n; *    Copyright (C) 2004 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Jan Glauber &lt;jan.glauber@de.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;linux/posix-timers.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
DECL|macro|VTIMER_MAGIC
mdefine_line|#define VTIMER_MAGIC (TIMER_MAGIC + 1)
DECL|variable|ext_int_info_timer
r_static
id|ext_int_info_t
id|ext_int_info_timer
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|vtimer_queue
comma
id|virt_cpu_timer
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VIRT_CPU_ACCOUNTING
multiline_comment|/*&n; * Update process times based on virtual cpu times stored by entry.S&n; * to the lowcore fields user_timer, system_timer &amp; steal_clock.&n; */
DECL|function|account_user_vtime
r_void
id|account_user_vtime
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|cputime_t
id|cputime
suffix:semicolon
id|__u64
id|timer
comma
id|clock
suffix:semicolon
r_int
id|rcu_user_flag
suffix:semicolon
id|timer
op_assign
id|S390_lowcore.last_update_timer
suffix:semicolon
id|clock
op_assign
id|S390_lowcore.last_update_clock
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;  STPT %0&bslash;n&quot;
multiline_comment|/* Store current cpu timer value */
l_string|&quot;  STCK %1&quot;
multiline_comment|/* Store current tod clock value */
suffix:colon
l_string|&quot;=m&quot;
(paren
id|S390_lowcore.last_update_timer
)paren
comma
l_string|&quot;=m&quot;
(paren
id|S390_lowcore.last_update_clock
)paren
)paren
suffix:semicolon
id|S390_lowcore.system_timer
op_add_assign
id|timer
op_minus
id|S390_lowcore.last_update_timer
suffix:semicolon
id|S390_lowcore.steal_clock
op_add_assign
id|S390_lowcore.last_update_clock
op_minus
id|clock
suffix:semicolon
id|cputime
op_assign
id|S390_lowcore.user_timer
op_rshift
l_int|12
suffix:semicolon
id|rcu_user_flag
op_assign
id|cputime
op_ne
l_int|0
suffix:semicolon
id|S390_lowcore.user_timer
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|S390_lowcore.steal_clock
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|account_user_time
c_func
(paren
id|tsk
comma
id|cputime
)paren
suffix:semicolon
id|cputime
op_assign
id|S390_lowcore.system_timer
op_rshift
l_int|12
suffix:semicolon
id|S390_lowcore.system_timer
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|S390_lowcore.steal_clock
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|account_system_time
c_func
(paren
id|tsk
comma
id|HARDIRQ_OFFSET
comma
id|cputime
)paren
suffix:semicolon
id|cputime
op_assign
id|S390_lowcore.steal_clock
suffix:semicolon
r_if
c_cond
(paren
(paren
id|__s64
)paren
id|cputime
OG
l_int|0
)paren
(brace
id|cputime
op_rshift_assign
l_int|12
suffix:semicolon
id|S390_lowcore.steal_clock
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|account_steal_time
c_func
(paren
id|tsk
comma
id|cputime
)paren
suffix:semicolon
)brace
id|run_local_timers
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rcu_pending
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
id|rcu_check_callbacks
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|rcu_user_flag
)paren
suffix:semicolon
id|scheduler_tick
c_func
(paren
)paren
suffix:semicolon
id|run_posix_cpu_timers
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Update process times based on virtual cpu times stored by entry.S&n; * to the lowcore fields user_timer, system_timer &amp; steal_clock.&n; */
DECL|function|account_system_vtime
r_void
id|account_system_vtime
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|cputime_t
id|cputime
suffix:semicolon
id|__u64
id|timer
suffix:semicolon
id|timer
op_assign
id|S390_lowcore.last_update_timer
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;  STPT %0&quot;
multiline_comment|/* Store current cpu timer value */
suffix:colon
l_string|&quot;=m&quot;
(paren
id|S390_lowcore.last_update_timer
)paren
)paren
suffix:semicolon
id|S390_lowcore.system_timer
op_add_assign
id|timer
op_minus
id|S390_lowcore.last_update_timer
suffix:semicolon
id|cputime
op_assign
id|S390_lowcore.system_timer
op_rshift
l_int|12
suffix:semicolon
id|S390_lowcore.system_timer
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|S390_lowcore.steal_clock
op_sub_assign
id|cputime
op_lshift
l_int|12
suffix:semicolon
id|account_system_time
c_func
(paren
id|tsk
comma
l_int|0
comma
id|cputime
)paren
suffix:semicolon
)brace
DECL|function|set_vtimer
r_static
r_inline
r_void
id|set_vtimer
c_func
(paren
id|__u64
id|expires
)paren
(brace
id|__u64
id|timer
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;  STPT %0&bslash;n&quot;
multiline_comment|/* Store current cpu timer value */
l_string|&quot;  SPT %1&quot;
multiline_comment|/* Set new value immediatly afterwards */
suffix:colon
l_string|&quot;=m&quot;
(paren
id|timer
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|expires
)paren
)paren
suffix:semicolon
id|S390_lowcore.system_timer
op_add_assign
id|S390_lowcore.last_update_timer
op_minus
id|timer
suffix:semicolon
id|S390_lowcore.last_update_timer
op_assign
id|expires
suffix:semicolon
multiline_comment|/* store expire time for this CPU timer */
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
dot
id|to_expire
op_assign
id|expires
suffix:semicolon
)brace
macro_line|#else
DECL|function|set_vtimer
r_static
r_inline
r_void
id|set_vtimer
c_func
(paren
id|__u64
id|expires
)paren
(brace
id|S390_lowcore.last_update_timer
op_assign
id|expires
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SPT %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|S390_lowcore.last_update_timer
)paren
)paren
suffix:semicolon
multiline_comment|/* store expire time for this CPU timer */
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
dot
id|to_expire
op_assign
id|expires
suffix:semicolon
)brace
macro_line|#endif
DECL|function|start_cpu_timer
r_static
r_void
id|start_cpu_timer
c_func
(paren
r_void
)paren
(brace
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|set_vtimer
c_func
(paren
id|vt_list-&gt;idle
)paren
suffix:semicolon
)brace
DECL|function|stop_cpu_timer
r_static
r_void
id|stop_cpu_timer
c_func
(paren
r_void
)paren
(brace
id|__u64
id|done
suffix:semicolon
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* nothing to do */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|vt_list-&gt;list
)paren
)paren
(brace
id|vt_list-&gt;idle
op_assign
id|VTIMER_MAX_SLICE
suffix:semicolon
r_goto
id|fire
suffix:semicolon
)brace
multiline_comment|/* store progress */
id|asm
r_volatile
(paren
l_string|&quot;STPT %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|done
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If done is negative we do not stop the CPU timer&n;&t; * because we will get instantly an interrupt that&n;&t; * will start the CPU timer again.&n;&t; */
r_if
c_cond
(paren
id|done
op_amp
l_int|1LL
op_lshift
l_int|63
)paren
r_return
suffix:semicolon
r_else
id|vt_list-&gt;offset
op_add_assign
id|vt_list-&gt;to_expire
op_minus
id|done
suffix:semicolon
multiline_comment|/* save the actual expire value */
id|vt_list-&gt;idle
op_assign
id|done
suffix:semicolon
multiline_comment|/*&n;&t; * We cannot halt the CPU timer, we just write a value that&n;&t; * nearly never expires (only after 71 years) and re-write&n;&t; * the stored expire value if we continue the timer&n;&t; */
id|fire
suffix:colon
id|set_vtimer
c_func
(paren
id|VTIMER_MAX_SLICE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Sorted add to a list. List is linear searched until first bigger&n; * element is found.&n; */
DECL|function|list_add_sorted
r_static
r_void
id|list_add_sorted
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|vtimer_list
op_star
id|event
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|event
comma
id|head
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|event-&gt;expires
OG
id|timer-&gt;expires
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|timer-&gt;entry
comma
op_amp
id|event-&gt;entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|list_add_tail
c_func
(paren
op_amp
id|timer-&gt;entry
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do the callback functions of expired vtimer events.&n; * Called from within the interrupt handler.&n; */
DECL|function|do_callbacks
r_static
r_void
id|do_callbacks
c_func
(paren
r_struct
id|list_head
op_star
id|cb_list
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
r_struct
id|vtimer_list
op_star
id|event
comma
op_star
id|tmp
suffix:semicolon
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_int
r_int
id|data
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
id|cb_list
)paren
)paren
r_return
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|event
comma
id|tmp
comma
id|cb_list
comma
id|entry
)paren
(brace
id|fn
op_assign
id|event-&gt;function
suffix:semicolon
id|data
op_assign
id|event-&gt;data
suffix:semicolon
id|fn
c_func
(paren
id|data
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event-&gt;interval
)paren
multiline_comment|/* delete one shot timer */
id|list_del_init
c_func
(paren
op_amp
id|event-&gt;entry
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* move interval timer back to list */
id|spin_lock
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|event-&gt;entry
)paren
suffix:semicolon
id|list_add_sorted
c_func
(paren
id|event
comma
op_amp
id|vt_list-&gt;list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Handler for the virtual CPU timer.&n; */
DECL|function|do_cpu_timer_interrupt
r_static
r_void
id|do_cpu_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u16
id|error_code
)paren
(brace
r_int
id|cpu
suffix:semicolon
id|__u64
id|next
comma
id|delta
suffix:semicolon
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
r_struct
id|vtimer_list
op_star
id|event
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|ptr
suffix:semicolon
multiline_comment|/* the callback queue */
r_struct
id|list_head
id|cb_list
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cb_list
)paren
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* walk timer list, fire all expired events */
id|spin_lock
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vt_list-&gt;to_expire
OL
id|VTIMER_MAX_SLICE
)paren
id|vt_list-&gt;offset
op_add_assign
id|vt_list-&gt;to_expire
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|event
comma
id|tmp
comma
op_amp
id|vt_list-&gt;list
comma
id|entry
)paren
(brace
r_if
c_cond
(paren
id|event-&gt;expires
OG
id|vt_list-&gt;offset
)paren
multiline_comment|/* found first unexpired event, leave */
r_break
suffix:semicolon
multiline_comment|/* re-charge interval timer, we have to add the offset */
r_if
c_cond
(paren
id|event-&gt;interval
)paren
id|event-&gt;expires
op_assign
id|event-&gt;interval
op_plus
id|vt_list-&gt;offset
suffix:semicolon
multiline_comment|/* move expired timer to the callback queue */
id|list_move_tail
c_func
(paren
op_amp
id|event-&gt;entry
comma
op_amp
id|cb_list
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
id|do_callbacks
c_func
(paren
op_amp
id|cb_list
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* next event is first in list */
id|spin_lock
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|vt_list-&gt;list
)paren
)paren
(brace
id|ptr
op_assign
id|vt_list-&gt;list.next
suffix:semicolon
id|event
op_assign
id|list_entry
c_func
(paren
id|ptr
comma
r_struct
id|vtimer_list
comma
id|entry
)paren
suffix:semicolon
id|next
op_assign
id|event-&gt;expires
op_minus
id|vt_list-&gt;offset
suffix:semicolon
multiline_comment|/* add the expired time from this interrupt handler&n;&t;&t; * and the callback functions&n;&t;&t; */
id|asm
r_volatile
(paren
l_string|&quot;STPT %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|delta
)paren
)paren
suffix:semicolon
id|delta
op_assign
l_int|0xffffffffffffffffLL
op_minus
id|delta
op_plus
l_int|1
suffix:semicolon
id|vt_list-&gt;offset
op_add_assign
id|delta
suffix:semicolon
id|next
op_sub_assign
id|delta
suffix:semicolon
)brace
r_else
(brace
id|vt_list-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|next
op_assign
id|VTIMER_MAX_SLICE
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
id|set_vtimer
c_func
(paren
id|next
)paren
suffix:semicolon
)brace
DECL|function|init_virt_timer
r_void
id|init_virt_timer
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
)paren
(brace
id|timer-&gt;magic
op_assign
id|VTIMER_MAGIC
suffix:semicolon
id|timer-&gt;function
op_assign
l_int|NULL
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|timer-&gt;entry
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|timer-&gt;lock
)paren
suffix:semicolon
)brace
DECL|variable|init_virt_timer
id|EXPORT_SYMBOL
c_func
(paren
id|init_virt_timer
)paren
suffix:semicolon
DECL|function|check_vtimer
r_static
r_inline
r_int
id|check_vtimer
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
)paren
(brace
r_if
c_cond
(paren
id|timer-&gt;magic
op_ne
id|VTIMER_MAGIC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vtimer_pending
r_static
r_inline
r_int
id|vtimer_pending
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
)paren
(brace
r_return
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|timer-&gt;entry
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this function should only run on the specified CPU&n; */
DECL|function|internal_add_vtimer
r_static
r_void
id|internal_add_vtimer
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|__u64
id|done
suffix:semicolon
r_struct
id|vtimer_list
op_star
id|event
suffix:semicolon
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|timer-&gt;cpu
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer-&gt;cpu
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;internal_add_vtimer: BUG, running on wrong CPU&quot;
)paren
suffix:semicolon
multiline_comment|/* if list is empty we only have to set the timer */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|vt_list-&gt;list
)paren
)paren
(brace
multiline_comment|/* reset the offset, this may happen if the last timer was&n;&t;&t; * just deleted by mod_virt_timer and the interrupt&n;&t;&t; * didn&squot;t happen until here&n;&t;&t; */
id|vt_list-&gt;offset
op_assign
l_int|0
suffix:semicolon
r_goto
id|fire
suffix:semicolon
)brace
multiline_comment|/* save progress */
id|asm
r_volatile
(paren
l_string|&quot;STPT %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|done
)paren
)paren
suffix:semicolon
multiline_comment|/* calculate completed work */
id|done
op_assign
id|vt_list-&gt;to_expire
op_minus
id|done
op_plus
id|vt_list-&gt;offset
suffix:semicolon
id|vt_list-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|event
comma
op_amp
id|vt_list-&gt;list
comma
id|entry
)paren
id|event-&gt;expires
op_sub_assign
id|done
suffix:semicolon
id|fire
suffix:colon
id|list_add_sorted
c_func
(paren
id|timer
comma
op_amp
id|vt_list-&gt;list
)paren
suffix:semicolon
multiline_comment|/* get first element, which is the next vtimer slice */
id|event
op_assign
id|list_entry
c_func
(paren
id|vt_list-&gt;list.next
comma
r_struct
id|vtimer_list
comma
id|entry
)paren
suffix:semicolon
id|set_vtimer
c_func
(paren
id|event-&gt;expires
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* release CPU aquired in prepare_vtimer or mod_virt_timer() */
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|prepare_vtimer
r_static
r_inline
r_int
id|prepare_vtimer
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
)paren
(brace
r_if
c_cond
(paren
id|check_vtimer
c_func
(paren
id|timer
)paren
op_logical_or
op_logical_neg
id|timer-&gt;function
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;add_virt_timer: uninitialized timer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|timer-&gt;expires
op_logical_or
id|timer-&gt;expires
OG
id|VTIMER_MAX_SLICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;add_virt_timer: invalid timer expire value!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vtimer_pending
c_func
(paren
id|timer
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;add_virt_timer: timer pending&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|timer-&gt;cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * add_virt_timer - add an oneshot virtual CPU timer&n; */
DECL|function|add_virt_timer
r_void
id|add_virt_timer
c_func
(paren
r_void
op_star
r_new
)paren
(brace
r_struct
id|vtimer_list
op_star
id|timer
suffix:semicolon
id|timer
op_assign
(paren
r_struct
id|vtimer_list
op_star
)paren
r_new
suffix:semicolon
r_if
c_cond
(paren
id|prepare_vtimer
c_func
(paren
id|timer
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|timer-&gt;interval
op_assign
l_int|0
suffix:semicolon
id|internal_add_vtimer
c_func
(paren
id|timer
)paren
suffix:semicolon
)brace
DECL|variable|add_virt_timer
id|EXPORT_SYMBOL
c_func
(paren
id|add_virt_timer
)paren
suffix:semicolon
multiline_comment|/*&n; * add_virt_timer_int - add an interval virtual CPU timer&n; */
DECL|function|add_virt_timer_periodic
r_void
id|add_virt_timer_periodic
c_func
(paren
r_void
op_star
r_new
)paren
(brace
r_struct
id|vtimer_list
op_star
id|timer
suffix:semicolon
id|timer
op_assign
(paren
r_struct
id|vtimer_list
op_star
)paren
r_new
suffix:semicolon
r_if
c_cond
(paren
id|prepare_vtimer
c_func
(paren
id|timer
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|timer-&gt;interval
op_assign
id|timer-&gt;expires
suffix:semicolon
id|internal_add_vtimer
c_func
(paren
id|timer
)paren
suffix:semicolon
)brace
DECL|variable|add_virt_timer_periodic
id|EXPORT_SYMBOL
c_func
(paren
id|add_virt_timer_periodic
)paren
suffix:semicolon
multiline_comment|/*&n; * If we change a pending timer the function must be called on the CPU&n; * where the timer is running on, e.g. by smp_call_function_on()&n; *&n; * The original mod_timer adds the timer if it is not pending. For compatibility&n; * we do the same. The timer will be added on the current CPU as a oneshot timer.&n; *&n; * returns whether it has modified a pending timer (1) or not (0)&n; */
DECL|function|mod_virt_timer
r_int
id|mod_virt_timer
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
comma
id|__u64
id|expires
)paren
(brace
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_if
c_cond
(paren
id|check_vtimer
c_func
(paren
id|timer
)paren
op_logical_or
op_logical_neg
id|timer-&gt;function
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mod_virt_timer: uninitialized timer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|expires
op_logical_or
id|expires
OG
id|VTIMER_MAX_SLICE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mod_virt_timer: invalid expire range&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This is a common optimization triggered by the&n;&t; * networking code - if the timer is re-modified&n;&t; * to be the same thing then just return:&n;&t; */
r_if
c_cond
(paren
id|timer-&gt;expires
op_eq
id|expires
op_logical_and
id|vtimer_pending
c_func
(paren
id|timer
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* disable interrupts before test if timer is pending */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* if timer isn&squot;t pending add it on the current CPU */
r_if
c_cond
(paren
op_logical_neg
id|vtimer_pending
c_func
(paren
id|timer
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* we do not activate an interval timer with mod_virt_timer */
id|timer-&gt;interval
op_assign
l_int|0
suffix:semicolon
id|timer-&gt;expires
op_assign
id|expires
suffix:semicolon
id|timer-&gt;cpu
op_assign
id|cpu
suffix:semicolon
id|internal_add_vtimer
c_func
(paren
id|timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check if we run on the right CPU */
r_if
c_cond
(paren
id|timer-&gt;cpu
op_ne
id|cpu
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mod_virt_timer: running on wrong CPU, check your code&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|list_del_init
c_func
(paren
op_amp
id|timer-&gt;entry
)paren
suffix:semicolon
id|timer-&gt;expires
op_assign
id|expires
suffix:semicolon
multiline_comment|/* also change the interval if we have an interval timer */
r_if
c_cond
(paren
id|timer-&gt;interval
)paren
id|timer-&gt;interval
op_assign
id|expires
suffix:semicolon
multiline_comment|/* the timer can&squot;t expire anymore so we can release the lock */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|internal_add_vtimer
c_func
(paren
id|timer
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|mod_virt_timer
id|EXPORT_SYMBOL
c_func
(paren
id|mod_virt_timer
)paren
suffix:semicolon
multiline_comment|/*&n; * delete a virtual timer&n; *&n; * returns whether the deleted timer was pending (1) or not (0)&n; */
DECL|function|del_virt_timer
r_int
id|del_virt_timer
c_func
(paren
r_struct
id|vtimer_list
op_star
id|timer
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
r_if
c_cond
(paren
id|check_vtimer
c_func
(paren
id|timer
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;del_virt_timer: timer not initialized&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* check if timer is pending */
r_if
c_cond
(paren
op_logical_neg
id|vtimer_pending
c_func
(paren
id|timer
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|timer-&gt;cpu
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t interrupt a running timer, just let it expire! */
id|list_del_init
c_func
(paren
op_amp
id|timer-&gt;entry
)paren
suffix:semicolon
multiline_comment|/* last timer removed */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|vt_list-&gt;list
)paren
)paren
(brace
id|vt_list-&gt;to_expire
op_assign
l_int|0
suffix:semicolon
id|vt_list-&gt;offset
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vt_list-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|del_virt_timer
id|EXPORT_SYMBOL
c_func
(paren
id|del_virt_timer
)paren
suffix:semicolon
multiline_comment|/*&n; * Start the virtual CPU timer on the current CPU.&n; */
DECL|function|init_cpu_vtimer
r_void
id|init_cpu_vtimer
c_func
(paren
r_void
)paren
(brace
r_struct
id|vtimer_queue
op_star
id|vt_list
suffix:semicolon
r_int
r_int
id|cr0
suffix:semicolon
multiline_comment|/* kick the virtual timer */
id|S390_lowcore.exit_timer
op_assign
id|VTIMER_MAX_SLICE
suffix:semicolon
id|S390_lowcore.last_update_timer
op_assign
id|VTIMER_MAX_SLICE
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SPT %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|S390_lowcore.last_update_timer
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;STCK %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|S390_lowcore.last_update_clock
)paren
)paren
suffix:semicolon
id|__ctl_store
c_func
(paren
id|cr0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|cr0
op_or_assign
l_int|0x400
suffix:semicolon
id|__ctl_load
c_func
(paren
id|cr0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|vt_list
op_assign
op_amp
id|per_cpu
c_func
(paren
id|virt_cpu_timer
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vt_list-&gt;list
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|vt_list-&gt;lock
)paren
suffix:semicolon
id|vt_list-&gt;to_expire
op_assign
l_int|0
suffix:semicolon
id|vt_list-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|vt_list-&gt;idle
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|vtimer_idle_notify
r_static
r_int
id|vtimer_idle_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|action
comma
r_void
op_star
id|hcpu
)paren
(brace
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|CPU_IDLE
suffix:colon
id|stop_cpu_timer
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_NOT_IDLE
suffix:colon
id|start_cpu_timer
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
DECL|variable|vtimer_idle_nb
r_static
r_struct
id|notifier_block
id|vtimer_idle_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|vtimer_idle_notify
comma
)brace
suffix:semicolon
DECL|function|vtime_init
r_void
id|__init
id|vtime_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* request the cpu timer external interrupt */
r_if
c_cond
(paren
id|register_early_external_interrupt
c_func
(paren
l_int|0x1005
comma
id|do_cpu_timer_interrupt
comma
op_amp
id|ext_int_info_timer
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t request external interrupt 0x1005&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_idle_notifier
c_func
(paren
op_amp
id|vtimer_idle_nb
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t register idle notifier&quot;
)paren
suffix:semicolon
id|init_cpu_vtimer
c_func
(paren
)paren
suffix:semicolon
)brace
eof
