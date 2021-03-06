multiline_comment|/*&n; *  ioctl.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; *  Please add a note about your changes to smbfs in the ChangeLog file.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/smb_mount.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;proto.h&quot;
r_int
DECL|function|smb_ioctl
id|smb_ioctl
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
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|smb_conn_opt
id|opt
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
id|uid16_t
id|uid16
suffix:semicolon
id|uid_t
id|uid32
suffix:semicolon
r_case
id|SMB_IOC_GETMOUNTUID
suffix:colon
id|SET_UID
c_func
(paren
id|uid16
comma
id|server-&gt;mnt-&gt;mounted_uid
)paren
suffix:semicolon
id|result
op_assign
id|put_user
c_func
(paren
id|uid16
comma
(paren
id|uid16_t
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SMB_IOC_GETMOUNTUID32
suffix:colon
id|SET_UID
c_func
(paren
id|uid32
comma
id|server-&gt;mnt-&gt;mounted_uid
)paren
suffix:semicolon
id|result
op_assign
id|put_user
c_func
(paren
id|uid32
comma
(paren
id|uid_t
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SMB_IOC_NEWCONN
suffix:colon
multiline_comment|/* arg is smb_conn_opt, or NULL if no connection was made */
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
id|smb_lock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|server-&gt;state
op_assign
id|CONN_RETRIED
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Connection attempt failed!  [%d]&bslash;n&quot;
comma
id|server-&gt;conn_error
)paren
suffix:semicolon
id|smbiod_flush
c_func
(paren
id|server
)paren
suffix:semicolon
id|smb_unlock_server
c_func
(paren
id|server
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_from_user
c_func
(paren
op_amp
id|opt
comma
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|opt
)paren
)paren
)paren
id|result
op_assign
id|smb_newconn
c_func
(paren
id|server
comma
op_amp
id|opt
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
eof
