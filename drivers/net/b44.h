macro_line|#ifndef _B44_H
DECL|macro|_B44_H
mdefine_line|#define _B44_H
multiline_comment|/* Register layout. */
DECL|macro|B44_DEVCTRL
mdefine_line|#define&t;B44_DEVCTRL&t;0x0000UL /* Device Control */
DECL|macro|DEVCTRL_PFE
mdefine_line|#define  DEVCTRL_PFE&t;&t;0x00000080 /* Pattern Filtering Enable */
DECL|macro|DEVCTRL_IPP
mdefine_line|#define  DEVCTRL_IPP&t;&t;0x00000400 /* Internal EPHY Present */
DECL|macro|DEVCTRL_EPR
mdefine_line|#define  DEVCTRL_EPR&t;&t;0x00008000 /* EPHY Reset */
DECL|macro|DEVCTRL_PME
mdefine_line|#define  DEVCTRL_PME&t;&t;0x00001000 /* PHY Mode Enable */
DECL|macro|DEVCTRL_PMCE
mdefine_line|#define  DEVCTRL_PMCE&t;&t;0x00002000 /* PHY Mode Clocks Enable */
DECL|macro|DEVCTRL_PADDR
mdefine_line|#define  DEVCTRL_PADDR&t;&t;0x0007c000 /* PHY Address */
DECL|macro|DEVCTRL_PADDR_SHIFT
mdefine_line|#define  DEVCTRL_PADDR_SHIFT&t;18
DECL|macro|B44_BIST_STAT
mdefine_line|#define B44_BIST_STAT&t;0x000CUL /* Built-In Self-Test Status */
DECL|macro|B44_WKUP_LEN
mdefine_line|#define B44_WKUP_LEN&t;0x0010UL /* Wakeup Length */
DECL|macro|WKUP_LEN_P0_MASK
mdefine_line|#define  WKUP_LEN_P0_MASK&t;0x0000007f /* Pattern 0 */
DECL|macro|WKUP_LEN_D0
mdefine_line|#define  WKUP_LEN_D0&t;&t;0x00000080
DECL|macro|WKUP_LEN_P1_MASK
mdefine_line|#define  WKUP_LEN_P1_MASK&t;0x00007f00 /* Pattern 1 */
DECL|macro|WKUP_LEN_P1_SHIFT
mdefine_line|#define  WKUP_LEN_P1_SHIFT&t;8
DECL|macro|WKUP_LEN_D1
mdefine_line|#define  WKUP_LEN_D1&t;&t;0x00008000
DECL|macro|WKUP_LEN_P2_MASK
mdefine_line|#define  WKUP_LEN_P2_MASK&t;0x007f0000 /* Pattern 2 */
DECL|macro|WKUP_LEN_P2_SHIFT
mdefine_line|#define  WKUP_LEN_P2_SHIFT&t;16
DECL|macro|WKUP_LEN_D2
mdefine_line|#define  WKUP_LEN_D2&t;&t;0x00000000
DECL|macro|WKUP_LEN_P3_MASK
mdefine_line|#define  WKUP_LEN_P3_MASK&t;0x7f000000 /* Pattern 3 */
DECL|macro|WKUP_LEN_P3_SHIFT
mdefine_line|#define  WKUP_LEN_P3_SHIFT&t;24
DECL|macro|WKUP_LEN_D3
mdefine_line|#define  WKUP_LEN_D3&t;&t;0x80000000
DECL|macro|B44_ISTAT
mdefine_line|#define B44_ISTAT&t;0x0020UL /* Interrupt Status */
DECL|macro|ISTAT_PME
mdefine_line|#define  ISTAT_PME&t;&t;0x00000040 /* Power Management Event */
DECL|macro|ISTAT_TO
mdefine_line|#define  ISTAT_TO&t;&t;0x00000080 /* General Purpose Timeout */
DECL|macro|ISTAT_DSCE
mdefine_line|#define  ISTAT_DSCE&t;&t;0x00000400 /* Descriptor Error */
DECL|macro|ISTAT_DATAE
mdefine_line|#define  ISTAT_DATAE&t;&t;0x00000800 /* Data Error */
DECL|macro|ISTAT_DPE
mdefine_line|#define  ISTAT_DPE&t;&t;0x00001000 /* Descr. Protocol Error */
DECL|macro|ISTAT_RDU
mdefine_line|#define  ISTAT_RDU&t;&t;0x00002000 /* Receive Descr. Underflow */
DECL|macro|ISTAT_RFO
mdefine_line|#define  ISTAT_RFO&t;&t;0x00004000 /* Receive FIFO Overflow */
DECL|macro|ISTAT_TFU
mdefine_line|#define  ISTAT_TFU&t;&t;0x00008000 /* Transmit FIFO Underflow */
DECL|macro|ISTAT_RX
mdefine_line|#define  ISTAT_RX&t;&t;0x00010000 /* RX Interrupt */
DECL|macro|ISTAT_TX
mdefine_line|#define  ISTAT_TX&t;&t;0x01000000 /* TX Interrupt */
DECL|macro|ISTAT_EMAC
mdefine_line|#define  ISTAT_EMAC&t;&t;0x04000000 /* EMAC Interrupt */
DECL|macro|ISTAT_MII_WRITE
mdefine_line|#define  ISTAT_MII_WRITE&t;0x08000000 /* MII Write Interrupt */
DECL|macro|ISTAT_MII_READ
mdefine_line|#define  ISTAT_MII_READ&t;&t;0x10000000 /* MII Read Interrupt */
DECL|macro|ISTAT_ERRORS
mdefine_line|#define  ISTAT_ERRORS (ISTAT_DSCE|ISTAT_DATAE|ISTAT_DPE|ISTAT_RDU|ISTAT_RFO|ISTAT_TFU)
DECL|macro|B44_IMASK
mdefine_line|#define B44_IMASK&t;0x0024UL /* Interrupt Mask */
DECL|macro|IMASK_DEF
mdefine_line|#define  IMASK_DEF&t;&t;(ISTAT_ERRORS | ISTAT_TO | ISTAT_RX | ISTAT_TX)
DECL|macro|B44_GPTIMER
mdefine_line|#define B44_GPTIMER&t;0x0028UL /* General Purpose Timer */
DECL|macro|B44_FILT_ADDR
mdefine_line|#define B44_FILT_ADDR&t;0x0090UL /* ENET Filter Address */
DECL|macro|B44_FILT_DATA
mdefine_line|#define B44_FILT_DATA&t;0x0094UL /* ENET Filter Data */
DECL|macro|B44_TXBURST
mdefine_line|#define B44_TXBURST&t;0x00A0UL /* TX Max Burst Length */
DECL|macro|B44_RXBURST
mdefine_line|#define B44_RXBURST&t;0x00A4UL /* RX Max Burst Length */
DECL|macro|B44_MAC_CTRL
mdefine_line|#define B44_MAC_CTRL&t;0x00A8UL /* MAC Control */
DECL|macro|MAC_CTRL_CRC32_ENAB
mdefine_line|#define  MAC_CTRL_CRC32_ENAB&t;0x00000001 /* CRC32 Generation Enable */
DECL|macro|MAC_CTRL_PHY_PDOWN
mdefine_line|#define  MAC_CTRL_PHY_PDOWN&t;0x00000004 /* Onchip EPHY Powerdown */
DECL|macro|MAC_CTRL_PHY_EDET
mdefine_line|#define  MAC_CTRL_PHY_EDET&t;0x00000008 /* Onchip EPHY Energy Detected */
DECL|macro|MAC_CTRL_PHY_LEDCTRL
mdefine_line|#define  MAC_CTRL_PHY_LEDCTRL&t;0x000000e0 /* Onchip EPHY LED Control */
DECL|macro|MAC_CTRL_PHY_LEDCTRL_SHIFT
mdefine_line|#define  MAC_CTRL_PHY_LEDCTRL_SHIFT 5
DECL|macro|B44_MAC_FLOW
mdefine_line|#define B44_MAC_FLOW&t;0x00ACUL /* MAC Flow Control */
DECL|macro|MAC_FLOW_RX_HI_WATER
mdefine_line|#define  MAC_FLOW_RX_HI_WATER&t;0x000000ff /* Receive FIFO HI Water Mark */
DECL|macro|MAC_FLOW_PAUSE_ENAB
mdefine_line|#define  MAC_FLOW_PAUSE_ENAB&t;0x00008000 /* Enable Pause Frame Generation */
DECL|macro|B44_RCV_LAZY
mdefine_line|#define B44_RCV_LAZY&t;0x0100UL /* Lazy Interrupt Control */
DECL|macro|RCV_LAZY_TO_MASK
mdefine_line|#define  RCV_LAZY_TO_MASK&t;0x00ffffff /* Timeout */
DECL|macro|RCV_LAZY_FC_MASK
mdefine_line|#define  RCV_LAZY_FC_MASK&t;0xff000000 /* Frame Count */
DECL|macro|RCV_LAZY_FC_SHIFT
mdefine_line|#define  RCV_LAZY_FC_SHIFT&t;24
DECL|macro|B44_DMATX_CTRL
mdefine_line|#define B44_DMATX_CTRL&t;0x0200UL /* DMA TX Control */
DECL|macro|DMATX_CTRL_ENABLE
mdefine_line|#define  DMATX_CTRL_ENABLE&t;0x00000001 /* Enable */
DECL|macro|DMATX_CTRL_SUSPEND
mdefine_line|#define  DMATX_CTRL_SUSPEND&t;0x00000002 /* Suepend Request */
DECL|macro|DMATX_CTRL_LPBACK
mdefine_line|#define  DMATX_CTRL_LPBACK&t;0x00000004 /* Loopback Enable */
DECL|macro|DMATX_CTRL_FAIRPRIOR
mdefine_line|#define  DMATX_CTRL_FAIRPRIOR&t;0x00000008 /* Fair Priority */
DECL|macro|DMATX_CTRL_FLUSH
mdefine_line|#define  DMATX_CTRL_FLUSH&t;0x00000010 /* Flush Request */
DECL|macro|B44_DMATX_ADDR
mdefine_line|#define B44_DMATX_ADDR&t;0x0204UL /* DMA TX Descriptor Ring Address */
DECL|macro|B44_DMATX_PTR
mdefine_line|#define B44_DMATX_PTR&t;0x0208UL /* DMA TX Last Posted Descriptor */
DECL|macro|B44_DMATX_STAT
mdefine_line|#define B44_DMATX_STAT&t;0x020CUL /* DMA TX Current Active Desc. + Status */
DECL|macro|DMATX_STAT_CDMASK
mdefine_line|#define  DMATX_STAT_CDMASK&t;0x00000fff /* Current Descriptor Mask */
DECL|macro|DMATX_STAT_SMASK
mdefine_line|#define  DMATX_STAT_SMASK&t;0x0000f000 /* State Mask */
DECL|macro|DMATX_STAT_SDISABLED
mdefine_line|#define  DMATX_STAT_SDISABLED&t;0x00000000 /* State Disabled */
DECL|macro|DMATX_STAT_SACTIVE
mdefine_line|#define  DMATX_STAT_SACTIVE&t;0x00001000 /* State Active */
DECL|macro|DMATX_STAT_SIDLE
mdefine_line|#define  DMATX_STAT_SIDLE&t;0x00002000 /* State Idle Wait */
DECL|macro|DMATX_STAT_SSTOPPED
mdefine_line|#define  DMATX_STAT_SSTOPPED&t;0x00003000 /* State Stopped */
DECL|macro|DMATX_STAT_SSUSP
mdefine_line|#define  DMATX_STAT_SSUSP&t;0x00004000 /* State Suspend Pending */
DECL|macro|DMATX_STAT_EMASK
mdefine_line|#define  DMATX_STAT_EMASK&t;0x000f0000 /* Error Mask */
DECL|macro|DMATX_STAT_ENONE
mdefine_line|#define  DMATX_STAT_ENONE&t;0x00000000 /* Error None */
DECL|macro|DMATX_STAT_EDPE
mdefine_line|#define  DMATX_STAT_EDPE&t;0x00010000 /* Error Desc. Protocol Error */
DECL|macro|DMATX_STAT_EDFU
mdefine_line|#define  DMATX_STAT_EDFU&t;0x00020000 /* Error Data FIFO Underrun */
DECL|macro|DMATX_STAT_EBEBR
mdefine_line|#define  DMATX_STAT_EBEBR&t;0x00030000 /* Error Bus Error on Buffer Read */
DECL|macro|DMATX_STAT_EBEDA
mdefine_line|#define  DMATX_STAT_EBEDA&t;0x00040000 /* Error Bus Error on Desc. Access */
DECL|macro|DMATX_STAT_FLUSHED
mdefine_line|#define  DMATX_STAT_FLUSHED&t;0x00100000 /* Flushed */
DECL|macro|B44_DMARX_CTRL
mdefine_line|#define B44_DMARX_CTRL&t;0x0210UL /* DMA RX Control */
DECL|macro|DMARX_CTRL_ENABLE
mdefine_line|#define  DMARX_CTRL_ENABLE&t;0x00000001 /* Enable */
DECL|macro|DMARX_CTRL_ROMASK
mdefine_line|#define  DMARX_CTRL_ROMASK&t;0x000000fe /* Receive Offset Mask */
DECL|macro|DMARX_CTRL_ROSHIFT
mdefine_line|#define  DMARX_CTRL_ROSHIFT&t;1 &t;   /* Receive Offset Shift */
DECL|macro|B44_DMARX_ADDR
mdefine_line|#define B44_DMARX_ADDR&t;0x0214UL /* DMA RX Descriptor Ring Address */
DECL|macro|B44_DMARX_PTR
mdefine_line|#define B44_DMARX_PTR&t;0x0218UL /* DMA RX Last Posted Descriptor */
DECL|macro|B44_DMARX_STAT
mdefine_line|#define B44_DMARX_STAT&t;0x021CUL /* DMA RX Current Active Desc. + Status */
DECL|macro|DMARX_STAT_CDMASK
mdefine_line|#define  DMARX_STAT_CDMASK&t;0x00000fff /* Current Descriptor Mask */
DECL|macro|DMARX_STAT_SMASK
mdefine_line|#define  DMARX_STAT_SMASK&t;0x0000f000 /* State Mask */
DECL|macro|DMARX_STAT_SDISABLED
mdefine_line|#define  DMARX_STAT_SDISABLED&t;0x00000000 /* State Disbaled */
DECL|macro|DMARX_STAT_SACTIVE
mdefine_line|#define  DMARX_STAT_SACTIVE&t;0x00001000 /* State Active */
DECL|macro|DMARX_STAT_SIDLE
mdefine_line|#define  DMARX_STAT_SIDLE&t;0x00002000 /* State Idle Wait */
DECL|macro|DMARX_STAT_SSTOPPED
mdefine_line|#define  DMARX_STAT_SSTOPPED&t;0x00003000 /* State Stopped */
DECL|macro|DMARX_STAT_EMASK
mdefine_line|#define  DMARX_STAT_EMASK&t;0x000f0000 /* Error Mask */
DECL|macro|DMARX_STAT_ENONE
mdefine_line|#define  DMARX_STAT_ENONE&t;0x00000000 /* Error None */
DECL|macro|DMARX_STAT_EDPE
mdefine_line|#define  DMARX_STAT_EDPE&t;0x00010000 /* Error Desc. Protocol Error */
DECL|macro|DMARX_STAT_EDFO
mdefine_line|#define  DMARX_STAT_EDFO&t;0x00020000 /* Error Data FIFO Overflow */
DECL|macro|DMARX_STAT_EBEBW
mdefine_line|#define  DMARX_STAT_EBEBW&t;0x00030000 /* Error Bus Error on Buffer Write */
DECL|macro|DMARX_STAT_EBEDA
mdefine_line|#define  DMARX_STAT_EBEDA&t;0x00040000 /* Error Bus Error on Desc. Access */
DECL|macro|B44_DMAFIFO_AD
mdefine_line|#define B44_DMAFIFO_AD&t;0x0220UL /* DMA FIFO Diag Address */
DECL|macro|DMAFIFO_AD_OMASK
mdefine_line|#define  DMAFIFO_AD_OMASK&t;0x0000ffff /* Offset Mask */
DECL|macro|DMAFIFO_AD_SMASK
mdefine_line|#define  DMAFIFO_AD_SMASK&t;0x000f0000 /* Select Mask */
DECL|macro|DMAFIFO_AD_SXDD
mdefine_line|#define  DMAFIFO_AD_SXDD&t;0x00000000 /* Select Transmit DMA Data */
DECL|macro|DMAFIFO_AD_SXDP
mdefine_line|#define  DMAFIFO_AD_SXDP&t;0x00010000 /* Select Transmit DMA Pointers */
DECL|macro|DMAFIFO_AD_SRDD
mdefine_line|#define  DMAFIFO_AD_SRDD&t;0x00040000 /* Select Receive DMA Data */
DECL|macro|DMAFIFO_AD_SRDP
mdefine_line|#define  DMAFIFO_AD_SRDP&t;0x00050000 /* Select Receive DMA Pointers */
DECL|macro|DMAFIFO_AD_SXFD
mdefine_line|#define  DMAFIFO_AD_SXFD&t;0x00080000 /* Select Transmit FIFO Data */
DECL|macro|DMAFIFO_AD_SXFP
mdefine_line|#define  DMAFIFO_AD_SXFP&t;0x00090000 /* Select Transmit FIFO Pointers */
DECL|macro|DMAFIFO_AD_SRFD
mdefine_line|#define  DMAFIFO_AD_SRFD&t;0x000c0000 /* Select Receive FIFO Data */
DECL|macro|DMAFIFO_AD_SRFP
mdefine_line|#define  DMAFIFO_AD_SRFP&t;0x000c0000 /* Select Receive FIFO Pointers */
DECL|macro|B44_DMAFIFO_LO
mdefine_line|#define B44_DMAFIFO_LO&t;0x0224UL /* DMA FIFO Diag Low Data */
DECL|macro|B44_DMAFIFO_HI
mdefine_line|#define B44_DMAFIFO_HI&t;0x0228UL /* DMA FIFO Diag High Data */
DECL|macro|B44_RXCONFIG
mdefine_line|#define B44_RXCONFIG&t;0x0400UL /* EMAC RX Config */
DECL|macro|RXCONFIG_DBCAST
mdefine_line|#define  RXCONFIG_DBCAST&t;0x00000001 /* Disable Broadcast */
DECL|macro|RXCONFIG_ALLMULTI
mdefine_line|#define  RXCONFIG_ALLMULTI&t;0x00000002 /* Accept All Multicast */
DECL|macro|RXCONFIG_NORX_WHILE_TX
mdefine_line|#define  RXCONFIG_NORX_WHILE_TX&t;0x00000004 /* Receive Disable While Transmitting */
DECL|macro|RXCONFIG_PROMISC
mdefine_line|#define  RXCONFIG_PROMISC&t;0x00000008 /* Promiscuous Enable */
DECL|macro|RXCONFIG_LPBACK
mdefine_line|#define  RXCONFIG_LPBACK&t;0x00000010 /* Loopback Enable */
DECL|macro|RXCONFIG_FLOW
mdefine_line|#define  RXCONFIG_FLOW&t;&t;0x00000020 /* Flow Control Enable */
DECL|macro|RXCONFIG_FLOW_ACCEPT
mdefine_line|#define  RXCONFIG_FLOW_ACCEPT&t;0x00000040 /* Accept Unicast Flow Control Frame */
DECL|macro|RXCONFIG_RFILT
mdefine_line|#define  RXCONFIG_RFILT&t;&t;0x00000080 /* Reject Filter */
DECL|macro|B44_RXMAXLEN
mdefine_line|#define B44_RXMAXLEN&t;0x0404UL /* EMAC RX Max Packet Length */
DECL|macro|B44_TXMAXLEN
mdefine_line|#define B44_TXMAXLEN&t;0x0408UL /* EMAC TX Max Packet Length */
DECL|macro|B44_MDIO_CTRL
mdefine_line|#define B44_MDIO_CTRL&t;0x0410UL /* EMAC MDIO Control */
DECL|macro|MDIO_CTRL_MAXF_MASK
mdefine_line|#define  MDIO_CTRL_MAXF_MASK&t;0x0000007f /* MDC Frequency */
DECL|macro|MDIO_CTRL_PREAMBLE
mdefine_line|#define  MDIO_CTRL_PREAMBLE&t;0x00000080 /* MII Preamble Enable */
DECL|macro|B44_MDIO_DATA
mdefine_line|#define B44_MDIO_DATA&t;0x0414UL /* EMAC MDIO Data */
DECL|macro|MDIO_DATA_DATA
mdefine_line|#define  MDIO_DATA_DATA&t;&t;0x0000ffff /* R/W Data */
DECL|macro|MDIO_DATA_TA_MASK
mdefine_line|#define  MDIO_DATA_TA_MASK&t;0x00030000 /* Turnaround Value */
DECL|macro|MDIO_DATA_TA_SHIFT
mdefine_line|#define  MDIO_DATA_TA_SHIFT&t;16
DECL|macro|MDIO_TA_VALID
mdefine_line|#define  MDIO_TA_VALID&t;&t;2
DECL|macro|MDIO_DATA_RA_MASK
mdefine_line|#define  MDIO_DATA_RA_MASK&t;0x007c0000 /* Register Address */
DECL|macro|MDIO_DATA_RA_SHIFT
mdefine_line|#define  MDIO_DATA_RA_SHIFT&t;18
DECL|macro|MDIO_DATA_PMD_MASK
mdefine_line|#define  MDIO_DATA_PMD_MASK&t;0x0f800000 /* Physical Media Device */
DECL|macro|MDIO_DATA_PMD_SHIFT
mdefine_line|#define  MDIO_DATA_PMD_SHIFT&t;23
DECL|macro|MDIO_DATA_OP_MASK
mdefine_line|#define  MDIO_DATA_OP_MASK&t;0x30000000 /* Opcode */
DECL|macro|MDIO_DATA_OP_SHIFT
mdefine_line|#define  MDIO_DATA_OP_SHIFT&t;28
DECL|macro|MDIO_OP_WRITE
mdefine_line|#define  MDIO_OP_WRITE&t;&t;1
DECL|macro|MDIO_OP_READ
mdefine_line|#define  MDIO_OP_READ&t;&t;2
DECL|macro|MDIO_DATA_SB_MASK
mdefine_line|#define  MDIO_DATA_SB_MASK&t;0xc0000000 /* Start Bits */
DECL|macro|MDIO_DATA_SB_SHIFT
mdefine_line|#define  MDIO_DATA_SB_SHIFT&t;30
DECL|macro|MDIO_DATA_SB_START
mdefine_line|#define  MDIO_DATA_SB_START&t;0x40000000 /* Start Of Frame */
DECL|macro|B44_EMAC_IMASK
mdefine_line|#define B44_EMAC_IMASK&t;0x0418UL /* EMAC Interrupt Mask */
DECL|macro|B44_EMAC_ISTAT
mdefine_line|#define B44_EMAC_ISTAT&t;0x041CUL /* EMAC Interrupt Status */
DECL|macro|EMAC_INT_MII
mdefine_line|#define  EMAC_INT_MII&t;&t;0x00000001 /* MII MDIO Interrupt */
DECL|macro|EMAC_INT_MIB
mdefine_line|#define  EMAC_INT_MIB&t;&t;0x00000002 /* MIB Interrupt */
DECL|macro|EMAC_INT_FLOW
mdefine_line|#define  EMAC_INT_FLOW&t;&t;0x00000003 /* Flow Control Interrupt */
DECL|macro|B44_CAM_DATA_LO
mdefine_line|#define B44_CAM_DATA_LO&t;0x0420UL /* EMAC CAM Data Low */
DECL|macro|B44_CAM_DATA_HI
mdefine_line|#define B44_CAM_DATA_HI&t;0x0424UL /* EMAC CAM Data High */
DECL|macro|CAM_DATA_HI_VALID
mdefine_line|#define  CAM_DATA_HI_VALID&t;0x00010000 /* Valid Bit */
DECL|macro|B44_CAM_CTRL
mdefine_line|#define B44_CAM_CTRL&t;0x0428UL /* EMAC CAM Control */
DECL|macro|CAM_CTRL_ENABLE
mdefine_line|#define  CAM_CTRL_ENABLE&t;0x00000001 /* CAM Enable */
DECL|macro|CAM_CTRL_MSEL
mdefine_line|#define  CAM_CTRL_MSEL&t;&t;0x00000002 /* Mask Select */
DECL|macro|CAM_CTRL_READ
mdefine_line|#define  CAM_CTRL_READ&t;&t;0x00000004 /* Read */
DECL|macro|CAM_CTRL_WRITE
mdefine_line|#define  CAM_CTRL_WRITE&t;&t;0x00000008 /* Read */
DECL|macro|CAM_CTRL_INDEX_MASK
mdefine_line|#define  CAM_CTRL_INDEX_MASK&t;0x003f0000 /* Index Mask */
DECL|macro|CAM_CTRL_INDEX_SHIFT
mdefine_line|#define  CAM_CTRL_INDEX_SHIFT&t;16
DECL|macro|CAM_CTRL_BUSY
mdefine_line|#define  CAM_CTRL_BUSY&t;&t;0x80000000 /* CAM Busy */
DECL|macro|B44_ENET_CTRL
mdefine_line|#define B44_ENET_CTRL&t;0x042CUL /* EMAC ENET Control */
DECL|macro|ENET_CTRL_ENABLE
mdefine_line|#define  ENET_CTRL_ENABLE&t;0x00000001 /* EMAC Enable */
DECL|macro|ENET_CTRL_DISABLE
mdefine_line|#define  ENET_CTRL_DISABLE&t;0x00000002 /* EMAC Disable */
DECL|macro|ENET_CTRL_SRST
mdefine_line|#define  ENET_CTRL_SRST&t;&t;0x00000004 /* EMAC Soft Reset */
DECL|macro|ENET_CTRL_EPSEL
mdefine_line|#define  ENET_CTRL_EPSEL&t;0x00000008 /* External PHY Select */
DECL|macro|B44_TX_CTRL
mdefine_line|#define B44_TX_CTRL&t;0x0430UL /* EMAC TX Control */
DECL|macro|TX_CTRL_DUPLEX
mdefine_line|#define  TX_CTRL_DUPLEX&t;&t;0x00000001 /* Full Duplex */
DECL|macro|TX_CTRL_FMODE
mdefine_line|#define  TX_CTRL_FMODE&t;&t;0x00000002 /* Flow Mode */
DECL|macro|TX_CTRL_SBENAB
mdefine_line|#define  TX_CTRL_SBENAB&t;&t;0x00000004 /* Single Backoff Enable */
DECL|macro|TX_CTRL_SMALL_SLOT
mdefine_line|#define  TX_CTRL_SMALL_SLOT&t;0x00000008 /* Small Slottime */
DECL|macro|B44_TX_WMARK
mdefine_line|#define B44_TX_WMARK&t;0x0434UL /* EMAC TX Watermark */
DECL|macro|B44_MIB_CTRL
mdefine_line|#define B44_MIB_CTRL&t;0x0438UL /* EMAC MIB Control */
DECL|macro|MIB_CTRL_CLR_ON_READ
mdefine_line|#define  MIB_CTRL_CLR_ON_READ&t;0x00000001 /* Autoclear on Read */
DECL|macro|B44_TX_GOOD_O
mdefine_line|#define B44_TX_GOOD_O&t;0x0500UL /* MIB TX Good Octets */
DECL|macro|B44_TX_GOOD_P
mdefine_line|#define B44_TX_GOOD_P&t;0x0504UL /* MIB TX Good Packets */
DECL|macro|B44_TX_O
mdefine_line|#define B44_TX_O&t;0x0508UL /* MIB TX Octets */
DECL|macro|B44_TX_P
mdefine_line|#define B44_TX_P&t;0x050CUL /* MIB TX Packets */
DECL|macro|B44_TX_BCAST
mdefine_line|#define B44_TX_BCAST&t;0x0510UL /* MIB TX Broadcast Packets */
DECL|macro|B44_TX_MCAST
mdefine_line|#define B44_TX_MCAST&t;0x0514UL /* MIB TX Multicast Packets */
DECL|macro|B44_TX_64
mdefine_line|#define B44_TX_64&t;0x0518UL /* MIB TX &lt;= 64 byte Packets */
DECL|macro|B44_TX_65_127
mdefine_line|#define B44_TX_65_127&t;0x051CUL /* MIB TX 65 to 127 byte Packets */
DECL|macro|B44_TX_128_255
mdefine_line|#define B44_TX_128_255&t;0x0520UL /* MIB TX 128 to 255 byte Packets */
DECL|macro|B44_TX_256_511
mdefine_line|#define B44_TX_256_511&t;0x0524UL /* MIB TX 256 to 511 byte Packets */
DECL|macro|B44_TX_512_1023
mdefine_line|#define B44_TX_512_1023&t;0x0528UL /* MIB TX 512 to 1023 byte Packets */
DECL|macro|B44_TX_1024_MAX
mdefine_line|#define B44_TX_1024_MAX&t;0x052CUL /* MIB TX 1024 to max byte Packets */
DECL|macro|B44_TX_JABBER
mdefine_line|#define B44_TX_JABBER&t;0x0530UL /* MIB TX Jabber Packets */
DECL|macro|B44_TX_OSIZE
mdefine_line|#define B44_TX_OSIZE&t;0x0534UL /* MIB TX Oversize Packets */
DECL|macro|B44_TX_FRAG
mdefine_line|#define B44_TX_FRAG&t;0x0538UL /* MIB TX Fragment Packets */
DECL|macro|B44_TX_URUNS
mdefine_line|#define B44_TX_URUNS&t;0x053CUL /* MIB TX Underruns */
DECL|macro|B44_TX_TCOLS
mdefine_line|#define B44_TX_TCOLS&t;0x0540UL /* MIB TX Total Collisions */
DECL|macro|B44_TX_SCOLS
mdefine_line|#define B44_TX_SCOLS&t;0x0544UL /* MIB TX Single Collisions */
DECL|macro|B44_TX_MCOLS
mdefine_line|#define B44_TX_MCOLS&t;0x0548UL /* MIB TX Multiple Collisions */
DECL|macro|B44_TX_ECOLS
mdefine_line|#define B44_TX_ECOLS&t;0x054CUL /* MIB TX Excessive Collisions */
DECL|macro|B44_TX_LCOLS
mdefine_line|#define B44_TX_LCOLS&t;0x0550UL /* MIB TX Late Collisions */
DECL|macro|B44_TX_DEFERED
mdefine_line|#define B44_TX_DEFERED&t;0x0554UL /* MIB TX Defered Packets */
DECL|macro|B44_TX_CLOST
mdefine_line|#define B44_TX_CLOST&t;0x0558UL /* MIB TX Carrier Lost */
DECL|macro|B44_TX_PAUSE
mdefine_line|#define B44_TX_PAUSE&t;0x055CUL /* MIB TX Pause Packets */
DECL|macro|B44_RX_GOOD_O
mdefine_line|#define B44_RX_GOOD_O&t;0x0580UL /* MIB RX Good Octets */
DECL|macro|B44_RX_GOOD_P
mdefine_line|#define B44_RX_GOOD_P&t;0x0584UL /* MIB RX Good Packets */
DECL|macro|B44_RX_O
mdefine_line|#define B44_RX_O&t;0x0588UL /* MIB RX Octets */
DECL|macro|B44_RX_P
mdefine_line|#define B44_RX_P&t;0x058CUL /* MIB RX Packets */
DECL|macro|B44_RX_BCAST
mdefine_line|#define B44_RX_BCAST&t;0x0590UL /* MIB RX Broadcast Packets */
DECL|macro|B44_RX_MCAST
mdefine_line|#define B44_RX_MCAST&t;0x0594UL /* MIB RX Multicast Packets */
DECL|macro|B44_RX_64
mdefine_line|#define B44_RX_64&t;0x0598UL /* MIB RX &lt;= 64 byte Packets */
DECL|macro|B44_RX_65_127
mdefine_line|#define B44_RX_65_127&t;0x059CUL /* MIB RX 65 to 127 byte Packets */
DECL|macro|B44_RX_128_255
mdefine_line|#define B44_RX_128_255&t;0x05A0UL /* MIB RX 128 to 255 byte Packets */
DECL|macro|B44_RX_256_511
mdefine_line|#define B44_RX_256_511&t;0x05A4UL /* MIB RX 256 to 511 byte Packets */
DECL|macro|B44_RX_512_1023
mdefine_line|#define B44_RX_512_1023&t;0x05A8UL /* MIB RX 512 to 1023 byte Packets */
DECL|macro|B44_RX_1024_MAX
mdefine_line|#define B44_RX_1024_MAX&t;0x05ACUL /* MIB RX 1024 to max byte Packets */
DECL|macro|B44_RX_JABBER
mdefine_line|#define B44_RX_JABBER&t;0x05B0UL /* MIB RX Jabber Packets */
DECL|macro|B44_RX_OSIZE
mdefine_line|#define B44_RX_OSIZE&t;0x05B4UL /* MIB RX Oversize Packets */
DECL|macro|B44_RX_FRAG
mdefine_line|#define B44_RX_FRAG&t;0x05B8UL /* MIB RX Fragment Packets */
DECL|macro|B44_RX_MISS
mdefine_line|#define B44_RX_MISS&t;0x05BCUL /* MIB RX Missed Packets */
DECL|macro|B44_RX_CRCA
mdefine_line|#define B44_RX_CRCA&t;0x05C0UL /* MIB RX CRC Align Errors */
DECL|macro|B44_RX_USIZE
mdefine_line|#define B44_RX_USIZE&t;0x05C4UL /* MIB RX Undersize Packets */
DECL|macro|B44_RX_CRC
mdefine_line|#define B44_RX_CRC&t;0x05C8UL /* MIB RX CRC Errors */
DECL|macro|B44_RX_ALIGN
mdefine_line|#define B44_RX_ALIGN&t;0x05CCUL /* MIB RX Align Errors */
DECL|macro|B44_RX_SYM
mdefine_line|#define B44_RX_SYM&t;0x05D0UL /* MIB RX Symbol Errors */
DECL|macro|B44_RX_PAUSE
mdefine_line|#define B44_RX_PAUSE&t;0x05D4UL /* MIB RX Pause Packets */
DECL|macro|B44_RX_NPAUSE
mdefine_line|#define B44_RX_NPAUSE&t;0x05D8UL /* MIB RX Non-Pause Packets */
DECL|macro|B44_SBIPSFLAG
mdefine_line|#define B44_SBIPSFLAG&t;0x0F08UL /* SB Initiator Port OCP Slave Flag */
DECL|macro|SBIPSFLAG_IMASK1
mdefine_line|#define  SBIPSFLAG_IMASK1&t;0x0000003f /* Which sbflags --&gt; mips interrupt 1 */
DECL|macro|SBIPSFLAG_ISHIFT1
mdefine_line|#define  SBIPSFLAG_ISHIFT1&t;0
DECL|macro|SBIPSFLAG_IMASK2
mdefine_line|#define  SBIPSFLAG_IMASK2&t;0x00003f00 /* Which sbflags --&gt; mips interrupt 2 */
DECL|macro|SBIPSFLAG_ISHIFT2
mdefine_line|#define  SBIPSFLAG_ISHIFT2&t;8
DECL|macro|SBIPSFLAG_IMASK3
mdefine_line|#define  SBIPSFLAG_IMASK3&t;0x003f0000 /* Which sbflags --&gt; mips interrupt 3 */
DECL|macro|SBIPSFLAG_ISHIFT3
mdefine_line|#define  SBIPSFLAG_ISHIFT3&t;16
DECL|macro|SBIPSFLAG_IMASK4
mdefine_line|#define  SBIPSFLAG_IMASK4&t;0x3f000000 /* Which sbflags --&gt; mips interrupt 4 */
DECL|macro|SBIPSFLAG_ISHIFT4
mdefine_line|#define  SBIPSFLAG_ISHIFT4&t;24
DECL|macro|B44_SBTPSFLAG
mdefine_line|#define B44_SBTPSFLAG&t;0x0F18UL /* SB Target Port OCP Slave Flag */
DECL|macro|SBTPS_NUM0_MASK
mdefine_line|#define  SBTPS_NUM0_MASK&t;0x0000003f
DECL|macro|SBTPS_F0EN0
mdefine_line|#define  SBTPS_F0EN0&t;&t;0x00000040
DECL|macro|B44_SBADMATCH3
mdefine_line|#define B44_SBADMATCH3&t;0x0F60UL /* SB Address Match 3 */
DECL|macro|B44_SBADMATCH2
mdefine_line|#define B44_SBADMATCH2&t;0x0F68UL /* SB Address Match 2 */
DECL|macro|B44_SBADMATCH1
mdefine_line|#define B44_SBADMATCH1&t;0x0F70UL /* SB Address Match 1 */
DECL|macro|B44_SBIMSTATE
mdefine_line|#define B44_SBIMSTATE&t;0x0F90UL /* SB Initiator Agent State */
DECL|macro|SBIMSTATE_PC
mdefine_line|#define  SBIMSTATE_PC&t;&t;0x0000000f /* Pipe Count */
DECL|macro|SBIMSTATE_AP_MASK
mdefine_line|#define  SBIMSTATE_AP_MASK&t;0x00000030 /* Arbitration Priority */
DECL|macro|SBIMSTATE_AP_BOTH
mdefine_line|#define  SBIMSTATE_AP_BOTH&t;0x00000000 /* Use both timeslices and token */
DECL|macro|SBIMSTATE_AP_TS
mdefine_line|#define  SBIMSTATE_AP_TS&t;0x00000010 /* Use timeslices only */
DECL|macro|SBIMSTATE_AP_TK
mdefine_line|#define  SBIMSTATE_AP_TK&t;0x00000020 /* Use token only */
DECL|macro|SBIMSTATE_AP_RSV
mdefine_line|#define  SBIMSTATE_AP_RSV&t;0x00000030 /* Reserved */
DECL|macro|SBIMSTATE_IBE
mdefine_line|#define  SBIMSTATE_IBE&t;&t;0x00020000 /* In Band Error */
DECL|macro|SBIMSTATE_TO
mdefine_line|#define  SBIMSTATE_TO&t;&t;0x00040000 /* Timeout */
DECL|macro|B44_SBINTVEC
mdefine_line|#define B44_SBINTVEC&t;0x0F94UL /* SB Interrupt Mask */
DECL|macro|SBINTVEC_PCI
mdefine_line|#define  SBINTVEC_PCI&t;&t;0x00000001 /* Enable interrupts for PCI */
DECL|macro|SBINTVEC_ENET0
mdefine_line|#define  SBINTVEC_ENET0&t;&t;0x00000002 /* Enable interrupts for enet 0 */
DECL|macro|SBINTVEC_ILINE20
mdefine_line|#define  SBINTVEC_ILINE20&t;0x00000004 /* Enable interrupts for iline20 */
DECL|macro|SBINTVEC_CODEC
mdefine_line|#define  SBINTVEC_CODEC&t;&t;0x00000008 /* Enable interrupts for v90 codec */
DECL|macro|SBINTVEC_USB
mdefine_line|#define  SBINTVEC_USB&t;&t;0x00000010 /* Enable interrupts for usb */
DECL|macro|SBINTVEC_EXTIF
mdefine_line|#define  SBINTVEC_EXTIF&t;&t;0x00000020 /* Enable interrupts for external i/f */
DECL|macro|SBINTVEC_ENET1
mdefine_line|#define  SBINTVEC_ENET1&t;&t;0x00000040 /* Enable interrupts for enet 1 */
DECL|macro|B44_SBTMSLOW
mdefine_line|#define B44_SBTMSLOW&t;0x0F98UL /* SB Target State Low */
DECL|macro|SBTMSLOW_RESET
mdefine_line|#define  SBTMSLOW_RESET&t;&t;0x00000001 /* Reset */
DECL|macro|SBTMSLOW_REJECT
mdefine_line|#define  SBTMSLOW_REJECT&t;0x00000002 /* Reject */
DECL|macro|SBTMSLOW_CLOCK
mdefine_line|#define  SBTMSLOW_CLOCK&t;&t;0x00010000 /* Clock Enable */
DECL|macro|SBTMSLOW_FGC
mdefine_line|#define  SBTMSLOW_FGC&t;&t;0x00020000 /* Force Gated Clocks On */
DECL|macro|SBTMSLOW_PE
mdefine_line|#define  SBTMSLOW_PE&t;&t;0x40000000 /* Power Management Enable */
DECL|macro|SBTMSLOW_BE
mdefine_line|#define  SBTMSLOW_BE&t;&t;0x80000000 /* BIST Enable */
DECL|macro|B44_SBTMSHIGH
mdefine_line|#define B44_SBTMSHIGH&t;0x0F9CUL /* SB Target State High */
DECL|macro|SBTMSHIGH_SERR
mdefine_line|#define  SBTMSHIGH_SERR&t;&t;0x00000001 /* S-error */
DECL|macro|SBTMSHIGH_INT
mdefine_line|#define  SBTMSHIGH_INT&t;&t;0x00000002 /* Interrupt */
DECL|macro|SBTMSHIGH_BUSY
mdefine_line|#define  SBTMSHIGH_BUSY&t;&t;0x00000004 /* Busy */
DECL|macro|SBTMSHIGH_GCR
mdefine_line|#define  SBTMSHIGH_GCR&t;&t;0x20000000 /* Gated Clock Request */
DECL|macro|SBTMSHIGH_BISTF
mdefine_line|#define  SBTMSHIGH_BISTF&t;0x40000000 /* BIST Failed */
DECL|macro|SBTMSHIGH_BISTD
mdefine_line|#define  SBTMSHIGH_BISTD&t;0x80000000 /* BIST Done */
DECL|macro|B44_SBBWA0
mdefine_line|#define B44_SBBWA0&t;0x0FA0UL /* SB Bandwidth Allocation Table 0 */
DECL|macro|SBBWA0_TAB0_MASK
mdefine_line|#define  SBBWA0_TAB0_MASK&t;0x0000ffff /* Lookup Table 0 */
DECL|macro|SBBWA0_TAB0_SHIFT
mdefine_line|#define  SBBWA0_TAB0_SHIFT&t;0
DECL|macro|SBBWA0_TAB1_MASK
mdefine_line|#define  SBBWA0_TAB1_MASK&t;0xffff0000 /* Lookup Table 0 */
DECL|macro|SBBWA0_TAB1_SHIFT
mdefine_line|#define  SBBWA0_TAB1_SHIFT&t;16
DECL|macro|B44_SBIMCFGLOW
mdefine_line|#define B44_SBIMCFGLOW&t;0x0FA8UL /* SB Initiator Configuration Low */
DECL|macro|SBIMCFGLOW_STO_MASK
mdefine_line|#define  SBIMCFGLOW_STO_MASK&t;0x00000003 /* Service Timeout */
DECL|macro|SBIMCFGLOW_RTO_MASK
mdefine_line|#define  SBIMCFGLOW_RTO_MASK&t;0x00000030 /* Request Timeout */
DECL|macro|SBIMCFGLOW_RTO_SHIFT
mdefine_line|#define  SBIMCFGLOW_RTO_SHIFT&t;4
DECL|macro|SBIMCFGLOW_CID_MASK
mdefine_line|#define  SBIMCFGLOW_CID_MASK&t;0x00ff0000 /* Connection ID */
DECL|macro|SBIMCFGLOW_CID_SHIFT
mdefine_line|#define  SBIMCFGLOW_CID_SHIFT&t;16
DECL|macro|B44_SBIMCFGHIGH
mdefine_line|#define B44_SBIMCFGHIGH&t;0x0FACUL /* SB Initiator Configuration High */
DECL|macro|SBIMCFGHIGH_IEM_MASK
mdefine_line|#define  SBIMCFGHIGH_IEM_MASK&t;0x0000000c /* Inband Error Mode */
DECL|macro|SBIMCFGHIGH_TEM_MASK
mdefine_line|#define  SBIMCFGHIGH_TEM_MASK&t;0x00000030 /* Timeout Error Mode */
DECL|macro|SBIMCFGHIGH_TEM_SHIFT
mdefine_line|#define  SBIMCFGHIGH_TEM_SHIFT&t;4
DECL|macro|SBIMCFGHIGH_BEM_MASK
mdefine_line|#define  SBIMCFGHIGH_BEM_MASK&t;0x000000c0 /* Bus Error Mode */
DECL|macro|SBIMCFGHIGH_BEM_SHIFT
mdefine_line|#define  SBIMCFGHIGH_BEM_SHIFT&t;6
DECL|macro|B44_SBADMATCH0
mdefine_line|#define B44_SBADMATCH0&t;0x0FB0UL /* SB Address Match 0 */
DECL|macro|SBADMATCH0_TYPE_MASK
mdefine_line|#define  SBADMATCH0_TYPE_MASK&t;0x00000003 /* Address Type */
DECL|macro|SBADMATCH0_AD64
mdefine_line|#define  SBADMATCH0_AD64&t;0x00000004 /* Reserved */
DECL|macro|SBADMATCH0_AI0_MASK
mdefine_line|#define  SBADMATCH0_AI0_MASK&t;0x000000f8 /* Type0 Size */
DECL|macro|SBADMATCH0_AI0_SHIFT
mdefine_line|#define  SBADMATCH0_AI0_SHIFT&t;3
DECL|macro|SBADMATCH0_AI1_MASK
mdefine_line|#define  SBADMATCH0_AI1_MASK&t;0x000001f8 /* Type1 Size */
DECL|macro|SBADMATCH0_AI1_SHIFT
mdefine_line|#define  SBADMATCH0_AI1_SHIFT&t;3
DECL|macro|SBADMATCH0_AI2_MASK
mdefine_line|#define  SBADMATCH0_AI2_MASK&t;0x000001f8 /* Type2 Size */
DECL|macro|SBADMATCH0_AI2_SHIFT
mdefine_line|#define  SBADMATCH0_AI2_SHIFT&t;3
DECL|macro|SBADMATCH0_ADEN
mdefine_line|#define  SBADMATCH0_ADEN&t;0x00000400 /* Enable */
DECL|macro|SBADMATCH0_ADNEG
mdefine_line|#define  SBADMATCH0_ADNEG&t;0x00000800 /* Negative Decode */
DECL|macro|SBADMATCH0_BS0_MASK
mdefine_line|#define  SBADMATCH0_BS0_MASK&t;0xffffff00 /* Type0 Base Address */
DECL|macro|SBADMATCH0_BS0_SHIFT
mdefine_line|#define  SBADMATCH0_BS0_SHIFT&t;8
DECL|macro|SBADMATCH0_BS1_MASK
mdefine_line|#define  SBADMATCH0_BS1_MASK&t;0xfffff000 /* Type1 Base Address */
DECL|macro|SBADMATCH0_BS1_SHIFT
mdefine_line|#define  SBADMATCH0_BS1_SHIFT&t;12
DECL|macro|SBADMATCH0_BS2_MASK
mdefine_line|#define  SBADMATCH0_BS2_MASK&t;0xffff0000 /* Type2 Base Address */
DECL|macro|SBADMATCH0_BS2_SHIFT
mdefine_line|#define  SBADMATCH0_BS2_SHIFT&t;16
DECL|macro|B44_SBTMCFGLOW
mdefine_line|#define B44_SBTMCFGLOW&t;0x0FB8UL /* SB Target Configuration Low */
DECL|macro|SBTMCFGLOW_CD_MASK
mdefine_line|#define  SBTMCFGLOW_CD_MASK&t;0x000000ff /* Clock Divide Mask */
DECL|macro|SBTMCFGLOW_CO_MASK
mdefine_line|#define  SBTMCFGLOW_CO_MASK&t;0x0000f800 /* Clock Offset Mask */
DECL|macro|SBTMCFGLOW_CO_SHIFT
mdefine_line|#define  SBTMCFGLOW_CO_SHIFT&t;11
DECL|macro|SBTMCFGLOW_IF_MASK
mdefine_line|#define  SBTMCFGLOW_IF_MASK&t;0x00fc0000 /* Interrupt Flags Mask */
DECL|macro|SBTMCFGLOW_IF_SHIFT
mdefine_line|#define  SBTMCFGLOW_IF_SHIFT&t;18
DECL|macro|SBTMCFGLOW_IM_MASK
mdefine_line|#define  SBTMCFGLOW_IM_MASK&t;0x03000000 /* Interrupt Mode Mask */
DECL|macro|SBTMCFGLOW_IM_SHIFT
mdefine_line|#define  SBTMCFGLOW_IM_SHIFT&t;24
DECL|macro|B44_SBTMCFGHIGH
mdefine_line|#define B44_SBTMCFGHIGH&t;0x0FBCUL /* SB Target Configuration High */
DECL|macro|SBTMCFGHIGH_BM_MASK
mdefine_line|#define  SBTMCFGHIGH_BM_MASK&t;0x00000003 /* Busy Mode */
DECL|macro|SBTMCFGHIGH_RM_MASK
mdefine_line|#define  SBTMCFGHIGH_RM_MASK&t;0x0000000C /* Retry Mode */
DECL|macro|SBTMCFGHIGH_RM_SHIFT
mdefine_line|#define  SBTMCFGHIGH_RM_SHIFT&t;2
DECL|macro|SBTMCFGHIGH_SM_MASK
mdefine_line|#define  SBTMCFGHIGH_SM_MASK&t;0x00000030 /* Stop Mode */
DECL|macro|SBTMCFGHIGH_SM_SHIFT
mdefine_line|#define  SBTMCFGHIGH_SM_SHIFT&t;4
DECL|macro|SBTMCFGHIGH_EM_MASK
mdefine_line|#define  SBTMCFGHIGH_EM_MASK&t;0x00000300 /* Error Mode */
DECL|macro|SBTMCFGHIGH_EM_SHIFT
mdefine_line|#define  SBTMCFGHIGH_EM_SHIFT&t;8
DECL|macro|SBTMCFGHIGH_IM_MASK
mdefine_line|#define  SBTMCFGHIGH_IM_MASK&t;0x00000c00 /* Interrupt Mode */
DECL|macro|SBTMCFGHIGH_IM_SHIFT
mdefine_line|#define  SBTMCFGHIGH_IM_SHIFT&t;10
DECL|macro|B44_SBBCFG
mdefine_line|#define B44_SBBCFG&t;0x0FC0UL /* SB Broadcast Configuration */
DECL|macro|SBBCFG_LAT_MASK
mdefine_line|#define  SBBCFG_LAT_MASK&t;0x00000003 /* SB Latency */
DECL|macro|SBBCFG_MAX0_MASK
mdefine_line|#define  SBBCFG_MAX0_MASK&t;0x000f0000 /* MAX Counter 0 */
DECL|macro|SBBCFG_MAX0_SHIFT
mdefine_line|#define  SBBCFG_MAX0_SHIFT&t;16
DECL|macro|SBBCFG_MAX1_MASK
mdefine_line|#define  SBBCFG_MAX1_MASK&t;0x00f00000 /* MAX Counter 1 */
DECL|macro|SBBCFG_MAX1_SHIFT
mdefine_line|#define  SBBCFG_MAX1_SHIFT&t;20
DECL|macro|B44_SBBSTATE
mdefine_line|#define B44_SBBSTATE&t;0x0FC8UL /* SB Broadcast State */
DECL|macro|SBBSTATE_SRD
mdefine_line|#define  SBBSTATE_SRD&t;&t;0x00000001 /* ST Reg Disable */
DECL|macro|SBBSTATE_HRD
mdefine_line|#define  SBBSTATE_HRD&t;&t;0x00000002 /* Hold Reg Disable */
DECL|macro|B44_SBACTCNFG
mdefine_line|#define B44_SBACTCNFG&t;0x0FD8UL /* SB Activate Configuration */
DECL|macro|B44_SBFLAGST
mdefine_line|#define B44_SBFLAGST&t;0x0FE8UL /* SB Current SBFLAGS */
DECL|macro|B44_SBIDLOW
mdefine_line|#define B44_SBIDLOW&t;0x0FF8UL /* SB Identification Low */
DECL|macro|SBIDLOW_CS_MASK
mdefine_line|#define  SBIDLOW_CS_MASK&t;0x00000003 /* Config Space Mask */
DECL|macro|SBIDLOW_AR_MASK
mdefine_line|#define  SBIDLOW_AR_MASK&t;0x00000038 /* Num Address Ranges Supported */
DECL|macro|SBIDLOW_AR_SHIFT
mdefine_line|#define  SBIDLOW_AR_SHIFT&t;3
DECL|macro|SBIDLOW_SYNCH
mdefine_line|#define  SBIDLOW_SYNCH&t;&t;0x00000040 /* Sync */
DECL|macro|SBIDLOW_INIT
mdefine_line|#define  SBIDLOW_INIT&t;&t;0x00000080 /* Initiator */
DECL|macro|SBIDLOW_MINLAT_MASK
mdefine_line|#define  SBIDLOW_MINLAT_MASK&t;0x00000f00 /* Minimum Backplane Latency */
DECL|macro|SBIDLOW_MINLAT_SHIFT
mdefine_line|#define  SBIDLOW_MINLAT_SHIFT&t;8
DECL|macro|SBIDLOW_MAXLAT_MASK
mdefine_line|#define  SBIDLOW_MAXLAT_MASK&t;0x0000f000 /* Maximum Backplane Latency */
DECL|macro|SBIDLOW_MAXLAT_SHIFT
mdefine_line|#define  SBIDLOW_MAXLAT_SHIFT&t;12
DECL|macro|SBIDLOW_FIRST
mdefine_line|#define  SBIDLOW_FIRST&t;&t;0x00010000 /* This Initiator is First */
DECL|macro|SBIDLOW_CW_MASK
mdefine_line|#define  SBIDLOW_CW_MASK&t;0x000c0000 /* Cycle Counter Width */
DECL|macro|SBIDLOW_CW_SHIFT
mdefine_line|#define  SBIDLOW_CW_SHIFT&t;18
DECL|macro|SBIDLOW_TP_MASK
mdefine_line|#define  SBIDLOW_TP_MASK&t;0x00f00000 /* Target Ports */
DECL|macro|SBIDLOW_TP_SHIFT
mdefine_line|#define  SBIDLOW_TP_SHIFT&t;20
DECL|macro|SBIDLOW_IP_MASK
mdefine_line|#define  SBIDLOW_IP_MASK&t;0x0f000000 /* Initiator Ports */
DECL|macro|SBIDLOW_IP_SHIFT
mdefine_line|#define  SBIDLOW_IP_SHIFT&t;24
DECL|macro|B44_SBIDHIGH
mdefine_line|#define B44_SBIDHIGH&t;0x0FFCUL /* SB Identification High */
DECL|macro|SBIDHIGH_RC_MASK
mdefine_line|#define  SBIDHIGH_RC_MASK&t;0x0000000f /* Revision Code */
DECL|macro|SBIDHIGH_CC_MASK
mdefine_line|#define  SBIDHIGH_CC_MASK&t;0x0000fff0 /* Core Code */
DECL|macro|SBIDHIGH_CC_SHIFT
mdefine_line|#define  SBIDHIGH_CC_SHIFT&t;4
DECL|macro|SBIDHIGH_VC_MASK
mdefine_line|#define  SBIDHIGH_VC_MASK&t;0xffff0000 /* Vendor Code */
DECL|macro|SBIDHIGH_VC_SHIFT
mdefine_line|#define  SBIDHIGH_VC_SHIFT&t;16
DECL|macro|CORE_CODE_ILINE20
mdefine_line|#define  CORE_CODE_ILINE20&t;0x801
DECL|macro|CORE_CODE_SDRAM
mdefine_line|#define  CORE_CODE_SDRAM&t;0x803
DECL|macro|CORE_CODE_PCI
mdefine_line|#define  CORE_CODE_PCI&t;&t;0x804
DECL|macro|CORE_CODE_MIPS
mdefine_line|#define  CORE_CODE_MIPS&t;&t;0x805
DECL|macro|CORE_CODE_ENET
mdefine_line|#define  CORE_CODE_ENET&t;&t;0x806
DECL|macro|CORE_CODE_CODEC
mdefine_line|#define  CORE_CODE_CODEC&t;0x807
DECL|macro|CORE_CODE_USB
mdefine_line|#define  CORE_CODE_USB&t;&t;0x808
DECL|macro|CORE_CODE_ILINE100
mdefine_line|#define  CORE_CODE_ILINE100&t;0x80a
DECL|macro|CORE_CODE_EXTIF
mdefine_line|#define  CORE_CODE_EXTIF&t;0x811
multiline_comment|/* SSB PCI config space registers.  */
DECL|macro|SSB_BAR0_WIN
mdefine_line|#define&t;SSB_BAR0_WIN&t;&t;0x80
DECL|macro|SSB_BAR1_WIN
mdefine_line|#define&t;SSB_BAR1_WIN&t;&t;0x84
DECL|macro|SSB_SPROM_CONTROL
mdefine_line|#define&t;SSB_SPROM_CONTROL&t;0x88
DECL|macro|SSB_BAR1_CONTROL
mdefine_line|#define&t;SSB_BAR1_CONTROL&t;0x8c
multiline_comment|/* SSB core and hsot control registers.  */
DECL|macro|SSB_CONTROL
mdefine_line|#define SSB_CONTROL&t;&t;0x0000UL
DECL|macro|SSB_ARBCONTROL
mdefine_line|#define SSB_ARBCONTROL&t;&t;0x0010UL
DECL|macro|SSB_ISTAT
mdefine_line|#define SSB_ISTAT&t;&t;0x0020UL
DECL|macro|SSB_IMASK
mdefine_line|#define SSB_IMASK&t;&t;0x0024UL
DECL|macro|SSB_MBOX
mdefine_line|#define SSB_MBOX&t;&t;0x0028UL
DECL|macro|SSB_BCAST_ADDR
mdefine_line|#define SSB_BCAST_ADDR&t;&t;0x0050UL
DECL|macro|SSB_BCAST_DATA
mdefine_line|#define SSB_BCAST_DATA&t;&t;0x0054UL
DECL|macro|SSB_PCI_TRANS_0
mdefine_line|#define SSB_PCI_TRANS_0&t;&t;0x0100UL
DECL|macro|SSB_PCI_TRANS_1
mdefine_line|#define SSB_PCI_TRANS_1&t;&t;0x0104UL
DECL|macro|SSB_PCI_TRANS_2
mdefine_line|#define SSB_PCI_TRANS_2&t;&t;0x0108UL
DECL|macro|SSB_SPROM
mdefine_line|#define SSB_SPROM&t;&t;0x0800UL
DECL|macro|SSB_PCI_MEM
mdefine_line|#define SSB_PCI_MEM&t;&t;0x00000000
DECL|macro|SSB_PCI_IO
mdefine_line|#define SSB_PCI_IO&t;&t;0x00000001
DECL|macro|SSB_PCI_CFG0
mdefine_line|#define SSB_PCI_CFG0&t;&t;0x00000002
DECL|macro|SSB_PCI_CFG1
mdefine_line|#define SSB_PCI_CFG1&t;&t;0x00000003
DECL|macro|SSB_PCI_PREF
mdefine_line|#define SSB_PCI_PREF&t;&t;0x00000004
DECL|macro|SSB_PCI_BURST
mdefine_line|#define SSB_PCI_BURST&t;&t;0x00000008
DECL|macro|SSB_PCI_MASK0
mdefine_line|#define SSB_PCI_MASK0&t;&t;0xfc000000
DECL|macro|SSB_PCI_MASK1
mdefine_line|#define SSB_PCI_MASK1&t;&t;0xfc000000
DECL|macro|SSB_PCI_MASK2
mdefine_line|#define SSB_PCI_MASK2&t;&t;0xc0000000
DECL|macro|br32
mdefine_line|#define br32(REG)&t;readl(bp-&gt;regs + (REG))
DECL|macro|bw32
mdefine_line|#define bw32(REG,VAL)&t;writel((VAL), bp-&gt;regs + (REG))
multiline_comment|/* 4400 PHY registers */
DECL|macro|B44_MII_AUXCTRL
mdefine_line|#define B44_MII_AUXCTRL&t;&t;24&t;/* Auxiliary Control */
DECL|macro|MII_AUXCTRL_DUPLEX
mdefine_line|#define  MII_AUXCTRL_DUPLEX&t;0x0001  /* Full Duplex */
DECL|macro|MII_AUXCTRL_SPEED
mdefine_line|#define  MII_AUXCTRL_SPEED&t;0x0002  /* 1=100Mbps, 0=10Mbps */
DECL|macro|MII_AUXCTRL_FORCED
mdefine_line|#define  MII_AUXCTRL_FORCED&t;0x0004&t;/* Forced 10/100 */
DECL|macro|B44_MII_ALEDCTRL
mdefine_line|#define B44_MII_ALEDCTRL&t;26&t;/* Activity LED */
DECL|macro|MII_ALEDCTRL_ALLMSK
mdefine_line|#define  MII_ALEDCTRL_ALLMSK&t;0x7fff
DECL|macro|B44_MII_TLEDCTRL
mdefine_line|#define B44_MII_TLEDCTRL&t;27&t;/* Traffic Meter LED */
DECL|macro|MII_TLEDCTRL_ENABLE
mdefine_line|#define  MII_TLEDCTRL_ENABLE&t;0x0040
multiline_comment|/* XXX Add this to mii.h */
macro_line|#ifndef ADVERTISE_PAUSE
DECL|macro|ADVERTISE_PAUSE_CAP
mdefine_line|#define ADVERTISE_PAUSE_CAP&t;&t;0x0400
macro_line|#endif
macro_line|#ifndef ADVERTISE_PAUSE_ASYM
DECL|macro|ADVERTISE_PAUSE_ASYM
mdefine_line|#define ADVERTISE_PAUSE_ASYM&t;&t;0x0800
macro_line|#endif
macro_line|#ifndef LPA_PAUSE
DECL|macro|LPA_PAUSE_CAP
mdefine_line|#define LPA_PAUSE_CAP&t;&t;&t;0x0400
macro_line|#endif
macro_line|#ifndef LPA_PAUSE_ASYM
DECL|macro|LPA_PAUSE_ASYM
mdefine_line|#define LPA_PAUSE_ASYM&t;&t;&t;0x0800
macro_line|#endif
DECL|struct|dma_desc
r_struct
id|dma_desc
(brace
DECL|member|ctrl
id|u32
id|ctrl
suffix:semicolon
DECL|member|addr
id|u32
id|addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* There are only 12 bits in the DMA engine for descriptor offsetting&n; * so the table must be aligned on a boundary of this.&n; */
DECL|macro|DMA_TABLE_BYTES
mdefine_line|#define DMA_TABLE_BYTES&t;&t;4096
DECL|macro|DESC_CTRL_LEN
mdefine_line|#define DESC_CTRL_LEN&t;0x00001fff
DECL|macro|DESC_CTRL_CMASK
mdefine_line|#define DESC_CTRL_CMASK&t;0x0ff00000 /* Core specific bits */
DECL|macro|DESC_CTRL_EOT
mdefine_line|#define DESC_CTRL_EOT&t;0x10000000 /* End of Table */
DECL|macro|DESC_CTRL_IOC
mdefine_line|#define DESC_CTRL_IOC&t;0x20000000 /* Interrupt On Completion */
DECL|macro|DESC_CTRL_EOF
mdefine_line|#define DESC_CTRL_EOF&t;0x40000000 /* End of Frame */
DECL|macro|DESC_CTRL_SOF
mdefine_line|#define DESC_CTRL_SOF&t;0x80000000 /* Start of Frame */
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  &t;256
DECL|struct|rx_header
r_struct
id|rx_header
(brace
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|pad
id|u16
id|pad
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RX_HEADER_LEN
mdefine_line|#define RX_HEADER_LEN&t;28
DECL|macro|RX_FLAG_OFIFO
mdefine_line|#define RX_FLAG_OFIFO&t;0x00000001 /* FIFO Overflow */
DECL|macro|RX_FLAG_CRCERR
mdefine_line|#define RX_FLAG_CRCERR&t;0x00000002 /* CRC Error */
DECL|macro|RX_FLAG_SERR
mdefine_line|#define RX_FLAG_SERR&t;0x00000004 /* Receive Symbol Error */
DECL|macro|RX_FLAG_ODD
mdefine_line|#define RX_FLAG_ODD&t;0x00000008 /* Frame has odd number of nibbles */
DECL|macro|RX_FLAG_LARGE
mdefine_line|#define RX_FLAG_LARGE&t;0x00000010 /* Frame is &gt; RX MAX Length */
DECL|macro|RX_FLAG_MCAST
mdefine_line|#define RX_FLAG_MCAST&t;0x00000020 /* Dest is Multicast Address */
DECL|macro|RX_FLAG_BCAST
mdefine_line|#define RX_FLAG_BCAST&t;0x00000040 /* Dest is Broadcast Address */
DECL|macro|RX_FLAG_MISS
mdefine_line|#define RX_FLAG_MISS&t;0x00000080 /* Received due to promisc mode */
DECL|macro|RX_FLAG_LAST
mdefine_line|#define RX_FLAG_LAST&t;0x00000800 /* Last buffer in frame */
DECL|macro|RX_FLAG_ERRORS
mdefine_line|#define RX_FLAG_ERRORS&t;(RX_FLAG_ODD | RX_FLAG_SERR | RX_FLAG_CRCERR | RX_FLAG_OFIFO)
DECL|struct|ring_info
r_struct
id|ring_info
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|DECLARE_PCI_UNMAP_ADDR
c_func
(paren
id|mapping
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|B44_MCAST_TABLE_SIZE
mdefine_line|#define B44_MCAST_TABLE_SIZE&t;32
multiline_comment|/* SW copy of device statistics, kept up to date by periodic timer&n; * which probes HW values.  Must have same relative layout as HW&n; * register above, because b44_stats_update depends upon this.&n; */
DECL|struct|b44_hw_stats
r_struct
id|b44_hw_stats
(brace
DECL|member|tx_good_octets
DECL|member|tx_good_pkts
DECL|member|tx_octets
id|u32
id|tx_good_octets
comma
id|tx_good_pkts
comma
id|tx_octets
suffix:semicolon
DECL|member|tx_pkts
DECL|member|tx_broadcast_pkts
DECL|member|tx_multicast_pkts
id|u32
id|tx_pkts
comma
id|tx_broadcast_pkts
comma
id|tx_multicast_pkts
suffix:semicolon
DECL|member|tx_len_64
DECL|member|tx_len_65_to_127
DECL|member|tx_len_128_to_255
id|u32
id|tx_len_64
comma
id|tx_len_65_to_127
comma
id|tx_len_128_to_255
suffix:semicolon
DECL|member|tx_len_256_to_511
DECL|member|tx_len_512_to_1023
DECL|member|tx_len_1024_to_max
id|u32
id|tx_len_256_to_511
comma
id|tx_len_512_to_1023
comma
id|tx_len_1024_to_max
suffix:semicolon
DECL|member|tx_jabber_pkts
DECL|member|tx_oversize_pkts
DECL|member|tx_fragment_pkts
id|u32
id|tx_jabber_pkts
comma
id|tx_oversize_pkts
comma
id|tx_fragment_pkts
suffix:semicolon
DECL|member|tx_underruns
DECL|member|tx_total_cols
DECL|member|tx_single_cols
id|u32
id|tx_underruns
comma
id|tx_total_cols
comma
id|tx_single_cols
suffix:semicolon
DECL|member|tx_multiple_cols
DECL|member|tx_excessive_cols
DECL|member|tx_late_cols
id|u32
id|tx_multiple_cols
comma
id|tx_excessive_cols
comma
id|tx_late_cols
suffix:semicolon
DECL|member|tx_defered
DECL|member|tx_carrier_lost
DECL|member|tx_pause_pkts
id|u32
id|tx_defered
comma
id|tx_carrier_lost
comma
id|tx_pause_pkts
suffix:semicolon
DECL|member|__pad1
id|u32
id|__pad1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|rx_good_octets
DECL|member|rx_good_pkts
DECL|member|rx_octets
id|u32
id|rx_good_octets
comma
id|rx_good_pkts
comma
id|rx_octets
suffix:semicolon
DECL|member|rx_pkts
DECL|member|rx_broadcast_pkts
DECL|member|rx_multicast_pkts
id|u32
id|rx_pkts
comma
id|rx_broadcast_pkts
comma
id|rx_multicast_pkts
suffix:semicolon
DECL|member|rx_len_64
DECL|member|rx_len_65_to_127
DECL|member|rx_len_128_to_255
id|u32
id|rx_len_64
comma
id|rx_len_65_to_127
comma
id|rx_len_128_to_255
suffix:semicolon
DECL|member|rx_len_256_to_511
DECL|member|rx_len_512_to_1023
DECL|member|rx_len_1024_to_max
id|u32
id|rx_len_256_to_511
comma
id|rx_len_512_to_1023
comma
id|rx_len_1024_to_max
suffix:semicolon
DECL|member|rx_jabber_pkts
DECL|member|rx_oversize_pkts
DECL|member|rx_fragment_pkts
id|u32
id|rx_jabber_pkts
comma
id|rx_oversize_pkts
comma
id|rx_fragment_pkts
suffix:semicolon
DECL|member|rx_missed_pkts
DECL|member|rx_crc_align_errs
DECL|member|rx_undersize
id|u32
id|rx_missed_pkts
comma
id|rx_crc_align_errs
comma
id|rx_undersize
suffix:semicolon
DECL|member|rx_crc_errs
DECL|member|rx_align_errs
DECL|member|rx_symbol_errs
id|u32
id|rx_crc_errs
comma
id|rx_align_errs
comma
id|rx_symbol_errs
suffix:semicolon
DECL|member|rx_pause_pkts
DECL|member|rx_nonpause_pkts
id|u32
id|rx_pause_pkts
comma
id|rx_nonpause_pkts
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|b44
r_struct
id|b44
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|imask
DECL|member|istat
id|u32
id|imask
comma
id|istat
suffix:semicolon
DECL|member|rx_ring
DECL|member|tx_ring
r_struct
id|dma_desc
op_star
id|rx_ring
comma
op_star
id|tx_ring
suffix:semicolon
DECL|member|tx_prod
DECL|member|tx_cons
id|u32
id|tx_prod
comma
id|tx_cons
suffix:semicolon
DECL|member|rx_prod
DECL|member|rx_cons
id|u32
id|rx_prod
comma
id|rx_cons
suffix:semicolon
DECL|member|rx_buffers
r_struct
id|ring_info
op_star
id|rx_buffers
suffix:semicolon
DECL|member|tx_buffers
r_struct
id|ring_info
op_star
id|tx_buffers
suffix:semicolon
DECL|member|dma_offset
id|u32
id|dma_offset
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|macro|B44_FLAG_INIT_COMPLETE
mdefine_line|#define B44_FLAG_INIT_COMPLETE&t;0x00000001
DECL|macro|B44_FLAG_BUGGY_TXPTR
mdefine_line|#define B44_FLAG_BUGGY_TXPTR&t;0x00000002
DECL|macro|B44_FLAG_REORDER_BUG
mdefine_line|#define B44_FLAG_REORDER_BUG&t;0x00000004
DECL|macro|B44_FLAG_PAUSE_AUTO
mdefine_line|#define B44_FLAG_PAUSE_AUTO&t;0x00008000
DECL|macro|B44_FLAG_FULL_DUPLEX
mdefine_line|#define B44_FLAG_FULL_DUPLEX&t;0x00010000
DECL|macro|B44_FLAG_100_BASE_T
mdefine_line|#define B44_FLAG_100_BASE_T&t;0x00020000
DECL|macro|B44_FLAG_TX_PAUSE
mdefine_line|#define B44_FLAG_TX_PAUSE&t;0x00040000
DECL|macro|B44_FLAG_RX_PAUSE
mdefine_line|#define B44_FLAG_RX_PAUSE&t;0x00080000
DECL|macro|B44_FLAG_FORCE_LINK
mdefine_line|#define B44_FLAG_FORCE_LINK&t;0x00100000
DECL|macro|B44_FLAG_ADV_10HALF
mdefine_line|#define B44_FLAG_ADV_10HALF&t;0x01000000
DECL|macro|B44_FLAG_ADV_10FULL
mdefine_line|#define B44_FLAG_ADV_10FULL&t;0x02000000
DECL|macro|B44_FLAG_ADV_100HALF
mdefine_line|#define B44_FLAG_ADV_100HALF&t;0x04000000
DECL|macro|B44_FLAG_ADV_100FULL
mdefine_line|#define B44_FLAG_ADV_100FULL&t;0x08000000
DECL|macro|B44_FLAG_INTERNAL_PHY
mdefine_line|#define B44_FLAG_INTERNAL_PHY&t;0x10000000
DECL|member|rx_offset
id|u32
id|rx_offset
suffix:semicolon
DECL|member|msg_enable
id|u32
id|msg_enable
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|hw_stats
r_struct
id|b44_hw_stats
id|hw_stats
suffix:semicolon
DECL|member|regs
r_int
r_int
id|regs
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
DECL|member|rx_ring_dma
DECL|member|tx_ring_dma
id|dma_addr_t
id|rx_ring_dma
comma
id|tx_ring_dma
suffix:semicolon
DECL|member|rx_pending
id|u32
id|rx_pending
suffix:semicolon
DECL|member|tx_pending
id|u32
id|tx_pending
suffix:semicolon
DECL|member|pci_cfg_state
id|u32
id|pci_cfg_state
(braket
l_int|64
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
DECL|member|phy_addr
id|u8
id|phy_addr
suffix:semicolon
DECL|member|mdc_port
id|u8
id|mdc_port
suffix:semicolon
DECL|member|core_unit
id|u8
id|core_unit
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _B44_H */
eof
