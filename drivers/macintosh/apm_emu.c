multiline_comment|/* APM emulation layer for PowerMac&n; * &n; * Copyright 2001 Benjamin Herrenschmidt (benh@kernel.crashing.org)&n; *&n; * Lots of code inherited from apm.c, see appropriate notice in&n; *  arch/i386/kernel/apm.c&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(args...) printk(KERN_DEBUG args)
singleline_comment|//#define DBG(args...) xmon_printf(args)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(args...) do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * The apm_bios device is one of the misc char devices.&n; * This is its minor number.&n; */
DECL|macro|APM_MINOR_DEV
mdefine_line|#define&t;APM_MINOR_DEV&t;134
multiline_comment|/*&n; * Maximum number of events stored&n; */
DECL|macro|APM_MAX_EVENTS
mdefine_line|#define APM_MAX_EVENTS&t;&t;20
DECL|macro|FAKE_APM_BIOS_VERSION
mdefine_line|#define FAKE_APM_BIOS_VERSION&t;0x0101
DECL|macro|APM_USER_NOTIFY_TIMEOUT
mdefine_line|#define APM_USER_NOTIFY_TIMEOUT&t;(5*HZ)
multiline_comment|/*&n; * The per-file APM data&n; */
DECL|struct|apm_user
r_struct
id|apm_user
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|next
r_struct
id|apm_user
op_star
id|next
suffix:semicolon
DECL|member|suser
r_int
id|suser
suffix:colon
l_int|1
suffix:semicolon
DECL|member|suspend_waiting
r_int
id|suspend_waiting
suffix:colon
l_int|1
suffix:semicolon
DECL|member|suspends_pending
r_int
id|suspends_pending
suffix:semicolon
DECL|member|suspends_read
r_int
id|suspends_read
suffix:semicolon
DECL|member|event_head
r_int
id|event_head
suffix:semicolon
DECL|member|event_tail
r_int
id|event_tail
suffix:semicolon
DECL|member|events
id|apm_event_t
id|events
(braket
id|APM_MAX_EVENTS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The magic number in apm_user&n; */
DECL|macro|APM_BIOS_MAGIC
mdefine_line|#define APM_BIOS_MAGIC&t;&t;0x4101
multiline_comment|/*&n; * Local variables&n; */
DECL|variable|suspends_pending
r_static
r_int
id|suspends_pending
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|apm_waitqueue
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|apm_suspend_waitqueue
)paren
suffix:semicolon
DECL|variable|user_list
r_static
r_struct
id|apm_user
op_star
id|user_list
suffix:semicolon
r_static
r_int
id|apm_notify_sleep
c_func
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|self
comma
r_int
id|when
)paren
suffix:semicolon
DECL|variable|apm_sleep_notifier
r_static
r_struct
id|pmu_sleep_notifier
id|apm_sleep_notifier
op_assign
(brace
id|apm_notify_sleep
comma
id|SLEEP_LEVEL_USERLAND
comma
)brace
suffix:semicolon
DECL|variable|driver_version
r_static
r_char
id|driver_version
(braket
)braket
op_assign
l_string|&quot;0.5&quot;
suffix:semicolon
multiline_comment|/* no spaces */
macro_line|#ifdef DEBUG
DECL|variable|apm_event_name
r_static
r_char
op_star
id|apm_event_name
(braket
)braket
op_assign
(brace
l_string|&quot;system standby&quot;
comma
l_string|&quot;system suspend&quot;
comma
l_string|&quot;normal resume&quot;
comma
l_string|&quot;critical resume&quot;
comma
l_string|&quot;low battery&quot;
comma
l_string|&quot;power status change&quot;
comma
l_string|&quot;update time&quot;
comma
l_string|&quot;critical suspend&quot;
comma
l_string|&quot;user standby&quot;
comma
l_string|&quot;user suspend&quot;
comma
l_string|&quot;system standby resume&quot;
comma
l_string|&quot;capabilities change&quot;
)brace
suffix:semicolon
DECL|macro|NR_APM_EVENT_NAME
mdefine_line|#define NR_APM_EVENT_NAME&t;&bslash;&n;&t;&t;(sizeof(apm_event_name) / sizeof(apm_event_name[0]))
macro_line|#endif
DECL|function|queue_empty
r_static
r_int
id|queue_empty
c_func
(paren
r_struct
id|apm_user
op_star
id|as
)paren
(brace
r_return
id|as-&gt;event_head
op_eq
id|as-&gt;event_tail
suffix:semicolon
)brace
DECL|function|get_queued_event
r_static
id|apm_event_t
id|get_queued_event
c_func
(paren
r_struct
id|apm_user
op_star
id|as
)paren
(brace
id|as-&gt;event_tail
op_assign
(paren
id|as-&gt;event_tail
op_plus
l_int|1
)paren
op_mod
id|APM_MAX_EVENTS
suffix:semicolon
r_return
id|as-&gt;events
(braket
id|as-&gt;event_tail
)braket
suffix:semicolon
)brace
DECL|function|queue_event
r_static
r_void
id|queue_event
c_func
(paren
id|apm_event_t
id|event
comma
r_struct
id|apm_user
op_star
id|sender
)paren
(brace
r_struct
id|apm_user
op_star
id|as
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;apm_emu: queue_event(%s)&bslash;n&quot;
comma
id|apm_event_name
(braket
id|event
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_list
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|as
op_assign
id|user_list
suffix:semicolon
id|as
op_ne
l_int|NULL
suffix:semicolon
id|as
op_assign
id|as-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|as
op_eq
id|sender
)paren
r_continue
suffix:semicolon
id|as-&gt;event_head
op_assign
(paren
id|as-&gt;event_head
op_plus
l_int|1
)paren
op_mod
id|APM_MAX_EVENTS
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;event_head
op_eq
id|as-&gt;event_tail
)paren
(brace
r_static
r_int
id|notified
suffix:semicolon
r_if
c_cond
(paren
id|notified
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;apm_emu: an event queue overflowed&bslash;n&quot;
)paren
suffix:semicolon
id|as-&gt;event_tail
op_assign
(paren
id|as-&gt;event_tail
op_plus
l_int|1
)paren
op_mod
id|APM_MAX_EVENTS
suffix:semicolon
)brace
id|as-&gt;events
(braket
id|as-&gt;event_head
)braket
op_assign
id|event
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|as-&gt;suser
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|APM_SYS_SUSPEND
suffix:colon
r_case
id|APM_USER_SUSPEND
suffix:colon
id|as-&gt;suspends_pending
op_increment
suffix:semicolon
id|suspends_pending
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|APM_NORMAL_RESUME
suffix:colon
id|as-&gt;suspend_waiting
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|apm_waitqueue
)paren
suffix:semicolon
)brace
DECL|function|check_apm_user
r_static
r_int
id|check_apm_user
c_func
(paren
r_struct
id|apm_user
op_star
id|as
comma
r_const
r_char
op_star
id|func
)paren
(brace
r_if
c_cond
(paren
(paren
id|as
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|as-&gt;magic
op_ne
id|APM_BIOS_MAGIC
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;apm_emu: %s passed bad filp&bslash;n&quot;
comma
id|func
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_read
r_static
id|ssize_t
id|do_read
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
r_char
id|__user
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
r_struct
id|apm_user
op_star
id|as
suffix:semicolon
r_int
id|i
suffix:semicolon
id|apm_event_t
id|event
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|as
op_assign
id|fp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|check_apm_user
c_func
(paren
id|as
comma
l_string|&quot;read&quot;
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
r_sizeof
(paren
id|apm_event_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
id|as
)paren
)paren
(brace
r_if
c_cond
(paren
id|fp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|apm_waitqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_empty
c_func
(paren
id|as
)paren
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|apm_waitqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
id|i
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
op_ge
r_sizeof
(paren
id|event
)paren
)paren
op_logical_and
op_logical_neg
id|queue_empty
c_func
(paren
id|as
)paren
)paren
(brace
id|event
op_assign
id|get_queued_event
c_func
(paren
id|as
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;apm_emu: do_read, returning: %s&bslash;n&quot;
comma
id|apm_event_name
(braket
id|event
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|event
comma
r_sizeof
(paren
id|event
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|count
)paren
r_break
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|APM_SYS_SUSPEND
suffix:colon
r_case
id|APM_USER_SUSPEND
suffix:colon
id|as-&gt;suspends_read
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|buf
op_add_assign
r_sizeof
(paren
id|event
)paren
suffix:semicolon
id|i
op_sub_assign
r_sizeof
(paren
id|event
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|count
)paren
r_return
id|count
op_minus
id|i
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
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_poll
r_static
r_int
r_int
id|do_poll
c_func
(paren
r_struct
id|file
op_star
id|fp
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|apm_user
op_star
id|as
suffix:semicolon
id|as
op_assign
id|fp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|check_apm_user
c_func
(paren
id|as
comma
l_string|&quot;poll&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|poll_wait
c_func
(paren
id|fp
comma
op_amp
id|apm_waitqueue
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue_empty
c_func
(paren
id|as
)paren
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
DECL|function|do_ioctl
r_static
r_int
id|do_ioctl
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
id|filp
comma
id|u_int
id|cmd
comma
id|u_long
id|arg
)paren
(brace
r_struct
id|apm_user
op_star
id|as
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|as
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|check_apm_user
c_func
(paren
id|as
comma
l_string|&quot;ioctl&quot;
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|as-&gt;suser
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|APM_IOC_SUSPEND
suffix:colon
multiline_comment|/* If a suspend message was sent to userland, we&n;&t;&t; * consider this as a confirmation message&n;&t;&t; */
r_if
c_cond
(paren
id|as-&gt;suspends_read
OG
l_int|0
)paren
(brace
id|as-&gt;suspends_read
op_decrement
suffix:semicolon
id|as-&gt;suspends_pending
op_decrement
suffix:semicolon
id|suspends_pending
op_decrement
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Route to PMU suspend ?
r_break
suffix:semicolon
)brace
id|as-&gt;suspend_waiting
op_assign
l_int|1
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|apm_waitqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;apm_emu: ioctl waking up sleep waiter !&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|apm_suspend_waitqueue
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|as-&gt;suspend_waiting
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|apm_waitqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_release
r_static
r_int
id|do_release
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
id|filp
)paren
(brace
r_struct
id|apm_user
op_star
id|as
suffix:semicolon
id|as
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|check_apm_user
c_func
(paren
id|as
comma
l_string|&quot;release&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;suspends_pending
OG
l_int|0
)paren
(brace
id|suspends_pending
op_sub_assign
id|as-&gt;suspends_pending
suffix:semicolon
r_if
c_cond
(paren
id|suspends_pending
op_le
l_int|0
)paren
id|wake_up
c_func
(paren
op_amp
id|apm_suspend_waitqueue
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|user_list
op_eq
id|as
)paren
id|user_list
op_assign
id|as-&gt;next
suffix:semicolon
r_else
(brace
r_struct
id|apm_user
op_star
id|as1
suffix:semicolon
r_for
c_loop
(paren
id|as1
op_assign
id|user_list
suffix:semicolon
(paren
id|as1
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|as1-&gt;next
op_ne
id|as
)paren
suffix:semicolon
id|as1
op_assign
id|as1-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as1
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;apm: filp not in user list&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|as1-&gt;next
op_assign
id|as-&gt;next
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|as
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_open
r_static
r_int
id|do_open
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
id|filp
)paren
(brace
r_struct
id|apm_user
op_star
id|as
suffix:semicolon
id|as
op_assign
(paren
r_struct
id|apm_user
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|as
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;apm: cannot allocate struct of size %d bytes&bslash;n&quot;
comma
r_sizeof
(paren
op_star
id|as
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|as-&gt;magic
op_assign
id|APM_BIOS_MAGIC
suffix:semicolon
id|as-&gt;event_tail
op_assign
id|as-&gt;event_head
op_assign
l_int|0
suffix:semicolon
id|as-&gt;suspends_pending
op_assign
l_int|0
suffix:semicolon
id|as-&gt;suspends_read
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * XXX - this is a tiny bit broken, when we consider BSD&n;         * process accounting. If the device is opened by root, we&n;&t; * instantly flag that we used superuser privs. Who knows,&n;&t; * we might close the device immediately without doing a&n;&t; * privileged operation -- cevans&n;&t; */
id|as-&gt;suser
op_assign
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
suffix:semicolon
id|as-&gt;next
op_assign
id|user_list
suffix:semicolon
id|user_list
op_assign
id|as
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|as
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;apm_emu: opened by %s, suser: %d&bslash;n&quot;
comma
id|current-&gt;comm
comma
(paren
r_int
)paren
id|as-&gt;suser
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Wait for all clients to ack the suspend request. APM API&n; * doesn&squot;t provide a way to NAK, but this could be added&n; * here.&n; */
DECL|function|wait_all_suspend
r_static
r_int
id|wait_all_suspend
c_func
(paren
r_void
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
id|add_wait_queue
c_func
(paren
op_amp
id|apm_suspend_waitqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;apm_emu: wait_all_suspend(), suspends_pending: %d&bslash;n&quot;
comma
id|suspends_pending
)paren
suffix:semicolon
r_while
c_loop
(paren
id|suspends_pending
OG
l_int|0
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|apm_suspend_waitqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;apm_emu: wait_all_suspend() - complete !&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|apm_notify_sleep
r_static
r_int
id|apm_notify_sleep
c_func
(paren
r_struct
id|pmu_sleep_notifier
op_star
id|self
comma
r_int
id|when
)paren
(brace
r_switch
c_cond
(paren
id|when
)paren
(brace
r_case
id|PBOOK_SLEEP_REQUEST
suffix:colon
id|queue_event
c_func
(paren
id|APM_SYS_SUSPEND
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wait_all_suspend
c_func
(paren
)paren
)paren
r_return
id|PBOOK_SLEEP_REFUSE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PBOOK_SLEEP_REJECT
suffix:colon
r_case
id|PBOOK_WAKE
suffix:colon
id|queue_event
c_func
(paren
id|APM_NORMAL_RESUME
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PBOOK_SLEEP_OK
suffix:semicolon
)brace
DECL|macro|APM_CRITICAL
mdefine_line|#define APM_CRITICAL&t;&t;10
DECL|macro|APM_LOW
mdefine_line|#define APM_LOW&t;&t;&t;30
DECL|function|apm_emu_get_info
r_static
r_int
id|apm_emu_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|fpos
comma
r_int
id|length
)paren
(brace
multiline_comment|/* Arguments, with symbols from linux/apm_bios.h.  Information is&n;&t;   from the Get Power Status (0x0a) call unless otherwise noted.&n;&n;&t;   0) Linux driver version (this will change if format changes)&n;&t;   1) APM BIOS Version.  Usually 1.0, 1.1 or 1.2.&n;&t;   2) APM flags from APM Installation Check (0x00):&n;&t;      bit 0: APM_16_BIT_SUPPORT&n;&t;      bit 1: APM_32_BIT_SUPPORT&n;&t;      bit 2: APM_IDLE_SLOWS_CLOCK&n;&t;      bit 3: APM_BIOS_DISABLED&n;&t;      bit 4: APM_BIOS_DISENGAGED&n;&t;   3) AC line status&n;&t;      0x00: Off-line&n;&t;      0x01: On-line&n;&t;      0x02: On backup power (BIOS &gt;= 1.1 only)&n;&t;      0xff: Unknown&n;&t;   4) Battery status&n;&t;      0x00: High&n;&t;      0x01: Low&n;&t;      0x02: Critical&n;&t;      0x03: Charging&n;&t;      0x04: Selected battery not present (BIOS &gt;= 1.2 only)&n;&t;      0xff: Unknown&n;&t;   5) Battery flag&n;&t;      bit 0: High&n;&t;      bit 1: Low&n;&t;      bit 2: Critical&n;&t;      bit 3: Charging&n;&t;      bit 7: No system battery&n;&t;      0xff: Unknown&n;&t;   6) Remaining battery life (percentage of charge):&n;&t;      0-100: valid&n;&t;      -1: Unknown&n;&t;   7) Remaining battery life (time units):&n;&t;      Number of remaining minutes or seconds&n;&t;      -1: Unknown&n;&t;   8) min = minutes; sec = seconds */
r_int
r_int
id|ac_line_status
op_assign
l_int|0xff
suffix:semicolon
r_int
r_int
id|battery_status
op_assign
l_int|0xff
suffix:semicolon
r_int
r_int
id|battery_flag
op_assign
l_int|0xff
suffix:semicolon
r_int
id|percentage
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|time_units
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|real_count
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_char
id|charging
op_assign
l_int|0
suffix:semicolon
r_int
id|charge
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|current
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|btype
op_assign
l_int|0
suffix:semicolon
id|ac_line_status
op_assign
(paren
(paren
id|pmu_power_flags
op_amp
id|PMU_PWR_AC_PRESENT
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pmu_battery_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pmu_batteries
(braket
id|i
)braket
dot
id|flags
op_amp
id|PMU_BATT_PRESENT
)paren
(brace
r_if
c_cond
(paren
id|percentage
OL
l_int|0
)paren
id|percentage
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|charge
OL
l_int|0
)paren
id|charge
op_assign
l_int|0
suffix:semicolon
id|percentage
op_add_assign
(paren
id|pmu_batteries
(braket
id|i
)braket
dot
id|charge
op_star
l_int|100
)paren
op_div
id|pmu_batteries
(braket
id|i
)braket
dot
id|max_charge
suffix:semicolon
id|charge
op_add_assign
id|pmu_batteries
(braket
id|i
)braket
dot
id|charge
suffix:semicolon
id|current
op_add_assign
id|pmu_batteries
(braket
id|i
)braket
dot
id|current
suffix:semicolon
r_if
c_cond
(paren
id|btype
op_eq
l_int|0
)paren
id|btype
op_assign
(paren
id|pmu_batteries
(braket
id|i
)braket
dot
id|flags
op_amp
id|PMU_BATT_TYPE_MASK
)paren
suffix:semicolon
id|real_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pmu_batteries
(braket
id|i
)braket
dot
id|flags
op_amp
id|PMU_BATT_CHARGING
)paren
)paren
id|charging
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|real_count
)paren
(brace
r_if
c_cond
(paren
id|current
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|btype
op_eq
id|PMU_BATT_TYPE_SMART
)paren
id|time_units
op_assign
(paren
id|charge
op_star
l_int|59
)paren
op_div
(paren
id|current
op_star
op_minus
l_int|1
)paren
suffix:semicolon
r_else
id|time_units
op_assign
(paren
id|charge
op_star
l_int|16440
)paren
op_div
(paren
id|current
op_star
op_minus
l_int|60
)paren
suffix:semicolon
)brace
id|percentage
op_div_assign
id|real_count
suffix:semicolon
r_if
c_cond
(paren
id|charging
OG
l_int|0
)paren
(brace
id|battery_status
op_assign
l_int|0x03
suffix:semicolon
id|battery_flag
op_assign
l_int|0x08
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|percentage
op_le
id|APM_CRITICAL
)paren
(brace
id|battery_status
op_assign
l_int|0x02
suffix:semicolon
id|battery_flag
op_assign
l_int|0x04
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|percentage
op_le
id|APM_LOW
)paren
(brace
id|battery_status
op_assign
l_int|0x01
suffix:semicolon
id|battery_flag
op_assign
l_int|0x02
suffix:semicolon
)brace
r_else
(brace
id|battery_status
op_assign
l_int|0x00
suffix:semicolon
id|battery_flag
op_assign
l_int|0x01
suffix:semicolon
)brace
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s %d.%d 0x%02x 0x%02x 0x%02x 0x%02x %d%% %d %s&bslash;n&quot;
comma
id|driver_version
comma
(paren
id|FAKE_APM_BIOS_VERSION
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|FAKE_APM_BIOS_VERSION
op_amp
l_int|0xff
comma
l_int|0
comma
id|ac_line_status
comma
id|battery_status
comma
id|battery_flag
comma
id|percentage
comma
id|time_units
comma
l_string|&quot;min&quot;
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|variable|apm_bios_fops
r_static
r_struct
id|file_operations
id|apm_bios_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|do_read
comma
dot
id|poll
op_assign
id|do_poll
comma
dot
id|ioctl
op_assign
id|do_ioctl
comma
dot
id|open
op_assign
id|do_open
comma
dot
id|release
op_assign
id|do_release
comma
)brace
suffix:semicolon
DECL|variable|apm_device
r_static
r_struct
id|miscdevice
id|apm_device
op_assign
(brace
id|APM_MINOR_DEV
comma
l_string|&quot;apm_bios&quot;
comma
op_amp
id|apm_bios_fops
)brace
suffix:semicolon
DECL|function|apm_emu_init
r_static
r_int
id|__init
id|apm_emu_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|apm_proc
suffix:semicolon
r_if
c_cond
(paren
id|sys_ctrler
op_ne
id|SYS_CTRLER_PMU
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;apm_emu: Requires a machine with a PMU.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|apm_proc
op_assign
id|create_proc_info_entry
c_func
(paren
l_string|&quot;apm&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|apm_emu_get_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apm_proc
)paren
id|apm_proc-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|apm_device
)paren
suffix:semicolon
id|pmu_register_sleep_notifier
c_func
(paren
op_amp
id|apm_sleep_notifier
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;apm_emu: APM Emulation %s initialized.&bslash;n&quot;
comma
id|driver_version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|apm_emu_exit
r_static
r_void
id|__exit
id|apm_emu_exit
c_func
(paren
r_void
)paren
(brace
id|pmu_unregister_sleep_notifier
c_func
(paren
op_amp
id|apm_sleep_notifier
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|apm_device
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;apm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;apm_emu: APM Emulation removed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|apm_emu_init
id|module_init
c_func
(paren
id|apm_emu_init
)paren
suffix:semicolon
DECL|variable|apm_emu_exit
id|module_exit
c_func
(paren
id|apm_emu_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Benjamin Herrenschmidt&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;APM emulation layer for PowerMac&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
