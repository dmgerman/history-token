multiline_comment|/*&n; * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and &n; * James Leu (jleu@mindspring.net).&n; * Copyright (C) 2001 by various other people who didn&squot;t put their name here.&n; * Licensed under the GPL.&n; */
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/netdevice.h&quot;
macro_line|#include &quot;linux/etherdevice.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;net_kern.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;etap.h&quot;
macro_line|#include &quot;etap_kern.h&quot;
DECL|struct|ethertap_setup
r_struct
id|ethertap_setup
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
DECL|variable|ethertap_priv
r_struct
id|ethertap_setup
id|ethertap_priv
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
DECL|function|etap_init
r_static
r_void
id|etap_init
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
id|ethertap_data
op_star
id|epri
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
id|epri
op_assign
(paren
r_struct
id|ethertap_data
op_star
)paren
id|pri-&gt;user
suffix:semicolon
id|epri-&gt;dev_name
op_assign
id|ethertap_priv
(braket
id|index
)braket
dot
id|dev_name
suffix:semicolon
id|epri-&gt;gate_addr
op_assign
id|ethertap_priv
(braket
id|index
)braket
dot
id|gate_addr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ethertap backend - %s&quot;
comma
id|epri-&gt;dev_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|epri-&gt;gate_addr
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;, IP = %s&quot;
comma
id|epri-&gt;gate_addr
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|epri-&gt;data_fd
op_assign
op_minus
l_int|1
suffix:semicolon
id|epri-&gt;control_fd
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|etap_protocol
r_static
r_int
r_int
id|etap_protocol
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
DECL|function|etap_read
r_static
r_int
id|etap_read
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
r_int
id|len
suffix:semicolon
op_star
id|skb
op_assign
id|ether_adjust_skb
c_func
(paren
op_star
id|skb
comma
id|ETH_HEADER_ETHERTAP
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
id|len
op_assign
id|net_recvfrom
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
l_int|2
op_star
id|ETH_HEADER_ETHERTAP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
r_return
id|len
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
op_star
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|etap_write
r_static
r_int
id|etap_write
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
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
op_star
id|skb
)paren
OL
l_int|2
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
suffix:semicolon
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
op_star
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
op_star
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|skb
op_assign
id|skb2
suffix:semicolon
)brace
id|skb_push
c_func
(paren
op_star
id|skb
comma
l_int|2
)paren
suffix:semicolon
r_return
id|net_send
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
DECL|variable|ethertap_kern_info
r_struct
id|net_kern_info
id|ethertap_kern_info
op_assign
(brace
id|init
suffix:colon
id|etap_init
comma
id|protocol
suffix:colon
id|etap_protocol
comma
id|read
suffix:colon
id|etap_read
comma
id|write
suffix:colon
id|etap_write
comma
)brace
suffix:semicolon
DECL|variable|ethertap_count
r_static
r_int
id|ethertap_count
op_assign
l_int|0
suffix:semicolon
DECL|function|ethertap_setup
r_int
id|ethertap_setup
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
id|ethertap_setup
op_star
id|pri
suffix:semicolon
r_int
id|err
suffix:semicolon
id|pri
op_assign
op_amp
id|ethertap_priv
(braket
id|ethertap_count
)braket
suffix:semicolon
id|err
op_assign
id|tap_setup_common
c_func
(paren
id|str
comma
l_string|&quot;ethertap&quot;
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
r_if
c_cond
(paren
id|pri-&gt;dev_name
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ethertap_setup : Missing tap device name&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dev-&gt;user
op_assign
op_amp
id|ethertap_user_info
suffix:semicolon
id|dev-&gt;kern
op_assign
op_amp
id|ethertap_kern_info
suffix:semicolon
id|dev-&gt;private_size
op_assign
r_sizeof
(paren
r_struct
id|ethertap_data
)paren
suffix:semicolon
id|dev-&gt;transport_index
op_assign
id|ethertap_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ethertap_transport
r_static
r_struct
id|transport
id|ethertap_transport
op_assign
(brace
id|list
suffix:colon
id|LIST_HEAD_INIT
c_func
(paren
id|ethertap_transport.list
)paren
comma
id|name
suffix:colon
l_string|&quot;ethertap&quot;
comma
id|setup
suffix:colon
id|ethertap_setup
)brace
suffix:semicolon
DECL|function|register_ethertap
r_static
r_int
id|register_ethertap
c_func
(paren
r_void
)paren
(brace
id|register_transport
c_func
(paren
op_amp
id|ethertap_transport
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|register_ethertap
id|__initcall
c_func
(paren
id|register_ethertap
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
