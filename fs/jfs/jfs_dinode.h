multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2001&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_DINODE
DECL|macro|_H_JFS_DINODE
mdefine_line|#define _H_JFS_DINODE
multiline_comment|/*&n; *      jfs_dinode.h: on-disk inode manager&n; */
DECL|macro|INODESLOTSIZE
mdefine_line|#define INODESLOTSIZE           128
DECL|macro|L2INODESLOTSIZE
mdefine_line|#define L2INODESLOTSIZE         7
DECL|macro|log2INODESIZE
mdefine_line|#define log2INODESIZE           9&t;/* log2(bytes per dinode) */
multiline_comment|/*&n; *      on-disk inode (dinode_t): 512 bytes&n; *&n; * note: align 64-bit fields on 8-byte boundary.&n; */
DECL|struct|dinode
r_struct
id|dinode
(brace
multiline_comment|/*&n;&t; *      I. base area (128 bytes)&n;&t; *      ------------------------&n;&t; *&n;&t; * define generic/POSIX attributes&n;&t; */
DECL|member|di_inostamp
id|u32
id|di_inostamp
suffix:semicolon
multiline_comment|/* 4: stamp to show inode belongs to fileset */
DECL|member|di_fileset
id|s32
id|di_fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|di_number
id|u32
id|di_number
suffix:semicolon
multiline_comment|/* 4: inode number, aka file serial number */
DECL|member|di_gen
id|u32
id|di_gen
suffix:semicolon
multiline_comment|/* 4: inode generation number */
DECL|member|di_ixpxd
id|pxd_t
id|di_ixpxd
suffix:semicolon
multiline_comment|/* 8: inode extent descriptor */
DECL|member|di_size
id|s64
id|di_size
suffix:semicolon
multiline_comment|/* 8: size */
DECL|member|di_nblocks
id|s64
id|di_nblocks
suffix:semicolon
multiline_comment|/* 8: number of blocks allocated */
DECL|member|di_nlink
id|u32
id|di_nlink
suffix:semicolon
multiline_comment|/* 4: number of links to the object */
DECL|member|di_uid
id|u32
id|di_uid
suffix:semicolon
multiline_comment|/* 4: user id of owner */
DECL|member|di_gid
id|u32
id|di_gid
suffix:semicolon
multiline_comment|/* 4: group id of owner */
DECL|member|di_mode
id|u32
id|di_mode
suffix:semicolon
multiline_comment|/* 4: attribute, format and permission */
DECL|member|di_atime
r_struct
id|timestruc_t
id|di_atime
suffix:semicolon
multiline_comment|/* 8: time last data accessed */
DECL|member|di_ctime
r_struct
id|timestruc_t
id|di_ctime
suffix:semicolon
multiline_comment|/* 8: time last status changed */
DECL|member|di_mtime
r_struct
id|timestruc_t
id|di_mtime
suffix:semicolon
multiline_comment|/* 8: time last data modified */
DECL|member|di_otime
r_struct
id|timestruc_t
id|di_otime
suffix:semicolon
multiline_comment|/* 8: time created */
DECL|member|di_acl
id|dxd_t
id|di_acl
suffix:semicolon
multiline_comment|/* 16: acl descriptor */
DECL|member|di_ea
id|dxd_t
id|di_ea
suffix:semicolon
multiline_comment|/* 16: ea descriptor */
DECL|member|di_next_index
id|u32
id|di_next_index
suffix:semicolon
multiline_comment|/* 4: Next available dir_table index */
DECL|member|di_acltype
id|s32
id|di_acltype
suffix:semicolon
multiline_comment|/* 4: Type of ACL */
multiline_comment|/*&n;&t; *      Extension Areas.&n;&t; *&n;&t; *      Historically, the inode was partitioned into 4 128-byte areas,&n;&t; *      the last 3 being defined as unions which could have multiple&n;&t; *      uses.  The first 96 bytes had been completely unused until&n;&t; *      an index table was added to the directory.  It is now more&n;&t; *      useful to describe the last 3/4 of the inode as a single&n;&t; *      union.  We would probably be better off redesigning the&n;&t; *      entire structure from scratch, but we don&squot;t want to break&n;&t; *      commonality with OS/2&squot;s JFS at this time.&n;&t; */
r_union
(brace
r_struct
(brace
multiline_comment|/*&n;&t;&t;&t; * This table contains the information needed to&n;&t;&t;&t; * find a directory entry from a 32-bit index.&n;&t;&t;&t; * If the index is small enough, the table is inline,&n;&t;&t;&t; * otherwise, an x-tree root overlays this table&n;&t;&t;&t; */
DECL|member|_table
id|dir_table_slot_t
id|_table
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 96: inline */
DECL|member|_dtroot
id|dtroot_t
id|_dtroot
suffix:semicolon
multiline_comment|/* 288: dtree root */
DECL|member|_dir
)brace
id|_dir
suffix:semicolon
multiline_comment|/* (384) */
DECL|macro|di_dirtable
mdefine_line|#define di_dirtable&t;u._dir._table
DECL|macro|di_dtroot
mdefine_line|#define di_dtroot&t;u._dir._dtroot
DECL|macro|di_parent
mdefine_line|#define di_parent       di_dtroot.header.idotdot
DECL|macro|di_DASD
mdefine_line|#define di_DASD&t;&t;di_dtroot.header.DASD
r_struct
(brace
r_union
(brace
DECL|member|_data
id|u8
id|_data
(braket
l_int|96
)braket
suffix:semicolon
multiline_comment|/* 96: unused */
r_struct
(brace
DECL|member|_imap
r_void
op_star
id|_imap
suffix:semicolon
multiline_comment|/* 4: unused */
DECL|member|_gengen
id|u32
id|_gengen
suffix:semicolon
multiline_comment|/* 4: generator */
DECL|member|_imap
)brace
id|_imap
suffix:semicolon
DECL|member|_u1
)brace
id|_u1
suffix:semicolon
multiline_comment|/* 96: */
DECL|macro|di_gengen
mdefine_line|#define di_gengen&t;u._file._u1._imap._gengen
r_union
(brace
DECL|member|_xtroot
id|xtpage_t
id|_xtroot
suffix:semicolon
r_struct
(brace
DECL|member|unused
id|u8
id|unused
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16: */
DECL|member|_dxd
id|dxd_t
id|_dxd
suffix:semicolon
multiline_comment|/* 16: */
r_union
(brace
DECL|member|_rdev
id|u32
id|_rdev
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|_fastsymlink
id|u8
id|_fastsymlink
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|_u
)brace
id|_u
suffix:semicolon
DECL|member|_inlineea
id|u8
id|_inlineea
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|_special
)brace
id|_special
suffix:semicolon
DECL|member|_u2
)brace
id|_u2
suffix:semicolon
DECL|member|_file
)brace
id|_file
suffix:semicolon
DECL|macro|di_xtroot
mdefine_line|#define di_xtroot&t;u._file._u2._xtroot
DECL|macro|di_dxd
mdefine_line|#define di_dxd&t;&t;u._file._u2._special._dxd
DECL|macro|di_btroot
mdefine_line|#define di_btroot&t;di_xtroot
DECL|macro|di_inlinedata
mdefine_line|#define di_inlinedata&t;u._file._u2._special._u
DECL|macro|di_rdev
mdefine_line|#define di_rdev&t;&t;u._file._u2._special._u._rdev
DECL|macro|di_fastsymlink
mdefine_line|#define di_fastsymlink&t;u._file._u2._special._u._fastsymlink
DECL|macro|di_inlineea
mdefine_line|#define di_inlineea     u._file._u2._special._inlineea
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|dinode_t
r_typedef
r_struct
id|dinode
id|dinode_t
suffix:semicolon
multiline_comment|/* extended mode bits (on-disk inode di_mode) */
DECL|macro|IFJOURNAL
mdefine_line|#define IFJOURNAL       0x00010000&t;/* journalled file */
DECL|macro|ISPARSE
mdefine_line|#define ISPARSE         0x00020000&t;/* sparse file enabled */
DECL|macro|INLINEEA
mdefine_line|#define INLINEEA        0x00040000&t;/* inline EA area free */
DECL|macro|ISWAPFILE
mdefine_line|#define ISWAPFILE&t;0x00800000&t;/* file open for pager swap space */
multiline_comment|/* more extended mode bits: attributes for OS/2 */
DECL|macro|IREADONLY
mdefine_line|#define IREADONLY&t;0x02000000&t;/* no write access to file */
DECL|macro|IARCHIVE
mdefine_line|#define IARCHIVE&t;0x40000000&t;/* file archive bit */
DECL|macro|ISYSTEM
mdefine_line|#define ISYSTEM&t;&t;0x08000000&t;/* system file */
DECL|macro|IHIDDEN
mdefine_line|#define IHIDDEN&t;&t;0x04000000&t;/* hidden file */
DECL|macro|IRASH
mdefine_line|#define IRASH&t;&t;0x4E000000&t;/* mask for changeable attributes */
DECL|macro|INEWNAME
mdefine_line|#define INEWNAME&t;0x80000000&t;/* non-8.3 filename format */
DECL|macro|IDIRECTORY
mdefine_line|#define IDIRECTORY&t;0x20000000&t;/* directory (shadow of real bit) */
DECL|macro|ATTRSHIFT
mdefine_line|#define ATTRSHIFT&t;25&t;/* bits to shift to move attribute&n;&t;&t;&t;&t;   specification to mode position */
macro_line|#endif /*_H_JFS_DINODE */
eof
