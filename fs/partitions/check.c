multiline_comment|/*&n; *  fs/partitions/check.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *  Re-organised Feb 1998 Russell King&n; *&n; *  We now have independent partition support from the&n; *  block drivers, which allows all the partition code to&n; *  be grouped in one location, and it to be mostly self&n; *  contained.&n; *&n; *  Added needed MAJORS for new pairs, {hdi,hdj}, {hdk,hdl}&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;devfs.h&quot;
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
macro_line|#ifdef CONFIG_BLK_DEV_MD
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
multiline_comment|/*&n;&t; * Probe partition formats with tables at disk address 0&n;&t; * that also have an ADFS boot block at 0xdc0.&n;&t; */
macro_line|#ifdef CONFIG_ACORN_PARTITION_ICS
id|adfspart_check_ICS
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_POWERTEC
id|adfspart_check_POWERTEC
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_EESOX
id|adfspart_check_EESOX
comma
macro_line|#endif
multiline_comment|/*&n;&t; * Now move on to formats that only have partition info at&n;&t; * disk address 0xdc0.  Since these may also have stale&n;&t; * PC/BIOS partition tables, they need to come before&n;&t; * the msdos entry.&n;&t; */
macro_line|#ifdef CONFIG_ACORN_PARTITION_CUMANA
id|adfspart_check_CUMANA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ACORN_PARTITION_ADFS
id|adfspart_check_ADFS
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
macro_line|#ifdef CONFIG_NEC98_PARTITION
id|nec98_partition
comma
multiline_comment|/* must be come before `msdos_partition&squot; */
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
multiline_comment|/*&n; * disk_name() is used by partition check code and the genhd driver.&n; * It formats the devicename of the indicated disk into&n; * the supplied buffer (of size at least 32), and returns&n; * a pointer to that same buffer (for convenience).&n; */
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
op_logical_neg
id|part
)paren
id|snprintf
c_func
(paren
id|buf
comma
id|BDEVNAME_SIZE
comma
l_string|&quot;%s&quot;
comma
id|hd-&gt;disk_name
)paren
suffix:semicolon
r_else
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
id|snprintf
c_func
(paren
id|buf
comma
id|BDEVNAME_SIZE
comma
l_string|&quot;%sp%d&quot;
comma
id|hd-&gt;disk_name
comma
id|part
)paren
suffix:semicolon
r_else
id|snprintf
c_func
(paren
id|buf
comma
id|BDEVNAME_SIZE
comma
l_string|&quot;%s%d&quot;
comma
id|hd-&gt;disk_name
comma
id|part
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|function|bdevname
r_const
r_char
op_star
id|bdevname
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|part
op_assign
id|MINOR
c_func
(paren
id|bdev-&gt;bd_dev
)paren
op_minus
id|bdev-&gt;bd_disk-&gt;first_minor
suffix:semicolon
r_return
id|disk_name
c_func
(paren
id|bdev-&gt;bd_disk
comma
id|part
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|variable|bdevname
id|EXPORT_SYMBOL
c_func
(paren
id|bdevname
)paren
suffix:semicolon
multiline_comment|/*&n; * There&squot;s very little reason to use this, you should really&n; * have a struct block_device just about everywhere and use&n; * bdevname() instead.&n; */
DECL|function|__bdevname
r_const
r_char
op_star
id|__bdevname
c_func
(paren
id|dev_t
id|dev
comma
r_char
op_star
id|buffer
)paren
(brace
id|scnprintf
c_func
(paren
id|buffer
comma
id|BDEVNAME_SIZE
comma
l_string|&quot;unknown-block(%u,%u)&quot;
comma
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|variable|__bdevname
id|EXPORT_SYMBOL
c_func
(paren
id|__bdevname
)paren
suffix:semicolon
r_static
r_struct
id|parsed_partitions
op_star
DECL|function|check_partition
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
r_struct
id|parsed_partitions
op_star
id|state
suffix:semicolon
r_int
id|i
comma
id|res
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
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
r_if
c_cond
(paren
id|hd-&gt;devfs_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; /dev/%s:&quot;
comma
id|hd-&gt;devfs_name
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
macro_line|#endif
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
id|hd-&gt;minors
suffix:semicolon
id|i
op_assign
id|res
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|res
op_logical_and
id|check_part
(braket
id|i
)braket
)paren
(brace
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
op_increment
)braket
(paren
id|state
comma
id|bdev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
OG
l_int|0
)paren
r_return
id|state
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|printk
c_func
(paren
l_string|&quot; unknown partition table&bslash;n&quot;
)paren
suffix:semicolon
r_else
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
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * sysfs bindings for partitions&n; */
DECL|struct|part_attribute
r_struct
id|part_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|hd_struct
op_star
comma
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_static
id|ssize_t
DECL|function|part_attr_show
id|part_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|page
)paren
(brace
r_struct
id|hd_struct
op_star
id|p
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|hd_struct
comma
id|kobj
)paren
suffix:semicolon
r_struct
id|part_attribute
op_star
id|part_attr
op_assign
id|container_of
c_func
(paren
id|attr
comma
r_struct
id|part_attribute
comma
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|part_attr-&gt;show
)paren
id|ret
op_assign
id|part_attr
op_member_access_from_pointer
id|show
c_func
(paren
id|p
comma
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|part_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|part_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|part_attr_show
comma
)brace
suffix:semicolon
DECL|function|part_dev_read
r_static
id|ssize_t
id|part_dev_read
c_func
(paren
r_struct
id|hd_struct
op_star
id|p
comma
r_char
op_star
id|page
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|container_of
c_func
(paren
id|p-&gt;kobj.parent
comma
r_struct
id|gendisk
comma
id|kobj
)paren
suffix:semicolon
id|dev_t
id|dev
op_assign
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
op_plus
id|p-&gt;partno
)paren
suffix:semicolon
r_return
id|print_dev_t
c_func
(paren
id|page
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|part_start_read
r_static
id|ssize_t
id|part_start_read
c_func
(paren
r_struct
id|hd_struct
op_star
id|p
comma
r_char
op_star
id|page
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|p-&gt;start_sect
)paren
suffix:semicolon
)brace
DECL|function|part_size_read
r_static
id|ssize_t
id|part_size_read
c_func
(paren
r_struct
id|hd_struct
op_star
id|p
comma
r_char
op_star
id|page
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|p-&gt;nr_sects
)paren
suffix:semicolon
)brace
DECL|function|part_stat_read
r_static
id|ssize_t
id|part_stat_read
c_func
(paren
r_struct
id|hd_struct
op_star
id|p
comma
r_char
op_star
id|page
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%8u %8llu %8u %8llu&bslash;n&quot;
comma
id|p-&gt;reads
comma
(paren
r_int
r_int
r_int
)paren
id|p-&gt;read_sectors
comma
id|p-&gt;writes
comma
(paren
r_int
r_int
r_int
)paren
id|p-&gt;write_sectors
)paren
suffix:semicolon
)brace
DECL|variable|part_attr_dev
r_static
r_struct
id|part_attribute
id|part_attr_dev
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dev&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|part_dev_read
)brace
suffix:semicolon
DECL|variable|part_attr_start
r_static
r_struct
id|part_attribute
id|part_attr_start
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;start&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|part_start_read
)brace
suffix:semicolon
DECL|variable|part_attr_size
r_static
r_struct
id|part_attribute
id|part_attr_size
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;size&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|part_size_read
)brace
suffix:semicolon
DECL|variable|part_attr_stat
r_static
r_struct
id|part_attribute
id|part_attr_stat
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;stat&quot;
comma
dot
id|mode
op_assign
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|part_stat_read
)brace
suffix:semicolon
DECL|variable|default_attrs
r_static
r_struct
id|attribute
op_star
id|default_attrs
(braket
)braket
op_assign
(brace
op_amp
id|part_attr_dev.attr
comma
op_amp
id|part_attr_start.attr
comma
op_amp
id|part_attr_size.attr
comma
op_amp
id|part_attr_stat.attr
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_extern
r_struct
id|subsystem
id|block_subsys
suffix:semicolon
DECL|function|part_release
r_static
r_void
id|part_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|hd_struct
op_star
id|p
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|hd_struct
comma
id|kobj
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|variable|ktype_part
r_struct
id|kobj_type
id|ktype_part
op_assign
(brace
dot
id|release
op_assign
id|part_release
comma
dot
id|default_attrs
op_assign
id|default_attrs
comma
dot
id|sysfs_ops
op_assign
op_amp
id|part_sysfs_ops
comma
)brace
suffix:semicolon
DECL|function|delete_partition
r_void
id|delete_partition
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
(braket
id|part
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;nr_sects
)paren
r_return
suffix:semicolon
id|disk-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;start_sect
op_assign
l_int|0
suffix:semicolon
id|p-&gt;nr_sects
op_assign
l_int|0
suffix:semicolon
id|p-&gt;reads
op_assign
id|p-&gt;writes
op_assign
id|p-&gt;read_sectors
op_assign
id|p-&gt;write_sectors
op_assign
l_int|0
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;%s/part%d&quot;
comma
id|disk-&gt;devfs_name
comma
id|part
)paren
suffix:semicolon
id|kobject_unregister
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
suffix:semicolon
)brace
DECL|function|add_partition
r_void
id|add_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
r_int
id|part
comma
id|sector_t
id|start
comma
id|sector_t
id|len
)paren
(brace
r_struct
id|hd_struct
op_star
id|p
suffix:semicolon
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
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
r_return
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|p-&gt;start_sect
op_assign
id|start
suffix:semicolon
id|p-&gt;nr_sects
op_assign
id|len
suffix:semicolon
id|p-&gt;partno
op_assign
id|part
suffix:semicolon
id|devfs_mk_bdev
c_func
(paren
id|MKDEV
c_func
(paren
id|disk-&gt;major
comma
id|disk-&gt;first_minor
op_plus
id|part
)paren
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_string|&quot;%s/part%d&quot;
comma
id|disk-&gt;devfs_name
comma
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|disk-&gt;kobj.name
(braket
id|strlen
c_func
(paren
id|disk-&gt;kobj.name
)paren
op_minus
l_int|1
)braket
)paren
)paren
id|snprintf
c_func
(paren
id|p-&gt;kobj.name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;%sp%d&quot;
comma
id|disk-&gt;kobj.name
comma
id|part
)paren
suffix:semicolon
r_else
id|snprintf
c_func
(paren
id|p-&gt;kobj.name
comma
id|KOBJ_NAME_LEN
comma
l_string|&quot;%s%d&quot;
comma
id|disk-&gt;kobj.name
comma
id|part
)paren
suffix:semicolon
id|p-&gt;kobj.parent
op_assign
op_amp
id|disk-&gt;kobj
suffix:semicolon
id|p-&gt;kobj.ktype
op_assign
op_amp
id|ktype_part
suffix:semicolon
id|kobject_register
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
suffix:semicolon
id|disk-&gt;part
(braket
id|part
op_minus
l_int|1
)braket
op_assign
id|p
suffix:semicolon
)brace
DECL|function|disk_sysfs_symlinks
r_static
r_void
id|disk_sysfs_symlinks
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_struct
id|device
op_star
id|target
op_assign
id|get_device
c_func
(paren
id|disk-&gt;driverfs_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target
)paren
(brace
id|sysfs_create_link
c_func
(paren
op_amp
id|disk-&gt;kobj
comma
op_amp
id|target-&gt;kobj
comma
l_string|&quot;device&quot;
)paren
suffix:semicolon
id|sysfs_create_link
c_func
(paren
op_amp
id|target-&gt;kobj
comma
op_amp
id|disk-&gt;kobj
comma
l_string|&quot;block&quot;
)paren
suffix:semicolon
)brace
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
r_char
op_star
id|s
suffix:semicolon
r_int
id|err
suffix:semicolon
id|strlcpy
c_func
(paren
id|disk-&gt;kobj.name
comma
id|disk-&gt;disk_name
comma
id|KOBJ_NAME_LEN
)paren
suffix:semicolon
multiline_comment|/* ewww... some of these buggers have / in name... */
id|s
op_assign
id|strchr
c_func
(paren
id|disk-&gt;kobj.name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
op_star
id|s
op_assign
l_char|&squot;!&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|kobject_add
c_func
(paren
op_amp
id|disk-&gt;kobj
)paren
)paren
)paren
r_return
suffix:semicolon
id|disk_sysfs_symlinks
c_func
(paren
id|disk
)paren
suffix:semicolon
multiline_comment|/* No minors to use for partitions */
r_if
c_cond
(paren
id|disk-&gt;minors
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|disk-&gt;devfs_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|devfs_add_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* always add handle for the whole disk */
id|devfs_add_partitioned
c_func
(paren
id|disk
)paren
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
id|bdget_disk
c_func
(paren
id|disk
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_return
suffix:semicolon
id|bdev-&gt;bd_invalidated
op_assign
l_int|1
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
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
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
r_struct
id|parsed_partitions
op_star
id|state
suffix:semicolon
r_int
id|p
comma
id|res
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
id|invalidate_partition
c_func
(paren
id|disk
comma
l_int|0
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
l_int|1
suffix:semicolon
id|p
OL
id|disk-&gt;minors
suffix:semicolon
id|p
op_increment
)paren
id|delete_partition
c_func
(paren
id|disk
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk-&gt;fops-&gt;revalidate_disk
)paren
id|disk-&gt;fops
op_member_access_from_pointer
id|revalidate_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_capacity
c_func
(paren
id|disk
)paren
op_logical_or
op_logical_neg
(paren
id|state
op_assign
id|check_partition
c_func
(paren
id|disk
comma
id|bdev
)paren
)paren
)paren
r_return
op_minus
id|EIO
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
id|state-&gt;limit
suffix:semicolon
id|p
op_increment
)paren
(brace
id|sector_t
id|size
op_assign
id|state-&gt;parts
(braket
id|p
)braket
dot
id|size
suffix:semicolon
id|sector_t
id|from
op_assign
id|state-&gt;parts
(braket
id|p
)braket
dot
id|from
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_continue
suffix:semicolon
id|add_partition
c_func
(paren
id|disk
comma
id|p
comma
id|from
comma
id|size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_MD
r_if
c_cond
(paren
id|state-&gt;parts
(braket
id|p
)braket
dot
id|flags
)paren
id|md_autodetect_dev
c_func
(paren
id|bdev-&gt;bd_dev
op_plus
id|p
)paren
suffix:semicolon
macro_line|#endif
)brace
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
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
DECL|variable|read_dev_sector
id|EXPORT_SYMBOL
c_func
(paren
id|read_dev_sector
)paren
suffix:semicolon
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
r_int
id|p
suffix:semicolon
multiline_comment|/* invalidate stuff */
r_for
c_loop
(paren
id|p
op_assign
id|disk-&gt;minors
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
id|invalidate_partition
c_func
(paren
id|disk
comma
id|p
)paren
suffix:semicolon
id|delete_partition
c_func
(paren
id|disk
comma
id|p
)paren
suffix:semicolon
)brace
id|invalidate_partition
c_func
(paren
id|disk
comma
l_int|0
)paren
suffix:semicolon
id|disk-&gt;capacity
op_assign
l_int|0
suffix:semicolon
id|disk-&gt;flags
op_and_assign
op_complement
id|GENHD_FL_UP
suffix:semicolon
id|unlink_gendisk
c_func
(paren
id|disk
)paren
suffix:semicolon
id|disk_stat_set_all
c_func
(paren
id|disk
comma
l_int|0
)paren
suffix:semicolon
id|disk-&gt;stamp
op_assign
id|disk-&gt;stamp_idle
op_assign
l_int|0
suffix:semicolon
id|devfs_remove_disk
c_func
(paren
id|disk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disk-&gt;driverfs_dev
)paren
(brace
id|sysfs_remove_link
c_func
(paren
op_amp
id|disk-&gt;kobj
comma
l_string|&quot;device&quot;
)paren
suffix:semicolon
id|sysfs_remove_link
c_func
(paren
op_amp
id|disk-&gt;driverfs_dev-&gt;kobj
comma
l_string|&quot;block&quot;
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|disk-&gt;driverfs_dev
)paren
suffix:semicolon
)brace
id|kobject_del
c_func
(paren
op_amp
id|disk-&gt;kobj
)paren
suffix:semicolon
)brace
eof
