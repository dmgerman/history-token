multiline_comment|/*&n; *  fs/partitions/check.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *  Re-organised Feb 1998 Russell King&n; *&n; *  We now have independent partition support from the&n; *  block drivers, which allows all the partition code to&n; *  be grouped in one location, and it to be mostly self&n; *  contained.&n; *&n; *  Added needed MAJORS for new pairs, {hdi,hdj}, {hdk,hdl}&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;acorn.h&quot;
macro_line|#include &quot;amiga.h&quot;
macro_line|#include &quot;atari.h&quot;
macro_line|#include &quot;ldm.h&quot;
macro_line|#include &quot;mac.h&quot;
macro_line|#include &quot;msdos.h&quot;
macro_line|#include &quot;osf.h&quot;
macro_line|#include &quot;sgi.h&quot;
macro_line|#include &quot;sun.h&quot;
macro_line|#include &quot;ibm.h&quot;
macro_line|#include &quot;ultrix.h&quot;
macro_line|#include &quot;efi.h&quot;
DECL|variable|warn_no_part
r_int
id|warn_no_part
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*This is ugly: should make genhd removable media aware*/
DECL|variable|check_part
r_static
r_int
(paren
op_star
id|check_part
(braket
)braket
)paren
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|first_sect
comma
r_int
id|first_minor
)paren
op_assign
(brace
macro_line|#ifdef CONFIG_ACORN_PARTITION
id|acorn_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EFI_PARTITION
id|efi_partition
comma
multiline_comment|/* this must come before msdos */
macro_line|#endif
macro_line|#ifdef CONFIG_LDM_PARTITION
id|ldm_partition
comma
multiline_comment|/* this must come before msdos */
macro_line|#endif
macro_line|#ifdef CONFIG_MSDOS_PARTITION
id|msdos_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_OSF_PARTITION
id|osf_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUN_PARTITION
id|sun_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGA_PARTITION
id|amiga_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI_PARTITION
id|atari_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MAC_PARTITION
id|mac_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_PARTITION
id|sgi_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ULTRIX_PARTITION
id|ultrix_partition
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IBM_PARTITION
id|ibm_partition
comma
macro_line|#endif
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;This is ucking fugly but its probably the best thing for 2.4.x&n; *&t;Take it as a clear reminder than we should put the device name&n; *&t;generation in the object kdev_t points to in 2.5.&n; */
macro_line|#ifdef CONFIG_ARCH_S390
DECL|variable|genhd_dasd_name
r_int
(paren
op_star
id|genhd_dasd_name
)paren
(paren
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|gendisk
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|genhd_dasd_name
id|EXPORT_SYMBOL
c_func
(paren
id|genhd_dasd_name
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * disk_name() is used by partition check code and the md driver.&n; * It formats the devicename of the indicated disk into&n; * the supplied buffer (of size at least 32), and returns&n; * a pointer to that same buffer (for convenience).&n; */
DECL|function|disk_name
r_char
op_star
id|disk_name
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_char
op_star
id|buf
)paren
(brace
r_const
r_char
op_star
id|maj
op_assign
id|hd-&gt;major_name
suffix:semicolon
r_int
r_int
id|unit
op_assign
(paren
id|minor
op_rshift
id|hd-&gt;minor_shift
)paren
suffix:semicolon
r_int
r_int
id|part
op_assign
(paren
id|minor
op_amp
(paren
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|unit
OL
id|hd-&gt;nr_real
)paren
op_logical_and
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|de
)paren
(brace
r_int
id|pos
suffix:semicolon
id|pos
op_assign
id|devfs_generate_path
(paren
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|de
comma
id|buf
comma
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
l_int|0
)paren
r_return
id|buf
op_plus
id|pos
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_S390
r_if
c_cond
(paren
id|genhd_dasd_name
op_logical_and
id|genhd_dasd_name
(paren
id|buf
comma
id|unit
comma
id|part
comma
id|hd
)paren
op_eq
l_int|0
)paren
r_return
id|buf
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * IDE devices use multiple major numbers, but the drives&n;&t; * are named as:  {hda,hdb}, {hdc,hdd}, {hde,hdf}, {hdg,hdh}..&n;&t; * This requires special handling here.&n;&t; */
r_switch
c_cond
(paren
id|hd-&gt;major
)paren
(brace
r_case
id|IDE9_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE8_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE7_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE6_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE5_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE4_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE3_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE2_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE1_MAJOR
suffix:colon
id|unit
op_add_assign
l_int|2
suffix:semicolon
r_case
id|IDE0_MAJOR
suffix:colon
id|maj
op_assign
l_string|&quot;hd&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MD_MAJOR
suffix:colon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s%d&quot;
comma
id|maj
comma
id|unit
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hd-&gt;major
op_ge
id|SCSI_DISK1_MAJOR
op_logical_and
id|hd-&gt;major
op_le
id|SCSI_DISK7_MAJOR
)paren
(brace
id|unit
op_assign
id|unit
op_plus
(paren
id|hd-&gt;major
op_minus
id|SCSI_DISK1_MAJOR
op_plus
l_int|1
)paren
op_star
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_plus
l_char|&squot;a&squot;
OG
l_char|&squot;z&squot;
)paren
(brace
id|unit
op_sub_assign
l_int|26
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;sd%c%c&quot;
comma
l_char|&squot;a&squot;
op_plus
id|unit
op_div
l_int|26
comma
l_char|&squot;a&squot;
op_plus
id|unit
op_mod
l_int|26
)paren
suffix:semicolon
r_if
c_cond
(paren
id|part
)paren
id|sprintf
c_func
(paren
id|buf
op_plus
l_int|4
comma
l_string|&quot;%d&quot;
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hd-&gt;major
op_ge
id|COMPAQ_SMART2_MAJOR
op_logical_and
id|hd-&gt;major
op_le
id|COMPAQ_SMART2_MAJOR
op_plus
l_int|7
)paren
(brace
r_int
id|ctlr
op_assign
id|hd-&gt;major
op_minus
id|COMPAQ_SMART2_MAJOR
suffix:semicolon
r_if
c_cond
(paren
id|part
op_eq
l_int|0
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/c%dd%d&quot;
comma
id|maj
comma
id|ctlr
comma
id|unit
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/c%dd%dp%d&quot;
comma
id|maj
comma
id|ctlr
comma
id|unit
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hd-&gt;major
op_ge
id|COMPAQ_CISS_MAJOR
op_logical_and
id|hd-&gt;major
op_le
id|COMPAQ_CISS_MAJOR
op_plus
l_int|7
)paren
(brace
r_int
id|ctlr
op_assign
id|hd-&gt;major
op_minus
id|COMPAQ_CISS_MAJOR
suffix:semicolon
r_if
c_cond
(paren
id|part
op_eq
l_int|0
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/c%dd%d&quot;
comma
id|maj
comma
id|ctlr
comma
id|unit
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/c%dd%dp%d&quot;
comma
id|maj
comma
id|ctlr
comma
id|unit
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hd-&gt;major
op_ge
id|DAC960_MAJOR
op_logical_and
id|hd-&gt;major
op_le
id|DAC960_MAJOR
op_plus
l_int|7
)paren
(brace
r_int
id|ctlr
op_assign
id|hd-&gt;major
op_minus
id|DAC960_MAJOR
suffix:semicolon
r_if
c_cond
(paren
id|part
op_eq
l_int|0
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/c%dd%d&quot;
comma
id|maj
comma
id|ctlr
comma
id|unit
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/c%dd%dp%d&quot;
comma
id|maj
comma
id|ctlr
comma
id|unit
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hd-&gt;major
op_eq
id|ATARAID_MAJOR
)paren
(brace
r_int
id|disk
op_assign
id|minor
op_rshift
id|hd-&gt;minor_shift
suffix:semicolon
r_int
id|part
op_assign
id|minor
op_amp
(paren
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|part
op_eq
l_int|0
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/d%d&quot;
comma
id|maj
comma
id|disk
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s/d%dp%d&quot;
comma
id|maj
comma
id|disk
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|part
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s%c%d&quot;
comma
id|maj
comma
id|unit
op_plus
l_char|&squot;a&squot;
comma
id|part
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s%c&quot;
comma
id|maj
comma
id|unit
op_plus
l_char|&squot;a&squot;
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a partitions details to the devices partition description.&n; */
DECL|function|add_gd_partition
r_void
id|add_gd_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_int
id|start
comma
r_int
id|size
)paren
(brace
macro_line|#ifndef CONFIG_DEVFS_FS
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
macro_line|#endif
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
op_assign
id|start
suffix:semicolon
id|hd-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
id|size
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|printk
c_func
(paren
l_string|&quot; p%d&quot;
comma
(paren
id|minor
op_amp
(paren
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
(paren
id|hd-&gt;major
op_ge
id|COMPAQ_SMART2_MAJOR
op_plus
l_int|0
op_logical_and
id|hd-&gt;major
op_le
id|COMPAQ_SMART2_MAJOR
op_plus
l_int|7
)paren
op_logical_or
(paren
id|hd-&gt;major
op_ge
id|COMPAQ_CISS_MAJOR
op_plus
l_int|0
op_logical_and
id|hd-&gt;major
op_le
id|COMPAQ_CISS_MAJOR
op_plus
l_int|7
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; p%d&quot;
comma
(paren
id|minor
op_amp
(paren
(paren
l_int|1
op_lshift
id|hd-&gt;minor_shift
)paren
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot; %s&quot;
comma
id|disk_name
c_func
(paren
id|hd
comma
id|minor
comma
id|buf
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|check_partition
r_static
r_void
id|check_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
id|kdev_t
id|dev
comma
r_int
id|first_part_minor
)paren
(brace
id|devfs_handle_t
id|de
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|first_time
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|first_sector
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|first_time
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Partition check:&bslash;n&quot;
)paren
suffix:semicolon
id|first_time
op_assign
l_int|0
suffix:semicolon
id|first_sector
op_assign
id|hd-&gt;part
(braket
id|minor
c_func
(paren
id|dev
)paren
)braket
dot
id|start_sect
suffix:semicolon
multiline_comment|/*&n;&t; * This is a kludge to allow the partition check to be&n;&t; * skipped for specific drives (e.g. IDE CD-ROM drives)&n;&t; */
r_if
c_cond
(paren
(paren
r_int
)paren
id|first_sector
op_eq
op_minus
l_int|1
)paren
(brace
id|hd-&gt;part
(braket
id|minor
c_func
(paren
id|dev
)paren
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hd-&gt;de_arr
)paren
id|de
op_assign
id|hd-&gt;de_arr
(braket
id|minor
c_func
(paren
id|dev
)paren
op_rshift
id|hd-&gt;minor_shift
)braket
suffix:semicolon
id|i
op_assign
id|devfs_generate_path
(paren
id|de
comma
id|buf
comma
r_sizeof
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; /dev/%s:&quot;
comma
id|buf
op_plus
id|i
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; %s:&quot;
comma
id|disk_name
c_func
(paren
id|hd
comma
id|minor
c_func
(paren
id|dev
)paren
comma
id|buf
)paren
)paren
suffix:semicolon
id|bdev
op_assign
id|bdget
c_func
(paren
id|kdev_t_to_nr
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|bdev-&gt;bd_contains
op_assign
id|bdev
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_size
op_assign
(paren
id|loff_t
)paren
id|hd-&gt;part
(braket
id|minor
c_func
(paren
id|dev
)paren
)braket
dot
id|nr_sects
op_lshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_openers
)paren
(brace
r_int
id|bsize
op_assign
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bsize
OL
id|PAGE_CACHE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|bdev-&gt;bd_inode-&gt;i_size
op_amp
id|bsize
)paren
r_break
suffix:semicolon
id|bsize
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|bdev-&gt;bd_block_size
op_assign
id|bsize
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_blkbits
op_assign
id|blksize_bits
c_func
(paren
id|bsize
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|check_part
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|res
suffix:semicolon
id|res
op_assign
id|check_part
(braket
id|i
)braket
(paren
id|hd
comma
id|bdev
comma
id|first_sector
comma
id|first_part_minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
r_if
c_cond
(paren
id|res
OL
l_int|0
op_logical_and
id|warn_no_part
)paren
id|printk
c_func
(paren
l_string|&quot; unable to read partition table&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|setup_devfs
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot; unknown partition table&bslash;n&quot;
)paren
suffix:semicolon
id|setup_devfs
suffix:colon
id|invalidate_bdev
c_func
(paren
id|bdev
comma
l_int|1
)paren
suffix:semicolon
id|truncate_inode_pages
c_func
(paren
id|bdev-&gt;bd_inode-&gt;i_mapping
comma
l_int|0
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|i
op_assign
id|first_part_minor
op_minus
l_int|1
suffix:semicolon
id|devfs_register_partitions
(paren
id|hd
comma
id|i
comma
id|hd-&gt;sizes
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|function|devfs_register_partition
r_static
r_void
id|devfs_register_partition
(paren
r_struct
id|gendisk
op_star
id|dev
comma
r_int
id|minor
comma
r_int
id|part
)paren
(brace
r_int
id|devnum
op_assign
id|minor
op_rshift
id|dev-&gt;minor_shift
suffix:semicolon
id|devfs_handle_t
id|dir
suffix:semicolon
r_int
r_int
id|devfs_flags
op_assign
id|DEVFS_FL_DEFAULT
suffix:semicolon
r_char
id|devname
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;part
(braket
id|minor
op_plus
id|part
)braket
dot
id|de
)paren
r_return
suffix:semicolon
id|dir
op_assign
id|devfs_get_parent
(paren
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|de
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_logical_and
(paren
id|dev-&gt;flags
(braket
id|devnum
)braket
op_amp
id|GENHD_FL_REMOVABLE
)paren
)paren
id|devfs_flags
op_or_assign
id|DEVFS_FL_REMOVABLE
suffix:semicolon
id|sprintf
(paren
id|devname
comma
l_string|&quot;part%d&quot;
comma
id|part
)paren
suffix:semicolon
id|dev-&gt;part
(braket
id|minor
op_plus
id|part
)braket
dot
id|de
op_assign
id|devfs_register
(paren
id|dir
comma
id|devname
comma
id|devfs_flags
comma
id|dev-&gt;major
comma
id|minor
op_plus
id|part
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|dev-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|disc_numspace
r_static
r_struct
id|unique_numspace
id|disc_numspace
op_assign
id|UNIQUE_NUMBERSPACE_INITIALISER
suffix:semicolon
DECL|function|devfs_register_disc
r_static
r_void
id|devfs_register_disc
(paren
r_struct
id|gendisk
op_star
id|dev
comma
r_int
id|minor
)paren
(brace
r_int
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
id|devnum
op_assign
id|minor
op_rshift
id|dev-&gt;minor_shift
suffix:semicolon
id|devfs_handle_t
id|dir
comma
id|slave
suffix:semicolon
r_int
r_int
id|devfs_flags
op_assign
id|DEVFS_FL_DEFAULT
suffix:semicolon
r_char
id|dirname
(braket
l_int|64
)braket
comma
id|symlink
(braket
l_int|16
)braket
suffix:semicolon
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|de
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_logical_and
(paren
id|dev-&gt;flags
(braket
id|devnum
)braket
op_amp
id|GENHD_FL_REMOVABLE
)paren
)paren
id|devfs_flags
op_or_assign
id|DEVFS_FL_REMOVABLE
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;de_arr
)paren
(brace
id|dir
op_assign
id|dev-&gt;de_arr
(braket
id|devnum
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
multiline_comment|/*  Aware driver wants to block disc management  */
r_return
suffix:semicolon
id|pos
op_assign
id|devfs_generate_path
(paren
id|dir
comma
id|dirname
op_plus
l_int|3
comma
r_sizeof
id|dirname
op_minus
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
suffix:semicolon
id|strncpy
(paren
id|dirname
op_plus
id|pos
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*  Unaware driver: construct &quot;real&quot; directory  */
id|sprintf
(paren
id|dirname
comma
l_string|&quot;../%s/disc%d&quot;
comma
id|dev-&gt;major_name
comma
id|devnum
)paren
suffix:semicolon
id|dir
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
id|dirname
op_plus
l_int|3
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|devfs_handle
)paren
id|devfs_handle
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;discs&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|number
op_assign
id|devfs_alloc_unique_number
(paren
op_amp
id|disc_numspace
)paren
suffix:semicolon
id|sprintf
(paren
id|symlink
comma
l_string|&quot;disc%d&quot;
comma
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|number
)paren
suffix:semicolon
id|devfs_mk_symlink
(paren
id|devfs_handle
comma
id|symlink
comma
id|DEVFS_FL_DEFAULT
comma
id|dirname
op_plus
id|pos
comma
op_amp
id|slave
comma
l_int|NULL
)paren
suffix:semicolon
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|de
op_assign
id|devfs_register
(paren
id|dir
comma
l_string|&quot;disc&quot;
comma
id|devfs_flags
comma
id|dev-&gt;major
comma
id|minor
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|dev-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_auto_unregister
(paren
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|de
comma
id|slave
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;de_arr
)paren
id|devfs_auto_unregister
(paren
id|slave
comma
id|dir
)paren
suffix:semicolon
)brace
macro_line|#endif  /*  CONFIG_DEVFS_FS  */
DECL|function|devfs_register_partitions
r_void
id|devfs_register_partitions
(paren
r_struct
id|gendisk
op_star
id|dev
comma
r_int
id|minor
comma
r_int
id|unregister
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
r_int
id|part
comma
id|max_p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unregister
)paren
id|devfs_register_disc
(paren
id|dev
comma
id|minor
)paren
suffix:semicolon
id|max_p
op_assign
(paren
l_int|1
op_lshift
id|dev-&gt;minor_shift
)paren
suffix:semicolon
r_for
c_loop
(paren
id|part
op_assign
l_int|1
suffix:semicolon
id|part
OL
id|max_p
suffix:semicolon
id|part
op_increment
)paren
(brace
r_if
c_cond
(paren
id|unregister
op_logical_or
(paren
id|dev-&gt;part
(braket
id|part
op_plus
id|minor
)braket
dot
id|nr_sects
OL
l_int|1
)paren
)paren
(brace
id|devfs_unregister
(paren
id|dev-&gt;part
(braket
id|part
op_plus
id|minor
)braket
dot
id|de
)paren
suffix:semicolon
id|dev-&gt;part
(braket
id|part
op_plus
id|minor
)braket
dot
id|de
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|devfs_register_partition
(paren
id|dev
comma
id|minor
comma
id|part
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unregister
)paren
(brace
id|devfs_unregister
(paren
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|de
)paren
suffix:semicolon
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|de
op_assign
l_int|NULL
suffix:semicolon
id|devfs_dealloc_unique_number
(paren
op_amp
id|disc_numspace
comma
id|dev-&gt;part
(braket
id|minor
)braket
dot
id|number
)paren
suffix:semicolon
)brace
macro_line|#endif  /*  CONFIG_DEVFS_FS  */
)brace
multiline_comment|/*&n; * This function will re-read the partition tables for a given device,&n; * and set things back up again.  There are some important caveats,&n; * however.  You must ensure that no one is using the device, and no one&n; * can start using the device while this function is being executed.&n; *&n; * Much of the cleanup from the old partition tables should have already been&n; * done&n; */
DECL|function|register_disk
r_void
id|register_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|gdev
comma
id|kdev_t
id|dev
comma
r_int
id|minors
comma
r_struct
id|block_device_operations
op_star
id|ops
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gdev
)paren
r_return
suffix:semicolon
id|grok_partitions
c_func
(paren
id|dev
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|grok_partitions
r_void
id|grok_partitions
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|size
)paren
(brace
r_int
id|i
comma
id|minors
comma
id|first_minor
comma
id|end_minor
suffix:semicolon
r_struct
id|gendisk
op_star
id|g
op_assign
id|get_gendisk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|g
)paren
r_return
suffix:semicolon
id|minors
op_assign
l_int|1
op_lshift
id|g-&gt;minor_shift
suffix:semicolon
id|first_minor
op_assign
id|minor
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_minor
op_amp
(paren
id|minors
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;grok_partitions: bad device 0x%02x:%02x&bslash;n&quot;
comma
id|major
c_func
(paren
id|dev
)paren
comma
id|first_minor
)paren
suffix:semicolon
id|first_minor
op_and_assign
op_complement
(paren
id|minors
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|end_minor
op_assign
id|first_minor
op_plus
id|minors
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|g-&gt;sizes
)paren
id|blk_size
(braket
id|g-&gt;major
)braket
op_assign
l_int|NULL
suffix:semicolon
id|g-&gt;part
(braket
id|first_minor
)braket
dot
id|nr_sects
op_assign
id|size
suffix:semicolon
multiline_comment|/* No such device or no minors to use for partitions */
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|minors
op_eq
l_int|1
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|g-&gt;sizes
)paren
(brace
id|g-&gt;sizes
(braket
id|first_minor
)braket
op_assign
id|size
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first_minor
op_plus
l_int|1
suffix:semicolon
id|i
OL
id|end_minor
suffix:semicolon
id|i
op_increment
)paren
id|g-&gt;sizes
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|blk_size
(braket
id|g-&gt;major
)braket
op_assign
id|g-&gt;sizes
suffix:semicolon
id|check_partition
c_func
(paren
id|g
comma
id|mk_kdev
c_func
(paren
id|g-&gt;major
comma
id|first_minor
)paren
comma
l_int|1
op_plus
id|first_minor
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * We need to set the sizes array before we will be able to access&n; &t; * any of the partitions on this device.&n; &t; */
r_if
c_cond
(paren
id|g-&gt;sizes
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* optional safeguard in ll_rw_blk.c */
r_for
c_loop
(paren
id|i
op_assign
id|first_minor
suffix:semicolon
id|i
OL
id|end_minor
suffix:semicolon
id|i
op_increment
)paren
id|g-&gt;sizes
(braket
id|i
)braket
op_assign
id|g-&gt;part
(braket
id|i
)braket
dot
id|nr_sects
op_rshift
(paren
id|BLOCK_SIZE_BITS
op_minus
l_int|9
)paren
suffix:semicolon
)brace
)brace
DECL|function|read_dev_sector
r_int
r_char
op_star
id|read_dev_sector
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|n
comma
id|Sector
op_star
id|p
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
r_int
id|sect
op_assign
id|PAGE_CACHE_SIZE
op_div
l_int|512
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|n
op_div
id|sect
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|PageError
c_func
(paren
id|page
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|p-&gt;v
op_assign
id|page
suffix:semicolon
r_return
(paren
r_int
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
op_plus
l_int|512
op_star
(paren
id|n
op_mod
id|sect
)paren
suffix:semicolon
id|fail
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|p-&gt;v
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|wipe_partitions
r_int
id|wipe_partitions
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|gendisk
op_star
id|g
suffix:semicolon
id|kdev_t
id|devp
suffix:semicolon
r_int
id|p
comma
id|major
comma
id|minor
comma
id|minor0
comma
id|max_p
comma
id|res
suffix:semicolon
id|g
op_assign
id|get_gendisk
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|g
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|max_p
op_assign
l_int|1
op_lshift
id|g-&gt;minor_shift
suffix:semicolon
id|major
op_assign
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
id|minor
op_assign
id|minor
c_func
(paren
id|dev
)paren
suffix:semicolon
id|minor0
op_assign
id|minor
op_amp
op_complement
(paren
id|max_p
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor0
op_ne
id|minor
)paren
multiline_comment|/* for now only whole-disk reread */
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* %%% later.. */
multiline_comment|/* invalidate stuff */
r_for
c_loop
(paren
id|p
op_assign
id|max_p
op_minus
l_int|1
suffix:semicolon
id|p
op_ge
l_int|0
suffix:semicolon
id|p
op_decrement
)paren
(brace
id|minor
op_assign
id|minor0
op_plus
id|p
suffix:semicolon
id|devp
op_assign
id|mk_kdev
c_func
(paren
id|major
comma
id|minor
)paren
suffix:semicolon
macro_line|#if 0&t;&t;&t;&t;&t;/* %%% superfluous? */
r_if
c_cond
(paren
id|g-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|res
op_assign
id|invalidate_device
c_func
(paren
id|devp
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
id|g-&gt;part
(braket
id|minor
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
id|g-&gt;part
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Make sure that a proposed subpartition is strictly contained inside&n; * the parent partition.  If all is well, call add_gd_partition().&n; */
r_int
DECL|function|check_and_add_subpartition
id|check_and_add_subpartition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|super_minor
comma
r_int
id|minor
comma
r_int
id|sub_start
comma
r_int
id|sub_size
)paren
(brace
r_int
id|start
op_assign
id|hd-&gt;part
(braket
id|super_minor
)braket
dot
id|start_sect
suffix:semicolon
r_int
id|size
op_assign
id|hd-&gt;part
(braket
id|super_minor
)braket
dot
id|nr_sects
suffix:semicolon
r_if
c_cond
(paren
id|start
op_eq
id|sub_start
op_logical_and
id|size
op_eq
id|sub_size
)paren
(brace
multiline_comment|/* full parent partition, we have it already */
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
op_le
id|sub_start
op_logical_and
id|start
op_plus
id|size
op_ge
id|sub_start
op_plus
id|sub_size
)paren
(brace
id|add_gd_partition
c_func
(paren
id|hd
comma
id|minor
comma
id|sub_start
comma
id|sub_size
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;bad subpartition - ignored&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
