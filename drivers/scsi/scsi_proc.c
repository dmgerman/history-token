multiline_comment|/*&n; * linux/drivers/scsi/scsi_proc.c&n; *&n; * The functions in this file provide an interface between&n; * the PROC file system and the SCSI device drivers&n; * It is mainly used for debugging, statistics and to pass &n; * information directly to the lowlevel driver.&n; *&n; * (c) 1995 Michael Neuffer neuffer@goofy.zdv.uni-mainz.de &n; * Version: 0.99.8   last change: 95/09/13&n; * &n; * generic command parser provided by: &n; * Andreas Heilwagen &lt;crashcar@informatik.uni-koblenz.de&gt;&n; *&n; * generic_proc_info() support of xxxx_info() by:&n; * Michael A. Griffith &lt;grif@acm.org&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
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
multiline_comment|/* Used if the driver currently has no own support for /proc/scsi */
DECL|function|generic_proc_info
r_static
r_int
id|generic_proc_info
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
id|count
comma
r_const
r_char
op_star
(paren
op_star
id|info
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
comma
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_int
id|len
comma
id|pos
comma
id|begin
op_assign
l_int|0
suffix:semicolon
r_static
r_const
r_char
id|noprocfs
(braket
)braket
op_assign
l_string|&quot;The driver does not yet support the proc-fs&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|info
op_logical_and
id|shost
)paren
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|info
c_func
(paren
id|shost
)paren
)paren
suffix:semicolon
r_else
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|noprocfs
)paren
suffix:semicolon
id|pos
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
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
r_return
id|len
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|shost-&gt;hostt-&gt;proc_info
op_eq
l_int|NULL
)paren
id|n
op_assign
id|generic_proc_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
comma
id|shost-&gt;hostt-&gt;info
comma
id|shost
)paren
suffix:semicolon
r_else
id|n
op_assign
(paren
id|shost-&gt;hostt
op_member_access_from_pointer
id|proc_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
comma
id|shost-&gt;host_no
comma
l_int|0
)paren
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
DECL|function|proc_scsi_write
r_static
r_int
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
op_logical_neg
id|shost-&gt;hostt-&gt;proc_info
)paren
r_return
op_minus
id|ENOSYS
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
id|page
comma
op_amp
id|start
comma
l_int|0
comma
id|count
comma
id|shost-&gt;host_no
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
id|Scsi_Host_Template
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
id|shost-&gt;hostt-&gt;proc_dir
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
id|shost-&gt;hostt-&gt;proc_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p-&gt;write_proc
op_assign
id|proc_scsi_write
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
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
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
id|shost-&gt;hostt-&gt;proc_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;hostt-&gt;present
)paren
id|remove_proc_entry
c_func
(paren
id|shost-&gt;hostt-&gt;proc_name
comma
id|proc_scsi
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX: this shouldn&squot;t really be exposed to drivers. */
DECL|function|proc_print_scsidevice
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
id|sdev
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|size
comma
r_int
id|len
)paren
(brace
r_int
id|x
comma
id|y
op_assign
op_star
id|size
suffix:semicolon
r_extern
r_const
r_char
op_star
r_const
id|scsi_device_types
(braket
id|MAX_SCSI_DEVICE_CODE
)braket
suffix:semicolon
id|y
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
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
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|8
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;vendor
(braket
id|x
)braket
op_ge
l_int|0x20
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;%c&quot;
comma
id|sdev-&gt;vendor
(braket
id|x
)braket
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; Model: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|16
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;model
(braket
id|x
)braket
op_ge
l_int|0x20
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;%c&quot;
comma
id|sdev-&gt;model
(braket
id|x
)braket
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; Rev: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|4
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;rev
(braket
id|x
)braket
op_ge
l_int|0x20
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;%c&quot;
comma
id|sdev-&gt;rev
(braket
id|x
)braket
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
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
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
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
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; CCS&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|size
op_assign
id|y
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|proc_print_scsidevice
id|EXPORT_SYMBOL
c_func
(paren
id|proc_print_scsidevice
)paren
suffix:semicolon
multiline_comment|/* &n; * proc_scsi_dev_info_read: dump the scsi_dev_info_list via&n; * /proc/scsi/device_info&n; */
DECL|function|proc_scsi_dev_info_read
r_static
r_int
id|proc_scsi_dev_info_read
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
)paren
(brace
r_struct
id|scsi_dev_info_list
op_star
id|devinfo
suffix:semicolon
r_int
id|size
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|devinfo
comma
op_amp
id|scsi_dev_info_list
comma
id|dev_info_list
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&squot;%.8s&squot; &squot;%.16s&squot; 0x%x&bslash;n&quot;
comma
id|devinfo-&gt;vendor
comma
id|devinfo-&gt;model
comma
id|devinfo-&gt;flags
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
r_goto
id|stop_output
suffix:semicolon
)brace
id|stop_output
suffix:colon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start slop */
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
multiline_comment|/* Ending slop */
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * proc_scsi_dev_info_write: allow additions to the scsi_dev_info_list via&n; * /proc.&n; *&n; * Use: echo &quot;vendor:model:flag&quot; &gt; /proc/scsi/device_info&n; *&n; * To add a black/white list entry for vendor and model with an integer&n; * value of flag to the scsi device info list.&n; */
DECL|function|proc_scsi_dev_info_write
r_static
r_int
id|proc_scsi_dev_info_write
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
id|length
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|err
op_assign
id|length
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
r_if
c_cond
(paren
op_logical_neg
(paren
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
)paren
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
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|scsi_dev_info_list_add_str
c_func
(paren
id|buffer
)paren
suffix:semicolon
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
DECL|function|scsi_proc_info
r_static
r_int
id|scsi_proc_info
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
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
id|Scsi_Device
op_star
id|sdev
suffix:semicolon
r_int
id|size
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * First, see if there are any attached devices or not.&n;&t; */
r_for
c_loop
(paren
id|shost
op_assign
id|scsi_host_get_next
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|shost
suffix:semicolon
id|shost
op_assign
id|scsi_host_get_next
c_func
(paren
id|shost
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|shost-&gt;my_devices
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Attached devices: %s&bslash;n&quot;
comma
(paren
id|shost
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;none&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_for
c_loop
(paren
id|shost
op_assign
id|scsi_host_get_next
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|shost
suffix:semicolon
id|shost
op_assign
id|scsi_host_get_next
c_func
(paren
id|shost
)paren
)paren
(brace
id|list_for_each_entry
c_func
(paren
id|sdev
comma
op_amp
id|shost-&gt;my_devices
comma
id|siblings
)paren
(brace
id|proc_print_scsidevice
c_func
(paren
id|sdev
comma
id|buffer
comma
op_amp
id|size
comma
id|len
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
r_goto
id|stop_output
suffix:semicolon
)brace
)brace
id|stop_output
suffix:colon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start slop */
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
multiline_comment|/* Ending slop */
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SCSI_LOGGING
multiline_comment|/*&n; * Function:    scsi_dump_status&n; *&n; * Purpose:     Brain dump of scsi system, used for problem solving.&n; *&n; * Arguments:   level - used to indicate level of detail.&n; *&n; * Notes:       The level isn&squot;t used at all yet, but we need to find some&n; *&t;&t;way of sensibly logging varying degrees of information.&n; *&t;&t;A quick one-line display of each command, plus the status&n; *&t;&t;would be most useful.&n; *&n; *              This does depend upon CONFIG_SCSI_LOGGING - I do want some&n; *&t;&t;way of turning it all off if the user wants a lean and mean&n; *&t;&t;kernel.  It would probably also be useful to allow the user&n; *&t;&t;to specify one single host to be dumped.  A second argument&n; *&t;&t;to the function would be useful for that purpose.&n; *&n; *              FIXME - some formatting of the output into tables would be&n; *&t;&t;        very handy.&n; */
DECL|function|scsi_dump_status
r_static
r_void
id|scsi_dump_status
c_func
(paren
r_int
id|level
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|Scsi_Device
op_star
id|SDpnt
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Dump of scsi host parameters:&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|shpnt
op_assign
id|scsi_host_get_next
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|shpnt
suffix:semicolon
id|shpnt
op_assign
id|scsi_host_get_next
c_func
(paren
id|shpnt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; %d %d %d : %d %d&bslash;n&quot;
comma
id|shpnt-&gt;host_failed
comma
id|shpnt-&gt;host_busy
comma
id|atomic_read
c_func
(paren
op_amp
id|shpnt-&gt;host_active
)paren
comma
id|shpnt-&gt;host_blocked
comma
id|shpnt-&gt;host_self_blocked
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Dump of scsi command parameters:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|shpnt
op_assign
id|scsi_host_get_next
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|shpnt
suffix:semicolon
id|shpnt
op_assign
id|scsi_host_get_next
c_func
(paren
id|shpnt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;h:c:t:l (dev sect nsect cnumsec sg) &quot;
l_string|&quot;(ret all flg) (to/cmd to ito) cmd snse result&bslash;n&quot;
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|SDpnt
comma
op_amp
id|shpnt-&gt;my_devices
comma
id|siblings
)paren
(brace
r_for
c_loop
(paren
id|SCpnt
op_assign
id|SDpnt-&gt;device_queue
suffix:semicolon
id|SCpnt
suffix:semicolon
id|SCpnt
op_assign
id|SCpnt-&gt;next
)paren
(brace
multiline_comment|/*  (0) h:c:t:l (dev sect nsect cnumsec sg) (ret all flg) (to/cmd to ito) cmd snse result %d %x      */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(%3d) %2d:%1d:%2d:%2d (%6s %4llu %4ld %4ld %4x %1d) (%1d %1d 0x%2x) (%4d %4d %4d) 0x%2.2x 0x%2.2x 0x%8.8x&bslash;n&quot;
comma
id|i
op_increment
comma
id|SCpnt-&gt;host-&gt;host_no
comma
id|SCpnt-&gt;device-&gt;channel
comma
id|SCpnt-&gt;device-&gt;id
comma
id|SCpnt-&gt;device-&gt;lun
comma
id|SCpnt-&gt;request-&gt;rq_disk
ques
c_cond
id|SCpnt-&gt;request-&gt;rq_disk-&gt;disk_name
suffix:colon
l_string|&quot;?&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|SCpnt-&gt;request-&gt;sector
comma
id|SCpnt-&gt;request-&gt;nr_sectors
comma
(paren
r_int
)paren
id|SCpnt-&gt;request-&gt;current_nr_sectors
comma
id|SCpnt-&gt;request-&gt;rq_status
comma
id|SCpnt-&gt;use_sg
comma
id|SCpnt-&gt;retries
comma
id|SCpnt-&gt;allowed
comma
id|SCpnt-&gt;flags
comma
id|SCpnt-&gt;timeout_per_command
comma
id|SCpnt-&gt;timeout
comma
id|SCpnt-&gt;internal_timeout
comma
id|SCpnt-&gt;cmnd
(braket
l_int|0
)braket
comma
id|SCpnt-&gt;sense_buffer
(braket
l_int|2
)braket
comma
id|SCpnt-&gt;result
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#endif&t;/* CONFIG_SCSI_LOGGING */ 
DECL|function|proc_scsi_gen_write
r_static
r_int
id|proc_scsi_gen_write
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
id|length
comma
r_void
op_star
id|data
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
multiline_comment|/*&n;&t; * Usage: echo &quot;scsi dump #N&quot; &gt; /proc/scsi/scsi&n;&t; * to dump status of all scsi commands.  The number is used to&n;&t; * specify the level of detail in the dump.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;dump&quot;
comma
id|buffer
op_plus
l_int|5
comma
l_int|4
)paren
)paren
(brace
r_int
r_int
id|level
suffix:semicolon
id|p
op_assign
id|buffer
op_plus
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_goto
id|out
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
id|scsi_dump_status
c_func
(paren
id|level
)paren
suffix:semicolon
)brace
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
id|create_proc_info_entry
c_func
(paren
l_string|&quot;scsi/scsi&quot;
comma
l_int|0
comma
l_int|0
comma
id|scsi_proc_info
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
id|pde-&gt;write_proc
op_assign
id|proc_scsi_gen_write
suffix:semicolon
id|pde
op_assign
id|create_proc_info_entry
c_func
(paren
l_string|&quot;scsi/device_info&quot;
comma
l_int|0
comma
l_int|0
comma
id|proc_scsi_dev_info_read
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pde
)paren
r_goto
id|err3
suffix:semicolon
id|pde-&gt;write_proc
op_assign
id|proc_scsi_dev_info_write
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err3
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;scsi/scsi&quot;
comma
l_int|0
)paren
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
id|__exit
id|scsi_exit_procfs
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;scsi/device_info&quot;
comma
l_int|0
)paren
suffix:semicolon
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
