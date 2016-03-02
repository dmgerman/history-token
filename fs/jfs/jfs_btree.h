multiline_comment|/*&n; *   Copyright (C) International Business Machines Corp., 2000-2004&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_BTREE
DECL|macro|_H_JFS_BTREE
mdefine_line|#define _H_JFS_BTREE
multiline_comment|/*&n; *&t;jfs_btree.h: B+-tree&n; *&n; * JFS B+-tree (dtree and xtree) common definitions&n; */
multiline_comment|/*&n; *&t;basic btree page - btpage&n; *&n;struct btpage {&n;&t;s64 next;&t;&t;right sibling bn&n;&t;s64 prev;&t;&t;left sibling bn&n;&n;&t;u8 flag;&n;&t;u8 rsrvd[7];&t;&t;type specific&n;&t;s64 self;&t;&t;self address&n;&n;&t;u8 entry[4064];&n;};&t;&t;&t;&t;&t;&t;*/
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
mdefine_line|#define BT_GETPAGE(IP, BN, MP, TYPE, SIZE, P, RC, ROOT)&bslash;&n;{&bslash;&n;&t;if ((BN) == 0)&bslash;&n;&t;{&bslash;&n;&t;&t;MP = (struct metapage *)&amp;JFS_IP(IP)-&gt;bxflag;&bslash;&n;&t;&t;P = (TYPE *)&amp;JFS_IP(IP)-&gt;ROOT;&bslash;&n;&t;&t;RC = 0;&bslash;&n;&t;}&bslash;&n;&t;else&bslash;&n;&t;{&bslash;&n;&t;&t;MP = read_metapage((IP), BN, SIZE, 1);&bslash;&n;&t;&t;if (MP) {&bslash;&n;&t;&t;&t;RC = 0;&bslash;&n;&t;&t;&t;P = (MP)-&gt;data;&bslash;&n;&t;&t;} else {&bslash;&n;&t;&t;&t;P = NULL;&bslash;&n;&t;&t;&t;jfs_err(&quot;bread failed!&quot;);&bslash;&n;&t;&t;&t;RC = -EIO;&bslash;&n;&t;&t;}&bslash;&n;&t;}&bslash;&n;}
DECL|macro|BT_MARK_DIRTY
mdefine_line|#define BT_MARK_DIRTY(MP, IP)&bslash;&n;{&bslash;&n;&t;if (BT_IS_ROOT(MP))&bslash;&n;&t;&t;mark_inode_dirty(IP);&bslash;&n;&t;else&bslash;&n;&t;&t;mark_metapage_dirty(MP);&bslash;&n;}
multiline_comment|/* put the page buffer */
DECL|macro|BT_PUTPAGE
mdefine_line|#define BT_PUTPAGE(MP)&bslash;&n;{&bslash;&n;&t;if (! BT_IS_ROOT(MP)) &bslash;&n;&t;&t;release_metapage(MP); &bslash;&n;}
multiline_comment|/*&n; *&t;btree traversal stack&n; *&n; * record the path traversed during the search;&n; * top frame record the leaf page/entry selected.&n; */
DECL|struct|btframe
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
multiline_comment|/* 2: unused */
DECL|member|mp
r_struct
id|metapage
op_star
id|mp
suffix:semicolon
multiline_comment|/* 4/8: */
)brace
suffix:semicolon
multiline_comment|/* (16/24) */
DECL|struct|btstack
r_struct
id|btstack
(brace
DECL|member|top
r_struct
id|btframe
op_star
id|top
suffix:semicolon
DECL|member|nsplit
r_int
id|nsplit
suffix:semicolon
DECL|member|stack
r_struct
id|btframe
id|stack
(braket
id|MAXTREEHEIGHT
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BT_CLR
mdefine_line|#define BT_CLR(btstack)&bslash;&n;&t;(btstack)-&gt;top = (btstack)-&gt;stack
DECL|macro|BT_STACK_FULL
mdefine_line|#define BT_STACK_FULL(btstack)&bslash;&n;&t;( (btstack)-&gt;top == &amp;((btstack)-&gt;stack[MAXTREEHEIGHT-1]))
DECL|macro|BT_PUSH
mdefine_line|#define BT_PUSH(BTSTACK, BN, INDEX)&bslash;&n;{&bslash;&n;&t;assert(!BT_STACK_FULL(BTSTACK));&bslash;&n;&t;(BTSTACK)-&gt;top-&gt;bn = BN;&bslash;&n;&t;(BTSTACK)-&gt;top-&gt;index = INDEX;&bslash;&n;&t;++(BTSTACK)-&gt;top;&bslash;&n;}
DECL|macro|BT_POP
mdefine_line|#define BT_POP(btstack)&bslash;&n;&t;( (btstack)-&gt;top == (btstack)-&gt;stack ? NULL : --(btstack)-&gt;top )
DECL|macro|BT_STACK
mdefine_line|#define BT_STACK(btstack)&bslash;&n;&t;( (btstack)-&gt;top == (btstack)-&gt;stack ? NULL : (btstack)-&gt;top )
DECL|function|BT_STACK_DUMP
r_static
r_inline
r_void
id|BT_STACK_DUMP
c_func
(paren
r_struct
id|btstack
op_star
id|btstack
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;btstack dump:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAXTREEHEIGHT
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bn = %Lx, index = %d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|btstack-&gt;stack
(braket
id|i
)braket
dot
id|bn
comma
id|btstack-&gt;stack
(braket
id|i
)braket
dot
id|index
)paren
suffix:semicolon
)brace
multiline_comment|/* retrieve search results */
DECL|macro|BT_GETSEARCH
mdefine_line|#define BT_GETSEARCH(IP, LEAF, BN, MP, TYPE, P, INDEX, ROOT)&bslash;&n;{&bslash;&n;&t;BN = (LEAF)-&gt;bn;&bslash;&n;&t;MP = (LEAF)-&gt;mp;&bslash;&n;&t;if (BN)&bslash;&n;&t;&t;P = (TYPE *)MP-&gt;data;&bslash;&n;&t;else&bslash;&n;&t;&t;P = (TYPE *)&amp;JFS_IP(IP)-&gt;ROOT;&bslash;&n;&t;INDEX = (LEAF)-&gt;index;&bslash;&n;}
multiline_comment|/* put the page buffer of search */
DECL|macro|BT_PUTSEARCH
mdefine_line|#define BT_PUTSEARCH(BTSTACK)&bslash;&n;{&bslash;&n;&t;if (! BT_IS_ROOT((BTSTACK)-&gt;top-&gt;mp))&bslash;&n;&t;&t;release_metapage((BTSTACK)-&gt;top-&gt;mp);&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_BTREE */
eof
