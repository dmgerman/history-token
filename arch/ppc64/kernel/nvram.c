multiline_comment|/*&n; *  c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * /dev/nvram driver for PPC64&n; *&n; * This perhaps should live in drivers/char&n; *&n; * TODO: Split the /dev/nvram part (that one can use&n; *       drivers/char/generic_nvram.c) from the arch &amp; partition&n; *       parsing code.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
DECL|macro|DEBUG_NVRAM
macro_line|#undef DEBUG_NVRAM
r_static
r_int
id|nvram_scan_partitions
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|nvram_setup_partition
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|nvram_create_os_partition
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|nvram_remove_os_partition
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|nvram_part
r_static
r_struct
id|nvram_partition
op_star
id|nvram_part
suffix:semicolon
DECL|variable|nvram_error_log_index
r_static
r_int
id|nvram_error_log_index
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|nvram_error_log_size
r_static
r_int
id|nvram_error_log_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|no_logging
r_int
id|no_logging
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Until we initialize everything,&n;&t;&t;&t; * make sure we don&squot;t try logging&n;&t;&t;&t; * anything */
r_extern
r_volatile
r_int
id|error_log_cnt
suffix:semicolon
DECL|struct|err_log_info
r_struct
id|err_log_info
(brace
DECL|member|error_type
r_int
id|error_type
suffix:semicolon
DECL|member|seq_num
r_int
r_int
id|seq_num
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dev_nvram_llseek
r_static
id|loff_t
id|dev_nvram_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.nvram_size
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|size
op_assign
id|ppc_md
dot
id|nvram_size
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|size
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
DECL|function|dev_nvram_read
r_static
id|ssize_t
id|dev_nvram_read
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
id|ssize_t
id|len
suffix:semicolon
r_char
op_star
id|tmp_buffer
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.nvram_size
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|size
op_assign
id|ppc_md
dot
id|nvram_size
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
r_if
c_cond
(paren
op_star
id|ppos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
)paren
id|count
op_assign
id|size
suffix:semicolon
id|tmp_buffer
op_assign
(paren
r_char
op_star
)paren
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
id|tmp_buffer
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dev_read_nvram: kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|len
op_assign
id|ppc_md
dot
id|nvram_read
c_func
(paren
id|tmp_buffer
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|len
op_le
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|tmp_buffer
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|tmp_buffer
comma
id|len
)paren
)paren
(brace
id|kfree
c_func
(paren
id|tmp_buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmp_buffer
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|dev_nvram_write
r_static
id|ssize_t
id|dev_nvram_write
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
id|ssize_t
id|len
suffix:semicolon
r_char
op_star
id|tmp_buffer
suffix:semicolon
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.nvram_size
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|size
op_assign
id|ppc_md
dot
id|nvram_size
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
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
r_if
c_cond
(paren
op_star
id|ppos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
)paren
id|count
op_assign
id|size
suffix:semicolon
id|tmp_buffer
op_assign
(paren
r_char
op_star
)paren
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
id|tmp_buffer
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dev_nvram_write: kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|tmp_buffer
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|kfree
c_func
(paren
id|tmp_buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|len
op_assign
id|ppc_md
dot
id|nvram_write
c_func
(paren
id|tmp_buffer
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|len
op_le
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|tmp_buffer
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmp_buffer
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|dev_nvram_ioctl
r_static
r_int
id|dev_nvram_ioctl
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
macro_line|#ifdef CONFIG_PPC_PMAC
r_case
id|OBSOLETE_PMAC_NVRAM_GET_OFFSET
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nvram: Using obsolete PMAC_NVRAM_GET_OFFSET ioctl&bslash;n&quot;
)paren
suffix:semicolon
r_case
id|IOC_NVRAM_GET_OFFSET
suffix:colon
(brace
r_int
id|part
comma
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_ne
id|PLATFORM_POWERMAC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|part
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|part
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|part
template_param
id|pmac_nvram_NR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|offset
op_assign
id|pmac_get_partition
c_func
(paren
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
op_amp
id|offset
comma
r_sizeof
(paren
id|offset
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|nvram_fops
r_struct
id|file_operations
id|nvram_fops
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
id|dev_nvram_llseek
comma
dot
id|read
op_assign
id|dev_nvram_read
comma
dot
id|write
op_assign
id|dev_nvram_write
comma
dot
id|ioctl
op_assign
id|dev_nvram_ioctl
comma
)brace
suffix:semicolon
DECL|variable|nvram_dev
r_static
r_struct
id|miscdevice
id|nvram_dev
op_assign
(brace
id|NVRAM_MINOR
comma
l_string|&quot;nvram&quot;
comma
op_amp
id|nvram_fops
)brace
suffix:semicolon
macro_line|#ifdef DEBUG_NVRAM
DECL|function|nvram_print_partitions
r_static
r_void
id|nvram_print_partitions
c_func
(paren
r_char
op_star
id|label
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|tmp_part
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;--------%s---------&bslash;n&quot;
comma
id|label
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;indx&bslash;t&bslash;tsig&bslash;tchks&bslash;tlen&bslash;tname&bslash;n&quot;
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|nvram_part-&gt;partition
)paren
(brace
id|tmp_part
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%d    &bslash;t%02x&bslash;t%02x&bslash;t%d&bslash;t%s&bslash;n&quot;
comma
id|tmp_part-&gt;index
comma
id|tmp_part-&gt;header.signature
comma
id|tmp_part-&gt;header.checksum
comma
id|tmp_part-&gt;header.length
comma
id|tmp_part-&gt;header.name
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|nvram_write_header
r_static
r_int
id|nvram_write_header
c_func
(paren
r_struct
id|nvram_partition
op_star
id|part
)paren
(brace
id|loff_t
id|tmp_index
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|tmp_index
op_assign
id|part-&gt;index
suffix:semicolon
id|rc
op_assign
id|ppc_md
dot
id|nvram_write
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|part-&gt;header
comma
id|NVRAM_HEADER_LEN
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|nvram_checksum
r_static
r_int
r_char
id|nvram_checksum
c_func
(paren
r_struct
id|nvram_header
op_star
id|p
)paren
(brace
r_int
r_int
id|c_sum
comma
id|c_sum2
suffix:semicolon
r_int
r_int
op_star
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|p-&gt;name
suffix:semicolon
multiline_comment|/* assume 6 shorts */
id|c_sum
op_assign
id|p-&gt;signature
op_plus
id|p-&gt;length
op_plus
id|sp
(braket
l_int|0
)braket
op_plus
id|sp
(braket
l_int|1
)braket
op_plus
id|sp
(braket
l_int|2
)braket
op_plus
id|sp
(braket
l_int|3
)braket
op_plus
id|sp
(braket
l_int|4
)braket
op_plus
id|sp
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* The sum may have spilled into the 3rd byte.  Fold it back. */
id|c_sum
op_assign
(paren
(paren
id|c_sum
op_amp
l_int|0xffff
)paren
op_plus
(paren
id|c_sum
op_rshift
l_int|16
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
multiline_comment|/* The sum cannot exceed 2 bytes.  Fold it into a checksum */
id|c_sum2
op_assign
(paren
id|c_sum
op_rshift
l_int|8
)paren
op_plus
(paren
id|c_sum
op_lshift
l_int|8
)paren
suffix:semicolon
id|c_sum
op_assign
(paren
(paren
id|c_sum
op_plus
id|c_sum2
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_return
id|c_sum
suffix:semicolon
)brace
multiline_comment|/*&n; * Find an nvram partition, sig can be 0 for any&n; * partition or name can be NULL for any name, else&n; * tries to match both&n; */
DECL|function|nvram_find_partition
r_struct
id|nvram_partition
op_star
id|nvram_find_partition
c_func
(paren
r_int
id|sig
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|nvram_partition
op_star
id|part
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|nvram_part-&gt;partition
)paren
(brace
id|part
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_logical_and
id|part-&gt;header.signature
op_ne
id|sig
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|name
op_logical_and
l_int|0
op_ne
id|strncmp
c_func
(paren
id|name
comma
id|part-&gt;header.name
comma
l_int|12
)paren
)paren
r_continue
suffix:semicolon
r_return
id|part
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|nvram_find_partition
id|EXPORT_SYMBOL
c_func
(paren
id|nvram_find_partition
)paren
suffix:semicolon
DECL|function|nvram_remove_os_partition
r_static
r_int
id|nvram_remove_os_partition
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|j
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|part
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|cur_part
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|list_for_each
c_func
(paren
id|i
comma
op_amp
id|nvram_part-&gt;partition
)paren
(brace
id|part
op_assign
id|list_entry
c_func
(paren
id|i
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|part-&gt;header.signature
op_ne
id|NVRAM_SIG_OS
)paren
r_continue
suffix:semicolon
multiline_comment|/* Make os partition a free partition */
id|part-&gt;header.signature
op_assign
id|NVRAM_SIG_FREE
suffix:semicolon
id|sprintf
c_func
(paren
id|part-&gt;header.name
comma
l_string|&quot;wwwwwwwwwwww&quot;
)paren
suffix:semicolon
id|part-&gt;header.checksum
op_assign
id|nvram_checksum
c_func
(paren
op_amp
id|part-&gt;header
)paren
suffix:semicolon
multiline_comment|/* Merge contiguous free partitions backwards */
id|list_for_each_prev
c_func
(paren
id|j
comma
op_amp
id|part-&gt;partition
)paren
(brace
id|cur_part
op_assign
id|list_entry
c_func
(paren
id|j
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_part
op_eq
id|nvram_part
op_logical_or
id|cur_part-&gt;header.signature
op_ne
id|NVRAM_SIG_FREE
)paren
(brace
r_break
suffix:semicolon
)brace
id|part-&gt;header.length
op_add_assign
id|cur_part-&gt;header.length
suffix:semicolon
id|part-&gt;header.checksum
op_assign
id|nvram_checksum
c_func
(paren
op_amp
id|part-&gt;header
)paren
suffix:semicolon
id|part-&gt;index
op_assign
id|cur_part-&gt;index
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|cur_part-&gt;partition
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cur_part
)paren
suffix:semicolon
id|j
op_assign
op_amp
id|part-&gt;partition
suffix:semicolon
multiline_comment|/* fixup our loop */
)brace
multiline_comment|/* Merge contiguous free partitions forwards */
id|list_for_each
c_func
(paren
id|j
comma
op_amp
id|part-&gt;partition
)paren
(brace
id|cur_part
op_assign
id|list_entry
c_func
(paren
id|j
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_part
op_eq
id|nvram_part
op_logical_or
id|cur_part-&gt;header.signature
op_ne
id|NVRAM_SIG_FREE
)paren
(brace
r_break
suffix:semicolon
)brace
id|part-&gt;header.length
op_add_assign
id|cur_part-&gt;header.length
suffix:semicolon
id|part-&gt;header.checksum
op_assign
id|nvram_checksum
c_func
(paren
op_amp
id|part-&gt;header
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|cur_part-&gt;partition
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cur_part
)paren
suffix:semicolon
id|j
op_assign
op_amp
id|part-&gt;partition
suffix:semicolon
multiline_comment|/* fixup our loop */
)brace
id|rc
op_assign
id|nvram_write_header
c_func
(paren
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_remove_os_partition: nvram_write failed (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* nvram_create_os_partition&n; *&n; * Create a OS linux partition to buffer error logs.&n; * Will create a partition starting at the first free&n; * space found if space has enough room.&n; */
DECL|function|nvram_create_os_partition
r_static
r_int
id|nvram_create_os_partition
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|part
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|new_part
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|free_part
op_assign
l_int|NULL
suffix:semicolon
r_int
id|seq_init
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|loff_t
id|tmp_index
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
suffix:semicolon
multiline_comment|/* Find a free partition that will give us the maximum needed size &n;&t;   If can&squot;t find one that will give us the minimum size needed */
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|nvram_part-&gt;partition
)paren
(brace
id|part
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|part-&gt;header.signature
op_ne
id|NVRAM_SIG_FREE
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|part-&gt;header.length
op_ge
id|NVRAM_MAX_REQ
)paren
(brace
id|size
op_assign
id|NVRAM_MAX_REQ
suffix:semicolon
id|free_part
op_assign
id|part
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_and
id|part-&gt;header.length
op_ge
id|NVRAM_MIN_REQ
)paren
(brace
id|size
op_assign
id|NVRAM_MIN_REQ
suffix:semicolon
id|free_part
op_assign
id|part
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/* Create our OS partition */
id|new_part
op_assign
(paren
r_struct
id|nvram_partition
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nvram_partition
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_part
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_create_os_partition: kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|new_part-&gt;index
op_assign
id|free_part-&gt;index
suffix:semicolon
id|new_part-&gt;header.signature
op_assign
id|NVRAM_SIG_OS
suffix:semicolon
id|new_part-&gt;header.length
op_assign
id|size
suffix:semicolon
id|sprintf
c_func
(paren
id|new_part-&gt;header.name
comma
l_string|&quot;ppc64,linux&quot;
)paren
suffix:semicolon
id|new_part-&gt;header.checksum
op_assign
id|nvram_checksum
c_func
(paren
op_amp
id|new_part-&gt;header
)paren
suffix:semicolon
id|rc
op_assign
id|nvram_write_header
c_func
(paren
id|new_part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_create_os_partition: nvram_write_header &bslash;&n;&t;&t;&t;&t;failed (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* make sure and initialize to zero the sequence number and the error&n;&t;   type logged */
id|tmp_index
op_assign
id|new_part-&gt;index
op_plus
id|NVRAM_HEADER_LEN
suffix:semicolon
id|rc
op_assign
id|ppc_md
dot
id|nvram_write
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|seq_init
comma
r_sizeof
(paren
id|seq_init
)paren
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_create_os_partition: nvram_write failed (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|nvram_error_log_index
op_assign
id|new_part-&gt;index
op_plus
id|NVRAM_HEADER_LEN
suffix:semicolon
id|nvram_error_log_size
op_assign
(paren
(paren
id|part-&gt;header.length
op_minus
l_int|1
)paren
op_star
id|NVRAM_BLOCK_LEN
)paren
op_minus
r_sizeof
(paren
r_struct
id|err_log_info
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|new_part-&gt;partition
comma
op_amp
id|free_part-&gt;partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_part-&gt;header.length
op_le
id|size
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|free_part-&gt;partition
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|free_part
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Adjust the partition we stole the space from */
id|free_part-&gt;index
op_add_assign
id|size
op_star
id|NVRAM_BLOCK_LEN
suffix:semicolon
id|free_part-&gt;header.length
op_sub_assign
id|size
suffix:semicolon
id|free_part-&gt;header.checksum
op_assign
id|nvram_checksum
c_func
(paren
op_amp
id|free_part-&gt;header
)paren
suffix:semicolon
id|rc
op_assign
id|nvram_write_header
c_func
(paren
id|free_part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_create_os_partition: nvram_write_header &quot;
l_string|&quot;failed (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* nvram_setup_partition&n; *&n; * This will setup the partition we need for buffering the&n; * error logs and cleanup partitions if needed.&n; *&n; * The general strategy is the following:&n; * 1.) If there is ppc64,linux partition large enough then use it.&n; * 2.) If there is not a ppc64,linux partition large enough, search&n; * for a free partition that is large enough.&n; * 3.) If there is not a free partition large enough remove &n; * _all_ OS partitions and consolidate the space.&n; * 4.) Will first try getting a chunk that will satisfy the maximum&n; * error log size (NVRAM_MAX_REQ).&n; * 5.) If the max chunk cannot be allocated then try finding a chunk&n; * that will satisfy the minum needed (NVRAM_MIN_REQ).&n; */
DECL|function|nvram_setup_partition
r_static
r_int
id|nvram_setup_partition
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|part
suffix:semicolon
r_int
id|rc
suffix:semicolon
multiline_comment|/* For now, we don&squot;t do any of this on pmac, until I&n;&t; * have figured out if it&squot;s worth killing some unused stuffs&n;&t; * in our nvram, as Apple defined partitions use pretty much&n;&t; * all of the space&n;&t; */
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_POWERMAC
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
multiline_comment|/* see if we have an OS partition that meets our needs.&n;&t;   will try getting the max we need.  If not we&squot;ll delete&n;&t;   partitions and try again. */
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|nvram_part-&gt;partition
)paren
(brace
id|part
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|nvram_partition
comma
id|partition
)paren
suffix:semicolon
r_if
c_cond
(paren
id|part-&gt;header.signature
op_ne
id|NVRAM_SIG_OS
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|part-&gt;header.name
comma
l_string|&quot;ppc64,linux&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|part-&gt;header.length
op_ge
id|NVRAM_MIN_REQ
)paren
(brace
multiline_comment|/* found our partition */
id|nvram_error_log_index
op_assign
id|part-&gt;index
op_plus
id|NVRAM_HEADER_LEN
suffix:semicolon
id|nvram_error_log_size
op_assign
(paren
(paren
id|part-&gt;header.length
op_minus
l_int|1
)paren
op_star
id|NVRAM_BLOCK_LEN
)paren
op_minus
r_sizeof
(paren
r_struct
id|err_log_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* try creating a partition with the free space we have */
id|rc
op_assign
id|nvram_create_os_partition
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* need to free up some space */
id|rc
op_assign
id|nvram_remove_os_partition
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* create a partition in this new space */
id|rc
op_assign
id|nvram_create_os_partition
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_create_os_partition: Could not find a &quot;
l_string|&quot;NVRAM partition large enough&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nvram_scan_partitions
r_static
r_int
id|nvram_scan_partitions
c_func
(paren
r_void
)paren
(brace
id|loff_t
id|cur_index
op_assign
l_int|0
suffix:semicolon
r_struct
id|nvram_header
id|phead
suffix:semicolon
r_struct
id|nvram_partition
op_star
id|tmp_part
suffix:semicolon
r_int
r_char
id|c_sum
suffix:semicolon
r_char
op_star
id|header
suffix:semicolon
r_int
id|total_size
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.nvram_size
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|total_size
op_assign
id|ppc_md
dot
id|nvram_size
c_func
(paren
)paren
suffix:semicolon
id|header
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|NVRAM_HEADER_LEN
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_scan_partitions: Failed kmalloc&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cur_index
OL
id|total_size
)paren
(brace
id|err
op_assign
id|ppc_md
dot
id|nvram_read
c_func
(paren
id|header
comma
id|NVRAM_HEADER_LEN
comma
op_amp
id|cur_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
id|NVRAM_HEADER_LEN
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_scan_partitions: Error parsing &quot;
l_string|&quot;nvram partitions&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|cur_index
op_sub_assign
id|NVRAM_HEADER_LEN
suffix:semicolon
multiline_comment|/* nvram_read will advance us */
id|memcpy
c_func
(paren
op_amp
id|phead
comma
id|header
comma
id|NVRAM_HEADER_LEN
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|c_sum
op_assign
id|nvram_checksum
c_func
(paren
op_amp
id|phead
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c_sum
op_ne
id|phead.checksum
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;WARNING: nvram partition checksum&quot;
l_string|&quot; was %02x, should be %02x!&bslash;n&quot;
comma
id|phead.checksum
comma
id|c_sum
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Terminating nvram partition scan&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|phead.length
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;WARNING: nvram corruption &quot;
l_string|&quot;detected: 0-length partition&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|tmp_part
op_assign
(paren
r_struct
id|nvram_partition
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nvram_partition
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_part
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_scan_partitions: kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|tmp_part-&gt;header
comma
op_amp
id|phead
comma
id|NVRAM_HEADER_LEN
)paren
suffix:semicolon
id|tmp_part-&gt;index
op_assign
id|cur_index
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|tmp_part-&gt;partition
comma
op_amp
id|nvram_part-&gt;partition
)paren
suffix:semicolon
id|cur_index
op_add_assign
id|phead.length
op_star
id|NVRAM_BLOCK_LEN
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|header
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|nvram_init
r_static
r_int
id|__init
id|nvram_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.nvram_size
op_eq
l_int|NULL
op_logical_or
id|ppc_md
dot
id|nvram_size
c_func
(paren
)paren
op_le
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|rc
op_assign
id|misc_register
c_func
(paren
op_amp
id|nvram_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_init: failed to register device&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* initialize our anchor for the nvram partition list */
id|nvram_part
op_assign
(paren
r_struct
id|nvram_partition
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nvram_partition
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nvram_part
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_init: Failed kmalloc&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|nvram_part-&gt;partition
)paren
suffix:semicolon
multiline_comment|/* Get all the NVRAM partitions */
id|error
op_assign
id|nvram_scan_partitions
c_func
(paren
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
l_string|&quot;nvram_init: Failed nvram_scan_partitions&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nvram_setup_partition
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nvram_init: Could not find nvram partition&quot;
l_string|&quot; for nvram buffered error logging.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_NVRAM
id|nvram_print_partitions
c_func
(paren
l_string|&quot;NVRAM Partitions&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|rc
suffix:semicolon
)brace
DECL|function|nvram_cleanup
r_void
id|__exit
id|nvram_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|nvram_dev
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* nvram_write_error_log&n; *&n; * We need to buffer the error logs into nvram to ensure that we have&n; * the failure information to decode.  If we have a severe error there&n; * is no way to guarantee that the OS or the machine is in a state to&n; * get back to user land and write the error to disk.  For example if&n; * the SCSI device driver causes a Machine Check by writing to a bad&n; * IO address, there is no way of guaranteeing that the device driver&n; * is in any state that is would also be able to write the error data&n; * captured to disk, thus we buffer it in NVRAM for analysis on the&n; * next boot.&n; *&n; * In NVRAM the partition containing the error log buffer will looks like:&n; * Header (in bytes):&n; * +-----------+----------+--------+------------+------------------+&n; * | signature | checksum | length | name       | data             |&n; * |0          |1         |2      3|4         15|16        length-1|&n; * +-----------+----------+--------+------------+------------------+&n; *&n; * The &squot;data&squot; section would look like (in bytes):&n; * +--------------+------------+-----------------------------------+&n; * | event_logged | sequence # | error log                         |&n; * |0            3|4          7|8            nvram_error_log_size-1|&n; * +--------------+------------+-----------------------------------+&n; *&n; * event_logged: 0 if event has not been logged to syslog, 1 if it has&n; * sequence #: The unique sequence # for each event. (until it wraps)&n; * error log: The error log from event_scan&n; */
DECL|function|nvram_write_error_log
r_int
id|nvram_write_error_log
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|length
comma
r_int
r_int
id|err_type
)paren
(brace
r_int
id|rc
suffix:semicolon
id|loff_t
id|tmp_index
suffix:semicolon
r_struct
id|err_log_info
id|info
suffix:semicolon
r_if
c_cond
(paren
id|no_logging
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nvram_error_log_index
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
OG
id|nvram_error_log_size
)paren
(brace
id|length
op_assign
id|nvram_error_log_size
suffix:semicolon
)brace
id|info.error_type
op_assign
id|err_type
suffix:semicolon
id|info.seq_num
op_assign
id|error_log_cnt
suffix:semicolon
id|tmp_index
op_assign
id|nvram_error_log_index
suffix:semicolon
id|rc
op_assign
id|ppc_md
dot
id|nvram_write
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|info
comma
r_sizeof
(paren
r_struct
id|err_log_info
)paren
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_write_error_log: Failed nvram_write (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|rc
op_assign
id|ppc_md
dot
id|nvram_write
c_func
(paren
id|buff
comma
id|length
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_write_error_log: Failed nvram_write (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* nvram_read_error_log&n; *&n; * Reads nvram for error log for at most &squot;length&squot;&n; */
DECL|function|nvram_read_error_log
r_int
id|nvram_read_error_log
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|length
comma
r_int
r_int
op_star
id|err_type
)paren
(brace
r_int
id|rc
suffix:semicolon
id|loff_t
id|tmp_index
suffix:semicolon
r_struct
id|err_log_info
id|info
suffix:semicolon
r_if
c_cond
(paren
id|nvram_error_log_index
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|nvram_error_log_size
)paren
id|length
op_assign
id|nvram_error_log_size
suffix:semicolon
id|tmp_index
op_assign
id|nvram_error_log_index
suffix:semicolon
id|rc
op_assign
id|ppc_md
dot
id|nvram_read
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|info
comma
r_sizeof
(paren
r_struct
id|err_log_info
)paren
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_read_error_log: Failed nvram_read (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|rc
op_assign
id|ppc_md
dot
id|nvram_read
c_func
(paren
id|buff
comma
id|length
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_read_error_log: Failed nvram_read (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|error_log_cnt
op_assign
id|info.seq_num
suffix:semicolon
op_star
id|err_type
op_assign
id|info.error_type
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This doesn&squot;t actually zero anything, but it sets the event_logged&n; * word to tell that this event is safely in syslog.&n; */
DECL|function|nvram_clear_error_log
r_int
id|nvram_clear_error_log
c_func
(paren
r_void
)paren
(brace
id|loff_t
id|tmp_index
suffix:semicolon
r_int
id|clear_word
op_assign
id|ERR_FLAG_ALREADY_LOGGED
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|tmp_index
op_assign
id|nvram_error_log_index
suffix:semicolon
id|rc
op_assign
id|ppc_md
dot
id|nvram_write
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|clear_word
comma
r_sizeof
(paren
r_int
)paren
comma
op_amp
id|tmp_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram_clear_error_log: Failed nvram_write (%d)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PSERIES */
DECL|variable|nvram_init
id|module_init
c_func
(paren
id|nvram_init
)paren
suffix:semicolon
DECL|variable|nvram_cleanup
id|module_exit
c_func
(paren
id|nvram_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
