multiline_comment|/*&n; *  ebt_ip&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bdschuym@pandora.be&gt;&n; *&n; *  April, 2002&n; *&n; *  Changes:&n; *    added ip-sport and ip-dport&n; *    Innominate Security Technologies AG &lt;mhopf@innominate.com&gt;&n; *    September, 2002&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/netfilter_bridge/ebt_ip.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|struct|tcpudphdr
r_struct
id|tcpudphdr
(brace
DECL|member|src
r_uint16
id|src
suffix:semicolon
DECL|member|dst
r_uint16
id|dst
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ebt_filter_ip
r_static
r_int
id|ebt_filter_ip
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_ip_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_ip_info
op_star
)paren
id|data
suffix:semicolon
r_struct
id|iphdr
id|_iph
comma
op_star
id|ih
suffix:semicolon
r_struct
id|tcpudphdr
id|_ports
comma
op_star
id|pptr
suffix:semicolon
id|ih
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
l_int|0
comma
r_sizeof
(paren
id|_iph
)paren
comma
op_amp
id|_iph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|NULL
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_TOS
op_logical_and
id|FWINV
c_func
(paren
id|info-&gt;tos
op_ne
id|ih-&gt;tos
comma
id|EBT_IP_TOS
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_SOURCE
op_logical_and
id|FWINV
c_func
(paren
(paren
id|ih-&gt;saddr
op_amp
id|info-&gt;smsk
)paren
op_ne
id|info-&gt;saddr
comma
id|EBT_IP_SOURCE
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_DEST
)paren
op_logical_and
id|FWINV
c_func
(paren
(paren
id|ih-&gt;daddr
op_amp
id|info-&gt;dmsk
)paren
op_ne
id|info-&gt;daddr
comma
id|EBT_IP_DEST
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_PROTO
)paren
(brace
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|info-&gt;protocol
op_ne
id|ih-&gt;protocol
comma
id|EBT_IP_PROTO
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_DPORT
)paren
op_logical_and
op_logical_neg
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_SPORT
)paren
)paren
r_return
id|EBT_MATCH
suffix:semicolon
id|pptr
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ih-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_ports
)paren
comma
op_amp
id|_ports
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pptr
op_eq
l_int|NULL
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_DPORT
)paren
(brace
id|u32
id|dst
op_assign
id|ntohs
c_func
(paren
id|pptr-&gt;dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|dst
template_param
id|info-&gt;dport
(braket
l_int|1
)braket
comma
id|EBT_IP_DPORT
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_SPORT
)paren
(brace
id|u32
id|src
op_assign
id|ntohs
c_func
(paren
id|pptr-&gt;src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FWINV
c_func
(paren
id|src
template_param
id|info-&gt;sport
(braket
l_int|1
)braket
comma
id|EBT_IP_SPORT
)paren
)paren
r_return
id|EBT_NOMATCH
suffix:semicolon
)brace
)brace
r_return
id|EBT_MATCH
suffix:semicolon
)brace
DECL|function|ebt_ip_check
r_static
r_int
id|ebt_ip_check
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_int
r_int
id|hookmask
comma
r_const
r_struct
id|ebt_entry
op_star
id|e
comma
r_void
op_star
id|data
comma
r_int
r_int
id|datalen
)paren
(brace
r_struct
id|ebt_ip_info
op_star
id|info
op_assign
(paren
r_struct
id|ebt_ip_info
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|datalen
op_ne
id|EBT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ebt_ip_info
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;ethproto
op_ne
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
op_logical_or
id|e-&gt;invflags
op_amp
id|EBT_IPROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
op_complement
id|EBT_IP_MASK
op_logical_or
id|info-&gt;invflags
op_amp
op_complement
id|EBT_IP_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
(paren
id|EBT_IP_DPORT
op_or
id|EBT_IP_SPORT
)paren
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;invflags
op_amp
id|EBT_IP_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;protocol
op_ne
id|IPPROTO_TCP
op_logical_and
id|info-&gt;protocol
op_ne
id|IPPROTO_UDP
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_DPORT
op_logical_and
id|info-&gt;dport
(braket
l_int|0
)braket
OG
id|info-&gt;dport
(braket
l_int|1
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;bitmask
op_amp
id|EBT_IP_SPORT
op_logical_and
id|info-&gt;sport
(braket
l_int|0
)braket
OG
id|info-&gt;sport
(braket
l_int|1
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|filter_ip
r_static
r_struct
id|ebt_match
id|filter_ip
op_assign
(brace
dot
id|name
op_assign
id|EBT_IP_MATCH
comma
dot
id|match
op_assign
id|ebt_filter_ip
comma
dot
id|check
op_assign
id|ebt_ip_check
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|ebt_register_match
c_func
(paren
op_amp
id|filter_ip
)paren
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ebt_unregister_match
c_func
(paren
op_amp
id|filter_ip
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
