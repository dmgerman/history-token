multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_EXTENDFS
DECL|macro|_H_JFS_EXTENDFS
mdefine_line|#define _H_JFS_EXTENDFS
multiline_comment|/*&n; *&t;jfs_extendfs.h&n; */
multiline_comment|/*&n; *&t;extendfs parameter list&n; */
r_typedef
r_struct
(brace
DECL|member|flag
id|u32
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
DECL|member|LVSize
id|s64
id|LVSize
suffix:semicolon
multiline_comment|/* 8: LV size in LV block */
DECL|member|FSSize
id|s64
id|FSSize
suffix:semicolon
multiline_comment|/* 8: FS size in LV block */
DECL|member|LogSize
id|s32
id|LogSize
suffix:semicolon
multiline_comment|/* 4: inlinelog size in LV block */
DECL|typedef|extendfs_t
)brace
id|extendfs_t
suffix:semicolon
multiline_comment|/* (28) */
multiline_comment|/* plist flag */
DECL|macro|EXTENDFS_QUERY
mdefine_line|#define EXTENDFS_QUERY&t;&t;0x00000001
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_EXTENDFS */
eof
