multiline_comment|/*&n; * Racal-Interlan ni5010 Ethernet definitions&n; *&n; * This is an extension to the Linux operating system, and is covered by the&n; * same Gnu Public License that covers that work.&n; *&n; * copyrights (c) 1996 by Jan-Pascal van Best (jvbest@wi.leidenuniv.nl)&n; *&n; * I have done a look in the following sources:&n; *   crynwr-packet-driver by Russ Nelson&n; */
DECL|macro|NI5010_BUFSIZE
mdefine_line|#define NI5010_BUFSIZE&t;2048&t;/* number of bytes in a buffer */
DECL|macro|NI5010_MAGICVAL0
mdefine_line|#define NI5010_MAGICVAL0 0x00  /* magic-values for ni5010 card */
DECL|macro|NI5010_MAGICVAL1
mdefine_line|#define NI5010_MAGICVAL1 0x55
DECL|macro|NI5010_MAGICVAL2
mdefine_line|#define NI5010_MAGICVAL2 0xAA
DECL|macro|SA_ADDR0
mdefine_line|#define SA_ADDR0 0x02
DECL|macro|SA_ADDR1
mdefine_line|#define SA_ADDR1 0x07
DECL|macro|SA_ADDR2
mdefine_line|#define SA_ADDR2 0x01
multiline_comment|/* The number of low I/O ports used by the ni5010 ethercard. */
DECL|macro|NI5010_IO_EXTENT
mdefine_line|#define NI5010_IO_EXTENT       32
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) if (NI5010_DEBUG) printk x
DECL|macro|PRINTK2
mdefine_line|#define PRINTK2(x) if (NI5010_DEBUG&gt;=2) printk x
DECL|macro|PRINTK3
mdefine_line|#define PRINTK3(x) if (NI5010_DEBUG&gt;=3) printk x
multiline_comment|/* The various IE command registers */
DECL|macro|EDLC_XSTAT
mdefine_line|#define EDLC_XSTAT&t;(ioaddr + 0x00)&t;/* EDLC transmit csr */
DECL|macro|EDLC_XCLR
mdefine_line|#define EDLC_XCLR&t;(ioaddr + 0x00)&t;/* EDLC transmit &quot;Clear IRQ&quot; */
DECL|macro|EDLC_XMASK
mdefine_line|#define EDLC_XMASK&t;(ioaddr + 0x01)&t;/* EDLC transmit &quot;IRQ Masks&quot; */
DECL|macro|EDLC_RSTAT
mdefine_line|#define EDLC_RSTAT&t;(ioaddr + 0x02)&t;/* EDLC receive csr */
DECL|macro|EDLC_RCLR
mdefine_line|#define EDLC_RCLR&t;(ioaddr + 0x02)&t;/* EDLC receive &quot;Clear IRQ&quot; */
DECL|macro|EDLC_RMASK
mdefine_line|#define EDLC_RMASK&t;(ioaddr + 0x03)&t;/* EDLC receive &quot;IRQ Masks&quot; */
DECL|macro|EDLC_XMODE
mdefine_line|#define EDLC_XMODE&t;(ioaddr + 0x04)&t;/* EDLC transmit Mode */
DECL|macro|EDLC_RMODE
mdefine_line|#define EDLC_RMODE&t;(ioaddr + 0x05)&t;/* EDLC receive Mode */
DECL|macro|EDLC_RESET
mdefine_line|#define EDLC_RESET&t;(ioaddr + 0x06)&t;/* EDLC RESET register */
DECL|macro|EDLC_TDR1
mdefine_line|#define EDLC_TDR1&t;(ioaddr + 0x07)&t;/* &quot;Time Domain Reflectometry&quot; reg1 */
DECL|macro|EDLC_ADDR
mdefine_line|#define EDLC_ADDR&t;(ioaddr + 0x08)&t;/* EDLC station address, 6 bytes */
multiline_comment|/* 0x0E doesn&squot;t exist for r/w */
DECL|macro|EDLC_TDR2
mdefine_line|#define EDLC_TDR2&t;(ioaddr + 0x0f)&t;/* &quot;Time Domain Reflectometry&quot; reg2 */
DECL|macro|IE_GP
mdefine_line|#define IE_GP&t;&t;(ioaddr + 0x10)&t;/* GP pointer (word register) */
multiline_comment|/* 0x11 is 2nd byte of GP Pointer */
DECL|macro|IE_RCNT
mdefine_line|#define IE_RCNT&t;&t;(ioaddr + 0x10)&t;/* Count of bytes in rcv&squot;d packet */
multiline_comment|/* 0x11 is 2nd byte of &quot;Byte Count&quot; */
DECL|macro|IE_MMODE
mdefine_line|#define IE_MMODE&t;(ioaddr + 0x12)&t;/* Memory Mode register */
DECL|macro|IE_DMA_RST
mdefine_line|#define IE_DMA_RST&t;(ioaddr + 0x13)&t;/* IE DMA Reset.  write only */
DECL|macro|IE_ISTAT
mdefine_line|#define IE_ISTAT&t;(ioaddr + 0x13)&t;/* IE Interrupt Status.  read only */
DECL|macro|IE_RBUF
mdefine_line|#define IE_RBUF&t;&t;(ioaddr + 0x14)&t;/* IE Receive Buffer port */
DECL|macro|IE_XBUF
mdefine_line|#define IE_XBUF&t;&t;(ioaddr + 0x15)&t;/* IE Transmit Buffer port */
DECL|macro|IE_SAPROM
mdefine_line|#define IE_SAPROM&t;(ioaddr + 0x16)&t;/* window on station addr prom */
DECL|macro|IE_RESET
mdefine_line|#define IE_RESET&t;(ioaddr + 0x17)&t;/* any write causes Board Reset */
multiline_comment|/* bits in EDLC_XSTAT, interrupt clear on write, status when read */
DECL|macro|XS_TPOK
mdefine_line|#define XS_TPOK&t;&t;0x80&t;/* transmit packet successful */
DECL|macro|XS_CS
mdefine_line|#define XS_CS&t;&t;0x40&t;/* carrier sense */
DECL|macro|XS_RCVD
mdefine_line|#define XS_RCVD&t;&t;0x20&t;/* transmitted packet received */
DECL|macro|XS_SHORT
mdefine_line|#define XS_SHORT&t;0x10&t;/* transmission media is shorted */
DECL|macro|XS_UFLW
mdefine_line|#define XS_UFLW&t;&t;0x08&t;/* underflow.  iff failed board */
DECL|macro|XS_COLL
mdefine_line|#define XS_COLL&t;&t;0x04&t;/* collision occurred */
DECL|macro|XS_16COLL
mdefine_line|#define XS_16COLL&t;0x02&t;/* 16th collision occurred */
DECL|macro|XS_PERR
mdefine_line|#define XS_PERR&t;&t;0x01&t;/* parity error */
DECL|macro|XS_CLR_UFLW
mdefine_line|#define XS_CLR_UFLW&t;0x08&t;/* clear underflow */
DECL|macro|XS_CLR_COLL
mdefine_line|#define XS_CLR_COLL&t;0x04&t;/* clear collision */
DECL|macro|XS_CLR_16COLL
mdefine_line|#define XS_CLR_16COLL&t;0x02&t;/* clear 16th collision */
DECL|macro|XS_CLR_PERR
mdefine_line|#define XS_CLR_PERR&t;0x01&t;/* clear parity error */
multiline_comment|/* bits in EDLC_XMASK, mask/enable transmit interrupts.  register is r/w */
DECL|macro|XM_TPOK
mdefine_line|#define XM_TPOK&t;&t;0x80&t;/* =1 to enable Xmt Pkt OK interrupts */
DECL|macro|XM_RCVD
mdefine_line|#define XM_RCVD&t;&t;0x20&t;/* =1 to enable Xmt Pkt Rcvd ints */
DECL|macro|XM_UFLW
mdefine_line|#define XM_UFLW&t;&t;0x08&t;/* =1 to enable Xmt Underflow ints */
DECL|macro|XM_COLL
mdefine_line|#define XM_COLL&t;&t;0x04&t;/* =1 to enable Xmt Collision ints */
DECL|macro|XM_COLL16
mdefine_line|#define XM_COLL16&t;0x02&t;/* =1 to enable Xmt 16th Coll ints */
DECL|macro|XM_PERR
mdefine_line|#define XM_PERR&t;&t;0x01&t;/* =1 to enable Xmt Parity Error ints */
multiline_comment|/* note: always clear this bit */
DECL|macro|XM_ALL
mdefine_line|#define XM_ALL&t;&t;(XM_TPOK | XM_RCVD | XM_UFLW | XM_COLL | XM_COLL16)
multiline_comment|/* bits in EDLC_RSTAT, interrupt clear on write, status when read */
DECL|macro|RS_PKT_OK
mdefine_line|#define RS_PKT_OK&t;0x80&t;/* received good packet */
DECL|macro|RS_RST_PKT
mdefine_line|#define RS_RST_PKT&t;0x10&t;/* RESET packet received */
DECL|macro|RS_RUNT
mdefine_line|#define RS_RUNT&t;&t;0x08&t;/* Runt Pkt rcvd.  Len &lt; 64 Bytes */
DECL|macro|RS_ALIGN
mdefine_line|#define RS_ALIGN&t;0x04&t;/* Alignment error. not 8 bit aligned */
DECL|macro|RS_CRC_ERR
mdefine_line|#define RS_CRC_ERR&t;0x02&t;/* Bad CRC on rcvd pkt */
DECL|macro|RS_OFLW
mdefine_line|#define RS_OFLW&t;&t;0x01&t;/* overflow for rcv FIFO */
DECL|macro|RS_VALID_BITS
mdefine_line|#define RS_VALID_BITS&t;( RS_PKT_OK | RS_RST_PKT | RS_RUNT | RS_ALIGN | RS_CRC_ERR | RS_OFLW )
multiline_comment|/* all valid RSTAT bits */
DECL|macro|RS_CLR_PKT_OK
mdefine_line|#define RS_CLR_PKT_OK&t;0x80&t;/* clear rcvd packet interrupt */
DECL|macro|RS_CLR_RST_PKT
mdefine_line|#define RS_CLR_RST_PKT&t;0x10&t;/* clear RESET packet received */
DECL|macro|RS_CLR_RUNT
mdefine_line|#define RS_CLR_RUNT&t;0x08&t;/* clear Runt Pckt received */
DECL|macro|RS_CLR_ALIGN
mdefine_line|#define RS_CLR_ALIGN&t;0x04&t;/* clear Alignment error */
DECL|macro|RS_CLR_CRC_ERR
mdefine_line|#define RS_CLR_CRC_ERR&t;0x02&t;/* clear CRC error */
DECL|macro|RS_CLR_OFLW
mdefine_line|#define RS_CLR_OFLW&t;0x01&t;/* clear rcv FIFO Overflow */
multiline_comment|/* bits in EDLC_RMASK, mask/enable receive interrupts.  register is r/w */
DECL|macro|RM_PKT_OK
mdefine_line|#define RM_PKT_OK&t;0x80&t;/* =1 to enable rcvd good packet ints */
DECL|macro|RM_RST_PKT
mdefine_line|#define RM_RST_PKT&t;0x10&t;/* =1 to enable RESET packet ints */
DECL|macro|RM_RUNT
mdefine_line|#define RM_RUNT&t;&t;0x08&t;/* =1 to enable Runt Pkt rcvd ints */
DECL|macro|RM_ALIGN
mdefine_line|#define RM_ALIGN&t;0x04&t;/* =1 to enable Alignment error ints */
DECL|macro|RM_CRC_ERR
mdefine_line|#define RM_CRC_ERR&t;0x02&t;/* =1 to enable Bad CRC error ints */
DECL|macro|RM_OFLW
mdefine_line|#define RM_OFLW&t;&t;0x01&t;/* =1 to enable overflow error ints */
multiline_comment|/* bits in EDLC_RMODE, set Receive Packet mode.  register is r/w */
DECL|macro|RMD_TEST
mdefine_line|#define RMD_TEST&t;0x80&t;/* =1 for Chip testing.  normally 0 */
DECL|macro|RMD_ADD_SIZ
mdefine_line|#define RMD_ADD_SIZ&t;0x10&t;/* =1 5-byte addr match.  normally 0 */
DECL|macro|RMD_EN_RUNT
mdefine_line|#define RMD_EN_RUNT&t;0x08&t;/* =1 enable runt rcv.  normally 0 */
DECL|macro|RMD_EN_RST
mdefine_line|#define RMD_EN_RST&t;0x04&t;/* =1 to rcv RESET pkt.  normally 0 */
DECL|macro|RMD_PROMISC
mdefine_line|#define RMD_PROMISC&t;0x03&t;/* receive *all* packets.  unusual */
DECL|macro|RMD_MULTICAST
mdefine_line|#define RMD_MULTICAST&t;0x02&t;/* receive multicasts too.  unusual */
DECL|macro|RMD_BROADCAST
mdefine_line|#define RMD_BROADCAST&t;0x01&t;/* receive broadcasts &amp; normal. usual */
DECL|macro|RMD_NO_PACKETS
mdefine_line|#define RMD_NO_PACKETS&t;0x00&t;/* don&squot;t receive any packets. unusual */
multiline_comment|/* bits in EDLC_XMODE, set Transmit Packet mode.  register is r/w */
DECL|macro|XMD_COLL_CNT
mdefine_line|#define XMD_COLL_CNT&t;0xf0&t;/* coll&squot;s since success.  read-only */
DECL|macro|XMD_IG_PAR
mdefine_line|#define XMD_IG_PAR&t;0x08&t;/* =1 to ignore parity.  ALWAYS set */
DECL|macro|XMD_T_MODE
mdefine_line|#define XMD_T_MODE&t;0x04&t;/* =1 to power xcvr. ALWAYS set this */
DECL|macro|XMD_LBC
mdefine_line|#define XMD_LBC&t;&t;0x02&t;/* =1 for loopbakc.  normally set */
DECL|macro|XMD_DIS_C
mdefine_line|#define XMD_DIS_C&t;0x01&t;/* =1 disables contention. normally 0 */
multiline_comment|/* bits in EDLC_RESET, write only */
DECL|macro|RS_RESET
mdefine_line|#define RS_RESET&t;0x80&t;/* =1 to hold EDLC in reset state */
multiline_comment|/* bits in IE_MMODE, write only */
DECL|macro|MM_EN_DMA
mdefine_line|#define MM_EN_DMA&t;0x80&t;/* =1 begin DMA xfer, Cplt clrs it */
DECL|macro|MM_EN_RCV
mdefine_line|#define MM_EN_RCV&t;0x40&t;/* =1 allows Pkt rcv.  clr&squot;d by rcv */
DECL|macro|MM_EN_XMT
mdefine_line|#define MM_EN_XMT&t;0x20&t;/* =1 begin Xmt pkt.  Cplt clrs it */
DECL|macro|MM_BUS_PAGE
mdefine_line|#define MM_BUS_PAGE&t;0x18&t;/* =00 ALWAYS.  Used when MUX=1 */
DECL|macro|MM_NET_PAGE
mdefine_line|#define MM_NET_PAGE&t;0x06&t;/* =00 ALWAYS.  Used when MUX=0 */
DECL|macro|MM_MUX
mdefine_line|#define MM_MUX&t;&t;0x01&t;/* =1 means Rcv Buff on system bus */
multiline_comment|/* =0 means Xmt Buff on system bus */
multiline_comment|/* bits in IE_ISTAT, read only */
DECL|macro|IS_TDIAG
mdefine_line|#define IS_TDIAG&t;0x80&t;/* =1 if Diagnostic problem */
DECL|macro|IS_EN_RCV
mdefine_line|#define IS_EN_RCV&t;0x20&t;/* =1 until frame is rcv&squot;d cplt */
DECL|macro|IS_EN_XMT
mdefine_line|#define IS_EN_XMT&t;0x10&t;/* =1 until frame is xmt&squot;d cplt */
DECL|macro|IS_EN_DMA
mdefine_line|#define IS_EN_DMA&t;0x08&t;/* =1 until DMA is cplt or aborted */
DECL|macro|IS_DMA_INT
mdefine_line|#define IS_DMA_INT&t;0x04&t;/* =0 iff DMA done interrupt. */
DECL|macro|IS_R_INT
mdefine_line|#define IS_R_INT&t;0x02&t;/* =0 iff unmasked Rcv interrupt */
DECL|macro|IS_X_INT
mdefine_line|#define IS_X_INT&t;0x01&t;/* =0 iff unmasked Xmt interrupt */
eof
