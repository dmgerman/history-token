multiline_comment|/*&n; *  linux/fs/minix/dir.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  minix directory handling functions&n; */
macro_line|#include &quot;minix.h&quot;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|typedef|minix_dirent
r_typedef
r_struct
id|minix_dir_entry
id|minix_dirent
suffix:semicolon
r_static
r_int
id|minix_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
DECL|variable|minix_dir_operations
r_struct
id|file_operations
id|minix_dir_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|minix_readdir
comma
dot
id|fsync
op_assign
id|minix_sync_file
comma
)brace
suffix:semicolon
DECL|function|dir_put_page
r_static
r_inline
r_void
id|dir_put_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the offset into page `page_nr&squot; of the last valid&n; * byte in that page, plus one.&n; */
r_static
r_int
DECL|function|minix_last_byte
id|minix_last_byte
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|page_nr
)paren
(brace
r_int
id|last_byte
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|page_nr
op_eq
(paren
id|inode-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
)paren
)paren
id|last_byte
op_assign
id|inode-&gt;i_size
op_amp
(paren
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|last_byte
suffix:semicolon
)brace
DECL|function|dir_pages
r_static
r_inline
r_int
r_int
id|dir_pages
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
id|inode-&gt;i_size
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
)brace
DECL|function|dir_commit_chunk
r_static
r_int
id|dir_commit_chunk
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|commit_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_DIRSYNC
c_func
(paren
id|dir
)paren
)paren
id|err
op_assign
id|write_one_page
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
r_else
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|dir_get_page
r_static
r_struct
id|page
op_star
id|dir_get_page
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|dir-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|n
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
id|fail
suffix:colon
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
DECL|function|minix_next_entry
r_static
r_inline
r_void
op_star
id|minix_next_entry
c_func
(paren
r_void
op_star
id|de
comma
r_struct
id|minix_sb_info
op_star
id|sbi
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|sbi-&gt;s_dirsize
)paren
suffix:semicolon
)brace
DECL|function|minix_readdir
r_static
r_int
id|minix_readdir
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
r_int
r_int
id|pos
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|offset
op_assign
id|pos
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_int
r_int
id|n
op_assign
id|pos
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
r_int
id|npages
op_assign
id|dir_pages
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|chunk_size
op_assign
id|sbi-&gt;s_dirsize
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|pos
op_assign
(paren
id|pos
op_plus
id|chunk_size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|chunk_size
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|inode-&gt;i_size
)paren
r_goto
id|done
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
OL
id|npages
suffix:semicolon
id|n
op_increment
comma
id|offset
op_assign
l_int|0
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|kaddr
comma
op_star
id|limit
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|dir_get_page
c_func
(paren
id|inode
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|kaddr
op_assign
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|p
op_assign
id|kaddr
op_plus
id|offset
suffix:semicolon
id|limit
op_assign
id|kaddr
op_plus
id|minix_last_byte
c_func
(paren
id|inode
comma
id|n
)paren
op_minus
id|chunk_size
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|p
op_le
id|limit
suffix:semicolon
id|p
op_assign
id|minix_next_entry
c_func
(paren
id|p
comma
id|sbi
)paren
)paren
(brace
id|minix_dirent
op_star
id|de
op_assign
(paren
id|minix_dirent
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
r_int
id|over
suffix:semicolon
r_int
id|l
op_assign
id|strnlen
c_func
(paren
id|de-&gt;name
comma
id|sbi-&gt;s_namelen
)paren
suffix:semicolon
id|offset
op_assign
id|p
op_minus
id|kaddr
suffix:semicolon
id|over
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;name
comma
id|l
comma
(paren
id|n
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_or
id|offset
comma
id|de-&gt;inode
comma
id|DT_UNKNOWN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|over
)paren
(brace
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
)brace
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|filp-&gt;f_pos
op_assign
(paren
id|n
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_or
id|offset
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|namecompare
r_static
r_inline
r_int
id|namecompare
c_func
(paren
r_int
id|len
comma
r_int
id|maxlen
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|len
OL
id|maxlen
op_logical_and
id|buffer
(braket
id|len
)braket
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
id|buffer
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;minix_find_entry()&n; *&n; * finds an entry in the specified directory with the wanted name. It&n; * returns the cache buffer in which the entry was found, and the entry&n; * itself (as a parameter - res_dir). It does NOT read the inode of the&n; * entry - you&squot;ll have to do that yourself if you want to.&n; */
DECL|function|minix_find_entry
id|minix_dirent
op_star
id|minix_find_entry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|page
op_star
op_star
id|res_page
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_int
r_int
id|npages
op_assign
id|dir_pages
c_func
(paren
id|dir
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
suffix:semicolon
op_star
id|res_page
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|npages
suffix:semicolon
id|n
op_increment
)paren
(brace
r_char
op_star
id|kaddr
suffix:semicolon
id|page
op_assign
id|dir_get_page
c_func
(paren
id|dir
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|kaddr
op_assign
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|minix_dir_entry
op_star
)paren
id|kaddr
suffix:semicolon
id|kaddr
op_add_assign
id|minix_last_byte
c_func
(paren
id|dir
comma
id|n
)paren
op_minus
id|sbi-&gt;s_dirsize
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
r_char
op_star
)paren
id|de
op_le
id|kaddr
suffix:semicolon
id|de
op_assign
id|minix_next_entry
c_func
(paren
id|de
comma
id|sbi
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|namecompare
c_func
(paren
id|namelen
comma
id|sbi-&gt;s_namelen
comma
id|name
comma
id|de-&gt;name
)paren
)paren
r_goto
id|found
suffix:semicolon
)brace
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
id|found
suffix:colon
op_star
id|res_page
op_assign
id|page
suffix:semicolon
r_return
id|de
suffix:semicolon
)brace
DECL|function|minix_add_link
r_int
id|minix_add_link
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
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
suffix:semicolon
r_int
r_int
id|npages
op_assign
id|dir_pages
c_func
(paren
id|dir
)paren
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_char
op_star
id|kaddr
suffix:semicolon
r_int
id|from
comma
id|to
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * We take care of directory expansion in the same loop&n;&t; * This code plays outside i_size, so it locks the page&n;&t; * to protect that region.&n;&t; */
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
op_le
id|npages
suffix:semicolon
id|n
op_increment
)paren
(brace
r_char
op_star
id|dir_end
suffix:semicolon
id|page
op_assign
id|dir_get_page
c_func
(paren
id|dir
comma
id|n
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_goto
id|out
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kaddr
op_assign
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|dir_end
op_assign
id|kaddr
op_plus
id|minix_last_byte
c_func
(paren
id|dir
comma
id|n
)paren
suffix:semicolon
id|de
op_assign
(paren
id|minix_dirent
op_star
)paren
id|kaddr
suffix:semicolon
id|kaddr
op_add_assign
id|PAGE_CACHE_SIZE
op_minus
id|sbi-&gt;s_dirsize
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
op_le
id|kaddr
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|de
op_eq
id|dir_end
)paren
(brace
multiline_comment|/* We hit i_size */
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
r_goto
id|got_it
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
)paren
r_goto
id|got_it
suffix:semicolon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|namecompare
c_func
(paren
id|namelen
comma
id|sbi-&gt;s_namelen
comma
id|name
comma
id|de-&gt;name
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|de
op_assign
id|minix_next_entry
c_func
(paren
id|de
comma
id|sbi
)paren
suffix:semicolon
)brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
id|got_it
suffix:colon
id|from
op_assign
(paren
r_char
op_star
)paren
id|de
op_minus
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|to
op_assign
id|from
op_plus
id|sbi-&gt;s_dirsize
suffix:semicolon
id|err
op_assign
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_unlock
suffix:semicolon
id|memcpy
(paren
id|de-&gt;name
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|memset
(paren
id|de-&gt;name
op_plus
id|namelen
comma
l_int|0
comma
id|sbi-&gt;s_dirsize
op_minus
id|namelen
op_minus
l_int|2
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|err
op_assign
id|dir_commit_chunk
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
id|out_put
suffix:colon
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_unlock
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out_put
suffix:semicolon
)brace
DECL|function|minix_delete_entry
r_int
id|minix_delete_entry
c_func
(paren
r_struct
id|minix_dir_entry
op_star
id|de
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|mapping-&gt;host
suffix:semicolon
r_char
op_star
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|from
op_assign
(paren
r_char
op_star
)paren
id|de
op_minus
id|kaddr
suffix:semicolon
r_int
id|to
op_assign
id|from
op_plus
id|minix_sb
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|s_dirsize
suffix:semicolon
r_int
id|err
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|dir_commit_chunk
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
)brace
r_else
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|minix_make_empty
r_int
id|minix_make_empty
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
l_int|0
)paren
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
suffix:semicolon
r_char
op_star
id|kaddr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
l_int|0
comma
l_int|2
op_star
id|sbi-&gt;s_dirsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|minix_dir_entry
op_star
)paren
id|kaddr
suffix:semicolon
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|strcpy
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|de
op_assign
id|minix_next_entry
c_func
(paren
id|de
comma
id|sbi
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|dir-&gt;i_ino
suffix:semicolon
id|strcpy
c_func
(paren
id|de-&gt;name
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|err
op_assign
id|dir_commit_chunk
c_func
(paren
id|page
comma
l_int|0
comma
l_int|2
op_star
id|sbi-&gt;s_dirsize
)paren
suffix:semicolon
id|fail
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * routine to check that the specified directory is empty (for rmdir)&n; */
DECL|function|minix_empty_dir
r_int
id|minix_empty_dir
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|i
comma
id|npages
op_assign
id|dir_pages
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|npages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|kaddr
suffix:semicolon
id|minix_dirent
op_star
id|de
suffix:semicolon
id|page
op_assign
id|dir_get_page
c_func
(paren
id|inode
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|kaddr
op_assign
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|de
op_assign
(paren
id|minix_dirent
op_star
)paren
id|kaddr
suffix:semicolon
id|kaddr
op_add_assign
id|minix_last_byte
c_func
(paren
id|inode
comma
id|i
)paren
op_minus
id|sbi-&gt;s_dirsize
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
op_le
id|kaddr
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;inode
op_ne
l_int|0
)paren
(brace
multiline_comment|/* check for . and .. */
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_goto
id|not_empty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;name
(braket
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;inode
op_ne
id|inode-&gt;i_ino
)paren
r_goto
id|not_empty
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|1
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_goto
id|not_empty
suffix:semicolon
r_else
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|2
)braket
)paren
r_goto
id|not_empty
suffix:semicolon
)brace
id|de
op_assign
id|minix_next_entry
c_func
(paren
id|de
comma
id|sbi
)paren
suffix:semicolon
)brace
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
id|not_empty
suffix:colon
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Releases the page */
DECL|function|minix_set_link
r_void
id|minix_set_link
c_func
(paren
r_struct
id|minix_dir_entry
op_star
id|de
comma
r_struct
id|page
op_star
id|page
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_int
id|from
op_assign
(paren
r_char
op_star
)paren
id|de
op_minus
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|to
op_assign
id|from
op_plus
id|sbi-&gt;s_dirsize
suffix:semicolon
r_int
id|err
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
id|de-&gt;inode
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|err
op_assign
id|dir_commit_chunk
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
)brace
r_else
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
DECL|function|minix_dotdot
r_struct
id|minix_dir_entry
op_star
id|minix_dotdot
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|page
op_star
op_star
id|p
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|dir_get_page
c_func
(paren
id|dir
comma
l_int|0
)paren
suffix:semicolon
r_struct
id|minix_sb_info
op_star
id|sbi
op_assign
id|minix_sb
c_func
(paren
id|dir-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|de
op_assign
id|minix_next_entry
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
comma
id|sbi
)paren
suffix:semicolon
op_star
id|p
op_assign
id|page
suffix:semicolon
)brace
r_return
id|de
suffix:semicolon
)brace
DECL|function|minix_inode_by_name
id|ino_t
id|minix_inode_by_name
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_struct
id|minix_dir_entry
op_star
id|de
op_assign
id|minix_find_entry
c_func
(paren
id|dentry
comma
op_amp
id|page
)paren
suffix:semicolon
id|ino_t
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
id|res
op_assign
id|de-&gt;inode
suffix:semicolon
id|dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
eof
