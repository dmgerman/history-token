macro_line|#ifndef _IP_NAT_H
DECL|macro|_IP_NAT_H
mdefine_line|#define _IP_NAT_H
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tuple.h&gt;
DECL|macro|IP_NAT_MAPPING_TYPE_MAX_NAMELEN
mdefine_line|#define IP_NAT_MAPPING_TYPE_MAX_NAMELEN 16
DECL|enum|ip_nat_manip_type
r_enum
id|ip_nat_manip_type
(brace
DECL|enumerator|IP_NAT_MANIP_SRC
id|IP_NAT_MANIP_SRC
comma
DECL|enumerator|IP_NAT_MANIP_DST
id|IP_NAT_MANIP_DST
)brace
suffix:semicolon
multiline_comment|/* SRC manip occurs POST_ROUTING or LOCAL_IN */
DECL|macro|HOOK2MANIP
mdefine_line|#define HOOK2MANIP(hooknum) ((hooknum) != NF_IP_POST_ROUTING &amp;&amp; (hooknum) != NF_IP_LOCAL_IN)
DECL|macro|IP_NAT_RANGE_MAP_IPS
mdefine_line|#define IP_NAT_RANGE_MAP_IPS 1
DECL|macro|IP_NAT_RANGE_PROTO_SPECIFIED
mdefine_line|#define IP_NAT_RANGE_PROTO_SPECIFIED 2
multiline_comment|/* Used internally by get_unique_tuple(). */
DECL|macro|IP_NAT_RANGE_FULL
mdefine_line|#define IP_NAT_RANGE_FULL 4
multiline_comment|/* NAT sequence number modifications */
DECL|struct|ip_nat_seq
r_struct
id|ip_nat_seq
(brace
multiline_comment|/* position of the last TCP sequence number &n;&t; * modification (if any) */
DECL|member|correction_pos
id|u_int32_t
id|correction_pos
suffix:semicolon
multiline_comment|/* sequence number offset before and after last modification */
DECL|member|offset_before
DECL|member|offset_after
r_int32
id|offset_before
comma
id|offset_after
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Single range specification. */
DECL|struct|ip_nat_range
r_struct
id|ip_nat_range
(brace
multiline_comment|/* Set to OR of flags above. */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Inclusive: network order. */
DECL|member|min_ip
DECL|member|max_ip
id|u_int32_t
id|min_ip
comma
id|max_ip
suffix:semicolon
multiline_comment|/* Inclusive: network order */
DECL|member|min
DECL|member|max
r_union
id|ip_conntrack_manip_proto
id|min
comma
id|max
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For backwards compat: don&squot;t use in modern code. */
DECL|struct|ip_nat_multi_range_compat
r_struct
id|ip_nat_multi_range_compat
(brace
DECL|member|rangesize
r_int
r_int
id|rangesize
suffix:semicolon
multiline_comment|/* Must be 1. */
multiline_comment|/* hangs off end. */
DECL|member|range
r_struct
id|ip_nat_range
id|range
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Worst case: local-out manip + 1 post-routing, and reverse dirn. */
DECL|macro|IP_NAT_MAX_MANIPS
mdefine_line|#define IP_NAT_MAX_MANIPS (2*3)
DECL|struct|ip_nat_info_manip
r_struct
id|ip_nat_info_manip
(brace
multiline_comment|/* The direction. */
DECL|member|direction
id|u_int8_t
id|direction
suffix:semicolon
multiline_comment|/* Which hook the manipulation happens on. */
DECL|member|hooknum
id|u_int8_t
id|hooknum
suffix:semicolon
multiline_comment|/* The manipulation type. */
DECL|member|maniptype
id|u_int8_t
id|maniptype
suffix:semicolon
multiline_comment|/* Manipulations to occur at each conntrack in this dirn. */
DECL|member|manip
r_struct
id|ip_conntrack_manip
id|manip
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
multiline_comment|/* Protects NAT hash tables, and NAT-private part of conntracks. */
DECL|variable|ip_nat_lock
id|DECLARE_RWLOCK_EXTERN
c_func
(paren
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* The structure embedded in the conntrack structure. */
DECL|struct|ip_nat_info
r_struct
id|ip_nat_info
(brace
multiline_comment|/* Set to zero when conntrack created: bitmask of maniptypes */
DECL|member|initialized
id|u_int16_t
id|initialized
suffix:semicolon
DECL|member|num_manips
id|u_int16_t
id|num_manips
suffix:semicolon
multiline_comment|/* Manipulations to be done on this conntrack. */
DECL|member|manips
r_struct
id|ip_nat_info_manip
id|manips
(braket
id|IP_NAT_MAX_MANIPS
)braket
suffix:semicolon
DECL|member|bysource
r_struct
id|list_head
id|bysource
suffix:semicolon
multiline_comment|/* Helper (NULL if none). */
DECL|member|helper
r_struct
id|ip_nat_helper
op_star
id|helper
suffix:semicolon
DECL|member|seq
r_struct
id|ip_nat_seq
id|seq
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Set up the info structure to map into this range. */
r_extern
r_int
r_int
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
suffix:semicolon
multiline_comment|/* Is this tuple already taken? (not by us)*/
r_extern
r_int
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
suffix:semicolon
multiline_comment|/* Calculate relative checksum. */
r_extern
id|u_int16_t
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
suffix:semicolon
macro_line|#else  /* !__KERNEL__: iptables wants this to compile. */
DECL|macro|ip_nat_multi_range
mdefine_line|#define ip_nat_multi_range ip_nat_multi_range_compat
macro_line|#endif /*__KERNEL__*/
macro_line|#endif
eof
