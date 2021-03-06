multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/* Everything about the rules for NAT. */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_nat_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_nat_lock)
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|macro|NAT_VALID_HOOKS
mdefine_line|#define NAT_VALID_HOOKS ((1&lt;&lt;NF_IP_PRE_ROUTING) | (1&lt;&lt;NF_IP_POST_ROUTING) | (1&lt;&lt;NF_IP_LOCAL_OUT))
r_static
r_struct
(brace
DECL|member|repl
r_struct
id|ipt_replace
id|repl
suffix:semicolon
DECL|member|entries
r_struct
id|ipt_standard
id|entries
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|term
r_struct
id|ipt_error
id|term
suffix:semicolon
DECL|variable|__initdata
)brace
id|nat_initial_table
id|__initdata
op_assign
(brace
(brace
l_string|&quot;nat&quot;
comma
id|NAT_VALID_HOOKS
comma
l_int|4
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
op_star
l_int|3
op_plus
r_sizeof
(paren
r_struct
id|ipt_error
)paren
comma
(brace
(braket
id|NF_IP_PRE_ROUTING
)braket
op_assign
l_int|0
comma
(braket
id|NF_IP_POST_ROUTING
)braket
op_assign
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
(braket
id|NF_IP_LOCAL_OUT
)braket
op_assign
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
op_star
l_int|2
)brace
comma
(brace
(braket
id|NF_IP_PRE_ROUTING
)braket
op_assign
l_int|0
comma
(braket
id|NF_IP_POST_ROUTING
)braket
op_assign
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
(braket
id|NF_IP_LOCAL_OUT
)braket
op_assign
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
op_star
l_int|2
)brace
comma
l_int|0
comma
l_int|NULL
comma
(brace
)brace
)brace
comma
(brace
multiline_comment|/* PRE_ROUTING */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_standard_target
)paren
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* POST_ROUTING */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_standard_target
)paren
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/* LOCAL_OUT */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_standard
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_standard_target
)paren
)paren
comma
l_string|&quot;&quot;
)brace
)brace
comma
(brace
)brace
)brace
comma
op_minus
id|NF_ACCEPT
op_minus
l_int|1
)brace
)brace
)brace
comma
multiline_comment|/* ERROR */
(brace
(brace
(brace
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ipt_entry
)paren
comma
r_sizeof
(paren
r_struct
id|ipt_error
)paren
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
)brace
)brace
comma
(brace
(brace
(brace
(brace
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_error_target
)paren
)paren
comma
id|IPT_ERROR_TARGET
)brace
)brace
comma
(brace
)brace
)brace
comma
l_string|&quot;ERROR&quot;
)brace
)brace
)brace
suffix:semicolon
DECL|variable|nat_table
r_static
r_struct
id|ipt_table
id|nat_table
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;nat&quot;
comma
dot
id|valid_hooks
op_assign
id|NAT_VALID_HOOKS
comma
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/* Source NAT */
DECL|function|ipt_snat_target
r_static
r_int
r_int
id|ipt_snat_target
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
r_const
r_struct
id|ip_nat_multi_range_compat
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
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
multiline_comment|/* Connection must be valid and new. */
id|IP_NF_ASSERT
c_func
(paren
id|ct
op_logical_and
(paren
id|ctinfo
op_eq
id|IP_CT_NEW
op_logical_or
id|ctinfo
op_eq
id|IP_CT_RELATED
op_logical_or
id|ctinfo
op_eq
id|IP_CT_RELATED
op_plus
id|IP_CT_IS_REPLY
)paren
)paren
suffix:semicolon
id|IP_NF_ASSERT
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|mr-&gt;range
(braket
l_int|0
)braket
comma
id|hooknum
)paren
suffix:semicolon
)brace
multiline_comment|/* Before 2.6.11 we did implicit source NAT if required. Warn about change. */
DECL|function|warn_if_extra_mangle
r_static
r_void
id|warn_if_extra_mangle
c_func
(paren
id|u32
id|dstip
comma
id|u32
id|srcip
)paren
(brace
r_static
r_int
id|warned
op_assign
l_int|0
suffix:semicolon
r_struct
id|flowi
id|fl
op_assign
(brace
dot
id|nl_u
op_assign
(brace
dot
id|ip4_u
op_assign
(brace
dot
id|daddr
op_assign
id|dstip
)brace
)brace
)brace
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
r_if
c_cond
(paren
id|ip_route_output_key
c_func
(paren
op_amp
id|rt
comma
op_amp
id|fl
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|rt-&gt;rt_src
op_ne
id|srcip
op_logical_and
op_logical_neg
id|warned
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NAT: no longer support implicit source local NAT&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;NAT: packet src %u.%u.%u.%u -&gt; dst %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|srcip
)paren
comma
id|NIPQUAD
c_func
(paren
id|dstip
)paren
)paren
suffix:semicolon
id|warned
op_assign
l_int|1
suffix:semicolon
)brace
id|ip_rt_put
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
DECL|function|ipt_dnat_target
r_static
r_int
r_int
id|ipt_dnat_target
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
r_const
r_struct
id|ip_nat_multi_range_compat
op_star
id|mr
op_assign
id|targinfo
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
id|NF_IP_LOCAL_OUT
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
multiline_comment|/* Connection must be valid and new. */
id|IP_NF_ASSERT
c_func
(paren
id|ct
op_logical_and
(paren
id|ctinfo
op_eq
id|IP_CT_NEW
op_logical_or
id|ctinfo
op_eq
id|IP_CT_RELATED
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_LOCAL_OUT
op_logical_and
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|flags
op_amp
id|IP_NAT_RANGE_MAP_IPS
)paren
id|warn_if_extra_mangle
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
comma
id|mr-&gt;range
(braket
l_int|0
)braket
dot
id|min_ip
)paren
suffix:semicolon
r_return
id|ip_nat_setup_info
c_func
(paren
id|ct
comma
op_amp
id|mr-&gt;range
(braket
l_int|0
)braket
comma
id|hooknum
)paren
suffix:semicolon
)brace
DECL|function|ipt_snat_checkentry
r_static
r_int
id|ipt_snat_checkentry
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
r_struct
id|ip_nat_multi_range_compat
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
multiline_comment|/* Must be a valid range */
r_if
c_cond
(paren
id|mr-&gt;rangesize
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SNAT: multiple ranges no longer supported&bslash;n&quot;
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
r_struct
id|ip_nat_multi_range_compat
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;SNAT: Target size %u wrong for %u ranges&bslash;n&quot;
comma
id|targinfosize
comma
id|mr-&gt;rangesize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Only allow these for NAT. */
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
l_string|&quot;SNAT: wrong table %s&bslash;n&quot;
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
id|hook_mask
op_amp
op_complement
(paren
l_int|1
op_lshift
id|NF_IP_POST_ROUTING
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;SNAT: hook mask 0x%x bad&bslash;n&quot;
comma
id|hook_mask
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
DECL|function|ipt_dnat_checkentry
r_static
r_int
id|ipt_dnat_checkentry
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
r_struct
id|ip_nat_multi_range_compat
op_star
id|mr
op_assign
id|targinfo
suffix:semicolon
multiline_comment|/* Must be a valid range */
r_if
c_cond
(paren
id|mr-&gt;rangesize
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DNAT: multiple ranges no longer supported&bslash;n&quot;
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
r_struct
id|ip_nat_multi_range_compat
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;DNAT: Target size %u wrong for %u ranges&bslash;n&quot;
comma
id|targinfosize
comma
id|mr-&gt;rangesize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Only allow these for NAT. */
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
l_string|&quot;DNAT: wrong table %s&bslash;n&quot;
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
id|NF_IP_LOCAL_OUT
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;DNAT: hook mask 0x%x bad&bslash;n&quot;
comma
id|hook_mask
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
r_inline
r_int
r_int
DECL|function|alloc_null_binding
id|alloc_null_binding
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_struct
id|ip_nat_info
op_star
id|info
comma
r_int
r_int
id|hooknum
)paren
(brace
multiline_comment|/* Force range to this IP; let proto decide mapping for&n;&t;   per-proto parts (hence not IP_NAT_RANGE_PROTO_SPECIFIED).&n;&t;   Use reply in case it&squot;s already been mangled (eg local packet).&n;&t;*/
id|u_int32_t
id|ip
op_assign
(paren
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
op_eq
id|IP_NAT_MANIP_SRC
ques
c_cond
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.dst.ip
suffix:colon
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple.src.ip
)paren
suffix:semicolon
r_struct
id|ip_nat_range
id|range
op_assign
(brace
id|IP_NAT_RANGE_MAP_IPS
comma
id|ip
comma
id|ip
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Allocating NULL binding for %p (%u.%u.%u.%u)&bslash;n&quot;
comma
id|conntrack
comma
id|NIPQUAD
c_func
(paren
id|ip
)paren
)paren
suffix:semicolon
r_return
id|ip_nat_setup_info
c_func
(paren
id|conntrack
comma
op_amp
id|range
comma
id|hooknum
)paren
suffix:semicolon
)brace
DECL|function|ip_nat_rule_find
r_int
id|ip_nat_rule_find
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|hooknum
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
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_struct
id|ip_nat_info
op_star
id|info
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ipt_do_table
c_func
(paren
id|pskb
comma
id|hooknum
comma
id|in
comma
id|out
comma
op_amp
id|nat_table
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|NF_ACCEPT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_initialized
c_func
(paren
id|ct
comma
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
)paren
)paren
multiline_comment|/* NUL mapping */
id|ret
op_assign
id|alloc_null_binding
c_func
(paren
id|ct
comma
id|info
comma
id|hooknum
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ipt_snat_reg
r_static
r_struct
id|ipt_target
id|ipt_snat_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SNAT&quot;
comma
dot
id|target
op_assign
id|ipt_snat_target
comma
dot
id|checkentry
op_assign
id|ipt_snat_checkentry
comma
)brace
suffix:semicolon
DECL|variable|ipt_dnat_reg
r_static
r_struct
id|ipt_target
id|ipt_dnat_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;DNAT&quot;
comma
dot
id|target
op_assign
id|ipt_dnat_target
comma
dot
id|checkentry
op_assign
id|ipt_dnat_checkentry
comma
)brace
suffix:semicolon
DECL|function|ip_nat_rule_init
r_int
id|__init
id|ip_nat_rule_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ipt_register_table
c_func
(paren
op_amp
id|nat_table
comma
op_amp
id|nat_initial_table.repl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|ret
op_assign
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_snat_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_goto
id|unregister_table
suffix:semicolon
id|ret
op_assign
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_dnat_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
r_goto
id|unregister_snat
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|unregister_snat
suffix:colon
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_snat_reg
)paren
suffix:semicolon
id|unregister_table
suffix:colon
id|ipt_unregister_table
c_func
(paren
op_amp
id|nat_table
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ip_nat_rule_cleanup
r_void
id|ip_nat_rule_cleanup
c_func
(paren
r_void
)paren
(brace
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_dnat_reg
)paren
suffix:semicolon
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_snat_reg
)paren
suffix:semicolon
id|ipt_unregister_table
c_func
(paren
op_amp
id|nat_table
)paren
suffix:semicolon
)brace
eof
