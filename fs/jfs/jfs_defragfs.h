multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2001&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_DEFRAGFS
DECL|macro|_H_JFS_DEFRAGFS
mdefine_line|#define _H_JFS_DEFRAGFS
multiline_comment|/*&n; *&t;defragfs parameter list&n; */
r_typedef
r_struct
(brace
DECL|member|flag
id|uint
id|flag
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|dev
id|u8
id|dev
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|pad
id|u8
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 3: */
DECL|member|fileset
id|s32
id|fileset
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|inostamp
id|u32
id|inostamp
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|ino
id|u32
id|ino
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|gen
id|u32
id|gen
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|xoff
id|s64
id|xoff
suffix:semicolon
multiline_comment|/* 8: */
DECL|member|old_xaddr
id|s64
id|old_xaddr
suffix:semicolon
multiline_comment|/* 8: */
DECL|member|new_xaddr
id|s64
id|new_xaddr
suffix:semicolon
multiline_comment|/* 8: */
DECL|member|xlen
id|s32
id|xlen
suffix:semicolon
multiline_comment|/* 4: */
DECL|typedef|defragfs_t
)brace
id|defragfs_t
suffix:semicolon
multiline_comment|/* (52) */
multiline_comment|/* plist flag */
DECL|macro|DEFRAGFS_SYNC
mdefine_line|#define DEFRAGFS_SYNC&t;&t;0x80000000
DECL|macro|DEFRAGFS_COMMIT
mdefine_line|#define DEFRAGFS_COMMIT&t;&t;0x40000000
DECL|macro|DEFRAGFS_RELOCATE
mdefine_line|#define DEFRAGFS_RELOCATE&t;0x10000000
DECL|macro|INODE_TYPE
mdefine_line|#define&t;INODE_TYPE&t;&t;0x0000F000&t;/* IFREG or IFDIR */
DECL|macro|EXTENT_TYPE
mdefine_line|#define EXTENT_TYPE&t;&t;0x000000ff
DECL|macro|DTPAGE
mdefine_line|#define DTPAGE&t;&t;&t;0x00000001
DECL|macro|XTPAGE
mdefine_line|#define XTPAGE&t;&t;&t;0x00000002
DECL|macro|DATAEXT
mdefine_line|#define DATAEXT&t;&t;&t;0x00000004
DECL|macro|EAEXT
mdefine_line|#define EAEXT&t;&t;&t;0x00000008
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_DEFRAGFS */
eof
