multiline_comment|/*&n; * inode.h - Defines for inode structures NTFS Linux kernel driver. Part of&n; *&t;     the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; * Copyright (C) 2002 Richard Russon.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_INODE_H
DECL|macro|_LINUX_NTFS_INODE_H
mdefine_line|#define _LINUX_NTFS_INODE_H
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &quot;volume.h&quot;
DECL|typedef|ntfs_inode
r_typedef
r_struct
id|_ntfs_inode
id|ntfs_inode
suffix:semicolon
multiline_comment|/*&n; * The NTFS in-memory inode structure. It is just used as an extension to the&n; * fields already provided in the VFS inode.&n; */
DECL|struct|_ntfs_inode
r_struct
id|_ntfs_inode
(brace
DECL|member|initialized_size
id|s64
id|initialized_size
suffix:semicolon
multiline_comment|/* Copy from $DATA/$INDEX_ALLOCATION. */
DECL|member|allocated_size
id|s64
id|allocated_size
suffix:semicolon
multiline_comment|/* Copy from $DATA/$INDEX_ALLOCATION. */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* NTFS specific flags describing this inode.&n;&t;&t;&t;&t;   See fs/ntfs/ntfs.h:ntfs_inode_state_bits. */
DECL|member|mft_no
id|u64
id|mft_no
suffix:semicolon
multiline_comment|/* Mft record number (inode number). */
DECL|member|seq_no
id|u16
id|seq_no
suffix:semicolon
multiline_comment|/* Sequence number of the mft record. */
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
multiline_comment|/* Inode reference count for book keeping. */
DECL|member|vol
id|ntfs_volume
op_star
id|vol
suffix:semicolon
multiline_comment|/* Pointer to the ntfs volume of this inode. */
DECL|member|run_list
id|run_list
id|run_list
suffix:semicolon
multiline_comment|/* If state has the NI_NonResident bit set,&n;&t;&t;&t;&t;   the run list of the unnamed data attribute&n;&t;&t;&t;&t;   (if a file) or of the index allocation&n;&t;&t;&t;&t;   attribute (directory). If run_list.rl is&n;&t;&t;&t;&t;   NULL, the run list has not been read in or&n;&t;&t;&t;&t;   has been unmapped. If NI_NonResident is&n;&t;&t;&t;&t;   clear, the unnamed data attribute is&n;&t;&t;&t;&t;   resident (file) or there is no $I30 index&n;&t;&t;&t;&t;   allocation attribute (directory). In that&n;&t;&t;&t;&t;   case run_list.rl is always NULL.*/
DECL|member|mrec_lock
r_struct
id|rw_semaphore
id|mrec_lock
suffix:semicolon
multiline_comment|/* Lock for serializing access to the&n;&t;&t;&t;&t;   mft record belonging to this inode. */
DECL|member|mft_count
id|atomic_t
id|mft_count
suffix:semicolon
multiline_comment|/* Mapping reference count for book keeping. */
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
multiline_comment|/* The page containing the mft record of the&n;&t;&t;&t;&t;   inode. This should only be touched by the&n;&t;&t;&t;&t;   (un)map_mft_record*() functions. */
DECL|member|page_ofs
r_int
id|page_ofs
suffix:semicolon
multiline_comment|/* Offset into the page at which the mft record&n;&t;&t;&t;&t;   begins. This should only be touched by the&n;&t;&t;&t;&t;   (un)map_mft_record*() functions. */
multiline_comment|/*&n;&t; * Attribute list support (only for use by the attribute lookup&n;&t; * functions). Setup during read_inode for all inodes with attribute&n;&t; * lists. Only valid if NI_AttrList is set in state, and attr_list_rl is&n;&t; * further only valid if NI_AttrListNonResident is set.&n;&t; */
DECL|member|attr_list_size
id|u32
id|attr_list_size
suffix:semicolon
multiline_comment|/* Length of attribute list value in bytes. */
DECL|member|attr_list
id|u8
op_star
id|attr_list
suffix:semicolon
multiline_comment|/* Attribute list value itself. */
DECL|member|attr_list_rl
id|run_list
id|attr_list_rl
suffix:semicolon
multiline_comment|/* Run list for the attribute list value. */
r_union
(brace
r_struct
(brace
multiline_comment|/* It is a directory or $MFT. */
DECL|member|index_block_size
id|u32
id|index_block_size
suffix:semicolon
multiline_comment|/* Size of an index block. */
DECL|member|index_block_size_bits
id|u8
id|index_block_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the above. */
DECL|member|index_vcn_size
id|u32
id|index_vcn_size
suffix:semicolon
multiline_comment|/* Size of a vcn in this&n;&t;&t;&t;&t;&t;&t;   directory index. */
DECL|member|index_vcn_size_bits
id|u8
id|index_vcn_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the above. */
DECL|member|bmp_size
id|s64
id|bmp_size
suffix:semicolon
multiline_comment|/* Size of the $I30 bitmap. */
DECL|member|bmp_initialized_size
id|s64
id|bmp_initialized_size
suffix:semicolon
multiline_comment|/* Copy from $I30 bitmap. */
DECL|member|bmp_allocated_size
id|s64
id|bmp_allocated_size
suffix:semicolon
multiline_comment|/* Copy from $I30 bitmap. */
DECL|member|bmp_rl
id|run_list
id|bmp_rl
suffix:semicolon
multiline_comment|/* Run list for the $I30 bitmap&n;&t;&t;&t;&t;&t;&t;   if it is non-resident. */
)brace
id|SN
c_func
(paren
id|idm
)paren
suffix:semicolon
r_struct
(brace
multiline_comment|/* It is a compressed file. */
DECL|member|compression_block_size
id|u32
id|compression_block_size
suffix:semicolon
multiline_comment|/* Size of a compression&n;&t;&t;&t;&t;&t;&t;           block (cb). */
DECL|member|compression_block_size_bits
id|u8
id|compression_block_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the size of&n;&t;&t;&t;&t;&t;&t;&t;   a cb. */
DECL|member|compression_block_clusters
id|u8
id|compression_block_clusters
suffix:semicolon
multiline_comment|/* Number of clusters&n;&t;&t;&t;&t;&t;&t;&t;   per compression&n;&t;&t;&t;&t;&t;&t;&t;   block. */
DECL|member|compressed_size
id|s64
id|compressed_size
suffix:semicolon
multiline_comment|/* Copy from $DATA. */
)brace
id|SN
c_func
(paren
id|icf
)paren
suffix:semicolon
)brace
id|SN
c_func
(paren
id|idc
)paren
suffix:semicolon
DECL|member|extent_lock
r_struct
id|semaphore
id|extent_lock
suffix:semicolon
multiline_comment|/* Lock for accessing/modifying the&n;&t;&t;&t;&t;&t;   below . */
DECL|member|nr_extents
id|s32
id|nr_extents
suffix:semicolon
multiline_comment|/* For a base mft record, the number of attached extent&n;&t;&t;&t;   inodes (0 if none), for extent records this is -1. */
r_union
(brace
multiline_comment|/* This union is only used if nr_extents != 0. */
DECL|member|extent_ntfs_inos
id|ntfs_inode
op_star
op_star
id|extent_ntfs_inos
suffix:semicolon
multiline_comment|/* For nr_extents &gt; 0, array of&n;&t;&t;&t;&t;&t;&t;   the ntfs inodes of the extent&n;&t;&t;&t;&t;&t;&t;   mft records belonging to&n;&t;&t;&t;&t;&t;&t;   this base inode which have&n;&t;&t;&t;&t;&t;&t;   been loaded. */
DECL|member|base_ntfs_ino
id|ntfs_inode
op_star
id|base_ntfs_ino
suffix:semicolon
multiline_comment|/* For nr_extents == -1, the&n;&t;&t;&t;&t;&t;&t;   ntfs inode of the base mft&n;&t;&t;&t;&t;&t;&t;   record. */
)brace
id|SN
c_func
(paren
id|ine
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|_IDM
mdefine_line|#define _IDM(X)  SC(idc.idm,X)
DECL|macro|_ICF
mdefine_line|#define _ICF(X)  SC(idc.icf,X)
DECL|macro|_INE
mdefine_line|#define _INE(X)  SC(ine,X)
r_typedef
r_struct
(brace
DECL|member|ntfs_inode
id|ntfs_inode
id|ntfs_inode
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
multiline_comment|/* The vfs inode structure. */
DECL|typedef|big_ntfs_inode
)brace
id|big_ntfs_inode
suffix:semicolon
multiline_comment|/**&n; * NTFS_I - return the ntfs inode given a vfs inode&n; * @inode:&t;VFS inode&n; *&n; * NTFS_I() returns the ntfs inode associated with the VFS @inode.&n; */
DECL|function|NTFS_I
r_static
r_inline
id|ntfs_inode
op_star
id|NTFS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|ntfs_inode
op_star
)paren
id|list_entry
c_func
(paren
id|inode
comma
id|big_ntfs_inode
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|VFS_I
r_static
r_inline
r_struct
id|inode
op_star
id|VFS_I
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
r_return
op_amp
(paren
(paren
id|big_ntfs_inode
op_star
)paren
id|ni
)paren
op_member_access_from_pointer
id|vfs_inode
suffix:semicolon
)brace
r_extern
r_struct
id|inode
op_star
id|ntfs_alloc_big_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_destroy_big_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_clear_big_inode
c_func
(paren
r_struct
id|inode
op_star
id|vi
)paren
suffix:semicolon
r_extern
id|ntfs_inode
op_star
id|ntfs_new_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_clear_inode
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|vi
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_read_inode_mount
c_func
(paren
r_struct
id|inode
op_star
id|vi
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_dirty_inode
c_func
(paren
r_struct
id|inode
op_star
id|vi
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_show_options
c_func
(paren
r_struct
id|seq_file
op_star
id|sf
comma
r_struct
id|vfsmount
op_star
id|mnt
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_FS_INODE_H */
eof
