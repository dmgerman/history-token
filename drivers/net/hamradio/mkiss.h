multiline_comment|/****************************************************************************&n; *&t;Defines for the Multi-KISS driver.&n; ****************************************************************************/
DECL|macro|AX25_MAXDEV
mdefine_line|#define AX25_MAXDEV&t;16&t;&t;/* MAX number of AX25 channels;&n;&t;&t;&t;&t;&t;   This can be overridden with&n;&t;&t;&t;&t;&t;   insmod -oax25_maxdev=nnn&t;*/
DECL|macro|AX_MTU
mdefine_line|#define AX_MTU&t;&t;236&t;
multiline_comment|/* SLIP/KISS protocol characters. */
DECL|macro|END
mdefine_line|#define END             0300&t;&t;/* indicates end of frame&t;*/
DECL|macro|ESC
mdefine_line|#define ESC             0333&t;&t;/* indicates byte stuffing&t;*/
DECL|macro|ESC_END
mdefine_line|#define ESC_END         0334&t;&t;/* ESC ESC_END means END &squot;data&squot;&t;*/
DECL|macro|ESC_ESC
mdefine_line|#define ESC_ESC         0335&t;&t;/* ESC ESC_ESC means ESC &squot;data&squot;&t;*/
DECL|struct|ax_disp
r_struct
id|ax_disp
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
DECL|member|mkiss
r_struct
id|ax_disp
op_star
id|mkiss
suffix:semicolon
multiline_comment|/* mkiss txport if mkiss channel*/
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
multiline_comment|/* SLIP interface statistics. */
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
multiline_comment|/* Frame bigger then SLIP buf.  */
multiline_comment|/* Detailed SLIP statistics. */
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
multiline_comment|/* long req&squot;d: used by set_bit --RR */
DECL|macro|AXF_INUSE
mdefine_line|#define AXF_INUSE&t;0&t;&t;/* Channel in use               */
DECL|macro|AXF_ESCAPE
mdefine_line|#define AXF_ESCAPE&t;1               /* ESC received                 */
DECL|macro|AXF_ERROR
mdefine_line|#define AXF_ERROR&t;2               /* Parity, etc. error           */
DECL|macro|AXF_KEEPTEST
mdefine_line|#define AXF_KEEPTEST&t;3&t;&t;/* Keepalive test flag&t;&t;*/
DECL|macro|AXF_OUTWAIT
mdefine_line|#define AXF_OUTWAIT&t;4&t;&t;/* is outpacket was flag&t;*/
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|crcmode
r_int
id|crcmode
suffix:semicolon
multiline_comment|/* MW: for FlexNet, SMACK etc.  */
DECL|macro|CRC_MODE_NONE
mdefine_line|#define CRC_MODE_NONE   0
DECL|macro|CRC_MODE_FLEX
mdefine_line|#define CRC_MODE_FLEX   1
DECL|macro|CRC_MODE_SMACK
mdefine_line|#define CRC_MODE_SMACK  2
)brace
suffix:semicolon
DECL|macro|AX25_MAGIC
mdefine_line|#define AX25_MAGIC&t;&t;0x5316
DECL|macro|MKISS_DRIVER_MAGIC
mdefine_line|#define MKISS_DRIVER_MAGIC&t;1215
eof
