multiline_comment|/* dir.c: AFS filesystem directory handling&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;vnode.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &quot;super.h&quot;
macro_line|#include &quot;internal.h&quot;
r_static
r_struct
id|dentry
op_star
id|afs_dir_lookup
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
comma
r_struct
id|nameidata
op_star
id|nd
)paren
suffix:semicolon
r_static
r_int
id|afs_dir_open
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
suffix:semicolon
r_static
r_int
id|afs_dir_readdir
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
suffix:semicolon
r_static
r_int
id|afs_d_revalidate
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
suffix:semicolon
r_static
r_int
id|afs_d_delete
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_static
r_int
id|afs_dir_lookup_filldir
c_func
(paren
r_void
op_star
id|_cookie
comma
r_const
r_char
op_star
id|name
comma
r_int
id|nlen
comma
id|loff_t
id|fpos
comma
id|ino_t
id|ino
comma
r_int
id|dtype
)paren
suffix:semicolon
DECL|variable|afs_dir_file_operations
r_struct
id|file_operations
id|afs_dir_file_operations
op_assign
(brace
dot
id|open
op_assign
id|afs_dir_open
comma
dot
id|readdir
op_assign
id|afs_dir_readdir
comma
)brace
suffix:semicolon
DECL|variable|afs_dir_inode_operations
r_struct
id|inode_operations
id|afs_dir_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|afs_dir_lookup
comma
dot
id|getattr
op_assign
id|afs_inode_getattr
comma
macro_line|#if 0 /* TODO */
dot
id|create
op_assign
id|afs_dir_create
comma
dot
id|link
op_assign
id|afs_dir_link
comma
dot
id|unlink
op_assign
id|afs_dir_unlink
comma
dot
id|symlink
op_assign
id|afs_dir_symlink
comma
dot
id|mkdir
op_assign
id|afs_dir_mkdir
comma
dot
id|rmdir
op_assign
id|afs_dir_rmdir
comma
dot
id|mknod
op_assign
id|afs_dir_mknod
comma
dot
id|rename
op_assign
id|afs_dir_rename
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|afs_fs_dentry_operations
r_static
r_struct
id|dentry_operations
id|afs_fs_dentry_operations
op_assign
(brace
dot
id|d_revalidate
op_assign
id|afs_d_revalidate
comma
dot
id|d_delete
op_assign
id|afs_d_delete
comma
)brace
suffix:semicolon
DECL|macro|AFS_DIR_HASHTBL_SIZE
mdefine_line|#define AFS_DIR_HASHTBL_SIZE&t;128
DECL|macro|AFS_DIR_DIRENT_SIZE
mdefine_line|#define AFS_DIR_DIRENT_SIZE&t;32
DECL|macro|AFS_DIRENT_PER_BLOCK
mdefine_line|#define AFS_DIRENT_PER_BLOCK&t;64
DECL|union|afs_dirent
r_union
id|afs_dirent
(brace
r_struct
(brace
DECL|member|valid
r_uint8
id|valid
suffix:semicolon
DECL|member|unused
r_uint8
id|unused
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|hash_next
r_uint16
id|hash_next
suffix:semicolon
DECL|member|vnode
r_uint32
id|vnode
suffix:semicolon
DECL|member|unique
r_uint32
id|unique
suffix:semicolon
DECL|member|name
r_uint8
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|overflow
r_uint8
id|overflow
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* if any char of the name (inc&n;&t;&t;&t;&t;&t;&t; * NUL) reaches here, consume&n;&t;&t;&t;&t;&t;&t; * the next dirent too */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|extended_name
r_uint8
id|extended_name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* AFS directory page header (one at the beginning of every 2048-byte chunk) */
DECL|struct|afs_dir_pagehdr
r_struct
id|afs_dir_pagehdr
(brace
DECL|member|npages
r_uint16
id|npages
suffix:semicolon
DECL|member|magic
r_uint16
id|magic
suffix:semicolon
DECL|macro|AFS_DIR_MAGIC
mdefine_line|#define AFS_DIR_MAGIC htons(1234)
DECL|member|nentries
r_uint8
id|nentries
suffix:semicolon
DECL|member|bitmap
r_uint8
id|bitmap
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pad
r_uint8
id|pad
(braket
l_int|19
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* directory block layout */
DECL|union|afs_dir_block
r_union
id|afs_dir_block
(brace
DECL|member|pagehdr
r_struct
id|afs_dir_pagehdr
id|pagehdr
suffix:semicolon
r_struct
(brace
DECL|member|pagehdr
r_struct
id|afs_dir_pagehdr
id|pagehdr
suffix:semicolon
DECL|member|alloc_ctrs
r_uint8
id|alloc_ctrs
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* dir hash table */
DECL|member|hashtable
r_uint16
id|hashtable
(braket
id|AFS_DIR_HASHTBL_SIZE
)braket
suffix:semicolon
DECL|member|hdr
)brace
id|hdr
suffix:semicolon
DECL|member|dirents
r_union
id|afs_dirent
id|dirents
(braket
id|AFS_DIRENT_PER_BLOCK
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* layout on a linux VM page */
DECL|struct|afs_dir_page
r_struct
id|afs_dir_page
(brace
DECL|member|blocks
r_union
id|afs_dir_block
id|blocks
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|afs_dir_lookup_cookie
r_struct
id|afs_dir_lookup_cookie
(brace
DECL|member|fid
r_struct
id|afs_fid
id|fid
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|nlen
r_int
id|nlen
suffix:semicolon
DECL|member|found
r_int
id|found
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * check that a directory page is valid&n; */
DECL|function|afs_dir_check_page
r_static
r_inline
r_void
id|afs_dir_check_page
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|afs_dir_page
op_star
id|dbuf
suffix:semicolon
id|loff_t
id|latter
suffix:semicolon
r_int
id|tmp
comma
id|qty
suffix:semicolon
macro_line|#if 0
multiline_comment|/* check the page count */
id|qty
op_assign
id|desc.size
op_div
r_sizeof
(paren
id|dbuf-&gt;blocks
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|qty
op_eq
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
op_eq
l_int|0
op_logical_and
id|qty
op_ne
id|ntohs
c_func
(paren
id|dbuf-&gt;blocks
(braket
l_int|0
)braket
dot
id|pagehdr.npages
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: %s(%lu): wrong number of dir blocks %d!=%hu&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dir-&gt;i_ino
comma
id|qty
comma
id|ntohs
c_func
(paren
id|dbuf-&gt;blocks
(braket
l_int|0
)braket
dot
id|pagehdr.npages
)paren
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* determine how many magic numbers there should be in this page */
id|latter
op_assign
id|dir-&gt;i_size
op_minus
(paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|latter
op_ge
id|PAGE_SIZE
)paren
id|qty
op_assign
id|PAGE_SIZE
suffix:semicolon
r_else
id|qty
op_assign
id|latter
suffix:semicolon
id|qty
op_div_assign
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
suffix:semicolon
multiline_comment|/* check them */
id|dbuf
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|qty
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dbuf-&gt;blocks
(braket
id|tmp
)braket
dot
id|pagehdr.magic
op_ne
id|AFS_DIR_MAGIC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: %s(%lu): bad magic %d/%d is %04hx&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dir-&gt;i_ino
comma
id|tmp
comma
id|qty
comma
id|ntohs
c_func
(paren
id|dbuf-&gt;blocks
(braket
id|tmp
)braket
dot
id|pagehdr.magic
)paren
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
id|SetPageChecked
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
id|error
suffix:colon
id|SetPageChecked
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_check_page() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * discard a page cached in the pagecache&n; */
DECL|function|afs_dir_put_page
r_static
r_inline
r_void
id|afs_dir_put_page
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
multiline_comment|/* end afs_dir_put_page() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * get a page into the pagecache&n; */
DECL|function|afs_dir_get_page
r_static
r_struct
id|page
op_star
id|afs_dir_get_page
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
r_int
id|index
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%lu},%lu&quot;
comma
id|dir-&gt;i_ino
comma
id|index
)paren
suffix:semicolon
id|page
op_assign
id|read_cache_page
c_func
(paren
id|dir-&gt;i_mapping
comma
id|index
comma
(paren
id|filler_t
op_star
)paren
id|dir-&gt;i_mapping-&gt;a_ops-&gt;readpage
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
r_if
c_cond
(paren
op_logical_neg
id|PageChecked
c_func
(paren
id|page
)paren
)paren
id|afs_dir_check_page
c_func
(paren
id|dir
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageError
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
id|afs_dir_put_page
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
multiline_comment|/* end afs_dir_get_page() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * open an AFS directory file&n; */
DECL|function|afs_dir_open
r_static
r_int
id|afs_dir_open
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
id|_enter
c_func
(paren
l_string|&quot;{%lu}&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
op_ne
l_int|2048
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
r_sizeof
(paren
r_union
id|afs_dirent
)paren
op_ne
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_amp
id|AFS_VNODE_DELETED
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_open() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * deal with one block in an AFS directory&n; */
DECL|function|afs_dir_iterate_block
r_static
r_int
id|afs_dir_iterate_block
c_func
(paren
r_int
op_star
id|fpos
comma
r_union
id|afs_dir_block
op_star
id|block
comma
r_int
id|blkoff
comma
r_void
op_star
id|cookie
comma
id|filldir_t
id|filldir
)paren
(brace
r_union
id|afs_dirent
op_star
id|dire
suffix:semicolon
r_int
id|offset
comma
id|next
comma
id|curr
suffix:semicolon
r_int
id|nlen
suffix:semicolon
r_int
id|tmp
comma
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%u,%x,%p,,&quot;
comma
op_star
id|fpos
comma
id|blkoff
comma
id|block
)paren
suffix:semicolon
id|curr
op_assign
(paren
op_star
id|fpos
op_minus
id|blkoff
)paren
op_div
r_sizeof
(paren
r_union
id|afs_dirent
)paren
suffix:semicolon
multiline_comment|/* walk through the block, an entry at a time */
r_for
c_loop
(paren
id|offset
op_assign
id|AFS_DIRENT_PER_BLOCK
op_minus
id|block-&gt;pagehdr.nentries
suffix:semicolon
id|offset
OL
id|AFS_DIRENT_PER_BLOCK
suffix:semicolon
id|offset
op_assign
id|next
)paren
(brace
id|next
op_assign
id|offset
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* skip entries marked unused in the bitmap */
r_if
c_cond
(paren
op_logical_neg
(paren
id|block-&gt;pagehdr.bitmap
(braket
id|offset
op_div
l_int|8
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|offset
op_mod
l_int|8
)paren
)paren
)paren
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;ENT[%Zu.%u]: unused&bslash;n&quot;
comma
id|blkoff
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|curr
)paren
op_star
id|fpos
op_assign
id|blkoff
op_plus
id|next
op_star
r_sizeof
(paren
r_union
id|afs_dirent
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* got a valid entry */
id|dire
op_assign
op_amp
id|block-&gt;dirents
(braket
id|offset
)braket
suffix:semicolon
id|nlen
op_assign
id|strnlen
c_func
(paren
id|dire-&gt;u.name
comma
r_sizeof
(paren
op_star
id|block
)paren
op_minus
id|offset
op_star
r_sizeof
(paren
r_union
id|afs_dirent
)paren
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;ENT[%Zu.%u]: %s %Zu &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|blkoff
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
comma
id|offset
comma
(paren
id|offset
OL
id|curr
ques
c_cond
l_string|&quot;skip&quot;
suffix:colon
l_string|&quot;fill&quot;
)paren
comma
id|nlen
comma
id|dire-&gt;u.name
)paren
suffix:semicolon
multiline_comment|/* work out where the next possible entry is */
r_for
c_loop
(paren
id|tmp
op_assign
id|nlen
suffix:semicolon
id|tmp
OG
l_int|15
suffix:semicolon
id|tmp
op_sub_assign
r_sizeof
(paren
r_union
id|afs_dirent
)paren
)paren
(brace
r_if
c_cond
(paren
id|next
op_ge
id|AFS_DIRENT_PER_BLOCK
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;ENT[%Zu.%u]:&quot;
l_string|&quot; %u travelled beyond end dir block&quot;
l_string|&quot; (len %u/%Zu)&bslash;n&quot;
comma
id|blkoff
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
comma
id|offset
comma
id|next
comma
id|tmp
comma
id|nlen
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|block-&gt;pagehdr.bitmap
(braket
id|next
op_div
l_int|8
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|next
op_mod
l_int|8
)paren
)paren
)paren
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;ENT[%Zu.%u]:&quot;
l_string|&quot; %u unmarked extension (len %u/%Zu)&bslash;n&quot;
comma
id|blkoff
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
comma
id|offset
comma
id|next
comma
id|tmp
comma
id|nlen
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|_debug
c_func
(paren
l_string|&quot;ENT[%Zu.%u]: ext %u/%Zu&bslash;n&quot;
comma
id|blkoff
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
comma
id|next
comma
id|tmp
comma
id|nlen
)paren
suffix:semicolon
id|next
op_increment
suffix:semicolon
)brace
multiline_comment|/* skip if starts before the current position */
r_if
c_cond
(paren
id|offset
OL
id|curr
)paren
r_continue
suffix:semicolon
multiline_comment|/* found the next entry */
id|ret
op_assign
id|filldir
c_func
(paren
id|cookie
comma
id|dire-&gt;u.name
comma
id|nlen
comma
id|blkoff
op_plus
id|offset
op_star
r_sizeof
(paren
r_union
id|afs_dirent
)paren
comma
id|ntohl
c_func
(paren
id|dire-&gt;u.vnode
)paren
comma
id|filldir
op_eq
id|afs_dir_lookup_filldir
ques
c_cond
id|dire-&gt;u.unique
suffix:colon
id|DT_UNKNOWN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = 0 [full]&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|fpos
op_assign
id|blkoff
op_plus
id|next
op_star
r_sizeof
(paren
r_union
id|afs_dirent
)paren
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot; = 1 [more]&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_iterate_block() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * read an AFS directory&n; */
DECL|function|afs_dir_iterate
r_static
r_int
id|afs_dir_iterate
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
op_star
id|fpos
comma
r_void
op_star
id|cookie
comma
id|filldir_t
id|filldir
)paren
(brace
r_union
id|afs_dir_block
op_star
id|dblock
suffix:semicolon
r_struct
id|afs_dir_page
op_star
id|dbuf
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|blkoff
comma
id|limit
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%lu},%u,,&quot;
comma
id|dir-&gt;i_ino
comma
op_star
id|fpos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|flags
op_amp
id|AFS_VNODE_DELETED
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ESTALE&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ESTALE
suffix:semicolon
)brace
multiline_comment|/* round the file position up to the next entry boundary */
op_star
id|fpos
op_add_assign
r_sizeof
(paren
r_union
id|afs_dirent
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|fpos
op_and_assign
op_complement
(paren
r_sizeof
(paren
r_union
id|afs_dirent
)paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* walk through the blocks in sequence */
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|fpos
OL
id|dir-&gt;i_size
)paren
(brace
id|blkoff
op_assign
op_star
id|fpos
op_amp
op_complement
(paren
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* fetch the appropriate page from the directory */
id|page
op_assign
id|afs_dir_get_page
c_func
(paren
id|dir
comma
id|blkoff
op_div
id|PAGE_SIZE
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
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|limit
op_assign
id|blkoff
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dbuf
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* deal with the individual blocks stashed on this page */
r_do
(brace
id|dblock
op_assign
op_amp
id|dbuf-&gt;blocks
(braket
(paren
id|blkoff
op_mod
id|PAGE_SIZE
)paren
op_div
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
)braket
suffix:semicolon
id|ret
op_assign
id|afs_dir_iterate_block
c_func
(paren
id|fpos
comma
id|dblock
comma
id|blkoff
comma
id|cookie
comma
id|filldir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
(brace
id|afs_dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|blkoff
op_add_assign
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|fpos
OL
id|dir-&gt;i_size
op_logical_and
id|blkoff
OL
id|limit
)paren
suffix:semicolon
id|afs_dir_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_iterate() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * read an AFS directory&n; */
DECL|function|afs_dir_readdir
r_static
r_int
id|afs_dir_readdir
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|cookie
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|fpos
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%Ld,{%lu}}&quot;
comma
id|file-&gt;f_pos
comma
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
id|fpos
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|ret
op_assign
id|afs_dir_iterate
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
comma
op_amp
id|fpos
comma
id|cookie
comma
id|filldir
)paren
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|fpos
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_readdir() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * search the directory for a name&n; * - if afs_dir_iterate_block() spots this function, it&squot;ll pass the FID&n; *   uniquifier through dtype&n; */
DECL|function|afs_dir_lookup_filldir
r_static
r_int
id|afs_dir_lookup_filldir
c_func
(paren
r_void
op_star
id|_cookie
comma
r_const
r_char
op_star
id|name
comma
r_int
id|nlen
comma
id|loff_t
id|fpos
comma
id|ino_t
id|ino
comma
r_int
id|dtype
)paren
(brace
r_struct
id|afs_dir_lookup_cookie
op_star
id|cookie
op_assign
id|_cookie
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%s,%Zu},%s,%u,,%lu,%u&quot;
comma
id|cookie-&gt;name
comma
id|cookie-&gt;nlen
comma
id|name
comma
id|nlen
comma
id|ino
comma
id|ntohl
c_func
(paren
id|dtype
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cookie-&gt;nlen
op_ne
id|nlen
op_logical_or
id|memcmp
c_func
(paren
id|cookie-&gt;name
comma
id|name
comma
id|nlen
)paren
op_ne
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = 0 [no]&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cookie-&gt;fid.vnode
op_assign
id|ino
suffix:semicolon
id|cookie-&gt;fid.unique
op_assign
id|ntohl
c_func
(paren
id|dtype
)paren
suffix:semicolon
id|cookie-&gt;found
op_assign
l_int|1
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = -1 [found]&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_lookup_filldir() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * look up an entry in a directory&n; */
DECL|function|afs_dir_lookup
r_static
r_struct
id|dentry
op_star
id|afs_dir_lookup
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
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_struct
id|afs_dir_lookup_cookie
id|cookie
suffix:semicolon
r_struct
id|afs_super_info
op_star
id|as
suffix:semicolon
r_struct
id|afs_vnode
op_star
id|vnode
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|fpos
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%lu},%p{%s}&quot;
comma
id|dir-&gt;i_ino
comma
id|dentry
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* insanity checks first */
id|BUG_ON
c_func
(paren
r_sizeof
(paren
r_union
id|afs_dir_block
)paren
op_ne
l_int|2048
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
r_sizeof
(paren
r_union
id|afs_dirent
)paren
op_ne
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
OG
l_int|255
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ENAMETOOLONG&quot;
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENAMETOOLONG
)paren
suffix:semicolon
)brace
id|vnode
op_assign
id|AFS_FS_I
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vnode-&gt;flags
op_amp
id|AFS_VNODE_DELETED
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ESTALE&quot;
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ESTALE
)paren
suffix:semicolon
)brace
id|as
op_assign
id|dir-&gt;i_sb-&gt;s_fs_info
suffix:semicolon
multiline_comment|/* search the directory */
id|cookie.name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
id|cookie.nlen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|cookie.fid.vid
op_assign
id|as-&gt;volume-&gt;vid
suffix:semicolon
id|cookie.found
op_assign
l_int|0
suffix:semicolon
id|fpos
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|afs_dir_iterate
c_func
(paren
id|dir
comma
op_amp
id|fpos
comma
op_amp
id|cookie
comma
id|afs_dir_lookup_filldir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cookie.found
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* instantiate the dentry */
id|ret
op_assign
id|afs_iget
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|cookie.fid
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
id|dentry-&gt;d_op
op_assign
op_amp
id|afs_fs_dentry_operations
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|vnode-&gt;status.version
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 { vn=%u u=%u } -&gt; { ino=%lu v=%lu }&quot;
comma
id|cookie.fid.vnode
comma
id|cookie.fid.unique
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|dentry-&gt;d_inode-&gt;i_version
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* end afs_dir_lookup() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * check that a dentry lookup hit has found a valid entry&n; * - NOTE! the hit can be a negative hit too, so we can&squot;t assume we have an&n; *   inode&n; * (derived from nfs_lookup_revalidate)&n; */
DECL|function|afs_d_revalidate
r_static
r_int
id|afs_d_revalidate
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
r_struct
id|afs_dir_lookup_cookie
id|cookie
suffix:semicolon
r_struct
id|dentry
op_star
id|parent
suffix:semicolon
r_struct
id|inode
op_star
id|inode
comma
op_star
id|dir
suffix:semicolon
r_int
id|fpos
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{sb=%p n=%s},&quot;
comma
id|dentry-&gt;d_sb
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
multiline_comment|/* lock down the parent dentry so we can peer at it */
id|parent
op_assign
id|dget_parent
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
id|dir
op_assign
id|parent-&gt;d_inode
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* handle a negative dentry */
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out_bad
suffix:semicolon
multiline_comment|/* handle a bad inode */
r_if
c_cond
(paren
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: afs_d_revalidate: %s/%s has bad inode&bslash;n&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out_bad
suffix:semicolon
)brace
multiline_comment|/* force a full look up if the parent directory changed since last the&n;&t; * server was consulted&n;&t; * - otherwise this inode must still exist, even if the inode details&n;&t; *   themselves have changed&n;&t; */
r_if
c_cond
(paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|flags
op_amp
id|AFS_VNODE_CHANGED
)paren
id|afs_vnode_fetch_status
c_func
(paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|flags
op_amp
id|AFS_VNODE_DELETED
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;%s: parent dir deleted&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out_bad
suffix:semicolon
)brace
r_if
c_cond
(paren
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_amp
id|AFS_VNODE_DELETED
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;%s: file already deleted&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|out_bad
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|dentry-&gt;d_fsdata
op_ne
(paren
r_int
r_int
)paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|status.version
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;%s: parent changed %lu -&gt; %u&quot;
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
r_int
)paren
id|dentry-&gt;d_fsdata
comma
(paren
r_int
)paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|status.version
)paren
suffix:semicolon
multiline_comment|/* search the directory for this vnode */
id|cookie.name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
id|cookie.nlen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|cookie.fid.vid
op_assign
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volume-&gt;vid
suffix:semicolon
id|cookie.found
op_assign
l_int|0
suffix:semicolon
id|fpos
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|afs_dir_iterate
c_func
(paren
id|dir
comma
op_amp
id|fpos
comma
op_amp
id|cookie
comma
id|afs_dir_lookup_filldir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;failed to iterate dir %s: %d&quot;
comma
id|parent-&gt;d_name.name
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_bad
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cookie.found
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;%s: dirent not found&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
)brace
multiline_comment|/* if the vnode ID has changed, then the dirent points to a&n;&t;&t; * different file */
r_if
c_cond
(paren
id|cookie.fid.vnode
op_ne
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fid.vnode
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;%s: dirent changed&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_goto
id|not_found
suffix:semicolon
)brace
multiline_comment|/* if the vnode ID uniqifier has changed, then the file has&n;&t;&t; * been deleted */
r_if
c_cond
(paren
id|cookie.fid.unique
op_ne
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fid.unique
)paren
(brace
id|_debug
c_func
(paren
l_string|&quot;%s: file deleted (uq %u -&gt; %u I:%lu)&quot;
comma
id|dentry-&gt;d_name.name
comma
id|cookie.fid.unique
comma
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|fid.unique
comma
id|inode-&gt;i_version
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|AFS_VNODE_DELETED
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|AFS_FS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
id|invalidate_remote_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_goto
id|out_bad
suffix:semicolon
)brace
id|dentry-&gt;d_fsdata
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|AFS_FS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|status.version
suffix:semicolon
)brace
id|out_valid
suffix:colon
id|dput
c_func
(paren
id|parent
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 1 [valid]&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* the dirent, if it exists, now points to a different vnode */
id|not_found
suffix:colon
id|dentry-&gt;d_flags
op_or_assign
id|DCACHE_NFSFS_RENAMED
suffix:semicolon
id|out_bad
suffix:colon
r_if
c_cond
(paren
id|inode
)paren
(brace
multiline_comment|/* don&squot;t unhash if we have submounts */
r_if
c_cond
(paren
id|have_submounts
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out_valid
suffix:semicolon
)brace
id|shrink_dcache_parent
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|_debug
c_func
(paren
l_string|&quot;dropping dentry %s/%s&quot;
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
id|d_drop
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|parent
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = 0 [bad]&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_d_revalidate() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * allow the VFS to enquire as to whether a dentry should be unhashed (mustn&squot;t&n; * sleep)&n; * - called from dput() when d_count is going to 0.&n; * - return 1 to request dentry be unhashed, 0 otherwise&n; */
DECL|function|afs_d_delete
r_static
r_int
id|afs_d_delete
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;%s&quot;
comma
id|dentry-&gt;d_name.name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_NFSFS_RENAMED
)paren
r_goto
id|zap
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|AFS_FS_I
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_member_access_from_pointer
id|flags
op_amp
id|AFS_VNODE_DELETED
)paren
r_goto
id|zap
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot; = 0 [keep]&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|zap
suffix:colon
id|_leave
c_func
(paren
l_string|&quot; = 1 [zap]&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* end afs_d_delete() */
eof
