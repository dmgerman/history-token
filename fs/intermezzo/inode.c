multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 1996 Peter J. Braam &lt;braam@maths.ox.ac.uk&gt; and&n; *    Michael Callahan &lt;callahan@maths.ox.ac.uk&gt;&n; *  Copyright (C) 1999 Carnegie Mellon University&n; *    Rewritten for Linux 2.1.  Peter Braam &lt;braam@cs.cmu.edu&gt;&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Super block/filesystem wide operations&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;intermezzo_fs.h&quot;
macro_line|#include &quot;intermezzo_psdev.h&quot;
r_extern
r_void
id|presto_free_cache
c_func
(paren
r_struct
id|presto_cache
op_star
)paren
suffix:semicolon
DECL|function|presto_set_ops
r_void
id|presto_set_ops
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|filter_fs
op_star
id|filter
)paren
(brace
id|ENTRY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
id|is_bad_inode
c_func
(paren
id|inode
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|filter_c2cfiops
c_func
(paren
id|filter
)paren
)paren
(brace
id|filter_setup_file_ops
c_func
(paren
id|filter
comma
id|inode
comma
op_amp
id|presto_file_iops
comma
op_amp
id|presto_file_fops
)paren
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
id|filter_c2ufiops
c_func
(paren
id|filter
)paren
suffix:semicolon
id|inode-&gt;i_fop
op_assign
id|filter_c2uffops
c_func
(paren
id|filter
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;set file methods for %ld to %p&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_op
)paren
suffix:semicolon
)brace
r_else
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
id|inode-&gt;i_op
op_assign
id|filter_c2udiops
c_func
(paren
id|filter
)paren
suffix:semicolon
id|inode-&gt;i_fop
op_assign
id|filter_c2udfops
c_func
(paren
id|filter
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;set dir methods for %ld to %p ioctl %p&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_op
comma
id|inode-&gt;i_fop-&gt;ioctl
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|filter_c2csiops
c_func
(paren
id|filter
)paren
)paren
(brace
id|filter_setup_symlink_ops
c_func
(paren
id|filter
comma
id|inode
comma
op_amp
id|presto_sym_iops
comma
op_amp
id|presto_sym_fops
)paren
suffix:semicolon
)brace
id|inode-&gt;i_op
op_assign
id|filter_c2usiops
c_func
(paren
id|filter
)paren
suffix:semicolon
id|inode-&gt;i_fop
op_assign
id|filter_c2usfops
c_func
(paren
id|filter
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;set link methods for %ld to %p&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_op
)paren
suffix:semicolon
)brace
id|EXIT
suffix:semicolon
)brace
DECL|function|presto_read_inode
r_void
id|presto_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
id|cache
op_assign
id|presto_get_cache
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;PRESTO: BAD, BAD: cannot find cache&bslash;n&quot;
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|filter_c2csops
c_func
(paren
id|cache-&gt;cache_filter
)paren
op_member_access_from_pointer
id|read_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;presto_read_inode: ino %ld, gid %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_gid
)paren
suffix:semicolon
id|presto_set_ops
c_func
(paren
id|inode
comma
id|cache-&gt;cache_filter
)paren
suffix:semicolon
multiline_comment|/* XXX handle special inodes here or not - probably not? */
)brace
DECL|function|presto_put_super
r_static
r_void
id|presto_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|presto_cache
op_star
id|cache
suffix:semicolon
r_struct
id|upc_channel
op_star
id|channel
suffix:semicolon
r_struct
id|super_operations
op_star
id|sops
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cache
op_assign
id|presto_cache_find
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache
)paren
(brace
id|EXIT
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|channel
op_assign
op_amp
id|izo_channels
(braket
id|presto_c2m
c_func
(paren
id|cache
)paren
)braket
suffix:semicolon
id|sops
op_assign
id|filter_c2csops
c_func
(paren
id|cache-&gt;cache_filter
)paren
suffix:semicolon
id|err
op_assign
id|izo_clear_all_fsetroots
c_func
(paren
id|cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|CERROR
c_func
(paren
l_string|&quot;%s: err %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
)paren
suffix:semicolon
)brace
id|PRESTO_FREE
c_func
(paren
id|cache-&gt;cache_vfsmount
comma
r_sizeof
(paren
r_struct
id|vfsmount
)paren
)paren
suffix:semicolon
multiline_comment|/* look at kill_super - fsync_super is not exported GRRR but &n;           probably not needed */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|shrink_dcache_parent
c_func
(paren
id|cache-&gt;cache_root
)paren
suffix:semicolon
id|dput
c_func
(paren
id|cache-&gt;cache_root
)paren
suffix:semicolon
singleline_comment|//fsync_super(sb); 
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sops-&gt;write_super
)paren
id|sops
op_member_access_from_pointer
id|write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sops-&gt;put_super
)paren
id|sops
op_member_access_from_pointer
id|put_super
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* free any remaining async upcalls when the filesystem is unmounted */
id|spin_lock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|lh
op_assign
id|channel-&gt;uc_pending.next
suffix:semicolon
r_while
c_loop
(paren
id|lh
op_ne
op_amp
id|channel-&gt;uc_pending
)paren
(brace
r_struct
id|upc_req
op_star
id|req
suffix:semicolon
id|req
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|upc_req
comma
id|rq_chain
)paren
suffix:semicolon
multiline_comment|/* assignment must be here: we are about to free &amp;lh */
id|lh
op_assign
id|lh-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|req-&gt;rq_flags
op_amp
id|REQ_ASYNC
)paren
)paren
r_continue
suffix:semicolon
id|list_del
c_func
(paren
op_amp
(paren
id|req-&gt;rq_chain
)paren
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|req-&gt;rq_data
comma
id|req-&gt;rq_bufsize
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|req
comma
r_sizeof
(paren
r_struct
id|upc_req
)paren
)paren
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|cache-&gt;cache_channel_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|channel-&gt;uc_lock
)paren
suffix:semicolon
id|presto_free_cache
c_func
(paren
id|cache
)paren
suffix:semicolon
m_exit
suffix:colon
id|CDEBUG
c_func
(paren
id|D_MALLOC
comma
l_string|&quot;after umount: kmem %ld, vmem %ld&bslash;n&quot;
comma
id|presto_kmemory
comma
id|presto_vmemory
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|presto_super_ops
r_struct
id|super_operations
id|presto_super_ops
op_assign
(brace
dot
id|read_inode
op_assign
id|presto_read_inode
comma
dot
id|put_super
op_assign
id|presto_put_super
comma
)brace
suffix:semicolon
multiline_comment|/* symlinks can be chowned */
DECL|variable|presto_sym_iops
r_struct
id|inode_operations
id|presto_sym_iops
op_assign
(brace
dot
id|setattr
op_assign
id|presto_setattr
)brace
suffix:semicolon
multiline_comment|/* NULL for now */
DECL|variable|presto_sym_fops
r_struct
id|file_operations
id|presto_sym_fops
suffix:semicolon
eof
