multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;jfs_incore.h&quot;
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_imap.h&quot;
macro_line|#include &quot;jfs_dinode.h&quot;
macro_line|#include &quot;jfs_debug.h&quot;
multiline_comment|/*&n; * NAME:&t;ialloc()&n; *&n; * FUNCTION:&t;Allocate a new inode&n; *&n; */
DECL|function|ialloc
r_struct
id|inode
op_star
id|ialloc
c_func
(paren
r_struct
id|inode
op_star
id|parent
comma
id|umode_t
id|mode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|parent-&gt;i_sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|jfs_inode_info
op_star
id|jfs_inode
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|jfs_warn
c_func
(paren
l_string|&quot;ialloc: new_inode returned NULL!&quot;
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
id|jfs_inode
op_assign
id|JFS_IP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|rc
op_assign
id|diAlloc
c_func
(paren
id|parent
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|jfs_warn
c_func
(paren
l_string|&quot;ialloc: diAlloc returned %d!&quot;
comma
id|rc
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
r_if
c_cond
(paren
id|parent-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|inode-&gt;i_gid
op_assign
id|parent-&gt;i_gid
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
id|mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
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
id|jfs_inode-&gt;mode2
op_assign
id|IDIRECTORY
op_or
id|mode
suffix:semicolon
r_else
id|jfs_inode-&gt;mode2
op_assign
id|INLINEEA
op_or
id|ISPARSE
op_or
id|mode
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|jfs_inode-&gt;otime
op_assign
id|inode-&gt;i_ctime.tv_sec
suffix:semicolon
id|inode-&gt;i_generation
op_assign
id|JFS_SBI
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|gengen
op_increment
suffix:semicolon
id|jfs_inode-&gt;cflag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Zero remaining fields */
id|memset
c_func
(paren
op_amp
id|jfs_inode-&gt;acl
comma
l_int|0
comma
r_sizeof
(paren
id|dxd_t
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|jfs_inode-&gt;ea
comma
l_int|0
comma
r_sizeof
(paren
id|dxd_t
)paren
)paren
suffix:semicolon
id|jfs_inode-&gt;next_index
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;acltype
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;btorder
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;btindex
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;bxflag
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;blid
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;atlhead
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;atltail
op_assign
l_int|0
suffix:semicolon
id|jfs_inode-&gt;xtlid
op_assign
l_int|0
suffix:semicolon
id|jfs_info
c_func
(paren
l_string|&quot;ialloc returns inode = 0x%p&bslash;n&quot;
comma
id|inode
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
eof
