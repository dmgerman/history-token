multiline_comment|/*&n; *  linux/include/linux/ext2_fs_i.h&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs_i.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT2_FS_I
DECL|macro|_LINUX_EXT2_FS_I
mdefine_line|#define _LINUX_EXT2_FS_I
multiline_comment|/*&n; * second extended file system inode data in memory&n; */
DECL|struct|ext2_inode_info
r_struct
id|ext2_inode_info
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
DECL|member|i_osync
id|__u16
id|i_osync
suffix:semicolon
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
DECL|member|i_next_alloc_block
id|__u32
id|i_next_alloc_block
suffix:semicolon
DECL|member|i_next_alloc_goal
id|__u32
id|i_next_alloc_goal
suffix:semicolon
DECL|member|i_prealloc_block
id|__u32
id|i_prealloc_block
suffix:semicolon
DECL|member|i_prealloc_count
id|__u32
id|i_prealloc_count
suffix:semicolon
DECL|member|i_new_inode
r_int
id|i_new_inode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Is a freshly allocated inode */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_EXT2_FS_I */
eof
