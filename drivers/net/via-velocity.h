multiline_comment|/*&n; * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.&n; * All rights reserved.&n; *&n; * This software may be redistributed and/or modified under&n; * the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License&n; * for more details.&n; *&n; * File: via-velocity.h&n; *&n; * Purpose: Header file to define driver&squot;s private structures.&n; *&n; * Author: Chuang Liang-Shing, AJ Jiang&n; *&n; * Date: Jan 24, 2003&n; */
macro_line|#ifndef VELOCITY_H
DECL|macro|VELOCITY_H
mdefine_line|#define VELOCITY_H
DECL|macro|VELOCITY_TX_CSUM_SUPPORT
mdefine_line|#define VELOCITY_TX_CSUM_SUPPORT
DECL|macro|VELOCITY_NAME
mdefine_line|#define VELOCITY_NAME          &quot;via-velocity&quot;
DECL|macro|VELOCITY_FULL_DRV_NAM
mdefine_line|#define VELOCITY_FULL_DRV_NAM  &quot;VIA Networking Velocity Family Gigabit Ethernet Adapter Driver&quot;
DECL|macro|VELOCITY_VERSION
mdefine_line|#define VELOCITY_VERSION       &quot;1.13&quot;
DECL|macro|PKT_BUF_SZ
mdefine_line|#define PKT_BUF_SZ          1540
DECL|macro|MAX_UNITS
mdefine_line|#define MAX_UNITS           8
DECL|macro|OPTION_DEFAULT
mdefine_line|#define OPTION_DEFAULT      { [0 ... MAX_UNITS-1] = -1}
DECL|macro|REV_ID_VT6110
mdefine_line|#define REV_ID_VT6110       (0)
DECL|macro|BYTE_REG_BITS_ON
mdefine_line|#define BYTE_REG_BITS_ON(x,p)       do { writeb(readb((p))|(x),(p));} while (0)
DECL|macro|WORD_REG_BITS_ON
mdefine_line|#define WORD_REG_BITS_ON(x,p)       do { writew(readw((p))|(x),(p));} while (0)
DECL|macro|DWORD_REG_BITS_ON
mdefine_line|#define DWORD_REG_BITS_ON(x,p)      do { writel(readl((p))|(x),(p));} while (0)
DECL|macro|BYTE_REG_BITS_IS_ON
mdefine_line|#define BYTE_REG_BITS_IS_ON(x,p)    (readb((p)) &amp; (x))
DECL|macro|WORD_REG_BITS_IS_ON
mdefine_line|#define WORD_REG_BITS_IS_ON(x,p)    (readw((p)) &amp; (x))
DECL|macro|DWORD_REG_BITS_IS_ON
mdefine_line|#define DWORD_REG_BITS_IS_ON(x,p)   (readl((p)) &amp; (x))
DECL|macro|BYTE_REG_BITS_OFF
mdefine_line|#define BYTE_REG_BITS_OFF(x,p)      do { writeb(readb((p)) &amp; (~(x)),(p));} while (0)
DECL|macro|WORD_REG_BITS_OFF
mdefine_line|#define WORD_REG_BITS_OFF(x,p)      do { writew(readw((p)) &amp; (~(x)),(p));} while (0)
DECL|macro|DWORD_REG_BITS_OFF
mdefine_line|#define DWORD_REG_BITS_OFF(x,p)     do { writel(readl((p)) &amp; (~(x)),(p));} while (0)
DECL|macro|BYTE_REG_BITS_SET
mdefine_line|#define BYTE_REG_BITS_SET(x,m,p)    do { writeb( (readb((p)) &amp; (~(m))) |(x),(p));} while (0)
DECL|macro|WORD_REG_BITS_SET
mdefine_line|#define WORD_REG_BITS_SET(x,m,p)    do { writew( (readw((p)) &amp; (~(m))) |(x),(p));} while (0)
DECL|macro|DWORD_REG_BITS_SET
mdefine_line|#define DWORD_REG_BITS_SET(x,m,p)   do { writel( (readl((p)) &amp; (~(m)))|(x),(p));}  while (0)
DECL|macro|VAR_USED
mdefine_line|#define VAR_USED(p)     do {(p)=(p);} while (0)
multiline_comment|/*&n; * Purpose: Structures for MAX RX/TX descriptors.&n; */
DECL|macro|B_OWNED_BY_CHIP
mdefine_line|#define B_OWNED_BY_CHIP     1
DECL|macro|B_OWNED_BY_HOST
mdefine_line|#define B_OWNED_BY_HOST     0
multiline_comment|/*&n; * Bits in the RSR0 register&n; */
DECL|macro|RSR_DETAG
mdefine_line|#define RSR_DETAG          0x0080
DECL|macro|RSR_SNTAG
mdefine_line|#define RSR_SNTAG          0x0040
DECL|macro|RSR_RXER
mdefine_line|#define RSR_RXER           0x0020
DECL|macro|RSR_RL
mdefine_line|#define RSR_RL             0x0010
DECL|macro|RSR_CE
mdefine_line|#define RSR_CE             0x0008
DECL|macro|RSR_FAE
mdefine_line|#define RSR_FAE            0x0004
DECL|macro|RSR_CRC
mdefine_line|#define RSR_CRC            0x0002
DECL|macro|RSR_VIDM
mdefine_line|#define RSR_VIDM           0x0001
multiline_comment|/*&n; * Bits in the RSR1 register&n; */
DECL|macro|RSR_RXOK
mdefine_line|#define RSR_RXOK           0x8000&t;
singleline_comment|// rx OK
DECL|macro|RSR_PFT
mdefine_line|#define RSR_PFT            0x4000&t;
singleline_comment|// Perfect filtering address match
DECL|macro|RSR_MAR
mdefine_line|#define RSR_MAR            0x2000&t;
singleline_comment|// MAC accept multicast address packet
DECL|macro|RSR_BAR
mdefine_line|#define RSR_BAR            0x1000&t;
singleline_comment|// MAC accept broadcast address packet
DECL|macro|RSR_PHY
mdefine_line|#define RSR_PHY            0x0800&t;
singleline_comment|// MAC accept physical address packet
DECL|macro|RSR_VTAG
mdefine_line|#define RSR_VTAG           0x0400&t;
singleline_comment|// 802.1p/1q tagging packet indicator
DECL|macro|RSR_STP
mdefine_line|#define RSR_STP            0x0200&t;
singleline_comment|// start of packet
DECL|macro|RSR_EDP
mdefine_line|#define RSR_EDP            0x0100&t;
singleline_comment|// end of packet
multiline_comment|/*&n; * Bits in the RSR1 register&n; */
DECL|macro|RSR1_RXOK
mdefine_line|#define RSR1_RXOK           0x80&t;
singleline_comment|// rx OK
DECL|macro|RSR1_PFT
mdefine_line|#define RSR1_PFT            0x40&t;
singleline_comment|// Perfect filtering address match
DECL|macro|RSR1_MAR
mdefine_line|#define RSR1_MAR            0x20&t;
singleline_comment|// MAC accept multicast address packet
DECL|macro|RSR1_BAR
mdefine_line|#define RSR1_BAR            0x10&t;
singleline_comment|// MAC accept broadcast address packet
DECL|macro|RSR1_PHY
mdefine_line|#define RSR1_PHY            0x08&t;
singleline_comment|// MAC accept physical address packet
DECL|macro|RSR1_VTAG
mdefine_line|#define RSR1_VTAG           0x04&t;
singleline_comment|// 802.1p/1q tagging packet indicator
DECL|macro|RSR1_STP
mdefine_line|#define RSR1_STP            0x02&t;
singleline_comment|// start of packet
DECL|macro|RSR1_EDP
mdefine_line|#define RSR1_EDP            0x01&t;
singleline_comment|// end of packet
multiline_comment|/*&n; * Bits in the CSM register&n; */
DECL|macro|CSM_IPOK
mdefine_line|#define CSM_IPOK            0x40&t;
singleline_comment|//IP Checkusm validatiaon ok
DECL|macro|CSM_TUPOK
mdefine_line|#define CSM_TUPOK           0x20&t;
singleline_comment|//TCP/UDP Checkusm validatiaon ok
DECL|macro|CSM_FRAG
mdefine_line|#define CSM_FRAG            0x10&t;
singleline_comment|//Fragment IP datagram
DECL|macro|CSM_IPKT
mdefine_line|#define CSM_IPKT            0x04&t;
singleline_comment|//Received an IP packet
DECL|macro|CSM_TCPKT
mdefine_line|#define CSM_TCPKT           0x02&t;
singleline_comment|//Received a TCP packet
DECL|macro|CSM_UDPKT
mdefine_line|#define CSM_UDPKT           0x01&t;
singleline_comment|//Received a UDP packet
multiline_comment|/*&n; * Bits in the TSR0 register&n; */
DECL|macro|TSR0_ABT
mdefine_line|#define TSR0_ABT            0x0080&t;
singleline_comment|// Tx abort because of excessive collision
DECL|macro|TSR0_OWT
mdefine_line|#define TSR0_OWT            0x0040&t;
singleline_comment|// Jumbo frame Tx abort
DECL|macro|TSR0_OWC
mdefine_line|#define TSR0_OWC            0x0020&t;
singleline_comment|// Out of window collision
DECL|macro|TSR0_COLS
mdefine_line|#define TSR0_COLS           0x0010&t;
singleline_comment|// experience collision in this transmit event
DECL|macro|TSR0_NCR3
mdefine_line|#define TSR0_NCR3           0x0008&t;
singleline_comment|// collision retry counter[3]
DECL|macro|TSR0_NCR2
mdefine_line|#define TSR0_NCR2           0x0004&t;
singleline_comment|// collision retry counter[2]
DECL|macro|TSR0_NCR1
mdefine_line|#define TSR0_NCR1           0x0002&t;
singleline_comment|// collision retry counter[1]
DECL|macro|TSR0_NCR0
mdefine_line|#define TSR0_NCR0           0x0001&t;
singleline_comment|// collision retry counter[0]
DECL|macro|TSR0_TERR
mdefine_line|#define TSR0_TERR           0x8000&t;
singleline_comment|//
DECL|macro|TSR0_FDX
mdefine_line|#define TSR0_FDX            0x4000&t;
singleline_comment|// current transaction is serviced by full duplex mode
DECL|macro|TSR0_GMII
mdefine_line|#define TSR0_GMII           0x2000&t;
singleline_comment|// current transaction is serviced by GMII mode
DECL|macro|TSR0_LNKFL
mdefine_line|#define TSR0_LNKFL          0x1000&t;
singleline_comment|// packet serviced during link down
DECL|macro|TSR0_SHDN
mdefine_line|#define TSR0_SHDN           0x0400&t;
singleline_comment|// shutdown case
DECL|macro|TSR0_CRS
mdefine_line|#define TSR0_CRS            0x0200&t;
singleline_comment|// carrier sense lost
DECL|macro|TSR0_CDH
mdefine_line|#define TSR0_CDH            0x0100&t;
singleline_comment|// AQE test fail (CD heartbeat)
multiline_comment|/*&n; * Bits in the TSR1 register&n; */
DECL|macro|TSR1_TERR
mdefine_line|#define TSR1_TERR           0x80&t;
singleline_comment|//
DECL|macro|TSR1_FDX
mdefine_line|#define TSR1_FDX            0x40&t;
singleline_comment|// current transaction is serviced by full duplex mode
DECL|macro|TSR1_GMII
mdefine_line|#define TSR1_GMII           0x20&t;
singleline_comment|// current transaction is serviced by GMII mode
DECL|macro|TSR1_LNKFL
mdefine_line|#define TSR1_LNKFL          0x10&t;
singleline_comment|// packet serviced during link down
DECL|macro|TSR1_SHDN
mdefine_line|#define TSR1_SHDN           0x04&t;
singleline_comment|// shutdown case
DECL|macro|TSR1_CRS
mdefine_line|#define TSR1_CRS            0x02&t;
singleline_comment|// carrier sense lost
DECL|macro|TSR1_CDH
mdefine_line|#define TSR1_CDH            0x01&t;
singleline_comment|// AQE test fail (CD heartbeat)
singleline_comment|//
singleline_comment|// Bits in the TCR0 register
singleline_comment|//
DECL|macro|TCR0_TIC
mdefine_line|#define TCR0_TIC            0x80&t;
singleline_comment|// assert interrupt immediately while descriptor has been send complete
DECL|macro|TCR0_PIC
mdefine_line|#define TCR0_PIC            0x40&t;
singleline_comment|// priority interrupt request, INA# is issued over adaptive interrupt scheme
DECL|macro|TCR0_VETAG
mdefine_line|#define TCR0_VETAG          0x20&t;
singleline_comment|// enable VLAN tag
DECL|macro|TCR0_IPCK
mdefine_line|#define TCR0_IPCK           0x10&t;
singleline_comment|// request IP  checksum calculation.
DECL|macro|TCR0_UDPCK
mdefine_line|#define TCR0_UDPCK          0x08&t;
singleline_comment|// request UDP checksum calculation.
DECL|macro|TCR0_TCPCK
mdefine_line|#define TCR0_TCPCK          0x04&t;
singleline_comment|// request TCP checksum calculation.
DECL|macro|TCR0_JMBO
mdefine_line|#define TCR0_JMBO           0x02&t;
singleline_comment|// indicate a jumbo packet in GMAC side
DECL|macro|TCR0_CRC
mdefine_line|#define TCR0_CRC            0x01&t;
singleline_comment|// disable CRC generation
DECL|macro|TCPLS_NORMAL
mdefine_line|#define TCPLS_NORMAL        3
DECL|macro|TCPLS_START
mdefine_line|#define TCPLS_START         2
DECL|macro|TCPLS_END
mdefine_line|#define TCPLS_END           1
DECL|macro|TCPLS_MED
mdefine_line|#define TCPLS_MED           0
singleline_comment|// max transmit or receive buffer size
DECL|macro|CB_RX_BUF_SIZE
mdefine_line|#define CB_RX_BUF_SIZE     2048UL&t;
singleline_comment|// max buffer size
singleline_comment|// NOTE: must be multiple of 4
DECL|macro|CB_MAX_RD_NUM
mdefine_line|#define CB_MAX_RD_NUM       512&t;
singleline_comment|// MAX # of RD
DECL|macro|CB_MAX_TD_NUM
mdefine_line|#define CB_MAX_TD_NUM       256&t;
singleline_comment|// MAX # of TD
DECL|macro|CB_INIT_RD_NUM_3119
mdefine_line|#define CB_INIT_RD_NUM_3119 128&t;
singleline_comment|// init # of RD, for setup VT3119
DECL|macro|CB_INIT_TD_NUM_3119
mdefine_line|#define CB_INIT_TD_NUM_3119 64&t;
singleline_comment|// init # of TD, for setup VT3119
DECL|macro|CB_INIT_RD_NUM
mdefine_line|#define CB_INIT_RD_NUM      128&t;
singleline_comment|// init # of RD, for setup default
DECL|macro|CB_INIT_TD_NUM
mdefine_line|#define CB_INIT_TD_NUM      64&t;
singleline_comment|// init # of TD, for setup default
singleline_comment|// for 3119
DECL|macro|CB_TD_RING_NUM
mdefine_line|#define CB_TD_RING_NUM      4&t;
singleline_comment|// # of TD rings.
DECL|macro|CB_MAX_SEG_PER_PKT
mdefine_line|#define CB_MAX_SEG_PER_PKT  7&t;
singleline_comment|// max data seg per packet (Tx)
multiline_comment|/*&n; *&t;If collisions excess 15 times , tx will abort, and&n; *&t;if tx fifo underflow, tx will fail&n; *&t;we should try to resend it&n; */
DECL|macro|CB_MAX_TX_ABORT_RETRY
mdefine_line|#define CB_MAX_TX_ABORT_RETRY   3
multiline_comment|/*&n; *&t;Receive descriptor&n; */
DECL|struct|rdesc0
r_struct
id|rdesc0
(brace
DECL|member|RSR
id|u16
id|RSR
suffix:semicolon
multiline_comment|/* Receive status */
DECL|member|len
id|u16
id|len
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* Received packet length */
DECL|member|reserved
id|u16
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|owner
id|u16
id|owner
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Who owns this buffer ? */
)brace
suffix:semicolon
DECL|struct|rdesc1
r_struct
id|rdesc1
(brace
DECL|member|PQTAG
id|u16
id|PQTAG
suffix:semicolon
DECL|member|CSM
id|u8
id|CSM
suffix:semicolon
DECL|member|IPKT
id|u8
id|IPKT
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rx_desc
r_struct
id|rx_desc
(brace
DECL|member|rdesc0
r_struct
id|rdesc0
id|rdesc0
suffix:semicolon
DECL|member|rdesc1
r_struct
id|rdesc1
id|rdesc1
suffix:semicolon
DECL|member|pa_low
id|u32
id|pa_low
suffix:semicolon
multiline_comment|/* Low 32 bit PCI address */
DECL|member|pa_high
id|u16
id|pa_high
suffix:semicolon
multiline_comment|/* Next 16 bit PCI address (48 total) */
DECL|member|len
id|u16
id|len
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Frame size */
DECL|member|inten
id|u16
id|inten
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Enable interrupt */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Transmit descriptor&n; */
DECL|struct|tdesc0
r_struct
id|tdesc0
(brace
DECL|member|TSR
id|u16
id|TSR
suffix:semicolon
multiline_comment|/* Transmit status register */
DECL|member|pktsize
id|u16
id|pktsize
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* Size of frame */
DECL|member|reserved
id|u16
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|owner
id|u16
id|owner
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Who owns the buffer */
)brace
suffix:semicolon
DECL|struct|pqinf
r_struct
id|pqinf
(brace
multiline_comment|/* Priority queue info */
DECL|member|VID
id|u16
id|VID
suffix:colon
l_int|12
suffix:semicolon
DECL|member|CFI
id|u16
id|CFI
suffix:colon
l_int|1
suffix:semicolon
DECL|member|priority
id|u16
id|priority
suffix:colon
l_int|3
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|struct|tdesc1
r_struct
id|tdesc1
(brace
DECL|member|pqinf
r_struct
id|pqinf
id|pqinf
suffix:semicolon
DECL|member|TCR
id|u8
id|TCR
suffix:semicolon
DECL|member|TCPLS
id|u8
id|TCPLS
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|CMDZ
id|u8
id|CMDZ
suffix:colon
l_int|4
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|struct|td_buf
r_struct
id|td_buf
(brace
DECL|member|pa_low
id|u32
id|pa_low
suffix:semicolon
DECL|member|pa_high
id|u16
id|pa_high
suffix:semicolon
DECL|member|bufsize
id|u16
id|bufsize
suffix:colon
l_int|14
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|queue
id|u16
id|queue
suffix:colon
l_int|1
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|struct|tx_desc
r_struct
id|tx_desc
(brace
DECL|member|tdesc0
r_struct
id|tdesc0
id|tdesc0
suffix:semicolon
DECL|member|tdesc1
r_struct
id|tdesc1
id|tdesc1
suffix:semicolon
DECL|member|td_buf
r_struct
id|td_buf
id|td_buf
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|velocity_rd_info
r_struct
id|velocity_rd_info
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|skb_dma
id|dma_addr_t
id|skb_dma
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;alloc_rd_info&t;&t;-&t;allocate an rd info block&n; *&n; *&t;Alocate and initialize a receive info structure used for keeping&n; *&t;track of kernel side information related to each receive&n; *&t;descriptor we are using&n; */
DECL|function|alloc_rd_info
r_static
r_inline
r_struct
id|velocity_rd_info
op_star
id|alloc_rd_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|velocity_rd_info
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|velocity_rd_info
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
(brace
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|velocity_rd_info
)paren
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Used to track transmit side buffers.&n; */
DECL|struct|velocity_td_info
r_struct
id|velocity_td_info
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|buf
id|u8
op_star
id|buf
suffix:semicolon
DECL|member|nskb_dma
r_int
id|nskb_dma
suffix:semicolon
DECL|member|skb_dma
id|dma_addr_t
id|skb_dma
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|buf_dma
id|dma_addr_t
id|buf_dma
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|velocity_owner
r_enum
id|velocity_owner
(brace
DECL|enumerator|OWNED_BY_HOST
id|OWNED_BY_HOST
op_assign
l_int|0
comma
DECL|enumerator|OWNED_BY_NIC
id|OWNED_BY_NIC
op_assign
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;MAC registers and macros.&n; */
DECL|macro|MCAM_SIZE
mdefine_line|#define MCAM_SIZE           64
DECL|macro|VCAM_SIZE
mdefine_line|#define VCAM_SIZE           64
DECL|macro|TX_QUEUE_NO
mdefine_line|#define TX_QUEUE_NO         4
DECL|macro|MAX_HW_MIB_COUNTER
mdefine_line|#define MAX_HW_MIB_COUNTER  32
DECL|macro|VELOCITY_MIN_MTU
mdefine_line|#define VELOCITY_MIN_MTU    (1514-14)
DECL|macro|VELOCITY_MAX_MTU
mdefine_line|#define VELOCITY_MAX_MTU    (9000)
multiline_comment|/*&n; *&t;Registers in the MAC&n; */
DECL|macro|MAC_REG_PAR
mdefine_line|#define MAC_REG_PAR         0x00&t;
singleline_comment|// physical address
DECL|macro|MAC_REG_RCR
mdefine_line|#define MAC_REG_RCR         0x06
DECL|macro|MAC_REG_TCR
mdefine_line|#define MAC_REG_TCR         0x07
DECL|macro|MAC_REG_CR0_SET
mdefine_line|#define MAC_REG_CR0_SET     0x08
DECL|macro|MAC_REG_CR1_SET
mdefine_line|#define MAC_REG_CR1_SET     0x09
DECL|macro|MAC_REG_CR2_SET
mdefine_line|#define MAC_REG_CR2_SET     0x0A
DECL|macro|MAC_REG_CR3_SET
mdefine_line|#define MAC_REG_CR3_SET     0x0B
DECL|macro|MAC_REG_CR0_CLR
mdefine_line|#define MAC_REG_CR0_CLR     0x0C
DECL|macro|MAC_REG_CR1_CLR
mdefine_line|#define MAC_REG_CR1_CLR     0x0D
DECL|macro|MAC_REG_CR2_CLR
mdefine_line|#define MAC_REG_CR2_CLR     0x0E
DECL|macro|MAC_REG_CR3_CLR
mdefine_line|#define MAC_REG_CR3_CLR     0x0F
DECL|macro|MAC_REG_MAR
mdefine_line|#define MAC_REG_MAR         0x10
DECL|macro|MAC_REG_CAM
mdefine_line|#define MAC_REG_CAM         0x10
DECL|macro|MAC_REG_DEC_BASE_HI
mdefine_line|#define MAC_REG_DEC_BASE_HI 0x18
DECL|macro|MAC_REG_DBF_BASE_HI
mdefine_line|#define MAC_REG_DBF_BASE_HI 0x1C
DECL|macro|MAC_REG_ISR_CTL
mdefine_line|#define MAC_REG_ISR_CTL     0x20
DECL|macro|MAC_REG_ISR_HOTMR
mdefine_line|#define MAC_REG_ISR_HOTMR   0x20
DECL|macro|MAC_REG_ISR_TSUPTHR
mdefine_line|#define MAC_REG_ISR_TSUPTHR 0x20
DECL|macro|MAC_REG_ISR_RSUPTHR
mdefine_line|#define MAC_REG_ISR_RSUPTHR 0x20
DECL|macro|MAC_REG_ISR_CTL1
mdefine_line|#define MAC_REG_ISR_CTL1    0x21
DECL|macro|MAC_REG_TXE_SR
mdefine_line|#define MAC_REG_TXE_SR      0x22
DECL|macro|MAC_REG_RXE_SR
mdefine_line|#define MAC_REG_RXE_SR      0x23
DECL|macro|MAC_REG_ISR
mdefine_line|#define MAC_REG_ISR         0x24
DECL|macro|MAC_REG_ISR0
mdefine_line|#define MAC_REG_ISR0        0x24
DECL|macro|MAC_REG_ISR1
mdefine_line|#define MAC_REG_ISR1        0x25
DECL|macro|MAC_REG_ISR2
mdefine_line|#define MAC_REG_ISR2        0x26
DECL|macro|MAC_REG_ISR3
mdefine_line|#define MAC_REG_ISR3        0x27
DECL|macro|MAC_REG_IMR
mdefine_line|#define MAC_REG_IMR         0x28
DECL|macro|MAC_REG_IMR0
mdefine_line|#define MAC_REG_IMR0        0x28
DECL|macro|MAC_REG_IMR1
mdefine_line|#define MAC_REG_IMR1        0x29
DECL|macro|MAC_REG_IMR2
mdefine_line|#define MAC_REG_IMR2        0x2A
DECL|macro|MAC_REG_IMR3
mdefine_line|#define MAC_REG_IMR3        0x2B
DECL|macro|MAC_REG_TDCSR_SET
mdefine_line|#define MAC_REG_TDCSR_SET   0x30
DECL|macro|MAC_REG_RDCSR_SET
mdefine_line|#define MAC_REG_RDCSR_SET   0x32
DECL|macro|MAC_REG_TDCSR_CLR
mdefine_line|#define MAC_REG_TDCSR_CLR   0x34
DECL|macro|MAC_REG_RDCSR_CLR
mdefine_line|#define MAC_REG_RDCSR_CLR   0x36
DECL|macro|MAC_REG_RDBASE_LO
mdefine_line|#define MAC_REG_RDBASE_LO   0x38
DECL|macro|MAC_REG_RDINDX
mdefine_line|#define MAC_REG_RDINDX      0x3C
DECL|macro|MAC_REG_TDBASE_LO
mdefine_line|#define MAC_REG_TDBASE_LO   0x40
DECL|macro|MAC_REG_RDCSIZE
mdefine_line|#define MAC_REG_RDCSIZE     0x50
DECL|macro|MAC_REG_TDCSIZE
mdefine_line|#define MAC_REG_TDCSIZE     0x52
DECL|macro|MAC_REG_TDINDX
mdefine_line|#define MAC_REG_TDINDX      0x54
DECL|macro|MAC_REG_TDIDX0
mdefine_line|#define MAC_REG_TDIDX0      0x54
DECL|macro|MAC_REG_TDIDX1
mdefine_line|#define MAC_REG_TDIDX1      0x56
DECL|macro|MAC_REG_TDIDX2
mdefine_line|#define MAC_REG_TDIDX2      0x58
DECL|macro|MAC_REG_TDIDX3
mdefine_line|#define MAC_REG_TDIDX3      0x5A
DECL|macro|MAC_REG_PAUSE_TIMER
mdefine_line|#define MAC_REG_PAUSE_TIMER 0x5C
DECL|macro|MAC_REG_RBRDU
mdefine_line|#define MAC_REG_RBRDU       0x5E
DECL|macro|MAC_REG_FIFO_TEST0
mdefine_line|#define MAC_REG_FIFO_TEST0  0x60
DECL|macro|MAC_REG_FIFO_TEST1
mdefine_line|#define MAC_REG_FIFO_TEST1  0x64
DECL|macro|MAC_REG_CAMADDR
mdefine_line|#define MAC_REG_CAMADDR     0x68
DECL|macro|MAC_REG_CAMCR
mdefine_line|#define MAC_REG_CAMCR       0x69
DECL|macro|MAC_REG_GFTEST
mdefine_line|#define MAC_REG_GFTEST      0x6A
DECL|macro|MAC_REG_FTSTCMD
mdefine_line|#define MAC_REG_FTSTCMD     0x6B
DECL|macro|MAC_REG_MIICFG
mdefine_line|#define MAC_REG_MIICFG      0x6C
DECL|macro|MAC_REG_MIISR
mdefine_line|#define MAC_REG_MIISR       0x6D
DECL|macro|MAC_REG_PHYSR0
mdefine_line|#define MAC_REG_PHYSR0      0x6E
DECL|macro|MAC_REG_PHYSR1
mdefine_line|#define MAC_REG_PHYSR1      0x6F
DECL|macro|MAC_REG_MIICR
mdefine_line|#define MAC_REG_MIICR       0x70
DECL|macro|MAC_REG_MIIADR
mdefine_line|#define MAC_REG_MIIADR      0x71
DECL|macro|MAC_REG_MIIDATA
mdefine_line|#define MAC_REG_MIIDATA     0x72
DECL|macro|MAC_REG_SOFT_TIMER0
mdefine_line|#define MAC_REG_SOFT_TIMER0 0x74
DECL|macro|MAC_REG_SOFT_TIMER1
mdefine_line|#define MAC_REG_SOFT_TIMER1 0x76
DECL|macro|MAC_REG_CFGA
mdefine_line|#define MAC_REG_CFGA        0x78
DECL|macro|MAC_REG_CFGB
mdefine_line|#define MAC_REG_CFGB        0x79
DECL|macro|MAC_REG_CFGC
mdefine_line|#define MAC_REG_CFGC        0x7A
DECL|macro|MAC_REG_CFGD
mdefine_line|#define MAC_REG_CFGD        0x7B
DECL|macro|MAC_REG_DCFG0
mdefine_line|#define MAC_REG_DCFG0       0x7C
DECL|macro|MAC_REG_DCFG1
mdefine_line|#define MAC_REG_DCFG1       0x7D
DECL|macro|MAC_REG_MCFG0
mdefine_line|#define MAC_REG_MCFG0       0x7E
DECL|macro|MAC_REG_MCFG1
mdefine_line|#define MAC_REG_MCFG1       0x7F
DECL|macro|MAC_REG_TBIST
mdefine_line|#define MAC_REG_TBIST       0x80
DECL|macro|MAC_REG_RBIST
mdefine_line|#define MAC_REG_RBIST       0x81
DECL|macro|MAC_REG_PMCC
mdefine_line|#define MAC_REG_PMCC        0x82
DECL|macro|MAC_REG_STICKHW
mdefine_line|#define MAC_REG_STICKHW     0x83
DECL|macro|MAC_REG_MIBCR
mdefine_line|#define MAC_REG_MIBCR       0x84
DECL|macro|MAC_REG_EERSV
mdefine_line|#define MAC_REG_EERSV       0x85
DECL|macro|MAC_REG_REVID
mdefine_line|#define MAC_REG_REVID       0x86
DECL|macro|MAC_REG_MIBREAD
mdefine_line|#define MAC_REG_MIBREAD     0x88
DECL|macro|MAC_REG_BPMA
mdefine_line|#define MAC_REG_BPMA        0x8C
DECL|macro|MAC_REG_EEWR_DATA
mdefine_line|#define MAC_REG_EEWR_DATA   0x8C
DECL|macro|MAC_REG_BPMD_WR
mdefine_line|#define MAC_REG_BPMD_WR     0x8F
DECL|macro|MAC_REG_BPCMD
mdefine_line|#define MAC_REG_BPCMD       0x90
DECL|macro|MAC_REG_BPMD_RD
mdefine_line|#define MAC_REG_BPMD_RD     0x91
DECL|macro|MAC_REG_EECHKSUM
mdefine_line|#define MAC_REG_EECHKSUM    0x92
DECL|macro|MAC_REG_EECSR
mdefine_line|#define MAC_REG_EECSR       0x93
DECL|macro|MAC_REG_EERD_DATA
mdefine_line|#define MAC_REG_EERD_DATA   0x94
DECL|macro|MAC_REG_EADDR
mdefine_line|#define MAC_REG_EADDR       0x96
DECL|macro|MAC_REG_EMBCMD
mdefine_line|#define MAC_REG_EMBCMD      0x97
DECL|macro|MAC_REG_JMPSR0
mdefine_line|#define MAC_REG_JMPSR0      0x98
DECL|macro|MAC_REG_JMPSR1
mdefine_line|#define MAC_REG_JMPSR1      0x99
DECL|macro|MAC_REG_JMPSR2
mdefine_line|#define MAC_REG_JMPSR2      0x9A
DECL|macro|MAC_REG_JMPSR3
mdefine_line|#define MAC_REG_JMPSR3      0x9B
DECL|macro|MAC_REG_CHIPGSR
mdefine_line|#define MAC_REG_CHIPGSR     0x9C
DECL|macro|MAC_REG_TESTCFG
mdefine_line|#define MAC_REG_TESTCFG     0x9D
DECL|macro|MAC_REG_DEBUG
mdefine_line|#define MAC_REG_DEBUG       0x9E
DECL|macro|MAC_REG_CHIPGCR
mdefine_line|#define MAC_REG_CHIPGCR     0x9F
DECL|macro|MAC_REG_WOLCR0_SET
mdefine_line|#define MAC_REG_WOLCR0_SET  0xA0
DECL|macro|MAC_REG_WOLCR1_SET
mdefine_line|#define MAC_REG_WOLCR1_SET  0xA1
DECL|macro|MAC_REG_PWCFG_SET
mdefine_line|#define MAC_REG_PWCFG_SET   0xA2
DECL|macro|MAC_REG_WOLCFG_SET
mdefine_line|#define MAC_REG_WOLCFG_SET  0xA3
DECL|macro|MAC_REG_WOLCR0_CLR
mdefine_line|#define MAC_REG_WOLCR0_CLR  0xA4
DECL|macro|MAC_REG_WOLCR1_CLR
mdefine_line|#define MAC_REG_WOLCR1_CLR  0xA5
DECL|macro|MAC_REG_PWCFG_CLR
mdefine_line|#define MAC_REG_PWCFG_CLR   0xA6
DECL|macro|MAC_REG_WOLCFG_CLR
mdefine_line|#define MAC_REG_WOLCFG_CLR  0xA7
DECL|macro|MAC_REG_WOLSR0_SET
mdefine_line|#define MAC_REG_WOLSR0_SET  0xA8
DECL|macro|MAC_REG_WOLSR1_SET
mdefine_line|#define MAC_REG_WOLSR1_SET  0xA9
DECL|macro|MAC_REG_WOLSR0_CLR
mdefine_line|#define MAC_REG_WOLSR0_CLR  0xAC
DECL|macro|MAC_REG_WOLSR1_CLR
mdefine_line|#define MAC_REG_WOLSR1_CLR  0xAD
DECL|macro|MAC_REG_PATRN_CRC0
mdefine_line|#define MAC_REG_PATRN_CRC0  0xB0
DECL|macro|MAC_REG_PATRN_CRC1
mdefine_line|#define MAC_REG_PATRN_CRC1  0xB2
DECL|macro|MAC_REG_PATRN_CRC2
mdefine_line|#define MAC_REG_PATRN_CRC2  0xB4
DECL|macro|MAC_REG_PATRN_CRC3
mdefine_line|#define MAC_REG_PATRN_CRC3  0xB6
DECL|macro|MAC_REG_PATRN_CRC4
mdefine_line|#define MAC_REG_PATRN_CRC4  0xB8
DECL|macro|MAC_REG_PATRN_CRC5
mdefine_line|#define MAC_REG_PATRN_CRC5  0xBA
DECL|macro|MAC_REG_PATRN_CRC6
mdefine_line|#define MAC_REG_PATRN_CRC6  0xBC
DECL|macro|MAC_REG_PATRN_CRC7
mdefine_line|#define MAC_REG_PATRN_CRC7  0xBE
DECL|macro|MAC_REG_BYTEMSK0_0
mdefine_line|#define MAC_REG_BYTEMSK0_0  0xC0
DECL|macro|MAC_REG_BYTEMSK0_1
mdefine_line|#define MAC_REG_BYTEMSK0_1  0xC4
DECL|macro|MAC_REG_BYTEMSK0_2
mdefine_line|#define MAC_REG_BYTEMSK0_2  0xC8
DECL|macro|MAC_REG_BYTEMSK0_3
mdefine_line|#define MAC_REG_BYTEMSK0_3  0xCC
DECL|macro|MAC_REG_BYTEMSK1_0
mdefine_line|#define MAC_REG_BYTEMSK1_0  0xD0
DECL|macro|MAC_REG_BYTEMSK1_1
mdefine_line|#define MAC_REG_BYTEMSK1_1  0xD4
DECL|macro|MAC_REG_BYTEMSK1_2
mdefine_line|#define MAC_REG_BYTEMSK1_2  0xD8
DECL|macro|MAC_REG_BYTEMSK1_3
mdefine_line|#define MAC_REG_BYTEMSK1_3  0xDC
DECL|macro|MAC_REG_BYTEMSK2_0
mdefine_line|#define MAC_REG_BYTEMSK2_0  0xE0
DECL|macro|MAC_REG_BYTEMSK2_1
mdefine_line|#define MAC_REG_BYTEMSK2_1  0xE4
DECL|macro|MAC_REG_BYTEMSK2_2
mdefine_line|#define MAC_REG_BYTEMSK2_2  0xE8
DECL|macro|MAC_REG_BYTEMSK2_3
mdefine_line|#define MAC_REG_BYTEMSK2_3  0xEC
DECL|macro|MAC_REG_BYTEMSK3_0
mdefine_line|#define MAC_REG_BYTEMSK3_0  0xF0
DECL|macro|MAC_REG_BYTEMSK3_1
mdefine_line|#define MAC_REG_BYTEMSK3_1  0xF4
DECL|macro|MAC_REG_BYTEMSK3_2
mdefine_line|#define MAC_REG_BYTEMSK3_2  0xF8
DECL|macro|MAC_REG_BYTEMSK3_3
mdefine_line|#define MAC_REG_BYTEMSK3_3  0xFC
multiline_comment|/*&n; *&t;Bits in the RCR register&n; */
DECL|macro|RCR_AS
mdefine_line|#define RCR_AS              0x80
DECL|macro|RCR_AP
mdefine_line|#define RCR_AP              0x40
DECL|macro|RCR_AL
mdefine_line|#define RCR_AL              0x20
DECL|macro|RCR_PROM
mdefine_line|#define RCR_PROM            0x10
DECL|macro|RCR_AB
mdefine_line|#define RCR_AB              0x08
DECL|macro|RCR_AM
mdefine_line|#define RCR_AM              0x04
DECL|macro|RCR_AR
mdefine_line|#define RCR_AR              0x02
DECL|macro|RCR_SEP
mdefine_line|#define RCR_SEP             0x01
multiline_comment|/*&n; *&t;Bits in the TCR register&n; */
DECL|macro|TCR_TB2BDIS
mdefine_line|#define TCR_TB2BDIS         0x80
DECL|macro|TCR_COLTMC1
mdefine_line|#define TCR_COLTMC1         0x08
DECL|macro|TCR_COLTMC0
mdefine_line|#define TCR_COLTMC0         0x04
DECL|macro|TCR_LB1
mdefine_line|#define TCR_LB1             0x02&t;/* loopback[1] */
DECL|macro|TCR_LB0
mdefine_line|#define TCR_LB0             0x01&t;/* loopback[0] */
multiline_comment|/*&n; *&t;Bits in the CR0 register&n; */
DECL|macro|CR0_TXON
mdefine_line|#define CR0_TXON            0x00000008UL
DECL|macro|CR0_RXON
mdefine_line|#define CR0_RXON            0x00000004UL
DECL|macro|CR0_STOP
mdefine_line|#define CR0_STOP            0x00000002UL&t;/* stop MAC, default = 1 */
DECL|macro|CR0_STRT
mdefine_line|#define CR0_STRT            0x00000001UL&t;/* start MAC */
DECL|macro|CR0_SFRST
mdefine_line|#define CR0_SFRST           0x00008000UL&t;/* software reset */
DECL|macro|CR0_TM1EN
mdefine_line|#define CR0_TM1EN           0x00004000UL
DECL|macro|CR0_TM0EN
mdefine_line|#define CR0_TM0EN           0x00002000UL
DECL|macro|CR0_DPOLL
mdefine_line|#define CR0_DPOLL           0x00000800UL&t;/* disable rx/tx auto polling */
DECL|macro|CR0_DISAU
mdefine_line|#define CR0_DISAU           0x00000100UL
DECL|macro|CR0_XONEN
mdefine_line|#define CR0_XONEN           0x00800000UL
DECL|macro|CR0_FDXTFCEN
mdefine_line|#define CR0_FDXTFCEN        0x00400000UL&t;/* full-duplex TX flow control enable */
DECL|macro|CR0_FDXRFCEN
mdefine_line|#define CR0_FDXRFCEN        0x00200000UL&t;/* full-duplex RX flow control enable */
DECL|macro|CR0_HDXFCEN
mdefine_line|#define CR0_HDXFCEN         0x00100000UL&t;/* half-duplex flow control enable */
DECL|macro|CR0_XHITH1
mdefine_line|#define CR0_XHITH1          0x00080000UL&t;/* TX XON high threshold 1 */
DECL|macro|CR0_XHITH0
mdefine_line|#define CR0_XHITH0          0x00040000UL&t;/* TX XON high threshold 0 */
DECL|macro|CR0_XLTH1
mdefine_line|#define CR0_XLTH1           0x00020000UL&t;/* TX pause frame low threshold 1 */
DECL|macro|CR0_XLTH0
mdefine_line|#define CR0_XLTH0           0x00010000UL&t;/* TX pause frame low threshold 0 */
DECL|macro|CR0_GSPRST
mdefine_line|#define CR0_GSPRST          0x80000000UL
DECL|macro|CR0_FORSRST
mdefine_line|#define CR0_FORSRST         0x40000000UL
DECL|macro|CR0_FPHYRST
mdefine_line|#define CR0_FPHYRST         0x20000000UL
DECL|macro|CR0_DIAG
mdefine_line|#define CR0_DIAG            0x10000000UL
DECL|macro|CR0_INTPCTL
mdefine_line|#define CR0_INTPCTL         0x04000000UL
DECL|macro|CR0_GINTMSK1
mdefine_line|#define CR0_GINTMSK1        0x02000000UL
DECL|macro|CR0_GINTMSK0
mdefine_line|#define CR0_GINTMSK0        0x01000000UL
multiline_comment|/*&n; *&t;Bits in the CR1 register&n; */
DECL|macro|CR1_SFRST
mdefine_line|#define CR1_SFRST           0x80&t;/* software reset */
DECL|macro|CR1_TM1EN
mdefine_line|#define CR1_TM1EN           0x40
DECL|macro|CR1_TM0EN
mdefine_line|#define CR1_TM0EN           0x20
DECL|macro|CR1_DPOLL
mdefine_line|#define CR1_DPOLL           0x08&t;/* disable rx/tx auto polling */
DECL|macro|CR1_DISAU
mdefine_line|#define CR1_DISAU           0x01
multiline_comment|/*&n; *&t;Bits in the CR2 register&n; */
DECL|macro|CR2_XONEN
mdefine_line|#define CR2_XONEN           0x80
DECL|macro|CR2_FDXTFCEN
mdefine_line|#define CR2_FDXTFCEN        0x40&t;/* full-duplex TX flow control enable */
DECL|macro|CR2_FDXRFCEN
mdefine_line|#define CR2_FDXRFCEN        0x20&t;/* full-duplex RX flow control enable */
DECL|macro|CR2_HDXFCEN
mdefine_line|#define CR2_HDXFCEN         0x10&t;/* half-duplex flow control enable */
DECL|macro|CR2_XHITH1
mdefine_line|#define CR2_XHITH1          0x08&t;/* TX XON high threshold 1 */
DECL|macro|CR2_XHITH0
mdefine_line|#define CR2_XHITH0          0x04&t;/* TX XON high threshold 0 */
DECL|macro|CR2_XLTH1
mdefine_line|#define CR2_XLTH1           0x02&t;/* TX pause frame low threshold 1 */
DECL|macro|CR2_XLTH0
mdefine_line|#define CR2_XLTH0           0x01&t;/* TX pause frame low threshold 0 */
multiline_comment|/*&n; *&t;Bits in the CR3 register&n; */
DECL|macro|CR3_GSPRST
mdefine_line|#define CR3_GSPRST          0x80
DECL|macro|CR3_FORSRST
mdefine_line|#define CR3_FORSRST         0x40
DECL|macro|CR3_FPHYRST
mdefine_line|#define CR3_FPHYRST         0x20
DECL|macro|CR3_DIAG
mdefine_line|#define CR3_DIAG            0x10
DECL|macro|CR3_INTPCTL
mdefine_line|#define CR3_INTPCTL         0x04
DECL|macro|CR3_GINTMSK1
mdefine_line|#define CR3_GINTMSK1        0x02
DECL|macro|CR3_GINTMSK0
mdefine_line|#define CR3_GINTMSK0        0x01
DECL|macro|ISRCTL_UDPINT
mdefine_line|#define ISRCTL_UDPINT       0x8000
DECL|macro|ISRCTL_TSUPDIS
mdefine_line|#define ISRCTL_TSUPDIS      0x4000
DECL|macro|ISRCTL_RSUPDIS
mdefine_line|#define ISRCTL_RSUPDIS      0x2000
DECL|macro|ISRCTL_PMSK1
mdefine_line|#define ISRCTL_PMSK1        0x1000
DECL|macro|ISRCTL_PMSK0
mdefine_line|#define ISRCTL_PMSK0        0x0800
DECL|macro|ISRCTL_INTPD
mdefine_line|#define ISRCTL_INTPD        0x0400
DECL|macro|ISRCTL_HCRLD
mdefine_line|#define ISRCTL_HCRLD        0x0200
DECL|macro|ISRCTL_SCRLD
mdefine_line|#define ISRCTL_SCRLD        0x0100
multiline_comment|/*&n; *&t;Bits in the ISR_CTL1 register&n; */
DECL|macro|ISRCTL1_UDPINT
mdefine_line|#define ISRCTL1_UDPINT      0x80
DECL|macro|ISRCTL1_TSUPDIS
mdefine_line|#define ISRCTL1_TSUPDIS     0x40
DECL|macro|ISRCTL1_RSUPDIS
mdefine_line|#define ISRCTL1_RSUPDIS     0x20
DECL|macro|ISRCTL1_PMSK1
mdefine_line|#define ISRCTL1_PMSK1       0x10
DECL|macro|ISRCTL1_PMSK0
mdefine_line|#define ISRCTL1_PMSK0       0x08
DECL|macro|ISRCTL1_INTPD
mdefine_line|#define ISRCTL1_INTPD       0x04
DECL|macro|ISRCTL1_HCRLD
mdefine_line|#define ISRCTL1_HCRLD       0x02
DECL|macro|ISRCTL1_SCRLD
mdefine_line|#define ISRCTL1_SCRLD       0x01
multiline_comment|/*&n; *&t;Bits in the TXE_SR register&n; */
DECL|macro|TXESR_TFDBS
mdefine_line|#define TXESR_TFDBS         0x08
DECL|macro|TXESR_TDWBS
mdefine_line|#define TXESR_TDWBS         0x04
DECL|macro|TXESR_TDRBS
mdefine_line|#define TXESR_TDRBS         0x02
DECL|macro|TXESR_TDSTR
mdefine_line|#define TXESR_TDSTR         0x01
multiline_comment|/*&n; *&t;Bits in the RXE_SR register&n; */
DECL|macro|RXESR_RFDBS
mdefine_line|#define RXESR_RFDBS         0x08
DECL|macro|RXESR_RDWBS
mdefine_line|#define RXESR_RDWBS         0x04
DECL|macro|RXESR_RDRBS
mdefine_line|#define RXESR_RDRBS         0x02
DECL|macro|RXESR_RDSTR
mdefine_line|#define RXESR_RDSTR         0x01
multiline_comment|/*&n; *&t;Bits in the ISR register&n; */
DECL|macro|ISR_ISR3
mdefine_line|#define ISR_ISR3            0x80000000UL
DECL|macro|ISR_ISR2
mdefine_line|#define ISR_ISR2            0x40000000UL
DECL|macro|ISR_ISR1
mdefine_line|#define ISR_ISR1            0x20000000UL
DECL|macro|ISR_ISR0
mdefine_line|#define ISR_ISR0            0x10000000UL
DECL|macro|ISR_TXSTLI
mdefine_line|#define ISR_TXSTLI          0x02000000UL
DECL|macro|ISR_RXSTLI
mdefine_line|#define ISR_RXSTLI          0x01000000UL
DECL|macro|ISR_HFLD
mdefine_line|#define ISR_HFLD            0x00800000UL
DECL|macro|ISR_UDPI
mdefine_line|#define ISR_UDPI            0x00400000UL
DECL|macro|ISR_MIBFI
mdefine_line|#define ISR_MIBFI           0x00200000UL
DECL|macro|ISR_SHDNI
mdefine_line|#define ISR_SHDNI           0x00100000UL
DECL|macro|ISR_PHYI
mdefine_line|#define ISR_PHYI            0x00080000UL
DECL|macro|ISR_PWEI
mdefine_line|#define ISR_PWEI            0x00040000UL
DECL|macro|ISR_TMR1I
mdefine_line|#define ISR_TMR1I           0x00020000UL
DECL|macro|ISR_TMR0I
mdefine_line|#define ISR_TMR0I           0x00010000UL
DECL|macro|ISR_SRCI
mdefine_line|#define ISR_SRCI            0x00008000UL
DECL|macro|ISR_LSTPEI
mdefine_line|#define ISR_LSTPEI          0x00004000UL
DECL|macro|ISR_LSTEI
mdefine_line|#define ISR_LSTEI           0x00002000UL
DECL|macro|ISR_OVFI
mdefine_line|#define ISR_OVFI            0x00001000UL
DECL|macro|ISR_FLONI
mdefine_line|#define ISR_FLONI           0x00000800UL
DECL|macro|ISR_RACEI
mdefine_line|#define ISR_RACEI           0x00000400UL
DECL|macro|ISR_TXWB1I
mdefine_line|#define ISR_TXWB1I          0x00000200UL
DECL|macro|ISR_TXWB0I
mdefine_line|#define ISR_TXWB0I          0x00000100UL
DECL|macro|ISR_PTX3I
mdefine_line|#define ISR_PTX3I           0x00000080UL
DECL|macro|ISR_PTX2I
mdefine_line|#define ISR_PTX2I           0x00000040UL
DECL|macro|ISR_PTX1I
mdefine_line|#define ISR_PTX1I           0x00000020UL
DECL|macro|ISR_PTX0I
mdefine_line|#define ISR_PTX0I           0x00000010UL
DECL|macro|ISR_PTXI
mdefine_line|#define ISR_PTXI            0x00000008UL
DECL|macro|ISR_PRXI
mdefine_line|#define ISR_PRXI            0x00000004UL
DECL|macro|ISR_PPTXI
mdefine_line|#define ISR_PPTXI           0x00000002UL
DECL|macro|ISR_PPRXI
mdefine_line|#define ISR_PPRXI           0x00000001UL
multiline_comment|/*&n; *&t;Bits in the IMR register&n; */
DECL|macro|IMR_TXSTLM
mdefine_line|#define IMR_TXSTLM          0x02000000UL
DECL|macro|IMR_UDPIM
mdefine_line|#define IMR_UDPIM           0x00400000UL
DECL|macro|IMR_MIBFIM
mdefine_line|#define IMR_MIBFIM          0x00200000UL
DECL|macro|IMR_SHDNIM
mdefine_line|#define IMR_SHDNIM          0x00100000UL
DECL|macro|IMR_PHYIM
mdefine_line|#define IMR_PHYIM           0x00080000UL
DECL|macro|IMR_PWEIM
mdefine_line|#define IMR_PWEIM           0x00040000UL
DECL|macro|IMR_TMR1IM
mdefine_line|#define IMR_TMR1IM          0x00020000UL
DECL|macro|IMR_TMR0IM
mdefine_line|#define IMR_TMR0IM          0x00010000UL
DECL|macro|IMR_SRCIM
mdefine_line|#define IMR_SRCIM           0x00008000UL
DECL|macro|IMR_LSTPEIM
mdefine_line|#define IMR_LSTPEIM         0x00004000UL
DECL|macro|IMR_LSTEIM
mdefine_line|#define IMR_LSTEIM          0x00002000UL
DECL|macro|IMR_OVFIM
mdefine_line|#define IMR_OVFIM           0x00001000UL
DECL|macro|IMR_FLONIM
mdefine_line|#define IMR_FLONIM          0x00000800UL
DECL|macro|IMR_RACEIM
mdefine_line|#define IMR_RACEIM          0x00000400UL
DECL|macro|IMR_TXWB1IM
mdefine_line|#define IMR_TXWB1IM         0x00000200UL
DECL|macro|IMR_TXWB0IM
mdefine_line|#define IMR_TXWB0IM         0x00000100UL
DECL|macro|IMR_PTX3IM
mdefine_line|#define IMR_PTX3IM          0x00000080UL
DECL|macro|IMR_PTX2IM
mdefine_line|#define IMR_PTX2IM          0x00000040UL
DECL|macro|IMR_PTX1IM
mdefine_line|#define IMR_PTX1IM          0x00000020UL
DECL|macro|IMR_PTX0IM
mdefine_line|#define IMR_PTX0IM          0x00000010UL
DECL|macro|IMR_PTXIM
mdefine_line|#define IMR_PTXIM           0x00000008UL
DECL|macro|IMR_PRXIM
mdefine_line|#define IMR_PRXIM           0x00000004UL
DECL|macro|IMR_PPTXIM
mdefine_line|#define IMR_PPTXIM          0x00000002UL
DECL|macro|IMR_PPRXIM
mdefine_line|#define IMR_PPRXIM          0x00000001UL
multiline_comment|/* 0x0013FB0FUL  =  initial value of IMR */
DECL|macro|INT_MASK_DEF
mdefine_line|#define INT_MASK_DEF        (IMR_PPTXIM|IMR_PPRXIM|IMR_PTXIM|IMR_PRXIM|&bslash;&n;                            IMR_PWEIM|IMR_TXWB0IM|IMR_TXWB1IM|IMR_FLONIM|&bslash;&n;                            IMR_OVFIM|IMR_LSTEIM|IMR_LSTPEIM|IMR_SRCIM|IMR_MIBFIM|&bslash;&n;                            IMR_SHDNIM|IMR_TMR1IM|IMR_TMR0IM|IMR_TXSTLM)
multiline_comment|/*&n; *&t;Bits in the TDCSR0/1, RDCSR0 register&n; */
DECL|macro|TRDCSR_DEAD
mdefine_line|#define TRDCSR_DEAD         0x0008
DECL|macro|TRDCSR_WAK
mdefine_line|#define TRDCSR_WAK          0x0004
DECL|macro|TRDCSR_ACT
mdefine_line|#define TRDCSR_ACT          0x0002
DECL|macro|TRDCSR_RUN
mdefine_line|#define TRDCSR_RUN&t;    0x0001
multiline_comment|/*&n; *&t;Bits in the CAMADDR register&n; */
DECL|macro|CAMADDR_CAMEN
mdefine_line|#define CAMADDR_CAMEN       0x80
DECL|macro|CAMADDR_VCAMSL
mdefine_line|#define CAMADDR_VCAMSL      0x40
multiline_comment|/*&n; *&t;Bits in the CAMCR register&n; */
DECL|macro|CAMCR_PS1
mdefine_line|#define CAMCR_PS1           0x80
DECL|macro|CAMCR_PS0
mdefine_line|#define CAMCR_PS0           0x40
DECL|macro|CAMCR_AITRPKT
mdefine_line|#define CAMCR_AITRPKT       0x20
DECL|macro|CAMCR_AITR16
mdefine_line|#define CAMCR_AITR16        0x10
DECL|macro|CAMCR_CAMRD
mdefine_line|#define CAMCR_CAMRD         0x08
DECL|macro|CAMCR_CAMWR
mdefine_line|#define CAMCR_CAMWR         0x04
DECL|macro|CAMCR_PS_CAM_MASK
mdefine_line|#define CAMCR_PS_CAM_MASK   0x40
DECL|macro|CAMCR_PS_CAM_DATA
mdefine_line|#define CAMCR_PS_CAM_DATA   0x80
DECL|macro|CAMCR_PS_MAR
mdefine_line|#define CAMCR_PS_MAR        0x00
multiline_comment|/*&n; *&t;Bits in the MIICFG register&n; */
DECL|macro|MIICFG_MPO1
mdefine_line|#define MIICFG_MPO1         0x80
DECL|macro|MIICFG_MPO0
mdefine_line|#define MIICFG_MPO0         0x40
DECL|macro|MIICFG_MFDC
mdefine_line|#define MIICFG_MFDC         0x20
multiline_comment|/*&n; *&t;Bits in the MIISR register&n; */
DECL|macro|MIISR_MIDLE
mdefine_line|#define MIISR_MIDLE         0x80
multiline_comment|/*&n; *&t; Bits in the PHYSR0 register&n; */
DECL|macro|PHYSR0_PHYRST
mdefine_line|#define PHYSR0_PHYRST       0x80
DECL|macro|PHYSR0_LINKGD
mdefine_line|#define PHYSR0_LINKGD       0x40
DECL|macro|PHYSR0_FDPX
mdefine_line|#define PHYSR0_FDPX         0x10
DECL|macro|PHYSR0_SPDG
mdefine_line|#define PHYSR0_SPDG         0x08
DECL|macro|PHYSR0_SPD10
mdefine_line|#define PHYSR0_SPD10        0x04
DECL|macro|PHYSR0_RXFLC
mdefine_line|#define PHYSR0_RXFLC        0x02
DECL|macro|PHYSR0_TXFLC
mdefine_line|#define PHYSR0_TXFLC        0x01
multiline_comment|/*&n; *&t;Bits in the PHYSR1 register&n; */
DECL|macro|PHYSR1_PHYTBI
mdefine_line|#define PHYSR1_PHYTBI       0x01
multiline_comment|/*&n; *&t;Bits in the MIICR register&n; */
DECL|macro|MIICR_MAUTO
mdefine_line|#define MIICR_MAUTO         0x80
DECL|macro|MIICR_RCMD
mdefine_line|#define MIICR_RCMD          0x40
DECL|macro|MIICR_WCMD
mdefine_line|#define MIICR_WCMD          0x20
DECL|macro|MIICR_MDPM
mdefine_line|#define MIICR_MDPM          0x10
DECL|macro|MIICR_MOUT
mdefine_line|#define MIICR_MOUT          0x08
DECL|macro|MIICR_MDO
mdefine_line|#define MIICR_MDO           0x04
DECL|macro|MIICR_MDI
mdefine_line|#define MIICR_MDI           0x02
DECL|macro|MIICR_MDC
mdefine_line|#define MIICR_MDC           0x01
multiline_comment|/*&n; *&t;Bits in the MIIADR register&n; */
DECL|macro|MIIADR_SWMPL
mdefine_line|#define MIIADR_SWMPL        0x80
multiline_comment|/*&n; *&t;Bits in the CFGA register&n; */
DECL|macro|CFGA_PMHCTG
mdefine_line|#define CFGA_PMHCTG         0x08
DECL|macro|CFGA_GPIO1PD
mdefine_line|#define CFGA_GPIO1PD        0x04
DECL|macro|CFGA_ABSHDN
mdefine_line|#define CFGA_ABSHDN         0x02
DECL|macro|CFGA_PACPI
mdefine_line|#define CFGA_PACPI          0x01
multiline_comment|/*&n; *&t;Bits in the CFGB register&n; */
DECL|macro|CFGB_GTCKOPT
mdefine_line|#define CFGB_GTCKOPT        0x80
DECL|macro|CFGB_MIIOPT
mdefine_line|#define CFGB_MIIOPT         0x40
DECL|macro|CFGB_CRSEOPT
mdefine_line|#define CFGB_CRSEOPT        0x20
DECL|macro|CFGB_OFSET
mdefine_line|#define CFGB_OFSET          0x10
DECL|macro|CFGB_CRANDOM
mdefine_line|#define CFGB_CRANDOM        0x08
DECL|macro|CFGB_CAP
mdefine_line|#define CFGB_CAP            0x04
DECL|macro|CFGB_MBA
mdefine_line|#define CFGB_MBA            0x02
DECL|macro|CFGB_BAKOPT
mdefine_line|#define CFGB_BAKOPT         0x01
multiline_comment|/*&n; *&t;Bits in the CFGC register&n; */
DECL|macro|CFGC_EELOAD
mdefine_line|#define CFGC_EELOAD         0x80
DECL|macro|CFGC_BROPT
mdefine_line|#define CFGC_BROPT          0x40
DECL|macro|CFGC_DLYEN
mdefine_line|#define CFGC_DLYEN          0x20
DECL|macro|CFGC_DTSEL
mdefine_line|#define CFGC_DTSEL          0x10
DECL|macro|CFGC_BTSEL
mdefine_line|#define CFGC_BTSEL          0x08
DECL|macro|CFGC_BPS2
mdefine_line|#define CFGC_BPS2           0x04&t;/* bootrom select[2] */
DECL|macro|CFGC_BPS1
mdefine_line|#define CFGC_BPS1           0x02&t;/* bootrom select[1] */
DECL|macro|CFGC_BPS0
mdefine_line|#define CFGC_BPS0           0x01&t;/* bootrom select[0] */
multiline_comment|/*&n; * Bits in the CFGD register&n; */
DECL|macro|CFGD_IODIS
mdefine_line|#define CFGD_IODIS          0x80
DECL|macro|CFGD_MSLVDACEN
mdefine_line|#define CFGD_MSLVDACEN      0x40
DECL|macro|CFGD_CFGDACEN
mdefine_line|#define CFGD_CFGDACEN       0x20
DECL|macro|CFGD_PCI64EN
mdefine_line|#define CFGD_PCI64EN        0x10
DECL|macro|CFGD_HTMRL4
mdefine_line|#define CFGD_HTMRL4         0x08
multiline_comment|/*&n; *&t;Bits in the DCFG1 register&n; */
DECL|macro|DCFG_XMWI
mdefine_line|#define DCFG_XMWI           0x8000
DECL|macro|DCFG_XMRM
mdefine_line|#define DCFG_XMRM           0x4000
DECL|macro|DCFG_XMRL
mdefine_line|#define DCFG_XMRL           0x2000
DECL|macro|DCFG_PERDIS
mdefine_line|#define DCFG_PERDIS         0x1000
DECL|macro|DCFG_MRWAIT
mdefine_line|#define DCFG_MRWAIT         0x0400
DECL|macro|DCFG_MWWAIT
mdefine_line|#define DCFG_MWWAIT         0x0200
DECL|macro|DCFG_LATMEN
mdefine_line|#define DCFG_LATMEN         0x0100
multiline_comment|/*&n; *&t;Bits in the MCFG0 register&n; */
DECL|macro|MCFG_RXARB
mdefine_line|#define MCFG_RXARB          0x0080
DECL|macro|MCFG_RFT1
mdefine_line|#define MCFG_RFT1           0x0020
DECL|macro|MCFG_RFT0
mdefine_line|#define MCFG_RFT0           0x0010
DECL|macro|MCFG_LOWTHOPT
mdefine_line|#define MCFG_LOWTHOPT       0x0008
DECL|macro|MCFG_PQEN
mdefine_line|#define MCFG_PQEN           0x0004
DECL|macro|MCFG_RTGOPT
mdefine_line|#define MCFG_RTGOPT         0x0002
DECL|macro|MCFG_VIDFR
mdefine_line|#define MCFG_VIDFR          0x0001
multiline_comment|/*&n; *&t;Bits in the MCFG1 register&n; */
DECL|macro|MCFG_TXARB
mdefine_line|#define MCFG_TXARB          0x8000
DECL|macro|MCFG_TXQBK1
mdefine_line|#define MCFG_TXQBK1         0x0800
DECL|macro|MCFG_TXQBK0
mdefine_line|#define MCFG_TXQBK0         0x0400
DECL|macro|MCFG_TXQNOBK
mdefine_line|#define MCFG_TXQNOBK        0x0200
DECL|macro|MCFG_SNAPOPT
mdefine_line|#define MCFG_SNAPOPT        0x0100
multiline_comment|/*&n; *&t;Bits in the PMCC  register&n; */
DECL|macro|PMCC_DSI
mdefine_line|#define PMCC_DSI            0x80
DECL|macro|PMCC_D2_DIS
mdefine_line|#define PMCC_D2_DIS         0x40
DECL|macro|PMCC_D1_DIS
mdefine_line|#define PMCC_D1_DIS         0x20
DECL|macro|PMCC_D3C_EN
mdefine_line|#define PMCC_D3C_EN         0x10
DECL|macro|PMCC_D3H_EN
mdefine_line|#define PMCC_D3H_EN         0x08
DECL|macro|PMCC_D2_EN
mdefine_line|#define PMCC_D2_EN          0x04
DECL|macro|PMCC_D1_EN
mdefine_line|#define PMCC_D1_EN          0x02
DECL|macro|PMCC_D0_EN
mdefine_line|#define PMCC_D0_EN          0x01
multiline_comment|/*&n; *&t;Bits in STICKHW&n; */
DECL|macro|STICKHW_SWPTAG
mdefine_line|#define STICKHW_SWPTAG      0x10
DECL|macro|STICKHW_WOLSR
mdefine_line|#define STICKHW_WOLSR       0x08
DECL|macro|STICKHW_WOLEN
mdefine_line|#define STICKHW_WOLEN       0x04
DECL|macro|STICKHW_DS1
mdefine_line|#define STICKHW_DS1         0x02&t;/* R/W by software/cfg cycle */
DECL|macro|STICKHW_DS0
mdefine_line|#define STICKHW_DS0         0x01&t;/* suspend well DS write port */
multiline_comment|/*&n; *&t;Bits in the MIBCR register&n; */
DECL|macro|MIBCR_MIBISTOK
mdefine_line|#define MIBCR_MIBISTOK      0x80
DECL|macro|MIBCR_MIBISTGO
mdefine_line|#define MIBCR_MIBISTGO      0x40
DECL|macro|MIBCR_MIBINC
mdefine_line|#define MIBCR_MIBINC        0x20
DECL|macro|MIBCR_MIBHI
mdefine_line|#define MIBCR_MIBHI         0x10
DECL|macro|MIBCR_MIBFRZ
mdefine_line|#define MIBCR_MIBFRZ        0x08
DECL|macro|MIBCR_MIBFLSH
mdefine_line|#define MIBCR_MIBFLSH       0x04
DECL|macro|MIBCR_MPTRINI
mdefine_line|#define MIBCR_MPTRINI       0x02
DECL|macro|MIBCR_MIBCLR
mdefine_line|#define MIBCR_MIBCLR        0x01
multiline_comment|/*&n; *&t;Bits in the EERSV register&n; */
DECL|macro|EERSV_BOOT_RPL
mdefine_line|#define EERSV_BOOT_RPL      ((u8) 0x01)&t; /* Boot method selection for VT6110 */
DECL|macro|EERSV_BOOT_MASK
mdefine_line|#define EERSV_BOOT_MASK     ((u8) 0x06)
DECL|macro|EERSV_BOOT_INT19
mdefine_line|#define EERSV_BOOT_INT19    ((u8) 0x00)
DECL|macro|EERSV_BOOT_INT18
mdefine_line|#define EERSV_BOOT_INT18    ((u8) 0x02)
DECL|macro|EERSV_BOOT_LOCAL
mdefine_line|#define EERSV_BOOT_LOCAL    ((u8) 0x04)
DECL|macro|EERSV_BOOT_BEV
mdefine_line|#define EERSV_BOOT_BEV      ((u8) 0x06)
multiline_comment|/*&n; *&t;Bits in BPCMD&n; */
DECL|macro|BPCMD_BPDNE
mdefine_line|#define BPCMD_BPDNE         0x80
DECL|macro|BPCMD_EBPWR
mdefine_line|#define BPCMD_EBPWR         0x02
DECL|macro|BPCMD_EBPRD
mdefine_line|#define BPCMD_EBPRD         0x01
multiline_comment|/*&n; *&t;Bits in the EECSR register&n; */
DECL|macro|EECSR_EMBP
mdefine_line|#define EECSR_EMBP          0x40&t;/* eeprom embeded programming */
DECL|macro|EECSR_RELOAD
mdefine_line|#define EECSR_RELOAD        0x20&t;/* eeprom content reload */
DECL|macro|EECSR_DPM
mdefine_line|#define EECSR_DPM           0x10&t;/* eeprom direct programming */
DECL|macro|EECSR_ECS
mdefine_line|#define EECSR_ECS           0x08&t;/* eeprom CS pin */
DECL|macro|EECSR_ECK
mdefine_line|#define EECSR_ECK           0x04&t;/* eeprom CK pin */
DECL|macro|EECSR_EDI
mdefine_line|#define EECSR_EDI           0x02&t;/* eeprom DI pin */
DECL|macro|EECSR_EDO
mdefine_line|#define EECSR_EDO           0x01&t;/* eeprom DO pin */
multiline_comment|/*&n; *&t;Bits in the EMBCMD register&n; */
DECL|macro|EMBCMD_EDONE
mdefine_line|#define EMBCMD_EDONE        0x80
DECL|macro|EMBCMD_EWDIS
mdefine_line|#define EMBCMD_EWDIS        0x08
DECL|macro|EMBCMD_EWEN
mdefine_line|#define EMBCMD_EWEN         0x04
DECL|macro|EMBCMD_EWR
mdefine_line|#define EMBCMD_EWR          0x02
DECL|macro|EMBCMD_ERD
mdefine_line|#define EMBCMD_ERD          0x01
multiline_comment|/*&n; *&t;Bits in TESTCFG register&n; */
DECL|macro|TESTCFG_HBDIS
mdefine_line|#define TESTCFG_HBDIS       0x80
multiline_comment|/*&n; *&t;Bits in CHIPGCR register&n; */
DECL|macro|CHIPGCR_FCGMII
mdefine_line|#define CHIPGCR_FCGMII      0x80
DECL|macro|CHIPGCR_FCFDX
mdefine_line|#define CHIPGCR_FCFDX       0x40
DECL|macro|CHIPGCR_FCRESV
mdefine_line|#define CHIPGCR_FCRESV      0x20
DECL|macro|CHIPGCR_FCMODE
mdefine_line|#define CHIPGCR_FCMODE      0x10
DECL|macro|CHIPGCR_LPSOPT
mdefine_line|#define CHIPGCR_LPSOPT      0x08
DECL|macro|CHIPGCR_TM1US
mdefine_line|#define CHIPGCR_TM1US       0x04
DECL|macro|CHIPGCR_TM0US
mdefine_line|#define CHIPGCR_TM0US       0x02
DECL|macro|CHIPGCR_PHYINTEN
mdefine_line|#define CHIPGCR_PHYINTEN    0x01
multiline_comment|/*&n; *&t;Bits in WOLCR0&n; */
DECL|macro|WOLCR_MSWOLEN7
mdefine_line|#define WOLCR_MSWOLEN7      0x0080&t;/* enable pattern match filtering */
DECL|macro|WOLCR_MSWOLEN6
mdefine_line|#define WOLCR_MSWOLEN6      0x0040
DECL|macro|WOLCR_MSWOLEN5
mdefine_line|#define WOLCR_MSWOLEN5      0x0020
DECL|macro|WOLCR_MSWOLEN4
mdefine_line|#define WOLCR_MSWOLEN4      0x0010
DECL|macro|WOLCR_MSWOLEN3
mdefine_line|#define WOLCR_MSWOLEN3      0x0008
DECL|macro|WOLCR_MSWOLEN2
mdefine_line|#define WOLCR_MSWOLEN2      0x0004
DECL|macro|WOLCR_MSWOLEN1
mdefine_line|#define WOLCR_MSWOLEN1      0x0002
DECL|macro|WOLCR_MSWOLEN0
mdefine_line|#define WOLCR_MSWOLEN0      0x0001
DECL|macro|WOLCR_ARP_EN
mdefine_line|#define WOLCR_ARP_EN        0x0001
multiline_comment|/*&n; *&t;Bits in WOLCR1&n; */
DECL|macro|WOLCR_LINKOFF_EN
mdefine_line|#define WOLCR_LINKOFF_EN      0x0800&t;/* link off detected enable */
DECL|macro|WOLCR_LINKON_EN
mdefine_line|#define WOLCR_LINKON_EN       0x0400&t;/* link on detected enable */
DECL|macro|WOLCR_MAGIC_EN
mdefine_line|#define WOLCR_MAGIC_EN        0x0200&t;/* magic packet filter enable */
DECL|macro|WOLCR_UNICAST_EN
mdefine_line|#define WOLCR_UNICAST_EN      0x0100&t;/* unicast filter enable */
multiline_comment|/*&n; *&t;Bits in PWCFG&n; */
DECL|macro|PWCFG_PHYPWOPT
mdefine_line|#define PWCFG_PHYPWOPT          0x80&t;/* internal MII I/F timing */
DECL|macro|PWCFG_PCISTICK
mdefine_line|#define PWCFG_PCISTICK          0x40&t;/* PCI sticky R/W enable */
DECL|macro|PWCFG_WOLTYPE
mdefine_line|#define PWCFG_WOLTYPE           0x20&t;/* pulse(1) or button (0) */
DECL|macro|PWCFG_LEGCY_WOL
mdefine_line|#define PWCFG_LEGCY_WOL         0x10
DECL|macro|PWCFG_PMCSR_PME_SR
mdefine_line|#define PWCFG_PMCSR_PME_SR      0x08
DECL|macro|PWCFG_PMCSR_PME_EN
mdefine_line|#define PWCFG_PMCSR_PME_EN      0x04&t;/* control by PCISTICK */
DECL|macro|PWCFG_LEGACY_WOLSR
mdefine_line|#define PWCFG_LEGACY_WOLSR      0x02&t;/* Legacy WOL_SR shadow */
DECL|macro|PWCFG_LEGACY_WOLEN
mdefine_line|#define PWCFG_LEGACY_WOLEN      0x01&t;/* Legacy WOL_EN shadow */
multiline_comment|/*&n; *&t;Bits in WOLCFG&n; */
DECL|macro|WOLCFG_PMEOVR
mdefine_line|#define WOLCFG_PMEOVR           0x80&t;/* for legacy use, force PMEEN always */
DECL|macro|WOLCFG_SAM
mdefine_line|#define WOLCFG_SAM              0x20&t;/* accept multicast case reset, default=0 */
DECL|macro|WOLCFG_SAB
mdefine_line|#define WOLCFG_SAB              0x10&t;/* accept broadcast case reset, default=0 */
DECL|macro|WOLCFG_SMIIACC
mdefine_line|#define WOLCFG_SMIIACC          0x08&t;/* ?? */
DECL|macro|WOLCFG_SGENWH
mdefine_line|#define WOLCFG_SGENWH           0x02
DECL|macro|WOLCFG_PHYINTEN
mdefine_line|#define WOLCFG_PHYINTEN         0x01&t;/* 0:PHYINT trigger enable, 1:use internal MII&n;&t;&t;&t;&t;&t;  to report status change */
multiline_comment|/*&n; *&t;Bits in WOLSR1&n; */
DECL|macro|WOLSR_LINKOFF_INT
mdefine_line|#define WOLSR_LINKOFF_INT      0x0800
DECL|macro|WOLSR_LINKON_INT
mdefine_line|#define WOLSR_LINKON_INT       0x0400
DECL|macro|WOLSR_MAGIC_INT
mdefine_line|#define WOLSR_MAGIC_INT        0x0200
DECL|macro|WOLSR_UNICAST_INT
mdefine_line|#define WOLSR_UNICAST_INT      0x0100
multiline_comment|/*&n; *&t;Ethernet address filter type&n; */
DECL|macro|PKT_TYPE_NONE
mdefine_line|#define PKT_TYPE_NONE               0x0000&t;/* Turn off receiver */
DECL|macro|PKT_TYPE_DIRECTED
mdefine_line|#define PKT_TYPE_DIRECTED           0x0001&t;/* obselete, directed address is always accepted */
DECL|macro|PKT_TYPE_MULTICAST
mdefine_line|#define PKT_TYPE_MULTICAST          0x0002
DECL|macro|PKT_TYPE_ALL_MULTICAST
mdefine_line|#define PKT_TYPE_ALL_MULTICAST      0x0004
DECL|macro|PKT_TYPE_BROADCAST
mdefine_line|#define PKT_TYPE_BROADCAST          0x0008
DECL|macro|PKT_TYPE_PROMISCUOUS
mdefine_line|#define PKT_TYPE_PROMISCUOUS        0x0020
DECL|macro|PKT_TYPE_LONG
mdefine_line|#define PKT_TYPE_LONG               0x2000&t;/* NOTE.... the definition of LONG is &gt;2048 bytes in our chip */
DECL|macro|PKT_TYPE_RUNT
mdefine_line|#define PKT_TYPE_RUNT               0x4000
DECL|macro|PKT_TYPE_ERROR
mdefine_line|#define PKT_TYPE_ERROR              0x8000&t;/* Accept error packets, e.g. CRC error */
multiline_comment|/*&n; *&t;Loopback mode&n; */
DECL|macro|MAC_LB_NONE
mdefine_line|#define MAC_LB_NONE         0x00
DECL|macro|MAC_LB_INTERNAL
mdefine_line|#define MAC_LB_INTERNAL     0x01
DECL|macro|MAC_LB_EXTERNAL
mdefine_line|#define MAC_LB_EXTERNAL     0x02
multiline_comment|/*&n; *&t;Enabled mask value of irq&n; */
macro_line|#if defined(_SIM)
DECL|macro|IMR_MASK_VALUE
mdefine_line|#define IMR_MASK_VALUE      0x0033FF0FUL&t;/* initial value of IMR&n;&t;&t;&t;&t;&t;&t;   set IMR0 to 0x0F according to spec */
macro_line|#else
DECL|macro|IMR_MASK_VALUE
mdefine_line|#define IMR_MASK_VALUE      0x0013FB0FUL&t;/* initial value of IMR&n;&t;&t;&t;&t;&t;&t;   ignore MIBFI,RACEI to&n;&t;&t;&t;&t;&t;&t;   reduce intr. frequency&n;&t;&t;&t;&t;&t;&t;   NOTE.... do not enable NoBuf int mask at driver driver&n;&t;&t;&t;&t;&t;&t;      when (1) NoBuf -&gt; RxThreshold = SF&n;&t;&t;&t;&t;&t;&t;&t;   (2) OK    -&gt; RxThreshold = original value&n;&t;&t;&t;&t;&t;&t; */
macro_line|#endif
multiline_comment|/*&n; *&t;Revision id&n; */
DECL|macro|REV_ID_VT3119_A0
mdefine_line|#define REV_ID_VT3119_A0&t;0x00
DECL|macro|REV_ID_VT3119_A1
mdefine_line|#define REV_ID_VT3119_A1&t;0x01
DECL|macro|REV_ID_VT3216_A0
mdefine_line|#define REV_ID_VT3216_A0&t;0x10
multiline_comment|/*&n; *&t;Max time out delay time&n; */
DECL|macro|W_MAX_TIMEOUT
mdefine_line|#define W_MAX_TIMEOUT       0x0FFFU
multiline_comment|/*&n; *&t;MAC registers as a structure. Cannot be directly accessed this&n; *&t;way but generates offsets for readl/writel() calls&n; */
DECL|struct|mac_regs
r_struct
id|mac_regs
(brace
DECL|member|PAR
r_volatile
id|u8
id|PAR
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|RCR
r_volatile
id|u8
id|RCR
suffix:semicolon
DECL|member|TCR
r_volatile
id|u8
id|TCR
suffix:semicolon
DECL|member|CR0Set
r_volatile
id|u32
id|CR0Set
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|CR0Clr
r_volatile
id|u32
id|CR0Clr
suffix:semicolon
multiline_comment|/* 0x0C */
DECL|member|MARCAM
r_volatile
id|u8
id|MARCAM
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|DecBaseHi
r_volatile
id|u32
id|DecBaseHi
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|DbfBaseHi
r_volatile
id|u16
id|DbfBaseHi
suffix:semicolon
multiline_comment|/* 0x1C */
DECL|member|reserved_1E
r_volatile
id|u16
id|reserved_1E
suffix:semicolon
DECL|member|ISRCTL
r_volatile
id|u16
id|ISRCTL
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|TXESR
r_volatile
id|u8
id|TXESR
suffix:semicolon
DECL|member|RXESR
r_volatile
id|u8
id|RXESR
suffix:semicolon
DECL|member|ISR
r_volatile
id|u32
id|ISR
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|IMR
r_volatile
id|u32
id|IMR
suffix:semicolon
DECL|member|TDStatusPort
r_volatile
id|u32
id|TDStatusPort
suffix:semicolon
multiline_comment|/* 0x2C */
DECL|member|TDCSRSet
r_volatile
id|u16
id|TDCSRSet
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|RDCSRSet
r_volatile
id|u8
id|RDCSRSet
suffix:semicolon
DECL|member|reserved_33
r_volatile
id|u8
id|reserved_33
suffix:semicolon
DECL|member|TDCSRClr
r_volatile
id|u16
id|TDCSRClr
suffix:semicolon
DECL|member|RDCSRClr
r_volatile
id|u8
id|RDCSRClr
suffix:semicolon
DECL|member|reserved_37
r_volatile
id|u8
id|reserved_37
suffix:semicolon
DECL|member|RDBaseLo
r_volatile
id|u32
id|RDBaseLo
suffix:semicolon
multiline_comment|/* 0x38 */
DECL|member|RDIdx
r_volatile
id|u16
id|RDIdx
suffix:semicolon
multiline_comment|/* 0x3C */
DECL|member|reserved_3E
r_volatile
id|u16
id|reserved_3E
suffix:semicolon
DECL|member|TDBaseLo
r_volatile
id|u32
id|TDBaseLo
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|RDCSize
r_volatile
id|u16
id|RDCSize
suffix:semicolon
multiline_comment|/* 0x50 */
DECL|member|TDCSize
r_volatile
id|u16
id|TDCSize
suffix:semicolon
multiline_comment|/* 0x52 */
DECL|member|TDIdx
r_volatile
id|u16
id|TDIdx
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x54 */
DECL|member|tx_pause_timer
r_volatile
id|u16
id|tx_pause_timer
suffix:semicolon
multiline_comment|/* 0x5C */
DECL|member|RBRDU
r_volatile
id|u16
id|RBRDU
suffix:semicolon
multiline_comment|/* 0x5E */
DECL|member|FIFOTest0
r_volatile
id|u32
id|FIFOTest0
suffix:semicolon
multiline_comment|/* 0x60 */
DECL|member|FIFOTest1
r_volatile
id|u32
id|FIFOTest1
suffix:semicolon
multiline_comment|/* 0x64 */
DECL|member|CAMADDR
r_volatile
id|u8
id|CAMADDR
suffix:semicolon
multiline_comment|/* 0x68 */
DECL|member|CAMCR
r_volatile
id|u8
id|CAMCR
suffix:semicolon
multiline_comment|/* 0x69 */
DECL|member|GFTEST
r_volatile
id|u8
id|GFTEST
suffix:semicolon
multiline_comment|/* 0x6A */
DECL|member|FTSTCMD
r_volatile
id|u8
id|FTSTCMD
suffix:semicolon
multiline_comment|/* 0x6B */
DECL|member|MIICFG
r_volatile
id|u8
id|MIICFG
suffix:semicolon
multiline_comment|/* 0x6C */
DECL|member|MIISR
r_volatile
id|u8
id|MIISR
suffix:semicolon
DECL|member|PHYSR0
r_volatile
id|u8
id|PHYSR0
suffix:semicolon
DECL|member|PHYSR1
r_volatile
id|u8
id|PHYSR1
suffix:semicolon
DECL|member|MIICR
r_volatile
id|u8
id|MIICR
suffix:semicolon
DECL|member|MIIADR
r_volatile
id|u8
id|MIIADR
suffix:semicolon
DECL|member|MIIDATA
r_volatile
id|u16
id|MIIDATA
suffix:semicolon
DECL|member|SoftTimer0
r_volatile
id|u16
id|SoftTimer0
suffix:semicolon
multiline_comment|/* 0x74 */
DECL|member|SoftTimer1
r_volatile
id|u16
id|SoftTimer1
suffix:semicolon
DECL|member|CFGA
r_volatile
id|u8
id|CFGA
suffix:semicolon
multiline_comment|/* 0x78 */
DECL|member|CFGB
r_volatile
id|u8
id|CFGB
suffix:semicolon
DECL|member|CFGC
r_volatile
id|u8
id|CFGC
suffix:semicolon
DECL|member|CFGD
r_volatile
id|u8
id|CFGD
suffix:semicolon
DECL|member|DCFG
r_volatile
id|u16
id|DCFG
suffix:semicolon
multiline_comment|/* 0x7C */
DECL|member|MCFG
r_volatile
id|u16
id|MCFG
suffix:semicolon
DECL|member|TBIST
r_volatile
id|u8
id|TBIST
suffix:semicolon
multiline_comment|/* 0x80 */
DECL|member|RBIST
r_volatile
id|u8
id|RBIST
suffix:semicolon
DECL|member|PMCPORT
r_volatile
id|u8
id|PMCPORT
suffix:semicolon
DECL|member|STICKHW
r_volatile
id|u8
id|STICKHW
suffix:semicolon
DECL|member|MIBCR
r_volatile
id|u8
id|MIBCR
suffix:semicolon
multiline_comment|/* 0x84 */
DECL|member|reserved_85
r_volatile
id|u8
id|reserved_85
suffix:semicolon
DECL|member|rev_id
r_volatile
id|u8
id|rev_id
suffix:semicolon
DECL|member|PORSTS
r_volatile
id|u8
id|PORSTS
suffix:semicolon
DECL|member|MIBData
r_volatile
id|u32
id|MIBData
suffix:semicolon
multiline_comment|/* 0x88 */
DECL|member|EEWrData
r_volatile
id|u16
id|EEWrData
suffix:semicolon
DECL|member|reserved_8E
r_volatile
id|u8
id|reserved_8E
suffix:semicolon
DECL|member|BPMDWr
r_volatile
id|u8
id|BPMDWr
suffix:semicolon
DECL|member|BPCMD
r_volatile
id|u8
id|BPCMD
suffix:semicolon
DECL|member|BPMDRd
r_volatile
id|u8
id|BPMDRd
suffix:semicolon
DECL|member|EECHKSUM
r_volatile
id|u8
id|EECHKSUM
suffix:semicolon
multiline_comment|/* 0x92 */
DECL|member|EECSR
r_volatile
id|u8
id|EECSR
suffix:semicolon
DECL|member|EERdData
r_volatile
id|u16
id|EERdData
suffix:semicolon
multiline_comment|/* 0x94 */
DECL|member|EADDR
r_volatile
id|u8
id|EADDR
suffix:semicolon
DECL|member|EMBCMD
r_volatile
id|u8
id|EMBCMD
suffix:semicolon
DECL|member|JMPSR0
r_volatile
id|u8
id|JMPSR0
suffix:semicolon
multiline_comment|/* 0x98 */
DECL|member|JMPSR1
r_volatile
id|u8
id|JMPSR1
suffix:semicolon
DECL|member|JMPSR2
r_volatile
id|u8
id|JMPSR2
suffix:semicolon
DECL|member|JMPSR3
r_volatile
id|u8
id|JMPSR3
suffix:semicolon
DECL|member|CHIPGSR
r_volatile
id|u8
id|CHIPGSR
suffix:semicolon
multiline_comment|/* 0x9C */
DECL|member|TESTCFG
r_volatile
id|u8
id|TESTCFG
suffix:semicolon
DECL|member|DEBUG
r_volatile
id|u8
id|DEBUG
suffix:semicolon
DECL|member|CHIPGCR
r_volatile
id|u8
id|CHIPGCR
suffix:semicolon
DECL|member|WOLCRSet
r_volatile
id|u16
id|WOLCRSet
suffix:semicolon
multiline_comment|/* 0xA0 */
DECL|member|PWCFGSet
r_volatile
id|u8
id|PWCFGSet
suffix:semicolon
DECL|member|WOLCFGSet
r_volatile
id|u8
id|WOLCFGSet
suffix:semicolon
DECL|member|WOLCRClr
r_volatile
id|u16
id|WOLCRClr
suffix:semicolon
multiline_comment|/* 0xA4 */
DECL|member|PWCFGCLR
r_volatile
id|u8
id|PWCFGCLR
suffix:semicolon
DECL|member|WOLCFGClr
r_volatile
id|u8
id|WOLCFGClr
suffix:semicolon
DECL|member|WOLSRSet
r_volatile
id|u16
id|WOLSRSet
suffix:semicolon
multiline_comment|/* 0xA8 */
DECL|member|reserved_AA
r_volatile
id|u16
id|reserved_AA
suffix:semicolon
DECL|member|WOLSRClr
r_volatile
id|u16
id|WOLSRClr
suffix:semicolon
multiline_comment|/* 0xAC */
DECL|member|reserved_AE
r_volatile
id|u16
id|reserved_AE
suffix:semicolon
DECL|member|PatternCRC
r_volatile
id|u16
id|PatternCRC
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0xB0 */
DECL|member|ByteMask
r_volatile
id|u32
id|ByteMask
(braket
l_int|4
)braket
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0xC0 */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|enum|hw_mib
r_enum
id|hw_mib
(brace
DECL|enumerator|HW_MIB_ifRxAllPkts
id|HW_MIB_ifRxAllPkts
op_assign
l_int|0
comma
DECL|enumerator|HW_MIB_ifRxOkPkts
id|HW_MIB_ifRxOkPkts
comma
DECL|enumerator|HW_MIB_ifTxOkPkts
id|HW_MIB_ifTxOkPkts
comma
DECL|enumerator|HW_MIB_ifRxErrorPkts
id|HW_MIB_ifRxErrorPkts
comma
DECL|enumerator|HW_MIB_ifRxRuntOkPkt
id|HW_MIB_ifRxRuntOkPkt
comma
DECL|enumerator|HW_MIB_ifRxRuntErrPkt
id|HW_MIB_ifRxRuntErrPkt
comma
DECL|enumerator|HW_MIB_ifRx64Pkts
id|HW_MIB_ifRx64Pkts
comma
DECL|enumerator|HW_MIB_ifTx64Pkts
id|HW_MIB_ifTx64Pkts
comma
DECL|enumerator|HW_MIB_ifRx65To127Pkts
id|HW_MIB_ifRx65To127Pkts
comma
DECL|enumerator|HW_MIB_ifTx65To127Pkts
id|HW_MIB_ifTx65To127Pkts
comma
DECL|enumerator|HW_MIB_ifRx128To255Pkts
id|HW_MIB_ifRx128To255Pkts
comma
DECL|enumerator|HW_MIB_ifTx128To255Pkts
id|HW_MIB_ifTx128To255Pkts
comma
DECL|enumerator|HW_MIB_ifRx256To511Pkts
id|HW_MIB_ifRx256To511Pkts
comma
DECL|enumerator|HW_MIB_ifTx256To511Pkts
id|HW_MIB_ifTx256To511Pkts
comma
DECL|enumerator|HW_MIB_ifRx512To1023Pkts
id|HW_MIB_ifRx512To1023Pkts
comma
DECL|enumerator|HW_MIB_ifTx512To1023Pkts
id|HW_MIB_ifTx512To1023Pkts
comma
DECL|enumerator|HW_MIB_ifRx1024To1518Pkts
id|HW_MIB_ifRx1024To1518Pkts
comma
DECL|enumerator|HW_MIB_ifTx1024To1518Pkts
id|HW_MIB_ifTx1024To1518Pkts
comma
DECL|enumerator|HW_MIB_ifTxEtherCollisions
id|HW_MIB_ifTxEtherCollisions
comma
DECL|enumerator|HW_MIB_ifRxPktCRCE
id|HW_MIB_ifRxPktCRCE
comma
DECL|enumerator|HW_MIB_ifRxJumboPkts
id|HW_MIB_ifRxJumboPkts
comma
DECL|enumerator|HW_MIB_ifTxJumboPkts
id|HW_MIB_ifTxJumboPkts
comma
DECL|enumerator|HW_MIB_ifRxMacControlFrames
id|HW_MIB_ifRxMacControlFrames
comma
DECL|enumerator|HW_MIB_ifTxMacControlFrames
id|HW_MIB_ifTxMacControlFrames
comma
DECL|enumerator|HW_MIB_ifRxPktFAE
id|HW_MIB_ifRxPktFAE
comma
DECL|enumerator|HW_MIB_ifRxLongOkPkt
id|HW_MIB_ifRxLongOkPkt
comma
DECL|enumerator|HW_MIB_ifRxLongPktErrPkt
id|HW_MIB_ifRxLongPktErrPkt
comma
DECL|enumerator|HW_MIB_ifTXSQEErrors
id|HW_MIB_ifTXSQEErrors
comma
DECL|enumerator|HW_MIB_ifRxNobuf
id|HW_MIB_ifRxNobuf
comma
DECL|enumerator|HW_MIB_ifRxSymbolErrors
id|HW_MIB_ifRxSymbolErrors
comma
DECL|enumerator|HW_MIB_ifInRangeLengthErrors
id|HW_MIB_ifInRangeLengthErrors
comma
DECL|enumerator|HW_MIB_ifLateCollisions
id|HW_MIB_ifLateCollisions
comma
DECL|enumerator|HW_MIB_SIZE
id|HW_MIB_SIZE
)brace
suffix:semicolon
DECL|enum|chip_type
r_enum
id|chip_type
(brace
DECL|enumerator|CHIP_TYPE_VT6110
id|CHIP_TYPE_VT6110
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|struct|velocity_info_tbl
r_struct
id|velocity_info_tbl
(brace
DECL|member|chip_id
r_enum
id|chip_type
id|chip_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|io_size
r_int
id|io_size
suffix:semicolon
DECL|member|txqueue
r_int
id|txqueue
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|mac_hw_mibs_init
mdefine_line|#define mac_hw_mibs_init(regs) {&bslash;&n;&t;BYTE_REG_BITS_ON(MIBCR_MIBFRZ,&amp;((regs)-&gt;MIBCR));&bslash;&n;&t;BYTE_REG_BITS_ON(MIBCR_MIBCLR,&amp;((regs)-&gt;MIBCR));&bslash;&n;&t;do {}&bslash;&n;&t;&t;while (BYTE_REG_BITS_IS_ON(MIBCR_MIBCLR,&amp;((regs)-&gt;MIBCR)));&bslash;&n;&t;BYTE_REG_BITS_OFF(MIBCR_MIBFRZ,&amp;((regs)-&gt;MIBCR));&bslash;&n;}
DECL|macro|mac_read_isr
mdefine_line|#define mac_read_isr(regs)  &t;&t;readl(&amp;((regs)-&gt;ISR))
DECL|macro|mac_write_isr
mdefine_line|#define mac_write_isr(regs, x)  &t;writel((x),&amp;((regs)-&gt;ISR))
DECL|macro|mac_clear_isr
mdefine_line|#define mac_clear_isr(regs) &t;&t;writel(0xffffffffL,&amp;((regs)-&gt;ISR))
DECL|macro|mac_write_int_mask
mdefine_line|#define mac_write_int_mask(mask, regs) &t;writel((mask),&amp;((regs)-&gt;IMR));
DECL|macro|mac_disable_int
mdefine_line|#define mac_disable_int(regs)       &t;writel(CR0_GINTMSK1,&amp;((regs)-&gt;CR0Clr))
DECL|macro|mac_enable_int
mdefine_line|#define mac_enable_int(regs)    &t;writel(CR0_GINTMSK1,&amp;((regs)-&gt;CR0Set))
DECL|macro|mac_hw_mibs_read
mdefine_line|#define mac_hw_mibs_read(regs, MIBs) {&bslash;&n;&t;int i;&bslash;&n;&t;BYTE_REG_BITS_ON(MIBCR_MPTRINI,&amp;((regs)-&gt;MIBCR));&bslash;&n;&t;for (i=0;i&lt;HW_MIB_SIZE;i++) {&bslash;&n;&t;&t;(MIBs)[i]=readl(&amp;((regs)-&gt;MIBData));&bslash;&n;&t;}&bslash;&n;}
DECL|macro|mac_set_dma_length
mdefine_line|#define mac_set_dma_length(regs, n) {&bslash;&n;&t;BYTE_REG_BITS_SET((n),0x07,&amp;((regs)-&gt;DCFG));&bslash;&n;}
DECL|macro|mac_set_rx_thresh
mdefine_line|#define mac_set_rx_thresh(regs, n) {&bslash;&n;&t;BYTE_REG_BITS_SET((n),(MCFG_RFT0|MCFG_RFT1),&amp;((regs)-&gt;MCFG));&bslash;&n;}
DECL|macro|mac_rx_queue_run
mdefine_line|#define mac_rx_queue_run(regs) {&bslash;&n;&t;writeb(TRDCSR_RUN, &amp;((regs)-&gt;RDCSRSet));&bslash;&n;}
DECL|macro|mac_rx_queue_wake
mdefine_line|#define mac_rx_queue_wake(regs) {&bslash;&n;&t;writeb(TRDCSR_WAK, &amp;((regs)-&gt;RDCSRSet));&bslash;&n;}
DECL|macro|mac_tx_queue_run
mdefine_line|#define mac_tx_queue_run(regs, n) {&bslash;&n;&t;writew(TRDCSR_RUN&lt;&lt;((n)*4),&amp;((regs)-&gt;TDCSRSet));&bslash;&n;}
DECL|macro|mac_tx_queue_wake
mdefine_line|#define mac_tx_queue_wake(regs, n) {&bslash;&n;&t;writew(TRDCSR_WAK&lt;&lt;(n*4),&amp;((regs)-&gt;TDCSRSet));&bslash;&n;}
DECL|macro|mac_eeprom_reload
mdefine_line|#define mac_eeprom_reload(regs) {&bslash;&n;&t;int i=0;&bslash;&n;&t;BYTE_REG_BITS_ON(EECSR_RELOAD,&amp;((regs)-&gt;EECSR));&bslash;&n;&t;do {&bslash;&n;&t;&t;udelay(10);&bslash;&n;&t;&t;if (i++&gt;0x1000) {&bslash;&n;&t;&t;&t;break;&bslash;&n;&t;&t;}&bslash;&n;&t;}while (BYTE_REG_BITS_IS_ON(EECSR_RELOAD,&amp;((regs)-&gt;EECSR)));&bslash;&n;}
DECL|enum|velocity_cam_type
r_enum
id|velocity_cam_type
(brace
DECL|enumerator|VELOCITY_VLAN_ID_CAM
id|VELOCITY_VLAN_ID_CAM
op_assign
l_int|0
comma
DECL|enumerator|VELOCITY_MULTICAST_CAM
id|VELOCITY_MULTICAST_CAM
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;mac_get_cam_mask&t;-&t;Read a CAM mask&n; *&t;@regs: register block for this velocity&n; *&t;@mask: buffer to store mask&n; *&t;@cam_type: CAM to fetch&n; *&n; *&t;Fetch the mask bits of the selected CAM and store them into the&n; *&t;provided mask buffer.&n; */
DECL|function|mac_get_cam_mask
r_static
r_inline
r_void
id|mac_get_cam_mask
c_func
(paren
r_struct
id|mac_regs
id|__iomem
op_star
id|regs
comma
id|u8
op_star
id|mask
comma
r_enum
id|velocity_cam_type
id|cam_type
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Select CAM mask */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_CAM_MASK
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cam_type
op_eq
id|VELOCITY_VLAN_ID_CAM
)paren
id|writeb
c_func
(paren
id|CAMADDR_VCAMSL
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
r_else
id|writeb
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
multiline_comment|/* read mask */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
op_star
id|mask
op_increment
op_assign
id|readb
c_func
(paren
op_amp
(paren
id|regs-&gt;MARCAM
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* disable CAMEN */
id|writeb
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
multiline_comment|/* Select mar */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_MAR
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mac_set_cam_mask&t;-&t;Set a CAM mask&n; *&t;@regs: register block for this velocity&n; *&t;@mask: CAM mask to load&n; *&t;@cam_type: CAM to store&n; *&n; *&t;Store a new mask into a CAM&n; */
DECL|function|mac_set_cam_mask
r_static
r_inline
r_void
id|mac_set_cam_mask
c_func
(paren
r_struct
id|mac_regs
id|__iomem
op_star
id|regs
comma
id|u8
op_star
id|mask
comma
r_enum
id|velocity_cam_type
id|cam_type
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Select CAM mask */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_CAM_MASK
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cam_type
op_eq
id|VELOCITY_VLAN_ID_CAM
)paren
id|writeb
c_func
(paren
id|CAMADDR_CAMEN
op_or
id|CAMADDR_VCAMSL
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
r_else
id|writeb
c_func
(paren
id|CAMADDR_CAMEN
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writeb
c_func
(paren
op_star
id|mask
op_increment
comma
op_amp
(paren
id|regs-&gt;MARCAM
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* disable CAMEN */
id|writeb
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
multiline_comment|/* Select mar */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_MAR
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mac_set_cam&t;-&t;set CAM data&n; *&t;@regs: register block of this velocity&n; *&t;@idx: Cam index&n; *&t;@addr: 2 or 6 bytes of CAM data&n; *&t;@cam_type: CAM to load&n; *&n; *&t;Load an address or vlan tag into a CAM&n; */
DECL|function|mac_set_cam
r_static
r_inline
r_void
id|mac_set_cam
c_func
(paren
r_struct
id|mac_regs
id|__iomem
op_star
id|regs
comma
r_int
id|idx
comma
id|u8
op_star
id|addr
comma
r_enum
id|velocity_cam_type
id|cam_type
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Select CAM mask */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_CAM_DATA
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
id|idx
op_and_assign
(paren
l_int|64
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cam_type
op_eq
id|VELOCITY_VLAN_ID_CAM
)paren
id|writeb
c_func
(paren
id|CAMADDR_CAMEN
op_or
id|CAMADDR_VCAMSL
op_or
id|idx
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
r_else
id|writeb
c_func
(paren
id|CAMADDR_CAMEN
op_or
id|idx
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cam_type
op_eq
id|VELOCITY_VLAN_ID_CAM
)paren
id|writew
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
comma
op_amp
id|regs-&gt;MARCAM
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writeb
c_func
(paren
op_star
id|addr
op_increment
comma
op_amp
(paren
id|regs-&gt;MARCAM
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
)brace
id|BYTE_REG_BITS_ON
c_func
(paren
id|CAMCR_CAMWR
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
multiline_comment|/* Select mar */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_MAR
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mac_get_cam&t;-&t;fetch CAM data&n; *&t;@regs: register block of this velocity&n; *&t;@idx: Cam index&n; *&t;@addr: buffer to hold up to 6 bytes of CAM data&n; *&t;@cam_type: CAM to load&n; *&n; *&t;Load an address or vlan tag from a CAM into the buffer provided by&n; *&t;the caller. VLAN tags are 2 bytes the address cam entries are 6.&n; */
DECL|function|mac_get_cam
r_static
r_inline
r_void
id|mac_get_cam
c_func
(paren
r_struct
id|mac_regs
id|__iomem
op_star
id|regs
comma
r_int
id|idx
comma
id|u8
op_star
id|addr
comma
r_enum
id|velocity_cam_type
id|cam_type
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Select CAM mask */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_CAM_DATA
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
id|idx
op_and_assign
(paren
l_int|64
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cam_type
op_eq
id|VELOCITY_VLAN_ID_CAM
)paren
id|writeb
c_func
(paren
id|CAMADDR_CAMEN
op_or
id|CAMADDR_VCAMSL
op_or
id|idx
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
r_else
id|writeb
c_func
(paren
id|CAMADDR_CAMEN
op_or
id|idx
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
id|BYTE_REG_BITS_ON
c_func
(paren
id|CAMCR_CAMRD
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cam_type
op_eq
id|VELOCITY_VLAN_ID_CAM
)paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
op_assign
id|readw
c_func
(paren
op_amp
(paren
id|regs-&gt;MARCAM
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
comma
id|addr
op_increment
)paren
op_star
(paren
(paren
id|u8
op_star
)paren
id|addr
)paren
op_assign
id|readb
c_func
(paren
op_amp
(paren
id|regs-&gt;MARCAM
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
op_amp
id|regs-&gt;CAMADDR
)paren
suffix:semicolon
multiline_comment|/* Select mar */
id|BYTE_REG_BITS_SET
c_func
(paren
id|CAMCR_PS_MAR
comma
id|CAMCR_PS1
op_or
id|CAMCR_PS0
comma
op_amp
id|regs-&gt;CAMCR
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mac_wol_reset&t;-&t;reset WOL after exiting low power&n; *&t;@regs: register block of this velocity&n; *&n; *&t;Called after we drop out of wake on lan mode in order to&n; *&t;reset the Wake on lan features. This function doesn&squot;t restore&n; *&t;the rest of the logic from the result of sleep/wakeup&n; */
DECL|function|mac_wol_reset
r_inline
r_static
r_void
id|mac_wol_reset
c_func
(paren
r_struct
id|mac_regs
id|__iomem
op_star
id|regs
)paren
(brace
multiline_comment|/* Turn off SWPTAG right after leaving power mode */
id|BYTE_REG_BITS_OFF
c_func
(paren
id|STICKHW_SWPTAG
comma
op_amp
id|regs-&gt;STICKHW
)paren
suffix:semicolon
multiline_comment|/* clear sticky bits */
id|BYTE_REG_BITS_OFF
c_func
(paren
(paren
id|STICKHW_DS1
op_or
id|STICKHW_DS0
)paren
comma
op_amp
id|regs-&gt;STICKHW
)paren
suffix:semicolon
id|BYTE_REG_BITS_OFF
c_func
(paren
id|CHIPGCR_FCGMII
comma
op_amp
id|regs-&gt;CHIPGCR
)paren
suffix:semicolon
id|BYTE_REG_BITS_OFF
c_func
(paren
id|CHIPGCR_FCMODE
comma
op_amp
id|regs-&gt;CHIPGCR
)paren
suffix:semicolon
multiline_comment|/* disable force PME-enable */
id|writeb
c_func
(paren
id|WOLCFG_PMEOVR
comma
op_amp
id|regs-&gt;WOLCFGClr
)paren
suffix:semicolon
multiline_comment|/* disable power-event config bit */
id|writew
c_func
(paren
l_int|0xFFFF
comma
op_amp
id|regs-&gt;WOLCRClr
)paren
suffix:semicolon
multiline_comment|/* clear power status */
id|writew
c_func
(paren
l_int|0xFFFF
comma
op_amp
id|regs-&gt;WOLSRClr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Header for WOL definitions. Used to compute hashes&n; */
DECL|typedef|MCAM_ADDR
r_typedef
id|u8
id|MCAM_ADDR
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|struct|arp_packet
r_struct
id|arp_packet
(brace
DECL|member|dest_mac
id|u8
id|dest_mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|src_mac
id|u8
id|src_mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|ar_hrd
id|u16
id|ar_hrd
suffix:semicolon
DECL|member|ar_pro
id|u16
id|ar_pro
suffix:semicolon
DECL|member|ar_hln
id|u8
id|ar_hln
suffix:semicolon
DECL|member|ar_pln
id|u8
id|ar_pln
suffix:semicolon
DECL|member|ar_op
id|u16
id|ar_op
suffix:semicolon
DECL|member|ar_sha
id|u8
id|ar_sha
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ar_sip
id|u8
id|ar_sip
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|ar_tha
id|u8
id|ar_tha
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ar_tip
id|u8
id|ar_tip
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|struct|_magic_packet
r_struct
id|_magic_packet
(brace
DECL|member|dest_mac
id|u8
id|dest_mac
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|src_mac
id|u8
id|src_mac
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|MAC
id|u8
id|MAC
(braket
l_int|16
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|password
id|u8
id|password
(braket
l_int|6
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Store for chip context when saving and restoring status. Not&n; *&t;all fields are saved/restored currently.&n; */
DECL|struct|velocity_context
r_struct
id|velocity_context
(brace
DECL|member|mac_reg
id|u8
id|mac_reg
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|cam_addr
id|MCAM_ADDR
id|cam_addr
(braket
id|MCAM_SIZE
)braket
suffix:semicolon
DECL|member|vcam
id|u16
id|vcam
(braket
id|VCAM_SIZE
)braket
suffix:semicolon
DECL|member|cammask
id|u32
id|cammask
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|patcrc
id|u32
id|patcrc
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pattern
id|u32
id|pattern
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;MII registers.&n; */
multiline_comment|/*&n; *&t;Registers in the MII (offset unit is WORD)&n; */
DECL|macro|MII_REG_BMCR
mdefine_line|#define MII_REG_BMCR        0x00&t;
singleline_comment|// physical address
DECL|macro|MII_REG_BMSR
mdefine_line|#define MII_REG_BMSR        0x01&t;
singleline_comment|//
DECL|macro|MII_REG_PHYID1
mdefine_line|#define MII_REG_PHYID1      0x02&t;
singleline_comment|// OUI
DECL|macro|MII_REG_PHYID2
mdefine_line|#define MII_REG_PHYID2      0x03&t;
singleline_comment|// OUI + Module ID + REV ID
DECL|macro|MII_REG_ANAR
mdefine_line|#define MII_REG_ANAR        0x04&t;
singleline_comment|//
DECL|macro|MII_REG_ANLPAR
mdefine_line|#define MII_REG_ANLPAR      0x05&t;
singleline_comment|//
DECL|macro|MII_REG_G1000CR
mdefine_line|#define MII_REG_G1000CR     0x09&t;
singleline_comment|//
DECL|macro|MII_REG_G1000SR
mdefine_line|#define MII_REG_G1000SR     0x0A&t;
singleline_comment|//
DECL|macro|MII_REG_MODCFG
mdefine_line|#define MII_REG_MODCFG      0x10&t;
singleline_comment|//
DECL|macro|MII_REG_TCSR
mdefine_line|#define MII_REG_TCSR        0x16&t;
singleline_comment|//
DECL|macro|MII_REG_PLED
mdefine_line|#define MII_REG_PLED        0x1B&t;
singleline_comment|//
singleline_comment|// NS, MYSON only
DECL|macro|MII_REG_PCR
mdefine_line|#define MII_REG_PCR         0x17&t;
singleline_comment|//
singleline_comment|// ESI only
DECL|macro|MII_REG_PCSR
mdefine_line|#define MII_REG_PCSR        0x17&t;
singleline_comment|//
DECL|macro|MII_REG_AUXCR
mdefine_line|#define MII_REG_AUXCR       0x1C&t;
singleline_comment|//
singleline_comment|// Marvell 88E1000/88E1000S
DECL|macro|MII_REG_PSCR
mdefine_line|#define MII_REG_PSCR        0x10&t;
singleline_comment|// PHY specific control register
singleline_comment|//
singleline_comment|// Bits in the BMCR register
singleline_comment|//
DECL|macro|BMCR_RESET
mdefine_line|#define BMCR_RESET          0x8000&t;
singleline_comment|//
DECL|macro|BMCR_LBK
mdefine_line|#define BMCR_LBK            0x4000&t;
singleline_comment|//
DECL|macro|BMCR_SPEED100
mdefine_line|#define BMCR_SPEED100       0x2000&t;
singleline_comment|//
DECL|macro|BMCR_AUTO
mdefine_line|#define BMCR_AUTO           0x1000&t;
singleline_comment|//
DECL|macro|BMCR_PD
mdefine_line|#define BMCR_PD             0x0800&t;
singleline_comment|//
DECL|macro|BMCR_ISO
mdefine_line|#define BMCR_ISO            0x0400&t;
singleline_comment|//
DECL|macro|BMCR_REAUTO
mdefine_line|#define BMCR_REAUTO         0x0200&t;
singleline_comment|//
DECL|macro|BMCR_FDX
mdefine_line|#define BMCR_FDX            0x0100&t;
singleline_comment|//
DECL|macro|BMCR_SPEED1G
mdefine_line|#define BMCR_SPEED1G        0x0040&t;
singleline_comment|//
singleline_comment|//
singleline_comment|// Bits in the BMSR register
singleline_comment|//
DECL|macro|BMSR_AUTOCM
mdefine_line|#define BMSR_AUTOCM         0x0020&t;
singleline_comment|//
DECL|macro|BMSR_LNK
mdefine_line|#define BMSR_LNK            0x0004&t;
singleline_comment|//
singleline_comment|//
singleline_comment|// Bits in the ANAR register
singleline_comment|//
DECL|macro|ANAR_ASMDIR
mdefine_line|#define ANAR_ASMDIR         0x0800&t;
singleline_comment|// Asymmetric PAUSE support
DECL|macro|ANAR_PAUSE
mdefine_line|#define ANAR_PAUSE          0x0400&t;
singleline_comment|// Symmetric PAUSE Support
DECL|macro|ANAR_T4
mdefine_line|#define ANAR_T4             0x0200&t;
singleline_comment|//
DECL|macro|ANAR_TXFD
mdefine_line|#define ANAR_TXFD           0x0100&t;
singleline_comment|//
DECL|macro|ANAR_TX
mdefine_line|#define ANAR_TX             0x0080&t;
singleline_comment|//
DECL|macro|ANAR_10FD
mdefine_line|#define ANAR_10FD           0x0040&t;
singleline_comment|//
DECL|macro|ANAR_10
mdefine_line|#define ANAR_10             0x0020&t;
singleline_comment|//
singleline_comment|//
singleline_comment|// Bits in the ANLPAR register
singleline_comment|//
DECL|macro|ANLPAR_ASMDIR
mdefine_line|#define ANLPAR_ASMDIR       0x0800&t;
singleline_comment|// Asymmetric PAUSE support
DECL|macro|ANLPAR_PAUSE
mdefine_line|#define ANLPAR_PAUSE        0x0400&t;
singleline_comment|// Symmetric PAUSE Support
DECL|macro|ANLPAR_T4
mdefine_line|#define ANLPAR_T4           0x0200&t;
singleline_comment|//
DECL|macro|ANLPAR_TXFD
mdefine_line|#define ANLPAR_TXFD         0x0100&t;
singleline_comment|//
DECL|macro|ANLPAR_TX
mdefine_line|#define ANLPAR_TX           0x0080&t;
singleline_comment|//
DECL|macro|ANLPAR_10FD
mdefine_line|#define ANLPAR_10FD         0x0040&t;
singleline_comment|//
DECL|macro|ANLPAR_10
mdefine_line|#define ANLPAR_10           0x0020&t;
singleline_comment|//
singleline_comment|//
singleline_comment|// Bits in the G1000CR register
singleline_comment|//
DECL|macro|G1000CR_1000FD
mdefine_line|#define G1000CR_1000FD      0x0200&t;
singleline_comment|// PHY is 1000-T Full-duplex capable
DECL|macro|G1000CR_1000
mdefine_line|#define G1000CR_1000        0x0100&t;
singleline_comment|// PHY is 1000-T Half-duplex capable
singleline_comment|//
singleline_comment|// Bits in the G1000SR register
singleline_comment|//
DECL|macro|G1000SR_1000FD
mdefine_line|#define G1000SR_1000FD      0x0800&t;
singleline_comment|// LP PHY is 1000-T Full-duplex capable
DECL|macro|G1000SR_1000
mdefine_line|#define G1000SR_1000        0x0400&t;
singleline_comment|// LP PHY is 1000-T Half-duplex capable
DECL|macro|TCSR_ECHODIS
mdefine_line|#define TCSR_ECHODIS        0x2000&t;
singleline_comment|//
DECL|macro|AUXCR_MDPPS
mdefine_line|#define AUXCR_MDPPS         0x0004&t;
singleline_comment|//
singleline_comment|// Bits in the PLED register
DECL|macro|PLED_LALBE
mdefine_line|#define PLED_LALBE&t;&t;&t;0x0004&t;
singleline_comment|//
singleline_comment|// Marvell 88E1000/88E1000S Bits in the PHY specific control register (10h)
DECL|macro|PSCR_ACRSTX
mdefine_line|#define PSCR_ACRSTX         0x0800&t;
singleline_comment|// Assert CRS on Transmit
DECL|macro|PHYID_CICADA_CS8201
mdefine_line|#define PHYID_CICADA_CS8201 0x000FC410UL
DECL|macro|PHYID_VT3216_32BIT
mdefine_line|#define PHYID_VT3216_32BIT  0x000FC610UL
DECL|macro|PHYID_VT3216_64BIT
mdefine_line|#define PHYID_VT3216_64BIT  0x000FC600UL
DECL|macro|PHYID_MARVELL_1000
mdefine_line|#define PHYID_MARVELL_1000  0x01410C50UL
DECL|macro|PHYID_MARVELL_1000S
mdefine_line|#define PHYID_MARVELL_1000S 0x01410C40UL
DECL|macro|PHYID_REV_ID_MASK
mdefine_line|#define PHYID_REV_ID_MASK   0x0000000FUL
DECL|macro|PHYID_GET_PHY_REV_ID
mdefine_line|#define PHYID_GET_PHY_REV_ID(i)     ((i) &amp; PHYID_REV_ID_MASK)
DECL|macro|PHYID_GET_PHY_ID
mdefine_line|#define PHYID_GET_PHY_ID(i)         ((i) &amp; ~PHYID_REV_ID_MASK)
DECL|macro|MII_REG_BITS_ON
mdefine_line|#define MII_REG_BITS_ON(x,i,p) do {&bslash;&n;    u16 w;&bslash;&n;    velocity_mii_read((p),(i),&amp;(w));&bslash;&n;    (w)|=(x);&bslash;&n;    velocity_mii_write((p),(i),(w));&bslash;&n;} while (0)
DECL|macro|MII_REG_BITS_OFF
mdefine_line|#define MII_REG_BITS_OFF(x,i,p) do {&bslash;&n;    u16 w;&bslash;&n;    velocity_mii_read((p),(i),&amp;(w));&bslash;&n;    (w)&amp;=(~(x));&bslash;&n;    velocity_mii_write((p),(i),(w));&bslash;&n;} while (0)
DECL|macro|MII_REG_BITS_IS_ON
mdefine_line|#define MII_REG_BITS_IS_ON(x,i,p) ({&bslash;&n;    u16 w;&bslash;&n;    velocity_mii_read((p),(i),&amp;(w));&bslash;&n;    ((int) ((w) &amp; (x)));})
DECL|macro|MII_GET_PHY_ID
mdefine_line|#define MII_GET_PHY_ID(p) ({&bslash;&n;    u32 id;&bslash;&n;    velocity_mii_read((p),MII_REG_PHYID2,(u16 *) &amp;id);&bslash;&n;    velocity_mii_read((p),MII_REG_PHYID1,((u16 *) &amp;id)+1);&bslash;&n;    (id);})
multiline_comment|/*&n; * Inline debug routine&n; */
DECL|enum|velocity_msg_level
r_enum
id|velocity_msg_level
(brace
DECL|enumerator|MSG_LEVEL_ERR
id|MSG_LEVEL_ERR
op_assign
l_int|0
comma
singleline_comment|//Errors that will cause abnormal operation.
DECL|enumerator|MSG_LEVEL_NOTICE
id|MSG_LEVEL_NOTICE
op_assign
l_int|1
comma
singleline_comment|//Some errors need users to be notified.
DECL|enumerator|MSG_LEVEL_INFO
id|MSG_LEVEL_INFO
op_assign
l_int|2
comma
singleline_comment|//Normal message.
DECL|enumerator|MSG_LEVEL_VERBOSE
id|MSG_LEVEL_VERBOSE
op_assign
l_int|3
comma
singleline_comment|//Will report all trival errors.
DECL|enumerator|MSG_LEVEL_DEBUG
id|MSG_LEVEL_DEBUG
op_assign
l_int|4
singleline_comment|//Only for debug purpose.
)brace
suffix:semicolon
macro_line|#ifdef VELOCITY_DEBUG
DECL|macro|ASSERT
mdefine_line|#define ASSERT(x) { &bslash;&n;&t;if (!(x)) { &bslash;&n;&t;&t;printk(KERN_ERR &quot;assertion %s failed: file %s line %d&bslash;n&quot;, #x,&bslash;&n;&t;&t;&t;__FUNCTION__, __LINE__);&bslash;&n;&t;&t;BUG(); &bslash;&n;&t;}&bslash;&n;}
DECL|macro|VELOCITY_DBG
mdefine_line|#define VELOCITY_DBG(p,args...) printk(p, ##args)
macro_line|#else
DECL|macro|ASSERT
mdefine_line|#define ASSERT(x)
DECL|macro|VELOCITY_DBG
mdefine_line|#define VELOCITY_DBG(x)
macro_line|#endif
DECL|macro|VELOCITY_PRT
mdefine_line|#define VELOCITY_PRT(l, p, args...) do {if (l&lt;=msglevel) printk( p ,##args);} while (0)
DECL|macro|VELOCITY_PRT_CAMMASK
mdefine_line|#define VELOCITY_PRT_CAMMASK(p,t) {&bslash;&n;&t;int i;&bslash;&n;&t;if ((t)==VELOCITY_MULTICAST_CAM) {&bslash;&n;        &t;for (i=0;i&lt;(MCAM_SIZE/8);i++)&bslash;&n;&t;&t;&t;printk(&quot;%02X&quot;,(p)-&gt;mCAMmask[i]);&bslash;&n;&t;}&bslash;&n;&t;else {&bslash;&n;&t;&t;for (i=0;i&lt;(VCAM_SIZE/8);i++)&bslash;&n;&t;&t;&t;printk(&quot;%02X&quot;,(p)-&gt;vCAMmask[i]);&bslash;&n;&t;}&bslash;&n;&t;printk(&quot;&bslash;n&quot;);&bslash;&n;}
DECL|macro|VELOCITY_WOL_MAGIC
mdefine_line|#define     VELOCITY_WOL_MAGIC             0x00000000UL
DECL|macro|VELOCITY_WOL_PHY
mdefine_line|#define     VELOCITY_WOL_PHY               0x00000001UL
DECL|macro|VELOCITY_WOL_ARP
mdefine_line|#define     VELOCITY_WOL_ARP               0x00000002UL
DECL|macro|VELOCITY_WOL_UCAST
mdefine_line|#define     VELOCITY_WOL_UCAST             0x00000004UL
DECL|macro|VELOCITY_WOL_BCAST
mdefine_line|#define     VELOCITY_WOL_BCAST             0x00000010UL
DECL|macro|VELOCITY_WOL_MCAST
mdefine_line|#define     VELOCITY_WOL_MCAST             0x00000020UL
DECL|macro|VELOCITY_WOL_MAGIC_SEC
mdefine_line|#define     VELOCITY_WOL_MAGIC_SEC         0x00000040UL
multiline_comment|/*&n; *&t;Flags for options&n; */
DECL|macro|VELOCITY_FLAGS_TAGGING
mdefine_line|#define     VELOCITY_FLAGS_TAGGING         0x00000001UL
DECL|macro|VELOCITY_FLAGS_TX_CSUM
mdefine_line|#define     VELOCITY_FLAGS_TX_CSUM         0x00000002UL
DECL|macro|VELOCITY_FLAGS_RX_CSUM
mdefine_line|#define     VELOCITY_FLAGS_RX_CSUM         0x00000004UL
DECL|macro|VELOCITY_FLAGS_IP_ALIGN
mdefine_line|#define     VELOCITY_FLAGS_IP_ALIGN        0x00000008UL
DECL|macro|VELOCITY_FLAGS_VAL_PKT_LEN
mdefine_line|#define     VELOCITY_FLAGS_VAL_PKT_LEN     0x00000010UL
DECL|macro|VELOCITY_FLAGS_FLOW_CTRL
mdefine_line|#define     VELOCITY_FLAGS_FLOW_CTRL       0x01000000UL
multiline_comment|/*&n; *&t;Flags for driver status&n; */
DECL|macro|VELOCITY_FLAGS_OPENED
mdefine_line|#define     VELOCITY_FLAGS_OPENED          0x00010000UL
DECL|macro|VELOCITY_FLAGS_VMNS_CONNECTED
mdefine_line|#define     VELOCITY_FLAGS_VMNS_CONNECTED  0x00020000UL
DECL|macro|VELOCITY_FLAGS_VMNS_COMMITTED
mdefine_line|#define     VELOCITY_FLAGS_VMNS_COMMITTED  0x00040000UL
DECL|macro|VELOCITY_FLAGS_WOL_ENABLED
mdefine_line|#define     VELOCITY_FLAGS_WOL_ENABLED     0x00080000UL
multiline_comment|/*&n; *&t;Flags for MII status&n; */
DECL|macro|VELOCITY_LINK_FAIL
mdefine_line|#define     VELOCITY_LINK_FAIL             0x00000001UL
DECL|macro|VELOCITY_SPEED_10
mdefine_line|#define     VELOCITY_SPEED_10              0x00000002UL
DECL|macro|VELOCITY_SPEED_100
mdefine_line|#define     VELOCITY_SPEED_100             0x00000004UL
DECL|macro|VELOCITY_SPEED_1000
mdefine_line|#define     VELOCITY_SPEED_1000            0x00000008UL
DECL|macro|VELOCITY_DUPLEX_FULL
mdefine_line|#define     VELOCITY_DUPLEX_FULL           0x00000010UL
DECL|macro|VELOCITY_AUTONEG_ENABLE
mdefine_line|#define     VELOCITY_AUTONEG_ENABLE        0x00000020UL
DECL|macro|VELOCITY_FORCED_BY_EEPROM
mdefine_line|#define     VELOCITY_FORCED_BY_EEPROM      0x00000040UL
multiline_comment|/*&n; *&t;For velocity_set_media_duplex&n; */
DECL|macro|VELOCITY_LINK_CHANGE
mdefine_line|#define     VELOCITY_LINK_CHANGE           0x00000001UL
DECL|enum|speed_opt
r_enum
id|speed_opt
(brace
DECL|enumerator|SPD_DPX_AUTO
id|SPD_DPX_AUTO
op_assign
l_int|0
comma
DECL|enumerator|SPD_DPX_100_HALF
id|SPD_DPX_100_HALF
op_assign
l_int|1
comma
DECL|enumerator|SPD_DPX_100_FULL
id|SPD_DPX_100_FULL
op_assign
l_int|2
comma
DECL|enumerator|SPD_DPX_10_HALF
id|SPD_DPX_10_HALF
op_assign
l_int|3
comma
DECL|enumerator|SPD_DPX_10_FULL
id|SPD_DPX_10_FULL
op_assign
l_int|4
)brace
suffix:semicolon
DECL|enum|velocity_init_type
r_enum
id|velocity_init_type
(brace
DECL|enumerator|VELOCITY_INIT_COLD
id|VELOCITY_INIT_COLD
op_assign
l_int|0
comma
DECL|enumerator|VELOCITY_INIT_RESET
id|VELOCITY_INIT_RESET
comma
DECL|enumerator|VELOCITY_INIT_WOL
id|VELOCITY_INIT_WOL
)brace
suffix:semicolon
DECL|enum|velocity_flow_cntl_type
r_enum
id|velocity_flow_cntl_type
(brace
DECL|enumerator|FLOW_CNTL_DEFAULT
id|FLOW_CNTL_DEFAULT
op_assign
l_int|1
comma
DECL|enumerator|FLOW_CNTL_TX
id|FLOW_CNTL_TX
comma
DECL|enumerator|FLOW_CNTL_RX
id|FLOW_CNTL_RX
comma
DECL|enumerator|FLOW_CNTL_TX_RX
id|FLOW_CNTL_TX_RX
comma
DECL|enumerator|FLOW_CNTL_DISABLE
id|FLOW_CNTL_DISABLE
comma
)brace
suffix:semicolon
DECL|struct|velocity_opt
r_struct
id|velocity_opt
(brace
DECL|member|numrx
r_int
id|numrx
suffix:semicolon
multiline_comment|/* Number of RX descriptors */
DECL|member|numtx
r_int
id|numtx
suffix:semicolon
multiline_comment|/* Number of TX descriptors */
DECL|member|spd_dpx
r_enum
id|speed_opt
id|spd_dpx
suffix:semicolon
multiline_comment|/* Media link mode */
DECL|member|vid
r_int
id|vid
suffix:semicolon
multiline_comment|/* vlan id */
DECL|member|DMA_length
r_int
id|DMA_length
suffix:semicolon
multiline_comment|/* DMA length */
DECL|member|rx_thresh
r_int
id|rx_thresh
suffix:semicolon
multiline_comment|/* RX_THRESH */
DECL|member|flow_cntl
r_int
id|flow_cntl
suffix:semicolon
DECL|member|wol_opts
r_int
id|wol_opts
suffix:semicolon
multiline_comment|/* Wake on lan options */
DECL|member|td_int_count
r_int
id|td_int_count
suffix:semicolon
DECL|member|int_works
r_int
id|int_works
suffix:semicolon
DECL|member|rx_bandwidth_hi
r_int
id|rx_bandwidth_hi
suffix:semicolon
DECL|member|rx_bandwidth_lo
r_int
id|rx_bandwidth_lo
suffix:semicolon
DECL|member|rx_bandwidth_en
r_int
id|rx_bandwidth_en
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|velocity_info
r_struct
id|velocity_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|rd_pool_dma
id|dma_addr_t
id|rd_pool_dma
suffix:semicolon
DECL|member|td_pool_dma
id|dma_addr_t
id|td_pool_dma
(braket
id|TX_QUEUE_NO
)braket
suffix:semicolon
DECL|member|tx_bufs_dma
id|dma_addr_t
id|tx_bufs_dma
suffix:semicolon
DECL|member|tx_bufs
id|u8
op_star
id|tx_bufs
suffix:semicolon
DECL|member|ip_addr
id|u8
id|ip_addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|chip_id
r_enum
id|chip_type
id|chip_id
suffix:semicolon
DECL|member|mac_regs
r_struct
id|mac_regs
id|__iomem
op_star
id|mac_regs
suffix:semicolon
DECL|member|memaddr
r_int
r_int
id|memaddr
suffix:semicolon
DECL|member|ioaddr
r_int
r_int
id|ioaddr
suffix:semicolon
DECL|member|io_size
id|u32
id|io_size
suffix:semicolon
DECL|member|rev_id
id|u8
id|rev_id
suffix:semicolon
DECL|macro|AVAIL_TD
mdefine_line|#define AVAIL_TD(p,q)   ((p)-&gt;options.numtx-((p)-&gt;td_used[(q)]))
DECL|member|num_txq
r_int
id|num_txq
suffix:semicolon
DECL|member|td_used
r_volatile
r_int
id|td_used
(braket
id|TX_QUEUE_NO
)braket
suffix:semicolon
DECL|member|td_curr
r_int
id|td_curr
(braket
id|TX_QUEUE_NO
)braket
suffix:semicolon
DECL|member|td_tail
r_int
id|td_tail
(braket
id|TX_QUEUE_NO
)braket
suffix:semicolon
DECL|member|td_rings
r_struct
id|tx_desc
op_star
id|td_rings
(braket
id|TX_QUEUE_NO
)braket
suffix:semicolon
DECL|member|td_infos
r_struct
id|velocity_td_info
op_star
id|td_infos
(braket
id|TX_QUEUE_NO
)braket
suffix:semicolon
DECL|member|rd_curr
r_int
id|rd_curr
suffix:semicolon
DECL|member|rd_dirty
r_int
id|rd_dirty
suffix:semicolon
DECL|member|rd_filled
id|u32
id|rd_filled
suffix:semicolon
DECL|member|rd_ring
r_struct
id|rx_desc
op_star
id|rd_ring
suffix:semicolon
DECL|member|rd_info
r_struct
id|velocity_rd_info
op_star
id|rd_info
suffix:semicolon
multiline_comment|/* It&squot;s an array */
DECL|macro|GET_RD_BY_IDX
mdefine_line|#define GET_RD_BY_IDX(vptr, idx)   (vptr-&gt;rd_ring[idx])
DECL|member|mib_counter
id|u32
id|mib_counter
(braket
id|MAX_HW_MIB_COUNTER
)braket
suffix:semicolon
DECL|member|options
r_struct
id|velocity_opt
id|options
suffix:semicolon
DECL|member|int_mask
id|u32
id|int_mask
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|rx_buf_sz
r_int
id|rx_buf_sz
suffix:semicolon
DECL|member|mii_status
id|u32
id|mii_status
suffix:semicolon
DECL|member|phy_id
id|u32
id|phy_id
suffix:semicolon
DECL|member|multicast_limit
r_int
id|multicast_limit
suffix:semicolon
DECL|member|vCAMmask
id|u8
id|vCAMmask
(braket
(paren
id|VCAM_SIZE
op_div
l_int|8
)paren
)braket
suffix:semicolon
DECL|member|mCAMmask
id|u8
id|mCAMmask
(braket
(paren
id|MCAM_SIZE
op_div
l_int|8
)paren
)braket
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|wol_opts
r_int
id|wol_opts
suffix:semicolon
DECL|member|wol_passwd
id|u8
id|wol_passwd
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|context
r_struct
id|velocity_context
id|context
suffix:semicolon
DECL|member|ticks
id|u32
id|ticks
suffix:semicolon
DECL|member|rx_bytes
id|u32
id|rx_bytes
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;velocity_get_ip&t;&t;-&t;find an IP address for the device&n; *&t;@vptr: Velocity to query&n; *&n; *&t;Dig out an IP address for this interface so that we can&n; *&t;configure wakeup with WOL for ARP. If there are multiple IP&n; *&t;addresses on this chain then we use the first - multi-IP WOL is not&n; *&t;supported.&n; *&n; *&t;CHECK ME: locking&n; */
DECL|function|velocity_get_ip
r_inline
r_static
r_int
id|velocity_get_ip
c_func
(paren
r_struct
id|velocity_info
op_star
id|vptr
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
op_assign
(paren
r_struct
id|in_device
op_star
)paren
id|vptr-&gt;dev-&gt;ip_ptr
suffix:semicolon
r_struct
id|in_ifaddr
op_star
id|ifa
suffix:semicolon
r_if
c_cond
(paren
id|in_dev
op_ne
l_int|NULL
)paren
(brace
id|ifa
op_assign
(paren
r_struct
id|in_ifaddr
op_star
)paren
id|in_dev-&gt;ifa_list
suffix:semicolon
r_if
c_cond
(paren
id|ifa
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|vptr-&gt;ip_addr
comma
op_amp
id|ifa-&gt;ifa_address
comma
l_int|4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;velocity_update_hw_mibs&t;-&t;fetch MIB counters from chip&n; *&t;@vptr: velocity to update&n; *&n; *&t;The velocity hardware keeps certain counters in the hardware&n; * &t;side. We need to read these when the user asks for statistics&n; *&t;or when they overflow (causing an interrupt). The read of the&n; *&t;statistic clears it, so we keep running master counters in user&n; *&t;space.&n; */
DECL|function|velocity_update_hw_mibs
r_static
r_inline
r_void
id|velocity_update_hw_mibs
c_func
(paren
r_struct
id|velocity_info
op_star
id|vptr
)paren
(brace
id|u32
id|tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|BYTE_REG_BITS_ON
c_func
(paren
id|MIBCR_MIBFLSH
comma
op_amp
(paren
id|vptr-&gt;mac_regs-&gt;MIBCR
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|BYTE_REG_BITS_IS_ON
c_func
(paren
id|MIBCR_MIBFLSH
comma
op_amp
(paren
id|vptr-&gt;mac_regs-&gt;MIBCR
)paren
)paren
)paren
suffix:semicolon
id|BYTE_REG_BITS_ON
c_func
(paren
id|MIBCR_MPTRINI
comma
op_amp
(paren
id|vptr-&gt;mac_regs-&gt;MIBCR
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|HW_MIB_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
op_assign
id|readl
c_func
(paren
op_amp
(paren
id|vptr-&gt;mac_regs-&gt;MIBData
)paren
)paren
op_amp
l_int|0x00FFFFFFUL
suffix:semicolon
id|vptr-&gt;mib_counter
(braket
id|i
)braket
op_add_assign
id|tmp
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;init_flow_control_register &t;-&t;set up flow control&n; *&t;@vptr: velocity to configure&n; *&n; *&t;Configure the flow control registers for this velocity device.&n; */
DECL|function|init_flow_control_register
r_static
r_inline
r_void
id|init_flow_control_register
c_func
(paren
r_struct
id|velocity_info
op_star
id|vptr
)paren
(brace
r_struct
id|mac_regs
id|__iomem
op_star
id|regs
op_assign
id|vptr-&gt;mac_regs
suffix:semicolon
multiline_comment|/* Set {XHITH1, XHITH0, XLTH1, XLTH0} in FlowCR1 to {1, 0, 1, 1}&n;&t;   depend on RD=64, and Turn on XNOEN in FlowCR1 */
id|writel
c_func
(paren
(paren
id|CR0_XONEN
op_or
id|CR0_XHITH1
op_or
id|CR0_XLTH1
op_or
id|CR0_XLTH0
)paren
comma
op_amp
id|regs-&gt;CR0Set
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|CR0_FDXTFCEN
op_or
id|CR0_FDXRFCEN
op_or
id|CR0_HDXFCEN
op_or
id|CR0_XHITH0
)paren
comma
op_amp
id|regs-&gt;CR0Clr
)paren
suffix:semicolon
multiline_comment|/* Set TxPauseTimer to 0xFFFF */
id|writew
c_func
(paren
l_int|0xFFFF
comma
op_amp
id|regs-&gt;tx_pause_timer
)paren
suffix:semicolon
multiline_comment|/* Initialize RBRDU to Rx buffer count. */
id|writew
c_func
(paren
id|vptr-&gt;options.numrx
comma
op_amp
id|regs-&gt;RBRDU
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
