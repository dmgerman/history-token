multiline_comment|/*&n; * icom.h&n; *&n; * Copyright (C) 2001 Michael Anderson, IBM Corporation&n; *&n; * Serial device driver include file.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include&lt;linux/serial_core.h&gt;
DECL|macro|BAUD_TABLE_LIMIT
mdefine_line|#define BAUD_TABLE_LIMIT&t;((sizeof(icom_acfg_baud)/sizeof(int)) - 1)
DECL|variable|icom_acfg_baud
r_static
r_int
id|icom_acfg_baud
(braket
)braket
op_assign
(brace
l_int|300
comma
l_int|600
comma
l_int|900
comma
l_int|1200
comma
l_int|1800
comma
l_int|2400
comma
l_int|3600
comma
l_int|4800
comma
l_int|7200
comma
l_int|9600
comma
l_int|14400
comma
l_int|19200
comma
l_int|28800
comma
l_int|38400
comma
l_int|57600
comma
l_int|76800
comma
l_int|115200
comma
l_int|153600
comma
l_int|230400
comma
l_int|307200
comma
l_int|460800
comma
)brace
suffix:semicolon
DECL|struct|icom_regs
r_struct
id|icom_regs
(brace
DECL|member|control
id|u32
id|control
suffix:semicolon
multiline_comment|/* Adapter Control Register     */
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
multiline_comment|/* Adapter Interrupt Register   */
DECL|member|int_mask
id|u32
id|int_mask
suffix:semicolon
multiline_comment|/* Adapter Interrupt Mask Reg   */
DECL|member|int_pri
id|u32
id|int_pri
suffix:semicolon
multiline_comment|/* Adapter Interrupt Priority r */
DECL|member|int_reg_b
id|u32
id|int_reg_b
suffix:semicolon
multiline_comment|/* Adapter non-masked Interrupt */
DECL|member|resvd01
id|u32
id|resvd01
suffix:semicolon
DECL|member|resvd02
id|u32
id|resvd02
suffix:semicolon
DECL|member|resvd03
id|u32
id|resvd03
suffix:semicolon
DECL|member|control_2
id|u32
id|control_2
suffix:semicolon
multiline_comment|/* Adapter Control Register 2   */
DECL|member|interrupt_2
id|u32
id|interrupt_2
suffix:semicolon
multiline_comment|/* Adapter Interrupt Register 2 */
DECL|member|int_mask_2
id|u32
id|int_mask_2
suffix:semicolon
multiline_comment|/* Adapter Interrupt Mask 2     */
DECL|member|int_pri_2
id|u32
id|int_pri_2
suffix:semicolon
multiline_comment|/* Adapter Interrupt Prior 2    */
DECL|member|int_reg_2b
id|u32
id|int_reg_2b
suffix:semicolon
multiline_comment|/* Adapter non-masked 2         */
)brace
suffix:semicolon
DECL|struct|func_dram
r_struct
id|func_dram
(brace
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|108
)braket
suffix:semicolon
multiline_comment|/* 0-1B0   reserved by personality code */
DECL|member|RcvStatusAddr
id|u32
id|RcvStatusAddr
suffix:semicolon
multiline_comment|/* 1B0-1B3 Status Address for Next rcv */
DECL|member|RcvStnAddr
id|u8
id|RcvStnAddr
suffix:semicolon
multiline_comment|/* 1B4     Receive Station Addr */
DECL|member|IdleState
id|u8
id|IdleState
suffix:semicolon
multiline_comment|/* 1B5     Idle State */
DECL|member|IdleMonitor
id|u8
id|IdleMonitor
suffix:semicolon
multiline_comment|/* 1B6     Idle Monitor */
DECL|member|FlagFillIdleTimer
id|u8
id|FlagFillIdleTimer
suffix:semicolon
multiline_comment|/* 1B7     Flag Fill Idle Timer */
DECL|member|XmitStatusAddr
id|u32
id|XmitStatusAddr
suffix:semicolon
multiline_comment|/* 1B8-1BB Transmit Status Address */
DECL|member|StartXmitCmd
id|u8
id|StartXmitCmd
suffix:semicolon
multiline_comment|/* 1BC     Start Xmit Command */
DECL|member|HDLCConfigReg
id|u8
id|HDLCConfigReg
suffix:semicolon
multiline_comment|/* 1BD     Reserved */
DECL|member|CauseCode
id|u8
id|CauseCode
suffix:semicolon
multiline_comment|/* 1BE     Cause code for fatal error */
DECL|member|xchar
id|u8
id|xchar
suffix:semicolon
multiline_comment|/* 1BF     High priority send */
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
multiline_comment|/* 1C0-1C3 Reserved */
DECL|member|PrevCmdReg
id|u8
id|PrevCmdReg
suffix:semicolon
multiline_comment|/* 1C4     Reserved */
DECL|member|CmdReg
id|u8
id|CmdReg
suffix:semicolon
multiline_comment|/* 1C5     Command Register */
DECL|member|async_config2
id|u8
id|async_config2
suffix:semicolon
multiline_comment|/* 1C6     Async Config Byte 2 */
DECL|member|async_config3
id|u8
id|async_config3
suffix:semicolon
multiline_comment|/* 1C7     Async Config Byte 3 */
DECL|member|dce_resvd
id|u8
id|dce_resvd
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 1C8-1DB DCE Rsvd           */
DECL|member|dce_resvd21
id|u8
id|dce_resvd21
suffix:semicolon
multiline_comment|/* 1DC     DCE Rsvd (21st byte */
DECL|member|misc_flags
id|u8
id|misc_flags
suffix:semicolon
multiline_comment|/* 1DD     misc flags         */
DECL|macro|V2_HARDWARE
mdefine_line|#define V2_HARDWARE     0x40
DECL|macro|ICOM_HDW_ACTIVE
mdefine_line|#define ICOM_HDW_ACTIVE 0x01
DECL|member|call_length
id|u8
id|call_length
suffix:semicolon
multiline_comment|/* 1DE     Phone #/CFI buff ln */
DECL|member|call_length2
id|u8
id|call_length2
suffix:semicolon
multiline_comment|/* 1DF     Upper byte (unused) */
DECL|member|call_addr
id|u32
id|call_addr
suffix:semicolon
multiline_comment|/* 1E0-1E3 Phn #/CFI buff addr */
DECL|member|timer_value
id|u16
id|timer_value
suffix:semicolon
multiline_comment|/* 1E4-1E5 general timer value */
DECL|member|timer_command
id|u8
id|timer_command
suffix:semicolon
multiline_comment|/* 1E6     general timer cmd  */
DECL|member|dce_command
id|u8
id|dce_command
suffix:semicolon
multiline_comment|/* 1E7     dce command reg    */
DECL|member|dce_cmd_status
id|u8
id|dce_cmd_status
suffix:semicolon
multiline_comment|/* 1E8     dce command stat   */
DECL|member|x21_r1_ioff
id|u8
id|x21_r1_ioff
suffix:semicolon
multiline_comment|/* 1E9     dce ready counter  */
DECL|member|x21_r0_ioff
id|u8
id|x21_r0_ioff
suffix:semicolon
multiline_comment|/* 1EA     dce not ready ctr  */
DECL|member|x21_ralt_ioff
id|u8
id|x21_ralt_ioff
suffix:semicolon
multiline_comment|/* 1EB     dce CNR counter    */
DECL|member|x21_r1_ion
id|u8
id|x21_r1_ion
suffix:semicolon
multiline_comment|/* 1EC     dce ready I on ctr */
DECL|member|rsvd_ier
id|u8
id|rsvd_ier
suffix:semicolon
multiline_comment|/* 1ED     Rsvd for IER (if ne */
DECL|member|ier
id|u8
id|ier
suffix:semicolon
multiline_comment|/* 1EE     Interrupt Enable   */
DECL|member|isr
id|u8
id|isr
suffix:semicolon
multiline_comment|/* 1EF     Input Signal Reg   */
DECL|member|osr
id|u8
id|osr
suffix:semicolon
multiline_comment|/* 1F0     Output Signal Reg  */
DECL|member|reset
id|u8
id|reset
suffix:semicolon
multiline_comment|/* 1F1     Reset/Reload Reg   */
DECL|member|disable
id|u8
id|disable
suffix:semicolon
multiline_comment|/* 1F2     Disable Reg        */
DECL|member|sync
id|u8
id|sync
suffix:semicolon
multiline_comment|/* 1F3     Sync Reg           */
DECL|member|error_stat
id|u8
id|error_stat
suffix:semicolon
multiline_comment|/* 1F4     Error Status       */
DECL|member|cable_id
id|u8
id|cable_id
suffix:semicolon
multiline_comment|/* 1F5     Cable ID           */
DECL|member|cs_length
id|u8
id|cs_length
suffix:semicolon
multiline_comment|/* 1F6     CS Load Length     */
DECL|member|mac_length
id|u8
id|mac_length
suffix:semicolon
multiline_comment|/* 1F7     Mac Load Length    */
DECL|member|cs_load_addr
id|u32
id|cs_load_addr
suffix:semicolon
multiline_comment|/* 1F8-1FB Call Load PCI Addr */
DECL|member|mac_load_addr
id|u32
id|mac_load_addr
suffix:semicolon
multiline_comment|/* 1FC-1FF Mac Load PCI Addr  */
)brace
suffix:semicolon
multiline_comment|/*&n; * adapter defines and structures&n; */
DECL|macro|ICOM_CONTROL_START_A
mdefine_line|#define ICOM_CONTROL_START_A         0x00000008
DECL|macro|ICOM_CONTROL_STOP_A
mdefine_line|#define ICOM_CONTROL_STOP_A          0x00000004
DECL|macro|ICOM_CONTROL_START_B
mdefine_line|#define ICOM_CONTROL_START_B         0x00000002
DECL|macro|ICOM_CONTROL_STOP_B
mdefine_line|#define ICOM_CONTROL_STOP_B          0x00000001
DECL|macro|ICOM_CONTROL_START_C
mdefine_line|#define ICOM_CONTROL_START_C         0x00000008
DECL|macro|ICOM_CONTROL_STOP_C
mdefine_line|#define ICOM_CONTROL_STOP_C          0x00000004
DECL|macro|ICOM_CONTROL_START_D
mdefine_line|#define ICOM_CONTROL_START_D         0x00000002
DECL|macro|ICOM_CONTROL_STOP_D
mdefine_line|#define ICOM_CONTROL_STOP_D          0x00000001
DECL|macro|ICOM_IRAM_OFFSET
mdefine_line|#define ICOM_IRAM_OFFSET             0x1000
DECL|macro|ICOM_IRAM_SIZE
mdefine_line|#define ICOM_IRAM_SIZE               0x0C00
DECL|macro|ICOM_DCE_IRAM_OFFSET
mdefine_line|#define ICOM_DCE_IRAM_OFFSET         0x0A00
DECL|macro|ICOM_CABLE_ID_VALID
mdefine_line|#define ICOM_CABLE_ID_VALID          0x01
DECL|macro|ICOM_CABLE_ID_MASK
mdefine_line|#define ICOM_CABLE_ID_MASK           0xF0
DECL|macro|ICOM_DISABLE
mdefine_line|#define ICOM_DISABLE                 0x80
DECL|macro|CMD_XMIT_RCV_ENABLE
mdefine_line|#define CMD_XMIT_RCV_ENABLE          0xC0
DECL|macro|CMD_XMIT_ENABLE
mdefine_line|#define CMD_XMIT_ENABLE              0x40
DECL|macro|CMD_RCV_DISABLE
mdefine_line|#define CMD_RCV_DISABLE              0x00
DECL|macro|CMD_RCV_ENABLE
mdefine_line|#define CMD_RCV_ENABLE               0x80
DECL|macro|CMD_RESTART
mdefine_line|#define CMD_RESTART                  0x01
DECL|macro|CMD_HOLD_XMIT
mdefine_line|#define CMD_HOLD_XMIT                0x02
DECL|macro|CMD_SND_BREAK
mdefine_line|#define CMD_SND_BREAK                0x04
DECL|macro|RS232_CABLE
mdefine_line|#define RS232_CABLE                  0x06
DECL|macro|V24_CABLE
mdefine_line|#define V24_CABLE                    0x0E
DECL|macro|V35_CABLE
mdefine_line|#define V35_CABLE                    0x0C
DECL|macro|V36_CABLE
mdefine_line|#define V36_CABLE                    0x02
DECL|macro|NO_CABLE
mdefine_line|#define NO_CABLE                     0x00
DECL|macro|START_DOWNLOAD
mdefine_line|#define START_DOWNLOAD               0x80
DECL|macro|ICOM_INT_MASK_PRC_A
mdefine_line|#define ICOM_INT_MASK_PRC_A          0x00003FFF
DECL|macro|ICOM_INT_MASK_PRC_B
mdefine_line|#define ICOM_INT_MASK_PRC_B          0x3FFF0000
DECL|macro|ICOM_INT_MASK_PRC_C
mdefine_line|#define ICOM_INT_MASK_PRC_C          0x00003FFF
DECL|macro|ICOM_INT_MASK_PRC_D
mdefine_line|#define ICOM_INT_MASK_PRC_D          0x3FFF0000
DECL|macro|INT_RCV_COMPLETED
mdefine_line|#define INT_RCV_COMPLETED            0x1000
DECL|macro|INT_XMIT_COMPLETED
mdefine_line|#define INT_XMIT_COMPLETED           0x2000
DECL|macro|INT_IDLE_DETECT
mdefine_line|#define INT_IDLE_DETECT              0x0800
DECL|macro|INT_RCV_DISABLED
mdefine_line|#define INT_RCV_DISABLED             0x0400
DECL|macro|INT_XMIT_DISABLED
mdefine_line|#define INT_XMIT_DISABLED            0x0200
DECL|macro|INT_RCV_XMIT_SHUTDOWN
mdefine_line|#define INT_RCV_XMIT_SHUTDOWN        0x0100
DECL|macro|INT_FATAL_ERROR
mdefine_line|#define INT_FATAL_ERROR              0x0080
DECL|macro|INT_CABLE_PULL
mdefine_line|#define INT_CABLE_PULL               0x0020
DECL|macro|INT_SIGNAL_CHANGE
mdefine_line|#define INT_SIGNAL_CHANGE            0x0010
DECL|macro|HDLC_PPP_PURE_ASYNC
mdefine_line|#define HDLC_PPP_PURE_ASYNC          0x02
DECL|macro|HDLC_FF_FILL
mdefine_line|#define HDLC_FF_FILL                 0x00
DECL|macro|HDLC_HDW_FLOW
mdefine_line|#define HDLC_HDW_FLOW                0x01
DECL|macro|START_XMIT
mdefine_line|#define START_XMIT                   0x80
DECL|macro|ICOM_ACFG_DRIVE1
mdefine_line|#define ICOM_ACFG_DRIVE1             0x20
DECL|macro|ICOM_ACFG_NO_PARITY
mdefine_line|#define ICOM_ACFG_NO_PARITY          0x00
DECL|macro|ICOM_ACFG_PARITY_ENAB
mdefine_line|#define ICOM_ACFG_PARITY_ENAB        0x02
DECL|macro|ICOM_ACFG_PARITY_ODD
mdefine_line|#define ICOM_ACFG_PARITY_ODD         0x01
DECL|macro|ICOM_ACFG_8BPC
mdefine_line|#define ICOM_ACFG_8BPC               0x00
DECL|macro|ICOM_ACFG_7BPC
mdefine_line|#define ICOM_ACFG_7BPC               0x04
DECL|macro|ICOM_ACFG_6BPC
mdefine_line|#define ICOM_ACFG_6BPC               0x08
DECL|macro|ICOM_ACFG_5BPC
mdefine_line|#define ICOM_ACFG_5BPC               0x0C
DECL|macro|ICOM_ACFG_1STOP_BIT
mdefine_line|#define ICOM_ACFG_1STOP_BIT          0x00
DECL|macro|ICOM_ACFG_2STOP_BIT
mdefine_line|#define ICOM_ACFG_2STOP_BIT          0x10
DECL|macro|ICOM_DTR
mdefine_line|#define ICOM_DTR                     0x80
DECL|macro|ICOM_RTS
mdefine_line|#define ICOM_RTS                     0x40
DECL|macro|ICOM_RI
mdefine_line|#define ICOM_RI                      0x08
DECL|macro|ICOM_DSR
mdefine_line|#define ICOM_DSR                     0x80
DECL|macro|ICOM_DCD
mdefine_line|#define ICOM_DCD                     0x20
DECL|macro|ICOM_CTS
mdefine_line|#define ICOM_CTS                     0x40
DECL|macro|NUM_XBUFFS
mdefine_line|#define NUM_XBUFFS 1
DECL|macro|NUM_RBUFFS
mdefine_line|#define NUM_RBUFFS 2
DECL|macro|RCV_BUFF_SZ
mdefine_line|#define RCV_BUFF_SZ 0x0200
DECL|macro|XMIT_BUFF_SZ
mdefine_line|#define XMIT_BUFF_SZ 0x1000
DECL|struct|statusArea
r_struct
id|statusArea
(brace
multiline_comment|/**********************************************/
multiline_comment|/* Transmit Status Area                       */
multiline_comment|/**********************************************/
DECL|struct|xmit_status_area
r_struct
id|xmit_status_area
(brace
DECL|member|leNext
id|u32
id|leNext
suffix:semicolon
multiline_comment|/* Next entry in Little Endian on Adapter */
DECL|member|leNextASD
id|u32
id|leNextASD
suffix:semicolon
DECL|member|leBuffer
id|u32
id|leBuffer
suffix:semicolon
multiline_comment|/* Buffer for entry in LE for Adapter */
DECL|member|leLengthASD
id|u16
id|leLengthASD
suffix:semicolon
DECL|member|leOffsetASD
id|u16
id|leOffsetASD
suffix:semicolon
DECL|member|leLength
id|u16
id|leLength
suffix:semicolon
multiline_comment|/* Length of data in segment */
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|macro|SA_FLAGS_DONE
mdefine_line|#define SA_FLAGS_DONE           0x0080&t;/* Done with Segment */
DECL|macro|SA_FLAGS_CONTINUED
mdefine_line|#define SA_FLAGS_CONTINUED      0x8000&t;/* More Segments */
DECL|macro|SA_FLAGS_IDLE
mdefine_line|#define SA_FLAGS_IDLE           0x4000&t;/* Mark IDLE after frm */
DECL|macro|SA_FLAGS_READY_TO_XMIT
mdefine_line|#define SA_FLAGS_READY_TO_XMIT  0x0800
DECL|macro|SA_FLAGS_STAT_MASK
mdefine_line|#define SA_FLAGS_STAT_MASK      0x007F
DECL|member|xmit
)brace
id|xmit
(braket
id|NUM_XBUFFS
)braket
suffix:semicolon
multiline_comment|/**********************************************/
multiline_comment|/* Receive Status Area                        */
multiline_comment|/**********************************************/
r_struct
(brace
DECL|member|leNext
id|u32
id|leNext
suffix:semicolon
multiline_comment|/* Next entry in Little Endian on Adapter */
DECL|member|leNextASD
id|u32
id|leNextASD
suffix:semicolon
DECL|member|leBuffer
id|u32
id|leBuffer
suffix:semicolon
multiline_comment|/* Buffer for entry in LE for Adapter */
DECL|member|WorkingLength
id|u16
id|WorkingLength
suffix:semicolon
multiline_comment|/* size of segment */
DECL|member|reserv01
id|u16
id|reserv01
suffix:semicolon
DECL|member|leLength
id|u16
id|leLength
suffix:semicolon
multiline_comment|/* Length of data in segment */
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|macro|SA_FL_RCV_DONE
mdefine_line|#define SA_FL_RCV_DONE           0x0010&t;/* Data ready */
DECL|macro|SA_FLAGS_OVERRUN
mdefine_line|#define SA_FLAGS_OVERRUN         0x0040
DECL|macro|SA_FLAGS_PARITY_ERROR
mdefine_line|#define SA_FLAGS_PARITY_ERROR    0x0080
DECL|macro|SA_FLAGS_FRAME_ERROR
mdefine_line|#define SA_FLAGS_FRAME_ERROR     0x0001
DECL|macro|SA_FLAGS_FRAME_TRUNC
mdefine_line|#define SA_FLAGS_FRAME_TRUNC     0x0002
DECL|macro|SA_FLAGS_BREAK_DET
mdefine_line|#define SA_FLAGS_BREAK_DET       0x0004&t;/* set conditionally by device driver, not hardware */
DECL|macro|SA_FLAGS_RCV_MASK
mdefine_line|#define SA_FLAGS_RCV_MASK        0xFFE6
DECL|member|rcv
)brace
id|rcv
(braket
id|NUM_RBUFFS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|icom_adapter
suffix:semicolon
DECL|macro|ICOM_MAJOR
mdefine_line|#define ICOM_MAJOR       243
DECL|macro|ICOM_MINOR_START
mdefine_line|#define ICOM_MINOR_START 0
DECL|struct|icom_port
r_struct
id|icom_port
(brace
DECL|member|uart_port
r_struct
id|uart_port
id|uart_port
suffix:semicolon
DECL|member|imbed_modem
id|u8
id|imbed_modem
suffix:semicolon
DECL|macro|ICOM_UNKNOWN
mdefine_line|#define ICOM_UNKNOWN&t;&t;1
DECL|macro|ICOM_RVX
mdefine_line|#define ICOM_RVX&t;&t;2
DECL|macro|ICOM_IMBED_MODEM
mdefine_line|#define ICOM_IMBED_MODEM&t;3
DECL|member|cable_id
r_int
r_char
id|cable_id
suffix:semicolon
DECL|member|read_status_mask
r_int
r_char
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
r_char
id|ignore_status_mask
suffix:semicolon
DECL|member|int_reg
r_void
id|__iomem
op_star
id|int_reg
suffix:semicolon
DECL|member|global_reg
r_struct
id|icom_regs
id|__iomem
op_star
id|global_reg
suffix:semicolon
DECL|member|dram
r_struct
id|func_dram
id|__iomem
op_star
id|dram
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|statStg
r_struct
id|statusArea
op_star
id|statStg
suffix:semicolon
DECL|member|statStg_pci
id|dma_addr_t
id|statStg_pci
suffix:semicolon
DECL|member|xmitRestart
id|u32
op_star
id|xmitRestart
suffix:semicolon
DECL|member|xmitRestart_pci
id|dma_addr_t
id|xmitRestart_pci
suffix:semicolon
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_buf_pci
id|dma_addr_t
id|xmit_buf_pci
suffix:semicolon
DECL|member|recv_buf
r_int
r_char
op_star
id|recv_buf
suffix:semicolon
DECL|member|recv_buf_pci
id|dma_addr_t
id|recv_buf_pci
suffix:semicolon
DECL|member|next_rcv
r_int
id|next_rcv
suffix:semicolon
DECL|member|put_length
r_int
id|put_length
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|macro|ICOM_PORT_ACTIVE
mdefine_line|#define ICOM_PORT_ACTIVE&t;1&t;/* Port exists. */
DECL|macro|ICOM_PORT_OFF
mdefine_line|#define ICOM_PORT_OFF&t;&t;0&t;/* Port does not exist. */
DECL|member|load_in_progress
r_int
id|load_in_progress
suffix:semicolon
DECL|member|adapter
r_struct
id|icom_adapter
op_star
id|adapter
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|icom_adapter
r_struct
id|icom_adapter
(brace
DECL|member|base_addr
r_void
id|__iomem
op_star
id|base_addr
suffix:semicolon
DECL|member|base_addr_pci
r_int
r_int
id|base_addr_pci
suffix:semicolon
DECL|member|irq_number
r_int
r_char
id|irq_number
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|port_info
r_struct
id|icom_port
id|port_info
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|macro|ADAPTER_V1
mdefine_line|#define ADAPTER_V1&t;0x0001
DECL|macro|ADAPTER_V2
mdefine_line|#define ADAPTER_V2&t;0x0002
DECL|member|subsystem_id
id|u32
id|subsystem_id
suffix:semicolon
DECL|macro|FOUR_PORT_MODEL
mdefine_line|#define FOUR_PORT_MODEL&t;&t;&t;&t;0x0252
DECL|macro|V2_TWO_PORTS_RVX
mdefine_line|#define V2_TWO_PORTS_RVX&t;&t;&t;0x021A
DECL|macro|V2_ONE_PORT_RVX_ONE_PORT_IMBED_MDM
mdefine_line|#define V2_ONE_PORT_RVX_ONE_PORT_IMBED_MDM&t;0x0251
DECL|member|numb_ports
r_int
id|numb_ports
suffix:semicolon
DECL|member|icom_adapter_entry
r_struct
id|list_head
id|icom_adapter_entry
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* prototype */
r_extern
r_void
id|iCom_sercons_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|struct|lookup_proc_table
r_struct
id|lookup_proc_table
(brace
DECL|member|global_control_reg
id|u32
id|__iomem
op_star
id|global_control_reg
suffix:semicolon
DECL|member|processor_id
r_int
r_int
id|processor_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lookup_int_table
r_struct
id|lookup_int_table
(brace
DECL|member|global_int_mask
id|u32
id|__iomem
op_star
id|global_int_mask
suffix:semicolon
DECL|member|processor_id
r_int
r_int
id|processor_id
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MSECS_TO_JIFFIES
mdefine_line|#define MSECS_TO_JIFFIES(ms) (((ms)*HZ+999)/1000)
eof
