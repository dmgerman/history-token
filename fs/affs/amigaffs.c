multiline_comment|/*&n; *  linux/fs/affs/amigaffs.c&n; *&n; *  (c) 1996  Hans-Joachim Widmaier - Rewritten&n; *&n; *  (C) 1993  Ray Burr - Amiga FFS filesystem.&n; *&n; *  Please send bug reports to: hjw@zvw.de&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
DECL|variable|ErrorBuffer
r_static
r_char
id|ErrorBuffer
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/*&n; * Functions for accessing Amiga-FFS structures.&n; */
multiline_comment|/* Insert a header block bh into the directory dir&n; * caller must hold AFFS_DIR-&gt;i_hash_lock!&n; */
r_int
DECL|function|affs_insert_hash
id|affs_insert_hash
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|dir_bh
suffix:semicolon
id|u32
id|ino
comma
id|hash_ino
suffix:semicolon
r_int
id|offset
suffix:semicolon
id|ino
op_assign
id|bh-&gt;b_blocknr
suffix:semicolon
id|offset
op_assign
id|affs_hash_name
c_func
(paren
id|sb
comma
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|name
op_plus
l_int|1
comma
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|name
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: insert_hash(dir=%u, ino=%d)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|dir-&gt;i_ino
comma
id|ino
)paren
suffix:semicolon
id|dir_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|hash_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_HEAD
c_func
(paren
id|dir_bh
)paren
op_member_access_from_pointer
id|table
(braket
id|offset
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|hash_ino
)paren
(brace
id|affs_brelse
c_func
(paren
id|dir_bh
)paren
suffix:semicolon
id|dir_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|hash_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir_bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|hash_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|dir_bh
)paren
op_member_access_from_pointer
id|hash_chain
)paren
suffix:semicolon
)brace
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|parent
op_assign
id|cpu_to_be32
c_func
(paren
id|dir-&gt;i_ino
)paren
suffix:semicolon
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|hash_chain
op_assign
l_int|0
suffix:semicolon
id|affs_fix_checksum
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|dir_bh-&gt;b_blocknr
)paren
id|AFFS_HEAD
c_func
(paren
id|dir_bh
)paren
op_member_access_from_pointer
id|table
(braket
id|offset
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|ino
)paren
suffix:semicolon
r_else
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|dir_bh
)paren
op_member_access_from_pointer
id|hash_chain
op_assign
id|cpu_to_be32
c_func
(paren
id|ino
)paren
suffix:semicolon
id|affs_adjust_checksum
c_func
(paren
id|dir_bh
comma
id|ino
)paren
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|dir_bh
comma
id|dir
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|dir_bh
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_version
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Remove a header block from its directory.&n; * caller must hold AFFS_DIR-&gt;i_hash_lock!&n; */
r_int
DECL|function|affs_remove_hash
id|affs_remove_hash
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|buffer_head
op_star
id|rem_bh
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|u32
id|rem_ino
comma
id|hash_ino
suffix:semicolon
id|__be32
id|ino
suffix:semicolon
r_int
id|offset
comma
id|retval
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|rem_ino
op_assign
id|rem_bh-&gt;b_blocknr
suffix:semicolon
id|offset
op_assign
id|affs_hash_name
c_func
(paren
id|sb
comma
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|rem_bh
)paren
op_member_access_from_pointer
id|name
op_plus
l_int|1
comma
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|rem_bh
)paren
op_member_access_from_pointer
id|name
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: remove_hash(dir=%d, ino=%d, hashval=%d)&bslash;n&quot;
comma
(paren
id|u32
)paren
id|dir-&gt;i_ino
comma
id|rem_ino
comma
id|offset
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|hash_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_HEAD
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|table
(braket
id|offset
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|hash_ino
)paren
(brace
r_if
c_cond
(paren
id|hash_ino
op_eq
id|rem_ino
)paren
(brace
id|ino
op_assign
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|rem_bh
)paren
op_member_access_from_pointer
id|hash_chain
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_ino
op_eq
id|bh-&gt;b_blocknr
)paren
id|AFFS_HEAD
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|table
(braket
id|offset
)braket
op_assign
id|ino
suffix:semicolon
r_else
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|hash_chain
op_assign
id|ino
suffix:semicolon
id|affs_adjust_checksum
c_func
(paren
id|bh
comma
id|be32_to_cpu
c_func
(paren
id|ino
)paren
op_minus
id|hash_ino
)paren
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|dir
)paren
suffix:semicolon
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|rem_bh
)paren
op_member_access_from_pointer
id|parent
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|hash_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|hash_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|hash_chain
)paren
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dir-&gt;i_version
op_increment
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_void
DECL|function|affs_fix_dcache
id|affs_fix_dcache
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|u32
id|entry_ino
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_void
op_star
id|data
op_assign
id|dentry-&gt;d_fsdata
suffix:semicolon
r_struct
id|list_head
op_star
id|head
comma
op_star
id|next
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|inode-&gt;i_dentry
suffix:semicolon
id|next
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
id|head
)paren
(brace
id|dentry
op_assign
id|list_entry
c_func
(paren
id|next
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry_ino
op_eq
(paren
id|u32
)paren
(paren
r_int
)paren
id|dentry-&gt;d_fsdata
)paren
(brace
id|dentry-&gt;d_fsdata
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
)brace
id|next
op_assign
id|next-&gt;next
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
multiline_comment|/* Remove header from link chain */
r_static
r_int
DECL|function|affs_remove_link
id|affs_remove_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|dir
comma
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
comma
op_star
id|link_bh
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|link_ino
comma
id|ino
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: remove_link(key=%ld)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|done
suffix:semicolon
id|link_ino
op_assign
(paren
id|u32
)paren
(paren
r_int
)paren
id|dentry-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|link_ino
)paren
(brace
multiline_comment|/* we can&squot;t remove the head of the link, as its blocknr is still used as ino,&n;&t;&t; * so we remove the block of the first link instead.&n;&t;&t; */
id|link_ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|link_chain
)paren
suffix:semicolon
id|link_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|link_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link_bh
)paren
r_goto
id|done
suffix:semicolon
id|dir
op_assign
id|iget
c_func
(paren
id|sb
comma
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|link_bh
)paren
op_member_access_from_pointer
id|parent
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_goto
id|done
suffix:semicolon
id|affs_lock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|affs_fix_dcache
c_func
(paren
id|dentry
comma
id|link_ino
)paren
suffix:semicolon
id|retval
op_assign
id|affs_remove_hash
c_func
(paren
id|dir
comma
id|link_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|done
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|link_bh
comma
id|inode
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|name
comma
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|link_bh
)paren
op_member_access_from_pointer
id|name
comma
l_int|32
)paren
suffix:semicolon
id|retval
op_assign
id|affs_insert_hash
c_func
(paren
id|dir
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|done
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|inode
)paren
suffix:semicolon
id|affs_unlock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_else
(brace
id|link_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|link_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link_bh
)paren
r_goto
id|done
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|ino
op_assign
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|link_chain
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ino
op_eq
id|link_ino
)paren
(brace
id|__be32
id|ino2
op_assign
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|link_bh
)paren
op_member_access_from_pointer
id|link_chain
suffix:semicolon
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|link_chain
op_assign
id|ino2
suffix:semicolon
id|affs_adjust_checksum
c_func
(paren
id|bh
comma
id|be32_to_cpu
c_func
(paren
id|ino2
)paren
op_minus
id|link_ino
)paren
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|inode
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Fix the link count, if bh is a normal header block without links */
r_switch
c_cond
(paren
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|stype
)paren
)paren
(brace
r_case
id|ST_LINKDIR
suffix:colon
r_case
id|ST_LINKFILE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|link_chain
)paren
id|inode-&gt;i_nlink
op_assign
l_int|1
suffix:semicolon
)brace
id|affs_free_block
c_func
(paren
id|sb
comma
id|link_ino
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|done
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|done
suffix:colon
id|affs_brelse
c_func
(paren
id|link_bh
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_empty_dir
id|affs_empty_dir
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|retval
comma
id|size
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|done
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOTEMPTY
suffix:semicolon
r_for
c_loop
(paren
id|size
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_hashsize
op_minus
l_int|1
suffix:semicolon
id|size
op_ge
l_int|0
suffix:semicolon
id|size
op_decrement
)paren
r_if
c_cond
(paren
id|AFFS_HEAD
c_func
(paren
id|bh
)paren
op_member_access_from_pointer
id|table
(braket
id|size
)braket
)paren
r_goto
id|not_empty
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|not_empty
suffix:colon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|done
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Remove a filesystem object. If the object to be removed has&n; * links to it, one of the links must be changed to inherit&n; * the file or directory. As above, any inode will do.&n; * The buffer will not be freed. If the header is a link, the&n; * block will be marked as free.&n; * This function returns a negative error number in case of&n; * an error, else 0 if the inode is to be deleted or 1 if not.&n; */
r_int
DECL|function|affs_remove_header
id|affs_remove_header
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
comma
op_star
id|dir
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|done
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: remove_header(key=%ld)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
(paren
id|u32
)paren
(paren
r_int
)paren
id|dentry-&gt;d_fsdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|done
suffix:semicolon
id|affs_lock_link
c_func
(paren
id|inode
)paren
suffix:semicolon
id|affs_lock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|be32_to_cpu
c_func
(paren
id|AFFS_TAIL
c_func
(paren
id|sb
comma
id|bh
)paren
op_member_access_from_pointer
id|stype
)paren
)paren
(brace
r_case
id|ST_USERDIR
suffix:colon
multiline_comment|/* if we ever want to support links to dirs&n;&t;&t; * i_hash_lock of the inode must only be&n;&t;&t; * taken after some checks&n;&t;&t; */
id|affs_lock_dir
c_func
(paren
id|inode
)paren
suffix:semicolon
id|retval
op_assign
id|affs_empty_dir
c_func
(paren
id|inode
)paren
suffix:semicolon
id|affs_unlock_dir
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|done_unlock
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|retval
op_assign
id|affs_remove_hash
c_func
(paren
id|dir
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|done_unlock
suffix:semicolon
id|mark_buffer_dirty_inode
c_func
(paren
id|bh
comma
id|inode
)paren
suffix:semicolon
id|affs_unlock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_nlink
OG
l_int|1
)paren
id|retval
op_assign
id|affs_remove_link
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_else
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
id|affs_unlock_link
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|done
suffix:colon
id|affs_brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|done_unlock
suffix:colon
id|affs_unlock_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|affs_unlock_link
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Checksum a block, do various consistency checks and optionally return&n;   the blocks type number.  DATA points to the block.  If their pointers&n;   are non-null, *PTYPE and *STYPE are set to the primary and secondary&n;   block types respectively, *HASHSIZE is set to the size of the hashtable&n;   (which lets us calculate the block size).&n;   Returns non-zero if the block is not consistent. */
id|u32
DECL|function|affs_checksum_block
id|affs_checksum_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|__be32
op_star
id|ptr
op_assign
(paren
id|__be32
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|u32
id|sum
suffix:semicolon
r_int
id|bsize
suffix:semicolon
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|bsize
op_assign
id|sb-&gt;s_blocksize
op_div
r_sizeof
(paren
id|__be32
)paren
suffix:semicolon
id|bsize
OG
l_int|0
suffix:semicolon
id|bsize
op_decrement
)paren
id|sum
op_add_assign
id|be32_to_cpu
c_func
(paren
op_star
id|ptr
op_increment
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * Calculate the checksum of a disk block and store it&n; * at the indicated position.&n; */
r_void
DECL|function|affs_fix_checksum
id|affs_fix_checksum
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
id|cnt
op_assign
id|sb-&gt;s_blocksize
op_div
r_sizeof
(paren
id|__be32
)paren
suffix:semicolon
id|__be32
op_star
id|ptr
op_assign
(paren
id|__be32
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|u32
id|checksum
suffix:semicolon
id|__be32
op_star
id|checksumptr
suffix:semicolon
id|checksumptr
op_assign
id|ptr
op_plus
l_int|5
suffix:semicolon
op_star
id|checksumptr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|checksum
op_assign
l_int|0
suffix:semicolon
id|cnt
OG
l_int|0
suffix:semicolon
id|ptr
op_increment
comma
id|cnt
op_decrement
)paren
id|checksum
op_add_assign
id|be32_to_cpu
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
op_star
id|checksumptr
op_assign
id|cpu_to_be32
c_func
(paren
op_minus
id|checksum
)paren
suffix:semicolon
)brace
r_void
DECL|function|secs_to_datestamp
id|secs_to_datestamp
c_func
(paren
id|time_t
id|secs
comma
r_struct
id|affs_date
op_star
id|ds
)paren
(brace
id|u32
id|days
suffix:semicolon
id|u32
id|minute
suffix:semicolon
id|secs
op_sub_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
op_plus
(paren
(paren
l_int|8
op_star
l_int|365
op_plus
l_int|2
)paren
op_star
l_int|24
op_star
l_int|60
op_star
l_int|60
)paren
suffix:semicolon
r_if
c_cond
(paren
id|secs
OL
l_int|0
)paren
id|secs
op_assign
l_int|0
suffix:semicolon
id|days
op_assign
id|secs
op_div
l_int|86400
suffix:semicolon
id|secs
op_sub_assign
id|days
op_star
l_int|86400
suffix:semicolon
id|minute
op_assign
id|secs
op_div
l_int|60
suffix:semicolon
id|secs
op_sub_assign
id|minute
op_star
l_int|60
suffix:semicolon
id|ds-&gt;days
op_assign
id|cpu_to_be32
c_func
(paren
id|days
)paren
suffix:semicolon
id|ds-&gt;mins
op_assign
id|cpu_to_be32
c_func
(paren
id|minute
)paren
suffix:semicolon
id|ds-&gt;ticks
op_assign
id|cpu_to_be32
c_func
(paren
id|secs
op_star
l_int|50
)paren
suffix:semicolon
)brace
id|mode_t
DECL|function|prot_to_mode
id|prot_to_mode
c_func
(paren
id|u32
id|prot
)paren
(brace
r_int
id|mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|prot
op_amp
id|FIBF_NOWRITE
)paren
)paren
id|mode
op_or_assign
id|S_IWUSR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|prot
op_amp
id|FIBF_NOREAD
)paren
)paren
id|mode
op_or_assign
id|S_IRUSR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|prot
op_amp
id|FIBF_NOEXECUTE
)paren
)paren
id|mode
op_or_assign
id|S_IXUSR
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
id|FIBF_GRP_WRITE
)paren
id|mode
op_or_assign
id|S_IWGRP
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
id|FIBF_GRP_READ
)paren
id|mode
op_or_assign
id|S_IRGRP
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
id|FIBF_GRP_EXECUTE
)paren
id|mode
op_or_assign
id|S_IXGRP
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
id|FIBF_OTR_WRITE
)paren
id|mode
op_or_assign
id|S_IWOTH
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
id|FIBF_OTR_READ
)paren
id|mode
op_or_assign
id|S_IROTH
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
id|FIBF_OTR_EXECUTE
)paren
id|mode
op_or_assign
id|S_IXOTH
suffix:semicolon
r_return
id|mode
suffix:semicolon
)brace
r_void
DECL|function|mode_to_prot
id|mode_to_prot
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|u32
id|prot
op_assign
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_protect
suffix:semicolon
id|mode_t
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|S_IXUSR
)paren
)paren
id|prot
op_or_assign
id|FIBF_NOEXECUTE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|S_IRUSR
)paren
)paren
id|prot
op_or_assign
id|FIBF_NOREAD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|S_IWUSR
)paren
)paren
id|prot
op_or_assign
id|FIBF_NOWRITE
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IXGRP
)paren
id|prot
op_or_assign
id|FIBF_GRP_EXECUTE
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IRGRP
)paren
id|prot
op_or_assign
id|FIBF_GRP_READ
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IWGRP
)paren
id|prot
op_or_assign
id|FIBF_GRP_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IXOTH
)paren
id|prot
op_or_assign
id|FIBF_OTR_EXECUTE
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IROTH
)paren
id|prot
op_or_assign
id|FIBF_OTR_READ
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_IWOTH
)paren
id|prot
op_or_assign
id|FIBF_OTR_WRITE
suffix:semicolon
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_protect
op_assign
id|prot
suffix:semicolon
)brace
r_void
DECL|function|affs_error
id|affs_error
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|ErrorBuffer
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;AFFS error (device %s): %s(): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|function
comma
id|ErrorBuffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AFFS: Remounting filesystem read-only&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
r_void
DECL|function|affs_warning
id|affs_warning
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|ErrorBuffer
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;AFFS warning (device %s): %s(): %s&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|function
comma
id|ErrorBuffer
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if the name is valid for a affs object. */
r_int
DECL|function|affs_check_name
id|affs_check_name
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|30
)paren
macro_line|#ifdef AFFS_NO_TRUNCATE
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
macro_line|#else
id|len
op_assign
l_int|30
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|name
(braket
id|i
)braket
OL
l_char|&squot; &squot;
op_logical_or
id|name
(braket
id|i
)braket
op_eq
l_char|&squot;:&squot;
op_logical_or
(paren
id|name
(braket
id|i
)braket
OG
l_int|0x7e
op_logical_and
id|name
(braket
id|i
)braket
OL
l_int|0xa0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This function copies name to bstr, with at most 30&n; * characters length. The bstr will be prepended by&n; * a length byte.&n; * NOTE: The name will must be already checked by&n; *       affs_check_name()!&n; */
r_int
DECL|function|affs_copy_name
id|affs_copy_name
c_func
(paren
r_int
r_char
op_star
id|bstr
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_int
id|len
op_assign
id|min
c_func
(paren
id|dentry-&gt;d_name.len
comma
l_int|30u
)paren
suffix:semicolon
op_star
id|bstr
op_increment
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|bstr
comma
id|dentry-&gt;d_name.name
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
