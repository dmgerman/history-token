multiline_comment|/*&n; *  linux/fs/attr.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  changes by Thomas Schoebel-Theuer&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/quotaops.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/time.h&gt;
multiline_comment|/* Taken over from the old code... */
multiline_comment|/* POSIX UID/GID verification for setting inode attributes. */
DECL|function|inode_change_ok
r_int
id|inode_change_ok
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|EPERM
suffix:semicolon
r_int
r_int
id|ia_valid
op_assign
id|attr-&gt;ia_valid
suffix:semicolon
multiline_comment|/* If force is set do it anyway. */
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_FORCE
)paren
r_goto
id|fine
suffix:semicolon
multiline_comment|/* Make sure a caller can chown. */
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
id|ATTR_UID
)paren
op_logical_and
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_or
id|attr-&gt;ia_uid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_CHOWN
)paren
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* Make sure caller can chgrp. */
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
id|ATTR_GID
)paren
op_logical_and
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_or
(paren
op_logical_neg
id|in_group_p
c_func
(paren
id|attr-&gt;ia_gid
)paren
op_logical_and
id|attr-&gt;ia_gid
op_ne
id|inode-&gt;i_gid
)paren
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_CHOWN
)paren
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* Make sure a caller can chmod. */
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
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
r_goto
id|error
suffix:semicolon
multiline_comment|/* Also check the setgid bit! */
r_if
c_cond
(paren
op_logical_neg
id|in_group_p
c_func
(paren
(paren
id|ia_valid
op_amp
id|ATTR_GID
)paren
ques
c_cond
id|attr-&gt;ia_gid
suffix:colon
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
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
)brace
multiline_comment|/* Check for setting the inode time. */
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
(brace
r_if
c_cond
(paren
id|current-&gt;fsuid
op_ne
id|inode-&gt;i_uid
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_FOWNER
)paren
)paren
r_goto
id|error
suffix:semicolon
)brace
id|fine
suffix:colon
id|retval
op_assign
l_int|0
suffix:semicolon
id|error
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|inode_change_ok
id|EXPORT_SYMBOL
c_func
(paren
id|inode_change_ok
)paren
suffix:semicolon
DECL|function|inode_setattr
r_int
id|inode_setattr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_int
r_int
id|ia_valid
op_assign
id|attr-&gt;ia_valid
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_SIZE
)paren
(brace
r_if
c_cond
(paren
id|attr-&gt;ia_size
op_ne
id|i_size_read
c_func
(paren
id|inode
)paren
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
r_if
c_cond
(paren
id|error
op_logical_or
(paren
id|ia_valid
op_eq
id|ATTR_SIZE
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * We skipped the truncate but must still update&n;&t;&t;&t; * timestamps&n;&t;&t;&t; */
id|ia_valid
op_or_assign
id|ATTR_MTIME
op_or
id|ATTR_CTIME
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_UID
)paren
id|inode-&gt;i_uid
op_assign
id|attr-&gt;ia_uid
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_GID
)paren
id|inode-&gt;i_gid
op_assign
id|attr-&gt;ia_gid
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_ATIME
)paren
id|inode-&gt;i_atime
op_assign
id|timespec_trunc
c_func
(paren
id|attr-&gt;ia_atime
comma
id|inode-&gt;i_sb-&gt;s_time_gran
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MTIME
)paren
id|inode-&gt;i_mtime
op_assign
id|timespec_trunc
c_func
(paren
id|attr-&gt;ia_mtime
comma
id|inode-&gt;i_sb-&gt;s_time_gran
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_CTIME
)paren
id|inode-&gt;i_ctime
op_assign
id|timespec_trunc
c_func
(paren
id|attr-&gt;ia_ctime
comma
id|inode-&gt;i_sb-&gt;s_time_gran
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
(brace
id|umode_t
id|mode
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
id|mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
)brace
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|inode_setattr
id|EXPORT_SYMBOL
c_func
(paren
id|inode_setattr
)paren
suffix:semicolon
DECL|function|setattr_mask
r_int
id|setattr_mask
c_func
(paren
r_int
r_int
id|ia_valid
)paren
(brace
r_int
r_int
id|dn_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_UID
)paren
id|dn_mask
op_or_assign
id|DN_ATTRIB
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_GID
)paren
id|dn_mask
op_or_assign
id|DN_ATTRIB
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_SIZE
)paren
id|dn_mask
op_or_assign
id|DN_MODIFY
suffix:semicolon
multiline_comment|/* both times implies a utime(s) call */
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
(paren
id|ATTR_ATIME
op_or
id|ATTR_MTIME
)paren
)paren
op_eq
(paren
id|ATTR_ATIME
op_or
id|ATTR_MTIME
)paren
)paren
id|dn_mask
op_or_assign
id|DN_ATTRIB
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_ATIME
)paren
id|dn_mask
op_or_assign
id|DN_ACCESS
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MTIME
)paren
id|dn_mask
op_or_assign
id|DN_MODIFY
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
id|dn_mask
op_or_assign
id|DN_ATTRIB
suffix:semicolon
r_return
id|dn_mask
suffix:semicolon
)brace
DECL|function|notify_change
r_int
id|notify_change
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
id|mode_t
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|timespec
id|now
op_assign
id|current_fs_time
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_int
r_int
id|ia_valid
op_assign
id|attr-&gt;ia_valid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|attr-&gt;ia_ctime
op_assign
id|now
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ia_valid
op_amp
id|ATTR_ATIME_SET
)paren
)paren
id|attr-&gt;ia_atime
op_assign
id|now
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ia_valid
op_amp
id|ATTR_MTIME_SET
)paren
)paren
id|attr-&gt;ia_mtime
op_assign
id|now
suffix:semicolon
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_KILL_SUID
)paren
(brace
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_KILL_SUID
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|S_ISUID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
)paren
(brace
id|ia_valid
op_assign
id|attr-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|attr-&gt;ia_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
)brace
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|S_ISUID
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ia_valid
op_amp
id|ATTR_KILL_SGID
)paren
(brace
id|attr-&gt;ia_valid
op_and_assign
op_complement
id|ATTR_KILL_SGID
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mode
op_amp
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
op_eq
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ia_valid
op_amp
id|ATTR_MODE
)paren
)paren
(brace
id|ia_valid
op_assign
id|attr-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|attr-&gt;ia_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
)brace
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|S_ISGID
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;ia_valid
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_op
op_logical_and
id|inode-&gt;i_op-&gt;setattr
)paren
(brace
id|error
op_assign
id|security_inode_setattr
c_func
(paren
id|dentry
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|inode-&gt;i_op
op_member_access_from_pointer
id|setattr
c_func
(paren
id|dentry
comma
id|attr
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|inode_change_ok
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|security_inode_setattr
c_func
(paren
id|dentry
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
(paren
id|ia_valid
op_amp
id|ATTR_UID
op_logical_and
id|attr-&gt;ia_uid
op_ne
id|inode-&gt;i_uid
)paren
op_logical_or
(paren
id|ia_valid
op_amp
id|ATTR_GID
op_logical_and
id|attr-&gt;ia_gid
op_ne
id|inode-&gt;i_gid
)paren
)paren
id|error
op_assign
id|DQUOT_TRANSFER
c_func
(paren
id|inode
comma
id|attr
)paren
ques
c_cond
op_minus
id|EDQUOT
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|inode_setattr
c_func
(paren
id|inode
comma
id|attr
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_int
r_int
id|dn_mask
op_assign
id|setattr_mask
c_func
(paren
id|ia_valid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn_mask
)paren
id|dnotify_parent
c_func
(paren
id|dentry
comma
id|dn_mask
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|variable|notify_change
id|EXPORT_SYMBOL
c_func
(paren
id|notify_change
)paren
suffix:semicolon
eof
