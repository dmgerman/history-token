macro_line|#ifndef __NET_SPX_H
DECL|macro|__NET_SPX_H
mdefine_line|#define __NET_SPX_H
macro_line|#include &lt;net/ipx.h&gt;
DECL|struct|spxhdr
r_struct
id|spxhdr
DECL|member|cctl
(brace
id|__u8
id|cctl
suffix:semicolon
DECL|member|dtype
id|__u8
id|dtype
suffix:semicolon
DECL|macro|SPX_DTYPE_ECONN
mdefine_line|#define SPX_DTYPE_ECONN&t;0xFE&t;/* Finished */
DECL|macro|SPX_DTYPE_ECACK
mdefine_line|#define SPX_DTYPE_ECACK&t;0xFF&t;/* Ok */
DECL|member|sconn
id|__u16
id|sconn
suffix:semicolon
multiline_comment|/* Connection ID */
DECL|member|dconn
id|__u16
id|dconn
suffix:semicolon
multiline_comment|/* Connection ID */
DECL|member|sequence
id|__u16
id|sequence
suffix:semicolon
DECL|member|ackseq
id|__u16
id|ackseq
suffix:semicolon
DECL|member|allocseq
id|__u16
id|allocseq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipxspxhdr
r_struct
id|ipxspxhdr
DECL|member|ipx
(brace
r_struct
id|ipxhdr
id|ipx
suffix:semicolon
DECL|member|spx
r_struct
id|spxhdr
id|spx
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPX_SYS_PKT_LEN
mdefine_line|#define&t;SPX_SYS_PKT_LEN&t;(sizeof(struct ipxspxhdr))
macro_line|#ifdef __KERNEL__
DECL|struct|spx_opt
r_struct
id|spx_opt
DECL|member|state
(brace
r_int
id|state
suffix:semicolon
DECL|member|sndbuf
r_int
id|sndbuf
suffix:semicolon
DECL|member|retries
r_int
id|retries
suffix:semicolon
multiline_comment|/* Number of WD retries */
DECL|member|retransmits
r_int
id|retransmits
suffix:semicolon
multiline_comment|/* Number of retransmits */
DECL|member|max_retries
r_int
id|max_retries
suffix:semicolon
DECL|member|wd_interval
r_int
id|wd_interval
suffix:semicolon
DECL|member|owner
r_void
op_star
id|owner
suffix:semicolon
DECL|member|dest_connid
id|__u16
id|dest_connid
suffix:semicolon
multiline_comment|/* Net order */
DECL|member|source_connid
id|__u16
id|source_connid
suffix:semicolon
multiline_comment|/* Net order */
DECL|member|sequence
id|__u16
id|sequence
suffix:semicolon
multiline_comment|/* Host order - our current pkt # */
DECL|member|alloc
id|__u16
id|alloc
suffix:semicolon
multiline_comment|/* Host order - max seq we can rcv now */
DECL|member|rmt_ack
id|__u16
id|rmt_ack
suffix:semicolon
multiline_comment|/* Host order - last pkt ACKd by remote */
DECL|member|rmt_seq
id|__u16
id|rmt_seq
suffix:semicolon
DECL|member|acknowledge
id|__u16
id|acknowledge
suffix:semicolon
DECL|member|rmt_alloc
id|__u16
id|rmt_alloc
suffix:semicolon
multiline_comment|/* Host order - max seq remote can handle now */
DECL|member|dest_addr
id|ipx_address
id|dest_addr
suffix:semicolon
DECL|member|source_addr
id|ipx_address
id|source_addr
suffix:semicolon
DECL|member|watchdog
r_struct
id|timer_list
id|watchdog
suffix:semicolon
multiline_comment|/* Idle watch */
DECL|member|retransmit
r_struct
id|timer_list
id|retransmit
suffix:semicolon
multiline_comment|/* Retransmit timer */
DECL|member|rcv_queue
r_struct
id|sk_buff_head
id|rcv_queue
suffix:semicolon
DECL|member|transmit_queue
r_struct
id|sk_buff_head
id|transmit_queue
suffix:semicolon
DECL|member|retransmit_queue
r_struct
id|sk_buff_head
id|retransmit_queue
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Packet connectino control defines */
DECL|macro|CCTL_SPXII_XHD
mdefine_line|#define CCTL_SPXII_XHD  0x01    /* SPX2 extended header */
DECL|macro|CCTL_SPX_UNKNOWN
mdefine_line|#define CCTL_SPX_UNKNOWN 0x02   /* Unknown (unused ??) */
DECL|macro|CCTL_SPXII_NEG
mdefine_line|#define CCTL_SPXII_NEG  0x04    /* Negotiate size */
DECL|macro|CCTL_SPXII
mdefine_line|#define CCTL_SPXII      0x08    /* Set for SPX2 */
DECL|macro|CCTL_EOM
mdefine_line|#define CCTL_EOM        0x10    /* End of message marker */
DECL|macro|CCTL_URG
mdefine_line|#define CCTL_URG        0x20    /* Urgent marker in SPP (not used in SPX?) */
DECL|macro|CCTL_ACK
mdefine_line|#define CCTL_ACK        0x40    /* Send me an ACK */
DECL|macro|CCTL_CTL
mdefine_line|#define CCTL_CTL        0x80    /* Control message */
DECL|macro|CCTL_SYS
mdefine_line|#define CCTL_SYS        CCTL_CTL        /* Spec uses CCTL_SYS */
multiline_comment|/* Connection state defines */
DECL|macro|SPX_CLOSED
mdefine_line|#define SPX_CLOSED&t;7
DECL|macro|SPX_CONNECTING
mdefine_line|#define&t;SPX_CONNECTING&t;8
DECL|macro|SPX_CONNECTED
mdefine_line|#define SPX_CONNECTED&t;9
multiline_comment|/* Packet transmit types - Internal */
DECL|macro|DATA
mdefine_line|#define DATA&t;0&t;/* Data */
DECL|macro|ACK
mdefine_line|#define ACK&t;1&t;/* Data ACK */
DECL|macro|WDACK
mdefine_line|#define WDACK&t;2&t;/* WD ACK */
DECL|macro|CONACK
mdefine_line|#define CONACK&t;3&t;/* Connection Request ACK */
DECL|macro|CONREQ
mdefine_line|#define&t;CONREQ&t;4&t;/* Connection Request */
DECL|macro|WDREQ
mdefine_line|#define WDREQ&t;5&t;/* WD Request */
DECL|macro|DISCON
mdefine_line|#define&t;DISCON&t;6&t;/* Informed Disconnect */
DECL|macro|DISACK
mdefine_line|#define&t;DISACK&t;7&t;/* Informed Disconnect ACK */
DECL|macro|RETRAN
mdefine_line|#define RETRAN&t;8&t;/* Int. Retransmit of packet */
DECL|macro|TQUEUE
mdefine_line|#define TQUEUE&t;9&t;/* Int. Transmit of a queued packet */
multiline_comment|/*&n; * These are good canidates for IOcontrol calls&n; */
multiline_comment|/* Watchdog defines */
DECL|macro|VERIFY_TIMEOUT
mdefine_line|#define VERIFY_TIMEOUT  3 * HZ
DECL|macro|ABORT_TIMEOUT
mdefine_line|#define ABORT_TIMEOUT   30 * HZ
multiline_comment|/* Packet retransmit defines */
DECL|macro|RETRY_COUNT
mdefine_line|#define RETRY_COUNT     10
DECL|macro|RETRY_TIME
mdefine_line|#define RETRY_TIME      1 * HZ
DECL|macro|MAX_RETRY_DELAY
mdefine_line|#define MAX_RETRY_DELAY 5 * HZ
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* def __NET_SPX_H */
eof
