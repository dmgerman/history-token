macro_line|#ifndef TLAN_H
DECL|macro|TLAN_H
mdefine_line|#define TLAN_H
multiline_comment|/********************************************************************&n; *&n; *  Linux ThunderLAN Driver&n; *&n; *  tlan.h&n; *  by James Banks&n; *&n; *  (C) 1997-1998 Caldera, Inc.&n; *  (C) 1999-2001 Torben Mathiasen&n; * &n; *  This software may be used and distributed according to the terms&n; *  of the GNU General Public License, incorporated herein by reference.&n; *&n; ** This file is best viewed/edited with tabstop=4, colums&gt;=132&n; *&n; *  &n; *  Dec 10, 1999&t;Torben Mathiasen &lt;torben.mathiasen@compaq.com&gt;&n; *&t;&t;&t;New Maintainer&n; *&n; ********************************************************************/
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
multiline_comment|/*****************************************************************&n;&t; * TLan Definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|FALSE
mdefine_line|#define FALSE&t;&t;&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;&t;&t;1
DECL|macro|TLAN_MIN_FRAME_SIZE
mdefine_line|#define TLAN_MIN_FRAME_SIZE&t;64
DECL|macro|TLAN_MAX_FRAME_SIZE
mdefine_line|#define TLAN_MAX_FRAME_SIZE&t;1600
DECL|macro|TLAN_NUM_RX_LISTS
mdefine_line|#define TLAN_NUM_RX_LISTS&t;32
DECL|macro|TLAN_NUM_TX_LISTS
mdefine_line|#define TLAN_NUM_TX_LISTS&t;64
DECL|macro|TLAN_IGNORE
mdefine_line|#define TLAN_IGNORE&t;&t;0
DECL|macro|TLAN_RECORD
mdefine_line|#define TLAN_RECORD&t;&t;1
DECL|macro|TLAN_DBG
mdefine_line|#define TLAN_DBG(lvl, format, args...)&t;if (debug&amp;lvl) printk(KERN_DEBUG &quot;TLAN: &quot; format, ##args );
DECL|macro|TLAN_DEBUG_GNRL
mdefine_line|#define TLAN_DEBUG_GNRL&t;&t;0x0001
DECL|macro|TLAN_DEBUG_TX
mdefine_line|#define TLAN_DEBUG_TX&t;&t;0x0002
DECL|macro|TLAN_DEBUG_RX
mdefine_line|#define TLAN_DEBUG_RX&t;&t;0x0004 
DECL|macro|TLAN_DEBUG_LIST
mdefine_line|#define TLAN_DEBUG_LIST&t;&t;0x0008
DECL|macro|TLAN_DEBUG_PROBE
mdefine_line|#define TLAN_DEBUG_PROBE&t;0x0010
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT&t;&t;(10*HZ)&t; /* We need time for auto-neg */
DECL|macro|MAX_TLAN_BOARDS
mdefine_line|#define MAX_TLAN_BOARDS&t;&t;8&t; /* Max number of boards installed at a time */
multiline_comment|/*****************************************************************&n;&t; * Device Identification Definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|PCI_DEVICE_ID_NETELLIGENT_10
mdefine_line|#define PCI_DEVICE_ID_NETELLIGENT_10&t;&t;&t;0xAE34
DECL|macro|PCI_DEVICE_ID_NETELLIGENT_10_100
mdefine_line|#define PCI_DEVICE_ID_NETELLIGENT_10_100&t;&t;0xAE32
DECL|macro|PCI_DEVICE_ID_NETFLEX_3P_INTEGRATED
mdefine_line|#define PCI_DEVICE_ID_NETFLEX_3P_INTEGRATED&t;&t;0xAE35
DECL|macro|PCI_DEVICE_ID_NETFLEX_3P
mdefine_line|#define PCI_DEVICE_ID_NETFLEX_3P&t;&t;&t;0xF130
DECL|macro|PCI_DEVICE_ID_NETFLEX_3P_BNC
mdefine_line|#define PCI_DEVICE_ID_NETFLEX_3P_BNC&t;&t;&t;0xF150
DECL|macro|PCI_DEVICE_ID_NETELLIGENT_10_100_PROLIANT
mdefine_line|#define PCI_DEVICE_ID_NETELLIGENT_10_100_PROLIANT&t;0xAE43
DECL|macro|PCI_DEVICE_ID_NETELLIGENT_10_100_DUAL
mdefine_line|#define PCI_DEVICE_ID_NETELLIGENT_10_100_DUAL&t;&t;0xAE40
DECL|macro|PCI_DEVICE_ID_DESKPRO_4000_5233MMX
mdefine_line|#define PCI_DEVICE_ID_DESKPRO_4000_5233MMX&t;&t;0xB011
DECL|macro|PCI_DEVICE_ID_NETELLIGENT_10_T2
mdefine_line|#define PCI_DEVICE_ID_NETELLIGENT_10_T2&t;&t;&t;0xB012
DECL|macro|PCI_DEVICE_ID_NETELLIGENT_10_100_WS_5100
mdefine_line|#define PCI_DEVICE_ID_NETELLIGENT_10_100_WS_5100&t;0xB030
macro_line|#ifndef PCI_DEVICE_ID_OLICOM_OC2183
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2183
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2183&t;&t;&t;0x0013
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_OLICOM_OC2325
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2325
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2325&t;&t;&t;0x0012
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_OLICOM_OC2326
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2326
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2326&t;&t;&t;0x0014
macro_line|#endif
DECL|struct|tlan_adapter_entry
r_typedef
r_struct
id|tlan_adapter_entry
(brace
DECL|member|vendorId
id|u16
id|vendorId
suffix:semicolon
DECL|member|deviceId
id|u16
id|deviceId
suffix:semicolon
DECL|member|deviceLabel
r_char
op_star
id|deviceLabel
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|addrOfs
id|u16
id|addrOfs
suffix:semicolon
DECL|typedef|TLanAdapterEntry
)brace
id|TLanAdapterEntry
suffix:semicolon
DECL|macro|TLAN_ADAPTER_NONE
mdefine_line|#define TLAN_ADAPTER_NONE&t;&t;0x00000000
DECL|macro|TLAN_ADAPTER_UNMANAGED_PHY
mdefine_line|#define TLAN_ADAPTER_UNMANAGED_PHY&t;0x00000001
DECL|macro|TLAN_ADAPTER_BIT_RATE_PHY
mdefine_line|#define TLAN_ADAPTER_BIT_RATE_PHY&t;0x00000002
DECL|macro|TLAN_ADAPTER_USE_INTERN_10
mdefine_line|#define TLAN_ADAPTER_USE_INTERN_10&t;0x00000004
DECL|macro|TLAN_ADAPTER_ACTIVITY_LED
mdefine_line|#define TLAN_ADAPTER_ACTIVITY_LED&t;0x00000008
DECL|macro|TLAN_SPEED_DEFAULT
mdefine_line|#define TLAN_SPEED_DEFAULT&t;0
DECL|macro|TLAN_SPEED_10
mdefine_line|#define TLAN_SPEED_10&t;&t;10
DECL|macro|TLAN_SPEED_100
mdefine_line|#define TLAN_SPEED_100&t;&t;100
DECL|macro|TLAN_DUPLEX_DEFAULT
mdefine_line|#define TLAN_DUPLEX_DEFAULT&t;0
DECL|macro|TLAN_DUPLEX_HALF
mdefine_line|#define TLAN_DUPLEX_HALF&t;1
DECL|macro|TLAN_DUPLEX_FULL
mdefine_line|#define TLAN_DUPLEX_FULL&t;2
multiline_comment|/*****************************************************************&n;&t; * EISA Definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|EISA_ID
mdefine_line|#define EISA_ID      0xc80   /* EISA ID Registers */ 
DECL|macro|EISA_ID0
mdefine_line|#define EISA_ID0     0xc80   /* EISA ID Register 0 */ 
DECL|macro|EISA_ID1
mdefine_line|#define EISA_ID1     0xc81   /* EISA ID Register 1 */ 
DECL|macro|EISA_ID2
mdefine_line|#define EISA_ID2     0xc82   /* EISA ID Register 2 */ 
DECL|macro|EISA_ID3
mdefine_line|#define EISA_ID3     0xc83   /* EISA ID Register 3 */ 
DECL|macro|EISA_CR
mdefine_line|#define EISA_CR      0xc84   /* EISA Control Register */
DECL|macro|EISA_REG0
mdefine_line|#define EISA_REG0    0xc88   /* EISA Configuration Register 0 */
DECL|macro|EISA_REG1
mdefine_line|#define EISA_REG1    0xc89   /* EISA Configuration Register 1 */
DECL|macro|EISA_REG2
mdefine_line|#define EISA_REG2    0xc8a   /* EISA Configuration Register 2 */
DECL|macro|EISA_REG3
mdefine_line|#define EISA_REG3    0xc8f   /* EISA Configuration Register 3 */
DECL|macro|EISA_APROM
mdefine_line|#define EISA_APROM   0xc90   /* Ethernet Address PROM */
multiline_comment|/*****************************************************************&n;&t; * Rx/Tx List Definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|TLAN_BUFFERS_PER_LIST
mdefine_line|#define TLAN_BUFFERS_PER_LIST&t;10
DECL|macro|TLAN_LAST_BUFFER
mdefine_line|#define TLAN_LAST_BUFFER&t;0x80000000
DECL|macro|TLAN_CSTAT_UNUSED
mdefine_line|#define TLAN_CSTAT_UNUSED&t;0x8000
DECL|macro|TLAN_CSTAT_FRM_CMP
mdefine_line|#define TLAN_CSTAT_FRM_CMP&t;0x4000
DECL|macro|TLAN_CSTAT_READY
mdefine_line|#define TLAN_CSTAT_READY&t;0x3000
DECL|macro|TLAN_CSTAT_EOC
mdefine_line|#define TLAN_CSTAT_EOC&t;&t;0x0800
DECL|macro|TLAN_CSTAT_RX_ERROR
mdefine_line|#define TLAN_CSTAT_RX_ERROR&t;0x0400
DECL|macro|TLAN_CSTAT_PASS_CRC
mdefine_line|#define TLAN_CSTAT_PASS_CRC&t;0x0200
DECL|macro|TLAN_CSTAT_DP_PR
mdefine_line|#define TLAN_CSTAT_DP_PR&t;0x0100
DECL|struct|tlan_buffer_ref_tag
r_typedef
r_struct
id|tlan_buffer_ref_tag
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|typedef|TLanBufferRef
)brace
id|TLanBufferRef
suffix:semicolon
DECL|struct|tlan_list_tag
r_typedef
r_struct
id|tlan_list_tag
(brace
DECL|member|forward
id|u32
id|forward
suffix:semicolon
DECL|member|cStat
id|u16
id|cStat
suffix:semicolon
DECL|member|frameSize
id|u16
id|frameSize
suffix:semicolon
DECL|member|buffer
id|TLanBufferRef
id|buffer
(braket
id|TLAN_BUFFERS_PER_LIST
)braket
suffix:semicolon
DECL|typedef|TLanList
)brace
id|TLanList
suffix:semicolon
DECL|typedef|TLanBuffer
r_typedef
id|u8
id|TLanBuffer
(braket
id|TLAN_MAX_FRAME_SIZE
)braket
suffix:semicolon
multiline_comment|/*****************************************************************&n;&t; * PHY definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|TLAN_PHY_MAX_ADDR
mdefine_line|#define TLAN_PHY_MAX_ADDR&t;0x1F
DECL|macro|TLAN_PHY_NONE
mdefine_line|#define TLAN_PHY_NONE&t;&t;0x20
multiline_comment|/*****************************************************************&n;&t; * TLAN Private Information Structure&n;&t; *&n;&t; ****************************************************************/
DECL|struct|tlan_private_tag
r_typedef
r_struct
id|tlan_private_tag
(brace
DECL|member|nextDevice
r_struct
id|net_device
op_star
id|nextDevice
suffix:semicolon
DECL|member|dmaStorage
r_void
op_star
id|dmaStorage
suffix:semicolon
DECL|member|padBuffer
id|u8
op_star
id|padBuffer
suffix:semicolon
DECL|member|rxList
id|TLanList
op_star
id|rxList
suffix:semicolon
DECL|member|rxBuffer
id|u8
op_star
id|rxBuffer
suffix:semicolon
DECL|member|rxHead
id|u32
id|rxHead
suffix:semicolon
DECL|member|rxTail
id|u32
id|rxTail
suffix:semicolon
DECL|member|rxEocCount
id|u32
id|rxEocCount
suffix:semicolon
DECL|member|txList
id|TLanList
op_star
id|txList
suffix:semicolon
DECL|member|txBuffer
id|u8
op_star
id|txBuffer
suffix:semicolon
DECL|member|txHead
id|u32
id|txHead
suffix:semicolon
DECL|member|txInProgress
id|u32
id|txInProgress
suffix:semicolon
DECL|member|txTail
id|u32
id|txTail
suffix:semicolon
DECL|member|txBusyCount
id|u32
id|txBusyCount
suffix:semicolon
DECL|member|phyOnline
id|u32
id|phyOnline
suffix:semicolon
DECL|member|timerSetAt
id|u32
id|timerSetAt
suffix:semicolon
DECL|member|timerType
id|u32
id|timerType
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
DECL|member|adapter
r_struct
id|board
op_star
id|adapter
suffix:semicolon
DECL|member|adapterRev
id|u32
id|adapterRev
suffix:semicolon
DECL|member|aui
id|u32
id|aui
suffix:semicolon
DECL|member|debug
id|u32
id|debug
suffix:semicolon
DECL|member|duplex
id|u32
id|duplex
suffix:semicolon
DECL|member|phy
id|u32
id|phy
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|phyNum
id|u32
id|phyNum
suffix:semicolon
DECL|member|speed
id|u32
id|speed
suffix:semicolon
DECL|member|tlanRev
id|u8
id|tlanRev
suffix:semicolon
DECL|member|tlanFullDuplex
id|u8
id|tlanFullDuplex
suffix:semicolon
DECL|member|devName
r_char
id|devName
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|link
id|u8
id|link
suffix:semicolon
DECL|member|is_eisa
id|u8
id|is_eisa
suffix:semicolon
DECL|member|tlan_tqueue
r_struct
id|tq_struct
id|tlan_tqueue
suffix:semicolon
DECL|member|neg_be_verbose
id|u8
id|neg_be_verbose
suffix:semicolon
DECL|typedef|TLanPrivateInfo
)brace
id|TLanPrivateInfo
suffix:semicolon
multiline_comment|/*****************************************************************&n;&t; * TLan Driver Timer Definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|TLAN_TIMER_LINK_BEAT
mdefine_line|#define TLAN_TIMER_LINK_BEAT&t;&t;1
DECL|macro|TLAN_TIMER_ACTIVITY
mdefine_line|#define TLAN_TIMER_ACTIVITY&t;&t;2
DECL|macro|TLAN_TIMER_PHY_PDOWN
mdefine_line|#define TLAN_TIMER_PHY_PDOWN&t;&t;3
DECL|macro|TLAN_TIMER_PHY_PUP
mdefine_line|#define TLAN_TIMER_PHY_PUP&t;&t;4
DECL|macro|TLAN_TIMER_PHY_RESET
mdefine_line|#define TLAN_TIMER_PHY_RESET&t;&t;5
DECL|macro|TLAN_TIMER_PHY_START_LINK
mdefine_line|#define TLAN_TIMER_PHY_START_LINK&t;6
DECL|macro|TLAN_TIMER_PHY_FINISH_AN
mdefine_line|#define TLAN_TIMER_PHY_FINISH_AN&t;7
DECL|macro|TLAN_TIMER_FINISH_RESET
mdefine_line|#define TLAN_TIMER_FINISH_RESET&t;&t;8
DECL|macro|TLAN_TIMER_ACT_DELAY
mdefine_line|#define TLAN_TIMER_ACT_DELAY&t;&t;(HZ/10)
multiline_comment|/*****************************************************************&n;&t; * TLan Driver Eeprom Definitions&n;&t; *&n;&t; ****************************************************************/
DECL|macro|TLAN_EEPROM_ACK
mdefine_line|#define TLAN_EEPROM_ACK&t;&t;0
DECL|macro|TLAN_EEPROM_STOP
mdefine_line|#define TLAN_EEPROM_STOP&t;1
multiline_comment|/*****************************************************************&n;&t; * Host Register Offsets and Contents&n;&t; *&n;&t; ****************************************************************/
DECL|macro|TLAN_HOST_CMD
mdefine_line|#define TLAN_HOST_CMD&t;&t;&t;0x00
DECL|macro|TLAN_HC_GO
mdefine_line|#define &t;TLAN_HC_GO&t;&t;0x80000000
DECL|macro|TLAN_HC_STOP
mdefine_line|#define&t;&t;TLAN_HC_STOP&t;&t;0x40000000
DECL|macro|TLAN_HC_ACK
mdefine_line|#define&t;&t;TLAN_HC_ACK&t;&t;0x20000000
DECL|macro|TLAN_HC_CS_MASK
mdefine_line|#define&t;&t;TLAN_HC_CS_MASK&t;&t;0x1FE00000
DECL|macro|TLAN_HC_EOC
mdefine_line|#define&t;&t;TLAN_HC_EOC&t;&t;0x00100000
DECL|macro|TLAN_HC_RT
mdefine_line|#define&t;&t;TLAN_HC_RT&t;&t;0x00080000
DECL|macro|TLAN_HC_NES
mdefine_line|#define&t;&t;TLAN_HC_NES&t;&t;0x00040000
DECL|macro|TLAN_HC_AD_RST
mdefine_line|#define&t;&t;TLAN_HC_AD_RST&t;&t;0x00008000
DECL|macro|TLAN_HC_LD_TMR
mdefine_line|#define&t;&t;TLAN_HC_LD_TMR&t;&t;0x00004000
DECL|macro|TLAN_HC_LD_THR
mdefine_line|#define&t;&t;TLAN_HC_LD_THR&t;&t;0x00002000
DECL|macro|TLAN_HC_REQ_INT
mdefine_line|#define&t;&t;TLAN_HC_REQ_INT&t;&t;0x00001000
DECL|macro|TLAN_HC_INT_OFF
mdefine_line|#define&t;&t;TLAN_HC_INT_OFF&t;&t;0x00000800
DECL|macro|TLAN_HC_INT_ON
mdefine_line|#define&t;&t;TLAN_HC_INT_ON&t;&t;0x00000400
DECL|macro|TLAN_HC_AC_MASK
mdefine_line|#define&t;&t;TLAN_HC_AC_MASK&t;&t;0x000000FF
DECL|macro|TLAN_CH_PARM
mdefine_line|#define TLAN_CH_PARM&t;&t;&t;0x04
DECL|macro|TLAN_DIO_ADR
mdefine_line|#define TLAN_DIO_ADR&t;&t;&t;0x08
DECL|macro|TLAN_DA_ADR_INC
mdefine_line|#define&t;&t;TLAN_DA_ADR_INC&t;&t;0x8000
DECL|macro|TLAN_DA_RAM_ADR
mdefine_line|#define&t;&t;TLAN_DA_RAM_ADR&t;&t;0x4000
DECL|macro|TLAN_HOST_INT
mdefine_line|#define TLAN_HOST_INT&t;&t;&t;0x0A
DECL|macro|TLAN_HI_IV_MASK
mdefine_line|#define&t;&t;TLAN_HI_IV_MASK&t;&t;0x1FE0
DECL|macro|TLAN_HI_IT_MASK
mdefine_line|#define&t;&t;TLAN_HI_IT_MASK&t;&t;0x001C
DECL|macro|TLAN_DIO_DATA
mdefine_line|#define TLAN_DIO_DATA&t;&t;&t;0x0C
multiline_comment|/* ThunderLAN Internal Register DIO Offsets */
DECL|macro|TLAN_NET_CMD
mdefine_line|#define TLAN_NET_CMD&t;&t;&t;0x00
DECL|macro|TLAN_NET_CMD_NRESET
mdefine_line|#define&t;&t;TLAN_NET_CMD_NRESET&t;0x80
DECL|macro|TLAN_NET_CMD_NWRAP
mdefine_line|#define&t;&t;TLAN_NET_CMD_NWRAP&t;0x40
DECL|macro|TLAN_NET_CMD_CSF
mdefine_line|#define&t;&t;TLAN_NET_CMD_CSF&t;0x20
DECL|macro|TLAN_NET_CMD_CAF
mdefine_line|#define&t;&t;TLAN_NET_CMD_CAF&t;0x10
DECL|macro|TLAN_NET_CMD_NOBRX
mdefine_line|#define&t;&t;TLAN_NET_CMD_NOBRX&t;0x08
DECL|macro|TLAN_NET_CMD_DUPLEX
mdefine_line|#define&t;&t;TLAN_NET_CMD_DUPLEX&t;0x04
DECL|macro|TLAN_NET_CMD_TRFRAM
mdefine_line|#define&t;&t;TLAN_NET_CMD_TRFRAM&t;0x02
DECL|macro|TLAN_NET_CMD_TXPACE
mdefine_line|#define&t;&t;TLAN_NET_CMD_TXPACE&t;0x01
DECL|macro|TLAN_NET_SIO
mdefine_line|#define TLAN_NET_SIO&t;&t;&t;0x01
DECL|macro|TLAN_NET_SIO_MINTEN
mdefine_line|#define &t;TLAN_NET_SIO_MINTEN&t;0x80
DECL|macro|TLAN_NET_SIO_ECLOK
mdefine_line|#define&t;&t;TLAN_NET_SIO_ECLOK&t;0x40
DECL|macro|TLAN_NET_SIO_ETXEN
mdefine_line|#define&t;&t;TLAN_NET_SIO_ETXEN&t;0x20
DECL|macro|TLAN_NET_SIO_EDATA
mdefine_line|#define&t;&t;TLAN_NET_SIO_EDATA&t;0x10
DECL|macro|TLAN_NET_SIO_NMRST
mdefine_line|#define&t;&t;TLAN_NET_SIO_NMRST&t;0x08
DECL|macro|TLAN_NET_SIO_MCLK
mdefine_line|#define&t;&t;TLAN_NET_SIO_MCLK&t;0x04
DECL|macro|TLAN_NET_SIO_MTXEN
mdefine_line|#define&t;&t;TLAN_NET_SIO_MTXEN&t;0x02
DECL|macro|TLAN_NET_SIO_MDATA
mdefine_line|#define&t;&t;TLAN_NET_SIO_MDATA&t;0x01
DECL|macro|TLAN_NET_STS
mdefine_line|#define TLAN_NET_STS&t;&t;&t;0x02
DECL|macro|TLAN_NET_STS_MIRQ
mdefine_line|#define&t;&t;TLAN_NET_STS_MIRQ&t;0x80
DECL|macro|TLAN_NET_STS_HBEAT
mdefine_line|#define&t;&t;TLAN_NET_STS_HBEAT&t;0x40
DECL|macro|TLAN_NET_STS_TXSTOP
mdefine_line|#define&t;&t;TLAN_NET_STS_TXSTOP&t;0x20
DECL|macro|TLAN_NET_STS_RXSTOP
mdefine_line|#define&t;&t;TLAN_NET_STS_RXSTOP&t;0x10
DECL|macro|TLAN_NET_STS_RSRVD
mdefine_line|#define&t;&t;TLAN_NET_STS_RSRVD&t;0x0F
DECL|macro|TLAN_NET_MASK
mdefine_line|#define TLAN_NET_MASK&t;&t;&t;0x03
DECL|macro|TLAN_NET_MASK_MASK7
mdefine_line|#define&t;&t;TLAN_NET_MASK_MASK7&t;0x80
DECL|macro|TLAN_NET_MASK_MASK6
mdefine_line|#define&t;&t;TLAN_NET_MASK_MASK6&t;0x40
DECL|macro|TLAN_NET_MASK_MASK5
mdefine_line|#define&t;&t;TLAN_NET_MASK_MASK5&t;0x20
DECL|macro|TLAN_NET_MASK_MASK4
mdefine_line|#define&t;&t;TLAN_NET_MASK_MASK4&t;0x10
DECL|macro|TLAN_NET_MASK_RSRVD
mdefine_line|#define&t;&t;TLAN_NET_MASK_RSRVD&t;0x0F
DECL|macro|TLAN_NET_CONFIG
mdefine_line|#define TLAN_NET_CONFIG&t;&t;&t;0x04
DECL|macro|TLAN_NET_CFG_RCLK
mdefine_line|#define &t;TLAN_NET_CFG_RCLK&t;0x8000
DECL|macro|TLAN_NET_CFG_TCLK
mdefine_line|#define&t;&t;TLAN_NET_CFG_TCLK&t;0x4000
DECL|macro|TLAN_NET_CFG_BIT
mdefine_line|#define&t;&t;TLAN_NET_CFG_BIT&t;0x2000
DECL|macro|TLAN_NET_CFG_RXCRC
mdefine_line|#define&t;&t;TLAN_NET_CFG_RXCRC&t;0x1000
DECL|macro|TLAN_NET_CFG_PEF
mdefine_line|#define&t;&t;TLAN_NET_CFG_PEF&t;0x0800
DECL|macro|TLAN_NET_CFG_1FRAG
mdefine_line|#define&t;&t;TLAN_NET_CFG_1FRAG&t;0x0400
DECL|macro|TLAN_NET_CFG_1CHAN
mdefine_line|#define&t;&t;TLAN_NET_CFG_1CHAN&t;0x0200
DECL|macro|TLAN_NET_CFG_MTEST
mdefine_line|#define&t;&t;TLAN_NET_CFG_MTEST&t;0x0100
DECL|macro|TLAN_NET_CFG_PHY_EN
mdefine_line|#define&t;&t;TLAN_NET_CFG_PHY_EN&t;0x0080
DECL|macro|TLAN_NET_CFG_MSMASK
mdefine_line|#define&t;&t;TLAN_NET_CFG_MSMASK&t;0x007F
DECL|macro|TLAN_MAN_TEST
mdefine_line|#define TLAN_MAN_TEST&t;&t;&t;0x06
DECL|macro|TLAN_DEF_VENDOR_ID
mdefine_line|#define TLAN_DEF_VENDOR_ID&t;&t;0x08
DECL|macro|TLAN_DEF_DEVICE_ID
mdefine_line|#define TLAN_DEF_DEVICE_ID&t;&t;0x0A
DECL|macro|TLAN_DEF_REVISION
mdefine_line|#define TLAN_DEF_REVISION&t;&t;0x0C
DECL|macro|TLAN_DEF_SUBCLASS
mdefine_line|#define TLAN_DEF_SUBCLASS&t;&t;0x0D
DECL|macro|TLAN_DEF_MIN_LAT
mdefine_line|#define TLAN_DEF_MIN_LAT&t;&t;0x0E
DECL|macro|TLAN_DEF_MAX_LAT
mdefine_line|#define TLAN_DEF_MAX_LAT&t;&t;0x0F
DECL|macro|TLAN_AREG_0
mdefine_line|#define TLAN_AREG_0&t;&t;&t;0x10
DECL|macro|TLAN_AREG_1
mdefine_line|#define TLAN_AREG_1&t;&t;&t;0x16
DECL|macro|TLAN_AREG_2
mdefine_line|#define TLAN_AREG_2&t;&t;&t;0x1C
DECL|macro|TLAN_AREG_3
mdefine_line|#define TLAN_AREG_3&t;&t;&t;0x22
DECL|macro|TLAN_HASH_1
mdefine_line|#define TLAN_HASH_1&t;&t;&t;0x28
DECL|macro|TLAN_HASH_2
mdefine_line|#define TLAN_HASH_2&t;&t;&t;0x2C
DECL|macro|TLAN_GOOD_TX_FRMS
mdefine_line|#define TLAN_GOOD_TX_FRMS&t;&t;0x30
DECL|macro|TLAN_TX_UNDERUNS
mdefine_line|#define TLAN_TX_UNDERUNS&t;&t;0x33
DECL|macro|TLAN_GOOD_RX_FRMS
mdefine_line|#define TLAN_GOOD_RX_FRMS&t;&t;0x34
DECL|macro|TLAN_RX_OVERRUNS
mdefine_line|#define TLAN_RX_OVERRUNS&t;&t;0x37
DECL|macro|TLAN_DEFERRED_TX
mdefine_line|#define TLAN_DEFERRED_TX&t;&t;0x38
DECL|macro|TLAN_CRC_ERRORS
mdefine_line|#define TLAN_CRC_ERRORS&t;&t;&t;0x3A
DECL|macro|TLAN_CODE_ERRORS
mdefine_line|#define TLAN_CODE_ERRORS&t;&t;0x3B
DECL|macro|TLAN_MULTICOL_FRMS
mdefine_line|#define TLAN_MULTICOL_FRMS&t;&t;0x3C
DECL|macro|TLAN_SINGLECOL_FRMS
mdefine_line|#define TLAN_SINGLECOL_FRMS&t;&t;0x3E
DECL|macro|TLAN_EXCESSCOL_FRMS
mdefine_line|#define TLAN_EXCESSCOL_FRMS&t;&t;0x40
DECL|macro|TLAN_LATE_COLS
mdefine_line|#define TLAN_LATE_COLS&t;&t;&t;0x41
DECL|macro|TLAN_CARRIER_LOSS
mdefine_line|#define TLAN_CARRIER_LOSS&t;&t;0x42
DECL|macro|TLAN_ACOMMIT
mdefine_line|#define TLAN_ACOMMIT&t;&t;&t;0x43
DECL|macro|TLAN_LED_REG
mdefine_line|#define TLAN_LED_REG&t;&t;&t;0x44
DECL|macro|TLAN_LED_ACT
mdefine_line|#define&t;&t;TLAN_LED_ACT&t;&t;0x10
DECL|macro|TLAN_LED_LINK
mdefine_line|#define&t;&t;TLAN_LED_LINK&t;&t;0x01
DECL|macro|TLAN_BSIZE_REG
mdefine_line|#define TLAN_BSIZE_REG&t;&t;&t;0x45
DECL|macro|TLAN_MAX_RX
mdefine_line|#define TLAN_MAX_RX&t;&t;&t;0x46
DECL|macro|TLAN_INT_DIS
mdefine_line|#define TLAN_INT_DIS&t;&t;&t;0x48
DECL|macro|TLAN_ID_TX_EOC
mdefine_line|#define&t;&t;TLAN_ID_TX_EOC&t;&t;0x04
DECL|macro|TLAN_ID_RX_EOF
mdefine_line|#define&t;&t;TLAN_ID_RX_EOF&t;&t;0x02
DECL|macro|TLAN_ID_RX_EOC
mdefine_line|#define&t;&t;TLAN_ID_RX_EOC&t;&t;0x01
multiline_comment|/* ThunderLAN Interrupt Codes */
DECL|macro|TLAN_INT_NUMBER_OF_INTS
mdefine_line|#define TLAN_INT_NUMBER_OF_INTS&t;8
DECL|macro|TLAN_INT_NONE
mdefine_line|#define TLAN_INT_NONE&t;&t;&t;0x0000
DECL|macro|TLAN_INT_TX_EOF
mdefine_line|#define TLAN_INT_TX_EOF&t;&t;&t;0x0001
DECL|macro|TLAN_INT_STAT_OVERFLOW
mdefine_line|#define TLAN_INT_STAT_OVERFLOW&t;&t;0x0002
DECL|macro|TLAN_INT_RX_EOF
mdefine_line|#define TLAN_INT_RX_EOF&t;&t;&t;0x0003
DECL|macro|TLAN_INT_DUMMY
mdefine_line|#define TLAN_INT_DUMMY&t;&t;&t;0x0004
DECL|macro|TLAN_INT_TX_EOC
mdefine_line|#define TLAN_INT_TX_EOC&t;&t;&t;0x0005
DECL|macro|TLAN_INT_STATUS_CHECK
mdefine_line|#define TLAN_INT_STATUS_CHECK&t;&t;0x0006
DECL|macro|TLAN_INT_RX_EOC
mdefine_line|#define TLAN_INT_RX_EOC&t;&t;&t;0x0007
multiline_comment|/* ThunderLAN MII Registers */
multiline_comment|/* Generic MII/PHY Registers */
DECL|macro|MII_GEN_CTL
mdefine_line|#define MII_GEN_CTL&t;&t;&t;0x00
DECL|macro|MII_GC_RESET
mdefine_line|#define &t;MII_GC_RESET&t;&t;0x8000
DECL|macro|MII_GC_LOOPBK
mdefine_line|#define&t;&t;MII_GC_LOOPBK&t;&t;0x4000
DECL|macro|MII_GC_SPEEDSEL
mdefine_line|#define&t;&t;MII_GC_SPEEDSEL&t;&t;0x2000
DECL|macro|MII_GC_AUTOENB
mdefine_line|#define&t;&t;MII_GC_AUTOENB&t;&t;0x1000
DECL|macro|MII_GC_PDOWN
mdefine_line|#define&t;&t;MII_GC_PDOWN&t;&t;0x0800
DECL|macro|MII_GC_ISOLATE
mdefine_line|#define&t;&t;MII_GC_ISOLATE&t;&t;0x0400
DECL|macro|MII_GC_AUTORSRT
mdefine_line|#define&t;&t;MII_GC_AUTORSRT&t;&t;0x0200
DECL|macro|MII_GC_DUPLEX
mdefine_line|#define&t;&t;MII_GC_DUPLEX&t;&t;0x0100
DECL|macro|MII_GC_COLTEST
mdefine_line|#define&t;&t;MII_GC_COLTEST&t;&t;0x0080
DECL|macro|MII_GC_RESERVED
mdefine_line|#define&t;&t;MII_GC_RESERVED&t;&t;0x007F
DECL|macro|MII_GEN_STS
mdefine_line|#define MII_GEN_STS&t;&t;&t;0x01
DECL|macro|MII_GS_100BT4
mdefine_line|#define&t;&t;MII_GS_100BT4&t;&t;0x8000
DECL|macro|MII_GS_100BTXFD
mdefine_line|#define&t;&t;MII_GS_100BTXFD&t;&t;0x4000
DECL|macro|MII_GS_100BTXHD
mdefine_line|#define&t;&t;MII_GS_100BTXHD&t;&t;0x2000
DECL|macro|MII_GS_10BTFD
mdefine_line|#define&t;&t;MII_GS_10BTFD&t;&t;0x1000
DECL|macro|MII_GS_10BTHD
mdefine_line|#define&t;&t;MII_GS_10BTHD&t;&t;0x0800
DECL|macro|MII_GS_RESERVED
mdefine_line|#define&t;&t;MII_GS_RESERVED&t;&t;0x07C0
DECL|macro|MII_GS_AUTOCMPLT
mdefine_line|#define&t;&t;MII_GS_AUTOCMPLT&t;0x0020
DECL|macro|MII_GS_RFLT
mdefine_line|#define&t;&t;MII_GS_RFLT&t;&t;0x0010
DECL|macro|MII_GS_AUTONEG
mdefine_line|#define&t;&t;MII_GS_AUTONEG&t;&t;0x0008
DECL|macro|MII_GS_LINK
mdefine_line|#define&t;&t;MII_GS_LINK&t;&t;0x0004
DECL|macro|MII_GS_JABBER
mdefine_line|#define&t;&t;MII_GS_JABBER&t;&t;0x0002
DECL|macro|MII_GS_EXTCAP
mdefine_line|#define&t;&t;MII_GS_EXTCAP&t;&t;0x0001
DECL|macro|MII_GEN_ID_HI
mdefine_line|#define MII_GEN_ID_HI&t;&t;&t;0x02
DECL|macro|MII_GEN_ID_LO
mdefine_line|#define MII_GEN_ID_LO&t;&t;&t;0x03
DECL|macro|MII_GIL_OUI
mdefine_line|#define &t;MII_GIL_OUI&t;&t;0xFC00
DECL|macro|MII_GIL_MODEL
mdefine_line|#define &t;MII_GIL_MODEL&t;&t;0x03F0
DECL|macro|MII_GIL_REVISION
mdefine_line|#define &t;MII_GIL_REVISION&t;0x000F
DECL|macro|MII_AN_ADV
mdefine_line|#define MII_AN_ADV&t;&t;&t;0x04
DECL|macro|MII_AN_LPA
mdefine_line|#define MII_AN_LPA&t;&t;&t;0x05
DECL|macro|MII_AN_EXP
mdefine_line|#define MII_AN_EXP&t;&t;&t;0x06
multiline_comment|/* ThunderLAN Specific MII/PHY Registers */
DECL|macro|TLAN_TLPHY_ID
mdefine_line|#define TLAN_TLPHY_ID&t;&t;&t;0x10
DECL|macro|TLAN_TLPHY_CTL
mdefine_line|#define TLAN_TLPHY_CTL&t;&t;&t;0x11
DECL|macro|TLAN_TC_IGLINK
mdefine_line|#define &t;TLAN_TC_IGLINK&t;&t;0x8000
DECL|macro|TLAN_TC_SWAPOL
mdefine_line|#define&t;&t;TLAN_TC_SWAPOL&t;&t;0x4000
DECL|macro|TLAN_TC_AUISEL
mdefine_line|#define&t;&t;TLAN_TC_AUISEL&t;&t;0x2000
DECL|macro|TLAN_TC_SQEEN
mdefine_line|#define&t;&t;TLAN_TC_SQEEN&t;&t;0x1000
DECL|macro|TLAN_TC_MTEST
mdefine_line|#define&t;&t;TLAN_TC_MTEST&t;&t;0x0800
DECL|macro|TLAN_TC_RESERVED
mdefine_line|#define&t;&t;TLAN_TC_RESERVED&t;0x07F8
DECL|macro|TLAN_TC_NFEW
mdefine_line|#define&t;&t;TLAN_TC_NFEW&t;&t;0x0004
DECL|macro|TLAN_TC_INTEN
mdefine_line|#define&t;&t;TLAN_TC_INTEN&t;&t;0x0002
DECL|macro|TLAN_TC_TINT
mdefine_line|#define&t;&t;TLAN_TC_TINT&t;&t;0x0001
DECL|macro|TLAN_TLPHY_STS
mdefine_line|#define TLAN_TLPHY_STS&t;&t;&t;0x12
DECL|macro|TLAN_TS_MINT
mdefine_line|#define&t;&t;TLAN_TS_MINT&t;&t;0x8000
DECL|macro|TLAN_TS_PHOK
mdefine_line|#define&t;&t;TLAN_TS_PHOK&t;&t;0x4000
DECL|macro|TLAN_TS_POLOK
mdefine_line|#define&t;&t;TLAN_TS_POLOK&t;&t;0x2000
DECL|macro|TLAN_TS_TPENERGY
mdefine_line|#define&t;&t;TLAN_TS_TPENERGY&t;0x1000
DECL|macro|TLAN_TS_RESERVED
mdefine_line|#define&t;&t;TLAN_TS_RESERVED&t;0x0FFF
DECL|macro|TLAN_TLPHY_PAR
mdefine_line|#define TLAN_TLPHY_PAR&t;&t;&t;0x19
DECL|macro|TLAN_PHY_CIM_STAT
mdefine_line|#define&t;&t;TLAN_PHY_CIM_STAT&t;0x0020
DECL|macro|TLAN_PHY_SPEED_100
mdefine_line|#define&t;&t;TLAN_PHY_SPEED_100&t;0x0040
DECL|macro|TLAN_PHY_DUPLEX_FULL
mdefine_line|#define&t;&t;TLAN_PHY_DUPLEX_FULL&t;0x0080
DECL|macro|TLAN_PHY_AN_EN_STAT
mdefine_line|#define&t;&t;TLAN_PHY_AN_EN_STAT     0x0400
multiline_comment|/* National Sem. &amp; Level1 PHY id&squot;s */
DECL|macro|NAT_SEM_ID1
mdefine_line|#define NAT_SEM_ID1&t;&t;&t;0x2000
DECL|macro|NAT_SEM_ID2
mdefine_line|#define NAT_SEM_ID2&t;&t;&t;0x5C01
DECL|macro|LEVEL1_ID1
mdefine_line|#define LEVEL1_ID1&t;&t;&t;0x7810
DECL|macro|LEVEL1_ID2
mdefine_line|#define LEVEL1_ID2&t;&t;&t;0x0000
DECL|macro|CIRC_INC
mdefine_line|#define CIRC_INC( a, b ) if ( ++a &gt;= b ) a = 0
multiline_comment|/* Routines to access internal registers. */
DECL|function|TLan_DioRead8
r_inline
id|u8
id|TLan_DioRead8
c_func
(paren
id|u16
id|base_addr
comma
id|u16
id|internal_addr
)paren
(brace
id|outw
c_func
(paren
id|internal_addr
comma
id|base_addr
op_plus
id|TLAN_DIO_ADR
)paren
suffix:semicolon
r_return
(paren
id|inb
c_func
(paren
(paren
id|base_addr
op_plus
id|TLAN_DIO_DATA
)paren
op_plus
(paren
id|internal_addr
op_amp
l_int|0x3
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* TLan_DioRead8 */
DECL|function|TLan_DioRead16
r_inline
id|u16
id|TLan_DioRead16
c_func
(paren
id|u16
id|base_addr
comma
id|u16
id|internal_addr
)paren
(brace
id|outw
c_func
(paren
id|internal_addr
comma
id|base_addr
op_plus
id|TLAN_DIO_ADR
)paren
suffix:semicolon
r_return
(paren
id|inw
c_func
(paren
(paren
id|base_addr
op_plus
id|TLAN_DIO_DATA
)paren
op_plus
(paren
id|internal_addr
op_amp
l_int|0x2
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* TLan_DioRead16 */
DECL|function|TLan_DioRead32
r_inline
id|u32
id|TLan_DioRead32
c_func
(paren
id|u16
id|base_addr
comma
id|u16
id|internal_addr
)paren
(brace
id|outw
c_func
(paren
id|internal_addr
comma
id|base_addr
op_plus
id|TLAN_DIO_ADR
)paren
suffix:semicolon
r_return
(paren
id|inl
c_func
(paren
id|base_addr
op_plus
id|TLAN_DIO_DATA
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* TLan_DioRead32 */
DECL|function|TLan_DioWrite8
r_inline
r_void
id|TLan_DioWrite8
c_func
(paren
id|u16
id|base_addr
comma
id|u16
id|internal_addr
comma
id|u8
id|data
)paren
(brace
id|outw
c_func
(paren
id|internal_addr
comma
id|base_addr
op_plus
id|TLAN_DIO_ADR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|base_addr
op_plus
id|TLAN_DIO_DATA
op_plus
(paren
id|internal_addr
op_amp
l_int|0x3
)paren
)paren
suffix:semicolon
)brace
DECL|function|TLan_DioWrite16
r_inline
r_void
id|TLan_DioWrite16
c_func
(paren
id|u16
id|base_addr
comma
id|u16
id|internal_addr
comma
id|u16
id|data
)paren
(brace
id|outw
c_func
(paren
id|internal_addr
comma
id|base_addr
op_plus
id|TLAN_DIO_ADR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|data
comma
id|base_addr
op_plus
id|TLAN_DIO_DATA
op_plus
(paren
id|internal_addr
op_amp
l_int|0x2
)paren
)paren
suffix:semicolon
)brace
DECL|function|TLan_DioWrite32
r_inline
r_void
id|TLan_DioWrite32
c_func
(paren
id|u16
id|base_addr
comma
id|u16
id|internal_addr
comma
id|u32
id|data
)paren
(brace
id|outw
c_func
(paren
id|internal_addr
comma
id|base_addr
op_plus
id|TLAN_DIO_ADR
)paren
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|base_addr
op_plus
id|TLAN_DIO_DATA
op_plus
(paren
id|internal_addr
op_amp
l_int|0x2
)paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_inline
r_void
id|TLan_ClearBit
c_func
(paren
id|u8
id|bit
comma
id|u16
id|port
)paren
(brace
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|port
)paren
op_amp
op_complement
id|bit
comma
id|port
)paren
suffix:semicolon
)brace
r_inline
r_int
id|TLan_GetBit
c_func
(paren
id|u8
id|bit
comma
id|u16
id|port
)paren
(brace
r_return
(paren
(paren
r_int
)paren
(paren
id|inb_p
c_func
(paren
id|port
)paren
op_amp
id|bit
)paren
)paren
suffix:semicolon
)brace
r_inline
r_void
id|TLan_SetBit
c_func
(paren
id|u8
id|bit
comma
id|u16
id|port
)paren
(brace
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
id|port
)paren
op_or
id|bit
comma
id|port
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|TLan_ClearBit
mdefine_line|#define TLan_ClearBit( bit, port )&t;outb_p(inb_p(port) &amp; ~bit, port)
DECL|macro|TLan_GetBit
mdefine_line|#define TLan_GetBit( bit, port )&t;((int) (inb_p(port) &amp; bit))
DECL|macro|TLan_SetBit
mdefine_line|#define TLan_SetBit( bit, port )&t;outb_p(inb_p(port) | bit, port)
macro_line|#ifdef I_LIKE_A_FAST_HASH_FUNCTION
multiline_comment|/* given 6 bytes, view them as 8 6-bit numbers and return the XOR of those */
multiline_comment|/* the code below is about seven times as fast as the original code */
DECL|function|TLan_HashFunc
r_inline
id|u32
id|TLan_HashFunc
c_func
(paren
id|u8
op_star
id|a
)paren
(brace
id|u8
id|hash
suffix:semicolon
id|hash
op_assign
(paren
id|a
(braket
l_int|0
)braket
op_xor
id|a
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* &amp; 077 */
id|hash
op_xor_assign
(paren
(paren
id|a
(braket
l_int|0
)braket
op_xor
id|a
(braket
l_int|3
)braket
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
multiline_comment|/* &amp; 003 */
id|hash
op_xor_assign
(paren
(paren
id|a
(braket
l_int|1
)braket
op_xor
id|a
(braket
l_int|4
)braket
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* &amp; 074 */
id|hash
op_xor_assign
(paren
(paren
id|a
(braket
l_int|1
)braket
op_xor
id|a
(braket
l_int|4
)braket
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* &amp; 017 */
id|hash
op_xor_assign
(paren
(paren
id|a
(braket
l_int|2
)braket
op_xor
id|a
(braket
l_int|5
)braket
)paren
op_lshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* &amp; 060 */
id|hash
op_xor_assign
(paren
(paren
id|a
(braket
l_int|2
)braket
op_xor
id|a
(braket
l_int|5
)braket
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* &amp; 077 */
r_return
(paren
id|hash
op_amp
l_int|077
)paren
suffix:semicolon
)brace
macro_line|#else /* original code */
DECL|function|xor
r_inline
id|u32
op_xor
(paren
id|u32
id|a
comma
id|u32
id|b
)paren
(brace
r_return
(paren
(paren
id|a
op_logical_and
op_logical_neg
id|b
)paren
op_logical_or
(paren
op_logical_neg
id|a
op_logical_and
id|b
)paren
)paren
suffix:semicolon
)brace
DECL|macro|XOR8
mdefine_line|#define XOR8( a, b, c, d, e, f, g, h )&t;xor( a, xor( b, xor( c, xor( d, xor( e, xor( f, xor( g, h ) ) ) ) ) ) )
DECL|macro|DA
mdefine_line|#define DA( a, bit )&t;&t;&t;&t;&t;( ( (u8) a[bit/8] ) &amp; ( (u8) ( 1 &lt;&lt; bit%8 ) ) )
DECL|function|TLan_HashFunc
r_inline
id|u32
id|TLan_HashFunc
c_func
(paren
id|u8
op_star
id|a
)paren
(brace
id|u32
id|hash
suffix:semicolon
id|hash
op_assign
id|XOR8
c_func
(paren
id|DA
c_func
(paren
id|a
comma
l_int|0
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|6
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|12
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|18
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|24
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|30
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|36
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|42
)paren
)paren
suffix:semicolon
id|hash
op_or_assign
id|XOR8
c_func
(paren
id|DA
c_func
(paren
id|a
comma
l_int|1
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|7
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|13
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|19
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|25
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|31
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|37
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|43
)paren
)paren
op_lshift
l_int|1
suffix:semicolon
id|hash
op_or_assign
id|XOR8
c_func
(paren
id|DA
c_func
(paren
id|a
comma
l_int|2
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|8
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|14
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|20
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|26
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|32
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|38
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|44
)paren
)paren
op_lshift
l_int|2
suffix:semicolon
id|hash
op_or_assign
id|XOR8
c_func
(paren
id|DA
c_func
(paren
id|a
comma
l_int|3
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|9
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|15
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|21
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|27
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|33
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|39
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|45
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|hash
op_or_assign
id|XOR8
c_func
(paren
id|DA
c_func
(paren
id|a
comma
l_int|4
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|10
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|16
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|22
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|28
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|34
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|40
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|46
)paren
)paren
op_lshift
l_int|4
suffix:semicolon
id|hash
op_or_assign
id|XOR8
c_func
(paren
id|DA
c_func
(paren
id|a
comma
l_int|5
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|11
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|17
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|23
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|29
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|35
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|41
)paren
comma
id|DA
c_func
(paren
id|a
comma
l_int|47
)paren
)paren
op_lshift
l_int|5
suffix:semicolon
r_return
id|hash
suffix:semicolon
)brace
macro_line|#endif /* I_LIKE_A_FAST_HASH_FUNCTION */
macro_line|#endif
eof
