multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n;*/
multiline_comment|/*&n; * Change History :&n; *&n;*/
macro_line|#ifndef _H_JFS_XTREE
DECL|macro|_H_JFS_XTREE
mdefine_line|#define _H_JFS_XTREE
multiline_comment|/*&n; *      jfs_xtree.h: extent allocation descriptor B+-tree manager&n; */
macro_line|#include &quot;jfs_btree.h&quot;
multiline_comment|/*&n; *      extent allocation descriptor (xad)&n; */
DECL|struct|xad
r_typedef
r_struct
id|xad
(brace
DECL|member|flag
r_int
id|flag
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 1: flag */
DECL|member|rsvrd
r_int
id|rsvrd
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 2: reserved */
DECL|member|off1
r_int
id|off1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 1: offset in unit of fsblksize */
DECL|member|off2
id|u32
id|off2
suffix:semicolon
multiline_comment|/* 4: offset in unit of fsblksize */
DECL|member|len
r_int
id|len
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* 3: length in unit of fsblksize */
DECL|member|addr1
r_int
id|addr1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 1: address in unit of fsblksize */
DECL|member|addr2
id|u32
id|addr2
suffix:semicolon
multiline_comment|/* 4: address in unit of fsblksize */
DECL|typedef|xad_t
)brace
id|xad_t
suffix:semicolon
multiline_comment|/* (16) */
DECL|macro|MAXXLEN
mdefine_line|#define MAXXLEN         ((1 &lt;&lt; 24) - 1)
DECL|macro|XTSLOTSIZE
mdefine_line|#define XTSLOTSIZE      16
DECL|macro|L2XTSLOTSIZE
mdefine_line|#define L2XTSLOTSIZE    4
multiline_comment|/* xad_t field construction */
DECL|macro|XADoffset
mdefine_line|#define XADoffset(xad, offset64)&bslash;&n;{&bslash;&n;        (xad)-&gt;off1 = ((u64)offset64) &gt;&gt; 32;&bslash;&n;        (xad)-&gt;off2 = __cpu_to_le32((offset64) &amp; 0xffffffff);&bslash;&n;}
DECL|macro|XADaddress
mdefine_line|#define XADaddress(xad, address64)&bslash;&n;{&bslash;&n;        (xad)-&gt;addr1 = ((u64)address64) &gt;&gt; 32;&bslash;&n;        (xad)-&gt;addr2 = __cpu_to_le32((address64) &amp; 0xffffffff);&bslash;&n;}
DECL|macro|XADlength
mdefine_line|#define XADlength(xad, length32)        (xad)-&gt;len = __cpu_to_le24(length32)
multiline_comment|/* xad_t field extraction */
DECL|macro|offsetXAD
mdefine_line|#define offsetXAD(xad)&bslash;&n;        ( ((s64)((xad)-&gt;off1)) &lt;&lt; 32 | __le32_to_cpu((xad)-&gt;off2))
DECL|macro|addressXAD
mdefine_line|#define addressXAD(xad)&bslash;&n;        ( ((s64)((xad)-&gt;addr1)) &lt;&lt; 32 | __le32_to_cpu((xad)-&gt;addr2))
DECL|macro|lengthXAD
mdefine_line|#define lengthXAD(xad)  __le24_to_cpu((xad)-&gt;len)
multiline_comment|/* xad list */
r_typedef
r_struct
(brace
DECL|member|maxnxad
id|s16
id|maxnxad
suffix:semicolon
DECL|member|nxad
id|s16
id|nxad
suffix:semicolon
DECL|member|xad
id|xad_t
op_star
id|xad
suffix:semicolon
DECL|typedef|xadlist_t
)brace
id|xadlist_t
suffix:semicolon
multiline_comment|/* xad_t flags */
DECL|macro|XAD_NEW
mdefine_line|#define XAD_NEW         0x01&t;/* new */
DECL|macro|XAD_EXTENDED
mdefine_line|#define XAD_EXTENDED    0x02&t;/* extended */
DECL|macro|XAD_COMPRESSED
mdefine_line|#define XAD_COMPRESSED  0x04&t;/* compressed with recorded length */
DECL|macro|XAD_NOTRECORDED
mdefine_line|#define XAD_NOTRECORDED 0x08&t;/* allocated but not recorded */
DECL|macro|XAD_COW
mdefine_line|#define XAD_COW         0x10&t;/* copy-on-write */
multiline_comment|/* possible values for maxentry */
DECL|macro|XTROOTINITSLOT_DIR
mdefine_line|#define XTROOTINITSLOT_DIR  6
DECL|macro|XTROOTINITSLOT
mdefine_line|#define XTROOTINITSLOT  10
DECL|macro|XTROOTMAXSLOT
mdefine_line|#define XTROOTMAXSLOT   18
DECL|macro|XTPAGEMAXSLOT
mdefine_line|#define XTPAGEMAXSLOT   256
DECL|macro|XTENTRYSTART
mdefine_line|#define XTENTRYSTART    2
multiline_comment|/*&n; *      xtree page:&n; */
r_typedef
r_union
(brace
DECL|struct|xtheader
r_struct
id|xtheader
(brace
DECL|member|next
id|s64
id|next
suffix:semicolon
multiline_comment|/* 8: */
DECL|member|prev
id|s64
id|prev
suffix:semicolon
multiline_comment|/* 8: */
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|rsrvd1
id|u8
id|rsrvd1
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|nextindex
id|s16
id|nextindex
suffix:semicolon
multiline_comment|/* 2: next index = number of entries */
DECL|member|maxentry
id|s16
id|maxentry
suffix:semicolon
multiline_comment|/* 2: max number of entries */
DECL|member|rsrvd2
id|s16
id|rsrvd2
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|self
id|pxd_t
id|self
suffix:semicolon
multiline_comment|/* 8: self */
DECL|member|header
)brace
id|header
suffix:semicolon
multiline_comment|/* (32) */
DECL|member|xad
id|xad_t
id|xad
(braket
id|XTROOTMAXSLOT
)braket
suffix:semicolon
multiline_comment|/* 16 * maxentry: xad array */
DECL|typedef|xtpage_t
)brace
id|xtpage_t
suffix:semicolon
multiline_comment|/*&n; *      external declaration&n; */
r_extern
r_int
id|xtLookup
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|lstart
comma
id|s64
id|llen
comma
r_int
op_star
id|pflag
comma
id|s64
op_star
id|paddr
comma
r_int
op_star
id|plen
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|xtLookupList
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|lxdlist_t
op_star
id|lxdlist
comma
id|xadlist_t
op_star
id|xadlist
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_void
id|xtInitRoot
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|xtInsert
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
r_int
id|xflag
comma
id|s64
id|xoff
comma
r_int
id|xlen
comma
id|s64
op_star
id|xaddrp
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|xtExtend
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|xoff
comma
r_int
id|xlen
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|xtTailgate
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|xoff
comma
r_int
id|xlen
comma
id|s64
id|xaddr
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|xtUpdate
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|xad
op_star
id|nxad
)paren
suffix:semicolon
r_extern
r_int
id|xtDelete
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|xoff
comma
r_int
id|xlen
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
id|s64
id|xtTruncate
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|newsize
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
id|s64
id|xtTruncate_pmap
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|committed_size
)paren
suffix:semicolon
r_extern
r_int
id|xtRelocate
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|xad_t
op_star
id|oxad
comma
id|s64
id|nxaddr
comma
r_int
id|xtype
)paren
suffix:semicolon
r_extern
r_int
id|xtAppend
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
r_int
id|xflag
comma
id|s64
id|xoff
comma
r_int
id|maxblocks
comma
r_int
op_star
id|xlenp
comma
id|s64
op_star
id|xaddrp
comma
r_int
id|flag
)paren
suffix:semicolon
macro_line|#ifdef  _JFS_DEBUG_XTREE
r_extern
r_int
id|xtDisplayTree
c_func
(paren
r_struct
id|inode
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|xtDisplayPage
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|bn
comma
id|xtpage_t
op_star
id|p
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _JFS_DEBUG_XTREE */
macro_line|#endif&t;&t;&t;&t;/* !_H_JFS_XTREE */
eof
