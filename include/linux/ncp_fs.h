multiline_comment|/*&n; *  ncp_fs.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_NCP_FS_H
DECL|macro|_LINUX_NCP_FS_H
mdefine_line|#define _LINUX_NCP_FS_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ncp_fs_i.h&gt;
macro_line|#include &lt;linux/ipx.h&gt;
macro_line|#include &lt;linux/ncp_no.h&gt;
multiline_comment|/*&n; * ioctl commands&n; */
DECL|struct|ncp_ioctl_request
r_struct
id|ncp_ioctl_request
(brace
DECL|member|function
r_int
r_int
id|function
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_fs_info
r_struct
id|ncp_fs_info
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|addr
r_struct
id|sockaddr_ipx
id|addr
suffix:semicolon
DECL|member|mounted_uid
id|__kernel_uid_t
id|mounted_uid
suffix:semicolon
DECL|member|connection
r_int
id|connection
suffix:semicolon
multiline_comment|/* Connection number the server assigned us */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* The negotiated buffer size, to be&n;&t;&t;&t;&t;   used for read/write requests! */
DECL|member|volume_number
r_int
id|volume_number
suffix:semicolon
DECL|member|directory_id
id|__u32
id|directory_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_fs_info_v2
r_struct
id|ncp_fs_info_v2
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|mounted_uid
r_int
r_int
id|mounted_uid
suffix:semicolon
DECL|member|connection
r_int
r_int
id|connection
suffix:semicolon
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
DECL|member|volume_number
r_int
r_int
id|volume_number
suffix:semicolon
DECL|member|directory_id
id|__u32
id|directory_id
suffix:semicolon
DECL|member|dummy1
id|__u32
id|dummy1
suffix:semicolon
DECL|member|dummy2
id|__u32
id|dummy2
suffix:semicolon
DECL|member|dummy3
id|__u32
id|dummy3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_sign_init
r_struct
id|ncp_sign_init
(brace
DECL|member|sign_root
r_char
id|sign_root
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sign_last
r_char
id|sign_last
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_lock_ioctl
r_struct
id|ncp_lock_ioctl
(brace
DECL|macro|NCP_LOCK_LOG
mdefine_line|#define NCP_LOCK_LOG&t;0
DECL|macro|NCP_LOCK_SH
mdefine_line|#define NCP_LOCK_SH&t;1
DECL|macro|NCP_LOCK_EX
mdefine_line|#define NCP_LOCK_EX&t;2
DECL|macro|NCP_LOCK_CLEAR
mdefine_line|#define NCP_LOCK_CLEAR&t;256
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|origin
r_int
id|origin
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|macro|NCP_LOCK_DEFAULT_TIMEOUT
mdefine_line|#define NCP_LOCK_DEFAULT_TIMEOUT&t;18
DECL|macro|NCP_LOCK_MAX_TIMEOUT
mdefine_line|#define NCP_LOCK_MAX_TIMEOUT&t;&t;180
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_setroot_ioctl
r_struct
id|ncp_setroot_ioctl
(brace
DECL|member|volNumber
r_int
id|volNumber
suffix:semicolon
DECL|member|namespace
r_int
r_namespace
suffix:semicolon
DECL|member|dirEntNum
id|__u32
id|dirEntNum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_objectname_ioctl
r_struct
id|ncp_objectname_ioctl
(brace
DECL|macro|NCP_AUTH_NONE
mdefine_line|#define NCP_AUTH_NONE&t;0x00
DECL|macro|NCP_AUTH_BIND
mdefine_line|#define NCP_AUTH_BIND&t;0x31
DECL|macro|NCP_AUTH_NDS
mdefine_line|#define NCP_AUTH_NDS&t;0x32
DECL|member|auth_type
r_int
id|auth_type
suffix:semicolon
DECL|member|object_name_len
r_int
id|object_name_len
suffix:semicolon
DECL|member|object_name
r_void
op_star
id|object_name
suffix:semicolon
multiline_comment|/* an userspace data, in most cases user name */
)brace
suffix:semicolon
DECL|struct|ncp_privatedata_ioctl
r_struct
id|ncp_privatedata_ioctl
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* ~1000 for NDS */
)brace
suffix:semicolon
multiline_comment|/* NLS charsets by ioctl */
DECL|macro|NCP_IOCSNAME_LEN
mdefine_line|#define NCP_IOCSNAME_LEN 20
DECL|struct|ncp_nls_ioctl
r_struct
id|ncp_nls_ioctl
(brace
DECL|member|codepage
r_int
r_char
id|codepage
(braket
id|NCP_IOCSNAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|iocharset
r_int
r_char
id|iocharset
(braket
id|NCP_IOCSNAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCP_IOC_NCPREQUEST
mdefine_line|#define&t;NCP_IOC_NCPREQUEST&t;&t;_IOR(&squot;n&squot;, 1, struct ncp_ioctl_request)
DECL|macro|NCP_IOC_GETMOUNTUID
mdefine_line|#define&t;NCP_IOC_GETMOUNTUID&t;&t;_IOW(&squot;n&squot;, 2, __kernel_old_uid_t)
DECL|macro|NCP_IOC_GETMOUNTUID2
mdefine_line|#define NCP_IOC_GETMOUNTUID2&t;&t;_IOW(&squot;n&squot;, 2, unsigned long)
DECL|macro|NCP_IOC_CONN_LOGGED_IN
mdefine_line|#define NCP_IOC_CONN_LOGGED_IN          _IO(&squot;n&squot;, 3)
DECL|macro|NCP_GET_FS_INFO_VERSION
mdefine_line|#define NCP_GET_FS_INFO_VERSION    (1)
DECL|macro|NCP_IOC_GET_FS_INFO
mdefine_line|#define NCP_IOC_GET_FS_INFO             _IOWR(&squot;n&squot;, 4, struct ncp_fs_info)
DECL|macro|NCP_GET_FS_INFO_VERSION_V2
mdefine_line|#define NCP_GET_FS_INFO_VERSION_V2 (2)
DECL|macro|NCP_IOC_GET_FS_INFO_V2
mdefine_line|#define NCP_IOC_GET_FS_INFO_V2&t;&t;_IOWR(&squot;n&squot;, 4, struct ncp_fs_info_v2)
DECL|macro|NCP_IOC_SIGN_INIT
mdefine_line|#define NCP_IOC_SIGN_INIT&t;&t;_IOR(&squot;n&squot;, 5, struct ncp_sign_init)
DECL|macro|NCP_IOC_SIGN_WANTED
mdefine_line|#define NCP_IOC_SIGN_WANTED&t;&t;_IOR(&squot;n&squot;, 6, int)
DECL|macro|NCP_IOC_SET_SIGN_WANTED
mdefine_line|#define NCP_IOC_SET_SIGN_WANTED&t;&t;_IOW(&squot;n&squot;, 6, int)
DECL|macro|NCP_IOC_LOCKUNLOCK
mdefine_line|#define NCP_IOC_LOCKUNLOCK&t;&t;_IOR(&squot;n&squot;, 7, struct ncp_lock_ioctl)
DECL|macro|NCP_IOC_GETROOT
mdefine_line|#define NCP_IOC_GETROOT&t;&t;&t;_IOW(&squot;n&squot;, 8, struct ncp_setroot_ioctl)
DECL|macro|NCP_IOC_SETROOT
mdefine_line|#define NCP_IOC_SETROOT&t;&t;&t;_IOR(&squot;n&squot;, 8, struct ncp_setroot_ioctl)
DECL|macro|NCP_IOC_GETOBJECTNAME
mdefine_line|#define NCP_IOC_GETOBJECTNAME&t;&t;_IOWR(&squot;n&squot;, 9, struct ncp_objectname_ioctl)
DECL|macro|NCP_IOC_SETOBJECTNAME
mdefine_line|#define NCP_IOC_SETOBJECTNAME&t;&t;_IOR(&squot;n&squot;, 9, struct ncp_objectname_ioctl)
DECL|macro|NCP_IOC_GETPRIVATEDATA
mdefine_line|#define NCP_IOC_GETPRIVATEDATA&t;&t;_IOWR(&squot;n&squot;, 10, struct ncp_privatedata_ioctl)
DECL|macro|NCP_IOC_SETPRIVATEDATA
mdefine_line|#define NCP_IOC_SETPRIVATEDATA&t;&t;_IOR(&squot;n&squot;, 10, struct ncp_privatedata_ioctl)
DECL|macro|NCP_IOC_GETCHARSETS
mdefine_line|#define NCP_IOC_GETCHARSETS&t;&t;_IOWR(&squot;n&squot;, 11, struct ncp_nls_ioctl)
DECL|macro|NCP_IOC_SETCHARSETS
mdefine_line|#define NCP_IOC_SETCHARSETS&t;&t;_IOR(&squot;n&squot;, 11, struct ncp_nls_ioctl)
DECL|macro|NCP_IOC_GETDENTRYTTL
mdefine_line|#define NCP_IOC_GETDENTRYTTL&t;&t;_IOW(&squot;n&squot;, 12, __u32)
DECL|macro|NCP_IOC_SETDENTRYTTL
mdefine_line|#define NCP_IOC_SETDENTRYTTL&t;&t;_IOR(&squot;n&squot;, 12, __u32)
multiline_comment|/*&n; * The packet size to allocate. One page should be enough.&n; */
DECL|macro|NCP_PACKET_SIZE
mdefine_line|#define NCP_PACKET_SIZE 4070
DECL|macro|NCP_MAXPATHLEN
mdefine_line|#define NCP_MAXPATHLEN 255
DECL|macro|NCP_MAXNAMELEN
mdefine_line|#define NCP_MAXNAMELEN 14
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* undef because public define in umsdos_fs.h (ncp_fs.h isn&squot;t public) */
DECL|macro|PRINTK
macro_line|#undef PRINTK
multiline_comment|/* define because it is easy to change PRINTK to {*}PRINTK */
DECL|macro|PRINTK
mdefine_line|#define PRINTK(format, args...) printk(KERN_DEBUG format , ## args)
DECL|macro|NCPFS_PARANOIA
macro_line|#undef NCPFS_PARANOIA
macro_line|#ifdef NCPFS_PARANOIA
DECL|macro|PPRINTK
mdefine_line|#define PPRINTK(format, args...) PRINTK(format , ## args)
macro_line|#else
DECL|macro|PPRINTK
mdefine_line|#define PPRINTK(format, args...)
macro_line|#endif
macro_line|#ifndef DEBUG_NCP
DECL|macro|DEBUG_NCP
mdefine_line|#define DEBUG_NCP 0
macro_line|#endif
macro_line|#if DEBUG_NCP &gt; 0
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format, args...) PRINTK(format , ## args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format, args...)
macro_line|#endif
macro_line|#if DEBUG_NCP &gt; 1
DECL|macro|DDPRINTK
mdefine_line|#define DDPRINTK(format, args...) PRINTK(format , ## args)
macro_line|#else
DECL|macro|DDPRINTK
mdefine_line|#define DDPRINTK(format, args...)
macro_line|#endif
DECL|macro|NCP_MAX_RPC_TIMEOUT
mdefine_line|#define NCP_MAX_RPC_TIMEOUT (6*HZ)
DECL|struct|ncp_entry_info
r_struct
id|ncp_entry_info
(brace
DECL|member|i
r_struct
id|nw_info_struct
id|i
suffix:semicolon
DECL|member|ino
id|ino_t
id|ino
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|access
r_int
id|access
suffix:semicolon
DECL|member|server_file_handle
id|__u32
id|server_file_handle
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|open_create_action
id|__u8
id|open_create_action
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|file_handle
id|__u8
id|file_handle
(braket
l_int|6
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Guess, what 0x564c is :-) */
DECL|macro|NCP_SUPER_MAGIC
mdefine_line|#define NCP_SUPER_MAGIC  0x564c
DECL|macro|NCP_SBP
mdefine_line|#define NCP_SBP(sb)&t;&t;(&amp;((sb)-&gt;u.ncpfs_sb))
DECL|macro|NCP_SERVER
mdefine_line|#define NCP_SERVER(inode)&t;NCP_SBP((inode)-&gt;i_sb)
DECL|function|NCP_FINFO
r_static
r_inline
r_struct
id|ncp_inode_info
op_star
id|NCP_FINFO
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|ncp_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_NCP_MALLOC
macro_line|#include &lt;linux/slab.h&gt;
r_extern
r_int
id|ncp_malloced
suffix:semicolon
r_extern
r_int
id|ncp_current_malloced
suffix:semicolon
r_static
r_inline
r_void
op_star
DECL|function|ncp_kmalloc
id|ncp_kmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
(brace
id|ncp_malloced
op_add_assign
l_int|1
suffix:semicolon
id|ncp_current_malloced
op_add_assign
l_int|1
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|priority
)paren
suffix:semicolon
)brace
DECL|function|ncp_kfree_s
r_static
r_inline
r_void
id|ncp_kfree_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
(brace
id|ncp_current_malloced
op_sub_assign
l_int|1
suffix:semicolon
id|kfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
macro_line|#else&t;&t;&t;&t;/* DEBUG_NCP_MALLOC */
DECL|macro|ncp_kmalloc
mdefine_line|#define ncp_kmalloc(s,p) kmalloc(s,p)
DECL|macro|ncp_kfree_s
mdefine_line|#define ncp_kfree_s(o,s) kfree(o)
macro_line|#endif&t;&t;&t;&t;/* DEBUG_NCP_MALLOC */
multiline_comment|/* linux/fs/ncpfs/inode.c */
r_int
id|ncp_notify_change
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|ncp_iget
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|ncp_entry_info
op_star
)paren
suffix:semicolon
r_void
id|ncp_update_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ncp_entry_info
op_star
)paren
suffix:semicolon
r_void
id|ncp_update_inode2
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ncp_entry_info
op_star
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/dir.c */
r_extern
r_struct
id|inode_operations
id|ncp_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ncp_dir_operations
suffix:semicolon
r_int
id|ncp_conn_logged_in
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|ncp_date_dos2unix
c_func
(paren
id|__u16
id|time
comma
id|__u16
id|date
)paren
suffix:semicolon
r_void
id|ncp_date_unix2dos
c_func
(paren
r_int
id|unix_date
comma
id|__u16
op_star
id|time
comma
id|__u16
op_star
id|date
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/ioctl.c */
r_int
id|ncp_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/sock.c */
r_int
id|ncp_request2
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
id|function
comma
r_void
op_star
id|reply
comma
r_int
id|max_reply_size
)paren
suffix:semicolon
DECL|function|ncp_request
r_static
r_int
r_inline
id|ncp_request
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
id|function
)paren
(brace
r_return
id|ncp_request2
c_func
(paren
id|server
comma
id|function
comma
id|server-&gt;packet
comma
id|server-&gt;packet_size
)paren
suffix:semicolon
)brace
r_int
id|ncp_connect
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_int
id|ncp_disconnect
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_void
id|ncp_lock_server
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_void
id|ncp_unlock_server
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/file.c */
r_extern
r_struct
id|inode_operations
id|ncp_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ncp_file_operations
suffix:semicolon
r_int
id|ncp_make_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/mmap.c */
r_int
id|ncp_mmap
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/ncplib_kernel.c */
r_int
id|ncp_make_closed
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|macro|ncp_namespace
mdefine_line|#define ncp_namespace(i)&t;(NCP_SERVER(i)-&gt;name_space[NCP_FINFO(i)-&gt;volNumber])
DECL|function|ncp_preserve_entry_case
r_static
r_inline
r_int
id|ncp_preserve_entry_case
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
id|__u32
id|nscreator
)paren
(brace
macro_line|#ifdef CONFIG_NCPFS_SMALLDOS
r_int
id|ns
op_assign
id|ncp_namespace
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ns
op_eq
id|NW_NS_DOS
)paren
macro_line|#ifdef CONFIG_NCPFS_OS2_NS
op_logical_or
(paren
(paren
id|ns
op_eq
id|NW_NS_OS2
)paren
op_logical_and
(paren
id|nscreator
op_eq
id|NW_NS_DOS
)paren
)paren
macro_line|#endif /* CONFIG_NCPFS_OS2_NS */
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_NCPFS_SMALLDOS */
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|ncp_preserve_case
mdefine_line|#define ncp_preserve_case(i)&t;(ncp_namespace(i) != NW_NS_DOS)
DECL|function|ncp_case_sensitive
r_static
r_inline
r_int
id|ncp_case_sensitive
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
(brace
macro_line|#ifdef CONFIG_NCPFS_NFS_NS
r_return
id|ncp_namespace
c_func
(paren
id|i
)paren
op_eq
id|NW_NS_NFS
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif&t;/* CONFIG_NCPFS_NFS_NS */
)brace
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* _LINUX_NCP_FS_H */
eof
