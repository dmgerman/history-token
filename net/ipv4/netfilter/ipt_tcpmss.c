multiline_comment|/* Kernel module to match TCP MSS values. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_tcpmss.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
DECL|macro|TH_SYN
mdefine_line|#define TH_SYN 0x02
multiline_comment|/* Returns 1 if the mss option is set and matched by the range, 0 otherwise */
r_static
r_inline
r_int
DECL|function|mssoption_match
id|mssoption_match
c_func
(paren
id|u_int16_t
id|min
comma
id|u_int16_t
id|max
comma
r_const
r_struct
id|tcphdr
op_star
id|tcp
comma
id|u_int16_t
id|datalen
comma
r_int
id|invert
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_const
id|u_int8_t
op_star
id|opt
op_assign
(paren
id|u_int8_t
op_star
)paren
id|tcp
suffix:semicolon
multiline_comment|/* If we don&squot;t have the whole header, drop packet. */
r_if
c_cond
(paren
id|tcp-&gt;doff
op_star
l_int|4
OG
id|datalen
)paren
(brace
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
r_sizeof
(paren
r_struct
id|tcphdr
)paren
suffix:semicolon
id|i
OL
id|tcp-&gt;doff
op_star
l_int|4
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
(paren
id|opt
(braket
id|i
)braket
op_eq
id|TCPOPT_MSS
)paren
op_logical_and
(paren
(paren
id|tcp-&gt;doff
op_star
l_int|4
op_minus
id|i
)paren
op_ge
id|TCPOLEN_MSS
)paren
op_logical_and
(paren
id|opt
(braket
id|i
op_plus
l_int|1
)braket
op_eq
id|TCPOLEN_MSS
)paren
)paren
(brace
id|u_int16_t
id|mssval
suffix:semicolon
id|mssval
op_assign
(paren
id|opt
(braket
id|i
op_plus
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
id|opt
(braket
id|i
op_plus
l_int|3
)braket
suffix:semicolon
r_return
(paren
id|mssval
op_ge
id|min
op_logical_and
id|mssval
op_le
id|max
)paren
op_xor
id|invert
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt
(braket
id|i
)braket
OL
l_int|2
)paren
id|i
op_increment
suffix:semicolon
r_else
id|i
op_add_assign
id|opt
(braket
id|i
op_plus
l_int|1
)braket
ques
c_cond
suffix:colon
l_int|1
suffix:semicolon
)brace
r_return
id|invert
suffix:semicolon
)brace
r_static
r_int
DECL|function|match
id|match
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
id|matchinfo
comma
r_int
id|offset
comma
r_const
r_void
op_star
id|hdr
comma
id|u_int16_t
id|datalen
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_const
r_struct
id|ipt_tcpmss_match_info
op_star
id|info
op_assign
id|matchinfo
suffix:semicolon
r_const
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|skb-&gt;nh.iph
op_plus
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_return
id|mssoption_match
c_func
(paren
id|info-&gt;mss_min
comma
id|info-&gt;mss_max
comma
id|tcph
comma
id|skb-&gt;len
op_minus
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
comma
id|info-&gt;invert
comma
id|hotdrop
)paren
suffix:semicolon
)brace
DECL|function|find_syn_match
r_static
r_inline
r_int
id|find_syn_match
c_func
(paren
r_const
r_struct
id|ipt_entry_match
op_star
id|m
)paren
(brace
r_const
r_struct
id|ipt_tcp
op_star
id|tcpinfo
op_assign
(paren
r_const
r_struct
id|ipt_tcp
op_star
)paren
id|m-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|m-&gt;u.kernel.match-&gt;name
comma
l_string|&quot;tcp&quot;
)paren
op_eq
l_int|0
op_logical_and
(paren
id|tcpinfo-&gt;flg_cmp
op_amp
id|TH_SYN
)paren
op_logical_and
op_logical_neg
(paren
id|tcpinfo-&gt;invflags
op_amp
id|IPT_TCP_INV_FLAGS
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|checkentry
id|checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_ip
op_star
id|ip
comma
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchsize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_if
c_cond
(paren
id|matchsize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_tcpmss_match_info
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Must specify -p tcp */
r_if
c_cond
(paren
id|ip-&gt;proto
op_ne
id|IPPROTO_TCP
op_logical_or
(paren
id|ip-&gt;invflags
op_amp
id|IPT_INV_PROTO
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tcpmss: Only works on TCP packets&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|tcpmss_match
r_static
r_struct
id|ipt_match
id|tcpmss_match
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;tcpmss&quot;
comma
op_amp
id|match
comma
op_amp
id|checkentry
comma
l_int|NULL
comma
id|THIS_MODULE
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
id|ipt_register_match
c_func
(paren
op_amp
id|tcpmss_match
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
id|ipt_unregister_match
c_func
(paren
op_amp
id|tcpmss_match
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
