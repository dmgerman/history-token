macro_line|#ifndef _LINUX_X25_ASY_H
DECL|macro|_LINUX_X25_ASY_H
mdefine_line|#define _LINUX_X25_ASY_H
multiline_comment|/* X.25 asy configuration. */
DECL|macro|SL_NRUNIT
mdefine_line|#define SL_NRUNIT&t;256&t;&t;/* MAX number of X.25 channels;&n;&t;&t;&t;&t;&t;   This can be overridden with&n;&t;&t;&t;&t;&t;   insmod -ox25_asy_maxdev=nnn&t;*/
DECL|macro|SL_MTU
mdefine_line|#define SL_MTU&t;&t;256&t;
multiline_comment|/* X25 async protocol characters. */
DECL|macro|X25_END
mdefine_line|#define X25_END         0x7E&t;&t;/* indicates end of frame&t;*/
DECL|macro|X25_ESC
mdefine_line|#define X25_ESC         0x7D&t;&t;/* indicates byte stuffing&t;*/
DECL|macro|X25_ESCAPE
mdefine_line|#define X25_ESCAPE(x)&t;((x)^0x20)
DECL|macro|X25_UNESCAPE
mdefine_line|#define X25_UNESCAPE(x)&t;((x)^0x20)
DECL|struct|x25_asy
r_struct
id|x25_asy
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* Various fields. */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;&t;*/
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* easy for intr handling&t;*/
multiline_comment|/* These are pointers to the malloc()ed frame buffers. */
DECL|member|rbuff
r_int
r_char
op_star
id|rbuff
suffix:semicolon
multiline_comment|/* receiver buffer&t;&t;*/
DECL|member|rcount
r_int
id|rcount
suffix:semicolon
multiline_comment|/* received chars counter       */
DECL|member|xbuff
r_int
r_char
op_star
id|xbuff
suffix:semicolon
multiline_comment|/* transmitter buffer&t;&t;*/
DECL|member|xhead
r_int
r_char
op_star
id|xhead
suffix:semicolon
multiline_comment|/* pointer to next byte to XMIT */
DECL|member|xleft
r_int
id|xleft
suffix:semicolon
multiline_comment|/* bytes left in XMIT queue     */
multiline_comment|/* X.25 interface statistics. */
DECL|member|rx_packets
r_int
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* inbound frames counter&t;*/
DECL|member|tx_packets
r_int
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* outbound frames counter      */
DECL|member|rx_bytes
r_int
r_int
id|rx_bytes
suffix:semicolon
multiline_comment|/* inbound byte counte&t;&t;*/
DECL|member|tx_bytes
r_int
r_int
id|tx_bytes
suffix:semicolon
multiline_comment|/* outbound byte counter&t;*/
DECL|member|rx_errors
r_int
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* Parity, etc. errors          */
DECL|member|tx_errors
r_int
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* Planned stuff                */
DECL|member|rx_dropped
r_int
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* No memory for skb            */
DECL|member|tx_dropped
r_int
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* When MTU change              */
DECL|member|rx_over_errors
r_int
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* Frame bigger then X.25 buf.  */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* Our mtu (to spot changes!)   */
DECL|member|buffsize
r_int
id|buffsize
suffix:semicolon
multiline_comment|/* Max buffers sizes            */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flag values/ mode etc&t;*/
DECL|macro|SLF_INUSE
mdefine_line|#define SLF_INUSE&t;0&t;&t;/* Channel in use               */
DECL|macro|SLF_ESCAPE
mdefine_line|#define SLF_ESCAPE&t;1               /* ESC received                 */
DECL|macro|SLF_ERROR
mdefine_line|#define SLF_ERROR&t;2               /* Parity, etc. error           */
DECL|macro|SLF_OUTWAIT
mdefine_line|#define SLF_OUTWAIT&t;4&t;&t;/* Waiting for output&t;&t;*/
)brace
suffix:semicolon
DECL|macro|X25_ASY_MAGIC
mdefine_line|#define X25_ASY_MAGIC 0x5303
r_extern
r_int
id|x25_asy_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_X25_ASY.H */
eof
