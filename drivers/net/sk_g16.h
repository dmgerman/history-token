multiline_comment|/*-&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Module         : sk_g16.h&n; * Version        : $Revision$  &n; *&n; * Author         : M.Hipp (mhipp@student.uni-tuebingen.de)&n; * changes by     : Patrick J.D. Weichmann&n; *&n; * Date Created   : 94/05/25&n; *&n; * Description    : In here are all necessary definitions of  &n; *                  the am7990 (LANCE) chip used for writing a&n; *                  network device driver which uses this chip &n; *&n; * $Log$&n;-*/
macro_line|#ifndef SK_G16_H
DECL|macro|SK_G16_H
mdefine_line|#define SK_G16_H
multiline_comment|/*&n; * &t;Control and Status Register 0 (CSR0) bit definitions&n; *&n; * (R=Readable) (W=Writeable) (S=Set on write) (C-Clear on write)&n; *&n; */
DECL|macro|CSR0_ERR
mdefine_line|#define CSR0_ERR&t;0x8000&t;/* Error summary (R) */
DECL|macro|CSR0_BABL
mdefine_line|#define CSR0_BABL&t;0x4000&t;/* Babble transmitter timeout error (RC) */
DECL|macro|CSR0_CERR
mdefine_line|#define CSR0_CERR&t;0x2000&t;/* Collision Error (RC) */
DECL|macro|CSR0_MISS
mdefine_line|#define CSR0_MISS&t;0x1000&t;/* Missed packet (RC) */
DECL|macro|CSR0_MERR
mdefine_line|#define CSR0_MERR&t;0x0800&t;/* Memory Error  (RC) */ 
DECL|macro|CSR0_RINT
mdefine_line|#define CSR0_RINT&t;0x0400&t;/* Receiver Interrupt (RC) */
DECL|macro|CSR0_TINT
mdefine_line|#define CSR0_TINT       0x0200&t;/* Transmit Interrupt (RC) */ 
DECL|macro|CSR0_IDON
mdefine_line|#define CSR0_IDON&t;0x0100&t;/* Initialization Done (RC) */
DECL|macro|CSR0_INTR
mdefine_line|#define CSR0_INTR&t;0x0080&t;/* Interrupt Flag (R) */
DECL|macro|CSR0_INEA
mdefine_line|#define CSR0_INEA&t;0x0040&t;/* Interrupt Enable (RW) */
DECL|macro|CSR0_RXON
mdefine_line|#define CSR0_RXON&t;0x0020&t;/* Receiver on (R) */
DECL|macro|CSR0_TXON
mdefine_line|#define CSR0_TXON&t;0x0010  /* Transmitter on (R) */
DECL|macro|CSR0_TDMD
mdefine_line|#define CSR0_TDMD&t;0x0008&t;/* Transmit Demand (RS) */
DECL|macro|CSR0_STOP
mdefine_line|#define CSR0_STOP&t;0x0004 &t;/* Stop (RS) */
DECL|macro|CSR0_STRT
mdefine_line|#define CSR0_STRT&t;0x0002&t;/* Start (RS) */
DECL|macro|CSR0_INIT
mdefine_line|#define CSR0_INIT&t;0x0001&t;/* Initialize (RS) */
DECL|macro|CSR0_CLRALL
mdefine_line|#define CSR0_CLRALL     0x7f00  /* mask for all clearable bits */
multiline_comment|/*&n; *    Control and Status Register 3 (CSR3) bit definitions&n; *&n; */
DECL|macro|CSR3_BSWAP
mdefine_line|#define CSR3_BSWAP&t;0x0004&t;/* Byte Swap (RW) */
DECL|macro|CSR3_ACON
mdefine_line|#define CSR3_ACON&t;0x0002  /* ALE Control (RW) */
DECL|macro|CSR3_BCON
mdefine_line|#define CSR3_BCON&t;0x0001&t;/* Byte Control (RW) */
multiline_comment|/*&n; *&t;Initialization Block Mode operation Bit Definitions.&n; */
DECL|macro|MODE_PROM
mdefine_line|#define MODE_PROM&t;0x8000&t;/* Promiscuous Mode */
DECL|macro|MODE_INTL
mdefine_line|#define MODE_INTL&t;0x0040  /* Internal Loopback */
DECL|macro|MODE_DRTY
mdefine_line|#define MODE_DRTY&t;0x0020  /* Disable Retry */ 
DECL|macro|MODE_COLL
mdefine_line|#define MODE_COLL&t;0x0010&t;/* Force Collision */
DECL|macro|MODE_DTCR
mdefine_line|#define MODE_DTCR&t;0x0008&t;/* Disable Transmit CRC) */
DECL|macro|MODE_LOOP
mdefine_line|#define MODE_LOOP&t;0x0004&t;/* Loopback */
DECL|macro|MODE_DTX
mdefine_line|#define MODE_DTX&t;0x0002&t;/* Disable the Transmitter */ 
DECL|macro|MODE_DRX
mdefine_line|#define MODE_DRX&t;0x0001  /* Disable the Receiver */
DECL|macro|MODE_NORMAL
mdefine_line|#define MODE_NORMAL &t;0x0000  /* Normal operation mode */
multiline_comment|/*&n; * &t;Receive message descriptor status bit definitions.&n; */
DECL|macro|RX_OWN
mdefine_line|#define RX_OWN&t;&t;0x80&t;/* Owner bit 0 = host, 1 = lance */
DECL|macro|RX_ERR
mdefine_line|#define RX_ERR&t;&t;0x40&t;/* Error Summary */
DECL|macro|RX_FRAM
mdefine_line|#define RX_FRAM&t;&t;0x20&t;/* Framing Error */
DECL|macro|RX_OFLO
mdefine_line|#define RX_OFLO&t;&t;0x10&t;/* Overflow Error */
DECL|macro|RX_CRC
mdefine_line|#define RX_CRC&t;&t;0x08&t;/* CRC Error */ 
DECL|macro|RX_BUFF
mdefine_line|#define RX_BUFF&t;&t;0x04&t;/* Buffer Error */
DECL|macro|RX_STP
mdefine_line|#define RX_STP&t;&t;0x02&t;/* Start of Packet */
DECL|macro|RX_ENP
mdefine_line|#define RX_ENP&t;&t;0x01&t;/* End of Packet */
multiline_comment|/*&n; *&t;Transmit message descriptor status bit definitions.&n; */
DECL|macro|TX_OWN
mdefine_line|#define TX_OWN&t;&t;0x80&t;/* Owner bit 0 = host, 1 = lance */
DECL|macro|TX_ERR
mdefine_line|#define TX_ERR&t;&t;0x40    /* Error Summary */
DECL|macro|TX_MORE
mdefine_line|#define TX_MORE&t;&t;0x10&t;/* More the 1 retry needed to Xmit */
DECL|macro|TX_ONE
mdefine_line|#define TX_ONE&t;&t;0x08&t;/* One retry needed to Xmit */
DECL|macro|TX_DEF
mdefine_line|#define TX_DEF&t;&t;0x04&t;/* Deferred */
DECL|macro|TX_STP
mdefine_line|#define TX_STP &t;&t;0x02&t;/* Start of Packet */
DECL|macro|TX_ENP
mdefine_line|#define TX_ENP&t;&t;0x01&t;/* End of Packet */
multiline_comment|/*&n; *      Transmit status (2) (valid if TX_ERR == 1)&n; */
DECL|macro|TX_BUFF
mdefine_line|#define TX_BUFF &t;0x8000  /* Buffering error (no ENP) */
DECL|macro|TX_UFLO
mdefine_line|#define TX_UFLO &t;0x4000  /* Underflow (late memory) */
DECL|macro|TX_LCOL
mdefine_line|#define TX_LCOL &t;0x1000  /* Late collision */
DECL|macro|TX_LCAR
mdefine_line|#define TX_LCAR &t;0x0400  /* Loss of Carrier */
DECL|macro|TX_RTRY
mdefine_line|#define TX_RTRY &t;0x0200  /* Failed after 16 retransmissions  */
DECL|macro|TX_TDR
mdefine_line|#define TX_TDR          0x003f  /* Time-domain-reflectometer-value */
multiline_comment|/* &n; * Structures used for Communication with the LANCE &n; */
multiline_comment|/* LANCE Initialize Block */
DECL|struct|init_block
r_struct
id|init_block
(brace
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* Mode Register */
DECL|member|paddr
r_int
r_char
id|paddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Physical Address (MAC) */
DECL|member|laddr
r_int
r_char
id|laddr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Logical Filter Address (not used) */
DECL|member|rdrp
r_int
r_int
id|rdrp
suffix:semicolon
multiline_comment|/* Receive Descriptor Ring pointer */
DECL|member|tdrp
r_int
r_int
id|tdrp
suffix:semicolon
multiline_comment|/* Transmit Descriptor Ring pointer */
)brace
suffix:semicolon
multiline_comment|/* Receive Message Descriptor Entry */
DECL|struct|rmd
r_struct
id|rmd
(brace
r_union
(brace
DECL|member|buffer
r_int
r_int
id|buffer
suffix:semicolon
multiline_comment|/* Address of buffer */
r_struct
(brace
DECL|member|unused
r_int
r_char
id|unused
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|status
r_int
r_volatile
r_char
id|status
suffix:semicolon
multiline_comment|/* Status Bits */
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|blen
r_volatile
r_int
id|blen
suffix:semicolon
multiline_comment|/* Buffer Length (two&squot;s complement) */
DECL|member|mlen
r_int
r_int
id|mlen
suffix:semicolon
multiline_comment|/* Message Byte Count */
)brace
suffix:semicolon
multiline_comment|/* Transmit Message Descriptor Entry */
DECL|struct|tmd
r_struct
id|tmd
(brace
r_union
(brace
DECL|member|buffer
r_int
r_int
id|buffer
suffix:semicolon
multiline_comment|/* Address of buffer */
r_struct
(brace
DECL|member|unused
r_int
r_char
id|unused
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|status
r_int
r_volatile
r_char
id|status
suffix:semicolon
multiline_comment|/* Status Bits */
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|blen
r_int
r_int
id|blen
suffix:semicolon
multiline_comment|/* Buffer Length (two&squot;s complement) */
DECL|member|status2
r_int
r_volatile
r_int
id|status2
suffix:semicolon
multiline_comment|/* Error Status Bits */
)brace
suffix:semicolon
macro_line|#endif /* End of SK_G16_H */
eof
