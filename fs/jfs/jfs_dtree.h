multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/*&n; * Change History :&n; *&n; */
macro_line|#ifndef _H_JFS_DTREE
DECL|macro|_H_JFS_DTREE
mdefine_line|#define&t;_H_JFS_DTREE
multiline_comment|/*&n; *&t;jfs_dtree.h: directory B+-tree manager&n; */
macro_line|#include &quot;jfs_btree.h&quot;
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|tid
id|tid_t
id|tid
suffix:semicolon
DECL|member|ip
r_struct
id|inode
op_star
id|ip
suffix:semicolon
DECL|member|ino
id|u32
id|ino
suffix:semicolon
DECL|member|leaf
)brace
id|leaf
suffix:semicolon
DECL|member|xd
id|pxd_t
id|xd
suffix:semicolon
DECL|typedef|ddata_t
)brace
id|ddata_t
suffix:semicolon
multiline_comment|/*&n; *      entry segment/slot&n; *&n; * an entry consists of type dependent head/only segment/slot and&n; * additional segments/slots linked vi next field;&n; * N.B. last/only segment of entry is terminated by next = -1;&n; */
multiline_comment|/*&n; *&t;directory page slot&n; */
r_typedef
r_struct
(brace
DECL|member|next
id|s8
id|next
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|cnt
id|s8
id|cnt
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|name
m_wchar_t
id|name
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* 30: */
DECL|typedef|dtslot_t
)brace
id|dtslot_t
suffix:semicolon
multiline_comment|/* (32) */
DECL|macro|DATASLOTSIZE
mdefine_line|#define DATASLOTSIZE&t;16
DECL|macro|L2DATASLOTSIZE
mdefine_line|#define L2DATASLOTSIZE&t;4
DECL|macro|DTSLOTSIZE
mdefine_line|#define&t;DTSLOTSIZE&t;32
DECL|macro|L2DTSLOTSIZE
mdefine_line|#define&t;L2DTSLOTSIZE&t;5
DECL|macro|DTSLOTHDRSIZE
mdefine_line|#define DTSLOTHDRSIZE&t;2
DECL|macro|DTSLOTDATASIZE
mdefine_line|#define DTSLOTDATASIZE&t;30
DECL|macro|DTSLOTDATALEN
mdefine_line|#define DTSLOTDATALEN&t;15
multiline_comment|/*&n; *&t; internal node entry head/only segment&n; */
r_typedef
r_struct
(brace
DECL|member|xd
id|pxd_t
id|xd
suffix:semicolon
multiline_comment|/* 8: child extent descriptor */
DECL|member|next
id|s8
id|next
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|namlen
id|u8
id|namlen
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|name
m_wchar_t
id|name
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* 22: 2-byte aligned */
DECL|typedef|idtentry_t
)brace
id|idtentry_t
suffix:semicolon
multiline_comment|/* (32) */
DECL|macro|DTIHDRSIZE
mdefine_line|#define DTIHDRSIZE&t;10
DECL|macro|DTIHDRDATALEN
mdefine_line|#define DTIHDRDATALEN&t;11
multiline_comment|/* compute number of slots for entry */
DECL|macro|NDTINTERNAL
mdefine_line|#define&t;NDTINTERNAL(klen) ( ((4 + (klen)) + (15 - 1)) / 15 )
multiline_comment|/*&n; *&t;leaf node entry head/only segment&n; *&n; * &t;For legacy filesystems, name contains 13 wchars -- no index field&n; */
r_typedef
r_struct
(brace
DECL|member|inumber
id|u32
id|inumber
suffix:semicolon
multiline_comment|/* 4: 4-byte aligned */
DECL|member|next
id|s8
id|next
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|namlen
id|u8
id|namlen
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|name
m_wchar_t
id|name
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* 22: 2-byte aligned */
DECL|member|index
id|u32
id|index
suffix:semicolon
multiline_comment|/* 4: index into dir_table */
DECL|typedef|ldtentry_t
)brace
id|ldtentry_t
suffix:semicolon
multiline_comment|/* (32) */
DECL|macro|DTLHDRSIZE
mdefine_line|#define DTLHDRSIZE&t;6
DECL|macro|DTLHDRDATALEN_LEGACY
mdefine_line|#define DTLHDRDATALEN_LEGACY&t;13&t;/* Old (OS/2) format */
DECL|macro|DTLHDRDATALEN
mdefine_line|#define DTLHDRDATALEN&t;11
multiline_comment|/*&n; * dir_table used for directory traversal during readdir&n; */
multiline_comment|/*&n; * Keep persistent index for directory entries&n; */
DECL|macro|DO_INDEX
mdefine_line|#define DO_INDEX(INODE) (JFS_SBI((INODE)-&gt;i_sb)-&gt;mntflag &amp; JFS_DIR_INDEX)
multiline_comment|/*&n; * Maximum entry in inline directory table&n; */
DECL|macro|MAX_INLINE_DIRTABLE_ENTRY
mdefine_line|#define MAX_INLINE_DIRTABLE_ENTRY 13
DECL|struct|dir_table_slot
r_typedef
r_struct
id|dir_table_slot
(brace
DECL|member|rsrvd
id|u8
id|rsrvd
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* 1: 0 if free */
DECL|member|slot
id|u8
id|slot
suffix:semicolon
multiline_comment|/* 1: slot within leaf page of entry */
DECL|member|addr1
id|u8
id|addr1
suffix:semicolon
multiline_comment|/* 1: upper 8 bits of leaf page address */
DECL|member|addr2
id|u32
id|addr2
suffix:semicolon
multiline_comment|/* 4: lower 32 bits of leaf page address -OR-&n;&t;&t;&t;&t;   index of next entry when this entry was deleted */
DECL|typedef|dir_table_slot_t
)brace
id|dir_table_slot_t
suffix:semicolon
multiline_comment|/* (8) */
multiline_comment|/*&n; * flag values&n; */
DECL|macro|DIR_INDEX_VALID
mdefine_line|#define DIR_INDEX_VALID 1
DECL|macro|DIR_INDEX_FREE
mdefine_line|#define DIR_INDEX_FREE 0
DECL|macro|DTSaddress
mdefine_line|#define DTSaddress(dir_table_slot, address64)&bslash;&n;{&bslash;&n;&t;(dir_table_slot)-&gt;addr1 = ((u64)address64) &gt;&gt; 32;&bslash;&n;&t;(dir_table_slot)-&gt;addr2 = __cpu_to_le32((address64) &amp; 0xffffffff);&bslash;&n;}
DECL|macro|addressDTS
mdefine_line|#define addressDTS(dts)&bslash;&n;&t;( ((s64)((dts)-&gt;addr1)) &lt;&lt; 32 | __le32_to_cpu((dts)-&gt;addr2) )
multiline_comment|/* compute number of slots for entry */
DECL|macro|NDTLEAF_LEGACY
mdefine_line|#define&t;NDTLEAF_LEGACY(klen)&t;( ((2 + (klen)) + (15 - 1)) / 15 )
DECL|macro|NDTLEAF
mdefine_line|#define&t;NDTLEAF&t;NDTINTERNAL
multiline_comment|/*&n; *&t;directory root page (in-line in on-disk inode):&n; *&n; * cf. dtpage_t below.&n; */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|DASD
id|dasd_t
id|DASD
suffix:semicolon
multiline_comment|/* 16: DASD limit/usage info  F226941 */
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|nextindex
id|u8
id|nextindex
suffix:semicolon
multiline_comment|/* 1: next free entry in stbl */
DECL|member|freecnt
id|s8
id|freecnt
suffix:semicolon
multiline_comment|/* 1: free count */
DECL|member|freelist
id|s8
id|freelist
suffix:semicolon
multiline_comment|/* 1: freelist header */
DECL|member|idotdot
id|u32
id|idotdot
suffix:semicolon
multiline_comment|/* 4: parent inode number */
DECL|member|stbl
id|s8
id|stbl
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 8: sorted entry index table */
DECL|member|header
)brace
id|header
suffix:semicolon
multiline_comment|/* (32) */
DECL|member|slot
id|dtslot_t
id|slot
(braket
l_int|9
)braket
suffix:semicolon
DECL|typedef|dtroot_t
)brace
id|dtroot_t
suffix:semicolon
DECL|macro|PARENT
mdefine_line|#define PARENT(IP) &bslash;&n;&t;(le32_to_cpu(JFS_IP(IP)-&gt;i_dtroot.header.idotdot))
DECL|macro|DTROOTMAXSLOT
mdefine_line|#define DTROOTMAXSLOT&t;9
DECL|macro|dtEmpty
mdefine_line|#define&t;dtEmpty(IP) (JFS_IP(IP)-&gt;i_dtroot.header.nextindex == 0)
multiline_comment|/*&n; *&t;directory regular page:&n; *&n; *&t;entry slot array of 32 byte slot&n; *&n; * sorted entry slot index table (stbl):&n; * contiguous slots at slot specified by stblindex,&n; * 1-byte per entry&n; *   512 byte block:  16 entry tbl (1 slot)&n; *  1024 byte block:  32 entry tbl (1 slot)&n; *  2048 byte block:  64 entry tbl (2 slot)&n; *  4096 byte block: 128 entry tbl (4 slot)&n; *&n; * data area:&n; *   512 byte block:  16 - 2 =  14 slot&n; *  1024 byte block:  32 - 2 =  30 slot&n; *  2048 byte block:  64 - 3 =  61 slot&n; *  4096 byte block: 128 - 5 = 123 slot&n; *&n; * N.B. index is 0-based; index fields refer to slot index&n; * except nextindex which refers to entry index in stbl;&n; * end of entry stot list or freelist is marked with -1.&n; */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|next
id|s64
id|next
suffix:semicolon
multiline_comment|/* 8: next sibling */
DECL|member|prev
id|s64
id|prev
suffix:semicolon
multiline_comment|/* 8: previous sibling */
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|nextindex
id|u8
id|nextindex
suffix:semicolon
multiline_comment|/* 1: next entry index in stbl */
DECL|member|freecnt
id|s8
id|freecnt
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|freelist
id|s8
id|freelist
suffix:semicolon
multiline_comment|/* 1: slot index of head of freelist */
DECL|member|maxslot
id|u8
id|maxslot
suffix:semicolon
multiline_comment|/* 1: number of slots in page slot[] */
DECL|member|stblindex
id|u8
id|stblindex
suffix:semicolon
multiline_comment|/* 1: slot index of start of stbl */
DECL|member|rsrvd
id|u8
id|rsrvd
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|self
id|pxd_t
id|self
suffix:semicolon
multiline_comment|/* 8: self pxd */
DECL|member|header
)brace
id|header
suffix:semicolon
multiline_comment|/* (32) */
DECL|member|slot
id|dtslot_t
id|slot
(braket
l_int|128
)braket
suffix:semicolon
DECL|typedef|dtpage_t
)brace
id|dtpage_t
suffix:semicolon
DECL|macro|DTPAGEMAXSLOT
mdefine_line|#define DTPAGEMAXSLOT        128
DECL|macro|DT8THPGNODEBYTES
mdefine_line|#define DT8THPGNODEBYTES     512
DECL|macro|DT8THPGNODETSLOTS
mdefine_line|#define DT8THPGNODETSLOTS      1
DECL|macro|DT8THPGNODESLOTS
mdefine_line|#define DT8THPGNODESLOTS      16
DECL|macro|DTQTRPGNODEBYTES
mdefine_line|#define DTQTRPGNODEBYTES    1024
DECL|macro|DTQTRPGNODETSLOTS
mdefine_line|#define DTQTRPGNODETSLOTS      1
DECL|macro|DTQTRPGNODESLOTS
mdefine_line|#define DTQTRPGNODESLOTS      32
DECL|macro|DTHALFPGNODEBYTES
mdefine_line|#define DTHALFPGNODEBYTES   2048
DECL|macro|DTHALFPGNODETSLOTS
mdefine_line|#define DTHALFPGNODETSLOTS     2
DECL|macro|DTHALFPGNODESLOTS
mdefine_line|#define DTHALFPGNODESLOTS     64
DECL|macro|DTFULLPGNODEBYTES
mdefine_line|#define DTFULLPGNODEBYTES   4096
DECL|macro|DTFULLPGNODETSLOTS
mdefine_line|#define DTFULLPGNODETSLOTS     4
DECL|macro|DTFULLPGNODESLOTS
mdefine_line|#define DTFULLPGNODESLOTS    128
DECL|macro|DTENTRYSTART
mdefine_line|#define DTENTRYSTART&t;1
multiline_comment|/* get sorted entry table of the page */
DECL|macro|DT_GETSTBL
mdefine_line|#define DT_GETSTBL(p) ( ((p)-&gt;header.flag &amp; BT_ROOT) ?&bslash;&n;&t;((dtroot_t *)(p))-&gt;header.stbl : &bslash;&n;&t;(s8 *)&amp;(p)-&gt;slot[(p)-&gt;header.stblindex] )
multiline_comment|/*&n; * Flags for dtSearch&n; */
DECL|macro|JFS_CREATE
mdefine_line|#define JFS_CREATE 1
DECL|macro|JFS_LOOKUP
mdefine_line|#define JFS_LOOKUP 2
DECL|macro|JFS_REMOVE
mdefine_line|#define JFS_REMOVE 3
DECL|macro|JFS_RENAME
mdefine_line|#define JFS_RENAME 4
DECL|macro|DIRENTSIZ
mdefine_line|#define DIRENTSIZ(namlen) &bslash;&n;    ( (sizeof(struct dirent) - 2*(JFS_NAME_MAX+1) + 2*((namlen)+1) + 3) &amp;~ 3 )
multiline_comment|/*&n; * Maximum file offset for directories.&n; */
DECL|macro|DIREND
mdefine_line|#define DIREND&t;INT_MAX
multiline_comment|/*&n; *&t;external declarations&n; */
r_extern
r_void
id|dtInitRoot
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
id|u32
id|idotdot
)paren
suffix:semicolon
r_extern
r_int
id|dtSearch
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|component_t
op_star
id|key
comma
id|ino_t
op_star
id|data
comma
id|btstack_t
op_star
id|btstack
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|dtInsert
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
id|component_t
op_star
id|key
comma
id|ino_t
op_star
id|ino
comma
id|btstack_t
op_star
id|btstack
)paren
suffix:semicolon
r_extern
r_int
id|dtDelete
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
id|component_t
op_star
id|key
comma
id|ino_t
op_star
id|data
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|dtRelocate
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
id|lmxaddr
comma
id|pxd_t
op_star
id|opxd
comma
id|s64
id|nxaddr
)paren
suffix:semicolon
r_extern
r_int
id|dtModify
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
id|component_t
op_star
id|key
comma
id|ino_t
op_star
id|orig_ino
comma
id|ino_t
id|new_ino
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|jfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
suffix:semicolon
macro_line|#ifdef  _JFS_DEBUG_DTREE
r_extern
r_int
id|dtDisplayTree
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
id|dtDisplayPage
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
id|dtpage_t
op_star
id|p
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _JFS_DEBUG_DTREE */
macro_line|#endif&t;&t;&t;&t;/* !_H_JFS_DTREE */
eof
