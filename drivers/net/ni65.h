multiline_comment|/* am7990 (lance) definitions&n; * &n; * This is an extension to the Linux operating system, and is covered by&n; * same Gnu Public License that covers that work.&n; * &n; * Michael Hipp&n; * email: mhipp@student.uni-tuebingen.de&n; *&n; * sources: (mail me or ask archie if you need them) &n; *    crynwr-packet-driver&n; */
multiline_comment|/*&n; * &t;Control and Status Register 0 (CSR0) bit definitions&n; * (R=Readable) (W=Writeable) (S=Set on write) (C-Clear on write)&n; *&n; */
DECL|macro|CSR0_ERR
mdefine_line|#define CSR0_ERR&t;0x8000&t;/* Error summary (R) */
DECL|macro|CSR0_BABL
mdefine_line|#define CSR0_BABL&t;0x4000&t;/* Babble transmitter timeout error (RC) */
DECL|macro|CSR0_CERR
mdefine_line|#define CSR0_CERR&t;0x2000&t;/* Collision Error (RC) */
DECL|macro|CSR0_MISS
mdefine_line|#define CSR0_MISS&t;0x1000&t;/* Missed packet (RC) */
DECL|macro|CSR0_MERR
mdefine_line|#define CSR0_MERR&t;0x0800&t;/* Memory Error (RC) */ 
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
mdefine_line|#define CSR0_CLRALL    0x7f00  /* mask for all clearable bits */
multiline_comment|/*&n; *&t;Initialization Block  Mode operation Bit Definitions.&n; */
DECL|macro|M_PROM
mdefine_line|#define M_PROM&t;&t;0x8000&t;/* Promiscuous Mode */
DECL|macro|M_INTL
mdefine_line|#define M_INTL&t;&t;0x0040  /* Internal Loopback */
DECL|macro|M_DRTY
mdefine_line|#define M_DRTY&t;&t;0x0020  /* Disable Retry */ 
DECL|macro|M_COLL
mdefine_line|#define M_COLL&t;&t;0x0010&t;/* Force Collision */
DECL|macro|M_DTCR
mdefine_line|#define M_DTCR&t;&t;0x0008&t;/* Disable Transmit CRC) */
DECL|macro|M_LOOP
mdefine_line|#define M_LOOP&t;&t;0x0004&t;/* Loopback */
DECL|macro|M_DTX
mdefine_line|#define M_DTX&t;&t;0x0002&t;/* Disable the Transmitter */ 
DECL|macro|M_DRX
mdefine_line|#define M_DRX&t;&t;0x0001  /* Disable the Receiver */
multiline_comment|/*&n; * &t;Receive message descriptor bit definitions.&n; */
DECL|macro|RCV_OWN
mdefine_line|#define RCV_OWN&t;&t;0x80&t;/* owner bit 0 = host, 1 = lance */
DECL|macro|RCV_ERR
mdefine_line|#define RCV_ERR&t;&t;0x40&t;/* Error Summary */
DECL|macro|RCV_FRAM
mdefine_line|#define RCV_FRAM&t;0x20&t;/* Framing Error */
DECL|macro|RCV_OFLO
mdefine_line|#define RCV_OFLO&t;0x10&t;/* Overflow Error */
DECL|macro|RCV_CRC
mdefine_line|#define RCV_CRC&t;&t;0x08&t;/* CRC Error */ 
DECL|macro|RCV_BUF_ERR
mdefine_line|#define RCV_BUF_ERR&t;0x04&t;/* Buffer Error */
DECL|macro|RCV_START
mdefine_line|#define RCV_START&t;0x02&t;/* Start of Packet */
DECL|macro|RCV_END
mdefine_line|#define RCV_END&t;&t;0x01&t;/* End of Packet */
multiline_comment|/*&n; *&t;Transmit  message descriptor bit definitions.&n; */
DECL|macro|XMIT_OWN
mdefine_line|#define XMIT_OWN&t;0x80&t;/* owner bit 0 = host, 1 = lance */
DECL|macro|XMIT_ERR
mdefine_line|#define XMIT_ERR&t;0x40    /* Error Summary */
DECL|macro|XMIT_RETRY
mdefine_line|#define XMIT_RETRY&t;0x10&t;/* more the 1 retry needed to Xmit */
DECL|macro|XMIT_1_RETRY
mdefine_line|#define XMIT_1_RETRY&t;0x08&t;/* one retry needed to Xmit */
DECL|macro|XMIT_DEF
mdefine_line|#define XMIT_DEF&t;0x04&t;/* Deferred */
DECL|macro|XMIT_START
mdefine_line|#define XMIT_START&t;0x02&t;/* Start of Packet */
DECL|macro|XMIT_END
mdefine_line|#define XMIT_END&t;0x01&t;/* End of Packet */
multiline_comment|/*&n; * transmit status (2) (valid if XMIT_ERR == 1)&n; */
DECL|macro|XMIT_TDRMASK
mdefine_line|#define XMIT_TDRMASK    0x03ff  /* time-domain-reflectometer-value */
DECL|macro|XMIT_RTRY
mdefine_line|#define XMIT_RTRY &t;0x0400  /* Failed after 16 retransmissions  */
DECL|macro|XMIT_LCAR
mdefine_line|#define XMIT_LCAR &t;0x0800  /* Loss of Carrier */
DECL|macro|XMIT_LCOL
mdefine_line|#define XMIT_LCOL &t;0x1000  /* Late collision */
DECL|macro|XMIT_RESERV
mdefine_line|#define XMIT_RESERV &t;0x2000  /* Reserved */
DECL|macro|XMIT_UFLO
mdefine_line|#define XMIT_UFLO &t;0x4000  /* Underflow (late memory) */
DECL|macro|XMIT_BUFF
mdefine_line|#define XMIT_BUFF &t;0x8000  /* Buffering error (no ENP) */
DECL|struct|init_block
r_struct
id|init_block
(brace
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|eaddr
r_int
r_char
id|eaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|filter
r_int
r_char
id|filter
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* bit 29-31: number of rmd&squot;s (power of 2) */
DECL|member|rrp
id|u32
id|rrp
suffix:semicolon
multiline_comment|/* receive ring pointer (align 8) */
multiline_comment|/* bit 29-31: number of tmd&squot;s (power of 2) */
DECL|member|trp
id|u32
id|trp
suffix:semicolon
multiline_comment|/* transmit ring pointer (align 8) */
)brace
suffix:semicolon
DECL|struct|rmd
r_struct
id|rmd
multiline_comment|/* Receive Message Descriptor */
(brace
r_union
(brace
DECL|member|buffer
r_volatile
id|u32
id|buffer
suffix:semicolon
r_struct
(brace
DECL|member|dummy
r_volatile
r_int
r_char
id|dummy
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|status
r_volatile
r_int
r_char
id|status
suffix:semicolon
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
DECL|member|mlen
r_volatile
r_int
r_int
id|mlen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tmd
r_struct
id|tmd
(brace
r_union
(brace
DECL|member|buffer
r_volatile
id|u32
id|buffer
suffix:semicolon
r_struct
(brace
DECL|member|dummy
r_volatile
r_int
r_char
id|dummy
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|status
r_volatile
r_int
r_char
id|status
suffix:semicolon
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
r_int
id|blen
suffix:semicolon
DECL|member|status2
r_volatile
r_int
r_int
id|status2
suffix:semicolon
)brace
suffix:semicolon
eof
