multiline_comment|/*&n; *  ncp_fs_sb.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _NCP_FS_SB
DECL|macro|_NCP_FS_SB
mdefine_line|#define _NCP_FS_SB
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ncp_mount.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|NCP_DEFAULT_OPTIONS
mdefine_line|#define NCP_DEFAULT_OPTIONS 0&t;&t;/* 2 for packet signatures */
DECL|struct|ncp_server
r_struct
id|ncp_server
(brace
DECL|member|m
r_struct
id|ncp_mount_data_kernel
id|m
suffix:semicolon
multiline_comment|/* Nearly all of the mount data is of&n;&t;&t;&t;&t;&t;   interest for us later, so we store&n;&t;&t;&t;&t;&t;   it completely. */
DECL|member|name_space
id|__u8
id|name_space
(braket
id|NCP_NUMBER_OF_VOLUMES
op_plus
l_int|2
)braket
suffix:semicolon
DECL|member|ncp_filp
r_struct
id|file
op_star
id|ncp_filp
suffix:semicolon
multiline_comment|/* File pointer to ncp socket */
DECL|member|sequence
id|u8
id|sequence
suffix:semicolon
DECL|member|task
id|u8
id|task
suffix:semicolon
DECL|member|connection
id|u16
id|connection
suffix:semicolon
multiline_comment|/* Remote connection number */
DECL|member|completion
id|u8
id|completion
suffix:semicolon
multiline_comment|/* Status message from server */
DECL|member|conn_status
id|u8
id|conn_status
suffix:semicolon
multiline_comment|/* Bit 4 = 1 ==&gt; Server going down, no&n;&t;&t;&t;&t;   requests allowed anymore.&n;&t;&t;&t;&t;   Bit 0 = 1 ==&gt; Server is down. */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Negotiated bufsize */
DECL|member|reply_size
r_int
id|reply_size
suffix:semicolon
multiline_comment|/* Size of last reply */
DECL|member|packet_size
r_int
id|packet_size
suffix:semicolon
DECL|member|packet
r_int
r_char
op_star
id|packet
suffix:semicolon
multiline_comment|/* Here we prepare requests and&n;&t;&t;&t;&t;   receive replies */
DECL|member|lock
r_int
id|lock
suffix:semicolon
multiline_comment|/* To prevent mismatch in protocols. */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|current_size
r_int
id|current_size
suffix:semicolon
multiline_comment|/* for packet preparation */
DECL|member|has_subfunction
r_int
id|has_subfunction
suffix:semicolon
DECL|member|ncp_reply_size
r_int
id|ncp_reply_size
suffix:semicolon
DECL|member|root_setuped
r_int
id|root_setuped
suffix:semicolon
multiline_comment|/* info for packet signing */
DECL|member|sign_wanted
r_int
id|sign_wanted
suffix:semicolon
multiline_comment|/* 1=Server needs signed packets */
DECL|member|sign_active
r_int
id|sign_active
suffix:semicolon
multiline_comment|/* 0=don&squot;t do signing, 1=do */
DECL|member|sign_root
r_char
id|sign_root
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* generated from password and encr. key */
DECL|member|sign_last
r_char
id|sign_last
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Authentication info: NDS or BINDERY, username */
r_struct
(brace
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
DECL|member|object_type
r_int
id|object_type
suffix:semicolon
DECL|member|auth
)brace
id|auth
suffix:semicolon
multiline_comment|/* Password info */
r_struct
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
DECL|member|priv
)brace
id|priv
suffix:semicolon
multiline_comment|/* nls info: codepage for volume and charset for I/O */
DECL|member|nls_vol
r_struct
id|nls_table
op_star
id|nls_vol
suffix:semicolon
DECL|member|nls_io
r_struct
id|nls_table
op_star
id|nls_io
suffix:semicolon
multiline_comment|/* maximum age in jiffies */
DECL|member|dentry_ttl
r_int
id|dentry_ttl
suffix:semicolon
multiline_comment|/* miscellaneous */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCP_FLAG_UTF8
mdefine_line|#define NCP_FLAG_UTF8&t;1
DECL|macro|NCP_CLR_FLAG
mdefine_line|#define NCP_CLR_FLAG(server, flag)&t;((server)-&gt;flags &amp;= ~(flag))
DECL|macro|NCP_SET_FLAG
mdefine_line|#define NCP_SET_FLAG(server, flag)&t;((server)-&gt;flags |= (flag))
DECL|macro|NCP_IS_FLAG
mdefine_line|#define NCP_IS_FLAG(server, flag)&t;((server)-&gt;flags &amp; (flag))
DECL|function|ncp_conn_valid
r_static
r_inline
r_int
id|ncp_conn_valid
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
(brace
r_return
(paren
(paren
id|server-&gt;conn_status
op_amp
l_int|0x11
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ncp_invalidate_conn
r_static
r_inline
r_void
id|ncp_invalidate_conn
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
(brace
id|server-&gt;conn_status
op_or_assign
l_int|0x01
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif
eof
