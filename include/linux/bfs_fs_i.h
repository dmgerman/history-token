multiline_comment|/*&n; *&t;include/linux/bfs_fs_i.h&n; *&t;Copyright (C) 1999 Tigran Aivazian &lt;tigran@veritas.com&gt;&n; */
macro_line|#ifndef _LINUX_BFS_FS_I
DECL|macro|_LINUX_BFS_FS_I
mdefine_line|#define _LINUX_BFS_FS_I
multiline_comment|/*&n; * BFS file system in-core inode info&n; */
DECL|struct|bfs_inode_info
r_struct
id|bfs_inode_info
(brace
DECL|member|i_dsk_ino
r_int
r_int
id|i_dsk_ino
suffix:semicolon
multiline_comment|/* inode number from the disk, can be 0 */
DECL|member|i_sblock
r_int
r_int
id|i_sblock
suffix:semicolon
DECL|member|i_eblock
r_int
r_int
id|i_eblock
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_BFS_FS_I */
eof
