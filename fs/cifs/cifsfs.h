multiline_comment|/*&n; *   fs/cifs/cifsfs.h&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#ifndef _CIFSFS_H
DECL|macro|_CIFSFS_H
mdefine_line|#define _CIFSFS_H
DECL|macro|ROOT_I
mdefine_line|#define ROOT_I 2
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
r_extern
r_struct
id|address_space_operations
id|cifs_addr_ops
suffix:semicolon
multiline_comment|/* Functions related to super block operations */
r_extern
r_struct
id|super_operations
id|cifs_super_ops
suffix:semicolon
r_extern
r_void
id|cifs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|cifs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* extern void cifs_write_inode(struct inode *); */
multiline_comment|/* BB not needed yet */
multiline_comment|/* Functions related to inodes */
r_extern
r_struct
id|inode_operations
id|cifs_dir_inode_ops
suffix:semicolon
r_extern
r_int
id|cifs_create
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
r_int
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
id|cifs_lookup
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
r_int
id|cifs_unlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_hardlink
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_mknod
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
r_int
comma
id|dev_t
)paren
suffix:semicolon
r_extern
r_int
id|cifs_mkdir
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
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cifs_rmdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_rename
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
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_revalidate
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_getattr
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
r_extern
r_int
id|cifs_setattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|cifs_file_inode_ops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|cifs_symlink_inode_ops
suffix:semicolon
multiline_comment|/* Functions related to files and directories */
r_extern
r_struct
id|file_operations
id|cifs_file_ops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|cifs_file_direct_ops
suffix:semicolon
multiline_comment|/* if directio mount */
r_extern
r_int
id|cifs_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|cifs_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|cifs_closedir
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
id|ssize_t
id|cifs_user_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|read_data
comma
r_int
id|read_size
comma
id|loff_t
op_star
id|poffset
)paren
suffix:semicolon
r_extern
id|ssize_t
id|cifs_user_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|write_data
comma
r_int
id|write_size
comma
id|loff_t
op_star
id|poffset
)paren
suffix:semicolon
r_extern
r_int
id|cifs_lock
c_func
(paren
r_struct
id|file
op_star
comma
r_int
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_fsync
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
r_int
id|cifs_flush
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_file_mmap
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|cifs_dir_ops
suffix:semicolon
r_extern
r_int
id|cifs_dir_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|cifs_readdir
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|direntry
comma
id|filldir_t
id|filldir
)paren
suffix:semicolon
r_extern
r_int
id|cifs_dir_notify
c_func
(paren
r_struct
id|file
op_star
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* Functions related to dir entries */
r_extern
r_struct
id|dentry_operations
id|cifs_dentry_ops
suffix:semicolon
multiline_comment|/* Functions related to symlinks */
r_extern
r_int
id|cifs_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
suffix:semicolon
r_extern
r_void
id|cifs_put_link
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
suffix:semicolon
r_extern
r_int
id|cifs_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
id|cifs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|direntry
comma
r_const
r_char
op_star
id|symname
)paren
suffix:semicolon
r_extern
r_int
id|cifs_removexattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_setxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
id|ssize_t
id|cifs_getxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|ssize_t
id|cifs_listxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|CIFS_VERSION
mdefine_line|#define CIFS_VERSION   &quot;1.31&quot;
macro_line|#endif&t;&t;&t;&t;/* _CIFSFS_H */
eof
