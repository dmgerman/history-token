multiline_comment|/*&n; *  c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * scan-log-data driver for PPC64  Todd Inglett &lt;tinglett@vnet.ibm.com&gt;&n; *&n; * When ppc64 hardware fails the service processor dumps internal state&n; * of the system.  After a reboot the operating system can access a dump&n; * of this data using this driver.  A dump exists if the device-tree&n; * /chosen/ibm,scan-log-data property exists.&n; *&n; * This driver exports /proc/ppc64/scan-log-dump which can be read.&n; * The driver supports only sequential reads.&n; *&n; * The driver looks at a write to the driver for the single word &quot;reset&quot;.&n; * If given, the driver will reset the scanlog so the platform can free it.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
DECL|macro|MODULE_VERS
mdefine_line|#define MODULE_VERS &quot;1.0&quot;
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME &quot;scanlog&quot;
multiline_comment|/* Status returns from ibm,scan-log-dump */
DECL|macro|SCANLOG_COMPLETE
mdefine_line|#define SCANLOG_COMPLETE 0
DECL|macro|SCANLOG_HWERROR
mdefine_line|#define SCANLOG_HWERROR -1
DECL|macro|SCANLOG_CONTINUE
mdefine_line|#define SCANLOG_CONTINUE 1
DECL|macro|DEBUG
mdefine_line|#define DEBUG(A...) do { if (scanlog_debug) printk(KERN_ERR &quot;scanlog: &quot; A); } while (0)
DECL|variable|scanlog_debug
r_static
r_int
id|scanlog_debug
suffix:semicolon
DECL|variable|ibm_scan_log_dump
r_static
r_int
r_int
id|ibm_scan_log_dump
suffix:semicolon
multiline_comment|/* RTAS token */
DECL|variable|proc_ppc64_scan_log_dump
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_ppc64_scan_log_dump
suffix:semicolon
multiline_comment|/* The proc file */
DECL|function|scanlog_read
r_static
id|ssize_t
id|scanlog_read
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
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
r_int
r_int
op_star
id|data
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_int
r_int
id|len
comma
id|off
suffix:semicolon
r_int
r_int
id|wait_time
suffix:semicolon
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|data
op_assign
(paren
r_int
r_int
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: read failed no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|RTAS_DATA_BUF_SIZE
)paren
id|count
op_assign
id|RTAS_DATA_BUF_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|1024
)paren
(brace
multiline_comment|/* This is the min supported by this RTAS call.  Rather&n;&t;&t; * than do all the buffering we insist the user code handle&n;&t;&t; * larger reads.  As long as cp works... :)&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: cannot perform a small read (%ld)&bslash;n&quot;
comma
id|count
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
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|wait_time
op_assign
id|HZ
op_div
l_int|2
suffix:semicolon
multiline_comment|/* default wait if no data */
id|spin_lock
c_func
(paren
op_amp
id|rtas_data_buf_lock
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|rtas_data_buf
comma
id|data
comma
id|RTAS_DATA_BUF_SIZE
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ibm_scan_log_dump
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
id|__pa
c_func
(paren
id|rtas_data_buf
)paren
comma
id|count
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|data
comma
id|rtas_data_buf
comma
id|RTAS_DATA_BUF_SIZE
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtas_data_buf_lock
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;status=%ld, data[0]=%x, data[1]=%x, data[2]=%x&bslash;n&quot;
comma
id|status
comma
id|data
(braket
l_int|0
)braket
comma
id|data
(braket
l_int|1
)braket
comma
id|data
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|SCANLOG_COMPLETE
suffix:colon
id|DEBUG
c_func
(paren
l_string|&quot;hit eof&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SCANLOG_HWERROR
suffix:colon
id|DEBUG
c_func
(paren
l_string|&quot;hardware error reading scan log data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
r_case
id|SCANLOG_CONTINUE
suffix:colon
multiline_comment|/* We may or may not have data yet */
id|len
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
id|off
op_assign
id|data
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
(paren
r_char
op_star
)paren
id|data
)paren
op_plus
id|off
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* Break to sleep default time */
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|status
OG
l_int|9900
op_logical_and
id|status
op_le
l_int|9905
)paren
(brace
multiline_comment|/* No data.  RTAS is hinting at a delay required&n;&t;&t;&t;&t; * between 1-100000 milliseconds&n;&t;&t;&t;&t; */
r_int
id|ms
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|status
OG
l_int|9900
suffix:semicolon
id|status
op_decrement
)paren
id|ms
op_assign
id|ms
op_star
l_int|10
suffix:semicolon
multiline_comment|/* Use microseconds for reasonable accuracy */
id|ms
op_mul_assign
l_int|1000
suffix:semicolon
id|wait_time
op_assign
id|ms
op_div
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
multiline_comment|/* round down is fine */
multiline_comment|/* Fall through to sleep */
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: unknown error from rtas: %ld&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
multiline_comment|/* Apparently no data yet.  Wait and try again. */
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|wait_time
)paren
suffix:semicolon
)brace
multiline_comment|/*NOTREACHED*/
)brace
DECL|function|scanlog_write
r_static
id|ssize_t
id|scanlog_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
r_char
id|stkbuf
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|19
)paren
id|count
op_assign
l_int|19
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
id|stkbuf
comma
id|buf
comma
id|count
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|stkbuf
(braket
id|count
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|stkbuf
comma
l_string|&quot;reset&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
id|DEBUG
c_func
(paren
l_string|&quot;reset scanlog&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ibm_scan_log_dump
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_string|&quot;rtas returns %ld&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|stkbuf
comma
l_string|&quot;debugon&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: debug on&bslash;n&quot;
)paren
suffix:semicolon
id|scanlog_debug
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|stkbuf
comma
l_string|&quot;debugoff&quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: debug off&bslash;n&quot;
)paren
suffix:semicolon
id|scanlog_debug
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|scanlog_open
r_static
r_int
id|scanlog_open
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
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
op_star
id|data
op_assign
(paren
r_int
r_int
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: open failed no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
(braket
l_int|0
)braket
op_ne
l_int|0
)paren
(brace
multiline_comment|/* This imperfect test stops a second copy of the&n;&t;&t; * data (or a reset while data is being copied)&n;&t;&t; */
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|data
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* re-init so we restart the scan */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scanlog_release
r_static
r_int
id|scanlog_release
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
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
op_star
id|data
op_assign
(paren
r_int
r_int
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scanlog: release failed no data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|data
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|scanlog_fops
r_struct
id|file_operations
id|scanlog_fops
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
id|scanlog_read
comma
dot
id|write
op_assign
id|scanlog_write
comma
dot
id|open
op_assign
id|scanlog_open
comma
dot
id|release
op_assign
id|scanlog_release
comma
)brace
suffix:semicolon
DECL|function|scanlog_init
r_int
id|__init
id|scanlog_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ibm_scan_log_dump
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,scan-log-dump&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ibm_scan_log_dump
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;scan-log-dump not implemented on this system&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc64/rtas/scan-log-dump&quot;
comma
id|S_IRUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;proc_fops
op_assign
op_amp
id|scanlog_fops
suffix:semicolon
multiline_comment|/* Ideally we could allocate a buffer &lt; 4G */
id|ent-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|RTAS_DATA_BUF_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent-&gt;data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to allocate a buffer&bslash;n&quot;
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;scan-log-dump&quot;
comma
id|ent-&gt;parent
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
(paren
(paren
r_int
r_int
op_star
)paren
id|ent-&gt;data
)paren
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to create ppc64/scan-log-dump proc entry&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|proc_ppc64_scan_log_dump
op_assign
id|ent
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scanlog_cleanup
r_void
id|__exit
id|scanlog_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|proc_ppc64_scan_log_dump
)paren
(brace
r_if
c_cond
(paren
id|proc_ppc64_scan_log_dump-&gt;data
)paren
id|kfree
c_func
(paren
id|proc_ppc64_scan_log_dump-&gt;data
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;scan-log-dump&quot;
comma
id|proc_ppc64_scan_log_dump-&gt;parent
)paren
suffix:semicolon
)brace
)brace
DECL|variable|scanlog_init
id|module_init
c_func
(paren
id|scanlog_init
)paren
suffix:semicolon
DECL|variable|scanlog_cleanup
id|module_exit
c_func
(paren
id|scanlog_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
