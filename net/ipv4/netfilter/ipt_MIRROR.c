multiline_comment|/*&n;  This is a module which is used for resending packets with inverted src and dst.&n;&n;  Based on code from: ip_nat_dumb.c,v 1.9 1999/08/20&n;  and various sources.&n;&n;  Copyright (C) 2000 Emmanuel Roger &lt;winfield@freegates.be&gt;&n;&n;  Changes:&n;&t;25 Aug 2001 Harald Welte &lt;laforge@gnumonks.org&gt;&n;&t;&t;- decrement and check TTL if not called from FORWARD hook&n;&n;  This program is free software; you can redistribute it and/or modify it&n;  under the terms of the GNU General Public License as published by the&n;  Free Software Foundation; either version 2 of the License, or (at your&n;  option) any later version.&n;&n;  This program is distributed in the hope that it will be useful, but&n;  WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;  General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software Foundation,&n;  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/route.h&gt;
r_struct
id|in_device
suffix:semicolon
macro_line|#include &lt;net/route.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|function|route_mirror
r_static
r_int
id|route_mirror
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_struct
id|rtable
op_star
id|rt
suffix:semicolon
multiline_comment|/* Backwards */
r_if
c_cond
(paren
id|ip_route_output
c_func
(paren
op_amp
id|rt
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|RT_TOS
c_func
(paren
id|iph-&gt;tos
)paren
op_or
id|RTO_CONN
comma
l_int|0
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check if the interface we are leaving by is the same as the&n;           one we arrived on */
r_if
c_cond
(paren
id|skb-&gt;dev
op_eq
id|rt-&gt;u.dst.dev
)paren
(brace
multiline_comment|/* Drop old route. */
id|dst_release
c_func
(paren
id|skb-&gt;dst
)paren
suffix:semicolon
id|skb-&gt;dst
op_assign
op_amp
id|rt-&gt;u.dst
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|ip_rewrite
id|ip_rewrite
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|u32
id|odaddr
op_assign
id|iph-&gt;saddr
suffix:semicolon
id|u32
id|osaddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|skb-&gt;nfcache
op_or_assign
id|NFC_ALTERED
suffix:semicolon
multiline_comment|/* Rewrite IP header */
id|iph-&gt;daddr
op_assign
id|odaddr
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|osaddr
suffix:semicolon
)brace
multiline_comment|/* Stolen from ip_finish_output2 */
DECL|function|ip_direct_send
r_static
r_void
id|ip_direct_send
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|hh_cache
op_star
id|hh
op_assign
id|dst-&gt;hh
suffix:semicolon
r_if
c_cond
(paren
id|hh
)paren
(brace
id|read_lock_bh
c_func
(paren
op_amp
id|hh-&gt;hh_lock
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;data
op_minus
l_int|16
comma
id|hh-&gt;hh_data
comma
l_int|16
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|hh-&gt;hh_lock
)paren
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
id|hh-&gt;hh_len
)paren
suffix:semicolon
id|hh
op_member_access_from_pointer
id|hh_output
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dst-&gt;neighbour
)paren
id|dst-&gt;neighbour
op_member_access_from_pointer
id|output
c_func
(paren
id|skb
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;khm in MIRROR&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
DECL|function|ipt_mirror_target
r_static
r_int
r_int
id|ipt_mirror_target
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
r_if
c_cond
(paren
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dst
op_ne
l_int|NULL
)paren
op_logical_and
id|route_mirror
c_func
(paren
op_star
id|pskb
)paren
)paren
(brace
id|ip_rewrite
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
multiline_comment|/* If we are not at FORWARD hook (INPUT/PREROUTING),&n;&t;&t; * the TTL isn&squot;t decreased by the IP stack */
r_if
c_cond
(paren
id|hooknum
op_ne
id|NF_IP_FORWARD
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;ttl
op_le
l_int|1
)paren
(brace
multiline_comment|/* this will traverse normal stack, and &n;&t;&t;&t;&t; * thus call conntrack on the icmp packet */
id|icmp_send
c_func
(paren
op_star
id|pskb
comma
id|ICMP_TIME_EXCEEDED
comma
id|ICMP_EXC_TTL
comma
l_int|0
)paren
suffix:semicolon
r_return
id|NF_DROP
suffix:semicolon
)brace
id|ip_decrease_ttl
c_func
(paren
id|iph
)paren
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t let conntrack code see this packet:&n;                   it will think we are starting a new&n;                   connection! --RR */
id|ip_direct_send
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
r_return
id|NF_STOLEN
suffix:semicolon
)brace
r_return
id|NF_DROP
suffix:semicolon
)brace
DECL|function|ipt_mirror_checkentry
r_static
r_int
id|ipt_mirror_checkentry
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
multiline_comment|/* Only on INPUT, FORWARD or PRE_ROUTING, otherwise loop danger. */
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
id|NF_IP_FORWARD
)paren
op_or
(paren
l_int|1
op_lshift
id|NF_IP_LOCAL_IN
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;MIRROR: bad hook&bslash;n&quot;
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
l_int|0
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;MIRROR: targinfosize %u != 0&bslash;n&quot;
comma
id|targinfosize
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
DECL|variable|ipt_mirror_reg
r_static
r_struct
id|ipt_target
id|ipt_mirror_reg
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;MIRROR&quot;
comma
id|ipt_mirror_target
comma
id|ipt_mirror_checkentry
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
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_mirror_reg
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
id|ipt_mirror_reg
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
