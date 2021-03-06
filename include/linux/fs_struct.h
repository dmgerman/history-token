macro_line|#ifndef _LINUX_FS_STRUCT_H
DECL|macro|_LINUX_FS_STRUCT_H
mdefine_line|#define _LINUX_FS_STRUCT_H
r_struct
id|dentry
suffix:semicolon
r_struct
id|vfsmount
suffix:semicolon
DECL|struct|fs_struct
r_struct
id|fs_struct
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|umask
r_int
id|umask
suffix:semicolon
DECL|member|root
DECL|member|pwd
DECL|member|altroot
r_struct
id|dentry
op_star
id|root
comma
op_star
id|pwd
comma
op_star
id|altroot
suffix:semicolon
DECL|member|rootmnt
DECL|member|pwdmnt
DECL|member|altrootmnt
r_struct
id|vfsmount
op_star
id|rootmnt
comma
op_star
id|pwdmnt
comma
op_star
id|altrootmnt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_FS
mdefine_line|#define INIT_FS {&t;&t;&t;&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(1),&t;&bslash;&n;&t;.lock&t;&t;= RW_LOCK_UNLOCKED,&t;&bslash;&n;&t;.umask&t;&t;= 0022, &bslash;&n;}
r_extern
r_void
id|exit_fs
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|set_fs_altroot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_fs_root
c_func
(paren
r_struct
id|fs_struct
op_star
comma
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|set_fs_pwd
c_func
(paren
r_struct
id|fs_struct
op_star
comma
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|fs_struct
op_star
id|copy_fs_struct
c_func
(paren
r_struct
id|fs_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|put_fs_struct
c_func
(paren
r_struct
id|fs_struct
op_star
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_FS_STRUCT_H */
eof
