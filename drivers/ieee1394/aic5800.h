multiline_comment|/*&n;**  aic5800.h - Adaptec AIC-5800 PCI-IEEE1394 chip driver header file&n;**  Copyright (C)1999 Emanuel Pirker &lt;epirker@edu.uni-klu.ac.at&gt;&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;*/
macro_line|#ifndef AIC5800_H
DECL|macro|AIC5800_H
mdefine_line|#define AIC5800_H
DECL|macro|AIC5800_DRIVER_NAME
mdefine_line|#define AIC5800_DRIVER_NAME      &quot;aic5800&quot;
DECL|macro|MAX_AIC5800_CARDS
mdefine_line|#define MAX_AIC5800_CARDS        4
DECL|macro|AIC5800_REGSPACE_SIZE
mdefine_line|#define AIC5800_REGSPACE_SIZE    512
DECL|macro|AIC5800_PBUF_SIZE
mdefine_line|#define AIC5800_PBUF_SIZE        512
DECL|macro|MAX_AT_PROGRAM_SIZE
mdefine_line|#define MAX_AT_PROGRAM_SIZE      10
DECL|macro|AIC5800_ARFIFO_SIZE
mdefine_line|#define AIC5800_ARFIFO_SIZE      128
DECL|struct|dma_cmd
r_struct
id|dma_cmd
(brace
DECL|member|control
id|u32
id|control
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|branchAddress
id|u32
id|branchAddress
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aic5800
r_struct
id|aic5800
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* sequential card number */
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* remapped memory spaces */
DECL|member|registers
r_void
op_star
id|registers
suffix:semicolon
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|phyid
DECL|member|isroot
r_int
id|phyid
comma
id|isroot
suffix:semicolon
DECL|member|rcv_page
r_void
op_star
id|rcv_page
suffix:semicolon
DECL|member|pbuf
r_void
op_star
id|pbuf
suffix:semicolon
DECL|member|AT_program
r_struct
id|dma_cmd
op_star
id|AT_program
suffix:semicolon
DECL|member|AT_status
id|u32
op_star
id|AT_status
suffix:semicolon
DECL|member|AR_program
r_struct
id|dma_cmd
op_star
id|AR_program
suffix:semicolon
DECL|member|AR_status
id|u32
op_star
id|AR_status
suffix:semicolon
DECL|member|AR_active
r_int
id|AR_active
suffix:semicolon
DECL|member|async_queue
r_struct
id|hpsb_packet
op_star
id|async_queue
suffix:semicolon
DECL|member|async_queue_lock
id|spinlock_t
id|async_queue_lock
suffix:semicolon
DECL|member|NumInterrupts
DECL|member|NumBusResets
r_int
r_int
id|NumInterrupts
comma
id|NumBusResets
suffix:semicolon
DECL|member|TxPackets
DECL|member|RxPackets
r_int
r_int
id|TxPackets
comma
id|RxPackets
suffix:semicolon
DECL|member|TxErrors
DECL|member|RxErrors
r_int
r_int
id|TxErrors
comma
id|RxErrors
suffix:semicolon
DECL|member|TxRdy
DECL|member|ATError
DECL|member|HdrErr
DECL|member|TCodeErr
DECL|member|SendRej
r_int
r_int
id|TxRdy
comma
id|ATError
comma
id|HdrErr
comma
id|TCodeErr
comma
id|SendRej
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Register read and write helper functions.&n; */
DECL|function|reg_write
r_inline
r_static
r_void
id|reg_write
c_func
(paren
r_const
r_struct
id|aic5800
op_star
id|aic
comma
r_int
id|offset
comma
id|u32
id|data
)paren
(brace
id|writel
c_func
(paren
id|data
comma
id|aic-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|reg_read
r_inline
r_static
id|u32
id|reg_read
c_func
(paren
r_const
r_struct
id|aic5800
op_star
id|aic
comma
r_int
id|offset
)paren
(brace
r_return
id|readl
c_func
(paren
id|aic-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|reg_set_bits
r_inline
r_static
r_void
id|reg_set_bits
c_func
(paren
r_const
r_struct
id|aic5800
op_star
id|aic
comma
r_int
id|offset
comma
id|u32
id|mask
)paren
(brace
id|reg_write
c_func
(paren
id|aic
comma
id|offset
comma
(paren
id|reg_read
c_func
(paren
id|aic
comma
id|offset
)paren
op_or
id|mask
)paren
)paren
suffix:semicolon
)brace
DECL|function|reg_clear_bits
r_inline
r_static
r_void
id|reg_clear_bits
c_func
(paren
r_const
r_struct
id|aic5800
op_star
id|aic
comma
r_int
id|offset
comma
id|u32
id|mask
)paren
(brace
id|reg_write
c_func
(paren
id|aic
comma
id|offset
comma
(paren
id|reg_read
c_func
(paren
id|aic
comma
id|offset
)paren
op_amp
op_complement
id|mask
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  AIC-5800 Registers */
DECL|macro|AT_ChannelControl
mdefine_line|#define AT_ChannelControl&t;0x0
DECL|macro|AT_ChannelStatus
mdefine_line|#define AT_ChannelStatus&t;0x4
DECL|macro|AT_CommandPtr
mdefine_line|#define AT_CommandPtr&t;0xC
DECL|macro|AT_InterruptSelect
mdefine_line|#define AT_InterruptSelect&t;0x10
DECL|macro|AT_BranchSelect
mdefine_line|#define AT_BranchSelect&t;0x14
DECL|macro|AT_WaitSelect
mdefine_line|#define AT_WaitSelect&t;0x18
multiline_comment|/* Asynchronous receive */
DECL|macro|AR_ChannelControl
mdefine_line|#define AR_ChannelControl&t;0x20
DECL|macro|AR_ChannelStatus
mdefine_line|#define AR_ChannelStatus&t;0x24
DECL|macro|AR_CommandPtr
mdefine_line|#define AR_CommandPtr&t;0x2C
multiline_comment|/* ITA */
DECL|macro|ITA_ChannelControl
mdefine_line|#define ITA_ChannelControl&t;0x40
DECL|macro|ITA_ChannelStatus
mdefine_line|#define ITA_ChannelStatus&t;0x44
DECL|macro|ITA_CommandPtr
mdefine_line|#define ITA_CommandPtr&t;0x4C
multiline_comment|/* ITB */
DECL|macro|ITB_ChannelControl
mdefine_line|#define ITB_ChannelControl&t;0x60
DECL|macro|ITB_ChannelStatus
mdefine_line|#define ITB_ChannelStatus&t;0x64
DECL|macro|ITB_CommandPtr
mdefine_line|#define ITB_CommandPtr&t;0x6C
multiline_comment|/* IRA */
DECL|macro|IRA_ChannelControl
mdefine_line|#define IRA_ChannelControl&t;0x80
DECL|macro|IRA_ChannelStatus
mdefine_line|#define IRA_ChannelStatus&t;0x84
DECL|macro|IRA_CommandPtr
mdefine_line|#define IRA_CommandPtr&t;0x8C
multiline_comment|/* IRB */
DECL|macro|IRB_ChannelControl
mdefine_line|#define IRB_ChannelControl&t;0xA0
DECL|macro|IRB_ChannelStatus
mdefine_line|#define IRB_ChannelStatus&t;0xA4
DECL|macro|IRB_CommandPtr
mdefine_line|#define IRB_CommandPtr&t;0xAC
multiline_comment|/* miscellaneous */
DECL|macro|misc_Version
mdefine_line|#define misc_Version&t;0x100
DECL|macro|misc_Control
mdefine_line|#define misc_Control&t;0x104
DECL|macro|misc_NodeID
mdefine_line|#define misc_NodeID&t;0x108
DECL|macro|misc_Reset
mdefine_line|#define misc_Reset&t;0x10C
DECL|macro|misc_PacketControl
mdefine_line|#define misc_PacketControl&t;0x110
DECL|macro|misc_Diagnostic
mdefine_line|#define misc_Diagnostic&t;0x114
DECL|macro|misc_PhyControl
mdefine_line|#define misc_PhyControl&t;0x118
DECL|macro|misc_ATRetries
mdefine_line|#define misc_ATRetries&t;0x11C
DECL|macro|misc_SSNinterface
mdefine_line|#define misc_SSNinterface&t;0x120
DECL|macro|misc_CycleTimer
mdefine_line|#define misc_CycleTimer&t;0x124
multiline_comment|/* ITA */
DECL|macro|ITA_EventCycle
mdefine_line|#define ITA_EventCycle&t;0x130
DECL|macro|ITA_Configuration
mdefine_line|#define ITA_Configuration&t;0x134
DECL|macro|ITA_Bandwidth
mdefine_line|#define ITA_Bandwidth&t;0x138
multiline_comment|/* ITB */
DECL|macro|ITB_EventCycle
mdefine_line|#define ITB_EventCycle&t;0x140
DECL|macro|ITB_Configuration
mdefine_line|#define ITB_Configuration&t;0x144
DECL|macro|ITB_Bandwidth
mdefine_line|#define ITB_Bandwidth&t;0x148
multiline_comment|/* IRA */
DECL|macro|IRA_EventCycle
mdefine_line|#define IRA_EventCycle&t;0x150
DECL|macro|IRA_Configuration
mdefine_line|#define IRA_Configuration&t;0x154
multiline_comment|/* IRB */
DECL|macro|IRB_EventCycle
mdefine_line|#define IRB_EventCycle&t;0x160
DECL|macro|IRB_Configuration
mdefine_line|#define IRB_Configuration&t;0x164
multiline_comment|/* RSU */
DECL|macro|RSU_Enable
mdefine_line|#define RSU_Enable&t;0x170
DECL|macro|RSU_Interrupt
mdefine_line|#define RSU_Interrupt&t;0x174
DECL|macro|RSU_TablePtr
mdefine_line|#define RSU_TablePtr&t;0x178
DECL|macro|RSU_InterruptSet
mdefine_line|#define RSU_InterruptSet&t;0x17C
multiline_comment|/* misc */
DECL|macro|misc_InterruptEvents
mdefine_line|#define misc_InterruptEvents&t;0x180
DECL|macro|misc_InterruptMask
mdefine_line|#define misc_InterruptMask&t;0x184
DECL|macro|misc_InterruptClear
mdefine_line|#define misc_InterruptClear&t;0x188
DECL|macro|misc_CardBusEvent
mdefine_line|#define misc_CardBusEvent&t;0x1E0
DECL|macro|misc_CardBusMask
mdefine_line|#define misc_CardBusMask&t;0x1E4
DECL|macro|misc_CardBusState
mdefine_line|#define misc_CardBusState&t;0x1E8
DECL|macro|misc_CardBusForce
mdefine_line|#define misc_CardBusForce&t;0x1EC
DECL|macro|misc_SEEPCTL
mdefine_line|#define misc_SEEPCTL&t;        0x1F0
multiline_comment|/* Interrupts */
DECL|macro|INT_DmaAT
mdefine_line|#define INT_DmaAT             1
DECL|macro|INT_DmaAR
mdefine_line|#define INT_DmaAR            (1&lt;&lt;1)
DECL|macro|INT_DmaITA
mdefine_line|#define INT_DmaITA           (1&lt;&lt;2)
DECL|macro|INT_DmaITB
mdefine_line|#define INT_DmaITB           (1&lt;&lt;3)
DECL|macro|INT_DmaIRA
mdefine_line|#define INT_DmaIRA           (1&lt;&lt;4)
DECL|macro|INT_DmaIRB
mdefine_line|#define INT_DmaIRB           (1&lt;&lt;5)
DECL|macro|INT_PERResponse
mdefine_line|#define INT_PERResponse      (1&lt;&lt;7)
DECL|macro|INT_CycleEventITA
mdefine_line|#define INT_CycleEventITA    (1&lt;&lt;8)
DECL|macro|INT_CycleEventITB
mdefine_line|#define INT_CycleEventITB    (1&lt;&lt;9)
DECL|macro|INT_CycleEventIRA
mdefine_line|#define INT_CycleEventIRA    (1&lt;&lt;10)
DECL|macro|INT_CycleEventIRB
mdefine_line|#define INT_CycleEventIRB    (1&lt;&lt;11)
DECL|macro|INT_BusReset
mdefine_line|#define INT_BusReset         (1&lt;&lt;12)
DECL|macro|INT_CmdReset
mdefine_line|#define INT_CmdReset         (1&lt;&lt;13)
DECL|macro|INT_PhyInt
mdefine_line|#define INT_PhyInt           (1&lt;&lt;14)
DECL|macro|INT_RcvData
mdefine_line|#define INT_RcvData          (1&lt;&lt;15)
DECL|macro|INT_TxRdy
mdefine_line|#define INT_TxRdy            (1&lt;&lt;16)
DECL|macro|INT_CycleStart
mdefine_line|#define INT_CycleStart       (1&lt;&lt;17)
DECL|macro|INT_CycleSeconds
mdefine_line|#define INT_CycleSeconds     (1&lt;&lt;18)
DECL|macro|INT_CycleLost
mdefine_line|#define INT_CycleLost        (1&lt;&lt;19)
DECL|macro|INT_ATError
mdefine_line|#define INT_ATError          (1&lt;&lt;20)
DECL|macro|INT_SendRej
mdefine_line|#define INT_SendRej          (1&lt;&lt;21)
DECL|macro|INT_HdrErr
mdefine_line|#define INT_HdrErr           (1&lt;&lt;22)
DECL|macro|INT_TCodeErr
mdefine_line|#define INT_TCodeErr         (1&lt;&lt;23)
DECL|macro|INT_PRQUxferErr
mdefine_line|#define INT_PRQUxferErr      (1&lt;&lt;24)
DECL|macro|INT_PWQUxferErr
mdefine_line|#define INT_PWQUxferErr      (1&lt;&lt;25)
DECL|macro|INT_RSUxferErr
mdefine_line|#define INT_RSUxferErr       (1&lt;&lt;26)
DECL|macro|INT_RSDone
mdefine_line|#define INT_RSDone           (1&lt;&lt;27)
DECL|macro|INT_PSOutOfRetries
mdefine_line|#define INT_PSOutOfRetries   (1&lt;&lt;28)
DECL|macro|INT_cycleTooLong
mdefine_line|#define INT_cycleTooLong     (1&lt;&lt;29)
multiline_comment|/* DB DMA constants */
DECL|macro|DMA_CMD_OUTPUTMORE
mdefine_line|#define DMA_CMD_OUTPUTMORE  0
DECL|macro|DMA_CMD_OUTPUTLAST
mdefine_line|#define DMA_CMD_OUTPUTLAST  0x10000000
DECL|macro|DMA_CMD_INPUTMORE
mdefine_line|#define DMA_CMD_INPUTMORE   0x20000000
DECL|macro|DMA_CMD_INPUTLAST
mdefine_line|#define DMA_CMD_INPUTLAST   0x30000000
DECL|macro|DMA_CMD_STOREQUAD
mdefine_line|#define DMA_CMD_STOREQUAD   0x40000000
DECL|macro|DMA_CMD_LOADQUAD
mdefine_line|#define DMA_CMD_LOADQUAD    0x50000000
DECL|macro|DMA_CMD_NOP
mdefine_line|#define DMA_CMD_NOP         0x60000000
DECL|macro|DMA_CMD_STOP
mdefine_line|#define DMA_CMD_STOP        0x70000000
DECL|macro|DMA_KEY_STREAM0
mdefine_line|#define DMA_KEY_STREAM0  0
DECL|macro|DMA_KEY_STREAM1
mdefine_line|#define DMA_KEY_STREAM1  (1&lt;&lt;24)
DECL|macro|DMA_KEY_STREAM2
mdefine_line|#define DMA_KEY_STREAM2  (2&lt;&lt;24)
DECL|macro|DMA_KEY_STREAM3
mdefine_line|#define DMA_KEY_STREAM3  (3&lt;&lt;24)
DECL|macro|DMA_KEY_REGS
mdefine_line|#define DMA_KEY_REGS     (5&lt;&lt;24)
DECL|macro|DMA_KEY_SYSTEM
mdefine_line|#define DMA_KEY_SYSTEM   (6&lt;&lt;24)
DECL|macro|DMA_KEY_DEVICE
mdefine_line|#define DMA_KEY_DEVICE   (7&lt;&lt;24)
DECL|macro|DMA_INTR_NEVER
mdefine_line|#define DMA_INTR_NEVER    0
DECL|macro|DMA_INTR_TRUE
mdefine_line|#define DMA_INTR_TRUE     (1&lt;&lt;20)
DECL|macro|DMA_INTR_FALSE
mdefine_line|#define DMA_INTR_FALSE    (2&lt;&lt;20)
DECL|macro|DMA_INTR_ALWAYS
mdefine_line|#define DMA_INTR_ALWAYS   (3&lt;&lt;20)
DECL|macro|DMA_WAIT_NEVER
mdefine_line|#define DMA_WAIT_NEVER    0
DECL|macro|DMA_WAIT_TRUE
mdefine_line|#define DMA_WAIT_TRUE     (1&lt;&lt;16)
DECL|macro|DMA_WAIT_FALSE
mdefine_line|#define DMA_WAIT_FALSE    (2&lt;&lt;16)
DECL|macro|DMA_WAIT_ALWAYS
mdefine_line|#define DMA_WAIT_ALWAYS   (3&lt;&lt;16)
DECL|macro|DMA_BRANCH_NEVER
mdefine_line|#define DMA_BRANCH_NEVER    0
DECL|macro|DMA_BRANCH_TRUE
mdefine_line|#define DMA_BRANCH_TRUE     (1&lt;&lt;18)
DECL|macro|DMA_BRANCH_FALSE
mdefine_line|#define DMA_BRANCH_FALSE    (2&lt;&lt;18)
DECL|macro|DMA_BRANCH_ALWAYS
mdefine_line|#define DMA_BRANCH_ALWAYS   (3&lt;&lt;18)
DECL|macro|DMA_SPEED_100
mdefine_line|#define DMA_SPEED_100 0
DECL|macro|DMA_SPEED_200
mdefine_line|#define DMA_SPEED_200 (1&lt;&lt;16)
DECL|macro|DMA_SPEED_400
mdefine_line|#define DMA_SPEED_400 (2&lt;&lt;16)
multiline_comment|/* PHY access */
DECL|macro|LINK_PHY_READ
mdefine_line|#define LINK_PHY_READ                     (1&lt;&lt;15)
DECL|macro|LINK_PHY_WRITE
mdefine_line|#define LINK_PHY_WRITE                    (1&lt;&lt;14)
DECL|macro|LINK_PHY_ADDR
mdefine_line|#define LINK_PHY_ADDR(addr)               (addr&lt;&lt;8)
DECL|macro|LINK_PHY_WDATA
mdefine_line|#define LINK_PHY_WDATA(data)              (data)
DECL|macro|LINK_PHY_RADDR
mdefine_line|#define LINK_PHY_RADDR(addr)              (addr&lt;&lt;24)
DECL|variable|aic5800_csr_rom
id|quadlet_t
id|aic5800_csr_rom
(braket
)braket
op_assign
(brace
multiline_comment|/* bus info block */
l_int|0x041ffb82
comma
singleline_comment|// length of bus info block, CRC
l_int|0x31333934
comma
singleline_comment|// 1394 designator 
l_int|0xf005a000
comma
singleline_comment|// various capabilites
l_int|0x0000d189
comma
singleline_comment|// node_vendor_id, chip_id_hi
l_int|0x401010fc
comma
singleline_comment|// chip_id_lo
multiline_comment|/* root directory */
l_int|0x00040e54
comma
singleline_comment|// length of root directory, CRC
l_int|0x030000d1
comma
singleline_comment|// module_vendor_id
l_int|0x0c008000
comma
singleline_comment|// various capabilities
l_int|0x8d000006
comma
singleline_comment|// offset of node unique id leaf
l_int|0xd1000001
comma
singleline_comment|// offset of unit directory
multiline_comment|/* unit directory */
l_int|0x0003e60d
comma
singleline_comment|// length of unit directory, CRC
l_int|0x12000000
comma
singleline_comment|// unit_spec_id
l_int|0x13000000
comma
singleline_comment|// unit_sw_version
l_int|0xd4000004
comma
singleline_comment|// offset of unit dependent directory
multiline_comment|/* node unique id leaf */
l_int|0x00026ba7
comma
singleline_comment|// length of leaf, CRC
l_int|0x0000d189
comma
singleline_comment|// node_vendor_id, chip_id_hi
l_int|0x401010fc
comma
singleline_comment|// chip_id_lo
multiline_comment|/* unit dependent directory */
l_int|0x0002ae47
comma
singleline_comment|// length of directory, CRC
l_int|0x81000002
comma
singleline_comment|// offset of vendor name leaf
l_int|0x82000006
comma
singleline_comment|// offset of model name leaf
multiline_comment|/* vendor name leaf */
l_int|0x000486a3
comma
singleline_comment|// length of leaf, CRC
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x41444150
comma
singleline_comment|// ADAP
l_int|0x54454300
comma
singleline_comment|// TEC
multiline_comment|/* model name leaf */
l_int|0x0004f420
comma
singleline_comment|// length of leaf, CRC
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x4148412d
comma
singleline_comment|// AHA-
l_int|0x38393430
singleline_comment|// 8940
)brace
suffix:semicolon
macro_line|#endif
eof
