multiline_comment|/* Header for use in defining a given protocol for connection tracking. */
macro_line|#ifndef _IP_CONNTRACK_PROTOCOL_H
DECL|macro|_IP_CONNTRACK_PROTOCOL_H
mdefine_line|#define _IP_CONNTRACK_PROTOCOL_H
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
multiline_comment|/* length of buffer to which print_tuple/print_conntrack members are&n; * writing */
DECL|macro|IP_CT_PRINT_BUFLEN
mdefine_line|#define IP_CT_PRINT_BUFLEN 100
DECL|struct|ip_conntrack_protocol
r_struct
id|ip_conntrack_protocol
(brace
multiline_comment|/* Next pointer. */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Protocol number. */
DECL|member|proto
id|u_int8_t
id|proto
suffix:semicolon
multiline_comment|/* Protocol name */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Try to fill in the third arg: dataoff is offset past IP&n;           hdr.  Return true if possible. */
DECL|member|pkt_to_tuple
r_int
(paren
op_star
id|pkt_to_tuple
)paren
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_int
id|dataoff
comma
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
suffix:semicolon
multiline_comment|/* Invert the per-proto part of the tuple: ie. turn xmit into reply.&n;&t; * Some packets can&squot;t be inverted: return 0 in that case.&n;&t; */
DECL|member|invert_tuple
r_int
(paren
op_star
id|invert_tuple
)paren
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
multiline_comment|/* Print out the per-protocol part of the tuple. */
DECL|member|print_tuple
r_int
r_int
(paren
op_star
id|print_tuple
)paren
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
)paren
suffix:semicolon
multiline_comment|/* Print out the private part of the conntrack. */
DECL|member|print_conntrack
r_int
r_int
(paren
op_star
id|print_conntrack
)paren
(paren
r_char
op_star
id|buffer
comma
r_const
r_struct
id|ip_conntrack
op_star
)paren
suffix:semicolon
multiline_comment|/* Returns verdict for packet, or -1 for invalid. */
DECL|member|packet
r_int
(paren
op_star
id|packet
)paren
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
suffix:semicolon
multiline_comment|/* Called when a new connection for this protocol found;&n;&t; * returns TRUE if it&squot;s OK.  If so, packet() called next. */
DECL|member|new
r_int
(paren
op_star
r_new
)paren
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Called when a conntrack entry is destroyed */
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|ip_conntrack
op_star
id|conntrack
)paren
suffix:semicolon
multiline_comment|/* Has to decide if a expectation matches one packet or not */
DECL|member|exp_matches_pkt
r_int
(paren
op_star
id|exp_matches_pkt
)paren
(paren
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|error
r_int
(paren
op_star
id|error
)paren
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
comma
r_int
r_int
id|hooknum
)paren
suffix:semicolon
multiline_comment|/* Module (if any) which this is connected to. */
DECL|member|me
r_struct
id|module
op_star
id|me
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Protocol registration. */
r_extern
r_int
id|ip_conntrack_protocol_register
c_func
(paren
r_struct
id|ip_conntrack_protocol
op_star
id|proto
)paren
suffix:semicolon
r_extern
r_void
id|ip_conntrack_protocol_unregister
c_func
(paren
r_struct
id|ip_conntrack_protocol
op_star
id|proto
)paren
suffix:semicolon
multiline_comment|/* Existing built-in protocols */
r_extern
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_tcp
suffix:semicolon
r_extern
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_udp
suffix:semicolon
r_extern
r_struct
id|ip_conntrack_protocol
id|ip_conntrack_protocol_icmp
suffix:semicolon
r_extern
r_int
id|ip_conntrack_protocol_tcp_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Log invalid packets */
r_extern
r_int
r_int
id|ip_ct_log_invalid
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
macro_line|#ifdef DEBUG_INVALID_PACKETS
DECL|macro|LOG_INVALID
mdefine_line|#define LOG_INVALID(proto) &bslash;&n;&t;(ip_ct_log_invalid == (proto) || ip_ct_log_invalid == IPPROTO_RAW)
macro_line|#else
DECL|macro|LOG_INVALID
mdefine_line|#define LOG_INVALID(proto) &bslash;&n;&t;((ip_ct_log_invalid == (proto) || ip_ct_log_invalid == IPPROTO_RAW) &bslash;&n;&t; &amp;&amp; net_ratelimit())
macro_line|#endif
macro_line|#else
DECL|macro|LOG_INVALID
mdefine_line|#define LOG_INVALID(proto) 0
macro_line|#endif /* CONFIG_SYSCTL */
macro_line|#endif /*_IP_CONNTRACK_PROTOCOL_H*/
eof
