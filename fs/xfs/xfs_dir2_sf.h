multiline_comment|/*&n; * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_DIR2_SF_H__
DECL|macro|__XFS_DIR2_SF_H__
mdefine_line|#define __XFS_DIR2_SF_H__
multiline_comment|/*&n; * Directory layout when stored internal to an inode.&n; *&n; * Small directories are packed as tightly as possible so as to&n; * fit into the literal area of the inode.&n; */
r_struct
id|dirent
suffix:semicolon
r_struct
id|uio
suffix:semicolon
r_struct
id|xfs_dabuf
suffix:semicolon
r_struct
id|xfs_da_args
suffix:semicolon
r_struct
id|xfs_dir2_block
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
multiline_comment|/*&n; * Maximum size of a shortform directory.&n; */
DECL|macro|XFS_DIR2_SF_MAX_SIZE
mdefine_line|#define XFS_DIR2_SF_MAX_SIZE&t;&bslash;&n;&t;(XFS_DINODE_MAX_SIZE - (uint)sizeof(xfs_dinode_core_t) - &bslash;&n;&t; (uint)sizeof(xfs_agino_t))
multiline_comment|/*&n; * Inode number stored as 8 8-bit values.&n; */
DECL|member|i
DECL|typedef|xfs_dir2_ino8_t
r_typedef
r_struct
(brace
id|__uint8_t
id|i
(braket
l_int|8
)braket
suffix:semicolon
)brace
id|xfs_dir2_ino8_t
suffix:semicolon
DECL|macro|XFS_DIR2_SF_GET_INO8_ARCH
mdefine_line|#define XFS_DIR2_SF_GET_INO8_ARCH(di,arch)&t;&bslash;&n;&t;(xfs_ino_t)(DIRINO_GET_ARCH(&amp;di,arch))
DECL|macro|XFS_DIR2_SF_GET_INO8
mdefine_line|#define XFS_DIR2_SF_GET_INO8(di)&t;&t;&bslash;&n;&t;XFS_DIR2_SF_GET_INO8_ARCH(di,ARCH_NOCONVERT)
multiline_comment|/*&n; * Inode number stored as 4 8-bit values.&n; * Works a lot of the time, when all the inode numbers in a directory&n; * fit in 32 bits.&n; */
DECL|member|i
DECL|typedef|xfs_dir2_ino4_t
r_typedef
r_struct
(brace
id|__uint8_t
id|i
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|xfs_dir2_ino4_t
suffix:semicolon
DECL|macro|XFS_DIR2_SF_GET_INO4_ARCH
mdefine_line|#define XFS_DIR2_SF_GET_INO4_ARCH(di,arch)&t;&bslash;&n;&t;(xfs_ino_t)(DIRINO4_GET_ARCH(&amp;di,arch))
DECL|macro|XFS_DIR2_SF_GET_INO4
mdefine_line|#define XFS_DIR2_SF_GET_INO4(di)&t;&t;&bslash;&n;&t;XFS_DIR2_SF_GET_INO4_ARCH(di,ARCH_NOCONVERT)
r_typedef
r_union
(brace
DECL|member|i8
id|xfs_dir2_ino8_t
id|i8
suffix:semicolon
DECL|member|i4
id|xfs_dir2_ino4_t
id|i4
suffix:semicolon
DECL|typedef|xfs_dir2_inou_t
)brace
id|xfs_dir2_inou_t
suffix:semicolon
DECL|macro|XFS_DIR2_MAX_SHORT_INUM
mdefine_line|#define XFS_DIR2_MAX_SHORT_INUM ((xfs_ino_t)0xffffffffULL)
multiline_comment|/*&n; * Normalized offset (in a data block) of the entry, really xfs_dir2_data_off_t.&n; * Only need 16 bits, this is the byte offset into the single block form.&n; */
DECL|member|i
DECL|typedef|xfs_dir2_sf_off_t
r_typedef
r_struct
(brace
id|__uint8_t
id|i
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|xfs_dir2_sf_off_t
suffix:semicolon
multiline_comment|/*&n; * The parent directory has a dedicated field, and the self-pointer must&n; * be calculated on the fly.&n; *&n; * Entries are packed toward the top as tightly as possible.  The header&n; * and the elements must be bcopy()&squot;d out into a work area to get correct&n; * alignment for the inode number fields.&n; */
DECL|struct|xfs_dir2_sf_hdr
r_typedef
r_struct
id|xfs_dir2_sf_hdr
(brace
DECL|member|count
id|__uint8_t
id|count
suffix:semicolon
multiline_comment|/* count of entries */
DECL|member|i8count
id|__uint8_t
id|i8count
suffix:semicolon
multiline_comment|/* count of 8-byte inode #s */
DECL|member|parent
id|xfs_dir2_inou_t
id|parent
suffix:semicolon
multiline_comment|/* parent dir inode number */
DECL|typedef|xfs_dir2_sf_hdr_t
)brace
id|xfs_dir2_sf_hdr_t
suffix:semicolon
DECL|struct|xfs_dir2_sf_entry
r_typedef
r_struct
id|xfs_dir2_sf_entry
(brace
DECL|member|namelen
id|__uint8_t
id|namelen
suffix:semicolon
multiline_comment|/* actual name length */
DECL|member|offset
id|xfs_dir2_sf_off_t
id|offset
suffix:semicolon
multiline_comment|/* saved offset */
DECL|member|name
id|__uint8_t
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name, variable size */
DECL|member|inumber
id|xfs_dir2_inou_t
id|inumber
suffix:semicolon
multiline_comment|/* inode number, var. offset */
DECL|typedef|xfs_dir2_sf_entry_t
)brace
id|xfs_dir2_sf_entry_t
suffix:semicolon
DECL|struct|xfs_dir2_sf
r_typedef
r_struct
id|xfs_dir2_sf
(brace
DECL|member|hdr
id|xfs_dir2_sf_hdr_t
id|hdr
suffix:semicolon
multiline_comment|/* shortform header */
DECL|member|list
id|xfs_dir2_sf_entry_t
id|list
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* shortform entries */
DECL|typedef|xfs_dir2_sf_t
)brace
id|xfs_dir2_sf_t
suffix:semicolon
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_HDR_SIZE)
r_int
id|xfs_dir2_sf_hdr_size
c_func
(paren
r_int
id|i8count
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_HDR_SIZE
mdefine_line|#define XFS_DIR2_SF_HDR_SIZE(i8count)&t;xfs_dir2_sf_hdr_size(i8count)
macro_line|#else
DECL|macro|XFS_DIR2_SF_HDR_SIZE
mdefine_line|#define XFS_DIR2_SF_HDR_SIZE(i8count)&t;&bslash;&n;&t;((uint)sizeof(xfs_dir2_sf_hdr_t) - &bslash;&n;&t; ((i8count) == 0) * &bslash;&n;&t; ((uint)sizeof(xfs_dir2_ino8_t) - (uint)sizeof(xfs_dir2_ino4_t)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_INUMBERP)
id|xfs_dir2_inou_t
op_star
id|xfs_dir2_sf_inumberp
c_func
(paren
id|xfs_dir2_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_INUMBERP
mdefine_line|#define XFS_DIR2_SF_INUMBERP(sfep)&t;xfs_dir2_sf_inumberp(sfep)
macro_line|#else
DECL|macro|XFS_DIR2_SF_INUMBERP
mdefine_line|#define XFS_DIR2_SF_INUMBERP(sfep)&t;&bslash;&n;&t;((xfs_dir2_inou_t *)&amp;(sfep)-&gt;name[(sfep)-&gt;namelen])
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_GET_INUMBER)
id|xfs_intino_t
id|xfs_dir2_sf_get_inumber_arch
c_func
(paren
id|xfs_dir2_sf_t
op_star
id|sfp
comma
id|xfs_dir2_inou_t
op_star
id|from
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_GET_INUMBER_ARCH
mdefine_line|#define XFS_DIR2_SF_GET_INUMBER_ARCH(sfp, from, arch)&t;&bslash;&n;&t;xfs_dir2_sf_get_inumber_arch(sfp, from, arch)
macro_line|#else
DECL|macro|XFS_DIR2_SF_GET_INUMBER_ARCH
mdefine_line|#define XFS_DIR2_SF_GET_INUMBER_ARCH(sfp, from, arch)&t;&bslash;&n;&t;((sfp)-&gt;hdr.i8count == 0 ? &bslash;&n;&t;&t;(xfs_intino_t)XFS_DIR2_SF_GET_INO4_ARCH(*(from), arch) : &bslash;&n;&t;&t;(xfs_intino_t)XFS_DIR2_SF_GET_INO8_ARCH(*(from), arch))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_PUT_INUMBER)
r_void
id|xfs_dir2_sf_put_inumber_arch
c_func
(paren
id|xfs_dir2_sf_t
op_star
id|sfp
comma
id|xfs_ino_t
op_star
id|from
comma
id|xfs_dir2_inou_t
op_star
id|to
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_PUT_INUMBER_ARCH
mdefine_line|#define XFS_DIR2_SF_PUT_INUMBER_ARCH(sfp,from,to,arch)&t;&bslash;&n;&t;xfs_dir2_sf_put_inumber_arch(sfp,from,to,arch)
macro_line|#else
DECL|macro|XFS_DIR2_SF_PUT_INUMBER_ARCH
mdefine_line|#define XFS_DIR2_SF_PUT_INUMBER_ARCH(sfp,from,to,arch)&t;&bslash;&n;&t;if ((sfp)-&gt;hdr.i8count == 0) { &bslash;&n;&t;    DIRINO4_COPY_ARCH(from,to,arch); &bslash;&n;&t;} else { &bslash;&n;&t;    DIRINO_COPY_ARCH(from,to,arch); &bslash;&n;&t;}
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_GET_OFFSET)
id|xfs_dir2_data_aoff_t
id|xfs_dir2_sf_get_offset_arch
c_func
(paren
id|xfs_dir2_sf_entry_t
op_star
id|sfep
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
id|xfs_dir2_data_aoff_t
id|xfs_dir2_sf_get_offset
c_func
(paren
id|xfs_dir2_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_GET_OFFSET_ARCH
mdefine_line|#define XFS_DIR2_SF_GET_OFFSET_ARCH(sfep,arch)&t;&bslash;&n;&t;xfs_dir2_sf_get_offset_arch(sfep,arch)
macro_line|#else
DECL|macro|XFS_DIR2_SF_GET_OFFSET_ARCH
mdefine_line|#define XFS_DIR2_SF_GET_OFFSET_ARCH(sfep,arch)&t;&bslash;&n;&t;INT_GET_UNALIGNED_16_ARCH(&amp;(sfep)-&gt;offset.i,arch)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_PUT_OFFSET)
r_void
id|xfs_dir2_sf_put_offset_arch
c_func
(paren
id|xfs_dir2_sf_entry_t
op_star
id|sfep
comma
id|xfs_dir2_data_aoff_t
id|off
comma
id|xfs_arch_t
id|arch
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_PUT_OFFSET_ARCH
mdefine_line|#define XFS_DIR2_SF_PUT_OFFSET_ARCH(sfep,off,arch) &bslash;&n;&t;xfs_dir2_sf_put_offset_arch(sfep,off,arch)
macro_line|#else
DECL|macro|XFS_DIR2_SF_PUT_OFFSET_ARCH
mdefine_line|#define XFS_DIR2_SF_PUT_OFFSET_ARCH(sfep,off,arch)&t;&bslash;&n;&t;INT_SET_UNALIGNED_16_ARCH(&amp;(sfep)-&gt;offset.i,off,arch)
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_ENTSIZE_BYNAME)
r_int
id|xfs_dir2_sf_entsize_byname
c_func
(paren
id|xfs_dir2_sf_t
op_star
id|sfp
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_ENTSIZE_BYNAME
mdefine_line|#define XFS_DIR2_SF_ENTSIZE_BYNAME(sfp,len)&t;&bslash;&n;&t;xfs_dir2_sf_entsize_byname(sfp,len)
macro_line|#else
DECL|macro|XFS_DIR2_SF_ENTSIZE_BYNAME
mdefine_line|#define XFS_DIR2_SF_ENTSIZE_BYNAME(sfp,len)&t;/* space a name uses */ &bslash;&n;&t;((uint)sizeof(xfs_dir2_sf_entry_t) - 1 + (len) - &bslash;&n;&t; ((sfp)-&gt;hdr.i8count == 0) * &bslash;&n;&t; ((uint)sizeof(xfs_dir2_ino8_t) - (uint)sizeof(xfs_dir2_ino4_t)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_ENTSIZE_BYENTRY)
r_int
id|xfs_dir2_sf_entsize_byentry
c_func
(paren
id|xfs_dir2_sf_t
op_star
id|sfp
comma
id|xfs_dir2_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_ENTSIZE_BYENTRY
mdefine_line|#define XFS_DIR2_SF_ENTSIZE_BYENTRY(sfp,sfep)&t;&bslash;&n;&t;xfs_dir2_sf_entsize_byentry(sfp,sfep)
macro_line|#else
DECL|macro|XFS_DIR2_SF_ENTSIZE_BYENTRY
mdefine_line|#define XFS_DIR2_SF_ENTSIZE_BYENTRY(sfp,sfep)&t;/* space an entry uses */ &bslash;&n;&t;((uint)sizeof(xfs_dir2_sf_entry_t) - 1 + (sfep)-&gt;namelen - &bslash;&n;&t; ((sfp)-&gt;hdr.i8count == 0) * &bslash;&n;&t; ((uint)sizeof(xfs_dir2_ino8_t) - (uint)sizeof(xfs_dir2_ino4_t)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_FIRSTENTRY)
id|xfs_dir2_sf_entry_t
op_star
id|xfs_dir2_sf_firstentry
c_func
(paren
id|xfs_dir2_sf_t
op_star
id|sfp
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_FIRSTENTRY
mdefine_line|#define XFS_DIR2_SF_FIRSTENTRY(sfp)&t;xfs_dir2_sf_firstentry(sfp)
macro_line|#else
DECL|macro|XFS_DIR2_SF_FIRSTENTRY
mdefine_line|#define XFS_DIR2_SF_FIRSTENTRY(sfp)&t;/* first entry in struct */ &bslash;&n;&t;((xfs_dir2_sf_entry_t *) &bslash;&n;&t; ((char *)(sfp) + XFS_DIR2_SF_HDR_SIZE(sfp-&gt;hdr.i8count)))
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_DIR2_SF_NEXTENTRY)
id|xfs_dir2_sf_entry_t
op_star
id|xfs_dir2_sf_nextentry
c_func
(paren
id|xfs_dir2_sf_t
op_star
id|sfp
comma
id|xfs_dir2_sf_entry_t
op_star
id|sfep
)paren
suffix:semicolon
DECL|macro|XFS_DIR2_SF_NEXTENTRY
mdefine_line|#define XFS_DIR2_SF_NEXTENTRY(sfp,sfep)&t;&t;xfs_dir2_sf_nextentry(sfp,sfep)
macro_line|#else
DECL|macro|XFS_DIR2_SF_NEXTENTRY
mdefine_line|#define XFS_DIR2_SF_NEXTENTRY(sfp,sfep)&t;&t;/* next entry in struct */ &bslash;&n;&t;((xfs_dir2_sf_entry_t *) &bslash;&n;&t;&t;((char *)(sfep) + XFS_DIR2_SF_ENTSIZE_BYENTRY(sfp,sfep)))
macro_line|#endif
multiline_comment|/*&n; * Functions.&n; */
r_extern
r_int
id|xfs_dir2_block_sfsize
c_func
(paren
r_struct
id|xfs_inode
op_star
id|dp
comma
r_struct
id|xfs_dir2_block
op_star
id|block
comma
id|xfs_dir2_sf_hdr_t
op_star
id|sfhp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_block_to_sf
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
r_struct
id|xfs_dabuf
op_star
id|bp
comma
r_int
id|size
comma
id|xfs_dir2_sf_hdr_t
op_star
id|sfhp
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_addname
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_create
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
comma
id|xfs_ino_t
id|pino
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_getdents
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
id|xfs_dir2_put_t
id|put
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_lookup
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_removename
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
r_extern
r_int
id|xfs_dir2_sf_replace
c_func
(paren
r_struct
id|xfs_da_args
op_star
id|args
)paren
suffix:semicolon
macro_line|#endif&t;/* __XFS_DIR2_SF_H__ */
eof
