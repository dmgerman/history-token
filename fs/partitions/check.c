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
r_int
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|part
)paren
(brace
r_if
c_cond
(paren
id|hd-&gt;disk_de
)paren
(brace
id|pos
op_assign
id|devfs_generate_path
c_func
(paren
id|hd-&gt;disk_de
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
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&quot;
comma
id|hd-&gt;disk_name
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hd-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
dot
id|de
)paren
(brace
id|pos
op_assign
id|devfs_generate_path
c_func
(paren
id|hd-&gt;part
(braket
id|part
op_minus
l_int|1
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
id|isdigit
c_func
(paren
id|hd-&gt;disk_name
(braket
id|strlen
c_func
(paren
id|hd-&gt;disk_name
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
id|hd-&gt;disk_name
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
id|hd-&gt;disk_name
comma
id|part
)paren
suffix:semicolon
)brace
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
id|hd-&gt;disk_dev
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
id|dev
op_assign
op_amp
id|p
(braket
id|part
op_minus
l_int|1
)braket
dot
id|hd_driverfs_dev
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
r_if
c_cond
(paren
op_logical_neg
id|p
(braket
id|part
op_minus
l_int|1
)braket
dot
id|nr_sects
)paren
r_continue
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
)brace
id|dev
op_assign
op_amp
id|hd-&gt;disk_dev
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
op_minus
l_int|1
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
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;driver_data
)paren
r_continue
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
r_static
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
id|device
op_star
id|dev
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
l_int|1
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
id|dev
op_assign
op_amp
id|hd-&gt;disk_dev
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
id|hd-&gt;flags
op_amp
id|GENHD_FL_DEVFS
)paren
id|de
op_assign
id|hd-&gt;de
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
r_return
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
op_minus
l_int|1
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
op_minus
l_int|1
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
id|bdev-&gt;bd_dev
op_plus
id|j
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; unknown partition table&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_DEVFS_FS
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
op_minus
l_int|1
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
id|dev-&gt;disk_de
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
c_func
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
op_minus
l_int|1
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
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|variable|disc_numspace
r_static
r_struct
id|unique_numspace
id|disc_numspace
op_assign
id|UNIQUE_NUMBERSPACE_INITIALISER
suffix:semicolon
DECL|variable|cdroms
r_static
id|devfs_handle_t
id|cdroms
suffix:semicolon
DECL|variable|cdrom_numspace
r_static
r_struct
id|unique_numspace
id|cdrom_numspace
op_assign
id|UNIQUE_NUMBERSPACE_INITIALISER
suffix:semicolon
macro_line|#endif
DECL|function|devfs_create_partitions
r_static
r_void
id|devfs_create_partitions
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
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
r_int
id|part
comma
id|max_p
op_assign
l_int|1
op_lshift
id|dev-&gt;minor_shift
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
id|dev-&gt;flags
op_amp
id|GENHD_FL_DEVFS
)paren
(brace
id|dir
op_assign
id|dev-&gt;de
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
id|dev-&gt;disk_name
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
id|dev-&gt;number
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
id|dev-&gt;number
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
id|dev-&gt;disk_de
op_assign
id|devfs_register
c_func
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
id|dev-&gt;disk_de
comma
id|slave
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;flags
op_amp
id|GENHD_FL_DEVFS
)paren
)paren
id|devfs_auto_unregister
(paren
id|slave
comma
id|dir
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
comma
id|p
op_increment
)paren
r_if
c_cond
(paren
id|p-&gt;nr_sects
)paren
id|devfs_register_partition
c_func
(paren
id|dev
comma
id|part
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|devfs_create_cdrom
r_static
r_void
id|devfs_create_cdrom
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
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
r_char
id|vname
(braket
l_int|23
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdroms
)paren
id|cdroms
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;cdroms&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|dev-&gt;number
op_assign
id|devfs_alloc_unique_number
c_func
(paren
op_amp
id|cdrom_numspace
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|vname
comma
l_string|&quot;cdrom%d&quot;
comma
id|dev-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;de
)paren
(brace
r_int
id|pos
suffix:semicolon
id|devfs_handle_t
id|slave
suffix:semicolon
r_char
id|rname
(braket
l_int|64
)braket
suffix:semicolon
id|dev-&gt;disk_de
op_assign
id|devfs_register
c_func
(paren
id|dev-&gt;de
comma
l_string|&quot;cd&quot;
comma
id|DEVFS_FL_DEFAULT
comma
id|dev-&gt;major
comma
id|dev-&gt;first_minor
comma
id|S_IFBLK
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
id|dev-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
id|pos
op_assign
id|devfs_generate_path
c_func
(paren
id|dev-&gt;disk_de
comma
id|rname
op_plus
l_int|3
comma
r_sizeof
(paren
id|rname
)paren
op_minus
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
l_int|0
)paren
(brace
id|strncpy
c_func
(paren
id|rname
op_plus
id|pos
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
suffix:semicolon
id|devfs_mk_symlink
c_func
(paren
id|cdroms
comma
id|vname
comma
id|DEVFS_FL_DEFAULT
comma
id|rname
op_plus
id|pos
comma
op_amp
id|slave
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_auto_unregister
c_func
(paren
id|dev-&gt;de
comma
id|slave
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|dev-&gt;disk_de
op_assign
id|devfs_register
(paren
l_int|NULL
comma
id|vname
comma
id|DEVFS_FL_DEFAULT
comma
id|dev-&gt;major
comma
id|dev-&gt;first_minor
comma
id|S_IFBLK
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
id|dev-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|devfs_remove_partitions
r_static
r_void
id|devfs_remove_partitions
c_func
(paren
r_struct
id|gendisk
op_star
id|dev
)paren
(brace
macro_line|#ifdef CONFIG_DEVFS_FS
r_int
id|part
suffix:semicolon
r_for
c_loop
(paren
id|part
op_assign
(paren
l_int|1
op_lshift
id|dev-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
id|part
op_decrement
suffix:semicolon
)paren
(brace
id|devfs_unregister
c_func
(paren
id|dev-&gt;part
(braket
id|part
)braket
dot
id|de
)paren
suffix:semicolon
id|dev-&gt;part
(braket
id|part
)braket
dot
id|de
op_assign
l_int|NULL
suffix:semicolon
)brace
id|devfs_unregister
c_func
(paren
id|dev-&gt;disk_de
)paren
suffix:semicolon
id|dev-&gt;disk_de
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|GENHD_FL_CD
)paren
id|devfs_dealloc_unique_number
c_func
(paren
op_amp
id|cdrom_numspace
comma
id|dev-&gt;number
)paren
suffix:semicolon
r_else
id|devfs_dealloc_unique_number
c_func
(paren
op_amp
id|disc_numspace
comma
id|dev-&gt;number
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Not exported, helper to add_disk(). */
DECL|function|register_disk
r_void
id|register_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_if
c_cond
(paren
id|disk-&gt;flags
op_amp
id|GENHD_FL_CD
)paren
id|devfs_create_cdrom
c_func
(paren
id|disk
)paren
suffix:semicolon
multiline_comment|/* No minors to use for partitions */
r_if
c_cond
(paren
op_logical_neg
id|disk-&gt;minor_shift
)paren
r_return
suffix:semicolon
multiline_comment|/* No such device (e.g., media were just removed) */
r_if
c_cond
(paren
op_logical_neg
id|get_capacity
c_func
(paren
id|disk
)paren
)paren
r_return
suffix:semicolon
id|bdev
op_assign
id|bdget
c_func
(paren
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
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
id|disk
comma
id|bdev
)paren
suffix:semicolon
id|driverfs_create_partitions
c_func
(paren
id|disk
)paren
suffix:semicolon
id|devfs_create_partitions
c_func
(paren
id|disk
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
DECL|function|update_partition
r_void
id|update_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_int
id|part
)paren
(brace
r_struct
id|hd_struct
op_star
id|p
op_assign
id|disk-&gt;part
op_plus
id|part
op_minus
l_int|1
suffix:semicolon
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
op_logical_neg
id|p-&gt;nr_sects
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;de
)paren
(brace
id|devfs_unregister
c_func
(paren
id|p-&gt;de
)paren
suffix:semicolon
id|p-&gt;de
op_assign
l_int|NULL
suffix:semicolon
)brace
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
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;de
)paren
id|devfs_register_partition
c_func
(paren
id|disk
comma
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver_data
op_logical_or
op_logical_neg
(paren
id|disk-&gt;flags
op_amp
id|GENHD_FL_DRIVERFS
)paren
)paren
r_return
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
id|disk-&gt;major
comma
id|disk-&gt;first_minor
op_plus
id|part
)paren
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
DECL|function|rescan_partitions
r_int
id|rescan_partitions
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
id|kdev_t
id|dev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
r_int
id|p
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_invalidated
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_part_count
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|res
op_assign
id|invalidate_device
c_func
(paren
id|dev
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
id|bdev-&gt;bd_invalidated
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
(paren
l_int|1
op_lshift
id|disk-&gt;minor_shift
)paren
op_minus
l_int|1
suffix:semicolon
id|p
op_increment
)paren
(brace
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
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;revalidate
)paren
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|revalidate
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_capacity
c_func
(paren
id|disk
)paren
)paren
id|check_partition
c_func
(paren
id|disk
comma
id|bdev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|1
suffix:semicolon
id|p
OL
(paren
l_int|1
op_lshift
id|disk-&gt;minor_shift
)paren
suffix:semicolon
id|p
op_increment
)paren
id|update_partition
c_func
(paren
id|disk
comma
id|p
)paren
suffix:semicolon
r_return
id|res
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
id|sector_t
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
(paren
id|pgoff_t
)paren
(paren
id|n
op_rshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
l_int|9
)paren
)paren
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
(paren
(paren
id|n
op_amp
(paren
(paren
l_int|1
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
l_int|9
)paren
)paren
op_minus
l_int|1
)paren
)paren
op_lshift
l_int|9
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
r_static
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
id|kdev_t
id|devp
suffix:semicolon
r_int
id|res
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
OG
l_int|0
suffix:semicolon
id|p
op_decrement
)paren
(brace
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
macro_line|#if 0&t;&t;&t;&t;&t;/* %%% superfluous? */
r_if
c_cond
(paren
id|disk-&gt;part
(braket
id|p
op_minus
l_int|1
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
op_minus
l_int|1
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
id|disk-&gt;part
(braket
id|p
op_minus
l_int|1
)braket
dot
id|nr_sects
op_assign
l_int|0
suffix:semicolon
)brace
id|devp
op_assign
id|mk_kdev
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
)paren
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
id|disk-&gt;capacity
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|del_gendisk
r_void
id|del_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
id|driverfs_remove_partitions
c_func
(paren
id|disk
)paren
suffix:semicolon
id|wipe_partitions
c_func
(paren
id|disk
)paren
suffix:semicolon
id|unlink_gendisk
c_func
(paren
id|disk
)paren
suffix:semicolon
id|devfs_remove_partitions
c_func
(paren
id|disk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk-&gt;part
)paren
(brace
id|kfree
c_func
(paren
id|disk-&gt;part
)paren
suffix:semicolon
id|disk-&gt;part
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|struct|dev_name
r_struct
id|dev_name
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|namebuf
r_char
id|namebuf
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|device_names
)paren
suffix:semicolon
DECL|function|partition_name
r_char
op_star
id|partition_name
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|gendisk
op_star
id|hd
suffix:semicolon
r_static
r_char
id|nomem
(braket
)braket
op_assign
l_string|&quot;&lt;nomem&gt;&quot;
suffix:semicolon
r_struct
id|dev_name
op_star
id|dname
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_int
id|part
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|device_names
)paren
(brace
id|dname
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|dev_name
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dname-&gt;dev
op_eq
id|dev
)paren
r_return
id|dname-&gt;name
suffix:semicolon
)brace
id|dname
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dname
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dname
)paren
r_return
id|nomem
suffix:semicolon
multiline_comment|/*&n;&t; * ok, add this new device name to the list&n;&t; */
id|hd
op_assign
id|get_gendisk
c_func
(paren
id|dev
comma
op_amp
id|part
)paren
suffix:semicolon
id|dname-&gt;name
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|hd
)paren
id|dname-&gt;name
op_assign
id|disk_name
c_func
(paren
id|hd
comma
id|part
comma
id|dname-&gt;namebuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dname-&gt;name
)paren
(brace
id|sprintf
c_func
(paren
id|dname-&gt;namebuf
comma
l_string|&quot;[dev %s]&quot;
comma
id|kdevname
c_func
(paren
id|to_kdev_t
c_func
(paren
id|dev
)paren
)paren
)paren
suffix:semicolon
id|dname-&gt;name
op_assign
id|dname-&gt;namebuf
suffix:semicolon
)brace
id|dname-&gt;dev
op_assign
id|dev
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|dname-&gt;list
comma
op_amp
id|device_names
)paren
suffix:semicolon
r_return
id|dname-&gt;name
suffix:semicolon
)brace
eof
