multiline_comment|/*&n; * proc/fs/generic.c --- generic routines for the proc-fs&n; *&n; * This file contains generic proc-fs routines for handling&n; * directories and files.&n; * &n; * Copyright (C) 1991, 1992 Linus Torvalds.&n; * Copyright (C) 1997 Theodore Ts&squot;o&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
r_static
id|ssize_t
id|proc_file_read
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
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
id|ssize_t
id|proc_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
id|loff_t
id|proc_file_lseek
c_func
(paren
r_struct
id|file
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
DECL|function|proc_match
r_int
id|proc_match
c_func
(paren
r_int
id|len
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de
op_logical_or
op_logical_neg
id|de-&gt;low_ino
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;namelen
op_ne
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|de-&gt;name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|variable|proc_file_operations
r_static
r_struct
id|file_operations
id|proc_file_operations
op_assign
(brace
id|llseek
suffix:colon
id|proc_file_lseek
comma
id|read
suffix:colon
id|proc_file_read
comma
id|write
suffix:colon
id|proc_file_write
comma
)brace
suffix:semicolon
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
multiline_comment|/* buffer size is one page but our output routines use some slack for overruns */
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE&t;(PAGE_SIZE - 1024)
r_static
id|ssize_t
DECL|function|proc_file_read
id|proc_file_read
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
id|nbytes
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
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|eof
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|n
comma
id|count
suffix:semicolon
r_char
op_star
id|start
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
(paren
id|nbytes
OG
l_int|0
)paren
op_logical_and
op_logical_neg
id|eof
)paren
(brace
id|count
op_assign
id|MIN
c_func
(paren
id|PROC_BLOCK_SIZE
comma
id|nbytes
)paren
suffix:semicolon
id|start
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;get_info
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Handle backwards compatibility with the old net&n;&t;&t;&t; * routines.&n;&t;&t;&t; */
id|n
op_assign
id|dp
op_member_access_from_pointer
id|get_info
c_func
(paren
id|page
comma
op_amp
id|start
comma
op_star
id|ppos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|count
)paren
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dp-&gt;read_proc
)paren
(brace
id|n
op_assign
id|dp
op_member_access_from_pointer
id|read_proc
c_func
(paren
id|page
comma
op_amp
id|start
comma
op_star
id|ppos
comma
id|count
comma
op_amp
id|eof
comma
id|dp-&gt;data
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * For proc files that are less than 4k&n;&t;&t;&t; */
id|start
op_assign
id|page
op_plus
op_star
id|ppos
suffix:semicolon
id|n
op_sub_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|count
)paren
id|n
op_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* End of file */
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* This is a hack to allow mangling of file pos independent&n; &t;&t; * of actual bytes read.  Simply place the data at page,&n; &t;&t; * return the bytes, and set `start&squot; to the desired offset&n; &t;&t; * as an unsigned int. - Paul.Russell@rustcorp.com.au&n;&t;&t; */
id|n
op_sub_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|start
OL
id|page
ques
c_cond
id|page
suffix:colon
id|start
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|start
OL
id|page
ques
c_cond
(paren
r_int
)paren
id|start
suffix:colon
id|n
suffix:semicolon
multiline_comment|/* Move down the file */
id|nbytes
op_sub_assign
id|n
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
id|retval
op_add_assign
id|n
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|proc_file_write
id|proc_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
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
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dp-&gt;write_proc
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* FIXME: does this routine need ppos?  probably... */
r_return
id|dp
op_member_access_from_pointer
id|write_proc
c_func
(paren
id|file
comma
id|buffer
comma
id|count
comma
id|dp-&gt;data
)paren
suffix:semicolon
)brace
r_static
id|loff_t
DECL|function|proc_file_lseek
id|proc_file_lseek
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
id|orig
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|offset
op_plus
id|file-&gt;f_pos
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|2
suffix:colon
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * This function parses a name such as &quot;tty/driver/serial&quot;, and&n; * returns the struct proc_dir_entry for &quot;/proc/tty/driver&quot;, and&n; * returns &quot;serial&quot; in residual.&n; */
DECL|function|xlate_proc_name
r_static
r_int
id|xlate_proc_name
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
op_star
id|ret
comma
r_const
r_char
op_star
op_star
id|residual
)paren
(brace
r_const
r_char
op_star
id|cp
op_assign
id|name
comma
op_star
id|next
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|len
suffix:semicolon
id|de
op_assign
op_amp
id|proc_root
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|next
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
r_break
suffix:semicolon
id|len
op_assign
id|next
op_minus
id|cp
suffix:semicolon
r_for
c_loop
(paren
id|de
op_assign
id|de-&gt;subdir
suffix:semicolon
id|de
suffix:semicolon
id|de
op_assign
id|de-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|proc_match
c_func
(paren
id|len
comma
id|cp
comma
id|de
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|cp
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
)brace
op_star
id|residual
op_assign
id|cp
suffix:semicolon
op_star
id|ret
op_assign
id|de
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_alloc_map
r_static
r_int
r_int
id|proc_alloc_map
(braket
(paren
id|PROC_NDYNAMIC
op_plus
id|BITS_PER_LONG
op_minus
l_int|1
)paren
op_div
id|BITS_PER_LONG
)braket
suffix:semicolon
DECL|variable|proc_alloc_map_lock
id|spinlock_t
id|proc_alloc_map_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|make_inode_number
r_static
r_int
id|make_inode_number
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|proc_alloc_map_lock
)paren
suffix:semicolon
id|i
op_assign
id|find_first_zero_bit
c_func
(paren
id|proc_alloc_map
comma
id|PROC_NDYNAMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_or
id|i
op_ge
id|PROC_NDYNAMIC
)paren
(brace
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|i
comma
id|proc_alloc_map
)paren
suffix:semicolon
id|i
op_add_assign
id|PROC_DYNAMIC_FIRST
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|proc_alloc_map_lock
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|proc_readlink
r_static
r_int
id|proc_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_char
op_star
id|s
op_assign
id|PDE
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_return
id|vfs_readlink
c_func
(paren
id|dentry
comma
id|buffer
comma
id|buflen
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|proc_follow_link
r_static
r_int
id|proc_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_char
op_star
id|s
op_assign
id|PDE
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_return
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|s
)paren
suffix:semicolon
)brace
DECL|variable|proc_link_inode_operations
r_static
r_struct
id|inode_operations
id|proc_link_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|proc_readlink
comma
id|follow_link
suffix:colon
id|proc_follow_link
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * As some entries in /proc are volatile, we want to &n; * get rid of unused dentries.  This could be made &n; * smarter: we could keep a &quot;volatile&quot; flag in the &n; * inode to indicate which ones to keep.&n; */
DECL|function|proc_delete_dentry
r_static
r_int
id|proc_delete_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|proc_dentry_operations
r_static
r_struct
id|dentry_operations
id|proc_dentry_operations
op_assign
(brace
id|d_delete
suffix:colon
id|proc_delete_dentry
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t create negative dentries here, return -ENOENT by hand&n; * instead.&n; */
DECL|function|proc_lookup
r_struct
id|dentry
op_star
id|proc_lookup
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
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|de
op_assign
id|PDE
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
r_for
c_loop
(paren
id|de
op_assign
id|de-&gt;subdir
suffix:semicolon
id|de
suffix:semicolon
id|de
op_assign
id|de-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de
op_logical_or
op_logical_neg
id|de-&gt;low_ino
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;namelen
op_ne
id|dentry-&gt;d_name.len
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|de-&gt;name
comma
id|de-&gt;namelen
)paren
)paren
(brace
r_int
id|ino
op_assign
id|de-&gt;low_ino
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|inode
op_assign
id|proc_get_inode
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
comma
id|de
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|dentry-&gt;d_op
op_assign
op_amp
id|proc_dentry_operations
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
l_int|NULL
suffix:semicolon
)brace
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This returns non-zero if at EOF, so that the /proc&n; * root directory can use this and check if it should&n; * continue with the &lt;pid&gt; entries..&n; *&n; * Note that the VFS-layer doesn&squot;t care about the return&n; * value of the readdir() call, as long as it&squot;s non-negative&n; * for success..&n; */
DECL|function|proc_readdir
r_int
id|proc_readdir
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
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|de
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|1
suffix:colon
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
id|filp-&gt;f_dentry-&gt;d_parent-&gt;d_inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fall through */
r_default
suffix:colon
id|de
op_assign
id|de-&gt;subdir
suffix:semicolon
id|i
op_sub_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_break
suffix:semicolon
id|de
op_assign
id|de-&gt;next
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;name
comma
id|de-&gt;namelen
comma
id|filp-&gt;f_pos
comma
id|de-&gt;low_ino
comma
id|de-&gt;mode
op_rshift
l_int|12
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|de
op_assign
id|de-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|de
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the generic /proc directory operations. They&n; * use the in-memory &quot;struct proc_dir_entry&quot; tree to parse&n; * the /proc directory.&n; */
DECL|variable|proc_dir_operations
r_static
r_struct
id|file_operations
id|proc_dir_operations
op_assign
(brace
id|read
suffix:colon
id|generic_read_dir
comma
id|readdir
suffix:colon
id|proc_readdir
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * proc directories can do almost nothing..&n; */
DECL|variable|proc_dir_inode_operations
r_static
r_struct
id|inode_operations
id|proc_dir_inode_operations
op_assign
(brace
id|lookup
suffix:colon
id|proc_lookup
comma
)brace
suffix:semicolon
DECL|function|proc_register
r_static
r_int
id|proc_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dir
comma
r_struct
id|proc_dir_entry
op_star
id|dp
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|make_inode_number
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|dp-&gt;low_ino
op_assign
id|i
suffix:semicolon
id|dp-&gt;next
op_assign
id|dir-&gt;subdir
suffix:semicolon
id|dp-&gt;parent
op_assign
id|dir
suffix:semicolon
id|dir-&gt;subdir
op_assign
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|dp-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;proc_iops
op_eq
l_int|NULL
)paren
(brace
id|dp-&gt;proc_fops
op_assign
op_amp
id|proc_dir_operations
suffix:semicolon
id|dp-&gt;proc_iops
op_assign
op_amp
id|proc_dir_inode_operations
suffix:semicolon
)brace
id|dir-&gt;nlink
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|dp-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;proc_iops
op_eq
l_int|NULL
)paren
id|dp-&gt;proc_iops
op_assign
op_amp
id|proc_link_inode_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|dp-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;proc_fops
op_eq
l_int|NULL
)paren
id|dp-&gt;proc_fops
op_assign
op_amp
id|proc_file_operations
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Kill an inode that got unregistered..&n; */
DECL|function|proc_kill_inodes
r_static
r_void
id|proc_kill_inodes
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|proc_mnt-&gt;mnt_sb
suffix:semicolon
multiline_comment|/*&n;&t; * Actually it&squot;s a partial revoke().&n;&t; */
id|file_list_lock
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|sb-&gt;s_files.next
suffix:semicolon
id|p
op_ne
op_amp
id|sb-&gt;s_files
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|file
op_star
id|filp
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|file
comma
id|f_list
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_op
op_ne
op_amp
id|proc_dentry_operations
)paren
r_continue
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|PDE
c_func
(paren
id|inode
)paren
op_ne
id|de
)paren
r_continue
suffix:semicolon
id|fops
op_assign
id|filp-&gt;f_op
suffix:semicolon
id|filp-&gt;f_op
op_assign
l_int|NULL
suffix:semicolon
id|fops_put
c_func
(paren
id|fops
)paren
suffix:semicolon
)brace
id|file_list_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|proc_create
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_create
c_func
(paren
r_struct
id|proc_dir_entry
op_star
op_star
id|parent
comma
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
id|nlink_t
id|nlink
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|fn
op_assign
id|name
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* make sure name is valid */
r_if
c_cond
(paren
op_logical_neg
id|name
op_logical_or
op_logical_neg
id|strlen
c_func
(paren
id|name
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|parent
)paren
op_logical_and
id|xlate_proc_name
c_func
(paren
id|name
comma
id|parent
comma
op_amp
id|fn
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|fn
)paren
suffix:semicolon
id|ent
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|proc_dir_entry
)paren
op_plus
id|len
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|ent
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|proc_dir_entry
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
(paren
r_char
op_star
)paren
id|ent
)paren
op_plus
r_sizeof
(paren
r_struct
id|proc_dir_entry
)paren
comma
id|fn
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|ent-&gt;name
op_assign
(paren
(paren
r_char
op_star
)paren
id|ent
)paren
op_plus
r_sizeof
(paren
op_star
id|ent
)paren
suffix:semicolon
id|ent-&gt;namelen
op_assign
id|len
suffix:semicolon
id|ent-&gt;mode
op_assign
id|mode
suffix:semicolon
id|ent-&gt;nlink
op_assign
id|nlink
suffix:semicolon
id|out
suffix:colon
r_return
id|ent
suffix:semicolon
)brace
DECL|function|proc_symlink
r_struct
id|proc_dir_entry
op_star
id|proc_symlink
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|parent
comma
r_const
r_char
op_star
id|dest
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|proc_create
c_func
(paren
op_amp
id|parent
comma
id|name
comma
(paren
id|S_IFLNK
op_or
id|S_IRUGO
op_or
id|S_IWUGO
op_or
id|S_IXUGO
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;data
op_assign
id|kmalloc
c_func
(paren
(paren
id|ent-&gt;size
op_assign
id|strlen
c_func
(paren
id|dest
)paren
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent-&gt;data
)paren
(brace
id|strcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|ent-&gt;data
comma
id|dest
)paren
suffix:semicolon
id|proc_register
c_func
(paren
id|parent
comma
id|ent
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|ent
)paren
suffix:semicolon
id|ent
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|ent
suffix:semicolon
)brace
DECL|function|proc_mknod
r_struct
id|proc_dir_entry
op_star
id|proc_mknod
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
comma
id|kdev_t
id|rdev
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|proc_create
c_func
(paren
op_amp
id|parent
comma
id|name
comma
id|mode
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;rdev
op_assign
id|rdev
suffix:semicolon
id|proc_register
c_func
(paren
id|parent
comma
id|ent
)paren
suffix:semicolon
)brace
r_return
id|ent
suffix:semicolon
)brace
DECL|function|proc_mkdir
r_struct
id|proc_dir_entry
op_star
id|proc_mkdir
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|proc_create
c_func
(paren
op_amp
id|parent
comma
id|name
comma
(paren
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
)paren
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;proc_fops
op_assign
op_amp
id|proc_dir_operations
suffix:semicolon
id|ent-&gt;proc_iops
op_assign
op_amp
id|proc_dir_inode_operations
suffix:semicolon
id|proc_register
c_func
(paren
id|parent
comma
id|ent
)paren
suffix:semicolon
)brace
r_return
id|ent
suffix:semicolon
)brace
DECL|function|create_proc_entry
r_struct
id|proc_dir_entry
op_star
id|create_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|nlink_t
id|nlink
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|mode
op_amp
id|S_IALLUGO
)paren
op_eq
l_int|0
)paren
id|mode
op_or_assign
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
id|nlink
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|mode
op_amp
id|S_IFMT
)paren
op_eq
l_int|0
)paren
id|mode
op_or_assign
id|S_IFREG
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mode
op_amp
id|S_IALLUGO
)paren
op_eq
l_int|0
)paren
id|mode
op_or_assign
id|S_IRUGO
suffix:semicolon
id|nlink
op_assign
l_int|1
suffix:semicolon
)brace
id|ent
op_assign
id|proc_create
c_func
(paren
op_amp
id|parent
comma
id|name
comma
id|mode
comma
id|nlink
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
id|ent-&gt;proc_fops
op_assign
op_amp
id|proc_dir_operations
suffix:semicolon
id|ent-&gt;proc_iops
op_assign
op_amp
id|proc_dir_inode_operations
suffix:semicolon
)brace
id|proc_register
c_func
(paren
id|parent
comma
id|ent
)paren
suffix:semicolon
)brace
r_return
id|ent
suffix:semicolon
)brace
DECL|function|free_proc_entry
r_void
id|free_proc_entry
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
r_int
id|ino
op_assign
id|de-&gt;low_ino
suffix:semicolon
r_if
c_cond
(paren
id|ino
OL
id|PROC_DYNAMIC_FIRST
op_logical_or
id|ino
op_ge
id|PROC_DYNAMIC_FIRST
op_plus
id|PROC_NDYNAMIC
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|de-&gt;mode
)paren
op_logical_and
id|de-&gt;data
)paren
id|kfree
c_func
(paren
id|de-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a /proc entry and free it if it&squot;s not currently in use.&n; * If it is in use, we set the &squot;deleted&squot; flag.&n; */
DECL|function|remove_proc_entry
r_void
id|remove_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_struct
id|proc_dir_entry
op_star
op_star
id|p
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_const
r_char
op_star
id|fn
op_assign
id|name
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
op_logical_and
id|xlate_proc_name
c_func
(paren
id|name
comma
op_amp
id|parent
comma
op_amp
id|fn
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|fn
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|parent-&gt;subdir
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|proc_match
c_func
(paren
id|len
comma
id|fn
comma
op_star
id|p
)paren
)paren
r_continue
suffix:semicolon
id|de
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|de-&gt;next
suffix:semicolon
id|de-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|de-&gt;mode
)paren
)paren
id|parent-&gt;nlink
op_decrement
suffix:semicolon
id|clear_bit
c_func
(paren
id|de-&gt;low_ino
op_minus
id|PROC_DYNAMIC_FIRST
comma
id|proc_alloc_map
)paren
suffix:semicolon
id|proc_kill_inodes
c_func
(paren
id|de
)paren
suffix:semicolon
id|de-&gt;nlink
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|de-&gt;count
)paren
)paren
id|free_proc_entry
c_func
(paren
id|de
)paren
suffix:semicolon
r_else
(brace
id|de-&gt;deleted
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;remove_proc_entry: %s/%s busy, count=%d&bslash;n&quot;
comma
id|parent-&gt;name
comma
id|de-&gt;name
comma
id|atomic_read
c_func
(paren
op_amp
id|de-&gt;count
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_return
suffix:semicolon
)brace
eof
