multiline_comment|/* net/atm/common.h - ATM sockets (common part for PVC and SVC) */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef NET_ATM_COMMON_H
DECL|macro|NET_ATM_COMMON_H
mdefine_line|#define NET_ATM_COMMON_H
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/poll.h&gt; /* for poll_table */
r_int
id|atm_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
comma
r_int
id|family
)paren
suffix:semicolon
r_int
id|atm_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
r_int
id|atm_connect
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|itf
comma
r_int
id|vpi
comma
r_int
id|vci
)paren
suffix:semicolon
r_int
id|atm_recvmsg
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|m
comma
r_int
id|total_len
comma
r_int
id|flags
)paren
suffix:semicolon
r_int
id|atm_sendmsg
c_func
(paren
r_struct
id|kiocb
op_star
id|iocb
comma
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|m
comma
r_int
id|total_len
)paren
suffix:semicolon
r_int
r_int
id|atm_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|socket
op_star
id|sock
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
r_int
id|vcc_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|atm_setsockopt
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
id|optlen
)paren
suffix:semicolon
r_int
id|atm_getsockopt
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|level
comma
r_int
id|optname
comma
r_char
op_star
id|optval
comma
r_int
op_star
id|optlen
)paren
suffix:semicolon
r_int
id|atm_connect_vcc
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|itf
comma
r_int
id|vpi
comma
r_int
id|vci
)paren
suffix:semicolon
r_void
id|atm_release_vcc_sk
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|free_sk
)paren
suffix:semicolon
r_void
id|atm_shutdown_dev
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|atmpvc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|atmpvc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|atmsvc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|atmsvc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|atm_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|atm_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* SVC */
r_void
id|svc_callback
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
r_int
id|svc_change_qos
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|atm_qos
op_star
id|qos
)paren
suffix:semicolon
multiline_comment|/* p2mp */
r_int
id|create_leaf
c_func
(paren
r_struct
id|socket
op_star
id|leaf
comma
r_struct
id|socket
op_star
id|session
)paren
suffix:semicolon
macro_line|#endif
eof
