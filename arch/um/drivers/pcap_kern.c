multiline_comment|/*&n; * Copyright (C) 2002 Jeff Dike &lt;jdike@karaya.com&gt;&n; * Licensed under the GPL.&n; */
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/netdevice.h&quot;
macro_line|#include &quot;linux/etherdevice.h&quot;
macro_line|#include &quot;net_kern.h&quot;
macro_line|#include &quot;net_user.h&quot;
macro_line|#include &quot;pcap_user.h&quot;
DECL|struct|pcap_init
r_struct
id|pcap_init
(brace
DECL|member|host_if
r_char
op_star
id|host_if
suffix:semicolon
DECL|member|promisc
r_int
id|promisc
suffix:semicolon
DECL|member|optimize
r_int
id|optimize
suffix:semicolon
DECL|member|filter
r_char
op_star
id|filter
suffix:semicolon
)brace
suffix:semicolon
DECL|function|pcap_init
r_void
id|pcap_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|uml_net_private
op_star
id|pri
suffix:semicolon
r_struct
id|pcap_data
op_star
id|ppri
suffix:semicolon
r_struct
id|pcap_init
op_star
id|init
op_assign
id|data
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
id|ppri
op_assign
(paren
r_struct
id|pcap_data
op_star
)paren
id|pri-&gt;user
suffix:semicolon
op_star
id|ppri
op_assign
(paren
(paren
r_struct
id|pcap_data
)paren
(brace
dot
id|host_if
op_assign
id|init-&gt;host_if
comma
dot
id|promisc
op_assign
id|init-&gt;promisc
comma
dot
id|optimize
op_assign
id|init-&gt;optimize
comma
dot
id|filter
op_assign
id|init-&gt;filter
comma
dot
id|compiled
op_assign
l_int|NULL
comma
dot
id|pcap
op_assign
l_int|NULL
)brace
)paren
suffix:semicolon
)brace
DECL|function|pcap_read
r_static
r_int
id|pcap_read
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
id|pcap_user_read
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
comma
(paren
r_struct
id|pcap_data
op_star
)paren
op_amp
id|lp-&gt;user
)paren
suffix:semicolon
)brace
DECL|function|pcap_write
r_static
r_int
id|pcap_write
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
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|variable|pcap_kern_info
r_static
r_struct
id|net_kern_info
id|pcap_kern_info
op_assign
(brace
dot
id|init
op_assign
id|pcap_init
comma
dot
id|protocol
op_assign
id|eth_protocol
comma
dot
id|read
op_assign
id|pcap_read
comma
dot
id|write
op_assign
id|pcap_write
comma
)brace
suffix:semicolon
DECL|function|pcap_setup
r_int
id|pcap_setup
c_func
(paren
r_char
op_star
id|str
comma
r_char
op_star
op_star
id|mac_out
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|pcap_init
op_star
id|init
op_assign
id|data
suffix:semicolon
r_char
op_star
id|remain
comma
op_star
id|host_if
op_assign
l_int|NULL
comma
op_star
id|options
(braket
l_int|2
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|init
op_assign
(paren
(paren
r_struct
id|pcap_init
)paren
(brace
dot
id|host_if
op_assign
l_string|&quot;eth0&quot;
comma
dot
id|promisc
op_assign
l_int|1
comma
dot
id|optimize
op_assign
l_int|0
comma
dot
id|filter
op_assign
l_int|NULL
)brace
)paren
suffix:semicolon
id|remain
op_assign
id|split_if_spec
c_func
(paren
id|str
comma
op_amp
id|host_if
comma
op_amp
id|init-&gt;filter
comma
op_amp
id|options
(braket
l_int|0
)braket
comma
op_amp
id|options
(braket
l_int|1
)braket
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remain
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pcap_setup - Extra garbage on &quot;
l_string|&quot;specification : &squot;%s&squot;&bslash;n&quot;
comma
id|remain
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host_if
op_ne
l_int|NULL
)paren
(brace
id|init-&gt;host_if
op_assign
id|host_if
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|options
)paren
op_div
r_sizeof
(paren
id|options
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|options
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|options
(braket
id|i
)braket
comma
l_string|&quot;promisc&quot;
)paren
)paren
(brace
id|init-&gt;promisc
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|options
(braket
id|i
)braket
comma
l_string|&quot;nopromisc&quot;
)paren
)paren
(brace
id|init-&gt;promisc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|options
(braket
id|i
)braket
comma
l_string|&quot;optimize&quot;
)paren
)paren
(brace
id|init-&gt;optimize
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|options
(braket
id|i
)braket
comma
l_string|&quot;nooptimize&quot;
)paren
)paren
(brace
id|init-&gt;optimize
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;pcap_setup : bad option - &squot;%s&squot;&bslash;n&quot;
comma
id|options
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pcap_transport
r_static
r_struct
id|transport
id|pcap_transport
op_assign
(brace
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|pcap_transport.list
)paren
comma
dot
id|name
op_assign
l_string|&quot;pcap&quot;
comma
dot
id|setup
op_assign
id|pcap_setup
comma
dot
id|user
op_assign
op_amp
id|pcap_user_info
comma
dot
id|kern
op_assign
op_amp
id|pcap_kern_info
comma
dot
id|private_size
op_assign
r_sizeof
(paren
r_struct
id|pcap_data
)paren
comma
dot
id|setup_size
op_assign
r_sizeof
(paren
r_struct
id|pcap_init
)paren
comma
)brace
suffix:semicolon
DECL|function|register_pcap
r_static
r_int
id|register_pcap
c_func
(paren
r_void
)paren
(brace
id|register_transport
c_func
(paren
op_amp
id|pcap_transport
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|register_pcap
id|__initcall
c_func
(paren
id|register_pcap
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
