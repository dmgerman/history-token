macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/fd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_fs_sb.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
macro_line|#include &quot;do_mounts.h&quot;
r_extern
r_int
id|get_filesystem_list
c_func
(paren
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|variable|rd_doload
r_int
id|__initdata
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load RAM disk, 0 = don&squot;t load */
DECL|variable|root_mountflags
r_int
id|root_mountflags
op_assign
id|MS_RDONLY
op_or
id|MS_VERBOSE
suffix:semicolon
DECL|variable|root_device_name
r_char
op_star
id|__initdata
id|root_device_name
suffix:semicolon
DECL|variable|saved_root_name
r_static
r_char
id|__initdata
id|saved_root_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* this is initialized in init/main.c */
DECL|variable|ROOT_DEV
id|dev_t
id|ROOT_DEV
suffix:semicolon
DECL|variable|ROOT_DEV
id|EXPORT_SYMBOL
c_func
(paren
id|ROOT_DEV
)paren
suffix:semicolon
DECL|function|load_ramdisk
r_static
r_int
id|__init
id|load_ramdisk
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|rd_doload
op_assign
id|simple_strtol
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
op_amp
l_int|3
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;load_ramdisk=&quot;
comma
id|load_ramdisk
)paren
suffix:semicolon
DECL|function|readonly
r_static
r_int
id|__init
id|readonly
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|root_mountflags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|readwrite
r_static
r_int
id|__init
id|readwrite
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;ro&quot;
comma
id|readonly
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;rw&quot;
comma
id|readwrite
)paren
suffix:semicolon
DECL|function|try_name
r_static
id|dev_t
id|try_name
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|part
)paren
(brace
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|range
suffix:semicolon
id|dev_t
id|res
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
r_int
id|maj
comma
id|min
suffix:semicolon
multiline_comment|/* read device number from .../dev */
id|sprintf
c_func
(paren
id|path
comma
l_string|&quot;/sys/block/%s/dev&quot;
comma
id|name
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
id|path
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|len
op_assign
id|sys_read
c_func
(paren
id|fd
comma
id|buf
comma
l_int|32
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
op_logical_or
id|len
op_eq
l_int|32
op_logical_or
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_goto
id|fail
suffix:semicolon
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%u:%u&quot;
comma
op_amp
id|maj
comma
op_amp
id|min
)paren
op_eq
l_int|2
)paren
(brace
multiline_comment|/*&n;&t;&t; * Try the %u:%u format -- see print_dev_t()&n;&t;&t; */
id|res
op_assign
id|MKDEV
c_func
(paren
id|maj
comma
id|min
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maj
op_ne
id|MAJOR
c_func
(paren
id|res
)paren
op_logical_or
id|min
op_ne
id|MINOR
c_func
(paren
id|res
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Nope.  Try old-style &quot;0321&quot;&n;&t;&t; */
id|res
op_assign
id|new_decode_dev
c_func
(paren
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|s
comma
l_int|16
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
)paren
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* if it&squot;s there and we are not looking for a partition - that&squot;s it */
r_if
c_cond
(paren
op_logical_neg
id|part
)paren
r_return
id|res
suffix:semicolon
multiline_comment|/* otherwise read range from .../range */
id|sprintf
c_func
(paren
id|path
comma
l_string|&quot;/sys/block/%s/range&quot;
comma
id|name
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
id|path
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|len
op_assign
id|sys_read
c_func
(paren
id|fd
comma
id|buf
comma
l_int|32
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
op_logical_or
id|len
op_eq
l_int|32
op_logical_or
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_goto
id|fail
suffix:semicolon
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|range
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|s
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* if partition is within range - we got it */
r_if
c_cond
(paren
id|part
OL
id|range
)paren
r_return
id|res
op_plus
id|part
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Convert a name into device number.  We accept the following variants:&n; *&n; *&t;1) device number in hexadecimal&t;represents itself&n; *&t;2) /dev/nfs represents Root_NFS (0xff)&n; *&t;3) /dev/&lt;disk_name&gt; represents the device number of disk&n; *&t;4) /dev/&lt;disk_name&gt;&lt;decimal&gt; represents the device number&n; *         of partition - device number of disk plus the partition number&n; *&t;5) /dev/&lt;disk_name&gt;p&lt;decimal&gt; - same as the above, that form is&n; *&t;   used when disk name of partitioned disk ends on a digit.&n; *&n; *&t;If name doesn&squot;t have fall into the categories above, we return 0.&n; *&t;Driverfs is used to check if something is a disk name - it has&n; *&t;all known disks under bus/block/devices.  If the disk name&n; *&t;contains slashes, name of driverfs node has them replaced with&n; *&t;bangs.  try_name() does the actual checks, assuming that driverfs&n; *&t;is mounted on rootfs /sys.&n; */
DECL|function|name_to_dev_t
id|dev_t
id|name_to_dev_t
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_char
id|s
(braket
l_int|32
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
id|dev_t
id|res
op_assign
l_int|0
suffix:semicolon
r_int
id|part
suffix:semicolon
macro_line|#ifdef CONFIG_SYSFS
r_int
id|mkdir_err
op_assign
id|sys_mkdir
c_func
(paren
l_string|&quot;/sys&quot;
comma
l_int|0700
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sys_mount
c_func
(paren
l_string|&quot;sysfs&quot;
comma
l_string|&quot;/sys&quot;
comma
l_string|&quot;sysfs&quot;
comma
l_int|0
comma
l_int|NULL
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;/dev/&quot;
comma
l_int|5
)paren
op_ne
l_int|0
)paren
(brace
r_int
id|maj
comma
id|min
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|name
comma
l_string|&quot;%u:%u&quot;
comma
op_amp
id|maj
comma
op_amp
id|min
)paren
op_eq
l_int|2
)paren
(brace
id|res
op_assign
id|MKDEV
c_func
(paren
id|maj
comma
id|min
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maj
op_ne
id|MAJOR
c_func
(paren
id|res
)paren
op_logical_or
id|min
op_ne
id|MINOR
c_func
(paren
id|res
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_else
(brace
id|res
op_assign
id|new_decode_dev
c_func
(paren
id|simple_strtoul
c_func
(paren
id|name
comma
op_amp
id|p
comma
l_int|16
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_goto
id|done
suffix:semicolon
)brace
id|name
op_add_assign
l_int|5
suffix:semicolon
id|res
op_assign
id|Root_NFS
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;nfs&quot;
)paren
op_eq
l_int|0
)paren
r_goto
id|done
suffix:semicolon
id|res
op_assign
id|Root_RAM0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ram&quot;
)paren
op_eq
l_int|0
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|name
)paren
OG
l_int|31
)paren
r_goto
id|fail
suffix:semicolon
id|strcpy
c_func
(paren
id|s
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|s
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;/&squot;
)paren
op_star
id|p
op_assign
l_char|&squot;!&squot;
suffix:semicolon
id|res
op_assign
id|try_name
c_func
(paren
id|s
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|done
suffix:semicolon
r_while
c_loop
(paren
id|p
OG
id|s
op_logical_and
id|isdigit
c_func
(paren
id|p
(braket
op_minus
l_int|1
)braket
)paren
)paren
id|p
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|s
op_logical_or
op_logical_neg
op_star
id|p
op_logical_or
op_star
id|p
op_eq
l_char|&squot;0&squot;
)paren
r_goto
id|fail
suffix:semicolon
id|part
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|res
op_assign
id|try_name
c_func
(paren
id|s
comma
id|part
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
id|s
op_plus
l_int|2
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
id|p
(braket
op_minus
l_int|2
)braket
)paren
op_logical_or
id|p
(braket
op_minus
l_int|1
)braket
op_ne
l_char|&squot;p&squot;
)paren
r_goto
id|fail
suffix:semicolon
id|p
(braket
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|res
op_assign
id|try_name
c_func
(paren
id|s
comma
id|part
)paren
suffix:semicolon
id|done
suffix:colon
macro_line|#ifdef CONFIG_SYSFS
id|sys_umount
c_func
(paren
l_string|&quot;/sys&quot;
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|mkdir_err
)paren
id|sys_rmdir
c_func
(paren
l_string|&quot;/sys&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|res
suffix:semicolon
id|fail
suffix:colon
id|res
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
DECL|function|root_dev_setup
r_static
r_int
id|__init
id|root_dev_setup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
id|strlcpy
c_func
(paren
id|saved_root_name
comma
id|line
comma
r_sizeof
(paren
id|saved_root_name
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;root=&quot;
comma
id|root_dev_setup
)paren
suffix:semicolon
DECL|variable|root_mount_data
r_static
r_char
op_star
id|__initdata
id|root_mount_data
suffix:semicolon
DECL|function|root_data_setup
r_static
r_int
id|__init
id|root_data_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|root_mount_data
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|root_fs_names
r_static
r_char
op_star
id|__initdata
id|root_fs_names
suffix:semicolon
DECL|function|fs_names_setup
r_static
r_int
id|__init
id|fs_names_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|root_fs_names
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|root_delay
r_static
r_int
r_int
id|__initdata
id|root_delay
suffix:semicolon
DECL|function|root_delay_setup
r_static
r_int
id|__init
id|root_delay_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|root_delay
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;rootflags=&quot;
comma
id|root_data_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;rootfstype=&quot;
comma
id|fs_names_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;rootdelay=&quot;
comma
id|root_delay_setup
)paren
suffix:semicolon
DECL|function|get_fs_names
r_static
r_void
id|__init
id|get_fs_names
c_func
(paren
r_char
op_star
id|page
)paren
(brace
r_char
op_star
id|s
op_assign
id|page
suffix:semicolon
r_if
c_cond
(paren
id|root_fs_names
)paren
(brace
id|strcpy
c_func
(paren
id|page
comma
id|root_fs_names
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
op_increment
)paren
(brace
r_if
c_cond
(paren
id|s
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot;,&squot;
)paren
id|s
(braket
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
id|len
op_assign
id|get_filesystem_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|next
suffix:semicolon
id|page
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|page
op_minus
l_int|1
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|next
)paren
(brace
id|next
op_assign
id|strchr
c_func
(paren
op_increment
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_increment
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|s
op_increment
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|s
(braket
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
op_star
id|s
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|do_mount_root
r_static
r_int
id|__init
id|do_mount_root
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|fs
comma
r_int
id|flags
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|err
op_assign
id|sys_mount
c_func
(paren
id|name
comma
l_string|&quot;/root&quot;
comma
id|fs
comma
id|flags
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|sys_chdir
c_func
(paren
l_string|&quot;/root&quot;
)paren
suffix:semicolon
id|ROOT_DEV
op_assign
id|current-&gt;fs-&gt;pwdmnt-&gt;mnt_sb-&gt;s_dev
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VFS: Mounted root (%s filesystem)%s.&bslash;n&quot;
comma
id|current-&gt;fs-&gt;pwdmnt-&gt;mnt_sb-&gt;s_type-&gt;name
comma
id|current-&gt;fs-&gt;pwdmnt-&gt;mnt_sb-&gt;s_flags
op_amp
id|MS_RDONLY
ques
c_cond
l_string|&quot; readonly&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mount_block_root
r_void
id|__init
id|mount_block_root
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|flags
)paren
(brace
r_char
op_star
id|fs_names
op_assign
id|__getname
c_func
(paren
)paren
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_char
id|b
(braket
id|BDEVNAME_SIZE
)braket
suffix:semicolon
id|get_fs_names
c_func
(paren
id|fs_names
)paren
suffix:semicolon
id|retry
suffix:colon
r_for
c_loop
(paren
id|p
op_assign
id|fs_names
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_add_assign
id|strlen
c_func
(paren
id|p
)paren
op_plus
l_int|1
)paren
(brace
r_int
id|err
op_assign
id|do_mount_root
c_func
(paren
id|name
comma
id|p
comma
id|flags
comma
id|root_mount_data
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|err
)paren
(brace
r_case
l_int|0
suffix:colon
r_goto
id|out
suffix:semicolon
r_case
op_minus
id|EACCES
suffix:colon
id|flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_goto
id|retry
suffix:semicolon
r_case
op_minus
id|EINVAL
suffix:colon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Allow the user to distinguish between failed sys_open&n;&t;&t; * and bad superblock on root device.&n;&t;&t; */
id|__bdevname
c_func
(paren
id|ROOT_DEV
comma
id|b
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VFS: Cannot open root device &bslash;&quot;%s&bslash;&quot; or %s&bslash;n&quot;
comma
id|root_device_name
comma
id|b
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Please append a correct &bslash;&quot;root=&bslash;&quot; boot option&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;VFS: Unable to mount root fs on %s&quot;
comma
id|b
)paren
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;VFS: Unable to mount root fs on %s&quot;
comma
id|__bdevname
c_func
(paren
id|ROOT_DEV
comma
id|b
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|putname
c_func
(paren
id|fs_names
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ROOT_NFS
DECL|function|mount_nfs_root
r_static
r_int
id|__init
id|mount_nfs_root
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|data
op_assign
id|nfs_root_data
c_func
(paren
)paren
suffix:semicolon
id|create_dev
c_func
(paren
l_string|&quot;/dev/root&quot;
comma
id|ROOT_DEV
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_logical_and
id|do_mount_root
c_func
(paren
l_string|&quot;/dev/root&quot;
comma
l_string|&quot;nfs&quot;
comma
id|root_mountflags
comma
id|data
)paren
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_RAM) || defined(CONFIG_BLK_DEV_FD)
DECL|function|change_floppy
r_void
id|__init
id|change_floppy
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_struct
id|termios
id|termios
suffix:semicolon
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
r_char
id|c
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
l_string|&quot;/dev/root&quot;
comma
id|O_RDWR
op_or
id|O_NDELAY
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
id|sys_ioctl
c_func
(paren
id|fd
comma
id|FDEJECT
comma
l_int|0
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;VFS: Insert %s and press ENTER&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
l_string|&quot;/dev/console&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCGETS
comma
(paren
r_int
)paren
op_amp
id|termios
)paren
suffix:semicolon
id|termios.c_lflag
op_and_assign
op_complement
id|ICANON
suffix:semicolon
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCSETSF
comma
(paren
r_int
)paren
op_amp
id|termios
)paren
suffix:semicolon
id|sys_read
c_func
(paren
id|fd
comma
op_amp
id|c
comma
l_int|1
)paren
suffix:semicolon
id|termios.c_lflag
op_or_assign
id|ICANON
suffix:semicolon
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCSETSF
comma
(paren
r_int
)paren
op_amp
id|termios
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|mount_root
r_void
id|__init
id|mount_root
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ROOT_NFS
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|ROOT_DEV
)paren
op_eq
id|UNNAMED_MAJOR
)paren
(brace
r_if
c_cond
(paren
id|mount_nfs_root
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;VFS: Unable to mount root fs via NFS, trying floppy.&bslash;n&quot;
)paren
suffix:semicolon
id|ROOT_DEV
op_assign
id|Root_FD0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_FD
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|ROOT_DEV
)paren
op_eq
id|FLOPPY_MAJOR
)paren
(brace
multiline_comment|/* rd_doload is 2 for a dual initrd/ramload setup */
r_if
c_cond
(paren
id|rd_doload
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|rd_load_disk
c_func
(paren
l_int|1
)paren
)paren
(brace
id|ROOT_DEV
op_assign
id|Root_RAM1
suffix:semicolon
id|root_device_name
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
id|change_floppy
c_func
(paren
l_string|&quot;root floppy&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|create_dev
c_func
(paren
l_string|&quot;/dev/root&quot;
comma
id|ROOT_DEV
comma
id|root_device_name
)paren
suffix:semicolon
id|mount_block_root
c_func
(paren
l_string|&quot;/dev/root&quot;
comma
id|root_mountflags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Prepare the namespace - decide what/where to mount, load ramdisks, etc.&n; */
DECL|function|prepare_namespace
r_void
id|__init
id|prepare_namespace
c_func
(paren
r_void
)paren
(brace
r_int
id|is_floppy
suffix:semicolon
id|mount_devfs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root_delay
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Waiting %dsec before mounting root device...&bslash;n&quot;
comma
id|root_delay
)paren
suffix:semicolon
id|ssleep
c_func
(paren
id|root_delay
)paren
suffix:semicolon
)brace
id|md_run_setup
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_root_name
(braket
l_int|0
)braket
)paren
(brace
id|root_device_name
op_assign
id|saved_root_name
suffix:semicolon
id|ROOT_DEV
op_assign
id|name_to_dev_t
c_func
(paren
id|root_device_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|root_device_name
comma
l_string|&quot;/dev/&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|root_device_name
op_add_assign
l_int|5
suffix:semicolon
)brace
id|is_floppy
op_assign
id|MAJOR
c_func
(paren
id|ROOT_DEV
)paren
op_eq
id|FLOPPY_MAJOR
suffix:semicolon
r_if
c_cond
(paren
id|initrd_load
c_func
(paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|is_floppy
op_logical_and
id|rd_doload
op_logical_and
id|rd_load_disk
c_func
(paren
l_int|0
)paren
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
id|mount_root
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
id|umount_devfs
c_func
(paren
l_string|&quot;/dev&quot;
)paren
suffix:semicolon
id|sys_mount
c_func
(paren
l_string|&quot;.&quot;
comma
l_string|&quot;/&quot;
comma
l_int|NULL
comma
id|MS_MOVE
comma
l_int|NULL
)paren
suffix:semicolon
id|sys_chroot
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|security_sb_post_mountroot
c_func
(paren
)paren
suffix:semicolon
id|mount_devfs_fs
(paren
)paren
suffix:semicolon
)brace
eof
