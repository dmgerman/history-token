multiline_comment|/*&n; * linux/fs/hfs/sysdep.c&n; *&n; * Copyright (C) 1996  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains the code to do various system dependent things.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
r_static
r_int
id|hfs_revalidate_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|hfs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_int
id|hfs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_static
r_void
id|hfs_dentry_iput
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|variable|hfs_dentry_operations
r_struct
id|dentry_operations
id|hfs_dentry_operations
op_assign
(brace
id|d_revalidate
suffix:colon
id|hfs_revalidate_dentry
comma
id|d_hash
suffix:colon
id|hfs_hash_dentry
comma
id|d_compare
suffix:colon
id|hfs_compare_dentry
comma
id|d_iput
suffix:colon
id|hfs_dentry_iput
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * hfs_buffer_get()&n; *&n; * Return a buffer for the &squot;block&squot;th block of the media.&n; * If (&squot;read&squot;==0) then the buffer is not read from disk.&n; */
DECL|function|hfs_buffer_get
id|hfs_buffer
id|hfs_buffer_get
c_func
(paren
id|hfs_sysmdb
id|sys_mdb
comma
r_int
id|block
comma
r_int
id|read
)paren
(brace
id|hfs_buffer
id|tmp
op_assign
id|HFS_BAD_BUFFER
suffix:semicolon
r_if
c_cond
(paren
id|read
)paren
(brace
id|tmp
op_assign
id|bread
c_func
(paren
id|sys_mdb-&gt;s_dev
comma
id|block
comma
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_assign
id|getblk
c_func
(paren
id|sys_mdb-&gt;s_dev
comma
id|block
comma
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
id|mark_buffer_uptodate
c_func
(paren
id|tmp
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|hfs_error
c_func
(paren
l_string|&quot;hfs_fs: unable to read block 0x%08x from dev %s&bslash;n&quot;
comma
id|block
comma
id|hfs_mdb_name
c_func
(paren
id|sys_mdb
)paren
)paren
suffix:semicolon
)brace
r_return
id|tmp
suffix:semicolon
)brace
multiline_comment|/* dentry case-handling: just lowercase everything */
multiline_comment|/* hfs_strhash now uses the same hashing function as the dcache. */
DECL|function|hfs_hash_dentry
r_static
r_int
id|hfs_hash_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|this
)paren
(brace
r_if
c_cond
(paren
id|this-&gt;len
OG
id|HFS_NAMELEN
)paren
r_return
l_int|0
suffix:semicolon
id|this-&gt;hash
op_assign
id|hfs_strhash
c_func
(paren
id|this-&gt;name
comma
id|this-&gt;len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* return 1 on failure and 0 on success */
DECL|function|hfs_compare_dentry
r_static
r_int
id|hfs_compare_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|qstr
op_star
id|a
comma
r_struct
id|qstr
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|a-&gt;len
op_ne
id|b-&gt;len
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;len
OG
id|HFS_NAMELEN
)paren
r_return
l_int|1
suffix:semicolon
r_return
op_logical_neg
id|hfs_streq
c_func
(paren
id|a-&gt;name
comma
id|a-&gt;len
comma
id|b-&gt;name
comma
id|b-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|hfs_dentry_iput
r_static
r_void
id|hfs_dentry_iput
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|hfs_cat_entry
op_star
id|entry
op_assign
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|entry
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|entry-&gt;sys_entry
(braket
id|HFS_ITYPE_TO_INT
c_func
(paren
id|HFS_ITYPE
c_func
(paren
id|inode-&gt;i_ino
)paren
)paren
)braket
op_assign
l_int|NULL
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|hfs_revalidate_dentry
r_static
r_int
id|hfs_revalidate_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|flags
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|diff
suffix:semicolon
multiline_comment|/* fix up inode on a timezone change */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_logical_and
(paren
id|diff
op_assign
(paren
id|hfs_to_utc
c_func
(paren
l_int|0
)paren
op_minus
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|tz_secondswest
)paren
)paren
)paren
(brace
id|inode-&gt;i_ctime
op_add_assign
id|diff
suffix:semicolon
id|inode-&gt;i_atime
op_add_assign
id|diff
suffix:semicolon
id|inode-&gt;i_mtime
op_add_assign
id|diff
suffix:semicolon
id|HFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|tz_secondswest
op_add_assign
id|diff
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
