multiline_comment|/*&n; * Copyright (c) 1995-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2.1 of the GNU Lesser General Public License&n; * as published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU Lesser General Public&n; * License along with this program; if not, write the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307,&n; * USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_FS_H__
DECL|macro|__XFS_FS_H__
mdefine_line|#define __XFS_FS_H__
multiline_comment|/*&n; * SGI&squot;s XFS filesystem&squot;s major stuff (constants, structures)&n; */
DECL|macro|XFS_NAME
mdefine_line|#define XFS_NAME&t;&quot;xfs&quot;
multiline_comment|/*&n; * Direct I/O attribute record used with XFS_IOC_DIOINFO&n; * d_miniosz is the min xfer size, xfer size multiple and file seek offset&n; * alignment.&n; */
macro_line|#ifndef HAVE_DIOATTR
DECL|struct|dioattr
r_struct
id|dioattr
(brace
DECL|member|d_mem
id|__u32
id|d_mem
suffix:semicolon
multiline_comment|/* data buffer memory alignment */
DECL|member|d_miniosz
id|__u32
id|d_miniosz
suffix:semicolon
multiline_comment|/* min xfer size&t;&t;*/
DECL|member|d_maxiosz
id|__u32
id|d_maxiosz
suffix:semicolon
multiline_comment|/* max xfer size&t;&t;*/
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Structure for XFS_IOC_FSGETXATTR[A] and XFS_IOC_FSSETXATTR.&n; */
macro_line|#ifndef HAVE_FSXATTR
DECL|struct|fsxattr
r_struct
id|fsxattr
(brace
DECL|member|fsx_xflags
id|__u32
id|fsx_xflags
suffix:semicolon
multiline_comment|/* xflags field value (get/set) */
DECL|member|fsx_extsize
id|__u32
id|fsx_extsize
suffix:semicolon
multiline_comment|/* extsize field value (get/set)*/
DECL|member|fsx_nextents
id|__u32
id|fsx_nextents
suffix:semicolon
multiline_comment|/* nextents field value (get)&t;*/
DECL|member|fsx_pad
r_int
r_char
id|fsx_pad
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Flags for the bs_xflags/fsx_xflags field&n; * There should be a one-to-one correspondence between these flags and the&n; * XFS_DIFLAG_s.&n; */
DECL|macro|XFS_XFLAG_REALTIME
mdefine_line|#define XFS_XFLAG_REALTIME&t;0x00000001&t;/* data in realtime volume */
DECL|macro|XFS_XFLAG_PREALLOC
mdefine_line|#define XFS_XFLAG_PREALLOC&t;0x00000002&t;/* preallocated file extents */
DECL|macro|XFS_XFLAG_IMMUTABLE
mdefine_line|#define XFS_XFLAG_IMMUTABLE&t;0x00000008&t;/* file cannot be modified */
DECL|macro|XFS_XFLAG_APPEND
mdefine_line|#define XFS_XFLAG_APPEND&t;0x00000010&t;/* all writes append */
DECL|macro|XFS_XFLAG_SYNC
mdefine_line|#define XFS_XFLAG_SYNC&t;&t;0x00000020&t;/* all writes synchronous */
DECL|macro|XFS_XFLAG_NOATIME
mdefine_line|#define XFS_XFLAG_NOATIME&t;0x00000040&t;/* do not update access time */
DECL|macro|XFS_XFLAG_NODUMP
mdefine_line|#define XFS_XFLAG_NODUMP&t;0x00000080&t;/* do not include in backups */
DECL|macro|XFS_XFLAG_RTINHERIT
mdefine_line|#define XFS_XFLAG_RTINHERIT&t;0x00000100&t;/* create with rt bit set */
DECL|macro|XFS_XFLAG_PROJINHERIT
mdefine_line|#define XFS_XFLAG_PROJINHERIT&t;0x00000200&t;/* create with parents projid */
DECL|macro|XFS_XFLAG_NOSYMLINKS
mdefine_line|#define XFS_XFLAG_NOSYMLINKS&t;0x00000400&t;/* disallow symlink creation */
DECL|macro|XFS_XFLAG_HASATTR
mdefine_line|#define XFS_XFLAG_HASATTR&t;0x80000000&t;/* no DIFLAG for this&t;*/
multiline_comment|/*&n; * Structure for XFS_IOC_GETBMAP.&n; * On input, fill in bmv_offset and bmv_length of the first structure&n; * to indicate the area of interest in the file, and bmv_entry with the&n; * number of array elements given.  The first structure is updated on&n; * return to give the offset and length for the next call.&n; */
macro_line|#ifndef HAVE_GETBMAP
DECL|struct|getbmap
r_struct
id|getbmap
(brace
DECL|member|bmv_offset
id|__s64
id|bmv_offset
suffix:semicolon
multiline_comment|/* file offset of segment in blocks */
DECL|member|bmv_block
id|__s64
id|bmv_block
suffix:semicolon
multiline_comment|/* starting block (64-bit daddr_t)  */
DECL|member|bmv_length
id|__s64
id|bmv_length
suffix:semicolon
multiline_comment|/* length of segment, blocks&t;    */
DECL|member|bmv_count
id|__s32
id|bmv_count
suffix:semicolon
multiline_comment|/* # of entries in array incl. 1st  */
DECL|member|bmv_entries
id|__s32
id|bmv_entries
suffix:semicolon
multiline_comment|/* # of entries filled in (output)  */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Structure for XFS_IOC_GETBMAPX.&t; Fields bmv_offset through bmv_entries&n; *&t;are used exactly as in the getbmap structure.  The getbmapx structure&n; *&t;has additional bmv_iflags and bmv_oflags fields. The bmv_iflags field&n; *&t;is only used for the first structure.  It contains input flags&n; *&t;specifying XFS_IOC_GETBMAPX actions.  The bmv_oflags field is filled&n; *&t;in by the XFS_IOC_GETBMAPX command for each returned structure after&n; *&t;the first.&n; */
macro_line|#ifndef HAVE_GETBMAPX
DECL|struct|getbmapx
r_struct
id|getbmapx
(brace
DECL|member|bmv_offset
id|__s64
id|bmv_offset
suffix:semicolon
multiline_comment|/* file offset of segment in blocks */
DECL|member|bmv_block
id|__s64
id|bmv_block
suffix:semicolon
multiline_comment|/* starting block (64-bit daddr_t)  */
DECL|member|bmv_length
id|__s64
id|bmv_length
suffix:semicolon
multiline_comment|/* length of segment, blocks&t;    */
DECL|member|bmv_count
id|__s32
id|bmv_count
suffix:semicolon
multiline_comment|/* # of entries in array incl. 1st  */
DECL|member|bmv_entries
id|__s32
id|bmv_entries
suffix:semicolon
multiline_comment|/* # of entries filled in (output). */
DECL|member|bmv_iflags
id|__s32
id|bmv_iflags
suffix:semicolon
multiline_comment|/* input flags (1st structure)&t;    */
DECL|member|bmv_oflags
id|__s32
id|bmv_oflags
suffix:semicolon
multiline_comment|/* output flags (after 1st structure)*/
DECL|member|bmv_unused1
id|__s32
id|bmv_unused1
suffix:semicolon
multiline_comment|/* future use&t;&t;&t;    */
DECL|member|bmv_unused2
id|__s32
id|bmv_unused2
suffix:semicolon
multiline_comment|/* future use&t;&t;&t;    */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&t;bmv_iflags values - set by XFS_IOC_GETBMAPX caller.&t;*/
DECL|macro|BMV_IF_ATTRFORK
mdefine_line|#define BMV_IF_ATTRFORK&t;&t;0x1&t;/* return attr fork rather than data */
DECL|macro|BMV_IF_NO_DMAPI_READ
mdefine_line|#define BMV_IF_NO_DMAPI_READ&t;0x2&t;/* Do not generate DMAPI read event  */
DECL|macro|BMV_IF_PREALLOC
mdefine_line|#define BMV_IF_PREALLOC&t;&t;0x4&t;/* rtn status BMV_OF_PREALLOC if req */
DECL|macro|BMV_IF_VALID
mdefine_line|#define BMV_IF_VALID&t;(BMV_IF_ATTRFORK|BMV_IF_NO_DMAPI_READ|BMV_IF_PREALLOC)
macro_line|#ifdef __KERNEL__
DECL|macro|BMV_IF_EXTENDED
mdefine_line|#define BMV_IF_EXTENDED 0x40000000&t;/* getpmapx if set */
macro_line|#endif
multiline_comment|/*&t;bmv_oflags values - returned for for each non-header segment */
DECL|macro|BMV_OF_PREALLOC
mdefine_line|#define BMV_OF_PREALLOC&t;&t;0x1&t;/* segment = unwritten pre-allocation */
multiline_comment|/*&t;Convert getbmap &lt;-&gt; getbmapx - move fields from p1 to p2. */
DECL|macro|GETBMAP_CONVERT
mdefine_line|#define GETBMAP_CONVERT(p1,p2) {&t;&bslash;&n;&t;p2.bmv_offset = p1.bmv_offset;&t;&bslash;&n;&t;p2.bmv_block = p1.bmv_block;&t;&bslash;&n;&t;p2.bmv_length = p1.bmv_length;&t;&bslash;&n;&t;p2.bmv_count = p1.bmv_count;&t;&bslash;&n;&t;p2.bmv_entries = p1.bmv_entries;  }
multiline_comment|/*&n; * Structure for XFS_IOC_FSSETDM.&n; * For use by backup and restore programs to set the XFS on-disk inode&n; * fields di_dmevmask and di_dmstate.  These must be set to exactly and&n; * only values previously obtained via xfs_bulkstat!  (Specifically the&n; * xfs_bstat_t fields bs_dmevmask and bs_dmstate.)&n; */
macro_line|#ifndef HAVE_FSDMIDATA
DECL|struct|fsdmidata
r_struct
id|fsdmidata
(brace
DECL|member|fsd_dmevmask
id|__u32
id|fsd_dmevmask
suffix:semicolon
multiline_comment|/* corresponds to di_dmevmask */
DECL|member|fsd_padding
id|__u16
id|fsd_padding
suffix:semicolon
DECL|member|fsd_dmstate
id|__u16
id|fsd_dmstate
suffix:semicolon
multiline_comment|/* corresponds to di_dmstate  */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * File segment locking set data type for 64 bit access.&n; * Also used for all the RESV/FREE interfaces.&n; */
DECL|struct|xfs_flock64
r_typedef
r_struct
id|xfs_flock64
(brace
DECL|member|l_type
id|__s16
id|l_type
suffix:semicolon
DECL|member|l_whence
id|__s16
id|l_whence
suffix:semicolon
DECL|member|l_start
id|__s64
id|l_start
suffix:semicolon
DECL|member|l_len
id|__s64
id|l_len
suffix:semicolon
multiline_comment|/* len == 0 means until end of file */
DECL|member|l_sysid
id|__s32
id|l_sysid
suffix:semicolon
DECL|member|l_pid
id|__u32
id|l_pid
suffix:semicolon
DECL|member|l_pad
id|__s32
id|l_pad
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserve area&t;&t;&t;    */
DECL|typedef|xfs_flock64_t
)brace
id|xfs_flock64_t
suffix:semicolon
multiline_comment|/*&n; * Output for XFS_IOC_FSGEOMETRY_V1&n; */
DECL|struct|xfs_fsop_geom_v1
r_typedef
r_struct
id|xfs_fsop_geom_v1
(brace
DECL|member|blocksize
id|__u32
id|blocksize
suffix:semicolon
multiline_comment|/* filesystem (data) block size */
DECL|member|rtextsize
id|__u32
id|rtextsize
suffix:semicolon
multiline_comment|/* realtime extent size&t;&t;*/
DECL|member|agblocks
id|__u32
id|agblocks
suffix:semicolon
multiline_comment|/* fsblocks in an AG&t;&t;*/
DECL|member|agcount
id|__u32
id|agcount
suffix:semicolon
multiline_comment|/* number of allocation groups&t;*/
DECL|member|logblocks
id|__u32
id|logblocks
suffix:semicolon
multiline_comment|/* fsblocks in the log&t;&t;*/
DECL|member|sectsize
id|__u32
id|sectsize
suffix:semicolon
multiline_comment|/* (data) sector size, bytes&t;*/
DECL|member|inodesize
id|__u32
id|inodesize
suffix:semicolon
multiline_comment|/* inode size in bytes&t;&t;*/
DECL|member|imaxpct
id|__u32
id|imaxpct
suffix:semicolon
multiline_comment|/* max allowed inode space(%)&t;*/
DECL|member|datablocks
id|__u64
id|datablocks
suffix:semicolon
multiline_comment|/* fsblocks in data subvolume&t;*/
DECL|member|rtblocks
id|__u64
id|rtblocks
suffix:semicolon
multiline_comment|/* fsblocks in realtime subvol&t;*/
DECL|member|rtextents
id|__u64
id|rtextents
suffix:semicolon
multiline_comment|/* rt extents in realtime subvol*/
DECL|member|logstart
id|__u64
id|logstart
suffix:semicolon
multiline_comment|/* starting fsblock of the log&t;*/
DECL|member|uuid
r_int
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* unique id of the filesystem&t;*/
DECL|member|sunit
id|__u32
id|sunit
suffix:semicolon
multiline_comment|/* stripe unit, fsblocks&t;*/
DECL|member|swidth
id|__u32
id|swidth
suffix:semicolon
multiline_comment|/* stripe width, fsblocks&t;*/
DECL|member|version
id|__s32
id|version
suffix:semicolon
multiline_comment|/* structure version&t;&t;*/
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* superblock version flags&t;*/
DECL|member|logsectsize
id|__u32
id|logsectsize
suffix:semicolon
multiline_comment|/* log sector size, bytes&t;*/
DECL|member|rtsectsize
id|__u32
id|rtsectsize
suffix:semicolon
multiline_comment|/* realtime sector size, bytes&t;*/
DECL|member|dirblocksize
id|__u32
id|dirblocksize
suffix:semicolon
multiline_comment|/* directory block size, bytes&t;*/
DECL|typedef|xfs_fsop_geom_v1_t
)brace
id|xfs_fsop_geom_v1_t
suffix:semicolon
multiline_comment|/*&n; * Output for XFS_IOC_FSGEOMETRY&n; */
DECL|struct|xfs_fsop_geom
r_typedef
r_struct
id|xfs_fsop_geom
(brace
DECL|member|blocksize
id|__u32
id|blocksize
suffix:semicolon
multiline_comment|/* filesystem (data) block size */
DECL|member|rtextsize
id|__u32
id|rtextsize
suffix:semicolon
multiline_comment|/* realtime extent size&t;&t;*/
DECL|member|agblocks
id|__u32
id|agblocks
suffix:semicolon
multiline_comment|/* fsblocks in an AG&t;&t;*/
DECL|member|agcount
id|__u32
id|agcount
suffix:semicolon
multiline_comment|/* number of allocation groups&t;*/
DECL|member|logblocks
id|__u32
id|logblocks
suffix:semicolon
multiline_comment|/* fsblocks in the log&t;&t;*/
DECL|member|sectsize
id|__u32
id|sectsize
suffix:semicolon
multiline_comment|/* (data) sector size, bytes&t;*/
DECL|member|inodesize
id|__u32
id|inodesize
suffix:semicolon
multiline_comment|/* inode size in bytes&t;&t;*/
DECL|member|imaxpct
id|__u32
id|imaxpct
suffix:semicolon
multiline_comment|/* max allowed inode space(%)&t;*/
DECL|member|datablocks
id|__u64
id|datablocks
suffix:semicolon
multiline_comment|/* fsblocks in data subvolume&t;*/
DECL|member|rtblocks
id|__u64
id|rtblocks
suffix:semicolon
multiline_comment|/* fsblocks in realtime subvol&t;*/
DECL|member|rtextents
id|__u64
id|rtextents
suffix:semicolon
multiline_comment|/* rt extents in realtime subvol*/
DECL|member|logstart
id|__u64
id|logstart
suffix:semicolon
multiline_comment|/* starting fsblock of the log&t;*/
DECL|member|uuid
r_int
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* unique id of the filesystem&t;*/
DECL|member|sunit
id|__u32
id|sunit
suffix:semicolon
multiline_comment|/* stripe unit, fsblocks&t;*/
DECL|member|swidth
id|__u32
id|swidth
suffix:semicolon
multiline_comment|/* stripe width, fsblocks&t;*/
DECL|member|version
id|__s32
id|version
suffix:semicolon
multiline_comment|/* structure version&t;&t;*/
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* superblock version flags&t;*/
DECL|member|logsectsize
id|__u32
id|logsectsize
suffix:semicolon
multiline_comment|/* log sector size, bytes&t;*/
DECL|member|rtsectsize
id|__u32
id|rtsectsize
suffix:semicolon
multiline_comment|/* realtime sector size, bytes&t;*/
DECL|member|dirblocksize
id|__u32
id|dirblocksize
suffix:semicolon
multiline_comment|/* directory block size, bytes&t;*/
DECL|member|logsunit
id|__u32
id|logsunit
suffix:semicolon
multiline_comment|/* log stripe unit, bytes */
DECL|typedef|xfs_fsop_geom_t
)brace
id|xfs_fsop_geom_t
suffix:semicolon
multiline_comment|/* Output for XFS_FS_COUNTS */
DECL|struct|xfs_fsop_counts
r_typedef
r_struct
id|xfs_fsop_counts
(brace
DECL|member|freedata
id|__u64
id|freedata
suffix:semicolon
multiline_comment|/* free data section blocks */
DECL|member|freertx
id|__u64
id|freertx
suffix:semicolon
multiline_comment|/* free rt extents */
DECL|member|freeino
id|__u64
id|freeino
suffix:semicolon
multiline_comment|/* free inodes */
DECL|member|allocino
id|__u64
id|allocino
suffix:semicolon
multiline_comment|/* total allocated inodes */
DECL|typedef|xfs_fsop_counts_t
)brace
id|xfs_fsop_counts_t
suffix:semicolon
multiline_comment|/* Input/Output for XFS_GET_RESBLKS and XFS_SET_RESBLKS */
DECL|struct|xfs_fsop_resblks
r_typedef
r_struct
id|xfs_fsop_resblks
(brace
DECL|member|resblks
id|__u64
id|resblks
suffix:semicolon
DECL|member|resblks_avail
id|__u64
id|resblks_avail
suffix:semicolon
DECL|typedef|xfs_fsop_resblks_t
)brace
id|xfs_fsop_resblks_t
suffix:semicolon
DECL|macro|XFS_FSOP_GEOM_VERSION
mdefine_line|#define XFS_FSOP_GEOM_VERSION&t;0
DECL|macro|XFS_FSOP_GEOM_FLAGS_ATTR
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_ATTR&t;0x0001&t;/* attributes in use&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_NLINK
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_NLINK&t;0x0002&t;/* 32-bit nlink values&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_QUOTA
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_QUOTA&t;0x0004&t;/* quotas enabled&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_IALIGN
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_IALIGN&t;0x0008&t;/* inode alignment&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_DALIGN
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_DALIGN&t;0x0010&t;/* large data alignment */
DECL|macro|XFS_FSOP_GEOM_FLAGS_SHARED
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_SHARED&t;0x0020&t;/* read-only shared&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_EXTFLG
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_EXTFLG&t;0x0040&t;/* special extent flag&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_DIRV2
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_DIRV2&t;0x0080&t;/* directory version 2&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_LOGV2
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_LOGV2&t;0x0100&t;/* log format version 2&t;*/
DECL|macro|XFS_FSOP_GEOM_FLAGS_SECTOR
mdefine_line|#define XFS_FSOP_GEOM_FLAGS_SECTOR&t;0x0200&t;/* sector sizes &gt;1BB&t;*/
multiline_comment|/*&n; * Minimum and maximum sizes need for growth checks&n; */
DECL|macro|XFS_MIN_AG_BLOCKS
mdefine_line|#define XFS_MIN_AG_BLOCKS&t;64
DECL|macro|XFS_MIN_LOG_BLOCKS
mdefine_line|#define XFS_MIN_LOG_BLOCKS&t;512
DECL|macro|XFS_MAX_LOG_BLOCKS
mdefine_line|#define XFS_MAX_LOG_BLOCKS&t;(64 * 1024)
DECL|macro|XFS_MIN_LOG_BYTES
mdefine_line|#define XFS_MIN_LOG_BYTES&t;(256 * 1024)
DECL|macro|XFS_MAX_LOG_BYTES
mdefine_line|#define XFS_MAX_LOG_BYTES&t;(128 * 1024 * 1024)
multiline_comment|/*&n; * Structures for XFS_IOC_FSGROWFSDATA, XFS_IOC_FSGROWFSLOG &amp; XFS_IOC_FSGROWFSRT&n; */
DECL|struct|xfs_growfs_data
r_typedef
r_struct
id|xfs_growfs_data
(brace
DECL|member|newblocks
id|__u64
id|newblocks
suffix:semicolon
multiline_comment|/* new data subvol size, fsblocks */
DECL|member|imaxpct
id|__u32
id|imaxpct
suffix:semicolon
multiline_comment|/* new inode space percentage limit */
DECL|typedef|xfs_growfs_data_t
)brace
id|xfs_growfs_data_t
suffix:semicolon
DECL|struct|xfs_growfs_log
r_typedef
r_struct
id|xfs_growfs_log
(brace
DECL|member|newblocks
id|__u32
id|newblocks
suffix:semicolon
multiline_comment|/* new log size, fsblocks */
DECL|member|isint
id|__u32
id|isint
suffix:semicolon
multiline_comment|/* 1 if new log is internal */
DECL|typedef|xfs_growfs_log_t
)brace
id|xfs_growfs_log_t
suffix:semicolon
DECL|struct|xfs_growfs_rt
r_typedef
r_struct
id|xfs_growfs_rt
(brace
DECL|member|newblocks
id|__u64
id|newblocks
suffix:semicolon
multiline_comment|/* new realtime size, fsblocks */
DECL|member|extsize
id|__u32
id|extsize
suffix:semicolon
multiline_comment|/* new realtime extent size, fsblocks */
DECL|typedef|xfs_growfs_rt_t
)brace
id|xfs_growfs_rt_t
suffix:semicolon
multiline_comment|/*&n; * Structures returned from ioctl XFS_IOC_FSBULKSTAT &amp; XFS_IOC_FSBULKSTAT_SINGLE&n; */
DECL|struct|xfs_bstime
r_typedef
r_struct
id|xfs_bstime
(brace
DECL|member|tv_sec
id|time_t
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds&t;&t;*/
DECL|member|tv_nsec
id|__s32
id|tv_nsec
suffix:semicolon
multiline_comment|/* and nanoseconds&t;*/
DECL|typedef|xfs_bstime_t
)brace
id|xfs_bstime_t
suffix:semicolon
DECL|struct|xfs_bstat
r_typedef
r_struct
id|xfs_bstat
(brace
DECL|member|bs_ino
id|__u64
id|bs_ino
suffix:semicolon
multiline_comment|/* inode number&t;&t;&t;*/
DECL|member|bs_mode
id|__u16
id|bs_mode
suffix:semicolon
multiline_comment|/* type and mode&t;&t;*/
DECL|member|bs_nlink
id|__u16
id|bs_nlink
suffix:semicolon
multiline_comment|/* number of links&t;&t;*/
DECL|member|bs_uid
id|__u32
id|bs_uid
suffix:semicolon
multiline_comment|/* user id&t;&t;&t;*/
DECL|member|bs_gid
id|__u32
id|bs_gid
suffix:semicolon
multiline_comment|/* group id&t;&t;&t;*/
DECL|member|bs_rdev
id|__u32
id|bs_rdev
suffix:semicolon
multiline_comment|/* device value&t;&t;&t;*/
DECL|member|bs_blksize
id|__s32
id|bs_blksize
suffix:semicolon
multiline_comment|/* block size&t;&t;&t;*/
DECL|member|bs_size
id|__s64
id|bs_size
suffix:semicolon
multiline_comment|/* file size&t;&t;&t;*/
DECL|member|bs_atime
id|xfs_bstime_t
id|bs_atime
suffix:semicolon
multiline_comment|/* access time&t;&t;&t;*/
DECL|member|bs_mtime
id|xfs_bstime_t
id|bs_mtime
suffix:semicolon
multiline_comment|/* modify time&t;&t;&t;*/
DECL|member|bs_ctime
id|xfs_bstime_t
id|bs_ctime
suffix:semicolon
multiline_comment|/* inode change time&t;&t;*/
DECL|member|bs_blocks
r_int64
id|bs_blocks
suffix:semicolon
multiline_comment|/* number of blocks&t;&t;*/
DECL|member|bs_xflags
id|__u32
id|bs_xflags
suffix:semicolon
multiline_comment|/* extended flags&t;&t;*/
DECL|member|bs_extsize
id|__s32
id|bs_extsize
suffix:semicolon
multiline_comment|/* extent size&t;&t;&t;*/
DECL|member|bs_extents
id|__s32
id|bs_extents
suffix:semicolon
multiline_comment|/* number of extents&t;&t;*/
DECL|member|bs_gen
id|__u32
id|bs_gen
suffix:semicolon
multiline_comment|/* generation count&t;&t;*/
DECL|member|bs_projid
id|__u16
id|bs_projid
suffix:semicolon
multiline_comment|/* project id&t;&t;&t;*/
DECL|member|bs_pad
r_int
r_char
id|bs_pad
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* pad space, unused&t;&t;*/
DECL|member|bs_dmevmask
id|__u32
id|bs_dmevmask
suffix:semicolon
multiline_comment|/* DMIG event mask&t;&t;*/
DECL|member|bs_dmstate
id|__u16
id|bs_dmstate
suffix:semicolon
multiline_comment|/* DMIG state info&t;&t;*/
DECL|member|bs_aextents
id|__u16
id|bs_aextents
suffix:semicolon
multiline_comment|/* attribute number of extents&t;*/
DECL|typedef|xfs_bstat_t
)brace
id|xfs_bstat_t
suffix:semicolon
multiline_comment|/*&n; * The user-level BulkStat Request interface structure.&n; */
DECL|struct|xfs_fsop_bulkreq
r_typedef
r_struct
id|xfs_fsop_bulkreq
(brace
DECL|member|lastip
id|__u64
id|__user
op_star
id|lastip
suffix:semicolon
multiline_comment|/* last inode # pointer&t;&t;*/
DECL|member|icount
id|__s32
id|icount
suffix:semicolon
multiline_comment|/* count of entries in buffer&t;*/
DECL|member|ubuffer
r_void
id|__user
op_star
id|ubuffer
suffix:semicolon
multiline_comment|/* user buffer for inode desc.&t;*/
DECL|member|ocount
id|__s32
id|__user
op_star
id|ocount
suffix:semicolon
multiline_comment|/* output count pointer&t;&t;*/
DECL|typedef|xfs_fsop_bulkreq_t
)brace
id|xfs_fsop_bulkreq_t
suffix:semicolon
multiline_comment|/*&n; * Structures returned from xfs_inumbers routine (XFS_IOC_FSINUMBERS).&n; */
DECL|struct|xfs_inogrp
r_typedef
r_struct
id|xfs_inogrp
(brace
DECL|member|xi_startino
id|__u64
id|xi_startino
suffix:semicolon
multiline_comment|/* starting inode number&t;*/
DECL|member|xi_alloccount
id|__s32
id|xi_alloccount
suffix:semicolon
multiline_comment|/* # bits set in allocmask&t;*/
DECL|member|xi_allocmask
id|__u64
id|xi_allocmask
suffix:semicolon
multiline_comment|/* mask of allocated inodes&t;*/
DECL|typedef|xfs_inogrp_t
)brace
id|xfs_inogrp_t
suffix:semicolon
multiline_comment|/*&n; * Error injection.&n; */
DECL|struct|xfs_error_injection
r_typedef
r_struct
id|xfs_error_injection
(brace
DECL|member|fd
id|__s32
id|fd
suffix:semicolon
DECL|member|errtag
id|__s32
id|errtag
suffix:semicolon
DECL|typedef|xfs_error_injection_t
)brace
id|xfs_error_injection_t
suffix:semicolon
multiline_comment|/*&n; * The user-level Handle Request interface structure.&n; */
DECL|struct|xfs_fsop_handlereq
r_typedef
r_struct
id|xfs_fsop_handlereq
(brace
DECL|member|fd
id|__u32
id|fd
suffix:semicolon
multiline_comment|/* fd for FD_TO_HANDLE&t;&t;*/
DECL|member|path
r_void
id|__user
op_star
id|path
suffix:semicolon
multiline_comment|/* user pathname&t;&t;*/
DECL|member|oflags
id|__u32
id|oflags
suffix:semicolon
multiline_comment|/* open flags&t;&t;&t;*/
DECL|member|ihandle
r_void
id|__user
op_star
id|ihandle
suffix:semicolon
multiline_comment|/* user supplied handle&t;&t;*/
DECL|member|ihandlen
id|__u32
id|ihandlen
suffix:semicolon
multiline_comment|/* user supplied length&t;&t;*/
DECL|member|ohandle
r_void
id|__user
op_star
id|ohandle
suffix:semicolon
multiline_comment|/* user buffer for handle&t;*/
DECL|member|ohandlen
id|__u32
id|__user
op_star
id|ohandlen
suffix:semicolon
multiline_comment|/* user buffer length&t;&t;*/
DECL|typedef|xfs_fsop_handlereq_t
)brace
id|xfs_fsop_handlereq_t
suffix:semicolon
multiline_comment|/*&n; * Compound structures for passing args through Handle Request interfaces&n; * xfs_fssetdm_by_handle, xfs_attrlist_by_handle, xfs_attrmulti_by_handle&n; * - ioctls: XFS_IOC_FSSETDM_BY_HANDLE, XFS_IOC_ATTRLIST_BY_HANDLE, and&n; *&t;     XFS_IOC_ATTRMULTI_BY_HANDLE&n; */
DECL|struct|xfs_fsop_setdm_handlereq
r_typedef
r_struct
id|xfs_fsop_setdm_handlereq
(brace
DECL|member|hreq
r_struct
id|xfs_fsop_handlereq
id|hreq
suffix:semicolon
multiline_comment|/* handle information&t;*/
DECL|member|data
r_struct
id|fsdmidata
id|__user
op_star
id|data
suffix:semicolon
multiline_comment|/* DMAPI data&t;*/
DECL|typedef|xfs_fsop_setdm_handlereq_t
)brace
id|xfs_fsop_setdm_handlereq_t
suffix:semicolon
DECL|struct|xfs_attrlist_cursor
r_typedef
r_struct
id|xfs_attrlist_cursor
(brace
DECL|member|opaque
id|__u32
id|opaque
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|xfs_attrlist_cursor_t
)brace
id|xfs_attrlist_cursor_t
suffix:semicolon
DECL|struct|xfs_fsop_attrlist_handlereq
r_typedef
r_struct
id|xfs_fsop_attrlist_handlereq
(brace
DECL|member|hreq
r_struct
id|xfs_fsop_handlereq
id|hreq
suffix:semicolon
multiline_comment|/* handle interface structure */
DECL|member|pos
r_struct
id|xfs_attrlist_cursor
id|pos
suffix:semicolon
multiline_comment|/* opaque cookie, list offset */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* which namespace to use */
DECL|member|buflen
id|__u32
id|buflen
suffix:semicolon
multiline_comment|/* length of buffer supplied */
DECL|member|buffer
r_void
id|__user
op_star
id|buffer
suffix:semicolon
multiline_comment|/* returned names */
DECL|typedef|xfs_fsop_attrlist_handlereq_t
)brace
id|xfs_fsop_attrlist_handlereq_t
suffix:semicolon
DECL|struct|xfs_attr_multiop
r_typedef
r_struct
id|xfs_attr_multiop
(brace
DECL|member|am_opcode
id|__u32
id|am_opcode
suffix:semicolon
DECL|member|am_error
id|__s32
id|am_error
suffix:semicolon
DECL|member|am_attrname
r_void
id|__user
op_star
id|am_attrname
suffix:semicolon
DECL|member|am_attrvalue
r_void
id|__user
op_star
id|am_attrvalue
suffix:semicolon
DECL|member|am_length
id|__u32
id|am_length
suffix:semicolon
DECL|member|am_flags
id|__u32
id|am_flags
suffix:semicolon
DECL|typedef|xfs_attr_multiop_t
)brace
id|xfs_attr_multiop_t
suffix:semicolon
DECL|struct|xfs_fsop_attrmulti_handlereq
r_typedef
r_struct
id|xfs_fsop_attrmulti_handlereq
(brace
DECL|member|hreq
r_struct
id|xfs_fsop_handlereq
id|hreq
suffix:semicolon
multiline_comment|/* handle interface structure */
DECL|member|opcount
id|__u32
id|opcount
suffix:semicolon
multiline_comment|/* count of following multiop */
DECL|member|ops
r_struct
id|xfs_attr_multiop
id|__user
op_star
id|ops
suffix:semicolon
multiline_comment|/* attr_multi data */
DECL|typedef|xfs_fsop_attrmulti_handlereq_t
)brace
id|xfs_fsop_attrmulti_handlereq_t
suffix:semicolon
multiline_comment|/*&n; * per machine unique filesystem identifier types.&n; */
DECL|member|val
DECL|typedef|xfs_fsid_t
r_typedef
r_struct
(brace
id|__u32
id|val
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|xfs_fsid_t
suffix:semicolon
multiline_comment|/* file system id type */
macro_line|#ifndef HAVE_FID
DECL|macro|MAXFIDSZ
mdefine_line|#define MAXFIDSZ&t;46
DECL|struct|fid
r_typedef
r_struct
id|fid
(brace
DECL|member|fid_len
id|__u16
id|fid_len
suffix:semicolon
multiline_comment|/* length of data in bytes */
DECL|member|fid_data
r_int
r_char
id|fid_data
(braket
id|MAXFIDSZ
)braket
suffix:semicolon
multiline_comment|/* data (fid_len worth)  */
DECL|typedef|fid_t
)brace
id|fid_t
suffix:semicolon
macro_line|#endif
DECL|struct|xfs_fid
r_typedef
r_struct
id|xfs_fid
(brace
DECL|member|xfs_fid_len
id|__u16
id|xfs_fid_len
suffix:semicolon
multiline_comment|/* length of remainder&t;*/
DECL|member|xfs_fid_pad
id|__u16
id|xfs_fid_pad
suffix:semicolon
DECL|member|xfs_fid_gen
id|__u32
id|xfs_fid_gen
suffix:semicolon
multiline_comment|/* generation number&t;*/
DECL|member|xfs_fid_ino
id|__u64
id|xfs_fid_ino
suffix:semicolon
multiline_comment|/* 64 bits inode number */
DECL|typedef|xfs_fid_t
)brace
id|xfs_fid_t
suffix:semicolon
DECL|struct|xfs_fid2
r_typedef
r_struct
id|xfs_fid2
(brace
DECL|member|fid_len
id|__u16
id|fid_len
suffix:semicolon
multiline_comment|/* length of remainder */
DECL|member|fid_pad
id|__u16
id|fid_pad
suffix:semicolon
multiline_comment|/* padding, must be zero */
DECL|member|fid_gen
id|__u32
id|fid_gen
suffix:semicolon
multiline_comment|/* generation number */
DECL|member|fid_ino
id|__u64
id|fid_ino
suffix:semicolon
multiline_comment|/* inode number */
DECL|typedef|xfs_fid2_t
)brace
id|xfs_fid2_t
suffix:semicolon
DECL|struct|xfs_handle
r_typedef
r_struct
id|xfs_handle
(brace
r_union
(brace
DECL|member|align
id|__s64
id|align
suffix:semicolon
multiline_comment|/* force alignment of ha_fid&t; */
DECL|member|_ha_fsid
id|xfs_fsid_t
id|_ha_fsid
suffix:semicolon
multiline_comment|/* unique file system identifier */
DECL|member|ha_u
)brace
id|ha_u
suffix:semicolon
DECL|member|ha_fid
id|xfs_fid_t
id|ha_fid
suffix:semicolon
multiline_comment|/* file system specific file ID&t; */
DECL|typedef|xfs_handle_t
)brace
id|xfs_handle_t
suffix:semicolon
DECL|macro|ha_fsid
mdefine_line|#define ha_fsid ha_u._ha_fsid
DECL|macro|XFS_HSIZE
mdefine_line|#define XFS_HSIZE(handle)&t;(((char *) &amp;(handle).ha_fid.xfs_fid_pad&t; &bslash;&n;&t;&t;&t;&t; - (char *) &amp;(handle))&t;&t;&t;  &bslash;&n;&t;&t;&t;&t; + (handle).ha_fid.xfs_fid_len)
DECL|macro|XFS_HANDLE_CMP
mdefine_line|#define XFS_HANDLE_CMP(h1, h2)&t;memcmp(h1, h2, sizeof(xfs_handle_t))
DECL|macro|FSHSIZE
mdefine_line|#define FSHSIZE&t;&t;sizeof(fsid_t)
multiline_comment|/* &n; * Flags for going down operation&n; */
DECL|macro|XFS_FSOP_GOING_FLAGS_DEFAULT
mdefine_line|#define XFS_FSOP_GOING_FLAGS_DEFAULT&t;&t;0x0&t;/* going down */
DECL|macro|XFS_FSOP_GOING_FLAGS_LOGFLUSH
mdefine_line|#define XFS_FSOP_GOING_FLAGS_LOGFLUSH&t;&t;0x1&t;/* flush log but not data */
DECL|macro|XFS_FSOP_GOING_FLAGS_NOLOGFLUSH
mdefine_line|#define XFS_FSOP_GOING_FLAGS_NOLOGFLUSH&t;&t;0x2&t;/* don&squot;t flush log nor data */
multiline_comment|/*&n; * ioctl commands that are used by Linux filesystems&n; */
DECL|macro|XFS_IOC_GETXFLAGS
mdefine_line|#define XFS_IOC_GETXFLAGS&t;_IOR(&squot;f&squot;, 1, long)
DECL|macro|XFS_IOC_SETXFLAGS
mdefine_line|#define XFS_IOC_SETXFLAGS&t;_IOW(&squot;f&squot;, 2, long)
DECL|macro|XFS_IOC_GETVERSION
mdefine_line|#define XFS_IOC_GETVERSION&t;_IOR(&squot;v&squot;, 1, long)
multiline_comment|/*&n; * ioctl commands that replace IRIX fcntl()&squot;s&n; * For &squot;documentation&squot; purposed more than anything else,&n; * the &quot;cmd #&quot; field reflects the IRIX fcntl number.&n; */
DECL|macro|XFS_IOC_ALLOCSP
mdefine_line|#define XFS_IOC_ALLOCSP&t;&t;_IOW (&squot;X&squot;, 10, struct xfs_flock64)
DECL|macro|XFS_IOC_FREESP
mdefine_line|#define XFS_IOC_FREESP&t;&t;_IOW (&squot;X&squot;, 11, struct xfs_flock64)
DECL|macro|XFS_IOC_DIOINFO
mdefine_line|#define XFS_IOC_DIOINFO&t;&t;_IOR (&squot;X&squot;, 30, struct dioattr)
DECL|macro|XFS_IOC_FSGETXATTR
mdefine_line|#define XFS_IOC_FSGETXATTR&t;_IOR (&squot;X&squot;, 31, struct fsxattr)
DECL|macro|XFS_IOC_FSSETXATTR
mdefine_line|#define XFS_IOC_FSSETXATTR&t;_IOW (&squot;X&squot;, 32, struct fsxattr)
DECL|macro|XFS_IOC_ALLOCSP64
mdefine_line|#define XFS_IOC_ALLOCSP64&t;_IOW (&squot;X&squot;, 36, struct xfs_flock64)
DECL|macro|XFS_IOC_FREESP64
mdefine_line|#define XFS_IOC_FREESP64&t;_IOW (&squot;X&squot;, 37, struct xfs_flock64)
DECL|macro|XFS_IOC_GETBMAP
mdefine_line|#define XFS_IOC_GETBMAP&t;&t;_IOWR(&squot;X&squot;, 38, struct getbmap)
DECL|macro|XFS_IOC_FSSETDM
mdefine_line|#define XFS_IOC_FSSETDM&t;&t;_IOW (&squot;X&squot;, 39, struct fsdmidata)
DECL|macro|XFS_IOC_RESVSP
mdefine_line|#define XFS_IOC_RESVSP&t;&t;_IOW (&squot;X&squot;, 40, struct xfs_flock64)
DECL|macro|XFS_IOC_UNRESVSP
mdefine_line|#define XFS_IOC_UNRESVSP&t;_IOW (&squot;X&squot;, 41, struct xfs_flock64)
DECL|macro|XFS_IOC_RESVSP64
mdefine_line|#define XFS_IOC_RESVSP64&t;_IOW (&squot;X&squot;, 42, struct xfs_flock64)
DECL|macro|XFS_IOC_UNRESVSP64
mdefine_line|#define XFS_IOC_UNRESVSP64&t;_IOW (&squot;X&squot;, 43, struct xfs_flock64)
DECL|macro|XFS_IOC_GETBMAPA
mdefine_line|#define XFS_IOC_GETBMAPA&t;_IOWR(&squot;X&squot;, 44, struct getbmap)
DECL|macro|XFS_IOC_FSGETXATTRA
mdefine_line|#define XFS_IOC_FSGETXATTRA&t;_IOR (&squot;X&squot;, 45, struct fsxattr)
multiline_comment|/*&t;XFS_IOC_SETBIOSIZE ---- deprecated 46&t;   */
multiline_comment|/*&t;XFS_IOC_GETBIOSIZE ---- deprecated 47&t;   */
DECL|macro|XFS_IOC_GETBMAPX
mdefine_line|#define XFS_IOC_GETBMAPX&t;_IOWR(&squot;X&squot;, 56, struct getbmap)
multiline_comment|/*&n; * ioctl commands that replace IRIX syssgi()&squot;s&n; */
DECL|macro|XFS_IOC_FSGEOMETRY_V1
mdefine_line|#define XFS_IOC_FSGEOMETRY_V1&t;     _IOR (&squot;X&squot;, 100, struct xfs_fsop_geom_v1)
DECL|macro|XFS_IOC_FSBULKSTAT
mdefine_line|#define XFS_IOC_FSBULKSTAT&t;     _IOWR(&squot;X&squot;, 101, struct xfs_fsop_bulkreq)
DECL|macro|XFS_IOC_FSBULKSTAT_SINGLE
mdefine_line|#define XFS_IOC_FSBULKSTAT_SINGLE    _IOWR(&squot;X&squot;, 102, struct xfs_fsop_bulkreq)
DECL|macro|XFS_IOC_FSINUMBERS
mdefine_line|#define XFS_IOC_FSINUMBERS&t;     _IOWR(&squot;X&squot;, 103, struct xfs_fsop_bulkreq)
DECL|macro|XFS_IOC_PATH_TO_FSHANDLE
mdefine_line|#define XFS_IOC_PATH_TO_FSHANDLE     _IOWR(&squot;X&squot;, 104, struct xfs_fsop_handlereq)
DECL|macro|XFS_IOC_PATH_TO_HANDLE
mdefine_line|#define XFS_IOC_PATH_TO_HANDLE&t;     _IOWR(&squot;X&squot;, 105, struct xfs_fsop_handlereq)
DECL|macro|XFS_IOC_FD_TO_HANDLE
mdefine_line|#define XFS_IOC_FD_TO_HANDLE&t;     _IOWR(&squot;X&squot;, 106, struct xfs_fsop_handlereq)
DECL|macro|XFS_IOC_OPEN_BY_HANDLE
mdefine_line|#define XFS_IOC_OPEN_BY_HANDLE&t;     _IOWR(&squot;X&squot;, 107, struct xfs_fsop_handlereq)
DECL|macro|XFS_IOC_READLINK_BY_HANDLE
mdefine_line|#define XFS_IOC_READLINK_BY_HANDLE   _IOWR(&squot;X&squot;, 108, struct xfs_fsop_handlereq)
DECL|macro|XFS_IOC_SWAPEXT
mdefine_line|#define XFS_IOC_SWAPEXT&t;&t;     _IOWR(&squot;X&squot;, 109, struct xfs_swapext)
DECL|macro|XFS_IOC_FSGROWFSDATA
mdefine_line|#define XFS_IOC_FSGROWFSDATA&t;     _IOW (&squot;X&squot;, 110, struct xfs_growfs_data)
DECL|macro|XFS_IOC_FSGROWFSLOG
mdefine_line|#define XFS_IOC_FSGROWFSLOG&t;     _IOW (&squot;X&squot;, 111, struct xfs_growfs_log)
DECL|macro|XFS_IOC_FSGROWFSRT
mdefine_line|#define XFS_IOC_FSGROWFSRT&t;     _IOW (&squot;X&squot;, 112, struct xfs_growfs_rt)
DECL|macro|XFS_IOC_FSCOUNTS
mdefine_line|#define XFS_IOC_FSCOUNTS&t;     _IOR (&squot;X&squot;, 113, struct xfs_fsop_counts)
DECL|macro|XFS_IOC_SET_RESBLKS
mdefine_line|#define XFS_IOC_SET_RESBLKS&t;     _IOWR(&squot;X&squot;, 114, struct xfs_fsop_resblks)
DECL|macro|XFS_IOC_GET_RESBLKS
mdefine_line|#define XFS_IOC_GET_RESBLKS&t;     _IOR (&squot;X&squot;, 115, struct xfs_fsop_resblks)
DECL|macro|XFS_IOC_ERROR_INJECTION
mdefine_line|#define XFS_IOC_ERROR_INJECTION&t;     _IOW (&squot;X&squot;, 116, struct xfs_error_injection)
DECL|macro|XFS_IOC_ERROR_CLEARALL
mdefine_line|#define XFS_IOC_ERROR_CLEARALL&t;     _IOW (&squot;X&squot;, 117, struct xfs_error_injection)
multiline_comment|/*&t;XFS_IOC_ATTRCTL_BY_HANDLE -- deprecated 118&t; */
DECL|macro|XFS_IOC_FREEZE
mdefine_line|#define XFS_IOC_FREEZE&t;&t;     _IOWR(&squot;X&squot;, 119, int)
DECL|macro|XFS_IOC_THAW
mdefine_line|#define XFS_IOC_THAW&t;&t;     _IOWR(&squot;X&squot;, 120, int)
DECL|macro|XFS_IOC_FSSETDM_BY_HANDLE
mdefine_line|#define XFS_IOC_FSSETDM_BY_HANDLE    _IOW (&squot;X&squot;, 121, struct xfs_fsop_setdm_handlereq)
DECL|macro|XFS_IOC_ATTRLIST_BY_HANDLE
mdefine_line|#define XFS_IOC_ATTRLIST_BY_HANDLE   _IOW (&squot;X&squot;, 122, struct xfs_fsop_attrlist_handlereq)
DECL|macro|XFS_IOC_ATTRMULTI_BY_HANDLE
mdefine_line|#define XFS_IOC_ATTRMULTI_BY_HANDLE  _IOW (&squot;X&squot;, 123, struct xfs_fsop_attrmulti_handlereq)
DECL|macro|XFS_IOC_FSGEOMETRY
mdefine_line|#define XFS_IOC_FSGEOMETRY&t;     _IOR (&squot;X&squot;, 124, struct xfs_fsop_geom)
DECL|macro|XFS_IOC_GOINGDOWN
mdefine_line|#define XFS_IOC_GOINGDOWN&t;     _IOR (&squot;X&squot;, 125, __uint32_t)
multiline_comment|/*&t;XFS_IOC_GETFSUUID ---------- deprecated 140&t; */
macro_line|#ifndef HAVE_BBMACROS
multiline_comment|/*&n; * Block I/O parameterization.&t;A basic block (BB) is the lowest size of&n; * filesystem allocation, and must equal 512.  Length units given to bio&n; * routines are in BB&squot;s.&n; */
DECL|macro|BBSHIFT
mdefine_line|#define BBSHIFT&t;&t;9
DECL|macro|BBSIZE
mdefine_line|#define BBSIZE&t;&t;(1&lt;&lt;BBSHIFT)
DECL|macro|BBMASK
mdefine_line|#define BBMASK&t;&t;(BBSIZE-1)
DECL|macro|BTOBB
mdefine_line|#define BTOBB(bytes)&t;(((__u64)(bytes) + BBSIZE - 1) &gt;&gt; BBSHIFT)
DECL|macro|BTOBBT
mdefine_line|#define BTOBBT(bytes)&t;((__u64)(bytes) &gt;&gt; BBSHIFT)
DECL|macro|BBTOB
mdefine_line|#define BBTOB(bbs)&t;((bbs) &lt;&lt; BBSHIFT)
macro_line|#endif
macro_line|#endif&t;/* __XFS_FS_H__ */
eof
