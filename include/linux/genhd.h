macro_line|#ifndef _LINUX_GENHD_H
DECL|macro|_LINUX_GENHD_H
mdefine_line|#define _LINUX_GENHD_H
multiline_comment|/*&n; * &t;genhd.h Copyright (C) 1992 Drew Eckhardt&n; *&t;Generic hard disk header file by  &n; * &t;&t;Drew Eckhardt&n; *&n; *&t;&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/device.h&gt;
r_enum
(brace
multiline_comment|/* These three have identical behaviour; use the second one if DOS fdisk gets&n;   confused about extended/logical partitions starting past cylinder 1023. */
DECL|enumerator|DOS_EXTENDED_PARTITION
id|DOS_EXTENDED_PARTITION
op_assign
l_int|5
comma
DECL|enumerator|LINUX_EXTENDED_PARTITION
id|LINUX_EXTENDED_PARTITION
op_assign
l_int|0x85
comma
DECL|enumerator|WIN98_EXTENDED_PARTITION
id|WIN98_EXTENDED_PARTITION
op_assign
l_int|0x0f
comma
DECL|enumerator|LINUX_SWAP_PARTITION
id|LINUX_SWAP_PARTITION
op_assign
l_int|0x82
comma
DECL|enumerator|LINUX_RAID_PARTITION
id|LINUX_RAID_PARTITION
op_assign
l_int|0xfd
comma
multiline_comment|/* autodetect RAID partition */
DECL|enumerator|SOLARIS_X86_PARTITION
id|SOLARIS_X86_PARTITION
op_assign
id|LINUX_SWAP_PARTITION
comma
DECL|enumerator|DM6_PARTITION
id|DM6_PARTITION
op_assign
l_int|0x54
comma
multiline_comment|/* has DDO: use xlated geom &amp; offset */
DECL|enumerator|EZD_PARTITION
id|EZD_PARTITION
op_assign
l_int|0x55
comma
multiline_comment|/* EZ-DRIVE */
DECL|enumerator|DM6_AUX1PARTITION
id|DM6_AUX1PARTITION
op_assign
l_int|0x51
comma
multiline_comment|/* no DDO:  use xlated geom */
DECL|enumerator|DM6_AUX3PARTITION
id|DM6_AUX3PARTITION
op_assign
l_int|0x53
comma
multiline_comment|/* no DDO:  use xlated geom */
DECL|enumerator|FREEBSD_PARTITION
id|FREEBSD_PARTITION
op_assign
l_int|0xa5
comma
multiline_comment|/* FreeBSD Partition ID */
DECL|enumerator|OPENBSD_PARTITION
id|OPENBSD_PARTITION
op_assign
l_int|0xa6
comma
multiline_comment|/* OpenBSD Partition ID */
DECL|enumerator|NETBSD_PARTITION
id|NETBSD_PARTITION
op_assign
l_int|0xa9
comma
multiline_comment|/* NetBSD Partition ID */
DECL|enumerator|BSDI_PARTITION
id|BSDI_PARTITION
op_assign
l_int|0xb7
comma
multiline_comment|/* BSDI Partition ID */
multiline_comment|/* Ours is not to wonder why.. */
DECL|enumerator|BSD_PARTITION
id|BSD_PARTITION
op_assign
id|FREEBSD_PARTITION
comma
DECL|enumerator|MINIX_PARTITION
id|MINIX_PARTITION
op_assign
l_int|0x81
comma
multiline_comment|/* Minix Partition ID */
DECL|enumerator|UNIXWARE_PARTITION
id|UNIXWARE_PARTITION
op_assign
l_int|0x63
comma
multiline_comment|/* Partition ID, same as */
multiline_comment|/* GNU_HURD and SCO Unix */
)brace
suffix:semicolon
DECL|struct|partition
r_struct
id|partition
(brace
DECL|member|boot_ind
r_int
r_char
id|boot_ind
suffix:semicolon
multiline_comment|/* 0x80 - active */
DECL|member|head
r_int
r_char
id|head
suffix:semicolon
multiline_comment|/* starting head */
DECL|member|sector
r_int
r_char
id|sector
suffix:semicolon
multiline_comment|/* starting sector */
DECL|member|cyl
r_int
r_char
id|cyl
suffix:semicolon
multiline_comment|/* starting cylinder */
DECL|member|sys_ind
r_int
r_char
id|sys_ind
suffix:semicolon
multiline_comment|/* What partition type */
DECL|member|end_head
r_int
r_char
id|end_head
suffix:semicolon
multiline_comment|/* end head */
DECL|member|end_sector
r_int
r_char
id|end_sector
suffix:semicolon
multiline_comment|/* end sector */
DECL|member|end_cyl
r_int
r_char
id|end_cyl
suffix:semicolon
multiline_comment|/* end cylinder */
DECL|member|start_sect
r_int
r_int
id|start_sect
suffix:semicolon
multiline_comment|/* starting sector counting from 0 */
DECL|member|nr_sects
r_int
r_int
id|nr_sects
suffix:semicolon
multiline_comment|/* nr of sectors in partition */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#  include &lt;linux/devfs_fs_kernel.h&gt;
DECL|struct|hd_struct
r_struct
id|hd_struct
(brace
DECL|member|start_sect
id|sector_t
id|start_sect
suffix:semicolon
DECL|member|nr_sects
id|sector_t
id|nr_sects
suffix:semicolon
DECL|member|de
id|devfs_handle_t
id|de
suffix:semicolon
multiline_comment|/* primary (master) devfs entry  */
DECL|member|hd_driverfs_dev
r_struct
id|device
op_star
id|hd_driverfs_dev
suffix:semicolon
multiline_comment|/* support driverfs hiearchy     */
DECL|member|reads
DECL|member|read_sectors
DECL|member|writes
DECL|member|write_sectors
r_int
id|reads
comma
id|read_sectors
comma
id|writes
comma
id|write_sectors
suffix:semicolon
DECL|member|policy
r_int
id|policy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GENHD_FL_REMOVABLE
mdefine_line|#define GENHD_FL_REMOVABLE  1
DECL|macro|GENHD_FL_DRIVERFS
mdefine_line|#define GENHD_FL_DRIVERFS  2
DECL|macro|GENHD_FL_DEVFS
mdefine_line|#define GENHD_FL_DEVFS&t;4
DECL|macro|GENHD_FL_CD
mdefine_line|#define GENHD_FL_CD&t;8
DECL|macro|GENHD_FL_UP
mdefine_line|#define GENHD_FL_UP&t;16
DECL|struct|gendisk
r_struct
id|gendisk
(brace
DECL|member|major
r_int
id|major
suffix:semicolon
multiline_comment|/* major number of driver */
DECL|member|first_minor
r_int
id|first_minor
suffix:semicolon
DECL|member|minors
r_int
id|minors
suffix:semicolon
DECL|member|minor_shift
r_int
id|minor_shift
suffix:semicolon
multiline_comment|/* number of times minor is shifted to&n;&t;&t;&t;&t;&t;   get real minor */
DECL|member|disk_name
r_char
id|disk_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* name of major driver */
DECL|member|part
r_struct
id|hd_struct
op_star
id|part
suffix:semicolon
multiline_comment|/* [indexed by minor] */
DECL|member|fops
r_struct
id|block_device_operations
op_star
id|fops
suffix:semicolon
DECL|member|queue
r_struct
id|request_queue
op_star
id|queue
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|capacity
id|sector_t
id|capacity
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|full_list
r_struct
id|list_head
id|full_list
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* devfs crap */
DECL|member|de
id|devfs_handle_t
id|de
suffix:semicolon
multiline_comment|/* more of the same */
DECL|member|disk_de
id|devfs_handle_t
id|disk_de
suffix:semicolon
multiline_comment|/* piled higher and deeper */
DECL|member|driverfs_dev
r_struct
id|device
op_star
id|driverfs_dev
suffix:semicolon
DECL|member|disk_dev
r_struct
id|device
id|disk_dev
suffix:semicolon
DECL|member|random
r_struct
id|timer_rand_state
op_star
id|random
suffix:semicolon
DECL|member|policy
r_int
id|policy
suffix:semicolon
DECL|member|sync_io
r_int
id|sync_io
suffix:semicolon
multiline_comment|/* RAID */
DECL|member|reads
DECL|member|writes
r_int
id|reads
comma
id|writes
suffix:semicolon
DECL|member|rio
DECL|member|wio
r_int
id|rio
comma
id|wio
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* drivers/block/genhd.c */
r_extern
r_void
id|add_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
suffix:semicolon
r_extern
r_void
id|del_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|gp
)paren
suffix:semicolon
r_extern
r_void
id|unlink_gendisk
c_func
(paren
r_struct
id|gendisk
op_star
id|gp
)paren
suffix:semicolon
r_extern
r_struct
id|gendisk
op_star
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
suffix:semicolon
DECL|function|get_start_sect
r_static
r_inline
id|sector_t
id|get_start_sect
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_return
id|bdev-&gt;bd_offset
suffix:semicolon
)brace
DECL|function|get_capacity
r_static
r_inline
id|sector_t
id|get_capacity
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
(brace
r_return
id|disk-&gt;capacity
suffix:semicolon
)brace
DECL|function|set_capacity
r_static
r_inline
r_void
id|set_capacity
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
comma
id|sector_t
id|size
)paren
(brace
id|disk-&gt;capacity
op_assign
id|size
suffix:semicolon
)brace
r_extern
r_struct
id|device_class
id|disk_devclass
suffix:semicolon
macro_line|#endif  /*  __KERNEL__  */
macro_line|#ifdef CONFIG_SOLARIS_X86_PARTITION
DECL|macro|SOLARIS_X86_NUMSLICE
mdefine_line|#define SOLARIS_X86_NUMSLICE&t;8
DECL|macro|SOLARIS_X86_VTOC_SANE
mdefine_line|#define SOLARIS_X86_VTOC_SANE&t;(0x600DDEEEUL)
DECL|struct|solaris_x86_slice
r_struct
id|solaris_x86_slice
(brace
DECL|member|s_tag
id|ushort
id|s_tag
suffix:semicolon
multiline_comment|/* ID tag of partition */
DECL|member|s_flag
id|ushort
id|s_flag
suffix:semicolon
multiline_comment|/* permission flags */
DECL|member|s_start
r_int
r_int
id|s_start
suffix:semicolon
multiline_comment|/* start sector no of partition */
DECL|member|s_size
r_int
r_int
id|s_size
suffix:semicolon
multiline_comment|/* # of blocks in partition */
)brace
suffix:semicolon
DECL|struct|solaris_x86_vtoc
r_struct
id|solaris_x86_vtoc
(brace
DECL|member|v_bootinfo
r_int
r_int
id|v_bootinfo
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* info needed by mboot (unsupported) */
DECL|member|v_sanity
r_int
r_int
id|v_sanity
suffix:semicolon
multiline_comment|/* to verify vtoc sanity */
DECL|member|v_version
r_int
r_int
id|v_version
suffix:semicolon
multiline_comment|/* layout version */
DECL|member|v_volume
r_char
id|v_volume
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* volume name */
DECL|member|v_sectorsz
id|ushort
id|v_sectorsz
suffix:semicolon
multiline_comment|/* sector size in bytes */
DECL|member|v_nparts
id|ushort
id|v_nparts
suffix:semicolon
multiline_comment|/* number of partitions */
DECL|member|v_reserved
r_int
r_int
id|v_reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* free space */
r_struct
id|solaris_x86_slice
DECL|member|v_slice
id|v_slice
(braket
id|SOLARIS_X86_NUMSLICE
)braket
suffix:semicolon
multiline_comment|/* slice headers */
DECL|member|timestamp
r_int
r_int
id|timestamp
(braket
id|SOLARIS_X86_NUMSLICE
)braket
suffix:semicolon
multiline_comment|/* timestamp (unsupported) */
DECL|member|v_asciilabel
r_char
id|v_asciilabel
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* for compatibility */
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SOLARIS_X86_PARTITION */
macro_line|#ifdef CONFIG_BSD_DISKLABEL
multiline_comment|/*&n; * BSD disklabel support by Yossi Gottlieb &lt;yogo@math.tau.ac.il&gt;&n; * updated by Marc Espie &lt;Marc.Espie@openbsd.org&gt;&n; */
multiline_comment|/* check against BSD src/sys/sys/disklabel.h for consistency */
DECL|macro|BSD_DISKMAGIC
mdefine_line|#define BSD_DISKMAGIC&t;(0x82564557UL)&t;/* The disk magic number */
DECL|macro|BSD_MAXPARTITIONS
mdefine_line|#define BSD_MAXPARTITIONS&t;8
DECL|macro|OPENBSD_MAXPARTITIONS
mdefine_line|#define OPENBSD_MAXPARTITIONS&t;16
DECL|macro|BSD_FS_UNUSED
mdefine_line|#define BSD_FS_UNUSED&t;&t;0&t;/* disklabel unused partition entry ID */
DECL|struct|bsd_disklabel
r_struct
id|bsd_disklabel
(brace
DECL|member|d_magic
id|__u32
id|d_magic
suffix:semicolon
multiline_comment|/* the magic number */
DECL|member|d_type
id|__s16
id|d_type
suffix:semicolon
multiline_comment|/* drive type */
DECL|member|d_subtype
id|__s16
id|d_subtype
suffix:semicolon
multiline_comment|/* controller/d_type specific */
DECL|member|d_typename
r_char
id|d_typename
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* type name, e.g. &quot;eagle&quot; */
DECL|member|d_packname
r_char
id|d_packname
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* pack identifier */
DECL|member|d_secsize
id|__u32
id|d_secsize
suffix:semicolon
multiline_comment|/* # of bytes per sector */
DECL|member|d_nsectors
id|__u32
id|d_nsectors
suffix:semicolon
multiline_comment|/* # of data sectors per track */
DECL|member|d_ntracks
id|__u32
id|d_ntracks
suffix:semicolon
multiline_comment|/* # of tracks per cylinder */
DECL|member|d_ncylinders
id|__u32
id|d_ncylinders
suffix:semicolon
multiline_comment|/* # of data cylinders per unit */
DECL|member|d_secpercyl
id|__u32
id|d_secpercyl
suffix:semicolon
multiline_comment|/* # of data sectors per cylinder */
DECL|member|d_secperunit
id|__u32
id|d_secperunit
suffix:semicolon
multiline_comment|/* # of data sectors per unit */
DECL|member|d_sparespertrack
id|__u16
id|d_sparespertrack
suffix:semicolon
multiline_comment|/* # of spare sectors per track */
DECL|member|d_sparespercyl
id|__u16
id|d_sparespercyl
suffix:semicolon
multiline_comment|/* # of spare sectors per cylinder */
DECL|member|d_acylinders
id|__u32
id|d_acylinders
suffix:semicolon
multiline_comment|/* # of alt. cylinders per unit */
DECL|member|d_rpm
id|__u16
id|d_rpm
suffix:semicolon
multiline_comment|/* rotational speed */
DECL|member|d_interleave
id|__u16
id|d_interleave
suffix:semicolon
multiline_comment|/* hardware sector interleave */
DECL|member|d_trackskew
id|__u16
id|d_trackskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per track */
DECL|member|d_cylskew
id|__u16
id|d_cylskew
suffix:semicolon
multiline_comment|/* sector 0 skew, per cylinder */
DECL|member|d_headswitch
id|__u32
id|d_headswitch
suffix:semicolon
multiline_comment|/* head switch time, usec */
DECL|member|d_trkseek
id|__u32
id|d_trkseek
suffix:semicolon
multiline_comment|/* track-to-track seek, usec */
DECL|member|d_flags
id|__u32
id|d_flags
suffix:semicolon
multiline_comment|/* generic flags */
DECL|macro|NDDATA
mdefine_line|#define NDDATA 5
DECL|member|d_drivedata
id|__u32
id|d_drivedata
(braket
id|NDDATA
)braket
suffix:semicolon
multiline_comment|/* drive-type specific information */
DECL|macro|NSPARE
mdefine_line|#define NSPARE 5
DECL|member|d_spare
id|__u32
id|d_spare
(braket
id|NSPARE
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|member|d_magic2
id|__u32
id|d_magic2
suffix:semicolon
multiline_comment|/* the magic number (again) */
DECL|member|d_checksum
id|__u16
id|d_checksum
suffix:semicolon
multiline_comment|/* xor of data incl. partitions */
multiline_comment|/* filesystem and partition information: */
DECL|member|d_npartitions
id|__u16
id|d_npartitions
suffix:semicolon
multiline_comment|/* number of partitions in following */
DECL|member|d_bbsize
id|__u32
id|d_bbsize
suffix:semicolon
multiline_comment|/* size of boot area at sn0, bytes */
DECL|member|d_sbsize
id|__u32
id|d_sbsize
suffix:semicolon
multiline_comment|/* max size of fs superblock, bytes */
DECL|struct|bsd_partition
r_struct
id|bsd_partition
(brace
multiline_comment|/* the partition table */
DECL|member|p_size
id|__u32
id|p_size
suffix:semicolon
multiline_comment|/* number of sectors in partition */
DECL|member|p_offset
id|__u32
id|p_offset
suffix:semicolon
multiline_comment|/* starting sector */
DECL|member|p_fsize
id|__u32
id|p_fsize
suffix:semicolon
multiline_comment|/* filesystem basic fragment size */
DECL|member|p_fstype
id|__u8
id|p_fstype
suffix:semicolon
multiline_comment|/* filesystem type, see below */
DECL|member|p_frag
id|__u8
id|p_frag
suffix:semicolon
multiline_comment|/* filesystem fragments per block */
DECL|member|p_cpg
id|__u16
id|p_cpg
suffix:semicolon
multiline_comment|/* filesystem cylinders per group */
DECL|member|d_partitions
)brace
id|d_partitions
(braket
id|BSD_MAXPARTITIONS
)braket
suffix:semicolon
multiline_comment|/* actually may be more */
)brace
suffix:semicolon
macro_line|#endif&t;/* CONFIG_BSD_DISKLABEL */
macro_line|#ifdef CONFIG_UNIXWARE_DISKLABEL
multiline_comment|/*&n; * Unixware slices support by Andrzej Krzysztofowicz &lt;ankry@mif.pg.gda.pl&gt;&n; * and Krzysztof G. Baranowski &lt;kgb@knm.org.pl&gt;&n; */
DECL|macro|UNIXWARE_DISKMAGIC
mdefine_line|#define UNIXWARE_DISKMAGIC     (0xCA5E600DUL)&t;/* The disk magic number */
DECL|macro|UNIXWARE_DISKMAGIC2
mdefine_line|#define UNIXWARE_DISKMAGIC2    (0x600DDEEEUL)&t;/* The slice table magic nr */
DECL|macro|UNIXWARE_NUMSLICE
mdefine_line|#define UNIXWARE_NUMSLICE      16
DECL|macro|UNIXWARE_FS_UNUSED
mdefine_line|#define UNIXWARE_FS_UNUSED     0&t;&t;/* Unused slice entry ID */
DECL|struct|unixware_slice
r_struct
id|unixware_slice
(brace
DECL|member|s_label
id|__u16
id|s_label
suffix:semicolon
multiline_comment|/* label */
DECL|member|s_flags
id|__u16
id|s_flags
suffix:semicolon
multiline_comment|/* permission flags */
DECL|member|start_sect
id|__u32
id|start_sect
suffix:semicolon
multiline_comment|/* starting sector */
DECL|member|nr_sects
id|__u32
id|nr_sects
suffix:semicolon
multiline_comment|/* number of sectors in slice */
)brace
suffix:semicolon
DECL|struct|unixware_disklabel
r_struct
id|unixware_disklabel
(brace
DECL|member|d_type
id|__u32
id|d_type
suffix:semicolon
multiline_comment|/* drive type */
DECL|member|d_magic
id|__u32
id|d_magic
suffix:semicolon
multiline_comment|/* the magic number */
DECL|member|d_version
id|__u32
id|d_version
suffix:semicolon
multiline_comment|/* version number */
DECL|member|d_serial
r_char
id|d_serial
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* serial number of the device */
DECL|member|d_ncylinders
id|__u32
id|d_ncylinders
suffix:semicolon
multiline_comment|/* # of data cylinders per device */
DECL|member|d_ntracks
id|__u32
id|d_ntracks
suffix:semicolon
multiline_comment|/* # of tracks per cylinder */
DECL|member|d_nsectors
id|__u32
id|d_nsectors
suffix:semicolon
multiline_comment|/* # of data sectors per track */
DECL|member|d_secsize
id|__u32
id|d_secsize
suffix:semicolon
multiline_comment|/* # of bytes per sector */
DECL|member|d_part_start
id|__u32
id|d_part_start
suffix:semicolon
multiline_comment|/* # of first sector of this partition */
DECL|member|d_unknown1
id|__u32
id|d_unknown1
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* ? */
DECL|member|d_alt_tbl
id|__u32
id|d_alt_tbl
suffix:semicolon
multiline_comment|/* byte offset of alternate table */
DECL|member|d_alt_len
id|__u32
id|d_alt_len
suffix:semicolon
multiline_comment|/* byte length of alternate table */
DECL|member|d_phys_cyl
id|__u32
id|d_phys_cyl
suffix:semicolon
multiline_comment|/* # of physical cylinders per device */
DECL|member|d_phys_trk
id|__u32
id|d_phys_trk
suffix:semicolon
multiline_comment|/* # of physical tracks per cylinder */
DECL|member|d_phys_sec
id|__u32
id|d_phys_sec
suffix:semicolon
multiline_comment|/* # of physical sectors per track */
DECL|member|d_phys_bytes
id|__u32
id|d_phys_bytes
suffix:semicolon
multiline_comment|/* # of physical bytes per sector */
DECL|member|d_unknown2
id|__u32
id|d_unknown2
suffix:semicolon
multiline_comment|/* ? */
DECL|member|d_unknown3
id|__u32
id|d_unknown3
suffix:semicolon
multiline_comment|/* ? */
DECL|member|d_pad
id|__u32
id|d_pad
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* pad */
DECL|struct|unixware_vtoc
r_struct
id|unixware_vtoc
(brace
DECL|member|v_magic
id|__u32
id|v_magic
suffix:semicolon
multiline_comment|/* the magic number */
DECL|member|v_version
id|__u32
id|v_version
suffix:semicolon
multiline_comment|/* version number */
DECL|member|v_name
r_char
id|v_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* volume name */
DECL|member|v_nslices
id|__u16
id|v_nslices
suffix:semicolon
multiline_comment|/* # of slices */
DECL|member|v_unknown1
id|__u16
id|v_unknown1
suffix:semicolon
multiline_comment|/* ? */
DECL|member|v_reserved
id|__u32
id|v_reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* reserved */
r_struct
id|unixware_slice
DECL|member|v_slice
id|v_slice
(braket
id|UNIXWARE_NUMSLICE
)braket
suffix:semicolon
multiline_comment|/* slice headers */
DECL|member|vtoc
)brace
id|vtoc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* 408 */
macro_line|#endif /* CONFIG_UNIXWARE_DISKLABEL */
macro_line|#ifdef CONFIG_MINIX_SUBPARTITION
DECL|macro|MINIX_NR_SUBPARTITIONS
macro_line|#   define MINIX_NR_SUBPARTITIONS  4
macro_line|#endif /* CONFIG_MINIX_SUBPARTITION */
macro_line|#ifdef __KERNEL__
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
id|part
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|add_partition
c_func
(paren
r_struct
id|gendisk
op_star
comma
r_int
comma
id|sector_t
comma
id|sector_t
)paren
suffix:semicolon
r_extern
r_void
id|delete_partition
c_func
(paren
r_struct
id|gendisk
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|gendisk
op_star
id|alloc_disk
c_func
(paren
r_int
id|minors
)paren
suffix:semicolon
r_extern
r_struct
id|gendisk
op_star
id|get_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
suffix:semicolon
r_extern
r_void
id|put_disk
c_func
(paren
r_struct
id|gendisk
op_star
id|disk
)paren
suffix:semicolon
r_extern
r_void
id|blk_register_region
c_func
(paren
id|dev_t
id|dev
comma
r_int
r_int
id|range
comma
r_struct
id|module
op_star
id|module
comma
r_struct
id|gendisk
op_star
(paren
op_star
id|probe
)paren
(paren
id|dev_t
comma
r_int
op_star
comma
r_void
op_star
)paren
comma
r_int
(paren
op_star
id|lock
)paren
(paren
id|dev_t
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|blk_unregister_region
c_func
(paren
id|dev_t
id|dev
comma
r_int
r_int
id|range
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
