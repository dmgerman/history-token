multiline_comment|/* This file contains all the functions required for the standalone&n;   ip_nat module.&n;&n;   These are not required by the compatibility layer.&n;*/
multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * 23 Apr 2001: Harald Welte &lt;laforge@gnumonks.org&gt;&n; * &t;- new API and handling of conntrack/nat helpers&n; * &t;- now capable of multiple expectations for one master&n; * */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_nat_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_nat_lock)
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_rule.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|macro|HOOKNAME
mdefine_line|#define HOOKNAME(hooknum) ((hooknum) == NF_IP_POST_ROUTING ? &quot;POST_ROUTING&quot;  &bslash;&n;&t;&t;&t;   : ((hooknum) == NF_IP_PRE_ROUTING ? &quot;PRE_ROUTING&quot; &bslash;&n;&t;&t;&t;      : ((hooknum) == NF_IP_LOCAL_OUT ? &quot;LOCAL_OUT&quot;  &bslash;&n;&t;&t;&t;         : ((hooknum) == NF_IP_LOCAL_IN ? &quot;LOCAL_IN&quot;  &bslash;&n;&t;&t;&t;&t;    : &quot;*ERROR*&quot;)))
DECL|function|call_expect
r_static
r_inline
r_int
id|call_expect
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|master
comma
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
r_return
id|master-&gt;nat.info.helper
op_member_access_from_pointer
id|expect
c_func
(paren
id|pskb
comma
id|hooknum
comma
id|ct
comma
id|info
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|ip_nat_fn
id|ip_nat_fn
c_func
(paren
r_int
r_int
id|hooknum
comma
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
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
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
r_struct
id|ip_nat_info
op_star
id|info
suffix:semicolon
multiline_comment|/* maniptype == SRC for postrouting. */
r_enum
id|ip_nat_manip_type
id|maniptype
op_assign
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
suffix:semicolon
multiline_comment|/* We never see fragments: conntrack defrags on pre-routing&n;&t;   and local-out, and ip_nat_out protects post-routing. */
id|IP_NF_ASSERT
c_func
(paren
op_logical_neg
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
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
id|NFC_UNKNOWN
suffix:semicolon
multiline_comment|/* If we had a hardware checksum before, it&squot;s now invalid */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_eq
id|CHECKSUM_HW
)paren
r_if
c_cond
(paren
id|skb_checksum_help
c_func
(paren
id|pskb
comma
(paren
id|out
op_eq
l_int|NULL
)paren
)paren
)paren
r_return
id|NF_DROP
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
multiline_comment|/* Can&squot;t track?  It&squot;s not due to stress, or conntrack would&n;&t;   have dropped it.  Hence it&squot;s the user&squot;s responsibilty to&n;&t;   packet filter it out, or implement conntrack/NAT for that&n;&t;   protocol. 8) --RR */
r_if
c_cond
(paren
op_logical_neg
id|ct
)paren
(brace
multiline_comment|/* Exception: ICMP redirect to new connection (not in&n;                   hash table yet).  We must not let this through, in&n;                   case we&squot;re doing NAT to the same network. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;protocol
op_eq
id|IPPROTO_ICMP
)paren
(brace
r_struct
id|icmphdr
id|_hdr
comma
op_star
id|hp
suffix:semicolon
id|hp
op_assign
id|skb_header_pointer
c_func
(paren
op_star
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
comma
r_sizeof
(paren
id|_hdr
)paren
comma
op_amp
id|_hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hp
op_ne
l_int|NULL
op_logical_and
id|hp-&gt;type
op_eq
id|ICMP_REDIRECT
)paren
r_return
id|NF_DROP
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ctinfo
)paren
(brace
r_case
id|IP_CT_RELATED
suffix:colon
r_case
id|IP_CT_RELATED
op_plus
id|IP_CT_IS_REPLY
suffix:colon
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;protocol
op_eq
id|IPPROTO_ICMP
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|icmp_reply_translation
c_func
(paren
id|pskb
comma
id|ct
comma
id|hooknum
comma
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
)paren
)paren
r_return
id|NF_DROP
suffix:semicolon
r_else
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Fall thru... (Only ICMPs can be IP_CT_IS_REPLY) */
r_case
id|IP_CT_NEW
suffix:colon
id|info
op_assign
op_amp
id|ct-&gt;nat.info
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* Seen it before?  This can happen for loopback, retrans,&n;&t;&t;   or local packets.. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;initialized
op_amp
(paren
l_int|1
op_lshift
id|maniptype
)paren
)paren
macro_line|#ifndef CONFIG_IP_NF_NAT_LOCAL
multiline_comment|/* If this session has already been confirmed we must not&n;&t;&t;     * touch it again even if there is no mapping set up.&n;&t;&t;     * Can only happen on local-&gt;local traffic with&n;&t;&t;     * CONFIG_IP_NF_NAT_LOCAL disabled.&n;&t;&t;     */
op_logical_and
op_logical_neg
(paren
id|ct-&gt;status
op_amp
id|IPS_CONFIRMED
)paren
macro_line|#endif
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|ct-&gt;master
op_logical_and
id|master_ct
c_func
(paren
id|ct
)paren
op_member_access_from_pointer
id|nat.info.helper
op_logical_and
id|master_ct
c_func
(paren
id|ct
)paren
op_member_access_from_pointer
id|nat.info.helper-&gt;expect
)paren
(brace
id|ret
op_assign
id|call_expect
c_func
(paren
id|master_ct
c_func
(paren
id|ct
)paren
comma
id|pskb
comma
id|hooknum
comma
id|ct
comma
id|info
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef CONFIG_IP_NF_NAT_LOCAL
multiline_comment|/* LOCAL_IN hook doesn&squot;t have a chain!  */
r_if
c_cond
(paren
id|hooknum
op_eq
id|NF_IP_LOCAL_IN
)paren
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
r_else
macro_line|#endif
id|ret
op_assign
id|ip_nat_rule_find
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
id|ct
comma
id|info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ne
id|NF_ACCEPT
)paren
(brace
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_else
id|DEBUGP
c_func
(paren
l_string|&quot;Already setup manip %s for ct %p&bslash;n&quot;
comma
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
ques
c_cond
l_string|&quot;SRC&quot;
suffix:colon
l_string|&quot;DST&quot;
comma
id|ct
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* ESTABLISHED */
id|IP_NF_ASSERT
c_func
(paren
id|ctinfo
op_eq
id|IP_CT_ESTABLISHED
op_logical_or
id|ctinfo
op_eq
(paren
id|IP_CT_ESTABLISHED
op_plus
id|IP_CT_IS_REPLY
)paren
)paren
suffix:semicolon
id|info
op_assign
op_amp
id|ct-&gt;nat.info
suffix:semicolon
)brace
id|IP_NF_ASSERT
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
id|do_bindings
c_func
(paren
id|ct
comma
id|ctinfo
comma
id|info
comma
id|hooknum
comma
id|pskb
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|ip_nat_out
id|ip_nat_out
c_func
(paren
r_int
r_int
id|hooknum
comma
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
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
multiline_comment|/* root is playing with raw sockets. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
r_return
id|NF_ACCEPT
suffix:semicolon
multiline_comment|/* We can hit fragment here; forwarded packets get&n;&t;   defragmented by connection tracking coming in, then&n;&t;   fragmented (grr) by the forward code.&n;&n;&t;   In future: If we have nfct != NULL, AND we have NAT&n;&t;   initialized, AND there is no helper, then we can do full&n;&t;   NAPT on the head, and IP-address-only NAT on the rest.&n;&n;&t;   I&squot;m starting to have nightmares about fragments.  */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
)paren
(brace
op_star
id|pskb
op_assign
id|ip_ct_gather_frags
c_func
(paren
op_star
id|pskb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|pskb
)paren
r_return
id|NF_STOLEN
suffix:semicolon
)brace
r_return
id|ip_nat_fn
c_func
(paren
id|hooknum
comma
id|pskb
comma
id|in
comma
id|out
comma
id|okfn
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_NF_NAT_LOCAL
r_static
r_int
r_int
DECL|function|ip_nat_local_fn
id|ip_nat_local_fn
c_func
(paren
r_int
r_int
id|hooknum
comma
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
(paren
op_star
id|okfn
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
)paren
(brace
id|u_int32_t
id|saddr
comma
id|daddr
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
multiline_comment|/* root is playing with raw sockets. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
OL
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
r_return
id|NF_ACCEPT
suffix:semicolon
id|saddr
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
suffix:semicolon
id|daddr
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
suffix:semicolon
id|ret
op_assign
id|ip_nat_fn
c_func
(paren
id|hooknum
comma
id|pskb
comma
id|in
comma
id|out
comma
id|okfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|NF_DROP
op_logical_and
id|ret
op_ne
id|NF_STOLEN
op_logical_and
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
op_ne
id|saddr
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;daddr
op_ne
id|daddr
)paren
)paren
r_return
id|ip_route_me_harder
c_func
(paren
id|pskb
)paren
op_eq
l_int|0
ques
c_cond
id|ret
suffix:colon
id|NF_DROP
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* We must be after connection tracking and before packet filtering. */
multiline_comment|/* Before packet filtering, change destination */
DECL|variable|ip_nat_in_ops
r_static
r_struct
id|nf_hook_ops
id|ip_nat_in_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_nat_fn
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_PRE_ROUTING
comma
dot
id|priority
op_assign
id|NF_IP_PRI_NAT_DST
comma
)brace
suffix:semicolon
multiline_comment|/* After packet filtering, change source */
DECL|variable|ip_nat_out_ops
r_static
r_struct
id|nf_hook_ops
id|ip_nat_out_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_nat_out
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_POST_ROUTING
comma
dot
id|priority
op_assign
id|NF_IP_PRI_NAT_SRC
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_IP_NF_NAT_LOCAL
multiline_comment|/* Before packet filtering, change destination */
DECL|variable|ip_nat_local_out_ops
r_static
r_struct
id|nf_hook_ops
id|ip_nat_local_out_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_nat_local_fn
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_LOCAL_OUT
comma
dot
id|priority
op_assign
id|NF_IP_PRI_NAT_DST
comma
)brace
suffix:semicolon
multiline_comment|/* After packet filtering, change source for reply packets of LOCAL_OUT DNAT */
DECL|variable|ip_nat_local_in_ops
r_static
r_struct
id|nf_hook_ops
id|ip_nat_local_in_ops
op_assign
(brace
dot
id|hook
op_assign
id|ip_nat_fn
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|pf
op_assign
id|PF_INET
comma
dot
id|hooknum
op_assign
id|NF_IP_LOCAL_IN
comma
dot
id|priority
op_assign
id|NF_IP_PRI_NAT_SRC
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Protocol registration. */
DECL|function|ip_nat_protocol_register
r_int
id|ip_nat_protocol_register
c_func
(paren
r_struct
id|ip_nat_protocol
op_star
id|proto
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip_nat_protos
(braket
id|proto-&gt;protonum
)braket
op_ne
op_amp
id|ip_nat_unknown_protocol
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ip_nat_protos
(braket
id|proto-&gt;protonum
)braket
op_assign
id|proto
suffix:semicolon
id|out
suffix:colon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Noone stores the protocol anywhere; simply delete it. */
DECL|function|ip_nat_protocol_unregister
r_void
id|ip_nat_protocol_unregister
c_func
(paren
r_struct
id|ip_nat_protocol
op_star
id|proto
)paren
(brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
id|ip_nat_protos
(braket
id|proto-&gt;protonum
)braket
op_assign
op_amp
id|ip_nat_unknown_protocol
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* Someone could be still looking at the proto in a bh. */
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|init_or_cleanup
r_static
r_int
id|init_or_cleanup
c_func
(paren
r_int
id|init
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|need_ip_conntrack
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init
)paren
r_goto
id|cleanup
suffix:semicolon
id|ret
op_assign
id|ip_nat_rule_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_init: can&squot;t setup rules.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_nothing
suffix:semicolon
)brace
id|ret
op_assign
id|ip_nat_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_init: can&squot;t setup rules.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_rule_init
suffix:semicolon
)brace
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_nat_in_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_init: can&squot;t register in hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_nat
suffix:semicolon
)brace
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_nat_out_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_init: can&squot;t register out hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_inops
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IP_NF_NAT_LOCAL
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_nat_local_out_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_init: can&squot;t register local out hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_outops
suffix:semicolon
)brace
id|ret
op_assign
id|nf_register_hook
c_func
(paren
op_amp
id|ip_nat_local_in_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_init: can&squot;t register local in hook.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_localoutops
suffix:semicolon
)brace
macro_line|#endif
r_return
id|ret
suffix:semicolon
id|cleanup
suffix:colon
macro_line|#ifdef CONFIG_IP_NF_NAT_LOCAL
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_nat_local_in_ops
)paren
suffix:semicolon
id|cleanup_localoutops
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_nat_local_out_ops
)paren
suffix:semicolon
id|cleanup_outops
suffix:colon
macro_line|#endif
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_nat_out_ops
)paren
suffix:semicolon
id|cleanup_inops
suffix:colon
id|nf_unregister_hook
c_func
(paren
op_amp
id|ip_nat_in_ops
)paren
suffix:semicolon
id|cleanup_nat
suffix:colon
id|ip_nat_cleanup
c_func
(paren
)paren
suffix:semicolon
id|cleanup_rule_init
suffix:colon
id|ip_nat_rule_cleanup
c_func
(paren
)paren
suffix:semicolon
id|cleanup_nothing
suffix:colon
id|MUST_BE_READ_WRITE_UNLOCKED
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
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
id|init_or_cleanup
c_func
(paren
l_int|1
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
id|init_or_cleanup
c_func
(paren
l_int|0
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
DECL|variable|ip_nat_setup_info
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_setup_info
)paren
suffix:semicolon
DECL|variable|ip_nat_protocol_register
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_protocol_register
)paren
suffix:semicolon
DECL|variable|ip_nat_protocol_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_protocol_unregister
)paren
suffix:semicolon
DECL|variable|ip_nat_helper_register
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_helper_register
)paren
suffix:semicolon
DECL|variable|ip_nat_helper_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_helper_unregister
)paren
suffix:semicolon
DECL|variable|ip_nat_cheat_check
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_cheat_check
)paren
suffix:semicolon
DECL|variable|ip_nat_mangle_tcp_packet
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_mangle_tcp_packet
)paren
suffix:semicolon
DECL|variable|ip_nat_mangle_udp_packet
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_mangle_udp_packet
)paren
suffix:semicolon
DECL|variable|ip_nat_used_tuple
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_used_tuple
)paren
suffix:semicolon
DECL|variable|ip_nat_find_helper
id|EXPORT_SYMBOL
c_func
(paren
id|ip_nat_find_helper
)paren
suffix:semicolon
DECL|variable|__ip_nat_find_helper
id|EXPORT_SYMBOL
c_func
(paren
id|__ip_nat_find_helper
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
