multiline_comment|/*&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
macro_line|#include &quot;xfs_inum.h&quot;
macro_line|#include &quot;xfs_log.h&quot;
macro_line|#include &quot;xfs_trans.h&quot;
macro_line|#include &quot;xfs_sb.h&quot;
macro_line|#include &quot;xfs_ag.h&quot;
macro_line|#include &quot;xfs_dir.h&quot;
macro_line|#include &quot;xfs_dir2.h&quot;
macro_line|#include &quot;xfs_alloc.h&quot;
macro_line|#include &quot;xfs_dmapi.h&quot;
macro_line|#include &quot;xfs_quota.h&quot;
macro_line|#include &quot;xfs_mount.h&quot;
macro_line|#include &quot;xfs_alloc_btree.h&quot;
macro_line|#include &quot;xfs_bmap_btree.h&quot;
macro_line|#include &quot;xfs_ialloc_btree.h&quot;
macro_line|#include &quot;xfs_btree.h&quot;
macro_line|#include &quot;xfs_ialloc.h&quot;
macro_line|#include &quot;xfs_attr_sf.h&quot;
macro_line|#include &quot;xfs_dir_sf.h&quot;
macro_line|#include &quot;xfs_dir2_sf.h&quot;
macro_line|#include &quot;xfs_dinode.h&quot;
macro_line|#include &quot;xfs_inode.h&quot;
macro_line|#include &quot;xfs_bmap.h&quot;
macro_line|#include &quot;xfs_bit.h&quot;
macro_line|#include &quot;xfs_rtalloc.h&quot;
macro_line|#include &quot;xfs_error.h&quot;
macro_line|#include &quot;xfs_itable.h&quot;
macro_line|#include &quot;xfs_rw.h&quot;
macro_line|#include &quot;xfs_acl.h&quot;
macro_line|#include &quot;xfs_cap.h&quot;
macro_line|#include &quot;xfs_mac.h&quot;
macro_line|#include &quot;xfs_attr.h&quot;
macro_line|#include &quot;xfs_buf_item.h&quot;
macro_line|#include &quot;xfs_utils.h&quot;
macro_line|#include &lt;linux/xattr.h&gt;
multiline_comment|/*&n; * Pull the link count and size up from the xfs inode to the linux inode&n; */
id|STATIC
r_void
DECL|function|validate_fields
id|validate_fields
c_func
(paren
r_struct
id|inode
op_star
id|ip
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|ip
)paren
suffix:semicolon
id|vattr_t
id|va
suffix:semicolon
r_int
id|error
suffix:semicolon
id|va.va_mask
op_assign
id|XFS_AT_NLINK
op_or
id|XFS_AT_SIZE
op_or
id|XFS_AT_NBLOCKS
suffix:semicolon
id|VOP_GETATTR
c_func
(paren
id|vp
comma
op_amp
id|va
comma
id|ATTR_LAZY
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|error
)paren
)paren
(brace
id|ip-&gt;i_nlink
op_assign
id|va.va_nlink
suffix:semicolon
id|ip-&gt;i_blocks
op_assign
id|va.va_nblocks
suffix:semicolon
multiline_comment|/* we&squot;re under i_sem so i_size can&squot;t change under us */
r_if
c_cond
(paren
id|i_size_read
c_func
(paren
id|ip
)paren
op_ne
id|va.va_size
)paren
id|i_size_write
c_func
(paren
id|ip
comma
id|va.va_size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Determine whether a process has a valid fs_struct (kernel daemons&n; * like knfsd don&squot;t have an fs_struct).&n; *&n; * XXX(hch):  nfsd is broken, better fix it instead.&n; */
id|STATIC
r_inline
r_int
DECL|function|has_fs_struct
id|has_fs_struct
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_return
(paren
id|task-&gt;fs
op_ne
id|init_task.fs
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_mknod
id|linvfs_mknod
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
r_int
id|mode
comma
id|dev_t
id|rdev
)paren
(brace
r_struct
id|inode
op_star
id|ip
suffix:semicolon
id|vattr_t
id|va
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
l_int|NULL
comma
op_star
id|dvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dir
)paren
suffix:semicolon
id|xfs_acl_t
op_star
id|default_acl
op_assign
l_int|NULL
suffix:semicolon
id|attrexists_t
id|test_default_acl
op_assign
id|_ACL_DEFAULT_EXISTS
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Irix uses Missed&squot;em&squot;V split, but doesn&squot;t want to see&n;&t; * the upper 5 bits of (14bit) major.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|sysv_valid_dev
c_func
(paren
id|rdev
)paren
op_logical_or
id|MAJOR
c_func
(paren
id|rdev
)paren
op_amp
op_complement
l_int|0x1ff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|test_default_acl
op_logical_and
id|test_default_acl
c_func
(paren
id|dvp
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|_ACL_ALLOC
c_func
(paren
id|default_acl
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_ACL_GET_DEFAULT
c_func
(paren
id|dvp
comma
id|default_acl
)paren
)paren
(brace
id|_ACL_FREE
c_func
(paren
id|default_acl
)paren
suffix:semicolon
id|default_acl
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|IS_POSIXACL
c_func
(paren
id|dir
)paren
op_logical_and
op_logical_neg
id|default_acl
op_logical_and
id|has_fs_struct
c_func
(paren
id|current
)paren
)paren
id|mode
op_and_assign
op_complement
id|current-&gt;fs-&gt;umask
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|va
comma
l_int|0
comma
r_sizeof
(paren
id|va
)paren
)paren
suffix:semicolon
id|va.va_mask
op_assign
id|XFS_AT_TYPE
op_or
id|XFS_AT_MODE
suffix:semicolon
id|va.va_type
op_assign
id|IFTOVT
c_func
(paren
id|mode
)paren
suffix:semicolon
id|va.va_mode
op_assign
id|mode
suffix:semicolon
r_switch
c_cond
(paren
id|mode
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFCHR
suffix:colon
r_case
id|S_IFBLK
suffix:colon
r_case
id|S_IFIFO
suffix:colon
r_case
id|S_IFSOCK
suffix:colon
id|va.va_rdev
op_assign
id|sysv_encode_dev
c_func
(paren
id|rdev
)paren
suffix:semicolon
id|va.va_mask
op_or_assign
id|XFS_AT_RDEV
suffix:semicolon
multiline_comment|/*FALLTHROUGH*/
r_case
id|S_IFREG
suffix:colon
id|VOP_CREATE
c_func
(paren
id|dvp
comma
id|dentry
comma
op_amp
id|va
comma
op_amp
id|vp
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFDIR
suffix:colon
id|VOP_MKDIR
c_func
(paren
id|dvp
comma
id|dentry
comma
op_amp
id|va
comma
op_amp
id|vp
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|error
op_assign
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|default_acl
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|error
op_assign
id|_ACL_INHERIT
c_func
(paren
id|vp
comma
op_amp
id|va
comma
id|default_acl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|VMODIFY
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|dentry
id|teardown
op_assign
(brace
)brace
suffix:semicolon
r_int
id|err2
suffix:semicolon
multiline_comment|/* Oh, the horror.&n;&t;&t;&t;&t; * If we can&squot;t add the ACL we must back out.&n;&t;&t;&t;&t; * ENOSPC can hit here, among other things.&n;&t;&t;&t;&t; */
id|teardown.d_inode
op_assign
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
id|teardown.d_name
op_assign
id|dentry-&gt;d_name
suffix:semicolon
id|remove_inode_hash
c_func
(paren
id|ip
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|ip
)paren
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
id|VOP_RMDIR
c_func
(paren
id|dvp
comma
op_amp
id|teardown
comma
l_int|NULL
comma
id|err2
)paren
suffix:semicolon
r_else
id|VOP_REMOVE
c_func
(paren
id|dvp
comma
op_amp
id|teardown
comma
l_int|NULL
comma
id|err2
)paren
suffix:semicolon
id|VN_RELE
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
)brace
id|_ACL_FREE
c_func
(paren
id|default_acl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|ASSERT
c_func
(paren
id|vp
)paren
suffix:semicolon
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISBLK
c_func
(paren
id|mode
)paren
)paren
id|ip-&gt;i_rdev
op_assign
id|rdev
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|validate_fields
c_func
(paren
id|ip
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|ip
)paren
suffix:semicolon
id|validate_fields
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_create
id|linvfs_create
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
r_int
id|mode
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_return
id|linvfs_mknod
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
comma
l_int|0
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_mkdir
id|linvfs_mkdir
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
r_int
id|mode
)paren
(brace
r_return
id|linvfs_mknod
c_func
(paren
id|dir
comma
id|dentry
comma
id|mode
op_or
id|S_IFDIR
comma
l_int|0
)paren
suffix:semicolon
)brace
id|STATIC
r_struct
id|dentry
op_star
DECL|function|linvfs_lookup
id|linvfs_lookup
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
id|inode
op_star
id|ip
op_assign
l_int|NULL
suffix:semicolon
id|vnode_t
op_star
id|vp
comma
op_star
id|cvp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_name.len
op_ge
id|MAXNAMELEN
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENAMETOOLONG
)paren
suffix:semicolon
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dir
)paren
suffix:semicolon
id|VOP_LOOKUP
c_func
(paren
id|vp
comma
id|dentry
comma
op_amp
id|cvp
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|ASSERT
c_func
(paren
id|cvp
)paren
suffix:semicolon
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|cvp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip
)paren
(brace
id|VN_RELE
c_func
(paren
id|cvp
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|error
op_logical_and
(paren
id|error
op_ne
id|ENOENT
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|error
)paren
suffix:semicolon
r_return
id|d_splice_alias
c_func
(paren
id|ip
comma
id|dentry
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_link
id|linvfs_link
c_func
(paren
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|ip
suffix:semicolon
multiline_comment|/* inode of guy being linked to */
id|vnode_t
op_star
id|tdvp
suffix:semicolon
multiline_comment|/* target directory for new name/link */
id|vnode_t
op_star
id|vp
suffix:semicolon
multiline_comment|/* vp of name being linked */
r_int
id|error
suffix:semicolon
id|ip
op_assign
id|old_dentry-&gt;d_inode
suffix:semicolon
multiline_comment|/* inode being linked to */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|ip-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|tdvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dir
)paren
suffix:semicolon
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|ip
)paren
suffix:semicolon
id|VOP_LINK
c_func
(paren
id|tdvp
comma
id|vp
comma
id|dentry
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|VMODIFY
c_func
(paren
id|tdvp
)paren
suffix:semicolon
id|VN_HOLD
c_func
(paren
id|vp
)paren
suffix:semicolon
id|validate_fields
c_func
(paren
id|ip
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|ip
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_unlink
id|linvfs_unlink
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
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|vnode_t
op_star
id|dvp
suffix:semicolon
multiline_comment|/* directory containing name to remove */
r_int
id|error
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|dvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dir
)paren
suffix:semicolon
id|VOP_REMOVE
c_func
(paren
id|dvp
comma
id|dentry
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|validate_fields
c_func
(paren
id|dir
)paren
suffix:semicolon
multiline_comment|/* For size only */
id|validate_fields
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_symlink
id|linvfs_symlink
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
r_const
r_char
op_star
id|symname
)paren
(brace
r_struct
id|inode
op_star
id|ip
suffix:semicolon
id|vattr_t
id|va
suffix:semicolon
id|vnode_t
op_star
id|dvp
suffix:semicolon
multiline_comment|/* directory containing name to remove */
id|vnode_t
op_star
id|cvp
suffix:semicolon
multiline_comment|/* used to lookup symlink to put in dentry */
r_int
id|error
suffix:semicolon
id|dvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dir
)paren
suffix:semicolon
id|cvp
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|va
comma
l_int|0
comma
r_sizeof
(paren
id|va
)paren
)paren
suffix:semicolon
id|va.va_type
op_assign
id|VLNK
suffix:semicolon
id|va.va_mode
op_assign
id|irix_symlink_mode
ques
c_cond
l_int|0777
op_amp
op_complement
id|current-&gt;fs-&gt;umask
suffix:colon
id|S_IRWXUGO
suffix:semicolon
id|va.va_mask
op_assign
id|XFS_AT_TYPE
op_or
id|XFS_AT_MODE
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|VOP_SYMLINK
c_func
(paren
id|dvp
comma
id|dentry
comma
op_amp
id|va
comma
(paren
r_char
op_star
)paren
id|symname
comma
op_amp
id|cvp
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
id|cvp
)paren
(brace
id|ASSERT
c_func
(paren
id|cvp-&gt;v_type
op_eq
id|VLNK
)paren
suffix:semicolon
id|ip
op_assign
id|LINVFS_GET_IP
c_func
(paren
id|cvp
)paren
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|ip
)paren
suffix:semicolon
id|validate_fields
c_func
(paren
id|dir
)paren
suffix:semicolon
id|validate_fields
c_func
(paren
id|ip
)paren
suffix:semicolon
multiline_comment|/* size needs update */
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_rmdir
id|linvfs_rmdir
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
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|vnode_t
op_star
id|dvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dir
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|VOP_RMDIR
c_func
(paren
id|dvp
comma
id|dentry
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|validate_fields
c_func
(paren
id|inode
)paren
suffix:semicolon
id|validate_fields
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_return
op_minus
id|error
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_rename
id|linvfs_rename
c_func
(paren
r_struct
id|inode
op_star
id|odir
comma
r_struct
id|dentry
op_star
id|odentry
comma
r_struct
id|inode
op_star
id|ndir
comma
r_struct
id|dentry
op_star
id|ndentry
)paren
(brace
r_struct
id|inode
op_star
id|new_inode
op_assign
id|ndentry-&gt;d_inode
suffix:semicolon
id|vnode_t
op_star
id|fvp
suffix:semicolon
multiline_comment|/* from directory */
id|vnode_t
op_star
id|tvp
suffix:semicolon
multiline_comment|/* target directory */
r_int
id|error
suffix:semicolon
id|fvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|odir
)paren
suffix:semicolon
id|tvp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|ndir
)paren
suffix:semicolon
id|VOP_RENAME
c_func
(paren
id|fvp
comma
id|odentry
comma
id|tvp
comma
id|ndentry
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|error
suffix:semicolon
r_if
c_cond
(paren
id|new_inode
)paren
id|validate_fields
c_func
(paren
id|new_inode
)paren
suffix:semicolon
id|validate_fields
c_func
(paren
id|odir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ndir
op_ne
id|odir
)paren
id|validate_fields
c_func
(paren
id|ndir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_readlink
id|linvfs_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
id|uio_t
id|uio
suffix:semicolon
id|iovec_t
id|iov
suffix:semicolon
r_int
id|error
suffix:semicolon
id|iov.iov_base
op_assign
id|buf
suffix:semicolon
id|iov.iov_len
op_assign
id|size
suffix:semicolon
id|uio.uio_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|uio.uio_offset
op_assign
l_int|0
suffix:semicolon
id|uio.uio_segflg
op_assign
id|UIO_USERSPACE
suffix:semicolon
id|uio.uio_resid
op_assign
id|size
suffix:semicolon
id|uio.uio_iovcnt
op_assign
l_int|1
suffix:semicolon
id|VOP_READLINK
c_func
(paren
id|vp
comma
op_amp
id|uio
comma
l_int|0
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|error
suffix:semicolon
r_return
(paren
id|size
op_minus
id|uio.uio_resid
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * careful here - this function can get called recursively, so&n; * we need to be very careful about how much stack we use.&n; * uio is kmalloced for this reason...&n; */
id|STATIC
r_int
DECL|function|linvfs_follow_link
id|linvfs_follow_link
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
id|vnode_t
op_star
id|vp
suffix:semicolon
id|uio_t
op_star
id|uio
suffix:semicolon
id|iovec_t
id|iov
suffix:semicolon
r_int
id|error
suffix:semicolon
r_char
op_star
id|link
suffix:semicolon
id|ASSERT
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|nd
)paren
suffix:semicolon
id|link
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|MAXNAMELEN
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|uio
op_assign
(paren
id|uio_t
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|uio_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uio
)paren
(brace
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
id|iov.iov_base
op_assign
id|link
suffix:semicolon
id|iov.iov_len
op_assign
id|MAXNAMELEN
suffix:semicolon
id|uio-&gt;uio_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|uio-&gt;uio_offset
op_assign
l_int|0
suffix:semicolon
id|uio-&gt;uio_segflg
op_assign
id|UIO_SYSSPACE
suffix:semicolon
id|uio-&gt;uio_resid
op_assign
id|MAXNAMELEN
suffix:semicolon
id|uio-&gt;uio_iovcnt
op_assign
l_int|1
suffix:semicolon
id|VOP_READLINK
c_func
(paren
id|vp
comma
id|uio
comma
l_int|0
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|kfree
c_func
(paren
id|uio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
id|link
(braket
id|MAXNAMELEN
op_minus
id|uio-&gt;uio_resid
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|kfree
c_func
(paren
id|uio
)paren
suffix:semicolon
multiline_comment|/* vfs_follow_link returns (-) errors */
id|error
op_assign
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|link
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_XFS_POSIX_ACL
id|STATIC
r_int
DECL|function|linvfs_permission
id|linvfs_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
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
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|mode
op_lshift_assign
l_int|6
suffix:semicolon
multiline_comment|/* convert from linux to vnode access bits */
id|VOP_ACCESS
c_func
(paren
id|vp
comma
id|mode
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
macro_line|#else
DECL|macro|linvfs_permission
mdefine_line|#define linvfs_permission NULL
macro_line|#endif
id|STATIC
r_int
DECL|function|linvfs_getattr
id|linvfs_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|vp-&gt;v_flag
op_amp
id|VMODIFIED
)paren
)paren
id|error
op_assign
id|vn_revalidate
c_func
(paren
id|vp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|generic_fillattr
c_func
(paren
id|inode
comma
id|stat
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_setattr
id|linvfs_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
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
r_int
id|ia_valid
op_assign
id|attr-&gt;ia_valid
suffix:semicolon
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|inode
)paren
suffix:semicolon
id|vattr_t
id|vattr
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|vattr
comma
l_int|0
comma
r_sizeof
(paren
id|vattr_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_UID
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_UID
suffix:semicolon
id|vattr.va_uid
op_assign
id|attr-&gt;ia_uid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_GID
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_GID
suffix:semicolon
id|vattr.va_gid
op_assign
id|attr-&gt;ia_gid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_SIZE
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_SIZE
suffix:semicolon
id|vattr.va_size
op_assign
id|attr-&gt;ia_size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_ATIME
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_ATIME
suffix:semicolon
id|vattr.va_atime
op_assign
id|attr-&gt;ia_atime
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MTIME
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_MTIME
suffix:semicolon
id|vattr.va_mtime
op_assign
id|attr-&gt;ia_mtime
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_CTIME
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_CTIME
suffix:semicolon
id|vattr.va_ctime
op_assign
id|attr-&gt;ia_ctime
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
id|vattr.va_mask
op_or_assign
id|XFS_AT_MODE
suffix:semicolon
id|vattr.va_mode
op_assign
id|attr-&gt;ia_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_group_p
c_func
(paren
id|inode-&gt;i_gid
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FSETID
)paren
)paren
id|inode-&gt;i_mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
(paren
id|ATTR_MTIME_SET
op_or
id|ATTR_ATIME_SET
)paren
)paren
id|flags
op_assign
id|ATTR_UTIME
suffix:semicolon
macro_line|#ifdef ATTR_NO_BLOCK
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
id|ATTR_NO_BLOCK
)paren
)paren
id|flags
op_or_assign
id|ATTR_NONBLOCK
suffix:semicolon
macro_line|#endif
id|VOP_SETATTR
c_func
(paren
id|vp
comma
op_amp
id|vattr
comma
id|flags
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|error
suffix:semicolon
multiline_comment|/* Positive error up from XFS */
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_SIZE
)paren
(brace
id|error
op_assign
id|vmtruncate
c_func
(paren
id|inode
comma
id|attr-&gt;ia_size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|vn_revalidate
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
id|STATIC
r_void
DECL|function|linvfs_truncate
id|linvfs_truncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|block_truncate_page
c_func
(paren
id|inode-&gt;i_mapping
comma
id|inode-&gt;i_size
comma
id|linvfs_get_block
)paren
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_setxattr
id|linvfs_setxattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|name
comma
r_const
r_void
op_star
id|data
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_char
op_star
id|attr
op_assign
(paren
r_char
op_star
)paren
id|name
suffix:semicolon
id|attrnames_t
op_star
id|namesp
suffix:semicolon
r_int
id|xflags
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
id|namesp
op_assign
id|attr_lookup_namespace
c_func
(paren
id|attr
comma
id|attr_namespaces
comma
id|ATTR_NAMECOUNT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namesp
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|attr
op_add_assign
id|namesp-&gt;attr_namelen
suffix:semicolon
id|error
op_assign
id|namesp
op_member_access_from_pointer
id|attr_capable
c_func
(paren
id|vp
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
multiline_comment|/* Convert Linux syscall to XFS internal ATTR flags */
r_if
c_cond
(paren
id|flags
op_amp
id|XATTR_CREATE
)paren
id|xflags
op_or_assign
id|ATTR_CREATE
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|XATTR_REPLACE
)paren
id|xflags
op_or_assign
id|ATTR_REPLACE
suffix:semicolon
id|xflags
op_or_assign
id|namesp-&gt;attr_flag
suffix:semicolon
r_return
id|namesp
op_member_access_from_pointer
id|attr_set
c_func
(paren
id|vp
comma
id|attr
comma
(paren
r_void
op_star
)paren
id|data
comma
id|size
comma
id|xflags
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_getxattr
id|linvfs_getxattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_char
op_star
id|attr
op_assign
(paren
r_char
op_star
)paren
id|name
suffix:semicolon
id|attrnames_t
op_star
id|namesp
suffix:semicolon
r_int
id|xflags
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|error
suffix:semicolon
id|namesp
op_assign
id|attr_lookup_namespace
c_func
(paren
id|attr
comma
id|attr_namespaces
comma
id|ATTR_NAMECOUNT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namesp
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|attr
op_add_assign
id|namesp-&gt;attr_namelen
suffix:semicolon
id|error
op_assign
id|namesp
op_member_access_from_pointer
id|attr_capable
c_func
(paren
id|vp
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
multiline_comment|/* Convert Linux syscall to XFS internal ATTR flags */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|xflags
op_or_assign
id|ATTR_KERNOVAL
suffix:semicolon
id|data
op_assign
l_int|NULL
suffix:semicolon
)brace
id|xflags
op_or_assign
id|namesp-&gt;attr_flag
suffix:semicolon
r_return
id|namesp
op_member_access_from_pointer
id|attr_get
c_func
(paren
id|vp
comma
id|attr
comma
(paren
r_void
op_star
)paren
id|data
comma
id|size
comma
id|xflags
)paren
suffix:semicolon
)brace
id|STATIC
id|ssize_t
DECL|function|linvfs_listxattr
id|linvfs_listxattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_int
id|error
comma
id|xflags
op_assign
id|ATTR_KERNAMELS
suffix:semicolon
id|ssize_t
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
id|xflags
op_or_assign
id|ATTR_KERNOVAL
suffix:semicolon
id|xflags
op_or_assign
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
ques
c_cond
id|ATTR_KERNFULLS
suffix:colon
id|ATTR_KERNORMALS
suffix:semicolon
id|error
op_assign
id|attr_generic_list
c_func
(paren
id|vp
comma
id|data
comma
id|size
comma
id|xflags
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|STATIC
r_int
DECL|function|linvfs_removexattr
id|linvfs_removexattr
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|vnode_t
op_star
id|vp
op_assign
id|LINVFS_GET_VP
c_func
(paren
id|dentry-&gt;d_inode
)paren
suffix:semicolon
r_char
op_star
id|attr
op_assign
(paren
r_char
op_star
)paren
id|name
suffix:semicolon
id|attrnames_t
op_star
id|namesp
suffix:semicolon
r_int
id|xflags
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
id|namesp
op_assign
id|attr_lookup_namespace
c_func
(paren
id|attr
comma
id|attr_namespaces
comma
id|ATTR_NAMECOUNT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|namesp
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|attr
op_add_assign
id|namesp-&gt;attr_namelen
suffix:semicolon
id|error
op_assign
id|namesp
op_member_access_from_pointer
id|attr_capable
c_func
(paren
id|vp
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|xflags
op_or_assign
id|namesp-&gt;attr_flag
suffix:semicolon
r_return
id|namesp
op_member_access_from_pointer
id|attr_remove
c_func
(paren
id|vp
comma
id|attr
comma
id|xflags
)paren
suffix:semicolon
)brace
DECL|variable|linvfs_file_inode_operations
r_struct
id|inode_operations
id|linvfs_file_inode_operations
op_assign
(brace
dot
id|permission
op_assign
id|linvfs_permission
comma
dot
id|truncate
op_assign
id|linvfs_truncate
comma
dot
id|getattr
op_assign
id|linvfs_getattr
comma
dot
id|setattr
op_assign
id|linvfs_setattr
comma
dot
id|setxattr
op_assign
id|linvfs_setxattr
comma
dot
id|getxattr
op_assign
id|linvfs_getxattr
comma
dot
id|listxattr
op_assign
id|linvfs_listxattr
comma
dot
id|removexattr
op_assign
id|linvfs_removexattr
comma
)brace
suffix:semicolon
DECL|variable|linvfs_dir_inode_operations
r_struct
id|inode_operations
id|linvfs_dir_inode_operations
op_assign
(brace
dot
id|create
op_assign
id|linvfs_create
comma
dot
id|lookup
op_assign
id|linvfs_lookup
comma
dot
id|link
op_assign
id|linvfs_link
comma
dot
id|unlink
op_assign
id|linvfs_unlink
comma
dot
id|symlink
op_assign
id|linvfs_symlink
comma
dot
id|mkdir
op_assign
id|linvfs_mkdir
comma
dot
id|rmdir
op_assign
id|linvfs_rmdir
comma
dot
id|mknod
op_assign
id|linvfs_mknod
comma
dot
id|rename
op_assign
id|linvfs_rename
comma
dot
id|permission
op_assign
id|linvfs_permission
comma
dot
id|getattr
op_assign
id|linvfs_getattr
comma
dot
id|setattr
op_assign
id|linvfs_setattr
comma
dot
id|setxattr
op_assign
id|linvfs_setxattr
comma
dot
id|getxattr
op_assign
id|linvfs_getxattr
comma
dot
id|listxattr
op_assign
id|linvfs_listxattr
comma
dot
id|removexattr
op_assign
id|linvfs_removexattr
comma
)brace
suffix:semicolon
DECL|variable|linvfs_symlink_inode_operations
r_struct
id|inode_operations
id|linvfs_symlink_inode_operations
op_assign
(brace
dot
id|readlink
op_assign
id|linvfs_readlink
comma
dot
id|follow_link
op_assign
id|linvfs_follow_link
comma
dot
id|permission
op_assign
id|linvfs_permission
comma
dot
id|getattr
op_assign
id|linvfs_getattr
comma
dot
id|setattr
op_assign
id|linvfs_setattr
comma
dot
id|setxattr
op_assign
id|linvfs_setxattr
comma
dot
id|getxattr
op_assign
id|linvfs_getxattr
comma
dot
id|listxattr
op_assign
id|linvfs_listxattr
comma
dot
id|removexattr
op_assign
id|linvfs_removexattr
comma
)brace
suffix:semicolon
eof
