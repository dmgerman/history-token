macro_line|#ifndef _SYSV_H
DECL|macro|_SYSV_H
mdefine_line|#define _SYSV_H
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|typedef|__fs16
r_typedef
id|__u16
id|__bitwise
id|__fs16
suffix:semicolon
DECL|typedef|__fs32
r_typedef
id|__u32
id|__bitwise
id|__fs32
suffix:semicolon
macro_line|#include &lt;linux/sysv_fs.h&gt;
multiline_comment|/*&n; * SystemV/V7/Coherent super-block data in memory&n; *&n; * The SystemV/V7/Coherent superblock contains dynamic data (it gets modified&n; * while the system is running). This is in contrast to the Minix and Berkeley&n; * filesystems (where the superblock is never modified). This affects the&n; * sync() operation: we must keep the superblock in a disk buffer and use this&n; * one as our &quot;working copy&quot;.&n; */
DECL|struct|sysv_sb_info
r_struct
id|sysv_sb_info
(brace
DECL|member|s_sb
r_struct
id|super_block
op_star
id|s_sb
suffix:semicolon
multiline_comment|/* VFS superblock */
DECL|member|s_type
r_int
id|s_type
suffix:semicolon
multiline_comment|/* file system type: FSTYPE_{XENIX|SYSV|COH} */
DECL|member|s_bytesex
r_char
id|s_bytesex
suffix:semicolon
multiline_comment|/* bytesex (le/be/pdp) */
DECL|member|s_truncate
r_char
id|s_truncate
suffix:semicolon
multiline_comment|/* if 1: names &gt; SYSV_NAMELEN chars are truncated */
multiline_comment|/* if 0: they are disallowed (ENAMETOOLONG) */
DECL|member|s_link_max
id|nlink_t
id|s_link_max
suffix:semicolon
multiline_comment|/* max number of hard links to a file */
DECL|member|s_inodes_per_block
r_int
r_int
id|s_inodes_per_block
suffix:semicolon
multiline_comment|/* number of inodes per block */
DECL|member|s_inodes_per_block_1
r_int
r_int
id|s_inodes_per_block_1
suffix:semicolon
multiline_comment|/* inodes_per_block - 1 */
DECL|member|s_inodes_per_block_bits
r_int
r_int
id|s_inodes_per_block_bits
suffix:semicolon
multiline_comment|/* log2(inodes_per_block) */
DECL|member|s_ind_per_block
r_int
r_int
id|s_ind_per_block
suffix:semicolon
multiline_comment|/* number of indirections per block */
DECL|member|s_ind_per_block_bits
r_int
r_int
id|s_ind_per_block_bits
suffix:semicolon
multiline_comment|/* log2(ind_per_block) */
DECL|member|s_ind_per_block_2
r_int
r_int
id|s_ind_per_block_2
suffix:semicolon
multiline_comment|/* ind_per_block ^ 2 */
DECL|member|s_toobig_block
r_int
r_int
id|s_toobig_block
suffix:semicolon
multiline_comment|/* 10 + ipb + ipb^2 + ipb^3 */
DECL|member|s_block_base
r_int
r_int
id|s_block_base
suffix:semicolon
multiline_comment|/* physical block number of block 0 */
DECL|member|s_fic_size
r_int
r_int
id|s_fic_size
suffix:semicolon
multiline_comment|/* free inode cache size, NICINOD */
DECL|member|s_flc_size
r_int
r_int
id|s_flc_size
suffix:semicolon
multiline_comment|/* free block list chunk size, NICFREE */
multiline_comment|/* The superblock is kept in one or two disk buffers: */
DECL|member|s_bh1
r_struct
id|buffer_head
op_star
id|s_bh1
suffix:semicolon
DECL|member|s_bh2
r_struct
id|buffer_head
op_star
id|s_bh2
suffix:semicolon
multiline_comment|/* These are pointers into the disk buffer, to compensate for&n;&t;   different superblock layout. */
DECL|member|s_sbd1
r_char
op_star
id|s_sbd1
suffix:semicolon
multiline_comment|/* entire superblock data, for part 1 */
DECL|member|s_sbd2
r_char
op_star
id|s_sbd2
suffix:semicolon
multiline_comment|/* entire superblock data, for part 2 */
DECL|member|s_sb_fic_count
id|__fs16
op_star
id|s_sb_fic_count
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_ninode */
DECL|member|s_sb_fic_inodes
id|sysv_ino_t
op_star
id|s_sb_fic_inodes
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_inode */
DECL|member|s_sb_total_free_inodes
id|__fs16
op_star
id|s_sb_total_free_inodes
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_tinode */
DECL|member|s_bcache_count
id|__fs16
op_star
id|s_bcache_count
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_nfree */
DECL|member|s_bcache
id|sysv_zone_t
op_star
id|s_bcache
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_free */
DECL|member|s_free_blocks
id|__fs32
op_star
id|s_free_blocks
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_tfree */
DECL|member|s_sb_time
id|__fs32
op_star
id|s_sb_time
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_time */
DECL|member|s_sb_state
id|__fs32
op_star
id|s_sb_state
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_state, only FSTYPE_SYSV */
multiline_comment|/* We keep those superblock entities that don&squot;t change here;&n;&t;   this saves us an indirection and perhaps a conversion. */
DECL|member|s_firstinodezone
id|u32
id|s_firstinodezone
suffix:semicolon
multiline_comment|/* index of first inode zone */
DECL|member|s_firstdatazone
id|u32
id|s_firstdatazone
suffix:semicolon
multiline_comment|/* same as s_sbd-&gt;s_isize */
DECL|member|s_ninodes
id|u32
id|s_ninodes
suffix:semicolon
multiline_comment|/* total number of inodes */
DECL|member|s_ndatazones
id|u32
id|s_ndatazones
suffix:semicolon
multiline_comment|/* total number of data zones */
DECL|member|s_nzones
id|u32
id|s_nzones
suffix:semicolon
multiline_comment|/* same as s_sbd-&gt;s_fsize */
DECL|member|s_namelen
id|u16
id|s_namelen
suffix:semicolon
multiline_comment|/* max length of dir entry */
DECL|member|s_forced_ro
r_int
id|s_forced_ro
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * SystemV/V7/Coherent FS inode data in memory&n; */
DECL|struct|sysv_inode_info
r_struct
id|sysv_inode_info
(brace
DECL|member|i_data
id|__fs32
id|i_data
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|i_dir_start_lookup
id|u32
id|i_dir_start_lookup
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
DECL|function|SYSV_I
r_static
r_inline
r_struct
id|sysv_inode_info
op_star
id|SYSV_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|sysv_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|SYSV_SB
r_static
r_inline
r_struct
id|sysv_sb_info
op_star
id|SYSV_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
multiline_comment|/* identify the FS in memory */
r_enum
(brace
DECL|enumerator|FSTYPE_NONE
id|FSTYPE_NONE
op_assign
l_int|0
comma
DECL|enumerator|FSTYPE_XENIX
id|FSTYPE_XENIX
comma
DECL|enumerator|FSTYPE_SYSV4
id|FSTYPE_SYSV4
comma
DECL|enumerator|FSTYPE_SYSV2
id|FSTYPE_SYSV2
comma
DECL|enumerator|FSTYPE_COH
id|FSTYPE_COH
comma
DECL|enumerator|FSTYPE_V7
id|FSTYPE_V7
comma
DECL|enumerator|FSTYPE_AFS
id|FSTYPE_AFS
comma
DECL|enumerator|FSTYPE_END
id|FSTYPE_END
comma
)brace
suffix:semicolon
DECL|macro|SYSV_MAGIC_BASE
mdefine_line|#define SYSV_MAGIC_BASE&t;&t;0x012FF7B3
DECL|macro|XENIX_SUPER_MAGIC
mdefine_line|#define XENIX_SUPER_MAGIC&t;(SYSV_MAGIC_BASE+FSTYPE_XENIX)
DECL|macro|SYSV4_SUPER_MAGIC
mdefine_line|#define SYSV4_SUPER_MAGIC&t;(SYSV_MAGIC_BASE+FSTYPE_SYSV4)
DECL|macro|SYSV2_SUPER_MAGIC
mdefine_line|#define SYSV2_SUPER_MAGIC&t;(SYSV_MAGIC_BASE+FSTYPE_SYSV2)
DECL|macro|COH_SUPER_MAGIC
mdefine_line|#define COH_SUPER_MAGIC&t;&t;(SYSV_MAGIC_BASE+FSTYPE_COH)
multiline_comment|/* Admissible values for i_nlink: 0.._LINK_MAX */
r_enum
(brace
DECL|enumerator|XENIX_LINK_MAX
id|XENIX_LINK_MAX
op_assign
l_int|126
comma
multiline_comment|/* ?? */
DECL|enumerator|SYSV_LINK_MAX
id|SYSV_LINK_MAX
op_assign
l_int|126
comma
multiline_comment|/* 127? 251? */
DECL|enumerator|V7_LINK_MAX
id|V7_LINK_MAX
op_assign
l_int|126
comma
multiline_comment|/* ?? */
DECL|enumerator|COH_LINK_MAX
id|COH_LINK_MAX
op_assign
l_int|10000
comma
)brace
suffix:semicolon
DECL|function|dirty_sb
r_static
r_inline
r_void
id|dirty_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbi-&gt;s_bh1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_bh1
op_ne
id|sbi-&gt;s_bh2
)paren
id|mark_buffer_dirty
c_func
(paren
id|sbi-&gt;s_bh2
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ialloc.c */
r_extern
r_struct
id|sysv_inode
op_star
id|sysv_raw_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|sysv_new_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
comma
id|mode_t
)paren
suffix:semicolon
r_extern
r_void
id|sysv_free_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sysv_count_free_inodes
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* balloc.c */
r_extern
id|sysv_zone_t
id|sysv_new_block
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_free_block
c_func
(paren
r_struct
id|super_block
op_star
comma
id|sysv_zone_t
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sysv_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* itree.c */
r_extern
r_void
id|sysv_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_int
id|sysv_write_inode
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
id|sysv_sync_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_sync_file
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sysv_set_inode
c_func
(paren
r_struct
id|inode
op_star
comma
id|dev_t
)paren
suffix:semicolon
r_extern
r_int
id|sysv_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|kstat
op_star
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|sysv_dir_entry
op_star
id|sysv_find_entry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_add_link
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_delete_entry
c_func
(paren
r_struct
id|sysv_dir_entry
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_make_empty
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sysv_empty_dir
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysv_set_link
c_func
(paren
r_struct
id|sysv_dir_entry
op_star
comma
r_struct
id|page
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sysv_dir_entry
op_star
id|sysv_dotdot
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
id|ino_t
id|sysv_inode_by_name
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|sysv_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|sysv_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|sysv_fast_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|sysv_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|sysv_dir_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|sysv_aops
suffix:semicolon
r_extern
r_struct
id|super_operations
id|sysv_sops
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|sysv_dentry_operations
suffix:semicolon
r_enum
(brace
DECL|enumerator|BYTESEX_LE
id|BYTESEX_LE
comma
DECL|enumerator|BYTESEX_PDP
id|BYTESEX_PDP
comma
DECL|enumerator|BYTESEX_BE
id|BYTESEX_BE
comma
)brace
suffix:semicolon
DECL|function|PDP_swab
r_static
r_inline
id|u32
id|PDP_swab
c_func
(paren
id|u32
id|x
)paren
(brace
macro_line|#ifdef __LITTLE_ENDIAN
r_return
(paren
(paren
id|x
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef __BIG_ENDIAN
r_return
(paren
(paren
id|x
op_amp
l_int|0xff00ff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|x
op_amp
l_int|0xff00ff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
macro_line|#else
macro_line|#error BYTESEX
macro_line|#endif
macro_line|#endif
)brace
DECL|function|fs32_to_cpu
r_static
r_inline
id|__u32
id|fs32_to_cpu
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|__fs32
id|n
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_eq
id|BYTESEX_PDP
)paren
r_return
id|PDP_swab
c_func
(paren
(paren
id|__force
id|__u32
)paren
id|n
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_eq
id|BYTESEX_LE
)paren
r_return
id|le32_to_cpu
c_func
(paren
(paren
id|__force
id|__le32
)paren
id|n
)paren
suffix:semicolon
r_else
r_return
id|be32_to_cpu
c_func
(paren
(paren
id|__force
id|__be32
)paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_fs32
r_static
r_inline
id|__fs32
id|cpu_to_fs32
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|__u32
id|n
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_eq
id|BYTESEX_PDP
)paren
r_return
(paren
id|__force
id|__fs32
)paren
id|PDP_swab
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_eq
id|BYTESEX_LE
)paren
r_return
(paren
id|__force
id|__fs32
)paren
id|cpu_to_le32
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_return
(paren
id|__force
id|__fs32
)paren
id|cpu_to_be32
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|fs32_add
r_static
r_inline
id|__fs32
id|fs32_add
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|__fs32
op_star
id|n
comma
r_int
id|d
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_eq
id|BYTESEX_PDP
)paren
op_star
(paren
id|__u32
op_star
)paren
id|n
op_assign
id|PDP_swab
c_func
(paren
id|PDP_swab
c_func
(paren
op_star
(paren
id|__u32
op_star
)paren
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_eq
id|BYTESEX_LE
)paren
op_star
(paren
id|__le32
op_star
)paren
id|n
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpu
c_func
(paren
op_star
(paren
id|__le32
op_star
)paren
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_else
op_star
(paren
id|__be32
op_star
)paren
id|n
op_assign
id|cpu_to_be32
c_func
(paren
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|__be32
op_star
)paren
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_return
op_star
id|n
suffix:semicolon
)brace
DECL|function|fs16_to_cpu
r_static
r_inline
id|__u16
id|fs16_to_cpu
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|__fs16
id|n
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_ne
id|BYTESEX_BE
)paren
r_return
id|le16_to_cpu
c_func
(paren
(paren
id|__force
id|__le16
)paren
id|n
)paren
suffix:semicolon
r_else
r_return
id|be16_to_cpu
c_func
(paren
(paren
id|__force
id|__be16
)paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_fs16
r_static
r_inline
id|__fs16
id|cpu_to_fs16
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|__u16
id|n
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_ne
id|BYTESEX_BE
)paren
r_return
(paren
id|__force
id|__fs16
)paren
id|cpu_to_le16
c_func
(paren
id|n
)paren
suffix:semicolon
r_else
r_return
(paren
id|__force
id|__fs16
)paren
id|cpu_to_be16
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
DECL|function|fs16_add
r_static
r_inline
id|__fs16
id|fs16_add
c_func
(paren
r_struct
id|sysv_sb_info
op_star
id|sbi
comma
id|__fs16
op_star
id|n
comma
r_int
id|d
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;s_bytesex
op_ne
id|BYTESEX_BE
)paren
op_star
(paren
id|__le16
op_star
)paren
id|n
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
op_star
(paren
id|__le16
op_star
)paren
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_else
op_star
(paren
id|__be16
op_star
)paren
id|n
op_assign
id|cpu_to_be16
c_func
(paren
id|be16_to_cpu
c_func
(paren
op_star
(paren
id|__be16
op_star
)paren
id|n
)paren
op_plus
id|d
)paren
suffix:semicolon
r_return
op_star
id|n
suffix:semicolon
)brace
macro_line|#endif /* _SYSV_H */
eof
