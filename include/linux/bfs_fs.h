multiline_comment|/*&n; *&t;include/linux/bfs_fs.h - BFS data structures on disk.&n; *&t;Copyright (C) 1999 Tigran Aivazian &lt;tigran@veritas.com&gt;&n; */
macro_line|#ifndef _LINUX_BFS_FS_H
DECL|macro|_LINUX_BFS_FS_H
mdefine_line|#define _LINUX_BFS_FS_H
DECL|macro|BFS_BSIZE_BITS
mdefine_line|#define BFS_BSIZE_BITS&t;&t;9
DECL|macro|BFS_BSIZE
mdefine_line|#define BFS_BSIZE&t;&t;(1&lt;&lt;BFS_BSIZE_BITS)
DECL|macro|BFS_MAGIC
mdefine_line|#define BFS_MAGIC&t;&t;0x1BADFACE
DECL|macro|BFS_ROOT_INO
mdefine_line|#define BFS_ROOT_INO&t;&t;2
DECL|macro|BFS_INODES_PER_BLOCK
mdefine_line|#define BFS_INODES_PER_BLOCK&t;8
multiline_comment|/* SVR4 vnode type values (bfs_inode-&gt;i_vtype) */
DECL|macro|BFS_VDIR
mdefine_line|#define BFS_VDIR&t;&t;2
DECL|macro|BFS_VREG
mdefine_line|#define BFS_VREG&t;&t;1
multiline_comment|/* BFS inode layout on disk */
DECL|struct|bfs_inode
r_struct
id|bfs_inode
(brace
DECL|member|i_ino
id|__u16
id|i_ino
suffix:semicolon
DECL|member|i_unused
id|__u16
id|i_unused
suffix:semicolon
DECL|member|i_sblock
id|__u32
id|i_sblock
suffix:semicolon
DECL|member|i_eblock
id|__u32
id|i_eblock
suffix:semicolon
DECL|member|i_eoffset
id|__u32
id|i_eoffset
suffix:semicolon
DECL|member|i_vtype
id|__u32
id|i_vtype
suffix:semicolon
DECL|member|i_mode
id|__u32
id|i_mode
suffix:semicolon
DECL|member|i_uid
id|__s32
id|i_uid
suffix:semicolon
DECL|member|i_gid
id|__s32
id|i_gid
suffix:semicolon
DECL|member|i_nlink
id|__u32
id|i_nlink
suffix:semicolon
DECL|member|i_atime
id|__u32
id|i_atime
suffix:semicolon
DECL|member|i_mtime
id|__u32
id|i_mtime
suffix:semicolon
DECL|member|i_ctime
id|__u32
id|i_ctime
suffix:semicolon
DECL|member|i_padding
id|__u32
id|i_padding
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BFS_NAMELEN
mdefine_line|#define BFS_NAMELEN&t;&t;14&t;
DECL|macro|BFS_DIRENT_SIZE
mdefine_line|#define BFS_DIRENT_SIZE&t;&t;16
DECL|macro|BFS_DIRS_PER_BLOCK
mdefine_line|#define BFS_DIRS_PER_BLOCK&t;32
DECL|struct|bfs_dirent
r_struct
id|bfs_dirent
(brace
DECL|member|ino
id|__u16
id|ino
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|BFS_NAMELEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* BFS superblock layout on disk */
DECL|struct|bfs_super_block
r_struct
id|bfs_super_block
(brace
DECL|member|s_magic
id|__u32
id|s_magic
suffix:semicolon
DECL|member|s_start
id|__u32
id|s_start
suffix:semicolon
DECL|member|s_end
id|__u32
id|s_end
suffix:semicolon
DECL|member|s_from
id|__s32
id|s_from
suffix:semicolon
DECL|member|s_to
id|__s32
id|s_to
suffix:semicolon
DECL|member|s_bfrom
id|__s32
id|s_bfrom
suffix:semicolon
DECL|member|s_bto
id|__s32
id|s_bto
suffix:semicolon
DECL|member|s_fsname
r_char
id|s_fsname
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|s_volume
r_char
id|s_volume
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|s_padding
id|__u32
id|s_padding
(braket
l_int|118
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BFS_NZFILESIZE
mdefine_line|#define BFS_NZFILESIZE(ip) &bslash;&n;        (((ip)-&gt;i_eoffset + 1) - (ip)-&gt;i_sblock * BFS_BSIZE)
DECL|macro|BFS_FILESIZE
mdefine_line|#define BFS_FILESIZE(ip) &bslash;&n;        ((ip)-&gt;i_sblock == 0 ? 0 : BFS_NZFILESIZE(ip))
DECL|macro|BFS_FILEBLOCKS
mdefine_line|#define BFS_FILEBLOCKS(ip) &bslash;&n;        ((ip)-&gt;i_sblock == 0 ? 0 : ((ip)-&gt;i_eblock + 1) - (ip)-&gt;i_sblock)
DECL|macro|BFS_OFF2INO
mdefine_line|#define BFS_OFF2INO(offset) &bslash;&n;        ((((offset) - BFS_BSIZE) / sizeof(struct bfs_inode)) + BFS_ROOT_INO)
DECL|macro|BFS_INO2OFF
mdefine_line|#define BFS_INO2OFF(ino) &bslash;&n;&t;((__u32)(((ino) - BFS_ROOT_INO) * sizeof(struct bfs_inode)) + BFS_BSIZE)
DECL|macro|BFS_UNCLEAN
mdefine_line|#define BFS_UNCLEAN(bfs_sb, sb)&t;&bslash;&n;&t;((bfs_sb-&gt;s_from != -1) &amp;&amp; (bfs_sb-&gt;s_to != -1) &amp;&amp; !(sb-&gt;s_flags &amp; MS_RDONLY))
macro_line|#ifdef __KERNEL__
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|bfs_file_inops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|bfs_file_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|bfs_aops
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|inode_operations
id|bfs_dir_inops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|bfs_dir_operations
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_BFS_FS_H */
eof
