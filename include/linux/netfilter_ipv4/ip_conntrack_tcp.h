macro_line|#ifndef _IP_CONNTRACK_TCP_H
DECL|macro|_IP_CONNTRACK_TCP_H
mdefine_line|#define _IP_CONNTRACK_TCP_H
multiline_comment|/* TCP tracking. */
macro_line|#ifndef __KERNEL__
macro_line|#error Only in kernel.
macro_line|#endif
DECL|enum|tcp_conntrack
r_enum
id|tcp_conntrack
(brace
DECL|enumerator|TCP_CONNTRACK_NONE
id|TCP_CONNTRACK_NONE
comma
DECL|enumerator|TCP_CONNTRACK_ESTABLISHED
id|TCP_CONNTRACK_ESTABLISHED
comma
DECL|enumerator|TCP_CONNTRACK_SYN_SENT
id|TCP_CONNTRACK_SYN_SENT
comma
DECL|enumerator|TCP_CONNTRACK_SYN_RECV
id|TCP_CONNTRACK_SYN_RECV
comma
DECL|enumerator|TCP_CONNTRACK_FIN_WAIT
id|TCP_CONNTRACK_FIN_WAIT
comma
DECL|enumerator|TCP_CONNTRACK_TIME_WAIT
id|TCP_CONNTRACK_TIME_WAIT
comma
DECL|enumerator|TCP_CONNTRACK_CLOSE
id|TCP_CONNTRACK_CLOSE
comma
DECL|enumerator|TCP_CONNTRACK_CLOSE_WAIT
id|TCP_CONNTRACK_CLOSE_WAIT
comma
DECL|enumerator|TCP_CONNTRACK_LAST_ACK
id|TCP_CONNTRACK_LAST_ACK
comma
DECL|enumerator|TCP_CONNTRACK_LISTEN
id|TCP_CONNTRACK_LISTEN
comma
DECL|enumerator|TCP_CONNTRACK_MAX
id|TCP_CONNTRACK_MAX
)brace
suffix:semicolon
DECL|struct|ip_ct_tcp
r_struct
id|ip_ct_tcp
(brace
DECL|member|state
r_enum
id|tcp_conntrack
id|state
suffix:semicolon
multiline_comment|/* Poor man&squot;s window tracking: sequence number of valid ACK&n;           handshake completion packet */
DECL|member|handshake_ack
id|u_int32_t
id|handshake_ack
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_TCP_H */
eof
