multiline_comment|/* net/atm/pvc.c - ATM PVC sockets */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/net.h&gt;&t;&t;/* struct socket, struct proto_ops */
macro_line|#include &lt;linux/atm.h&gt;&t;&t;/* ATM stuff */
macro_line|#include &lt;linux/atmdev.h&gt;&t;/* ATM devices */
macro_line|#include &lt;linux/atmclip.h&gt;&t;/* Classical IP over ATM */
macro_line|#include &lt;linux/errno.h&gt;&t;/* error codes */
macro_line|#include &lt;linux/kernel.h&gt;&t;/* printk */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;net/sock.h&gt;&t;&t;/* for sock_no_* */
macro_line|#ifdef CONFIG_ATM_CLIP
macro_line|#include &lt;net/atmclip.h&gt;
macro_line|#endif
macro_line|#include &quot;resources.h&quot;&t;&t;/* devs and vccs */
macro_line|#include &quot;common.h&quot;&t;&t;/* common for PVCs and SVCs */
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
DECL|function|pvc_shutdown
r_static
r_int
id|pvc_shutdown
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|how
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pvc_bind
r_static
r_int
id|pvc_bind
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|sockaddr
comma
r_int
id|sockaddr_len
)paren
(brace
r_struct
id|sockaddr_atmpvc
op_star
id|addr
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_if
c_cond
(paren
id|sockaddr_len
op_ne
r_sizeof
(paren
r_struct
id|sockaddr_atmpvc
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr
op_assign
(paren
r_struct
id|sockaddr_atmpvc
op_star
)paren
id|sockaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;sap_family
op_ne
id|AF_ATMPVC
)paren
r_return
op_minus
id|EAFNOSUPPORT
suffix:semicolon
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_HASQOS
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
r_return
op_minus
id|EBADFD
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ATM_VF_PARTIAL
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
r_if
c_cond
(paren
id|vcc-&gt;vpi
op_ne
id|ATM_VPI_UNSPEC
)paren
id|addr-&gt;sap_addr.vpi
op_assign
id|vcc-&gt;vpi
suffix:semicolon
r_if
c_cond
(paren
id|vcc-&gt;vci
op_ne
id|ATM_VCI_UNSPEC
)paren
id|addr-&gt;sap_addr.vci
op_assign
id|vcc-&gt;vci
suffix:semicolon
)brace
r_return
id|atm_connect
c_func
(paren
id|sock
comma
id|addr-&gt;sap_addr.itf
comma
id|addr-&gt;sap_addr.vpi
comma
id|addr-&gt;sap_addr.vci
)paren
suffix:semicolon
)brace
DECL|function|pvc_connect
r_static
r_int
id|pvc_connect
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|sockaddr
comma
r_int
id|sockaddr_len
comma
r_int
id|flags
)paren
(brace
r_return
id|pvc_bind
c_func
(paren
id|sock
comma
id|sockaddr
comma
id|sockaddr_len
)paren
suffix:semicolon
)brace
DECL|function|pvc_getname
r_static
r_int
id|pvc_getname
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|sockaddr
comma
r_int
op_star
id|sockaddr_len
comma
r_int
id|peer
)paren
(brace
r_struct
id|sockaddr_atmpvc
op_star
id|addr
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;dev
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_ADDR
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
r_return
op_minus
id|ENOTCONN
suffix:semicolon
op_star
id|sockaddr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_atmpvc
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_struct
id|sockaddr_atmpvc
op_star
)paren
id|sockaddr
suffix:semicolon
id|addr-&gt;sap_family
op_assign
id|AF_ATMPVC
suffix:semicolon
id|addr-&gt;sap_addr.itf
op_assign
id|vcc-&gt;dev-&gt;number
suffix:semicolon
id|addr-&gt;sap_addr.vpi
op_assign
id|vcc-&gt;vpi
suffix:semicolon
id|addr-&gt;sap_addr.vci
op_assign
id|vcc-&gt;vci
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pvc_proto_ops
r_static
r_struct
id|proto_ops
id|SOCKOPS_WRAPPED
c_func
(paren
id|pvc_proto_ops
)paren
op_assign
(brace
dot
id|family
op_assign
id|PF_ATMPVC
comma
dot
id|release
op_assign
id|atm_release
comma
dot
id|bind
op_assign
id|pvc_bind
comma
dot
id|connect
op_assign
id|pvc_connect
comma
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
dot
id|accept
op_assign
id|sock_no_accept
comma
dot
id|getname
op_assign
id|pvc_getname
comma
dot
id|poll
op_assign
id|atm_poll
comma
dot
id|ioctl
op_assign
id|atm_ioctl
comma
dot
id|listen
op_assign
id|sock_no_listen
comma
dot
id|shutdown
op_assign
id|pvc_shutdown
comma
dot
id|setsockopt
op_assign
id|atm_setsockopt
comma
dot
id|getsockopt
op_assign
id|atm_getsockopt
comma
dot
id|sendmsg
op_assign
id|atm_sendmsg
comma
dot
id|recvmsg
op_assign
id|atm_recvmsg
comma
dot
id|mmap
op_assign
id|sock_no_mmap
comma
dot
id|sendpage
op_assign
id|sock_no_sendpage
comma
)brace
suffix:semicolon
macro_line|#include &lt;linux/smp_lock.h&gt;
id|SOCKOPS_WRAP
c_func
(paren
id|pvc_proto
comma
id|PF_ATMPVC
)paren
suffix:semicolon
DECL|function|pvc_create
r_static
r_int
id|pvc_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
(brace
id|sock-&gt;ops
op_assign
op_amp
id|pvc_proto_ops
suffix:semicolon
r_return
id|atm_create
c_func
(paren
id|sock
comma
id|protocol
comma
id|PF_ATMPVC
)paren
suffix:semicolon
)brace
DECL|variable|pvc_family_ops
r_static
r_struct
id|net_proto_family
id|pvc_family_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_ATMPVC
comma
dot
id|create
op_assign
id|pvc_create
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Initialize the ATM PVC protocol family&n; */
DECL|function|atmpvc_init
r_static
r_int
id|__init
id|atmpvc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|sock_register
c_func
(paren
op_amp
id|pvc_family_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATMPVC: can&squot;t register (%d)&quot;
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ATM_CLIP
id|atm_clip_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
id|error
op_assign
id|atm_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|printk
c_func
(paren
l_string|&quot;atm_proc_init fails with %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atmpvc_init
id|module_init
c_func
(paren
id|atmpvc_init
)paren
suffix:semicolon
eof
