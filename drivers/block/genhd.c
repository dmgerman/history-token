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
DECL|variable|gendisk_lock
r_static
id|rwlock_t
id|gendisk_lock
suffix:semicolon
multiline_comment|/*&n; * Global kernel list of partitioning information.&n; *&n; * XXX: you should _never_ access this directly.&n; *&t;the only reason this is exported is source compatiblity.&n; */
DECL|variable|gendisk_head
multiline_comment|/*static*/
r_struct
id|gendisk
op_star
id|gendisk_head
suffix:semicolon
DECL|variable|gendisk_head
id|EXPORT_SYMBOL
c_func
(paren
id|gendisk_head
)paren
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
id|MAJOR
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
r_int
DECL|function|get_partition_list
id|get_partition_list
c_func
(paren
r_char
op_star
id|page
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
)paren
(brace
r_struct
id|gendisk
op_star
id|gp
suffix:semicolon
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|len
comma
id|n
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;major minor  #blocks  name&bslash;n&bslash;n&quot;
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
(brace
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
id|gp-&gt;nr_real
op_lshift
id|gp-&gt;minor_shift
)paren
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|gp-&gt;part
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
id|len
op_add_assign
id|snprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_int|63
comma
l_string|&quot;%4d  %4d %10d %s&bslash;n&quot;
comma
id|gp-&gt;major
comma
id|n
comma
id|gp-&gt;sizes
(braket
id|n
)braket
comma
id|disk_name
c_func
(paren
id|gp
comma
id|n
comma
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|offset
)paren
id|offset
op_sub_assign
id|len
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
op_ge
id|offset
op_plus
id|count
)paren
r_goto
id|out
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|gendisk_lock
)paren
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
OG
id|count
ques
c_cond
id|count
suffix:colon
id|len
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_int
id|blk_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FUSION_BOOT
r_extern
r_int
id|fusion_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|net_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|console_map_init
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
id|i2o_init
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
id|sti
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_I2O
id|i2o_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FUSION_BOOT
id|fusion_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_NET
id|net_dev_init
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
macro_line|#ifdef CONFIG_VT
id|console_map_init
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
