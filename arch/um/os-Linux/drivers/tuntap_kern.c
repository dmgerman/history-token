multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/netdevice.h&quot;
macro_line|#include &quot;linux/etherdevice.h&quot;
macro_line|#include &quot;linux/skbuff.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;asm/errno.h&quot;
macro_line|#include &quot;net_kern.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;tuntap.h&quot;
DECL|struct|tuntap_setup
r_struct
id|tuntap_setup
(brace
DECL|member|dev_name
r_char
op_star
id|dev_name
suffix:semicolon
DECL|member|gate_addr
r_char
op_star
id|gate_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|tuntap_priv
r_struct
id|tuntap_setup
id|tuntap_priv
(braket
id|MAX_UML_NETDEV
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|MAX_UML_NETDEV
op_minus
l_int|1
)braket
op_assign
(brace
id|dev_name
suffix:colon
l_int|NULL
comma
id|gate_addr
suffix:colon
l_int|NULL
comma
)brace
)brace
suffix:semicolon
DECL|function|tuntap_init
r_static
r_void
id|tuntap_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|index
)paren
(brace
r_struct
id|uml_net_private
op_star
id|pri
suffix:semicolon
r_struct
id|tuntap_data
op_star
id|tpri
suffix:semicolon
id|init_etherdev
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|pri
op_assign
id|dev-&gt;priv
suffix:semicolon
id|tpri
op_assign
(paren
r_struct
id|tuntap_data
op_star
)paren
id|pri-&gt;user
suffix:semicolon
id|tpri-&gt;dev_name
op_assign
id|tuntap_priv
(braket
id|index
)braket
dot
id|dev_name
suffix:semicolon
id|tpri-&gt;fixed_config
op_assign
(paren
id|tpri-&gt;dev_name
op_ne
l_int|NULL
)paren
suffix:semicolon
id|tpri-&gt;gate_addr
op_assign
id|tuntap_priv
(braket
id|index
)braket
dot
id|gate_addr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;TUN/TAP backend - &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tpri-&gt;gate_addr
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IP = %s&quot;
comma
id|tpri-&gt;gate_addr
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|tpri-&gt;fd
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|tuntap_protocol
r_static
r_int
r_int
id|tuntap_protocol
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
id|eth_type_trans
c_func
(paren
id|skb
comma
id|skb-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|tuntap_read
r_static
r_int
id|tuntap_read
c_func
(paren
r_int
id|fd
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
id|lp
)paren
(brace
op_star
id|skb
op_assign
id|ether_adjust_skb
c_func
(paren
op_star
id|skb
comma
id|ETH_HEADER_OTHER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|skb
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
id|net_read
c_func
(paren
id|fd
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|mac.raw
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|dev-&gt;mtu
op_plus
id|ETH_HEADER_OTHER
)paren
suffix:semicolon
)brace
DECL|function|tuntap_write
r_static
r_int
id|tuntap_write
c_func
(paren
r_int
id|fd
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|uml_net_private
op_star
id|lp
)paren
(brace
r_return
id|net_write
c_func
(paren
id|fd
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|data
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
)paren
suffix:semicolon
)brace
DECL|variable|tuntap_kern_info
r_struct
id|net_kern_info
id|tuntap_kern_info
op_assign
(brace
id|init
suffix:colon
id|tuntap_init
comma
id|protocol
suffix:colon
id|tuntap_protocol
comma
id|read
suffix:colon
id|tuntap_read
comma
id|write
suffix:colon
id|tuntap_write
comma
)brace
suffix:semicolon
DECL|variable|tuntap_count
r_static
r_int
id|tuntap_count
op_assign
l_int|0
suffix:semicolon
DECL|function|tuntap_setup
r_int
id|tuntap_setup
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|uml_net
op_star
id|dev
)paren
(brace
r_struct
id|tuntap_setup
op_star
id|pri
suffix:semicolon
r_int
id|err
suffix:semicolon
id|pri
op_assign
op_amp
id|tuntap_priv
(braket
id|tuntap_count
)braket
suffix:semicolon
id|err
op_assign
id|tap_setup_common
c_func
(paren
id|str
comma
l_string|&quot;tuntap&quot;
comma
op_amp
id|pri-&gt;dev_name
comma
id|dev-&gt;mac
comma
op_amp
id|dev-&gt;have_mac
comma
op_amp
id|pri-&gt;gate_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|dev-&gt;user
op_assign
op_amp
id|tuntap_user_info
suffix:semicolon
id|dev-&gt;kern
op_assign
op_amp
id|tuntap_kern_info
suffix:semicolon
id|dev-&gt;private_size
op_assign
r_sizeof
(paren
r_struct
id|tuntap_data
)paren
suffix:semicolon
id|dev-&gt;transport_index
op_assign
id|tuntap_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tuntap_transport
r_static
r_struct
id|transport
id|tuntap_transport
op_assign
(brace
id|list
suffix:colon
id|LIST_HEAD_INIT
c_func
(paren
id|tuntap_transport.list
)paren
comma
id|name
suffix:colon
l_string|&quot;tuntap&quot;
comma
id|setup
suffix:colon
id|tuntap_setup
)brace
suffix:semicolon
DECL|function|register_tuntap
r_static
r_int
id|register_tuntap
c_func
(paren
r_void
)paren
(brace
id|register_transport
c_func
(paren
op_amp
id|tuntap_transport
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|register_tuntap
id|__initcall
c_func
(paren
id|register_tuntap
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof