multiline_comment|/*&n; *   fs/cifs/link.c&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;cifsfs.h&quot;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;cifs_fs_sb.h&quot;
r_int
DECL|function|cifs_hardlink
id|cifs_hardlink
c_func
(paren
r_struct
id|dentry
op_star
id|old_file
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|direntry
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|EACCES
suffix:semicolon
r_int
id|xid
suffix:semicolon
r_char
op_star
id|fromName
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|toName
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb_target
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_struct
id|cifsInodeInfo
op_star
id|cifsInode
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
id|cifs_sb_target
op_assign
id|CIFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|pTcon
op_assign
id|cifs_sb_target-&gt;tcon
suffix:semicolon
multiline_comment|/* No need to check for cross device links since server will do that - BB note DFS case in future though (when we may have to check) */
id|fromName
op_assign
id|build_path_from_dentry
c_func
(paren
id|old_file
)paren
suffix:semicolon
id|toName
op_assign
id|build_path_from_dentry
c_func
(paren
id|direntry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cifs_sb_target-&gt;tcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
id|rc
op_assign
id|CIFSUnixCreateHardLink
c_func
(paren
id|xid
comma
id|pTcon
comma
id|fromName
comma
id|toName
comma
id|cifs_sb_target-&gt;local_nls
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|CIFSCreateHardLink
c_func
(paren
id|xid
comma
id|pTcon
comma
id|fromName
comma
id|toName
comma
id|cifs_sb_target-&gt;local_nls
)paren
suffix:semicolon
multiline_comment|/* if (!rc)     */
(brace
multiline_comment|/*   renew_parental_timestamps(old_file);&n;&t;&t;   inode-&gt;i_nlink++;&n;&t;&t;   mark_inode_dirty(inode);&n;&t;&t;   d_instantiate(direntry, inode); */
multiline_comment|/* BB add call to either mark inode dirty or refresh its data and timestamp to current time */
)brace
id|d_drop
c_func
(paren
id|direntry
)paren
suffix:semicolon
multiline_comment|/* force new lookup from server */
id|cifsInode
op_assign
id|CIFS_I
c_func
(paren
id|old_file-&gt;d_inode
)paren
suffix:semicolon
id|cifsInode-&gt;time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* will force revalidate to go get info when needed */
r_if
c_cond
(paren
id|fromName
)paren
id|kfree
c_func
(paren
id|fromName
)paren
suffix:semicolon
r_if
c_cond
(paren
id|toName
)paren
id|kfree
c_func
(paren
id|toName
)paren
suffix:semicolon
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|cifs_follow_link
id|cifs_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
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
id|direntry-&gt;d_inode
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EACCES
suffix:semicolon
r_int
id|xid
suffix:semicolon
r_char
op_star
id|full_path
op_assign
l_int|NULL
suffix:semicolon
r_char
id|target_path
(braket
l_int|257
)braket
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
id|full_path
op_assign
id|build_path_from_dentry
c_func
(paren
id|direntry
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;&bslash;nFull path: %s inode = 0x%p&bslash;n&quot;
comma
id|full_path
comma
id|inode
)paren
)paren
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
multiline_comment|/* can not call the following line due to EFAULT in vfs_readlink which is presumably expecting a user space buffer */
multiline_comment|/* length = cifs_readlink(direntry,target_path, sizeof(target_path) - 1);    */
multiline_comment|/* BB add read reparse point symlink code and Unix extensions symlink code here BB */
r_if
c_cond
(paren
id|pTcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
id|rc
op_assign
id|CIFSSMBUnixQuerySymLink
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|target_path
comma
r_sizeof
(paren
id|target_path
)paren
op_minus
l_int|1
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* rc = CIFSSMBQueryReparseLinkInfo */
multiline_comment|/* BB Add code to Query ReparsePoint info */
)brace
multiline_comment|/* BB Anything else to do to handle recursive links? */
multiline_comment|/* BB Should we be using page symlink ops here? */
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|target_path
(braket
l_int|256
)braket
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|target_path
)paren
suffix:semicolon
)brace
multiline_comment|/* else EACCESS */
r_if
c_cond
(paren
id|full_path
)paren
id|kfree
c_func
(paren
id|full_path
)paren
suffix:semicolon
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|cifs_symlink
id|cifs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|direntry
comma
r_const
r_char
op_star
id|symname
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_int
id|xid
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_char
op_star
id|full_path
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|newinode
op_assign
l_int|NULL
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
id|full_path
op_assign
id|build_path_from_dentry
c_func
(paren
id|direntry
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;&bslash;nFull path: %s &quot;
comma
id|full_path
)paren
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; symname is %s&bslash;n&quot;
comma
id|symname
)paren
)paren
suffix:semicolon
multiline_comment|/* BB what if DFS and this volume is on different share? BB */
r_if
c_cond
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
id|rc
op_assign
id|CIFSUnixCreateSymLink
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|symname
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
multiline_comment|/* else&n;&t;   rc = CIFSCreateReparseSymLink(xid, pTcon, fromName, toName,cifs_sb_target-&gt;local_nls); */
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|pTcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
id|rc
op_assign
id|cifs_get_inode_info_unix
c_func
(paren
op_amp
id|newinode
comma
id|full_path
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|cifs_get_inode_info
c_func
(paren
op_amp
id|newinode
comma
id|full_path
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;&bslash;nCreate symlink worked but get_inode_info failed with rc = %d &quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|direntry-&gt;d_op
op_assign
op_amp
id|cifs_dentry_ops
suffix:semicolon
id|d_instantiate
c_func
(paren
id|direntry
comma
id|newinode
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|full_path
)paren
id|kfree
c_func
(paren
id|full_path
)paren
suffix:semicolon
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|cifs_readlink
id|cifs_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
comma
r_char
op_star
id|pBuffer
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
id|direntry-&gt;d_inode
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EACCES
suffix:semicolon
r_int
id|xid
suffix:semicolon
r_struct
id|cifs_sb_info
op_star
id|cifs_sb
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|pTcon
suffix:semicolon
r_char
op_star
id|full_path
op_assign
l_int|NULL
suffix:semicolon
r_char
id|tmpbuffer
(braket
l_int|256
)braket
suffix:semicolon
id|xid
op_assign
id|GetXid
c_func
(paren
)paren
suffix:semicolon
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
id|pTcon
op_assign
id|cifs_sb-&gt;tcon
suffix:semicolon
id|full_path
op_assign
id|build_path_from_dentry
c_func
(paren
id|direntry
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;&bslash;nFull path: %s inode = 0x%p pBuffer = 0x%p buflen = %d&bslash;n&quot;
comma
id|full_path
comma
id|inode
comma
id|pBuffer
comma
id|buflen
)paren
)paren
suffix:semicolon
multiline_comment|/* BB add read reparse point symlink code and Unix extensions symlink code here BB */
r_if
c_cond
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
id|rc
op_assign
id|CIFSSMBUnixQuerySymLink
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|tmpbuffer
comma
r_sizeof
(paren
id|tmpbuffer
)paren
op_minus
l_int|1
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* rc = CIFSSMBQueryReparseLinkInfo */
multiline_comment|/* BB Add code to Query ReparsePoint info */
)brace
multiline_comment|/* BB Anything else to do to handle recursive links? */
multiline_comment|/* BB Should we be using page ops here? */
multiline_comment|/* BB null terminate returned string in pBuffer? BB */
r_if
c_cond
(paren
id|buflen
OG
r_sizeof
(paren
id|tmpbuffer
)paren
)paren
id|buflen
op_assign
r_sizeof
(paren
id|tmpbuffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|rc
op_assign
id|vfs_readlink
c_func
(paren
id|direntry
comma
id|pBuffer
comma
id|buflen
comma
id|tmpbuffer
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;vfs_readlink called from cifs_readlink returned %d&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|full_path
)paren
id|kfree
c_func
(paren
id|full_path
)paren
suffix:semicolon
id|FreeXid
c_func
(paren
id|xid
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
