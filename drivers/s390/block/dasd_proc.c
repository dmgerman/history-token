multiline_comment|/*&n; * File...........: linux/drivers/s390/block/dasd_proc.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; *&t;&t;    Horst Hummel &lt;Horst.Hummel@de.ibm.com&gt;&n; *&t;&t;    Carsten Otte &lt;Cotte@de.ibm.com&gt;&n; *&t;&t;    Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999-2002&n; *&n; * /proc interface for the dasd driver.&n; *&n; * 05/04/02 split from dasd.c, code restructuring.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* This is ugly... */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_proc:&quot;
macro_line|#include &quot;dasd_int.h&quot;
r_typedef
r_struct
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|typedef|tempinfo_t
)brace
id|tempinfo_t
suffix:semicolon
DECL|variable|dasd_proc_root_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|dasd_proc_root_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|dasd_devices_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|dasd_devices_entry
suffix:semicolon
DECL|variable|dasd_statistics_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|dasd_statistics_entry
suffix:semicolon
r_static
id|ssize_t
DECL|function|dasd_generic_read
id|dasd_generic_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|user_buf
comma
r_int
id|user_len
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|loff_t
id|len
suffix:semicolon
id|tempinfo_t
op_star
id|p_info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
op_ge
id|p_info-&gt;len
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* EOF */
id|len
op_assign
id|p_info-&gt;len
op_minus
op_star
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|user_len
OL
id|len
)paren
id|len
op_assign
id|user_len
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|user_buf
comma
op_amp
(paren
id|p_info-&gt;data
(braket
op_star
id|offset
)braket
)paren
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
(paren
op_star
id|offset
)paren
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
multiline_comment|/* number of bytes &quot;read&quot; */
)brace
r_static
r_int
DECL|function|dasd_generic_close
id|dasd_generic_close
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
id|tempinfo_t
op_star
id|info
suffix:semicolon
id|info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;data
)paren
id|vfree
(paren
id|info-&gt;data
)paren
suffix:semicolon
id|kfree
(paren
id|info
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_char
op_star
DECL|function|dasd_get_user_string
id|dasd_get_user_string
c_func
(paren
r_const
r_char
op_star
id|user_buf
comma
r_int
id|user_len
)paren
(brace
r_char
op_star
id|buffer
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|user_len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|user_buf
comma
id|user_len
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
)brace
multiline_comment|/* got the string, now strip linefeed. */
r_if
c_cond
(paren
id|buffer
(braket
id|user_len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buffer
(braket
id|user_len
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_else
id|buffer
(braket
id|user_len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|dasd_devices_write
id|dasd_devices_write
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
id|user_buf
comma
r_int
id|user_len
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_char
op_star
id|buffer
comma
op_star
id|str
suffix:semicolon
r_int
id|add_or_set
suffix:semicolon
r_int
id|from
comma
id|to
comma
id|features
suffix:semicolon
id|buffer
op_assign
id|dasd_get_user_string
c_func
(paren
id|user_buf
comma
id|user_len
)paren
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;/proc/dasd/devices: &squot;%s&squot;&quot;
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Scan for &quot;add &quot; or &quot;set &quot;. */
r_for
c_loop
(paren
id|str
op_assign
id|buffer
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;add&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|str
(braket
l_int|3
)braket
)paren
)paren
id|add_or_set
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;set&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|str
(braket
l_int|3
)braket
)paren
)paren
id|add_or_set
op_assign
l_int|1
suffix:semicolon
r_else
r_goto
id|out_error
suffix:semicolon
r_for
c_loop
(paren
id|str
op_assign
id|str
op_plus
l_int|4
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
multiline_comment|/* Scan for &quot;device &quot; and &quot;range=&quot; and ignore it. This is sick. */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;device&quot;
comma
l_int|6
)paren
op_eq
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|str
(braket
l_int|6
)braket
)paren
)paren
r_for
c_loop
(paren
id|str
op_assign
id|str
op_plus
l_int|6
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;range=&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
r_for
c_loop
(paren
id|str
op_assign
id|str
op_plus
l_int|6
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
multiline_comment|/* Scan device number range and feature string. */
id|to
op_assign
id|from
op_assign
id|dasd_devno
c_func
(paren
id|str
comma
op_amp
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|str
op_increment
suffix:semicolon
id|to
op_assign
id|dasd_devno
c_func
(paren
id|str
comma
op_amp
id|str
)paren
suffix:semicolon
)brace
id|features
op_assign
id|dasd_feature_list
c_func
(paren
id|str
comma
op_amp
id|str
)paren
suffix:semicolon
multiline_comment|/* Negative numbers in from/to/features indicate errors */
r_if
c_cond
(paren
id|from
OL
l_int|0
op_logical_or
id|to
OL
l_int|0
op_logical_or
id|features
OL
l_int|0
)paren
r_goto
id|out_error
suffix:semicolon
r_if
c_cond
(paren
id|add_or_set
op_eq
l_int|0
)paren
(brace
id|dasd_add_range
c_func
(paren
id|from
comma
id|to
comma
id|features
)paren
suffix:semicolon
id|dasd_enable_devices
c_func
(paren
id|from
comma
id|to
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;on&quot;
)paren
op_eq
l_int|0
)paren
id|dasd_enable_devices
c_func
(paren
id|from
comma
id|to
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
op_eq
l_int|0
)paren
id|dasd_disable_devices
c_func
(paren
id|from
comma
id|to
)paren
suffix:semicolon
r_else
r_goto
id|out_error
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|user_len
suffix:semicolon
id|out_error
suffix:colon
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;/proc/dasd/devices: range parse error in &squot;%s&squot;&quot;
comma
id|buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dasd_devices_print
id|dasd_devices_print
c_func
(paren
id|dasd_devmap_t
op_star
id|devmap
comma
r_char
op_star
id|str
)paren
(brace
id|dasd_device_t
op_star
id|device
suffix:semicolon
r_struct
id|gendisk
op_star
id|gdp
suffix:semicolon
r_char
id|buffer
(braket
l_int|7
)braket
suffix:semicolon
r_char
op_star
id|substr
suffix:semicolon
r_int
id|minor
suffix:semicolon
r_int
id|len
suffix:semicolon
id|device
op_assign
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Print device number. */
id|len
op_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%04x&quot;
comma
id|devmap-&gt;devno
)paren
suffix:semicolon
multiline_comment|/* Print discipline string. */
r_if
c_cond
(paren
id|device
op_ne
l_int|NULL
op_logical_and
id|device-&gt;discipline
op_ne
l_int|NULL
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;(%s)&quot;
comma
id|device-&gt;discipline-&gt;name
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
multiline_comment|/* Print kdev. */
id|gdp
op_assign
id|dasd_gendisk_from_devindex
c_func
(paren
id|devmap-&gt;devindex
)paren
suffix:semicolon
id|minor
op_assign
id|devmap-&gt;devindex
op_mod
id|DASD_PER_MAJOR
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot; at (%3d:%3d)&quot;
comma
id|gdp-&gt;major
comma
id|minor
)paren
suffix:semicolon
multiline_comment|/* Print device name. */
r_if
c_cond
(paren
id|device
op_eq
l_int|NULL
)paren
(brace
id|dasd_device_name
c_func
(paren
id|buffer
comma
id|minor
comma
l_int|0
comma
id|gdp
)paren
suffix:semicolon
id|substr
op_assign
id|buffer
suffix:semicolon
)brace
r_else
id|substr
op_assign
id|device-&gt;name
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot; is %-7s&quot;
comma
id|substr
)paren
suffix:semicolon
multiline_comment|/* Print devices features. */
id|substr
op_assign
(paren
id|devmap-&gt;features
op_amp
id|DASD_FEATURE_READONLY
)paren
ques
c_cond
l_string|&quot;(ro)&quot;
suffix:colon
l_string|&quot; &quot;
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;%4s: &quot;
comma
id|substr
)paren
suffix:semicolon
multiline_comment|/* Print device status information. */
r_if
c_cond
(paren
id|device
op_eq
l_int|NULL
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|device-&gt;state
)paren
(brace
r_case
id|DASD_STATE_NEW
suffix:colon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;new&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DASD_STATE_KNOWN
suffix:colon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;detected&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DASD_STATE_BASIC
suffix:colon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;basic&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DASD_STATE_ACCEPT
suffix:colon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;accepted&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DASD_STATE_READY
suffix:colon
r_case
id|DASD_STATE_ONLINE
suffix:colon
r_if
c_cond
(paren
id|device-&gt;state
OL
id|DASD_STATE_ONLINE
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;fenced &quot;
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;active &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dasd_check_blocksize
c_func
(paren
id|device-&gt;bp_block
)paren
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;n/f&t; &quot;
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;at blocksize: %d, %ld blocks, %ld MB&quot;
comma
id|device-&gt;bp_block
comma
id|device-&gt;blocks
comma
(paren
(paren
id|device-&gt;bp_block
op_rshift
l_int|9
)paren
op_star
id|device-&gt;blocks
)paren
op_rshift
l_int|11
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;no stat&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_devices_open
id|dasd_devices_open
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
id|tempinfo_t
op_star
id|info
suffix:semicolon
r_int
id|size
comma
id|len
suffix:semicolon
r_int
id|devindex
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|tempinfo_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;No memory available for data (tempinfo)&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|size
op_assign
id|dasd_max_devindex
op_star
l_int|128
suffix:semicolon
id|info-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|vmalloc
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_logical_and
id|info-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;No memory available for data (info-&gt;data)&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|info
suffix:semicolon
id|DBF_EVENT
c_func
(paren
id|DBF_NOTICE
comma
l_string|&quot;procfs-area: %p, size 0x%x allocated&quot;
comma
id|info-&gt;data
comma
id|size
)paren
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|devindex
op_assign
l_int|0
suffix:semicolon
id|devindex
OL
id|dasd_max_devindex
suffix:semicolon
id|devindex
op_increment
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_devindex
c_func
(paren
id|devindex
)paren
suffix:semicolon
id|len
op_add_assign
id|dasd_devices_print
c_func
(paren
id|devmap
comma
id|info-&gt;data
op_plus
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dasd_probeonly
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;(probeonly)&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|info-&gt;data
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|info-&gt;len
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;len = %i, size = %i&bslash;n&quot;
comma
id|len
comma
id|size
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dasd_devices_file_ops
r_static
r_struct
id|file_operations
id|dasd_devices_file_ops
op_assign
(brace
id|read
suffix:colon
id|dasd_generic_read
comma
multiline_comment|/* read */
id|write
suffix:colon
id|dasd_devices_write
comma
multiline_comment|/* write */
id|open
suffix:colon
id|dasd_devices_open
comma
multiline_comment|/* open */
id|release
suffix:colon
id|dasd_generic_close
comma
multiline_comment|/* close */
)brace
suffix:semicolon
DECL|variable|dasd_devices_inode_ops
r_static
r_struct
id|inode_operations
id|dasd_devices_inode_ops
op_assign
(brace
)brace
suffix:semicolon
r_static
r_inline
r_char
op_star
DECL|function|dasd_statistics_array
id|dasd_statistics_array
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|array
comma
r_int
id|shift
)paren
(brace
r_int
id|i
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
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%7d &quot;
comma
id|array
(braket
id|i
)braket
op_rshift
id|shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|15
)paren
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_statistics_open
id|dasd_statistics_open
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
id|tempinfo_t
op_star
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_PROFILE
id|dasd_profile_info_t
op_star
id|prof
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_int
id|shift
suffix:semicolon
macro_line|#endif
id|MOD_INC_USE_COUNT
suffix:semicolon
id|info
op_assign
(paren
id|tempinfo_t
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|tempinfo_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|NULL
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;No memory available for data (tempinfo)&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
(paren
r_void
op_star
)paren
id|info
suffix:semicolon
multiline_comment|/* FIXME! determine space needed in a better way */
id|info-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|vmalloc
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;No memory available for data (info-&gt;data)&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DASD_PROFILE
multiline_comment|/* check for active profiling */
r_if
c_cond
(paren
id|dasd_profile_level
op_eq
id|DASD_PROFILE_OFF
)paren
(brace
id|info-&gt;len
op_assign
id|sprintf
c_func
(paren
id|info-&gt;data
comma
l_string|&quot;Statistics are off - they might be &quot;
l_string|&quot;switched on using &squot;echo set on &gt; &quot;
l_string|&quot;/proc/dasd/statistics&squot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|prof
op_assign
op_amp
id|dasd_global_profile
suffix:semicolon
multiline_comment|/* prevent couter &squot;overflow&squot; on output */
r_for
c_loop
(paren
id|shift
op_assign
l_int|0
suffix:semicolon
(paren
id|prof-&gt;dasd_io_reqs
op_rshift
id|shift
)paren
OG
l_int|9999999
suffix:semicolon
id|shift
op_increment
)paren
suffix:semicolon
id|str
op_assign
id|info-&gt;data
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%d dasd I/O requests&bslash;n&quot;
comma
id|prof-&gt;dasd_io_reqs
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;with %d sectors(512B each)&bslash;n&quot;
comma
id|prof-&gt;dasd_io_sects
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;   __&lt;4&t;   ___8&t;   __16&t;   __32&t;   __64&t;   _128&t;&quot;
l_string|&quot;   _256&t;   _512&t;   __1k&t;   __2k&t;   __4k&t;   __8k&t;&quot;
l_string|&quot;   _16k&t;   _32k&t;   _64k&t;   128k&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;   _256&t;   _512&t;   __1M&t;   __2M&t;   __4M&t;   __8M&t;&quot;
l_string|&quot;   _16M&t;   _32M&t;   _64M&t;   128M&t;   256M&t;   512M&t;&quot;
l_string|&quot;   __1G&t;   __2G&t;   __4G &quot;
l_string|&quot;   _&gt;4G&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of sizes (512B secs)&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_secs
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of I/O times (microseconds)&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_times
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of I/O times per sector&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_timps
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of I/O time till ssch&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_time1
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of I/O time between ssch and irq&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_time2
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of I/O time between ssch &quot;
l_string|&quot;and irq per sector&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_time2ps
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;Histogram of I/O time between irq and end&bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_time3
comma
id|shift
)paren
suffix:semicolon
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;# of req in chanq at enqueuing (1..32) &bslash;n&quot;
)paren
suffix:semicolon
id|str
op_assign
id|dasd_statistics_array
c_func
(paren
id|str
comma
id|prof-&gt;dasd_io_nr_req
comma
id|shift
)paren
suffix:semicolon
id|info-&gt;len
op_assign
id|str
op_minus
id|info-&gt;data
suffix:semicolon
macro_line|#else
id|info-&gt;len
op_assign
id|sprintf
c_func
(paren
id|info-&gt;data
comma
l_string|&quot;Statistics are not activated in this kernel&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|dasd_statistics_write
id|dasd_statistics_write
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
id|user_buf
comma
r_int
id|user_len
comma
id|loff_t
op_star
id|offset
)paren
(brace
macro_line|#ifdef CONFIG_DASD_PROFILE
r_char
op_star
id|buffer
comma
op_star
id|str
suffix:semicolon
id|buffer
op_assign
id|dasd_get_user_string
c_func
(paren
id|user_buf
comma
id|user_len
)paren
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;/proc/dasd/statictics: &squot;%s&squot;&quot;
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/* check for valid verbs */
r_for
c_loop
(paren
id|str
op_assign
id|buffer
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;set&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|str
(braket
l_int|3
)braket
)paren
)paren
(brace
multiline_comment|/* &squot;set xxx&squot; was given */
r_for
c_loop
(paren
id|str
op_assign
id|str
op_plus
l_int|4
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|str
)paren
suffix:semicolon
id|str
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;on&quot;
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* switch on statistics profiling */
id|dasd_profile_level
op_assign
id|DASD_PROFILE_ON
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;Statictics switched on&quot;
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
id|str
comma
l_string|&quot;off&quot;
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* switch off and reset statistics profiling */
id|memset
c_func
(paren
op_amp
id|dasd_global_profile
comma
l_int|0
comma
r_sizeof
(paren
id|dasd_profile_info_t
)paren
)paren
suffix:semicolon
id|dasd_profile_level
op_assign
id|DASD_PROFILE_OFF
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;Statictics switched off&quot;
)paren
suffix:semicolon
)brace
r_else
r_goto
id|out_error
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;reset&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* reset the statistics */
id|memset
c_func
(paren
op_amp
id|dasd_global_profile
comma
l_int|0
comma
r_sizeof
(paren
id|dasd_profile_info_t
)paren
)paren
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;Statictics reset&quot;
)paren
suffix:semicolon
)brace
r_else
r_goto
id|out_error
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|user_len
suffix:semicolon
id|out_error
suffix:colon
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;/proc/dasd/statistics: only &squot;set on&squot;, &squot;set off&squot; &quot;
l_string|&quot;and &squot;reset&squot; are supported verbs&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#else
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;/proc/dasd/statistics: is not activated in this kernel&quot;
)paren
suffix:semicolon
r_return
id|user_len
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_PROFILE */
)brace
DECL|variable|dasd_statistics_file_ops
r_static
r_struct
id|file_operations
id|dasd_statistics_file_ops
op_assign
(brace
id|read
suffix:colon
id|dasd_generic_read
comma
multiline_comment|/* read */
id|write
suffix:colon
id|dasd_statistics_write
comma
multiline_comment|/* write */
id|open
suffix:colon
id|dasd_statistics_open
comma
multiline_comment|/* open */
id|release
suffix:colon
id|dasd_generic_close
comma
multiline_comment|/* close */
)brace
suffix:semicolon
DECL|variable|dasd_statistics_inode_ops
r_static
r_struct
id|inode_operations
id|dasd_statistics_inode_ops
op_assign
(brace
)brace
suffix:semicolon
r_int
DECL|function|dasd_proc_init
id|dasd_proc_init
c_func
(paren
r_void
)paren
(brace
id|dasd_proc_root_entry
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;dasd&quot;
comma
op_amp
id|proc_root
)paren
suffix:semicolon
id|dasd_devices_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;devices&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|dasd_proc_root_entry
)paren
suffix:semicolon
id|dasd_devices_entry-&gt;proc_fops
op_assign
op_amp
id|dasd_devices_file_ops
suffix:semicolon
id|dasd_devices_entry-&gt;proc_iops
op_assign
op_amp
id|dasd_devices_inode_ops
suffix:semicolon
id|dasd_statistics_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;statistics&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|dasd_proc_root_entry
)paren
suffix:semicolon
id|dasd_statistics_entry-&gt;proc_fops
op_assign
op_amp
id|dasd_statistics_file_ops
suffix:semicolon
id|dasd_statistics_entry-&gt;proc_iops
op_assign
op_amp
id|dasd_statistics_inode_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|dasd_proc_exit
id|dasd_proc_exit
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;devices&quot;
comma
id|dasd_proc_root_entry
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;statistics&quot;
comma
id|dasd_proc_root_entry
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;dasd&quot;
comma
op_amp
id|proc_root
)paren
suffix:semicolon
)brace
eof