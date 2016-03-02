multiline_comment|/*&n; * inode.h - Defines for inode structures NTFS Linux kernel driver. Part of&n; *&t;     the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; * Copyright (c) 2002 Richard Russon&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_INODE_H
DECL|macro|_LINUX_NTFS_INODE_H
mdefine_line|#define _LINUX_NTFS_INODE_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;layout.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;runlist.h&quot;
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
multiline_comment|/* Copy from the attribute record. */
DECL|member|allocated_size
id|s64
id|allocated_size
suffix:semicolon
multiline_comment|/* Copy from the attribute record. */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* NTFS specific flags describing this inode.&n;&t;&t;&t;&t;   See ntfs_inode_state_bits below. */
DECL|member|mft_no
r_int
r_int
id|mft_no
suffix:semicolon
multiline_comment|/* Number of the mft record / inode. */
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
multiline_comment|/*&n;&t; * If NInoAttr() is true, the below fields describe the attribute which&n;&t; * this fake inode belongs to. The actual inode of this attribute is&n;&t; * pointed to by base_ntfs_ino and nr_extents is always set to -1 (see&n;&t; * below). For real inodes, we also set the type (AT_DATA for files and&n;&t; * AT_INDEX_ALLOCATION for directories), with the name = NULL and&n;&t; * name_len = 0 for files and name = I30 (global constant) and&n;&t; * name_len = 4 for directories.&n;&t; */
DECL|member|type
id|ATTR_TYPE
id|type
suffix:semicolon
multiline_comment|/* Attribute type of this fake inode. */
DECL|member|name
id|ntfschar
op_star
id|name
suffix:semicolon
multiline_comment|/* Attribute name of this fake inode. */
DECL|member|name_len
id|u32
id|name_len
suffix:semicolon
multiline_comment|/* Attribute name length of this fake inode. */
DECL|member|runlist
id|runlist
id|runlist
suffix:semicolon
multiline_comment|/* If state has the NI_NonResident bit set,&n;&t;&t;&t;&t;   the runlist of the unnamed data attribute&n;&t;&t;&t;&t;   (if a file) or of the index allocation&n;&t;&t;&t;&t;   attribute (directory) or of the attribute&n;&t;&t;&t;&t;   described by the fake inode (if NInoAttr()).&n;&t;&t;&t;&t;   If runlist.rl is NULL, the runlist has not&n;&t;&t;&t;&t;   been read in yet or has been unmapped. If&n;&t;&t;&t;&t;   NI_NonResident is clear, the attribute is&n;&t;&t;&t;&t;   resident (file and fake inode) or there is&n;&t;&t;&t;&t;   no $I30 index allocation attribute&n;&t;&t;&t;&t;   (small directory). In the latter case&n;&t;&t;&t;&t;   runlist.rl is always NULL.*/
multiline_comment|/*&n;&t; * The following fields are only valid for real inodes and extent&n;&t; * inodes.&n;&t; */
DECL|member|mrec_lock
r_struct
id|semaphore
id|mrec_lock
suffix:semicolon
multiline_comment|/* Lock for serializing access to the&n;&t;&t;&t;&t;   mft record belonging to this inode. */
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
id|runlist
id|attr_list_rl
suffix:semicolon
multiline_comment|/* Run list for the attribute list value. */
r_union
(brace
r_struct
(brace
multiline_comment|/* It is a directory, $MFT, or an index inode. */
DECL|member|bmp_ino
r_struct
id|inode
op_star
id|bmp_ino
suffix:semicolon
multiline_comment|/* Attribute inode for the&n;&t;&t;&t;&t;&t;&t;   index $BITMAP. */
DECL|member|block_size
id|u32
id|block_size
suffix:semicolon
multiline_comment|/* Size of an index block. */
DECL|member|vcn_size
id|u32
id|vcn_size
suffix:semicolon
multiline_comment|/* Size of a vcn in this&n;&t;&t;&t;&t;&t;&t;   index. */
DECL|member|collation_rule
id|COLLATION_RULE
id|collation_rule
suffix:semicolon
multiline_comment|/* The collation rule&n;&t;&t;&t;&t;&t;&t;   for the index. */
DECL|member|block_size_bits
id|u8
id|block_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the above. */
DECL|member|vcn_size_bits
id|u8
id|vcn_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the above. */
DECL|member|index
)brace
id|index
suffix:semicolon
r_struct
(brace
multiline_comment|/* It is a compressed file or an attribute inode. */
DECL|member|size
id|s64
id|size
suffix:semicolon
multiline_comment|/* Copy of compressed_size from&n;&t;&t;&t;&t;&t;&t;   $DATA. */
DECL|member|block_size
id|u32
id|block_size
suffix:semicolon
multiline_comment|/* Size of a compression block&n;&t;&t;&t;&t;&t;&t;   (cb). */
DECL|member|block_size_bits
id|u8
id|block_size_bits
suffix:semicolon
multiline_comment|/* Log2 of the size of a cb. */
DECL|member|block_clusters
id|u8
id|block_clusters
suffix:semicolon
multiline_comment|/* Number of clusters per cb. */
DECL|member|compressed
)brace
id|compressed
suffix:semicolon
DECL|member|itype
)brace
id|itype
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
multiline_comment|/* For a base mft record, the number of attached extent&n;&t;&t;&t;   inodes (0 if none), for extent records and for fake&n;&t;&t;&t;   inodes describing an attribute this is -1. */
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
multiline_comment|/* For nr_extents == -1, the&n;&t;&t;&t;&t;&t;&t;   ntfs inode of the base mft&n;&t;&t;&t;&t;&t;&t;   record. For fake inodes, the&n;&t;&t;&t;&t;&t;&t;   real (base) inode to which&n;&t;&t;&t;&t;&t;&t;   the attribute belongs. */
DECL|member|ext
)brace
id|ext
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Defined bits for the state field in the ntfs_inode structure.&n; * (f) = files only, (d) = directories only, (a) = attributes/fake inodes only&n; */
r_typedef
r_enum
(brace
DECL|enumerator|NI_Dirty
id|NI_Dirty
comma
multiline_comment|/* 1: Mft record needs to be written to disk. */
DECL|enumerator|NI_AttrList
id|NI_AttrList
comma
multiline_comment|/* 1: Mft record contains an attribute list. */
DECL|enumerator|NI_AttrListNonResident
id|NI_AttrListNonResident
comma
multiline_comment|/* 1: Attribute list is non-resident. Implies&n;&t;&t;&t;&t;      NI_AttrList is set. */
DECL|enumerator|NI_Attr
id|NI_Attr
comma
multiline_comment|/* 1: Fake inode for attribute i/o.&n;&t;&t;&t;&t;   0: Real inode or extent inode. */
DECL|enumerator|NI_MstProtected
id|NI_MstProtected
comma
multiline_comment|/* 1: Attribute is protected by MST fixups.&n;&t;&t;&t;&t;   0: Attribute is not protected by fixups. */
DECL|enumerator|NI_NonResident
id|NI_NonResident
comma
multiline_comment|/* 1: Unnamed data attr is non-resident (f).&n;&t;&t;&t;&t;   1: Attribute is non-resident (a). */
DECL|enumerator|NI_IndexAllocPresent
id|NI_IndexAllocPresent
op_assign
id|NI_NonResident
comma
multiline_comment|/* 1: $I30 index alloc attr is&n;&t;&t;&t;&t;&t;&t;   present (d). */
DECL|enumerator|NI_Compressed
id|NI_Compressed
comma
multiline_comment|/* 1: Unnamed data attr is compressed (f).&n;&t;&t;&t;&t;   1: Create compressed files by default (d).&n;&t;&t;&t;&t;   1: Attribute is compressed (a). */
DECL|enumerator|NI_Encrypted
id|NI_Encrypted
comma
multiline_comment|/* 1: Unnamed data attr is encrypted (f).&n;&t;&t;&t;&t;   1: Create encrypted files by default (d).&n;&t;&t;&t;&t;   1: Attribute is encrypted (a). */
DECL|enumerator|NI_Sparse
id|NI_Sparse
comma
multiline_comment|/* 1: Unnamed data attr is sparse (f).&n;&t;&t;&t;&t;   1: Create sparse files by default (d).&n;&t;&t;&t;&t;   1: Attribute is sparse (a). */
DECL|typedef|ntfs_inode_state_bits
)brace
id|ntfs_inode_state_bits
suffix:semicolon
multiline_comment|/*&n; * NOTE: We should be adding dirty mft records to a list somewhere and they&n; * should be independent of the (ntfs/vfs) inode structure so that an inode can&n; * be removed but the record can be left dirty for syncing later.&n; */
multiline_comment|/*&n; * Macro tricks to expand the NInoFoo(), NInoSetFoo(), and NInoClearFoo()&n; * functions.&n; */
DECL|macro|NINO_FNS
mdefine_line|#define NINO_FNS(flag)&t;&t;&t;&t;&t;&bslash;&n;static inline int NIno##flag(ntfs_inode *ni)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return test_bit(NI_##flag, &amp;(ni)-&gt;state);&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void NInoSet##flag(ntfs_inode *ni)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_bit(NI_##flag, &amp;(ni)-&gt;state);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void NInoClear##flag(ntfs_inode *ni)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clear_bit(NI_##flag, &amp;(ni)-&gt;state);&t;&t;&bslash;&n;}
multiline_comment|/*&n; * As above for NInoTestSetFoo() and NInoTestClearFoo().&n; */
DECL|macro|TAS_NINO_FNS
mdefine_line|#define TAS_NINO_FNS(flag)&t;&t;&t;&t;&t;&bslash;&n;static inline int NInoTestSet##flag(ntfs_inode *ni)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return test_and_set_bit(NI_##flag, &amp;(ni)-&gt;state);&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline int NInoTestClear##flag(ntfs_inode *ni)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return test_and_clear_bit(NI_##flag, &amp;(ni)-&gt;state);&t;&bslash;&n;}
multiline_comment|/* Emit the ntfs inode bitops functions. */
id|NINO_FNS
c_func
(paren
id|Dirty
)paren
id|TAS_NINO_FNS
c_func
(paren
id|Dirty
)paren
id|NINO_FNS
c_func
(paren
id|AttrList
)paren
id|NINO_FNS
c_func
(paren
id|AttrListNonResident
)paren
id|NINO_FNS
c_func
(paren
id|Attr
)paren
id|NINO_FNS
c_func
(paren
id|MstProtected
)paren
id|NINO_FNS
c_func
(paren
id|NonResident
)paren
id|NINO_FNS
c_func
(paren
id|IndexAllocPresent
)paren
id|NINO_FNS
c_func
(paren
id|Compressed
)paren
id|NINO_FNS
c_func
(paren
id|Encrypted
)paren
id|NINO_FNS
c_func
(paren
id|Sparse
)paren
multiline_comment|/*&n; * The full structure containing a ntfs_inode and a vfs struct inode. Used for&n; * all real and fake inodes but not for extent inodes which lack the vfs struct&n; * inode.&n; */
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
multiline_comment|/**&n; * ntfs_attr - ntfs in memory attribute structure&n; * @mft_no:&t;mft record number of the base mft record of this attribute&n; * @name:&t;Unicode name of the attribute (NULL if unnamed)&n; * @name_len:&t;length of @name in Unicode characters (0 if unnamed)&n; * @type:&t;attribute type (see layout.h)&n; *&n; * This structure exists only to provide a small structure for the&n; * ntfs_{attr_}iget()/ntfs_test_inode()/ntfs_init_locked_inode() mechanism.&n; *&n; * NOTE: Elements are ordered by size to make the structure as compact as&n; * possible on all architectures.&n; */
r_typedef
r_struct
(brace
DECL|member|mft_no
r_int
r_int
id|mft_no
suffix:semicolon
DECL|member|name
id|ntfschar
op_star
id|name
suffix:semicolon
DECL|member|name_len
id|u32
id|name_len
suffix:semicolon
DECL|member|type
id|ATTR_TYPE
id|type
suffix:semicolon
DECL|typedef|ntfs_attr
)brace
id|ntfs_attr
suffix:semicolon
DECL|typedef|test_t
r_typedef
r_int
(paren
op_star
id|test_t
)paren
(paren
r_struct
id|inode
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_test_inode
c_func
(paren
r_struct
id|inode
op_star
id|vi
comma
id|ntfs_attr
op_star
id|na
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|ntfs_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|mft_no
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|ntfs_attr_iget
c_func
(paren
r_struct
id|inode
op_star
id|base_vi
comma
id|ATTR_TYPE
id|type
comma
id|ntfschar
op_star
id|name
comma
id|u32
id|name_len
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|ntfs_index_iget
c_func
(paren
r_struct
id|inode
op_star
id|base_vi
comma
id|ntfschar
op_star
id|name
comma
id|u32
id|name_len
)paren
suffix:semicolon
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
id|ntfs_new_extent_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|mft_no
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_clear_extent_inode
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
suffix:semicolon
r_extern
r_int
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
id|ntfs_put_inode
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
macro_line|#ifdef NTFS_RW
r_extern
r_void
id|ntfs_truncate
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
id|ntfs_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|vi
comma
r_int
id|sync
)paren
suffix:semicolon
DECL|function|ntfs_commit_inode
r_static
r_inline
r_void
id|ntfs_commit_inode
c_func
(paren
r_struct
id|inode
op_star
id|vi
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_bad_inode
c_func
(paren
id|vi
)paren
)paren
id|ntfs_write_inode
c_func
(paren
id|vi
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* _LINUX_NTFS_INODE_H */
eof
