multiline_comment|/*&n; *&t;Real Time Clock interface for q40 and other m68k machines&n; *      emulate some RTC irq capabilities in software&n; *&n; *      Copyright (C) 1999 Richard Zidlicky&n; *&n; *&t;based on Paul Gortmaker&squot;s rtc.c device and&n; *           Sam Creasey Generic rtc driver&n; *&n; *&t;This driver allows use of the real time clock (built into&n; *&t;nearly all computers) from user space. It exports the /dev/rtc&n; *&t;interface supporting various ioctl() and also the /proc/dev/rtc&n; *&t;pseudo-file for status information.&n; *&n; *&t;The ioctls can be used to set the interrupt behaviour where&n; *  supported.&n; *&n; *&t;The /dev/rtc interface will block on reads until an interrupt&n; *&t;has been received. If a RTC interrupt has already happened,&n; *&t;it will output an unsigned long and then block. The output value&n; *&t;contains the interrupt status in the low byte and the number of&n; *&t;interrupts since the last read in the remaining high bytes. The&n; *&t;/dev/rtc interface can also be used with the select(2) call.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n;&n; *      1.01 fix for 2.3.X                    rz@linux-m68k.org&n; *      1.02 merged with code from genrtc.c   rz@linux-m68k.org&n; *      1.03 make it more portable            zippel@linux-m68k.org&n; *      1.04 removed useless timer code       rz@linux-m68k.org&n; *      1.05 portable RTC_UIE emulation       rz@linux-m68k.org&n; *      1.06 set_rtc_time can return an error trini@kernel.crashing.org&n; */
DECL|macro|RTC_VERSION
mdefine_line|#define RTC_VERSION&t;&quot;1.06&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
multiline_comment|/*&n; *&t;We sponge a minor off of the misc major. No need slurping&n; *&t;up another valuable major dev number for this. If you add&n; *&t;an ioctl, make sure you don&squot;t conflict with SPARC&squot;s RTC&n; *&t;ioctls.&n; */
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|gen_rtc_wait
)paren
suffix:semicolon
r_static
r_int
id|gen_rtc_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Bits in gen_rtc_status.&n; */
DECL|macro|RTC_IS_OPEN
mdefine_line|#define RTC_IS_OPEN&t;&t;0x01&t;/* means /dev/rtc is in use&t;*/
DECL|variable|gen_rtc_status
r_int
r_char
id|gen_rtc_status
suffix:semicolon
multiline_comment|/* bitmapped status byte.&t;*/
DECL|variable|gen_rtc_irq_data
r_int
r_int
id|gen_rtc_irq_data
suffix:semicolon
multiline_comment|/* our output to the world&t;*/
multiline_comment|/* months start at 0 now */
DECL|variable|days_in_mo
r_int
r_char
id|days_in_mo
(braket
)braket
op_assign
(brace
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|variable|irq_active
r_static
r_int
id|irq_active
suffix:semicolon
macro_line|#ifdef CONFIG_GEN_RTC_X
DECL|variable|genrtc_task
r_struct
id|tq_struct
id|genrtc_task
suffix:semicolon
DECL|variable|timer_task
r_static
r_struct
id|timer_list
id|timer_task
suffix:semicolon
DECL|variable|oldsecs
r_static
r_int
r_int
id|oldsecs
suffix:semicolon
DECL|variable|lostint
r_static
r_int
id|lostint
suffix:semicolon
DECL|variable|tt_exp
r_static
r_int
id|tt_exp
suffix:semicolon
r_void
id|gen_rtc_timer
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|variable|stask_active
r_static
r_volatile
r_int
id|stask_active
suffix:semicolon
multiline_comment|/* schedule_task */
DECL|variable|ttask_active
r_static
r_volatile
r_int
id|ttask_active
suffix:semicolon
multiline_comment|/* timer_task */
DECL|variable|stop_rtc_timers
r_static
r_int
id|stop_rtc_timers
suffix:semicolon
multiline_comment|/* don&squot;t requeue tasks */
DECL|variable|gen_rtc_lock
r_static
id|spinlock_t
id|gen_rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Routine to poll RTC seconds field for change as often as posible,&n; * after first RTC_UIE use timer to reduce polling&n; */
DECL|function|genrtc_troutine
r_void
id|genrtc_troutine
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|get_rtc_ss
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stop_rtc_timers
)paren
(brace
id|stask_active
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldsecs
op_ne
id|tmp
)paren
(brace
id|oldsecs
op_assign
id|tmp
suffix:semicolon
id|timer_task.function
op_assign
id|gen_rtc_timer
suffix:semicolon
id|timer_task.expires
op_assign
id|jiffies
op_plus
id|HZ
op_minus
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
id|tt_exp
op_assign
id|timer_task.expires
suffix:semicolon
id|ttask_active
op_assign
l_int|1
suffix:semicolon
id|stask_active
op_assign
l_int|0
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|timer_task
)paren
suffix:semicolon
id|gen_rtc_interrupt
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|schedule_task
c_func
(paren
op_amp
id|genrtc_task
)paren
op_eq
l_int|0
)paren
id|stask_active
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|gen_rtc_timer
r_void
id|gen_rtc_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|lostint
op_assign
id|get_rtc_ss
c_func
(paren
)paren
op_minus
id|oldsecs
suffix:semicolon
r_if
c_cond
(paren
id|lostint
OL
l_int|0
)paren
id|lostint
op_assign
l_int|60
op_minus
id|lostint
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|tt_exp
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;genrtc: timer task delayed by %ld jiffies&bslash;n&quot;
comma
id|jiffies
op_minus
id|tt_exp
)paren
suffix:semicolon
id|ttask_active
op_assign
l_int|0
suffix:semicolon
id|stask_active
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|schedule_task
c_func
(paren
op_amp
id|genrtc_task
)paren
op_eq
l_int|0
)paren
)paren
id|stask_active
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * call gen_rtc_interrupt function to signal an RTC_UIE,&n; * arg is unused.&n; * Could be invoked either from a real interrupt handler or&n; * from some routine that periodically (eg 100HZ) monitors&n; * whether RTC_SECS changed&n; */
DECL|function|gen_rtc_interrupt
r_void
id|gen_rtc_interrupt
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
multiline_comment|/*  We store the status in the low byte and the number of&n;&t; *&t;interrupts received since the last read in the remainder&n;&t; *&t;of rtc_irq_data.  */
id|gen_rtc_irq_data
op_add_assign
l_int|0x100
suffix:semicolon
id|gen_rtc_irq_data
op_and_assign
op_complement
l_int|0xff
suffix:semicolon
id|gen_rtc_irq_data
op_or_assign
id|RTC_UIE
suffix:semicolon
r_if
c_cond
(paren
id|lostint
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;genrtc: system delaying clock ticks?&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* increment count so that userspace knows something is wrong */
id|gen_rtc_irq_data
op_add_assign
(paren
(paren
id|lostint
op_minus
l_int|1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|lostint
op_assign
l_int|0
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|gen_rtc_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Now all the various file operations that we export.&n; */
DECL|function|gen_rtc_read
r_static
id|ssize_t
id|gen_rtc_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
r_int
id|data
suffix:semicolon
id|ssize_t
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
r_sizeof
(paren
r_int
r_int
)paren
op_logical_and
id|count
op_ne
r_sizeof
(paren
r_int
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
op_logical_and
op_logical_neg
id|gen_rtc_irq_data
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|gen_rtc_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|data
op_assign
id|xchg
c_func
(paren
op_amp
id|gen_rtc_irq_data
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|out
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* first test allows optimizer to nuke this case for 32-bit machines */
r_if
c_cond
(paren
r_sizeof
(paren
r_int
)paren
op_ne
r_sizeof
(paren
r_int
)paren
op_logical_and
id|count
op_eq
r_sizeof
(paren
r_int
r_int
)paren
)paren
(brace
r_int
r_int
id|uidata
op_assign
id|data
suffix:semicolon
id|retval
op_assign
id|put_user
c_func
(paren
id|uidata
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
id|retval
op_assign
id|put_user
c_func
(paren
id|data
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
id|retval
op_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|out
suffix:colon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|gen_rtc_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|gen_rtc_poll
r_static
r_int
r_int
id|gen_rtc_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|gen_rtc_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gen_rtc_irq_data
op_ne
l_int|0
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Used to disable/enable interrupts, only RTC_UIE supported&n; * We also clear out any old irq data after an ioctl() that&n; * meddles with the interrupt enable/disable bits.&n; */
DECL|function|gen_clear_rtc_irq_bit
r_static
r_inline
r_void
id|gen_clear_rtc_irq_bit
c_func
(paren
r_int
r_char
id|bit
)paren
(brace
macro_line|#ifdef CONFIG_GEN_RTC_X
id|stop_rtc_timers
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ttask_active
)paren
(brace
id|del_timer_sync
c_func
(paren
op_amp
id|timer_task
)paren
suffix:semicolon
id|ttask_active
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|stask_active
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|gen_rtc_lock
)paren
suffix:semicolon
id|irq_active
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|gen_rtc_lock
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|gen_set_rtc_irq_bit
r_static
r_inline
r_int
id|gen_set_rtc_irq_bit
c_func
(paren
r_int
r_char
id|bit
)paren
(brace
macro_line|#ifdef CONFIG_GEN_RTC_X
id|spin_lock
c_func
(paren
op_amp
id|gen_rtc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_active
)paren
(brace
id|irq_active
op_assign
l_int|1
suffix:semicolon
id|stop_rtc_timers
op_assign
l_int|0
suffix:semicolon
id|lostint
op_assign
l_int|0
suffix:semicolon
id|genrtc_task.routine
op_assign
id|genrtc_troutine
suffix:semicolon
id|oldsecs
op_assign
id|get_rtc_ss
c_func
(paren
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|timer_task
)paren
suffix:semicolon
id|stask_active
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|schedule_task
c_func
(paren
op_amp
id|genrtc_task
)paren
op_eq
l_int|0
)paren
(brace
id|stask_active
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|gen_rtc_lock
)paren
suffix:semicolon
id|gen_rtc_irq_data
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
DECL|function|gen_rtc_ioctl
r_static
r_int
id|gen_rtc_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|rtc_time
id|wtime
suffix:semicolon
r_struct
id|rtc_pll_info
id|pll
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_PLL_GET
suffix:colon
r_if
c_cond
(paren
id|get_rtc_pll
c_func
(paren
op_amp
id|pll
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|pll
comma
r_sizeof
id|pll
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|RTC_PLL_SET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|pll
comma
(paren
r_struct
id|rtc_pll_info
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|pll
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|set_rtc_pll
c_func
(paren
op_amp
id|pll
)paren
suffix:semicolon
r_case
id|RTC_UIE_OFF
suffix:colon
multiline_comment|/* disable ints from RTC updates.&t;*/
id|gen_clear_rtc_irq_bit
c_func
(paren
id|RTC_UIE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|RTC_UIE_ON
suffix:colon
multiline_comment|/* enable ints for RTC updates.&t;*/
r_return
id|gen_set_rtc_irq_bit
c_func
(paren
id|RTC_UIE
)paren
suffix:semicolon
r_case
id|RTC_RD_TIME
suffix:colon
multiline_comment|/* Read the time/date from RTC&t;*/
multiline_comment|/* this doesn&squot;t get week-day, who cares */
id|memset
c_func
(paren
op_amp
id|wtime
comma
l_int|0
comma
r_sizeof
(paren
id|wtime
)paren
)paren
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|wtime
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|wtime
comma
r_sizeof
(paren
id|wtime
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|RTC_SET_TIME
suffix:colon
multiline_comment|/* Set the RTC */
(brace
r_int
id|year
suffix:semicolon
r_int
r_char
id|leap_yr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|wtime
comma
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|wtime
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|year
op_assign
id|wtime.tm_year
op_plus
l_int|1900
suffix:semicolon
id|leap_yr
op_assign
(paren
(paren
op_logical_neg
(paren
id|year
op_mod
l_int|4
)paren
op_logical_and
(paren
id|year
op_mod
l_int|100
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|year
op_mod
l_int|400
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wtime.tm_mon
template_param
l_int|11
)paren
op_logical_or
(paren
id|wtime.tm_mday
OL
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|wtime.tm_mday
template_param
(paren
id|days_in_mo
(braket
id|wtime.tm_mon
)braket
op_plus
(paren
(paren
id|wtime.tm_mon
op_eq
l_int|1
)paren
op_logical_and
id|leap_yr
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|wtime.tm_hour
OL
l_int|0
op_logical_or
id|wtime.tm_hour
op_ge
l_int|24
op_logical_or
id|wtime.tm_min
OL
l_int|0
op_logical_or
id|wtime.tm_min
op_ge
l_int|60
op_logical_or
id|wtime.tm_sec
OL
l_int|0
op_logical_or
id|wtime.tm_sec
op_ge
l_int|60
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|set_rtc_time
c_func
(paren
op_amp
id|wtime
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We enforce only one user at a time here with the open/close.&n; *&t;Also clear the previous interrupt data on an open, and clean&n; *&t;up things on a close.&n; */
DECL|function|gen_rtc_open
r_static
r_int
id|gen_rtc_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|gen_rtc_status
op_amp
id|RTC_IS_OPEN
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|gen_rtc_status
op_or_assign
id|RTC_IS_OPEN
suffix:semicolon
id|gen_rtc_irq_data
op_assign
l_int|0
suffix:semicolon
id|irq_active
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gen_rtc_release
r_static
r_int
id|gen_rtc_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
multiline_comment|/*&n;&t; * Turn off all interrupts once the device is no longer&n;&t; * in use and clear the data.&n;&t; */
id|gen_clear_rtc_irq_bit
c_func
(paren
id|RTC_PIE
op_or
id|RTC_AIE
op_or
id|RTC_UIE
)paren
suffix:semicolon
id|gen_rtc_status
op_and_assign
op_complement
id|RTC_IS_OPEN
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|gen_rtc_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;The various file operations we support.&n; */
DECL|variable|gen_rtc_fops
r_static
r_struct
id|file_operations
id|gen_rtc_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
macro_line|#ifdef CONFIG_GEN_RTC_X
dot
id|read
op_assign
id|gen_rtc_read
comma
dot
id|poll
op_assign
id|gen_rtc_poll
comma
macro_line|#endif
dot
id|ioctl
op_assign
id|gen_rtc_ioctl
comma
dot
id|open
op_assign
id|gen_rtc_open
comma
dot
id|release
op_assign
id|gen_rtc_release
)brace
suffix:semicolon
DECL|variable|rtc_gen_dev
r_static
r_struct
id|miscdevice
id|rtc_gen_dev
op_assign
(brace
id|RTC_MINOR
comma
l_string|&quot;rtc&quot;
comma
op_amp
id|gen_rtc_fops
)brace
suffix:semicolon
DECL|function|rtc_generic_init
r_int
id|__init
id|rtc_generic_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Generic RTC Driver v%s&bslash;n&quot;
comma
id|RTC_VERSION
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|rtc_gen_dev
)paren
suffix:semicolon
id|create_proc_read_entry
(paren
l_string|&quot;driver/rtc&quot;
comma
l_int|0
comma
l_int|0
comma
id|gen_rtc_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtc_generic_exit
r_static
r_void
id|__exit
id|rtc_generic_exit
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
(paren
l_string|&quot;driver/rtc&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|rtc_gen_dev
)paren
suffix:semicolon
)brace
DECL|variable|rtc_generic_init
id|module_init
c_func
(paren
id|rtc_generic_init
)paren
suffix:semicolon
DECL|variable|rtc_generic_exit
id|module_exit
c_func
(paren
id|rtc_generic_exit
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
multiline_comment|/*&n; *&t;Info exported via &quot;/proc/rtc&quot;.&n; */
DECL|function|gen_rtc_proc_output
r_int
id|gen_rtc_proc_output
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_struct
id|rtc_pll_info
id|pll
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;rtc_time&bslash;t: %02d:%02d:%02d&bslash;n&quot;
l_string|&quot;rtc_date&bslash;t: %04d-%02d-%02d&bslash;n&quot;
l_string|&quot;rtc_epoch&bslash;t: %04u&bslash;n&quot;
comma
id|tm.tm_hour
comma
id|tm.tm_min
comma
id|tm.tm_sec
comma
id|tm.tm_year
op_plus
l_int|1900
comma
id|tm.tm_mon
op_plus
l_int|1
comma
id|tm.tm_mday
comma
l_int|1900
)paren
suffix:semicolon
id|tm.tm_hour
op_assign
l_int|0
suffix:semicolon
id|tm.tm_min
op_assign
l_int|0
suffix:semicolon
id|tm.tm_sec
op_assign
l_int|0
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;alarm&bslash;t&bslash;t: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tm.tm_hour
op_le
l_int|24
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%02d:&quot;
comma
id|tm.tm_hour
)paren
suffix:semicolon
r_else
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;**:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tm.tm_min
op_le
l_int|59
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%02d:&quot;
comma
id|tm.tm_min
)paren
suffix:semicolon
r_else
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;**:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tm.tm_sec
op_le
l_int|59
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%02d&bslash;n&quot;
comma
id|tm.tm_sec
)paren
suffix:semicolon
r_else
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;**&bslash;n&quot;
)paren
suffix:semicolon
id|tmp
op_assign
id|RTC_24H
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DST_enable&bslash;t: %s&bslash;n&quot;
l_string|&quot;BCD&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;24hr&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;square_wave&bslash;t: %s&bslash;n&quot;
l_string|&quot;alarm_IRQ&bslash;t: %s&bslash;n&quot;
l_string|&quot;update_IRQ&bslash;t: %s&bslash;n&quot;
l_string|&quot;periodic_IRQ&bslash;t: %s&bslash;n&quot;
l_string|&quot;periodic_freq&bslash;t: %ld&bslash;n&quot;
l_string|&quot;batt_status&bslash;t: %s&bslash;n&quot;
comma
(paren
id|tmp
op_amp
id|RTC_DST_EN
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|tmp
op_amp
id|RTC_DM_BINARY
)paren
ques
c_cond
l_string|&quot;no&quot;
suffix:colon
l_string|&quot;yes&quot;
comma
(paren
id|tmp
op_amp
id|RTC_24H
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|tmp
op_amp
id|RTC_SQWE
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|tmp
op_amp
id|RTC_AIE
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|irq_active
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|tmp
op_amp
id|RTC_PIE
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
l_int|0L
multiline_comment|/* freq */
comma
l_string|&quot;okay&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_rtc_pll
c_func
(paren
op_amp
id|pll
)paren
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;PLL adjustment&bslash;t: %d&bslash;n&quot;
l_string|&quot;PLL max +ve adjustment&bslash;t: %d&bslash;n&quot;
l_string|&quot;PLL max -ve adjustment&bslash;t: %d&bslash;n&quot;
l_string|&quot;PLL +ve adjustment factor&bslash;t: %d&bslash;n&quot;
l_string|&quot;PLL -ve adjustment factor&bslash;t: %d&bslash;n&quot;
l_string|&quot;PLL frequency&bslash;t: %ld&bslash;n&quot;
comma
id|pll.pll_value
comma
id|pll.pll_max
comma
id|pll.pll_min
comma
id|pll.pll_posmult
comma
id|pll.pll_negmult
comma
id|pll.pll_clock
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|gen_rtc_read_proc
r_static
r_int
id|gen_rtc_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|gen_rtc_proc_output
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Richard Zidlicky&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof