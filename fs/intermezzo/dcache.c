multiline_comment|/*&n; * Directory operations for InterMezzo filesystem&n; * Original version: (C) 1996 P. Braam and M. Callahan&n; * Rewritten for Linux 2.1. (C) 1997 Carnegie Mellon University&n; *&n; * Stelias encourages users to contribute improvements to&n; * the InterMezzo project. Contact Peter Braam (coda@stelias.com).&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
r_static
r_int
id|presto_dentry_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_int
)paren
suffix:semicolon
DECL|variable|presto_dentry_slab
r_static
id|kmem_cache_t
op_star
id|presto_dentry_slab
suffix:semicolon
multiline_comment|/* called when a cache lookup succeeds */
DECL|function|presto_dentry_revalidate
r_static
r_int
id|presto_dentry_revalidate
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_int
id|flag
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de-&gt;d_inode
suffix:semicolon
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|EXIT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|EXIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|EXIT
suffix:semicolon
r_return
(paren
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_DATA
)paren
op_logical_and
(paren
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_ATTR
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|EXIT
suffix:semicolon
r_return
id|presto_chk
c_func
(paren
id|de
comma
id|PRESTO_ATTR
)paren
suffix:semicolon
)brace
)brace
DECL|function|presto_d_release
r_static
r_void
id|presto_d_release
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|presto_d2d
c_func
(paren
id|dentry
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VERY BAD: dentry: %p&bslash;n&quot;
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
id|printk
c_func
(paren
l_string|&quot;    inode: %ld&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|presto_dentry_slab
comma
id|presto_d2d
c_func
(paren
id|dentry
)paren
)paren
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|presto_dentry_ops
r_struct
id|dentry_operations
id|presto_dentry_ops
op_assign
(brace
id|d_revalidate
suffix:colon
id|presto_dentry_revalidate
comma
id|d_release
suffix:colon
id|presto_d_release
)brace
suffix:semicolon
singleline_comment|// XXX THIS DEPENDS ON THE KERNEL LOCK!
DECL|function|presto_set_dd
r_void
id|presto_set_dd
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_fsdata
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VERY BAD: dentry: %p&bslash;n&quot;
comma
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
id|printk
c_func
(paren
l_string|&quot;    inode: %ld&bslash;n&quot;
comma
id|dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dentry-&gt;d_inode
)paren
(brace
id|dentry-&gt;d_fsdata
op_assign
id|kmem_cache_alloc
c_func
(paren
id|presto_dentry_slab
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dentry-&gt;d_fsdata
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|presto_dentry_data
)paren
)paren
suffix:semicolon
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
op_assign
l_int|1
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* If there&squot;s already a dentry for this inode, share the data */
r_if
c_cond
(paren
id|dentry-&gt;d_alias.next
op_ne
op_amp
id|dentry-&gt;d_inode-&gt;i_dentry
op_logical_or
id|dentry-&gt;d_alias.prev
op_ne
op_amp
id|dentry-&gt;d_inode-&gt;i_dentry
)paren
(brace
r_struct
id|dentry
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_alias.next
op_ne
op_amp
id|dentry-&gt;d_inode-&gt;i_dentry
)paren
id|de
op_assign
id|list_entry
c_func
(paren
id|dentry-&gt;d_alias.next
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
r_else
id|de
op_assign
id|list_entry
c_func
(paren
id|dentry-&gt;d_alias.prev
comma
r_struct
id|dentry
comma
id|d_alias
)paren
suffix:semicolon
id|dentry-&gt;d_fsdata
op_assign
id|de-&gt;d_fsdata
suffix:semicolon
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
op_increment
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dentry-&gt;d_fsdata
op_assign
id|kmem_cache_alloc
c_func
(paren
id|presto_dentry_slab
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dentry-&gt;d_fsdata
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|presto_dentry_data
)paren
)paren
suffix:semicolon
id|presto_d2d
c_func
(paren
id|dentry
)paren
op_member_access_from_pointer
id|dd_count
op_assign
l_int|1
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|presto_init_ddata_cache
r_void
id|presto_init_ddata_cache
c_func
(paren
r_void
)paren
(brace
id|ENTRY
suffix:semicolon
id|presto_dentry_slab
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;presto_cache&quot;
comma
r_sizeof
(paren
r_struct
id|presto_dentry_data
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
op_or
id|SLAB_POISON
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
)brace
DECL|function|presto_cleanup_ddata_cache
r_void
id|presto_cleanup_ddata_cache
c_func
(paren
r_void
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|presto_dentry_slab
)paren
suffix:semicolon
)brace
eof
