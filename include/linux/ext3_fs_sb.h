multiline_comment|/*&n; *  linux/include/linux/ext3_fs_sb.h&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs_sb.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT3_FS_SB
DECL|macro|_LINUX_EXT3_FS_SB
mdefine_line|#define _LINUX_EXT3_FS_SB
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#endif
multiline_comment|/*&n; * third extended-fs super-block data in memory&n; */
DECL|struct|ext3_sb_info
r_struct
id|ext3_sb_info
(brace
DECL|member|s_frag_size
r_int
r_int
id|s_frag_size
suffix:semicolon
multiline_comment|/* Size of a fragment in bytes */
DECL|member|s_frags_per_block
r_int
r_int
id|s_frags_per_block
suffix:semicolon
multiline_comment|/* Number of fragments per block */
DECL|member|s_inodes_per_block
r_int
r_int
id|s_inodes_per_block
suffix:semicolon
multiline_comment|/* Number of inodes per block */
DECL|member|s_frags_per_group
r_int
r_int
id|s_frags_per_group
suffix:semicolon
multiline_comment|/* Number of fragments in a group */
DECL|member|s_blocks_per_group
r_int
r_int
id|s_blocks_per_group
suffix:semicolon
multiline_comment|/* Number of blocks in a group */
DECL|member|s_inodes_per_group
r_int
r_int
id|s_inodes_per_group
suffix:semicolon
multiline_comment|/* Number of inodes in a group */
DECL|member|s_itb_per_group
r_int
r_int
id|s_itb_per_group
suffix:semicolon
multiline_comment|/* Number of inode table blocks per group */
DECL|member|s_gdb_count
r_int
r_int
id|s_gdb_count
suffix:semicolon
multiline_comment|/* Number of group descriptor blocks */
DECL|member|s_desc_per_block
r_int
r_int
id|s_desc_per_block
suffix:semicolon
multiline_comment|/* Number of group descriptors per block */
DECL|member|s_groups_count
r_int
r_int
id|s_groups_count
suffix:semicolon
multiline_comment|/* Number of groups in the fs */
DECL|member|s_sbh
r_struct
id|buffer_head
op_star
id|s_sbh
suffix:semicolon
multiline_comment|/* Buffer containing the super block */
DECL|member|s_es
r_struct
id|ext3_super_block
op_star
id|s_es
suffix:semicolon
multiline_comment|/* Pointer to the super block in the buffer */
DECL|member|s_group_desc
r_struct
id|buffer_head
op_star
op_star
id|s_group_desc
suffix:semicolon
DECL|member|s_mount_opt
r_int
r_int
id|s_mount_opt
suffix:semicolon
DECL|member|s_resuid
id|uid_t
id|s_resuid
suffix:semicolon
DECL|member|s_resgid
id|gid_t
id|s_resgid
suffix:semicolon
DECL|member|s_mount_state
r_int
r_int
id|s_mount_state
suffix:semicolon
DECL|member|s_pad
r_int
r_int
id|s_pad
suffix:semicolon
DECL|member|s_addr_per_block_bits
r_int
id|s_addr_per_block_bits
suffix:semicolon
DECL|member|s_desc_per_block_bits
r_int
id|s_desc_per_block_bits
suffix:semicolon
DECL|member|s_inode_size
r_int
id|s_inode_size
suffix:semicolon
DECL|member|s_first_ino
r_int
id|s_first_ino
suffix:semicolon
DECL|member|s_next_generation
id|u32
id|s_next_generation
suffix:semicolon
multiline_comment|/* Journaling */
DECL|member|s_journal_inode
r_struct
id|inode
op_star
id|s_journal_inode
suffix:semicolon
DECL|member|s_journal
r_struct
id|journal_s
op_star
id|s_journal
suffix:semicolon
DECL|member|s_orphan
r_struct
id|list_head
id|s_orphan
suffix:semicolon
DECL|member|s_commit_interval
r_int
r_int
id|s_commit_interval
suffix:semicolon
DECL|member|journal_bdev
r_struct
id|block_device
op_star
id|journal_bdev
suffix:semicolon
macro_line|#ifdef CONFIG_JBD_DEBUG
DECL|member|turn_ro_timer
r_struct
id|timer_list
id|turn_ro_timer
suffix:semicolon
multiline_comment|/* For turning read-only (crash simulation) */
DECL|member|ro_wait_queue
id|wait_queue_head_t
id|ro_wait_queue
suffix:semicolon
multiline_comment|/* For people waiting for the fs to go read-only */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_EXT3_FS_SB */
eof
