multiline_comment|/* NAT for netfilter; shared with compatibility layer. */
multiline_comment|/* (C) 1999-2001 Paul `Rusty&squot; Russell&n; * (C) 2002-2004 Netfilter Core Team &lt;coreteam@netfilter.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;  /* For tcp_prot in getorigdst */
macro_line|#include &lt;linux/icmp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/jhash.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_nat_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_nat_lock)
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|variable|ip_nat_lock
id|DECLARE_RWLOCK
c_func
(paren
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* Calculated at init based on memory size */
DECL|variable|ip_nat_htable_size
r_static
r_int
r_int
id|ip_nat_htable_size
suffix:semicolon
DECL|variable|bysource
r_static
r_struct
id|list_head
op_star
id|bysource
suffix:semicolon
DECL|variable|ip_nat_protos
r_struct
id|ip_nat_protocol
op_star
id|ip_nat_protos
(braket
id|MAX_IP_NAT_PROTO
)braket
suffix:semicolon
multiline_comment|/* We keep an extra hash for each conntrack, for fast searching. */
r_static
r_inline
r_int
r_int
DECL|function|hash_by_src
id|hash_by_src
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
multiline_comment|/* Original src, to ensure we map it consistently if poss. */
r_return
id|jhash_3words
c_func
(paren
id|tuple-&gt;src.ip
comma
id|tuple-&gt;src.u.all
comma
id|tuple-&gt;dst.protonum
comma
l_int|0
)paren
op_mod
id|ip_nat_htable_size
suffix:semicolon
)brace
multiline_comment|/* Noone using conntrack by the time this called. */
DECL|function|ip_nat_cleanup_conntrack
r_static
r_void
id|ip_nat_cleanup_conntrack
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conn
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|conn-&gt;status
op_amp
id|IPS_NAT_DONE_MASK
)paren
)paren
r_return
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|conn-&gt;nat.info.bysource
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* We do checksum mangling, so if they were wrong before they&squot;re still&n; * wrong.  Also works for incomplete packets (eg. ICMP dest&n; * unreachables.) */
id|u_int16_t
DECL|function|ip_nat_cheat_check
id|ip_nat_cheat_check
c_func
(paren
id|u_int32_t
id|oldvalinv
comma
id|u_int32_t
id|newval
comma
id|u_int16_t
id|oldcheck
)paren
(brace
id|u_int32_t
id|diffs
(braket
)braket
op_assign
(brace
id|oldvalinv
comma
id|newval
)brace
suffix:semicolon
r_return
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
id|oldcheck
op_xor
l_int|0xFFFF
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Is this tuple already taken? (not by us) */
r_int
DECL|function|ip_nat_used_tuple
id|ip_nat_used_tuple
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_conntrack
op_star
id|ignored_conntrack
)paren
(brace
multiline_comment|/* Conntrack tracking doesn&squot;t keep track of outgoing tuples; only&n;&t;   incoming ones.  NAT means they don&squot;t have a fixed mapping,&n;&t;   so we invert the tuple and look for the incoming reply.&n;&n;&t;   We could keep a separate hash if this proves too slow. */
r_struct
id|ip_conntrack_tuple
id|reply
suffix:semicolon
id|invert_tuplepr
c_func
(paren
op_amp
id|reply
comma
id|tuple
)paren
suffix:semicolon
r_return
id|ip_conntrack_tuple_taken
c_func
(paren
op_amp
id|reply
comma
id|ignored_conntrack
)paren
suffix:semicolon
)brace
multiline_comment|/* If we source map this tuple so reply looks like reply_tuple, will&n; * that meet the constraints of range. */
r_static
r_int
DECL|function|in_range
id|in_range
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
)paren
(brace
r_struct
id|ip_nat_protocol
op_star
id|proto
op_assign
id|ip_nat_find_proto
c_func
(paren
id|tuple-&gt;dst.protonum
)paren
suffix:semicolon
multiline_comment|/* If we are supposed to map IPs, then we must be in the&n;&t;   range specified, otherwise let this drag us onto a new src IP. */
r_if
c_cond
(paren
id|range-&gt;flags
op_amp
id|IP_NAT_RANGE_MAP_IPS
)paren
(brace
r_if
c_cond
(paren
id|ntohl
c_func
(paren
id|tuple-&gt;src.ip
)paren
template_param
id|ntohl
c_func
(paren
id|range-&gt;max_ip
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|range-&gt;flags
op_amp
id|IP_NAT_RANGE_PROTO_SPECIFIED
)paren
op_logical_or
id|proto
op_member_access_from_pointer
id|in_range
c_func
(paren
id|tuple
comma
id|IP_NAT_MANIP_SRC
comma
op_amp
id|range-&gt;min
comma
op_amp
id|range-&gt;max
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
r_inline
r_int
DECL|function|same_src
id|same_src
c_func
(paren
r_const
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
r_return
(paren
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.dst.protonum
op_eq
id|tuple-&gt;dst.protonum
op_logical_and
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.ip
op_eq
id|tuple-&gt;src.ip
op_logical_and
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple.src.u.all
op_eq
id|tuple-&gt;src.u.all
)paren
suffix:semicolon
)brace
multiline_comment|/* Only called for SRC manip */
r_static
r_int
DECL|function|find_appropriate_src
id|find_appropriate_src
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_struct
id|ip_conntrack_tuple
op_star
id|result
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
)paren
(brace
r_int
r_int
id|h
op_assign
id|hash_by_src
c_func
(paren
id|tuple
)paren
suffix:semicolon
r_struct
id|ip_conntrack
op_star
id|ct
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|ct
comma
op_amp
id|bysource
(braket
id|h
)braket
comma
id|nat.info.bysource
)paren
(brace
r_if
c_cond
(paren
id|same_src
c_func
(paren
id|ct
comma
id|tuple
)paren
)paren
(brace
multiline_comment|/* Copy source part from reply tuple. */
id|invert_tuplepr
c_func
(paren
id|result
comma
op_amp
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
)paren
suffix:semicolon
id|result-&gt;dst
op_assign
id|tuple-&gt;dst
suffix:semicolon
r_if
c_cond
(paren
id|in_range
c_func
(paren
id|result
comma
id|range
)paren
)paren
(brace
id|READ_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
id|READ_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* For [FUTURE] fragmentation handling, we want the least-used&n;   src-ip/dst-ip/proto triple.  Fairness doesn&squot;t come into it.  Thus&n;   if the range specifies 1.2.3.4 ports 10000-10005 and 1.2.3.5 ports&n;   1-65535, we don&squot;t do pro-rata allocation based on ports; we choose&n;   the ip with the lowest src-ip/dst-ip/proto usage.&n;*/
r_static
r_void
DECL|function|find_best_ips_proto
id|find_best_ips_proto
c_func
(paren
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
comma
r_const
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_enum
id|ip_nat_manip_type
id|maniptype
)paren
(brace
id|u_int32_t
op_star
id|var_ipp
suffix:semicolon
multiline_comment|/* Host order */
id|u_int32_t
id|minip
comma
id|maxip
comma
id|j
suffix:semicolon
multiline_comment|/* No IP mapping?  Do nothing. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|range-&gt;flags
op_amp
id|IP_NAT_RANGE_MAP_IPS
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|var_ipp
op_assign
op_amp
id|tuple-&gt;src.ip
suffix:semicolon
r_else
id|var_ipp
op_assign
op_amp
id|tuple-&gt;dst.ip
suffix:semicolon
multiline_comment|/* Fast path: only one choice. */
r_if
c_cond
(paren
id|range-&gt;min_ip
op_eq
id|range-&gt;max_ip
)paren
(brace
op_star
id|var_ipp
op_assign
id|range-&gt;min_ip
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Hashing source and destination IPs gives a fairly even&n;&t; * spread in practice (if there are a small number of IPs&n;&t; * involved, there usually aren&squot;t that many connections&n;&t; * anyway).  The consistency means that servers see the same&n;&t; * client coming from the same IP (some Internet Banking sites&n;&t; * like this), even across reboots. */
id|minip
op_assign
id|ntohl
c_func
(paren
id|range-&gt;min_ip
)paren
suffix:semicolon
id|maxip
op_assign
id|ntohl
c_func
(paren
id|range-&gt;max_ip
)paren
suffix:semicolon
id|j
op_assign
id|jhash_2words
c_func
(paren
id|tuple-&gt;src.ip
comma
id|tuple-&gt;dst.ip
comma
l_int|0
)paren
suffix:semicolon
op_star
id|var_ipp
op_assign
id|htonl
c_func
(paren
id|minip
op_plus
id|j
op_mod
(paren
id|maxip
op_minus
id|minip
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Manipulate the tuple into the range given.  For NF_IP_POST_ROUTING,&n; * we change the source to map into the range.  For NF_IP_PRE_ROUTING&n; * and NF_IP_LOCAL_OUT, we change the destination to map into the&n; * range.  It might not be possible to get a unique tuple, but we try.&n; * At worst (or if we race), we will end up with a final duplicate in&n; * __ip_conntrack_confirm and drop the packet. */
r_static
r_void
DECL|function|get_unique_tuple
id|get_unique_tuple
c_func
(paren
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|orig_tuple
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
comma
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_enum
id|ip_nat_manip_type
id|maniptype
)paren
(brace
r_struct
id|ip_nat_protocol
op_star
id|proto
op_assign
id|ip_nat_find_proto
c_func
(paren
id|orig_tuple-&gt;dst.protonum
)paren
suffix:semicolon
multiline_comment|/* 1) If this srcip/proto/src-proto-part is currently mapped,&n;&t;   and that same mapping gives a unique tuple within the given&n;&t;   range, use that.&n;&n;&t;   This is only required for source (ie. NAT/masq) mappings.&n;&t;   So far, we don&squot;t do local source mappings, so multiple&n;&t;   manips not an issue.  */
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
(brace
r_if
c_cond
(paren
id|find_appropriate_src
c_func
(paren
id|orig_tuple
comma
id|tuple
comma
id|range
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;get_unique_tuple: Found current src map&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_used_tuple
c_func
(paren
id|tuple
comma
id|conntrack
)paren
)paren
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* 2) Select the least-used IP/proto combination in the given&n;&t;   range. */
op_star
id|tuple
op_assign
op_star
id|orig_tuple
suffix:semicolon
id|find_best_ips_proto
c_func
(paren
id|tuple
comma
id|range
comma
id|conntrack
comma
id|maniptype
)paren
suffix:semicolon
multiline_comment|/* 3) The per-protocol part of the manip is made to map into&n;&t;   the range to make a unique tuple. */
multiline_comment|/* Only bother mapping if it&squot;s not already in range and unique */
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|range-&gt;flags
op_amp
id|IP_NAT_RANGE_PROTO_SPECIFIED
)paren
op_logical_or
id|proto
op_member_access_from_pointer
id|in_range
c_func
(paren
id|tuple
comma
id|maniptype
comma
op_amp
id|range-&gt;min
comma
op_amp
id|range-&gt;max
)paren
)paren
op_logical_and
op_logical_neg
id|ip_nat_used_tuple
c_func
(paren
id|tuple
comma
id|conntrack
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Last change: get protocol to try to obtain unique tuple. */
id|proto
op_member_access_from_pointer
id|unique_tuple
c_func
(paren
id|tuple
comma
id|range
comma
id|maniptype
comma
id|conntrack
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|ip_nat_setup_info
id|ip_nat_setup_info
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|ip_nat_range
op_star
id|range
comma
r_int
r_int
id|hooknum
)paren
(brace
r_struct
id|ip_conntrack_tuple
id|curr_tuple
comma
id|new_tuple
suffix:semicolon
r_struct
id|ip_nat_info
op_star
id|info
op_assign
op_amp
id|conntrack-&gt;nat.info
suffix:semicolon
r_int
id|have_to_hash
op_assign
op_logical_neg
(paren
id|conntrack-&gt;status
op_amp
id|IPS_NAT_DONE_MASK
)paren
suffix:semicolon
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
op_logical_or
id|hooknum
op_eq
id|NF_IP_LOCAL_IN
op_logical_or
id|hooknum
op_eq
id|NF_IP_LOCAL_OUT
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|ip_nat_initialized
c_func
(paren
id|conntrack
comma
id|maniptype
)paren
)paren
suffix:semicolon
multiline_comment|/* What we&squot;ve got will look like inverse of reply. Normally&n;&t;   this is what is in the conntrack, except for prior&n;&t;   manipulations (future optimization: if num_manips == 0,&n;&t;   orig_tp =&n;&t;   conntrack-&gt;tuplehash[IP_CT_DIR_ORIGINAL].tuple) */
id|invert_tuplepr
c_func
(paren
op_amp
id|curr_tuple
comma
op_amp
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_REPLY
)braket
dot
id|tuple
)paren
suffix:semicolon
id|get_unique_tuple
c_func
(paren
op_amp
id|new_tuple
comma
op_amp
id|curr_tuple
comma
id|range
comma
id|conntrack
comma
id|maniptype
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip_ct_tuple_equal
c_func
(paren
op_amp
id|new_tuple
comma
op_amp
id|curr_tuple
)paren
)paren
(brace
r_struct
id|ip_conntrack_tuple
id|reply
suffix:semicolon
multiline_comment|/* Alter conntrack table so will recognize replies. */
id|invert_tuplepr
c_func
(paren
op_amp
id|reply
comma
op_amp
id|new_tuple
)paren
suffix:semicolon
id|ip_conntrack_alter_reply
c_func
(paren
id|conntrack
comma
op_amp
id|reply
)paren
suffix:semicolon
multiline_comment|/* Non-atomic: we own this at the moment. */
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|conntrack-&gt;status
op_or_assign
id|IPS_SRC_NAT
suffix:semicolon
r_else
id|conntrack-&gt;status
op_or_assign
id|IPS_DST_NAT
suffix:semicolon
)brace
multiline_comment|/* Place in source hash if this is the first time. */
r_if
c_cond
(paren
id|have_to_hash
)paren
(brace
r_int
r_int
id|srchash
op_assign
id|hash_by_src
c_func
(paren
op_amp
id|conntrack-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|tuple
)paren
suffix:semicolon
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|info-&gt;bysource
comma
op_amp
id|bysource
(braket
id|srchash
)braket
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* It&squot;s done. */
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_DST
)paren
id|set_bit
c_func
(paren
id|IPS_DST_NAT_DONE_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
suffix:semicolon
r_else
id|set_bit
c_func
(paren
id|IPS_SRC_NAT_DONE_BIT
comma
op_amp
id|conntrack-&gt;status
)paren
suffix:semicolon
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Returns true if succeeded. */
r_static
r_int
DECL|function|manip_pkt
id|manip_pkt
c_func
(paren
id|u_int16_t
id|proto
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_int
r_int
id|iphdroff
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|target
comma
r_enum
id|ip_nat_manip_type
id|maniptype
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
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
r_if
c_cond
(paren
op_logical_neg
id|skb_ip_make_writable
c_func
(paren
id|pskb
comma
id|iphdroff
op_plus
r_sizeof
(paren
op_star
id|iph
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|iph
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
op_plus
id|iphdroff
suffix:semicolon
multiline_comment|/* Manipulate protcol part. */
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_find_proto
c_func
(paren
id|proto
)paren
op_member_access_from_pointer
id|manip_pkt
c_func
(paren
id|pskb
comma
id|iphdroff
comma
id|target
comma
id|maniptype
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|iph
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
op_plus
id|iphdroff
suffix:semicolon
r_if
c_cond
(paren
id|maniptype
op_eq
id|IP_NAT_MANIP_SRC
)paren
(brace
id|iph-&gt;check
op_assign
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|iph-&gt;saddr
comma
id|target-&gt;src.ip
comma
id|iph-&gt;check
)paren
suffix:semicolon
id|iph-&gt;saddr
op_assign
id|target-&gt;src.ip
suffix:semicolon
)brace
r_else
(brace
id|iph-&gt;check
op_assign
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|iph-&gt;daddr
comma
id|target-&gt;dst.ip
comma
id|iph-&gt;check
)paren
suffix:semicolon
id|iph-&gt;daddr
op_assign
id|target-&gt;dst.ip
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Do packet manipulations according to ip_nat_setup_info. */
DECL|function|nat_packet
r_int
r_int
id|nat_packet
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|hooknum
comma
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_enum
id|ip_conntrack_dir
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_int
r_int
id|statusbit
suffix:semicolon
r_enum
id|ip_nat_manip_type
id|mtype
op_assign
id|HOOK2MANIP
c_func
(paren
id|hooknum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IPS_SEQ_ADJUST_BIT
comma
op_amp
id|ct-&gt;status
)paren
op_logical_and
(paren
id|hooknum
op_eq
id|NF_IP_POST_ROUTING
op_logical_or
id|hooknum
op_eq
id|NF_IP_LOCAL_IN
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_core: adjusting sequence number&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* future: put this in a l4-proto specific function,&n;&t;&t; * and call this function here. */
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_seq_adjust
c_func
(paren
id|pskb
comma
id|ct
comma
id|ctinfo
)paren
)paren
r_return
id|NF_DROP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mtype
op_eq
id|IP_NAT_MANIP_SRC
)paren
id|statusbit
op_assign
id|IPS_SRC_NAT
suffix:semicolon
r_else
id|statusbit
op_assign
id|IPS_DST_NAT
suffix:semicolon
multiline_comment|/* Invert if this is reply dir. */
r_if
c_cond
(paren
id|dir
op_eq
id|IP_CT_DIR_REPLY
)paren
id|statusbit
op_xor_assign
id|IPS_NAT_MASK
suffix:semicolon
multiline_comment|/* Non-atomic: these bits don&squot;t change. */
r_if
c_cond
(paren
id|ct-&gt;status
op_amp
id|statusbit
)paren
(brace
r_struct
id|ip_conntrack_tuple
id|target
suffix:semicolon
multiline_comment|/* We are aiming to look like inverse of other direction. */
id|invert_tuplepr
c_func
(paren
op_amp
id|target
comma
op_amp
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|manip_pkt
c_func
(paren
id|target.dst.protonum
comma
id|pskb
comma
l_int|0
comma
op_amp
id|target
comma
id|mtype
)paren
)paren
r_return
id|NF_DROP
suffix:semicolon
)brace
r_return
id|NF_ACCEPT
suffix:semicolon
)brace
multiline_comment|/* Dir is direction ICMP is coming from (opposite to packet it contains) */
DECL|function|icmp_reply_translation
r_int
id|icmp_reply_translation
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_nat_manip_type
id|manip
comma
r_enum
id|ip_conntrack_dir
id|dir
)paren
(brace
r_struct
(brace
r_struct
id|icmphdr
id|icmp
suffix:semicolon
r_struct
id|iphdr
id|ip
suffix:semicolon
)brace
op_star
id|inside
suffix:semicolon
r_struct
id|ip_conntrack_tuple
id|inner
comma
id|target
suffix:semicolon
r_int
id|hdrlen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
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
id|hdrlen
op_plus
r_sizeof
(paren
op_star
id|inside
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|inside
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
op_plus
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
multiline_comment|/* We&squot;re actually going to mangle it beyond trivial checksum&n;&t;   adjustment, so make sure the current checksum is correct. */
r_if
c_cond
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|ip_summed
op_ne
id|CHECKSUM_UNNECESSARY
)paren
(brace
id|hdrlen
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|u16
)paren
id|csum_fold
c_func
(paren
id|skb_checksum
c_func
(paren
op_star
id|pskb
comma
id|hdrlen
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|hdrlen
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must be RELATED */
id|IP_NF_ASSERT
c_func
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfctinfo
op_eq
id|IP_CT_RELATED
op_logical_or
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfctinfo
op_eq
id|IP_CT_RELATED
op_plus
id|IP_CT_IS_REPLY
)paren
suffix:semicolon
multiline_comment|/* Redirects on non-null nats must be dropped, else they&squot;ll&n;           start talking to each other without our translation, and be&n;           confused... --RR */
r_if
c_cond
(paren
id|inside-&gt;icmp.type
op_eq
id|ICMP_REDIRECT
)paren
(brace
multiline_comment|/* If NAT isn&squot;t finished, assume it and drop. */
r_if
c_cond
(paren
(paren
id|ct-&gt;status
op_amp
id|IPS_NAT_DONE_MASK
)paren
op_ne
id|IPS_NAT_DONE_MASK
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ct-&gt;status
op_amp
id|IPS_NAT_MASK
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;icmp_reply_translation: translating error %p manp %u dir %s&bslash;n&quot;
comma
op_star
id|pskb
comma
id|manip
comma
id|dir
op_eq
id|IP_CT_DIR_ORIGINAL
ques
c_cond
l_string|&quot;ORIG&quot;
suffix:colon
l_string|&quot;REPLY&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip_ct_get_tuple
c_func
(paren
op_amp
id|inside-&gt;ip
comma
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
op_plus
r_sizeof
(paren
r_struct
id|icmphdr
)paren
op_plus
id|inside-&gt;ip.ihl
op_star
l_int|4
comma
op_amp
id|inner
comma
id|ip_ct_find_proto
c_func
(paren
id|inside-&gt;ip.protocol
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Change inner back to look like incoming packet.  We do the&n;&t;   opposite manip on this hook to normal, because it might not&n;&t;   pass all hooks (locally-generated ICMP).  Consider incoming&n;&t;   packet: PREROUTING (DST manip), routing produces ICMP, goes&n;&t;   through POSTROUTING (which must correct the DST manip). */
r_if
c_cond
(paren
op_logical_neg
id|manip_pkt
c_func
(paren
id|inside-&gt;ip.protocol
comma
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
op_plus
r_sizeof
(paren
id|inside-&gt;icmp
)paren
comma
op_amp
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple
comma
op_logical_neg
id|manip
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Change outer to look the reply to an incoming packet&n;&t; * (proto 0 means don&squot;t invert per-proto part). */
multiline_comment|/* Obviously, we need to NAT destination IP, but source IP&n;&t;   should be NAT&squot;ed only if it is from a NAT&squot;d host.&n;&n;&t;   Explanation: some people use NAT for anonymizing.  Also,&n;&t;   CERT recommends dropping all packets from private IP&n;&t;   addresses (although ICMP errors from internal links with&n;&t;   such addresses are not too uncommon, as Alan Cox points&n;&t;   out) */
r_if
c_cond
(paren
id|manip
op_ne
id|IP_NAT_MANIP_SRC
op_logical_or
(paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;saddr
op_eq
id|ct-&gt;tuplehash
(braket
id|dir
)braket
dot
id|tuple.src.ip
)paren
)paren
(brace
id|invert_tuplepr
c_func
(paren
op_amp
id|target
comma
op_amp
id|ct-&gt;tuplehash
(braket
op_logical_neg
id|dir
)braket
dot
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|manip_pkt
c_func
(paren
l_int|0
comma
id|pskb
comma
l_int|0
comma
op_amp
id|target
comma
id|manip
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reloading &quot;inside&quot; here since manip_pkt inner. */
id|inside
op_assign
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|data
op_plus
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|inside-&gt;icmp.checksum
op_assign
l_int|0
suffix:semicolon
id|inside-&gt;icmp.checksum
op_assign
id|csum_fold
c_func
(paren
id|skb_checksum
c_func
(paren
op_star
id|pskb
comma
id|hdrlen
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
op_minus
id|hdrlen
comma
l_int|0
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ip_nat_init
r_int
id|__init
id|ip_nat_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Leave them the same for the moment. */
id|ip_nat_htable_size
op_assign
id|ip_conntrack_htable_size
suffix:semicolon
multiline_comment|/* One vmalloc for both hash tables */
id|bysource
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|list_head
)paren
op_star
id|ip_nat_htable_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bysource
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Sew in builtin protocols. */
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_IP_NAT_PROTO
suffix:semicolon
id|i
op_increment
)paren
id|ip_nat_protos
(braket
id|i
)braket
op_assign
op_amp
id|ip_nat_unknown_protocol
suffix:semicolon
id|ip_nat_protos
(braket
id|IPPROTO_TCP
)braket
op_assign
op_amp
id|ip_nat_protocol_tcp
suffix:semicolon
id|ip_nat_protos
(braket
id|IPPROTO_UDP
)braket
op_assign
op_amp
id|ip_nat_protocol_udp
suffix:semicolon
id|ip_nat_protos
(braket
id|IPPROTO_ICMP
)braket
op_assign
op_amp
id|ip_nat_protocol_icmp
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ip_nat_htable_size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|bysource
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: Man, this is a hack.  &lt;SIGH&gt; */
id|IP_NF_ASSERT
c_func
(paren
id|ip_conntrack_destroyed
op_eq
l_int|NULL
)paren
suffix:semicolon
id|ip_conntrack_destroyed
op_assign
op_amp
id|ip_nat_cleanup_conntrack
suffix:semicolon
multiline_comment|/* Initialize fake conntrack so that NAT will skip it */
id|ip_conntrack_untracked.status
op_or_assign
id|IPS_NAT_DONE_MASK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear NAT section of all conntracks, in case we&squot;re loaded again. */
DECL|function|clean_nat
r_static
r_int
id|clean_nat
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|i
comma
r_void
op_star
id|data
)paren
(brace
id|memset
c_func
(paren
op_amp
id|i-&gt;nat
comma
l_int|0
comma
r_sizeof
(paren
id|i-&gt;nat
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Not __exit: called from ip_nat_standalone.c:init_or_cleanup() --RR */
DECL|function|ip_nat_cleanup
r_void
id|ip_nat_cleanup
c_func
(paren
r_void
)paren
(brace
id|ip_ct_iterate_cleanup
c_func
(paren
op_amp
id|clean_nat
comma
l_int|NULL
)paren
suffix:semicolon
id|ip_conntrack_destroyed
op_assign
l_int|NULL
suffix:semicolon
id|vfree
c_func
(paren
id|bysource
)paren
suffix:semicolon
)brace
eof
