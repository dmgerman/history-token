multiline_comment|/*&n; *  Autogenerated with cproto on:  Sat Sep 13 17:18:51 CEST 2003&n; */
r_struct
id|smb_request
suffix:semicolon
r_struct
id|sock
suffix:semicolon
r_struct
id|statfs
suffix:semicolon
multiline_comment|/* proc.c */
r_extern
r_int
id|smb_setcodepage
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|smb_nls_codepage
op_star
id|cp
)paren
suffix:semicolon
r_extern
id|__u32
id|smb_len
c_func
(paren
id|__u8
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|smb_get_rsize
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_get_wsize
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_errno
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|smb_newconn
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|smb_conn_opt
op_star
id|opt
)paren
suffix:semicolon
r_extern
id|__u8
op_star
id|smb_setup_header
c_func
(paren
r_struct
id|smb_request
op_star
id|req
comma
id|__u8
id|command
comma
id|__u16
id|wct
comma
id|__u16
id|bcc
)paren
suffix:semicolon
r_extern
r_int
id|smb_open
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|wish
)paren
suffix:semicolon
r_extern
r_int
id|smb_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
)paren
suffix:semicolon
r_extern
r_int
id|smb_close_fileid
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u16
id|fileid
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_create
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u16
id|attr
comma
id|time_t
id|ctime
comma
id|__u16
op_star
id|fileid
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_mv
c_func
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_mkdir
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_rmdir
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_unlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_flush
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
id|__u16
id|fileid
)paren
suffix:semicolon
r_extern
r_void
id|smb_init_root_dirent
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|smb_fattr
op_star
id|fattr
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|smb_decode_unix_basic
c_func
(paren
r_struct
id|smb_fattr
op_star
id|fattr
comma
r_struct
id|smb_sb_info
op_star
id|server
comma
r_char
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_getattr
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|smb_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_struct
id|smb_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_setattr_unix
c_func
(paren
r_struct
id|dentry
op_star
id|d
comma
r_struct
id|iattr
op_star
id|attr
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_settime
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|smb_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_dskattr
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_read_link
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|dentry
op_star
id|d
comma
r_char
op_star
id|buffer
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_symlink
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|dentry
op_star
id|d
comma
r_const
r_char
op_star
id|oldpath
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_link
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
suffix:semicolon
r_extern
r_int
id|smb_proc_query_cifsunix
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_void
id|smb_install_null_ops
c_func
(paren
r_struct
id|smb_ops
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|smb_dir_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|smb_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|smb_dir_inode_operations_unix
suffix:semicolon
r_extern
r_void
id|smb_new_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_void
id|smb_renew_times
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
multiline_comment|/* cache.c */
r_extern
r_void
id|smb_invalid_dir_cache
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_void
id|smb_invalidate_dircache_entries
c_func
(paren
r_struct
id|dentry
op_star
id|parent
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|smb_dget_fpos
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|parent
comma
r_int
r_int
id|fpos
)paren
suffix:semicolon
r_extern
r_int
id|smb_fill_cache
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
comma
r_struct
id|smb_cache_control
op_star
id|ctrl
comma
r_struct
id|qstr
op_star
id|qname
comma
r_struct
id|smb_fattr
op_star
id|entry
)paren
suffix:semicolon
multiline_comment|/* sock.c */
r_extern
r_void
id|smb_data_ready
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|smb_valid_socket
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|smb_close_socket
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_recv_available
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_receive_header
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_receive_drop
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_receive
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|smb_send_request
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_struct
id|inode
op_star
id|smb_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|smb_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_void
id|smb_get_inode_attr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|smb_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_void
id|smb_set_inode_attr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|smb_fattr
op_star
id|fattr
)paren
suffix:semicolon
r_extern
r_void
id|smb_invalidate_inodes
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_revalidate_inode
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|smb_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|raw_data
comma
r_int
id|silent
)paren
suffix:semicolon
r_extern
r_int
id|smb_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
suffix:semicolon
r_extern
r_int
id|smb_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|address_space_operations
id|smb_file_aops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|smb_file_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|smb_file_inode_operations
suffix:semicolon
multiline_comment|/* ioctl.c */
r_extern
r_int
id|smb_ioctl
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* smbiod.c */
r_extern
r_void
id|smbiod_wake_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|smbiod_register_server
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_void
id|smbiod_unregister_server
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_void
id|smbiod_flush
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smbiod_retry
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* request.c */
r_extern
r_int
id|smb_init_request_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smb_destroy_request_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|smb_request
op_star
id|smb_alloc_request
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_int
id|bufsize
)paren
suffix:semicolon
r_extern
r_void
id|smb_rget
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|smb_rput
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|smb_add_request
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|smb_request_send_req
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|smb_request_send_server
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|smb_request_recv
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_int
id|smb_symlink
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
id|dentry
comma
r_const
r_char
op_star
id|oldname
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|smb_link_inode_operations
suffix:semicolon
eof
