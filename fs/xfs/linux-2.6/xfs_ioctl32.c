multiline_comment|/*&n; * Copyright (c) 2004 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/ioctl32.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;xfs_types.h&quot;
macro_line|#include &quot;xfs_fs.h&quot;
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
DECL|function|xfs_ioctl32_bulkstat
id|xfs_ioctl32_bulkstat
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
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
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|xfs_ioctl32_trans
r_struct
id|ioctl_trans
id|xfs_ioctl32_trans
(braket
)braket
op_assign
(brace
(brace
id|XFS_IOC_DIOINFO
comma
)brace
comma
(brace
id|XFS_IOC_FSGEOMETRY_V1
comma
)brace
comma
(brace
id|XFS_IOC_FSGEOMETRY
comma
)brace
comma
(brace
id|XFS_IOC_GETVERSION
comma
)brace
comma
(brace
id|XFS_IOC_GETXFLAGS
comma
)brace
comma
(brace
id|XFS_IOC_SETXFLAGS
comma
)brace
comma
(brace
id|XFS_IOC_FSGETXATTR
comma
)brace
comma
(brace
id|XFS_IOC_FSSETXATTR
comma
)brace
comma
(brace
id|XFS_IOC_FSGETXATTRA
comma
)brace
comma
(brace
id|XFS_IOC_FSSETDM
comma
)brace
comma
(brace
id|XFS_IOC_GETBMAP
comma
)brace
comma
(brace
id|XFS_IOC_GETBMAPA
comma
)brace
comma
(brace
id|XFS_IOC_GETBMAPX
comma
)brace
comma
multiline_comment|/* not handled&n;&t;{ XFS_IOC_FD_TO_HANDLE, },&n;&t;{ XFS_IOC_PATH_TO_HANDLE, },&n;&t;{ XFS_IOC_PATH_TO_HANDLE, },&n;&t;{ XFS_IOC_PATH_TO_FSHANDLE, },&n;&t;{ XFS_IOC_OPEN_BY_HANDLE, },&n;&t;{ XFS_IOC_FSSETDM_BY_HANDLE, },&n;&t;{ XFS_IOC_READLINK_BY_HANDLE, },&n;&t;{ XFS_IOC_ATTRLIST_BY_HANDLE, },&n;&t;{ XFS_IOC_ATTRMULTI_BY_HANDLE, },&n;*/
(brace
id|XFS_IOC_FSCOUNTS
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_SET_RESBLKS
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_GET_RESBLKS
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_FSGROWFSDATA
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_FSGROWFSLOG
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_FSGROWFSRT
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_FREEZE
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_THAW
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_GOINGDOWN
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_ERROR_INJECTION
comma
l_int|NULL
comma
)brace
comma
(brace
id|XFS_IOC_ERROR_CLEARALL
comma
l_int|NULL
comma
)brace
comma
macro_line|#ifndef BROKEN_X86_ALIGNMENT
multiline_comment|/* xfs_flock_t and xfs_bstat_t have wrong u32 vs u64 alignment */
(brace
id|XFS_IOC_ALLOCSP
comma
)brace
comma
(brace
id|XFS_IOC_FREESP
comma
)brace
comma
(brace
id|XFS_IOC_RESVSP
comma
)brace
comma
(brace
id|XFS_IOC_UNRESVSP
comma
)brace
comma
(brace
id|XFS_IOC_ALLOCSP64
comma
)brace
comma
(brace
id|XFS_IOC_FREESP64
comma
)brace
comma
(brace
id|XFS_IOC_RESVSP64
comma
)brace
comma
(brace
id|XFS_IOC_UNRESVSP64
comma
)brace
comma
(brace
id|XFS_IOC_SWAPEXT
comma
)brace
comma
(brace
id|XFS_IOC_FSBULKSTAT_SINGLE
comma
id|xfs_ioctl32_bulkstat
)brace
comma
(brace
id|XFS_IOC_FSBULKSTAT
comma
id|xfs_ioctl32_bulkstat
)brace
comma
(brace
id|XFS_IOC_FSINUMBERS
comma
id|xfs_ioctl32_bulkstat
)brace
comma
macro_line|#endif
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|xfs_ioctl32_init
id|xfs_ioctl32_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|xfs_ioctl32_trans
(braket
id|i
)braket
dot
id|cmd
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|error
op_assign
id|register_ioctl32_conversion
c_func
(paren
id|xfs_ioctl32_trans
(braket
id|i
)braket
dot
id|cmd
comma
id|xfs_ioctl32_trans
(braket
id|i
)braket
dot
id|handler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_while
c_loop
(paren
op_decrement
id|i
)paren
id|unregister_ioctl32_conversion
c_func
(paren
id|xfs_ioctl32_trans
(braket
id|i
)braket
dot
id|cmd
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_void
DECL|function|xfs_ioctl32_exit
id|xfs_ioctl32_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|xfs_ioctl32_trans
(braket
id|i
)braket
dot
id|cmd
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|unregister_ioctl32_conversion
c_func
(paren
id|xfs_ioctl32_trans
(braket
id|i
)braket
dot
id|cmd
)paren
suffix:semicolon
)brace
eof
