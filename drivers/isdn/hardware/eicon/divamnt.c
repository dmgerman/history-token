multiline_comment|/* $Id: divamnt.c,v 1.32.6.5 2004/08/28 20:03:53 armin Exp $&n; *&n; * Driver for Eicon DIVA Server ISDN cards.&n; * Maint module&n; *&n; * Copyright 2000-2003 by Armin Schindler (mac@melware.de)&n; * Copyright 2000-2003 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;divasync.h&quot;
macro_line|#include &quot;debug_if.h&quot;
DECL|variable|main_revision
r_static
r_char
op_star
id|main_revision
op_assign
l_string|&quot;$Revision: 1.32.6.5 $&quot;
suffix:semicolon
DECL|variable|major
r_static
r_int
id|major
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Maint driver for Eicon DIVA Server cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Cytronics &amp; Melware, Eicon Networks&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;DIVA card driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|buffer_length
r_int
id|buffer_length
op_assign
l_int|128
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|buffer_length
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|diva_dbg_mem
r_int
r_int
id|diva_dbg_mem
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|diva_dbg_mem
comma
l_string|&quot;l&quot;
)paren
suffix:semicolon
DECL|variable|DRIVERNAME
r_static
r_char
op_star
id|DRIVERNAME
op_assign
l_string|&quot;Eicon DIVA - MAINT module (http://www.melware.net)&quot;
suffix:semicolon
DECL|variable|DRIVERLNAME
r_static
r_char
op_star
id|DRIVERLNAME
op_assign
l_string|&quot;diva_mnt&quot;
suffix:semicolon
DECL|variable|DEVNAME
r_static
r_char
op_star
id|DEVNAME
op_assign
l_string|&quot;DivasMAINT&quot;
suffix:semicolon
DECL|variable|DRIVERRELEASE_MNT
r_char
op_star
id|DRIVERRELEASE_MNT
op_assign
l_string|&quot;2.0&quot;
suffix:semicolon
DECL|variable|msgwaitq
r_static
id|wait_queue_head_t
id|msgwaitq
suffix:semicolon
DECL|variable|opened
r_static
r_int
r_int
id|opened
suffix:semicolon
DECL|variable|start_time
r_static
r_struct
id|timeval
id|start_time
suffix:semicolon
r_extern
r_int
id|mntfunc_init
c_func
(paren
r_int
op_star
comma
r_void
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mntfunc_finit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|maint_read_write
c_func
(paren
r_void
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/*&n; *  helper functions&n; */
DECL|function|getrev
r_static
r_char
op_star
id|getrev
c_func
(paren
r_const
r_char
op_star
id|revision
)paren
(brace
r_char
op_star
id|rev
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
(brace
id|rev
op_assign
id|p
op_plus
l_int|2
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|rev
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|rev
op_assign
l_string|&quot;1.0&quot;
suffix:semicolon
r_return
id|rev
suffix:semicolon
)brace
multiline_comment|/*&n; * kernel/user space copy functions&n; */
DECL|function|diva_os_copy_to_user
r_int
id|diva_os_copy_to_user
c_func
(paren
r_void
op_star
id|os_handle
comma
r_void
id|__user
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
)paren
(brace
r_return
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|src
comma
id|length
)paren
)paren
suffix:semicolon
)brace
DECL|function|diva_os_copy_from_user
r_int
id|diva_os_copy_from_user
c_func
(paren
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_const
r_void
id|__user
op_star
id|src
comma
r_int
id|length
)paren
(brace
r_return
(paren
id|copy_from_user
c_func
(paren
id|dst
comma
id|src
comma
id|length
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * get time&n; */
DECL|function|diva_os_get_time
r_void
id|diva_os_get_time
c_func
(paren
id|dword
op_star
id|sec
comma
id|dword
op_star
id|usec
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tv.tv_sec
OG
id|start_time.tv_sec
)paren
(brace
r_if
c_cond
(paren
id|start_time.tv_usec
OG
id|tv.tv_usec
)paren
(brace
id|tv.tv_sec
op_decrement
suffix:semicolon
id|tv.tv_usec
op_add_assign
l_int|1000000
suffix:semicolon
)brace
op_star
id|sec
op_assign
(paren
id|dword
)paren
(paren
id|tv.tv_sec
op_minus
id|start_time.tv_sec
)paren
suffix:semicolon
op_star
id|usec
op_assign
(paren
id|dword
)paren
(paren
id|tv.tv_usec
op_minus
id|start_time.tv_usec
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tv.tv_sec
op_eq
id|start_time.tv_sec
)paren
(brace
op_star
id|sec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start_time.tv_usec
OL
id|tv.tv_usec
)paren
(brace
op_star
id|usec
op_assign
(paren
id|dword
)paren
(paren
id|tv.tv_usec
op_minus
id|start_time.tv_usec
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|usec
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|sec
op_assign
(paren
id|dword
)paren
id|tv.tv_sec
suffix:semicolon
op_star
id|usec
op_assign
(paren
id|dword
)paren
id|tv.tv_usec
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * device node operations&n; */
DECL|function|maint_poll
r_static
r_int
r_int
id|maint_poll
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
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|msgwaitq
comma
id|wait
)paren
suffix:semicolon
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;private_data
op_logical_or
id|diva_dbg_q_length
c_func
(paren
)paren
)paren
(brace
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
r_return
(paren
id|mask
)paren
suffix:semicolon
)brace
DECL|function|maint_open
r_static
r_int
id|maint_open
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
multiline_comment|/* only one open is allowed, so we test&n;&t;   it atomically */
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|opened
)paren
)paren
r_return
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
id|filep-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
id|nonseekable_open
c_func
(paren
id|ino
comma
id|filep
)paren
suffix:semicolon
)brace
DECL|function|maint_close
r_static
r_int
id|maint_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
r_if
c_cond
(paren
id|filep-&gt;private_data
)paren
(brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|filep-&gt;private_data
)paren
suffix:semicolon
id|filep-&gt;private_data
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* clear &squot;used&squot; flag */
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|opened
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|divas_maint_write
r_static
id|ssize_t
id|divas_maint_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
r_return
(paren
id|maint_read_write
c_func
(paren
(paren
r_char
id|__user
op_star
)paren
id|buf
comma
(paren
r_int
)paren
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|divas_maint_read
r_static
id|ssize_t
id|divas_maint_read
c_func
(paren
r_struct
id|file
op_star
id|file
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
r_return
(paren
id|maint_read_write
c_func
(paren
id|buf
comma
(paren
r_int
)paren
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|variable|divas_maint_fops
r_static
r_struct
id|file_operations
id|divas_maint_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|divas_maint_read
comma
dot
id|write
op_assign
id|divas_maint_write
comma
dot
id|poll
op_assign
id|maint_poll
comma
dot
id|open
op_assign
id|maint_open
comma
dot
id|release
op_assign
id|maint_close
)brace
suffix:semicolon
DECL|function|divas_maint_unregister_chrdev
r_static
r_void
id|divas_maint_unregister_chrdev
c_func
(paren
r_void
)paren
(brace
id|devfs_remove
c_func
(paren
id|DEVNAME
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|major
comma
id|DEVNAME
)paren
suffix:semicolon
)brace
DECL|function|divas_maint_register_chrdev
r_static
r_int
id|DIVA_INIT_FUNCTION
id|divas_maint_register_chrdev
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|major
op_assign
id|register_chrdev
c_func
(paren
l_int|0
comma
id|DEVNAME
comma
op_amp
id|divas_maint_fops
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to create /dev entry.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
l_int|0
)paren
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|DEVNAME
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * wake up reader&n; */
DECL|function|diva_maint_wakeup_read
r_void
id|diva_maint_wakeup_read
c_func
(paren
r_void
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|msgwaitq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Driver Load&n; */
DECL|function|maint_init
r_static
r_int
id|DIVA_INIT_FUNCTION
id|maint_init
c_func
(paren
r_void
)paren
(brace
r_char
id|tmprev
(braket
l_int|50
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|start_time
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|msgwaitq
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|DRIVERNAME
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Rel:%s  Rev:&quot;
comma
id|DRIVERLNAME
comma
id|DRIVERRELEASE_MNT
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tmprev
comma
id|main_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  Build: %s &bslash;n&quot;
comma
id|getrev
c_func
(paren
id|tmprev
)paren
comma
id|DIVA_BUILD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|divas_maint_register_chrdev
c_func
(paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mntfunc_init
c_func
(paren
op_amp
id|buffer_length
comma
op_amp
id|buffer
comma
id|diva_dbg_mem
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to connect to DIDD.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
id|divas_maint_unregister_chrdev
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: trace buffer = %p - %d kBytes, %s (Major: %d)&bslash;n&quot;
comma
id|DRIVERLNAME
comma
id|buffer
comma
(paren
id|buffer_length
op_div
l_int|1024
)paren
comma
(paren
id|diva_dbg_mem
op_eq
l_int|0
)paren
ques
c_cond
l_string|&quot;internal&quot;
suffix:colon
l_string|&quot;external&quot;
comma
id|major
)paren
suffix:semicolon
id|out
suffix:colon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;**  Driver Unload&n;*/
DECL|function|maint_exit
r_static
r_void
id|DIVA_EXIT_FUNCTION
id|maint_exit
c_func
(paren
r_void
)paren
(brace
id|divas_maint_unregister_chrdev
c_func
(paren
)paren
suffix:semicolon
id|mntfunc_finit
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: module unloaded.&bslash;n&quot;
comma
id|DRIVERLNAME
)paren
suffix:semicolon
)brace
DECL|variable|maint_init
id|module_init
c_func
(paren
id|maint_init
)paren
suffix:semicolon
DECL|variable|maint_exit
id|module_exit
c_func
(paren
id|maint_exit
)paren
suffix:semicolon
eof
