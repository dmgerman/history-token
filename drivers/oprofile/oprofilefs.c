multiline_comment|/**&n; * @file oprofilefs.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon&n; *&n; * A simple filesystem for configuration and&n; * access of oprofile.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;oprof.h&quot;
DECL|macro|OPROFILEFS_MAGIC
mdefine_line|#define OPROFILEFS_MAGIC 0x6f70726f
DECL|variable|oprofilefs_lock
id|spinlock_t
id|oprofilefs_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|oprofilefs_get_inode
r_static
r_struct
id|inode
op_star
id|oprofilefs_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|variable|s_ops
r_static
r_struct
id|super_operations
id|s_ops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
comma
dot
id|drop_inode
op_assign
id|generic_delete_inode
comma
)brace
suffix:semicolon
DECL|function|oprofilefs_str_to_user
id|ssize_t
id|oprofilefs_str_to_user
c_func
(paren
r_char
r_const
op_star
id|str
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
OG
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|len
op_minus
op_star
id|offset
)paren
id|count
op_assign
id|len
op_minus
op_star
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|str
op_plus
op_star
id|offset
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|offset
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|macro|TMPBUFSIZE
mdefine_line|#define TMPBUFSIZE 50
DECL|function|oprofilefs_ulong_to_user
id|ssize_t
id|oprofilefs_ulong_to_user
c_func
(paren
r_int
r_int
op_star
id|val
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_char
id|tmpbuf
(braket
id|TMPBUFSIZE
)braket
suffix:semicolon
r_int
id|maxlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
id|maxlen
op_assign
id|snprintf
c_func
(paren
id|tmpbuf
comma
id|TMPBUFSIZE
comma
l_string|&quot;%lu&bslash;n&quot;
comma
op_star
id|val
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxlen
OG
id|TMPBUFSIZE
)paren
id|maxlen
op_assign
id|TMPBUFSIZE
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
OG
id|maxlen
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|maxlen
op_minus
op_star
id|offset
)paren
id|count
op_assign
id|maxlen
op_minus
op_star
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|tmpbuf
op_plus
op_star
id|offset
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|offset
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|oprofilefs_ulong_from_user
r_int
id|oprofilefs_ulong_from_user
c_func
(paren
r_int
r_int
op_star
id|val
comma
r_char
r_const
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_char
id|tmpbuf
(braket
id|TMPBUFSIZE
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|TMPBUFSIZE
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memset
c_func
(paren
id|tmpbuf
comma
l_int|0x0
comma
id|TMPBUFSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|tmpbuf
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
op_star
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|tmpbuf
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ulong_read_file
r_static
id|ssize_t
id|ulong_read_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_return
id|oprofilefs_ulong_to_user
c_func
(paren
id|file-&gt;private_data
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|ulong_write_file
r_static
id|ssize_t
id|ulong_write_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
r_const
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
r_int
r_int
op_star
id|value
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_star
id|offset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|retval
op_assign
id|oprofilefs_ulong_from_user
c_func
(paren
id|value
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|default_open
r_static
r_int
id|default_open
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
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;u.generic_ip
)paren
id|filp-&gt;private_data
op_assign
id|inode-&gt;u.generic_ip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ulong_fops
r_static
r_struct
id|file_operations
id|ulong_fops
op_assign
(brace
dot
id|read
op_assign
id|ulong_read_file
comma
dot
id|write
op_assign
id|ulong_write_file
comma
dot
id|open
op_assign
id|default_open
comma
)brace
suffix:semicolon
DECL|variable|ulong_ro_fops
r_static
r_struct
id|file_operations
id|ulong_ro_fops
op_assign
(brace
dot
id|read
op_assign
id|ulong_read_file
comma
dot
id|open
op_assign
id|default_open
comma
)brace
suffix:semicolon
DECL|function|__oprofilefs_create_file
r_static
r_struct
id|dentry
op_star
id|__oprofilefs_create_file
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|qstr
id|qname
suffix:semicolon
id|qname.name
op_assign
id|name
suffix:semicolon
id|qname.len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|qname.hash
op_assign
id|full_name_hash
c_func
(paren
id|qname.name
comma
id|qname.len
)paren
suffix:semicolon
id|dentry
op_assign
id|d_alloc
c_func
(paren
id|root
comma
op_amp
id|qname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_return
l_int|0
suffix:semicolon
id|inode
op_assign
id|oprofilefs_get_inode
c_func
(paren
id|sb
comma
id|S_IFREG
op_or
l_int|0644
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|inode-&gt;i_fop
op_assign
id|fops
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
id|dentry
suffix:semicolon
)brace
DECL|function|oprofilefs_create_ulong
r_int
id|oprofilefs_create_ulong
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_struct
id|dentry
op_star
id|d
op_assign
id|__oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
id|name
comma
op_amp
id|ulong_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|d-&gt;d_inode-&gt;u.generic_ip
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|oprofilefs_create_ro_ulong
r_int
id|oprofilefs_create_ro_ulong
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_struct
id|dentry
op_star
id|d
op_assign
id|__oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
id|name
comma
op_amp
id|ulong_ro_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|d-&gt;d_inode-&gt;u.generic_ip
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_read_file
r_static
id|ssize_t
id|atomic_read_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|atomic_t
op_star
id|aval
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|val
op_assign
id|atomic_read
c_func
(paren
id|aval
)paren
suffix:semicolon
r_return
id|oprofilefs_ulong_to_user
c_func
(paren
op_amp
id|val
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|variable|atomic_ro_fops
r_static
r_struct
id|file_operations
id|atomic_ro_fops
op_assign
(brace
dot
id|read
op_assign
id|atomic_read_file
comma
dot
id|open
op_assign
id|default_open
comma
)brace
suffix:semicolon
DECL|function|oprofilefs_create_ro_atomic
r_int
id|oprofilefs_create_ro_atomic
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
id|atomic_t
op_star
id|val
)paren
(brace
r_struct
id|dentry
op_star
id|d
op_assign
id|__oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
id|name
comma
op_amp
id|atomic_ro_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|d-&gt;d_inode-&gt;u.generic_ip
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|oprofilefs_create_file
r_int
id|oprofilefs_create_file
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|__oprofilefs_create_file
c_func
(paren
id|sb
comma
id|root
comma
id|name
comma
id|fops
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|oprofilefs_mkdir
r_struct
id|dentry
op_star
id|oprofilefs_mkdir
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
comma
r_char
r_const
op_star
id|name
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|qstr
id|qname
suffix:semicolon
id|qname.name
op_assign
id|name
suffix:semicolon
id|qname.len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|qname.hash
op_assign
id|full_name_hash
c_func
(paren
id|qname.name
comma
id|qname.len
)paren
suffix:semicolon
id|dentry
op_assign
id|d_alloc
c_func
(paren
id|root
comma
op_amp
id|qname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_return
l_int|0
suffix:semicolon
id|inode
op_assign
id|oprofilefs_get_inode
c_func
(paren
id|sb
comma
id|S_IFDIR
op_or
l_int|0755
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
op_amp
id|simple_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
r_return
id|dentry
suffix:semicolon
)brace
DECL|function|oprofilefs_fill_super
r_static
r_int
id|oprofilefs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_struct
id|dentry
op_star
id|root_dentry
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|OPROFILEFS_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|s_ops
suffix:semicolon
id|root_inode
op_assign
id|oprofilefs_get_inode
c_func
(paren
id|sb
comma
id|S_IFDIR
op_or
l_int|0755
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|root_inode-&gt;i_op
op_assign
op_amp
id|simple_dir_inode_operations
suffix:semicolon
id|root_inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
id|root_dentry
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_dentry
)paren
(brace
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sb-&gt;s_root
op_assign
id|root_dentry
suffix:semicolon
id|oprofile_create_files
c_func
(paren
id|sb
comma
id|root_dentry
)paren
suffix:semicolon
singleline_comment|// FIXME: verify kill_litter_super removes our dentries
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|oprofilefs_get_sb
r_static
r_struct
id|super_block
op_star
id|oprofilefs_get_sb
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
(brace
r_return
id|get_sb_single
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|oprofilefs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|oprofilefs_type
r_static
r_struct
id|file_system_type
id|oprofilefs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;oprofilefs&quot;
comma
dot
id|get_sb
op_assign
id|oprofilefs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|function|oprofilefs_register
r_int
id|__init
id|oprofilefs_register
c_func
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|oprofilefs_type
)paren
suffix:semicolon
)brace
DECL|function|oprofilefs_unregister
r_void
id|__exit
id|oprofilefs_unregister
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|oprofilefs_type
)paren
suffix:semicolon
)brace
eof
