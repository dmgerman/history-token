macro_line|#ifndef _NFS_FS_SB
DECL|macro|_NFS_FS_SB
mdefine_line|#define _NFS_FS_SB
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
)brace
suffix:semicolon
multiline_comment|/*&n; * nfs super-block data in memory&n; */
DECL|struct|nfs_sb_info
r_struct
id|nfs_sb_info
(brace
DECL|member|s_server
r_struct
id|nfs_server
id|s_server
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
