multiline_comment|/*&n; *&t;Index to functions.&n; */
r_int
id|el1_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|el1_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
suffix:semicolon
r_static
r_int
id|el_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|el_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|el_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|el_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|el_receive
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|el_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|el1_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|el1_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|netdev_ethtool_ops
r_static
r_struct
id|ethtool_ops
id|netdev_ethtool_ops
suffix:semicolon
DECL|macro|EL1_IO_EXTENT
mdefine_line|#define EL1_IO_EXTENT&t;16
macro_line|#ifndef EL_DEBUG
DECL|macro|EL_DEBUG
mdefine_line|#define EL_DEBUG  0&t;/* use 0 for production, 1 for devel., &gt;2 for debug */
macro_line|#endif&t;&t;&t;/* Anything above 5 is wordy death! */
DECL|macro|debug
mdefine_line|#define debug el_debug
DECL|variable|el_debug
r_static
r_int
id|el_debug
op_assign
id|EL_DEBUG
suffix:semicolon
multiline_comment|/*&n; *&t;Board-specific info in dev-&gt;priv.&n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|tx_pkt_start
r_int
id|tx_pkt_start
suffix:semicolon
multiline_comment|/* The length of the current Tx packet. */
DECL|member|collisions
r_int
id|collisions
suffix:semicolon
multiline_comment|/* Tx collisions this packet */
DECL|member|loading
r_int
id|loading
suffix:semicolon
multiline_comment|/* Spot buffer load collisions */
DECL|member|txing
r_int
id|txing
suffix:semicolon
multiline_comment|/* True if card is in TX mode */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Serializing lock */
)brace
suffix:semicolon
"&f;"
DECL|macro|RX_STATUS
mdefine_line|#define RX_STATUS (ioaddr + 0x06)
DECL|macro|RX_CMD
mdefine_line|#define RX_CMD&t;  RX_STATUS
DECL|macro|TX_STATUS
mdefine_line|#define TX_STATUS (ioaddr + 0x07)
DECL|macro|TX_CMD
mdefine_line|#define TX_CMD&t;  TX_STATUS
DECL|macro|GP_LOW
mdefine_line|#define GP_LOW &t;  (ioaddr + 0x08)
DECL|macro|GP_HIGH
mdefine_line|#define GP_HIGH   (ioaddr + 0x09)
DECL|macro|RX_BUF_CLR
mdefine_line|#define RX_BUF_CLR (ioaddr + 0x0A)
DECL|macro|RX_LOW
mdefine_line|#define RX_LOW&t;  (ioaddr + 0x0A)
DECL|macro|RX_HIGH
mdefine_line|#define RX_HIGH   (ioaddr + 0x0B)
DECL|macro|SAPROM
mdefine_line|#define SAPROM&t;  (ioaddr + 0x0C)
DECL|macro|AX_STATUS
mdefine_line|#define AX_STATUS (ioaddr + 0x0E)
DECL|macro|AX_CMD
mdefine_line|#define AX_CMD&t;  AX_STATUS
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT  (ioaddr + 0x0F)
DECL|macro|TX_RDY
mdefine_line|#define TX_RDY 0x08&t;&t;/* In TX_STATUS */
DECL|macro|EL1_DATAPTR
mdefine_line|#define EL1_DATAPTR&t;0x08
DECL|macro|EL1_RXPTR
mdefine_line|#define EL1_RXPTR&t;0x0A
DECL|macro|EL1_SAPROM
mdefine_line|#define EL1_SAPROM&t;0x0C
DECL|macro|EL1_DATAPORT
mdefine_line|#define EL1_DATAPORT &t;0x0f
multiline_comment|/*&n; *&t;Writes to the ax command register.&n; */
DECL|macro|AX_OFF
mdefine_line|#define AX_OFF&t;0x00&t;&t;&t;/* Irq off, buffer access on */
DECL|macro|AX_SYS
mdefine_line|#define AX_SYS  0x40&t;&t;&t;/* Load the buffer */
DECL|macro|AX_XMIT
mdefine_line|#define AX_XMIT 0x44&t;&t;&t;/* Transmit a packet */
DECL|macro|AX_RX
mdefine_line|#define AX_RX&t;0x48&t;&t;&t;/* Receive a packet */
DECL|macro|AX_LOOP
mdefine_line|#define AX_LOOP&t;0x0C&t;&t;&t;/* Loopback mode */
DECL|macro|AX_RESET
mdefine_line|#define AX_RESET 0x80
multiline_comment|/*&n; *&t;Normal receive mode written to RX_STATUS.  We must intr on short packets&n; *&t;to avoid bogus rx lockups.&n; */
DECL|macro|RX_NORM
mdefine_line|#define RX_NORM 0xA8&t;&t;/* 0x68 == all addrs, 0xA8 only to me. */
DECL|macro|RX_PROM
mdefine_line|#define RX_PROM 0x68&t;&t;/* Senior Prom, uhmm promiscuous mode. */
DECL|macro|RX_MULT
mdefine_line|#define RX_MULT 0xE8&t;&t;/* Accept multicast packets. */
DECL|macro|TX_NORM
mdefine_line|#define TX_NORM 0x0A&t;&t;/* Interrupt on everything that might hang the chip */
multiline_comment|/*&n; *&t;TX_STATUS register.&n; */
DECL|macro|TX_COLLISION
mdefine_line|#define TX_COLLISION 0x02
DECL|macro|TX_16COLLISIONS
mdefine_line|#define TX_16COLLISIONS 0x04
DECL|macro|TX_READY
mdefine_line|#define TX_READY 0x08
DECL|macro|RX_RUNT
mdefine_line|#define RX_RUNT 0x08
DECL|macro|RX_MISSED
mdefine_line|#define RX_MISSED 0x01&t;&t;/* Missed a packet due to 3c501 braindamage. */
DECL|macro|RX_GOOD
mdefine_line|#define RX_GOOD&t;0x30&t;&t;/* Good packet 0x20, or simple overflow 0x10. */
eof
