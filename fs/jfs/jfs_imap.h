multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_IMAP
DECL|macro|_H_JFS_IMAP
mdefine_line|#define _H_JFS_IMAP
macro_line|#include &quot;jfs_txnmgr.h&quot;
multiline_comment|/*&n; *&t;jfs_imap.h: disk inode manager&n; */
DECL|macro|EXTSPERIAG
mdefine_line|#define&t;EXTSPERIAG&t;128&t;/* number of disk inode extent per iag  */
DECL|macro|IMAPBLKNO
mdefine_line|#define IMAPBLKNO&t;0&t;/* lblkno of dinomap within inode map   */
DECL|macro|SMAPSZ
mdefine_line|#define SMAPSZ&t;&t;4&t;/* number of words per summary map      */
DECL|macro|EXTSPERSUM
mdefine_line|#define&t;EXTSPERSUM&t;32&t;/* number of extents per summary map entry */
DECL|macro|L2EXTSPERSUM
mdefine_line|#define&t;L2EXTSPERSUM&t;5&t;/* l2 number of extents per summary map */
DECL|macro|PGSPERIEXT
mdefine_line|#define&t;PGSPERIEXT&t;4&t;/* number of 4K pages per dinode extent */
DECL|macro|MAXIAGS
mdefine_line|#define&t;MAXIAGS&t;&t;((1&lt;&lt;20)-1)&t;/* maximum number of iags       */
DECL|macro|MAXAG
mdefine_line|#define&t;MAXAG&t;&t;128&t;/* maximum number of allocation groups  */
DECL|macro|AMAPSIZE
mdefine_line|#define AMAPSIZE      512&t;/* bytes in the IAG allocation maps */
DECL|macro|SMAPSIZE
mdefine_line|#define SMAPSIZE      16&t;/* bytes in the IAG summary maps */
multiline_comment|/* convert inode number to iag number */
DECL|macro|INOTOIAG
mdefine_line|#define&t;INOTOIAG(ino)&t;((ino) &gt;&gt; L2INOSPERIAG)
multiline_comment|/* convert iag number to logical block number of the iag page */
DECL|macro|IAGTOLBLK
mdefine_line|#define IAGTOLBLK(iagno,l2nbperpg)&t;(((iagno) + 1) &lt;&lt; (l2nbperpg))
multiline_comment|/* get the starting block number of the 4K page of an inode extent&n; * that contains ino.&n; */
DECL|macro|INOPBLK
mdefine_line|#define INOPBLK(pxd,ino,l2nbperpg)    &t;(addressPXD((pxd)) +&t;&t;&bslash;&n;&t;((((ino) &amp; (INOSPEREXT-1)) &gt;&gt; L2INOSPERPAGE) &lt;&lt; (l2nbperpg)))
multiline_comment|/*&n; *&t;inode allocation map:&n; * &n; * inode allocation map consists of &n; * . the inode map control page and&n; * . inode allocation group pages (per 4096 inodes)&n; * which are addressed by standard JFS xtree.&n; */
multiline_comment|/*&n; *&t;inode allocation group page (per 4096 inodes of an AG)&n; */
r_typedef
r_struct
(brace
DECL|member|agstart
id|s64
id|agstart
suffix:semicolon
multiline_comment|/* 8: starting block of ag              */
DECL|member|iagnum
id|s32
id|iagnum
suffix:semicolon
multiline_comment|/* 4: inode allocation group number     */
DECL|member|inofreefwd
id|s32
id|inofreefwd
suffix:semicolon
multiline_comment|/* 4: ag inode free list forward        */
DECL|member|inofreeback
id|s32
id|inofreeback
suffix:semicolon
multiline_comment|/* 4: ag inode free list back           */
DECL|member|extfreefwd
id|s32
id|extfreefwd
suffix:semicolon
multiline_comment|/* 4: ag inode extent free list forward */
DECL|member|extfreeback
id|s32
id|extfreeback
suffix:semicolon
multiline_comment|/* 4: ag inode extent free list back    */
DECL|member|iagfree
id|s32
id|iagfree
suffix:semicolon
multiline_comment|/* 4: iag free list                     */
multiline_comment|/* summary map: 1 bit per inode extent */
DECL|member|inosmap
id|s32
id|inosmap
(braket
id|SMAPSZ
)braket
suffix:semicolon
multiline_comment|/* 16: sum map of mapwords w/ free inodes;&n;&t;&t;&t;&t; *      note: this indicates free and backed&n;&t;&t;&t;&t; *      inodes, if the extent is not backed the&n;&t;&t;&t;&t; *      value will be 1.  if the extent is&n;&t;&t;&t;&t; *      backed but all inodes are being used the&n;&t;&t;&t;&t; *      value will be 1.  if the extent is&n;&t;&t;&t;&t; *      backed but at least one of the inodes is&n;&t;&t;&t;&t; *      free the value will be 0.&n;&t;&t;&t;&t; */
DECL|member|extsmap
id|s32
id|extsmap
(braket
id|SMAPSZ
)braket
suffix:semicolon
multiline_comment|/* 16: sum map of mapwords w/ free extents */
DECL|member|nfreeinos
id|s32
id|nfreeinos
suffix:semicolon
multiline_comment|/* 4: number of free inodes             */
DECL|member|nfreeexts
id|s32
id|nfreeexts
suffix:semicolon
multiline_comment|/* 4: number of free extents            */
multiline_comment|/* (72) */
DECL|member|pad
id|u8
id|pad
(braket
l_int|1976
)braket
suffix:semicolon
multiline_comment|/* 1976: pad to 2048 bytes */
multiline_comment|/* allocation bit map: 1 bit per inode (0 - free, 1 - allocated) */
DECL|member|wmap
id|u32
id|wmap
(braket
id|EXTSPERIAG
)braket
suffix:semicolon
multiline_comment|/* 512: working allocation map  */
DECL|member|pmap
id|u32
id|pmap
(braket
id|EXTSPERIAG
)braket
suffix:semicolon
multiline_comment|/* 512: persistent allocation map */
DECL|member|inoext
id|pxd_t
id|inoext
(braket
id|EXTSPERIAG
)braket
suffix:semicolon
multiline_comment|/* 1024: inode extent addresses */
DECL|typedef|iag_t
)brace
id|iag_t
suffix:semicolon
multiline_comment|/* (4096) */
multiline_comment|/*&n; *&t;per AG control information (in inode map control page)&n; */
r_typedef
r_struct
(brace
DECL|member|inofree
id|s32
id|inofree
suffix:semicolon
multiline_comment|/* 4: free inode list anchor            */
DECL|member|extfree
id|s32
id|extfree
suffix:semicolon
multiline_comment|/* 4: free extent list anchor           */
DECL|member|numinos
id|s32
id|numinos
suffix:semicolon
multiline_comment|/* 4: number of backed inodes           */
DECL|member|numfree
id|s32
id|numfree
suffix:semicolon
multiline_comment|/* 4: number of free inodes             */
DECL|typedef|iagctl_t
)brace
id|iagctl_t
suffix:semicolon
multiline_comment|/* (16) */
multiline_comment|/*&n; *&t;per fileset/aggregate inode map control page&n; */
r_typedef
r_struct
(brace
DECL|member|in_freeiag
id|s32
id|in_freeiag
suffix:semicolon
multiline_comment|/* 4: free iag list anchor     */
DECL|member|in_nextiag
id|s32
id|in_nextiag
suffix:semicolon
multiline_comment|/* 4: next free iag number     */
DECL|member|in_numinos
id|s32
id|in_numinos
suffix:semicolon
multiline_comment|/* 4: num of backed inodes */
DECL|member|in_numfree
id|s32
id|in_numfree
suffix:semicolon
multiline_comment|/* 4: num of free backed inodes */
DECL|member|in_nbperiext
id|s32
id|in_nbperiext
suffix:semicolon
multiline_comment|/* 4: num of blocks per inode extent */
DECL|member|in_l2nbperiext
id|s32
id|in_l2nbperiext
suffix:semicolon
multiline_comment|/* 4: l2 of in_nbperiext */
DECL|member|in_diskblock
id|s32
id|in_diskblock
suffix:semicolon
multiline_comment|/* 4: for standalone test driver  */
DECL|member|in_maxag
id|s32
id|in_maxag
suffix:semicolon
multiline_comment|/* 4: for standalone test driver  */
DECL|member|pad
id|u8
id|pad
(braket
l_int|2016
)braket
suffix:semicolon
multiline_comment|/* 2016: pad to 2048 */
DECL|member|in_agctl
id|iagctl_t
id|in_agctl
(braket
id|MAXAG
)braket
suffix:semicolon
multiline_comment|/* 2048: AG control information */
DECL|typedef|dinomap_t
)brace
id|dinomap_t
suffix:semicolon
multiline_comment|/* (4096) */
multiline_comment|/*&n; *&t;In-core inode map control page&n; */
DECL|struct|inomap
r_typedef
r_struct
id|inomap
(brace
DECL|member|im_imap
id|dinomap_t
id|im_imap
suffix:semicolon
multiline_comment|/* 4096: inode allocation control */
DECL|member|im_ipimap
r_struct
id|inode
op_star
id|im_ipimap
suffix:semicolon
multiline_comment|/* 4: ptr to inode for imap   */
DECL|member|im_freelock
r_struct
id|semaphore
id|im_freelock
suffix:semicolon
multiline_comment|/* 4: iag free list lock      */
DECL|member|im_aglock
r_struct
id|semaphore
id|im_aglock
(braket
id|MAXAG
)braket
suffix:semicolon
multiline_comment|/* 512: per AG locks          */
DECL|member|im_DBGdimap
id|u32
op_star
id|im_DBGdimap
suffix:semicolon
DECL|member|im_numinos
id|atomic_t
id|im_numinos
suffix:semicolon
multiline_comment|/* num of backed inodes */
DECL|member|im_numfree
id|atomic_t
id|im_numfree
suffix:semicolon
multiline_comment|/* num of free backed inodes */
DECL|typedef|imap_t
)brace
id|imap_t
suffix:semicolon
DECL|macro|im_freeiag
mdefine_line|#define&t;im_freeiag&t;im_imap.in_freeiag
DECL|macro|im_nextiag
mdefine_line|#define&t;im_nextiag&t;im_imap.in_nextiag
DECL|macro|im_agctl
mdefine_line|#define&t;im_agctl&t;im_imap.in_agctl
DECL|macro|im_nbperiext
mdefine_line|#define&t;im_nbperiext&t;im_imap.in_nbperiext
DECL|macro|im_l2nbperiext
mdefine_line|#define&t;im_l2nbperiext&t;im_imap.in_l2nbperiext
multiline_comment|/* for standalone testdriver&n; */
DECL|macro|im_diskblock
mdefine_line|#define&t;im_diskblock&t;im_imap.in_diskblock
DECL|macro|im_maxag
mdefine_line|#define&t;im_maxag&t;im_imap.in_maxag
r_extern
r_int
id|diFree
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|diAlloc
c_func
(paren
r_struct
id|inode
op_star
comma
id|boolean_t
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|diSync
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* external references */
r_extern
r_int
id|diUpdatePMap
c_func
(paren
r_struct
id|inode
op_star
id|ipimap
comma
r_int
r_int
id|inum
comma
id|boolean_t
id|is_free
comma
id|tblock_t
op_star
id|tblk
)paren
suffix:semicolon
macro_line|#ifdef _STILL_TO_PORT
r_extern
r_int
id|diExtendFS
c_func
(paren
id|inode_t
op_star
id|ipimap
comma
id|inode_t
op_star
id|ipbmap
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _STILL_TO_PORT */
r_extern
r_int
id|diMount
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|diUnmount
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|diRead
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|diReadSpecial
c_func
(paren
r_struct
id|super_block
op_star
comma
id|ino_t
)paren
suffix:semicolon
r_extern
r_void
id|diWriteSpecial
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|diFreeSpecial
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|diWrite
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_IMAP */
eof
