multiline_comment|/* xfrm4_tunnel.c: Generic IP tunnel transformer.&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
DECL|function|ipip_output
r_static
r_int
id|ipip_output
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|pskb
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipip_xfrm_rcv
r_static
r_int
id|ipip_xfrm_rcv
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_decap_state
op_star
id|decap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ipip_handler
r_static
r_struct
id|xfrm_tunnel
op_star
id|ipip_handler
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|xfrm4_tunnel_sem
)paren
suffix:semicolon
DECL|function|xfrm4_tunnel_register
r_int
id|xfrm4_tunnel_register
c_func
(paren
r_struct
id|xfrm_tunnel
op_star
id|handler
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|xfrm4_tunnel_sem
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ipip_handler
op_ne
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ipip_handler
op_assign
id|handler
suffix:semicolon
id|up
c_func
(paren
op_amp
id|xfrm4_tunnel_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|xfrm4_tunnel_register
id|EXPORT_SYMBOL
c_func
(paren
id|xfrm4_tunnel_register
)paren
suffix:semicolon
DECL|function|xfrm4_tunnel_deregister
r_int
id|xfrm4_tunnel_deregister
c_func
(paren
r_struct
id|xfrm_tunnel
op_star
id|handler
)paren
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|xfrm4_tunnel_sem
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ipip_handler
op_ne
id|handler
)paren
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ipip_handler
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|xfrm4_tunnel_sem
)paren
suffix:semicolon
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|xfrm4_tunnel_deregister
id|EXPORT_SYMBOL
c_func
(paren
id|xfrm4_tunnel_deregister
)paren
suffix:semicolon
DECL|function|ipip_rcv
r_static
r_int
id|ipip_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|xfrm_tunnel
op_star
id|handler
op_assign
id|ipip_handler
suffix:semicolon
multiline_comment|/* Tunnel devices take precedence.  */
r_if
c_cond
(paren
id|handler
op_logical_and
id|handler
op_member_access_from_pointer
id|handler
c_func
(paren
id|skb
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xfrm4_rcv
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|ipip_err
r_static
r_void
id|ipip_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|info
)paren
(brace
r_struct
id|xfrm_tunnel
op_star
id|handler
op_assign
id|ipip_handler
suffix:semicolon
id|u32
id|arg
op_assign
id|info
suffix:semicolon
r_if
c_cond
(paren
id|handler
)paren
id|handler
op_member_access_from_pointer
id|err_handler
c_func
(paren
id|skb
comma
op_amp
id|arg
)paren
suffix:semicolon
)brace
DECL|function|ipip_init_state
r_static
r_int
id|ipip_init_state
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_void
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;props.mode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;encap
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|x-&gt;props.header_len
op_assign
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipip_destroy
r_static
r_void
id|ipip_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
)brace
DECL|variable|ipip_type
r_static
r_struct
id|xfrm_type
id|ipip_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;IPIP&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|proto
op_assign
id|IPPROTO_IPIP
comma
dot
id|init_state
op_assign
id|ipip_init_state
comma
dot
id|destructor
op_assign
id|ipip_destroy
comma
dot
id|input
op_assign
id|ipip_xfrm_rcv
comma
dot
id|output
op_assign
id|ipip_output
)brace
suffix:semicolon
DECL|variable|ipip_protocol
r_static
r_struct
id|net_protocol
id|ipip_protocol
op_assign
(brace
dot
id|handler
op_assign
id|ipip_rcv
comma
dot
id|err_handler
op_assign
id|ipip_err
comma
dot
id|no_policy
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|ipip_init
r_static
r_int
id|__init
id|ipip_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|xfrm_register_type
c_func
(paren
op_amp
id|ipip_type
comma
id|AF_INET
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipip init: can&squot;t add xfrm type&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet_add_protocol
c_func
(paren
op_amp
id|ipip_protocol
comma
id|IPPROTO_IPIP
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipip init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ipip_type
comma
id|AF_INET
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipip_fini
r_static
r_void
id|__exit
id|ipip_fini
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet_del_protocol
c_func
(paren
op_amp
id|ipip_protocol
comma
id|IPPROTO_IPIP
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipip close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ipip_type
comma
id|AF_INET
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipip close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|ipip_init
id|module_init
c_func
(paren
id|ipip_init
)paren
suffix:semicolon
DECL|variable|ipip_fini
id|module_exit
c_func
(paren
id|ipip_fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
