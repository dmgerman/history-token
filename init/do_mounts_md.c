macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &quot;do_mounts.h&quot;
multiline_comment|/*&n; * When md (and any require personalities) are compiled into the kernel&n; * (not a module), arrays can be assembles are boot time using with AUTODETECT&n; * where specially marked partitions are registered with md_autodetect_dev(),&n; * and with MD_BOOT where devices to be collected are given on the boot line&n; * with md=.....&n; * The code for that is here.&n; */
DECL|variable|raid_noautodetect
r_static
r_int
id|__initdata
id|raid_noautodetect
suffix:semicolon
r_static
r_struct
(brace
DECL|member|device_set
r_char
id|device_set
(braket
id|MAX_MD_DEVS
)braket
suffix:semicolon
DECL|member|pers
r_int
id|pers
(braket
id|MAX_MD_DEVS
)braket
suffix:semicolon
DECL|member|chunk
r_int
id|chunk
(braket
id|MAX_MD_DEVS
)braket
suffix:semicolon
DECL|member|device_names
r_char
op_star
id|device_names
(braket
id|MAX_MD_DEVS
)braket
suffix:semicolon
DECL|variable|__initdata
)brace
id|md_setup_args
id|__initdata
suffix:semicolon
multiline_comment|/*&n; * Parse the command-line parameters given our kernel, but do not&n; * actually try to invoke the MD device now; that is handled by&n; * md_setup_drive after the low-level disk drivers have initialised.&n; *&n; * 27/11/1999: Fixed to work correctly with the 2.3 kernel (which&n; *             assigns the task of parsing integer arguments to the&n; *             invoked program now).  Added ability to initialise all&n; *             the MD devices (by specifying multiple &quot;md=&quot; lines)&n; *             instead of just one.  -- KTK&n; * 18May2000: Added support for persistent-superblock arrays:&n; *             md=n,0,factor,fault,device-list   uses RAID0 for device n&n; *             md=n,-1,factor,fault,device-list  uses LINEAR for device n&n; *             md=n,device-list      reads a RAID superblock from the devices&n; *             elements in device-list are read by name_to_kdev_t so can be&n; *             a hex number or something like /dev/hda1 /dev/sdb&n; * 2001-06-03: Dave Cinege &lt;dcinege@psychosis.com&gt;&n; *&t;&t;Shifted name_to_kdev_t() and related operations to md_set_drive()&n; *&t;&t;for later execution. Rewrote section to make devfs compatible.&n; */
DECL|function|md_setup
r_static
r_int
id|__init
id|md_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|minor
comma
id|level
comma
id|factor
comma
id|fault
comma
id|pers
suffix:semicolon
r_char
op_star
id|pername
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_char
op_star
id|str1
op_assign
id|str
suffix:semicolon
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|minor
)paren
op_ne
l_int|2
)paren
(brace
multiline_comment|/* MD Number */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: Too few arguments supplied to md=.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|minor
op_ge
id|MAX_MD_DEVS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: md=%d, Minor device number too high.&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|md_setup_args.device_names
(braket
id|minor
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: md=%d, Specified more than once. &quot;
l_string|&quot;Replacing previous definition.&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|level
)paren
)paren
(brace
multiline_comment|/* RAID Personality */
r_case
l_int|2
suffix:colon
multiline_comment|/* could be 0 or -1.. */
r_if
c_cond
(paren
id|level
op_eq
l_int|0
op_logical_or
id|level
op_eq
id|LEVEL_LINEAR
)paren
(brace
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|factor
)paren
op_ne
l_int|2
op_logical_or
multiline_comment|/* Chunk Size */
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|fault
)paren
op_ne
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: Too few arguments supplied to md=.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|md_setup_args.pers
(braket
id|minor
)braket
op_assign
id|level
suffix:semicolon
id|md_setup_args.chunk
(braket
id|minor
)braket
op_assign
l_int|1
op_lshift
(paren
id|factor
op_plus
l_int|12
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|level
)paren
(brace
r_case
id|LEVEL_LINEAR
suffix:colon
id|pers
op_assign
id|LINEAR
suffix:semicolon
id|pername
op_assign
l_string|&quot;linear&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|pers
op_assign
id|RAID0
suffix:semicolon
id|pername
op_assign
l_string|&quot;raid0&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: The kernel has not been configured for raid%d support!&bslash;n&quot;
comma
id|level
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|md_setup_args.pers
(braket
id|minor
)braket
op_assign
id|pers
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* FALL THROUGH */
r_case
l_int|1
suffix:colon
multiline_comment|/* the first device is numeric */
id|str
op_assign
id|str1
suffix:semicolon
multiline_comment|/* FALL THROUGH */
r_case
l_int|0
suffix:colon
id|md_setup_args.pers
(braket
id|minor
)braket
op_assign
l_int|0
suffix:semicolon
id|pername
op_assign
l_string|&quot;super-block&quot;
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;md: Will configure md%d (%s) from %s, below.&bslash;n&quot;
comma
id|minor
comma
id|pername
comma
id|str
)paren
suffix:semicolon
id|md_setup_args.device_names
(braket
id|minor
)braket
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|md_setup_drive
r_static
r_void
id|__init
id|md_setup_drive
c_func
(paren
r_void
)paren
(brace
r_int
id|minor
comma
id|i
suffix:semicolon
id|dev_t
id|dev
suffix:semicolon
id|dev_t
id|devices
(braket
id|MD_SB_DISKS
op_plus
l_int|1
)braket
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
l_int|0
suffix:semicolon
id|minor
OL
id|MAX_MD_DEVS
suffix:semicolon
id|minor
op_increment
)paren
(brace
r_int
id|fd
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|devname
suffix:semicolon
id|mdu_disk_info_t
id|dinfo
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
comma
id|devfs_name
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|devname
op_assign
id|md_setup_args.device_names
(braket
id|minor
)braket
)paren
)paren
r_continue
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;/dev/md%d&quot;
comma
id|minor
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|devfs_name
comma
l_string|&quot;/dev/md/%d&quot;
comma
id|minor
)paren
suffix:semicolon
id|create_dev
c_func
(paren
id|name
comma
id|MKDEV
c_func
(paren
id|MD_MAJOR
comma
id|minor
)paren
comma
id|devfs_name
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
id|MD_SB_DISKS
op_logical_and
id|devname
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_char
id|comp_name
(braket
l_int|64
)braket
suffix:semicolon
r_struct
id|stat
id|buf
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|devname
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|name_to_dev_t
c_func
(paren
id|devname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|devname
comma
l_string|&quot;/dev/&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|devname
op_add_assign
l_int|5
suffix:semicolon
id|snprintf
c_func
(paren
id|comp_name
comma
l_int|63
comma
l_string|&quot;/dev/%s&quot;
comma
id|devname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sys_newstat
c_func
(paren
id|comp_name
comma
op_amp
id|buf
)paren
op_eq
l_int|0
op_logical_and
id|S_ISBLK
c_func
(paren
id|buf.st_mode
)paren
)paren
id|dev
op_assign
id|buf.st_rdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: Unknown device name: %s&bslash;n&quot;
comma
id|devname
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|devices
(braket
id|i
)braket
op_assign
id|dev
suffix:semicolon
id|md_setup_args.device_set
(braket
id|minor
)braket
op_assign
l_int|1
suffix:semicolon
id|devname
op_assign
id|p
suffix:semicolon
)brace
id|devices
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|md_setup_args.device_set
(braket
id|minor
)braket
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;md: Loading md%d: %s&bslash;n&quot;
comma
id|minor
comma
id|md_setup_args.device_names
(braket
id|minor
)braket
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|name
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;md: open failed - cannot start array %d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SET_ARRAY_INFO
comma
l_int|0
)paren
op_eq
op_minus
id|EBUSY
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: Ignoring md=%d, already autodetected. (Use raid=noautodetect)&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|md_setup_args.pers
(braket
id|minor
)braket
)paren
(brace
multiline_comment|/* non-persistent */
id|mdu_array_info_t
id|ainfo
suffix:semicolon
id|ainfo.level
op_assign
id|pers_to_level
c_func
(paren
id|md_setup_args.pers
(braket
id|minor
)braket
)paren
suffix:semicolon
id|ainfo.size
op_assign
l_int|0
suffix:semicolon
id|ainfo.nr_disks
op_assign
l_int|0
suffix:semicolon
id|ainfo.raid_disks
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|devices
(braket
id|ainfo.raid_disks
)braket
)paren
id|ainfo.raid_disks
op_increment
suffix:semicolon
id|ainfo.md_minor
op_assign
id|minor
suffix:semicolon
id|ainfo.not_persistent
op_assign
l_int|1
suffix:semicolon
id|ainfo.state
op_assign
(paren
l_int|1
op_lshift
id|MD_SB_CLEAN
)paren
suffix:semicolon
id|ainfo.layout
op_assign
l_int|0
suffix:semicolon
id|ainfo.chunk_size
op_assign
id|md_setup_args.chunk
(braket
id|minor
)braket
suffix:semicolon
id|err
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SET_ARRAY_INFO
comma
(paren
r_int
)paren
op_amp
id|ainfo
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|err
op_logical_and
id|i
op_le
id|MD_SB_DISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
id|devices
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
id|dinfo.number
op_assign
id|i
suffix:semicolon
id|dinfo.raid_disk
op_assign
id|i
suffix:semicolon
id|dinfo.state
op_assign
(paren
l_int|1
op_lshift
id|MD_DISK_ACTIVE
)paren
op_or
(paren
l_int|1
op_lshift
id|MD_DISK_SYNC
)paren
suffix:semicolon
id|dinfo.major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dinfo.minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|err
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|ADD_NEW_DISK
comma
(paren
r_int
)paren
op_amp
id|dinfo
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* persistent */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|MD_SB_DISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
id|devices
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
id|dinfo.major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dinfo.minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sys_ioctl
c_func
(paren
id|fd
comma
id|ADD_NEW_DISK
comma
(paren
r_int
)paren
op_amp
id|dinfo
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|RUN_ARRAY
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;md: starting md%d failed&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
)brace
DECL|function|raid_setup
r_static
r_int
id|__init
id|raid_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|len
comma
id|pos
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|len
)paren
(brace
r_char
op_star
id|comma
op_assign
id|strchr
c_func
(paren
id|str
op_plus
id|pos
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_int
id|wlen
suffix:semicolon
r_if
c_cond
(paren
id|comma
)paren
id|wlen
op_assign
(paren
id|comma
op_minus
id|str
)paren
op_minus
id|pos
suffix:semicolon
r_else
id|wlen
op_assign
(paren
id|len
op_minus
l_int|1
)paren
op_minus
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;noautodetect&quot;
comma
id|wlen
)paren
)paren
id|raid_noautodetect
op_assign
l_int|1
suffix:semicolon
id|pos
op_add_assign
id|wlen
op_plus
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;raid=&quot;
comma
id|raid_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;md=&quot;
comma
id|md_setup
)paren
suffix:semicolon
DECL|function|md_run_setup
r_void
id|__init
id|md_run_setup
c_func
(paren
r_void
)paren
(brace
id|create_dev
c_func
(paren
l_string|&quot;/dev/md0&quot;
comma
id|MKDEV
c_func
(paren
id|MD_MAJOR
comma
l_int|0
)paren
comma
l_string|&quot;md/0&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raid_noautodetect
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;md: Skipping autodetection of RAID arrays. (raid=noautodetect)&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_int
id|fd
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/md0&quot;
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
op_ge
l_int|0
)paren
(brace
id|sys_ioctl
c_func
(paren
id|fd
comma
id|RAID_AUTORUN
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
)brace
id|md_setup_drive
c_func
(paren
)paren
suffix:semicolon
)brace
eof
