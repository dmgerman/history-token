multiline_comment|/*&n; * Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Communication to userspace based on kernel/printk.c&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUG(A...)&t;printk(KERN_ERR A)
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(A...)
macro_line|#endif
DECL|variable|rtas_log_lock
r_static
id|spinlock_t
id|rtas_log_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|rtas_log_wait
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|rtas_log_wait
)paren
suffix:semicolon
DECL|macro|LOG_NUMBER
mdefine_line|#define LOG_NUMBER&t;&t;64&t;&t;/* must be a power of two */
DECL|macro|LOG_NUMBER_MASK
mdefine_line|#define LOG_NUMBER_MASK&t;&t;(LOG_NUMBER-1)
DECL|variable|rtas_log_buf
r_static
r_char
op_star
id|rtas_log_buf
suffix:semicolon
DECL|variable|rtas_log_start
r_static
r_int
r_int
id|rtas_log_start
suffix:semicolon
DECL|variable|rtas_log_size
r_static
r_int
r_int
id|rtas_log_size
suffix:semicolon
DECL|variable|surveillance_requested
r_static
r_int
id|surveillance_requested
suffix:semicolon
DECL|variable|rtas_event_scan_rate
r_static
r_int
r_int
id|rtas_event_scan_rate
suffix:semicolon
DECL|variable|rtas_error_log_max
r_static
r_int
r_int
id|rtas_error_log_max
suffix:semicolon
DECL|macro|EVENT_SCAN_ALL_EVENTS
mdefine_line|#define EVENT_SCAN_ALL_EVENTS&t;0xf0000000
DECL|macro|SURVEILLANCE_TOKEN
mdefine_line|#define SURVEILLANCE_TOKEN&t;9000
DECL|macro|SURVEILLANCE_TIMEOUT
mdefine_line|#define SURVEILLANCE_TIMEOUT&t;1
DECL|macro|SURVEILLANCE_SCANRATE
mdefine_line|#define SURVEILLANCE_SCANRATE&t;1
multiline_comment|/*&n; * Since we use 32 bit RTAS, the physical address of this must be below&n; * 4G or else bad things happen. Allocate this in the kernel data and&n; * make it big enough.&n; */
DECL|macro|RTAS_ERROR_LOG_MAX
mdefine_line|#define RTAS_ERROR_LOG_MAX 1024
DECL|variable|logdata
r_static
r_int
r_char
id|logdata
(braket
id|RTAS_ERROR_LOG_MAX
)braket
suffix:semicolon
DECL|function|rtas_log_open
r_static
r_int
id|rtas_log_open
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtas_log_release
r_static
r_int
id|rtas_log_release
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtas_log_read
r_static
id|ssize_t
id|rtas_log_read
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
r_int
id|error
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|count
OL
id|rtas_error_log_max
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|count
op_assign
id|rtas_error_log_max
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|rtas_error_log_max
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|error
op_assign
id|wait_event_interruptible
c_func
(paren
id|rtas_log_wait
comma
id|rtas_log_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtas_log_lock
)paren
suffix:semicolon
id|offset
op_assign
id|rtas_error_log_max
op_star
(paren
id|rtas_log_start
op_amp
id|LOG_NUMBER_MASK
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|tmp
comma
op_amp
id|rtas_log_buf
(braket
id|offset
)braket
comma
id|count
)paren
suffix:semicolon
id|rtas_log_start
op_add_assign
l_int|1
suffix:semicolon
id|rtas_log_size
op_sub_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtas_log_lock
)paren
suffix:semicolon
id|error
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|tmp
comma
id|count
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|count
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|rtas_log_poll
r_static
r_int
r_int
id|rtas_log_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
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
id|rtas_log_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas_log_size
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
DECL|variable|proc_rtas_log_operations
r_struct
id|file_operations
id|proc_rtas_log_operations
op_assign
(brace
id|read
suffix:colon
id|rtas_log_read
comma
id|poll
suffix:colon
id|rtas_log_poll
comma
id|open
suffix:colon
id|rtas_log_open
comma
id|release
suffix:colon
id|rtas_log_release
comma
)brace
suffix:semicolon
DECL|function|log_rtas
r_static
r_void
id|log_rtas
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;logging rtas event&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtas_log_lock
)paren
suffix:semicolon
id|offset
op_assign
id|rtas_error_log_max
op_star
(paren
(paren
id|rtas_log_start
op_plus
id|rtas_log_size
)paren
op_amp
id|LOG_NUMBER_MASK
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|rtas_log_buf
(braket
id|offset
)braket
comma
id|buf
comma
id|rtas_error_log_max
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas_log_size
OL
id|LOG_NUMBER
)paren
id|rtas_log_size
op_add_assign
l_int|1
suffix:semicolon
r_else
id|rtas_log_start
op_add_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtas_log_lock
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|rtas_log_wait
)paren
suffix:semicolon
)brace
DECL|function|enable_surveillance
r_static
r_int
id|enable_surveillance
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;set-indicator&quot;
)paren
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|SURVEILLANCE_TOKEN
comma
l_int|0
comma
id|SURVEILLANCE_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtasd: could not enable surveillance&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rtas_event_scan_rate
op_assign
id|SURVEILLANCE_SCANRATE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_eventscan_parms
r_static
r_int
id|get_eventscan_parms
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
op_star
id|ip
suffix:semicolon
id|node
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
suffix:semicolon
id|ip
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;rtas-event-scan-rate&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtasd: no rtas-event-scan-rate&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rtas_event_scan_rate
op_assign
op_star
id|ip
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;rtas-event-scan-rate %d&bslash;n&quot;
comma
id|rtas_event_scan_rate
)paren
suffix:semicolon
id|ip
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;rtas-error-log-max&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtasd: no rtas-error-log-max&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rtas_error_log_max
op_assign
op_star
id|ip
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;rtas-error-log-max %d&bslash;n&quot;
comma
id|rtas_error_log_max
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas_error_log_max
OG
id|RTAS_ERROR_LOG_MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtasd: truncated error log from %d to %d bytes&bslash;n&quot;
comma
id|rtas_error_log_max
comma
id|RTAS_ERROR_LOG_MAX
)paren
suffix:semicolon
id|rtas_error_log_max
op_assign
id|RTAS_ERROR_LOG_MAX
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|sys_sched_get_priority_max
c_func
(paren
r_int
id|policy
)paren
suffix:semicolon
DECL|function|rtasd
r_static
r_int
id|rtasd
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|cpu
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|first_pass
op_assign
l_int|1
suffix:semicolon
r_int
id|event_scan
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;event-scan&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event_scan
op_eq
id|RTAS_UNKNOWN_SERVICE
op_logical_or
id|get_eventscan_parms
c_func
(paren
)paren
op_eq
op_minus
l_int|1
)paren
r_goto
id|error
suffix:semicolon
id|rtas_log_buf
op_assign
id|vmalloc
c_func
(paren
id|rtas_error_log_max
op_star
id|LOG_NUMBER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rtas_log_buf
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtasd: no memory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_string|&quot;will sleep for %d jiffies&bslash;n&quot;
comma
(paren
id|HZ
op_star
l_int|60
op_div
id|rtas_event_scan_rate
)paren
op_div
l_int|2
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;rtasd&quot;
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Rusty unreal time task */
id|current-&gt;policy
op_assign
id|SCHED_FIFO
suffix:semicolon
id|current-&gt;nice
op_assign
id|sys_sched_get_priority_max
c_func
(paren
id|SCHED_FIFO
)paren
op_plus
l_int|1
suffix:semicolon
macro_line|#endif
id|cpu
op_assign
l_int|0
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
l_int|1UL
op_lshift
id|cpu_logical_map
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_do
(brace
id|memset
c_func
(paren
id|logdata
comma
l_int|0
comma
id|rtas_error_log_max
)paren
suffix:semicolon
id|error
op_assign
id|rtas_call
c_func
(paren
id|event_scan
comma
l_int|4
comma
l_int|1
comma
l_int|NULL
comma
id|EVENT_SCAN_ALL_EVENTS
comma
l_int|0
comma
id|__pa
c_func
(paren
id|logdata
)paren
comma
id|rtas_error_log_max
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;event-scan failed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|log_rtas
c_func
(paren
id|logdata
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|error
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_string|&quot;watchdog scheduled on cpu %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|cpu
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_ge
id|smp_num_cpus
)paren
(brace
r_if
c_cond
(paren
id|first_pass
op_logical_and
id|surveillance_requested
)paren
(brace
id|DEBUG
c_func
(paren
l_string|&quot;enabling surveillance&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable_surveillance
c_func
(paren
)paren
)paren
r_goto
id|error_vfree
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;surveillance enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|first_pass
op_assign
l_int|0
suffix:semicolon
id|cpu
op_assign
l_int|0
suffix:semicolon
)brace
id|set_cpus_allowed
c_func
(paren
id|current
comma
l_int|1UL
op_lshift
id|cpu_logical_map
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
multiline_comment|/* Check all cpus for pending events before sleeping*/
r_if
c_cond
(paren
op_logical_neg
id|first_pass
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
id|HZ
op_star
l_int|60
op_div
id|rtas_event_scan_rate
)paren
op_div
l_int|2
)paren
suffix:semicolon
)brace
)brace
id|error_vfree
suffix:colon
id|vfree
c_func
(paren
id|rtas_log_buf
)paren
suffix:semicolon
id|error
suffix:colon
multiline_comment|/* Should delete proc entries */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|rtas_init
r_static
r_int
id|__init
id|rtas_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|rtas_dir
comma
op_star
id|entry
suffix:semicolon
id|rtas_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;rtas&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rtas_dir
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to create rtas proc directory&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;error_log&quot;
comma
id|S_IRUSR
comma
id|rtas_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_rtas_log_operations
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to create rtas/error_log proc entry&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kernel_thread
c_func
(paren
id|rtasd
comma
l_int|0
comma
id|CLONE_FS
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to start RTAS daemon&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RTAS daemon started&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|surveillance_setup
r_static
r_int
id|__init
id|surveillance_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
id|surveillance_requested
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|rtas_init
id|__initcall
c_func
(paren
id|rtas_init
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;surveillance=&quot;
comma
id|surveillance_setup
)paren
suffix:semicolon
eof
