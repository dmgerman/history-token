multiline_comment|/*&n; *  fs/partitions/check.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *  Re-organised Feb 1998 Russell King&n; *&n; *  We now have independent partition support from the&n; *  block drivers, which allows all the partition code to&n; *  be grouped in one location, and it to be mostly self&n; *  contained.&n; *&n; *  Added needed MAJORS for new pairs, {hdi,hdj}, {hdk,hdl}&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
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
macro_line|#if CONFIG_BLK_DEV_MD
r_extern
r_void
id|md_autodetect_dev
c_func
(paren
id|dev_t
id|dev
)paren
suffix:semicolon
macro_line|#endif
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
id|parsed_partitions
op_star
comma
r_struct
id|block_device
op_star
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
multiline_comment|/*&n; * disk_name() is used by partition check code and the md driver.&n; * It formats the devicename of the indicated disk into&n; * the supplied buffer (of size at least 32), and returns&n; * a pointer to that same buffer (for convenience).&n; */
DECL|function|disk_name
r_char
op_star
id|disk_name
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|part
comma
r_char
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|part
OL
l_int|1
op_lshift
id|hd-&gt;minor_shift
op_logical_and
id|hd-&gt;part
(braket
id|part
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
c_func
(paren
id|hd-&gt;part
(braket
id|part
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
r_if
c_cond
(paren
op_logical_neg
id|part
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&quot;
comma
id|hd-&gt;major_name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|hd-&gt;major_name
(braket
id|strlen
c_func
(paren
id|hd-&gt;major_name
)paren
op_minus
l_int|1
)braket
)paren
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%sp%d&quot;
comma
id|hd-&gt;major_name
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
l_string|&quot;%s%d&quot;
comma
id|hd-&gt;major_name
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/* Driverfs file support */
DECL|function|partition_device_kdev_read
r_static
id|ssize_t
id|partition_device_kdev_read
c_func
(paren
r_struct
id|device
op_star
id|driverfs_dev
comma
r_char
op_star
id|page
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
id|kdev_t
id|kdev
suffix:semicolon
id|kdev.value
op_assign
(paren
r_int
)paren
(paren
r_int
)paren
id|driverfs_dev-&gt;driver_data
suffix:semicolon
r_return
id|off
ques
c_cond
l_int|0
suffix:colon
id|sprintf
(paren
id|page
comma
l_string|&quot;%x&bslash;n&quot;
comma
id|kdev.value
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|kdev
comma
id|S_IRUGO
comma
id|partition_device_kdev_read
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|partition_device_type_read
r_static
id|ssize_t
id|partition_device_type_read
c_func
(paren
r_struct
id|device
op_star
id|driverfs_dev
comma
r_char
op_star
id|page
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_return
id|off
ques
c_cond
l_int|0
suffix:colon
id|sprintf
(paren
id|page
comma
l_string|&quot;BLK&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|type
comma
id|S_IRUGO
comma
id|partition_device_type_read
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|driverfs_create_partitions
r_static
r_void
id|driverfs_create_partitions
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
)paren
(brace
r_int
id|max_p
op_assign
l_int|1
op_lshift
id|hd-&gt;minor_shift
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
op_assign
id|hd-&gt;part
suffix:semicolon
r_char
id|name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
r_char
id|bus_id
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
r_struct
id|device
op_star
id|dev
comma
op_star
id|parent
suffix:semicolon
r_int
id|part
suffix:semicolon
multiline_comment|/* if driverfs not supported by subsystem, skip partitions */
r_if
c_cond
(paren
op_logical_neg
(paren
id|hd-&gt;flags
op_amp
id|GENHD_FL_DRIVERFS
)paren
)paren
r_return
suffix:semicolon
id|parent
op_assign
id|hd-&gt;driverfs_dev
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s&quot;
comma
id|parent-&gt;name
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|bus_id
comma
l_string|&quot;%s:&quot;
comma
id|parent-&gt;bus_id
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|name
op_assign
op_star
id|bus_id
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
id|dev
op_assign
op_amp
id|p
(braket
l_int|0
)braket
dot
id|hd_driverfs_dev
suffix:semicolon
id|dev-&gt;driver_data
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|__mkdev
c_func
(paren
id|hd-&gt;major
comma
id|hd-&gt;first_minor
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;%sdisc&quot;
comma
id|name
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;bus_id
comma
l_string|&quot;%sdisc&quot;
comma
id|bus_id
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
op_logical_neg
id|p
(braket
id|part
)braket
dot
id|nr_sects
)paren
r_continue
suffix:semicolon
id|dev
op_assign
op_amp
id|p
(braket
id|part
)braket
dot
id|hd_driverfs_dev
suffix:semicolon
id|dev-&gt;driver_data
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|__mkdev
c_func
(paren
id|hd-&gt;major
comma
id|hd-&gt;first_minor
op_plus
id|part
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;%spart%d&quot;
comma
id|name
comma
id|part
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;bus_id
comma
l_string|&quot;%s:p%d&quot;
comma
id|bus_id
comma
id|part
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|part
op_assign
l_int|0
suffix:semicolon
id|part
OL
id|max_p
suffix:semicolon
id|part
op_increment
)paren
(brace
id|dev
op_assign
op_amp
id|p
(braket
id|part
)braket
dot
id|hd_driverfs_dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;driver_data
)paren
r_continue
suffix:semicolon
id|dev-&gt;parent
op_assign
id|parent
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|dev-&gt;bus
op_assign
id|parent-&gt;bus
suffix:semicolon
id|device_register
c_func
(paren
id|dev
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_type
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_kdev
)paren
suffix:semicolon
)brace
)brace
DECL|function|driverfs_remove_partitions
r_void
id|driverfs_remove_partitions
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
)paren
(brace
r_int
id|max_p
op_assign
l_int|1
op_lshift
id|hd-&gt;minor_shift
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
suffix:semicolon
r_int
id|part
suffix:semicolon
r_for
c_loop
(paren
id|part
op_assign
l_int|0
comma
id|p
op_assign
id|hd-&gt;part
suffix:semicolon
id|part
OL
id|max_p
suffix:semicolon
id|part
op_increment
comma
id|p
op_increment
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|p-&gt;hd_driverfs_dev
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver_data
)paren
(brace
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_type
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_kdev
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;driver_data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;DON&squot;T EXPORT&n; */
DECL|function|check_partition
r_void
id|check_partition
c_func
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
)paren
(brace
id|devfs_handle_t
id|de
op_assign
l_int|NULL
suffix:semicolon
id|dev_t
id|dev
op_assign
id|bdev-&gt;bd_dev
suffix:semicolon
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_struct
id|parsed_partitions
op_star
id|state
suffix:semicolon
r_int
id|i
suffix:semicolon
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|parsed_partitions
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|hd-&gt;de_arr
)paren
id|de
op_assign
id|hd-&gt;de_arr
(braket
l_int|0
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
(brace
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
id|sprintf
c_func
(paren
id|state-&gt;name
comma
l_string|&quot;p&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|disk_name
c_func
(paren
id|hd
comma
l_int|0
comma
id|state-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; %s:&quot;
comma
id|state-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|state-&gt;name
(braket
id|strlen
c_func
(paren
id|state-&gt;name
)paren
op_minus
l_int|1
)braket
)paren
)paren
id|sprintf
c_func
(paren
id|state-&gt;name
comma
l_string|&quot;p&quot;
)paren
suffix:semicolon
)brace
id|state-&gt;limit
op_assign
l_int|1
op_lshift
id|hd-&gt;minor_shift
suffix:semicolon
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
comma
id|j
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|state-&gt;parts
comma
l_int|0
comma
r_sizeof
(paren
id|state-&gt;parts
)paren
)paren
suffix:semicolon
id|res
op_assign
id|check_part
(braket
id|i
)braket
(paren
id|state
comma
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|warn_no_part
)paren
id|printk
c_func
(paren
l_string|&quot; unable to read partition table&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|p
op_assign
id|hd-&gt;part
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|state-&gt;limit
suffix:semicolon
id|j
op_increment
)paren
(brace
id|p
(braket
id|j
)braket
dot
id|start_sect
op_assign
id|state-&gt;parts
(braket
id|j
)braket
dot
id|from
suffix:semicolon
id|p
(braket
id|j
)braket
dot
id|nr_sects
op_assign
id|state-&gt;parts
(braket
id|j
)braket
dot
id|size
suffix:semicolon
macro_line|#if CONFIG_BLK_DEV_MD
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;parts
(braket
id|j
)braket
dot
id|flags
)paren
r_continue
suffix:semicolon
id|md_autodetect_dev
c_func
(paren
id|dev
op_plus
id|j
)paren
suffix:semicolon
macro_line|#endif
)brace
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; unknown partition table&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
id|driverfs_create_partitions
c_func
(paren
id|hd
)paren
suffix:semicolon
id|devfs_register_partitions
c_func
(paren
id|hd
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|function|devfs_register_partition
r_static
r_void
id|devfs_register_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
comma
r_int
id|part
)paren
(brace
id|devfs_handle_t
id|dir
suffix:semicolon
r_int
r_int
id|devfs_flags
op_assign
id|DEVFS_FL_DEFAULT
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
op_assign
id|dev-&gt;part
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
id|p
(braket
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
c_func
(paren
id|p
(braket
l_int|0
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
op_amp
id|GENHD_FL_REMOVABLE
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
id|p
(braket
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
id|dev-&gt;first_minor
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
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
(brace
r_int
id|pos
op_assign
l_int|0
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
r_struct
id|hd_struct
op_star
id|p
op_assign
id|dev-&gt;part
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|0
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
op_amp
id|GENHD_FL_REMOVABLE
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
l_int|0
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
c_func
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
c_func
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
c_func
(paren
id|dirname
comma
l_string|&quot;../%s/disc%d&quot;
comma
id|dev-&gt;major_name
comma
id|dev-&gt;first_minor
op_rshift
id|dev-&gt;minor_shift
)paren
suffix:semicolon
id|dir
op_assign
id|devfs_mk_dir
c_func
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
c_func
(paren
l_int|NULL
comma
l_string|&quot;discs&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|p
(braket
l_int|0
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
c_func
(paren
id|symlink
comma
l_string|&quot;disc%d&quot;
comma
id|p
(braket
l_int|0
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
id|p
(braket
l_int|0
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
id|dev-&gt;first_minor
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
c_func
(paren
id|p
(braket
l_int|0
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
id|unregister
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
r_int
id|part
comma
id|max_p
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
op_assign
id|dev-&gt;part
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unregister
)paren
id|devfs_register_disc
c_func
(paren
id|dev
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
id|p
(braket
id|part
)braket
dot
id|nr_sects
OL
l_int|1
)paren
)paren
(brace
id|devfs_unregister
c_func
(paren
id|p
(braket
id|part
)braket
dot
id|de
)paren
suffix:semicolon
id|p
(braket
id|part
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
c_func
(paren
id|dev
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
c_func
(paren
id|p
(braket
l_int|0
)braket
dot
id|de
)paren
suffix:semicolon
id|p
(braket
l_int|0
)braket
dot
id|de
op_assign
l_int|NULL
suffix:semicolon
id|devfs_dealloc_unique_number
c_func
(paren
op_amp
id|disc_numspace
comma
id|p
(braket
l_int|0
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
id|g
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
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_struct
id|hd_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|g
)paren
r_return
suffix:semicolon
id|p
op_assign
id|g-&gt;part
suffix:semicolon
id|p
(braket
l_int|0
)braket
dot
id|nr_sects
op_assign
id|size
suffix:semicolon
multiline_comment|/* No minors to use for partitions */
r_if
c_cond
(paren
op_logical_neg
id|g-&gt;minor_shift
)paren
r_return
suffix:semicolon
multiline_comment|/* No such device (e.g., media were just removed) */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
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
r_if
c_cond
(paren
id|blkdev_get
c_func
(paren
id|bdev
comma
id|FMODE_READ
comma
l_int|0
comma
id|BDEV_RAW
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|check_partition
c_func
(paren
id|g
comma
id|bdev
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_RAW
)paren
suffix:semicolon
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
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_int
id|max_p
op_assign
l_int|1
op_lshift
id|disk-&gt;minor_shift
suffix:semicolon
r_int
id|p
suffix:semicolon
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
id|kdev_t
id|devp
op_assign
id|mk_kdev
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
op_plus
id|p
)paren
suffix:semicolon
r_int
id|res
suffix:semicolon
macro_line|#if 0&t;&t;&t;&t;&t;/* %%% superfluous? */
r_if
c_cond
(paren
id|disk-&gt;part
(braket
id|p
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
id|disk-&gt;part
(braket
id|p
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
id|disk-&gt;part
(braket
id|p
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
eof
