multiline_comment|/*&n; * include/asm-ppc/gt64260_defs.h&n; *&n; * Register definitions for the Marvell/Galileo GT64260, MV64360, etc.&n; * host bridges.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_MV64x60_DEFS_H
DECL|macro|__ASMPPC_MV64x60_DEFS_H
mdefine_line|#define __ASMPPC_MV64x60_DEFS_H
multiline_comment|/*&n; * Define the Marvell bridges that are supported&n; */
DECL|macro|MV64x60_TYPE_INVALID
mdefine_line|#define&t;MV64x60_TYPE_INVALID&t;&t;&t;0
DECL|macro|MV64x60_TYPE_GT64260A
mdefine_line|#define&t;MV64x60_TYPE_GT64260A&t;&t;&t;1
DECL|macro|MV64x60_TYPE_GT64260B
mdefine_line|#define&t;MV64x60_TYPE_GT64260B&t;&t;&t;2
DECL|macro|MV64x60_TYPE_MV64360
mdefine_line|#define&t;MV64x60_TYPE_MV64360&t;&t;&t;3
DECL|macro|MV64x60_TYPE_MV64361
mdefine_line|#define&t;MV64x60_TYPE_MV64361&t;&t;&t;4
DECL|macro|MV64x60_TYPE_MV64362
mdefine_line|#define&t;MV64x60_TYPE_MV64362&t;&t;&t;5
DECL|macro|MV64x60_TYPE_MV64460
mdefine_line|#define&t;MV64x60_TYPE_MV64460&t;&t;&t;6
multiline_comment|/* Revisions of each supported chip */
DECL|macro|GT64260_REV_A
mdefine_line|#define&t;GT64260_REV_A&t;&t;&t;&t;0x10
DECL|macro|GT64260_REV_B
mdefine_line|#define&t;GT64260_REV_B&t;&t;&t;&t;0x20
DECL|macro|MV64360
mdefine_line|#define&t;MV64360&t;&t;&t;&t;&t;0x01
DECL|macro|MV64460
mdefine_line|#define&t;MV64460&t;&t;&t;&t;&t;0x01
multiline_comment|/* Minimum window size supported by 64260 is 1MB */
DECL|macro|GT64260_WINDOW_SIZE_MIN
mdefine_line|#define GT64260_WINDOW_SIZE_MIN&t;&t;&t;0x00100000
DECL|macro|MV64360_WINDOW_SIZE_MIN
mdefine_line|#define MV64360_WINDOW_SIZE_MIN&t;&t;&t;0x00010000
multiline_comment|/* IRQ&squot;s for embedded controllers */
DECL|macro|MV64x60_IRQ_DEV
mdefine_line|#define&t;MV64x60_IRQ_DEV&t;&t;&t;&t;1
DECL|macro|MV64x60_IRQ_CPU_ERR
mdefine_line|#define&t;MV64x60_IRQ_CPU_ERR&t;&t;&t;3
DECL|macro|MV64x60_IRQ_TIMER_0_1
mdefine_line|#define&t;MV64x60_IRQ_TIMER_0_1&t;&t;&t;8
DECL|macro|MV64x60_IRQ_TIMER_2_3
mdefine_line|#define&t;MV64x60_IRQ_TIMER_2_3&t;&t;&t;9
DECL|macro|MV64x60_IRQ_TIMER_4_5
mdefine_line|#define&t;MV64x60_IRQ_TIMER_4_5&t;&t;&t;10
DECL|macro|MV64x60_IRQ_TIMER_6_7
mdefine_line|#define&t;MV64x60_IRQ_TIMER_6_7&t;&t;&t;11
DECL|macro|MV64x60_IRQ_ETH_0
mdefine_line|#define&t;MV64x60_IRQ_ETH_0&t;&t;&t;32
DECL|macro|MV64x60_IRQ_ETH_1
mdefine_line|#define&t;MV64x60_IRQ_ETH_1&t;&t;&t;33
DECL|macro|MV64x60_IRQ_ETH_2
mdefine_line|#define&t;MV64x60_IRQ_ETH_2&t;&t;&t;34
DECL|macro|MV64x60_IRQ_SDMA_0
mdefine_line|#define&t;MV64x60_IRQ_SDMA_0&t;&t;&t;36
DECL|macro|MV64x60_IRQ_I2C
mdefine_line|#define&t;MV64x60_IRQ_I2C&t;&t;&t;&t;37
DECL|macro|MV64x60_IRQ_BRG
mdefine_line|#define&t;MV64x60_IRQ_BRG&t;&t;&t;&t;39
DECL|macro|MV64x60_IRQ_MPSC_0
mdefine_line|#define&t;MV64x60_IRQ_MPSC_0&t;&t;&t;40
DECL|macro|MV64x60_IRQ_MPSC_1
mdefine_line|#define&t;MV64x60_IRQ_MPSC_1&t;&t;&t;42
DECL|macro|MV64x60_IRQ_COMM
mdefine_line|#define&t;MV64x60_IRQ_COMM&t;&t;&t;43
DECL|macro|MV64360_IRQ_PCI0
mdefine_line|#define&t;MV64360_IRQ_PCI0&t;&t;&t;12
DECL|macro|MV64360_IRQ_SRAM_PAR_ERR
mdefine_line|#define&t;MV64360_IRQ_SRAM_PAR_ERR&t;&t;13
DECL|macro|MV64360_IRQ_PCI1
mdefine_line|#define&t;MV64360_IRQ_PCI1&t;&t;&t;16
DECL|macro|MV64360_IRQ_SDMA_1
mdefine_line|#define&t;MV64360_IRQ_SDMA_1&t;&t;&t;38
multiline_comment|/* Offsets for register blocks */
DECL|macro|GT64260_ENET_PHY_ADDR
mdefine_line|#define&t;GT64260_ENET_PHY_ADDR&t;&t;&t;0x2000
DECL|macro|GT64260_ENET_ESMIR
mdefine_line|#define&t;GT64260_ENET_ESMIR&t;&t;&t;0x2010
DECL|macro|GT64260_ENET_0_OFFSET
mdefine_line|#define GT64260_ENET_0_OFFSET&t;&t;&t;0x2400
DECL|macro|GT64260_ENET_1_OFFSET
mdefine_line|#define GT64260_ENET_1_OFFSET&t;&t;&t;0x2800
DECL|macro|GT64260_ENET_2_OFFSET
mdefine_line|#define GT64260_ENET_2_OFFSET&t;&t;&t;0x2c00
DECL|macro|MV64x60_SDMA_0_OFFSET
mdefine_line|#define&t;MV64x60_SDMA_0_OFFSET&t;&t;&t;0x4000
DECL|macro|MV64x60_SDMA_1_OFFSET
mdefine_line|#define&t;MV64x60_SDMA_1_OFFSET&t;&t;&t;0x6000
DECL|macro|MV64x60_MPSC_0_OFFSET
mdefine_line|#define&t;MV64x60_MPSC_0_OFFSET&t;&t;&t;0x8000
DECL|macro|MV64x60_MPSC_1_OFFSET
mdefine_line|#define&t;MV64x60_MPSC_1_OFFSET&t;&t;&t;0x9000
DECL|macro|MV64x60_MPSC_ROUTING_OFFSET
mdefine_line|#define&t;MV64x60_MPSC_ROUTING_OFFSET&t;&t;0xb400
DECL|macro|MV64x60_SDMA_INTR_OFFSET
mdefine_line|#define&t;MV64x60_SDMA_INTR_OFFSET&t;&t;0xb800
DECL|macro|MV64x60_BRG_0_OFFSET
mdefine_line|#define&t;MV64x60_BRG_0_OFFSET&t;&t;&t;0xb200
DECL|macro|MV64x60_BRG_1_OFFSET
mdefine_line|#define&t;MV64x60_BRG_1_OFFSET&t;&t;&t;0xb208
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;CPU Interface Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* CPU physical address of bridge&squot;s registers */
DECL|macro|MV64x60_INTERNAL_SPACE_DECODE
mdefine_line|#define MV64x60_INTERNAL_SPACE_DECODE&t;&t;0x0068
DECL|macro|MV64x60_INTERNAL_SPACE_SIZE
mdefine_line|#define MV64x60_INTERNAL_SPACE_SIZE&t;&t;0x10000
DECL|macro|MV64x60_INTERNAL_SPACE_DEFAULT_ADDR
mdefine_line|#define MV64x60_INTERNAL_SPACE_DEFAULT_ADDR&t;0x14000000
DECL|macro|MV64360_CPU_BAR_ENABLE
mdefine_line|#define&t;MV64360_CPU_BAR_ENABLE&t;&t;&t;0x0278
multiline_comment|/* CPU Memory Controller Window Registers (4 windows) */
DECL|macro|MV64x60_CPU2MEM_WINDOWS
mdefine_line|#define&t;MV64x60_CPU2MEM_WINDOWS&t;&t;&t;4
DECL|macro|MV64x60_CPU2MEM_0_BASE
mdefine_line|#define&t;MV64x60_CPU2MEM_0_BASE&t;&t;&t;0x0008
DECL|macro|MV64x60_CPU2MEM_0_SIZE
mdefine_line|#define&t;MV64x60_CPU2MEM_0_SIZE&t;&t;&t;0x0010
DECL|macro|MV64x60_CPU2MEM_1_BASE
mdefine_line|#define&t;MV64x60_CPU2MEM_1_BASE&t;&t;&t;0x0208
DECL|macro|MV64x60_CPU2MEM_1_SIZE
mdefine_line|#define&t;MV64x60_CPU2MEM_1_SIZE&t;&t;&t;0x0210
DECL|macro|MV64x60_CPU2MEM_2_BASE
mdefine_line|#define&t;MV64x60_CPU2MEM_2_BASE&t;&t;&t;0x0018
DECL|macro|MV64x60_CPU2MEM_2_SIZE
mdefine_line|#define&t;MV64x60_CPU2MEM_2_SIZE&t;&t;&t;0x0020
DECL|macro|MV64x60_CPU2MEM_3_BASE
mdefine_line|#define&t;MV64x60_CPU2MEM_3_BASE&t;&t;&t;0x0218
DECL|macro|MV64x60_CPU2MEM_3_SIZE
mdefine_line|#define&t;MV64x60_CPU2MEM_3_SIZE&t;&t;&t;0x0220
multiline_comment|/* CPU Device Controller Window Registers (4 windows) */
DECL|macro|MV64x60_CPU2DEV_WINDOWS
mdefine_line|#define&t;MV64x60_CPU2DEV_WINDOWS&t;&t;&t;4
DECL|macro|MV64x60_CPU2DEV_0_BASE
mdefine_line|#define&t;MV64x60_CPU2DEV_0_BASE&t;&t;&t;0x0028
DECL|macro|MV64x60_CPU2DEV_0_SIZE
mdefine_line|#define&t;MV64x60_CPU2DEV_0_SIZE&t;&t;&t;0x0030
DECL|macro|MV64x60_CPU2DEV_1_BASE
mdefine_line|#define&t;MV64x60_CPU2DEV_1_BASE&t;&t;&t;0x0228
DECL|macro|MV64x60_CPU2DEV_1_SIZE
mdefine_line|#define&t;MV64x60_CPU2DEV_1_SIZE&t;&t;&t;0x0230
DECL|macro|MV64x60_CPU2DEV_2_BASE
mdefine_line|#define&t;MV64x60_CPU2DEV_2_BASE&t;&t;&t;0x0248
DECL|macro|MV64x60_CPU2DEV_2_SIZE
mdefine_line|#define&t;MV64x60_CPU2DEV_2_SIZE&t;&t;&t;0x0250
DECL|macro|MV64x60_CPU2DEV_3_BASE
mdefine_line|#define&t;MV64x60_CPU2DEV_3_BASE&t;&t;&t;0x0038
DECL|macro|MV64x60_CPU2DEV_3_SIZE
mdefine_line|#define&t;MV64x60_CPU2DEV_3_SIZE&t;&t;&t;0x0040
DECL|macro|MV64x60_CPU2BOOT_0_BASE
mdefine_line|#define&t;MV64x60_CPU2BOOT_0_BASE&t;&t;&t;0x0238
DECL|macro|MV64x60_CPU2BOOT_0_SIZE
mdefine_line|#define&t;MV64x60_CPU2BOOT_0_SIZE&t;&t;&t;0x0240
DECL|macro|MV64360_CPU2SRAM_BASE
mdefine_line|#define&t;MV64360_CPU2SRAM_BASE&t;&t;&t;0x0268
multiline_comment|/* CPU Windows to PCI space (2 PCI buses each w/ 1 I/O &amp; 4 MEM windows) */
DECL|macro|MV64x60_PCI_BUSES
mdefine_line|#define&t;MV64x60_PCI_BUSES&t;&t;&t;2
DECL|macro|MV64x60_PCI_IO_WINDOWS_PER_BUS
mdefine_line|#define&t;MV64x60_PCI_IO_WINDOWS_PER_BUS&t;&t;1
DECL|macro|MV64x60_PCI_MEM_WINDOWS_PER_BUS
mdefine_line|#define&t;MV64x60_PCI_MEM_WINDOWS_PER_BUS&t;&t;4
DECL|macro|MV64x60_CPU2PCI_SWAP_BYTE
mdefine_line|#define&t;MV64x60_CPU2PCI_SWAP_BYTE&t;&t;0x00000000
DECL|macro|MV64x60_CPU2PCI_SWAP_NONE
mdefine_line|#define&t;MV64x60_CPU2PCI_SWAP_NONE&t;&t;0x01000000
DECL|macro|MV64x60_CPU2PCI_SWAP_BYTE_WORD
mdefine_line|#define&t;MV64x60_CPU2PCI_SWAP_BYTE_WORD&t;&t;0x02000000
DECL|macro|MV64x60_CPU2PCI_SWAP_WORD
mdefine_line|#define&t;MV64x60_CPU2PCI_SWAP_WORD&t;&t;0x03000000
DECL|macro|MV64x60_CPU2PCI_MEM_REQ64
mdefine_line|#define&t;MV64x60_CPU2PCI_MEM_REQ64&t;&t;(1&lt;&lt;27)
DECL|macro|MV64x60_CPU2PCI0_IO_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI0_IO_BASE&t;&t;0x0048
DECL|macro|MV64x60_CPU2PCI0_IO_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI0_IO_SIZE&t;&t;0x0050
DECL|macro|MV64x60_CPU2PCI0_MEM_0_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_0_BASE&t;&t;0x0058
DECL|macro|MV64x60_CPU2PCI0_MEM_0_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_0_SIZE&t;&t;0x0060
DECL|macro|MV64x60_CPU2PCI0_MEM_1_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_1_BASE&t;&t;0x0080
DECL|macro|MV64x60_CPU2PCI0_MEM_1_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_1_SIZE&t;&t;0x0088
DECL|macro|MV64x60_CPU2PCI0_MEM_2_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_2_BASE&t;&t;0x0258
DECL|macro|MV64x60_CPU2PCI0_MEM_2_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_2_SIZE&t;&t;0x0260
DECL|macro|MV64x60_CPU2PCI0_MEM_3_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_3_BASE&t;&t;0x0280
DECL|macro|MV64x60_CPU2PCI0_MEM_3_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_3_SIZE&t;&t;0x0288
DECL|macro|MV64x60_CPU2PCI0_IO_REMAP
mdefine_line|#define&t;MV64x60_CPU2PCI0_IO_REMAP&t;&t;0x00f0
DECL|macro|MV64x60_CPU2PCI0_MEM_0_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_0_REMAP_LO&t;&t;0x00f8
DECL|macro|MV64x60_CPU2PCI0_MEM_0_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_0_REMAP_HI&t;&t;0x0320
DECL|macro|MV64x60_CPU2PCI0_MEM_1_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_1_REMAP_LO&t;&t;0x0100
DECL|macro|MV64x60_CPU2PCI0_MEM_1_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_1_REMAP_HI&t;&t;0x0328
DECL|macro|MV64x60_CPU2PCI0_MEM_2_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_2_REMAP_LO&t;&t;0x02f8
DECL|macro|MV64x60_CPU2PCI0_MEM_2_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_2_REMAP_HI&t;&t;0x0330
DECL|macro|MV64x60_CPU2PCI0_MEM_3_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_3_REMAP_LO&t;&t;0x0300
DECL|macro|MV64x60_CPU2PCI0_MEM_3_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI0_MEM_3_REMAP_HI&t;&t;0x0338
DECL|macro|MV64x60_CPU2PCI1_IO_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI1_IO_BASE&t;&t;0x0090
DECL|macro|MV64x60_CPU2PCI1_IO_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI1_IO_SIZE&t;&t;0x0098
DECL|macro|MV64x60_CPU2PCI1_MEM_0_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_0_BASE&t;&t;0x00a0
DECL|macro|MV64x60_CPU2PCI1_MEM_0_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_0_SIZE&t;&t;0x00a8
DECL|macro|MV64x60_CPU2PCI1_MEM_1_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_1_BASE&t;&t;0x00b0
DECL|macro|MV64x60_CPU2PCI1_MEM_1_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_1_SIZE&t;&t;0x00b8
DECL|macro|MV64x60_CPU2PCI1_MEM_2_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_2_BASE&t;&t;0x02a0
DECL|macro|MV64x60_CPU2PCI1_MEM_2_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_2_SIZE&t;&t;0x02a8
DECL|macro|MV64x60_CPU2PCI1_MEM_3_BASE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_3_BASE&t;&t;0x02b0
DECL|macro|MV64x60_CPU2PCI1_MEM_3_SIZE
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_3_SIZE&t;&t;0x02b8
DECL|macro|MV64x60_CPU2PCI1_IO_REMAP
mdefine_line|#define&t;MV64x60_CPU2PCI1_IO_REMAP&t;&t;0x0108
DECL|macro|MV64x60_CPU2PCI1_MEM_0_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_0_REMAP_LO&t;&t;0x0110
DECL|macro|MV64x60_CPU2PCI1_MEM_0_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_0_REMAP_HI&t;&t;0x0340
DECL|macro|MV64x60_CPU2PCI1_MEM_1_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_1_REMAP_LO&t;&t;0x0118
DECL|macro|MV64x60_CPU2PCI1_MEM_1_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_1_REMAP_HI&t;&t;0x0348
DECL|macro|MV64x60_CPU2PCI1_MEM_2_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_2_REMAP_LO&t;&t;0x0310
DECL|macro|MV64x60_CPU2PCI1_MEM_2_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_2_REMAP_HI&t;&t;0x0350
DECL|macro|MV64x60_CPU2PCI1_MEM_3_REMAP_LO
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_3_REMAP_LO&t;&t;0x0318
DECL|macro|MV64x60_CPU2PCI1_MEM_3_REMAP_HI
mdefine_line|#define&t;MV64x60_CPU2PCI1_MEM_3_REMAP_HI&t;&t;0x0358
multiline_comment|/* CPU Control Registers */
DECL|macro|MV64x60_CPU_CONFIG
mdefine_line|#define MV64x60_CPU_CONFIG&t;&t;&t;0x0000
DECL|macro|MV64x60_CPU_MODE
mdefine_line|#define MV64x60_CPU_MODE&t;&t;&t;0x0120
DECL|macro|MV64x60_CPU_MASTER_CNTL
mdefine_line|#define MV64x60_CPU_MASTER_CNTL&t;&t;&t;0x0160
DECL|macro|MV64x60_CPU_XBAR_CNTL_LO
mdefine_line|#define MV64x60_CPU_XBAR_CNTL_LO&t;&t;0x0150
DECL|macro|MV64x60_CPU_XBAR_CNTL_HI
mdefine_line|#define MV64x60_CPU_XBAR_CNTL_HI&t;&t;0x0158
DECL|macro|MV64x60_CPU_XBAR_TO
mdefine_line|#define MV64x60_CPU_XBAR_TO&t;&t;&t;0x0168
DECL|macro|GT64260_CPU_RR_XBAR_CNTL_LO
mdefine_line|#define GT64260_CPU_RR_XBAR_CNTL_LO&t;&t;0x0170
DECL|macro|GT64260_CPU_RR_XBAR_CNTL_HI
mdefine_line|#define GT64260_CPU_RR_XBAR_CNTL_HI&t;&t;0x0178
DECL|macro|MV64360_CPU_PADS_CALIBRATION
mdefine_line|#define MV64360_CPU_PADS_CALIBRATION&t;&t;0x03b4
DECL|macro|MV64360_CPU_RESET_SAMPLE_LO
mdefine_line|#define MV64360_CPU_RESET_SAMPLE_LO&t;&t;0x03c4
DECL|macro|MV64360_CPU_RESET_SAMPLE_HI
mdefine_line|#define MV64360_CPU_RESET_SAMPLE_HI&t;&t;0x03d4
multiline_comment|/* SMP Register Map */
DECL|macro|MV64360_WHO_AM_I
mdefine_line|#define MV64360_WHO_AM_I&t;&t;&t;0x0200
DECL|macro|MV64360_CPU0_DOORBELL
mdefine_line|#define MV64360_CPU0_DOORBELL&t;&t;&t;0x0214
DECL|macro|MV64360_CPU0_DOORBELL_CLR
mdefine_line|#define MV64360_CPU0_DOORBELL_CLR&t;&t;0x021c
DECL|macro|MV64360_CPU0_DOORBELL_MASK
mdefine_line|#define MV64360_CPU0_DOORBELL_MASK&t;&t;0x0234
DECL|macro|MV64360_CPU1_DOORBELL
mdefine_line|#define MV64360_CPU1_DOORBELL&t;&t;&t;0x0224
DECL|macro|MV64360_CPU1_DOORBELL_CLR
mdefine_line|#define MV64360_CPU1_DOORBELL_CLR&t;&t;0x022c
DECL|macro|MV64360_CPU1_DOORBELL_MASK
mdefine_line|#define MV64360_CPU1_DOORBELL_MASK&t;&t;0x023c
DECL|macro|MV64360_CPUx_DOORBELL
mdefine_line|#define MV64360_CPUx_DOORBELL(x)&t;&t;(0x0214 + ((x)*0x10))
DECL|macro|MV64360_CPUx_DOORBELL_CLR
mdefine_line|#define MV64360_CPUx_DOORBELL_CLR(x)&t;&t;(0x021c + ((x)*0x10))
DECL|macro|MV64360_CPUx_DOORBELL_MASK
mdefine_line|#define MV64360_CPUx_DOORBELL_MASK(x)&t;&t;(0x0234 + ((x)*0x08))
DECL|macro|MV64360_SEMAPHORE_0
mdefine_line|#define MV64360_SEMAPHORE_0&t;&t;&t;0x0244
DECL|macro|MV64360_SEMAPHORE_1
mdefine_line|#define MV64360_SEMAPHORE_1&t;&t;&t;0x024c
DECL|macro|MV64360_SEMAPHORE_2
mdefine_line|#define MV64360_SEMAPHORE_2&t;&t;&t;0x0254
DECL|macro|MV64360_SEMAPHORE_3
mdefine_line|#define MV64360_SEMAPHORE_3&t;&t;&t;0x025c
DECL|macro|MV64360_SEMAPHORE_4
mdefine_line|#define MV64360_SEMAPHORE_4&t;&t;&t;0x0264
DECL|macro|MV64360_SEMAPHORE_5
mdefine_line|#define MV64360_SEMAPHORE_5&t;&t;&t;0x026c
DECL|macro|MV64360_SEMAPHORE_6
mdefine_line|#define MV64360_SEMAPHORE_6&t;&t;&t;0x0274
DECL|macro|MV64360_SEMAPHORE_7
mdefine_line|#define MV64360_SEMAPHORE_7&t;&t;&t;0x027c
multiline_comment|/* CPU Sync Barrier Registers */
DECL|macro|GT64260_CPU_SYNC_BARRIER_PCI0
mdefine_line|#define GT64260_CPU_SYNC_BARRIER_PCI0&t;&t;0x00c0
DECL|macro|GT64260_CPU_SYNC_BARRIER_PCI1
mdefine_line|#define GT64260_CPU_SYNC_BARRIER_PCI1&t;&t;0x00c8
DECL|macro|MV64360_CPU0_SYNC_BARRIER_TRIG
mdefine_line|#define MV64360_CPU0_SYNC_BARRIER_TRIG&t;&t;0x00c0
DECL|macro|MV64360_CPU0_SYNC_BARRIER_VIRT
mdefine_line|#define MV64360_CPU0_SYNC_BARRIER_VIRT&t;&t;0x00c8
DECL|macro|MV64360_CPU1_SYNC_BARRIER_TRIG
mdefine_line|#define MV64360_CPU1_SYNC_BARRIER_TRIG&t;&t;0x00d0
DECL|macro|MV64360_CPU1_SYNC_BARRIER_VIRT
mdefine_line|#define MV64360_CPU1_SYNC_BARRIER_VIRT&t;&t;0x00d8
multiline_comment|/* CPU Deadlock and Ordering registers (Rev B part only) */
DECL|macro|GT64260_CPU_DEADLOCK_ORDERING
mdefine_line|#define GT64260_CPU_DEADLOCK_ORDERING&t;&t;&t;0x02d0
DECL|macro|GT64260_CPU_WB_PRIORITY_BUFFER_DEPTH
mdefine_line|#define GT64260_CPU_WB_PRIORITY_BUFFER_DEPTH&t;&t;0x02d8
DECL|macro|GT64260_CPU_COUNTERS_SYNC_BARRIER_ATTRIBUTE
mdefine_line|#define GT64260_CPU_COUNTERS_SYNC_BARRIER_ATTRIBUTE&t;0x02e0
multiline_comment|/* CPU Access Protection Registers (gt64260 realy has 8 but don&squot;t need) */
DECL|macro|MV64x260_CPU_PROT_WINDOWS
mdefine_line|#define&t;MV64x260_CPU_PROT_WINDOWS&t;&t;4
DECL|macro|GT64260_CPU_PROT_ACCPROTECT
mdefine_line|#define&t;GT64260_CPU_PROT_ACCPROTECT&t;&t;(1&lt;&lt;16)
DECL|macro|GT64260_CPU_PROT_WRPROTECT
mdefine_line|#define&t;GT64260_CPU_PROT_WRPROTECT&t;&t;(1&lt;&lt;17)
DECL|macro|GT64260_CPU_PROT_CACHEPROTECT
mdefine_line|#define&t;GT64260_CPU_PROT_CACHEPROTECT&t;&t;(1&lt;&lt;18)
DECL|macro|MV64360_CPU_PROT_ACCPROTECT
mdefine_line|#define&t;MV64360_CPU_PROT_ACCPROTECT&t;&t;(1&lt;&lt;20)
DECL|macro|MV64360_CPU_PROT_WRPROTECT
mdefine_line|#define&t;MV64360_CPU_PROT_WRPROTECT&t;&t;(1&lt;&lt;21)
DECL|macro|MV64360_CPU_PROT_CACHEPROTECT
mdefine_line|#define&t;MV64360_CPU_PROT_CACHEPROTECT&t;&t;(1&lt;&lt;22)
DECL|macro|MV64360_CPU_PROT_WIN_ENABLE
mdefine_line|#define&t;MV64360_CPU_PROT_WIN_ENABLE&t;&t;(1&lt;&lt;31)
DECL|macro|MV64x60_CPU_PROT_BASE_0
mdefine_line|#define MV64x60_CPU_PROT_BASE_0&t;&t;&t;0x0180
DECL|macro|MV64x60_CPU_PROT_SIZE_0
mdefine_line|#define MV64x60_CPU_PROT_SIZE_0&t;&t;&t;0x0188
DECL|macro|MV64x60_CPU_PROT_BASE_1
mdefine_line|#define MV64x60_CPU_PROT_BASE_1&t;&t;&t;0x0190
DECL|macro|MV64x60_CPU_PROT_SIZE_1
mdefine_line|#define MV64x60_CPU_PROT_SIZE_1&t;&t;&t;0x0198
DECL|macro|MV64x60_CPU_PROT_BASE_2
mdefine_line|#define MV64x60_CPU_PROT_BASE_2&t;&t;&t;0x01a0
DECL|macro|MV64x60_CPU_PROT_SIZE_2
mdefine_line|#define MV64x60_CPU_PROT_SIZE_2&t;&t;&t;0x01a8
DECL|macro|MV64x60_CPU_PROT_BASE_3
mdefine_line|#define MV64x60_CPU_PROT_BASE_3&t;&t;&t;0x01b0
DECL|macro|MV64x60_CPU_PROT_SIZE_3
mdefine_line|#define MV64x60_CPU_PROT_SIZE_3&t;&t;&t;0x01b8
DECL|macro|GT64260_CPU_PROT_BASE_4
mdefine_line|#define GT64260_CPU_PROT_BASE_4&t;&t;&t;0x01c0
DECL|macro|GT64260_CPU_PROT_SIZE_4
mdefine_line|#define GT64260_CPU_PROT_SIZE_4&t;&t;&t;0x01c8
DECL|macro|GT64260_CPU_PROT_BASE_5
mdefine_line|#define GT64260_CPU_PROT_BASE_5&t;&t;&t;0x01d0
DECL|macro|GT64260_CPU_PROT_SIZE_5
mdefine_line|#define GT64260_CPU_PROT_SIZE_5&t;&t;&t;0x01d8
DECL|macro|GT64260_CPU_PROT_BASE_6
mdefine_line|#define GT64260_CPU_PROT_BASE_6&t;&t;&t;0x01e0
DECL|macro|GT64260_CPU_PROT_SIZE_6
mdefine_line|#define GT64260_CPU_PROT_SIZE_6&t;&t;&t;0x01e8
DECL|macro|GT64260_CPU_PROT_BASE_7
mdefine_line|#define GT64260_CPU_PROT_BASE_7&t;&t;&t;0x01f0
DECL|macro|GT64260_CPU_PROT_SIZE_7
mdefine_line|#define GT64260_CPU_PROT_SIZE_7&t;&t;&t;0x01f8
multiline_comment|/* CPU Snoop Control Registers (64260 only) */
DECL|macro|GT64260_CPU_SNOOP_WINDOWS
mdefine_line|#define&t;GT64260_CPU_SNOOP_WINDOWS&t;&t;4
DECL|macro|GT64260_CPU_SNOOP_NONE
mdefine_line|#define&t;GT64260_CPU_SNOOP_NONE&t;&t;&t;0x00000000
DECL|macro|GT64260_CPU_SNOOP_WT
mdefine_line|#define&t;GT64260_CPU_SNOOP_WT&t;&t;&t;0x00010000
DECL|macro|GT64260_CPU_SNOOP_WB
mdefine_line|#define&t;GT64260_CPU_SNOOP_WB&t;&t;&t;0x00020000
DECL|macro|GT64260_CPU_SNOOP_MASK
mdefine_line|#define&t;GT64260_CPU_SNOOP_MASK&t;&t;&t;0x00030000
DECL|macro|GT64260_CPU_SNOOP_ALL_BITS
mdefine_line|#define&t;GT64260_CPU_SNOOP_ALL_BITS&t;&t;GT64260_CPU_SNOOP_MASK
DECL|macro|GT64260_CPU_SNOOP_BASE_0
mdefine_line|#define GT64260_CPU_SNOOP_BASE_0&t;&t;0x0380
DECL|macro|GT64260_CPU_SNOOP_SIZE_0
mdefine_line|#define GT64260_CPU_SNOOP_SIZE_0&t;&t;0x0388
DECL|macro|GT64260_CPU_SNOOP_BASE_1
mdefine_line|#define GT64260_CPU_SNOOP_BASE_1&t;&t;0x0390
DECL|macro|GT64260_CPU_SNOOP_SIZE_1
mdefine_line|#define GT64260_CPU_SNOOP_SIZE_1&t;&t;0x0398
DECL|macro|GT64260_CPU_SNOOP_BASE_2
mdefine_line|#define GT64260_CPU_SNOOP_BASE_2&t;&t;0x03a0
DECL|macro|GT64260_CPU_SNOOP_SIZE_2
mdefine_line|#define GT64260_CPU_SNOOP_SIZE_2&t;&t;0x03a8
DECL|macro|GT64260_CPU_SNOOP_BASE_3
mdefine_line|#define GT64260_CPU_SNOOP_BASE_3&t;&t;0x03b0
DECL|macro|GT64260_CPU_SNOOP_SIZE_3
mdefine_line|#define GT64260_CPU_SNOOP_SIZE_3&t;&t;0x03b8
multiline_comment|/* CPU Snoop Control Registers (64360 only) */
DECL|macro|MV64360_CPU_SNOOP_WINDOWS
mdefine_line|#define&t;MV64360_CPU_SNOOP_WINDOWS&t;&t;4
DECL|macro|MV64360_CPU_SNOOP_NONE
mdefine_line|#define&t;MV64360_CPU_SNOOP_NONE&t;&t;&t;0x00000000
DECL|macro|MV64360_CPU_SNOOP_WT
mdefine_line|#define&t;MV64360_CPU_SNOOP_WT&t;&t;&t;0x00010000
DECL|macro|MV64360_CPU_SNOOP_WB
mdefine_line|#define&t;MV64360_CPU_SNOOP_WB&t;&t;&t;0x00020000
DECL|macro|MV64360_CPU_SNOOP_MASK
mdefine_line|#define&t;MV64360_CPU_SNOOP_MASK&t;&t;&t;0x00030000
DECL|macro|MV64360_CPU_SNOOP_ALL_BITS
mdefine_line|#define&t;MV64360_CPU_SNOOP_ALL_BITS&t;&t;MV64360_CPU_SNOOP_MASK
multiline_comment|/* CPU Error Report Registers */
DECL|macro|MV64x60_CPU_ERR_ADDR_LO
mdefine_line|#define MV64x60_CPU_ERR_ADDR_LO&t;&t;&t;0x0070
DECL|macro|MV64x60_CPU_ERR_ADDR_HI
mdefine_line|#define MV64x60_CPU_ERR_ADDR_HI&t;&t;&t;0x0078
DECL|macro|MV64x60_CPU_ERR_DATA_LO
mdefine_line|#define MV64x60_CPU_ERR_DATA_LO&t;&t;&t;0x0128
DECL|macro|MV64x60_CPU_ERR_DATA_HI
mdefine_line|#define MV64x60_CPU_ERR_DATA_HI&t;&t;&t;0x0130
DECL|macro|MV64x60_CPU_ERR_PARITY
mdefine_line|#define MV64x60_CPU_ERR_PARITY&t;&t;&t;0x0138
DECL|macro|MV64x60_CPU_ERR_CAUSE
mdefine_line|#define MV64x60_CPU_ERR_CAUSE&t;&t;&t;0x0140
DECL|macro|MV64x60_CPU_ERR_MASK
mdefine_line|#define MV64x60_CPU_ERR_MASK&t;&t;&t;0x0148
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;SRAM Cotnroller Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|MV64360_SRAM_CONFIG
mdefine_line|#define&t;MV64360_SRAM_CONFIG&t;&t;&t;0x0380
DECL|macro|MV64360_SRAM_TEST_MODE
mdefine_line|#define&t;MV64360_SRAM_TEST_MODE&t;&t;&t;0x03f4
DECL|macro|MV64360_SRAM_ERR_CAUSE
mdefine_line|#define&t;MV64360_SRAM_ERR_CAUSE&t;&t;&t;0x0388
DECL|macro|MV64360_SRAM_ERR_ADDR_LO
mdefine_line|#define&t;MV64360_SRAM_ERR_ADDR_LO&t;&t;0x0390
DECL|macro|MV64360_SRAM_ERR_ADDR_HI
mdefine_line|#define&t;MV64360_SRAM_ERR_ADDR_HI&t;&t;0x03f8
DECL|macro|MV64360_SRAM_ERR_DATA_LO
mdefine_line|#define&t;MV64360_SRAM_ERR_DATA_LO&t;&t;0x0398
DECL|macro|MV64360_SRAM_ERR_DATA_HI
mdefine_line|#define&t;MV64360_SRAM_ERR_DATA_HI&t;&t;0x03a0
DECL|macro|MV64360_SRAM_ERR_PARITY
mdefine_line|#define&t;MV64360_SRAM_ERR_PARITY&t;&t;&t;0x03a8
DECL|macro|MV64360_SRAM_SIZE
mdefine_line|#define&t;MV64360_SRAM_SIZE&t;&t;&t;0x00040000 /* 256 KB of SRAM */
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;SDRAM/MEM Cotnroller Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* SDRAM Config Registers (64260) */
DECL|macro|GT64260_SDRAM_CONFIG
mdefine_line|#define&t;GT64260_SDRAM_CONFIG&t;&t;&t;0x0448
multiline_comment|/* SDRAM Error Report Registers (64260) */
DECL|macro|GT64260_SDRAM_ERR_DATA_LO
mdefine_line|#define&t;GT64260_SDRAM_ERR_DATA_LO&t;&t;0x0484
DECL|macro|GT64260_SDRAM_ERR_DATA_HI
mdefine_line|#define&t;GT64260_SDRAM_ERR_DATA_HI&t;&t;0x0480
DECL|macro|GT64260_SDRAM_ERR_ADDR
mdefine_line|#define&t;GT64260_SDRAM_ERR_ADDR&t;&t;&t;0x0490
DECL|macro|GT64260_SDRAM_ERR_ECC_RCVD
mdefine_line|#define&t;GT64260_SDRAM_ERR_ECC_RCVD&t;&t;0x0488
DECL|macro|GT64260_SDRAM_ERR_ECC_CALC
mdefine_line|#define&t;GT64260_SDRAM_ERR_ECC_CALC&t;&t;0x048c
DECL|macro|GT64260_SDRAM_ERR_ECC_CNTL
mdefine_line|#define&t;GT64260_SDRAM_ERR_ECC_CNTL&t;&t;0x0494
DECL|macro|GT64260_SDRAM_ERR_ECC_ERR_CNT
mdefine_line|#define&t;GT64260_SDRAM_ERR_ECC_ERR_CNT&t;&t;0x0498
multiline_comment|/* SDRAM Config Registers (64360) */
DECL|macro|MV64360_SDRAM_CONFIG
mdefine_line|#define&t;MV64360_SDRAM_CONFIG&t;&t;&t;0x1400
multiline_comment|/* SDRAM Control Registers */
DECL|macro|MV64360_D_UNIT_CONTROL_LOW
mdefine_line|#define MV64360_D_UNIT_CONTROL_LOW&t;&t;0x1404
DECL|macro|MV64360_D_UNIT_CONTROL_HIGH
mdefine_line|#define MV64360_D_UNIT_CONTROL_HIGH&t;&t;0x1424
multiline_comment|/* SDRAM Error Report Registers (64360) */
DECL|macro|MV64360_SDRAM_ERR_DATA_LO
mdefine_line|#define&t;MV64360_SDRAM_ERR_DATA_LO&t;&t;0x1444
DECL|macro|MV64360_SDRAM_ERR_DATA_HI
mdefine_line|#define&t;MV64360_SDRAM_ERR_DATA_HI&t;&t;0x1440
DECL|macro|MV64360_SDRAM_ERR_ADDR
mdefine_line|#define&t;MV64360_SDRAM_ERR_ADDR&t;&t;&t;0x1450
DECL|macro|MV64360_SDRAM_ERR_ECC_RCVD
mdefine_line|#define&t;MV64360_SDRAM_ERR_ECC_RCVD&t;&t;0x1448
DECL|macro|MV64360_SDRAM_ERR_ECC_CALC
mdefine_line|#define&t;MV64360_SDRAM_ERR_ECC_CALC&t;&t;0x144c
DECL|macro|MV64360_SDRAM_ERR_ECC_CNTL
mdefine_line|#define&t;MV64360_SDRAM_ERR_ECC_CNTL&t;&t;0x1454
DECL|macro|MV64360_SDRAM_ERR_ECC_ERR_CNT
mdefine_line|#define&t;MV64360_SDRAM_ERR_ECC_ERR_CNT&t;&t;0x1458
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Device/BOOT Cotnroller Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* Device Control Registers */
DECL|macro|MV64x60_DEV_BANK_PARAMS_0
mdefine_line|#define&t;MV64x60_DEV_BANK_PARAMS_0&t;&t;0x045c
DECL|macro|MV64x60_DEV_BANK_PARAMS_1
mdefine_line|#define&t;MV64x60_DEV_BANK_PARAMS_1&t;&t;0x0460
DECL|macro|MV64x60_DEV_BANK_PARAMS_2
mdefine_line|#define&t;MV64x60_DEV_BANK_PARAMS_2&t;&t;0x0464
DECL|macro|MV64x60_DEV_BANK_PARAMS_3
mdefine_line|#define&t;MV64x60_DEV_BANK_PARAMS_3&t;&t;0x0468
DECL|macro|MV64x60_DEV_BOOT_PARAMS
mdefine_line|#define&t;MV64x60_DEV_BOOT_PARAMS&t;&t;&t;0x046c
DECL|macro|MV64x60_DEV_IF_CNTL
mdefine_line|#define&t;MV64x60_DEV_IF_CNTL&t;&t;&t;0x04c0
DECL|macro|MV64x60_DEV_IF_XBAR_CNTL_LO
mdefine_line|#define&t;MV64x60_DEV_IF_XBAR_CNTL_LO&t;&t;0x04c8
DECL|macro|MV64x60_DEV_IF_XBAR_CNTL_HI
mdefine_line|#define&t;MV64x60_DEV_IF_XBAR_CNTL_HI&t;&t;0x04cc
DECL|macro|MV64x60_DEV_IF_XBAR_CNTL_TO
mdefine_line|#define&t;MV64x60_DEV_IF_XBAR_CNTL_TO&t;&t;0x04c4
multiline_comment|/* Device Interrupt Registers */
DECL|macro|MV64x60_DEV_INTR_CAUSE
mdefine_line|#define&t;MV64x60_DEV_INTR_CAUSE&t;&t;&t;0x04d0
DECL|macro|MV64x60_DEV_INTR_MASK
mdefine_line|#define&t;MV64x60_DEV_INTR_MASK&t;&t;&t;0x04d4
DECL|macro|MV64x60_DEV_INTR_ERR_ADDR
mdefine_line|#define&t;MV64x60_DEV_INTR_ERR_ADDR&t;&t;0x04d8
DECL|macro|MV64360_DEV_INTR_ERR_DATA
mdefine_line|#define&t;MV64360_DEV_INTR_ERR_DATA&t;&t;0x04dc
DECL|macro|MV64360_DEV_INTR_ERR_PAR
mdefine_line|#define&t;MV64360_DEV_INTR_ERR_PAR&t;&t;0x04e0
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;PCI Bridge Interface Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* PCI Configuration Access Registers */
DECL|macro|MV64x60_PCI0_CONFIG_ADDR
mdefine_line|#define&t;MV64x60_PCI0_CONFIG_ADDR&t;&t;0x0cf8
DECL|macro|MV64x60_PCI0_CONFIG_DATA
mdefine_line|#define&t;MV64x60_PCI0_CONFIG_DATA&t;&t;0x0cfc
DECL|macro|MV64x60_PCI0_IACK
mdefine_line|#define&t;MV64x60_PCI0_IACK&t;&t;&t;0x0c34
DECL|macro|MV64x60_PCI1_CONFIG_ADDR
mdefine_line|#define&t;MV64x60_PCI1_CONFIG_ADDR&t;&t;0x0c78
DECL|macro|MV64x60_PCI1_CONFIG_DATA
mdefine_line|#define&t;MV64x60_PCI1_CONFIG_DATA&t;&t;0x0c7c
DECL|macro|MV64x60_PCI1_IACK
mdefine_line|#define&t;MV64x60_PCI1_IACK&t;&t;&t;0x0cb4
multiline_comment|/* PCI Control Registers */
DECL|macro|MV64x60_PCI0_CMD
mdefine_line|#define&t;MV64x60_PCI0_CMD&t;&t;&t;0x0c00
DECL|macro|MV64x60_PCI0_MODE
mdefine_line|#define&t;MV64x60_PCI0_MODE&t;&t;&t;0x0d00
DECL|macro|MV64x60_PCI0_TO_RETRY
mdefine_line|#define&t;MV64x60_PCI0_TO_RETRY&t;&t;&t;0x0c04
DECL|macro|MV64x60_PCI0_RD_BUF_DISCARD_TIMER
mdefine_line|#define&t;MV64x60_PCI0_RD_BUF_DISCARD_TIMER&t;0x0d04
DECL|macro|MV64x60_PCI0_MSI_TRIGGER_TIMER
mdefine_line|#define&t;MV64x60_PCI0_MSI_TRIGGER_TIMER&t;&t;0x0c38
DECL|macro|MV64x60_PCI0_ARBITER_CNTL
mdefine_line|#define&t;MV64x60_PCI0_ARBITER_CNTL&t;&t;0x1d00
DECL|macro|MV64x60_PCI0_XBAR_CNTL_LO
mdefine_line|#define&t;MV64x60_PCI0_XBAR_CNTL_LO&t;&t;0x1d08
DECL|macro|MV64x60_PCI0_XBAR_CNTL_HI
mdefine_line|#define&t;MV64x60_PCI0_XBAR_CNTL_HI&t;&t;0x1d0c
DECL|macro|MV64x60_PCI0_XBAR_CNTL_TO
mdefine_line|#define&t;MV64x60_PCI0_XBAR_CNTL_TO&t;&t;0x1d04
DECL|macro|MV64x60_PCI0_RD_RESP_XBAR_CNTL_LO
mdefine_line|#define&t;MV64x60_PCI0_RD_RESP_XBAR_CNTL_LO&t;0x1d18
DECL|macro|MV64x60_PCI0_RD_RESP_XBAR_CNTL_HI
mdefine_line|#define&t;MV64x60_PCI0_RD_RESP_XBAR_CNTL_HI&t;0x1d1c
DECL|macro|MV64x60_PCI0_SYNC_BARRIER
mdefine_line|#define&t;MV64x60_PCI0_SYNC_BARRIER&t;&t;0x1d10
DECL|macro|MV64x60_PCI0_P2P_CONFIG
mdefine_line|#define&t;MV64x60_PCI0_P2P_CONFIG&t;&t;&t;0x1d14
DECL|macro|MV64x60_PCI0_INTR_MASK
mdefine_line|#define&t;MV64x60_PCI0_INTR_MASK
DECL|macro|GT64260_PCI0_P2P_SWAP_CNTL
mdefine_line|#define&t;GT64260_PCI0_P2P_SWAP_CNTL&t;&t;0x1d54
DECL|macro|MV64x60_PCI1_CMD
mdefine_line|#define&t;MV64x60_PCI1_CMD&t;&t;&t;0x0c80
DECL|macro|MV64x60_PCI1_MODE
mdefine_line|#define&t;MV64x60_PCI1_MODE&t;&t;&t;0x0d80
DECL|macro|MV64x60_PCI1_TO_RETRY
mdefine_line|#define&t;MV64x60_PCI1_TO_RETRY&t;&t;&t;0x0c84
DECL|macro|MV64x60_PCI1_RD_BUF_DISCARD_TIMER
mdefine_line|#define&t;MV64x60_PCI1_RD_BUF_DISCARD_TIMER&t;0x0d84
DECL|macro|MV64x60_PCI1_MSI_TRIGGER_TIMER
mdefine_line|#define&t;MV64x60_PCI1_MSI_TRIGGER_TIMER&t;&t;0x0cb8
DECL|macro|MV64x60_PCI1_ARBITER_CNTL
mdefine_line|#define&t;MV64x60_PCI1_ARBITER_CNTL&t;&t;0x1d80
DECL|macro|MV64x60_PCI1_XBAR_CNTL_LO
mdefine_line|#define&t;MV64x60_PCI1_XBAR_CNTL_LO&t;&t;0x1d88
DECL|macro|MV64x60_PCI1_XBAR_CNTL_HI
mdefine_line|#define&t;MV64x60_PCI1_XBAR_CNTL_HI&t;&t;0x1d8c
DECL|macro|MV64x60_PCI1_XBAR_CNTL_TO
mdefine_line|#define&t;MV64x60_PCI1_XBAR_CNTL_TO&t;&t;0x1d84
DECL|macro|MV64x60_PCI1_RD_RESP_XBAR_CNTL_LO
mdefine_line|#define&t;MV64x60_PCI1_RD_RESP_XBAR_CNTL_LO&t;0x1d98
DECL|macro|MV64x60_PCI1_RD_RESP_XBAR_CNTL_HI
mdefine_line|#define&t;MV64x60_PCI1_RD_RESP_XBAR_CNTL_HI&t;0x1d9c
DECL|macro|MV64x60_PCI1_SYNC_BARRIER
mdefine_line|#define&t;MV64x60_PCI1_SYNC_BARRIER&t;&t;0x1d90
DECL|macro|MV64x60_PCI1_P2P_CONFIG
mdefine_line|#define&t;MV64x60_PCI1_P2P_CONFIG&t;&t;&t;0x1d94
DECL|macro|GT64260_PCI1_P2P_SWAP_CNTL
mdefine_line|#define&t;GT64260_PCI1_P2P_SWAP_CNTL&t;&t;0x1dd4
multiline_comment|/* Different modes that the pci hoses can be in (bits 5:4 in PCI Mode reg) */
DECL|macro|MV64x60_PCIMODE_CONVENTIONAL
mdefine_line|#define&t;MV64x60_PCIMODE_CONVENTIONAL&t;&t;0
DECL|macro|MV64x60_PCIMODE_PCIX_66
mdefine_line|#define&t;MV64x60_PCIMODE_PCIX_66&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|MV64x60_PCIMODE_PCIX_100
mdefine_line|#define&t;MV64x60_PCIMODE_PCIX_100&t;&t;(2 &lt;&lt; 4)
DECL|macro|MV64x60_PCIMODE_PCIX_133
mdefine_line|#define&t;MV64x60_PCIMODE_PCIX_133&t;&t;(3 &lt;&lt; 4)
DECL|macro|MV64x60_PCIMODE_MASK
mdefine_line|#define&t;MV64x60_PCIMODE_MASK&t;&t;&t;(0x3 &lt;&lt; 4)
multiline_comment|/* PCI Access Control Regions Registers */
DECL|macro|GT64260_PCI_ACC_CNTL_PREFETCHEN
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_PREFETCHEN&t;&t;(1&lt;&lt;12)
DECL|macro|GT64260_PCI_ACC_CNTL_DREADEN
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_DREADEN&t;&t;(1&lt;&lt;13)
DECL|macro|GT64260_PCI_ACC_CNTL_RDPREFETCH
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_RDPREFETCH&t;&t;(1&lt;&lt;16)
DECL|macro|GT64260_PCI_ACC_CNTL_RDLINEPREFETCH
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_RDLINEPREFETCH&t;(1&lt;&lt;17)
DECL|macro|GT64260_PCI_ACC_CNTL_RDMULPREFETCH
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_RDMULPREFETCH&t;(1&lt;&lt;18)
DECL|macro|GT64260_PCI_ACC_CNTL_MBURST_32_BTYES
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_MBURST_32_BTYES&t;0x00000000
DECL|macro|GT64260_PCI_ACC_CNTL_MBURST_64_BYTES
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_MBURST_64_BYTES&t;0x00100000
DECL|macro|GT64260_PCI_ACC_CNTL_MBURST_128_BYTES
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_MBURST_128_BYTES&t;0x00200000
DECL|macro|GT64260_PCI_ACC_CNTL_MBURST_MASK
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_MBURST_MASK&t;0x00300000
DECL|macro|GT64260_PCI_ACC_CNTL_SWAP_BYTE
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_SWAP_BYTE&t;&t;0x00000000
DECL|macro|GT64260_PCI_ACC_CNTL_SWAP_NONE
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_SWAP_NONE&t;&t;0x01000000
DECL|macro|GT64260_PCI_ACC_CNTL_SWAP_BYTE_WORD
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_SWAP_BYTE_WORD&t;0x02000000
DECL|macro|GT64260_PCI_ACC_CNTL_SWAP_WORD
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_SWAP_WORD&t;&t;0x03000000
DECL|macro|GT64260_PCI_ACC_CNTL_SWAP_MASK
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_SWAP_MASK&t;&t;0x03000000
DECL|macro|GT64260_PCI_ACC_CNTL_ACCPROT
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_ACCPROT&t;&t;(1&lt;&lt;28)
DECL|macro|GT64260_PCI_ACC_CNTL_WRPROT
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_WRPROT&t;&t;(1&lt;&lt;29)
DECL|macro|GT64260_PCI_ACC_CNTL_ALL_BITS
mdefine_line|#define&t;GT64260_PCI_ACC_CNTL_ALL_BITS&t;(GT64260_PCI_ACC_CNTL_PREFETCHEN |    &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_DREADEN |       &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_RDPREFETCH |    &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_RDLINEPREFETCH |&bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_RDMULPREFETCH | &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_MBURST_MASK |   &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_SWAP_MASK |     &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_ACCPROT|        &bslash;&n;&t;&t;&t;&t;&t; GT64260_PCI_ACC_CNTL_WRPROT)
DECL|macro|MV64360_PCI_ACC_CNTL_ENABLE
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_ENABLE&t;&t;(1&lt;&lt;0)
DECL|macro|MV64360_PCI_ACC_CNTL_REQ64
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_REQ64&t;&t;(1&lt;&lt;1)
DECL|macro|MV64360_PCI_ACC_CNTL_SNOOP_NONE
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SNOOP_NONE&t;&t;0x00000000
DECL|macro|MV64360_PCI_ACC_CNTL_SNOOP_WT
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SNOOP_WT&t;&t;0x00000004
DECL|macro|MV64360_PCI_ACC_CNTL_SNOOP_WB
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SNOOP_WB&t;&t;0x00000008
DECL|macro|MV64360_PCI_ACC_CNTL_SNOOP_MASK
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SNOOP_MASK&t;&t;0x0000000c
DECL|macro|MV64360_PCI_ACC_CNTL_ACCPROT
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_ACCPROT&t;&t;(1&lt;&lt;4)
DECL|macro|MV64360_PCI_ACC_CNTL_WRPROT
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_WRPROT&t;&t;(1&lt;&lt;5)
DECL|macro|MV64360_PCI_ACC_CNTL_SWAP_BYTE
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SWAP_BYTE&t;&t;0x00000000
DECL|macro|MV64360_PCI_ACC_CNTL_SWAP_NONE
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SWAP_NONE&t;&t;0x00000040
DECL|macro|MV64360_PCI_ACC_CNTL_SWAP_BYTE_WORD
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SWAP_BYTE_WORD&t;0x00000080
DECL|macro|MV64360_PCI_ACC_CNTL_SWAP_WORD
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SWAP_WORD&t;&t;0x000000c0
DECL|macro|MV64360_PCI_ACC_CNTL_SWAP_MASK
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_SWAP_MASK&t;&t;0x000000c0
DECL|macro|MV64360_PCI_ACC_CNTL_MBURST_32_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_MBURST_32_BYTES&t;0x00000000
DECL|macro|MV64360_PCI_ACC_CNTL_MBURST_64_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_MBURST_64_BYTES&t;0x00000100
DECL|macro|MV64360_PCI_ACC_CNTL_MBURST_128_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_MBURST_128_BYTES&t;0x00000200
DECL|macro|MV64360_PCI_ACC_CNTL_MBURST_MASK
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_MBURST_MASK&t;0x00000300
DECL|macro|MV64360_PCI_ACC_CNTL_RDSIZE_32_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_RDSIZE_32_BYTES&t;0x00000000
DECL|macro|MV64360_PCI_ACC_CNTL_RDSIZE_64_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_RDSIZE_64_BYTES&t;0x00000400
DECL|macro|MV64360_PCI_ACC_CNTL_RDSIZE_128_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_RDSIZE_128_BYTES&t;0x00000800
DECL|macro|MV64360_PCI_ACC_CNTL_RDSIZE_256_BYTES
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_RDSIZE_256_BYTES&t;0x00000c00
DECL|macro|MV64360_PCI_ACC_CNTL_RDSIZE_MASK
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_RDSIZE_MASK&t;0x00000c00
DECL|macro|MV64360_PCI_ACC_CNTL_ALL_BITS
mdefine_line|#define&t;MV64360_PCI_ACC_CNTL_ALL_BITS&t;(MV64360_PCI_ACC_CNTL_ENABLE |&t;    &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_REQ64 |&t;    &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_SNOOP_MASK |  &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_ACCPROT |&t;    &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_WRPROT |&t;    &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_SWAP_MASK |   &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_MBURST_MASK | &bslash;&n;&t;&t;&t;&t;&t; MV64360_PCI_ACC_CNTL_RDSIZE_MASK)
DECL|macro|MV64x60_PCI0_ACC_CNTL_0_BASE_LO
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_0_BASE_LO&t;&t;0x1e00
DECL|macro|MV64x60_PCI0_ACC_CNTL_0_BASE_HI
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_0_BASE_HI&t;&t;0x1e04
DECL|macro|MV64x60_PCI0_ACC_CNTL_0_SIZE
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_0_SIZE&t;&t;0x1e08
DECL|macro|MV64x60_PCI0_ACC_CNTL_1_BASE_LO
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_1_BASE_LO&t;&t;0x1e10
DECL|macro|MV64x60_PCI0_ACC_CNTL_1_BASE_HI
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_1_BASE_HI&t;&t;0x1e14
DECL|macro|MV64x60_PCI0_ACC_CNTL_1_SIZE
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_1_SIZE&t;&t;0x1e18
DECL|macro|MV64x60_PCI0_ACC_CNTL_2_BASE_LO
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_2_BASE_LO&t;&t;0x1e20
DECL|macro|MV64x60_PCI0_ACC_CNTL_2_BASE_HI
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_2_BASE_HI&t;&t;0x1e24
DECL|macro|MV64x60_PCI0_ACC_CNTL_2_SIZE
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_2_SIZE&t;&t;0x1e28
DECL|macro|MV64x60_PCI0_ACC_CNTL_3_BASE_LO
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_3_BASE_LO&t;&t;0x1e30
DECL|macro|MV64x60_PCI0_ACC_CNTL_3_BASE_HI
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_3_BASE_HI&t;&t;0x1e34
DECL|macro|MV64x60_PCI0_ACC_CNTL_3_SIZE
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_3_SIZE&t;&t;0x1e38
DECL|macro|MV64x60_PCI0_ACC_CNTL_4_BASE_LO
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_4_BASE_LO&t;&t;0x1e40
DECL|macro|MV64x60_PCI0_ACC_CNTL_4_BASE_HI
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_4_BASE_HI&t;&t;0x1e44
DECL|macro|MV64x60_PCI0_ACC_CNTL_4_SIZE
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_4_SIZE&t;&t;0x1e48
DECL|macro|MV64x60_PCI0_ACC_CNTL_5_BASE_LO
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_5_BASE_LO&t;&t;0x1e50
DECL|macro|MV64x60_PCI0_ACC_CNTL_5_BASE_HI
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_5_BASE_HI&t;&t;0x1e54
DECL|macro|MV64x60_PCI0_ACC_CNTL_5_SIZE
mdefine_line|#define&t;MV64x60_PCI0_ACC_CNTL_5_SIZE&t;&t;0x1e58
DECL|macro|GT64260_PCI0_ACC_CNTL_6_BASE_LO
mdefine_line|#define&t;GT64260_PCI0_ACC_CNTL_6_BASE_LO&t;&t;0x1e60
DECL|macro|GT64260_PCI0_ACC_CNTL_6_BASE_HI
mdefine_line|#define&t;GT64260_PCI0_ACC_CNTL_6_BASE_HI&t;&t;0x1e64
DECL|macro|GT64260_PCI0_ACC_CNTL_6_SIZE
mdefine_line|#define&t;GT64260_PCI0_ACC_CNTL_6_SIZE&t;&t;0x1e68
DECL|macro|GT64260_PCI0_ACC_CNTL_7_BASE_LO
mdefine_line|#define&t;GT64260_PCI0_ACC_CNTL_7_BASE_LO&t;&t;0x1e70
DECL|macro|GT64260_PCI0_ACC_CNTL_7_BASE_HI
mdefine_line|#define&t;GT64260_PCI0_ACC_CNTL_7_BASE_HI&t;&t;0x1e74
DECL|macro|GT64260_PCI0_ACC_CNTL_7_SIZE
mdefine_line|#define&t;GT64260_PCI0_ACC_CNTL_7_SIZE&t;&t;0x1e78
DECL|macro|MV64x60_PCI1_ACC_CNTL_0_BASE_LO
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_0_BASE_LO&t;&t;0x1e80
DECL|macro|MV64x60_PCI1_ACC_CNTL_0_BASE_HI
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_0_BASE_HI&t;&t;0x1e84
DECL|macro|MV64x60_PCI1_ACC_CNTL_0_SIZE
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_0_SIZE&t;&t;0x1e88
DECL|macro|MV64x60_PCI1_ACC_CNTL_1_BASE_LO
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_1_BASE_LO&t;&t;0x1e90
DECL|macro|MV64x60_PCI1_ACC_CNTL_1_BASE_HI
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_1_BASE_HI&t;&t;0x1e94
DECL|macro|MV64x60_PCI1_ACC_CNTL_1_SIZE
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_1_SIZE&t;&t;0x1e98
DECL|macro|MV64x60_PCI1_ACC_CNTL_2_BASE_LO
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_2_BASE_LO&t;&t;0x1ea0
DECL|macro|MV64x60_PCI1_ACC_CNTL_2_BASE_HI
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_2_BASE_HI&t;&t;0x1ea4
DECL|macro|MV64x60_PCI1_ACC_CNTL_2_SIZE
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_2_SIZE&t;&t;0x1ea8
DECL|macro|MV64x60_PCI1_ACC_CNTL_3_BASE_LO
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_3_BASE_LO&t;&t;0x1eb0
DECL|macro|MV64x60_PCI1_ACC_CNTL_3_BASE_HI
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_3_BASE_HI&t;&t;0x1eb4
DECL|macro|MV64x60_PCI1_ACC_CNTL_3_SIZE
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_3_SIZE&t;&t;0x1eb8
DECL|macro|MV64x60_PCI1_ACC_CNTL_4_BASE_LO
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_4_BASE_LO&t;&t;0x1ec0
DECL|macro|MV64x60_PCI1_ACC_CNTL_4_BASE_HI
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_4_BASE_HI&t;&t;0x1ec4
DECL|macro|MV64x60_PCI1_ACC_CNTL_4_SIZE
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_4_SIZE&t;&t;0x1ec8
DECL|macro|MV64x60_PCI1_ACC_CNTL_5_BASE_LO
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_5_BASE_LO&t;&t;0x1ed0
DECL|macro|MV64x60_PCI1_ACC_CNTL_5_BASE_HI
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_5_BASE_HI&t;&t;0x1ed4
DECL|macro|MV64x60_PCI1_ACC_CNTL_5_SIZE
mdefine_line|#define&t;MV64x60_PCI1_ACC_CNTL_5_SIZE&t;&t;0x1ed8
DECL|macro|GT64260_PCI1_ACC_CNTL_6_BASE_LO
mdefine_line|#define&t;GT64260_PCI1_ACC_CNTL_6_BASE_LO&t;&t;0x1ee0
DECL|macro|GT64260_PCI1_ACC_CNTL_6_BASE_HI
mdefine_line|#define&t;GT64260_PCI1_ACC_CNTL_6_BASE_HI&t;&t;0x1ee4
DECL|macro|GT64260_PCI1_ACC_CNTL_6_SIZE
mdefine_line|#define&t;GT64260_PCI1_ACC_CNTL_6_SIZE&t;&t;0x1ee8
DECL|macro|GT64260_PCI1_ACC_CNTL_7_BASE_LO
mdefine_line|#define&t;GT64260_PCI1_ACC_CNTL_7_BASE_LO&t;&t;0x1ef0
DECL|macro|GT64260_PCI1_ACC_CNTL_7_BASE_HI
mdefine_line|#define&t;GT64260_PCI1_ACC_CNTL_7_BASE_HI&t;&t;0x1ef4
DECL|macro|GT64260_PCI1_ACC_CNTL_7_SIZE
mdefine_line|#define&t;GT64260_PCI1_ACC_CNTL_7_SIZE&t;&t;0x1ef8
multiline_comment|/* PCI Snoop Control Registers (64260 only) */
DECL|macro|GT64260_PCI_SNOOP_NONE
mdefine_line|#define&t;GT64260_PCI_SNOOP_NONE&t;&t;&t;0x00000000
DECL|macro|GT64260_PCI_SNOOP_WT
mdefine_line|#define&t;GT64260_PCI_SNOOP_WT&t;&t;&t;0x00001000
DECL|macro|GT64260_PCI_SNOOP_WB
mdefine_line|#define&t;GT64260_PCI_SNOOP_WB&t;&t;&t;0x00002000
DECL|macro|GT64260_PCI0_SNOOP_0_BASE_LO
mdefine_line|#define&t;GT64260_PCI0_SNOOP_0_BASE_LO&t;&t;0x1f00
DECL|macro|GT64260_PCI0_SNOOP_0_BASE_HI
mdefine_line|#define&t;GT64260_PCI0_SNOOP_0_BASE_HI&t;&t;0x1f04
DECL|macro|GT64260_PCI0_SNOOP_0_SIZE
mdefine_line|#define&t;GT64260_PCI0_SNOOP_0_SIZE&t;&t;0x1f08
DECL|macro|GT64260_PCI0_SNOOP_1_BASE_LO
mdefine_line|#define&t;GT64260_PCI0_SNOOP_1_BASE_LO&t;&t;0x1f10
DECL|macro|GT64260_PCI0_SNOOP_1_BASE_HI
mdefine_line|#define&t;GT64260_PCI0_SNOOP_1_BASE_HI&t;&t;0x1f14
DECL|macro|GT64260_PCI0_SNOOP_1_SIZE
mdefine_line|#define&t;GT64260_PCI0_SNOOP_1_SIZE&t;&t;0x1f18
DECL|macro|GT64260_PCI0_SNOOP_2_BASE_LO
mdefine_line|#define&t;GT64260_PCI0_SNOOP_2_BASE_LO&t;&t;0x1f20
DECL|macro|GT64260_PCI0_SNOOP_2_BASE_HI
mdefine_line|#define&t;GT64260_PCI0_SNOOP_2_BASE_HI&t;&t;0x1f24
DECL|macro|GT64260_PCI0_SNOOP_2_SIZE
mdefine_line|#define&t;GT64260_PCI0_SNOOP_2_SIZE&t;&t;0x1f28
DECL|macro|GT64260_PCI0_SNOOP_3_BASE_LO
mdefine_line|#define&t;GT64260_PCI0_SNOOP_3_BASE_LO&t;&t;0x1f30
DECL|macro|GT64260_PCI0_SNOOP_3_BASE_HI
mdefine_line|#define&t;GT64260_PCI0_SNOOP_3_BASE_HI&t;&t;0x1f34
DECL|macro|GT64260_PCI0_SNOOP_3_SIZE
mdefine_line|#define&t;GT64260_PCI0_SNOOP_3_SIZE&t;&t;0x1f38
DECL|macro|GT64260_PCI1_SNOOP_0_BASE_LO
mdefine_line|#define&t;GT64260_PCI1_SNOOP_0_BASE_LO&t;&t;0x1f80
DECL|macro|GT64260_PCI1_SNOOP_0_BASE_HI
mdefine_line|#define&t;GT64260_PCI1_SNOOP_0_BASE_HI&t;&t;0x1f84
DECL|macro|GT64260_PCI1_SNOOP_0_SIZE
mdefine_line|#define&t;GT64260_PCI1_SNOOP_0_SIZE&t;&t;0x1f88
DECL|macro|GT64260_PCI1_SNOOP_1_BASE_LO
mdefine_line|#define&t;GT64260_PCI1_SNOOP_1_BASE_LO&t;&t;0x1f90
DECL|macro|GT64260_PCI1_SNOOP_1_BASE_HI
mdefine_line|#define&t;GT64260_PCI1_SNOOP_1_BASE_HI&t;&t;0x1f94
DECL|macro|GT64260_PCI1_SNOOP_1_SIZE
mdefine_line|#define&t;GT64260_PCI1_SNOOP_1_SIZE&t;&t;0x1f98
DECL|macro|GT64260_PCI1_SNOOP_2_BASE_LO
mdefine_line|#define&t;GT64260_PCI1_SNOOP_2_BASE_LO&t;&t;0x1fa0
DECL|macro|GT64260_PCI1_SNOOP_2_BASE_HI
mdefine_line|#define&t;GT64260_PCI1_SNOOP_2_BASE_HI&t;&t;0x1fa4
DECL|macro|GT64260_PCI1_SNOOP_2_SIZE
mdefine_line|#define&t;GT64260_PCI1_SNOOP_2_SIZE&t;&t;0x1fa8
DECL|macro|GT64260_PCI1_SNOOP_3_BASE_LO
mdefine_line|#define&t;GT64260_PCI1_SNOOP_3_BASE_LO&t;&t;0x1fb0
DECL|macro|GT64260_PCI1_SNOOP_3_BASE_HI
mdefine_line|#define&t;GT64260_PCI1_SNOOP_3_BASE_HI&t;&t;0x1fb4
DECL|macro|GT64260_PCI1_SNOOP_3_SIZE
mdefine_line|#define&t;GT64260_PCI1_SNOOP_3_SIZE&t;&t;0x1fb8
multiline_comment|/* PCI Error Report Registers */
DECL|macro|MV64x60_PCI0_ERR_SERR_MASK
mdefine_line|#define MV64x60_PCI0_ERR_SERR_MASK&t;&t;0x0c28
DECL|macro|MV64x60_PCI0_ERR_ADDR_LO
mdefine_line|#define MV64x60_PCI0_ERR_ADDR_LO&t;&t;0x1d40
DECL|macro|MV64x60_PCI0_ERR_ADDR_HI
mdefine_line|#define MV64x60_PCI0_ERR_ADDR_HI&t;&t;0x1d44
DECL|macro|MV64x60_PCI0_ERR_DATA_LO
mdefine_line|#define MV64x60_PCI0_ERR_DATA_LO&t;&t;0x1d48
DECL|macro|MV64x60_PCI0_ERR_DATA_HI
mdefine_line|#define MV64x60_PCI0_ERR_DATA_HI&t;&t;0x1d4c
DECL|macro|MV64x60_PCI0_ERR_CMD
mdefine_line|#define MV64x60_PCI0_ERR_CMD&t;&t;&t;0x1d50
DECL|macro|MV64x60_PCI0_ERR_CAUSE
mdefine_line|#define MV64x60_PCI0_ERR_CAUSE&t;&t;&t;0x1d58
DECL|macro|MV64x60_PCI0_ERR_MASK
mdefine_line|#define MV64x60_PCI0_ERR_MASK&t;&t;&t;0x1d5c
DECL|macro|MV64x60_PCI1_ERR_SERR_MASK
mdefine_line|#define MV64x60_PCI1_ERR_SERR_MASK&t;&t;0x0ca8
DECL|macro|MV64x60_PCI1_ERR_ADDR_LO
mdefine_line|#define MV64x60_PCI1_ERR_ADDR_LO&t;&t;0x1dc0
DECL|macro|MV64x60_PCI1_ERR_ADDR_HI
mdefine_line|#define MV64x60_PCI1_ERR_ADDR_HI&t;&t;0x1dc4
DECL|macro|MV64x60_PCI1_ERR_DATA_LO
mdefine_line|#define MV64x60_PCI1_ERR_DATA_LO&t;&t;0x1dc8
DECL|macro|MV64x60_PCI1_ERR_DATA_HI
mdefine_line|#define MV64x60_PCI1_ERR_DATA_HI&t;&t;0x1dcc
DECL|macro|MV64x60_PCI1_ERR_CMD
mdefine_line|#define MV64x60_PCI1_ERR_CMD&t;&t;&t;0x1dd0
DECL|macro|MV64x60_PCI1_ERR_CAUSE
mdefine_line|#define MV64x60_PCI1_ERR_CAUSE&t;&t;&t;0x1dd8
DECL|macro|MV64x60_PCI1_ERR_MASK
mdefine_line|#define MV64x60_PCI1_ERR_MASK&t;&t;&t;0x1ddc
multiline_comment|/* PCI Slave Address Decoding Registers */
DECL|macro|MV64x60_PCI0_MEM_0_SIZE
mdefine_line|#define&t;MV64x60_PCI0_MEM_0_SIZE&t;&t;&t;0x0c08
DECL|macro|MV64x60_PCI0_MEM_1_SIZE
mdefine_line|#define&t;MV64x60_PCI0_MEM_1_SIZE&t;&t;&t;0x0d08
DECL|macro|MV64x60_PCI0_MEM_2_SIZE
mdefine_line|#define&t;MV64x60_PCI0_MEM_2_SIZE&t;&t;&t;0x0c0c
DECL|macro|MV64x60_PCI0_MEM_3_SIZE
mdefine_line|#define&t;MV64x60_PCI0_MEM_3_SIZE&t;&t;&t;0x0d0c
DECL|macro|MV64x60_PCI1_MEM_0_SIZE
mdefine_line|#define&t;MV64x60_PCI1_MEM_0_SIZE&t;&t;&t;0x0c88
DECL|macro|MV64x60_PCI1_MEM_1_SIZE
mdefine_line|#define&t;MV64x60_PCI1_MEM_1_SIZE&t;&t;&t;0x0d88
DECL|macro|MV64x60_PCI1_MEM_2_SIZE
mdefine_line|#define&t;MV64x60_PCI1_MEM_2_SIZE&t;&t;&t;0x0c8c
DECL|macro|MV64x60_PCI1_MEM_3_SIZE
mdefine_line|#define&t;MV64x60_PCI1_MEM_3_SIZE&t;&t;&t;0x0d8c
DECL|macro|MV64x60_PCI0_BAR_ENABLE
mdefine_line|#define&t;MV64x60_PCI0_BAR_ENABLE&t;&t;&t;0x0c3c
DECL|macro|MV64x60_PCI1_BAR_ENABLE
mdefine_line|#define&t;MV64x60_PCI1_BAR_ENABLE&t;&t;&t;0x0cbc
DECL|macro|MV64x60_PCI0_PCI_DECODE_CNTL
mdefine_line|#define&t;MV64x60_PCI0_PCI_DECODE_CNTL&t;&t;0x0d3c
DECL|macro|MV64x60_PCI1_PCI_DECODE_CNTL
mdefine_line|#define&t;MV64x60_PCI1_PCI_DECODE_CNTL&t;&t;0x0dbc
DECL|macro|MV64x60_PCI0_SLAVE_MEM_0_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_MEM_0_REMAP&t;&t;0x0c48
DECL|macro|MV64x60_PCI0_SLAVE_MEM_1_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_MEM_1_REMAP&t;&t;0x0d48
DECL|macro|MV64x60_PCI0_SLAVE_MEM_2_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_MEM_2_REMAP&t;&t;0x0c4c
DECL|macro|MV64x60_PCI0_SLAVE_MEM_3_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_MEM_3_REMAP&t;&t;0x0d4c
DECL|macro|MV64x60_PCI0_SLAVE_DEV_0_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_DEV_0_REMAP&t;&t;0x0c50
DECL|macro|MV64x60_PCI0_SLAVE_DEV_1_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_DEV_1_REMAP&t;&t;0x0d50
DECL|macro|MV64x60_PCI0_SLAVE_DEV_2_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_DEV_2_REMAP&t;&t;0x0d58
DECL|macro|MV64x60_PCI0_SLAVE_DEV_3_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_DEV_3_REMAP&t;&t;0x0c54
DECL|macro|MV64x60_PCI0_SLAVE_BOOT_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_BOOT_REMAP&t;&t;0x0d54
DECL|macro|MV64x60_PCI0_SLAVE_P2P_MEM_0_REMAP_LO
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_P2P_MEM_0_REMAP_LO&t;0x0d5c
DECL|macro|MV64x60_PCI0_SLAVE_P2P_MEM_0_REMAP_HI
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_P2P_MEM_0_REMAP_HI&t;0x0d60
DECL|macro|MV64x60_PCI0_SLAVE_P2P_MEM_1_REMAP_LO
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_P2P_MEM_1_REMAP_LO&t;0x0d64
DECL|macro|MV64x60_PCI0_SLAVE_P2P_MEM_1_REMAP_HI
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_P2P_MEM_1_REMAP_HI&t;0x0d68
DECL|macro|MV64x60_PCI0_SLAVE_P2P_IO_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_P2P_IO_REMAP&t;&t;0x0d6c
DECL|macro|MV64x60_PCI0_SLAVE_CPU_REMAP
mdefine_line|#define&t;MV64x60_PCI0_SLAVE_CPU_REMAP&t;&t;0x0d70
DECL|macro|MV64x60_PCI1_SLAVE_MEM_0_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_MEM_0_REMAP&t;&t;0x0cc8
DECL|macro|MV64x60_PCI1_SLAVE_MEM_1_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_MEM_1_REMAP&t;&t;0x0dc8
DECL|macro|MV64x60_PCI1_SLAVE_MEM_2_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_MEM_2_REMAP&t;&t;0x0ccc
DECL|macro|MV64x60_PCI1_SLAVE_MEM_3_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_MEM_3_REMAP&t;&t;0x0dcc
DECL|macro|MV64x60_PCI1_SLAVE_DEV_0_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_DEV_0_REMAP&t;&t;0x0cd0
DECL|macro|MV64x60_PCI1_SLAVE_DEV_1_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_DEV_1_REMAP&t;&t;0x0dd0
DECL|macro|MV64x60_PCI1_SLAVE_DEV_2_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_DEV_2_REMAP&t;&t;0x0dd8
DECL|macro|MV64x60_PCI1_SLAVE_DEV_3_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_DEV_3_REMAP&t;&t;0x0cd4
DECL|macro|MV64x60_PCI1_SLAVE_BOOT_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_BOOT_REMAP&t;&t;0x0dd4
DECL|macro|MV64x60_PCI1_SLAVE_P2P_MEM_0_REMAP_LO
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_P2P_MEM_0_REMAP_LO&t;0x0ddc
DECL|macro|MV64x60_PCI1_SLAVE_P2P_MEM_0_REMAP_HI
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_P2P_MEM_0_REMAP_HI&t;0x0de0
DECL|macro|MV64x60_PCI1_SLAVE_P2P_MEM_1_REMAP_LO
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_P2P_MEM_1_REMAP_LO&t;0x0de4
DECL|macro|MV64x60_PCI1_SLAVE_P2P_MEM_1_REMAP_HI
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_P2P_MEM_1_REMAP_HI&t;0x0de8
DECL|macro|MV64x60_PCI1_SLAVE_P2P_IO_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_P2P_IO_REMAP&t;&t;0x0dec
DECL|macro|MV64x60_PCI1_SLAVE_CPU_REMAP
mdefine_line|#define&t;MV64x60_PCI1_SLAVE_CPU_REMAP&t;&t;0x0df0
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;ENET Controller Interface Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* ENET Controller Window Registers (6 windows) */
DECL|macro|MV64360_ENET2MEM_WINDOWS
mdefine_line|#define&t;MV64360_ENET2MEM_WINDOWS&t;&t;6
DECL|macro|MV64360_ENET2MEM_0_BASE
mdefine_line|#define&t;MV64360_ENET2MEM_0_BASE&t;&t;&t;0x2200
DECL|macro|MV64360_ENET2MEM_0_SIZE
mdefine_line|#define&t;MV64360_ENET2MEM_0_SIZE&t;&t;&t;0x2204
DECL|macro|MV64360_ENET2MEM_1_BASE
mdefine_line|#define&t;MV64360_ENET2MEM_1_BASE&t;&t;&t;0x2208
DECL|macro|MV64360_ENET2MEM_1_SIZE
mdefine_line|#define&t;MV64360_ENET2MEM_1_SIZE&t;&t;&t;0x220c
DECL|macro|MV64360_ENET2MEM_2_BASE
mdefine_line|#define&t;MV64360_ENET2MEM_2_BASE&t;&t;&t;0x2210
DECL|macro|MV64360_ENET2MEM_2_SIZE
mdefine_line|#define&t;MV64360_ENET2MEM_2_SIZE&t;&t;&t;0x2214
DECL|macro|MV64360_ENET2MEM_3_BASE
mdefine_line|#define&t;MV64360_ENET2MEM_3_BASE&t;&t;&t;0x2218
DECL|macro|MV64360_ENET2MEM_3_SIZE
mdefine_line|#define&t;MV64360_ENET2MEM_3_SIZE&t;&t;&t;0x221c
DECL|macro|MV64360_ENET2MEM_4_BASE
mdefine_line|#define&t;MV64360_ENET2MEM_4_BASE&t;&t;&t;0x2220
DECL|macro|MV64360_ENET2MEM_4_SIZE
mdefine_line|#define&t;MV64360_ENET2MEM_4_SIZE&t;&t;&t;0x2224
DECL|macro|MV64360_ENET2MEM_5_BASE
mdefine_line|#define&t;MV64360_ENET2MEM_5_BASE&t;&t;&t;0x2228
DECL|macro|MV64360_ENET2MEM_5_SIZE
mdefine_line|#define&t;MV64360_ENET2MEM_5_SIZE&t;&t;&t;0x222c
DECL|macro|MV64360_ENET2MEM_SNOOP_NONE
mdefine_line|#define&t;MV64360_ENET2MEM_SNOOP_NONE&t;&t;0x00000000
DECL|macro|MV64360_ENET2MEM_SNOOP_WT
mdefine_line|#define&t;MV64360_ENET2MEM_SNOOP_WT&t;&t;0x00001000
DECL|macro|MV64360_ENET2MEM_SNOOP_WB
mdefine_line|#define&t;MV64360_ENET2MEM_SNOOP_WB&t;&t;0x00002000
DECL|macro|MV64360_ENET2MEM_BAR_ENABLE
mdefine_line|#define&t;MV64360_ENET2MEM_BAR_ENABLE&t;&t;0x2290
DECL|macro|MV64360_ENET2MEM_ACC_PROT_0
mdefine_line|#define&t;MV64360_ENET2MEM_ACC_PROT_0&t;&t;0x2294
DECL|macro|MV64360_ENET2MEM_ACC_PROT_1
mdefine_line|#define&t;MV64360_ENET2MEM_ACC_PROT_1&t;&t;0x2298
DECL|macro|MV64360_ENET2MEM_ACC_PROT_2
mdefine_line|#define&t;MV64360_ENET2MEM_ACC_PROT_2&t;&t;0x229c
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;MPSC Controller Interface Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* MPSC Controller Window Registers (4 windows) */
DECL|macro|MV64360_MPSC2MEM_WINDOWS
mdefine_line|#define&t;MV64360_MPSC2MEM_WINDOWS&t;&t;4
DECL|macro|MV64360_MPSC2MEM_0_BASE
mdefine_line|#define&t;MV64360_MPSC2MEM_0_BASE&t;&t;&t;0xf200
DECL|macro|MV64360_MPSC2MEM_0_SIZE
mdefine_line|#define&t;MV64360_MPSC2MEM_0_SIZE&t;&t;&t;0xf204
DECL|macro|MV64360_MPSC2MEM_1_BASE
mdefine_line|#define&t;MV64360_MPSC2MEM_1_BASE&t;&t;&t;0xf208
DECL|macro|MV64360_MPSC2MEM_1_SIZE
mdefine_line|#define&t;MV64360_MPSC2MEM_1_SIZE&t;&t;&t;0xf20c
DECL|macro|MV64360_MPSC2MEM_2_BASE
mdefine_line|#define&t;MV64360_MPSC2MEM_2_BASE&t;&t;&t;0xf210
DECL|macro|MV64360_MPSC2MEM_2_SIZE
mdefine_line|#define&t;MV64360_MPSC2MEM_2_SIZE&t;&t;&t;0xf214
DECL|macro|MV64360_MPSC2MEM_3_BASE
mdefine_line|#define&t;MV64360_MPSC2MEM_3_BASE&t;&t;&t;0xf218
DECL|macro|MV64360_MPSC2MEM_3_SIZE
mdefine_line|#define&t;MV64360_MPSC2MEM_3_SIZE&t;&t;&t;0xf21c
DECL|macro|MV64360_MPSC_0_REMAP
mdefine_line|#define MV64360_MPSC_0_REMAP&t;&t;&t;0xf240
DECL|macro|MV64360_MPSC_1_REMAP
mdefine_line|#define MV64360_MPSC_1_REMAP&t;&t;&t;0xf244
DECL|macro|MV64360_MPSC2MEM_SNOOP_NONE
mdefine_line|#define&t;MV64360_MPSC2MEM_SNOOP_NONE&t;&t;0x00000000
DECL|macro|MV64360_MPSC2MEM_SNOOP_WT
mdefine_line|#define&t;MV64360_MPSC2MEM_SNOOP_WT&t;&t;0x00001000
DECL|macro|MV64360_MPSC2MEM_SNOOP_WB
mdefine_line|#define&t;MV64360_MPSC2MEM_SNOOP_WB&t;&t;0x00002000
DECL|macro|MV64360_MPSC2MEM_BAR_ENABLE
mdefine_line|#define&t;MV64360_MPSC2MEM_BAR_ENABLE&t;&t;0xf250
DECL|macro|MV64360_MPSC2MEM_ACC_PROT_0
mdefine_line|#define&t;MV64360_MPSC2MEM_ACC_PROT_0&t;&t;0xf254
DECL|macro|MV64360_MPSC2MEM_ACC_PROT_1
mdefine_line|#define&t;MV64360_MPSC2MEM_ACC_PROT_1&t;&t;0xf258
DECL|macro|MV64360_MPSC2REGS_BASE
mdefine_line|#define&t;MV64360_MPSC2REGS_BASE&t;&t;&t;0xf25c
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Timer/Counter Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|MV64x60_TIMR_CNTR_0
mdefine_line|#define&t;MV64x60_TIMR_CNTR_0&t;&t;&t;0x0850
DECL|macro|MV64x60_TIMR_CNTR_1
mdefine_line|#define&t;MV64x60_TIMR_CNTR_1&t;&t;&t;0x0854
DECL|macro|MV64x60_TIMR_CNTR_2
mdefine_line|#define&t;MV64x60_TIMR_CNTR_2&t;&t;&t;0x0858
DECL|macro|MV64x60_TIMR_CNTR_3
mdefine_line|#define&t;MV64x60_TIMR_CNTR_3&t;&t;&t;0x085c
DECL|macro|MV64x60_TIMR_CNTR_0_3_CNTL
mdefine_line|#define&t;MV64x60_TIMR_CNTR_0_3_CNTL&t;&t;0x0864
DECL|macro|MV64x60_TIMR_CNTR_0_3_INTR_CAUSE
mdefine_line|#define&t;MV64x60_TIMR_CNTR_0_3_INTR_CAUSE&t;0x0868
DECL|macro|MV64x60_TIMR_CNTR_0_3_INTR_MASK
mdefine_line|#define&t;MV64x60_TIMR_CNTR_0_3_INTR_MASK&t;&t;0x086c
DECL|macro|GT64260_TIMR_CNTR_4
mdefine_line|#define&t;GT64260_TIMR_CNTR_4&t;&t;&t;0x0950
DECL|macro|GT64260_TIMR_CNTR_5
mdefine_line|#define&t;GT64260_TIMR_CNTR_5&t;&t;&t;0x0954
DECL|macro|GT64260_TIMR_CNTR_6
mdefine_line|#define&t;GT64260_TIMR_CNTR_6&t;&t;&t;0x0958
DECL|macro|GT64260_TIMR_CNTR_7
mdefine_line|#define&t;GT64260_TIMR_CNTR_7&t;&t;&t;0x095c
DECL|macro|GT64260_TIMR_CNTR_4_7_CNTL
mdefine_line|#define&t;GT64260_TIMR_CNTR_4_7_CNTL&t;&t;0x0964
DECL|macro|GT64260_TIMR_CNTR_4_7_INTR_CAUSE
mdefine_line|#define&t;GT64260_TIMR_CNTR_4_7_INTR_CAUSE&t;0x0968
DECL|macro|GT64260_TIMR_CNTR_4_7_INTR_MASK
mdefine_line|#define&t;GT64260_TIMR_CNTR_4_7_INTR_MASK&t;&t;0x096c
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Communications Controller&n; *&n; *****************************************************************************&n; */
DECL|macro|GT64260_SER_INIT_PCI_ADDR_HI
mdefine_line|#define&t;GT64260_SER_INIT_PCI_ADDR_HI&t;&t;0xf320
DECL|macro|GT64260_SER_INIT_LAST_DATA
mdefine_line|#define&t;GT64260_SER_INIT_LAST_DATA&t;&t;0xf324
DECL|macro|GT64260_SER_INIT_CONTROL
mdefine_line|#define&t;GT64260_SER_INIT_CONTROL&t;&t;0xf328
DECL|macro|GT64260_SER_INIT_STATUS
mdefine_line|#define&t;GT64260_SER_INIT_STATUS&t;&t;&t;0xf32c
DECL|macro|MV64x60_COMM_ARBITER_CNTL
mdefine_line|#define&t;MV64x60_COMM_ARBITER_CNTL&t;&t;0xf300
DECL|macro|MV64x60_COMM_CONFIG
mdefine_line|#define&t;MV64x60_COMM_CONFIG&t;&t;&t;0xb40c
DECL|macro|MV64x60_COMM_XBAR_TO
mdefine_line|#define&t;MV64x60_COMM_XBAR_TO&t;&t;&t;0xf304
DECL|macro|MV64x60_COMM_INTR_CAUSE
mdefine_line|#define&t;MV64x60_COMM_INTR_CAUSE&t;&t;&t;0xf310
DECL|macro|MV64x60_COMM_INTR_MASK
mdefine_line|#define&t;MV64x60_COMM_INTR_MASK&t;&t;&t;0xf314
DECL|macro|MV64x60_COMM_ERR_ADDR
mdefine_line|#define&t;MV64x60_COMM_ERR_ADDR&t;&t;&t;0xf318
DECL|macro|MV64360_COMM_ARBITER_CNTL
mdefine_line|#define MV64360_COMM_ARBITER_CNTL&t;&t;0xf300
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;IDMA Controller Interface Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* IDMA Controller Window Registers (8 windows) */
DECL|macro|MV64360_IDMA2MEM_WINDOWS
mdefine_line|#define&t;MV64360_IDMA2MEM_WINDOWS&t;&t;8
DECL|macro|MV64360_IDMA2MEM_0_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_0_BASE&t;&t;&t;0x0a00
DECL|macro|MV64360_IDMA2MEM_0_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_0_SIZE&t;&t;&t;0x0a04
DECL|macro|MV64360_IDMA2MEM_1_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_1_BASE&t;&t;&t;0x0a08
DECL|macro|MV64360_IDMA2MEM_1_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_1_SIZE&t;&t;&t;0x0a0c
DECL|macro|MV64360_IDMA2MEM_2_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_2_BASE&t;&t;&t;0x0a10
DECL|macro|MV64360_IDMA2MEM_2_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_2_SIZE&t;&t;&t;0x0a14
DECL|macro|MV64360_IDMA2MEM_3_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_3_BASE&t;&t;&t;0x0a18
DECL|macro|MV64360_IDMA2MEM_3_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_3_SIZE&t;&t;&t;0x0a1c
DECL|macro|MV64360_IDMA2MEM_4_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_4_BASE&t;&t;&t;0x0a20
DECL|macro|MV64360_IDMA2MEM_4_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_4_SIZE&t;&t;&t;0x0a24
DECL|macro|MV64360_IDMA2MEM_5_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_5_BASE&t;&t;&t;0x0a28
DECL|macro|MV64360_IDMA2MEM_5_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_5_SIZE&t;&t;&t;0x0a2c
DECL|macro|MV64360_IDMA2MEM_6_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_6_BASE&t;&t;&t;0x0a30
DECL|macro|MV64360_IDMA2MEM_6_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_6_SIZE&t;&t;&t;0x0a34
DECL|macro|MV64360_IDMA2MEM_7_BASE
mdefine_line|#define&t;MV64360_IDMA2MEM_7_BASE&t;&t;&t;0x0a38
DECL|macro|MV64360_IDMA2MEM_7_SIZE
mdefine_line|#define&t;MV64360_IDMA2MEM_7_SIZE&t;&t;&t;0x0a3c
DECL|macro|MV64360_IDMA2MEM_SNOOP_NONE
mdefine_line|#define&t;MV64360_IDMA2MEM_SNOOP_NONE&t;&t;0x00000000
DECL|macro|MV64360_IDMA2MEM_SNOOP_WT
mdefine_line|#define&t;MV64360_IDMA2MEM_SNOOP_WT&t;&t;0x00001000
DECL|macro|MV64360_IDMA2MEM_SNOOP_WB
mdefine_line|#define&t;MV64360_IDMA2MEM_SNOOP_WB&t;&t;0x00002000
DECL|macro|MV64360_IDMA2MEM_BAR_ENABLE
mdefine_line|#define&t;MV64360_IDMA2MEM_BAR_ENABLE&t;&t;0x0a80
DECL|macro|MV64360_IDMA2MEM_ACC_PROT_0
mdefine_line|#define&t;MV64360_IDMA2MEM_ACC_PROT_0&t;&t;0x0a70
DECL|macro|MV64360_IDMA2MEM_ACC_PROT_1
mdefine_line|#define&t;MV64360_IDMA2MEM_ACC_PROT_1&t;&t;0x0a74
DECL|macro|MV64360_IDMA2MEM_ACC_PROT_2
mdefine_line|#define&t;MV64360_IDMA2MEM_ACC_PROT_2&t;&t;0x0a78
DECL|macro|MV64360_IDMA2MEM_ACC_PROT_3
mdefine_line|#define&t;MV64360_IDMA2MEM_ACC_PROT_3&t;&t;0x0a7c
DECL|macro|MV64x60_IDMA_0_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_0_OFFSET&t;&t;&t;0x0800
DECL|macro|MV64x60_IDMA_1_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_1_OFFSET&t;&t;&t;0x0804
DECL|macro|MV64x60_IDMA_2_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_2_OFFSET&t;&t;&t;0x0808
DECL|macro|MV64x60_IDMA_3_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_3_OFFSET&t;&t;&t;0x080c
DECL|macro|MV64x60_IDMA_4_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_4_OFFSET&t;&t;&t;0x0900
DECL|macro|MV64x60_IDMA_5_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_5_OFFSET&t;&t;&t;0x0904
DECL|macro|MV64x60_IDMA_6_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_6_OFFSET&t;&t;&t;0x0908
DECL|macro|MV64x60_IDMA_7_OFFSET
mdefine_line|#define&t;MV64x60_IDMA_7_OFFSET&t;&t;&t;0x090c
DECL|macro|MV64x60_IDMA_BYTE_COUNT
mdefine_line|#define&t;MV64x60_IDMA_BYTE_COUNT&t;&t;&t;(0x0800 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_SRC_ADDR
mdefine_line|#define&t;MV64x60_IDMA_SRC_ADDR&t;&t;&t;(0x0810 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_DST_ADDR
mdefine_line|#define&t;MV64x60_IDMA_DST_ADDR&t;&t;&t;(0x0820 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_NEXT_DESC
mdefine_line|#define&t;MV64x60_IDMA_NEXT_DESC&t;&t;&t;(0x0830 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_CUR_DESC
mdefine_line|#define&t;MV64x60_IDMA_CUR_DESC&t;&t;&t;(0x0870 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_SRC_PCI_ADDR_HI
mdefine_line|#define&t;MV64x60_IDMA_SRC_PCI_ADDR_HI&t;&t;(0x0890 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_DST_PCI_ADDR_HI
mdefine_line|#define&t;MV64x60_IDMA_DST_PCI_ADDR_HI&t;&t;(0x08a0 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_NEXT_DESC_PCI_ADDR_HI
mdefine_line|#define&t;MV64x60_IDMA_NEXT_DESC_PCI_ADDR_HI&t;(0x08b0 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_CONTROL_LO
mdefine_line|#define&t;MV64x60_IDMA_CONTROL_LO&t;&t;&t;(0x0840 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_CONTROL_HI
mdefine_line|#define&t;MV64x60_IDMA_CONTROL_HI&t;&t;&t;(0x0880 - MV64x60_IDMA_0_OFFSET)
DECL|macro|MV64x60_IDMA_0_3_ARBITER_CNTL
mdefine_line|#define&t;MV64x60_IDMA_0_3_ARBITER_CNTL&t;&t;0x0860
DECL|macro|MV64x60_IDMA_4_7_ARBITER_CNTL
mdefine_line|#define&t;MV64x60_IDMA_4_7_ARBITER_CNTL&t;&t;0x0960
DECL|macro|MV64x60_IDMA_0_3_XBAR_TO
mdefine_line|#define&t;MV64x60_IDMA_0_3_XBAR_TO&t;&t;0x08d0
DECL|macro|MV64x60_IDMA_4_7_XBAR_TO
mdefine_line|#define&t;MV64x60_IDMA_4_7_XBAR_TO&t;&t;0x09d0
DECL|macro|MV64x60_IDMA_0_3_INTR_CAUSE
mdefine_line|#define&t;MV64x60_IDMA_0_3_INTR_CAUSE&t;&t;0x08c0
DECL|macro|MV64x60_IDMA_0_3_INTR_MASK
mdefine_line|#define&t;MV64x60_IDMA_0_3_INTR_MASK&t;&t;0x08c4
DECL|macro|MV64x60_IDMA_0_3_ERROR_ADDR
mdefine_line|#define&t;MV64x60_IDMA_0_3_ERROR_ADDR&t;&t;0x08c8
DECL|macro|MV64x60_IDMA_0_3_ERROR_SELECT
mdefine_line|#define&t;MV64x60_IDMA_0_3_ERROR_SELECT&t;&t;0x08cc
DECL|macro|MV64x60_IDMA_4_7_INTR_CAUSE
mdefine_line|#define&t;MV64x60_IDMA_4_7_INTR_CAUSE&t;&t;0x09c0
DECL|macro|MV64x60_IDMA_4_7_INTR_MASK
mdefine_line|#define&t;MV64x60_IDMA_4_7_INTR_MASK&t;&t;0x09c4
DECL|macro|MV64x60_IDMA_4_7_ERROR_ADDR
mdefine_line|#define&t;MV64x60_IDMA_4_7_ERROR_ADDR&t;&t;0x09c8
DECL|macro|MV64x60_IDMA_4_7_ERROR_SELECT
mdefine_line|#define&t;MV64x60_IDMA_4_7_ERROR_SELECT&t;&t;0x09cc
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Watchdog Timer Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|MV64x60_WDT_WDC
mdefine_line|#define&t;MV64x60_WDT_WDC&t;&t;&t;&t;0xb410
DECL|macro|MV64x60_WDT_WDV
mdefine_line|#define&t;MV64x60_WDT_WDV&t;&t;&t;&t;0xb414
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t; General Purpose Pins Controller Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|MV64x60_GPP_IO_CNTL
mdefine_line|#define&t;MV64x60_GPP_IO_CNTL&t;&t;&t;0xf100
DECL|macro|MV64x60_GPP_LEVEL_CNTL
mdefine_line|#define&t;MV64x60_GPP_LEVEL_CNTL&t;&t;&t;0xf110
DECL|macro|MV64x60_GPP_VALUE
mdefine_line|#define&t;MV64x60_GPP_VALUE&t;&t;&t;0xf104
DECL|macro|MV64x60_GPP_INTR_CAUSE
mdefine_line|#define&t;MV64x60_GPP_INTR_CAUSE&t;&t;&t;0xf108
DECL|macro|MV64x60_GPP_INTR_MASK
mdefine_line|#define&t;MV64x60_GPP_INTR_MASK&t;&t;&t;0xf10c
DECL|macro|MV64x60_GPP_VALUE_SET
mdefine_line|#define&t;MV64x60_GPP_VALUE_SET&t;&t;&t;0xf118
DECL|macro|MV64x60_GPP_VALUE_CLR
mdefine_line|#define&t;MV64x60_GPP_VALUE_CLR&t;&t;&t;0xf11c
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Multi-Purpose Pins Controller Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|MV64x60_MPP_CNTL_0
mdefine_line|#define&t;MV64x60_MPP_CNTL_0&t;&t;&t;0xf000
DECL|macro|MV64x60_MPP_CNTL_1
mdefine_line|#define&t;MV64x60_MPP_CNTL_1&t;&t;&t;0xf004
DECL|macro|MV64x60_MPP_CNTL_2
mdefine_line|#define&t;MV64x60_MPP_CNTL_2&t;&t;&t;0xf008
DECL|macro|MV64x60_MPP_CNTL_3
mdefine_line|#define&t;MV64x60_MPP_CNTL_3&t;&t;&t;0xf00c
DECL|macro|GT64260_MPP_SERIAL_PORTS_MULTIPLEX
mdefine_line|#define&t;GT64260_MPP_SERIAL_PORTS_MULTIPLEX&t;0xf010
DECL|macro|MV64x60_ETH_BAR_GAP
mdefine_line|#define MV64x60_ETH_BAR_GAP&t;&t;&t;0x8
DECL|macro|MV64x60_ETH_SIZE_REG_GAP
mdefine_line|#define MV64x60_ETH_SIZE_REG_GAP&t;&t;0x8
DECL|macro|MV64x60_ETH_HIGH_ADDR_REMAP_REG_GAP
mdefine_line|#define MV64x60_ETH_HIGH_ADDR_REMAP_REG_GAP&t;0x4
DECL|macro|MV64x60_ETH_PORT_ACCESS_CTRL_GAP
mdefine_line|#define MV64x60_ETH_PORT_ACCESS_CTRL_GAP&t;0x4
DECL|macro|MV64x60_EBAR_ATTR_DRAM_CS0
mdefine_line|#define MV64x60_EBAR_ATTR_DRAM_CS0&t;&t;0x00000E00
DECL|macro|MV64x60_EBAR_ATTR_DRAM_CS1
mdefine_line|#define MV64x60_EBAR_ATTR_DRAM_CS1&t;&t;0x00000D00
DECL|macro|MV64x60_EBAR_ATTR_DRAM_CS2
mdefine_line|#define MV64x60_EBAR_ATTR_DRAM_CS2&t;&t;0x00000B00
DECL|macro|MV64x60_EBAR_ATTR_DRAM_CS3
mdefine_line|#define MV64x60_EBAR_ATTR_DRAM_CS3&t;&t;0x00000700
DECL|macro|MV64x60_EBAR_ATTR_CBS_SRAM_BLOCK0
mdefine_line|#define MV64x60_EBAR_ATTR_CBS_SRAM_BLOCK0&t;0x00000000
DECL|macro|MV64x60_EBAR_ATTR_CBS_SRAM_BLOCK1
mdefine_line|#define MV64x60_EBAR_ATTR_CBS_SRAM_BLOCK1&t;0x00000100
DECL|macro|MV64x60_EBAR_ATTR_CBS_SRAM
mdefine_line|#define MV64x60_EBAR_ATTR_CBS_SRAM&t;&t;0x00000000
DECL|macro|MV64x60_EBAR_ATTR_CBS_CPU_BUS
mdefine_line|#define MV64x60_EBAR_ATTR_CBS_CPU_BUS&t;&t;0x00000800
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Interrupt Controller Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|GT64260_IC_OFFSET
mdefine_line|#define&t;GT64260_IC_OFFSET&t;&t;&t;0x0c18
DECL|macro|GT64260_IC_MAIN_CAUSE_LO
mdefine_line|#define&t;GT64260_IC_MAIN_CAUSE_LO&t;&t;0x0c18
DECL|macro|GT64260_IC_MAIN_CAUSE_HI
mdefine_line|#define&t;GT64260_IC_MAIN_CAUSE_HI&t;&t;0x0c68
DECL|macro|GT64260_IC_CPU_INTR_MASK_LO
mdefine_line|#define&t;GT64260_IC_CPU_INTR_MASK_LO&t;&t;0x0c1c
DECL|macro|GT64260_IC_CPU_INTR_MASK_HI
mdefine_line|#define&t;GT64260_IC_CPU_INTR_MASK_HI&t;&t;0x0c6c
DECL|macro|GT64260_IC_CPU_SELECT_CAUSE
mdefine_line|#define&t;GT64260_IC_CPU_SELECT_CAUSE&t;&t;0x0c70
DECL|macro|GT64260_IC_PCI0_INTR_MASK_LO
mdefine_line|#define&t;GT64260_IC_PCI0_INTR_MASK_LO&t;&t;0x0c24
DECL|macro|GT64260_IC_PCI0_INTR_MASK_HI
mdefine_line|#define&t;GT64260_IC_PCI0_INTR_MASK_HI&t;&t;0x0c64
DECL|macro|GT64260_IC_PCI0_SELECT_CAUSE
mdefine_line|#define&t;GT64260_IC_PCI0_SELECT_CAUSE&t;&t;0x0c74
DECL|macro|GT64260_IC_PCI1_INTR_MASK_LO
mdefine_line|#define&t;GT64260_IC_PCI1_INTR_MASK_LO&t;&t;0x0ca4
DECL|macro|GT64260_IC_PCI1_INTR_MASK_HI
mdefine_line|#define&t;GT64260_IC_PCI1_INTR_MASK_HI&t;&t;0x0ce4
DECL|macro|GT64260_IC_PCI1_SELECT_CAUSE
mdefine_line|#define&t;GT64260_IC_PCI1_SELECT_CAUSE&t;&t;0x0cf4
DECL|macro|GT64260_IC_CPU_INT_0_MASK
mdefine_line|#define&t;GT64260_IC_CPU_INT_0_MASK&t;&t;0x0e60
DECL|macro|GT64260_IC_CPU_INT_1_MASK
mdefine_line|#define&t;GT64260_IC_CPU_INT_1_MASK&t;&t;0x0e64
DECL|macro|GT64260_IC_CPU_INT_2_MASK
mdefine_line|#define&t;GT64260_IC_CPU_INT_2_MASK&t;&t;0x0e68
DECL|macro|GT64260_IC_CPU_INT_3_MASK
mdefine_line|#define&t;GT64260_IC_CPU_INT_3_MASK&t;&t;0x0e6c
DECL|macro|MV64360_IC_OFFSET
mdefine_line|#define&t;MV64360_IC_OFFSET&t;&t;&t;0x0000
DECL|macro|MV64360_IC_MAIN_CAUSE_LO
mdefine_line|#define&t;MV64360_IC_MAIN_CAUSE_LO&t;&t;0x0004
DECL|macro|MV64360_IC_MAIN_CAUSE_HI
mdefine_line|#define&t;MV64360_IC_MAIN_CAUSE_HI&t;&t;0x000c
DECL|macro|MV64360_IC_CPU0_INTR_MASK_LO
mdefine_line|#define&t;MV64360_IC_CPU0_INTR_MASK_LO&t;&t;0x0014
DECL|macro|MV64360_IC_CPU0_INTR_MASK_HI
mdefine_line|#define&t;MV64360_IC_CPU0_INTR_MASK_HI&t;&t;0x001c
DECL|macro|MV64360_IC_CPU0_SELECT_CAUSE
mdefine_line|#define&t;MV64360_IC_CPU0_SELECT_CAUSE&t;&t;0x0024
DECL|macro|MV64360_IC_CPU1_INTR_MASK_LO
mdefine_line|#define&t;MV64360_IC_CPU1_INTR_MASK_LO&t;&t;0x0034
DECL|macro|MV64360_IC_CPU1_INTR_MASK_HI
mdefine_line|#define&t;MV64360_IC_CPU1_INTR_MASK_HI&t;&t;0x003c
DECL|macro|MV64360_IC_CPU1_SELECT_CAUSE
mdefine_line|#define&t;MV64360_IC_CPU1_SELECT_CAUSE&t;&t;0x0044
DECL|macro|MV64360_IC_INT0_MASK_LO
mdefine_line|#define&t;MV64360_IC_INT0_MASK_LO&t;&t;&t;0x0054
DECL|macro|MV64360_IC_INT0_MASK_HI
mdefine_line|#define&t;MV64360_IC_INT0_MASK_HI&t;&t;&t;0x005c
DECL|macro|MV64360_IC_INT0_SELECT_CAUSE
mdefine_line|#define&t;MV64360_IC_INT0_SELECT_CAUSE&t;&t;0x0064
DECL|macro|MV64360_IC_INT1_MASK_LO
mdefine_line|#define&t;MV64360_IC_INT1_MASK_LO&t;&t;&t;0x0074
DECL|macro|MV64360_IC_INT1_MASK_HI
mdefine_line|#define&t;MV64360_IC_INT1_MASK_HI&t;&t;&t;0x007c
DECL|macro|MV64360_IC_INT1_SELECT_CAUSE
mdefine_line|#define&t;MV64360_IC_INT1_SELECT_CAUSE&t;&t;0x0084
macro_line|#endif /* __ASMPPC_MV64x60_DEFS_H */
eof
