multiline_comment|/* NETMAP - static NAT mapping of IP network addresses (1:1).&n; * The mapping can be applied to source (POSTROUTING),&n; * destination (PREROUTING), or both (with separate rules).&n; */
multiline_comment|/* (C) 2000-2001 Svenning Soerensen &lt;svenning@post5.tele.dk&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
DECL|macro|MODULENAME
mdefine_line|#define MODULENAME &quot;NETMAP&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Svenning Soerensen &lt;svenning@post5.tele.dk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iptables 1:1 NAT mapping of IP networks target&quot;
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
r_static
r_int
DECL|function|check
id|check
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
r_struct
id|ip_nat_multi_range
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|tablename
comma
l_string|&quot;nat&quot;
)paren
op_ne
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
id|MODULENAME
l_string|&quot;:check: bad table `%s&squot;.&bslash;n&quot;
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
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
op_star
id|mr
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
id|MODULENAME
l_string|&quot;:check: size %u.&bslash;n&quot;
comma
id|targinfosize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hook_mask
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|NF_IP_PRE_ROUTING
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
id|MODULENAME
l_string|&quot;:check: bad hooks %x.&bslash;n&quot;
comma
id|hook_mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|flags
op_amp
id|IP_NAT_RANGE_MAP_IPS
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
id|MODULENAME
l_string|&quot;:check: bad MAP_IPS.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mr-&gt;rangesize
op_ne
l_int|1
)paren
(brace
id|DEBUGP
c_func
(paren
id|MODULENAME
l_string|&quot;:check: bad rangesize %u.&bslash;n&quot;
comma
id|mr-&gt;rangesize
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
r_struct
id|ip_conntrack
op_star
id|ct
suffix:semicolon
r_enum
id|ip_conntrack_info
id|ctinfo
suffix:semicolon
id|u_int32_t
id|new_ip
comma
id|netmask
suffix:semicolon
r_const
r_struct
id|ip_nat_multi_range
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
r_struct
id|ip_nat_multi_range
id|newrange
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
op_logical_or
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
)paren
suffix:semicolon
id|ct
op_assign
id|ip_conntrack_get
c_func
(paren
op_star
id|pskb
comma
op_amp
id|ctinfo
)paren
suffix:semicolon
id|netmask
op_assign
op_complement
(paren
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|min_ip
op_xor
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|max_ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_PRE_ROUTING
)paren
id|new_ip
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
op_amp
op_complement
id|netmask
suffix:semicolon
r_else
id|new_ip
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
op_amp
op_complement
id|netmask
suffix:semicolon
id|new_ip
op_or_assign
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|min_ip
op_amp
id|netmask
suffix:semicolon
id|newrange
op_assign
(paren
(paren
r_struct
id|ip_nat_multi_range
)paren
(brace
l_int|1
comma
(brace
(brace
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|flags
op_or
id|IP_NAT_RANGE_MAP_IPS
comma
id|new_ip
comma
id|new_ip
comma
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|min
comma
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|max
)brace
)brace
)brace
)paren
suffix:semicolon
multiline_comment|/* Hand modified range to generic setup. */
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|newrange
comma
id|hooknum
)paren
suffix:semicolon
)brace
DECL|variable|target_module
r_static
r_struct
id|ipt_target
id|target_module
op_assign
(brace
dot
id|name
op_assign
id|MODULENAME
comma
dot
id|target
op_assign
id|target
comma
dot
id|checkentry
op_assign
id|check
comma
dot
id|me
op_assign
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
id|ipt_register_target
c_func
(paren
op_amp
id|target_module
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
id|ipt_unregister_target
c_func
(paren
op_amp
id|target_module
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
