macro_line|#ifndef _NFS_FS_SB
DECL|macro|_NFS_FS_SB
mdefine_line|#define _NFS_FS_SB
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/backing-dev.h&gt;
multiline_comment|/*&n; * NFS client parameters stored in the superblock.&n; */
DECL|struct|nfs_server
r_struct
id|nfs_server
(brace
DECL|member|client
r_struct
id|rpc_clnt
op_star
id|client
suffix:semicolon
multiline_comment|/* RPC client handle */
DECL|member|client_sys
r_struct
id|rpc_clnt
op_star
id|client_sys
suffix:semicolon
multiline_comment|/* 2nd handle for FSINFO */
DECL|member|rpc_ops
r_struct
id|nfs_rpc_ops
op_star
id|rpc_ops
suffix:semicolon
multiline_comment|/* NFS protocol vector */
DECL|member|backing_dev_info
r_struct
id|backing_dev_info
id|backing_dev_info
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|caps
r_int
r_int
id|caps
suffix:semicolon
multiline_comment|/* server capabilities */
DECL|member|rsize
r_int
r_int
id|rsize
suffix:semicolon
multiline_comment|/* read size */
DECL|member|rpages
r_int
r_int
id|rpages
suffix:semicolon
multiline_comment|/* read size (in pages) */
DECL|member|wsize
r_int
r_int
id|wsize
suffix:semicolon
multiline_comment|/* write size */
DECL|member|wpages
r_int
r_int
id|wpages
suffix:semicolon
multiline_comment|/* write size (in pages) */
DECL|member|dtsize
r_int
r_int
id|dtsize
suffix:semicolon
multiline_comment|/* readdir size */
DECL|member|bsize
r_int
r_int
id|bsize
suffix:semicolon
multiline_comment|/* server block size */
DECL|member|acregmin
r_int
r_int
id|acregmin
suffix:semicolon
multiline_comment|/* attr cache timeouts */
DECL|member|acregmax
r_int
r_int
id|acregmax
suffix:semicolon
DECL|member|acdirmin
r_int
r_int
id|acdirmin
suffix:semicolon
DECL|member|acdirmax
r_int
r_int
id|acdirmax
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
DECL|member|hostname
r_char
op_star
id|hostname
suffix:semicolon
multiline_comment|/* remote hostname */
DECL|member|fh
r_struct
id|nfs_fh
id|fh
suffix:semicolon
DECL|member|addr
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
macro_line|#ifdef CONFIG_NFS_V4
multiline_comment|/* Our own IP address, as a null-terminated string.&n;&t; * This is used to generate the clientid, and the callback address.&n;&t; */
DECL|member|ip_addr
r_char
id|ip_addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|mnt_path
r_char
op_star
id|mnt_path
suffix:semicolon
DECL|member|nfs4_state
r_struct
id|nfs4_client
op_star
id|nfs4_state
suffix:semicolon
multiline_comment|/* all NFSv4 state starts here */
DECL|member|nfs4_siblings
r_struct
id|list_head
id|nfs4_siblings
suffix:semicolon
multiline_comment|/* List of other nfs_server structs&n;&t;&t;&t;&t;&t;&t; * that share the same clientid&n;&t;&t;&t;&t;&t;&t; */
DECL|member|attr_bitmask
id|u32
id|attr_bitmask
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* V4 bitmask representing the set&n;&t;&t;&t;&t;&t;&t;   of attributes supported on this&n;&t;&t;&t;&t;&t;&t;   filesystem */
DECL|member|acl_bitmask
id|u32
id|acl_bitmask
suffix:semicolon
multiline_comment|/* V4 bitmask representing the ACEs&n;&t;&t;&t;&t;&t;&t;   that are supported on this&n;&t;&t;&t;&t;&t;&t;   filesystem */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Server capabilities */
DECL|macro|NFS_CAP_READDIRPLUS
mdefine_line|#define NFS_CAP_READDIRPLUS&t;(1U &lt;&lt; 0)
DECL|macro|NFS_CAP_HARDLINKS
mdefine_line|#define NFS_CAP_HARDLINKS&t;(1U &lt;&lt; 1)
DECL|macro|NFS_CAP_SYMLINKS
mdefine_line|#define NFS_CAP_SYMLINKS&t;(1U &lt;&lt; 2)
DECL|macro|NFS_CAP_ACLS
mdefine_line|#define NFS_CAP_ACLS&t;&t;(1U &lt;&lt; 3)
macro_line|#endif
eof
