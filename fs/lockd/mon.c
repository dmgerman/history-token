multiline_comment|/*&n; * linux/fs/lockd/mon.c&n; *&n; * The kernel statd client.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/lockd/sm_inter.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_MONITOR
r_static
r_struct
id|rpc_clnt
op_star
id|nsm_create
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|rpc_program
id|nsm_program
suffix:semicolon
multiline_comment|/*&n; * Local NSM state&n; */
DECL|variable|nsm_local_state
id|u32
id|nsm_local_state
suffix:semicolon
multiline_comment|/*&n; * Common procedure for SM_MON/SM_UNMON calls&n; */
r_static
r_int
DECL|function|nsm_mon_unmon
id|nsm_mon_unmon
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
id|u32
id|proc
comma
r_struct
id|nsm_res
op_star
id|res
)paren
(brace
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_int
id|status
suffix:semicolon
r_struct
id|nsm_args
id|args
suffix:semicolon
id|status
op_assign
op_minus
id|EACCES
suffix:semicolon
id|clnt
op_assign
id|nsm_create
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clnt
)paren
r_goto
id|out
suffix:semicolon
id|args.addr
op_assign
id|host-&gt;h_addr.sin_addr.s_addr
suffix:semicolon
id|args.proto
op_assign
(paren
id|host-&gt;h_proto
op_lshift
l_int|1
)paren
op_or
id|host-&gt;h_server
suffix:semicolon
id|args.prog
op_assign
id|NLM_PROGRAM
suffix:semicolon
id|args.vers
op_assign
id|host-&gt;h_version
suffix:semicolon
id|args.proc
op_assign
id|NLMPROC_NSM_NOTIFY
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|clnt
comma
id|proc
comma
op_amp
id|args
comma
id|res
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;nsm_mon_unmon: rpc failed, status=%d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_else
id|status
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up monitoring of a remote host&n; */
r_int
DECL|function|nsm_monitor
id|nsm_monitor
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
)paren
(brace
r_struct
id|nsm_res
id|res
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nsm_monitor(%s)&bslash;n&quot;
comma
id|host-&gt;h_name
)paren
suffix:semicolon
id|status
op_assign
id|nsm_mon_unmon
c_func
(paren
id|host
comma
id|SM_MON
comma
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
op_logical_or
id|res.status
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: cannot monitor %s&bslash;n&quot;
comma
id|host-&gt;h_name
)paren
suffix:semicolon
r_else
id|host-&gt;h_monitored
op_assign
l_int|1
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Cease to monitor remote host&n; */
r_int
DECL|function|nsm_unmonitor
id|nsm_unmonitor
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
)paren
(brace
r_struct
id|nsm_res
id|res
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nsm_unmonitor(%s)&bslash;n&quot;
comma
id|host-&gt;h_name
)paren
suffix:semicolon
id|status
op_assign
id|nsm_mon_unmon
c_func
(paren
id|host
comma
id|SM_UNMON
comma
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: cannot unmonitor %s&bslash;n&quot;
comma
id|host-&gt;h_name
)paren
suffix:semicolon
r_else
id|host-&gt;h_monitored
op_assign
l_int|0
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Create NSM client for the local host&n; */
r_static
r_struct
id|rpc_clnt
op_star
DECL|function|nsm_create
id|nsm_create
c_func
(paren
r_void
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
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|htonl
c_func
(paren
id|INADDR_LOOPBACK
)paren
suffix:semicolon
id|sin.sin_port
op_assign
l_int|0
suffix:semicolon
id|xprt
op_assign
id|xprt_create_proto
c_func
(paren
id|IPPROTO_UDP
comma
op_amp
id|sin
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xprt
)paren
r_goto
id|out
suffix:semicolon
id|clnt
op_assign
id|rpc_create_client
c_func
(paren
id|xprt
comma
l_string|&quot;localhost&quot;
comma
op_amp
id|nsm_program
comma
id|SM_VERSION
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clnt
)paren
r_goto
id|out_destroy
suffix:semicolon
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
id|xprt-&gt;resvport
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* NSM requires a reserved port */
id|out
suffix:colon
r_return
id|clnt
suffix:semicolon
id|out_destroy
suffix:colon
id|xprt_destroy
c_func
(paren
id|xprt
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR functions for NSM.&n; */
r_static
id|u32
op_star
DECL|function|xdr_encode_common
id|xdr_encode_common
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nsm_args
op_star
id|argp
)paren
(brace
r_char
id|buffer
(braket
l_int|20
)braket
suffix:semicolon
id|u32
id|addr
op_assign
id|ntohl
c_func
(paren
id|argp-&gt;addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use the dotted-quad IP address of the remote host as&n;&t; * identifier. Linux statd always looks up the canonical&n;&t; * hostname first for whatever remote hostname it receives,&n;&t; * so this works alright.&n;&t; */
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
(paren
id|addr
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
comma
(paren
id|addr
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
comma
(paren
id|addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
(paren
id|addr
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|buffer
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|system_utsname.nodename
)paren
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|argp-&gt;prog
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|argp-&gt;vers
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|argp-&gt;proc
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_encode_mon
id|xdr_encode_mon
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nsm_args
op_star
id|argp
)paren
(brace
id|p
op_assign
id|xdr_encode_common
c_func
(paren
id|rqstp
comma
id|p
comma
id|argp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|argp-&gt;addr
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|argp-&gt;vers
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|argp-&gt;proto
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
id|rqstp-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|rqstp-&gt;rq_svec
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
DECL|function|xdr_encode_unmon
id|xdr_encode_unmon
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nsm_args
op_star
id|argp
)paren
(brace
id|p
op_assign
id|xdr_encode_common
c_func
(paren
id|rqstp
comma
id|p
comma
id|argp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:semicolon
id|rqstp-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|rqstp-&gt;rq_svec
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
DECL|function|xdr_decode_stat_res
id|xdr_decode_stat_res
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nsm_res
op_star
id|resp
)paren
(brace
id|resp-&gt;status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|resp-&gt;state
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nsm: xdr_decode_stat_res status %d state %d&bslash;n&quot;
comma
id|resp-&gt;status
comma
id|resp-&gt;state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_decode_stat
id|xdr_decode_stat
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nsm_res
op_star
id|resp
)paren
(brace
id|resp-&gt;state
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|SM_my_name_sz
mdefine_line|#define SM_my_name_sz&t;(1+XDR_QUADLEN(SM_MAXSTRLEN))
DECL|macro|SM_my_id_sz
mdefine_line|#define SM_my_id_sz&t;(3+1+SM_my_name_sz)
DECL|macro|SM_mon_id_sz
mdefine_line|#define SM_mon_id_sz&t;(1+XDR_QUADLEN(20)+SM_my_id_sz)
DECL|macro|SM_mon_sz
mdefine_line|#define SM_mon_sz&t;(SM_mon_id_sz+4)
DECL|macro|SM_monres_sz
mdefine_line|#define SM_monres_sz&t;2
DECL|macro|SM_unmonres_sz
mdefine_line|#define SM_unmonres_sz&t;1
macro_line|#ifndef MAX
DECL|macro|MAX
macro_line|# define MAX(a, b)&t;(((a) &gt; (b))? (a) : (b))
macro_line|#endif
DECL|variable|nsm_procedures
r_static
r_struct
id|rpc_procinfo
id|nsm_procedures
(braket
)braket
op_assign
(brace
(braket
id|SM_MON
)braket
op_assign
(brace
dot
id|p_proc
op_assign
id|SM_MON
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_mon
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_stat_res
comma
dot
id|p_bufsiz
op_assign
id|MAX
c_func
(paren
id|SM_mon_sz
comma
id|SM_monres_sz
)paren
op_lshift
l_int|2
comma
)brace
comma
(braket
id|SM_UNMON
)braket
op_assign
(brace
dot
id|p_proc
op_assign
id|SM_UNMON
comma
dot
id|p_encode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_encode_unmon
comma
dot
id|p_decode
op_assign
(paren
id|kxdrproc_t
)paren
id|xdr_decode_stat
comma
dot
id|p_bufsiz
op_assign
id|MAX
c_func
(paren
id|SM_mon_id_sz
comma
id|SM_unmonres_sz
)paren
op_lshift
l_int|2
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|nsm_version1
r_static
r_struct
id|rpc_version
id|nsm_version1
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
r_sizeof
(paren
id|nsm_procedures
)paren
op_div
r_sizeof
(paren
id|nsm_procedures
(braket
l_int|0
)braket
)paren
comma
dot
id|procs
op_assign
id|nsm_procedures
)brace
suffix:semicolon
DECL|variable|nsm_version
r_static
r_struct
id|rpc_version
op_star
id|nsm_version
(braket
)braket
op_assign
(brace
(braket
l_int|1
)braket
op_assign
op_amp
id|nsm_version1
comma
)brace
suffix:semicolon
DECL|variable|nsm_stats
r_static
r_struct
id|rpc_stat
id|nsm_stats
suffix:semicolon
DECL|variable|nsm_program
r_struct
id|rpc_program
id|nsm_program
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;statd&quot;
comma
dot
id|number
op_assign
id|SM_PROGRAM
comma
dot
id|nrvers
op_assign
r_sizeof
(paren
id|nsm_version
)paren
op_div
r_sizeof
(paren
id|nsm_version
(braket
l_int|0
)braket
)paren
comma
dot
id|version
op_assign
id|nsm_version
comma
dot
id|stats
op_assign
op_amp
id|nsm_stats
)brace
suffix:semicolon
eof
