macro_line|#ifndef _NFS_FS_SB
DECL|macro|_NFS_FS_SB
mdefine_line|#define _NFS_FS_SB
macro_line|#include &lt;linux/list.h&gt;
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
DECL|member|rpc_ops
r_struct
id|nfs_rpc_ops
op_star
id|rpc_ops
suffix:semicolon
multiline_comment|/* NFS protocol vector */
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
DECL|member|rw_requests
r_struct
id|nfs_reqlist
op_star
id|rw_requests
suffix:semicolon
multiline_comment|/* async read/write requests */
DECL|member|lru_read
r_struct
id|list_head
id|lru_read
comma
DECL|member|lru_dirty
id|lru_dirty
comma
DECL|member|lru_commit
id|lru_commit
comma
DECL|member|lru_busy
id|lru_busy
suffix:semicolon
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
)brace
suffix:semicolon
multiline_comment|/* Server capabilities */
DECL|macro|NFS_CAP_READDIRPLUS
mdefine_line|#define NFS_CAP_READDIRPLUS&t;(1)
macro_line|#endif
eof
