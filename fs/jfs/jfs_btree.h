multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2001&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_BTREE
DECL|macro|_H_JFS_BTREE
mdefine_line|#define _H_JFS_BTREE
multiline_comment|/*&n; *&t;jfs_btree.h: B+-tree&n; *&n; * JFS B+-tree (dtree and xtree) common definitions&n; */
multiline_comment|/*&n; *&t;basic btree page - btpage_t&n; */
r_typedef
r_struct
(brace
DECL|member|next
id|s64
id|next
suffix:semicolon
multiline_comment|/* 8: right sibling bn */
DECL|member|prev
id|s64
id|prev
suffix:semicolon
multiline_comment|/* 8: left sibling bn */
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|rsrvd
id|u8
id|rsrvd
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 7: type specific */
DECL|member|self
id|s64
id|self
suffix:semicolon
multiline_comment|/* 8: self address */
DECL|member|entry
id|u8
id|entry
(braket
l_int|4064
)braket
suffix:semicolon
multiline_comment|/* 4064: */
DECL|typedef|btpage_t
)brace
id|btpage_t
suffix:semicolon
multiline_comment|/* (4096) */
multiline_comment|/* btpaget_t flag */
DECL|macro|BT_TYPE
mdefine_line|#define BT_TYPE&t;&t;0x07&t;/* B+-tree index */
DECL|macro|BT_ROOT
mdefine_line|#define&t;BT_ROOT&t;&t;0x01&t;/* root page */
DECL|macro|BT_LEAF
mdefine_line|#define&t;BT_LEAF&t;&t;0x02&t;/* leaf page */
DECL|macro|BT_INTERNAL
mdefine_line|#define&t;BT_INTERNAL&t;0x04&t;/* internal page */
DECL|macro|BT_RIGHTMOST
mdefine_line|#define&t;BT_RIGHTMOST&t;0x10&t;/* rightmost page */
DECL|macro|BT_LEFTMOST
mdefine_line|#define&t;BT_LEFTMOST&t;0x20&t;/* leftmost page */
DECL|macro|BT_SWAPPED
mdefine_line|#define&t;BT_SWAPPED&t;0x80&t;/* used by fsck for endian swapping */
multiline_comment|/* btorder (in inode) */
DECL|macro|BT_RANDOM
mdefine_line|#define&t;BT_RANDOM&t;&t;0x0000
DECL|macro|BT_SEQUENTIAL
mdefine_line|#define&t;BT_SEQUENTIAL&t;&t;0x0001
DECL|macro|BT_LOOKUP
mdefine_line|#define&t;BT_LOOKUP&t;&t;0x0010
DECL|macro|BT_INSERT
mdefine_line|#define&t;BT_INSERT&t;&t;0x0020
DECL|macro|BT_DELETE
mdefine_line|#define&t;BT_DELETE&t;&t;0x0040
multiline_comment|/*&n; *&t;btree page buffer cache access&n; */
DECL|macro|BT_IS_ROOT
mdefine_line|#define BT_IS_ROOT(MP) (((MP)-&gt;xflag &amp; COMMIT_PAGE) == 0)
multiline_comment|/* get page from buffer page */
DECL|macro|BT_PAGE
mdefine_line|#define BT_PAGE(IP, MP, TYPE, ROOT)&bslash;&n;&t;(BT_IS_ROOT(MP) ? (TYPE *)&amp;JFS_IP(IP)-&gt;ROOT : (TYPE *)(MP)-&gt;data)
multiline_comment|/* get the page buffer and the page for specified block address */
DECL|macro|BT_GETPAGE
mdefine_line|#define BT_GETPAGE(IP, BN, MP, TYPE, SIZE, P, RC, ROOT)&bslash;&n;{&bslash;&n;&t;if ((BN) == 0)&bslash;&n;&t;{&bslash;&n;&t;&t;MP = (metapage_t *)&amp;JFS_IP(IP)-&gt;bxflag;&bslash;&n;&t;&t;P = (TYPE *)&amp;JFS_IP(IP)-&gt;ROOT;&bslash;&n;&t;&t;RC = 0;&bslash;&n;&t;&t;jEVENT(0,(&quot;%d BT_GETPAGE returning root&bslash;n&quot;, __LINE__));&bslash;&n;&t;}&bslash;&n;&t;else&bslash;&n;&t;{&bslash;&n;&t;&t;jEVENT(0,(&quot;%d BT_GETPAGE reading block %d&bslash;n&quot;, __LINE__,&bslash;&n;&t;&t;&t; (int)BN));&bslash;&n;&t;&t;MP = read_metapage((IP), BN, SIZE, 1);&bslash;&n;&t;&t;if (MP) {&bslash;&n;&t;&t;&t;RC = 0;&bslash;&n;&t;&t;&t;P = (MP)-&gt;data;&bslash;&n;&t;&t;} else {&bslash;&n;&t;&t;&t;P = NULL;&bslash;&n;&t;&t;&t;jERROR(1,(&quot;bread failed!&bslash;n&quot;));&bslash;&n;&t;&t;&t;RC = EIO;&bslash;&n;&t;&t;}&bslash;&n;&t;}&bslash;&n;}
DECL|macro|BT_MARK_DIRTY
mdefine_line|#define BT_MARK_DIRTY(MP, IP)&bslash;&n;{&bslash;&n;&t;if (BT_IS_ROOT(MP))&bslash;&n;&t;&t;mark_inode_dirty(IP);&bslash;&n;&t;else&bslash;&n;&t;&t;mark_metapage_dirty(MP);&bslash;&n;}
multiline_comment|/* put the page buffer */
DECL|macro|BT_PUTPAGE
mdefine_line|#define BT_PUTPAGE(MP)&bslash;&n;{&bslash;&n;&t;if (! BT_IS_ROOT(MP)) &bslash;&n;&t;&t;release_metapage(MP); &bslash;&n;}
multiline_comment|/*&n; *&t;btree traversal stack&n; *&n; * record the path traversed during the search;&n; * top frame record the leaf page/entry selected.&n; */
DECL|macro|MAXTREEHEIGHT
mdefine_line|#define&t;MAXTREEHEIGHT&t;&t;8
DECL|struct|btframe
r_typedef
r_struct
id|btframe
(brace
multiline_comment|/* stack frame */
DECL|member|bn
id|s64
id|bn
suffix:semicolon
multiline_comment|/* 8: */
DECL|member|index
id|s16
id|index
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|lastindex
id|s16
id|lastindex
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|mp
r_struct
id|metapage
op_star
id|mp
suffix:semicolon
multiline_comment|/* 4: */
DECL|typedef|btframe_t
)brace
id|btframe_t
suffix:semicolon
multiline_comment|/* (16) */
DECL|struct|btstack
r_typedef
r_struct
id|btstack
(brace
DECL|member|top
id|btframe_t
op_star
id|top
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|nsplit
r_int
id|nsplit
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|stack
id|btframe_t
id|stack
(braket
id|MAXTREEHEIGHT
)braket
suffix:semicolon
DECL|typedef|btstack_t
)brace
id|btstack_t
suffix:semicolon
DECL|macro|BT_CLR
mdefine_line|#define BT_CLR(btstack)&bslash;&n;&t;(btstack)-&gt;top = (btstack)-&gt;stack
DECL|macro|BT_PUSH
mdefine_line|#define BT_PUSH(BTSTACK, BN, INDEX)&bslash;&n;{&bslash;&n;&t;(BTSTACK)-&gt;top-&gt;bn = BN;&bslash;&n;&t;(BTSTACK)-&gt;top-&gt;index = INDEX;&bslash;&n;&t;++(BTSTACK)-&gt;top;&bslash;&n;&t;assert((BTSTACK)-&gt;top != &amp;((BTSTACK)-&gt;stack[MAXTREEHEIGHT]));&bslash;&n;}
DECL|macro|BT_POP
mdefine_line|#define BT_POP(btstack)&bslash;&n;&t;( (btstack)-&gt;top == (btstack)-&gt;stack ? NULL : --(btstack)-&gt;top )
DECL|macro|BT_STACK
mdefine_line|#define BT_STACK(btstack)&bslash;&n;&t;( (btstack)-&gt;top == (btstack)-&gt;stack ? NULL : (btstack)-&gt;top )
multiline_comment|/* retrieve search results */
DECL|macro|BT_GETSEARCH
mdefine_line|#define BT_GETSEARCH(IP, LEAF, BN, MP, TYPE, P, INDEX, ROOT)&bslash;&n;{&bslash;&n;&t;BN = (LEAF)-&gt;bn;&bslash;&n;&t;MP = (LEAF)-&gt;mp;&bslash;&n;&t;if (BN)&bslash;&n;&t;&t;P = (TYPE *)MP-&gt;data;&bslash;&n;&t;else&bslash;&n;&t;&t;P = (TYPE *)&amp;JFS_IP(IP)-&gt;ROOT;&bslash;&n;&t;INDEX = (LEAF)-&gt;index;&bslash;&n;}
multiline_comment|/* put the page buffer of search */
DECL|macro|BT_PUTSEARCH
mdefine_line|#define BT_PUTSEARCH(BTSTACK)&bslash;&n;{&bslash;&n;&t;if (! BT_IS_ROOT((BTSTACK)-&gt;top-&gt;mp))&bslash;&n;&t;&t;release_metapage((BTSTACK)-&gt;top-&gt;mp);&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_BTREE */
eof
