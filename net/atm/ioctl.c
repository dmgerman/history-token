multiline_comment|/* ATM ioctl handling */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
multiline_comment|/* 2003 John Levon  &lt;levon@movementarian.org&gt; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/net.h&gt;&t;&t;/* struct socket, struct proto_ops */
macro_line|#include &lt;linux/atm.h&gt;&t;&t;/* ATM stuff */
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmclip.h&gt;&t;/* CLIP_*ENCAP */
macro_line|#include &lt;linux/atmarp.h&gt;&t;/* manifest constants */
macro_line|#include &lt;linux/sonet.h&gt;&t;/* for ioctls */
macro_line|#include &lt;linux/atmsvc.h&gt;
macro_line|#include &lt;linux/atmmpc.h&gt;
macro_line|#include &lt;net/atmclip.h&gt;
macro_line|#include &lt;linux/atmlec.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &quot;resources.h&quot;
macro_line|#include &quot;signaling.h&quot;&t;&t;/* for WAITING and sigd_attach */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|ioctl_mutex
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|ioctl_list
)paren
suffix:semicolon
DECL|function|register_atm_ioctl
r_void
id|register_atm_ioctl
c_func
(paren
r_struct
id|atm_ioctl
op_star
id|ioctl
)paren
(brace
id|down
c_func
(paren
op_amp
id|ioctl_mutex
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ioctl-&gt;list
comma
op_amp
id|ioctl_list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ioctl_mutex
)paren
suffix:semicolon
)brace
DECL|function|deregister_atm_ioctl
r_void
id|deregister_atm_ioctl
c_func
(paren
r_struct
id|atm_ioctl
op_star
id|ioctl
)paren
(brace
id|down
c_func
(paren
op_amp
id|ioctl_mutex
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|ioctl-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ioctl_mutex
)paren
suffix:semicolon
)brace
DECL|variable|register_atm_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|register_atm_ioctl
)paren
suffix:semicolon
DECL|variable|deregister_atm_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|deregister_atm_ioctl
)paren
suffix:semicolon
DECL|function|vcc_ioctl
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
(brace
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
id|vcc
op_assign
id|ATM_SD
c_func
(paren
id|sock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCOUTQ
suffix:colon
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|ATM_VF_READY
comma
op_amp
id|vcc-&gt;flags
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|error
op_assign
id|put_user
c_func
(paren
id|vcc-&gt;sk-&gt;sk_sndbuf
op_minus
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;sk_wmem_alloc
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
r_case
id|SIOCINQ
suffix:colon
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|vcc-&gt;sk-&gt;sk_receive_queue
)paren
suffix:semicolon
id|error
op_assign
id|put_user
c_func
(paren
id|skb
ques
c_cond
id|skb-&gt;len
suffix:colon
l_int|0
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_case
id|SIOCGSTAMP
suffix:colon
multiline_comment|/* borrowed from IP */
id|error
op_assign
id|sock_get_timestamp
c_func
(paren
id|vcc-&gt;sk
comma
(paren
r_struct
id|timeval
op_star
)paren
id|arg
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
r_case
id|ATM_SETSC
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ATM_SETSC is obsolete&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
r_case
id|ATMSIGD_CTRL
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * The user/kernel protocol for exchanging signalling&n;&t;&t;&t; * info uses kernel pointers as opaque references,&n;&t;&t;&t; * so the holder of the file descriptor can scribble&n;&t;&t;&t; * on the kernel... so we should make sure that we&n;&t;&t;&t; * have the same privledges that /proc/kcore needs&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|error
op_assign
id|sigd_attach
c_func
(paren
id|vcc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|sock-&gt;state
op_assign
id|SS_CONNECTED
suffix:semicolon
r_goto
id|done
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|ATMMPC_CTRL
op_logical_or
id|cmd
op_eq
id|ATMMPC_DATA
)paren
id|request_module
c_func
(paren
l_string|&quot;mpoa&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|ATMARPD_CTRL
)paren
id|request_module
c_func
(paren
l_string|&quot;clip&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|ATMLEC_CTRL
)paren
id|request_module
c_func
(paren
l_string|&quot;lec&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOIOCTLCMD
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ioctl_mutex
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|ioctl_list
)paren
(brace
r_struct
id|atm_ioctl
op_star
id|ic
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|atm_ioctl
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|try_module_get
c_func
(paren
id|ic-&gt;owner
)paren
)paren
(brace
id|error
op_assign
id|ic
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|sock
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|ic-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
op_minus
id|ENOIOCTLCMD
)paren
r_break
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|ioctl_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
op_minus
id|ENOIOCTLCMD
)paren
r_goto
id|done
suffix:semicolon
id|error
op_assign
id|atm_dev_ioctl
c_func
(paren
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|done
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
