macro_line|#ifndef _IP_CONNTRACK_H
DECL|macro|_IP_CONNTRACK_H
mdefine_line|#define _IP_CONNTRACK_H
multiline_comment|/* Connection state tracking for netfilter.  This is separated from,&n;   but required by, the NAT layer; it can also be used by an iptables&n;   extension. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tuple.h&gt;
DECL|enum|ip_conntrack_info
r_enum
id|ip_conntrack_info
(brace
multiline_comment|/* Part of an established connection (either direction). */
DECL|enumerator|IP_CT_ESTABLISHED
id|IP_CT_ESTABLISHED
comma
multiline_comment|/* Like NEW, but related to an existing connection, or ICMP error&n;&t;   (in either direction). */
DECL|enumerator|IP_CT_RELATED
id|IP_CT_RELATED
comma
multiline_comment|/* Started a new connection to track (only&n;           IP_CT_DIR_ORIGINAL); may be a retransmission. */
DECL|enumerator|IP_CT_NEW
id|IP_CT_NEW
comma
multiline_comment|/* &gt;= this indicates reply direction */
DECL|enumerator|IP_CT_IS_REPLY
id|IP_CT_IS_REPLY
comma
multiline_comment|/* Number of distinct IP_CT types (no NEW in reply dirn). */
DECL|enumerator|IP_CT_NUMBER
id|IP_CT_NUMBER
op_assign
id|IP_CT_IS_REPLY
op_star
l_int|2
op_minus
l_int|1
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_icmp.h&gt;
macro_line|#ifdef CONFIG_NF_DEBUG
DECL|macro|IP_NF_ASSERT
mdefine_line|#define IP_NF_ASSERT(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(x))&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/* Wooah!  I&squot;m tripping my conntrack in a frenzy of&t;&bslash;&n;&t;&t;   netplay... */&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;NF_IP_ASSERT: %s:%i(%s)&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;       __FILE__, __LINE__, __FUNCTION__);&t;&t;&bslash;&n;} while(0)
macro_line|#else
DECL|macro|IP_NF_ASSERT
mdefine_line|#define IP_NF_ASSERT(x)
macro_line|#endif
multiline_comment|/* Bitset representing status of connection. */
DECL|enum|ip_conntrack_status
r_enum
id|ip_conntrack_status
(brace
multiline_comment|/* It&squot;s an expected connection: bit 0 set.  This bit never changed */
DECL|enumerator|IPS_EXPECTED_BIT
id|IPS_EXPECTED_BIT
op_assign
l_int|0
comma
DECL|enumerator|IPS_EXPECTED
id|IPS_EXPECTED
op_assign
(paren
l_int|1
op_lshift
id|IPS_EXPECTED_BIT
)paren
comma
multiline_comment|/* We&squot;ve seen packets both ways: bit 1 set.  Can be set, not unset. */
DECL|enumerator|IPS_SEEN_REPLY_BIT
id|IPS_SEEN_REPLY_BIT
op_assign
l_int|1
comma
DECL|enumerator|IPS_SEEN_REPLY
id|IPS_SEEN_REPLY
op_assign
(paren
l_int|1
op_lshift
id|IPS_SEEN_REPLY_BIT
)paren
comma
multiline_comment|/* Conntrack should never be early-expired. */
DECL|enumerator|IPS_ASSURED_BIT
id|IPS_ASSURED_BIT
op_assign
l_int|2
comma
DECL|enumerator|IPS_ASSURED
id|IPS_ASSURED
op_assign
(paren
l_int|1
op_lshift
id|IPS_ASSURED_BIT
)paren
comma
)brace
suffix:semicolon
DECL|struct|ip_conntrack_expect
r_struct
id|ip_conntrack_expect
(brace
multiline_comment|/* Internal linked list */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* We expect this tuple, with the following mask */
DECL|member|tuple
DECL|member|mask
r_struct
id|ip_conntrack_tuple
id|tuple
comma
id|mask
suffix:semicolon
multiline_comment|/* Function to call after setup and insertion */
DECL|member|expectfn
r_int
(paren
op_star
id|expectfn
)paren
(paren
r_struct
id|ip_conntrack
op_star
r_new
)paren
suffix:semicolon
multiline_comment|/* The conntrack we are part of (set iff we&squot;re live) */
DECL|member|expectant
r_struct
id|ip_conntrack
op_star
id|expectant
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_IP_NF_NAT_NEEDED
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_ftp.h&gt;
DECL|struct|ip_conntrack
r_struct
id|ip_conntrack
(brace
multiline_comment|/* Usage count in here is 1 for hash table/destruct timer, 1 per skb,&n;           plus 1 for any connection(s) we are `master&squot; for */
DECL|member|ct_general
r_struct
id|nf_conntrack
id|ct_general
suffix:semicolon
multiline_comment|/* These are my tuples; original and reply */
DECL|member|tuplehash
r_struct
id|ip_conntrack_tuple_hash
id|tuplehash
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
multiline_comment|/* Have we seen traffic both ways yet? (bitset) */
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* Timer function; drops refcnt when it goes off. */
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
multiline_comment|/* If we&squot;re expecting another related connection, this will be&n;           in expected linked list */
DECL|member|expected
r_struct
id|ip_conntrack_expect
id|expected
suffix:semicolon
multiline_comment|/* If we were expected by another connection, this will be it */
DECL|member|master
r_struct
id|nf_ct_info
id|master
suffix:semicolon
multiline_comment|/* Helper, if any. */
DECL|member|helper
r_struct
id|ip_conntrack_helper
op_star
id|helper
suffix:semicolon
multiline_comment|/* Our various nf_ct_info structs specify *what* relation this&n;           packet has to the conntrack */
DECL|member|infos
r_struct
id|nf_ct_info
id|infos
(braket
id|IP_CT_NUMBER
)braket
suffix:semicolon
multiline_comment|/* Storage reserved for other modules: */
r_union
(brace
DECL|member|tcp
r_struct
id|ip_ct_tcp
id|tcp
suffix:semicolon
DECL|member|icmp
r_struct
id|ip_ct_icmp
id|icmp
suffix:semicolon
DECL|member|proto
)brace
id|proto
suffix:semicolon
r_union
(brace
DECL|member|ct_ftp_info
r_struct
id|ip_ct_ftp
id|ct_ftp_info
suffix:semicolon
DECL|member|help
)brace
id|help
suffix:semicolon
macro_line|#ifdef CONFIG_IP_NF_NAT_NEEDED
r_struct
(brace
DECL|member|info
r_struct
id|ip_nat_info
id|info
suffix:semicolon
r_union
(brace
multiline_comment|/* insert nat helper private data here */
DECL|member|help
)brace
id|help
suffix:semicolon
macro_line|#if defined(CONFIG_IP_NF_TARGET_MASQUERADE) || &bslash;&n;&t;defined(CONFIG_IP_NF_TARGET_MASQUERADE_MODULE)
DECL|member|masq_index
r_int
id|masq_index
suffix:semicolon
macro_line|#endif
DECL|member|nat
)brace
id|nat
suffix:semicolon
macro_line|#endif /* CONFIG_IP_NF_NAT_NEEDED */
)brace
suffix:semicolon
multiline_comment|/* Alter reply tuple (maybe alter helper).  If it&squot;s already taken,&n;   return 0 and don&squot;t do alteration. */
r_extern
r_int
id|ip_conntrack_alter_reply
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|newreply
)paren
suffix:semicolon
multiline_comment|/* Is this tuple taken? (ignoring any belonging to the given&n;   conntrack). */
r_extern
r_int
id|ip_conntrack_tuple_taken
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
multiline_comment|/* Return conntrack_info and tuple hash for given skb. */
r_extern
r_struct
id|ip_conntrack
op_star
id|ip_conntrack_get
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_enum
id|ip_conntrack_info
op_star
id|ctinfo
)paren
suffix:semicolon
r_extern
r_struct
id|module
op_star
id|ip_conntrack_module
suffix:semicolon
r_extern
r_int
id|invert_tuplepr
c_func
(paren
r_struct
id|ip_conntrack_tuple
op_star
id|inverse
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|orig
)paren
suffix:semicolon
multiline_comment|/* Refresh conntrack for this many jiffies */
r_extern
r_void
id|ip_ct_refresh
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_int
r_int
id|extra_jiffies
)paren
suffix:semicolon
multiline_comment|/* These are for NAT.  Icky. */
multiline_comment|/* Call me when a conntrack is destroyed. */
r_extern
r_void
(paren
op_star
id|ip_conntrack_destroyed
)paren
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
suffix:semicolon
multiline_comment|/* Returns new sk_buff, or NULL */
r_struct
id|sk_buff
op_star
id|ip_ct_gather_frags
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Delete all conntracks which match. */
r_extern
r_void
id|ip_ct_selective_cleanup
c_func
(paren
r_int
(paren
op_star
id|kill
)paren
(paren
r_const
r_struct
id|ip_conntrack
op_star
id|i
comma
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* It&squot;s confirmed if it is, or has been in the hash table. */
DECL|function|is_confirmed
r_static
r_inline
r_int
id|is_confirmed
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
)paren
(brace
r_return
id|ct-&gt;tuplehash
(braket
id|IP_CT_DIR_ORIGINAL
)braket
dot
id|list.next
op_ne
l_int|NULL
suffix:semicolon
)brace
r_extern
r_int
r_int
id|ip_conntrack_htable_size
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _IP_CONNTRACK_H */
eof
