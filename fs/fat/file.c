multiline_comment|/*&n; *  linux/fs/fat/file.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *&n; *  regular file handling primitives for fat-based filesystems&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|function|fat_file_aio_write
r_static
id|ssize_t
id|fat_file_aio_write
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|pos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|iocb-&gt;ki_filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|generic_file_aio_write
c_func
(paren
id|iocb
comma
id|buf
comma
id|count
comma
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
singleline_comment|//&t;&t;check the locking rules
singleline_comment|//&t;&t;if (IS_SYNC(inode))
singleline_comment|//&t;&t;&t;fat_sync_inode(inode);
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fat_file_writev
r_static
id|ssize_t
id|fat_file_writev
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_struct
id|iovec
op_star
id|iov
comma
r_int
r_int
id|nr_segs
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|generic_file_writev
c_func
(paren
id|filp
comma
id|iov
comma
id|nr_segs
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fat_generic_ioctl
r_int
id|fat_generic_ioctl
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
(brace
r_struct
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|u32
id|__user
op_star
id|user_attr
op_assign
(paren
id|u32
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FAT_IOCTL_GET_ATTRIBUTES
suffix:colon
(brace
id|u32
id|attr
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
id|attr
op_assign
id|ATTR_DIR
suffix:semicolon
r_else
id|attr
op_assign
id|fat_attr
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|attr
comma
id|user_attr
)paren
suffix:semicolon
)brace
r_case
id|FAT_IOCTL_SET_ATTRIBUTES
suffix:colon
(brace
id|u32
id|attr
comma
id|oldattr
suffix:semicolon
r_int
id|err
comma
id|is_dir
op_assign
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_struct
id|iattr
id|ia
suffix:semicolon
id|err
op_assign
id|get_user
c_func
(paren
id|attr
comma
id|user_attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EROFS
suffix:semicolon
r_goto
id|up
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * ATTR_VOLUME and ATTR_DIR cannot be changed; this also&n;&t;&t; * prevents the user from turning us into a VFAT&n;&t;&t; * longname entry.  Also, we obviously can&squot;t set&n;&t;&t; * any of the NTFS attributes in the high 24 bits.&n;&t;&t; */
id|attr
op_and_assign
l_int|0xff
op_amp
op_complement
(paren
id|ATTR_VOLUME
op_or
id|ATTR_DIR
)paren
suffix:semicolon
multiline_comment|/* Merge in ATTR_VOLUME and ATTR_DIR */
id|attr
op_or_assign
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_amp
id|ATTR_VOLUME
)paren
op_or
(paren
id|is_dir
ques
c_cond
id|ATTR_DIR
suffix:colon
l_int|0
)paren
suffix:semicolon
id|oldattr
op_assign
id|fat_attr
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* Equivalent to a chmod() */
id|ia.ia_valid
op_assign
id|ATTR_MODE
op_or
id|ATTR_CTIME
suffix:semicolon
r_if
c_cond
(paren
id|is_dir
)paren
(brace
id|ia.ia_mode
op_assign
id|MSDOS_MKMODE
c_func
(paren
id|attr
comma
id|S_IRWXUGO
op_amp
op_complement
id|sbi-&gt;options.fs_dmask
)paren
op_or
id|S_IFDIR
suffix:semicolon
)brace
r_else
(brace
id|ia.ia_mode
op_assign
id|MSDOS_MKMODE
c_func
(paren
id|attr
comma
(paren
id|S_IRUGO
op_or
id|S_IWUGO
op_or
(paren
id|inode-&gt;i_mode
op_amp
id|S_IXUGO
)paren
)paren
op_amp
op_complement
id|sbi-&gt;options.fs_fmask
)paren
op_or
id|S_IFREG
suffix:semicolon
)brace
multiline_comment|/* The root directory has no attributes */
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
op_logical_and
id|attr
op_ne
id|ATTR_DIR
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|up
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sbi-&gt;options.sys_immutable
)paren
(brace
r_if
c_cond
(paren
(paren
id|attr
op_or
id|oldattr
)paren
op_amp
id|ATTR_SYS
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_LINUX_IMMUTABLE
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|up
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* This MUST be done before doing anything irreversible... */
id|err
op_assign
id|notify_change
c_func
(paren
id|filp-&gt;f_dentry
comma
op_amp
id|ia
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|up
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;options.sys_immutable
)paren
(brace
r_if
c_cond
(paren
id|attr
op_amp
id|ATTR_SYS
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_IMMUTABLE
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
id|S_IMMUTABLE
suffix:semicolon
)brace
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_assign
id|attr
op_amp
id|ATTR_UNUSED
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|up
suffix:colon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
multiline_comment|/* Inappropriate ioctl for device */
)brace
)brace
DECL|variable|fat_file_operations
r_struct
id|file_operations
id|fat_file_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|do_sync_read
comma
dot
id|write
op_assign
id|do_sync_write
comma
dot
id|readv
op_assign
id|generic_file_readv
comma
dot
id|writev
op_assign
id|fat_file_writev
comma
dot
id|aio_read
op_assign
id|generic_file_aio_read
comma
dot
id|aio_write
op_assign
id|fat_file_aio_write
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|ioctl
op_assign
id|fat_generic_ioctl
comma
dot
id|fsync
op_assign
id|file_fsync
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|function|fat_notify_change
r_int
id|fat_notify_change
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
(brace
r_struct
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|dentry-&gt;d_sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|mask
comma
id|error
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* FAT cannot truncate to a longer file */
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_SIZE
)paren
(brace
r_if
c_cond
(paren
id|attr-&gt;ia_size
OG
id|inode-&gt;i_size
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|error
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;options.quiet
)paren
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
op_logical_and
(paren
id|attr-&gt;ia_uid
op_ne
id|sbi-&gt;options.fs_uid
)paren
)paren
op_logical_or
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
op_logical_and
(paren
id|attr-&gt;ia_gid
op_ne
id|sbi-&gt;options.fs_gid
)paren
)paren
op_logical_or
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
op_logical_and
(paren
id|attr-&gt;ia_mode
op_amp
op_complement
id|MSDOS_VALID_MODE
)paren
)paren
)paren
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_if
c_cond
(paren
id|sbi-&gt;options.quiet
)paren
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|error
op_assign
id|inode_setattr
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|mask
op_assign
id|sbi-&gt;options.fs_dmask
suffix:semicolon
r_else
id|mask
op_assign
id|sbi-&gt;options.fs_fmask
suffix:semicolon
id|inode-&gt;i_mode
op_and_assign
id|S_IFMT
op_or
(paren
id|S_IRWXUGO
op_amp
op_complement
id|mask
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|fat_notify_change
id|EXPORT_SYMBOL
c_func
(paren
id|fat_notify_change
)paren
suffix:semicolon
multiline_comment|/* Free all clusters after the skip&squot;th cluster. */
DECL|function|fat_free
r_static
r_int
id|fat_free
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|skip
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|ret
comma
id|wait
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Write a new EOF, and get the remaining cluster chain for freeing.&n;&t; */
id|wait
op_assign
id|IS_DIRSYNC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skip
)paren
(brace
r_struct
id|fat_entry
id|fatent
suffix:semicolon
r_int
id|fclus
comma
id|dclus
suffix:semicolon
id|ret
op_assign
id|fat_get_cluster
c_func
(paren
id|inode
comma
id|skip
op_minus
l_int|1
comma
op_amp
id|fclus
comma
op_amp
id|dclus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ret
op_eq
id|FAT_ENT_EOF
)paren
r_return
l_int|0
suffix:semicolon
id|fatent_init
c_func
(paren
op_amp
id|fatent
)paren
suffix:semicolon
id|ret
op_assign
id|fat_ent_read
c_func
(paren
id|inode
comma
op_amp
id|fatent
comma
id|dclus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|FAT_ENT_EOF
)paren
(brace
id|fatent_brelse
c_func
(paren
op_amp
id|fatent
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret
op_eq
id|FAT_ENT_FREE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: invalid cluster chain (i_pos %lld)&quot;
comma
id|__FUNCTION__
comma
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_pos
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
r_int
id|err
op_assign
id|fat_ent_write
c_func
(paren
id|inode
comma
op_amp
id|fatent
comma
id|FAT_ENT_EOF
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ret
op_assign
id|err
suffix:semicolon
)brace
id|fatent_brelse
c_func
(paren
op_amp
id|fatent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|fat_cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|fat_cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|ret
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
l_int|0
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_logstart
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
(brace
r_int
id|err
op_assign
id|fat_sync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
r_else
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_assign
id|skip
op_lshift
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_bits
op_minus
l_int|9
)paren
suffix:semicolon
multiline_comment|/* Freeing the remained cluster chain */
r_return
id|fat_free_clusters
c_func
(paren
id|inode
comma
id|ret
)paren
suffix:semicolon
)brace
DECL|function|fat_truncate
r_void
id|fat_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_const
r_int
r_int
id|cluster_size
op_assign
id|sbi-&gt;cluster_size
suffix:semicolon
r_int
id|nr_clusters
suffix:semicolon
multiline_comment|/*&n;&t; * This protects against truncating a file bigger than it was then&n;&t; * trying to write into the hole.&n;&t; */
r_if
c_cond
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
OG
id|inode-&gt;i_size
)paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|nr_clusters
op_assign
(paren
id|inode-&gt;i_size
op_plus
(paren
id|cluster_size
op_minus
l_int|1
)paren
)paren
op_rshift
id|sbi-&gt;cluster_bits
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fat_free
c_func
(paren
id|inode
comma
id|nr_clusters
)paren
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_attrs
op_or_assign
id|ATTR_ARCH
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME_SEC
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_SYNC
c_func
(paren
id|inode
)paren
)paren
id|fat_sync_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|variable|fat_file_inode_operations
r_struct
id|inode_operations
id|fat_file_inode_operations
op_assign
(brace
dot
id|truncate
op_assign
id|fat_truncate
comma
dot
id|setattr
op_assign
id|fat_notify_change
comma
)brace
suffix:semicolon
eof
