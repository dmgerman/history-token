multiline_comment|/*&n; *  ioctl.c&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *  Modified 1997 Peter Waltenberg, Bill Hawes, David Woodhouse for 2.1 dcache&n; *  Modified 1998, 1999 Wolfram Pienkoss for NLS&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &quot;ncplib_kernel.h&quot;
multiline_comment|/* maximum limit for ncp_objectname_ioctl */
DECL|macro|NCP_OBJECT_NAME_MAX_LEN
mdefine_line|#define NCP_OBJECT_NAME_MAX_LEN&t;4096
multiline_comment|/* maximum limit for ncp_privatedata_ioctl */
DECL|macro|NCP_PRIVATE_DATA_MAX_LEN
mdefine_line|#define NCP_PRIVATE_DATA_MAX_LEN 8192
multiline_comment|/* maximum negotiable packet size */
DECL|macro|NCP_PACKET_SIZE_INTERNAL
mdefine_line|#define NCP_PACKET_SIZE_INTERNAL 65536
DECL|function|ncp_ioctl
r_int
id|ncp_ioctl
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
id|ncp_server
op_star
id|server
op_assign
id|NCP_SERVER
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|result
suffix:semicolon
r_struct
id|ncp_ioctl_request
id|request
suffix:semicolon
r_char
op_star
id|bouncebuffer
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NCP_IOC_NCPREQUEST
suffix:colon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
r_struct
id|ncp_ioctl_request
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|request.function
OG
l_int|255
)paren
op_logical_or
(paren
id|request.size
OG
id|NCP_PACKET_SIZE
op_minus
r_sizeof
(paren
r_struct
id|ncp_request_header
)paren
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bouncebuffer
op_assign
id|vmalloc
c_func
(paren
id|NCP_PACKET_SIZE_INTERNAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bouncebuffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|bouncebuffer
comma
id|request.data
comma
id|request.size
)paren
)paren
(brace
id|vfree
c_func
(paren
id|bouncebuffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ncp_lock_server
c_func
(paren
id|server
)paren
suffix:semicolon
multiline_comment|/* FIXME: We hack around in the server&squot;s structures&n;&t;&t;   here to be able to use ncp_request */
id|server-&gt;has_subfunction
op_assign
l_int|0
suffix:semicolon
id|server-&gt;current_size
op_assign
id|request.size
suffix:semicolon
id|memcpy
c_func
(paren
id|server-&gt;packet
comma
id|bouncebuffer
comma
id|request.size
)paren
suffix:semicolon
id|result
op_assign
id|ncp_request2
c_func
(paren
id|server
comma
id|request.function
comma
id|bouncebuffer
comma
id|NCP_PACKET_SIZE_INTERNAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_else
id|result
op_assign
id|server-&gt;reply_size
suffix:semicolon
id|ncp_unlock_server
c_func
(paren
id|server
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ncp_ioctl: copy %d bytes&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|request.data
comma
id|bouncebuffer
comma
id|result
)paren
)paren
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|vfree
c_func
(paren
id|bouncebuffer
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
r_case
id|NCP_IOC_CONN_LOGGED_IN
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|server-&gt;m.int_flags
op_amp
id|NCP_IMOUNT_LOGGEDIN_POSSIBLE
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;root_setuped
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|server-&gt;root_setuped
op_assign
l_int|1
suffix:semicolon
r_return
id|ncp_conn_logged_in
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_case
id|NCP_IOC_GET_FS_INFO
suffix:colon
(brace
r_struct
id|ncp_fs_info
id|info
suffix:semicolon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
(paren
r_struct
id|ncp_fs_info
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|info.version
op_ne
id|NCP_GET_FS_INFO_VERSION
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;info.version invalid: %d&bslash;n&quot;
comma
id|info.version
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* TODO: info.addr = server-&gt;m.serv_addr; */
id|info.mounted_uid
op_assign
id|NEW_TO_OLD_UID
c_func
(paren
id|server-&gt;m.mounted_uid
)paren
suffix:semicolon
id|info.connection
op_assign
id|server-&gt;connection
suffix:semicolon
id|info.buffer_size
op_assign
id|server-&gt;buffer_size
suffix:semicolon
id|info.volume_number
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
suffix:semicolon
id|info.directory_id
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|DosDirNum
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ncp_fs_info
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_GET_FS_INFO_V2
suffix:colon
(brace
r_struct
id|ncp_fs_info_v2
id|info2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info2
comma
(paren
r_struct
id|ncp_fs_info_v2
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|info2
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|info2.version
op_ne
id|NCP_GET_FS_INFO_VERSION_V2
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;info.version invalid: %d&bslash;n&quot;
comma
id|info2.version
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|info2.mounted_uid
op_assign
id|server-&gt;m.mounted_uid
suffix:semicolon
id|info2.connection
op_assign
id|server-&gt;connection
suffix:semicolon
id|info2.buffer_size
op_assign
id|server-&gt;buffer_size
suffix:semicolon
id|info2.volume_number
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
suffix:semicolon
id|info2.directory_id
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|DosDirNum
suffix:semicolon
id|info2.dummy1
op_assign
id|info2.dummy2
op_assign
id|info2.dummy3
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ncp_fs_info_v2
op_star
)paren
id|arg
comma
op_amp
id|info2
comma
r_sizeof
(paren
id|info2
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_GETMOUNTUID2
suffix:colon
(brace
r_int
r_int
id|tmp
op_assign
id|server-&gt;m.mounted_uid
suffix:semicolon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
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
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_GETROOT
suffix:colon
(brace
r_struct
id|ncp_setroot_ioctl
id|sr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|server-&gt;m.mounted_vol
(braket
l_int|0
)braket
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
op_assign
id|inode-&gt;i_sb-&gt;s_root
suffix:semicolon
r_if
c_cond
(paren
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
r_if
c_cond
(paren
id|inode
)paren
(brace
id|sr.volNumber
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
suffix:semicolon
id|sr.dirEntNum
op_assign
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
suffix:semicolon
id|sr
dot
r_namespace
op_assign
id|server-&gt;name_space
(braket
id|sr.volNumber
)braket
suffix:semicolon
)brace
r_else
id|DPRINTK
c_func
(paren
l_string|&quot;ncpfs: s_root-&gt;d_inode==NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|DPRINTK
c_func
(paren
l_string|&quot;ncpfs: s_root==NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|sr.volNumber
op_assign
op_minus
l_int|1
suffix:semicolon
id|sr
dot
r_namespace
op_assign
l_int|0
suffix:semicolon
id|sr.dirEntNum
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ncp_setroot_ioctl
op_star
)paren
id|arg
comma
op_amp
id|sr
comma
r_sizeof
(paren
id|sr
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_SETROOT
suffix:colon
(brace
r_struct
id|ncp_setroot_ioctl
id|sr
suffix:semicolon
r_int
r_int
id|vnum
comma
id|de
comma
id|dosde
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|server-&gt;root_setuped
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sr
comma
(paren
r_struct
id|ncp_setroot_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|sr
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|sr.volNumber
OL
l_int|0
)paren
(brace
id|server-&gt;m.mounted_vol
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|vnum
op_assign
id|NCP_NUMBER_OF_VOLUMES
suffix:semicolon
id|de
op_assign
l_int|0
suffix:semicolon
id|dosde
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sr.volNumber
op_ge
id|NCP_NUMBER_OF_VOLUMES
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_struct
id|nw_info_struct
id|ni
suffix:semicolon
r_if
c_cond
(paren
id|ncp_mount_subdir
c_func
(paren
id|server
comma
op_amp
id|ni
comma
id|sr.volNumber
comma
id|sr
dot
r_namespace
comma
id|sr.dirEntNum
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|vnum
op_assign
id|ni.volNumber
suffix:semicolon
id|de
op_assign
id|ni.dirEntNum
suffix:semicolon
id|dosde
op_assign
id|ni.DosDirNum
suffix:semicolon
)brace
id|dentry
op_assign
id|inode-&gt;i_sb-&gt;s_root
suffix:semicolon
id|server-&gt;root_setuped
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
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
r_if
c_cond
(paren
id|inode
)paren
(brace
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|volNumber
op_assign
id|vnum
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|dirEntNum
op_assign
id|de
suffix:semicolon
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|DosDirNum
op_assign
id|dosde
suffix:semicolon
)brace
r_else
id|DPRINTK
c_func
(paren
l_string|&quot;ncpfs: s_root-&gt;d_inode==NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|DPRINTK
c_func
(paren
l_string|&quot;ncpfs: s_root==NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NCPFS_PACKET_SIGNING&t;
r_case
id|NCP_IOC_SIGN_INIT
suffix:colon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
)paren
(brace
r_if
c_cond
(paren
id|server-&gt;sign_wanted
)paren
(brace
r_struct
id|ncp_sign_init
id|sign
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sign
comma
(paren
r_struct
id|ncp_sign_init
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|sign
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memcpy
c_func
(paren
id|server-&gt;sign_root
comma
id|sign.sign_root
comma
l_int|8
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|server-&gt;sign_last
comma
id|sign.sign_last
comma
l_int|16
)paren
suffix:semicolon
id|server-&gt;sign_active
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ignore when signatures not wanted */
)brace
r_else
(brace
id|server-&gt;sign_active
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|NCP_IOC_SIGN_WANTED
suffix:colon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|server-&gt;sign_wanted
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
r_return
l_int|0
suffix:semicolon
r_case
id|NCP_IOC_SET_SIGN_WANTED
suffix:colon
(brace
r_int
id|newstate
suffix:semicolon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
multiline_comment|/* get only low 8 bits... */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|newstate
comma
(paren
r_int
r_char
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;sign_active
)paren
(brace
multiline_comment|/* cannot turn signatures OFF when active */
r_if
c_cond
(paren
op_logical_neg
id|newstate
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|server-&gt;sign_wanted
op_assign
id|newstate
op_ne
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NCPFS_PACKET_SIGNING */
macro_line|#ifdef CONFIG_NCPFS_IOCTL_LOCKING
r_case
id|NCP_IOC_LOCKUNLOCK
suffix:colon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
(brace
r_struct
id|ncp_lock_ioctl
id|rqdata
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rqdata
comma
(paren
r_struct
id|ncp_lock_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|rqdata
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|rqdata.origin
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* check for cmd */
r_switch
c_cond
(paren
id|rqdata.cmd
)paren
(brace
r_case
id|NCP_LOCK_EX
suffix:colon
r_case
id|NCP_LOCK_SH
suffix:colon
r_if
c_cond
(paren
id|rqdata.timeout
op_eq
l_int|0
)paren
id|rqdata.timeout
op_assign
id|NCP_LOCK_DEFAULT_TIMEOUT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rqdata.timeout
OG
id|NCP_LOCK_MAX_TIMEOUT
)paren
id|rqdata.timeout
op_assign
id|NCP_LOCK_MAX_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NCP_LOCK_LOG
suffix:colon
id|rqdata.timeout
op_assign
id|NCP_LOCK_DEFAULT_TIMEOUT
suffix:semicolon
multiline_comment|/* has no effect */
r_case
id|NCP_LOCK_CLEAR
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* locking needs both read and write access */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ncp_make_open
c_func
(paren
id|inode
comma
id|O_RDWR
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
id|result
suffix:semicolon
)brace
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ncp_conn_valid
c_func
(paren
id|server
)paren
)paren
r_goto
id|outrel
suffix:semicolon
id|result
op_assign
op_minus
id|EISDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_goto
id|outrel
suffix:semicolon
r_if
c_cond
(paren
id|rqdata.cmd
op_eq
id|NCP_LOCK_CLEAR
)paren
(brace
id|result
op_assign
id|ncp_ClearPhysicalRecord
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|rqdata.offset
comma
id|rqdata.length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no such lock */
)brace
r_else
(brace
r_int
id|lockcmd
suffix:semicolon
r_switch
c_cond
(paren
id|rqdata.cmd
)paren
(brace
r_case
id|NCP_LOCK_EX
suffix:colon
id|lockcmd
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NCP_LOCK_SH
suffix:colon
id|lockcmd
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|lockcmd
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_assign
id|ncp_LogPhysicalRecord
c_func
(paren
id|NCP_SERVER
c_func
(paren
id|inode
)paren
comma
id|NCP_FINFO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|file_handle
comma
id|lockcmd
comma
id|rqdata.offset
comma
id|rqdata.length
comma
id|rqdata.timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
id|result
op_assign
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|outrel
suffix:colon
id|ncp_inode_close
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_NCPFS_IOCTL_LOCKING */
r_case
id|NCP_IOC_GETOBJECTNAME
suffix:colon
r_if
c_cond
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
(brace
r_struct
id|ncp_objectname_ioctl
id|user
suffix:semicolon
r_int
id|outl
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user
comma
(paren
r_struct
id|ncp_objectname_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|user.auth_type
op_assign
id|server-&gt;auth.auth_type
suffix:semicolon
id|outl
op_assign
id|user.object_name_len
suffix:semicolon
id|user.object_name_len
op_assign
id|server-&gt;auth.object_name_len
suffix:semicolon
r_if
c_cond
(paren
id|outl
OG
id|user.object_name_len
)paren
id|outl
op_assign
id|user.object_name_len
suffix:semicolon
r_if
c_cond
(paren
id|outl
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|user.object_name
comma
id|server-&gt;auth.object_name
comma
id|outl
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ncp_objectname_ioctl
op_star
)paren
id|arg
comma
op_amp
id|user
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_SETOBJECTNAME
suffix:colon
r_if
c_cond
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
(brace
r_struct
id|ncp_objectname_ioctl
id|user
suffix:semicolon
r_void
op_star
id|newname
suffix:semicolon
r_void
op_star
id|oldname
suffix:semicolon
r_int
id|oldnamelen
suffix:semicolon
r_void
op_star
id|oldprivate
suffix:semicolon
r_int
id|oldprivatelen
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user
comma
(paren
r_struct
id|ncp_objectname_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|user.object_name_len
OG
id|NCP_OBJECT_NAME_MAX_LEN
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|user.object_name_len
)paren
(brace
id|newname
op_assign
id|ncp_kmalloc
c_func
(paren
id|user.object_name_len
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newname
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|newname
comma
id|user.object_name
comma
id|user.object_name_len
)paren
)paren
(brace
id|ncp_kfree_s
c_func
(paren
id|newname
comma
id|user.object_name_len
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
(brace
id|newname
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* enter critical section */
multiline_comment|/* maybe that kfree can sleep so do that this way */
multiline_comment|/* it is at least more SMP friendly (in future...) */
id|oldname
op_assign
id|server-&gt;auth.object_name
suffix:semicolon
id|oldnamelen
op_assign
id|server-&gt;auth.object_name_len
suffix:semicolon
id|oldprivate
op_assign
id|server-&gt;priv.data
suffix:semicolon
id|oldprivatelen
op_assign
id|server-&gt;priv.len
suffix:semicolon
id|server-&gt;auth.auth_type
op_assign
id|user.auth_type
suffix:semicolon
id|server-&gt;auth.object_name_len
op_assign
id|user.object_name_len
suffix:semicolon
id|server-&gt;auth.object_name
op_assign
id|user.object_name
suffix:semicolon
id|server-&gt;priv.len
op_assign
l_int|0
suffix:semicolon
id|server-&gt;priv.data
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* leave critical section */
r_if
c_cond
(paren
id|oldprivate
)paren
id|ncp_kfree_s
c_func
(paren
id|oldprivate
comma
id|oldprivatelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldname
)paren
id|ncp_kfree_s
c_func
(paren
id|oldname
comma
id|oldnamelen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_GETPRIVATEDATA
suffix:colon
r_if
c_cond
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
(brace
r_struct
id|ncp_privatedata_ioctl
id|user
suffix:semicolon
r_int
id|outl
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user
comma
(paren
r_struct
id|ncp_privatedata_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|outl
op_assign
id|user.len
suffix:semicolon
id|user.len
op_assign
id|server-&gt;priv.len
suffix:semicolon
r_if
c_cond
(paren
id|outl
OG
id|user.len
)paren
id|outl
op_assign
id|user.len
suffix:semicolon
r_if
c_cond
(paren
id|outl
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|user.data
comma
id|server-&gt;priv.data
comma
id|outl
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ncp_privatedata_ioctl
op_star
)paren
id|arg
comma
op_amp
id|user
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_SETPRIVATEDATA
suffix:colon
r_if
c_cond
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
(brace
r_struct
id|ncp_privatedata_ioctl
id|user
suffix:semicolon
r_void
op_star
r_new
suffix:semicolon
r_void
op_star
id|old
suffix:semicolon
r_int
id|oldlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user
comma
(paren
r_struct
id|ncp_privatedata_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|user.len
OG
id|NCP_PRIVATE_DATA_MAX_LEN
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|user.len
)paren
(brace
r_new
op_assign
id|ncp_kmalloc
c_func
(paren
id|user.len
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
r_new
comma
id|user.data
comma
id|user.len
)paren
)paren
(brace
id|ncp_kfree_s
c_func
(paren
r_new
comma
id|user.len
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
(brace
r_new
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* enter critical section */
id|old
op_assign
id|server-&gt;priv.data
suffix:semicolon
id|oldlen
op_assign
id|server-&gt;priv.len
suffix:semicolon
id|server-&gt;priv.len
op_assign
id|user.len
suffix:semicolon
id|server-&gt;priv.data
op_assign
r_new
suffix:semicolon
multiline_comment|/* leave critical section */
r_if
c_cond
(paren
id|old
)paren
id|ncp_kfree_s
c_func
(paren
id|old
comma
id|oldlen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NCPFS_NLS
multiline_comment|/* Here we are select the iocharset and the codepage for NLS.&n; * Thanks Petr Vandrovec for idea and many hints.&n; */
r_case
id|NCP_IOC_SETCHARSETS
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;root_setuped
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
(brace
r_struct
id|ncp_nls_ioctl
id|user
suffix:semicolon
r_struct
id|nls_table
op_star
id|codepage
suffix:semicolon
r_struct
id|nls_table
op_star
id|iocharset
suffix:semicolon
r_struct
id|nls_table
op_star
id|oldset_io
suffix:semicolon
r_struct
id|nls_table
op_star
id|oldset_cp
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user
comma
(paren
r_struct
id|ncp_nls_ioctl
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|codepage
op_assign
l_int|NULL
suffix:semicolon
id|user.codepage
(braket
id|NCP_IOCSNAME_LEN
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user.codepage
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|user.codepage
comma
l_string|&quot;default&quot;
)paren
)paren
id|codepage
op_assign
id|load_nls_default
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|codepage
op_assign
id|load_nls
c_func
(paren
id|user.codepage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|codepage
)paren
(brace
r_return
op_minus
id|EBADRQC
suffix:semicolon
)brace
)brace
id|iocharset
op_assign
l_int|NULL
suffix:semicolon
id|user.iocharset
(braket
id|NCP_IOCSNAME_LEN
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user.iocharset
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|user.iocharset
comma
l_string|&quot;default&quot;
)paren
)paren
(brace
id|iocharset
op_assign
id|load_nls_default
c_func
(paren
)paren
suffix:semicolon
id|NCP_CLR_FLAG
c_func
(paren
id|server
comma
id|NCP_FLAG_UTF8
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|user.iocharset
comma
l_string|&quot;utf8&quot;
)paren
)paren
(brace
id|iocharset
op_assign
id|load_nls_default
c_func
(paren
)paren
suffix:semicolon
id|NCP_SET_FLAG
c_func
(paren
id|server
comma
id|NCP_FLAG_UTF8
)paren
suffix:semicolon
)brace
r_else
(brace
id|iocharset
op_assign
id|load_nls
c_func
(paren
id|user.iocharset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iocharset
)paren
(brace
id|unload_nls
c_func
(paren
id|codepage
)paren
suffix:semicolon
r_return
op_minus
id|EBADRQC
suffix:semicolon
)brace
id|NCP_CLR_FLAG
c_func
(paren
id|server
comma
id|NCP_FLAG_UTF8
)paren
suffix:semicolon
)brace
)brace
id|oldset_cp
op_assign
id|server-&gt;nls_vol
suffix:semicolon
id|server-&gt;nls_vol
op_assign
id|codepage
suffix:semicolon
id|oldset_io
op_assign
id|server-&gt;nls_io
suffix:semicolon
id|server-&gt;nls_io
op_assign
id|iocharset
suffix:semicolon
r_if
c_cond
(paren
id|oldset_cp
)paren
id|unload_nls
c_func
(paren
id|oldset_cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldset_io
)paren
id|unload_nls
c_func
(paren
id|oldset_io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_GETCHARSETS
suffix:colon
multiline_comment|/* not tested */
(brace
r_struct
id|ncp_nls_ioctl
id|user
suffix:semicolon
r_int
id|len
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|user
comma
l_int|0
comma
r_sizeof
(paren
id|user
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;nls_vol
op_logical_and
id|server-&gt;nls_vol-&gt;charset
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|server-&gt;nls_vol-&gt;charset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|NCP_IOCSNAME_LEN
)paren
id|len
op_assign
id|NCP_IOCSNAME_LEN
suffix:semicolon
id|strncpy
c_func
(paren
id|user.codepage
comma
id|server-&gt;nls_vol-&gt;charset
comma
id|len
)paren
suffix:semicolon
id|user.codepage
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|NCP_IS_FLAG
c_func
(paren
id|server
comma
id|NCP_FLAG_UTF8
)paren
)paren
id|strcpy
c_func
(paren
id|user.iocharset
comma
l_string|&quot;utf8&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|server-&gt;nls_io
op_logical_and
id|server-&gt;nls_io-&gt;charset
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|server-&gt;nls_io-&gt;charset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|NCP_IOCSNAME_LEN
)paren
id|len
op_assign
id|NCP_IOCSNAME_LEN
suffix:semicolon
id|strncpy
c_func
(paren
id|user.iocharset
comma
id|server-&gt;nls_io-&gt;charset
comma
id|len
)paren
suffix:semicolon
id|user.iocharset
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ncp_nls_ioctl
op_star
)paren
id|arg
comma
op_amp
id|user
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NCPFS_NLS */
r_case
id|NCP_IOC_SETDENTRYTTL
suffix:colon
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_WRITE
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
(brace
id|u_int32_t
id|user
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|user
comma
(paren
id|u_int32_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* 20 secs at most... */
r_if
c_cond
(paren
id|user
OG
l_int|20000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|user
op_assign
(paren
id|user
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
id|server-&gt;dentry_ttl
op_assign
id|user
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|NCP_IOC_GETDENTRYTTL
suffix:colon
(brace
id|u_int32_t
id|user
op_assign
(paren
id|server-&gt;dentry_ttl
op_star
l_int|1000
)paren
op_div
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|u_int32_t
op_star
)paren
id|arg
comma
op_amp
id|user
comma
r_sizeof
(paren
id|user
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* #ifdef CONFIG_UID16 */
multiline_comment|/* NCP_IOC_GETMOUNTUID may be same as NCP_IOC_GETMOUNTUID2,&n;           so we have this out of switch */
r_if
c_cond
(paren
id|cmd
op_eq
id|NCP_IOC_GETMOUNTUID
)paren
(brace
r_if
c_cond
(paren
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
id|current-&gt;uid
op_ne
id|server-&gt;m.mounted_uid
)paren
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|NEW_TO_OLD_UID
c_func
(paren
id|server-&gt;m.mounted_uid
)paren
comma
(paren
id|__kernel_uid_t
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* #endif */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
