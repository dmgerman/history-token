r_extern
r_struct
id|vfsmount
op_star
id|sysfs_mount
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|sysfs_new_inode
c_func
(paren
id|mode_t
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|sysfs_create
c_func
(paren
r_struct
id|dentry
op_star
comma
r_int
id|mode
comma
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|inode
op_star
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|sysfs_get_dentry
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
id|sysfs_add_file
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_const
r_struct
id|attribute
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_void
id|sysfs_hash_and_remove
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|sysfs_create_subdir
c_func
(paren
r_struct
id|kobject
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sysfs_remove_subdir
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
eof
