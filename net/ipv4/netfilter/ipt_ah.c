multiline_comment|/* Kernel module to match AH parameters. */
multiline_comment|/* (C) 1999-2000 Yon Uriarte &lt;yon@astaro.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_ah.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Yon Uriarte &lt;yon@astaro.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables AH SPI match module&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_CONNTRACK
DECL|macro|duprintf
mdefine_line|#define duprintf(format, args...) printk(format , ## args)
macro_line|#else
DECL|macro|duprintf
mdefine_line|#define duprintf(format, args...)
macro_line|#endif
multiline_comment|/* Returns 1 if the spi is matched by the range, 0 otherwise */
r_static
r_inline
r_int
DECL|function|spi_match
id|spi_match
c_func
(paren
id|u_int32_t
id|min
comma
id|u_int32_t
id|max
comma
id|u_int32_t
id|spi
comma
r_int
id|invert
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
id|duprintf
c_func
(paren
l_string|&quot;ah spi_match:%c 0x%x &lt;= 0x%x &lt;= 0x%x&quot;
comma
id|invert
ques
c_cond
l_char|&squot;!&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|min
comma
id|spi
comma
id|max
)paren
suffix:semicolon
id|r
op_assign
(paren
id|spi
op_ge
id|min
op_logical_and
id|spi
op_le
id|max
)paren
op_xor
id|invert
suffix:semicolon
id|duprintf
c_func
(paren
l_string|&quot; result %s&bslash;n&quot;
comma
id|r
ques
c_cond
l_string|&quot;PASS&quot;
suffix:colon
l_string|&quot;FAILED&quot;
)paren
suffix:semicolon
r_return
id|r
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
r_int
op_star
id|hotdrop
)paren
(brace
r_struct
id|ip_auth_hdr
id|_ahdr
comma
op_star
id|ah
suffix:semicolon
r_const
r_struct
id|ipt_ah
op_star
id|ahinfo
op_assign
id|matchinfo
suffix:semicolon
multiline_comment|/* Must not be a fragment. */
r_if
c_cond
(paren
id|offset
)paren
r_return
l_int|0
suffix:semicolon
id|ah
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_ahdr
)paren
comma
op_amp
id|_ahdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ah
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* We&squot;ve been asked to examine this packet, and we&n;&t;&t; * can&squot;t.  Hence, no choice but to drop.&n;&t;&t; */
id|duprintf
c_func
(paren
l_string|&quot;Dropping evil AH tinygram.&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|spi_match
c_func
(paren
id|ahinfo-&gt;spis
(braket
l_int|0
)braket
comma
id|ahinfo-&gt;spis
(braket
l_int|1
)braket
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|ahinfo-&gt;invflags
op_amp
id|IPT_AH_INV_SPI
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Called when user tries to insert an entry of this type. */
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
id|matchinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
r_struct
id|ipt_ah
op_star
id|ahinfo
op_assign
id|matchinfo
suffix:semicolon
multiline_comment|/* Must specify proto == AH, and no unknown invflags */
r_if
c_cond
(paren
id|ip-&gt;proto
op_ne
id|IPPROTO_AH
op_logical_or
(paren
id|ip-&gt;invflags
op_amp
id|IPT_INV_PROTO
)paren
)paren
(brace
id|duprintf
c_func
(paren
l_string|&quot;ipt_ah: Protocol %u != %u&bslash;n&quot;
comma
id|ip-&gt;proto
comma
id|IPPROTO_AH
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|matchinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_ah
)paren
)paren
)paren
(brace
id|duprintf
c_func
(paren
l_string|&quot;ipt_ah: matchsize %u != %u&bslash;n&quot;
comma
id|matchinfosize
comma
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_ah
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ahinfo-&gt;invflags
op_amp
op_complement
id|IPT_AH_INV_MASK
)paren
(brace
id|duprintf
c_func
(paren
l_string|&quot;ipt_ah: unknown flags %X&bslash;n&quot;
comma
id|ahinfo-&gt;invflags
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
DECL|variable|ah_match
r_static
r_struct
id|ipt_match
id|ah_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ah&quot;
comma
dot
id|match
op_assign
op_amp
id|match
comma
dot
id|checkentry
op_assign
op_amp
id|checkentry
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
id|ipt_register_match
c_func
(paren
op_amp
id|ah_match
)paren
suffix:semicolon
)brace
DECL|function|cleanup
r_static
r_void
id|__exit
id|cleanup
c_func
(paren
r_void
)paren
(brace
id|ipt_unregister_match
c_func
(paren
op_amp
id|ah_match
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
DECL|variable|cleanup
id|module_exit
c_func
(paren
id|cleanup
)paren
suffix:semicolon
eof
