multiline_comment|/*&n; *  linux/include/linux/ext3_fs_i.h&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs_i.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT3_FS_I
DECL|macro|_LINUX_EXT3_FS_I
mdefine_line|#define _LINUX_EXT3_FS_I
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/rbtree.h&gt;
macro_line|#include &lt;linux/seqlock.h&gt;
DECL|struct|ext3_reserve_window
r_struct
id|ext3_reserve_window
(brace
DECL|member|_rsv_start
id|__u32
id|_rsv_start
suffix:semicolon
multiline_comment|/* First byte reserved */
DECL|member|_rsv_end
id|__u32
id|_rsv_end
suffix:semicolon
multiline_comment|/* Last byte reserved or 0 */
)brace
suffix:semicolon
DECL|struct|ext3_reserve_window_node
r_struct
id|ext3_reserve_window_node
(brace
DECL|member|rsv_node
r_struct
id|rb_node
id|rsv_node
suffix:semicolon
DECL|member|rsv_goal_size
id|atomic_t
id|rsv_goal_size
suffix:semicolon
DECL|member|rsv_alloc_hit
id|atomic_t
id|rsv_alloc_hit
suffix:semicolon
DECL|member|rsv_seqlock
id|seqlock_t
id|rsv_seqlock
suffix:semicolon
DECL|member|rsv_window
r_struct
id|ext3_reserve_window
id|rsv_window
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|rsv_start
mdefine_line|#define rsv_start rsv_window._rsv_start
DECL|macro|rsv_end
mdefine_line|#define rsv_end rsv_window._rsv_end
multiline_comment|/*&n; * third extended file system inode data in memory&n; */
DECL|struct|ext3_inode_info
r_struct
id|ext3_inode_info
(brace
DECL|member|i_data
id|__le32
id|i_data
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* unconverted */
DECL|member|i_flags
id|__u32
id|i_flags
suffix:semicolon
macro_line|#ifdef EXT3_FRAGMENTS
DECL|member|i_faddr
id|__u32
id|i_faddr
suffix:semicolon
DECL|member|i_frag_no
id|__u8
id|i_frag_no
suffix:semicolon
DECL|member|i_frag_size
id|__u8
id|i_frag_size
suffix:semicolon
macro_line|#endif
DECL|member|i_file_acl
id|__u32
id|i_file_acl
suffix:semicolon
DECL|member|i_dir_acl
id|__u32
id|i_dir_acl
suffix:semicolon
DECL|member|i_dtime
id|__u32
id|i_dtime
suffix:semicolon
multiline_comment|/*&n;&t; * i_block_group is the number of the block group which contains&n;&t; * this file&squot;s inode.  Constant across the lifetime of the inode,&n;&t; * it is ued for making block allocation decisions - we try to&n;&t; * place a file&squot;s data blocks near its inode block, and new inodes&n;&t; * near to their parent directory&squot;s inode.&n;&t; */
DECL|member|i_block_group
id|__u32
id|i_block_group
suffix:semicolon
DECL|member|i_state
id|__u32
id|i_state
suffix:semicolon
multiline_comment|/* Dynamic state flags for ext3 */
multiline_comment|/*&n;&t; * i_next_alloc_block is the logical (file-relative) number of the&n;&t; * most-recently-allocated block in this file.  Yes, it is misnamed.&n;&t; * We use this for detecting linearly ascending allocation requests.&n;&t; */
DECL|member|i_next_alloc_block
id|__u32
id|i_next_alloc_block
suffix:semicolon
multiline_comment|/*&n;&t; * i_next_alloc_goal is the *physical* companion to i_next_alloc_block.&n;&t; * it the the physical block number of the block which was most-recently&n;&t; * allocated to this file.  This give us the goal (target) for the next&n;&t; * allocation when we detect linearly ascending requests.&n;&t; */
DECL|member|i_next_alloc_goal
id|__u32
id|i_next_alloc_goal
suffix:semicolon
multiline_comment|/* block reservation window */
DECL|member|i_rsv_window
r_struct
id|ext3_reserve_window_node
id|i_rsv_window
suffix:semicolon
DECL|member|i_dir_start_lookup
id|__u32
id|i_dir_start_lookup
suffix:semicolon
macro_line|#ifdef CONFIG_EXT3_FS_XATTR
multiline_comment|/*&n;&t; * Extended attributes can be read independently of the main file&n;&t; * data. Taking i_sem even when reading would cause contention&n;&t; * between readers of EAs and writers of regular file data, so&n;&t; * instead we synchronize on xattr_sem when reading or changing&n;&t; * EAs.&n;&t; */
DECL|member|xattr_sem
r_struct
id|rw_semaphore
id|xattr_sem
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EXT3_FS_POSIX_ACL
DECL|member|i_acl
r_struct
id|posix_acl
op_star
id|i_acl
suffix:semicolon
DECL|member|i_default_acl
r_struct
id|posix_acl
op_star
id|i_default_acl
suffix:semicolon
macro_line|#endif
DECL|member|i_orphan
r_struct
id|list_head
id|i_orphan
suffix:semicolon
multiline_comment|/* unlinked but open inodes */
multiline_comment|/*&n;&t; * i_disksize keeps track of what the inode size is ON DISK, not&n;&t; * in memory.  During truncate, i_size is set to the new size by&n;&t; * the VFS prior to calling ext3_truncate(), but the filesystem won&squot;t&n;&t; * set i_disksize to 0 until the truncate is actually under way.&n;&t; *&n;&t; * The intent is that i_disksize always represents the blocks which&n;&t; * are used by this file.  This allows recovery to restart truncate&n;&t; * on orphans if we crash during truncate.  We actually write i_disksize&n;&t; * into the on-disk inode when writing inodes out, instead of i_size.&n;&t; *&n;&t; * The only time when i_disksize and i_size may be different is when&n;&t; * a truncate is in progress.  The only things which change i_disksize&n;&t; * are ext3_get_block (growth) and ext3_truncate (shrinkth).&n;&t; */
DECL|member|i_disksize
id|loff_t
id|i_disksize
suffix:semicolon
multiline_comment|/*&n;&t; * truncate_sem is for serialising ext3_truncate() against&n;&t; * ext3_getblock().  In the 2.4 ext2 design, great chunks of inode&squot;s&n;&t; * data tree are chopped off during truncate. We can&squot;t do that in&n;&t; * ext3 because whenever we perform intermediate commits during&n;&t; * truncate, the inode and all the metadata blocks *must* be in a&n;&t; * consistent state which allows truncation of the orphans to restart&n;&t; * during recovery.  Hence we must fix the get_block-vs-truncate race&n;&t; * by other means, so we have truncate_sem.&n;&t; */
DECL|member|truncate_sem
r_struct
id|semaphore
id|truncate_sem
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_EXT3_FS_I */
eof
