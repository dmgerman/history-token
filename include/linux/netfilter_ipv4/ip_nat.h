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
multiline_comment|/* SRC manip occurs only on POST_ROUTING */
DECL|macro|HOOK2MANIP
mdefine_line|#define HOOK2MANIP(hooknum) ((hooknum) != NF_IP_POST_ROUTING)
multiline_comment|/* 2.3.19 (I hope) will define this in linux/netfilter_ipv4.h. */
macro_line|#ifndef SO_ORIGINAL_DST
DECL|macro|SO_ORIGINAL_DST
mdefine_line|#define SO_ORIGINAL_DST 80
macro_line|#endif
DECL|macro|IP_NAT_RANGE_MAP_IPS
mdefine_line|#define IP_NAT_RANGE_MAP_IPS 1
DECL|macro|IP_NAT_RANGE_PROTO_SPECIFIED
mdefine_line|#define IP_NAT_RANGE_PROTO_SPECIFIED 2
multiline_comment|/* Used internally by get_unique_tuple(). */
DECL|macro|IP_NAT_RANGE_FULL
mdefine_line|#define IP_NAT_RANGE_FULL 4
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
multiline_comment|/* A range consists of an array of 1 or more ip_nat_range */
DECL|struct|ip_nat_multi_range
r_struct
id|ip_nat_multi_range
(brace
DECL|member|rangesize
r_int
r_int
id|rangesize
suffix:semicolon
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
multiline_comment|/* Hashes for by-source and IP/protocol. */
DECL|struct|ip_nat_hash
r_struct
id|ip_nat_hash
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* conntrack we&squot;re embedded in: NULL if not in hash. */
DECL|member|conntrack
r_struct
id|ip_conntrack
op_star
id|conntrack
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
multiline_comment|/* The structure embedded in the conntrack structure. */
DECL|struct|ip_nat_info
r_struct
id|ip_nat_info
(brace
multiline_comment|/* Set to zero when conntrack created: bitmask of maniptypes */
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
DECL|member|num_manips
r_int
r_int
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
multiline_comment|/* The mapping type which created us (NULL for null mapping). */
DECL|member|mtype
r_const
r_struct
id|ip_nat_mapping_type
op_star
id|mtype
suffix:semicolon
DECL|member|bysource
DECL|member|byipsproto
r_struct
id|ip_nat_hash
id|bysource
comma
id|byipsproto
suffix:semicolon
multiline_comment|/* Helper (NULL if none). */
DECL|member|helper
r_struct
id|ip_nat_helper
op_star
id|helper
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
id|ip_nat_multi_range
op_star
id|mr
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
macro_line|#endif /*__KERNEL__*/
macro_line|#endif
eof
