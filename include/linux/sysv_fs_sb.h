macro_line|#ifndef _SYSV_FS_SB
DECL|macro|_SYSV_FS_SB
mdefine_line|#define _SYSV_FS_SB
multiline_comment|/*&n; * SystemV/V7/Coherent super-block data in memory&n; * The SystemV/V7/Coherent superblock contains dynamic data (it gets modified&n; * while the system is running). This is in contrast to the Minix and Berkeley&n; * filesystems (where the superblock is never modified). This affects the&n; * sync() operation: we must keep the superblock in a disk buffer and use this&n; * one as our &quot;working copy&quot;.&n; */
DECL|struct|sysv_sb_info
r_struct
id|sysv_sb_info
(brace
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
DECL|member|s_kludge_symlinks
r_char
id|s_kludge_symlinks
suffix:semicolon
multiline_comment|/* flag whether symlinks have a kludgey mode */
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
id|u16
op_star
id|s_sb_fic_count
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_ninode */
DECL|member|s_sb_fic_inodes
id|u16
op_star
id|s_sb_fic_inodes
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_inode */
DECL|member|s_sb_total_free_inodes
id|u16
op_star
id|s_sb_total_free_inodes
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_tinode */
DECL|member|s_bcache_count
id|u16
op_star
id|s_bcache_count
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_nfree */
DECL|member|s_bcache
id|u32
op_star
id|s_bcache
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_free */
DECL|member|s_free_blocks
id|u32
op_star
id|s_free_blocks
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_tfree */
DECL|member|s_sb_time
id|u32
op_star
id|s_sb_time
suffix:semicolon
multiline_comment|/* pointer to s_sbd-&gt;s_time */
DECL|member|s_sb_state
id|u32
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
)brace
suffix:semicolon
multiline_comment|/* The field s_toobig_block is currently unused. */
multiline_comment|/* sv_ == u.sysv_sb.s_ */
DECL|macro|sv_type
mdefine_line|#define sv_type&t;&t;&t;&t;&t;u.sysv_sb.s_type
DECL|macro|sv_bytesex
mdefine_line|#define sv_bytesex&t;&t;&t;&t;u.sysv_sb.s_bytesex
DECL|macro|sv_kludge_symlinks
mdefine_line|#define sv_kludge_symlinks&t;&t;&t;u.sysv_sb.s_kludge_symlinks
DECL|macro|sv_truncate
mdefine_line|#define sv_truncate&t;&t;&t;&t;u.sysv_sb.s_truncate
DECL|macro|sv_link_max
mdefine_line|#define sv_link_max&t;&t;&t;&t;u.sysv_sb.s_link_max
DECL|macro|sv_inodes_per_block
mdefine_line|#define sv_inodes_per_block&t;&t;&t;u.sysv_sb.s_inodes_per_block
DECL|macro|sv_inodes_per_block_1
mdefine_line|#define sv_inodes_per_block_1&t;&t;&t;u.sysv_sb.s_inodes_per_block_1
DECL|macro|sv_inodes_per_block_bits
mdefine_line|#define sv_inodes_per_block_bits&t;&t;u.sysv_sb.s_inodes_per_block_bits
DECL|macro|sv_ind_per_block
mdefine_line|#define sv_ind_per_block&t;&t;&t;u.sysv_sb.s_ind_per_block
DECL|macro|sv_ind_per_block_bits
mdefine_line|#define sv_ind_per_block_bits&t;&t;&t;u.sysv_sb.s_ind_per_block_bits
DECL|macro|sv_ind_per_block_2
mdefine_line|#define sv_ind_per_block_2&t;&t;&t;u.sysv_sb.s_ind_per_block_2
DECL|macro|sv_toobig_block
mdefine_line|#define sv_toobig_block&t;&t;&t;&t;u.sysv_sb.s_toobig_block
DECL|macro|sv_block_base
mdefine_line|#define sv_block_base&t;&t;&t;&t;u.sysv_sb.s_block_base
DECL|macro|sv_fic_size
mdefine_line|#define sv_fic_size&t;&t;&t;&t;u.sysv_sb.s_fic_size
DECL|macro|sv_flc_size
mdefine_line|#define sv_flc_size&t;&t;&t;&t;u.sysv_sb.s_flc_size
DECL|macro|sv_bh1
mdefine_line|#define sv_bh1&t;&t;&t;&t;&t;u.sysv_sb.s_bh1
DECL|macro|sv_bh2
mdefine_line|#define sv_bh2&t;&t;&t;&t;&t;u.sysv_sb.s_bh2
DECL|macro|sv_sbd1
mdefine_line|#define sv_sbd1&t;&t;&t;&t;&t;u.sysv_sb.s_sbd1
DECL|macro|sv_sbd2
mdefine_line|#define sv_sbd2&t;&t;&t;&t;&t;u.sysv_sb.s_sbd2
DECL|macro|sv_sb_fic_count
mdefine_line|#define sv_sb_fic_count&t;&t;&t;&t;u.sysv_sb.s_sb_fic_count
DECL|macro|sv_sb_fic_inodes
mdefine_line|#define sv_sb_fic_inodes&t;&t;&t;u.sysv_sb.s_sb_fic_inodes
DECL|macro|sv_sb_total_free_inodes
mdefine_line|#define sv_sb_total_free_inodes&t;&t;&t;u.sysv_sb.s_sb_total_free_inodes
DECL|macro|sv_bcache_count
mdefine_line|#define sv_bcache_count&t;&t;&t;&t;u.sysv_sb.s_bcache_count
DECL|macro|sv_bcache
mdefine_line|#define sv_bcache&t;&t;&t;&t;u.sysv_sb.s_bcache
DECL|macro|sv_free_blocks
mdefine_line|#define sv_free_blocks&t;&t;&t;&t;u.sysv_sb.s_free_blocks
DECL|macro|sv_sb_time
mdefine_line|#define sv_sb_time&t;&t;&t;&t;u.sysv_sb.s_sb_time
DECL|macro|sv_sb_state
mdefine_line|#define sv_sb_state&t;&t;&t;&t;u.sysv_sb.s_sb_state
DECL|macro|sv_firstinodezone
mdefine_line|#define sv_firstinodezone&t;&t;&t;u.sysv_sb.s_firstinodezone
DECL|macro|sv_firstdatazone
mdefine_line|#define sv_firstdatazone&t;&t;&t;u.sysv_sb.s_firstdatazone
DECL|macro|sv_ninodes
mdefine_line|#define sv_ninodes&t;&t;&t;&t;u.sysv_sb.s_ninodes
DECL|macro|sv_ndatazones
mdefine_line|#define sv_ndatazones&t;&t;&t;&t;u.sysv_sb.s_ndatazones
DECL|macro|sv_nzones
mdefine_line|#define sv_nzones&t;&t;&t;&t;u.sysv_sb.s_nzones
DECL|macro|sv_namelen
mdefine_line|#define sv_namelen                              u.sysv_sb.s_namelen
macro_line|#endif
eof
