multiline_comment|/* iptables module for setting the IPv4 DSCP field, Version 1.8&n; *&n; * (C) 2002 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; * based on ipt_FTOS.c (C) 2000 by Matthew G. Marsh &lt;mgm@paktronix.com&gt;&n; * This software is distributed under GNU GPL v2, 1991&n; * &n; * See RFC2474 for a description of the DSCP field within the IP Header.&n; *&n; * ipt_DSCP.c,v 1.8 2002/08/06 18:41:57 laforge Exp&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_DSCP.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Harald Welte &lt;laforge@gnumonks.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IP tables DSCP modification module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_int
r_int
DECL|function|target
id|target
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
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
r_int
r_int
id|hooknum
comma
r_const
r_void
op_star
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
r_const
r_struct
id|ipt_DSCP_info
op_star
id|dinfo
op_assign
id|targinfo
suffix:semicolon
id|u_int8_t
id|sh_dscp
op_assign
(paren
(paren
id|dinfo-&gt;dscp
op_lshift
id|IPT_DSCP_SHIFT
)paren
op_amp
id|IPT_DSCP_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
op_amp
id|IPT_DSCP_MASK
)paren
op_ne
id|sh_dscp
)paren
(brace
id|u_int16_t
id|diffs
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_ip_make_writable
c_func
(paren
id|pskb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
)paren
r_return
id|NF_DROP
suffix:semicolon
id|diffs
(braket
l_int|0
)braket
op_assign
id|htons
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
)paren
op_xor
l_int|0xFFFF
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
op_assign
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
op_amp
op_complement
id|IPT_DSCP_MASK
)paren
op_or
id|sh_dscp
suffix:semicolon
id|diffs
(braket
l_int|1
)braket
op_assign
id|htons
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;tos
)paren
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;check
op_assign
id|csum_fold
c_func
(paren
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|diffs
comma
r_sizeof
(paren
id|diffs
)paren
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;check
op_xor
l_int|0xFFFF
)paren
)paren
suffix:semicolon
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
)brace
r_return
id|IPT_CONTINUE
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
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
id|u_int8_t
id|dscp
op_assign
(paren
(paren
r_struct
id|ipt_DSCP_info
op_star
)paren
id|targinfo
)paren
op_member_access_from_pointer
id|dscp
suffix:semicolon
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_DSCP_info
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DSCP: targinfosize %u != %Zu&bslash;n&quot;
comma
id|targinfosize
comma
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_DSCP_info
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
id|strcmp
c_func
(paren
id|tablename
comma
l_string|&quot;mangle&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DSCP: can only be called from &bslash;&quot;mangle&bslash;&quot; table, not &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|tablename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dscp
OG
id|IPT_DSCP_MAX
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DSCP: dscp %x out of range&bslash;n&quot;
comma
id|dscp
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
DECL|variable|ipt_dscp_reg
r_static
r_struct
id|ipt_target
id|ipt_dscp_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;DSCP&quot;
comma
dot
id|target
op_assign
id|target
comma
dot
id|checkentry
op_assign
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
r_if
c_cond
(paren
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_dscp_reg
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_dscp_reg
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
eof
