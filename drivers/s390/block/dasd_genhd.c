multiline_comment|/*&n; * File...........: linux/drivers/s390/block/dasd_ioctl.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; *&t;&t;    Horst Hummel &lt;Horst.Hummel@de.ibm.com&gt;&n; *&t;&t;    Carsten Otte &lt;Cotte@de.ibm.com&gt;&n; *&t;&t;    Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999-2001&n; *&n; * Dealing with devices registered to multiple major numbers.&n; *&n; * 05/04/02 split from dasd.c, code restructuring.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* This is ugly... */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_gendisk:&quot;
macro_line|#include &quot;dasd_int.h&quot;
DECL|variable|dasd_major_lock
r_static
id|spinlock_t
id|dasd_major_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|dasd_major_info
r_static
r_struct
id|list_head
id|dasd_major_info
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|dasd_major_info
)paren
suffix:semicolon
DECL|struct|major_info
r_struct
id|major_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|major
r_int
id|major
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Returns the queue corresponding to a device behind a kdev.&n; */
r_static
id|request_queue_t
op_star
DECL|function|dasd_get_queue
id|dasd_get_queue
c_func
(paren
id|kdev_t
id|kdev
)paren
(brace
id|dasd_devmap_t
op_star
id|devmap
suffix:semicolon
id|dasd_device_t
op_star
id|device
suffix:semicolon
id|request_queue_t
op_star
id|queue
suffix:semicolon
id|devmap
op_assign
id|dasd_devmap_from_kdev
c_func
(paren
id|kdev
)paren
suffix:semicolon
id|device
op_assign
(paren
id|devmap
op_ne
l_int|NULL
)paren
ques
c_cond
id|dasd_get_device
c_func
(paren
id|devmap
)paren
suffix:colon
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
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
l_int|NULL
suffix:semicolon
id|queue
op_assign
id|device-&gt;request_queue
suffix:semicolon
id|dasd_put_device
c_func
(paren
id|devmap
)paren
suffix:semicolon
r_return
id|queue
suffix:semicolon
)brace
multiline_comment|/*&n; * Register major number for the dasd driver. Call with DASD_MAJOR to&n; * setup the static dasd device major 94 or with 0 to allocated a major&n; * dynamically.&n; */
r_static
r_int
DECL|function|dasd_register_major
id|dasd_register_major
c_func
(paren
r_int
id|major
)paren
(brace
r_struct
id|major_info
op_star
id|mi
suffix:semicolon
r_int
id|new_major
suffix:semicolon
multiline_comment|/* Allocate major info structure. */
id|mi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|major_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* Check if one of the allocations failed. */
r_if
c_cond
(paren
id|mi
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
l_string|&quot;Cannot get memory to allocate another &quot;
l_string|&quot;major number&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* Register block device. */
id|new_major
op_assign
id|register_blkdev
c_func
(paren
id|major
comma
l_string|&quot;dasd&quot;
comma
op_amp
id|dasd_device_operations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_major
OL
l_int|0
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;Cannot register to major no %d, rc = %d&quot;
comma
id|major
comma
id|new_major
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mi
)paren
suffix:semicolon
r_return
id|new_major
suffix:semicolon
)brace
r_if
c_cond
(paren
id|major
op_ne
l_int|0
)paren
id|new_major
op_assign
id|major
suffix:semicolon
multiline_comment|/* Initialize major info structure. */
id|mi-&gt;major
op_assign
id|new_major
suffix:semicolon
multiline_comment|/* Setup block device pointers for the new major. */
id|blk_dev
(braket
id|new_major
)braket
dot
id|queue
op_assign
id|dasd_get_queue
suffix:semicolon
multiline_comment|/* Insert the new major info structure into dasd_major_info list. */
id|spin_lock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|mi-&gt;list
comma
op_amp
id|dasd_major_info
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|dasd_unregister_major
id|dasd_unregister_major
c_func
(paren
r_struct
id|major_info
op_star
id|mi
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|mi
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Delete the major info from dasd_major_info. */
id|spin_lock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|mi-&gt;list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
multiline_comment|/* Clear block device pointers. */
id|blk_dev
(braket
id|mi-&gt;major
)braket
dot
id|queue
op_assign
l_int|NULL
suffix:semicolon
id|rc
op_assign
id|unregister_blkdev
c_func
(paren
id|mi-&gt;major
comma
l_string|&quot;dasd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;Cannot unregister from major no %d, rc = %d&quot;
comma
id|mi-&gt;major
comma
id|rc
)paren
suffix:semicolon
multiline_comment|/* Free memory. */
id|kfree
c_func
(paren
id|mi
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This one is needed for naming 18000+ possible dasd devices.&n; *   dasda - dasdz : 26 devices&n; *   dasdaa - dasdzz : 676 devices, added up = 702&n; *   dasdaaa - dasdzzz : 17576 devices, added up = 18278&n; */
r_int
DECL|function|dasd_device_name
id|dasd_device_name
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|index
comma
r_int
id|partition
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|partition
OG
id|DASD_PARTN_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;dasd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
l_int|25
)paren
(brace
r_if
c_cond
(paren
id|index
OG
l_int|701
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
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|index
op_minus
l_int|702
)paren
op_div
l_int|676
)paren
op_mod
l_int|26
)paren
)paren
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
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|index
op_minus
l_int|26
)paren
op_div
l_int|26
)paren
op_mod
l_int|26
)paren
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|str
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
id|index
op_mod
l_int|26
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|partition
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
l_string|&quot;%d&quot;
comma
id|partition
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate gendisk structure for devindex.&n; */
r_struct
id|gendisk
op_star
DECL|function|dasd_gendisk_alloc
id|dasd_gendisk_alloc
c_func
(paren
r_char
op_star
id|device_name
comma
r_int
id|devindex
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|major_info
op_star
id|mi
suffix:semicolon
r_struct
id|gendisk
op_star
id|gdp
suffix:semicolon
r_int
id|index
comma
id|len
comma
id|rc
suffix:semicolon
multiline_comment|/* Make sure the major for this device exists. */
id|mi
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
id|index
op_assign
id|devindex
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|dasd_major_info
)paren
(brace
id|mi
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|major_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|DASD_PER_MAJOR
)paren
r_break
suffix:semicolon
id|index
op_sub_assign
id|DASD_PER_MAJOR
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
id|DASD_PER_MAJOR
)paren
r_break
suffix:semicolon
id|rc
op_assign
id|dasd_register_major
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|DBF_EXC
c_func
(paren
id|DBF_ALERT
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;out of major numbers!&quot;
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|rc
)paren
suffix:semicolon
)brace
)brace
id|gdp
op_assign
id|alloc_disk
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
multiline_comment|/* Initialize gendisk structure. */
id|memcpy
c_func
(paren
id|gdp-&gt;disk_name
comma
id|device_name
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/* huh? -- AV */
id|gdp-&gt;major
op_assign
id|mi-&gt;major
suffix:semicolon
id|gdp-&gt;first_minor
op_assign
id|index
op_lshift
id|DASD_PARTN_BITS
suffix:semicolon
id|gdp-&gt;minor_shift
op_assign
id|DASD_PARTN_BITS
suffix:semicolon
id|gdp-&gt;fops
op_assign
op_amp
id|dasd_device_operations
suffix:semicolon
multiline_comment|/*&n;&t; * Set device name.&n;&t; *   dasda - dasdz : 26 devices&n;&t; *   dasdaa - dasdzz : 676 devices, added up = 702&n;&t; *   dasdaaa - dasdzzz : 17576 devices, added up = 18278&n;&t; */
id|len
op_assign
id|sprintf
c_func
(paren
id|device_name
comma
l_string|&quot;dasd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devindex
OG
l_int|25
)paren
(brace
r_if
c_cond
(paren
id|devindex
OG
l_int|701
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|device_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|devindex
op_minus
l_int|702
)paren
op_div
l_int|676
)paren
op_mod
l_int|26
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|device_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|devindex
op_minus
l_int|26
)paren
op_div
l_int|26
)paren
op_mod
l_int|26
)paren
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|device_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
id|devindex
op_mod
l_int|26
)paren
)paren
suffix:semicolon
r_return
id|gdp
suffix:semicolon
)brace
multiline_comment|/*&n; * Return devindex of first device using a specific major number.&n; */
DECL|function|dasd_gendisk_major_index
r_int
id|dasd_gendisk_major_index
c_func
(paren
r_int
id|major
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|major_info
op_star
id|mi
suffix:semicolon
r_int
id|devindex
comma
id|rc
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|devindex
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|dasd_major_info
)paren
(brace
id|mi
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|major_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;major
op_eq
id|major
)paren
(brace
id|rc
op_assign
id|devindex
suffix:semicolon
r_break
suffix:semicolon
)brace
id|devindex
op_add_assign
id|DASD_PER_MAJOR
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Return major number for device with device index devindex.&n; */
DECL|function|dasd_gendisk_index_major
r_int
id|dasd_gendisk_index_major
c_func
(paren
r_int
id|devindex
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|major_info
op_star
id|mi
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|dasd_major_info
)paren
(brace
id|mi
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|major_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devindex
OL
id|DASD_PER_MAJOR
)paren
(brace
id|rc
op_assign
id|mi-&gt;major
suffix:semicolon
r_break
suffix:semicolon
)brace
id|devindex
op_sub_assign
id|DASD_PER_MAJOR
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Register disk to genhd. This will trigger a partition detection.&n; */
r_void
DECL|function|dasd_setup_partitions
id|dasd_setup_partitions
c_func
(paren
id|dasd_device_t
op_star
id|device
)paren
(brace
multiline_comment|/* Make the disk known. */
id|set_capacity
c_func
(paren
id|device-&gt;gdp
comma
id|device-&gt;blocks
op_lshift
id|device-&gt;s2b_shift
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|device-&gt;gdp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove all inodes in the system for a device and make the&n; * partitions unusable by setting their size to zero.&n; */
r_void
DECL|function|dasd_destroy_partitions
id|dasd_destroy_partitions
c_func
(paren
id|dasd_device_t
op_star
id|device
)paren
(brace
id|del_gendisk
c_func
(paren
id|device-&gt;gdp
)paren
suffix:semicolon
)brace
r_int
DECL|function|dasd_gendisk_init
id|dasd_gendisk_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
multiline_comment|/* Register to static dasd major 94 */
id|rc
op_assign
id|dasd_register_major
c_func
(paren
id|DASD_MAJOR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;Couldn&squot;t register successfully to &quot;
l_string|&quot;major no %d&quot;
comma
id|DASD_MAJOR
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_void
DECL|function|dasd_gendisk_exit
id|dasd_gendisk_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|l
comma
op_star
id|n
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|l
comma
id|n
comma
op_amp
id|dasd_major_info
)paren
id|dasd_unregister_major
c_func
(paren
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|major_info
comma
id|list
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dasd_major_lock
)paren
suffix:semicolon
)brace
eof
