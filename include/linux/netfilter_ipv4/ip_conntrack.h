macro_line|#ifndef _IP_CONNTRACK_H
DECL|macro|_IP_CONNTRACK_H
mdefine_line|#define _IP_CONNTRACK_H
multiline_comment|/* Connection state tracking for netfilter.  This is separated from,&n;   but required by, the NAT layer; it can also be used by an iptables&n;   extension. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tuple.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
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
multiline_comment|/* Connection is confirmed: originating packet has left box */
DECL|enumerator|IPS_CONFIRMED_BIT
id|IPS_CONFIRMED_BIT
op_assign
l_int|3
comma
DECL|enumerator|IPS_CONFIRMED
id|IPS_CONFIRMED
op_assign
(paren
l_int|1
op_lshift
id|IPS_CONFIRMED_BIT
)paren
comma
)brace
suffix:semicolon
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_tcp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_icmp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_sctp.h&gt;
multiline_comment|/* per conntrack: protocol private data */
DECL|union|ip_conntrack_proto
r_union
id|ip_conntrack_proto
(brace
multiline_comment|/* insert conntrack proto private data here */
DECL|member|sctp
r_struct
id|ip_ct_sctp
id|sctp
suffix:semicolon
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
)brace
suffix:semicolon
DECL|union|ip_conntrack_expect_proto
r_union
id|ip_conntrack_expect_proto
(brace
multiline_comment|/* insert expect proto private data here */
)brace
suffix:semicolon
multiline_comment|/* Add protocol helper include file here */
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_amanda.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_ftp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_irc.h&gt;
multiline_comment|/* per expectation: application helper private data */
DECL|union|ip_conntrack_expect_help
r_union
id|ip_conntrack_expect_help
(brace
multiline_comment|/* insert conntrack helper private data (expect) here */
DECL|member|exp_amanda_info
r_struct
id|ip_ct_amanda_expect
id|exp_amanda_info
suffix:semicolon
DECL|member|exp_ftp_info
r_struct
id|ip_ct_ftp_expect
id|exp_ftp_info
suffix:semicolon
DECL|member|exp_irc_info
r_struct
id|ip_ct_irc_expect
id|exp_irc_info
suffix:semicolon
macro_line|#ifdef CONFIG_IP_NF_NAT_NEEDED
r_union
(brace
multiline_comment|/* insert nat helper private data (expect) here */
DECL|member|nat
)brace
id|nat
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* per conntrack: application helper private data */
DECL|union|ip_conntrack_help
r_union
id|ip_conntrack_help
(brace
multiline_comment|/* insert conntrack helper private data (master) here */
DECL|member|ct_ftp_info
r_struct
id|ip_ct_ftp_master
id|ct_ftp_info
suffix:semicolon
DECL|member|ct_irc_info
r_struct
id|ip_ct_irc_master
id|ct_irc_info
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_IP_NF_NAT_NEEDED
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
multiline_comment|/* per conntrack: nat application helper private data */
DECL|union|ip_conntrack_nat_help
r_union
id|ip_conntrack_nat_help
(brace
multiline_comment|/* insert nat helper private data here */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|macro|IP_NF_ASSERT
mdefine_line|#define IP_NF_ASSERT(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(x))&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/* Wooah!  I&squot;m tripping my conntrack in a frenzy of&t;&bslash;&n;&t;&t;   netplay... */&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;NF_IP_ASSERT: %s:%i(%s)&bslash;n&quot;,&t;&t;&t;&bslash;&n;&t;&t;       __FILE__, __LINE__, __FUNCTION__);&t;&t;&bslash;&n;} while(0)
macro_line|#else
DECL|macro|IP_NF_ASSERT
mdefine_line|#define IP_NF_ASSERT(x)
macro_line|#endif
DECL|struct|ip_conntrack_expect
r_struct
id|ip_conntrack_expect
(brace
multiline_comment|/* Internal linked list (global expectation list) */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|use
id|atomic_t
id|use
suffix:semicolon
multiline_comment|/* expectation list for this master */
DECL|member|expected_list
r_struct
id|list_head
id|expected_list
suffix:semicolon
multiline_comment|/* The conntrack of the master connection */
DECL|member|expectant
r_struct
id|ip_conntrack
op_star
id|expectant
suffix:semicolon
multiline_comment|/* The conntrack of the sibling connection, set after&n;&t; * expectation arrived */
DECL|member|sibling
r_struct
id|ip_conntrack
op_star
id|sibling
suffix:semicolon
multiline_comment|/* Tuple saved for conntrack */
DECL|member|ct_tuple
r_struct
id|ip_conntrack_tuple
id|ct_tuple
suffix:semicolon
multiline_comment|/* Timer function; deletes the expectation. */
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
multiline_comment|/* Data filled out by the conntrack helpers follow: */
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
multiline_comment|/* At which sequence number did this expectation occur */
DECL|member|seq
id|u_int32_t
id|seq
suffix:semicolon
DECL|member|proto
r_union
id|ip_conntrack_expect_proto
id|proto
suffix:semicolon
DECL|member|help
r_union
id|ip_conntrack_expect_help
id|help
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip_conntrack_counter
r_struct
id|ip_conntrack_counter
(brace
DECL|member|packets
id|u_int64_t
id|packets
suffix:semicolon
DECL|member|bytes
id|u_int64_t
id|bytes
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|ip_conntrack_helper
suffix:semicolon
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
multiline_comment|/* Have we seen traffic both ways yet? (bitset) */
DECL|member|status
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
macro_line|#ifdef CONFIG_IP_NF_CT_ACCT
multiline_comment|/* Accounting Information (same cache line as other written members) */
DECL|member|counters
r_struct
id|ip_conntrack_counter
id|counters
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* If we&squot;re expecting another related connection, this will be&n;           in expected linked list */
DECL|member|sibling_list
r_struct
id|list_head
id|sibling_list
suffix:semicolon
multiline_comment|/* Current number of expected connections */
DECL|member|expecting
r_int
r_int
id|expecting
suffix:semicolon
multiline_comment|/* If we were expected by an expectation, this will be it */
DECL|member|master
r_struct
id|ip_conntrack_expect
op_star
id|master
suffix:semicolon
multiline_comment|/* Helper, if any. */
DECL|member|helper
r_struct
id|ip_conntrack_helper
op_star
id|helper
suffix:semicolon
multiline_comment|/* Storage reserved for other modules: */
DECL|member|proto
r_union
id|ip_conntrack_proto
id|proto
suffix:semicolon
DECL|member|help
r_union
id|ip_conntrack_help
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
DECL|member|help
r_union
id|ip_conntrack_nat_help
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
macro_line|#if defined(CONFIG_IP_NF_CONNTRACK_MARK)
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
macro_line|#endif
multiline_comment|/* Traversed often, so hopefully in different cacheline to top */
multiline_comment|/* These are my tuples; original and reply */
DECL|member|tuplehash
r_struct
id|ip_conntrack_tuple_hash
id|tuplehash
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* get master conntrack via master expectation */
DECL|macro|master_ct
mdefine_line|#define master_ct(conntr) (conntr-&gt;master ? conntr-&gt;master-&gt;expectant : NULL)
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
r_static
r_inline
r_struct
id|ip_conntrack
op_star
DECL|function|ip_conntrack_get
id|ip_conntrack_get
c_func
(paren
r_const
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
(brace
op_star
id|ctinfo
op_assign
id|skb-&gt;nfctinfo
suffix:semicolon
r_return
(paren
r_struct
id|ip_conntrack
op_star
)paren
id|skb-&gt;nfct
suffix:semicolon
)brace
multiline_comment|/* decrement reference count on a conntrack */
r_extern
r_inline
r_void
id|ip_conntrack_put
c_func
(paren
r_struct
id|ip_conntrack
op_star
id|ct
)paren
suffix:semicolon
multiline_comment|/* find unconfirmed expectation based on tuple */
r_struct
id|ip_conntrack_expect
op_star
id|ip_conntrack_expect_find_get
c_func
(paren
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
suffix:semicolon
multiline_comment|/* decrement reference count on an expectation */
r_void
id|ip_conntrack_expect_put
c_func
(paren
r_struct
id|ip_conntrack_expect
op_star
id|exp
)paren
suffix:semicolon
multiline_comment|/* call to create an explicit dependency on ip_conntrack. */
r_extern
r_void
id|need_ip_conntrack
c_func
(paren
r_void
)paren
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
id|ip_ct_refresh_acct
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
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|extra_jiffies
)paren
suffix:semicolon
multiline_comment|/* These are for NAT.  Icky. */
multiline_comment|/* Update TCP window tracking data when NAT mangles the packet */
r_extern
r_int
id|ip_conntrack_tcp_update
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_int
id|dir
)paren
suffix:semicolon
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
multiline_comment|/* Fake conntrack entry for untracked connections */
r_extern
r_struct
id|ip_conntrack
id|ip_conntrack_untracked
suffix:semicolon
r_extern
r_int
id|ip_ct_no_defrag
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
multiline_comment|/* Iterate over all conntracks: if iter returns true, it&squot;s deleted. */
r_extern
r_void
id|ip_ct_iterate_cleanup
c_func
(paren
r_int
(paren
op_star
id|iter
)paren
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
id|test_bit
c_func
(paren
id|IPS_CONFIRMED_BIT
comma
op_amp
id|ct-&gt;status
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|ip_conntrack_htable_size
suffix:semicolon
DECL|struct|ip_conntrack_stat
r_struct
id|ip_conntrack_stat
(brace
DECL|member|searched
r_int
r_int
id|searched
suffix:semicolon
DECL|member|found
r_int
r_int
id|found
suffix:semicolon
DECL|member|new
r_int
r_int
r_new
suffix:semicolon
DECL|member|invalid
r_int
r_int
id|invalid
suffix:semicolon
DECL|member|ignore
r_int
r_int
id|ignore
suffix:semicolon
DECL|member|delete
r_int
r_int
r_delete
suffix:semicolon
DECL|member|delete_list
r_int
r_int
id|delete_list
suffix:semicolon
DECL|member|insert
r_int
r_int
id|insert
suffix:semicolon
DECL|member|insert_failed
r_int
r_int
id|insert_failed
suffix:semicolon
DECL|member|drop
r_int
r_int
id|drop
suffix:semicolon
DECL|member|early_drop
r_int
r_int
id|early_drop
suffix:semicolon
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
DECL|member|expect_new
r_int
r_int
id|expect_new
suffix:semicolon
DECL|member|expect_create
r_int
r_int
id|expect_create
suffix:semicolon
DECL|member|expect_delete
r_int
r_int
id|expect_delete
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CONNTRACK_STAT_INC
mdefine_line|#define CONNTRACK_STAT_INC(count) (__get_cpu_var(ip_conntrack_stat).count++)
multiline_comment|/* eg. PROVIDES_CONNTRACK(ftp); */
DECL|macro|PROVIDES_CONNTRACK
mdefine_line|#define PROVIDES_CONNTRACK(name)                        &bslash;&n;        int needs_ip_conntrack_##name;                  &bslash;&n;        EXPORT_SYMBOL(needs_ip_conntrack_##name)
multiline_comment|/*. eg. NEEDS_CONNTRACK(ftp); */
DECL|macro|NEEDS_CONNTRACK
mdefine_line|#define NEEDS_CONNTRACK(name)                                           &bslash;&n;        extern int needs_ip_conntrack_##name;                           &bslash;&n;        static int *need_ip_conntrack_##name __attribute_used__ = &amp;needs_ip_conntrack_##name
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _IP_CONNTRACK_H */
eof
