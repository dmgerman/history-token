multiline_comment|/*&n; * linux/fs/ext2/ioctl.c&n; *&n; * Copyright (C) 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; */
macro_line|#include &quot;ext2.h&quot;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|ext2_ioctl
r_int
id|ext2_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|ext2_inode_info
op_star
id|ei
op_assign
id|EXT2_I
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|ext2_debug
(paren
l_string|&quot;cmd = %u, arg = %lu&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|EXT2_IOC_GETFLAGS
suffix:colon
id|flags
op_assign
id|ei-&gt;i_flags
op_amp
id|EXT2_FL_USER_VISIBLE
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|flags
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|EXT2_IOC_SETFLAGS
suffix:colon
(brace
r_int
r_int
id|oldflags
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|flags
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|oldflags
op_assign
id|ei-&gt;i_flags
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The IMMUTABLE and APPEND_ONLY flags can only be changed by&n;&t;&t; * the relevant capability.&n;&t;&t; *&n;&t;&t; * This test looks nicer. Thanks to Pauline Middelink&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|flags
op_xor
id|oldflags
)paren
op_amp
(paren
id|EXT2_APPEND_FL
op_or
id|EXT2_IMMUTABLE_FL
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_LINUX_IMMUTABLE
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|flags
op_assign
id|flags
op_amp
id|EXT2_FL_USER_MODIFIABLE
suffix:semicolon
id|flags
op_or_assign
id|oldflags
op_amp
op_complement
id|EXT2_FL_USER_MODIFIABLE
suffix:semicolon
id|ei-&gt;i_flags
op_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT2_SYNC_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_SYNC
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_SYNC
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT2_APPEND_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_APPEND
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_APPEND
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT2_IMMUTABLE_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_IMMUTABLE
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_IMMUTABLE
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT2_NOATIME_FL
)paren
id|inode-&gt;i_flags
op_or_assign
id|S_NOATIME
suffix:semicolon
r_else
id|inode-&gt;i_flags
op_and_assign
op_complement
id|S_NOATIME
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|EXT2_IOC_GETVERSION
suffix:colon
r_return
id|put_user
c_func
(paren
id|inode-&gt;i_generation
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|EXT2_IOC_SETVERSION
suffix:colon
r_if
c_cond
(paren
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|IS_RDONLY
c_func
(paren
id|inode
)paren
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|inode-&gt;i_generation
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
)brace
eof
