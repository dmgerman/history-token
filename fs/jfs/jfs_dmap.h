multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; *&t;jfs_dmap.h: block allocation map manager&n; */
macro_line|#ifndef&t;_H_JFS_DMAP
DECL|macro|_H_JFS_DMAP
mdefine_line|#define _H_JFS_DMAP
macro_line|#include &quot;jfs_txnmgr.h&quot;
DECL|macro|BMAPVERSION
mdefine_line|#define BMAPVERSION&t;1&t;/* version number */
DECL|macro|TREESIZE
mdefine_line|#define&t;TREESIZE&t;(256+64+16+4+1)&t;/* size of a dmap tree */
DECL|macro|LEAFIND
mdefine_line|#define&t;LEAFIND&t;&t;(64+16+4+1)&t;/* index of 1st leaf of a dmap tree */
DECL|macro|LPERDMAP
mdefine_line|#define LPERDMAP&t;256&t;/* num leaves per dmap tree */
DECL|macro|L2LPERDMAP
mdefine_line|#define L2LPERDMAP&t;8&t;/* l2 number of leaves per dmap tree */
DECL|macro|DBWORD
mdefine_line|#define&t;DBWORD&t;&t;32&t;/* # of blks covered by a map word */
DECL|macro|L2DBWORD
mdefine_line|#define&t;L2DBWORD&t;5&t;/* l2 # of blks covered by a mword */
DECL|macro|BUDMIN
mdefine_line|#define BUDMIN  &t;L2DBWORD&t;/* max free string in a map word */
DECL|macro|BPERDMAP
mdefine_line|#define BPERDMAP&t;(LPERDMAP * DBWORD)&t;/* num of blks per dmap */
DECL|macro|L2BPERDMAP
mdefine_line|#define L2BPERDMAP&t;13&t;/* l2 num of blks per dmap */
DECL|macro|CTLTREESIZE
mdefine_line|#define CTLTREESIZE&t;(1024+256+64+16+4+1)&t;/* size of a dmapctl tree */
DECL|macro|CTLLEAFIND
mdefine_line|#define CTLLEAFIND&t;(256+64+16+4+1)&t;/* idx of 1st leaf of a dmapctl tree */
DECL|macro|LPERCTL
mdefine_line|#define LPERCTL&t;&t;1024&t;/* num of leaves per dmapctl tree */
DECL|macro|L2LPERCTL
mdefine_line|#define L2LPERCTL&t;10&t;/* l2 num of leaves per dmapctl tree */
DECL|macro|ROOT
mdefine_line|#define&t;ROOT&t;&t;0&t;/* index of the root of a tree */
DECL|macro|NOFREE
mdefine_line|#define&t;NOFREE&t;&t;((s8) -1)&t;/* no blocks free */
DECL|macro|MAXAG
mdefine_line|#define&t;MAXAG&t;&t;128&t;/* max number of allocation groups */
DECL|macro|L2MAXAG
mdefine_line|#define L2MAXAG&t;&t;7&t;/* l2 max num of AG */
DECL|macro|L2MINAGSZ
mdefine_line|#define L2MINAGSZ&t;25&t;/* l2 of minimum AG size in bytes */
DECL|macro|BMAPBLKNO
mdefine_line|#define&t;BMAPBLKNO&t;0&t;/* lblkno of bmap within the map */
multiline_comment|/*&n; * maximum l2 number of disk blocks at the various dmapctl levels.&n; */
DECL|macro|L2MAXL0SIZE
mdefine_line|#define&t;L2MAXL0SIZE&t;(L2BPERDMAP + 1 * L2LPERCTL)
DECL|macro|L2MAXL1SIZE
mdefine_line|#define&t;L2MAXL1SIZE&t;(L2BPERDMAP + 2 * L2LPERCTL)
DECL|macro|L2MAXL2SIZE
mdefine_line|#define&t;L2MAXL2SIZE&t;(L2BPERDMAP + 3 * L2LPERCTL)
multiline_comment|/*&n; * maximum number of disk blocks at the various dmapctl levels.&n; */
DECL|macro|MAXL0SIZE
mdefine_line|#define&t;MAXL0SIZE&t;((s64)1 &lt;&lt; L2MAXL0SIZE)
DECL|macro|MAXL1SIZE
mdefine_line|#define&t;MAXL1SIZE&t;((s64)1 &lt;&lt; L2MAXL1SIZE)
DECL|macro|MAXL2SIZE
mdefine_line|#define&t;MAXL2SIZE&t;((s64)1 &lt;&lt; L2MAXL2SIZE)
DECL|macro|MAXMAPSIZE
mdefine_line|#define&t;MAXMAPSIZE&t;MAXL2SIZE&t;/* maximum aggregate map size */
multiline_comment|/* &n; * determine the maximum free string for four (lower level) nodes&n; * of the tree.&n; */
DECL|function|TREEMAX
r_static
id|__inline
r_int
r_char
id|TREEMAX
c_func
(paren
r_int
r_char
op_star
id|cp
)paren
(brace
r_int
r_char
id|tmp1
comma
id|tmp2
suffix:semicolon
id|tmp1
op_assign
id|max
c_func
(paren
op_star
(paren
id|cp
op_plus
l_int|2
)paren
comma
op_star
(paren
id|cp
op_plus
l_int|3
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
id|max
c_func
(paren
op_star
(paren
id|cp
)paren
comma
op_star
(paren
id|cp
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|max
c_func
(paren
id|tmp1
comma
id|tmp2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * convert disk block number to the logical block number of the dmap&n; * describing the disk block.  s is the log2(number of logical blocks per page)&n; *&n; * The calculation figures out how many logical pages are in front of the dmap.&n; *&t;- the number of dmaps preceding it&n; *&t;- the number of L0 pages preceding its L0 page&n; *&t;- the number of L1 pages preceding its L1 page&n; *&t;- 3 is added to account for the L2, L1, and L0 page for this dmap&n; *&t;- 1 is added to account for the control page of the map.&n; */
DECL|macro|BLKTODMAP
mdefine_line|#define BLKTODMAP(b,s)    &bslash;&n;        ((((b) &gt;&gt; 13) + ((b) &gt;&gt; 23) + ((b) &gt;&gt; 33) + 3 + 1) &lt;&lt; (s))
multiline_comment|/*&n; * convert disk block number to the logical block number of the LEVEL 0&n; * dmapctl describing the disk block.  s is the log2(number of logical blocks&n; * per page)&n; *&n; * The calculation figures out how many logical pages are in front of the L0.&n; *&t;- the number of dmap pages preceding it&n; *&t;- the number of L0 pages preceding it&n; *&t;- the number of L1 pages preceding its L1 page&n; *&t;- 2 is added to account for the L2, and L1 page for this L0&n; *&t;- 1 is added to account for the control page of the map.&n; */
DECL|macro|BLKTOL0
mdefine_line|#define BLKTOL0(b,s)      &bslash;&n;        (((((b) &gt;&gt; 23) &lt;&lt; 10) + ((b) &gt;&gt; 23) + ((b) &gt;&gt; 33) + 2 + 1) &lt;&lt; (s))
multiline_comment|/*&n; * convert disk block number to the logical block number of the LEVEL 1&n; * dmapctl describing the disk block.  s is the log2(number of logical blocks&n; * per page)&n; *&n; * The calculation figures out how many logical pages are in front of the L1.&n; *&t;- the number of dmap pages preceding it&n; *&t;- the number of L0 pages preceding it&n; *&t;- the number of L1 pages preceding it&n; *&t;- 1 is added to account for the L2 page&n; *&t;- 1 is added to account for the control page of the map.&n; */
DECL|macro|BLKTOL1
mdefine_line|#define BLKTOL1(b,s)      &bslash;&n;     (((((b) &gt;&gt; 33) &lt;&lt; 20) + (((b) &gt;&gt; 33) &lt;&lt; 10) + ((b) &gt;&gt; 33) + 1 + 1) &lt;&lt; (s))
multiline_comment|/*&n; * convert disk block number to the logical block number of the dmapctl&n; * at the specified level which describes the disk block.&n; */
DECL|macro|BLKTOCTL
mdefine_line|#define BLKTOCTL(b,s,l)   &bslash;&n;        (((l) == 2) ? 1 : ((l) == 1) ? BLKTOL1((b),(s)) : BLKTOL0((b),(s)))
multiline_comment|/* &n; * convert aggregate map size to the zero origin dmapctl level of the&n; * top dmapctl.&n; */
DECL|macro|BMAPSZTOLEV
mdefine_line|#define&t;BMAPSZTOLEV(size)&t;&bslash;&n;&t;(((size) &lt;= MAXL0SIZE) ? 0 : ((size) &lt;= MAXL1SIZE) ? 1 : 2)
multiline_comment|/* convert disk block number to allocation group number.&n; */
DECL|macro|BLKTOAG
mdefine_line|#define BLKTOAG(b,sbi)&t;((b) &gt;&gt; ((sbi)-&gt;bmap-&gt;db_agl2size))
multiline_comment|/* convert allocation group number to starting disk block&n; * number.&n; */
DECL|macro|AGTOBLK
mdefine_line|#define AGTOBLK(a,ip)&t;&bslash;&n;&t;((s64)(a) &lt;&lt; (JFS_SBI((ip)-&gt;i_sb)-&gt;bmap-&gt;db_agl2size))
multiline_comment|/*&n; *&t;dmap summary tree&n; *&n; * dmaptree_t must be consistent with dmapctl_t.&n; */
r_typedef
r_struct
(brace
DECL|member|nleafs
id|s32
id|nleafs
suffix:semicolon
multiline_comment|/* 4: number of tree leafs      */
DECL|member|l2nleafs
id|s32
id|l2nleafs
suffix:semicolon
multiline_comment|/* 4: l2 number of tree leafs   */
DECL|member|leafidx
id|s32
id|leafidx
suffix:semicolon
multiline_comment|/* 4: index of first tree leaf  */
DECL|member|height
id|s32
id|height
suffix:semicolon
multiline_comment|/* 4: height of the tree        */
DECL|member|budmin
id|s8
id|budmin
suffix:semicolon
multiline_comment|/* 1: min l2 tree leaf value to combine */
DECL|member|stree
id|s8
id|stree
(braket
id|TREESIZE
)braket
suffix:semicolon
multiline_comment|/* TREESIZE: tree               */
DECL|member|pad
id|u8
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 2: pad to word boundary      */
DECL|typedef|dmaptree_t
)brace
id|dmaptree_t
suffix:semicolon
multiline_comment|/* - 360 -                      */
multiline_comment|/*&n; *&t;dmap page per 8K blocks bitmap&n; */
r_typedef
r_struct
(brace
DECL|member|nblocks
id|s32
id|nblocks
suffix:semicolon
multiline_comment|/* 4: num blks covered by this dmap     */
DECL|member|nfree
id|s32
id|nfree
suffix:semicolon
multiline_comment|/* 4: num of free blks in this dmap     */
DECL|member|start
id|s64
id|start
suffix:semicolon
multiline_comment|/* 8: starting blkno for this dmap      */
DECL|member|tree
id|dmaptree_t
id|tree
suffix:semicolon
multiline_comment|/* 360: dmap tree                       */
DECL|member|pad
id|u8
id|pad
(braket
l_int|1672
)braket
suffix:semicolon
multiline_comment|/* 1672: pad to 2048 bytes              */
DECL|member|wmap
id|u32
id|wmap
(braket
id|LPERDMAP
)braket
suffix:semicolon
multiline_comment|/* 1024: bits of the working map        */
DECL|member|pmap
id|u32
id|pmap
(braket
id|LPERDMAP
)braket
suffix:semicolon
multiline_comment|/* 1024: bits of the persistent map     */
DECL|typedef|dmap_t
)brace
id|dmap_t
suffix:semicolon
multiline_comment|/* - 4096 -                             */
multiline_comment|/*&n; *&t;disk map control page per level.&n; *&n; * dmapctl_t must be consistent with dmaptree_t.&n; */
r_typedef
r_struct
(brace
DECL|member|nleafs
id|s32
id|nleafs
suffix:semicolon
multiline_comment|/* 4: number of tree leafs      */
DECL|member|l2nleafs
id|s32
id|l2nleafs
suffix:semicolon
multiline_comment|/* 4: l2 number of tree leafs   */
DECL|member|leafidx
id|s32
id|leafidx
suffix:semicolon
multiline_comment|/* 4: index of the first tree leaf      */
DECL|member|height
id|s32
id|height
suffix:semicolon
multiline_comment|/* 4: height of tree            */
DECL|member|budmin
id|s8
id|budmin
suffix:semicolon
multiline_comment|/* 1: minimum l2 tree leaf value        */
DECL|member|stree
id|s8
id|stree
(braket
id|CTLTREESIZE
)braket
suffix:semicolon
multiline_comment|/* CTLTREESIZE: dmapctl tree    */
DECL|member|pad
id|u8
id|pad
(braket
l_int|2714
)braket
suffix:semicolon
multiline_comment|/* 2714: pad to 4096            */
DECL|typedef|dmapctl_t
)brace
id|dmapctl_t
suffix:semicolon
multiline_comment|/* - 4096 -                     */
multiline_comment|/*&n; *&t;common definition for dmaptree_t within dmap and dmapctl&n; */
r_typedef
r_union
(brace
DECL|member|t1
id|dmaptree_t
id|t1
suffix:semicolon
DECL|member|t2
id|dmapctl_t
id|t2
suffix:semicolon
DECL|typedef|dmtree_t
)brace
id|dmtree_t
suffix:semicolon
multiline_comment|/* macros for accessing fields within dmtree_t */
DECL|macro|dmt_nleafs
mdefine_line|#define&t;dmt_nleafs&t;t1.nleafs
DECL|macro|dmt_l2nleafs
mdefine_line|#define&t;dmt_l2nleafs &t;t1.l2nleafs
DECL|macro|dmt_leafidx
mdefine_line|#define&t;dmt_leafidx &t;t1.leafidx
DECL|macro|dmt_height
mdefine_line|#define&t;dmt_height &t;t1.height
DECL|macro|dmt_budmin
mdefine_line|#define&t;dmt_budmin &t;t1.budmin
DECL|macro|dmt_stree
mdefine_line|#define&t;dmt_stree &t;t1.stree
multiline_comment|/* &n; *&t;on-disk aggregate disk allocation map descriptor.&n; */
r_typedef
r_struct
(brace
DECL|member|dn_mapsize
id|s64
id|dn_mapsize
suffix:semicolon
multiline_comment|/* 8: number of blocks in aggregate     */
DECL|member|dn_nfree
id|s64
id|dn_nfree
suffix:semicolon
multiline_comment|/* 8: num free blks in aggregate map    */
DECL|member|dn_l2nbperpage
id|s32
id|dn_l2nbperpage
suffix:semicolon
multiline_comment|/* 4: number of blks per page           */
DECL|member|dn_numag
id|s32
id|dn_numag
suffix:semicolon
multiline_comment|/* 4: total number of ags               */
DECL|member|dn_maxlevel
id|s32
id|dn_maxlevel
suffix:semicolon
multiline_comment|/* 4: number of active ags              */
DECL|member|dn_maxag
id|s32
id|dn_maxag
suffix:semicolon
multiline_comment|/* 4: max active alloc group number     */
DECL|member|dn_agpref
id|s32
id|dn_agpref
suffix:semicolon
multiline_comment|/* 4: preferred alloc group (hint)      */
DECL|member|dn_aglevel
id|s32
id|dn_aglevel
suffix:semicolon
multiline_comment|/* 4: dmapctl level holding the AG      */
DECL|member|dn_agheigth
id|s32
id|dn_agheigth
suffix:semicolon
multiline_comment|/* 4: height in dmapctl of the AG       */
DECL|member|dn_agwidth
id|s32
id|dn_agwidth
suffix:semicolon
multiline_comment|/* 4: width in dmapctl of the AG        */
DECL|member|dn_agstart
id|s32
id|dn_agstart
suffix:semicolon
multiline_comment|/* 4: start tree index at AG height     */
DECL|member|dn_agl2size
id|s32
id|dn_agl2size
suffix:semicolon
multiline_comment|/* 4: l2 num of blks per alloc group    */
DECL|member|dn_agfree
id|s64
id|dn_agfree
(braket
id|MAXAG
)braket
suffix:semicolon
multiline_comment|/* 8*MAXAG: per AG free count           */
DECL|member|dn_agsize
id|s64
id|dn_agsize
suffix:semicolon
multiline_comment|/* 8: num of blks per alloc group       */
DECL|member|dn_maxfreebud
id|s8
id|dn_maxfreebud
suffix:semicolon
multiline_comment|/* 1: max free buddy system             */
DECL|member|pad
id|u8
id|pad
(braket
l_int|3007
)braket
suffix:semicolon
multiline_comment|/* 3007: pad to 4096                    */
DECL|typedef|dbmap_t
)brace
id|dbmap_t
suffix:semicolon
multiline_comment|/* - 4096 -                             */
multiline_comment|/* &n; *&t;in-memory aggregate disk allocation map descriptor.&n; */
DECL|struct|bmap
r_typedef
r_struct
id|bmap
(brace
DECL|member|db_bmap
id|dbmap_t
id|db_bmap
suffix:semicolon
multiline_comment|/* on-disk aggregate map descriptor */
DECL|member|db_ipbmap
r_struct
id|inode
op_star
id|db_ipbmap
suffix:semicolon
multiline_comment|/* ptr to aggregate map incore inode */
DECL|member|db_bmaplock
r_struct
id|semaphore
id|db_bmaplock
suffix:semicolon
multiline_comment|/* aggregate map lock */
DECL|member|db_DBmap
id|u32
op_star
id|db_DBmap
suffix:semicolon
DECL|typedef|bmap_t
)brace
id|bmap_t
suffix:semicolon
multiline_comment|/* macros for accessing fields within in-memory aggregate map descriptor */
DECL|macro|db_mapsize
mdefine_line|#define&t;db_mapsize&t;db_bmap.dn_mapsize
DECL|macro|db_nfree
mdefine_line|#define&t;db_nfree&t;db_bmap.dn_nfree
DECL|macro|db_agfree
mdefine_line|#define&t;db_agfree&t;db_bmap.dn_agfree
DECL|macro|db_agsize
mdefine_line|#define&t;db_agsize&t;db_bmap.dn_agsize
DECL|macro|db_agl2size
mdefine_line|#define&t;db_agl2size&t;db_bmap.dn_agl2size
DECL|macro|db_agwidth
mdefine_line|#define&t;db_agwidth&t;db_bmap.dn_agwidth
DECL|macro|db_agheigth
mdefine_line|#define&t;db_agheigth&t;db_bmap.dn_agheigth
DECL|macro|db_agstart
mdefine_line|#define&t;db_agstart&t;db_bmap.dn_agstart
DECL|macro|db_numag
mdefine_line|#define&t;db_numag&t;db_bmap.dn_numag
DECL|macro|db_maxlevel
mdefine_line|#define&t;db_maxlevel&t;db_bmap.dn_maxlevel
DECL|macro|db_aglevel
mdefine_line|#define&t;db_aglevel&t;db_bmap.dn_aglevel
DECL|macro|db_agpref
mdefine_line|#define&t;db_agpref&t;db_bmap.dn_agpref
DECL|macro|db_maxag
mdefine_line|#define&t;db_maxag&t;db_bmap.dn_maxag
DECL|macro|db_maxfreebud
mdefine_line|#define&t;db_maxfreebud&t;db_bmap.dn_maxfreebud
DECL|macro|db_l2nbperpage
mdefine_line|#define&t;db_l2nbperpage&t;db_bmap.dn_l2nbperpage
multiline_comment|/*&n; * macros for various conversions needed by the allocators.&n; * blkstol2(), cntlz(), and cnttz() are operating system dependent functions.&n; */
multiline_comment|/* convert number of blocks to log2 number of blocks, rounding up to&n; * the next log2 value if blocks is not a l2 multiple.&n; */
DECL|macro|BLKSTOL2
mdefine_line|#define&t;BLKSTOL2(d)&t;&t;(blkstol2(d))
multiline_comment|/* convert number of leafs to log2 leaf value */
DECL|macro|NLSTOL2BSZ
mdefine_line|#define&t;NLSTOL2BSZ(n)&t;&t;(31 - cntlz((n)) + BUDMIN)
multiline_comment|/* convert leaf index to log2 leaf value */
DECL|macro|LITOL2BSZ
mdefine_line|#define&t;LITOL2BSZ(n,m,b)&t;((((n) == 0) ? (m) : cnttz((n))) + (b))
multiline_comment|/* convert a block number to a dmap control leaf index */
DECL|macro|BLKTOCTLLEAF
mdefine_line|#define BLKTOCTLLEAF(b,m)&t;&bslash;&n;&t;(((b) &amp; (((s64)1 &lt;&lt; ((m) + L2LPERCTL)) - 1)) &gt;&gt; (m))
multiline_comment|/* convert log2 leaf value to buddy size */
DECL|macro|BUDSIZE
mdefine_line|#define&t;BUDSIZE(s,m)&t;&t;(1 &lt;&lt; ((s) - (m)))
multiline_comment|/*&n; *&t;external references.&n; */
r_extern
r_int
id|dbMount
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
)paren
suffix:semicolon
r_extern
r_int
id|dbUnmount
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
comma
r_int
id|mounterror
)paren
suffix:semicolon
r_extern
r_int
id|dbFree
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
comma
id|s64
id|blkno
comma
id|s64
id|nblocks
)paren
suffix:semicolon
r_extern
r_int
id|dbUpdatePMap
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
comma
r_int
id|free
comma
id|s64
id|blkno
comma
id|s64
id|nblocks
comma
id|tblock_t
op_star
id|tblk
)paren
suffix:semicolon
r_extern
r_int
id|dbNextAG
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
)paren
suffix:semicolon
r_extern
r_int
id|dbAlloc
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
comma
id|s64
id|hint
comma
id|s64
id|nblocks
comma
id|s64
op_star
id|results
)paren
suffix:semicolon
r_extern
r_int
id|dbAllocExact
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|blkno
comma
r_int
id|nblocks
)paren
suffix:semicolon
r_extern
r_int
id|dbReAlloc
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
comma
id|s64
id|blkno
comma
id|s64
id|nblocks
comma
id|s64
id|addnblocks
comma
id|s64
op_star
id|results
)paren
suffix:semicolon
r_extern
r_int
id|dbSync
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
)paren
suffix:semicolon
r_extern
r_int
id|dbAllocBottomUp
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|s64
id|blkno
comma
id|s64
id|nblocks
)paren
suffix:semicolon
r_extern
r_int
id|dbExtendFS
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
comma
id|s64
id|blkno
comma
id|s64
id|nblocks
)paren
suffix:semicolon
r_extern
r_void
id|dbFinalizeBmap
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
)paren
suffix:semicolon
r_extern
id|s64
id|dbMapFileSizeToMapSize
c_func
(paren
r_struct
id|inode
op_star
id|ipbmap
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_DMAP */
eof
