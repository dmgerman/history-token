macro_line|#ifndef __LINUX_NET_SCM_H
DECL|macro|__LINUX_NET_SCM_H
mdefine_line|#define __LINUX_NET_SCM_H
multiline_comment|/* Well, we should have at least one descriptor open&n; * to accept passed FDs 8)&n; */
DECL|macro|SCM_MAX_FD
mdefine_line|#define SCM_MAX_FD&t;(OPEN_MAX-1)
DECL|struct|scm_fp_list
r_struct
id|scm_fp_list
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|fp
r_struct
id|file
op_star
id|fp
(braket
id|SCM_MAX_FD
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|scm_cookie
r_struct
id|scm_cookie
(brace
DECL|member|creds
r_struct
id|ucred
id|creds
suffix:semicolon
multiline_comment|/* Skb credentials&t;*/
DECL|member|fp
r_struct
id|scm_fp_list
op_star
id|fp
suffix:semicolon
multiline_comment|/* Passed files&t;&t;*/
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
multiline_comment|/* Connection seqno&t;*/
)brace
suffix:semicolon
r_extern
r_void
id|scm_detach_fds
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|scm_cookie
op_star
id|scm
)paren
suffix:semicolon
r_extern
r_int
id|__scm_send
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|scm_cookie
op_star
id|scm
)paren
suffix:semicolon
r_extern
r_void
id|__scm_destroy
c_func
(paren
r_struct
id|scm_cookie
op_star
id|scm
)paren
suffix:semicolon
r_extern
r_struct
id|scm_fp_list
op_star
id|scm_fp_dup
c_func
(paren
r_struct
id|scm_fp_list
op_star
id|fpl
)paren
suffix:semicolon
DECL|function|scm_destroy
r_static
id|__inline__
r_void
id|scm_destroy
c_func
(paren
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
r_if
c_cond
(paren
id|scm
op_logical_and
id|scm-&gt;fp
)paren
id|__scm_destroy
c_func
(paren
id|scm
)paren
suffix:semicolon
)brace
DECL|function|scm_send
r_static
id|__inline__
r_int
id|scm_send
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
id|memset
c_func
(paren
id|scm
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|scm
)paren
)paren
suffix:semicolon
id|scm-&gt;creds.uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|scm-&gt;creds.gid
op_assign
id|current-&gt;gid
suffix:semicolon
id|scm-&gt;creds.pid
op_assign
id|current-&gt;pid
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;msg_controllen
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__scm_send
c_func
(paren
id|sock
comma
id|msg
comma
id|scm
)paren
suffix:semicolon
)brace
DECL|function|scm_recv
r_static
id|__inline__
r_void
id|scm_recv
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|scm_cookie
op_star
id|scm
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|msg-&gt;msg_control
)paren
(brace
r_if
c_cond
(paren
id|sock-&gt;passcred
op_logical_or
id|scm-&gt;fp
)paren
id|msg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
id|scm_destroy
c_func
(paren
id|scm
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sock-&gt;passcred
)paren
id|put_cmsg
c_func
(paren
id|msg
comma
id|SOL_SOCKET
comma
id|SCM_CREDENTIALS
comma
r_sizeof
(paren
id|scm-&gt;creds
)paren
comma
op_amp
id|scm-&gt;creds
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scm-&gt;fp
)paren
r_return
suffix:semicolon
id|scm_detach_fds
c_func
(paren
id|msg
comma
id|scm
)paren
suffix:semicolon
)brace
macro_line|#endif /* __LINUX_NET_SCM_H */
eof
