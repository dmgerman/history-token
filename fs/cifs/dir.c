multiline_comment|/*&n; *   fs/cifs/dir.c&n; *&n; *   vfs operations that deal with dentries&n; * &n; *   Copyright (C) International Business Machines  Corp., 2002,2003&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &quot;cifsfs.h&quot;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;cifs_fs_sb.h&quot;
r_void
DECL|function|renew_parental_timestamps
id|renew_parental_timestamps
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
)paren
(brace
multiline_comment|/* BB check if there is a way to get the kernel to do this or if we really need this */
r_do
(brace
id|direntry-&gt;d_time
op_assign
id|jiffies
suffix:semicolon
id|direntry
op_assign
id|direntry-&gt;d_parent
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|IS_ROOT
c_func
(paren
id|direntry
)paren
)paren
suffix:semicolon
multiline_comment|/* BB for DFS case should stop at the root of share which could be lower than root of this mount due to implicit dfs connections */
)brace
multiline_comment|/* Note: caller must free return buffer */
r_char
op_star
DECL|function|build_path_from_dentry
id|build_path_from_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
)paren
(brace
r_struct
id|dentry
op_star
id|temp
suffix:semicolon
r_int
id|namelen
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|full_path
suffix:semicolon
r_for
c_loop
(paren
id|temp
op_assign
id|direntry
suffix:semicolon
op_logical_neg
id|IS_ROOT
c_func
(paren
id|temp
)paren
suffix:semicolon
)paren
(brace
id|namelen
op_add_assign
(paren
l_int|1
op_plus
id|temp-&gt;d_name.len
)paren
suffix:semicolon
id|temp
op_assign
id|temp-&gt;d_parent
suffix:semicolon
)brace
id|namelen
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* allow for trailing null */
id|full_path
op_assign
id|kmalloc
c_func
(paren
id|namelen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|namelen
op_decrement
suffix:semicolon
id|full_path
(braket
id|namelen
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* trailing null */
r_for
c_loop
(paren
id|temp
op_assign
id|direntry
suffix:semicolon
op_logical_neg
id|IS_ROOT
c_func
(paren
id|temp
)paren
suffix:semicolon
)paren
(brace
id|namelen
op_sub_assign
l_int|1
op_plus
id|temp-&gt;d_name.len
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OL
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|full_path
(braket
id|namelen
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
id|strncpy
c_func
(paren
id|full_path
op_plus
id|namelen
op_plus
l_int|1
comma
id|temp-&gt;d_name.name
comma
id|temp-&gt;d_name.len
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|0
comma
(paren
l_string|&quot; name: %s &quot;
comma
id|full_path
op_plus
id|namelen
)paren
)paren
suffix:semicolon
)brace
id|temp
op_assign
id|temp-&gt;d_parent
suffix:semicolon
)brace
r_if
c_cond
(paren
id|namelen
op_ne
l_int|0
)paren
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;We did not end path lookup where we expected namelen is %d&quot;
comma
id|namelen
)paren
)paren
suffix:semicolon
r_return
id|full_path
suffix:semicolon
)brace
r_char
op_star
DECL|function|build_wildcard_path_from_dentry
id|build_wildcard_path_from_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
)paren
(brace
r_struct
id|dentry
op_star
id|temp
suffix:semicolon
r_int
id|namelen
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|full_path
suffix:semicolon
r_for
c_loop
(paren
id|temp
op_assign
id|direntry
suffix:semicolon
op_logical_neg
id|IS_ROOT
c_func
(paren
id|temp
)paren
suffix:semicolon
)paren
(brace
id|namelen
op_add_assign
(paren
l_int|1
op_plus
id|temp-&gt;d_name.len
)paren
suffix:semicolon
id|temp
op_assign
id|temp-&gt;d_parent
suffix:semicolon
)brace
id|namelen
op_add_assign
l_int|3
suffix:semicolon
multiline_comment|/* allow for trailing null and wildcard (slash and *) */
id|full_path
op_assign
id|kmalloc
c_func
(paren
id|namelen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|namelen
op_decrement
suffix:semicolon
id|full_path
(braket
id|namelen
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* trailing null */
id|namelen
op_decrement
suffix:semicolon
id|full_path
(braket
id|namelen
)braket
op_assign
l_char|&squot;*&squot;
suffix:semicolon
id|namelen
op_decrement
suffix:semicolon
id|full_path
(braket
id|namelen
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
r_for
c_loop
(paren
id|temp
op_assign
id|direntry
suffix:semicolon
op_logical_neg
id|IS_ROOT
c_func
(paren
id|temp
)paren
suffix:semicolon
)paren
(brace
id|namelen
op_sub_assign
l_int|1
op_plus
id|temp-&gt;d_name.len
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OL
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|full_path
(braket
id|namelen
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
id|strncpy
c_func
(paren
id|full_path
op_plus
id|namelen
op_plus
l_int|1
comma
id|temp-&gt;d_name.name
comma
id|temp-&gt;d_name.len
)paren
suffix:semicolon
)brace
id|temp
op_assign
id|temp-&gt;d_parent
suffix:semicolon
)brace
r_if
c_cond
(paren
id|namelen
op_ne
l_int|0
)paren
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;We did not end path lookup where we expected namelen is %d&quot;
comma
id|namelen
)paren
)paren
suffix:semicolon
r_return
id|full_path
suffix:semicolon
)brace
multiline_comment|/* Inode operations in similar order to how they appear in the Linux file fs.h */
r_int
DECL|function|cifs_create
id|cifs_create
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
r_int
id|mode
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_int
id|xid
suffix:semicolon
r_int
id|oplock
op_assign
l_int|0
suffix:semicolon
r_int
id|desiredAccess
op_assign
id|GENERIC_READ
op_or
id|GENERIC_WRITE
suffix:semicolon
id|__u16
id|fileHandle
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
id|FILE_ALL_INFO
op_star
id|buf
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
r_struct
id|cifsFileInfo
op_star
id|pCifsFile
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|cifsInodeInfo
op_star
id|pCifsInode
suffix:semicolon
r_int
id|disposition
op_assign
id|FILE_OVERWRITE_IF
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
r_if
c_cond
(paren
id|nd
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In create for inode %p dentry-&gt;inode %p nd flags = 0x%x for %s&quot;
comma
id|inode
comma
id|direntry-&gt;d_inode
comma
id|nd-&gt;flags
comma
id|full_path
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nd-&gt;intent.open.flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDONLY
)paren
id|desiredAccess
op_assign
id|GENERIC_READ
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|nd-&gt;intent.open.flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_WRONLY
)paren
id|desiredAccess
op_assign
id|GENERIC_WRITE
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|nd-&gt;intent.open.flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDWR
)paren
(brace
multiline_comment|/* GENERIC_ALL is too much permission to request */
multiline_comment|/* can cause unnecessary access denied on create */
multiline_comment|/* desiredAccess = GENERIC_ALL; */
id|desiredAccess
op_assign
id|GENERIC_READ
op_or
id|GENERIC_WRITE
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|nd-&gt;intent.open.flags
op_amp
(paren
id|O_CREAT
op_or
id|O_EXCL
)paren
)paren
op_eq
(paren
id|O_CREAT
op_or
id|O_EXCL
)paren
)paren
(brace
id|disposition
op_assign
id|FILE_CREATE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|nd-&gt;intent.open.flags
op_amp
(paren
id|O_CREAT
op_or
id|O_TRUNC
)paren
)paren
op_eq
(paren
id|O_CREAT
op_or
id|O_TRUNC
)paren
)paren
(brace
id|disposition
op_assign
id|FILE_OVERWRITE_IF
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|nd-&gt;intent.open.flags
op_amp
id|O_CREAT
)paren
op_eq
id|O_CREAT
)paren
(brace
id|disposition
op_assign
id|FILE_OPEN_IF
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Create flag not set in create function&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* BB add processing to set equivalent of mode - e.g. via CreateX with ACLs */
r_if
c_cond
(paren
id|oplockEnabled
)paren
id|oplock
op_assign
id|REQ_OPLOCK
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|FILE_ALL_INFO
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|rc
op_assign
id|CIFSSMBOpen
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|disposition
comma
id|desiredAccess
comma
id|CREATE_NOT_DIR
comma
op_amp
id|fileHandle
comma
op_amp
id|oplock
comma
id|buf
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;cifs_create returned 0x%x &quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* If Open reported that we actually created a file&n;&t;&t;then we now have to set the mode if possible */
r_if
c_cond
(paren
(paren
id|cifs_sb-&gt;tcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
op_logical_and
(paren
id|oplock
op_amp
id|CIFS_CREATE_ACTION
)paren
)paren
id|CIFSSMBUnixSetPerms
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|mode
comma
(paren
id|__u64
)paren
op_minus
l_int|1
comma
(paren
id|__u64
)paren
op_minus
l_int|1
comma
l_int|0
multiline_comment|/* dev */
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* BB implement via Windows security descriptors */
multiline_comment|/* eg CIFSSMBWinSetPerms(xid,pTcon,full_path,mode,-1,-1,local_nls);*/
multiline_comment|/* could set r/o dos attribute if mode &amp; 0222 == 0 */
)brace
multiline_comment|/* BB server might mask mode so we have to query for Unix case*/
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
(brace
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
id|buf
comma
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newinode
)paren
(brace
id|newinode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
)brace
)brace
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
l_string|&quot;Create worked but get_inode_info failed with rc = %d&quot;
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
r_if
c_cond
(paren
(paren
id|nd-&gt;flags
op_amp
id|LOOKUP_OPEN
)paren
op_eq
id|FALSE
)paren
(brace
multiline_comment|/* mknod case - do not leave file open */
id|CIFSSMBClose
c_func
(paren
id|xid
comma
id|pTcon
comma
id|fileHandle
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|newinode
)paren
(brace
id|pCifsFile
op_assign
(paren
r_struct
id|cifsFileInfo
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cifsFileInfo
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pCifsFile
)paren
(brace
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|pCifsFile
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cifsFileInfo
)paren
)paren
suffix:semicolon
id|pCifsFile-&gt;netfid
op_assign
id|fileHandle
suffix:semicolon
id|pCifsFile-&gt;pid
op_assign
id|current-&gt;tgid
suffix:semicolon
id|pCifsFile-&gt;pInode
op_assign
id|newinode
suffix:semicolon
id|pCifsFile-&gt;invalidHandle
op_assign
id|FALSE
suffix:semicolon
id|pCifsFile-&gt;closePend
op_assign
id|FALSE
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|pCifsFile-&gt;fh_sem
)paren
suffix:semicolon
multiline_comment|/* pCifsFile-&gt;pfile = file; */
multiline_comment|/* put in at open time */
id|write_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|pCifsFile-&gt;tlist
comma
op_amp
id|pTcon-&gt;openFileList
)paren
suffix:semicolon
id|pCifsInode
op_assign
id|CIFS_I
c_func
(paren
id|newinode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pCifsInode
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|pCifsFile-&gt;flist
comma
op_amp
id|pCifsInode-&gt;openFileList
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|oplock
op_amp
l_int|0xF
)paren
op_eq
id|OPLOCK_EXCLUSIVE
)paren
(brace
id|pCifsInode-&gt;clientCanCacheAll
op_assign
id|TRUE
suffix:semicolon
id|pCifsInode-&gt;clientCanCacheRead
op_assign
id|TRUE
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Exclusive Oplock granted on inode %p&quot;
comma
id|newinode
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|oplock
op_amp
l_int|0xF
)paren
op_eq
id|OPLOCK_READ
)paren
(brace
id|pCifsInode-&gt;clientCanCacheRead
op_assign
id|TRUE
suffix:semicolon
)brace
)brace
id|write_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|buf
)paren
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
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
DECL|function|cifs_mknod
r_int
id|cifs_mknod
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
r_int
id|mode
comma
id|dev_t
id|device_number
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|EPERM
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
r_if
c_cond
(paren
op_logical_neg
id|old_valid_dev
c_func
(paren
id|device_number
)paren
)paren
r_return
op_minus
id|EINVAL
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
r_if
c_cond
(paren
id|pTcon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNIX
)paren
(brace
id|rc
op_assign
id|CIFSSMBUnixSetPerms
c_func
(paren
id|xid
comma
id|pTcon
comma
id|full_path
comma
id|mode
comma
id|current-&gt;euid
comma
id|current-&gt;egid
comma
id|device_number
comma
id|cifs_sb-&gt;local_nls
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
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
id|direntry-&gt;d_op
op_assign
op_amp
id|cifs_dentry_ops
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
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
r_struct
id|dentry
op_star
DECL|function|cifs_lookup
id|cifs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|parent_dir_inode
comma
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
r_int
id|rc
comma
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
r_struct
id|inode
op_star
id|newInode
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|full_path
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
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; parent inode = 0x%p name is: %s and dentry = 0x%p&quot;
comma
id|parent_dir_inode
comma
id|direntry-&gt;d_name.name
comma
id|direntry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nd
)paren
(brace
multiline_comment|/* BB removeme */
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In lookup nd flags 0x%x open intent flags 0x%x&quot;
comma
id|nd-&gt;flags
comma
id|nd-&gt;intent.open.flags
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* BB removeme BB */
multiline_comment|/* BB Add check of incoming data - e.g. frame not longer than maximum SMB - let server check the namelen BB */
multiline_comment|/* check whether path exists */
id|cifs_sb
op_assign
id|CIFS_SB
c_func
(paren
id|parent_dir_inode-&gt;i_sb
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
r_if
c_cond
(paren
id|direntry-&gt;d_inode
op_ne
l_int|NULL
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; non-NULL inode in lookup&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; NULL inode in lookup&quot;
)paren
)paren
suffix:semicolon
)brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; Full path: %s inode = 0x%p&quot;
comma
id|full_path
comma
id|direntry-&gt;d_inode
)paren
)paren
suffix:semicolon
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
id|newInode
comma
id|full_path
comma
id|parent_dir_inode-&gt;i_sb
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|cifs_get_inode_info
c_func
(paren
op_amp
id|newInode
comma
id|full_path
comma
l_int|NULL
comma
id|parent_dir_inode-&gt;i_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_eq
l_int|0
)paren
op_logical_and
(paren
id|newInode
op_ne
l_int|NULL
)paren
)paren
(brace
id|direntry-&gt;d_op
op_assign
op_amp
id|cifs_dentry_ops
suffix:semicolon
id|d_add
c_func
(paren
id|direntry
comma
id|newInode
)paren
suffix:semicolon
multiline_comment|/* since paths are not looked up by component - the parent directories are presumed to be good here */
id|renew_parental_timestamps
c_func
(paren
id|direntry
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rc
op_eq
op_minus
id|ENOENT
)paren
(brace
id|rc
op_assign
l_int|0
suffix:semicolon
id|d_add
c_func
(paren
id|direntry
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error 0x%x or (%d decimal) on cifs_get_inode_info in lookup&quot;
comma
id|rc
comma
id|rc
)paren
)paren
suffix:semicolon
multiline_comment|/* BB special case check for Access Denied - watch security exposure of returning dir info implicitly via different rc if file exists or not but no access BB */
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
id|ERR_PTR
c_func
(paren
id|rc
)paren
suffix:semicolon
)brace
r_int
DECL|function|cifs_dir_open
id|cifs_dir_open
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
multiline_comment|/* NB: currently unused since searches are opened in readdir */
r_int
id|rc
op_assign
l_int|0
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
id|build_wildcard_path_from_dentry
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; inode = 0x%p and full path is %s&quot;
comma
id|inode
comma
id|full_path
)paren
)paren
suffix:semicolon
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
r_static
r_int
DECL|function|cifs_d_revalidate
id|cifs_d_revalidate
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
r_int
id|isValid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&t;lock_kernel(); */
multiline_comment|/* surely we do not want to lock the kernel for a whole network round trip which could take seconds */
r_if
c_cond
(paren
id|direntry-&gt;d_inode
)paren
(brace
r_if
c_cond
(paren
id|cifs_revalidate
c_func
(paren
id|direntry
)paren
)paren
(brace
multiline_comment|/* unlock_kernel(); */
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;In cifs_d_revalidate with no inode but name = %s and dentry 0x%p&quot;
comma
id|direntry-&gt;d_name.name
comma
id|direntry
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*    unlock_kernel(); */
r_return
id|isValid
suffix:semicolon
)brace
multiline_comment|/* static int cifs_d_delete(struct dentry *direntry)&n;{&n;&t;int rc = 0;&n;&n;&t;cFYI(1, (&quot;In cifs d_delete, name = %s&quot;, direntry-&gt;d_name.name));&n;&n;&t;return rc;&n;}     */
DECL|variable|cifs_dentry_ops
r_struct
id|dentry_operations
id|cifs_dentry_ops
op_assign
(brace
dot
id|d_revalidate
op_assign
id|cifs_d_revalidate
comma
multiline_comment|/* d_delete:       cifs_d_delete,       */
multiline_comment|/* not needed except for debugging */
multiline_comment|/* no need for d_hash, d_compare, d_release, d_iput ... yet. BB confirm this BB */
)brace
suffix:semicolon
eof
