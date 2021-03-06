multiline_comment|/*&n; * linux/fs/nfs/mount_clnt.c&n; *&n; * MOUNT client to support NFSroot.&n; *&n; * Copyright (C) 1997, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/xprt.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|NFSDBG_FACILITY
macro_line|# define NFSDBG_FACILITY&t;NFSDBG_ROOT
macro_line|#endif
multiline_comment|/*&n;#define MOUNT_PROGRAM&t;&t;100005&n;#define MOUNT_VERSION&t;&t;1&n;#define MOUNT_MNT&t;&t;1&n;#define MOUNT_UMNT&t;&t;3&n; */
r_static
r_struct
id|rpc_clnt
op_star
id|mnt_create
c_func
(paren
r_char
op_star
comma
r_struct
id|sockaddr_in
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|variable|mnt_program
r_static
r_struct
id|rpc_program
id|mnt_program
suffix:semicolon
DECL|struct|mnt_fhstatus
r_struct
id|mnt_fhstatus
(brace
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Obtain an NFS file handle for the given host and path&n; */
r_int
DECL|function|nfsroot_mount
id|nfsroot_mount
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|addr
comma
r_char
op_star
id|path
comma
r_struct
id|nfs_fh
op_star
id|fh
comma
r_int
id|version
comma
r_int
id|protocol
)paren
(brace
r_struct
id|rpc_clnt
op_star
id|mnt_clnt
suffix:semicolon
r_struct
id|mnt_fhstatus
id|result
op_assign
(brace
dot
id|fh
op_assign
id|fh
)brace
suffix:semicolon
r_char
id|hostname
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|call
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS:      nfs_mount(%08x:%s)&bslash;n&quot;
comma
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|addr-&gt;sin_addr.s_addr
)paren
comma
id|path
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|hostname
comma
l_string|&quot;%u.%u.%u.%u&quot;
comma
id|NIPQUAD
c_func
(paren
id|addr-&gt;sin_addr.s_addr
)paren
)paren
suffix:semicolon
id|mnt_clnt
op_assign
id|mnt_create
c_func
(paren
id|hostname
comma
id|addr
comma
id|version
comma
id|protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|mnt_clnt
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|mnt_clnt
)paren
suffix:semicolon
id|call
op_assign
(paren
id|version
op_eq
id|NFS_MNT3_VERSION
)paren
ques
c_cond
id|MOUNTPROC3_MNT
suffix:colon
id|MNTPROC_MNT
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|mnt_clnt
comma
id|call
comma
id|path
comma
op_amp
id|result
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
OL
l_int|0
ques
c_cond
id|status
suffix:colon
(paren
id|result.status
ques
c_cond
op_minus
id|EACCES
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_struct
id|rpc_clnt
op_star
DECL|function|mnt_create
id|mnt_create
c_func
(paren
r_char
op_star
id|hostname
comma
r_struct
id|sockaddr_in
op_star
id|srvaddr
comma
r_int
id|version
comma
r_int
id|protocol
)paren
(brace
r_struct
id|rpc_xprt
op_star
id|xprt
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
id|xprt
op_assign
id|xprt_create_proto
c_func
(paren
id|protocol
comma
id|srvaddr
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|xprt
)paren
)paren
r_return
(paren
r_struct
id|rpc_clnt
op_star
)paren
id|xprt
suffix:semicolon
id|clnt
op_assign
id|rpc_create_client
c_func
(paren
id|xprt
comma
id|hostname
comma
op_amp
id|mnt_program
comma
id|version
comma
id|RPC_AUTH_UNIX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|clnt
)paren
)paren
(brace
id|xprt_destroy
c_func
(paren
id|xprt
)paren
suffix:semicolon
)brace
r_else
(brace
id|clnt-&gt;cl_softrtry
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_chatty
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_oneshot
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_intr
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|clnt
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR encode/decode functions for MOUNT&n; */
r_static
r_int
DECL|function|xdr_encode_dirpath
id|xdr_encode_dirpath
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_const
r_char
op_star
id|path
)paren
(brace
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|path
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_decode_fhstatus
id|xdr_decode_fhstatus
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|mnt_fhstatus
op_star
id|res
)paren
(brace
r_struct
id|nfs_fh
op_star
id|fh
op_assign
id|res-&gt;fh
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res-&gt;status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|fh-&gt;size
op_assign
id|NFS2_FHSIZE
suffix:semicolon
id|memcpy
c_func
(paren
id|fh-&gt;data
comma
id|p
comma
id|NFS2_FHSIZE
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_decode_fhstatus3
id|xdr_decode_fhstatus3
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|mnt_fhstatus
op_star
id|res
)paren
(brace
r_struct
id|nfs_fh
op_star
id|fh
op_assign
id|res-&gt;fh
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res-&gt;status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|size
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|NFS3_FHSIZE
)paren
(brace
id|fh-&gt;size
op_assign
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|fh-&gt;data
comma
id|p
comma
id|size
)paren
suffix:semicolon
)brace
r_else
id|res-&gt;status
op_assign
op_minus
id|EBADHANDLE
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|MNT_dirpath_sz
mdefine_line|#define MNT_dirpath_sz&t;&t;(1 + 256)
DECL|macro|MNT_fhstatus_sz
mdefine_line|#define MNT_fhstatus_sz&t;&t;(1 + 8)
DECL|variable|mnt_procedures
r_static
r_struct
id|rpc_procinfo
id|mnt_procedures
(braket
)braket
op_assign
(brace
(braket
id|MNTPROC_MNT
)braket
op_assign
(brace
dot
id|p_proc
op_assign
id|MNTPROC_MNT
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_dirpath
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_fhstatus
comma
dot
id|p_bufsiz
op_assign
id|MNT_dirpath_sz
op_lshift
l_int|2
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|mnt3_procedures
r_static
r_struct
id|rpc_procinfo
id|mnt3_procedures
(braket
)braket
op_assign
(brace
(braket
id|MOUNTPROC3_MNT
)braket
op_assign
(brace
dot
id|p_proc
op_assign
id|MOUNTPROC3_MNT
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_dirpath
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_fhstatus3
comma
dot
id|p_bufsiz
op_assign
id|MNT_dirpath_sz
op_lshift
l_int|2
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|mnt_version1
r_static
r_struct
id|rpc_version
id|mnt_version1
op_assign
(brace
dot
id|number
op_assign
l_int|1
comma
dot
id|nrprocs
op_assign
l_int|2
comma
dot
id|procs
op_assign
id|mnt_procedures
)brace
suffix:semicolon
DECL|variable|mnt_version3
r_static
r_struct
id|rpc_version
id|mnt_version3
op_assign
(brace
dot
id|number
op_assign
l_int|3
comma
dot
id|nrprocs
op_assign
l_int|2
comma
dot
id|procs
op_assign
id|mnt3_procedures
)brace
suffix:semicolon
DECL|variable|mnt_version
r_static
r_struct
id|rpc_version
op_star
id|mnt_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
op_amp
id|mnt_version1
comma
l_int|NULL
comma
op_amp
id|mnt_version3
comma
)brace
suffix:semicolon
DECL|variable|mnt_stats
r_static
r_struct
id|rpc_stat
id|mnt_stats
suffix:semicolon
DECL|variable|mnt_program
r_static
r_struct
id|rpc_program
id|mnt_program
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mount&quot;
comma
dot
id|number
op_assign
id|NFS_MNT_PROGRAM
comma
dot
id|nrvers
op_assign
r_sizeof
(paren
id|mnt_version
)paren
op_div
r_sizeof
(paren
id|mnt_version
(braket
l_int|0
)braket
)paren
comma
dot
id|version
op_assign
id|mnt_version
comma
dot
id|stats
op_assign
op_amp
id|mnt_stats
comma
)brace
suffix:semicolon
eof
