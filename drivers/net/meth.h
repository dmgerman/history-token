multiline_comment|/*&n; * snull.h -- definitions for the network module&n; *&n; * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet&n; * Copyright (C) 2001 O&squot;Reilly &amp; Associates&n; *&n; * The source code in this file can be freely used, adapted,&n; * and redistributed in source or binary form, so long as an&n; * acknowledgment appears in derived source files.  The citation&n; * should list that the code comes from the book &quot;Linux Device&n; * Drivers&quot; by Alessandro Rubini and Jonathan Corbet, published&n; * by O&squot;Reilly &amp; Associates.   No warranty is attached;&n; * we cannot take responsibility for errors or fitness for use.&n; */
multiline_comment|/* version dependencies have been confined to a separate file */
multiline_comment|/* Tunable parameters */
DECL|macro|TX_RING_ENTRIES
mdefine_line|#define TX_RING_ENTRIES 64&t;/* 64-512?*/
DECL|macro|RX_RING_ENTRIES
mdefine_line|#define RX_RING_ENTRIES 16 /* Do not change */
multiline_comment|/* Internal constants */
DECL|macro|TX_RING_BUFFER_SIZE
mdefine_line|#define TX_RING_BUFFER_SIZE&t;(TX_RING_ENTRIES*sizeof(tx_packet))
DECL|macro|RX_BUFFER_SIZE
mdefine_line|#define RX_BUFFER_SIZE 1546 /* ethenet packet size */
DECL|macro|METH_RX_BUFF_SIZE
mdefine_line|#define METH_RX_BUFF_SIZE 4096
DECL|macro|METH_RX_HEAD
mdefine_line|#define METH_RX_HEAD 34 /* status + 3 quad garbage-fill + 2 byte zero-pad */
DECL|macro|RX_BUFFER_OFFSET
mdefine_line|#define RX_BUFFER_OFFSET (sizeof(rx_status_vector)+2) /* staus vector + 2 bytes of padding */
DECL|macro|RX_BUCKET_SIZE
mdefine_line|#define RX_BUCKET_SIZE 256
DECL|macro|BIT
macro_line|#undef BIT
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;(1UL &lt;&lt; (x))
multiline_comment|/* For more detailed explanations of what each field menas,&n;   see Nick&squot;s great comments to #defines below (or docs, if&n;   you are lucky enough toget hold of them :)*/
multiline_comment|/* tx status vector is written over tx command header upon&n;   dma completion. */
DECL|struct|tx_status_vector
r_typedef
r_struct
id|tx_status_vector
(brace
DECL|member|sent
id|u64
id|sent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always set to 1...*/
DECL|member|pad0
id|u64
id|pad0
suffix:colon
l_int|34
suffix:semicolon
multiline_comment|/* always set to 0 */
DECL|member|flags
id|u64
id|flags
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/*I&squot;m too lazy to specify each one separately at the moment*/
DECL|member|col_retry_cnt
id|u64
id|col_retry_cnt
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/*collision retry count*/
DECL|member|len
id|u64
id|len
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/*Transmit length in bytes*/
DECL|typedef|tx_status_vector
)brace
id|tx_status_vector
suffix:semicolon
multiline_comment|/*&n; * Each packet is 128 bytes long.&n; * It consists of header, 0-3 concatination&n; * buffer pointers and up to 120 data bytes.&n; */
DECL|struct|tx_packet_hdr
r_typedef
r_struct
id|tx_packet_hdr
(brace
DECL|member|pad1
id|u64
id|pad1
suffix:colon
l_int|36
suffix:semicolon
multiline_comment|/*should be filled with 0 */
DECL|member|cat_ptr3_valid
id|u64
id|cat_ptr3_valid
suffix:colon
l_int|1
comma
multiline_comment|/*Concatination pointer valid flags*/
DECL|member|cat_ptr2_valid
id|cat_ptr2_valid
suffix:colon
l_int|1
comma
DECL|member|cat_ptr1_valid
id|cat_ptr1_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tx_int_flag
id|u64
id|tx_int_flag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*Generate TX intrrupt when packet has been sent*/
DECL|member|term_dma_flag
id|u64
id|term_dma_flag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*Terminate transmit DMA on transmit abort conditions*/
DECL|member|data_offset
id|u64
id|data_offset
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/*Starting byte offset in ring data block*/
DECL|member|data_len
id|u64
id|data_len
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/*Length of valid data in bytes-1*/
DECL|typedef|tx_packet_hdr
)brace
id|tx_packet_hdr
suffix:semicolon
DECL|union|tx_cat_ptr
r_typedef
r_union
id|tx_cat_ptr
(brace
r_struct
(brace
DECL|member|pad2
id|u64
id|pad2
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* should be 0 */
DECL|member|len
id|u64
id|len
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/*length of buffer data - 1*/
DECL|member|start_addr
id|u64
id|start_addr
suffix:colon
l_int|29
suffix:semicolon
multiline_comment|/*Physical starting address*/
DECL|member|pad1
id|u64
id|pad1
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* should be zero */
DECL|member|form
)brace
id|form
suffix:semicolon
DECL|member|raw
id|u64
id|raw
suffix:semicolon
DECL|typedef|tx_cat_ptr
)brace
id|tx_cat_ptr
suffix:semicolon
DECL|struct|tx_packet
r_typedef
r_struct
id|tx_packet
(brace
r_union
(brace
DECL|member|header
id|tx_packet_hdr
id|header
suffix:semicolon
DECL|member|res
id|tx_status_vector
id|res
suffix:semicolon
DECL|member|raw
id|u64
id|raw
suffix:semicolon
DECL|member|header
)brace
id|header
suffix:semicolon
r_union
(brace
DECL|member|cat_buf
id|tx_cat_ptr
id|cat_buf
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dt
r_char
id|dt
(braket
l_int|120
)braket
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|typedef|tx_packet
)brace
id|tx_packet
suffix:semicolon
DECL|union|rx_status_vector
r_typedef
r_union
id|rx_status_vector
(brace
r_volatile
r_struct
(brace
DECL|member|pad1
id|u64
id|pad1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*fill it with ones*/
DECL|member|pad2
id|u64
id|pad2
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/*fill with 0*/
DECL|member|ip_chk_sum
id|u64
id|ip_chk_sum
suffix:colon
l_int|16
suffix:semicolon
DECL|member|seq_num
id|u64
id|seq_num
suffix:colon
l_int|5
suffix:semicolon
DECL|member|mac_addr_match
id|u64
id|mac_addr_match
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mcast_addr_match
id|u64
id|mcast_addr_match
suffix:colon
l_int|1
suffix:semicolon
DECL|member|carrier_event_seen
id|u64
id|carrier_event_seen
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bad_packet
id|u64
id|bad_packet
suffix:colon
l_int|1
suffix:semicolon
DECL|member|long_event_seen
id|u64
id|long_event_seen
suffix:colon
l_int|1
suffix:semicolon
DECL|member|invalid_preamble
id|u64
id|invalid_preamble
suffix:colon
l_int|1
suffix:semicolon
DECL|member|broadcast
id|u64
id|broadcast
suffix:colon
l_int|1
suffix:semicolon
DECL|member|multicast
id|u64
id|multicast
suffix:colon
l_int|1
suffix:semicolon
DECL|member|crc_error
id|u64
id|crc_error
suffix:colon
l_int|1
suffix:semicolon
DECL|member|huh
id|u64
id|huh
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*???*/
DECL|member|rx_code_violation
id|u64
id|rx_code_violation
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rx_len
id|u64
id|rx_len
suffix:colon
l_int|16
suffix:semicolon
DECL|member|parsed
)brace
id|parsed
suffix:semicolon
DECL|member|raw
r_volatile
id|u64
id|raw
suffix:semicolon
DECL|typedef|rx_status_vector
)brace
id|rx_status_vector
suffix:semicolon
DECL|struct|rx_packet
r_typedef
r_struct
id|rx_packet
(brace
DECL|member|status
id|rx_status_vector
id|status
suffix:semicolon
DECL|member|pad
id|u64
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* For whatever reason, there needs to be 4 double-word offset */
DECL|member|pad2
id|u16
id|pad2
suffix:semicolon
DECL|member|buf
r_char
id|buf
(braket
id|METH_RX_BUFF_SIZE
op_minus
r_sizeof
(paren
id|rx_status_vector
)paren
op_minus
l_int|3
op_star
r_sizeof
(paren
id|u64
)paren
op_minus
r_sizeof
(paren
id|u16
)paren
)braket
suffix:semicolon
multiline_comment|/* data */
DECL|typedef|rx_packet
)brace
id|rx_packet
suffix:semicolon
DECL|macro|TX_INFO_RPTR
mdefine_line|#define TX_INFO_RPTR    0x00FF0000
DECL|macro|TX_INFO_WPTR
mdefine_line|#define TX_INFO_WPTR    0x000000FF
multiline_comment|/* Bits in METH_MAC */
DECL|macro|SGI_MAC_RESET
mdefine_line|#define SGI_MAC_RESET&t;&t;BIT(0)&t;/* 0: MAC110 active in run mode, 1: Global reset signal to MAC110 core is active */
DECL|macro|METH_PHY_FDX
mdefine_line|#define METH_PHY_FDX&t;&t;BIT(1) /* 0: Disable full duplex, 1: Enable full duplex */
DECL|macro|METH_PHY_LOOP
mdefine_line|#define METH_PHY_LOOP&t;BIT(2) /* 0: Normal operation, follows 10/100mbit and M10T/MII select, 1: loops internal MII bus */
multiline_comment|/*    selects ignored */
DECL|macro|METH_100MBIT
mdefine_line|#define METH_100MBIT&t;&t;BIT(3) /* 0: 10meg mode, 1: 100meg mode */
DECL|macro|METH_PHY_MII
mdefine_line|#define METH_PHY_MII&t;&t;BIT(4) /* 0: MII selected, 1: SIA selected */
multiline_comment|/*   Note: when loopback is set this bit becomes collision control.  Setting this bit will */
multiline_comment|/*         cause a collision to be reported. */
multiline_comment|/* Bits 5 and 6 are used to determine the the Destination address filter mode */
DECL|macro|METH_ACCEPT_MY
mdefine_line|#define METH_ACCEPT_MY 0&t;&t;&t;/* 00: Accept PHY address only */
DECL|macro|METH_ACCEPT_MCAST
mdefine_line|#define METH_ACCEPT_MCAST 0x20&t;/* 01: Accept physical, broadcast, and multicast filter matches only */
DECL|macro|METH_ACCEPT_AMCAST
mdefine_line|#define METH_ACCEPT_AMCAST 0x40&t;/* 10: Accept physical, broadcast, and all multicast packets */
DECL|macro|METH_PROMISC
mdefine_line|#define METH_PROMISC 0x60&t;&t;/* 11: Promiscious mode */
DECL|macro|METH_PHY_LINK_FAIL
mdefine_line|#define METH_PHY_LINK_FAIL&t;BIT(7) /* 0: Link failure detection disabled, 1: Hardware scans for link failure in PHY */
DECL|macro|METH_MAC_IPG
mdefine_line|#define METH_MAC_IPG&t;0x1ffff00
DECL|macro|METH_DEFAULT_IPG
mdefine_line|#define METH_DEFAULT_IPG ((17&lt;&lt;15) | (11&lt;&lt;22) | (21&lt;&lt;8))
multiline_comment|/* 0x172e5c00 */
multiline_comment|/* 23, 23, 23 */
multiline_comment|/*0x54A9500 */
multiline_comment|/*21,21,21*/
multiline_comment|/* Bits 8 through 14 are used to determine Inter-Packet Gap between &quot;Back to Back&quot; packets */
multiline_comment|/* The gap depends on the clock speed of the link, 80ns per increment for 100baseT, 800ns  */
multiline_comment|/* per increment for 10BaseT */
multiline_comment|/* Bits 15 through 21 are used to determine IPGR1 */
multiline_comment|/* Bits 22 through 28 are used to determine IPGR2 */
DECL|macro|METH_REV_SHIFT
mdefine_line|#define METH_REV_SHIFT 29       /* Bits 29 through 31 are used to determine the revision */
multiline_comment|/* 000: Inital revision */
multiline_comment|/* 001: First revision, Improved TX concatenation */
multiline_comment|/* DMA control bits */
DECL|macro|METH_RX_OFFSET_SHIFT
mdefine_line|#define METH_RX_OFFSET_SHIFT 12 /* Bits 12:14 of DMA control register indicate starting offset of packet data for RX operation */
DECL|macro|METH_RX_DEPTH_SHIFT
mdefine_line|#define METH_RX_DEPTH_SHIFT 4 /* Bits 8:4 define RX fifo depth -- when # of RX fifo entries != depth, interrupt is generted */
DECL|macro|METH_DMA_TX_EN
mdefine_line|#define METH_DMA_TX_EN BIT(1) /* enable TX DMA */
DECL|macro|METH_DMA_TX_INT_EN
mdefine_line|#define METH_DMA_TX_INT_EN BIT(0) /* enable TX Buffer Empty interrupt */
DECL|macro|METH_DMA_RX_EN
mdefine_line|#define METH_DMA_RX_EN BIT(15) /* Enable RX */
DECL|macro|METH_DMA_RX_INT_EN
mdefine_line|#define METH_DMA_RX_INT_EN BIT(9) /* Enable interrupt on RX packet */
multiline_comment|/* RX FIFO MCL Info bits */
DECL|macro|METH_RX_FIFO_WPTR
mdefine_line|#define METH_RX_FIFO_WPTR(x)   (((x)&gt;&gt;16)&amp;0xf)
DECL|macro|METH_RX_FIFO_RPTR
mdefine_line|#define METH_RX_FIFO_RPTR(x)   (((x)&gt;&gt;8)&amp;0xf)
DECL|macro|METH_RX_FIFO_DEPTH
mdefine_line|#define METH_RX_FIFO_DEPTH(x)  ((x)&amp;0x1f)
multiline_comment|/* RX status bits */
DECL|macro|METH_RX_ST_VALID
mdefine_line|#define METH_RX_ST_VALID BIT(63)
DECL|macro|METH_RX_ST_RCV_CODE_VIOLATION
mdefine_line|#define METH_RX_ST_RCV_CODE_VIOLATION BIT(16)
DECL|macro|METH_RX_ST_DRBL_NBL
mdefine_line|#define METH_RX_ST_DRBL_NBL BIT(17)
DECL|macro|METH_RX_ST_CRC_ERR
mdefine_line|#define METH_RX_ST_CRC_ERR BIT(18)
DECL|macro|METH_RX_ST_MCAST_PKT
mdefine_line|#define METH_RX_ST_MCAST_PKT BIT(19)
DECL|macro|METH_RX_ST_BCAST_PKT
mdefine_line|#define METH_RX_ST_BCAST_PKT BIT(20)
DECL|macro|METH_RX_ST_INV_PREAMBLE_CTX
mdefine_line|#define METH_RX_ST_INV_PREAMBLE_CTX BIT(21)
DECL|macro|METH_RX_ST_LONG_EVT_SEEN
mdefine_line|#define METH_RX_ST_LONG_EVT_SEEN BIT(22)
DECL|macro|METH_RX_ST_BAD_PACKET
mdefine_line|#define METH_RX_ST_BAD_PACKET BIT(23)
DECL|macro|METH_RX_ST_CARRIER_EVT_SEEN
mdefine_line|#define METH_RX_ST_CARRIER_EVT_SEEN BIT(24)
DECL|macro|METH_RX_ST_MCAST_FILTER_MATCH
mdefine_line|#define METH_RX_ST_MCAST_FILTER_MATCH BIT(25)
DECL|macro|METH_RX_ST_PHYS_ADDR_MATCH
mdefine_line|#define METH_RX_ST_PHYS_ADDR_MATCH BIT(26)
DECL|macro|METH_RX_STATUS_ERRORS
mdefine_line|#define METH_RX_STATUS_ERRORS &bslash;&n;&t;( &bslash;&n;&t;METH_RX_ST_RCV_CODE_VIOLATION| &bslash;&n;&t;METH_RX_ST_CRC_ERR| &bslash;&n;&t;METH_RX_ST_INV_PREAMBLE_CTX| &bslash;&n;&t;METH_RX_ST_LONG_EVT_SEEN| &bslash;&n;&t;METH_RX_ST_BAD_PACKET| &bslash;&n;&t;METH_RX_ST_CARRIER_EVT_SEEN &bslash;&n;&t;)
multiline_comment|/* Bits in METH_INT */
multiline_comment|/* Write _1_ to corresponding bit to clear */
DECL|macro|METH_INT_TX_EMPTY
mdefine_line|#define METH_INT_TX_EMPTY&t;BIT(0)&t;/* 0: No interrupt pending, 1: The TX ring buffer is empty */
DECL|macro|METH_INT_TX_PKT
mdefine_line|#define METH_INT_TX_PKT&t;&t;BIT(1)&t;/* 0: No interrupt pending */
multiline_comment|/* 1: A TX message had the INT request bit set, the packet has been sent. */
DECL|macro|METH_INT_TX_LINK_FAIL
mdefine_line|#define METH_INT_TX_LINK_FAIL&t;BIT(2)&t;/* 0: No interrupt pending, 1: PHY has reported a link failure */
DECL|macro|METH_INT_MEM_ERROR
mdefine_line|#define METH_INT_MEM_ERROR&t;BIT(3)&t;/* 0: No interrupt pending */
multiline_comment|/* 1: A memory error occurred durring DMA, DMA stopped, Fatal */
DECL|macro|METH_INT_TX_ABORT
mdefine_line|#define METH_INT_TX_ABORT&t;&t;BIT(4)&t;/* 0: No interrupt pending, 1: The TX aborted operation, DMA stopped, FATAL */
DECL|macro|METH_INT_RX_THRESHOLD
mdefine_line|#define METH_INT_RX_THRESHOLD&t;BIT(5)&t;/* 0: No interrupt pending, 1: Selected receive threshold condition Valid */
DECL|macro|METH_INT_RX_UNDERFLOW
mdefine_line|#define METH_INT_RX_UNDERFLOW&t;BIT(6)&t;/* 0: No interrupt pending, 1: FIFO was empty, packet could not be queued */
DECL|macro|METH_INT_RX_OVERFLOW
mdefine_line|#define METH_INT_RX_OVERFLOW&t;&t;BIT(7)&t;/* 0: No interrupt pending, 1: DMA FIFO Overflow, DMA stopped, FATAL */
multiline_comment|/*#define METH_INT_RX_RPTR_MASK 0x0001F00*/
multiline_comment|/* Bits 8 through 12 alias of RX read-pointer */
DECL|macro|METH_INT_RX_RPTR_MASK
mdefine_line|#define METH_INT_RX_RPTR_MASK 0x0000F00&t;&t;/* Bits 8 through 11 alias of RX read-pointer - so, is Rx FIFO 16 or 32 entry?*/
multiline_comment|/* Bits 13 through 15 are always 0. */
DECL|macro|METH_INT_TX_RPTR_MASK
mdefine_line|#define METH_INT_TX_RPTR_MASK&t;0x1FF0000        /* Bits 16 through 24 alias of TX read-pointer */
DECL|macro|METH_INT_RX_SEQ_MASK
mdefine_line|#define METH_INT_RX_SEQ_MASK&t;0x2E000000&t;/* Bits 25 through 29 are the starting seq number for the message at the */
multiline_comment|/* top of the queue */
DECL|macro|METH_INT_ERROR
mdefine_line|#define METH_INT_ERROR&t;(METH_INT_TX_LINK_FAIL| &bslash;&n;&t;&t;&t;METH_INT_MEM_ERROR| &bslash;&n;&t;&t;&t;METH_INT_TX_ABORT| &bslash;&n;&t;&t;&t;METH_INT_RX_OVERFLOW| &bslash;&n;&t;&t;&t;METH_INT_RX_UNDERFLOW)
DECL|macro|METH_INT_MCAST_HASH
mdefine_line|#define METH_INT_MCAST_HASH&t;&t;BIT(30) /* If RX DMA is enabled the hash select logic output is latched here */
multiline_comment|/* TX status bits */
DECL|macro|METH_TX_ST_DONE
mdefine_line|#define METH_TX_ST_DONE      BIT(63) /* TX complete */
DECL|macro|METH_TX_ST_SUCCESS
mdefine_line|#define METH_TX_ST_SUCCESS   BIT(23) /* Packet was transmitted successfully */
DECL|macro|METH_TX_ST_TOOLONG
mdefine_line|#define METH_TX_ST_TOOLONG   BIT(24) /* TX abort due to excessive length */
DECL|macro|METH_TX_ST_UNDERRUN
mdefine_line|#define METH_TX_ST_UNDERRUN  BIT(25) /* TX abort due to underrun (?) */
DECL|macro|METH_TX_ST_EXCCOLL
mdefine_line|#define METH_TX_ST_EXCCOLL   BIT(26) /* TX abort due to excess collisions */
DECL|macro|METH_TX_ST_DEFER
mdefine_line|#define METH_TX_ST_DEFER     BIT(27) /* TX abort due to excess deferals */
DECL|macro|METH_TX_ST_LATECOLL
mdefine_line|#define METH_TX_ST_LATECOLL  BIT(28) /* TX abort due to late collision */
multiline_comment|/* Tx command header bits */
DECL|macro|METH_TX_CMD_INT_EN
mdefine_line|#define METH_TX_CMD_INT_EN BIT(24) /* Generate TX interrupt when packet is sent */
multiline_comment|/* Phy MDIO interface busy flag */
DECL|macro|MDIO_BUSY
mdefine_line|#define MDIO_BUSY    BIT(16)
DECL|macro|MDIO_DATA_MASK
mdefine_line|#define MDIO_DATA_MASK 0xFFFF
multiline_comment|/* PHY defines */
DECL|macro|PHY_QS6612X
mdefine_line|#define PHY_QS6612X    0x0181441    /* Quality TX */
DECL|macro|PHY_ICS1889
mdefine_line|#define PHY_ICS1889    0x0015F41    /* ICS FX */
DECL|macro|PHY_ICS1890
mdefine_line|#define PHY_ICS1890    0x0015F42    /* ICS TX */
DECL|macro|PHY_DP83840
mdefine_line|#define PHY_DP83840    0x20005C0    /* National TX */
DECL|macro|ADVANCE_RX_PTR
mdefine_line|#define ADVANCE_RX_PTR(x)  x=(x+1)&amp;(RX_RING_ENTRIES-1)
eof
