multiline_comment|/*&n; * linux/drivers/scsi/scsi_proc.c&n; *&n; * The functions in this file provide an interface between&n; * the PROC file system and the SCSI device drivers&n; * It is mainly used for debugging, statistics and to pass &n; * information directly to the lowlevel driver.&n; *&n; * (c) 1995 Michael Neuffer neuffer@goofy.zdv.uni-mainz.de &n; * Version: 0.99.8   last change: 95/09/13&n; * &n; * generic command parser provided by: &n; * Andreas Heilwagen &lt;crashcar@informatik.uni-koblenz.de&gt;&n; *&n; * generic_proc_info() support of xxxx_info() by:&n; * Michael A. Griffith &lt;grif@acm.org&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;scsi_priv.h&quot;
macro_line|#include &quot;scsi_logging.h&quot;
multiline_comment|/* 4K page size, but our output routines, use some slack for overruns */
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE (3*1024)
multiline_comment|/* XXX: this shouldn&squot;t really be exposed to drivers. */
DECL|variable|proc_scsi
r_struct
id|proc_dir_entry
op_star
id|proc_scsi
suffix:semicolon
DECL|variable|proc_scsi
id|EXPORT_SYMBOL
c_func
(paren
id|proc_scsi
)paren
suffix:semicolon
DECL|function|proc_scsi_read
r_static
r_int
id|proc_scsi_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
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
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|data
suffix:semicolon
r_int
id|n
suffix:semicolon
id|n
op_assign
id|shost-&gt;hostt
op_member_access_from_pointer
id|proc_info
c_func
(paren
id|shost
comma
id|buffer
comma
id|start
comma
id|offset
comma
id|length
comma
l_int|0
)paren
suffix:semicolon
op_star
id|eof
op_assign
(paren
id|n
OL
id|length
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|proc_scsi_write_proc
r_static
r_int
id|proc_scsi_write_proc
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
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|data
suffix:semicolon
id|ssize_t
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_char
op_star
id|start
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PROC_BLOCK_SIZE
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|page
comma
id|buf
comma
id|count
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|shost-&gt;hostt
op_member_access_from_pointer
id|proc_info
c_func
(paren
id|shost
comma
id|page
comma
op_amp
id|start
comma
l_int|0
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|scsi_proc_host_add
r_void
id|scsi_proc_host_add
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_struct
id|scsi_host_template
op_star
id|sht
op_assign
id|shost-&gt;hostt
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;proc_info
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;proc_dir
)paren
(brace
id|sht-&gt;proc_dir
op_assign
id|proc_mkdir
c_func
(paren
id|sht-&gt;proc_name
comma
id|proc_scsi
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;proc_dir
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: proc_mkdir failed for %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|sht-&gt;proc_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sht-&gt;proc_dir-&gt;owner
op_assign
id|sht-&gt;module
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
id|p
op_assign
id|create_proc_read_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|sht-&gt;proc_dir
comma
id|proc_scsi_read
comma
id|shost
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Failed to register host %d in&quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|shost-&gt;host_no
comma
id|sht-&gt;proc_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p-&gt;write_proc
op_assign
id|proc_scsi_write_proc
suffix:semicolon
id|p-&gt;owner
op_assign
id|shost-&gt;hostt-&gt;module
suffix:semicolon
)brace
DECL|function|scsi_proc_host_rm
r_void
id|scsi_proc_host_rm
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_struct
id|scsi_host_template
op_star
id|sht
op_assign
id|shost-&gt;hostt
suffix:semicolon
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sht-&gt;proc_info
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|name
comma
id|sht-&gt;proc_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sht-&gt;present
)paren
id|remove_proc_entry
c_func
(paren
id|sht-&gt;proc_name
comma
id|proc_scsi
)paren
suffix:semicolon
)brace
)brace
DECL|function|proc_print_scsidevice
r_static
r_int
id|proc_print_scsidevice
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|seq_file
op_star
id|s
op_assign
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;Host: scsi%d Channel: %02d Id: %02d Lun: %02d&bslash;n  Vendor: &quot;
comma
id|sdev-&gt;host-&gt;host_no
comma
id|sdev-&gt;channel
comma
id|sdev-&gt;id
comma
id|sdev-&gt;lun
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;vendor
(braket
id|i
)braket
op_ge
l_int|0x20
)paren
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;%c&quot;
comma
id|sdev-&gt;vendor
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; Model: &quot;
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;model
(braket
id|i
)braket
op_ge
l_int|0x20
)paren
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;%c&quot;
comma
id|sdev-&gt;model
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; Rev: &quot;
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;rev
(braket
id|i
)braket
op_ge
l_int|0x20
)paren
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;%c&quot;
comma
id|sdev-&gt;rev
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;  Type:   %s &quot;
comma
id|sdev-&gt;type
OL
id|MAX_SCSI_DEVICE_CODE
ques
c_cond
id|scsi_device_types
(braket
(paren
r_int
)paren
id|sdev-&gt;type
)braket
suffix:colon
l_string|&quot;Unknown          &quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;               ANSI&quot;
l_string|&quot; SCSI revision: %02x&quot;
comma
(paren
id|sdev-&gt;scsi_level
op_minus
l_int|1
)paren
ques
c_cond
id|sdev-&gt;scsi_level
op_minus
l_int|1
suffix:colon
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;scsi_level
op_eq
l_int|2
)paren
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot; CCS&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scsi_add_single_device
r_static
r_int
id|scsi_add_single_device
c_func
(paren
id|uint
id|host
comma
id|uint
id|channel
comma
id|uint
id|id
comma
id|uint
id|lun
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|shost
op_assign
id|scsi_host_lookup
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_find_device
c_func
(paren
id|shost
comma
id|channel
comma
id|id
comma
id|lun
)paren
)paren
(brace
id|sdev
op_assign
id|scsi_add_device
c_func
(paren
id|shost
comma
id|channel
comma
id|id
comma
id|lun
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sdev
)paren
)paren
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_else
id|error
op_assign
l_int|0
suffix:semicolon
)brace
id|scsi_host_put
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|scsi_remove_single_device
r_static
r_int
id|scsi_remove_single_device
c_func
(paren
id|uint
id|host
comma
id|uint
id|channel
comma
id|uint
id|id
comma
id|uint
id|lun
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|shost
op_assign
id|scsi_host_lookup
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sdev
op_assign
id|scsi_find_device
c_func
(paren
id|shost
comma
id|channel
comma
id|id
comma
id|lun
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sdev
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;access_count
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|scsi_remove_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|out
suffix:colon
id|scsi_host_put
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|proc_scsi_write
r_static
id|ssize_t
id|proc_scsi_write
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
id|length
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|host
comma
id|channel
comma
id|id
comma
id|lun
suffix:semicolon
r_char
op_star
id|buffer
comma
op_star
id|p
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|length
OG
id|PAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|buffer
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|length
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
id|PAGE_SIZE
)paren
id|buffer
(braket
id|length
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|buffer
(braket
id|PAGE_SIZE
op_minus
l_int|1
)braket
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
l_int|11
op_logical_or
id|strncmp
c_func
(paren
l_string|&quot;scsi&quot;
comma
id|buffer
comma
l_int|4
)paren
)paren
r_goto
id|out
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_LOGGING
multiline_comment|/*&n;&t; * Usage: echo &quot;scsi log token #N&quot; &gt; /proc/scsi/scsi&n;&t; * where token is one of [error,scan,mlqueue,mlcomplete,llqueue,&n;&t; * llcomplete,hlqueue,hlcomplete]&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;log&quot;
comma
id|buffer
op_plus
l_int|5
comma
l_int|3
)paren
)paren
(brace
r_char
op_star
id|token
suffix:semicolon
r_int
r_int
id|level
suffix:semicolon
id|p
op_assign
id|buffer
op_plus
l_int|9
suffix:semicolon
id|token
op_assign
id|p
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_ne
l_char|&squot; &squot;
op_logical_and
op_star
id|p
op_ne
l_char|&squot;&bslash;t&squot;
op_logical_and
op_star
id|p
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|p
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|token
comma
l_string|&quot;all&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Turn on absolutely everything.&n;&t;&t;&t;&t; */
id|scsi_logging_level
op_assign
op_complement
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|token
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Turn off absolutely everything.&n;&t;&t;&t;&t; */
id|scsi_logging_level
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|level
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Now figure out what to do with it.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;error&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_ERROR_RECOVERY_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;timeout&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_TIMEOUT_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;scan&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_SCAN_BUS_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;mlqueue&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_MLQUEUE_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;mlcomplete&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_MLCOMPLETE_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;llqueue&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_LLQUEUE_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;llcomplete&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_LLCOMPLETE_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;hlqueue&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_HLQUEUE_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;hlcomplete&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_HLCOMPLETE_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|token
comma
l_string|&quot;ioctl&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|SCSI_SET_IOCTL_LOGGING
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
r_else
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;scsi logging level set to 0x%8.8x&bslash;n&quot;
comma
id|scsi_logging_level
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_SCSI_LOGGING */
multiline_comment|/*&n;&t; * Usage: echo &quot;scsi add-single-device 0 1 2 3&quot; &gt;/proc/scsi/scsi&n;&t; * with  &quot;0 1 2 3&quot; replaced by your &quot;Host Channel Id Lun&quot;.&n;&t; * Consider this feature BETA.&n;&t; *     CAUTION: This is not for hotplugging your peripherals. As&n;&t; *     SCSI was not designed for this you could damage your&n;&t; *     hardware !&n;&t; * However perhaps it is legal to switch on an&n;&t; * already connected device. It is perhaps not&n;&t; * guaranteed this device doesn&squot;t corrupt an ongoing data transfer.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;add-single-device&quot;
comma
id|buffer
op_plus
l_int|5
comma
l_int|17
)paren
)paren
(brace
id|p
op_assign
id|buffer
op_plus
l_int|23
suffix:semicolon
id|host
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|channel
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|id
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|lun
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|scsi_add_single_device
c_func
(paren
id|host
comma
id|channel
comma
id|id
comma
id|lun
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
id|err
op_assign
id|length
suffix:semicolon
multiline_comment|/*&n;&t; * Usage: echo &quot;scsi remove-single-device 0 1 2 3&quot; &gt;/proc/scsi/scsi&n;&t; * with  &quot;0 1 2 3&quot; replaced by your &quot;Host Channel Id Lun&quot;.&n;&t; *&n;&t; * Consider this feature pre-BETA.&n;&t; *&n;&t; *     CAUTION: This is not for hotplugging your peripherals. As&n;&t; *     SCSI was not designed for this you could damage your&n;&t; *     hardware and thoroughly confuse the SCSI subsystem.&n;&t; *&n;&t; */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;remove-single-device&quot;
comma
id|buffer
op_plus
l_int|5
comma
l_int|20
)paren
)paren
(brace
id|p
op_assign
id|buffer
op_plus
l_int|26
suffix:semicolon
id|host
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|channel
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|id
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|lun
op_assign
id|simple_strtoul
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|scsi_remove_single_device
c_func
(paren
id|host
comma
id|channel
comma
id|id
comma
id|lun
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|proc_scsi_show
r_static
r_int
id|proc_scsi_show
c_func
(paren
r_struct
id|seq_file
op_star
id|s
comma
r_void
op_star
id|p
)paren
(brace
id|seq_printf
c_func
(paren
id|s
comma
l_string|&quot;Attached devices:&bslash;n&quot;
)paren
suffix:semicolon
id|bus_for_each_dev
c_func
(paren
op_amp
id|scsi_bus_type
comma
l_int|NULL
comma
id|s
comma
id|proc_print_scsidevice
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_scsi_open
r_static
r_int
id|proc_scsi_open
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
multiline_comment|/*&n;&t; * We don&squot;t really needs this for the write case but it doesn&squot;t&n;&t; * harm either.&n;&t; */
r_return
id|single_open
c_func
(paren
id|file
comma
id|proc_scsi_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|proc_scsi_operations
r_static
r_struct
id|file_operations
id|proc_scsi_operations
op_assign
(brace
dot
id|open
op_assign
id|proc_scsi_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|write
op_assign
id|proc_scsi_write
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
DECL|function|scsi_init_procfs
r_int
id|__init
id|scsi_init_procfs
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|pde
suffix:semicolon
id|proc_scsi
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;scsi&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_scsi
)paren
r_goto
id|err1
suffix:semicolon
id|pde
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;scsi/scsi&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pde
)paren
r_goto
id|err2
suffix:semicolon
id|pde-&gt;proc_fops
op_assign
op_amp
id|proc_scsi_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err2
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;scsi&quot;
comma
l_int|0
)paren
suffix:semicolon
id|err1
suffix:colon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|scsi_exit_procfs
r_void
id|scsi_exit_procfs
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;scsi/scsi&quot;
comma
l_int|0
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;scsi&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
