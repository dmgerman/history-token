multiline_comment|/*&n; *   lanstreamer.h -- driver for the IBM Auto LANStreamer PCI Adapter&n; *&n; *  Written By: Mike Sullivan, IBM Corporation&n; *&n; *  Copyright (C) 1999 IBM Corporation&n; *&n; *  Linux driver for IBM PCI tokenring cards based on the LanStreamer MPC&n; *  chipset. &n; *&n; *  This driver is based on the olympic driver for IBM PCI TokenRing cards (Pit/Pit-Phy/Olympic&n; *  chipsets) written  by:&n; *      1999 Peter De Schrijver All Rights Reserved&n; *&t;1999 Mike Phillips (phillim@amtrak.com)&n; *&n; *  Base Driver Skeleton:&n; *      Written 1993-94 by Donald Becker.&n; *&n; *      Copyright 1993 United States Government as represented by the&n; *      Director, National Security Agency.&n; *&n; * This program is free software; you can redistribute it and/or modify      &n; * it under the terms of the GNU General Public License as published by      &n; * the Free Software Foundation; either version 2 of the License, or         &n; * (at your option) any later version.                                       &n; *                                                                           &n; * This program is distributed in the hope that it will be useful,           &n; * but WITHOUT ANY WARRANTY; without even the implied warranty of            &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             &n; * GNU General Public License for more details.                              &n; *                                                                           &n; * NO WARRANTY                                                               &n; * THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR        &n; * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT      &n; * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,      &n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is    &n; * solely responsible for determining the appropriateness of using and       &n; * distributing the Program and assumes all risks associated with its        &n; * exercise of rights under this Agreement, including but not limited to     &n; * the risks and costs of program errors, damage to or loss of data,         &n; * programs or equipment, and unavailability or interruption of operations.  &n; *                                                                           &n; * DISCLAIMER OF LIABILITY                                                   &n; * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY   &n; * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        &n; * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND   &n; * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     &n; * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE    &n; * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED  &n; * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES             &n; *                                                                           &n; * You should have received a copy of the GNU General Public License         &n; * along with this program; if not, write to the Free Software               &n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA &n; *                                                                           &n; * &n; *  12/10/99 - Alpha Release 0.1.0&n; *            First release to the public&n; *&n; */
DECL|macro|BCTL
mdefine_line|#define BCTL 0x60
DECL|macro|BCTL_SOFTRESET
mdefine_line|#define BCTL_SOFTRESET (1&lt;&lt;15)
DECL|macro|GPR
mdefine_line|#define GPR 0x4a
DECL|macro|GPR_AUTOSENSE
mdefine_line|#define GPR_AUTOSENSE (1&lt;&lt;2)
DECL|macro|GPR_16MBPS
mdefine_line|#define GPR_16MBPS (1&lt;&lt;3)
DECL|macro|LISR
mdefine_line|#define LISR 0x10
DECL|macro|LISR_SUM
mdefine_line|#define LISR_SUM 0x12
DECL|macro|LISR_RUM
mdefine_line|#define LISR_RUM 0x14
DECL|macro|LISR_LIE
mdefine_line|#define LISR_LIE (1&lt;&lt;15)
DECL|macro|LISR_SLIM
mdefine_line|#define LISR_SLIM (1&lt;&lt;13)
DECL|macro|LISR_SLI
mdefine_line|#define LISR_SLI (1&lt;&lt;12)
DECL|macro|LISR_BPEI
mdefine_line|#define LISR_BPEI (1&lt;&lt;9)
DECL|macro|LISR_BPE
mdefine_line|#define LISR_BPE (1&lt;&lt;8)
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
mdefine_line|#define SISR 0x16
DECL|macro|SISR_SUM
mdefine_line|#define SISR_SUM 0x18
DECL|macro|SISR_RUM
mdefine_line|#define SISR_RUM 0x1A
DECL|macro|SISR_MASK
mdefine_line|#define SISR_MASK 0x54
DECL|macro|SISR_MASK_SUM
mdefine_line|#define SISR_MASK_SUM 0x56
DECL|macro|SISR_MASK_RUM
mdefine_line|#define SISR_MASK_RUM 0x58
DECL|macro|SISR_MI
mdefine_line|#define SISR_MI (1&lt;&lt;15)
DECL|macro|SISR_TIMER
mdefine_line|#define SISR_TIMER (1&lt;&lt;11)
DECL|macro|SISR_LAP_PAR_ERR
mdefine_line|#define SISR_LAP_PAR_ERR (1&lt;&lt;10)
DECL|macro|SISR_LAP_ACC_ERR
mdefine_line|#define SISR_LAP_ACC_ERR (1&lt;&lt;9)
DECL|macro|SISR_PAR_ERR
mdefine_line|#define SISR_PAR_ERR (1&lt;&lt;8)
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
DECL|macro|MISR_RUM
mdefine_line|#define MISR_RUM 0x5A
DECL|macro|MISR_MASK
mdefine_line|#define MISR_MASK 0x5C
DECL|macro|MISR_MASK_RUM
mdefine_line|#define MISR_MASK_RUM 0x5E
DECL|macro|MISR_TX2_IDLE
mdefine_line|#define MISR_TX2_IDLE (1&lt;&lt;15)
DECL|macro|MISR_TX2_NO_STATUS
mdefine_line|#define MISR_TX2_NO_STATUS (1&lt;&lt;14)
DECL|macro|MISR_TX2_HALT
mdefine_line|#define MISR_TX2_HALT (1&lt;&lt;13)
DECL|macro|MISR_TX2_EOF
mdefine_line|#define MISR_TX2_EOF (1&lt;&lt;12)
DECL|macro|MISR_TX1_IDLE
mdefine_line|#define MISR_TX1_IDLE (1&lt;&lt;11)
DECL|macro|MISR_TX1_NO_STATUS
mdefine_line|#define MISR_TX1_NO_STATUS (1&lt;&lt;10)
DECL|macro|MISR_TX1_HALT
mdefine_line|#define MISR_TX1_HALT (1&lt;&lt;9)
DECL|macro|MISR_TX1_EOF
mdefine_line|#define MISR_TX1_EOF (1&lt;&lt;8)
DECL|macro|MISR_RX_NOBUF
mdefine_line|#define MISR_RX_NOBUF (1&lt;&lt;5)
DECL|macro|MISR_RX_EOB
mdefine_line|#define MISR_RX_EOB (1&lt;&lt;4)
DECL|macro|MISR_RX_NO_STATUS
mdefine_line|#define MISR_RX_NO_STATUS (1&lt;&lt;2)
DECL|macro|MISR_RX_HALT
mdefine_line|#define MISR_RX_HALT (1&lt;&lt;1)
DECL|macro|MISR_RX_EOF
mdefine_line|#define MISR_RX_EOF (1&lt;&lt;0)
DECL|macro|LAPA
mdefine_line|#define LAPA 0x62
DECL|macro|LAPE
mdefine_line|#define LAPE 0x64
DECL|macro|LAPD
mdefine_line|#define LAPD 0x66
DECL|macro|LAPDINC
mdefine_line|#define LAPDINC 0x68
DECL|macro|LAPWWO
mdefine_line|#define LAPWWO 0x6A
DECL|macro|LAPWWC
mdefine_line|#define LAPWWC 0x6C
DECL|macro|LAPCTL
mdefine_line|#define LAPCTL 0x6E
DECL|macro|TIMER
mdefine_line|#define TIMER 0x4E4
DECL|macro|BMCTL_SUM
mdefine_line|#define BMCTL_SUM 0x50
DECL|macro|BMCTL_RUM
mdefine_line|#define BMCTL_RUM 0x52
DECL|macro|BMCTL_TX1_DIS
mdefine_line|#define BMCTL_TX1_DIS (1&lt;&lt;14)
DECL|macro|BMCTL_TX2_DIS
mdefine_line|#define BMCTL_TX2_DIS (1&lt;&lt;10)
DECL|macro|BMCTL_RX_DIS
mdefine_line|#define BMCTL_RX_DIS (1&lt;&lt;6)
DECL|macro|BMCTL_RX_ENABLED
mdefine_line|#define BMCTL_RX_ENABLED  (1&lt;&lt;5)
DECL|macro|RXLBDA
mdefine_line|#define RXLBDA  0x90
DECL|macro|RXBDA
mdefine_line|#define RXBDA   0x94
DECL|macro|RXSTAT
mdefine_line|#define RXSTAT  0x98
DECL|macro|RXDBA
mdefine_line|#define RXDBA   0x9C
DECL|macro|TX1LFDA
mdefine_line|#define TX1LFDA 0xA0
DECL|macro|TX1FDA
mdefine_line|#define TX1FDA  0xA4
DECL|macro|TX1STAT
mdefine_line|#define TX1STAT 0xA8
DECL|macro|TX1DBA
mdefine_line|#define TX1DBA  0xAC
DECL|macro|TX2LFDA
mdefine_line|#define TX2LFDA 0xB0
DECL|macro|TX2FDA
mdefine_line|#define TX2FDA  0xB4
DECL|macro|TX2STAT
mdefine_line|#define TX2STAT 0xB8
DECL|macro|TX2DBA
mdefine_line|#define TX2DBA  0xBC
DECL|macro|STREAMER_IO_SPACE
mdefine_line|#define STREAMER_IO_SPACE 256
DECL|macro|SRB_COMMAND_SIZE
mdefine_line|#define SRB_COMMAND_SIZE 50
DECL|macro|STREAMER_MAX_ADAPTERS
mdefine_line|#define STREAMER_MAX_ADAPTERS 8&t;/* 0x08 __MODULE_STRING can&squot;t hand 0xnn */
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
multiline_comment|/* Defines for SRB Commands */
DECL|macro|SRB_CLOSE_ADAPTER
mdefine_line|#define SRB_CLOSE_ADAPTER 0x04
DECL|macro|SRB_CONFIGURE_BRIDGE
mdefine_line|#define SRB_CONFIGURE_BRIDGE 0x0c
DECL|macro|SRB_CONFIGURE_HP_CHANNEL
mdefine_line|#define SRB_CONFIGURE_HP_CHANNEL 0x13
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
DECL|macro|SRB_RESET_TARGET_SEGMETN
mdefine_line|#define SRB_RESET_TARGET_SEGMETN 0x14
DECL|macro|SRB_SAVE_CONFIGURATION
mdefine_line|#define SRB_SAVE_CONFIGURATION 0x1b
DECL|macro|SRB_SET_BRIDGE_PARMS
mdefine_line|#define SRB_SET_BRIDGE_PARMS 0x09
DECL|macro|SRB_SET_FUNC_ADDRESS
mdefine_line|#define SRB_SET_FUNC_ADDRESS 0x07
DECL|macro|SRB_SET_GROUP_ADDRESS
mdefine_line|#define SRB_SET_GROUP_ADDRESS 0x06
DECL|macro|SRB_SET_TARGET_SEGMENT
mdefine_line|#define SRB_SET_TARGET_SEGMENT 0x05
multiline_comment|/* Clear return code */
DECL|macro|STREAMER_CLEAR_RET_CODE
mdefine_line|#define STREAMER_CLEAR_RET_CODE 0xfe
multiline_comment|/* ARB Commands */
DECL|macro|ARB_RECEIVE_DATA
mdefine_line|#define ARB_RECEIVE_DATA 0x81
DECL|macro|ARB_LAN_CHANGE_STATUS
mdefine_line|#define ARB_LAN_CHANGE_STATUS 0x84
multiline_comment|/* ASB Response commands */
DECL|macro|ASB_RECEIVE_DATA
mdefine_line|#define ASB_RECEIVE_DATA 0x81
multiline_comment|/* Streamer defaults for buffers */
DECL|macro|STREAMER_RX_RING_SIZE
mdefine_line|#define STREAMER_RX_RING_SIZE 16&t;/* should be a power of 2 */
DECL|macro|STREAMER_TX_RING_SIZE
mdefine_line|#define STREAMER_TX_RING_SIZE 8&t;/* should be a power of 2 */
DECL|macro|PKT_BUF_SZ
mdefine_line|#define PKT_BUF_SZ 4096&t;&t;/* Default packet size */
multiline_comment|/* Streamer data structures */
DECL|struct|streamer_tx_desc
r_struct
id|streamer_tx_desc
(brace
DECL|member|forward
id|__u32
id|forward
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|bufcnt_framelen
id|__u32
id|bufcnt_framelen
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|member|buflen
id|__u32
id|buflen
suffix:semicolon
DECL|member|rsvd1
id|__u32
id|rsvd1
suffix:semicolon
DECL|member|rsvd2
id|__u32
id|rsvd2
suffix:semicolon
DECL|member|rsvd3
id|__u32
id|rsvd3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|streamer_rx_desc
r_struct
id|streamer_rx_desc
(brace
DECL|member|forward
id|__u32
id|forward
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|member|framelen_buflen
id|__u32
id|framelen_buflen
suffix:semicolon
)brace
suffix:semicolon
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
DECL|struct|streamer_private
r_struct
id|streamer_private
(brace
DECL|member|srb
id|__u16
id|srb
suffix:semicolon
DECL|member|trb
id|__u16
id|trb
suffix:semicolon
DECL|member|arb
id|__u16
id|arb
suffix:semicolon
DECL|member|asb
id|__u16
id|asb
suffix:semicolon
DECL|member|next
r_struct
id|streamer_private
op_star
id|next
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|streamer_mmio
id|__u8
op_star
id|streamer_mmio
suffix:semicolon
DECL|member|streamer_card_name
r_char
op_star
id|streamer_card_name
suffix:semicolon
DECL|member|streamer_lock
id|spinlock_t
id|streamer_lock
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
DECL|member|streamer_rx_ring
r_struct
id|streamer_rx_desc
op_star
id|streamer_rx_ring
suffix:semicolon
DECL|member|streamer_tx_ring
r_struct
id|streamer_tx_desc
op_star
id|streamer_tx_ring
suffix:semicolon
DECL|member|tx_ring_skb
r_struct
id|sk_buff
op_star
id|tx_ring_skb
(braket
id|STREAMER_TX_RING_SIZE
)braket
comma
DECL|member|rx_ring_skb
op_star
id|rx_ring_skb
(braket
id|STREAMER_RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_ring_free
DECL|member|tx_ring_last_status
DECL|member|rx_ring_last_received
r_int
id|tx_ring_free
comma
id|tx_ring_last_status
comma
id|rx_ring_last_received
comma
DECL|member|free_tx_ring_entries
id|free_tx_ring_entries
suffix:semicolon
DECL|member|streamer_stats
r_struct
id|net_device_stats
id|streamer_stats
suffix:semicolon
DECL|member|streamer_lan_status
id|__u16
id|streamer_lan_status
suffix:semicolon
DECL|member|streamer_ring_speed
id|__u8
id|streamer_ring_speed
suffix:semicolon
DECL|member|pkt_buf_sz
id|__u16
id|pkt_buf_sz
suffix:semicolon
DECL|member|streamer_receive_options
DECL|member|streamer_copy_all_options
id|__u8
id|streamer_receive_options
comma
id|streamer_copy_all_options
comma
DECL|member|streamer_message_level
id|streamer_message_level
suffix:semicolon
DECL|member|streamer_addr_table_addr
DECL|member|streamer_parms_addr
id|__u16
id|streamer_addr_table_addr
comma
id|streamer_parms_addr
suffix:semicolon
DECL|member|mac_rx_buffer
id|__u16
id|mac_rx_buffer
suffix:semicolon
DECL|member|streamer_laa
id|__u8
id|streamer_laa
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|streamer_adapter_addr_table
r_struct
id|streamer_adapter_addr_table
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
DECL|struct|streamer_parameters_table
r_struct
id|streamer_parameters_table
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
