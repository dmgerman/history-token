macro_line|#ifndef _IP_CONNTRACK_TCP_H
DECL|macro|_IP_CONNTRACK_TCP_H
mdefine_line|#define _IP_CONNTRACK_TCP_H
multiline_comment|/* TCP tracking. */
DECL|enum|tcp_conntrack
r_enum
id|tcp_conntrack
(brace
DECL|enumerator|TCP_CONNTRACK_NONE
id|TCP_CONNTRACK_NONE
comma
DECL|enumerator|TCP_CONNTRACK_SYN_SENT
id|TCP_CONNTRACK_SYN_SENT
comma
DECL|enumerator|TCP_CONNTRACK_SYN_RECV
id|TCP_CONNTRACK_SYN_RECV
comma
DECL|enumerator|TCP_CONNTRACK_ESTABLISHED
id|TCP_CONNTRACK_ESTABLISHED
comma
DECL|enumerator|TCP_CONNTRACK_FIN_WAIT
id|TCP_CONNTRACK_FIN_WAIT
comma
DECL|enumerator|TCP_CONNTRACK_CLOSE_WAIT
id|TCP_CONNTRACK_CLOSE_WAIT
comma
DECL|enumerator|TCP_CONNTRACK_LAST_ACK
id|TCP_CONNTRACK_LAST_ACK
comma
DECL|enumerator|TCP_CONNTRACK_TIME_WAIT
id|TCP_CONNTRACK_TIME_WAIT
comma
DECL|enumerator|TCP_CONNTRACK_CLOSE
id|TCP_CONNTRACK_CLOSE
comma
DECL|enumerator|TCP_CONNTRACK_LISTEN
id|TCP_CONNTRACK_LISTEN
comma
DECL|enumerator|TCP_CONNTRACK_MAX
id|TCP_CONNTRACK_MAX
comma
DECL|enumerator|TCP_CONNTRACK_IGNORE
id|TCP_CONNTRACK_IGNORE
)brace
suffix:semicolon
multiline_comment|/* Window scaling is advertised by the sender */
DECL|macro|IP_CT_TCP_FLAG_WINDOW_SCALE
mdefine_line|#define IP_CT_TCP_FLAG_WINDOW_SCALE&t;&t;0x01
multiline_comment|/* SACK is permitted by the sender */
DECL|macro|IP_CT_TCP_FLAG_SACK_PERM
mdefine_line|#define IP_CT_TCP_FLAG_SACK_PERM&t;&t;0x02
DECL|struct|ip_ct_tcp_state
r_struct
id|ip_ct_tcp_state
(brace
DECL|member|td_end
id|u_int32_t
id|td_end
suffix:semicolon
multiline_comment|/* max of seq + len */
DECL|member|td_maxend
id|u_int32_t
id|td_maxend
suffix:semicolon
multiline_comment|/* max of ack + max(win, 1) */
DECL|member|td_maxwin
id|u_int32_t
id|td_maxwin
suffix:semicolon
multiline_comment|/* max(win) */
DECL|member|td_scale
id|u_int8_t
id|td_scale
suffix:semicolon
multiline_comment|/* window scale factor */
DECL|member|loose
id|u_int8_t
id|loose
suffix:semicolon
multiline_comment|/* used when connection picked up from the middle */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/* per direction state flags */
)brace
suffix:semicolon
DECL|struct|ip_ct_tcp
r_struct
id|ip_ct_tcp
(brace
DECL|member|seen
r_struct
id|ip_ct_tcp_state
id|seen
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* connection parameters per direction */
DECL|member|state
id|u_int8_t
id|state
suffix:semicolon
multiline_comment|/* state of the connection (enum tcp_conntrack) */
multiline_comment|/* For detecting stale connections */
DECL|member|last_dir
id|u_int8_t
id|last_dir
suffix:semicolon
multiline_comment|/* Direction of the last packet (enum ip_conntrack_dir) */
DECL|member|retrans
id|u_int8_t
id|retrans
suffix:semicolon
multiline_comment|/* Number of retransmitted packets */
DECL|member|last_index
id|u_int8_t
id|last_index
suffix:semicolon
multiline_comment|/* Index of the last packet */
DECL|member|last_seq
id|u_int32_t
id|last_seq
suffix:semicolon
multiline_comment|/* Last sequence number seen in dir */
DECL|member|last_ack
id|u_int32_t
id|last_ack
suffix:semicolon
multiline_comment|/* Last sequence number seen in opposite dir */
DECL|member|last_end
id|u_int32_t
id|last_end
suffix:semicolon
multiline_comment|/* Last seq + len */
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_TCP_H */
eof
