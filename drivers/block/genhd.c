multiline_comment|/*&n; *  Code extracted from&n; *  linux/kernel/hd.c&n; *&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *&n; *  devfs support - jj, rgooch, 980122&n; *&n; *  Moved partition checking code to fs/partitions* - Russell King&n; *  (linux@arm.uk.linux.org)&n; */
multiline_comment|/*&n; * TODO:  rip out the remaining init crap from this file  --hch&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|variable|gendisk_lock
r_static
id|rwlock_t
id|gendisk_lock
suffix:semicolon
multiline_comment|/*&n; * Global kernel list of partitioning information.&n; */
r_static
id|LIST_HEAD
c_func
(paren
id|gendisk_list
)paren
suffix:semicolon
multiline_comment|/*&n; *  TEMPORARY KLUDGE.&n; */
r_static
r_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|get
r_struct
id|gendisk
op_star
(paren
op_star
id|get
)paren
(paren
r_int
id|minor
)paren
suffix:semicolon
DECL|variable|gendisks
)brace
id|gendisks
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
DECL|function|blk_set_probe
r_void
id|blk_set_probe
c_func
(paren
r_int
id|major
comma
r_struct
id|gendisk
op_star
(paren
id|p
)paren
(paren
r_int
)paren
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
id|gendisks
(braket
id|major
)braket
dot
id|get
op_assign
id|p
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
)brace
DECL|variable|blk_set_probe
id|EXPORT_SYMBOL
c_func
(paren
id|blk_set_probe
)paren
suffix:semicolon
multiline_comment|/* Will go away */
multiline_comment|/**&n; * add_gendisk - add partitioning information to kernel list&n; * @gp: per-device partitioning information&n; *&n; * This function registers the partitioning information in @gp&n; * with the kernel.&n; */
DECL|function|add_gendisk
r_static
r_void
id|add_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|gp
)paren
(brace
r_struct
id|hd_struct
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|gp-&gt;minor_shift
)paren
(brace
r_int
id|size
op_assign
r_sizeof
(paren
r_struct
id|hd_struct
)paren
op_star
(paren
(paren
l_int|1
op_lshift
id|gp-&gt;minor_shift
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
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
l_string|&quot;out of memory; no partitions for %s&bslash;n&quot;
comma
id|gp-&gt;major_name
)paren
suffix:semicolon
id|gp-&gt;minor_shift
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
id|gp-&gt;part
op_assign
id|p
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|gp-&gt;list
comma
op_amp
id|gendisks
(braket
id|gp-&gt;major
)braket
dot
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gp-&gt;minor_shift
)paren
id|list_add_tail
c_func
(paren
op_amp
id|gp-&gt;full_list
comma
op_amp
id|gendisk_list
)paren
suffix:semicolon
r_else
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|gp-&gt;full_list
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
)brace
DECL|function|add_disk
r_void
id|add_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
id|add_gendisk
c_func
(paren
id|disk
)paren
suffix:semicolon
id|register_disk
c_func
(paren
id|disk
comma
id|mk_kdev
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
comma
l_int|1
op_lshift
id|disk-&gt;minor_shift
comma
id|disk-&gt;fops
comma
id|get_capacity
c_func
(paren
id|disk
)paren
)paren
suffix:semicolon
)brace
DECL|variable|add_disk
id|EXPORT_SYMBOL
c_func
(paren
id|add_disk
)paren
suffix:semicolon
DECL|variable|del_gendisk
id|EXPORT_SYMBOL
c_func
(paren
id|del_gendisk
)paren
suffix:semicolon
DECL|function|unlink_gendisk
r_void
id|unlink_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|disk-&gt;full_list
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|disk-&gt;list
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * get_gendisk - get partitioning information for a given device&n; * @dev: device to get partitioning information for&n; *&n; * This function gets the structure containing partitioning&n; * information for the given device @dev.&n; */
r_struct
id|gendisk
op_star
DECL|function|get_gendisk
id|get_gendisk
c_func
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_int
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|part
op_assign
l_int|0
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gendisks
(braket
id|major
)braket
dot
id|get
)paren
(brace
id|disk
op_assign
id|gendisks
(braket
id|major
)braket
dot
id|get
c_func
(paren
id|minor
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_return
id|disk
suffix:semicolon
)brace
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|gendisks
(braket
id|major
)braket
dot
id|list
)paren
(brace
id|disk
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|gendisk
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk-&gt;first_minor
OG
id|minor
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|disk-&gt;first_minor
op_plus
(paren
l_int|1
op_lshift
id|disk-&gt;minor_shift
)paren
op_le
id|minor
)paren
r_continue
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
op_star
id|part
op_assign
id|minor
op_minus
id|disk-&gt;first_minor
suffix:semicolon
r_return
id|disk
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|get_gendisk
id|EXPORT_SYMBOL
c_func
(paren
id|get_gendisk
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* iterator */
DECL|function|part_start
r_static
r_void
op_star
id|part_start
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|gendisk_list
)paren
r_if
c_cond
(paren
op_logical_neg
id|l
op_decrement
)paren
r_return
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|gendisk
comma
id|full_list
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|part_next
r_static
r_void
op_star
id|part_next
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
op_assign
(paren
(paren
r_struct
id|gendisk
op_star
)paren
id|v
)paren
op_member_access_from_pointer
id|full_list.next
suffix:semicolon
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|p
op_eq
op_amp
id|gendisk_list
ques
c_cond
l_int|NULL
suffix:colon
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|gendisk
comma
id|full_list
)paren
suffix:semicolon
)brace
DECL|function|part_stop
r_static
r_void
id|part_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
r_void
op_star
id|v
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
)brace
DECL|function|show_partition
r_static
r_int
id|show_partition
c_func
(paren
r_struct
id|seq_file
op_star
id|part
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|gendisk
op_star
id|sgp
op_assign
id|v
suffix:semicolon
r_int
id|n
suffix:semicolon
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|sgp-&gt;full_list
op_eq
id|gendisk_list.next
)paren
id|seq_puts
c_func
(paren
id|part
comma
l_string|&quot;major minor  #blocks  name&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t show non-partitionable devices or empty devices */
r_if
c_cond
(paren
op_logical_neg
id|get_capacity
c_func
(paren
id|sgp
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* show the full disk and all non-0 size partitions of it */
id|seq_printf
c_func
(paren
id|part
comma
l_string|&quot;%4d  %4d %10ld %s&bslash;n&quot;
comma
id|sgp-&gt;major
comma
id|sgp-&gt;first_minor
comma
id|get_capacity
c_func
(paren
id|sgp
)paren
op_rshift
l_int|1
comma
id|disk_name
c_func
(paren
id|sgp
comma
l_int|0
comma
id|buf
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
(paren
l_int|1
op_lshift
id|sgp-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sgp-&gt;part
(braket
id|n
)braket
dot
id|nr_sects
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|seq_printf
c_func
(paren
id|part
comma
l_string|&quot;%4d  %4d %10ld %s&bslash;n&quot;
comma
id|sgp-&gt;major
comma
id|n
op_plus
l_int|1
op_plus
id|sgp-&gt;first_minor
comma
id|sgp-&gt;part
(braket
id|n
)braket
dot
id|nr_sects
op_rshift
l_int|1
comma
id|disk_name
c_func
(paren
id|sgp
comma
id|n
op_plus
l_int|1
comma
id|buf
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|partitions_op
r_struct
id|seq_operations
id|partitions_op
op_assign
(brace
id|start
suffix:colon
id|part_start
comma
id|next
suffix:colon
id|part_next
comma
id|stop
suffix:colon
id|part_stop
comma
id|show
suffix:colon
id|show_partition
)brace
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|blk_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|soc_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atmdev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpqarray_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|disk_devclass
r_struct
id|device_class
id|disk_devclass
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;disk&quot;
comma
)brace
suffix:semicolon
DECL|function|device_init
r_int
id|__init
id|device_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|gendisk_lock
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
id|MAX_BLKDEV
suffix:semicolon
id|i
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|gendisks
(braket
id|i
)braket
dot
id|list
)paren
suffix:semicolon
id|blk_dev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FC4_SOC
multiline_comment|/* This has to be done before scsi_dev_init */
id|soc_probe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_CPQ_DA
id|cpqarray_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM
(paren
r_void
)paren
id|atmdev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|devclass_register
c_func
(paren
op_amp
id|disk_devclass
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|device_init
id|__initcall
c_func
(paren
id|device_init
)paren
suffix:semicolon
DECL|variable|disk_devclass
id|EXPORT_SYMBOL
c_func
(paren
id|disk_devclass
)paren
suffix:semicolon
eof
