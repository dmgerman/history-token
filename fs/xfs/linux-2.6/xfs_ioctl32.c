multiline_comment|/*&n; * Copyright (c) 2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/ioctl32.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;xfs.h&quot;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
macro_line|#include &quot;xfs_vfs.h&quot;
macro_line|#include &quot;xfs_vnode.h&quot;
macro_line|#include &quot;xfs_dfrag.h&quot;
macro_line|#if defined(CONFIG_IA64) || defined(CONFIG_X86_64)
DECL|macro|BROKEN_X86_ALIGNMENT
mdefine_line|#define BROKEN_X86_ALIGNMENT
macro_line|#else
DECL|struct|xfs_fsop_bulkreq32
r_typedef
r_struct
id|xfs_fsop_bulkreq32
(brace
DECL|member|lastip
id|compat_uptr_t
id|lastip
suffix:semicolon
multiline_comment|/* last inode # pointer&t;&t;*/
DECL|member|icount
id|__s32
id|icount
suffix:semicolon
multiline_comment|/* count of entries in buffer&t;*/
DECL|member|ubuffer
id|compat_uptr_t
id|ubuffer
suffix:semicolon
multiline_comment|/* user buffer for inode desc.&t;*/
DECL|member|ocount
id|__s32
id|ocount
suffix:semicolon
multiline_comment|/* output count pointer&t;&t;*/
DECL|typedef|xfs_fsop_bulkreq32_t
)brace
id|xfs_fsop_bulkreq32_t
suffix:semicolon
r_static
r_int
r_int
DECL|function|xfs_ioctl32_bulkstat
id|xfs_ioctl32_bulkstat
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
id|xfs_fsop_bulkreq32_t
id|__user
op_star
id|p32
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
id|xfs_fsop_bulkreq_t
id|__user
op_star
id|p
op_assign
id|compat_alloc_user_space
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|u32
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|addr
comma
op_amp
id|p32-&gt;lastip
)paren
op_logical_or
id|put_user
c_func
(paren
id|compat_ptr
c_func
(paren
id|addr
)paren
comma
op_amp
id|p-&gt;lastip
)paren
op_logical_or
id|copy_in_user
c_func
(paren
op_amp
id|p-&gt;icount
comma
op_amp
id|p32-&gt;icount
comma
r_sizeof
(paren
id|s32
)paren
)paren
op_logical_or
id|get_user
c_func
(paren
id|addr
comma
op_amp
id|p32-&gt;ubuffer
)paren
op_logical_or
id|put_user
c_func
(paren
id|compat_ptr
c_func
(paren
id|addr
)paren
comma
op_amp
id|p-&gt;ubuffer
)paren
op_logical_or
id|get_user
c_func
(paren
id|addr
comma
op_amp
id|p32-&gt;ocount
)paren
op_logical_or
id|put_user
c_func
(paren
id|compat_ptr
c_func
(paren
id|addr
)paren
comma
op_amp
id|p-&gt;ocount
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
)brace
macro_line|#endif
r_static
r_int
DECL|function|__xfs_compat_ioctl
id|__xfs_compat_ioctl
c_func
(paren
r_int
id|mode
comma
r_struct
id|file
op_star
id|f
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|f-&gt;f_dentry-&gt;d_inode
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|XFS_IOC_DIOINFO
suffix:colon
r_case
id|XFS_IOC_FSGEOMETRY_V1
suffix:colon
r_case
id|XFS_IOC_FSGEOMETRY
suffix:colon
r_case
id|XFS_IOC_GETVERSION
suffix:colon
r_case
id|XFS_IOC_GETXFLAGS
suffix:colon
r_case
id|XFS_IOC_SETXFLAGS
suffix:colon
r_case
id|XFS_IOC_FSGETXATTR
suffix:colon
r_case
id|XFS_IOC_FSSETXATTR
suffix:colon
r_case
id|XFS_IOC_FSGETXATTRA
suffix:colon
r_case
id|XFS_IOC_FSSETDM
suffix:colon
r_case
id|XFS_IOC_GETBMAP
suffix:colon
r_case
id|XFS_IOC_GETBMAPA
suffix:colon
r_case
id|XFS_IOC_GETBMAPX
suffix:colon
multiline_comment|/* not handled&n;&t;case XFS_IOC_FD_TO_HANDLE:&n;&t;case XFS_IOC_PATH_TO_HANDLE:&n;&t;case XFS_IOC_PATH_TO_HANDLE:&n;&t;case XFS_IOC_PATH_TO_FSHANDLE:&n;&t;case XFS_IOC_OPEN_BY_HANDLE:&n;&t;case XFS_IOC_FSSETDM_BY_HANDLE:&n;&t;case XFS_IOC_READLINK_BY_HANDLE:&n;&t;case XFS_IOC_ATTRLIST_BY_HANDLE:&n;&t;case XFS_IOC_ATTRMULTI_BY_HANDLE:&n;*/
r_case
id|XFS_IOC_FSCOUNTS
suffix:colon
r_case
id|XFS_IOC_SET_RESBLKS
suffix:colon
r_case
id|XFS_IOC_GET_RESBLKS
suffix:colon
r_case
id|XFS_IOC_FSGROWFSDATA
suffix:colon
r_case
id|XFS_IOC_FSGROWFSLOG
suffix:colon
r_case
id|XFS_IOC_FSGROWFSRT
suffix:colon
r_case
id|XFS_IOC_FREEZE
suffix:colon
r_case
id|XFS_IOC_THAW
suffix:colon
r_case
id|XFS_IOC_GOINGDOWN
suffix:colon
r_case
id|XFS_IOC_ERROR_INJECTION
suffix:colon
r_case
id|XFS_IOC_ERROR_CLEARALL
suffix:colon
r_break
suffix:semicolon
macro_line|#ifndef BROKEN_X86_ALIGNMENT
multiline_comment|/* xfs_flock_t and xfs_bstat_t have wrong u32 vs u64 alignment */
r_case
id|XFS_IOC_ALLOCSP
suffix:colon
r_case
id|XFS_IOC_FREESP
suffix:colon
r_case
id|XFS_IOC_RESVSP
suffix:colon
r_case
id|XFS_IOC_UNRESVSP
suffix:colon
r_case
id|XFS_IOC_ALLOCSP64
suffix:colon
r_case
id|XFS_IOC_FREESP64
suffix:colon
r_case
id|XFS_IOC_RESVSP64
suffix:colon
r_case
id|XFS_IOC_UNRESVSP64
suffix:colon
r_case
id|XFS_IOC_SWAPEXT
suffix:colon
r_break
suffix:semicolon
r_case
id|XFS_IOC_FSBULKSTAT_SINGLE
suffix:colon
r_case
id|XFS_IOC_FSBULKSTAT
suffix:colon
r_case
id|XFS_IOC_FSINUMBERS
suffix:colon
id|arg
op_assign
id|xfs_ioctl32_bulkstat
c_func
(paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
id|VOP_IOCTL
c_func
(paren
id|vp
comma
id|inode
comma
id|f
comma
id|mode
comma
id|cmd
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
id|error
)paren
suffix:semicolon
id|VMODIFY
c_func
(paren
id|vp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|xfs_compat_ioctl
r_int
id|xfs_compat_ioctl
c_func
(paren
r_struct
id|file
op_star
id|f
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|__xfs_compat_ioctl
c_func
(paren
l_int|0
comma
id|f
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|xfs_compat_invis_ioctl
r_int
id|xfs_compat_invis_ioctl
c_func
(paren
r_struct
id|file
op_star
id|f
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|__xfs_compat_ioctl
c_func
(paren
id|IO_INVIS
comma
id|f
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
eof
