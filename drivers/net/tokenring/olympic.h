multiline_comment|/*&n; *  olympic.h (c) 1999 Peter De Schrijver All Rights Reserved&n; *                1999 Mike Phillips (mikep@linuxtr.net)&n; *&n; *  Linux driver for IBM PCI tokenring cards based on the olympic and the PIT/PHY chipset.&n; *&n; *  Base Driver Skeleton:&n; *      Written 1993-94 by Donald Becker.&n; *&n; *      Copyright 1993 United States Government as represented by the&n; *      Director, National Security Agency.&n; *&n; *  This software may be used and distributed according to the terms&n; *  of the GNU General Public License, incorporated herein by reference.&n; */
DECL|macro|CID
mdefine_line|#define CID 0x4e
DECL|macro|BCTL
mdefine_line|#define BCTL 0x70
DECL|macro|BCTL_SOFTRESET
mdefine_line|#define BCTL_SOFTRESET (1&lt;&lt;15)
DECL|macro|BCTL_MIMREB
mdefine_line|#define BCTL_MIMREB (1&lt;&lt;6)
DECL|macro|BCTL_MODE_INDICATOR
mdefine_line|#define BCTL_MODE_INDICATOR (1&lt;&lt;5)
DECL|macro|GPR
mdefine_line|#define GPR 0x4a
DECL|macro|GPR_OPTI_BF
mdefine_line|#define GPR_OPTI_BF (1&lt;&lt;6)
DECL|macro|GPR_NEPTUNE_BF
mdefine_line|#define GPR_NEPTUNE_BF (1&lt;&lt;4) 
DECL|macro|GPR_AUTOSENSE
mdefine_line|#define GPR_AUTOSENSE (1&lt;&lt;2)
DECL|macro|GPR_16MBPS
mdefine_line|#define GPR_16MBPS (1&lt;&lt;3) 
DECL|macro|PAG
mdefine_line|#define PAG 0x85
DECL|macro|LBC
mdefine_line|#define LBC 0x8e
DECL|macro|LISR
mdefine_line|#define LISR 0x10
DECL|macro|LISR_SUM
mdefine_line|#define LISR_SUM 0x14
DECL|macro|LISR_RWM
mdefine_line|#define LISR_RWM 0x18
DECL|macro|LISR_LIE
mdefine_line|#define LISR_LIE (1&lt;&lt;15)
DECL|macro|LISR_SLIM
mdefine_line|#define LISR_SLIM (1&lt;&lt;13)
DECL|macro|LISR_SLI
mdefine_line|#define LISR_SLI (1&lt;&lt;12)
DECL|macro|LISR_PCMSRMASK
mdefine_line|#define LISR_PCMSRMASK (1&lt;&lt;11)
DECL|macro|LISR_PCMSRINT
mdefine_line|#define LISR_PCMSRINT (1&lt;&lt;10)
DECL|macro|LISR_WOLMASK
mdefine_line|#define LISR_WOLMASK (1&lt;&lt;9)
DECL|macro|LISR_WOL
mdefine_line|#define LISR_WOL (1&lt;&lt;8)
DECL|macro|LISR_SRB_CMD
mdefine_line|#define LISR_SRB_CMD (1&lt;&lt;5)
DECL|macro|LISR_ASB_REPLY
mdefine_line|#define LISR_ASB_REPLY (1&lt;&lt;4)
DECL|macro|LISR_ASB_FREE_REQ
mdefine_line|#define LISR_ASB_FREE_REQ (1&lt;&lt;2)
DECL|macro|LISR_ARB_FREE
mdefine_line|#define LISR_ARB_FREE (1&lt;&lt;1)
DECL|macro|LISR_TRB_FRAME
mdefine_line|#define LISR_TRB_FRAME (1&lt;&lt;0)
DECL|macro|SISR
mdefine_line|#define SISR 0x20
DECL|macro|SISR_SUM
mdefine_line|#define SISR_SUM 0x24
DECL|macro|SISR_RWM
mdefine_line|#define SISR_RWM 0x28
DECL|macro|SISR_RR
mdefine_line|#define SISR_RR 0x2C
DECL|macro|SISR_RESMASK
mdefine_line|#define SISR_RESMASK 0x30
DECL|macro|SISR_MASK
mdefine_line|#define SISR_MASK 0x54
DECL|macro|SISR_MASK_SUM
mdefine_line|#define SISR_MASK_SUM 0x58
DECL|macro|SISR_MASK_RWM
mdefine_line|#define SISR_MASK_RWM 0x5C
DECL|macro|SISR_TX2_IDLE
mdefine_line|#define SISR_TX2_IDLE (1&lt;&lt;31)
DECL|macro|SISR_TX2_HALT
mdefine_line|#define SISR_TX2_HALT (1&lt;&lt;29)
DECL|macro|SISR_TX2_EOF
mdefine_line|#define SISR_TX2_EOF (1&lt;&lt;28)
DECL|macro|SISR_TX1_IDLE
mdefine_line|#define SISR_TX1_IDLE (1&lt;&lt;27)
DECL|macro|SISR_TX1_HALT
mdefine_line|#define SISR_TX1_HALT (1&lt;&lt;25)
DECL|macro|SISR_TX1_EOF
mdefine_line|#define SISR_TX1_EOF (1&lt;&lt;24)
DECL|macro|SISR_TIMEOUT
mdefine_line|#define SISR_TIMEOUT (1&lt;&lt;23)
DECL|macro|SISR_RX_NOBUF
mdefine_line|#define SISR_RX_NOBUF (1&lt;&lt;22)
DECL|macro|SISR_RX_STATUS
mdefine_line|#define SISR_RX_STATUS (1&lt;&lt;21)
DECL|macro|SISR_RX_HALT
mdefine_line|#define SISR_RX_HALT (1&lt;&lt;18)
DECL|macro|SISR_RX_EOF_EARLY
mdefine_line|#define SISR_RX_EOF_EARLY (1&lt;&lt;16)
DECL|macro|SISR_MI
mdefine_line|#define SISR_MI (1&lt;&lt;15)
DECL|macro|SISR_PI
mdefine_line|#define SISR_PI (1&lt;&lt;13)
DECL|macro|SISR_ERR
mdefine_line|#define SISR_ERR (1&lt;&lt;9)
DECL|macro|SISR_ADAPTER_CHECK
mdefine_line|#define SISR_ADAPTER_CHECK (1&lt;&lt;6)
DECL|macro|SISR_SRB_REPLY
mdefine_line|#define SISR_SRB_REPLY (1&lt;&lt;5)
DECL|macro|SISR_ASB_FREE
mdefine_line|#define SISR_ASB_FREE (1&lt;&lt;4)
DECL|macro|SISR_ARB_CMD
mdefine_line|#define SISR_ARB_CMD (1&lt;&lt;3)
DECL|macro|SISR_TRB_REPLY
mdefine_line|#define SISR_TRB_REPLY (1&lt;&lt;2)
DECL|macro|EISR
mdefine_line|#define EISR 0x34
DECL|macro|EISR_RWM
mdefine_line|#define EISR_RWM 0x38
DECL|macro|EISR_MASK
mdefine_line|#define EISR_MASK 0x3c
DECL|macro|LAPA
mdefine_line|#define LAPA 0x60
DECL|macro|LAPWWO
mdefine_line|#define LAPWWO 0x64
DECL|macro|LAPWWC
mdefine_line|#define LAPWWC 0x68
DECL|macro|LAPCTL
mdefine_line|#define LAPCTL 0x6C
DECL|macro|LAIPD
mdefine_line|#define LAIPD 0x78
DECL|macro|LAIPDDINC
mdefine_line|#define LAIPDDINC 0x7C
DECL|macro|TIMER
mdefine_line|#define TIMER 0x50
DECL|macro|CLKCTL
mdefine_line|#define CLKCTL 0x74
DECL|macro|PM_CON
mdefine_line|#define PM_CON 0x4
DECL|macro|BMCTL_SUM
mdefine_line|#define BMCTL_SUM 0x40
DECL|macro|BMCTL_RWM
mdefine_line|#define BMCTL_RWM 0x44
DECL|macro|BMCTL_TX2_DIS
mdefine_line|#define BMCTL_TX2_DIS (1&lt;&lt;30) 
DECL|macro|BMCTL_TX1_DIS
mdefine_line|#define BMCTL_TX1_DIS (1&lt;&lt;26) 
DECL|macro|BMCTL_RX_DIS
mdefine_line|#define BMCTL_RX_DIS (1&lt;&lt;22) 
DECL|macro|BMASR
mdefine_line|#define BMASR 0xcc
DECL|macro|RXDESCQ
mdefine_line|#define RXDESCQ 0x90
DECL|macro|RXDESCQCNT
mdefine_line|#define RXDESCQCNT 0x94
DECL|macro|RXCDA
mdefine_line|#define RXCDA 0x98
DECL|macro|RXENQ
mdefine_line|#define RXENQ 0x9C
DECL|macro|RXSTATQ
mdefine_line|#define RXSTATQ 0xA0
DECL|macro|RXSTATQCNT
mdefine_line|#define RXSTATQCNT 0xA4
DECL|macro|RXCSA
mdefine_line|#define RXCSA 0xA8
DECL|macro|RXCLEN
mdefine_line|#define RXCLEN 0xAC
DECL|macro|RXHLEN
mdefine_line|#define RXHLEN 0xAE
DECL|macro|TXDESCQ_1
mdefine_line|#define TXDESCQ_1 0xb0
DECL|macro|TXDESCQ_2
mdefine_line|#define TXDESCQ_2 0xd0
DECL|macro|TXDESCQCNT_1
mdefine_line|#define TXDESCQCNT_1 0xb4
DECL|macro|TXDESCQCNT_2
mdefine_line|#define TXDESCQCNT_2 0xd4
DECL|macro|TXCDA_1
mdefine_line|#define TXCDA_1 0xb8
DECL|macro|TXCDA_2
mdefine_line|#define TXCDA_2 0xd8
DECL|macro|TXENQ_1
mdefine_line|#define TXENQ_1 0xbc
DECL|macro|TXENQ_2
mdefine_line|#define TXENQ_2 0xdc
DECL|macro|TXSTATQ_1
mdefine_line|#define TXSTATQ_1 0xc0
DECL|macro|TXSTATQ_2
mdefine_line|#define TXSTATQ_2 0xe0
DECL|macro|TXSTATQCNT_1
mdefine_line|#define TXSTATQCNT_1 0xc4
DECL|macro|TXSTATQCNT_2
mdefine_line|#define TXSTATQCNT_2 0xe4
DECL|macro|TXCSA_1
mdefine_line|#define TXCSA_1 0xc8
DECL|macro|TXCSA_2
mdefine_line|#define TXCSA_2 0xe8
multiline_comment|/* Cardbus */
DECL|macro|FERMASK
mdefine_line|#define FERMASK 0xf4
DECL|macro|FERMASK_INT_BIT
mdefine_line|#define FERMASK_INT_BIT (1&lt;&lt;15)
DECL|macro|OLYMPIC_IO_SPACE
mdefine_line|#define OLYMPIC_IO_SPACE 256
DECL|macro|SRB_COMMAND_SIZE
mdefine_line|#define SRB_COMMAND_SIZE 50
DECL|macro|OLYMPIC_MAX_ADAPTERS
mdefine_line|#define OLYMPIC_MAX_ADAPTERS 8 /* 0x08 __MODULE_STRING can&squot;t hand 0xnn */
multiline_comment|/* Defines for LAN STATUS CHANGE reports */
DECL|macro|LSC_SIG_LOSS
mdefine_line|#define LSC_SIG_LOSS 0x8000
DECL|macro|LSC_HARD_ERR
mdefine_line|#define LSC_HARD_ERR 0x4000
DECL|macro|LSC_SOFT_ERR
mdefine_line|#define LSC_SOFT_ERR 0x2000
DECL|macro|LSC_TRAN_BCN
mdefine_line|#define LSC_TRAN_BCN 0x1000
DECL|macro|LSC_LWF
mdefine_line|#define LSC_LWF      0x0800
DECL|macro|LSC_ARW
mdefine_line|#define LSC_ARW      0x0400
DECL|macro|LSC_FPE
mdefine_line|#define LSC_FPE      0x0200
DECL|macro|LSC_RR
mdefine_line|#define LSC_RR       0x0100
DECL|macro|LSC_CO
mdefine_line|#define LSC_CO       0x0080
DECL|macro|LSC_SS
mdefine_line|#define LSC_SS       0x0040
DECL|macro|LSC_RING_REC
mdefine_line|#define LSC_RING_REC 0x0020
DECL|macro|LSC_SR_CO
mdefine_line|#define LSC_SR_CO    0x0010
DECL|macro|LSC_FDX_MODE
mdefine_line|#define LSC_FDX_MODE 0x0004
multiline_comment|/* Defines for OPEN ADAPTER command */
DECL|macro|OPEN_ADAPTER_EXT_WRAP
mdefine_line|#define OPEN_ADAPTER_EXT_WRAP (1&lt;&lt;15)
DECL|macro|OPEN_ADAPTER_DIS_HARDEE
mdefine_line|#define OPEN_ADAPTER_DIS_HARDEE (1&lt;&lt;14)
DECL|macro|OPEN_ADAPTER_DIS_SOFTERR
mdefine_line|#define OPEN_ADAPTER_DIS_SOFTERR (1&lt;&lt;13)
DECL|macro|OPEN_ADAPTER_PASS_ADC_MAC
mdefine_line|#define OPEN_ADAPTER_PASS_ADC_MAC (1&lt;&lt;12)
DECL|macro|OPEN_ADAPTER_PASS_ATT_MAC
mdefine_line|#define OPEN_ADAPTER_PASS_ATT_MAC (1&lt;&lt;11)
DECL|macro|OPEN_ADAPTER_ENABLE_EC
mdefine_line|#define OPEN_ADAPTER_ENABLE_EC (1&lt;&lt;10)
DECL|macro|OPEN_ADAPTER_CONTENDER
mdefine_line|#define OPEN_ADAPTER_CONTENDER (1&lt;&lt;8)
DECL|macro|OPEN_ADAPTER_PASS_BEACON
mdefine_line|#define OPEN_ADAPTER_PASS_BEACON (1&lt;&lt;7)
DECL|macro|OPEN_ADAPTER_ENABLE_FDX
mdefine_line|#define OPEN_ADAPTER_ENABLE_FDX (1&lt;&lt;6)
DECL|macro|OPEN_ADAPTER_ENABLE_RPL
mdefine_line|#define OPEN_ADAPTER_ENABLE_RPL (1&lt;&lt;5)
DECL|macro|OPEN_ADAPTER_INHIBIT_ETR
mdefine_line|#define OPEN_ADAPTER_INHIBIT_ETR (1&lt;&lt;4)
DECL|macro|OPEN_ADAPTER_INTERNAL_WRAP
mdefine_line|#define OPEN_ADAPTER_INTERNAL_WRAP (1&lt;&lt;3)
DECL|macro|OPEN_ADAPTER_USE_OPTS2
mdefine_line|#define OPEN_ADAPTER_USE_OPTS2 (1&lt;&lt;0)
DECL|macro|OPEN_ADAPTER_2_ENABLE_ONNOW
mdefine_line|#define OPEN_ADAPTER_2_ENABLE_ONNOW (1&lt;&lt;15)
multiline_comment|/* Defines for SRB Commands */
DECL|macro|SRB_ACCESS_REGISTER
mdefine_line|#define SRB_ACCESS_REGISTER 0x1f
DECL|macro|SRB_CLOSE_ADAPTER
mdefine_line|#define SRB_CLOSE_ADAPTER 0x04
DECL|macro|SRB_CONFIGURE_BRIDGE
mdefine_line|#define SRB_CONFIGURE_BRIDGE 0x0c
DECL|macro|SRB_CONFIGURE_WAKEUP_EVENT
mdefine_line|#define SRB_CONFIGURE_WAKEUP_EVENT 0x1a
DECL|macro|SRB_MODIFY_BRIDGE_PARMS
mdefine_line|#define SRB_MODIFY_BRIDGE_PARMS 0x15
DECL|macro|SRB_MODIFY_OPEN_OPTIONS
mdefine_line|#define SRB_MODIFY_OPEN_OPTIONS 0x01
DECL|macro|SRB_MODIFY_RECEIVE_OPTIONS
mdefine_line|#define SRB_MODIFY_RECEIVE_OPTIONS 0x17
DECL|macro|SRB_NO_OPERATION
mdefine_line|#define SRB_NO_OPERATION 0x00
DECL|macro|SRB_OPEN_ADAPTER
mdefine_line|#define SRB_OPEN_ADAPTER 0x03
DECL|macro|SRB_READ_LOG
mdefine_line|#define SRB_READ_LOG 0x08
DECL|macro|SRB_READ_SR_COUNTERS
mdefine_line|#define SRB_READ_SR_COUNTERS 0x16
DECL|macro|SRB_RESET_GROUP_ADDRESS
mdefine_line|#define SRB_RESET_GROUP_ADDRESS 0x02
DECL|macro|SRB_SAVE_CONFIGURATION
mdefine_line|#define SRB_SAVE_CONFIGURATION 0x1b
DECL|macro|SRB_SET_BRIDGE_PARMS
mdefine_line|#define SRB_SET_BRIDGE_PARMS 0x09
DECL|macro|SRB_SET_BRIDGE_TARGETS
mdefine_line|#define SRB_SET_BRIDGE_TARGETS 0x10
DECL|macro|SRB_SET_FUNC_ADDRESS
mdefine_line|#define SRB_SET_FUNC_ADDRESS 0x07
DECL|macro|SRB_SET_GROUP_ADDRESS
mdefine_line|#define SRB_SET_GROUP_ADDRESS 0x06
DECL|macro|SRB_SET_GROUP_ADDR_OPTIONS
mdefine_line|#define SRB_SET_GROUP_ADDR_OPTIONS 0x11
DECL|macro|SRB_UPDATE_WAKEUP_PATTERN
mdefine_line|#define SRB_UPDATE_WAKEUP_PATTERN 0x19
multiline_comment|/* Clear return code */
DECL|macro|OLYMPIC_CLEAR_RET_CODE
mdefine_line|#define OLYMPIC_CLEAR_RET_CODE 0xfe 
multiline_comment|/* ARB Commands */
DECL|macro|ARB_RECEIVE_DATA
mdefine_line|#define ARB_RECEIVE_DATA 0x81
DECL|macro|ARB_LAN_CHANGE_STATUS
mdefine_line|#define ARB_LAN_CHANGE_STATUS 0x84
multiline_comment|/* ASB Response commands */
DECL|macro|ASB_RECEIVE_DATA
mdefine_line|#define ASB_RECEIVE_DATA 0x81
multiline_comment|/* Olympic defaults for buffers */
DECL|macro|OLYMPIC_RX_RING_SIZE
mdefine_line|#define OLYMPIC_RX_RING_SIZE 16 /* should be a power of 2 */
DECL|macro|OLYMPIC_TX_RING_SIZE
mdefine_line|#define OLYMPIC_TX_RING_SIZE 8 /* should be a power of 2 */
DECL|macro|PKT_BUF_SZ
mdefine_line|#define PKT_BUF_SZ 4096 /* Default packet size */
multiline_comment|/* Olympic data structures */
multiline_comment|/* xxxx These structures are all little endian in hardware. */
DECL|struct|olympic_tx_desc
r_struct
id|olympic_tx_desc
(brace
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|member|status_length
id|__u32
id|status_length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|olympic_tx_status
r_struct
id|olympic_tx_status
(brace
DECL|member|status
id|__u32
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|olympic_rx_desc
r_struct
id|olympic_rx_desc
(brace
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|member|res_length
id|__u32
id|res_length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|olympic_rx_status
r_struct
id|olympic_rx_status
(brace
DECL|member|fragmentcnt_framelen
id|__u32
id|fragmentcnt_framelen
suffix:semicolon
DECL|member|status_buffercnt
id|__u32
id|status_buffercnt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* xxxx END These structures are all little endian in hardware. */
multiline_comment|/* xxxx There may be more, but I&squot;m pretty sure about these */
DECL|struct|mac_receive_buffer
r_struct
id|mac_receive_buffer
(brace
DECL|member|next
id|__u16
id|next
suffix:semicolon
DECL|member|padding
id|__u8
id|padding
suffix:semicolon
DECL|member|frame_status
id|__u8
id|frame_status
suffix:semicolon
DECL|member|buffer_length
id|__u16
id|buffer_length
suffix:semicolon
DECL|member|frame_data
id|__u8
id|frame_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|olympic_private
r_struct
id|olympic_private
(brace
DECL|member|srb
id|__u16
id|srb
suffix:semicolon
multiline_comment|/* be16 */
DECL|member|trb
id|__u16
id|trb
suffix:semicolon
multiline_comment|/* be16 */
DECL|member|arb
id|__u16
id|arb
suffix:semicolon
multiline_comment|/* be16 */
DECL|member|asb
id|__u16
id|asb
suffix:semicolon
multiline_comment|/* be16 */
DECL|member|olympic_mmio
id|__u8
op_star
id|olympic_mmio
suffix:semicolon
DECL|member|olympic_lap
id|__u8
op_star
id|olympic_lap
suffix:semicolon
DECL|member|olympic_card_name
r_char
op_star
id|olympic_card_name
suffix:semicolon
DECL|member|olympic_lock
id|spinlock_t
id|olympic_lock
suffix:semicolon
DECL|member|srb_queued
r_volatile
r_int
id|srb_queued
suffix:semicolon
multiline_comment|/* True if an SRB is still posted */
DECL|member|srb_wait
id|wait_queue_head_t
id|srb_wait
suffix:semicolon
DECL|member|asb_queued
r_volatile
r_int
id|asb_queued
suffix:semicolon
multiline_comment|/* True if an ASB is posted */
DECL|member|trb_queued
r_volatile
r_int
id|trb_queued
suffix:semicolon
multiline_comment|/* True if a TRB is posted */
DECL|member|trb_wait
id|wait_queue_head_t
id|trb_wait
suffix:semicolon
DECL|member|olympic_rx_ring
r_struct
id|olympic_rx_desc
id|olympic_rx_ring
(braket
id|OLYMPIC_RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|olympic_tx_ring
r_struct
id|olympic_tx_desc
id|olympic_tx_ring
(braket
id|OLYMPIC_TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|olympic_rx_status_ring
r_struct
id|olympic_rx_status
id|olympic_rx_status_ring
(braket
id|OLYMPIC_RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|olympic_tx_status_ring
r_struct
id|olympic_tx_status
id|olympic_tx_status_ring
(braket
id|OLYMPIC_TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_ring_skb
DECL|member|rx_ring_skb
r_struct
id|sk_buff
op_star
id|tx_ring_skb
(braket
id|OLYMPIC_TX_RING_SIZE
)braket
comma
op_star
id|rx_ring_skb
(braket
id|OLYMPIC_RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_ring_free
DECL|member|tx_ring_last_status
DECL|member|rx_ring_last_received
DECL|member|rx_status_last_received
DECL|member|free_tx_ring_entries
r_int
id|tx_ring_free
comma
id|tx_ring_last_status
comma
id|rx_ring_last_received
comma
id|rx_status_last_received
comma
id|free_tx_ring_entries
suffix:semicolon
DECL|member|olympic_stats
r_struct
id|net_device_stats
id|olympic_stats
suffix:semicolon
DECL|member|olympic_lan_status
id|__u16
id|olympic_lan_status
suffix:semicolon
DECL|member|olympic_ring_speed
id|__u8
id|olympic_ring_speed
suffix:semicolon
DECL|member|pkt_buf_sz
id|__u16
id|pkt_buf_sz
suffix:semicolon
DECL|member|olympic_receive_options
DECL|member|olympic_copy_all_options
DECL|member|olympic_message_level
id|__u8
id|olympic_receive_options
comma
id|olympic_copy_all_options
comma
id|olympic_message_level
suffix:semicolon
DECL|member|olympic_addr_table_addr
DECL|member|olympic_parms_addr
id|__u16
id|olympic_addr_table_addr
comma
id|olympic_parms_addr
suffix:semicolon
DECL|member|olympic_laa
id|__u8
id|olympic_laa
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|olympic_adapter_addr_table
r_struct
id|olympic_adapter_addr_table
(brace
DECL|member|node_addr
id|__u8
id|node_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|func_addr
id|__u8
id|func_addr
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|olympic_parameters_table
r_struct
id|olympic_parameters_table
(brace
DECL|member|phys_addr
id|__u8
id|phys_addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|up_node_addr
id|__u8
id|up_node_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|up_phys_addr
id|__u8
id|up_phys_addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|poll_addr
id|__u8
id|poll_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
DECL|member|acc_priority
id|__u16
id|acc_priority
suffix:semicolon
DECL|member|auth_source_class
id|__u16
id|auth_source_class
suffix:semicolon
DECL|member|att_code
id|__u16
id|att_code
suffix:semicolon
DECL|member|source_addr
id|__u8
id|source_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|beacon_type
id|__u16
id|beacon_type
suffix:semicolon
DECL|member|major_vector
id|__u16
id|major_vector
suffix:semicolon
DECL|member|lan_status
id|__u16
id|lan_status
suffix:semicolon
DECL|member|soft_error_time
id|__u16
id|soft_error_time
suffix:semicolon
DECL|member|reserved1
id|__u16
id|reserved1
suffix:semicolon
DECL|member|local_ring
id|__u16
id|local_ring
suffix:semicolon
DECL|member|mon_error
id|__u16
id|mon_error
suffix:semicolon
DECL|member|beacon_transmit
id|__u16
id|beacon_transmit
suffix:semicolon
DECL|member|beacon_receive
id|__u16
id|beacon_receive
suffix:semicolon
DECL|member|frame_correl
id|__u16
id|frame_correl
suffix:semicolon
DECL|member|beacon_naun
id|__u8
id|beacon_naun
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
DECL|member|beacon_phys
id|__u8
id|beacon_phys
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
