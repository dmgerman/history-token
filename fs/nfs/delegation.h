multiline_comment|/*&n; * linux/fs/nfs/delegation.h&n; *&n; * Copyright (c) Trond Myklebust&n; *&n; * Definitions pertaining to NFS delegated files&n; */
macro_line|#ifndef FS_NFS_DELEGATION_H
DECL|macro|FS_NFS_DELEGATION_H
mdefine_line|#define FS_NFS_DELEGATION_H
multiline_comment|/*&n; * NFSv4 delegation&n; */
DECL|struct|nfs_delegation
r_struct
id|nfs_delegation
(brace
DECL|member|super_list
r_struct
id|list_head
id|super_list
suffix:semicolon
DECL|member|cred
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|stateid
id|nfs4_stateid
id|stateid
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|maxsize
id|loff_t
id|maxsize
suffix:semicolon
)brace
suffix:semicolon
r_int
id|nfs_inode_set_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|rpc_cred
op_star
id|cred
comma
r_struct
id|nfs_openres
op_star
id|res
)paren
suffix:semicolon
r_int
id|nfs_inode_return_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_int
id|nfs_async_inode_return_delegation
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
id|nfs4_stateid
op_star
id|stateid
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|nfs_delegation_find_inode
c_func
(paren
r_struct
id|nfs4_client
op_star
id|clp
comma
r_const
r_struct
id|nfs_fh
op_star
id|fhandle
)paren
suffix:semicolon
r_void
id|nfs_return_all_delegations
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
multiline_comment|/* NFSv4 delegation-related procedures */
r_int
id|nfs4_proc_delegreturn
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|rpc_cred
op_star
id|cred
comma
r_const
id|nfs4_stateid
op_star
id|stateid
)paren
suffix:semicolon
r_int
id|nfs4_open_delegation_recall
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nfs4_state
op_star
id|state
)paren
suffix:semicolon
macro_line|#endif
eof
