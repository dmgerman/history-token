multiline_comment|/*&n; *&t;fs/libfs.c&n; *&t;Library for filesystems writers.&n; */
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|function|simple_statfs
r_int
id|simple_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
id|buf-&gt;f_type
op_assign
id|sb-&gt;s_magic
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|NAME_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Lookup the data. This is trivial - if the dentry didn&squot;t already&n; * exist, we know it is negative.&n; */
DECL|function|simple_lookup
r_struct
id|dentry
op_star
id|simple_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|d_add
c_func
(paren
id|dentry
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|simple_sync_file
r_int
id|simple_sync_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dcache_dir_open
r_int
id|dcache_dir_open
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
(brace
r_static
r_struct
id|qstr
id|cursor_name
op_assign
(brace
dot
id|len
op_assign
l_int|1
comma
dot
id|name
op_assign
l_string|&quot;.&quot;
)brace
suffix:semicolon
id|file-&gt;private_data
op_assign
id|d_alloc
c_func
(paren
id|file-&gt;f_dentry
comma
op_amp
id|cursor_name
)paren
suffix:semicolon
r_return
id|file-&gt;private_data
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|dcache_dir_close
r_int
id|dcache_dir_close
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
(brace
id|dput
c_func
(paren
id|file-&gt;private_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dcache_dir_lseek
id|loff_t
id|dcache_dir_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
id|down
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
)paren
r_break
suffix:semicolon
r_default
suffix:colon
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
l_int|2
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|dentry
op_star
id|cursor
op_assign
id|file-&gt;private_data
suffix:semicolon
id|loff_t
id|n
op_assign
id|file-&gt;f_pos
op_minus
l_int|2
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|p
op_assign
id|file-&gt;f_dentry-&gt;d_subdirs.next
suffix:semicolon
r_while
c_loop
(paren
id|n
op_logical_and
id|p
op_ne
op_amp
id|file-&gt;f_dentry-&gt;d_subdirs
)paren
(brace
r_struct
id|dentry
op_star
id|next
suffix:semicolon
id|next
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|next-&gt;d_hash
)paren
op_logical_and
id|next-&gt;d_inode
)paren
id|n
op_decrement
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|cursor-&gt;d_child
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|cursor-&gt;d_child
comma
id|p
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
multiline_comment|/* Relationship between i_mode and the DT_xxx types */
DECL|function|dt_type
r_static
r_inline
r_int
r_char
id|dt_type
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|inode-&gt;i_mode
op_rshift
l_int|12
)paren
op_amp
l_int|15
suffix:semicolon
)brace
multiline_comment|/*&n; * Directory is locked and all positive dentries in it are safe, since&n; * for ramfs-type trees they can&squot;t go away without unlink() or rmdir(),&n; * both impossible due to the lock on directory.&n; */
DECL|function|dcache_readdir
r_int
id|dcache_readdir
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
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|dentry
op_star
id|cursor
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_struct
id|list_head
op_star
id|p
comma
op_star
id|q
op_assign
op_amp
id|cursor-&gt;d_child
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
r_int
id|i
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|ino
op_assign
id|dentry-&gt;d_inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|i
comma
id|ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
l_int|1
suffix:colon
id|ino
op_assign
id|parent_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|i
comma
id|ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_default
suffix:colon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|2
)paren
(brace
id|list_del
c_func
(paren
id|q
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|q
comma
op_amp
id|dentry-&gt;d_subdirs
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|q-&gt;next
suffix:semicolon
id|p
op_ne
op_amp
id|dentry-&gt;d_subdirs
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|dentry
op_star
id|next
suffix:semicolon
id|next
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|next-&gt;d_hash
)paren
op_logical_or
op_logical_neg
id|next-&gt;d_inode
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|next-&gt;d_name.name
comma
id|next-&gt;d_name.len
comma
id|filp-&gt;f_pos
comma
id|next-&gt;d_inode-&gt;i_ino
comma
id|dt_type
c_func
(paren
id|next-&gt;d_inode
)paren
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
multiline_comment|/* next is still alive */
id|list_del
c_func
(paren
id|q
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|q
comma
id|p
)paren
suffix:semicolon
id|p
op_assign
id|q
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|generic_read_dir
id|ssize_t
id|generic_read_dir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|siz
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_return
op_minus
id|EISDIR
suffix:semicolon
)brace
DECL|variable|simple_dir_operations
r_struct
id|file_operations
id|simple_dir_operations
op_assign
(brace
dot
id|open
op_assign
id|dcache_dir_open
comma
dot
id|release
op_assign
id|dcache_dir_close
comma
dot
id|llseek
op_assign
id|dcache_dir_lseek
comma
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|dcache_readdir
comma
)brace
suffix:semicolon
DECL|variable|simple_dir_inode_operations
r_struct
id|inode_operations
id|simple_dir_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|simple_lookup
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Common helper for pseudo-filesystems (sockfs, pipefs, bdev - stuff that&n; * will never be mountable)&n; */
r_struct
id|super_block
op_star
DECL|function|get_sb_pseudo
id|get_sb_pseudo
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_char
op_star
id|name
comma
r_struct
id|super_operations
op_star
id|ops
comma
r_int
r_int
id|magic
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|sget
c_func
(paren
id|fs_type
comma
l_int|NULL
comma
id|set_anon_super
comma
l_int|NULL
)paren
suffix:semicolon
r_static
r_struct
id|super_operations
id|default_ops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
)brace
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|root
suffix:semicolon
r_struct
id|qstr
id|d_name
op_assign
(brace
dot
id|name
op_assign
id|name
comma
dot
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|s
)paren
)paren
r_return
id|s
suffix:semicolon
id|s-&gt;s_flags
op_assign
id|MS_NOUSER
suffix:semicolon
id|s-&gt;s_maxbytes
op_assign
op_complement
l_int|0ULL
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|magic
suffix:semicolon
id|s-&gt;s_op
op_assign
id|ops
ques
c_cond
id|ops
suffix:colon
op_amp
id|default_ops
suffix:semicolon
id|root
op_assign
id|new_inode
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
r_goto
id|Enomem
suffix:semicolon
id|root-&gt;i_mode
op_assign
id|S_IFDIR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
suffix:semicolon
id|root-&gt;i_uid
op_assign
id|root-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|root-&gt;i_atime
op_assign
id|root-&gt;i_mtime
op_assign
id|root-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dentry
op_assign
id|d_alloc
c_func
(paren
l_int|NULL
comma
op_amp
id|d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
(brace
id|iput
c_func
(paren
id|root
)paren
suffix:semicolon
r_goto
id|Enomem
suffix:semicolon
)brace
id|dentry-&gt;d_sb
op_assign
id|s
suffix:semicolon
id|dentry-&gt;d_parent
op_assign
id|dentry
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|root
)paren
suffix:semicolon
id|s-&gt;s_root
op_assign
id|dentry
suffix:semicolon
id|s-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
r_return
id|s
suffix:semicolon
id|Enomem
suffix:colon
id|up_write
c_func
(paren
op_amp
id|s-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
eof
