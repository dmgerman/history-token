macro_line|#ifndef __UM_FS_HOSTFS
DECL|macro|__UM_FS_HOSTFS
mdefine_line|#define __UM_FS_HOSTFS
macro_line|#include &quot;os.h&quot;
multiline_comment|/* These are exactly the same definitions as in fs.h, but the names are&n; * changed so that this file can be included in both kernel and user files.&n; */
DECL|macro|HOSTFS_ATTR_MODE
mdefine_line|#define HOSTFS_ATTR_MODE&t;1
DECL|macro|HOSTFS_ATTR_UID
mdefine_line|#define HOSTFS_ATTR_UID &t;2
DECL|macro|HOSTFS_ATTR_GID
mdefine_line|#define HOSTFS_ATTR_GID &t;4
DECL|macro|HOSTFS_ATTR_SIZE
mdefine_line|#define HOSTFS_ATTR_SIZE&t;8
DECL|macro|HOSTFS_ATTR_ATIME
mdefine_line|#define HOSTFS_ATTR_ATIME&t;16
DECL|macro|HOSTFS_ATTR_MTIME
mdefine_line|#define HOSTFS_ATTR_MTIME&t;32
DECL|macro|HOSTFS_ATTR_CTIME
mdefine_line|#define HOSTFS_ATTR_CTIME&t;64
DECL|macro|HOSTFS_ATTR_ATIME_SET
mdefine_line|#define HOSTFS_ATTR_ATIME_SET&t;128
DECL|macro|HOSTFS_ATTR_MTIME_SET
mdefine_line|#define HOSTFS_ATTR_MTIME_SET&t;256
DECL|macro|HOSTFS_ATTR_FORCE
mdefine_line|#define HOSTFS_ATTR_FORCE&t;512&t;/* Not a change, but a change it */
DECL|macro|HOSTFS_ATTR_ATTR_FLAG
mdefine_line|#define HOSTFS_ATTR_ATTR_FLAG&t;1024
DECL|struct|hostfs_iattr
r_struct
id|hostfs_iattr
(brace
DECL|member|ia_valid
r_int
r_int
id|ia_valid
suffix:semicolon
DECL|member|ia_mode
id|mode_t
id|ia_mode
suffix:semicolon
DECL|member|ia_uid
id|uid_t
id|ia_uid
suffix:semicolon
DECL|member|ia_gid
id|gid_t
id|ia_gid
suffix:semicolon
DECL|member|ia_size
id|loff_t
id|ia_size
suffix:semicolon
DECL|member|ia_atime
r_struct
id|timespec
id|ia_atime
suffix:semicolon
DECL|member|ia_mtime
r_struct
id|timespec
id|ia_mtime
suffix:semicolon
DECL|member|ia_ctime
r_struct
id|timespec
id|ia_ctime
suffix:semicolon
DECL|member|ia_attr_flags
r_int
r_int
id|ia_attr_flags
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|stat_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
r_int
op_star
id|inode_out
comma
r_int
op_star
id|mode_out
comma
r_int
op_star
id|nlink_out
comma
r_int
op_star
id|uid_out
comma
r_int
op_star
id|gid_out
comma
r_int
r_int
r_int
op_star
id|size_out
comma
r_struct
id|timespec
op_star
id|atime_out
comma
r_struct
id|timespec
op_star
id|mtime_out
comma
r_struct
id|timespec
op_star
id|ctime_out
comma
r_int
op_star
id|blksize_out
comma
r_int
r_int
r_int
op_star
id|blocks_out
)paren
suffix:semicolon
r_extern
r_int
id|access_file
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
suffix:semicolon
r_extern
r_int
id|open_file
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|append
)paren
suffix:semicolon
r_extern
r_int
id|file_type
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
op_star
id|maj
comma
r_int
op_star
id|min
)paren
suffix:semicolon
r_extern
r_void
op_star
id|open_dir
c_func
(paren
r_char
op_star
id|path
comma
r_int
op_star
id|err_out
)paren
suffix:semicolon
r_extern
r_char
op_star
id|read_dir
c_func
(paren
r_void
op_star
id|stream
comma
r_int
r_int
r_int
op_star
id|pos
comma
r_int
r_int
r_int
op_star
id|ino_out
comma
r_int
op_star
id|len_out
)paren
suffix:semicolon
r_extern
r_void
id|close_file
c_func
(paren
r_void
op_star
id|stream
)paren
suffix:semicolon
r_extern
r_void
id|close_dir
c_func
(paren
r_void
op_star
id|stream
)paren
suffix:semicolon
r_extern
r_int
id|read_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
r_int
op_star
id|offset
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|write_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
r_int
op_star
id|offset
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|lseek_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|offset
comma
r_int
id|whence
)paren
suffix:semicolon
r_extern
r_int
id|file_create
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|ur
comma
r_int
id|uw
comma
r_int
id|ux
comma
r_int
id|gr
comma
r_int
id|gw
comma
r_int
id|gx
comma
r_int
op_logical_or
comma
r_int
id|ow
comma
r_int
id|ox
)paren
suffix:semicolon
r_extern
r_int
id|set_attr
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_struct
id|hostfs_iattr
op_star
id|attrs
)paren
suffix:semicolon
r_extern
r_int
id|make_symlink
c_func
(paren
r_const
r_char
op_star
id|from
comma
r_const
r_char
op_star
id|to
)paren
suffix:semicolon
r_extern
r_int
id|unlink_file
c_func
(paren
r_const
r_char
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|do_mkdir
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|do_rmdir
c_func
(paren
r_const
r_char
op_star
id|file
)paren
suffix:semicolon
r_extern
r_int
id|do_mknod
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|mode
comma
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|link_file
c_func
(paren
r_const
r_char
op_star
id|from
comma
r_const
r_char
op_star
id|to
)paren
suffix:semicolon
r_extern
r_int
id|do_readlink
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|rename_file
c_func
(paren
r_char
op_star
id|from
comma
r_char
op_star
id|to
)paren
suffix:semicolon
r_extern
r_int
id|do_statfs
c_func
(paren
r_char
op_star
id|root
comma
r_int
op_star
id|bsize_out
comma
r_int
r_int
op_star
id|blocks_out
comma
r_int
r_int
op_star
id|bfree_out
comma
r_int
r_int
op_star
id|bavail_out
comma
r_int
r_int
op_star
id|files_out
comma
r_int
r_int
op_star
id|ffree_out
comma
r_void
op_star
id|fsid_out
comma
r_int
id|fsid_size
comma
r_int
op_star
id|namelen_out
comma
r_int
op_star
id|spare_out
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
