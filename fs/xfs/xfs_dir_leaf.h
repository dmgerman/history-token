multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR_LEAF_H__
DECL|macro|__XFS_DIR_LEAF_H__
mdefine_line|#define __XFS_DIR_LEAF_H__
multiline_comment|/*&n; * Directory layout, internal structure, access macros, etc.&n; *&n; * Large directories are structured around Btrees where all the data&n; * elements are in the leaf nodes.  Filenames are hashed into an int,&n; * then that int is used as the index into the Btree.  Since the hashval&n; * of a filename may not be unique, we may have duplicate keys.&t; The&n; * internal links in the Btree are logical block offsets into the file.&n; */
r_struct
id|dirent
suffix:semicolon
r_struct
id|uio
suffix:semicolon
r_struct
id|xfs_bmap_free
suffix:semicolon
r_struct
id|xfs_dabuf
suffix:semicolon
r_struct
id|xfs_da_args
suffix:semicolon
r_struct
id|xfs_da_state
suffix:semicolon
r_struct
id|xfs_da_state_blk
suffix:semicolon
r_struct
id|xfs_dir_put_args
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
multiline_comment|/*========================================================================&n; * Directory Structure when equal to XFS_LBSIZE(mp) bytes.&n; *========================================================================*/
multiline_comment|/*&n; * This is the structure of the leaf nodes in the Btree.&n; *&n; * Struct leaf_entry&squot;s are packed from the top.&t; Names grow from the bottom&n; * but are not packed.&t;The freemap contains run-length-encoded entries&n; * for the free bytes after the leaf_entry&squot;s, but only the N largest such,&n; * smaller runs are dropped.  When the freemap doesn&squot;t show enough space&n; * for an allocation, we compact the namelist area and try again.  If we&n; * still don&squot;t have enough space, then we have to split the block.&n; *&n; * Since we have duplicate hash keys, for each key that matches, compare&n; * the actual string.  The root and intermediate node search always takes&n; * the first-in-the-block key match found, so we should only have to work&n; * &quot;forw&quot;ard.  If none matches, continue with the &quot;forw&quot;ard leaf nodes&n; * until the hash key changes or the filename is found.&n; *&n; * The parent directory and the self-pointer are explicitly represented&n; * (ie: there are entries for &quot;.&quot; and &quot;..&quot;).&n; *&n; * Note that the count being a __uint16_t limits us to something like a&n; * blocksize of 1.3MB in the face of worst case (short) filenames.&n; */
DECL|macro|XFS_DIR_LEAF_MAPSIZE
mdefine_line|#define XFS_DIR_LEAF_MAPSIZE&t;3&t;/* how many freespace slots */
DECL|struct|xfs_dir_leafblock
r_typedef
r_struct
id|xfs_dir_leafblock
(brace
DECL|struct|xfs_dir_leaf_hdr
r_struct
id|xfs_dir_leaf_hdr
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
multiline_comment|/* count of active leaf_entry&squot;s */
DECL|member|namebytes
id|__uint16_t
id|namebytes
suffix:semicolon
multiline_comment|/* num bytes of name strings stored */
DECL|member|firstused
id|__uint16_t
id|firstused
suffix:semicolon
multiline_comment|/* first used byte in name area */
DECL|member|holes
id|__uint8_t
id|holes
suffix:semicolon
multiline_comment|/* != 0 if blk needs compaction */
DECL|member|pad1
id|__uint8_t
id|pad1
suffix:semicolon
DECL|struct|xfs_dir_leaf_map
r_struct
id|xfs_dir_leaf_map
(brace
multiline_comment|/* RLE map of free bytes */
DECL|member|base
id|__uint16_t
id|base
suffix:semicolon
multiline_comment|/* base of free region */
DECL|member|size
id|__uint16_t
id|size
suffix:semicolon
multiline_comment|/* run length of free region */
DECL|member|freemap
)brace
id|freemap
(braket
id|XFS_DIR_LEAF_MAPSIZE
)braket
suffix:semicolon
multiline_comment|/* N largest free regions */
DECL|member|hdr
)brace
id|hdr
suffix:semicolon
DECL|struct|xfs_dir_leaf_entry
r_struct
id|xfs_dir_leaf_entry
(brace
multiline_comment|/* sorted on key, not name */
DECL|member|hashval
id|xfs_dahash_t
id|hashval
suffix:semicolon
multiline_comment|/* hash value of name */
DECL|member|nameidx
id|__uint16_t
id|nameidx
suffix:semicolon
multiline_comment|/* index into buffer of name */
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* length of name string */
DECL|member|pad2
id|__uint8_t
id|pad2
suffix:semicolon
DECL|member|entries
)brace
id|entries
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* var sized array */
DECL|struct|xfs_dir_leaf_name
r_struct
id|xfs_dir_leaf_name
(brace
DECL|member|inumber
id|xfs_dir_ino_t
id|inumber
suffix:semicolon
multiline_comment|/* inode number for this key */
DECL|member|name
id|__uint8_t
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name string itself */
DECL|member|namelist
)brace
id|namelist
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* grows from bottom of buf */
DECL|typedef|xfs_dir_leafblock_t
)brace
id|xfs_dir_leafblock_t
suffix:semicolon
DECL|typedef|xfs_dir_leaf_hdr_t
r_typedef
r_struct
id|xfs_dir_leaf_hdr
id|xfs_dir_leaf_hdr_t
suffix:semicolon
DECL|typedef|xfs_dir_leaf_map_t
r_typedef
r_struct
id|xfs_dir_leaf_map
id|xfs_dir_leaf_map_t
suffix:semicolon
DECL|typedef|xfs_dir_leaf_entry_t
r_typedef
r_struct
id|xfs_dir_leaf_entry
id|xfs_dir_leaf_entry_t
suffix:semicolon
DECL|typedef|xfs_dir_leaf_name_t
r_typedef
r_struct
id|xfs_dir_leaf_name
id|xfs_dir_leaf_name_t
suffix:semicolon
multiline_comment|/*&n; * Length of name for which a 512-byte block filesystem&n; * can get a double split.&n; */
DECL|macro|XFS_DIR_LEAF_CAN_DOUBLE_SPLIT_LEN
mdefine_line|#define XFS_DIR_LEAF_CAN_DOUBLE_SPLIT_LEN&t;&bslash;&n;&t;(512 - (uint)sizeof(xfs_dir_leaf_hdr_t) - &bslash;&n;&t; (uint)sizeof(xfs_dir_leaf_entry_t) * 2 - &bslash;&n;&t; (uint)sizeof(xfs_dir_leaf_name_t) * 2 - (MAXNAMELEN - 2) + 1 + 1)
DECL|typedef|xfs_dir_put_t
r_typedef
r_int
(paren
op_star
id|xfs_dir_put_t
)paren
(paren
r_struct
id|xfs_dir_put_args
op_star
id|pa
)paren
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|o
id|xfs_off_t
id|o
suffix:semicolon
multiline_comment|/* offset (cookie) */
multiline_comment|/*&n;&t; * Watch the order here (endian-ness dependent).&n;&t; */
r_struct
(brace
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|member|h
id|xfs_dahash_t
id|h
suffix:semicolon
multiline_comment|/* hash value */
DECL|member|be
id|__uint32_t
id|be
suffix:semicolon
multiline_comment|/* block and entry */
macro_line|#else&t;/* __BYTE_ORDER == __BIG_ENDIAN */
id|__uint32_t
id|be
suffix:semicolon
multiline_comment|/* block and entry */
id|xfs_dahash_t
id|h
suffix:semicolon
multiline_comment|/* hash value */
macro_line|#endif&t;/* __BYTE_ORDER == __BIG_ENDIAN */
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|typedef|xfs_dircook_t
)brace
id|xfs_dircook_t
suffix:semicolon
DECL|macro|XFS_PUT_COOKIE
mdefine_line|#define XFS_PUT_COOKIE(c,mp,bno,entry,hash)&t;&bslash;&n;&t;((c).s.be = XFS_DA_MAKE_BNOENTRY(mp, bno, entry), (c).s.h = (hash))
DECL|macro|XFS_GET_DIR_INO_ARCH
mdefine_line|#define XFS_GET_DIR_INO_ARCH(mp,di,arch) &bslash;&n;    DIRINO_GET_ARCH(&amp;(di),arch)
DECL|macro|XFS_GET_DIR_INO
mdefine_line|#define XFS_GET_DIR_INO(mp,di) &bslash;&n;    XFS_GET_DIR_INO_ARCH(mp,di,ARCH_NOCONVERT)
DECL|struct|xfs_dir_put_args
r_typedef
r_struct
id|xfs_dir_put_args
(brace
DECL|member|cook
id|xfs_dircook_t
id|cook
suffix:semicolon
multiline_comment|/* cookie of (next) entry */
DECL|member|ino
id|xfs_intino_t
id|ino
suffix:semicolon
multiline_comment|/* inode number */
DECL|member|dbp
r_struct
id|xfs_dirent
op_star
id|dbp
suffix:semicolon
multiline_comment|/* buffer pointer */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* directory entry name */
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
multiline_comment|/* length of name */
DECL|member|done
r_int
id|done
suffix:semicolon
multiline_comment|/* output: set if value was stored */
DECL|member|put
id|xfs_dir_put_t
id|put
suffix:semicolon
multiline_comment|/* put function ptr (i/o) */
DECL|member|uio
r_struct
id|uio
op_star
id|uio
suffix:semicolon
multiline_comment|/* uio control structure */
DECL|typedef|xfs_dir_put_args_t
)brace
id|xfs_dir_put_args_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_LEAF_ENTSIZE_BYNAME)
r_int
id|xfs_dir_leaf_entsize_byname
c_func
(paren
r_int
id|len
)paren
suffix:semicolon
DECL|macro|XFS_DIR_LEAF_ENTSIZE_BYNAME
mdefine_line|#define XFS_DIR_LEAF_ENTSIZE_BYNAME(len)&t;xfs_dir_leaf_entsize_byname(len)
macro_line|#else
DECL|macro|XFS_DIR_LEAF_ENTSIZE_BYNAME
mdefine_line|#define XFS_DIR_LEAF_ENTSIZE_BYNAME(len)&t;/* space a name will use */ &bslash;&n;&t;((uint)sizeof(xfs_dir_leaf_name_t)-1 + len)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_LEAF_ENTSIZE_BYENTRY)
r_int
id|xfs_dir_leaf_entsize_byentry
c_func
(paren
id|xfs_dir_leaf_entry_t
op_star
id|entry
)paren
suffix:semicolon
DECL|macro|XFS_DIR_LEAF_ENTSIZE_BYENTRY
mdefine_line|#define XFS_DIR_LEAF_ENTSIZE_BYENTRY(entry)&t;&bslash;&n;&t;xfs_dir_leaf_entsize_byentry(entry)
macro_line|#else
DECL|macro|XFS_DIR_LEAF_ENTSIZE_BYENTRY
mdefine_line|#define XFS_DIR_LEAF_ENTSIZE_BYENTRY(entry)&t;/* space an entry will use */ &bslash;&n;&t;((uint)sizeof(xfs_dir_leaf_name_t)-1 + (entry)-&gt;namelen)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR_LEAF_NAMESTRUCT)
id|xfs_dir_leaf_name_t
op_star
id|xfs_dir_leaf_namestruct
c_func
(paren
id|xfs_dir_leafblock_t
op_star
id|leafp
comma
r_int
id|offset
)paren
suffix:semicolon
DECL|macro|XFS_DIR_LEAF_NAMESTRUCT
mdefine_line|#define XFS_DIR_LEAF_NAMESTRUCT(leafp,offset)&t;&bslash;&n;&t;xfs_dir_leaf_namestruct(leafp,offset)
macro_line|#else
DECL|macro|XFS_DIR_LEAF_NAMESTRUCT
mdefine_line|#define XFS_DIR_LEAF_NAMESTRUCT(leafp,offset)&t;/* point to name struct */ &bslash;&n;&t;((xfs_dir_leaf_name_t *)&amp;((char *)(leafp))[offset])
macro_line|#endif
multiline_comment|/*========================================================================&n; * Function prototypes for the kernel.&n; *========================================================================*/
multiline_comment|/*&n; * Internal routines when dirsize &lt; XFS_LITINO(mp).&n; */
r_int
id|xfs_dir_shortform_create
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_ino_t
id|parent
)paren
suffix:semicolon
r_int
id|xfs_dir_shortform_addname
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_int
id|xfs_dir_shortform_lookup
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_int
id|xfs_dir_shortform_to_leaf
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_int
id|xfs_dir_shortform_removename
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_int
id|xfs_dir_shortform_getdents
c_func
(paren
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|uio
op_star
id|uio
comma
r_int
op_star
id|eofp
comma
r_struct
id|xfs_dirent
op_star
id|dbp
comma
id|xfs_dir_put_t
id|put
)paren
suffix:semicolon
r_int
id|xfs_dir_shortform_replace
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
multiline_comment|/*&n; * Internal routines when dirsize == XFS_LBSIZE(mp).&n; */
r_int
id|xfs_dir_leaf_to_node
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_to_shortform
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
multiline_comment|/*&n; * Routines used for growing the Btree.&n; */
r_int
id|xfs_dir_leaf_create
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_dablk_t
id|which_block
comma
r_struct
id|xfs_dabuf
op_star
op_star
id|bpp
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_split
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
comma
r_struct
id|xfs_da_state_blk
op_star
id|oldblk
comma
r_struct
id|xfs_da_state_blk
op_star
id|newblk
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_add
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|leaf_buffer
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_int
id|insertion_index
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_addname
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_lookup_int
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|leaf_buffer
comma
r_struct
id|xfs_da_args
op_star
id|args
comma
r_int
op_star
id|index_found_at
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_remove
c_func
(paren
r_struct
id|xfs_trans
op_star
id|trans
comma
r_struct
id|xfs_dabuf
op_star
id|leaf_buffer
comma
r_int
id|index_to_remove
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_getdents_int
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_struct
id|xfs_inode
op_star
id|dp
comma
id|xfs_dablk_t
id|bno
comma
r_struct
id|uio
op_star
id|uio
comma
r_int
op_star
id|eobp
comma
r_struct
id|xfs_dirent
op_star
id|dbp
comma
id|xfs_dir_put_t
id|put
comma
id|xfs_daddr_t
id|nextda
)paren
suffix:semicolon
multiline_comment|/*&n; * Routines used for shrinking the Btree.&n; */
r_int
id|xfs_dir_leaf_toosmall
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
comma
r_int
op_star
id|retval
)paren
suffix:semicolon
r_void
id|xfs_dir_leaf_unbalance
c_func
(paren
r_struct
id|xfs_da_state
op_star
id|state
comma
r_struct
id|xfs_da_state_blk
op_star
id|drop_blk
comma
r_struct
id|xfs_da_state_blk
op_star
id|save_blk
)paren
suffix:semicolon
multiline_comment|/*&n; * Utility routines.&n; */
id|uint
id|xfs_dir_leaf_lasthash
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_int
op_star
id|count
)paren
suffix:semicolon
r_int
id|xfs_dir_leaf_order
c_func
(paren
r_struct
id|xfs_dabuf
op_star
id|leaf1_bp
comma
r_struct
id|xfs_dabuf
op_star
id|leaf2_bp
)paren
suffix:semicolon
r_int
id|xfs_dir_put_dirent64_direct
c_func
(paren
id|xfs_dir_put_args_t
op_star
id|pa
)paren
suffix:semicolon
r_int
id|xfs_dir_put_dirent64_uio
c_func
(paren
id|xfs_dir_put_args_t
op_star
id|pa
)paren
suffix:semicolon
r_int
id|xfs_dir_ino_validate
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
id|xfs_ino_t
id|ino
)paren
suffix:semicolon
multiline_comment|/*&n; * Global data.&n; */
r_extern
id|xfs_dahash_t
id|xfs_dir_hash_dot
comma
id|xfs_dir_hash_dotdot
suffix:semicolon
macro_line|#endif /* __XFS_DIR_LEAF_H__ */
eof
