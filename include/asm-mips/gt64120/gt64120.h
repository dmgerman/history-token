multiline_comment|/*&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; * Carsten Langgaard, carstenl@mips.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; */
macro_line|#ifndef __ASM_GT64120_GT64120_H
DECL|macro|__ASM_GT64120_GT64120_H
mdefine_line|#define __ASM_GT64120_GT64120_H
DECL|macro|MSK
mdefine_line|#define MSK(n)                    ((1 &lt;&lt; (n)) - 1)
multiline_comment|/*&n; *  Register offset addresses&n; */
DECL|macro|GT_CPU_OFS
mdefine_line|#define GT_CPU_OFS&t;&t;0x000
multiline_comment|/*&n; * Interrupt Registers&n; */
DECL|macro|GT_SCS10LD_OFS
mdefine_line|#define GT_SCS10LD_OFS&t;&t;0x008
DECL|macro|GT_SCS10HD_OFS
mdefine_line|#define GT_SCS10HD_OFS&t;&t;0x010
DECL|macro|GT_SCS32LD_OFS
mdefine_line|#define GT_SCS32LD_OFS&t;&t;0x018
DECL|macro|GT_SCS32HD_OFS
mdefine_line|#define GT_SCS32HD_OFS&t;&t;0x020
DECL|macro|GT_CS20LD_OFS
mdefine_line|#define GT_CS20LD_OFS&t;&t;0x028
DECL|macro|GT_CS20HD_OFS
mdefine_line|#define GT_CS20HD_OFS&t;&t;0x030
DECL|macro|GT_CS3BOOTLD_OFS
mdefine_line|#define GT_CS3BOOTLD_OFS&t;0x038
DECL|macro|GT_CS3BOOTHD_OFS
mdefine_line|#define GT_CS3BOOTHD_OFS&t;0x040
DECL|macro|GT_PCI0IOLD_OFS
mdefine_line|#define GT_PCI0IOLD_OFS&t;&t;0x048
DECL|macro|GT_PCI0IOHD_OFS
mdefine_line|#define GT_PCI0IOHD_OFS&t;&t;0x050
DECL|macro|GT_PCI0M0LD_OFS
mdefine_line|#define GT_PCI0M0LD_OFS&t;&t;0x058
DECL|macro|GT_PCI0M0HD_OFS
mdefine_line|#define GT_PCI0M0HD_OFS&t;&t;0x060
DECL|macro|GT_ISD_OFS
mdefine_line|#define GT_ISD_OFS&t;&t;0x068
DECL|macro|GT_PCI0M1LD_OFS
mdefine_line|#define GT_PCI0M1LD_OFS&t;&t;0x080
DECL|macro|GT_PCI0M1HD_OFS
mdefine_line|#define GT_PCI0M1HD_OFS&t;&t;0x088
DECL|macro|GT_PCI1IOLD_OFS
mdefine_line|#define GT_PCI1IOLD_OFS&t;&t;0x090
DECL|macro|GT_PCI1IOHD_OFS
mdefine_line|#define GT_PCI1IOHD_OFS&t;&t;0x098
DECL|macro|GT_PCI1M0LD_OFS
mdefine_line|#define GT_PCI1M0LD_OFS&t;&t;0x0a0
DECL|macro|GT_PCI1M0HD_OFS
mdefine_line|#define GT_PCI1M0HD_OFS&t;&t;0x0a8
DECL|macro|GT_PCI1M1LD_OFS
mdefine_line|#define GT_PCI1M1LD_OFS&t;&t;0x0b0
DECL|macro|GT_PCI1M1HD_OFS
mdefine_line|#define GT_PCI1M1HD_OFS&t;&t;0x0b8
multiline_comment|/*&n; * GT64120A only&n; */
DECL|macro|GT_PCI0IOREMAP_OFS
mdefine_line|#define GT_PCI0IOREMAP_OFS&t;0x0f0
DECL|macro|GT_PCI0M0REMAP_OFS
mdefine_line|#define GT_PCI0M0REMAP_OFS&t;0x0f8
DECL|macro|GT_PCI0M1REMAP_OFS
mdefine_line|#define GT_PCI0M1REMAP_OFS&t;0x100
DECL|macro|GT_PCI1IOREMAP_OFS
mdefine_line|#define GT_PCI1IOREMAP_OFS&t;0x108
DECL|macro|GT_PCI1M0REMAP_OFS
mdefine_line|#define GT_PCI1M0REMAP_OFS&t;0x110
DECL|macro|GT_PCI1M1REMAP_OFS
mdefine_line|#define GT_PCI1M1REMAP_OFS&t;0x118
DECL|macro|GT_SCS0LD_OFS
mdefine_line|#define GT_SCS0LD_OFS&t;&t;0x400
DECL|macro|GT_SCS0HD_OFS
mdefine_line|#define GT_SCS0HD_OFS&t;&t;0x404
DECL|macro|GT_SCS1LD_OFS
mdefine_line|#define GT_SCS1LD_OFS&t;&t;0x408
DECL|macro|GT_SCS1HD_OFS
mdefine_line|#define GT_SCS1HD_OFS&t;&t;0x40c
DECL|macro|GT_SCS2LD_OFS
mdefine_line|#define GT_SCS2LD_OFS&t;&t;0x410
DECL|macro|GT_SCS2HD_OFS
mdefine_line|#define GT_SCS2HD_OFS&t;&t;0x414
DECL|macro|GT_SCS3LD_OFS
mdefine_line|#define GT_SCS3LD_OFS&t;&t;0x418
DECL|macro|GT_SCS3HD_OFS
mdefine_line|#define GT_SCS3HD_OFS&t;&t;0x41c
DECL|macro|GT_CS0LD_OFS
mdefine_line|#define GT_CS0LD_OFS&t;&t;0x420
DECL|macro|GT_CS0HD_OFS
mdefine_line|#define GT_CS0HD_OFS&t;&t;0x424
DECL|macro|GT_CS1LD_OFS
mdefine_line|#define GT_CS1LD_OFS&t;&t;0x428
DECL|macro|GT_CS1HD_OFS
mdefine_line|#define GT_CS1HD_OFS&t;&t;0x42c
DECL|macro|GT_CS2LD_OFS
mdefine_line|#define GT_CS2LD_OFS&t;&t;0x430
DECL|macro|GT_CS2HD_OFS
mdefine_line|#define GT_CS2HD_OFS&t;&t;0x434
DECL|macro|GT_CS3LD_OFS
mdefine_line|#define GT_CS3LD_OFS&t;&t;0x438
DECL|macro|GT_CS3HD_OFS
mdefine_line|#define GT_CS3HD_OFS&t;&t;0x43c
DECL|macro|GT_BOOTLD_OFS
mdefine_line|#define GT_BOOTLD_OFS&t;&t;0x440
DECL|macro|GT_BOOTHD_OFS
mdefine_line|#define GT_BOOTHD_OFS&t;&t;0x444
DECL|macro|GT_SDRAM_B0_OFS
mdefine_line|#define GT_SDRAM_B0_OFS&t;    &t;0x44c
DECL|macro|GT_SDRAM_CFG_OFS
mdefine_line|#define GT_SDRAM_CFG_OFS&t;0x448
DECL|macro|GT_SDRAM_B2_OFS
mdefine_line|#define GT_SDRAM_B2_OFS&t;&t;0x454
DECL|macro|GT_SDRAM_OPMODE_OFS
mdefine_line|#define GT_SDRAM_OPMODE_OFS&t;0x474
DECL|macro|GT_SDRAM_BM_OFS
mdefine_line|#define GT_SDRAM_BM_OFS&t;&t;0x478
DECL|macro|GT_SDRAM_ADDRDECODE_OFS
mdefine_line|#define GT_SDRAM_ADDRDECODE_OFS&t;0x47c
DECL|macro|GT_PCI0_CMD_OFS
mdefine_line|#define GT_PCI0_CMD_OFS&t;&t;0xc00&t;/* GT64120A only */
DECL|macro|GT_PCI0_TOR_OFS
mdefine_line|#define GT_PCI0_TOR_OFS&t;&t;0xc04
DECL|macro|GT_PCI0_BS_SCS10_OFS
mdefine_line|#define GT_PCI0_BS_SCS10_OFS    0xc08
DECL|macro|GT_PCI0_BS_SCS32_OFS
mdefine_line|#define GT_PCI0_BS_SCS32_OFS    0xc0c
DECL|macro|GT_INTRCAUSE_OFS
mdefine_line|#define GT_INTRCAUSE_OFS&t;0xc18
DECL|macro|GT_INTRMASK_OFS
mdefine_line|#define GT_INTRMASK_OFS&t;&t;0xc1c&t;/* GT64120A only */
DECL|macro|GT_PCI0_IACK_OFS
mdefine_line|#define GT_PCI0_IACK_OFS&t;0xc34
DECL|macro|GT_PCI0_BARE_OFS
mdefine_line|#define GT_PCI0_BARE_OFS&t;0xc3c
DECL|macro|GT_HINTRCAUSE_OFS
mdefine_line|#define GT_HINTRCAUSE_OFS&t;0xc98&t;/* GT64120A only */
DECL|macro|GT_HINTRMASK_OFS
mdefine_line|#define GT_HINTRMASK_OFS&t;0xc9c&t;/* GT64120A only */
DECL|macro|GT_PCI1_CFGADDR_OFS
mdefine_line|#define GT_PCI1_CFGADDR_OFS&t;0xcf0&t;/* GT64120A only */
DECL|macro|GT_PCI1_CFGDATA_OFS
mdefine_line|#define GT_PCI1_CFGDATA_OFS&t;0xcf4&t;/* GT64120A only */
DECL|macro|GT_PCI0_CFGADDR_OFS
mdefine_line|#define GT_PCI0_CFGADDR_OFS&t;0xcf8
DECL|macro|GT_PCI0_CFGDATA_OFS
mdefine_line|#define GT_PCI0_CFGDATA_OFS&t;0xcfc
multiline_comment|/*&n; * Timer/Counter.  GT64120A only.&n; */
DECL|macro|GT_TC0_OFS
mdefine_line|#define GT_TC0_OFS&t;&t;0x850
DECL|macro|GT_TC1_OFS
mdefine_line|#define GT_TC1_OFS&t;&t;0x854
DECL|macro|GT_TC2_OFS
mdefine_line|#define GT_TC2_OFS&t;&t;0x858
DECL|macro|GT_TC3_OFS
mdefine_line|#define GT_TC3_OFS&t;&t;0x85C
DECL|macro|GT_TC_CONTROL_OFS
mdefine_line|#define GT_TC_CONTROL_OFS&t;0x864
multiline_comment|/*&n; * I2O Support Registers&n; */
DECL|macro|INBOUND_MESSAGE_REGISTER0_PCI_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_PCI_SIDE&t;&t;0x010
DECL|macro|INBOUND_MESSAGE_REGISTER1_PCI_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_PCI_SIDE&t;&t;0x014
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_PCI_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_PCI_SIDE&t;&t;0x018
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_PCI_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_PCI_SIDE&t;&t;0x01c
DECL|macro|INBOUND_DOORBELL_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_PCI_SIDE&t;&t;0x020
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE&t;0x024
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE&t;0x028
DECL|macro|OUTBOUND_DOORBELL_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_PCI_SIDE&t;&t;0x02c
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE&t;0x030
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE&t;0x034
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE&t;0x040
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE&t;0x044
DECL|macro|QUEUE_CONTROL_REGISTER_PCI_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_PCI_SIDE&t;&t;&t;0x050
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_PCI_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_PCI_SIDE&t;&t;0x054
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x060
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x064
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x068
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x06c
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x070
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x074
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE&t;0x078
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE&t;0x07c
DECL|macro|INBOUND_MESSAGE_REGISTER0_CPU_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER0_CPU_SIDE&t;&t;0x1c10
DECL|macro|INBOUND_MESSAGE_REGISTER1_CPU_SIDE
mdefine_line|#define INBOUND_MESSAGE_REGISTER1_CPU_SIDE&t;&t;0x1c14
DECL|macro|OUTBOUND_MESSAGE_REGISTER0_CPU_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER0_CPU_SIDE&t;&t;0x1c18
DECL|macro|OUTBOUND_MESSAGE_REGISTER1_CPU_SIDE
mdefine_line|#define OUTBOUND_MESSAGE_REGISTER1_CPU_SIDE&t;&t;0x1c1c
DECL|macro|INBOUND_DOORBELL_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_DOORBELL_REGISTER_CPU_SIDE&t;&t;0x1c20
DECL|macro|INBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE&t;0x1c24
DECL|macro|INBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE&t;0x1c28
DECL|macro|OUTBOUND_DOORBELL_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_DOORBELL_REGISTER_CPU_SIDE&t;&t;0x1c2c
DECL|macro|OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE&t;0x1c30
DECL|macro|OUTBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE&t;0x1c34
DECL|macro|INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE&t;0x1c40
DECL|macro|OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE&t;0x1c44
DECL|macro|QUEUE_CONTROL_REGISTER_CPU_SIDE
mdefine_line|#define QUEUE_CONTROL_REGISTER_CPU_SIDE&t;&t;&t;0x1c50
DECL|macro|QUEUE_BASE_ADDRESS_REGISTER_CPU_SIDE
mdefine_line|#define QUEUE_BASE_ADDRESS_REGISTER_CPU_SIDE&t;&t;0x1c54
DECL|macro|INBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c60
DECL|macro|INBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c64
DECL|macro|INBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c68
DECL|macro|INBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define INBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c6c
DECL|macro|OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c70
DECL|macro|OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c74
DECL|macro|OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE&t;0x1c78
DECL|macro|OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE
mdefine_line|#define OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE&t;0x1c7c
multiline_comment|/*&n; *  Register encodings&n; */
DECL|macro|GT_CPU_ENDIAN_SHF
mdefine_line|#define GT_CPU_ENDIAN_SHF       12
DECL|macro|GT_CPU_ENDIAN_MSK
mdefine_line|#define GT_CPU_ENDIAN_MSK       (MSK(1) &lt;&lt; GT_CPU_ENDIAN_SHF)
DECL|macro|GT_CPU_ENDIAN_BIT
mdefine_line|#define GT_CPU_ENDIAN_BIT       GT_CPU_ENDIAN_MSK
DECL|macro|GT_CPU_WR_SHF
mdefine_line|#define GT_CPU_WR_SHF&t;&t;16
DECL|macro|GT_CPU_WR_MSK
mdefine_line|#define GT_CPU_WR_MSK&t;&t;(MSK(1) &lt;&lt; GT_CPU_WR_SHF)
DECL|macro|GT_CPU_WR_BIT
mdefine_line|#define GT_CPU_WR_BIT&t;&t;GT_CPU_WR_MSK
DECL|macro|GT_CPU_WR_DXDXDXDX
mdefine_line|#define GT_CPU_WR_DXDXDXDX&t;0
DECL|macro|GT_CPU_WR_DDDD
mdefine_line|#define GT_CPU_WR_DDDD&t;&t;1
DECL|macro|GT_CFGADDR_CFGEN_SHF
mdefine_line|#define GT_CFGADDR_CFGEN_SHF&t;31
DECL|macro|GT_CFGADDR_CFGEN_MSK
mdefine_line|#define GT_CFGADDR_CFGEN_MSK&t;(MSK(1) &lt;&lt; GT_CFGADDR_CFGEN_SHF)
DECL|macro|GT_CFGADDR_CFGEN_BIT
mdefine_line|#define GT_CFGADDR_CFGEN_BIT&t;GT_CFGADDR_CFGEN_MSK
DECL|macro|GT_CFGADDR_BUSNUM_SHF
mdefine_line|#define GT_CFGADDR_BUSNUM_SHF&t;16
DECL|macro|GT_CFGADDR_BUSNUM_MSK
mdefine_line|#define GT_CFGADDR_BUSNUM_MSK&t;(MSK(8) &lt;&lt; GT_CFGADDR_BUSNUM_SHF)
DECL|macro|GT_CFGADDR_DEVNUM_SHF
mdefine_line|#define GT_CFGADDR_DEVNUM_SHF&t;11
DECL|macro|GT_CFGADDR_DEVNUM_MSK
mdefine_line|#define GT_CFGADDR_DEVNUM_MSK&t;(MSK(5) &lt;&lt; GT_CFGADDR_DEVNUM_SHF)
DECL|macro|GT_CFGADDR_FUNCNUM_SHF
mdefine_line|#define GT_CFGADDR_FUNCNUM_SHF&t;8
DECL|macro|GT_CFGADDR_FUNCNUM_MSK
mdefine_line|#define GT_CFGADDR_FUNCNUM_MSK&t;(MSK(3) &lt;&lt; GT_CFGADDR_FUNCNUM_SHF)
DECL|macro|GT_CFGADDR_REGNUM_SHF
mdefine_line|#define GT_CFGADDR_REGNUM_SHF&t;2
DECL|macro|GT_CFGADDR_REGNUM_MSK
mdefine_line|#define GT_CFGADDR_REGNUM_MSK&t;(MSK(6) &lt;&lt; GT_CFGADDR_REGNUM_SHF)
DECL|macro|GT_SDRAM_BM_ORDER_SHF
mdefine_line|#define GT_SDRAM_BM_ORDER_SHF&t;2
DECL|macro|GT_SDRAM_BM_ORDER_MSK
mdefine_line|#define GT_SDRAM_BM_ORDER_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_BM_ORDER_SHF)
DECL|macro|GT_SDRAM_BM_ORDER_BIT
mdefine_line|#define GT_SDRAM_BM_ORDER_BIT&t;GT_SDRAM_BM_ORDER_MSK
DECL|macro|GT_SDRAM_BM_ORDER_SUB
mdefine_line|#define GT_SDRAM_BM_ORDER_SUB&t;1
DECL|macro|GT_SDRAM_BM_ORDER_LIN
mdefine_line|#define GT_SDRAM_BM_ORDER_LIN&t;0
DECL|macro|GT_SDRAM_BM_RSVD_ALL1
mdefine_line|#define GT_SDRAM_BM_RSVD_ALL1&t;0xffb
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_SHF
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_SHF&t;0
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_MSK
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_MSK&t;(MSK(3) &lt;&lt; GT_SDRAM_ADDRDECODE_ADDR_SHF)
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_0
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_0&t;0
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_1
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_1&t;1
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_2
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_2&t;2
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_3
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_3&t;3
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_4
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_4&t;4
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_5
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_5&t;5
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_6
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_6&t;6
DECL|macro|GT_SDRAM_ADDRDECODE_ADDR_7
mdefine_line|#define GT_SDRAM_ADDRDECODE_ADDR_7&t;7
DECL|macro|GT_SDRAM_B0_CASLAT_SHF
mdefine_line|#define GT_SDRAM_B0_CASLAT_SHF&t;&t;0
DECL|macro|GT_SDRAM_B0_CASLAT_MSK
mdefine_line|#define GT_SDRAM_B0_CASLAT_MSK&t;&t;(MSK(2) &lt;&lt; GT_SDRAM_B0__SHF)
DECL|macro|GT_SDRAM_B0_CASLAT_2
mdefine_line|#define GT_SDRAM_B0_CASLAT_2&t;&t;1
DECL|macro|GT_SDRAM_B0_CASLAT_3
mdefine_line|#define GT_SDRAM_B0_CASLAT_3&t;&t;2
DECL|macro|GT_SDRAM_B0_FTDIS_SHF
mdefine_line|#define GT_SDRAM_B0_FTDIS_SHF&t;&t;2
DECL|macro|GT_SDRAM_B0_FTDIS_MSK
mdefine_line|#define GT_SDRAM_B0_FTDIS_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_FTDIS_SHF)
DECL|macro|GT_SDRAM_B0_FTDIS_BIT
mdefine_line|#define GT_SDRAM_B0_FTDIS_BIT&t;&t;GT_SDRAM_B0_FTDIS_MSK
DECL|macro|GT_SDRAM_B0_SRASPRCHG_SHF
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_SHF&t;3
DECL|macro|GT_SDRAM_B0_SRASPRCHG_MSK
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_SRASPRCHG_SHF)
DECL|macro|GT_SDRAM_B0_SRASPRCHG_BIT
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_BIT&t;GT_SDRAM_B0_SRASPRCHG_MSK
DECL|macro|GT_SDRAM_B0_SRASPRCHG_2
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_2&t;&t;0
DECL|macro|GT_SDRAM_B0_SRASPRCHG_3
mdefine_line|#define GT_SDRAM_B0_SRASPRCHG_3&t;&t;1
DECL|macro|GT_SDRAM_B0_B0COMPAB_SHF
mdefine_line|#define GT_SDRAM_B0_B0COMPAB_SHF&t;4
DECL|macro|GT_SDRAM_B0_B0COMPAB_MSK
mdefine_line|#define GT_SDRAM_B0_B0COMPAB_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_B0COMPAB_SHF)
DECL|macro|GT_SDRAM_B0_B0COMPAB_BIT
mdefine_line|#define GT_SDRAM_B0_B0COMPAB_BIT&t;GT_SDRAM_B0_B0COMPAB_MSK
DECL|macro|GT_SDRAM_B0_64BITINT_SHF
mdefine_line|#define GT_SDRAM_B0_64BITINT_SHF&t;5
DECL|macro|GT_SDRAM_B0_64BITINT_MSK
mdefine_line|#define GT_SDRAM_B0_64BITINT_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_64BITINT_SHF)
DECL|macro|GT_SDRAM_B0_64BITINT_BIT
mdefine_line|#define GT_SDRAM_B0_64BITINT_BIT&t;GT_SDRAM_B0_64BITINT_MSK
DECL|macro|GT_SDRAM_B0_64BITINT_2
mdefine_line|#define GT_SDRAM_B0_64BITINT_2&t;&t;0
DECL|macro|GT_SDRAM_B0_64BITINT_4
mdefine_line|#define GT_SDRAM_B0_64BITINT_4&t;&t;1
DECL|macro|GT_SDRAM_B0_BW_SHF
mdefine_line|#define GT_SDRAM_B0_BW_SHF&t;&t;6
DECL|macro|GT_SDRAM_B0_BW_MSK
mdefine_line|#define GT_SDRAM_B0_BW_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BW_SHF)
DECL|macro|GT_SDRAM_B0_BW_BIT
mdefine_line|#define GT_SDRAM_B0_BW_BIT&t;&t;GT_SDRAM_B0_BW_MSK
DECL|macro|GT_SDRAM_B0_BW_32
mdefine_line|#define GT_SDRAM_B0_BW_32&t;&t;0
DECL|macro|GT_SDRAM_B0_BW_64
mdefine_line|#define GT_SDRAM_B0_BW_64&t;&t;1
DECL|macro|GT_SDRAM_B0_BLODD_SHF
mdefine_line|#define GT_SDRAM_B0_BLODD_SHF&t;&t;7
DECL|macro|GT_SDRAM_B0_BLODD_MSK
mdefine_line|#define GT_SDRAM_B0_BLODD_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BLODD_SHF)
DECL|macro|GT_SDRAM_B0_BLODD_BIT
mdefine_line|#define GT_SDRAM_B0_BLODD_BIT&t;&t;GT_SDRAM_B0_BLODD_MSK
DECL|macro|GT_SDRAM_B0_PAR_SHF
mdefine_line|#define GT_SDRAM_B0_PAR_SHF&t;&t;8
DECL|macro|GT_SDRAM_B0_PAR_MSK
mdefine_line|#define GT_SDRAM_B0_PAR_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_PAR_SHF)
DECL|macro|GT_SDRAM_B0_PAR_BIT
mdefine_line|#define GT_SDRAM_B0_PAR_BIT&t;&t;GT_SDRAM_B0_PAR_MSK
DECL|macro|GT_SDRAM_B0_BYPASS_SHF
mdefine_line|#define GT_SDRAM_B0_BYPASS_SHF&t;&t;9
DECL|macro|GT_SDRAM_B0_BYPASS_MSK
mdefine_line|#define GT_SDRAM_B0_BYPASS_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BYPASS_SHF)
DECL|macro|GT_SDRAM_B0_BYPASS_BIT
mdefine_line|#define GT_SDRAM_B0_BYPASS_BIT&t;&t;GT_SDRAM_B0_BYPASS_MSK
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_SHF
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_SHF&t;10
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_MSK
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_SRAS2SCAS_SHF)
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_BIT
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_BIT&t;GT_SDRAM_B0_SRAS2SCAS_MSK
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_2
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_2&t;&t;0
DECL|macro|GT_SDRAM_B0_SRAS2SCAS_3
mdefine_line|#define GT_SDRAM_B0_SRAS2SCAS_3&t;&t;1
DECL|macro|GT_SDRAM_B0_SIZE_SHF
mdefine_line|#define GT_SDRAM_B0_SIZE_SHF&t;&t;11
DECL|macro|GT_SDRAM_B0_SIZE_MSK
mdefine_line|#define GT_SDRAM_B0_SIZE_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_SIZE_SHF)
DECL|macro|GT_SDRAM_B0_SIZE_BIT
mdefine_line|#define GT_SDRAM_B0_SIZE_BIT&t;&t;GT_SDRAM_B0_SIZE_MSK
DECL|macro|GT_SDRAM_B0_SIZE_16M
mdefine_line|#define GT_SDRAM_B0_SIZE_16M&t;&t;0
DECL|macro|GT_SDRAM_B0_SIZE_64M
mdefine_line|#define GT_SDRAM_B0_SIZE_64M&t;&t;1
DECL|macro|GT_SDRAM_B0_EXTPAR_SHF
mdefine_line|#define GT_SDRAM_B0_EXTPAR_SHF&t;&t;12
DECL|macro|GT_SDRAM_B0_EXTPAR_MSK
mdefine_line|#define GT_SDRAM_B0_EXTPAR_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_EXTPAR_SHF)
DECL|macro|GT_SDRAM_B0_EXTPAR_BIT
mdefine_line|#define GT_SDRAM_B0_EXTPAR_BIT&t;&t;GT_SDRAM_B0_EXTPAR_MSK
DECL|macro|GT_SDRAM_B0_BLEN_SHF
mdefine_line|#define GT_SDRAM_B0_BLEN_SHF&t;&t;13
DECL|macro|GT_SDRAM_B0_BLEN_MSK
mdefine_line|#define GT_SDRAM_B0_BLEN_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_B0_BLEN_SHF)
DECL|macro|GT_SDRAM_B0_BLEN_BIT
mdefine_line|#define GT_SDRAM_B0_BLEN_BIT&t;&t;GT_SDRAM_B0_BLEN_MSK
DECL|macro|GT_SDRAM_B0_BLEN_8
mdefine_line|#define GT_SDRAM_B0_BLEN_8&t;&t;0
DECL|macro|GT_SDRAM_B0_BLEN_4
mdefine_line|#define GT_SDRAM_B0_BLEN_4&t;&t;1
DECL|macro|GT_SDRAM_CFG_REFINT_SHF
mdefine_line|#define GT_SDRAM_CFG_REFINT_SHF&t;&t;0
DECL|macro|GT_SDRAM_CFG_REFINT_MSK
mdefine_line|#define GT_SDRAM_CFG_REFINT_MSK&t;&t;(MSK(14) &lt;&lt; GT_SDRAM_CFG_REFINT_SHF)
DECL|macro|GT_SDRAM_CFG_NINTERLEAVE_SHF
mdefine_line|#define GT_SDRAM_CFG_NINTERLEAVE_SHF&t;14
DECL|macro|GT_SDRAM_CFG_NINTERLEAVE_MSK
mdefine_line|#define GT_SDRAM_CFG_NINTERLEAVE_MSK    (MSK(1) &lt;&lt; GT_SDRAM_CFG_NINTERLEAVE_SHF)
DECL|macro|GT_SDRAM_CFG_NINTERLEAVE_BIT
mdefine_line|#define GT_SDRAM_CFG_NINTERLEAVE_BIT&t;GT_SDRAM_CFG_NINTERLEAVE_MSK
DECL|macro|GT_SDRAM_CFG_RMW_SHF
mdefine_line|#define GT_SDRAM_CFG_RMW_SHF&t;&t;15
DECL|macro|GT_SDRAM_CFG_RMW_MSK
mdefine_line|#define GT_SDRAM_CFG_RMW_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_RMW_SHF)
DECL|macro|GT_SDRAM_CFG_RMW_BIT
mdefine_line|#define GT_SDRAM_CFG_RMW_BIT&t;&t;GT_SDRAM_CFG_RMW_MSK
DECL|macro|GT_SDRAM_CFG_NONSTAGREF_SHF
mdefine_line|#define GT_SDRAM_CFG_NONSTAGREF_SHF&t;16
DECL|macro|GT_SDRAM_CFG_NONSTAGREF_MSK
mdefine_line|#define GT_SDRAM_CFG_NONSTAGREF_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_NONSTAGREF_SHF)
DECL|macro|GT_SDRAM_CFG_NONSTAGREF_BIT
mdefine_line|#define GT_SDRAM_CFG_NONSTAGREF_BIT&t;GT_SDRAM_CFG_NONSTAGREF_MSK
DECL|macro|GT_SDRAM_CFG_DUPCNTL_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPCNTL_SHF&t;19
DECL|macro|GT_SDRAM_CFG_DUPCNTL_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPCNTL_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPCNTL_SHF)
DECL|macro|GT_SDRAM_CFG_DUPCNTL_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPCNTL_BIT&t;GT_SDRAM_CFG_DUPCNTL_MSK
DECL|macro|GT_SDRAM_CFG_DUPBA_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPBA_SHF&t;&t;20
DECL|macro|GT_SDRAM_CFG_DUPBA_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPBA_MSK&t;&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPBA_SHF)
DECL|macro|GT_SDRAM_CFG_DUPBA_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPBA_BIT&t;&t;GT_SDRAM_CFG_DUPBA_MSK
DECL|macro|GT_SDRAM_CFG_DUPEOT0_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPEOT0_SHF&t;21
DECL|macro|GT_SDRAM_CFG_DUPEOT0_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPEOT0_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPEOT0_SHF)
DECL|macro|GT_SDRAM_CFG_DUPEOT0_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPEOT0_BIT&t;GT_SDRAM_CFG_DUPEOT0_MSK
DECL|macro|GT_SDRAM_CFG_DUPEOT1_SHF
mdefine_line|#define GT_SDRAM_CFG_DUPEOT1_SHF&t;22
DECL|macro|GT_SDRAM_CFG_DUPEOT1_MSK
mdefine_line|#define GT_SDRAM_CFG_DUPEOT1_MSK&t;(MSK(1) &lt;&lt; GT_SDRAM_CFG_DUPEOT1_SHF)
DECL|macro|GT_SDRAM_CFG_DUPEOT1_BIT
mdefine_line|#define GT_SDRAM_CFG_DUPEOT1_BIT&t;GT_SDRAM_CFG_DUPEOT1_MSK
DECL|macro|GT_SDRAM_OPMODE_OP_SHF
mdefine_line|#define GT_SDRAM_OPMODE_OP_SHF&t;&t;0
DECL|macro|GT_SDRAM_OPMODE_OP_MSK
mdefine_line|#define GT_SDRAM_OPMODE_OP_MSK&t;&t;(MSK(3) &lt;&lt; GT_SDRAM_OPMODE_OP_SHF)
DECL|macro|GT_SDRAM_OPMODE_OP_NORMAL
mdefine_line|#define GT_SDRAM_OPMODE_OP_NORMAL&t;0
DECL|macro|GT_SDRAM_OPMODE_OP_NOP
mdefine_line|#define GT_SDRAM_OPMODE_OP_NOP&t;&t;1
DECL|macro|GT_SDRAM_OPMODE_OP_PRCHG
mdefine_line|#define GT_SDRAM_OPMODE_OP_PRCHG&t;2
DECL|macro|GT_SDRAM_OPMODE_OP_MODE
mdefine_line|#define GT_SDRAM_OPMODE_OP_MODE&t;&t;3
DECL|macro|GT_SDRAM_OPMODE_OP_CBR
mdefine_line|#define GT_SDRAM_OPMODE_OP_CBR&t;&t;4
DECL|macro|GT_PCI0_BARE_SWSCS3BOOTDIS_SHF
mdefine_line|#define GT_PCI0_BARE_SWSCS3BOOTDIS_SHF&t;0
DECL|macro|GT_PCI0_BARE_SWSCS3BOOTDIS_MSK
mdefine_line|#define GT_PCI0_BARE_SWSCS3BOOTDIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SWSCS3BOOTDIS_SHF)
DECL|macro|GT_PCI0_BARE_SWSCS3BOOTDIS_BIT
mdefine_line|#define GT_PCI0_BARE_SWSCS3BOOTDIS_BIT&t;GT_PCI0_BARE_SWSCS3BOOTDIS_MSK
DECL|macro|GT_PCI0_BARE_SWSCS32DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SWSCS32DIS_SHF&t;1
DECL|macro|GT_PCI0_BARE_SWSCS32DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SWSCS32DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SWSCS32DIS_SHF)
DECL|macro|GT_PCI0_BARE_SWSCS32DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SWSCS32DIS_BIT&t;GT_PCI0_BARE_SWSCS32DIS_MSK
DECL|macro|GT_PCI0_BARE_SWSCS10DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SWSCS10DIS_SHF&t;2
DECL|macro|GT_PCI0_BARE_SWSCS10DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SWSCS10DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SWSCS10DIS_SHF)
DECL|macro|GT_PCI0_BARE_SWSCS10DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SWSCS10DIS_BIT&t;GT_PCI0_BARE_SWSCS10DIS_MSK
DECL|macro|GT_PCI0_BARE_INTIODIS_SHF
mdefine_line|#define GT_PCI0_BARE_INTIODIS_SHF&t;3
DECL|macro|GT_PCI0_BARE_INTIODIS_MSK
mdefine_line|#define GT_PCI0_BARE_INTIODIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_INTIODIS_SHF)
DECL|macro|GT_PCI0_BARE_INTIODIS_BIT
mdefine_line|#define GT_PCI0_BARE_INTIODIS_BIT&t;GT_PCI0_BARE_INTIODIS_MSK
DECL|macro|GT_PCI0_BARE_INTMEMDIS_SHF
mdefine_line|#define GT_PCI0_BARE_INTMEMDIS_SHF&t;4
DECL|macro|GT_PCI0_BARE_INTMEMDIS_MSK
mdefine_line|#define GT_PCI0_BARE_INTMEMDIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_INTMEMDIS_SHF)
DECL|macro|GT_PCI0_BARE_INTMEMDIS_BIT
mdefine_line|#define GT_PCI0_BARE_INTMEMDIS_BIT&t;GT_PCI0_BARE_INTMEMDIS_MSK
DECL|macro|GT_PCI0_BARE_CS3BOOTDIS_SHF
mdefine_line|#define GT_PCI0_BARE_CS3BOOTDIS_SHF&t;5
DECL|macro|GT_PCI0_BARE_CS3BOOTDIS_MSK
mdefine_line|#define GT_PCI0_BARE_CS3BOOTDIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_CS3BOOTDIS_SHF)
DECL|macro|GT_PCI0_BARE_CS3BOOTDIS_BIT
mdefine_line|#define GT_PCI0_BARE_CS3BOOTDIS_BIT&t;GT_PCI0_BARE_CS3BOOTDIS_MSK
DECL|macro|GT_PCI0_BARE_CS20DIS_SHF
mdefine_line|#define GT_PCI0_BARE_CS20DIS_SHF&t;6
DECL|macro|GT_PCI0_BARE_CS20DIS_MSK
mdefine_line|#define GT_PCI0_BARE_CS20DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_CS20DIS_SHF)
DECL|macro|GT_PCI0_BARE_CS20DIS_BIT
mdefine_line|#define GT_PCI0_BARE_CS20DIS_BIT&t;GT_PCI0_BARE_CS20DIS_MSK
DECL|macro|GT_PCI0_BARE_SCS32DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SCS32DIS_SHF&t;7
DECL|macro|GT_PCI0_BARE_SCS32DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SCS32DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SCS32DIS_SHF)
DECL|macro|GT_PCI0_BARE_SCS32DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SCS32DIS_BIT&t;GT_PCI0_BARE_SCS32DIS_MSK
DECL|macro|GT_PCI0_BARE_SCS10DIS_SHF
mdefine_line|#define GT_PCI0_BARE_SCS10DIS_SHF&t;8
DECL|macro|GT_PCI0_BARE_SCS10DIS_MSK
mdefine_line|#define GT_PCI0_BARE_SCS10DIS_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_BARE_SCS10DIS_SHF)
DECL|macro|GT_PCI0_BARE_SCS10DIS_BIT
mdefine_line|#define GT_PCI0_BARE_SCS10DIS_BIT&t;GT_PCI0_BARE_SCS10DIS_MSK
DECL|macro|GT_INTRCAUSE_MASABORT0_SHF
mdefine_line|#define GT_INTRCAUSE_MASABORT0_SHF&t;18
DECL|macro|GT_INTRCAUSE_MASABORT0_MSK
mdefine_line|#define GT_INTRCAUSE_MASABORT0_MSK&t;(MSK(1) &lt;&lt; GT_INTRCAUSE_MASABORT0_SHF)
DECL|macro|GT_INTRCAUSE_MASABORT0_BIT
mdefine_line|#define GT_INTRCAUSE_MASABORT0_BIT&t;GT_INTRCAUSE_MASABORT0_MSK
DECL|macro|GT_INTRCAUSE_TARABORT0_SHF
mdefine_line|#define GT_INTRCAUSE_TARABORT0_SHF&t;19
DECL|macro|GT_INTRCAUSE_TARABORT0_MSK
mdefine_line|#define GT_INTRCAUSE_TARABORT0_MSK&t;(MSK(1) &lt;&lt; GT_INTRCAUSE_TARABORT0_SHF)
DECL|macro|GT_INTRCAUSE_TARABORT0_BIT
mdefine_line|#define GT_INTRCAUSE_TARABORT0_BIT&t;GT_INTRCAUSE_TARABORT0_MSK
DECL|macro|GT_PCI0_CFGADDR_REGNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_REGNUM_SHF&t;2
DECL|macro|GT_PCI0_CFGADDR_REGNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_REGNUM_MSK&t;(MSK(6) &lt;&lt; GT_PCI0_CFGADDR_REGNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_FUNCTNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_FUNCTNUM_SHF&t;8
DECL|macro|GT_PCI0_CFGADDR_FUNCTNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_FUNCTNUM_MSK    (MSK(3) &lt;&lt; GT_PCI0_CFGADDR_FUNCTNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_DEVNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_DEVNUM_SHF&t;11
DECL|macro|GT_PCI0_CFGADDR_DEVNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_DEVNUM_MSK&t;(MSK(5) &lt;&lt; GT_PCI0_CFGADDR_DEVNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_BUSNUM_SHF
mdefine_line|#define GT_PCI0_CFGADDR_BUSNUM_SHF&t;16
DECL|macro|GT_PCI0_CFGADDR_BUSNUM_MSK
mdefine_line|#define GT_PCI0_CFGADDR_BUSNUM_MSK&t;(MSK(8) &lt;&lt; GT_PCI0_CFGADDR_BUSNUM_SHF)
DECL|macro|GT_PCI0_CFGADDR_CONFIGEN_SHF
mdefine_line|#define GT_PCI0_CFGADDR_CONFIGEN_SHF&t;31
DECL|macro|GT_PCI0_CFGADDR_CONFIGEN_MSK
mdefine_line|#define GT_PCI0_CFGADDR_CONFIGEN_MSK&t;(MSK(1) &lt;&lt; GT_PCI0_CFGADDR_CONFIGEN_SHF)
DECL|macro|GT_PCI0_CFGADDR_CONFIGEN_BIT
mdefine_line|#define GT_PCI0_CFGADDR_CONFIGEN_BIT&t;GT_PCI0_CFGADDR_CONFIGEN_MSK
DECL|macro|GT_PCI0_CMD_MBYTESWAP_SHF
mdefine_line|#define GT_PCI0_CMD_MBYTESWAP_SHF       0
DECL|macro|GT_PCI0_CMD_MBYTESWAP_MSK
mdefine_line|#define GT_PCI0_CMD_MBYTESWAP_MSK       (MSK(1) &lt;&lt; GT_PCI0_CMD_MBYTESWAP_SHF)
DECL|macro|GT_PCI0_CMD_MBYTESWAP_BIT
mdefine_line|#define GT_PCI0_CMD_MBYTESWAP_BIT       GT_PCI0_CMD_MBYTESWAP_MSK
DECL|macro|GT_PCI0_CMD_MWORDSWAP_SHF
mdefine_line|#define GT_PCI0_CMD_MWORDSWAP_SHF       10
DECL|macro|GT_PCI0_CMD_MWORDSWAP_MSK
mdefine_line|#define GT_PCI0_CMD_MWORDSWAP_MSK       (MSK(1) &lt;&lt; GT_PCI0_CMD_MWORDSWAP_SHF)
DECL|macro|GT_PCI0_CMD_MWORDSWAP_BIT
mdefine_line|#define GT_PCI0_CMD_MWORDSWAP_BIT       GT_PCI0_CMD_MWORDSWAP_MSK
DECL|macro|GT_PCI0_CMD_SBYTESWAP_SHF
mdefine_line|#define GT_PCI0_CMD_SBYTESWAP_SHF       16
DECL|macro|GT_PCI0_CMD_SBYTESWAP_MSK
mdefine_line|#define GT_PCI0_CMD_SBYTESWAP_MSK       (MSK(1) &lt;&lt; GT_PCI0_CMD_SBYTESWAP_SHF)
DECL|macro|GT_PCI0_CMD_SBYTESWAP_BIT
mdefine_line|#define GT_PCI0_CMD_SBYTESWAP_BIT       GT_PCI0_CMD_SBYTESWAP_MSK
DECL|macro|GT_PCI0_CMD_SWORDSWAP_SHF
mdefine_line|#define GT_PCI0_CMD_SWORDSWAP_SHF       11
DECL|macro|GT_PCI0_CMD_SWORDSWAP_MSK
mdefine_line|#define GT_PCI0_CMD_SWORDSWAP_MSK       (MSK(1) &lt;&lt; GT_PCI0_CMD_SWORDSWAP_SHF)
DECL|macro|GT_PCI0_CMD_SWORDSWAP_BIT
mdefine_line|#define GT_PCI0_CMD_SWORDSWAP_BIT       GT_PCI0_CMD_SWORDSWAP_MSK
multiline_comment|/*&n; *  Misc&n; */
DECL|macro|GT_DEF_BASE
mdefine_line|#define GT_DEF_BASE&t;&t;0x14000000
DECL|macro|GT_DEF_PCI0_IO_BASE
mdefine_line|#define GT_DEF_PCI0_IO_BASE&t;0x10000000
DECL|macro|GT_DEF_PCI0_IO_SIZE
mdefine_line|#define GT_DEF_PCI0_IO_SIZE&t;0x02000000
DECL|macro|GT_DEF_PCI0_MEM0_BASE
mdefine_line|#define GT_DEF_PCI0_MEM0_BASE&t;0x12000000
DECL|macro|GT_DEF_PCI0_MEM0_SIZE
mdefine_line|#define GT_DEF_PCI0_MEM0_SIZE&t;0x02000000
DECL|macro|GT_MAX_BANKSIZE
mdefine_line|#define GT_MAX_BANKSIZE&t;&t;(256 * 1024 * 1024)   /* Max 256MB bank */
DECL|macro|GT_LATTIM_MIN
mdefine_line|#define GT_LATTIM_MIN    &t;6&t;&t;      /* Minimum lat&t;*/
multiline_comment|/***********************************************************************&n; *              BOARD-DEPENDENT SECTIONS                               *&n; ***********************************************************************&n; */
multiline_comment|/*&n; * include asm/gt64120/&lt;board&gt;/gt64120_dep.h file&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#if defined(CONFIG_MOMENCO_OCELOT)
macro_line|#include &lt;asm/gt64120/momenco_ocelot/gt64120_dep.h&gt;
macro_line|#endif
multiline_comment|/*&n; * The gt64120_dep.h file must define the following macros&n; *&n; *   GT_READ(ofs, data_pointer)&n; *   GT_WRITE(ofs, data)           - read/write GT64120 registers in 32bit&n; *&n; *   TIMER &t;- gt64120 timer irq, temporary solution until&n; *&t;&t;  full gt64120 cascade interrupt support is in place&n; */
multiline_comment|/*&n; * Board-dependent functions, which must be defined in&n; * arch/mips/gt64120/&lt;board&gt;/pci.c file.&n; *&n; * This function is called by pcibios_fixup_bus(bus), which in turn is&n; * invoked a bus is scanned.  You typically fixes IRQ numbers in this routine.&n; */
r_extern
r_void
id|__init
id|gt64120_board_pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
macro_line|#endif /* __ASM_GT64120_GT64120_H */
eof
