multiline_comment|/*&n; *  linux/include/linux/ext3_fs_i.h&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs_i.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT3_FS_I
DECL|macro|_LINUX_EXT3_FS_I
mdefine_line|#define _LINUX_EXT3_FS_I
macro_line|#include &lt;linux/rwsem.h&gt;
multiline_comment|/*&n; * second extended file system inode data in memory&n; */
DECL|struct|ext3_inode_info
r_struct
id|ext3_inode_info
(brace
DECL|member|i_data
id|__u32
id|i_data
(braket
l_int|15
)braket
suffix:semicolon
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
DECL|member|unused
id|__u16
id|unused
suffix:semicolon
multiline_comment|/* formerly i_osync */
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
DECL|member|i_block_group
id|__u32
id|i_block_group
suffix:semicolon
DECL|member|i_state
id|__u32
id|i_state
suffix:semicolon
multiline_comment|/* Dynamic state flags for ext3 */
DECL|member|i_next_alloc_block
id|__u32
id|i_next_alloc_block
suffix:semicolon
DECL|member|i_next_alloc_goal
id|__u32
id|i_next_alloc_goal
suffix:semicolon
macro_line|#ifdef EXT3_PREALLOCATE
DECL|member|i_prealloc_block
id|__u32
id|i_prealloc_block
suffix:semicolon
DECL|member|i_prealloc_count
id|__u32
id|i_prealloc_count
suffix:semicolon
macro_line|#endif
DECL|member|i_dir_start_lookup
id|__u32
id|i_dir_start_lookup
suffix:semicolon
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
id|rw_semaphore
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
