multiline_comment|/*&n; * 25-Jul-1998 Major changes to allow for ip chain table&n; *&n; * 3-Jan-2000 Named tables to allow packet selection for different uses.&n; */
multiline_comment|/*&n; * &t;Format of an IP6 firewall descriptor&n; *&n; * &t;src, dst, src_mask, dst_mask are always stored in network byte order.&n; * &t;flags are stored in host byte order (of course).&n; * &t;Port numbers are stored in HOST byte order.&n; */
macro_line|#ifndef _IP6_TABLES_H
DECL|macro|_IP6_TABLES_H
mdefine_line|#define _IP6_TABLES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/netfilter_ipv6.h&gt;
DECL|macro|IP6T_FUNCTION_MAXNAMELEN
mdefine_line|#define IP6T_FUNCTION_MAXNAMELEN 30
DECL|macro|IP6T_TABLE_MAXNAMELEN
mdefine_line|#define IP6T_TABLE_MAXNAMELEN 32
multiline_comment|/* Yes, Virginia, you have to zero the padding. */
DECL|struct|ip6t_ip6
r_struct
id|ip6t_ip6
(brace
multiline_comment|/* Source and destination IP6 addr */
DECL|member|src
DECL|member|dst
r_struct
id|in6_addr
id|src
comma
id|dst
suffix:semicolon
multiline_comment|/* Mask for src and dest IP6 addr */
DECL|member|smsk
DECL|member|dmsk
r_struct
id|in6_addr
id|smsk
comma
id|dmsk
suffix:semicolon
DECL|member|iniface
DECL|member|outiface
r_char
id|iniface
(braket
id|IFNAMSIZ
)braket
comma
id|outiface
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|iniface_mask
DECL|member|outiface_mask
r_int
r_char
id|iniface_mask
(braket
id|IFNAMSIZ
)braket
comma
id|outiface_mask
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* ARGH, HopByHop uses 0, so can&squot;t do 0 = ANY,&n;&t;   instead IP6T_F_NOPROTO must be set */
DECL|member|proto
id|u_int16_t
id|proto
suffix:semicolon
multiline_comment|/* TOS to match iff flags &amp; IP6T_F_TOS */
DECL|member|tos
id|u_int8_t
id|tos
suffix:semicolon
multiline_comment|/* Flags word */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/* Inverse flags */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FIXME: If alignment in kernel different from userspace? --RR */
DECL|struct|ip6t_entry_match
r_struct
id|ip6t_entry_match
(brace
r_union
(brace
r_struct
(brace
DECL|member|match_size
id|u_int16_t
id|match_size
suffix:semicolon
multiline_comment|/* Used by userspace */
DECL|member|name
r_char
id|name
(braket
id|IP6T_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|user
)brace
id|user
suffix:semicolon
r_struct
(brace
DECL|member|match_size
id|u_int16_t
id|match_size
suffix:semicolon
multiline_comment|/* Used inside the kernel */
DECL|member|match
r_struct
id|ip6t_match
op_star
id|match
suffix:semicolon
DECL|member|kernel
)brace
id|kernel
suffix:semicolon
multiline_comment|/* Total length */
DECL|member|match_size
id|u_int16_t
id|match_size
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip6t_entry_target
r_struct
id|ip6t_entry_target
(brace
r_union
(brace
r_struct
(brace
DECL|member|target_size
id|u_int16_t
id|target_size
suffix:semicolon
multiline_comment|/* Used by userspace */
DECL|member|name
r_char
id|name
(braket
id|IP6T_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|user
)brace
id|user
suffix:semicolon
r_struct
(brace
DECL|member|target_size
id|u_int16_t
id|target_size
suffix:semicolon
multiline_comment|/* Used inside the kernel */
DECL|member|target
r_struct
id|ip6t_target
op_star
id|target
suffix:semicolon
DECL|member|kernel
)brace
id|kernel
suffix:semicolon
multiline_comment|/* Total length */
DECL|member|target_size
id|u_int16_t
id|target_size
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip6t_standard_target
r_struct
id|ip6t_standard_target
(brace
DECL|member|target
r_struct
id|ip6t_entry_target
id|target
suffix:semicolon
DECL|member|verdict
r_int
id|verdict
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip6t_counters
r_struct
id|ip6t_counters
(brace
DECL|member|pcnt
DECL|member|bcnt
id|u_int64_t
id|pcnt
comma
id|bcnt
suffix:semicolon
multiline_comment|/* Packet and byte counters */
)brace
suffix:semicolon
multiline_comment|/* Values for &quot;flag&quot; field in struct ip6t_ip6 (general ip6 structure). */
DECL|macro|IP6T_F_PROTO
mdefine_line|#define IP6T_F_PROTO&t;&t;0x01&t;/* Set if rule cares about upper &n;&t;&t;&t;&t;&t;   protocols */
DECL|macro|IP6T_F_TOS
mdefine_line|#define IP6T_F_TOS&t;&t;0x02&t;/* Match the TOS. */
DECL|macro|IP6T_F_MASK
mdefine_line|#define IP6T_F_MASK&t;&t;0x03&t;/* All possible flag bits mask. */
multiline_comment|/* Values for &quot;inv&quot; field in struct ip6t_ip6. */
DECL|macro|IP6T_INV_VIA_IN
mdefine_line|#define IP6T_INV_VIA_IN&t;&t;0x01&t;/* Invert the sense of IN IFACE. */
DECL|macro|IP6T_INV_VIA_OUT
mdefine_line|#define IP6T_INV_VIA_OUT&t;&t;0x02&t;/* Invert the sense of OUT IFACE */
DECL|macro|IP6T_INV_TOS
mdefine_line|#define IP6T_INV_TOS&t;&t;0x04&t;/* Invert the sense of TOS. */
DECL|macro|IP6T_INV_SRCIP
mdefine_line|#define IP6T_INV_SRCIP&t;&t;0x08&t;/* Invert the sense of SRC IP. */
DECL|macro|IP6T_INV_DSTIP
mdefine_line|#define IP6T_INV_DSTIP&t;&t;0x10&t;/* Invert the sense of DST OP. */
DECL|macro|IP6T_INV_FRAG
mdefine_line|#define IP6T_INV_FRAG&t;&t;0x20&t;/* Invert the sense of FRAG. */
DECL|macro|IP6T_INV_PROTO
mdefine_line|#define IP6T_INV_PROTO&t;&t;0x40&t;/* Invert the sense of PROTO. */
DECL|macro|IP6T_INV_MASK
mdefine_line|#define IP6T_INV_MASK&t;&t;0x7F&t;/* All possible flag bits mask. */
multiline_comment|/* This structure defines each of the firewall rules.  Consists of 3&n;   parts which are 1) general IP header stuff 2) match specific&n;   stuff 3) the target to perform if the rule matches */
DECL|struct|ip6t_entry
r_struct
id|ip6t_entry
(brace
DECL|member|ipv6
r_struct
id|ip6t_ip6
id|ipv6
suffix:semicolon
multiline_comment|/* Mark with fields that we care about. */
DECL|member|nfcache
r_int
r_int
id|nfcache
suffix:semicolon
multiline_comment|/* Size of ipt_entry + matches */
DECL|member|target_offset
id|u_int16_t
id|target_offset
suffix:semicolon
multiline_comment|/* Size of ipt_entry + matches + target */
DECL|member|next_offset
id|u_int16_t
id|next_offset
suffix:semicolon
multiline_comment|/* Back pointer */
DECL|member|comefrom
r_int
r_int
id|comefrom
suffix:semicolon
multiline_comment|/* Packet and byte counters. */
DECL|member|counters
r_struct
id|ip6t_counters
id|counters
suffix:semicolon
multiline_comment|/* The matches (if any), then the target. */
DECL|member|elems
r_int
r_char
id|elems
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * New IP firewall options for [gs]etsockopt at the RAW IP level.&n; * Unlike BSD Linux inherits IP options so you don&squot;t have to use&n; * a raw socket for this. Instead we check rights in the calls. */
DECL|macro|IP6T_BASE_CTL
mdefine_line|#define IP6T_BASE_CTL&t;&t;&t;64&t;/* base for firewall socket options */
DECL|macro|IP6T_SO_SET_REPLACE
mdefine_line|#define IP6T_SO_SET_REPLACE&t;&t;(IP6T_BASE_CTL)
DECL|macro|IP6T_SO_SET_ADD_COUNTERS
mdefine_line|#define IP6T_SO_SET_ADD_COUNTERS&t;(IP6T_BASE_CTL + 1)
DECL|macro|IP6T_SO_SET_MAX
mdefine_line|#define IP6T_SO_SET_MAX&t;&t;&t;IP6T_SO_SET_ADD_COUNTERS
DECL|macro|IP6T_SO_GET_INFO
mdefine_line|#define IP6T_SO_GET_INFO&t;&t;(IP6T_BASE_CTL)
DECL|macro|IP6T_SO_GET_ENTRIES
mdefine_line|#define IP6T_SO_GET_ENTRIES&t;&t;(IP6T_BASE_CTL + 1)
DECL|macro|IP6T_SO_GET_MAX
mdefine_line|#define IP6T_SO_GET_MAX&t;&t;&t;IP6T_SO_GET_ENTRIES
multiline_comment|/* CONTINUE verdict for targets */
DECL|macro|IP6T_CONTINUE
mdefine_line|#define IP6T_CONTINUE 0xFFFFFFFF
multiline_comment|/* For standard target */
DECL|macro|IP6T_RETURN
mdefine_line|#define IP6T_RETURN (-NF_MAX_VERDICT - 1)
multiline_comment|/* TCP matching stuff */
DECL|struct|ip6t_tcp
r_struct
id|ip6t_tcp
(brace
DECL|member|spts
id|u_int16_t
id|spts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Source port range. */
DECL|member|dpts
id|u_int16_t
id|dpts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Destination port range. */
DECL|member|option
id|u_int8_t
id|option
suffix:semicolon
multiline_comment|/* TCP Option iff non-zero*/
DECL|member|flg_mask
id|u_int8_t
id|flg_mask
suffix:semicolon
multiline_comment|/* TCP flags mask byte */
DECL|member|flg_cmp
id|u_int8_t
id|flg_cmp
suffix:semicolon
multiline_comment|/* TCP flags compare byte */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
multiline_comment|/* Inverse flags */
)brace
suffix:semicolon
multiline_comment|/* Values for &quot;inv&quot; field in struct ipt_tcp. */
DECL|macro|IP6T_TCP_INV_SRCPT
mdefine_line|#define IP6T_TCP_INV_SRCPT&t;0x01&t;/* Invert the sense of source ports. */
DECL|macro|IP6T_TCP_INV_DSTPT
mdefine_line|#define IP6T_TCP_INV_DSTPT&t;0x02&t;/* Invert the sense of dest ports. */
DECL|macro|IP6T_TCP_INV_FLAGS
mdefine_line|#define IP6T_TCP_INV_FLAGS&t;0x04&t;/* Invert the sense of TCP flags. */
DECL|macro|IP6T_TCP_INV_OPTION
mdefine_line|#define IP6T_TCP_INV_OPTION&t;0x08&t;/* Invert the sense of option test. */
DECL|macro|IP6T_TCP_INV_MASK
mdefine_line|#define IP6T_TCP_INV_MASK&t;0x0F&t;/* All possible flags. */
multiline_comment|/* UDP matching stuff */
DECL|struct|ip6t_udp
r_struct
id|ip6t_udp
(brace
DECL|member|spts
id|u_int16_t
id|spts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Source port range. */
DECL|member|dpts
id|u_int16_t
id|dpts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Destination port range. */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
multiline_comment|/* Inverse flags */
)brace
suffix:semicolon
multiline_comment|/* Values for &quot;invflags&quot; field in struct ipt_udp. */
DECL|macro|IP6T_UDP_INV_SRCPT
mdefine_line|#define IP6T_UDP_INV_SRCPT&t;0x01&t;/* Invert the sense of source ports. */
DECL|macro|IP6T_UDP_INV_DSTPT
mdefine_line|#define IP6T_UDP_INV_DSTPT&t;0x02&t;/* Invert the sense of dest ports. */
DECL|macro|IP6T_UDP_INV_MASK
mdefine_line|#define IP6T_UDP_INV_MASK&t;0x03&t;/* All possible flags. */
multiline_comment|/* ICMP matching stuff */
DECL|struct|ip6t_icmp
r_struct
id|ip6t_icmp
(brace
DECL|member|type
id|u_int8_t
id|type
suffix:semicolon
multiline_comment|/* type to match */
DECL|member|code
id|u_int8_t
id|code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* range of code */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
multiline_comment|/* Inverse flags */
)brace
suffix:semicolon
multiline_comment|/* Values for &quot;inv&quot; field for struct ipt_icmp. */
DECL|macro|IP6T_ICMP_INV
mdefine_line|#define IP6T_ICMP_INV&t;0x01&t;/* Invert the sense of type/code test */
multiline_comment|/* The argument to IP6T_SO_GET_INFO */
DECL|struct|ip6t_getinfo
r_struct
id|ip6t_getinfo
(brace
multiline_comment|/* Which table: caller fills this in. */
DECL|member|name
r_char
id|name
(braket
id|IP6T_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Kernel fills these in. */
multiline_comment|/* Which hook entry points are valid: bitmask */
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* Hook entry points: one per netfilter hook. */
DECL|member|hook_entry
r_int
r_int
id|hook_entry
(braket
id|NF_IP6_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Underflow points. */
DECL|member|underflow
r_int
r_int
id|underflow
(braket
id|NF_IP6_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|num_entries
r_int
r_int
id|num_entries
suffix:semicolon
multiline_comment|/* Size of entries. */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to IP6T_SO_SET_REPLACE. */
DECL|struct|ip6t_replace
r_struct
id|ip6t_replace
(brace
multiline_comment|/* Which table. */
DECL|member|name
r_char
id|name
(braket
id|IP6T_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Which hook entry points are valid: bitmask.  You can&squot;t&n;           change this. */
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|num_entries
r_int
r_int
id|num_entries
suffix:semicolon
multiline_comment|/* Total size of new entries */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* Hook entry points. */
DECL|member|hook_entry
r_int
r_int
id|hook_entry
(braket
id|NF_IP6_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Underflow points. */
DECL|member|underflow
r_int
r_int
id|underflow
(braket
id|NF_IP6_NUMHOOKS
)braket
suffix:semicolon
multiline_comment|/* Information about old entries: */
multiline_comment|/* Number of counters (must be equal to current number of entries). */
DECL|member|num_counters
r_int
r_int
id|num_counters
suffix:semicolon
multiline_comment|/* The old entries&squot; counters. */
DECL|member|counters
r_struct
id|ip6t_counters
op_star
id|counters
suffix:semicolon
multiline_comment|/* The entries (hang off end: not really an array). */
DECL|member|entries
r_struct
id|ip6t_entry
id|entries
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to IP6T_SO_ADD_COUNTERS. */
DECL|struct|ip6t_counters_info
r_struct
id|ip6t_counters_info
(brace
multiline_comment|/* Which table. */
DECL|member|name
r_char
id|name
(braket
id|IP6T_TABLE_MAXNAMELEN
)braket
suffix:semicolon
DECL|member|num_counters
r_int
r_int
id|num_counters
suffix:semicolon
multiline_comment|/* The counters (actually `number&squot; of these). */
DECL|member|counters
r_struct
id|ip6t_counters
id|counters
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument to IP6T_SO_GET_ENTRIES. */
DECL|struct|ip6t_get_entries
r_struct
id|ip6t_get_entries
(brace
multiline_comment|/* Which table: user fills this in. */
DECL|member|name
r_char
id|name
(braket
id|IP6T_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* User fills this in: total entry size. */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* The entries. */
DECL|member|entrytable
r_struct
id|ip6t_entry
id|entrytable
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Standard return verdict, or do jump. */
DECL|macro|IP6T_STANDARD_TARGET
mdefine_line|#define IP6T_STANDARD_TARGET &quot;&quot;
multiline_comment|/* Error verdict. */
DECL|macro|IP6T_ERROR_TARGET
mdefine_line|#define IP6T_ERROR_TARGET &quot;ERROR&quot;
multiline_comment|/* Helper functions */
r_static
id|__inline__
r_struct
id|ip6t_entry_target
op_star
DECL|function|ip6t_get_target
id|ip6t_get_target
c_func
(paren
r_struct
id|ip6t_entry
op_star
id|e
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|e
op_plus
id|e-&gt;target_offset
suffix:semicolon
)brace
multiline_comment|/* fn returns 0 to continue iteration */
DECL|macro|IP6T_MATCH_ITERATE
mdefine_line|#define IP6T_MATCH_ITERATE(e, fn, args...)&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __i;&t;&t;&t;&bslash;&n;&t;int __ret = 0;&t;&t;&t;&t;&bslash;&n;&t;struct ip6t_entry_match *__m;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__i = sizeof(struct ip6t_entry);&t;&bslash;&n;&t;     __i &lt; (e)-&gt;target_offset;&t;&t;&bslash;&n;&t;     __i += __m-&gt;u.match_size) {&t;&bslash;&n;&t;&t;__m = (void *)(e) + __i;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__ret = fn(__m , ## args);&t;&bslash;&n;&t;&t;if (__ret != 0)&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* fn returns 0 to continue iteration */
DECL|macro|IP6T_ENTRY_ITERATE
mdefine_line|#define IP6T_ENTRY_ITERATE(entries, size, fn, args...)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __i;&t;&t;&t;&t;&t;&bslash;&n;&t;int __ret = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct ip6t_entry *__e;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__i = 0; __i &lt; (size); __i += __e-&gt;next_offset) {&t;&bslash;&n;&t;&t;__e = (void *)(entries) + __i;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__ret = fn(__e , ## args);&t;&t;&t;&bslash;&n;&t;&t;if (__ret != 0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; *&t;Main firewall chains definitions and global var&squot;s definitions.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_void
id|ip6t_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
DECL|struct|ip6t_match
r_struct
id|ip6t_match
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_const
r_char
id|name
(braket
id|IP6T_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Return true or false: return FALSE and set *hotdrop = 1 to&n;           force immediate packet drop. */
DECL|member|match
r_int
(paren
op_star
id|match
)paren
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
suffix:semicolon
multiline_comment|/* Called when user tries to insert an entry of this type. */
multiline_comment|/* Should return true or false. */
DECL|member|checkentry
r_int
(paren
op_star
id|checkentry
)paren
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_ip6
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
suffix:semicolon
multiline_comment|/* Called when entry of this type deleted. */
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchinfosize
)paren
suffix:semicolon
multiline_comment|/* Set this to THIS_MODULE if you are a module, otherwise NULL */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Registration hooks for targets. */
DECL|struct|ip6t_target
r_struct
id|ip6t_target
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|name
r_const
r_char
id|name
(braket
id|IP6T_FUNCTION_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Returns verdict. */
DECL|member|target
r_int
r_int
(paren
op_star
id|target
)paren
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
id|userdata
)paren
suffix:semicolon
multiline_comment|/* Called when user tries to insert an entry of this type:&n;           hook_mask is a bitmask of hooks from which it can be&n;           called. */
multiline_comment|/* Should return true or false. */
DECL|member|checkentry
r_int
(paren
op_star
id|checkentry
)paren
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_entry
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
suffix:semicolon
multiline_comment|/* Called when entry of this type deleted. */
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
)paren
suffix:semicolon
multiline_comment|/* Set this to THIS_MODULE if you are a module, otherwise NULL */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ip6t_register_target
c_func
(paren
r_struct
id|ip6t_target
op_star
id|target
)paren
suffix:semicolon
r_extern
r_void
id|ip6t_unregister_target
c_func
(paren
r_struct
id|ip6t_target
op_star
id|target
)paren
suffix:semicolon
r_extern
r_int
id|ip6t_register_match
c_func
(paren
r_struct
id|ip6t_match
op_star
id|match
)paren
suffix:semicolon
r_extern
r_void
id|ip6t_unregister_match
c_func
(paren
r_struct
id|ip6t_match
op_star
id|match
)paren
suffix:semicolon
multiline_comment|/* Furniture shopping... */
DECL|struct|ip6t_table
r_struct
id|ip6t_table
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* A unique name... */
DECL|member|name
r_char
id|name
(braket
id|IP6T_TABLE_MAXNAMELEN
)braket
suffix:semicolon
multiline_comment|/* Seed table: copied in register_table */
DECL|member|table
r_struct
id|ip6t_replace
op_star
id|table
suffix:semicolon
multiline_comment|/* What hooks you will enter on */
DECL|member|valid_hooks
r_int
r_int
id|valid_hooks
suffix:semicolon
multiline_comment|/* Lock for the curtain */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
multiline_comment|/* Man behind the curtain... */
DECL|member|private
r_struct
id|ip6t_table_info
op_star
r_private
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ip6t_register_table
c_func
(paren
r_struct
id|ip6t_table
op_star
id|table
)paren
suffix:semicolon
r_extern
r_void
id|ip6t_unregister_table
c_func
(paren
r_struct
id|ip6t_table
op_star
id|table
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ip6t_do_table
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
id|hook
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
id|ip6t_table
op_star
id|table
comma
r_void
op_star
id|userdata
)paren
suffix:semicolon
DECL|macro|IP6T_ALIGN
mdefine_line|#define IP6T_ALIGN(s) (((s) + (__alignof__(struct ip6t_entry)-1)) &amp; ~(__alignof__(struct ip6t_entry)-1))
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /* _IP6_TABLES_H */
eof
