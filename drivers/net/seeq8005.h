multiline_comment|/* &n; * defines, etc for the seeq8005&n; */
multiline_comment|/*&n; * This file is distributed under GPL.&n; *&n; * This style and layout of this file is also copied&n; * from many of the other linux network device drivers.&n; */
multiline_comment|/* The number of low I/O ports used by the ethercard. */
DECL|macro|SEEQ8005_IO_EXTENT
mdefine_line|#define SEEQ8005_IO_EXTENT&t;16
DECL|macro|SEEQ_B
mdefine_line|#define SEEQ_B&t;&t;(ioaddr)
DECL|macro|SEEQ_CMD
mdefine_line|#define&t;SEEQ_CMD&t;(SEEQ_B)&t;&t;/* Write only */
DECL|macro|SEEQ_STATUS
mdefine_line|#define&t;SEEQ_STATUS&t;(SEEQ_B)&t;&t;/* Read only */
DECL|macro|SEEQ_CFG1
mdefine_line|#define SEEQ_CFG1&t;(SEEQ_B + 2)
DECL|macro|SEEQ_CFG2
mdefine_line|#define SEEQ_CFG2&t;(SEEQ_B + 4)
DECL|macro|SEEQ_REA
mdefine_line|#define&t;SEEQ_REA&t;(SEEQ_B + 6)&t;&t;/* Receive End Area Register */
DECL|macro|SEEQ_RPR
mdefine_line|#define SEEQ_RPR&t;(SEEQ_B + 10)&t;&t;/* Receive Pointer Register */
DECL|macro|SEEQ_TPR
mdefine_line|#define&t;SEEQ_TPR&t;(SEEQ_B + 12)&t;&t;/* Transmit Pointer Register */
DECL|macro|SEEQ_DMAAR
mdefine_line|#define&t;SEEQ_DMAAR&t;(SEEQ_B + 14)&t;&t;/* DMA Address Register */
DECL|macro|SEEQ_BUFFER
mdefine_line|#define SEEQ_BUFFER&t;(SEEQ_B + 8)&t;&t;/* Buffer Window Register */
DECL|macro|DEFAULT_TEA
mdefine_line|#define&t;DEFAULT_TEA&t;(0x3f)
DECL|macro|SEEQCMD_DMA_INT_EN
mdefine_line|#define SEEQCMD_DMA_INT_EN&t;(0x0001)&t;/* DMA Interrupt Enable */
DECL|macro|SEEQCMD_RX_INT_EN
mdefine_line|#define SEEQCMD_RX_INT_EN&t;(0x0002)&t;/* Receive Interrupt Enable */
DECL|macro|SEEQCMD_TX_INT_EN
mdefine_line|#define SEEQCMD_TX_INT_EN&t;(0x0004)&t;/* Transmit Interrupt Enable */
DECL|macro|SEEQCMD_WINDOW_INT_EN
mdefine_line|#define SEEQCMD_WINDOW_INT_EN&t;(0x0008)&t;/* What the hell is this for?? */
DECL|macro|SEEQCMD_INT_MASK
mdefine_line|#define SEEQCMD_INT_MASK&t;(0x000f)
DECL|macro|SEEQCMD_DMA_INT_ACK
mdefine_line|#define SEEQCMD_DMA_INT_ACK&t;(0x0010)&t;/* DMA ack */
DECL|macro|SEEQCMD_RX_INT_ACK
mdefine_line|#define SEEQCMD_RX_INT_ACK&t;(0x0020)
DECL|macro|SEEQCMD_TX_INT_ACK
mdefine_line|#define SEEQCMD_TX_INT_ACK&t;(0x0040)
DECL|macro|SEEQCMD_WINDOW_INT_ACK
mdefine_line|#define&t;SEEQCMD_WINDOW_INT_ACK&t;(0x0080)
DECL|macro|SEEQCMD_ACK_ALL
mdefine_line|#define SEEQCMD_ACK_ALL&t;&t;(0x00f0)
DECL|macro|SEEQCMD_SET_DMA_ON
mdefine_line|#define SEEQCMD_SET_DMA_ON&t;(0x0100)&t;/* Enables DMA Request logic */
DECL|macro|SEEQCMD_SET_RX_ON
mdefine_line|#define SEEQCMD_SET_RX_ON&t;(0x0200)&t;/* Enables Packet RX */
DECL|macro|SEEQCMD_SET_TX_ON
mdefine_line|#define SEEQCMD_SET_TX_ON&t;(0x0400)&t;/* Starts TX run */
DECL|macro|SEEQCMD_SET_DMA_OFF
mdefine_line|#define SEEQCMD_SET_DMA_OFF&t;(0x0800)
DECL|macro|SEEQCMD_SET_RX_OFF
mdefine_line|#define SEEQCMD_SET_RX_OFF&t;(0x1000)
DECL|macro|SEEQCMD_SET_TX_OFF
mdefine_line|#define SEEQCMD_SET_TX_OFF&t;(0x2000)
DECL|macro|SEEQCMD_SET_ALL_OFF
mdefine_line|#define SEEQCMD_SET_ALL_OFF&t;(0x3800)&t;/* set all logic off */
DECL|macro|SEEQCMD_FIFO_READ
mdefine_line|#define SEEQCMD_FIFO_READ&t;(0x4000)&t;/* Set FIFO to read mode (read from Buffer) */
DECL|macro|SEEQCMD_FIFO_WRITE
mdefine_line|#define SEEQCMD_FIFO_WRITE&t;(0x8000)&t;/* Set FIFO to write mode */
DECL|macro|SEEQSTAT_DMA_INT_EN
mdefine_line|#define SEEQSTAT_DMA_INT_EN&t;(0x0001)&t;/* Status of interrupt enable */
DECL|macro|SEEQSTAT_RX_INT_EN
mdefine_line|#define SEEQSTAT_RX_INT_EN&t;(0x0002)
DECL|macro|SEEQSTAT_TX_INT_EN
mdefine_line|#define SEEQSTAT_TX_INT_EN&t;(0x0004)
DECL|macro|SEEQSTAT_WINDOW_INT_EN
mdefine_line|#define SEEQSTAT_WINDOW_INT_EN&t;(0x0008)
DECL|macro|SEEQSTAT_DMA_INT
mdefine_line|#define&t;SEEQSTAT_DMA_INT&t;(0x0010)&t;/* Interrupt flagged */
DECL|macro|SEEQSTAT_RX_INT
mdefine_line|#define SEEQSTAT_RX_INT&t;&t;(0x0020)
DECL|macro|SEEQSTAT_TX_INT
mdefine_line|#define SEEQSTAT_TX_INT&t;&t;(0x0040)
DECL|macro|SEEQSTAT_WINDOW_INT
mdefine_line|#define&t;SEEQSTAT_WINDOW_INT&t;(0x0080)
DECL|macro|SEEQSTAT_ANY_INT
mdefine_line|#define SEEQSTAT_ANY_INT&t;(0x00f0)
DECL|macro|SEEQSTAT_DMA_ON
mdefine_line|#define SEEQSTAT_DMA_ON&t;&t;(0x0100)&t;/* DMA logic on */
DECL|macro|SEEQSTAT_RX_ON
mdefine_line|#define SEEQSTAT_RX_ON&t;&t;(0x0200)&t;/* Packet RX on */
DECL|macro|SEEQSTAT_TX_ON
mdefine_line|#define SEEQSTAT_TX_ON&t;&t;(0x0400)&t;/* TX running */
DECL|macro|SEEQSTAT_FIFO_FULL
mdefine_line|#define SEEQSTAT_FIFO_FULL&t;(0x2000)
DECL|macro|SEEQSTAT_FIFO_EMPTY
mdefine_line|#define SEEQSTAT_FIFO_EMPTY&t;(0x4000)
DECL|macro|SEEQSTAT_FIFO_DIR
mdefine_line|#define SEEQSTAT_FIFO_DIR&t;(0x8000)&t;/* 1=read, 0=write */
DECL|macro|SEEQCFG1_BUFFER_MASK
mdefine_line|#define SEEQCFG1_BUFFER_MASK&t;(0x000f)&t;/* define what maps into the BUFFER register */
DECL|macro|SEEQCFG1_BUFFER_MAC0
mdefine_line|#define SEEQCFG1_BUFFER_MAC0&t;(0x0000)&t;/* MAC station addresses 0-5 */
DECL|macro|SEEQCFG1_BUFFER_MAC1
mdefine_line|#define SEEQCFG1_BUFFER_MAC1&t;(0x0001)
DECL|macro|SEEQCFG1_BUFFER_MAC2
mdefine_line|#define SEEQCFG1_BUFFER_MAC2&t;(0x0002)
DECL|macro|SEEQCFG1_BUFFER_MAC3
mdefine_line|#define SEEQCFG1_BUFFER_MAC3&t;(0x0003)
DECL|macro|SEEQCFG1_BUFFER_MAC4
mdefine_line|#define SEEQCFG1_BUFFER_MAC4&t;(0x0004)
DECL|macro|SEEQCFG1_BUFFER_MAC5
mdefine_line|#define SEEQCFG1_BUFFER_MAC5&t;(0x0005)
DECL|macro|SEEQCFG1_BUFFER_PROM
mdefine_line|#define SEEQCFG1_BUFFER_PROM&t;(0x0006)&t;/* The Address/CFG PROM */
DECL|macro|SEEQCFG1_BUFFER_TEA
mdefine_line|#define SEEQCFG1_BUFFER_TEA&t;(0x0007)&t;/* Transmit end area */
DECL|macro|SEEQCFG1_BUFFER_BUFFER
mdefine_line|#define SEEQCFG1_BUFFER_BUFFER&t;(0x0008)&t;/* Packet buffer memory */
DECL|macro|SEEQCFG1_BUFFER_INT_VEC
mdefine_line|#define SEEQCFG1_BUFFER_INT_VEC&t;(0x0009)&t;/* Interrupt Vector */
DECL|macro|SEEQCFG1_DMA_INTVL_MASK
mdefine_line|#define SEEQCFG1_DMA_INTVL_MASK&t;(0x0030)
DECL|macro|SEEQCFG1_DMA_CONT
mdefine_line|#define SEEQCFG1_DMA_CONT&t;(0x0000)
DECL|macro|SEEQCFG1_DMA_800ns
mdefine_line|#define SEEQCFG1_DMA_800ns&t;(0x0010)
DECL|macro|SEEQCFG1_DMA_1600ns
mdefine_line|#define SEEQCFG1_DMA_1600ns&t;(0x0020)
DECL|macro|SEEQCFG1_DMA_3200ns
mdefine_line|#define SEEQCFG1_DMA_3200ns&t;(0x0030)
DECL|macro|SEEQCFG1_DMA_LEN_MASK
mdefine_line|#define SEEQCFG1_DMA_LEN_MASK&t;(0x00c0)
DECL|macro|SEEQCFG1_DMA_LEN1
mdefine_line|#define SEEQCFG1_DMA_LEN1&t;(0x0000)
DECL|macro|SEEQCFG1_DMA_LEN2
mdefine_line|#define SEEQCFG1_DMA_LEN2&t;(0x0040)
DECL|macro|SEEQCFG1_DMA_LEN4
mdefine_line|#define SEEQCFG1_DMA_LEN4&t;(0x0080)
DECL|macro|SEEQCFG1_DMA_LEN8
mdefine_line|#define SEEQCFG1_DMA_LEN8&t;(0x00c0)
DECL|macro|SEEQCFG1_MAC_MASK
mdefine_line|#define SEEQCFG1_MAC_MASK&t;(0x3f00)&t;/* Dis/enable bits for MAC addresses */
DECL|macro|SEEQCFG1_MAC0_EN
mdefine_line|#define SEEQCFG1_MAC0_EN&t;(0x0100)
DECL|macro|SEEQCFG1_MAC1_EN
mdefine_line|#define SEEQCFG1_MAC1_EN&t;(0x0200)
DECL|macro|SEEQCFG1_MAC2_EN
mdefine_line|#define SEEQCFG1_MAC2_EN&t;(0x0400)
DECL|macro|SEEQCFG1_MAC3_EN
mdefine_line|#define SEEQCFG1_MAC3_EN&t;(0x0800)
DECL|macro|SEEQCFG1_MAC4_EN
mdefine_line|#define&t;SEEQCFG1_MAC4_EN&t;(0x1000)
DECL|macro|SEEQCFG1_MAC5_EN
mdefine_line|#define SEEQCFG1_MAC5_EN&t;(0x2000)
DECL|macro|SEEQCFG1_MATCH_MASK
mdefine_line|#define&t;SEEQCFG1_MATCH_MASK&t;(0xc000)&t;/* Packet matching logic cfg bits */
DECL|macro|SEEQCFG1_MATCH_SPECIFIC
mdefine_line|#define SEEQCFG1_MATCH_SPECIFIC&t;(0x0000)&t;/* only matching MAC addresses */
DECL|macro|SEEQCFG1_MATCH_BROAD
mdefine_line|#define SEEQCFG1_MATCH_BROAD&t;(0x4000)&t;/* matching and broadcast addresses */
DECL|macro|SEEQCFG1_MATCH_MULTI
mdefine_line|#define SEEQCFG1_MATCH_MULTI&t;(0x8000)&t;/* matching, broadcast and multicast */
DECL|macro|SEEQCFG1_MATCH_ALL
mdefine_line|#define SEEQCFG1_MATCH_ALL&t;(0xc000)&t;/* Promiscuous mode */
DECL|macro|SEEQCFG1_DEFAULT
mdefine_line|#define SEEQCFG1_DEFAULT&t;(SEEQCFG1_BUFFER_BUFFER | SEEQCFG1_MAC0_EN | SEEQCFG1_MATCH_BROAD)
DECL|macro|SEEQCFG2_BYTE_SWAP
mdefine_line|#define SEEQCFG2_BYTE_SWAP&t;(0x0001)&t;/* 0=Intel byte-order */
DECL|macro|SEEQCFG2_AUTO_REA
mdefine_line|#define SEEQCFG2_AUTO_REA&t;(0x0002)&t;/* if set, Receive End Area will be updated when reading from Buffer */
DECL|macro|SEEQCFG2_CRC_ERR_EN
mdefine_line|#define SEEQCFG2_CRC_ERR_EN&t;(0x0008)&t;/* enables receiving of packets with CRC errors */
DECL|macro|SEEQCFG2_DRIBBLE_EN
mdefine_line|#define SEEQCFG2_DRIBBLE_EN&t;(0x0010)&t;/* enables receiving of non-aligned packets */
DECL|macro|SEEQCFG2_SHORT_EN
mdefine_line|#define SEEQCFG2_SHORT_EN&t;(0x0020)&t;/* enables receiving of short packets */
DECL|macro|SEEQCFG2_SLOTSEL
mdefine_line|#define&t;SEEQCFG2_SLOTSEL&t;(0x0040)&t;/* 0= standard IEEE802.3, 1= smaller,faster, non-standard */
DECL|macro|SEEQCFG2_NO_PREAM
mdefine_line|#define SEEQCFG2_NO_PREAM&t;(0x0080)&t;/* 1= user supplies Xmit preamble bytes */
DECL|macro|SEEQCFG2_ADDR_LEN
mdefine_line|#define SEEQCFG2_ADDR_LEN&t;(0x0100)&t;/* 1= 2byte addresses */
DECL|macro|SEEQCFG2_REC_CRC
mdefine_line|#define SEEQCFG2_REC_CRC&t;(0x0200)&t;/* 0= received packets will have CRC stripped from them */
DECL|macro|SEEQCFG2_XMIT_NO_CRC
mdefine_line|#define SEEQCFG2_XMIT_NO_CRC&t;(0x0400)&t;/* don&squot;t xmit CRC with each packet (user supplies it) */
DECL|macro|SEEQCFG2_LOOPBACK
mdefine_line|#define SEEQCFG2_LOOPBACK&t;(0x0800)
DECL|macro|SEEQCFG2_CTRLO
mdefine_line|#define SEEQCFG2_CTRLO&t;&t;(0x1000)
DECL|macro|SEEQCFG2_RESET
mdefine_line|#define SEEQCFG2_RESET&t;&t;(0x8000)&t;/* software Hard-reset bit */
DECL|struct|seeq_pkt_hdr
r_struct
id|seeq_pkt_hdr
(brace
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* address of next packet header */
DECL|member|babble_int
r_int
r_char
id|babble_int
suffix:colon
l_int|1
comma
multiline_comment|/* enable int on &gt;1514 byte packet */
DECL|member|coll_int
id|coll_int
suffix:colon
l_int|1
comma
multiline_comment|/* enable int on collision */
DECL|member|coll_16_int
id|coll_16_int
suffix:colon
l_int|1
comma
multiline_comment|/* enable int on &gt;15 collision */
DECL|member|xmit_int
id|xmit_int
suffix:colon
l_int|1
comma
multiline_comment|/* enable int on success (or xmit with &lt;15 collision) */
DECL|member|unused
id|unused
suffix:colon
l_int|1
comma
DECL|member|data_follows
id|data_follows
suffix:colon
l_int|1
comma
multiline_comment|/* if not set, process this as a header and pointer only */
DECL|member|chain_cont
id|chain_cont
suffix:colon
l_int|1
comma
multiline_comment|/* if set, more headers in chain &t;&t;only cmd bit valid in recv header */
DECL|member|xmit_recv
id|xmit_recv
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if set, a xmit packet, else a receive packet.*/
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SEEQPKTH_BAB_INT_EN
mdefine_line|#define SEEQPKTH_BAB_INT_EN&t;(0x01)&t;&t;/* xmit only */
DECL|macro|SEEQPKTH_COL_INT_EN
mdefine_line|#define SEEQPKTH_COL_INT_EN&t;(0x02)&t;&t;/* xmit only */
DECL|macro|SEEQPKTH_COL16_INT_EN
mdefine_line|#define SEEQPKTH_COL16_INT_EN&t;(0x04)&t;&t;/* xmit only */
DECL|macro|SEEQPKTH_XMIT_INT_EN
mdefine_line|#define SEEQPKTH_XMIT_INT_EN&t;(0x08)&t;&t;/* xmit only */
DECL|macro|SEEQPKTH_DATA_FOLLOWS
mdefine_line|#define SEEQPKTH_DATA_FOLLOWS&t;(0x20)&t;&t;/* supposedly in xmit only */
DECL|macro|SEEQPKTH_CHAIN
mdefine_line|#define SEEQPKTH_CHAIN&t;&t;(0x40)&t;&t;/* more headers follow */
DECL|macro|SEEQPKTH_XMIT
mdefine_line|#define SEEQPKTH_XMIT&t;&t;(0x80)
DECL|macro|SEEQPKTS_BABBLE
mdefine_line|#define SEEQPKTS_BABBLE&t;&t;(0x0100)&t;/* xmit only */
DECL|macro|SEEQPKTS_OVERSIZE
mdefine_line|#define SEEQPKTS_OVERSIZE&t;(0x0100)&t;/* recv only */
DECL|macro|SEEQPKTS_COLLISION
mdefine_line|#define SEEQPKTS_COLLISION&t;(0x0200)&t;/* xmit only */
DECL|macro|SEEQPKTS_CRC_ERR
mdefine_line|#define SEEQPKTS_CRC_ERR&t;(0x0200)&t;/* recv only */
DECL|macro|SEEQPKTS_COLL16
mdefine_line|#define SEEQPKTS_COLL16&t;&t;(0x0400)&t;/* xmit only */
DECL|macro|SEEQPKTS_DRIB
mdefine_line|#define SEEQPKTS_DRIB&t;&t;(0x0400)&t;/* recv only */
DECL|macro|SEEQPKTS_SHORT
mdefine_line|#define SEEQPKTS_SHORT&t;&t;(0x0800)&t;/* recv only */
DECL|macro|SEEQPKTS_DONE
mdefine_line|#define SEEQPKTS_DONE&t;&t;(0x8000)
DECL|macro|SEEQPKTS_ANY_ERROR
mdefine_line|#define SEEQPKTS_ANY_ERROR&t;(0x0f00)
eof
