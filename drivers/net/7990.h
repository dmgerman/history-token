multiline_comment|/* &n; * 7990.h -- LANCE ethernet IC generic routines.&n; * This is an attempt to separate out the bits of various ethernet&n; * drivers that are common because they all use the AMD 7990 LANCE&n; * (Local Area Network Controller for Ethernet) chip.&n; * &n; * Copyright (C) 05/1998 Peter Maydell &lt;pmaydell@chiark.greenend.org.uk&gt;&n; *&n; * Most of this stuff was obtained by looking at other LANCE drivers,&n; * in particular a2065.[ch]. The AMD C-LANCE datasheet was also helpful.&n; */
macro_line|#ifndef _7990_H
DECL|macro|_7990_H
mdefine_line|#define _7990_H
multiline_comment|/* The lance only has two register locations. We communicate mostly via memory. */
DECL|struct|lance_regs
r_struct
id|lance_regs
(brace
DECL|member|rdp
r_int
r_int
id|rdp
suffix:semicolon
multiline_comment|/* Register Data Port */
DECL|member|rap
r_int
r_int
id|rap
suffix:semicolon
multiline_comment|/* Register Address Port */
)brace
suffix:semicolon
multiline_comment|/* Transmit/receive ring definitions.&n; * We allow the specific drivers to override these defaults if they want to.&n; * NB: according to lance.c, increasing the number of buffers is a waste&n; * of space and reduces the chance that an upper layer will be able to&n; * reorder queued Tx packets based on priority. [Clearly there is a minimum&n; * limit too: too small and we drop rx packets and can&squot;t tx at full speed.]&n; * 4+4 seems to be the usual setting; the atarilance driver uses 3 and 5.&n; */
multiline_comment|/* Blast! This won&squot;t work. The problem is that we can&squot;t specify a default&n; * setting because that would cause the lance_init_block struct to be&n; * too long (and overflow the RAM on shared-memory cards like the HP LANCE.&n; */
macro_line|#ifndef LANCE_LOG_TX_BUFFERS
DECL|macro|LANCE_LOG_TX_BUFFERS
mdefine_line|#define LANCE_LOG_TX_BUFFERS 1
DECL|macro|LANCE_LOG_RX_BUFFERS
mdefine_line|#define LANCE_LOG_RX_BUFFERS 3
macro_line|#endif
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE (1&lt;&lt;LANCE_LOG_TX_BUFFERS)
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE (1&lt;&lt;LANCE_LOG_RX_BUFFERS)
DECL|macro|TX_RING_MOD_MASK
mdefine_line|#define TX_RING_MOD_MASK (TX_RING_SIZE - 1)
DECL|macro|RX_RING_MOD_MASK
mdefine_line|#define RX_RING_MOD_MASK (RX_RING_SIZE - 1)
DECL|macro|TX_RING_LEN_BITS
mdefine_line|#define TX_RING_LEN_BITS ((LANCE_LOG_TX_BUFFERS) &lt;&lt; 29)
DECL|macro|RX_RING_LEN_BITS
mdefine_line|#define RX_RING_LEN_BITS ((LANCE_LOG_RX_BUFFERS) &lt;&lt; 29)
DECL|macro|PKT_BUFF_SIZE
mdefine_line|#define PKT_BUFF_SIZE (1544)
DECL|macro|RX_BUFF_SIZE
mdefine_line|#define RX_BUFF_SIZE PKT_BUFF_SIZE
DECL|macro|TX_BUFF_SIZE
mdefine_line|#define TX_BUFF_SIZE PKT_BUFF_SIZE
multiline_comment|/* Each receive buffer is described by a receive message descriptor (RMD) */
DECL|struct|lance_rx_desc
r_struct
id|lance_rx_desc
(brace
DECL|member|rmd0
r_volatile
r_int
r_int
id|rmd0
suffix:semicolon
multiline_comment|/* low address of packet */
DECL|member|rmd1_bits
r_volatile
r_int
r_char
id|rmd1_bits
suffix:semicolon
multiline_comment|/* descriptor bits */
DECL|member|rmd1_hadr
r_volatile
r_int
r_char
id|rmd1_hadr
suffix:semicolon
multiline_comment|/* high address of packet */
DECL|member|length
r_volatile
r_int
id|length
suffix:semicolon
multiline_comment|/* This length is 2s complement (negative)!&n;&t;&t;&t;&t;     * Buffer length&n;&t;&t;&t;&t;     */
DECL|member|mblength
r_volatile
r_int
r_int
id|mblength
suffix:semicolon
multiline_comment|/* Actual number of bytes received */
)brace
suffix:semicolon
multiline_comment|/* Ditto for TMD: */
DECL|struct|lance_tx_desc
r_struct
id|lance_tx_desc
(brace
DECL|member|tmd0
r_volatile
r_int
r_int
id|tmd0
suffix:semicolon
multiline_comment|/* low address of packet */
DECL|member|tmd1_bits
r_volatile
r_int
r_char
id|tmd1_bits
suffix:semicolon
multiline_comment|/* descriptor bits */
DECL|member|tmd1_hadr
r_volatile
r_int
r_char
id|tmd1_hadr
suffix:semicolon
multiline_comment|/* high address of packet */
DECL|member|length
r_volatile
r_int
id|length
suffix:semicolon
multiline_comment|/* Length is 2s complement (negative)! */
DECL|member|misc
r_volatile
r_int
r_int
id|misc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* There are three memory structures accessed by the LANCE:&n; * the initialization block, the receive and transmit descriptor rings,&n; * and the data buffers themselves. In fact we might as well put the&n; * init block,the Tx and Rx rings and the buffers together in memory:&n; */
DECL|struct|lance_init_block
r_struct
id|lance_init_block
(brace
DECL|member|mode
r_volatile
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* Pre-set mode (reg. 15) */
DECL|member|phys_addr
r_volatile
r_int
r_char
id|phys_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Physical ethernet address */
DECL|member|filter
r_volatile
r_int
id|filter
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Multicast filter (64 bits) */
multiline_comment|/* Receive and transmit ring base, along with extra bits. */
DECL|member|rx_ptr
r_volatile
r_int
r_int
id|rx_ptr
suffix:semicolon
multiline_comment|/* receive descriptor addr */
DECL|member|rx_len
r_volatile
r_int
r_int
id|rx_len
suffix:semicolon
multiline_comment|/* receive len and high addr */
DECL|member|tx_ptr
r_volatile
r_int
r_int
id|tx_ptr
suffix:semicolon
multiline_comment|/* transmit descriptor addr */
DECL|member|tx_len
r_volatile
r_int
r_int
id|tx_len
suffix:semicolon
multiline_comment|/* transmit len and high addr */
multiline_comment|/* The Tx and Rx ring entries must be aligned on 8-byte boundaries. &n;         * This will be true if this whole struct is 8-byte aligned.&n;         */
DECL|member|btx_ring
r_volatile
r_struct
id|lance_tx_desc
id|btx_ring
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|brx_ring
r_volatile
r_struct
id|lance_rx_desc
id|brx_ring
(braket
id|RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_buf
r_volatile
r_char
id|tx_buf
(braket
id|TX_RING_SIZE
)braket
(braket
id|TX_BUFF_SIZE
)braket
suffix:semicolon
DECL|member|rx_buf
r_volatile
r_char
id|rx_buf
(braket
id|RX_RING_SIZE
)braket
(braket
id|RX_BUFF_SIZE
)braket
suffix:semicolon
multiline_comment|/* we use this just to make the struct big enough that we can move its startaddr&n;         * in order to force alignment to an eight byte boundary.&n;         */
)brace
suffix:semicolon
multiline_comment|/* This is where we keep all the stuff the driver needs to know about.&n; * I&squot;m definitely unhappy about the mechanism for allowing specific&n; * drivers to add things...&n; */
DECL|struct|lance_private
r_struct
id|lance_private
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|ll
r_volatile
r_struct
id|lance_regs
op_star
id|ll
suffix:semicolon
DECL|member|init_block
r_volatile
r_struct
id|lance_init_block
op_star
id|init_block
suffix:semicolon
multiline_comment|/* CPU address of RAM */
DECL|member|lance_init_block
r_volatile
r_struct
id|lance_init_block
op_star
id|lance_init_block
suffix:semicolon
multiline_comment|/* LANCE address of RAM */
DECL|member|rx_new
DECL|member|tx_new
r_int
id|rx_new
comma
id|tx_new
suffix:semicolon
DECL|member|rx_old
DECL|member|tx_old
r_int
id|rx_old
comma
id|tx_old
suffix:semicolon
DECL|member|lance_log_rx_bufs
DECL|member|lance_log_tx_bufs
r_int
id|lance_log_rx_bufs
comma
id|lance_log_tx_bufs
suffix:semicolon
DECL|member|rx_ring_mod_mask
DECL|member|tx_ring_mod_mask
r_int
id|rx_ring_mod_mask
comma
id|tx_ring_mod_mask
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|tpe
r_int
id|tpe
suffix:semicolon
multiline_comment|/* TPE is selected */
DECL|member|auto_select
r_int
id|auto_select
suffix:semicolon
multiline_comment|/* cable-selection is by carrier */
DECL|member|busmaster_regval
r_int
r_int
id|busmaster_regval
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ to register */
multiline_comment|/* This is because the HP LANCE is disgusting and you have to check &n;         * a DIO-specific register every time you read/write the LANCE regs :-&lt;&n;         * [could we get away with making these some sort of macro?]&n;         */
DECL|member|writerap
r_void
(paren
op_star
id|writerap
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|writerdp
r_void
(paren
op_star
id|writerdp
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|readrdp
r_int
r_int
(paren
op_star
id|readrdp
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|devlock
id|spinlock_t
id|devlock
suffix:semicolon
DECL|member|tx_full
r_char
id|tx_full
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *              Am7990 Control and Status Registers&n; */
DECL|macro|LE_CSR0
mdefine_line|#define LE_CSR0         0x0000          /* LANCE Controller Status */
DECL|macro|LE_CSR1
mdefine_line|#define LE_CSR1         0x0001          /* IADR[15:0] (bit0==0 ie word aligned) */
DECL|macro|LE_CSR2
mdefine_line|#define LE_CSR2         0x0002          /* IADR[23:16] (high bits reserved) */
DECL|macro|LE_CSR3
mdefine_line|#define LE_CSR3         0x0003          /* Misc */
multiline_comment|/*&n; *&t;&t;Bit definitions for CSR0 (LANCE Controller Status)&n; */
DECL|macro|LE_C0_ERR
mdefine_line|#define LE_C0_ERR&t;0x8000&t;&t;/* Error = BABL | CERR | MISS | MERR */
DECL|macro|LE_C0_BABL
mdefine_line|#define LE_C0_BABL&t;0x4000&t;&t;/* Babble: Transmitted too many bits */
DECL|macro|LE_C0_CERR
mdefine_line|#define LE_C0_CERR&t;0x2000&t;&t;/* No Heartbeat (10BASE-T) */
DECL|macro|LE_C0_MISS
mdefine_line|#define LE_C0_MISS&t;0x1000&t;&t;/* Missed Frame (no rx buffer to put it in) */
DECL|macro|LE_C0_MERR
mdefine_line|#define LE_C0_MERR&t;0x0800&t;&t;/* Memory Error */
DECL|macro|LE_C0_RINT
mdefine_line|#define LE_C0_RINT&t;0x0400&t;&t;/* Receive Interrupt */
DECL|macro|LE_C0_TINT
mdefine_line|#define LE_C0_TINT&t;0x0200&t;&t;/* Transmit Interrupt */
DECL|macro|LE_C0_IDON
mdefine_line|#define LE_C0_IDON&t;0x0100&t;&t;/* Initialization Done */
DECL|macro|LE_C0_INTR
mdefine_line|#define LE_C0_INTR&t;0x0080&t;&t;/* Interrupt Flag &n;                                         = BABL | MISS | MERR | RINT | TINT | IDON */
DECL|macro|LE_C0_INEA
mdefine_line|#define LE_C0_INEA&t;0x0040&t;&t;/* Interrupt Enable */
DECL|macro|LE_C0_RXON
mdefine_line|#define LE_C0_RXON&t;0x0020&t;&t;/* Receive On */
DECL|macro|LE_C0_TXON
mdefine_line|#define LE_C0_TXON&t;0x0010&t;&t;/* Transmit On */
DECL|macro|LE_C0_TDMD
mdefine_line|#define LE_C0_TDMD&t;0x0008&t;&t;/* Transmit Demand */
DECL|macro|LE_C0_STOP
mdefine_line|#define LE_C0_STOP&t;0x0004&t;&t;/* Stop */
DECL|macro|LE_C0_STRT
mdefine_line|#define LE_C0_STRT&t;0x0002&t;&t;/* Start */
DECL|macro|LE_C0_INIT
mdefine_line|#define LE_C0_INIT&t;0x0001&t;&t;/* Initialize */
multiline_comment|/*&n; *&t;&t;Bit definitions for CSR3&n; */
DECL|macro|LE_C3_BSWP
mdefine_line|#define LE_C3_BSWP&t;0x0004&t;&t;/* Byte Swap&n;&t;&t;&t;&t;&t;   (on for big endian byte order) */
DECL|macro|LE_C3_ACON
mdefine_line|#define LE_C3_ACON&t;0x0002&t;&t;/* ALE Control&n;&t;&t;&t;&t;&t;   (on for active low ALE) */
DECL|macro|LE_C3_BCON
mdefine_line|#define LE_C3_BCON&t;0x0001&t;&t;/* Byte Control */
multiline_comment|/*&n; *&t;&t;Mode Flags&n; */
DECL|macro|LE_MO_PROM
mdefine_line|#define LE_MO_PROM&t;0x8000&t;&t;/* Promiscuous Mode */
multiline_comment|/* these next ones 0x4000 -- 0x0080 are not available on the LANCE 7990,&n; * but they are in NetBSD&squot;s am7990.h, presumably for backwards-compatible chips&n; */
DECL|macro|LE_MO_DRCVBC
mdefine_line|#define LE_MO_DRCVBC  0x4000          /* disable receive broadcast */
DECL|macro|LE_MO_DRCVPA
mdefine_line|#define LE_MO_DRCVPA  0x2000          /* disable physical address detection */
DECL|macro|LE_MO_DLNKTST
mdefine_line|#define LE_MO_DLNKTST 0x1000          /* disable link status */
DECL|macro|LE_MO_DAPC
mdefine_line|#define LE_MO_DAPC    0x0800          /* disable automatic polarity correction */
DECL|macro|LE_MO_MENDECL
mdefine_line|#define LE_MO_MENDECL 0x0400          /* MENDEC loopback mode */
DECL|macro|LE_MO_LRTTSEL
mdefine_line|#define LE_MO_LRTTSEL 0x0200          /* lower RX threshold / TX mode selection */
DECL|macro|LE_MO_PSEL1
mdefine_line|#define LE_MO_PSEL1   0x0100          /* port selection bit1 */
DECL|macro|LE_MO_PSEL0
mdefine_line|#define LE_MO_PSEL0   0x0080          /* port selection bit0 */
multiline_comment|/* and this one is from the C-LANCE data sheet... */
DECL|macro|LE_MO_EMBA
mdefine_line|#define LE_MO_EMBA      0x0080          /* Enable Modified Backoff Algorithm &n;                                           (C-LANCE, not original LANCE) */
DECL|macro|LE_MO_INTL
mdefine_line|#define LE_MO_INTL&t;0x0040&t;&t;/* Internal Loopback */
DECL|macro|LE_MO_DRTY
mdefine_line|#define LE_MO_DRTY&t;0x0020&t;&t;/* Disable Retry */
DECL|macro|LE_MO_FCOLL
mdefine_line|#define LE_MO_FCOLL&t;0x0010&t;&t;/* Force Collision */
DECL|macro|LE_MO_DXMTFCS
mdefine_line|#define LE_MO_DXMTFCS&t;0x0008&t;&t;/* Disable Transmit CRC */
DECL|macro|LE_MO_LOOP
mdefine_line|#define LE_MO_LOOP&t;0x0004&t;&t;/* Loopback Enable */
DECL|macro|LE_MO_DTX
mdefine_line|#define LE_MO_DTX&t;0x0002&t;&t;/* Disable Transmitter */
DECL|macro|LE_MO_DRX
mdefine_line|#define LE_MO_DRX&t;0x0001&t;&t;/* Disable Receiver */
multiline_comment|/*&n; *&t;&t;Receive Flags&n; */
DECL|macro|LE_R1_OWN
mdefine_line|#define LE_R1_OWN&t;0x80&t;&t;/* LANCE owns the descriptor */
DECL|macro|LE_R1_ERR
mdefine_line|#define LE_R1_ERR&t;0x40&t;&t;/* Error */
DECL|macro|LE_R1_FRA
mdefine_line|#define LE_R1_FRA&t;0x20&t;&t;/* Framing Error */
DECL|macro|LE_R1_OFL
mdefine_line|#define LE_R1_OFL&t;0x10&t;&t;/* Overflow Error */
DECL|macro|LE_R1_CRC
mdefine_line|#define LE_R1_CRC&t;0x08&t;&t;/* CRC Error */
DECL|macro|LE_R1_BUF
mdefine_line|#define LE_R1_BUF&t;0x04&t;&t;/* Buffer Error */
DECL|macro|LE_R1_SOP
mdefine_line|#define LE_R1_SOP&t;0x02&t;&t;/* Start of Packet */
DECL|macro|LE_R1_EOP
mdefine_line|#define LE_R1_EOP&t;0x01&t;&t;/* End of Packet */
DECL|macro|LE_R1_POK
mdefine_line|#define LE_R1_POK       0x03&t;&t;/* Packet is complete: SOP + EOP */
multiline_comment|/*&n; *&t;&t;Transmit Flags&n; */
DECL|macro|LE_T1_OWN
mdefine_line|#define LE_T1_OWN&t;0x80&t;&t;/* LANCE owns the descriptor */
DECL|macro|LE_T1_ERR
mdefine_line|#define LE_T1_ERR&t;0x40&t;&t;/* Error */
DECL|macro|LE_T1_RES
mdefine_line|#define LE_T1_RES&t;0x20&t;&t;/* Reserved, LANCE writes this with a zero */
DECL|macro|LE_T1_EMORE
mdefine_line|#define LE_T1_EMORE&t;0x10&t;&t;/* More than one retry needed */
DECL|macro|LE_T1_EONE
mdefine_line|#define LE_T1_EONE&t;0x08&t;&t;/* One retry needed */
DECL|macro|LE_T1_EDEF
mdefine_line|#define LE_T1_EDEF&t;0x04&t;&t;/* Deferred */
DECL|macro|LE_T1_SOP
mdefine_line|#define LE_T1_SOP&t;0x02&t;&t;/* Start of Packet */
DECL|macro|LE_T1_EOP
mdefine_line|#define LE_T1_EOP&t;0x01&t;&t;/* End of Packet */
DECL|macro|LE_T1_POK
mdefine_line|#define LE_T1_POK&t;0x03&t;&t;/* Packet is complete: SOP + EOP */
multiline_comment|/*&n; *&t;&t;Error Flags&n; */
DECL|macro|LE_T3_BUF
mdefine_line|#define LE_T3_BUF &t;0x8000&t;&t;/* Buffer Error */
DECL|macro|LE_T3_UFL
mdefine_line|#define LE_T3_UFL &t;0x4000&t;&t;/* Underflow Error */
DECL|macro|LE_T3_LCOL
mdefine_line|#define LE_T3_LCOL &t;0x1000&t;&t;/* Late Collision */
DECL|macro|LE_T3_CLOS
mdefine_line|#define LE_T3_CLOS &t;0x0800&t;&t;/* Loss of Carrier */
DECL|macro|LE_T3_RTY
mdefine_line|#define LE_T3_RTY &t;0x0400&t;&t;/* Retry Error */
DECL|macro|LE_T3_TDR
mdefine_line|#define LE_T3_TDR&t;0x03ff&t;&t;/* Time Domain Reflectometry */
multiline_comment|/* Miscellaneous useful macros */
DECL|macro|TX_BUFFS_AVAIL
mdefine_line|#define TX_BUFFS_AVAIL ((lp-&gt;tx_old&lt;=lp-&gt;tx_new)?&bslash;&n;                        lp-&gt;tx_old+lp-&gt;tx_ring_mod_mask-lp-&gt;tx_new:&bslash;&n;                        lp-&gt;tx_old - lp-&gt;tx_new-1)
multiline_comment|/* The LANCE only uses 24 bit addresses. This does the obvious thing. */
DECL|macro|LANCE_ADDR
mdefine_line|#define LANCE_ADDR(x) ((int)(x) &amp; ~0xff000000)
multiline_comment|/* Now the prototypes we export */
r_extern
r_int
id|lance_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|lance_close
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|lance_start_xmit
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
r_extern
r_struct
id|net_device_stats
op_star
id|lance_get_stats
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|lance_set_multicast
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|lance_tx_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* ndef _7990_H */
eof
