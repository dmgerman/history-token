macro_line|#ifndef _IPT_LOG_H
DECL|macro|_IPT_LOG_H
mdefine_line|#define _IPT_LOG_H
DECL|macro|IPT_LOG_TCPSEQ
mdefine_line|#define IPT_LOG_TCPSEQ&t;&t;0x01&t;/* Log TCP sequence numbers */
DECL|macro|IPT_LOG_TCPOPT
mdefine_line|#define IPT_LOG_TCPOPT&t;&t;0x02&t;/* Log TCP options */
DECL|macro|IPT_LOG_IPOPT
mdefine_line|#define IPT_LOG_IPOPT&t;&t;0x04&t;/* Log IP options */
DECL|macro|IPT_LOG_MASK
mdefine_line|#define IPT_LOG_MASK&t;&t;0x07
DECL|struct|ipt_log_info
r_struct
id|ipt_log_info
(brace
DECL|member|level
r_int
r_char
id|level
suffix:semicolon
DECL|member|logflags
r_int
r_char
id|logflags
suffix:semicolon
DECL|member|prefix
r_char
id|prefix
(braket
l_int|30
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_LOG_H*/
eof
