multiline_comment|/*&n; *  linux/fs/nfs/symlink.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  Optimization changes Copyright (C) 1994 Florian La Roche&n; *&n; *  Jun 7 1999, cache symlink lookups in the page cache.  -DaveM&n; *&n; *  nfs symlink handling code&n; */
DECL|macro|NFS_NEED_XDR_TYPES
mdefine_line|#define NFS_NEED_XDR_TYPES
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs2.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/* Symlink caching in the page cache is even more simplistic&n; * and straight-forward than readdir caching.&n; */
DECL|function|nfs_symlink_filler
r_static
r_int
id|nfs_symlink_filler
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_void
op_star
id|buffer
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* We place the length at the beginning of the page,&n;&t; * in host byte order, followed by the string.  The&n;&t; * XDR response verification will NULL terminate it.&n;&t; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|readlink
c_func
(paren
id|inode
comma
id|buffer
comma
id|PAGE_CACHE_SIZE
op_minus
r_sizeof
(paren
id|u32
)paren
op_minus
l_int|4
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|nfs_getlink
r_static
r_char
op_star
id|nfs_getlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
op_star
id|ppage
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
id|u32
op_star
id|p
suffix:semicolon
id|page
op_assign
id|ERR_PTR
c_func
(paren
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
r_goto
id|read_failed
suffix:semicolon
id|page
op_assign
id|read_cache_page
c_func
(paren
op_amp
id|inode-&gt;i_data
comma
l_int|0
comma
(paren
id|filler_t
op_star
)paren
id|nfs_symlink_filler
comma
id|inode
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
id|read_failed
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
id|getlink_read_error
suffix:semicolon
op_star
id|ppage
op_assign
id|page
suffix:semicolon
id|p
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
(paren
id|p
op_plus
l_int|1
)paren
suffix:semicolon
id|getlink_read_error
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|read_failed
suffix:colon
r_return
(paren
r_char
op_star
)paren
id|page
suffix:semicolon
)brace
DECL|function|nfs_readlink
r_static
r_int
id|nfs_readlink
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
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_int
id|res
op_assign
id|vfs_readlink
c_func
(paren
id|dentry
comma
id|buffer
comma
id|buflen
comma
id|nfs_getlink
c_func
(paren
id|inode
comma
op_amp
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
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
r_return
id|res
suffix:semicolon
)brace
DECL|function|nfs_follow_link
r_static
r_int
id|nfs_follow_link
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
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_int
id|res
op_assign
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|nfs_getlink
c_func
(paren
id|inode
comma
op_amp
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
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
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|nfs_symlink_inode_operations
r_struct
id|inode_operations
id|nfs_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|nfs_readlink
comma
id|follow_link
suffix:colon
id|nfs_follow_link
comma
id|getattr
suffix:colon
id|nfs_getattr
comma
id|setattr
suffix:colon
id|nfs_setattr
comma
)brace
suffix:semicolon
eof
