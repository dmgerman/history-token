multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *   Portions Copyright (c) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_dmap.h&quot;
macro_line|#include &quot;jfs_txnmgr.h&quot;
macro_line|#include &quot;jfs_xattr.h&quot;
macro_line|#include &quot;jfs_acl.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
r_extern
r_int
id|jfs_commit_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|jfs_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|function|jfs_fsync
r_int
id|jfs_fsync
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
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
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY
)paren
op_logical_or
(paren
id|datasync
op_logical_and
op_logical_neg
(paren
id|inode-&gt;i_state
op_amp
id|I_DIRTY_DATASYNC
)paren
)paren
)paren
(brace
multiline_comment|/* Make sure committed changes hit the disk */
id|jfs_flush_journal
c_func
(paren
id|JFS_SBI
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|log
comma
l_int|1
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|rc
op_or_assign
id|jfs_commit_inode
c_func
(paren
id|inode
comma
l_int|1
)paren
suffix:semicolon
r_return
id|rc
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|jfs_open
r_static
r_int
id|jfs_open
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
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|generic_file_open
c_func
(paren
id|inode
comma
id|file
)paren
)paren
)paren
r_return
id|rc
suffix:semicolon
multiline_comment|/*&n;&t; * We attempt to allow only one &quot;active&quot; file open per aggregate&n;&t; * group.  Otherwise, appending to files in parallel can cause&n;&t; * fragmentation within the files.&n;&t; *&n;&t; * If the file is empty, it was probably just created and going&n;&t; * to be written to.  If it has a size, we&squot;ll hold off until the&n;&t; * file is actually grown.&n;&t; */
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
op_logical_and
(paren
id|inode-&gt;i_size
op_eq
l_int|0
)paren
)paren
(brace
r_struct
id|jfs_inode_info
op_star
id|ji
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|ji-&gt;ag_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ji-&gt;active_ag
op_eq
op_minus
l_int|1
)paren
(brace
id|ji-&gt;active_ag
op_assign
id|ji-&gt;agno
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|JFS_SBI
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|bmap-&gt;db_active
(braket
id|ji-&gt;agno
)braket
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|ji-&gt;ag_lock
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jfs_release
r_static
r_int
id|jfs_release
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
r_struct
id|jfs_inode_info
op_star
id|ji
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|ji-&gt;ag_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ji-&gt;active_ag
op_ne
op_minus
l_int|1
)paren
(brace
r_struct
id|bmap
op_star
id|bmap
op_assign
id|JFS_SBI
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|bmap
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|bmap-&gt;db_active
(braket
id|ji-&gt;active_ag
)braket
)paren
suffix:semicolon
id|ji-&gt;active_ag
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|ji-&gt;ag_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jfs_file_inode_operations
r_struct
id|inode_operations
id|jfs_file_inode_operations
op_assign
(brace
dot
id|truncate
op_assign
id|jfs_truncate
comma
dot
id|setxattr
op_assign
id|jfs_setxattr
comma
dot
id|getxattr
op_assign
id|jfs_getxattr
comma
dot
id|listxattr
op_assign
id|jfs_listxattr
comma
dot
id|removexattr
op_assign
id|jfs_removexattr
comma
macro_line|#ifdef CONFIG_JFS_POSIX_ACL
dot
id|setattr
op_assign
id|jfs_setattr
comma
dot
id|permission
op_assign
id|jfs_permission
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|jfs_file_operations
r_struct
id|file_operations
id|jfs_file_operations
op_assign
(brace
dot
id|open
op_assign
id|jfs_open
comma
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|write
op_assign
id|generic_file_write
comma
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|aio_read
op_assign
id|generic_file_aio_read
comma
dot
id|aio_write
op_assign
id|generic_file_aio_write
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|readv
op_assign
id|generic_file_readv
comma
dot
id|writev
op_assign
id|generic_file_writev
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
dot
id|fsync
op_assign
id|jfs_fsync
comma
dot
id|release
op_assign
id|jfs_release
comma
)brace
suffix:semicolon
eof
