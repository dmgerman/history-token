multiline_comment|/*&n; * Copyright (c) 2000, 2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DA_BTREE_H__
DECL|macro|__XFS_DA_BTREE_H__
mdefine_line|#define&t;__XFS_DA_BTREE_H__
r_struct
id|xfs_buf
suffix:semicolon
r_struct
id|xfs_bmap_free
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
r_struct
id|zone
suffix:semicolon
multiline_comment|/*========================================================================&n; * Directory Structure when greater than XFS_LBSIZE(mp) bytes.&n; *========================================================================*/
multiline_comment|/*&n; * This structure is common to both leaf nodes and non-leaf nodes in the Btree.&n; *&n; * Is is used to manage a doubly linked list of all blocks at the same&n; * level in the Btree, and to identify which type of block this is.&n; */
DECL|macro|XFS_DA_NODE_MAGIC
mdefine_line|#define XFS_DA_NODE_MAGIC&t;0xfebe&t;/* magic number: non-leaf blocks */
DECL|macro|XFS_DIR_LEAF_MAGIC
mdefine_line|#define XFS_DIR_LEAF_MAGIC&t;0xfeeb&t;/* magic number: directory leaf blks */
DECL|macro|XFS_ATTR_LEAF_MAGIC
mdefine_line|#define XFS_ATTR_LEAF_MAGIC&t;0xfbee&t;/* magic number: attribute leaf blks */
DECL|macro|XFS_DIR2_LEAF1_MAGIC
mdefine_line|#define&t;XFS_DIR2_LEAF1_MAGIC&t;0xd2f1&t;/* magic number: v2 dirlf single blks */
DECL|macro|XFS_DIR2_LEAFN_MAGIC
mdefine_line|#define&t;XFS_DIR2_LEAFN_MAGIC&t;0xd2ff&t;/* magic number: v2 dirlf multi blks */
DECL|macro|XFS_DIRX_LEAF_MAGIC
mdefine_line|#define&t;XFS_DIRX_LEAF_MAGIC(mp)&t;&bslash;&n;&t;(XFS_DIR_IS_V1(mp) ? XFS_DIR_LEAF_MAGIC : XFS_DIR2_LEAFN_MAGIC)
DECL|struct|xfs_da_blkinfo
r_typedef
r_struct
id|xfs_da_blkinfo
(brace
DECL|member|forw
id|xfs_dablk_t
id|forw
suffix:semicolon
multiline_comment|/* previous block in list */
DECL|member|back
id|xfs_dablk_t
id|back
suffix:semicolon
multiline_comment|/* following block in list */
DECL|member|magic
id|__uint16_t
id|magic
suffix:semicolon
multiline_comment|/* validity check on block */
DECL|member|pad
id|__uint16_t
id|pad
suffix:semicolon
multiline_comment|/* unused */
DECL|typedef|xfs_da_blkinfo_t
)brace
id|xfs_da_blkinfo_t
suffix:semicolon
multiline_comment|/*&n; * This is the structure of the root and intermediate nodes in the Btree.&n; * The leaf nodes are defined above.&n; *&n; * Entries are not packed.&n; *&n; * Since we have duplicate keys, use a binary search but always follow&n; * all match in the block, not just the first match found.&n; */
DECL|macro|XFS_DA_NODE_MAXDEPTH
mdefine_line|#define&t;XFS_DA_NODE_MAXDEPTH&t;5&t;/* max depth of Btree */
DECL|struct|xfs_da_intnode
r_typedef
r_struct
id|xfs_da_intnode
(brace
DECL|struct|xfs_da_node_hdr
r_struct
id|xfs_da_node_hdr
(brace
multiline_comment|/* constant-structure header block */
DECL|member|info
id|xfs_da_blkinfo_t
id|info
suffix:semicolon
multiline_comment|/* block type, links, etc. */
DECL|member|count
id|__uint16_t
id|count
suffix:semicolon
multiline_comment|/* count of active entries */
DECL|member|level
id|__uint16_t
id|level
suffix:semicolon
multiline_comment|/* level above leaves (leaf == 0) */
DECL|member|hdr
)brace
id|hdr
suffix:semicolon
DECL|struct|xfs_da_node_entry
r_struct
id|xfs_da_node_entry
(brace
DECL|member|hashval
id|xfs_dahash_t
id|hashval
suffix:semicolon
multiline_comment|/* hash value for this descendant */
DECL|member|before
id|xfs_dablk_t
id|before
suffix:semicolon
multiline_comment|/* Btree block before this key */
DECL|member|btree
)brace
id|btree
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* variable sized array of keys */
DECL|typedef|xfs_da_intnode_t
)brace
id|xfs_da_intnode_t
suffix:semicolon
DECL|typedef|xfs_da_node_hdr_t
r_typedef
r_struct
id|xfs_da_node_hdr
id|xfs_da_node_hdr_t
suffix:semicolon
DECL|typedef|xfs_da_node_entry_t
r_typedef
r_struct
id|xfs_da_node_entry
id|xfs_da_node_entry_t
suffix:semicolon
DECL|macro|XFS_DA_MAXHASH
mdefine_line|#define XFS_DA_MAXHASH&t;((xfs_dahash_t)-1) /* largest valid hash value */
multiline_comment|/*&n; * Macros used by directory code to interface to the filesystem.&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LBSIZE)
r_int
id|xfs_lbsize
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_LBSIZE
mdefine_line|#define&t;XFS_LBSIZE(mp)&t;&t;&t;xfs_lbsize(mp)
macro_line|#else
DECL|macro|XFS_LBSIZE
mdefine_line|#define&t;XFS_LBSIZE(mp)&t;((mp)-&gt;m_sb.sb_blocksize)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_LBLOG)
r_int
id|xfs_lblog
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
DECL|macro|XFS_LBLOG
mdefine_line|#define&t;XFS_LBLOG(mp)&t;&t;&t;xfs_lblog(mp)
macro_line|#else
DECL|macro|XFS_LBLOG
mdefine_line|#define&t;XFS_LBLOG(mp)&t;((mp)-&gt;m_sb.sb_blocklog)
macro_line|#endif
multiline_comment|/*&n; * Macros used by directory code to interface to the kernel&n; */
multiline_comment|/*&n; * Macros used to manipulate directory off_t&squot;s&n; */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DA_MAKE_BNOENTRY)
id|__uint32_t
id|xfs_da_make_bnoentry
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dablk_t
id|bno
comma
r_int
id|entry
)paren
suffix:semicolon
DECL|macro|XFS_DA_MAKE_BNOENTRY
mdefine_line|#define&t;XFS_DA_MAKE_BNOENTRY(mp,bno,entry)&t;&bslash;&n;&t;xfs_da_make_bnoentry(mp,bno,entry)
macro_line|#else
DECL|macro|XFS_DA_MAKE_BNOENTRY
mdefine_line|#define&t;XFS_DA_MAKE_BNOENTRY(mp,bno,entry) &bslash;&n;&t;(((bno) &lt;&lt; (mp)-&gt;m_dircook_elog) | (entry))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DA_MAKE_COOKIE)
id|xfs_off_t
id|xfs_da_make_cookie
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_dablk_t
id|bno
comma
r_int
id|entry
comma
id|xfs_dahash_t
id|hash
)paren
suffix:semicolon
DECL|macro|XFS_DA_MAKE_COOKIE
mdefine_line|#define&t;XFS_DA_MAKE_COOKIE(mp,bno,entry,hash)&t;&bslash;&n;&t;xfs_da_make_cookie(mp,bno,entry,hash)
macro_line|#else
DECL|macro|XFS_DA_MAKE_COOKIE
mdefine_line|#define&t;XFS_DA_MAKE_COOKIE(mp,bno,entry,hash) &bslash;&n;&t;(((xfs_off_t)XFS_DA_MAKE_BNOENTRY(mp, bno, entry) &lt;&lt; 32) | (hash))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DA_COOKIE_HASH)
id|xfs_dahash_t
id|xfs_da_cookie_hash
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_off_t
id|cookie
)paren
suffix:semicolon
DECL|macro|XFS_DA_COOKIE_HASH
mdefine_line|#define&t;XFS_DA_COOKIE_HASH(mp,cookie)&t;&t;xfs_da_cookie_hash(mp,cookie)
macro_line|#else
DECL|macro|XFS_DA_COOKIE_HASH
mdefine_line|#define&t;XFS_DA_COOKIE_HASH(mp,cookie)&t;((xfs_dahash_t)(cookie))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DA_COOKIE_BNO)
id|xfs_dablk_t
id|xfs_da_cookie_bno
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_off_t
id|cookie
)paren
suffix:semicolon
DECL|macro|XFS_DA_COOKIE_BNO
mdefine_line|#define&t;XFS_DA_COOKIE_BNO(mp,cookie)&t;&t;xfs_da_cookie_bno(mp,cookie)
macro_line|#else
DECL|macro|XFS_DA_COOKIE_BNO
mdefine_line|#define&t;XFS_DA_COOKIE_BNO(mp,cookie) &bslash;&n;&t;(((xfs_off_t)(cookie) &gt;&gt; 31) == -1LL ? &bslash;&n;&t;&t;(xfs_dablk_t)0 : &bslash;&n;&t;&t;(xfs_dablk_t)((xfs_off_t)(cookie) &gt;&gt; ((mp)-&gt;m_dircook_elog + 32)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DA_COOKIE_ENTRY)
r_int
id|xfs_da_cookie_entry
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_off_t
id|cookie
)paren
suffix:semicolon
DECL|macro|XFS_DA_COOKIE_ENTRY
mdefine_line|#define&t;XFS_DA_COOKIE_ENTRY(mp,cookie)&t;&t;xfs_da_cookie_entry(mp,cookie)
macro_line|#else
DECL|macro|XFS_DA_COOKIE_ENTRY
mdefine_line|#define&t;XFS_DA_COOKIE_ENTRY(mp,cookie) &bslash;&n;&t;(((xfs_off_t)(cookie) &gt;&gt; 31) == -1LL ? &bslash;&n;&t;&t;(xfs_dablk_t)0 : &bslash;&n;&t;&t;(xfs_dablk_t)(((xfs_off_t)(cookie) &gt;&gt; 32) &amp; &bslash;&n;&t;&t;&t;      ((1 &lt;&lt; (mp)-&gt;m_dircook_elog) - 1)))
macro_line|#endif
multiline_comment|/*========================================================================&n; * Btree searching and modification structure definitions.&n; *========================================================================*/
multiline_comment|/*&n; * Structure to ease passing around component names.&n; */
DECL|struct|xfs_da_args
r_typedef
r_struct
id|xfs_da_args
(brace
DECL|member|name
id|uchar_t
op_star
id|name
suffix:semicolon
multiline_comment|/* string (maybe not NULL terminated) */
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
multiline_comment|/* length of string (maybe no NULL) */
DECL|member|value
id|uchar_t
op_star
id|value
suffix:semicolon
multiline_comment|/* set of bytes (maybe contain NULLs) */
DECL|member|valuelen
r_int
id|valuelen
suffix:semicolon
multiline_comment|/* length of value */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* argument flags (eg: ATTR_NOCREATE) */
DECL|member|hashval
id|xfs_dahash_t
id|hashval
suffix:semicolon
multiline_comment|/* hash value of name */
DECL|member|inumber
id|xfs_ino_t
id|inumber
suffix:semicolon
multiline_comment|/* input/output inode number */
DECL|member|dp
r_struct
id|xfs_inode
op_star
id|dp
suffix:semicolon
multiline_comment|/* directory inode to manipulate */
DECL|member|firstblock
id|xfs_fsblock_t
op_star
id|firstblock
suffix:semicolon
multiline_comment|/* ptr to firstblock for bmap calls */
DECL|member|flist
r_struct
id|xfs_bmap_free
op_star
id|flist
suffix:semicolon
multiline_comment|/* ptr to freelist for bmap_finish */
DECL|member|trans
r_struct
id|xfs_trans
op_star
id|trans
suffix:semicolon
multiline_comment|/* current trans (changes over time) */
DECL|member|total
id|xfs_extlen_t
id|total
suffix:semicolon
multiline_comment|/* total blocks needed, for 1st bmap */
DECL|member|whichfork
r_int
id|whichfork
suffix:semicolon
multiline_comment|/* data or attribute fork */
DECL|member|blkno
id|xfs_dablk_t
id|blkno
suffix:semicolon
multiline_comment|/* blkno of attr leaf of interest */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* index of attr of interest in blk */
DECL|member|rmtblkno
id|xfs_dablk_t
id|rmtblkno
suffix:semicolon
multiline_comment|/* remote attr value starting blkno */
DECL|member|rmtblkcnt
r_int
id|rmtblkcnt
suffix:semicolon
multiline_comment|/* remote attr value block count */
DECL|member|blkno2
id|xfs_dablk_t
id|blkno2
suffix:semicolon
multiline_comment|/* blkno of 2nd attr leaf of interest */
DECL|member|index2
r_int
id|index2
suffix:semicolon
multiline_comment|/* index of 2nd attr in blk */
DECL|member|rmtblkno2
id|xfs_dablk_t
id|rmtblkno2
suffix:semicolon
multiline_comment|/* remote attr value starting blkno */
DECL|member|rmtblkcnt2
r_int
id|rmtblkcnt2
suffix:semicolon
multiline_comment|/* remote attr value block count */
DECL|member|justcheck
r_int
id|justcheck
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: check for ok with no space */
DECL|member|rename
r_int
id|rename
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: this is an atomic rename op */
DECL|member|addname
r_int
id|addname
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: this is an add operation */
DECL|member|oknoent
r_int
id|oknoent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: ok to return ENOENT, else die */
DECL|typedef|xfs_da_args_t
)brace
id|xfs_da_args_t
suffix:semicolon
multiline_comment|/*&n; * Structure to describe buffer(s) for a block.&n; * This is needed in the directory version 2 format case, when&n; * multiple non-contiguous fsblocks might be needed to cover one&n; * logical directory block.&n; * If the buffer count is 1 then the data pointer points to the&n; * same place as the b_addr field for the buffer, else to kmem_alloced memory.&n; */
DECL|struct|xfs_dabuf
r_typedef
r_struct
id|xfs_dabuf
(brace
DECL|member|nbuf
r_int
id|nbuf
suffix:semicolon
multiline_comment|/* number of buffer pointers present */
DECL|member|dirty
r_int
id|dirty
suffix:semicolon
multiline_comment|/* data needs to be copied back */
DECL|member|bbcount
r_int
id|bbcount
suffix:semicolon
multiline_comment|/* how large is data in bbs */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* pointer for buffers&squot; data */
macro_line|#ifdef XFS_DABUF_DEBUG
DECL|member|ra
id|inst_t
op_star
id|ra
suffix:semicolon
multiline_comment|/* return address of caller to make */
DECL|member|next
r_struct
id|xfs_dabuf
op_star
id|next
suffix:semicolon
multiline_comment|/* next in global chain */
DECL|member|prev
r_struct
id|xfs_dabuf
op_star
id|prev
suffix:semicolon
multiline_comment|/* previous in global chain */
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
multiline_comment|/* device for buffer */
DECL|member|blkno
id|xfs_daddr_t
id|blkno
suffix:semicolon
multiline_comment|/* daddr first in bps[0] */
macro_line|#endif
DECL|member|bps
r_struct
id|xfs_buf
op_star
id|bps
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* actually nbuf of these */
DECL|typedef|xfs_dabuf_t
)brace
id|xfs_dabuf_t
suffix:semicolon
DECL|macro|XFS_DA_BUF_SIZE
mdefine_line|#define&t;XFS_DA_BUF_SIZE(n)&t;&bslash;&n;&t;(sizeof(xfs_dabuf_t) + sizeof(struct xfs_buf *) * ((n) - 1))
macro_line|#ifdef XFS_DABUF_DEBUG
r_extern
id|xfs_dabuf_t
op_star
id|xfs_dabuf_global_list
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Storage for holding state during Btree searches and split/join ops.&n; *&n; * Only need space for 5 intermediate nodes.  With a minimum of 62-way&n; * fanout to the Btree, we can support over 900 million directory blocks,&n; * which is slightly more than enough.&n; */
DECL|struct|xfs_da_state_blk
r_typedef
r_struct
id|xfs_da_state_blk
(brace
DECL|member|bp
id|xfs_dabuf_t
op_star
id|bp
suffix:semicolon
multiline_comment|/* buffer containing block */
DECL|member|blkno
id|xfs_dablk_t
id|blkno
suffix:semicolon
multiline_comment|/* filesystem blkno of buffer */
DECL|member|disk_blkno
id|xfs_daddr_t
id|disk_blkno
suffix:semicolon
multiline_comment|/* on-disk blkno (in BBs) of buffer */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* relevant index into block */
DECL|member|hashval
id|xfs_dahash_t
id|hashval
suffix:semicolon
multiline_comment|/* last hash value in block */
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* blk&squot;s magic number, ie: blk type */
DECL|typedef|xfs_da_state_blk_t
)brace
id|xfs_da_state_blk_t
suffix:semicolon
DECL|struct|xfs_da_state_path
r_typedef
r_struct
id|xfs_da_state_path
(brace
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* number of active levels */
DECL|member|blk
id|xfs_da_state_blk_t
id|blk
(braket
id|XFS_DA_NODE_MAXDEPTH
)braket
suffix:semicolon
DECL|typedef|xfs_da_state_path_t
)brace
id|xfs_da_state_path_t
suffix:semicolon
DECL|struct|xfs_da_state
r_typedef
r_struct
id|xfs_da_state
(brace
DECL|member|args
id|xfs_da_args_t
op_star
id|args
suffix:semicolon
multiline_comment|/* filename arguments */
DECL|member|mp
r_struct
id|xfs_mount
op_star
id|mp
suffix:semicolon
multiline_comment|/* filesystem mount point */
DECL|member|blocksize
r_int
r_int
id|blocksize
suffix:semicolon
multiline_comment|/* logical block size */
DECL|member|node_ents
r_int
r_int
id|node_ents
suffix:semicolon
multiline_comment|/* how many entries in danode */
DECL|member|path
id|xfs_da_state_path_t
id|path
suffix:semicolon
multiline_comment|/* search/split paths */
DECL|member|altpath
id|xfs_da_state_path_t
id|altpath
suffix:semicolon
multiline_comment|/* alternate path for join */
DECL|member|inleaf
r_int
r_int
id|inleaf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* insert into 1-&gt;lf, 0-&gt;splf */
DECL|member|holeok
r_int
r_int
id|holeok
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: can deal with a hole */
DECL|member|extravalid
r_int
r_int
id|extravalid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: extrablk is in use */
DECL|member|extraafter
r_int
r_int
id|extraafter
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* T/F: extrablk is after new */
DECL|member|extrablk
id|xfs_da_state_blk_t
id|extrablk
suffix:semicolon
multiline_comment|/* for double-splits on leafs */
multiline_comment|/* for dirv2 extrablk is data */
DECL|typedef|xfs_da_state_t
)brace
id|xfs_da_state_t
suffix:semicolon
multiline_comment|/*&n; * Utility macros to aid in logging changed structure fields.&n; */
DECL|macro|XFS_DA_LOGOFF
mdefine_line|#define XFS_DA_LOGOFF(BASE, ADDR)&t;((char *)(ADDR) - (char *)(BASE))
DECL|macro|XFS_DA_LOGRANGE
mdefine_line|#define XFS_DA_LOGRANGE(BASE, ADDR, SIZE)&t;&bslash;&n;&t;&t;(uint)(XFS_DA_LOGOFF(BASE, ADDR)), &bslash;&n;&t;&t;(uint)(XFS_DA_LOGOFF(BASE, ADDR)+(SIZE)-1)
macro_line|#ifdef __KERNEL__
multiline_comment|/*========================================================================&n; * Function prototypes for the kernel.&n; *========================================================================*/
multiline_comment|/*&n; * Routines used for growing the Btree.&n; */
r_int
id|xfs_da_node_create
c_func
(paren
id|xfs_da_args_t
op_star
id|args
comma
id|xfs_dablk_t
id|blkno
comma
r_int
id|level
comma
id|xfs_dabuf_t
op_star
op_star
id|bpp
comma
r_int
id|whichfork
)paren
suffix:semicolon
r_int
id|xfs_da_split
c_func
(paren
id|xfs_da_state_t
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/*&n; * Routines used for shrinking the Btree.&n; */
r_int
id|xfs_da_join
c_func
(paren
id|xfs_da_state_t
op_star
id|state
)paren
suffix:semicolon
r_void
id|xfs_da_fixhashpath
c_func
(paren
id|xfs_da_state_t
op_star
id|state
comma
id|xfs_da_state_path_t
op_star
id|path_to_to_fix
)paren
suffix:semicolon
multiline_comment|/*&n; * Routines used for finding things in the Btree.&n; */
r_int
id|xfs_da_node_lookup_int
c_func
(paren
id|xfs_da_state_t
op_star
id|state
comma
r_int
op_star
id|result
)paren
suffix:semicolon
r_int
id|xfs_da_path_shift
c_func
(paren
id|xfs_da_state_t
op_star
id|state
comma
id|xfs_da_state_path_t
op_star
id|path
comma
r_int
id|forward
comma
r_int
id|release
comma
r_int
op_star
id|result
)paren
suffix:semicolon
multiline_comment|/*&n; * Utility routines.&n; */
r_int
id|xfs_da_blk_unlink
c_func
(paren
id|xfs_da_state_t
op_star
id|state
comma
id|xfs_da_state_blk_t
op_star
id|drop_blk
comma
id|xfs_da_state_blk_t
op_star
id|save_blk
)paren
suffix:semicolon
r_int
id|xfs_da_blk_link
c_func
(paren
id|xfs_da_state_t
op_star
id|state
comma
id|xfs_da_state_blk_t
op_star
id|old_blk
comma
id|xfs_da_state_blk_t
op_star
id|new_blk
)paren
suffix:semicolon
multiline_comment|/*&n; * Utility routines.&n; */
r_int
id|xfs_da_grow_inode
c_func
(paren
id|xfs_da_args_t
op_star
id|args
comma
id|xfs_dablk_t
op_star
id|new_blkno
)paren
suffix:semicolon
r_int
id|xfs_da_get_buf
c_func
(paren
r_struct
id|xfs_trans
op_star
id|trans
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
id|xfs_dablk_t
id|bno
comma
id|xfs_daddr_t
id|mappedbno
comma
id|xfs_dabuf_t
op_star
op_star
id|bp
comma
r_int
id|whichfork
)paren
suffix:semicolon
r_int
id|xfs_da_read_buf
c_func
(paren
r_struct
id|xfs_trans
op_star
id|trans
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
id|xfs_dablk_t
id|bno
comma
id|xfs_daddr_t
id|mappedbno
comma
id|xfs_dabuf_t
op_star
op_star
id|bpp
comma
r_int
id|whichfork
)paren
suffix:semicolon
id|xfs_daddr_t
id|xfs_da_reada_buf
c_func
(paren
r_struct
id|xfs_trans
op_star
id|trans
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
id|xfs_dablk_t
id|bno
comma
r_int
id|whichfork
)paren
suffix:semicolon
r_int
id|xfs_da_shrink_inode
c_func
(paren
id|xfs_da_args_t
op_star
id|args
comma
id|xfs_dablk_t
id|dead_blkno
comma
id|xfs_dabuf_t
op_star
id|dead_buf
)paren
suffix:semicolon
id|uint
id|xfs_da_hashname
c_func
(paren
id|uchar_t
op_star
id|name_string
comma
r_int
id|name_length
)paren
suffix:semicolon
id|uint
id|xfs_da_log2_roundup
c_func
(paren
id|uint
id|i
)paren
suffix:semicolon
id|xfs_da_state_t
op_star
id|xfs_da_state_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|xfs_da_state_free
c_func
(paren
id|xfs_da_state_t
op_star
id|state
)paren
suffix:semicolon
r_void
id|xfs_da_state_kill_altpath
c_func
(paren
id|xfs_da_state_t
op_star
id|state
)paren
suffix:semicolon
r_void
id|xfs_da_buf_done
c_func
(paren
id|xfs_dabuf_t
op_star
id|dabuf
)paren
suffix:semicolon
r_void
id|xfs_da_log_buf
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
id|xfs_dabuf_t
op_star
id|dabuf
comma
id|uint
id|first
comma
id|uint
id|last
)paren
suffix:semicolon
r_void
id|xfs_da_brelse
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
id|xfs_dabuf_t
op_star
id|dabuf
)paren
suffix:semicolon
r_void
id|xfs_da_binval
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
id|xfs_dabuf_t
op_star
id|dabuf
)paren
suffix:semicolon
id|xfs_daddr_t
id|xfs_da_blkno
c_func
(paren
id|xfs_dabuf_t
op_star
id|dabuf
)paren
suffix:semicolon
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_da_state_zone
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_DA_BTREE_H__ */
eof
