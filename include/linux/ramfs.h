macro_line|#ifndef _LINUX_RAMFS_H
DECL|macro|_LINUX_RAMFS_H
mdefine_line|#define _LINUX_RAMFS_H
r_struct
id|inode
op_star
id|ramfs_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|mode
comma
id|dev_t
id|dev
)paren
suffix:semicolon
r_struct
id|super_block
op_star
id|ramfs_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ramfs_file_operations
suffix:semicolon
r_extern
r_struct
id|vm_operations_struct
id|generic_file_vm_ops
suffix:semicolon
macro_line|#endif
eof
