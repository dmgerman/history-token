multiline_comment|/*&n; * Copyright (C) 2001 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Communication to userspace based on kernel/printk.c&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUG(A...)&t;printk(KERN_ERR A)
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(A...)
macro_line|#endif
DECL|variable|log_lock
r_static
id|spinlock_t
id|log_lock
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
DECL|variable|surveillance_timeout
r_static
r_int
id|surveillance_timeout
op_assign
op_minus
l_int|1
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
DECL|variable|rtas_error_log_buffer_max
r_static
r_int
r_int
id|rtas_error_log_buffer_max
suffix:semicolon
r_extern
r_volatile
r_int
id|no_more_logging
suffix:semicolon
DECL|variable|error_log_cnt
r_volatile
r_int
id|error_log_cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Since we use 32 bit RTAS, the physical address of this must be below&n; * 4G or else bad things happen. Allocate this in the kernel data and&n; * make it big enough.&n; */
DECL|variable|logdata
r_static
r_int
r_char
id|logdata
(braket
id|RTAS_ERROR_LOG_MAX
)braket
suffix:semicolon
multiline_comment|/* To see this info, grep RTAS /var/log/messages and each entry&n; * will be collected together with obvious begin/end.&n; * There will be a unique identifier on the begin and end lines.&n; * This will persist across reboots.&n; *&n; * format of error logs returned from RTAS:&n; * bytes&t;(size)&t;: contents&n; * --------------------------------------------------------&n; * 0-7&t;&t;(8)&t;: rtas_error_log&n; * 8-47&t;&t;(40)&t;: extended info&n; * 48-51&t;(4)&t;: vendor id&n; * 52-1023 (vendor specific) : location code and debug data&n; */
DECL|function|printk_log_rtas
r_static
r_void
id|printk_log_rtas
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
comma
id|j
comma
id|n
suffix:semicolon
r_int
id|perline
op_assign
l_int|16
suffix:semicolon
r_char
id|buffer
(braket
l_int|64
)braket
suffix:semicolon
r_char
op_star
id|str
op_assign
l_string|&quot;RTAS event&quot;
suffix:semicolon
id|printk
c_func
(paren
id|RTAS_ERR
l_string|&quot;%d -------- %s begin --------&bslash;n&quot;
comma
id|error_log_cnt
comma
id|str
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Print perline bytes on each line, each line will start&n;&t; * with RTAS and a changing number, so syslogd will&n;&t; * print lines that are otherwise the same.  Separate every&n;&t; * 4 bytes with a space.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|i
op_mod
id|perline
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
l_int|0
)paren
(brace
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
r_sizeof
(paren
id|buffer
)paren
)paren
suffix:semicolon
id|n
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;RTAS %d:&quot;
comma
id|i
op_div
id|perline
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|4
)paren
op_eq
l_int|0
)paren
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot;%02x&quot;
comma
(paren
r_int
r_char
)paren
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
(paren
id|perline
op_minus
l_int|1
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|i
op_mod
id|perline
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
id|printk
c_func
(paren
id|RTAS_ERR
l_string|&quot;%d -------- %s end ----------&bslash;n&quot;
comma
id|error_log_cnt
comma
id|str
)paren
suffix:semicolon
)brace
DECL|function|log_rtas_len
r_static
r_int
id|log_rtas_len
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|rtas_error_log
op_star
id|err
suffix:semicolon
multiline_comment|/* rtas fixed header */
id|len
op_assign
l_int|8
suffix:semicolon
id|err
op_assign
(paren
r_struct
id|rtas_error_log
op_star
)paren
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|err-&gt;extended_log_length
)paren
(brace
multiline_comment|/* extended header */
id|len
op_add_assign
id|err-&gt;extended_log_length
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|RTAS_ERROR_LOG_MAX
)paren
id|len
op_assign
id|RTAS_ERROR_LOG_MAX
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * First write to nvram, if fatal error, that is the only&n; * place we log the info.  The error will be picked up&n; * on the next reboot by rtasd.  If not fatal, run the&n; * method for the type of error.  Currently, only RTAS&n; * errors have methods implemented, but in the future&n; * there might be a need to store data in nvram before a&n; * call to panic().&n; *&n; * XXX We write to nvram periodically, to indicate error has&n; * been written and sync&squot;d, but there is a possibility&n; * that if we don&squot;t shutdown correctly, a duplicate error&n; * record will be created on next reboot.&n; */
DECL|function|pSeries_log_error
r_void
id|pSeries_log_error
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|err_type
comma
r_int
id|fatal
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;logging event&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
multiline_comment|/* get length and increase count */
r_switch
c_cond
(paren
id|err_type
op_amp
id|ERR_TYPE_MASK
)paren
(brace
r_case
id|ERR_TYPE_RTAS_LOG
suffix:colon
id|len
op_assign
id|log_rtas_len
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|err_type
op_amp
id|ERR_FLAG_BOOT
)paren
)paren
id|error_log_cnt
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ERR_TYPE_KERNEL_PANIC
suffix:colon
r_default
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Write error to NVRAM */
r_if
c_cond
(paren
op_logical_neg
id|no_more_logging
op_logical_and
op_logical_neg
(paren
id|err_type
op_amp
id|ERR_FLAG_BOOT
)paren
)paren
id|nvram_write_error_log
c_func
(paren
id|buf
comma
id|len
comma
id|err_type
)paren
suffix:semicolon
multiline_comment|/* Check to see if we need to or have stopped logging */
r_if
c_cond
(paren
id|fatal
op_logical_or
id|no_more_logging
)paren
(brace
id|no_more_logging
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* call type specific method for error */
r_switch
c_cond
(paren
id|err_type
op_amp
id|ERR_TYPE_MASK
)paren
(brace
r_case
id|ERR_TYPE_RTAS_LOG
suffix:colon
multiline_comment|/* put into syslog and error_log file */
id|printk_log_rtas
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
id|offset
op_assign
id|rtas_error_log_buffer_max
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
multiline_comment|/* First copy over sequence number */
id|memcpy
c_func
(paren
op_amp
id|rtas_log_buf
(braket
id|offset
)braket
comma
(paren
r_void
op_star
)paren
op_amp
id|error_log_cnt
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* Second copy over error log data */
id|offset
op_add_assign
r_sizeof
(paren
r_int
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
id|len
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|rtas_log_wait
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ERR_TYPE_KERNEL_PANIC
suffix:colon
r_default
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
multiline_comment|/* This will check if all events are logged, if they are then, we&n; * know that we can safely clear the events in NVRAM.&n; * Next we&squot;ll sit and wait for something else to log.&n; */
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
id|s
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
id|rtas_error_log_buffer_max
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|count
op_assign
id|rtas_error_log_buffer_max
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
id|EFAULT
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|count
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
multiline_comment|/* if it&squot;s 0, then we know we got the last one (the one in NVRAM) */
r_if
c_cond
(paren
id|rtas_log_size
op_eq
l_int|0
op_logical_and
op_logical_neg
id|no_more_logging
)paren
id|nvram_clear_error_log
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|log_lock
comma
id|s
)paren
suffix:semicolon
id|offset
op_assign
id|rtas_error_log_buffer_max
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|log_lock
comma
id|s
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
dot
id|read
op_assign
id|rtas_log_read
comma
dot
id|poll
op_assign
id|rtas_log_poll
comma
dot
id|open
op_assign
id|rtas_log_open
comma
dot
id|release
op_assign
id|rtas_log_release
comma
)brace
suffix:semicolon
DECL|function|enable_surveillance
r_static
r_int
id|enable_surveillance
c_func
(paren
r_int
id|timeout
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
id|timeout
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
id|of_find_node_by_path
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
id|of_node_put
c_func
(paren
id|node
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
id|of_node_put
c_func
(paren
id|node
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
id|of_node_put
c_func
(paren
id|node
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_event_scan
r_static
r_void
id|do_event_scan
c_func
(paren
r_int
id|event_scan
)paren
(brace
r_int
id|error
suffix:semicolon
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
id|RTAS_EVENT_SCAN_ALL_EVENTS
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
id|pSeries_log_error
c_func
(paren
id|logdata
comma
id|ERR_TYPE_RTAS_LOG
comma
l_int|0
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
)brace
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
r_int
id|err_type
suffix:semicolon
r_int
id|cpu
op_assign
l_int|0
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
id|cpumask_t
id|all
op_assign
id|CPU_MASK_ALL
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;rtasd&quot;
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
multiline_comment|/* We can use rtas_log_buf now */
id|no_more_logging
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;RTAS daemon started&bslash;n&quot;
)paren
suffix:semicolon
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
multiline_comment|/* See if we have any error stored in NVRAM */
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
id|rc
op_assign
id|nvram_read_error_log
c_func
(paren
id|logdata
comma
id|rtas_error_log_max
comma
op_amp
id|err_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
r_if
c_cond
(paren
id|err_type
op_ne
id|ERR_FLAG_ALREADY_LOGGED
)paren
(brace
id|pSeries_log_error
c_func
(paren
id|logdata
comma
id|err_type
op_or
id|ERR_FLAG_BOOT
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* First pass. */
id|lock_cpu_hotplug
c_func
(paren
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
(brace
id|DEBUG
c_func
(paren
l_string|&quot;scheduling on %d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
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
id|do_event_scan
c_func
(paren
id|event_scan
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
id|unlock_cpu_hotplug
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|surveillance_timeout
op_ne
op_minus
l_int|1
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
id|surveillance_timeout
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
id|lock_cpu_hotplug
c_func
(paren
)paren
suffix:semicolon
id|cpu
op_assign
id|first_cpu_const
c_func
(paren
id|mk_cpumask_const
c_func
(paren
id|cpu_online_map
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|do_event_scan
c_func
(paren
id|event_scan
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|all
)paren
suffix:semicolon
multiline_comment|/* Drop hotplug lock, and sleep for a bit (at least&n;&t;&t; * one second since some machines have problems if we&n;&t;&t; * call event-scan too quickly). */
id|unlock_cpu_hotplug
c_func
(paren
)paren
suffix:semicolon
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
id|lock_cpu_hotplug
c_func
(paren
)paren
suffix:semicolon
id|cpu
op_assign
id|next_cpu_const
c_func
(paren
id|cpu
comma
id|mk_cpumask_const
c_func
(paren
id|cpu_online_map
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|NR_CPUS
)paren
id|cpu
op_assign
id|first_cpu_const
c_func
(paren
id|mk_cpumask_const
c_func
(paren
id|cpu_online_map
)paren
)paren
suffix:semicolon
)brace
id|error_vfree
suffix:colon
r_if
c_cond
(paren
id|rtas_log_buf
)paren
id|vfree
c_func
(paren
id|rtas_log_buf
)paren
suffix:semicolon
id|rtas_log_buf
op_assign
l_int|NULL
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
id|entry
suffix:semicolon
multiline_comment|/* No RTAS, only warn if we are on a pSeries box  */
r_if
c_cond
(paren
id|rtas_token
c_func
(paren
l_string|&quot;event-scan&quot;
)paren
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_amp
id|PLATFORM_PSERIES
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtasd: no RTAS on system&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/error_log&quot;
comma
id|S_IRUSR
comma
l_int|NULL
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
l_string|&quot;Failed to create error_log proc entry&bslash;n&quot;
)paren
suffix:semicolon
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
multiline_comment|/* Make room for the sequence number */
id|rtas_error_log_buffer_max
op_assign
id|rtas_error_log_max
op_plus
r_sizeof
(paren
r_int
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
op_ge
l_int|0
op_logical_and
id|i
op_le
l_int|255
)paren
id|surveillance_timeout
op_assign
id|i
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
