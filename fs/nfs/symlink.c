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
macro_line|#include &lt;linux/namei.h&gt;
multiline_comment|/* Symlink caching in the page cache is even more simplistic&n; * and straight-forward than readdir caching.&n; *&n; * At the beginning of the page we store pointer to struct page in question,&n; * simplifying nfs_put_link() (if inode got invalidated we can&squot;t find the page&n; * to be freed via pagecache lookup).&n; * The NUL-terminated string follows immediately thereafter.&n; */
DECL|struct|nfs_symlink
r_struct
id|nfs_symlink
(brace
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|body
r_char
id|body
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
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
r_const
r_int
r_int
id|pgbase
op_assign
m_offsetof
(paren
r_struct
id|nfs_symlink
comma
id|body
)paren
suffix:semicolon
r_const
r_int
r_int
id|pglen
op_assign
id|PAGE_SIZE
op_minus
id|pgbase
suffix:semicolon
r_int
id|error
suffix:semicolon
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
id|page
comma
id|pgbase
comma
id|pglen
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
suffix:semicolon
r_struct
id|nfs_symlink
op_star
id|p
suffix:semicolon
r_void
op_star
id|err
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
id|err
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
(brace
id|err
op_assign
id|page
suffix:semicolon
r_goto
id|read_failed
suffix:semicolon
)brace
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
(brace
id|err
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
r_goto
id|getlink_read_error
suffix:semicolon
)brace
id|p
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|p-&gt;page
op_assign
id|page
suffix:semicolon
id|nd_set_link
c_func
(paren
id|nd
comma
id|p-&gt;body
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|getlink_read_error
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|read_failed
suffix:colon
id|nd_set_link
c_func
(paren
id|nd
comma
id|err
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nfs_put_link
r_static
r_void
id|nfs_put_link
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
id|nd_get_link
c_func
(paren
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|s
)paren
)paren
(brace
r_struct
id|nfs_symlink
op_star
id|p
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|p
op_assign
id|container_of
c_func
(paren
id|s
comma
r_struct
id|nfs_symlink
comma
id|body
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|page
op_assign
id|p-&gt;page
suffix:semicolon
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
)brace
multiline_comment|/*&n; * symlinks can&squot;t do much...&n; */
DECL|variable|nfs_symlink_inode_operations
r_struct
id|inode_operations
id|nfs_symlink_inode_operations
op_assign
(brace
dot
id|readlink
op_assign
id|generic_readlink
comma
dot
id|follow_link
op_assign
id|nfs_follow_link
comma
dot
id|put_link
op_assign
id|nfs_put_link
comma
dot
id|getattr
op_assign
id|nfs_getattr
comma
dot
id|setattr
op_assign
id|nfs_setattr
comma
)brace
suffix:semicolon
eof
