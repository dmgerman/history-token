macro_line|#ifndef _LINUX_BLKPG_H
DECL|macro|_LINUX_BLKPG_H
mdefine_line|#define _LINUX_BLKPG_H
multiline_comment|/*&n; * Partition table and disk geometry handling&n; *&n; * A single ioctl with lots of subfunctions:&n; *&n; * Device number stuff:&n; *    get_whole_disk()&t;&t;(given the device number of a partition,&n; *                               find the device number of the encompassing disk)&n; *    get_all_partitions()&t;(given the device number of a disk, return the&n; *&t;&t;&t;&t; device numbers of all its known partitions)&n; *&n; * Partition stuff:&n; *    add_partition()&n; *    delete_partition()&n; *    test_partition_in_use()&t;(also for test_disk_in_use)&n; *&n; * Geometry stuff:&n; *    get_geometry()&n; *    set_geometry()&n; *    get_bios_drivedata()&n; *&n; * For today, only the partition stuff - aeb, 990515&n; */
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|BLKPG
mdefine_line|#define BLKPG      _IO(0x12,105)
multiline_comment|/* The argument structure */
DECL|struct|blkpg_ioctl_arg
r_struct
id|blkpg_ioctl_arg
(brace
DECL|member|op
r_int
id|op
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|datalen
r_int
id|datalen
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The subfunctions (for the op field) */
DECL|macro|BLKPG_ADD_PARTITION
mdefine_line|#define BLKPG_ADD_PARTITION&t;1
DECL|macro|BLKPG_DEL_PARTITION
mdefine_line|#define BLKPG_DEL_PARTITION&t;2
multiline_comment|/* Sizes of name fields. Unused at present. */
DECL|macro|BLKPG_DEVNAMELTH
mdefine_line|#define BLKPG_DEVNAMELTH&t;64
DECL|macro|BLKPG_VOLNAMELTH
mdefine_line|#define BLKPG_VOLNAMELTH&t;64
multiline_comment|/* The data structure for ADD_PARTITION and DEL_PARTITION */
DECL|struct|blkpg_partition
r_struct
id|blkpg_partition
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* starting offset in bytes */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* length in bytes */
DECL|member|pno
r_int
id|pno
suffix:semicolon
multiline_comment|/* partition number */
DECL|member|devname
r_char
id|devname
(braket
id|BLKPG_DEVNAMELTH
)braket
suffix:semicolon
multiline_comment|/* partition name, like sda5 or c0d1p2,&n;&t;&t;&t;&t;&t;   to be used in kernel messages */
DECL|member|volname
r_char
id|volname
(braket
id|BLKPG_VOLNAMELTH
)braket
suffix:semicolon
multiline_comment|/* volume label */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_char
op_star
id|partition_name
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|blk_ioctl
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_BLKPG_H */
eof
