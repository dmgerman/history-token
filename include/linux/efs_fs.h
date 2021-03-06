multiline_comment|/*&n; * efs_fs.h&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from work (c) 1995,1996 Christian Vogelgsang.&n; */
macro_line|#ifndef __EFS_FS_H__
DECL|macro|__EFS_FS_H__
mdefine_line|#define __EFS_FS_H__
DECL|macro|EFS_VERSION
mdefine_line|#define EFS_VERSION &quot;1.0a&quot;
DECL|variable|cprt
r_static
r_const
r_char
id|cprt
(braket
)braket
op_assign
l_string|&quot;EFS: &quot;
id|EFS_VERSION
l_string|&quot; - (c) 1999 Al Smith &lt;Al.Smith@aeschi.ch.eu.org&gt;&quot;
suffix:semicolon
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* 1 block is 512 bytes */
DECL|macro|EFS_BLOCKSIZE_BITS
mdefine_line|#define&t;EFS_BLOCKSIZE_BITS&t;9
DECL|macro|EFS_BLOCKSIZE
mdefine_line|#define&t;EFS_BLOCKSIZE&t;&t;(1 &lt;&lt; EFS_BLOCKSIZE_BITS)
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/efs_fs_i.h&gt;
macro_line|#include &lt;linux/efs_fs_sb.h&gt;
macro_line|#include &lt;linux/efs_dir.h&gt;
DECL|function|INODE_INFO
r_static
r_inline
r_struct
id|efs_inode_info
op_star
id|INODE_INFO
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
r_struct
id|efs_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|SUPER_INFO
r_static
r_inline
r_struct
id|efs_sb_info
op_star
id|SUPER_INFO
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
r_struct
id|statfs
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|efs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|efs_dir_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|efs_symlink_aops
suffix:semicolon
r_extern
r_void
id|efs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
id|efs_block_t
id|efs_map_block
c_func
(paren
r_struct
id|inode
op_star
comma
id|efs_block_t
)paren
suffix:semicolon
r_extern
r_int
id|efs_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
id|sector_t
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|efs_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|nameidata
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|efs_get_parent
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|efs_bmap
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __EFS_FS_H__ */
eof
