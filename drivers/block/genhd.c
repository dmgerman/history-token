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
DECL|variable|gendisk_lock
r_static
id|rwlock_t
id|gendisk_lock
suffix:semicolon
multiline_comment|/*&n; * Global kernel list of partitioning information.&n; */
DECL|variable|gendisk_head
r_static
r_struct
id|gendisk
op_star
id|gendisk_head
suffix:semicolon
multiline_comment|/**&n; * add_gendisk - add partitioning information to kernel list&n; * @gp: per-device partitioning information&n; *&n; * This function registers the partitioning information in @gp&n; * with the kernel.&n; */
r_void
DECL|function|add_gendisk
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
id|gendisk
op_star
id|sgp
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
multiline_comment|/*&n; &t; *&t;In 2.5 this will go away. Fix the drivers who rely on&n; &t; *&t;old behaviour.&n; &t; */
r_for
c_loop
(paren
id|sgp
op_assign
id|gendisk_head
suffix:semicolon
id|sgp
suffix:semicolon
id|sgp
op_assign
id|sgp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|sgp
op_eq
id|gp
)paren
(brace
singleline_comment|//&t;&t;&t;printk(KERN_ERR &quot;add_gendisk: device major %d is buggy and added a live gendisk!&bslash;n&quot;,
singleline_comment|//&t;&t;&t;&t;sgp-&gt;major)
r_goto
id|out
suffix:semicolon
)brace
)brace
id|gp-&gt;next
op_assign
id|gendisk_head
suffix:semicolon
id|gendisk_head
op_assign
id|gp
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
)brace
DECL|variable|add_gendisk
id|EXPORT_SYMBOL
c_func
(paren
id|add_gendisk
)paren
suffix:semicolon
multiline_comment|/**&n; * del_gendisk - remove partitioning information from kernel list&n; * @gp: per-device partitioning information&n; *&n; * This function unregisters the partitioning information in @gp&n; * with the kernel.&n; */
r_void
DECL|function|del_gendisk
id|del_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|gp
)paren
(brace
r_struct
id|gendisk
op_star
op_star
id|gpp
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|gpp
op_assign
op_amp
id|gendisk_head
suffix:semicolon
op_star
id|gpp
suffix:semicolon
id|gpp
op_assign
op_amp
(paren
(paren
op_star
id|gpp
)paren
op_member_access_from_pointer
id|next
)paren
)paren
r_if
c_cond
(paren
op_star
id|gpp
op_eq
id|gp
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|gpp
)paren
op_star
id|gpp
op_assign
(paren
op_star
id|gpp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
)brace
DECL|variable|del_gendisk
id|EXPORT_SYMBOL
c_func
(paren
id|del_gendisk
)paren
suffix:semicolon
multiline_comment|/**&n; * get_gendisk - get partitioning information for a given device&n; * @dev: device to get partitioning information for&n; *&n; * This function gets the structure containing partitioning&n; * information for the given device @dev.&n; */
r_struct
id|gendisk
op_star
DECL|function|get_gendisk
id|get_gendisk
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|gendisk
op_star
id|gp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|maj
op_assign
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|gp
op_assign
id|gendisk_head
suffix:semicolon
id|gp
suffix:semicolon
id|gp
op_assign
id|gp-&gt;next
)paren
r_if
c_cond
(paren
id|gp-&gt;major
op_eq
id|maj
)paren
r_break
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_return
id|gp
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
id|loff_t
id|k
op_assign
op_star
id|pos
suffix:semicolon
r_struct
id|gendisk
op_star
id|sgp
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sgp
op_assign
id|gendisk_head
suffix:semicolon
id|sgp
suffix:semicolon
id|sgp
op_assign
id|sgp-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|k
op_decrement
)paren
r_return
id|sgp
suffix:semicolon
)brace
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
op_increment
op_star
id|pos
suffix:semicolon
r_return
(paren
(paren
r_struct
id|gendisk
op_star
)paren
id|v
)paren
op_member_access_from_pointer
id|next
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
id|sgp
op_eq
id|gendisk_head
)paren
id|seq_puts
c_func
(paren
id|part
comma
l_string|&quot;major minor  #blocks  name&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* show the full disk and all non-0 size partitions of it */
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
id|sgp-&gt;nr_real
op_lshift
id|sgp-&gt;minor_shift
)paren
suffix:semicolon
id|n
op_increment
)paren
(brace
r_int
id|minormask
op_assign
(paren
l_int|1
op_lshift
id|sgp-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_amp
id|minormask
)paren
op_logical_and
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
l_string|&quot;%4d  %4d %10d %s&bslash;n&quot;
comma
id|sgp-&gt;major
comma
id|n
comma
id|sgp-&gt;sizes
(braket
id|n
)braket
comma
id|disk_name
c_func
(paren
id|sgp
comma
id|n
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
DECL|function|device_init
r_int
id|__init
id|device_init
c_func
(paren
r_void
)paren
(brace
id|rwlock_init
c_func
(paren
op_amp
id|gendisk_lock
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
eof
