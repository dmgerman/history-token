multiline_comment|/*&n; *&n; * Alchemy Semi Au1000 ethernet driver include file&n; *&n; * Author: Pete Popov &lt;ppopov@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * &n; */
DECL|macro|NUM_INTERFACES
mdefine_line|#define NUM_INTERFACES 2
DECL|macro|MAC_IOSIZE
mdefine_line|#define MAC_IOSIZE 0x10000
DECL|macro|NUM_RX_DMA
mdefine_line|#define NUM_RX_DMA 4       /* Au1000 has 4 rx hardware descriptors */
DECL|macro|NUM_TX_DMA
mdefine_line|#define NUM_TX_DMA 4       /* Au1000 has 4 tx hardware descriptors */
DECL|macro|NUM_RX_BUFFS
mdefine_line|#define NUM_RX_BUFFS 4
DECL|macro|NUM_TX_BUFFS
mdefine_line|#define NUM_TX_BUFFS 4
DECL|macro|MAX_BUF_SIZE
mdefine_line|#define MAX_BUF_SIZE 2048
DECL|macro|ETH_TX_TIMEOUT
mdefine_line|#define ETH_TX_TIMEOUT HZ/4
DECL|macro|MAC_MIN_PKT_SIZE
mdefine_line|#define MAC_MIN_PKT_SIZE 64
macro_line|#if defined(CONFIG_MIPS_PB1000) || defined(CONFIG_MIPS_PB1500)
DECL|macro|PHY_ADDRESS
mdefine_line|#define PHY_ADDRESS              0
DECL|macro|PHY_CONTROL_DEFAULT
mdefine_line|#define PHY_CONTROL_DEFAULT 0x3000
DECL|macro|PHY_CONTROL_REG_ADDR
mdefine_line|#define PHY_CONTROL_REG_ADDR     0
macro_line|#endif
DECL|macro|MULTICAST_FILTER_LIMIT
mdefine_line|#define MULTICAST_FILTER_LIMIT 64
multiline_comment|/* FIXME &n; * The PHY defines should be in a separate file.&n; */
multiline_comment|/* MII register offsets */
DECL|macro|MII_CONTROL
mdefine_line|#define&t;MII_CONTROL 0x0000
DECL|macro|MII_STATUS
mdefine_line|#define MII_STATUS  0x0001
DECL|macro|MII_PHY_ID0
mdefine_line|#define MII_PHY_ID0 0x0002
DECL|macro|MII_PHY_ID1
mdefine_line|#define&t;MII_PHY_ID1 0x0003
DECL|macro|MII_ANADV
mdefine_line|#define MII_ANADV   0x0004
DECL|macro|MII_ANLPAR
mdefine_line|#define MII_ANLPAR  0x0005
DECL|macro|MII_AEXP
mdefine_line|#define MII_AEXP    0x0006
DECL|macro|MII_ANEXT
mdefine_line|#define MII_ANEXT   0x0007
DECL|macro|MII_LSI_CONFIG
mdefine_line|#define MII_LSI_CONFIG 0x0011
DECL|macro|MII_LSI_STAT
mdefine_line|#define MII_LSI_STAT   0x0012
DECL|macro|MII_AUX_CNTRL
mdefine_line|#define MII_AUX_CNTRL  0x0018
multiline_comment|/* mii registers specific to AMD 79C901 */
DECL|macro|MII_STATUS_SUMMARY
mdefine_line|#define&t;MII_STATUS_SUMMARY = 0x0018
multiline_comment|/* MII Control register bit definitions. */
DECL|macro|MII_CNTL_FDX
mdefine_line|#define&t;MII_CNTL_FDX      0x0100
DECL|macro|MII_CNTL_RST_AUTO
mdefine_line|#define MII_CNTL_RST_AUTO 0x0200
DECL|macro|MII_CNTL_ISOLATE
mdefine_line|#define&t;MII_CNTL_ISOLATE  0x0400
DECL|macro|MII_CNTL_PWRDWN
mdefine_line|#define MII_CNTL_PWRDWN   0x0800
DECL|macro|MII_CNTL_AUTO
mdefine_line|#define&t;MII_CNTL_AUTO     0x1000
DECL|macro|MII_CNTL_F100
mdefine_line|#define MII_CNTL_F100     0x2000
DECL|macro|MII_CNTL_LPBK
mdefine_line|#define&t;MII_CNTL_LPBK     0x4000
DECL|macro|MII_CNTL_RESET
mdefine_line|#define MII_CNTL_RESET    0x8000
multiline_comment|/* MII Status register bit  */
DECL|macro|MII_STAT_EXT
mdefine_line|#define&t;MII_STAT_EXT        0x0001 
DECL|macro|MII_STAT_JAB
mdefine_line|#define MII_STAT_JAB        0x0002
DECL|macro|MII_STAT_LINK
mdefine_line|#define&t;MII_STAT_LINK       0x0004
DECL|macro|MII_STAT_CAN_AUTO
mdefine_line|#define MII_STAT_CAN_AUTO   0x0008
DECL|macro|MII_STAT_FAULT
mdefine_line|#define&t;MII_STAT_FAULT      0x0010 
DECL|macro|MII_STAT_AUTO_DONE
mdefine_line|#define MII_STAT_AUTO_DONE  0x0020
DECL|macro|MII_STAT_CAN_T
mdefine_line|#define&t;MII_STAT_CAN_T      0x0800
DECL|macro|MII_STAT_CAN_T_FDX
mdefine_line|#define MII_STAT_CAN_T_FDX  0x1000
DECL|macro|MII_STAT_CAN_TX
mdefine_line|#define&t;MII_STAT_CAN_TX     0x2000 
DECL|macro|MII_STAT_CAN_TX_FDX
mdefine_line|#define MII_STAT_CAN_TX_FDX 0x4000
DECL|macro|MII_STAT_CAN_T4
mdefine_line|#define&t;MII_STAT_CAN_T4     0x8000
DECL|macro|MII_ID1_OUI_LO
mdefine_line|#define&t;&t;MII_ID1_OUI_LO&t;&t;0xFC00&t;/* low bits of OUI mask */
DECL|macro|MII_ID1_MODEL
mdefine_line|#define&t;&t;MII_ID1_MODEL&t;&t;0x03F0&t;/* model number */
DECL|macro|MII_ID1_REV
mdefine_line|#define&t;&t;MII_ID1_REV&t;&t;0x000F&t;/* model number */
multiline_comment|/* MII NWAY Register Bits ...&n;   valid for the ANAR (Auto-Negotiation Advertisement) and&n;   ANLPAR (Auto-Negotiation Link Partner) registers */
DECL|macro|MII_NWAY_NODE_SEL
mdefine_line|#define&t;MII_NWAY_NODE_SEL 0x001f
DECL|macro|MII_NWAY_CSMA_CD
mdefine_line|#define MII_NWAY_CSMA_CD  0x0001
DECL|macro|MII_NWAY_T
mdefine_line|#define&t;MII_NWAY_T&t;  0x0020
DECL|macro|MII_NWAY_T_FDX
mdefine_line|#define MII_NWAY_T_FDX    0x0040
DECL|macro|MII_NWAY_TX
mdefine_line|#define&t;MII_NWAY_TX       0x0080
DECL|macro|MII_NWAY_TX_FDX
mdefine_line|#define MII_NWAY_TX_FDX   0x0100
DECL|macro|MII_NWAY_T4
mdefine_line|#define&t;MII_NWAY_T4       0x0200 
DECL|macro|MII_NWAY_PAUSE
mdefine_line|#define MII_NWAY_PAUSE    0x0400 
DECL|macro|MII_NWAY_RF
mdefine_line|#define&t;MII_NWAY_RF       0x2000 /* Remote Fault */
DECL|macro|MII_NWAY_ACK
mdefine_line|#define MII_NWAY_ACK      0x4000 /* Remote Acknowledge */
DECL|macro|MII_NWAY_NP
mdefine_line|#define&t;MII_NWAY_NP       0x8000 /* Next Page (Enable) */
multiline_comment|/* mii stsout register bits */
DECL|macro|MII_STSOUT_LINK_FAIL
mdefine_line|#define&t;MII_STSOUT_LINK_FAIL 0x4000
DECL|macro|MII_STSOUT_SPD
mdefine_line|#define&t;MII_STSOUT_SPD       0x0080
DECL|macro|MII_STSOUT_DPLX
mdefine_line|#define MII_STSOUT_DPLX      0x0040
multiline_comment|/* mii stsics register bits */
DECL|macro|MII_STSICS_SPD
mdefine_line|#define&t;MII_STSICS_SPD       0x8000
DECL|macro|MII_STSICS_DPLX
mdefine_line|#define MII_STSICS_DPLX      0x4000
DECL|macro|MII_STSICS_LINKSTS
mdefine_line|#define&t;MII_STSICS_LINKSTS   0x0001
multiline_comment|/* mii stssum register bits */
DECL|macro|MII_STSSUM_LINK
mdefine_line|#define&t;MII_STSSUM_LINK  0x0008
DECL|macro|MII_STSSUM_DPLX
mdefine_line|#define MII_STSSUM_DPLX  0x0004
DECL|macro|MII_STSSUM_AUTO
mdefine_line|#define&t;MII_STSSUM_AUTO  0x0002
DECL|macro|MII_STSSUM_SPD
mdefine_line|#define MII_STSSUM_SPD   0x0001
multiline_comment|/* lsi status register */
DECL|macro|MII_LSI_STAT_FDX
mdefine_line|#define MII_LSI_STAT_FDX&t;0x0008
DECL|macro|MII_LSI_STAT_SPD
mdefine_line|#define MII_LSI_STAT_SPD&t;0x0010
multiline_comment|/* Auxilliary Control/Status Register */
DECL|macro|MII_AUX_FDX
mdefine_line|#define MII_AUX_FDX      0x0001
DECL|macro|MII_AUX_100
mdefine_line|#define MII_AUX_100      0x0002
DECL|macro|MII_AUX_F100
mdefine_line|#define MII_AUX_F100     0x0004
DECL|macro|MII_AUX_ANEG
mdefine_line|#define MII_AUX_ANEG     0x0008
DECL|struct|mii_phy
r_typedef
r_struct
id|mii_phy
(brace
DECL|member|next
r_struct
id|mii_phy
op_star
id|next
suffix:semicolon
DECL|member|chip_info
r_struct
id|mii_chip_info
op_star
id|chip_info
suffix:semicolon
DECL|member|phy_addr
r_int
id|phy_addr
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|typedef|mii_phy_t
)brace
id|mii_phy_t
suffix:semicolon
DECL|struct|phy_ops
r_struct
id|phy_ops
(brace
DECL|member|phy_init
r_int
(paren
op_star
id|phy_init
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|phy_reset
r_int
(paren
op_star
id|phy_reset
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|phy_status
r_int
(paren
op_star
id|phy_status
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
comma
id|u16
op_star
comma
id|u16
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Data Buffer Descriptor. Data buffers must be aligned on 32 byte &n; * boundary for both, receive and transmit.&n; */
DECL|struct|db_dest
r_typedef
r_struct
id|db_dest
(brace
DECL|member|pnext
r_struct
id|db_dest
op_star
id|pnext
suffix:semicolon
DECL|member|vaddr
r_volatile
id|u32
op_star
id|vaddr
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
DECL|typedef|db_dest_t
)brace
id|db_dest_t
suffix:semicolon
multiline_comment|/*&n; * The transmit and receive descriptors are memory &n; * mapped registers.&n; */
DECL|struct|tx_dma
r_typedef
r_struct
id|tx_dma
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|buff_stat
id|u32
id|buff_stat
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|pad
id|u32
id|pad
suffix:semicolon
DECL|typedef|tx_dma_t
)brace
id|tx_dma_t
suffix:semicolon
DECL|struct|rx_dma
r_typedef
r_struct
id|rx_dma
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|buff_stat
id|u32
id|buff_stat
suffix:semicolon
DECL|member|pad
id|u32
id|pad
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|rx_dma_t
)brace
id|rx_dma_t
suffix:semicolon
multiline_comment|/*&n; * MAC control registers, memory mapped.&n; */
DECL|struct|mac_reg
r_typedef
r_struct
id|mac_reg
(brace
DECL|member|control
id|u32
id|control
suffix:semicolon
DECL|member|mac_addr_high
id|u32
id|mac_addr_high
suffix:semicolon
DECL|member|mac_addr_low
id|u32
id|mac_addr_low
suffix:semicolon
DECL|member|multi_hash_high
id|u32
id|multi_hash_high
suffix:semicolon
DECL|member|multi_hash_low
id|u32
id|multi_hash_low
suffix:semicolon
DECL|member|mii_control
id|u32
id|mii_control
suffix:semicolon
DECL|member|mii_data
id|u32
id|mii_data
suffix:semicolon
DECL|member|flow_control
id|u32
id|flow_control
suffix:semicolon
DECL|member|vlan1_tag
id|u32
id|vlan1_tag
suffix:semicolon
DECL|member|vlan2_tag
id|u32
id|vlan2_tag
suffix:semicolon
DECL|typedef|mac_reg_t
)brace
id|mac_reg_t
suffix:semicolon
DECL|struct|au1000_private
r_struct
id|au1000_private
(brace
DECL|member|pDBfree
id|db_dest_t
op_star
id|pDBfree
suffix:semicolon
DECL|member|db
id|db_dest_t
id|db
(braket
id|NUM_RX_BUFFS
op_plus
id|NUM_TX_BUFFS
)braket
suffix:semicolon
DECL|member|rx_dma_ring
r_volatile
id|rx_dma_t
op_star
id|rx_dma_ring
(braket
id|NUM_RX_DMA
)braket
suffix:semicolon
DECL|member|tx_dma_ring
r_volatile
id|tx_dma_t
op_star
id|tx_dma_ring
(braket
id|NUM_TX_DMA
)braket
suffix:semicolon
DECL|member|rx_db_inuse
id|db_dest_t
op_star
id|rx_db_inuse
(braket
id|NUM_RX_DMA
)braket
suffix:semicolon
DECL|member|tx_db_inuse
id|db_dest_t
op_star
id|tx_db_inuse
(braket
id|NUM_TX_DMA
)braket
suffix:semicolon
DECL|member|rx_head
id|u32
id|rx_head
suffix:semicolon
DECL|member|tx_head
id|u32
id|tx_head
suffix:semicolon
DECL|member|tx_tail
id|u32
id|tx_tail
suffix:semicolon
DECL|member|tx_full
id|u32
id|tx_full
suffix:semicolon
DECL|member|mii
id|mii_phy_t
op_star
id|mii
suffix:semicolon
DECL|member|phy_ops
r_struct
id|phy_ops
op_star
id|phy_ops
suffix:semicolon
multiline_comment|/* These variables are just for quick access to certain regs addresses. */
DECL|member|mac
r_volatile
id|mac_reg_t
op_star
id|mac
suffix:semicolon
multiline_comment|/* mac registers                      */
DECL|member|enable
r_volatile
id|u32
op_star
id|enable
suffix:semicolon
multiline_comment|/* address of MAC Enable Register     */
DECL|member|vaddr
id|u32
id|vaddr
suffix:semicolon
multiline_comment|/* virtual address of rx/tx buffers   */
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
multiline_comment|/* dma address of rx/tx buffers       */
DECL|member|hash_table
id|u8
op_star
id|hash_table
suffix:semicolon
DECL|member|hash_mode
id|u32
id|hash_mode
suffix:semicolon
DECL|member|intr_work_done
id|u32
id|intr_work_done
suffix:semicolon
multiline_comment|/* number of Rx and Tx pkts processed in the isr */
DECL|member|phy_addr
id|u32
id|phy_addr
suffix:semicolon
multiline_comment|/* PHY address */
DECL|member|options
id|u32
id|options
suffix:semicolon
multiline_comment|/* User-settable misc. driver options. */
DECL|member|drv_flags
id|u32
id|drv_flags
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Serialise access to device */
)brace
suffix:semicolon
eof
