multiline_comment|/*&n; * arch/ppc/platforms/radstone_ppc7d.h&n; *&n; * Board definitions for the Radstone PPC7D boards.&n; *&n; * Author: James Chapman &lt;jchapman@katalix.com&gt;&n; *&n; * Based on code done by Rabeeh Khoury - rabeeh@galileo.co.il&n; * Based on code done by - Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * The MV64360 has 2 PCI buses each with 1 window from the CPU bus to&n; * PCI I/O space and 4 windows from the CPU bus to PCI MEM space.&n; * We&squot;ll only use one PCI MEM window on each PCI bus.&n; *&n; * This is the CPU physical memory map (windows must be at least 1MB&n; * and start on a boundary that is a multiple of the window size):&n; *&n; *    0xff800000-0xffffffff      - Boot window&n; *    0xff000000-0xff000fff&t; - AFIX registers (DevCS2)&n; *    0xfef00000-0xfef0ffff      - Internal MV64x60 registers&n; *    0xfef40000-0xfef7ffff      - Internal SRAM&n; *    0xfef00000-0xfef0ffff      - MV64360 Registers&n; *    0x70000000-0x7fffffff      - soldered flash (DevCS3)&n; *    0xe8000000-0xe9ffffff      - PCI I/O&n; *    0x80000000-0xbfffffff      - PCI MEM&n; */
macro_line|#ifndef __PPC_PLATFORMS_PPC7D_H
DECL|macro|__PPC_PLATFORMS_PPC7D_H
mdefine_line|#define __PPC_PLATFORMS_PPC7D_H
macro_line|#include &lt;asm/ppcboot.h&gt;
multiline_comment|/*****************************************************************************&n; * CPU Physical Memory Map setup.&n; *****************************************************************************/
DECL|macro|PPC7D_BOOT_WINDOW_BASE
mdefine_line|#define PPC7D_BOOT_WINDOW_BASE&t;&t;&t;0xff800000
DECL|macro|PPC7D_AFIX_REG_BASE
mdefine_line|#define PPC7D_AFIX_REG_BASE&t;&t;&t;0xff000000
DECL|macro|PPC7D_INTERNAL_SRAM_BASE
mdefine_line|#define PPC7D_INTERNAL_SRAM_BASE&t;&t;0xfef40000
DECL|macro|PPC7D_FLASH_BASE
mdefine_line|#define PPC7D_FLASH_BASE&t;&t;&t;0x70000000
DECL|macro|PPC7D_BOOT_WINDOW_SIZE_ACTUAL
mdefine_line|#define PPC7D_BOOT_WINDOW_SIZE_ACTUAL&t;&t;0x00800000 /* 8MB */
DECL|macro|PPC7D_FLASH_SIZE_ACTUAL
mdefine_line|#define PPC7D_FLASH_SIZE_ACTUAL&t;&t;&t;0x10000000 /* 256MB */
DECL|macro|PPC7D_BOOT_WINDOW_SIZE
mdefine_line|#define PPC7D_BOOT_WINDOW_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;PPC7D_BOOT_WINDOW_SIZE_ACTUAL)
DECL|macro|PPC7D_FLASH_SIZE
mdefine_line|#define PPC7D_FLASH_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;PPC7D_FLASH_SIZE_ACTUAL)
DECL|macro|PPC7D_AFIX_REG_SIZE
mdefine_line|#define PPC7D_AFIX_REG_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN, 0xff)
DECL|macro|PPC7D_PCI0_MEM0_START_PROC_ADDR
mdefine_line|#define PPC7D_PCI0_MEM0_START_PROC_ADDR        0x80000000UL
DECL|macro|PPC7D_PCI0_MEM0_START_PCI_HI_ADDR
mdefine_line|#define PPC7D_PCI0_MEM0_START_PCI_HI_ADDR      0x00000000UL
DECL|macro|PPC7D_PCI0_MEM0_START_PCI_LO_ADDR
mdefine_line|#define PPC7D_PCI0_MEM0_START_PCI_LO_ADDR      0x80000000UL
DECL|macro|PPC7D_PCI0_MEM0_SIZE
mdefine_line|#define PPC7D_PCI0_MEM0_SIZE                   0x20000000UL
DECL|macro|PPC7D_PCI0_MEM1_START_PROC_ADDR
mdefine_line|#define PPC7D_PCI0_MEM1_START_PROC_ADDR        0xe8010000UL
DECL|macro|PPC7D_PCI0_MEM1_START_PCI_HI_ADDR
mdefine_line|#define PPC7D_PCI0_MEM1_START_PCI_HI_ADDR      0x00000000UL
DECL|macro|PPC7D_PCI0_MEM1_START_PCI_LO_ADDR
mdefine_line|#define PPC7D_PCI0_MEM1_START_PCI_LO_ADDR      0x00000000UL
DECL|macro|PPC7D_PCI0_MEM1_SIZE
mdefine_line|#define PPC7D_PCI0_MEM1_SIZE                   0x000f0000UL
DECL|macro|PPC7D_PCI0_IO_START_PROC_ADDR
mdefine_line|#define PPC7D_PCI0_IO_START_PROC_ADDR          0xe8000000UL
DECL|macro|PPC7D_PCI0_IO_START_PCI_ADDR
mdefine_line|#define PPC7D_PCI0_IO_START_PCI_ADDR           0x00000000UL
DECL|macro|PPC7D_PCI0_IO_SIZE
mdefine_line|#define PPC7D_PCI0_IO_SIZE                     0x00010000UL
DECL|macro|PPC7D_PCI1_MEM0_START_PROC_ADDR
mdefine_line|#define PPC7D_PCI1_MEM0_START_PROC_ADDR        0xa0000000UL
DECL|macro|PPC7D_PCI1_MEM0_START_PCI_HI_ADDR
mdefine_line|#define PPC7D_PCI1_MEM0_START_PCI_HI_ADDR      0x00000000UL
DECL|macro|PPC7D_PCI1_MEM0_START_PCI_LO_ADDR
mdefine_line|#define PPC7D_PCI1_MEM0_START_PCI_LO_ADDR      0xa0000000UL
DECL|macro|PPC7D_PCI1_MEM0_SIZE
mdefine_line|#define PPC7D_PCI1_MEM0_SIZE                   0x20000000UL
DECL|macro|PPC7D_PCI1_MEM1_START_PROC_ADDR
mdefine_line|#define PPC7D_PCI1_MEM1_START_PROC_ADDR        0xe9800000UL
DECL|macro|PPC7D_PCI1_MEM1_START_PCI_HI_ADDR
mdefine_line|#define PPC7D_PCI1_MEM1_START_PCI_HI_ADDR      0x00000000UL
DECL|macro|PPC7D_PCI1_MEM1_START_PCI_LO_ADDR
mdefine_line|#define PPC7D_PCI1_MEM1_START_PCI_LO_ADDR      0x00000000UL
DECL|macro|PPC7D_PCI1_MEM1_SIZE
mdefine_line|#define PPC7D_PCI1_MEM1_SIZE                   0x00800000UL
DECL|macro|PPC7D_PCI1_IO_START_PROC_ADDR
mdefine_line|#define PPC7D_PCI1_IO_START_PROC_ADDR          0xe9000000UL
DECL|macro|PPC7D_PCI1_IO_START_PCI_ADDR
mdefine_line|#define PPC7D_PCI1_IO_START_PCI_ADDR           0x00000000UL
DECL|macro|PPC7D_PCI1_IO_SIZE
mdefine_line|#define PPC7D_PCI1_IO_SIZE                     0x00010000UL
DECL|macro|PPC7D_DEFAULT_BAUD
mdefine_line|#define&t;PPC7D_DEFAULT_BAUD&t;&t;&t;9600
DECL|macro|PPC7D_MPSC_CLK_SRC
mdefine_line|#define&t;PPC7D_MPSC_CLK_SRC&t;&t;&t;8&t;  /* TCLK */
DECL|macro|PPC7D_MPSC_CLK_FREQ
mdefine_line|#define&t;PPC7D_MPSC_CLK_FREQ&t;&t;&t;133333333 /* 133.3333... MHz */
DECL|macro|PPC7D_ETH0_PHY_ADDR
mdefine_line|#define&t;PPC7D_ETH0_PHY_ADDR&t;&t;&t;8
DECL|macro|PPC7D_ETH1_PHY_ADDR
mdefine_line|#define&t;PPC7D_ETH1_PHY_ADDR&t;&t;&t;9
DECL|macro|PPC7D_ETH2_PHY_ADDR
mdefine_line|#define&t;PPC7D_ETH2_PHY_ADDR&t;&t;&t;0
DECL|macro|PPC7D_ETH_TX_QUEUE_SIZE
mdefine_line|#define PPC7D_ETH_TX_QUEUE_SIZE&t;&t;&t;400
DECL|macro|PPC7D_ETH_RX_QUEUE_SIZE
mdefine_line|#define PPC7D_ETH_RX_QUEUE_SIZE&t;&t;&t;400
DECL|macro|PPC7D_ETH_PORT_CONFIG_VALUE
mdefine_line|#define&t;PPC7D_ETH_PORT_CONFIG_VALUE&t;&t;&t;&bslash;&n;&t;MV64340_ETH_UNICAST_NORMAL_MODE&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DEFAULT_RX_QUEUE_0&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DEFAULT_RX_ARP_QUEUE_0&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_RECEIVE_BC_IF_NOT_IP_OR_ARP&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_RECEIVE_BC_IF_IP&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_RECEIVE_BC_IF_ARP&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_CAPTURE_TCP_FRAMES_DIS&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_CAPTURE_UDP_FRAMES_DIS&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DEFAULT_RX_TCP_QUEUE_0&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DEFAULT_RX_UDP_QUEUE_0&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DEFAULT_RX_BPDU_QUEUE_0
DECL|macro|PPC7D_ETH_PORT_CONFIG_EXTEND_VALUE
mdefine_line|#define&t;PPC7D_ETH_PORT_CONFIG_EXTEND_VALUE&t;&t;&bslash;&n;&t;MV64340_ETH_SPAN_BPDU_PACKETS_AS_NORMAL&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_PARTITION_DISABLE
DECL|macro|GT_ETH_IPG_INT_RX
mdefine_line|#define&t;GT_ETH_IPG_INT_RX(value)&t;&t;&t;&bslash;&n;&t;((value &amp; 0x3fff) &lt;&lt; 8)
DECL|macro|PPC7D_ETH_PORT_SDMA_CONFIG_VALUE
mdefine_line|#define&t;PPC7D_ETH_PORT_SDMA_CONFIG_VALUE&t;&t;&bslash;&n;&t;MV64340_ETH_RX_BURST_SIZE_4_64BIT&t;&t;|&t;&bslash;&n;&t;GT_ETH_IPG_INT_RX(0)&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_TX_BURST_SIZE_4_64BIT
DECL|macro|PPC7D_ETH_PORT_SERIAL_CONTROL_VALUE
mdefine_line|#define&t;PPC7D_ETH_PORT_SERIAL_CONTROL_VALUE&t;&t;&bslash;&n;&t;MV64340_ETH_ENABLE_AUTO_NEG_FOR_DUPLX&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DISABLE_AUTO_NEG_FOR_FLOW_CTRL&t;|&t;&bslash;&n;&t;MV64340_ETH_ADV_SYMMETRIC_FLOW_CTRL&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_FORCE_FC_MODE_NO_PAUSE_DIS_TX&t;|&t;&bslash;&n;&t;MV64340_ETH_FORCE_BP_MODE_NO_JAM&t;&t;|&t;&bslash;&n;&t;(1 &lt;&lt; 9)&t;&t;&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DO_NOT_FORCE_LINK_FAIL&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_RETRANSMIT_16_ATTEMPTS&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_ENABLE_AUTO_NEG_SPEED_GMII&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DTE_ADV_0&t;&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_DISABLE_AUTO_NEG_BYPASS&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_AUTO_NEG_NO_CHANGE&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_MAX_RX_PACKET_9700BYTE&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_CLR_EXT_LOOPBACK&t;&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_SET_FULL_DUPLEX_MODE&t;&t;|&t;&bslash;&n;&t;MV64340_ETH_ENABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX
multiline_comment|/*****************************************************************************&n; * Serial defines.&n; *****************************************************************************/
DECL|macro|PPC7D_SERIAL_0
mdefine_line|#define PPC7D_SERIAL_0&t;&t;0xe80003f8
DECL|macro|PPC7D_SERIAL_1
mdefine_line|#define PPC7D_SERIAL_1&t;&t;0xe80002f8
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;&t;&t;1843200
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;&t;( UART_CLK / 16 )
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, PPC7D_SERIAL_0, 4, STD_COM_FLAGS, /* ttyS0 */ &bslash;&n;&t;&t;iomem_base: (u8 *)PPC7D_SERIAL_0,&t;&t;&t;  &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM, },&t;&t;&t;&t;  &bslash;&n;        { 0, BASE_BAUD, PPC7D_SERIAL_1, 3, STD_COM_FLAGS, /* ttyS1 */ &bslash;&n;&t;&t;iomem_base: (u8 *)PPC7D_SERIAL_1,&t;&t;&t;  &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
multiline_comment|/*****************************************************************************&n; * CPLD defines.&n; *&n; * Register map:-&n; *&n; * 0000 to 000F &t;South Bridge DMA 1 Control&n; * 0020 and 0021 &t;South Bridge Interrupt 1 Control&n; * 0040 to 0043 &t;South Bridge Counter Control&n; * 0060 &t;&t;Keyboard&n; * 0061 &t;&t;South Bridge NMI Status and Control&n; * 0064 &t;&t;Keyboard&n; * 0071 and 0072 &t;RTC R/W&n; * 0078 to 007B &t;South Bridge BIOS Timer&n; * 0080 to 0090 &t;South Bridge DMA Pages&n; * 00A0 and 00A1 &t;South Bridge Interrupt 2 Control&n; * 00C0 to 00DE &t;South Bridge DMA 2 Control&n; * 02E8 to 02EF &t;COM6 R/W&n; * 02F8 to 02FF &t;South Bridge COM2 R/W&n; * 03E8 to 03EF &t;COM5 R/W&n; * 03F8 to 03FF &t;South Bridge COM1 R/W&n; * 040A &t;&t;South Bridge DMA Scatter/Gather RO&n; * 040B &t;&t;DMA 1 Extended Mode WO&n; * 0410 to 043F &t;South Bridge DMA Scatter/Gather&n; * 0481 to 048B &t;South Bridge DMA High Pages&n; * 04D0 and 04D1 &t;South Bridge Edge/Level Control&n; * 04D6 &t;&t;DMA 2 Extended Mode WO&n; * 0804 &t;&t;Memory Configuration RO&n; * 0806 &t;&t;Memory Configuration Extend RO&n; * 0808 &t;&t;SCSI Activity LED R/W&n; * 080C &t;&t;Equipment Present 1 RO&n; * 080E &t;&t;Equipment Present 2 RO&n; * 0810 &t;&t;Equipment Present 3 RO&n; * 0812 &t;&t;Equipment Present 4 RO&n; * 0818 &t;&t;Key Lock RO&n; * 0820 &t;&t;LEDS R/W&n; * 0824 &t;&t;COMs R/W&n; * 0826 &t;&t;RTS R/W&n; * 0828 &t;&t;Reset R/W&n; * 082C &t;&t;Watchdog Trig R/W&n; * 082E &t;&t;Interrupt R/W&n; * 0830 &t;&t;Interrupt Status RO&n; * 0832 &t;&t;PCI configuration RO&n; * 0854 &t;&t;Board Revision RO&n; * 0858 &t;&t;Extended ID RO&n; * 0864 &t;&t;ID Link RO&n; * 0866 &t;&t;Motherboard Type RO&n; * 0868 &t;&t;FLASH Write control RO&n; * 086A &t;&t;Software FLASH write protect R/W&n; * 086E &t;&t;FLASH Control R/W&n; *****************************************************************************/
DECL|macro|PPC7D_CPLD_MEM_CONFIG
mdefine_line|#define PPC7D_CPLD_MEM_CONFIG&t;&t;&t;0x0804
DECL|macro|PPC7D_CPLD_MEM_CONFIG_EXTEND
mdefine_line|#define PPC7D_CPLD_MEM_CONFIG_EXTEND&t;&t;0x0806
DECL|macro|PPC7D_CPLD_SCSI_ACTIVITY_LED
mdefine_line|#define PPC7D_CPLD_SCSI_ACTIVITY_LED&t;&t;0x0808
DECL|macro|PPC7D_CPLD_EQUIPMENT_PRESENT_1
mdefine_line|#define PPC7D_CPLD_EQUIPMENT_PRESENT_1&t;&t;0x080C
DECL|macro|PPC7D_CPLD_EQUIPMENT_PRESENT_2
mdefine_line|#define PPC7D_CPLD_EQUIPMENT_PRESENT_2&t;&t;0x080E
DECL|macro|PPC7D_CPLD_EQUIPMENT_PRESENT_3
mdefine_line|#define PPC7D_CPLD_EQUIPMENT_PRESENT_3&t;&t;0x0810
DECL|macro|PPC7D_CPLD_EQUIPMENT_PRESENT_4
mdefine_line|#define PPC7D_CPLD_EQUIPMENT_PRESENT_4&t;&t;0x0812
DECL|macro|PPC7D_CPLD_KEY_LOCK
mdefine_line|#define PPC7D_CPLD_KEY_LOCK&t;&t;&t;0x0818
DECL|macro|PPC7D_CPLD_LEDS
mdefine_line|#define PPC7D_CPLD_LEDS&t;&t;&t;&t;0x0820
DECL|macro|PPC7D_CPLD_COMS
mdefine_line|#define PPC7D_CPLD_COMS&t;&t;&t;&t;0x0824
DECL|macro|PPC7D_CPLD_RTS
mdefine_line|#define PPC7D_CPLD_RTS&t;&t;&t;&t;0x0826
DECL|macro|PPC7D_CPLD_RESET
mdefine_line|#define PPC7D_CPLD_RESET&t;&t;&t;0x0828
DECL|macro|PPC7D_CPLD_WATCHDOG_TRIG
mdefine_line|#define PPC7D_CPLD_WATCHDOG_TRIG&t;&t;0x082C
DECL|macro|PPC7D_CPLD_INTR
mdefine_line|#define PPC7D_CPLD_INTR&t;&t;&t;&t;0x082E
DECL|macro|PPC7D_CPLD_INTR_STATUS
mdefine_line|#define PPC7D_CPLD_INTR_STATUS&t;&t;&t;0x0830
DECL|macro|PPC7D_CPLD_PCI_CONFIG
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG&t;&t;&t;0x0832
DECL|macro|PPC7D_CPLD_BOARD_REVISION
mdefine_line|#define PPC7D_CPLD_BOARD_REVISION&t;&t;0x0854
DECL|macro|PPC7D_CPLD_EXTENDED_ID
mdefine_line|#define PPC7D_CPLD_EXTENDED_ID&t;&t;&t;0x0858
DECL|macro|PPC7D_CPLD_ID_LINK
mdefine_line|#define PPC7D_CPLD_ID_LINK&t;&t;&t;0x0864
DECL|macro|PPC7D_CPLD_MOTHERBOARD_TYPE
mdefine_line|#define PPC7D_CPLD_MOTHERBOARD_TYPE&t;&t;0x0866
DECL|macro|PPC7D_CPLD_FLASH_WRITE_CNTL
mdefine_line|#define PPC7D_CPLD_FLASH_WRITE_CNTL&t;&t;0x0868
DECL|macro|PPC7D_CPLD_SW_FLASH_WRITE_PROTECT
mdefine_line|#define PPC7D_CPLD_SW_FLASH_WRITE_PROTECT&t;0x086A
DECL|macro|PPC7D_CPLD_FLASH_CNTL
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL&t;&t;&t;0x086E
multiline_comment|/* MEMORY_CONFIG_EXTEND */
DECL|macro|PPC7D_CPLD_SDRAM_BANK_SIZE_MASK
mdefine_line|#define PPC7D_CPLD_SDRAM_BANK_SIZE_MASK&t;&t;0xc0
DECL|macro|PPC7D_CPLD_SDRAM_BANK_SIZE_128M
mdefine_line|#define PPC7D_CPLD_SDRAM_BANK_SIZE_128M&t;&t;0
DECL|macro|PPC7D_CPLD_SDRAM_BANK_SIZE_256M
mdefine_line|#define PPC7D_CPLD_SDRAM_BANK_SIZE_256M&t;&t;0x40
DECL|macro|PPC7D_CPLD_SDRAM_BANK_SIZE_512M
mdefine_line|#define PPC7D_CPLD_SDRAM_BANK_SIZE_512M&t;&t;0x80
DECL|macro|PPC7D_CPLD_SDRAM_BANK_SIZE_1G
mdefine_line|#define PPC7D_CPLD_SDRAM_BANK_SIZE_1G&t;&t;0xc0
DECL|macro|PPC7D_CPLD_FLASH_DEV_SIZE_MASK
mdefine_line|#define PPC7D_CPLD_FLASH_DEV_SIZE_MASK&t;&t;0x03
DECL|macro|PPC7D_CPLD_FLASH_BANK_NUM_MASK
mdefine_line|#define PPC7D_CPLD_FLASH_BANK_NUM_MASK&t;&t;0x0c
DECL|macro|PPC7D_CPLD_FLASH_DEV_SIZE_64M
mdefine_line|#define PPC7D_CPLD_FLASH_DEV_SIZE_64M&t;&t;0
DECL|macro|PPC7D_CPLD_FLASH_DEV_SIZE_32M
mdefine_line|#define PPC7D_CPLD_FLASH_DEV_SIZE_32M&t;&t;1
DECL|macro|PPC7D_CPLD_FLASH_DEV_SIZE_16M
mdefine_line|#define PPC7D_CPLD_FLASH_DEV_SIZE_16M&t;&t;3
DECL|macro|PPC7D_CPLD_FLASH_BANK_NUM_4
mdefine_line|#define PPC7D_CPLD_FLASH_BANK_NUM_4&t;&t;0x00
DECL|macro|PPC7D_CPLD_FLASH_BANK_NUM_3
mdefine_line|#define PPC7D_CPLD_FLASH_BANK_NUM_3&t;&t;0x04
DECL|macro|PPC7D_CPLD_FLASH_BANK_NUM_2
mdefine_line|#define PPC7D_CPLD_FLASH_BANK_NUM_2&t;&t;0x08
DECL|macro|PPC7D_CPLD_FLASH_BANK_NUM_1
mdefine_line|#define PPC7D_CPLD_FLASH_BANK_NUM_1&t;&t;0x0c
multiline_comment|/* SCSI_LED */
DECL|macro|PPC7D_CPLD_SCSI_ACTIVITY_LED_OFF
mdefine_line|#define PPC7D_CPLD_SCSI_ACTIVITY_LED_OFF&t;0
DECL|macro|PPC7D_CPLD_SCSI_ACTIVITY_LED_ON
mdefine_line|#define PPC7D_CPLD_SCSI_ACTIVITY_LED_ON&t;&t;1
multiline_comment|/* EQUIPMENT_PRESENT_1 */
DECL|macro|PPC7D_CPLD_EQPT_PRES_1_FITTED
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_1_FITTED&t;&t;0
DECL|macro|PPC7D_CPLD_EQPT_PRES_1_PMC2_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_1_PMC2_MASK&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_EQPT_PRES_1_PMC1_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_1_PMC1_MASK&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_EQPT_PRES_1_AFIX_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_1_AFIX_MASK&t;(0x80 &gt;&gt; 4)
multiline_comment|/* EQUIPMENT_PRESENT_2 */
DECL|macro|PPC7D_CPLD_EQPT_PRES_2_FITTED
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_2_FITTED&t;&t;!0
DECL|macro|PPC7D_CPLD_EQPT_PRES_2_UNIVERSE_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_2_UNIVERSE_MASK&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_EQPT_PRES_2_COM36_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_2_COM36_MASK&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_EQPT_PRES_2_GIGE_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_2_GIGE_MASK&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_EQPT_PRES_2_DUALGIGE_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_2_DUALGIGE_MASK&t;(0x80 &gt;&gt; 4)
multiline_comment|/* EQUIPMENT_PRESENT_3 */
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC2_V_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC2_V_MASK&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC2_5V
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC2_5V&t;&t;(0 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC2_3V
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC2_3V&t;&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC1_V_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC1_V_MASK&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC1_5V
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC1_5V&t;&t;(0 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC1_3V
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC1_3V&t;&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC_POWER_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC_POWER_MASK&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC_POWER_INTER
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC_POWER_INTER&t;(0 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_EQPT_PRES_3_PMC_POWER_VME
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_3_PMC_POWER_VME&t;(0x80 &gt;&gt; 5)
multiline_comment|/* EQUIPMENT_PRESENT_4 */
DECL|macro|PPC7D_CPLD_EQPT_PRES_4_LPT_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_4_LPT_MASK&t;&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_EQPT_PRES_4_LPT_FITTED
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_4_LPT_FITTED&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_EQPT_PRES_4_PS2_USB2_MASK
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_4_PS2_USB2_MASK&t;(0xc0 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_EQPT_PRES_4_PS2_FITTED
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_4_PS2_FITTED&t;(0x40 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_EQPT_PRES_4_USB2_FITTED
mdefine_line|#define PPC7D_CPLD_EQPT_PRES_4_USB2_FITTED&t;(0x80 &gt;&gt; 6)
multiline_comment|/* CPLD_LEDS */
DECL|macro|PPC7D_CPLD_LEDS_ON
mdefine_line|#define PPC7D_CPLD_LEDS_ON&t;&t;&t;(!0)
DECL|macro|PPC7D_CPLD_LEDS_OFF
mdefine_line|#define PPC7D_CPLD_LEDS_OFF&t;&t;&t;(0)
DECL|macro|PPC7D_CPLD_LEDS_NVRAM_PAGE_MASK
mdefine_line|#define PPC7D_CPLD_LEDS_NVRAM_PAGE_MASK&t;&t;(0xc0 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_LEDS_DS201_MASK
mdefine_line|#define PPC7D_CPLD_LEDS_DS201_MASK&t;&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_LEDS_DS219_MASK
mdefine_line|#define PPC7D_CPLD_LEDS_DS219_MASK&t;&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_LEDS_DS220_MASK
mdefine_line|#define PPC7D_CPLD_LEDS_DS220_MASK&t;&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_LEDS_DS221_MASK
mdefine_line|#define PPC7D_CPLD_LEDS_DS221_MASK&t;&t;(0x80 &gt;&gt; 7)
multiline_comment|/* CPLD_COMS */
DECL|macro|PPC7D_CPLD_COMS_COM3_TCLKEN
mdefine_line|#define PPC7D_CPLD_COMS_COM3_TCLKEN&t;&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_COMS_COM3_RTCLKEN
mdefine_line|#define PPC7D_CPLD_COMS_COM3_RTCLKEN&t;&t;(0x80 &gt;&gt; 1)
DECL|macro|PPC7D_CPLD_COMS_COM3_MODE_MASK
mdefine_line|#define PPC7D_CPLD_COMS_COM3_MODE_MASK&t;&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_COMS_COM3_MODE_RS232
mdefine_line|#define PPC7D_CPLD_COMS_COM3_MODE_RS232&t;&t;(0)
DECL|macro|PPC7D_CPLD_COMS_COM3_MODE_RS422
mdefine_line|#define PPC7D_CPLD_COMS_COM3_MODE_RS422&t;&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_COMS_COM3_TXEN
mdefine_line|#define PPC7D_CPLD_COMS_COM3_TXEN&t;&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_COMS_COM4_TCLKEN
mdefine_line|#define PPC7D_CPLD_COMS_COM4_TCLKEN&t;&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_COMS_COM4_RTCLKEN
mdefine_line|#define PPC7D_CPLD_COMS_COM4_RTCLKEN&t;&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_COMS_COM4_MODE_MASK
mdefine_line|#define PPC7D_CPLD_COMS_COM4_MODE_MASK&t;&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_COMS_COM4_MODE_RS232
mdefine_line|#define PPC7D_CPLD_COMS_COM4_MODE_RS232&t;&t;(0)
DECL|macro|PPC7D_CPLD_COMS_COM4_MODE_RS422
mdefine_line|#define PPC7D_CPLD_COMS_COM4_MODE_RS422&t;&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_COMS_COM4_TXEN
mdefine_line|#define PPC7D_CPLD_COMS_COM4_TXEN&t;&t;(0x80 &gt;&gt; 7)
multiline_comment|/* CPLD_RTS */
DECL|macro|PPC7D_CPLD_RTS_COM36_LOOPBACK
mdefine_line|#define PPC7D_CPLD_RTS_COM36_LOOPBACK&t;&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_RTS_COM4_SCLK
mdefine_line|#define PPC7D_CPLD_RTS_COM4_SCLK&t;&t;(0x80 &gt;&gt; 1)
DECL|macro|PPC7D_CPLD_RTS_COM3_TXFUNC_MASK
mdefine_line|#define PPC7D_CPLD_RTS_COM3_TXFUNC_MASK&t;&t;(0xc0 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_RTS_COM3_TXFUNC_DISABLED
mdefine_line|#define PPC7D_CPLD_RTS_COM3_TXFUNC_DISABLED&t;(0 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_RTS_COM3_TXFUNC_ENABLED
mdefine_line|#define PPC7D_CPLD_RTS_COM3_TXFUNC_ENABLED&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_RTS_COM3_TXFUNC_ENABLED_RTG3
mdefine_line|#define PPC7D_CPLD_RTS_COM3_TXFUNC_ENABLED_RTG3&t;(0xc0 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_RTS_COM3_TXFUNC_ENABLED_RTG3S
mdefine_line|#define PPC7D_CPLD_RTS_COM3_TXFUNC_ENABLED_RTG3S (0xc0 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_RTS_COM56_MODE_MASK
mdefine_line|#define PPC7D_CPLD_RTS_COM56_MODE_MASK&t;&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_RTS_COM56_MODE_RS232
mdefine_line|#define PPC7D_CPLD_RTS_COM56_MODE_RS232&t;&t;(0)
DECL|macro|PPC7D_CPLD_RTS_COM56_MODE_RS422
mdefine_line|#define PPC7D_CPLD_RTS_COM56_MODE_RS422&t;&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_RTS_COM56_ENABLE_MASK
mdefine_line|#define PPC7D_CPLD_RTS_COM56_ENABLE_MASK&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_RTS_COM56_DISABLED
mdefine_line|#define PPC7D_CPLD_RTS_COM56_DISABLED&t;&t;(0)
DECL|macro|PPC7D_CPLD_RTS_COM56_ENABLED
mdefine_line|#define PPC7D_CPLD_RTS_COM56_ENABLED&t;&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_RTS_COM4_TXFUNC_MASK
mdefine_line|#define PPC7D_CPLD_RTS_COM4_TXFUNC_MASK&t;&t;(0xc0 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_RTS_COM4_TXFUNC_DISABLED
mdefine_line|#define PPC7D_CPLD_RTS_COM4_TXFUNC_DISABLED&t;(0 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_RTS_COM4_TXFUNC_ENABLED
mdefine_line|#define PPC7D_CPLD_RTS_COM4_TXFUNC_ENABLED&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_RTS_COM4_TXFUNC_ENABLED_RTG3
mdefine_line|#define PPC7D_CPLD_RTS_COM4_TXFUNC_ENABLED_RTG3&t;(0x40 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_RTS_COM4_TXFUNC_ENABLED_RTG3S
mdefine_line|#define PPC7D_CPLD_RTS_COM4_TXFUNC_ENABLED_RTG3S (0x40 &gt;&gt; 6)
multiline_comment|/* WATCHDOG_TRIG */
DECL|macro|PPC7D_CPLD_WDOG_CAUSE_MASK
mdefine_line|#define PPC7D_CPLD_WDOG_CAUSE_MASK&t;&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_WDOG_CAUSE_NORMAL_RESET
mdefine_line|#define PPC7D_CPLD_WDOG_CAUSE_NORMAL_RESET&t;(0 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_WDOG_CAUSE_WATCHDOG
mdefine_line|#define PPC7D_CPLD_WDOG_CAUSE_WATCHDOG&t;&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_WDOG_ENABLE_MASK
mdefine_line|#define PPC7D_CPLD_WDOG_ENABLE_MASK&t;&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_WDOG_ENABLE_OFF
mdefine_line|#define PPC7D_CPLD_WDOG_ENABLE_OFF&t;&t;(0 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_WDOG_ENABLE_ON
mdefine_line|#define PPC7D_CPLD_WDOG_ENABLE_ON&t;&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_WDOG_RESETSW_MASK
mdefine_line|#define PPC7D_CPLD_WDOG_RESETSW_MASK&t;&t;(0x80 &gt;&gt; 7)
DECL|macro|PPC7D_CPLD_WDOG_RESETSW_OFF
mdefine_line|#define PPC7D_CPLD_WDOG_RESETSW_OFF&t;&t;(0 &gt;&gt; 7)
DECL|macro|PPC7D_CPLD_WDOG_RESETSW_ON
mdefine_line|#define PPC7D_CPLD_WDOG_RESETSW_ON&t;&t;(0x80 &gt;&gt; 7)
multiline_comment|/* Interrupt mask and status bits */
DECL|macro|PPC7D_CPLD_INTR_TEMP_MASK
mdefine_line|#define PPC7D_CPLD_INTR_TEMP_MASK&t;&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_INTR_HB8_MASK
mdefine_line|#define PPC7D_CPLD_INTR_HB8_MASK&t;&t;(0x80 &gt;&gt; 1)
DECL|macro|PPC7D_CPLD_INTR_PHY1_MASK
mdefine_line|#define PPC7D_CPLD_INTR_PHY1_MASK&t;&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_INTR_PHY0_MASK
mdefine_line|#define PPC7D_CPLD_INTR_PHY0_MASK&t;&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_INTR_ISANMI_MASK
mdefine_line|#define PPC7D_CPLD_INTR_ISANMI_MASK&t;&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_INTR_CRITTEMP_MASK
mdefine_line|#define PPC7D_CPLD_INTR_CRITTEMP_MASK&t;&t;(0x80 &gt;&gt; 6)
multiline_comment|/* CPLD_INTR */
DECL|macro|PPC7D_CPLD_INTR_ENABLE_OFF
mdefine_line|#define PPC7D_CPLD_INTR_ENABLE_OFF&t;&t;(0)
DECL|macro|PPC7D_CPLD_INTR_ENABLE_ON
mdefine_line|#define PPC7D_CPLD_INTR_ENABLE_ON&t;&t;(!0)
multiline_comment|/* CPLD_INTR_STATUS */
DECL|macro|PPC7D_CPLD_INTR_STATUS_OFF
mdefine_line|#define PPC7D_CPLD_INTR_STATUS_OFF&t;&t;(0)
DECL|macro|PPC7D_CPLD_INTR_STATUS_ON
mdefine_line|#define PPC7D_CPLD_INTR_STATUS_ON&t;&t;(!0)
multiline_comment|/* CPLD_PCI_CONFIG */
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_MASK
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_MASK&t;&t;0x70
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_PCI33
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_PCI33&t;0x00
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_PCI66
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_PCI66&t;0x10
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX33
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX33&t;0x40
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX66
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX66&t;0x50
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX100
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX100      0x60
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX133
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI0_PCIX133&t;0x70
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_MASK
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_MASK&t;&t;0x07
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_PCI33
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_PCI33&t;0x00
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_PCI66
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_PCI66&t;0x01
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX33
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX33&t;0x04
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX66
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX66&t;0x05
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX100
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX100&t;0x06
DECL|macro|PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX133
mdefine_line|#define PPC7D_CPLD_PCI_CONFIG_PCI1_PCIX133&t;0x07
multiline_comment|/* CPLD_BOARD_REVISION */
DECL|macro|PPC7D_CPLD_BOARD_REVISION_NUMBER_MASK
mdefine_line|#define PPC7D_CPLD_BOARD_REVISION_NUMBER_MASK&t;0xe0
DECL|macro|PPC7D_CPLD_BOARD_REVISION_LETTER_MASK
mdefine_line|#define PPC7D_CPLD_BOARD_REVISION_LETTER_MASK&t;0x1f
multiline_comment|/* CPLD_EXTENDED_ID */
DECL|macro|PPC7D_CPLD_EXTENDED_ID_PPC7D
mdefine_line|#define PPC7D_CPLD_EXTENDED_ID_PPC7D&t;&t;0x18
multiline_comment|/* CPLD_ID_LINK */
DECL|macro|PPC7D_CPLD_ID_LINK_VME64_GAP_MASK
mdefine_line|#define PPC7D_CPLD_ID_LINK_VME64_GAP_MASK&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_ID_LINK_VME64_GA4_MASK
mdefine_line|#define PPC7D_CPLD_ID_LINK_VME64_GA4_MASK&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_ID_LINK_E13_MASK
mdefine_line|#define PPC7D_CPLD_ID_LINK_E13_MASK&t;&t;(0x80 &gt;&gt; 4)
DECL|macro|PPC7D_CPLD_ID_LINK_E12_MASK
mdefine_line|#define PPC7D_CPLD_ID_LINK_E12_MASK&t;&t;(0x80 &gt;&gt; 5)
DECL|macro|PPC7D_CPLD_ID_LINK_E7_MASK
mdefine_line|#define PPC7D_CPLD_ID_LINK_E7_MASK&t;&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_ID_LINK_E6_MASK
mdefine_line|#define PPC7D_CPLD_ID_LINK_E6_MASK&t;&t;(0x80 &gt;&gt; 7)
multiline_comment|/* CPLD_MOTHERBOARD_TYPE */
DECL|macro|PPC7D_CPLD_MB_TYPE_ECC_ENABLE_MASK
mdefine_line|#define PPC7D_CPLD_MB_TYPE_ECC_ENABLE_MASK&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_MB_TYPE_ECC_ENABLED
mdefine_line|#define PPC7D_CPLD_MB_TYPE_ECC_ENABLED&t;&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_MB_TYPE_ECC_DISABLED
mdefine_line|#define PPC7D_CPLD_MB_TYPE_ECC_DISABLED&t;&t;(0 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_MB_TYPE_ECC_FITTED_MASK
mdefine_line|#define PPC7D_CPLD_MB_TYPE_ECC_FITTED_MASK&t;(0x80 &gt;&gt; 3)
DECL|macro|PPC7D_CPLD_MB_TYPE_PLL_MASK
mdefine_line|#define PPC7D_CPLD_MB_TYPE_PLL_MASK&t;&t;0x0c
DECL|macro|PPC7D_CPLD_MB_TYPE_PLL_133
mdefine_line|#define PPC7D_CPLD_MB_TYPE_PLL_133&t;&t;0x00
DECL|macro|PPC7D_CPLD_MB_TYPE_PLL_100
mdefine_line|#define PPC7D_CPLD_MB_TYPE_PLL_100&t;&t;0x08
DECL|macro|PPC7D_CPLD_MB_TYPE_PLL_64
mdefine_line|#define PPC7D_CPLD_MB_TYPE_PLL_64&t;&t;0x04
DECL|macro|PPC7D_CPLD_MB_TYPE_HW_ID_MASK
mdefine_line|#define PPC7D_CPLD_MB_TYPE_HW_ID_MASK&t;&t;0x03
multiline_comment|/* CPLD_FLASH_WRITE_CNTL */
DECL|macro|PPD7D_CPLD_FLASH_CNTL_WR_LINK_MASK
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_WR_LINK_MASK&t;(0x80 &gt;&gt; 0)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_WR_LINK_FITTED
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_WR_LINK_FITTED&t;(0x80 &gt;&gt; 0)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_BOOT_LINK_MASK
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_BOOT_LINK_MASK&t;(0x80 &gt;&gt; 2)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_BOOT_LINK_FITTED
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_BOOT_LINK_FITTED&t;(0x80 &gt;&gt; 2)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_USER_LINK_MASK
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_USER_LINK_MASK&t;(0x80 &gt;&gt; 3)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_USER_LINK_FITTED
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_USER_LINK_FITTED&t;(0x80 &gt;&gt; 3)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_RECO_WR_MASK
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_RECO_WR_MASK&t;(0x80 &gt;&gt; 5)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_RECO_WR_ENABLED
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_RECO_WR_ENABLED&t;(0x80 &gt;&gt; 5)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_BOOT_WR_MASK
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_BOOT_WR_MASK&t;(0x80 &gt;&gt; 6)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_BOOT_WR_ENABLED
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_BOOT_WR_ENABLED&t;(0x80 &gt;&gt; 6)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_USER_WR_MASK
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_USER_WR_MASK&t;(0x80 &gt;&gt; 7)
DECL|macro|PPD7D_CPLD_FLASH_CNTL_USER_WR_ENABLED
mdefine_line|#define PPD7D_CPLD_FLASH_CNTL_USER_WR_ENABLED&t;(0x80 &gt;&gt; 7)
multiline_comment|/* CPLD_SW_FLASH_WRITE_PROTECT */
DECL|macro|PPC7D_CPLD_SW_FLASH_WRPROT_ENABLED
mdefine_line|#define PPC7D_CPLD_SW_FLASH_WRPROT_ENABLED&t;(!0)
DECL|macro|PPC7D_CPLD_SW_FLASH_WRPROT_DISABLED
mdefine_line|#define PPC7D_CPLD_SW_FLASH_WRPROT_DISABLED&t;(0)
DECL|macro|PPC7D_CPLD_SW_FLASH_WRPROT_SYSBOOT_MASK
mdefine_line|#define PPC7D_CPLD_SW_FLASH_WRPROT_SYSBOOT_MASK&t;(0x80 &gt;&gt; 6)
DECL|macro|PPC7D_CPLD_SW_FLASH_WRPROT_USER_MASK
mdefine_line|#define PPC7D_CPLD_SW_FLASH_WRPROT_USER_MASK&t;(0x80 &gt;&gt; 7)
multiline_comment|/* CPLD_FLASH_WRITE_CNTL */
DECL|macro|PPC7D_CPLD_FLASH_CNTL_NVRAM_PROT_MASK
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL_NVRAM_PROT_MASK&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_FLASH_CNTL_NVRAM_DISABLED
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL_NVRAM_DISABLED&t;(0 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_FLASH_CNTL_NVRAM_ENABLED
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL_NVRAM_ENABLED&t;(0x80 &gt;&gt; 0)
DECL|macro|PPC7D_CPLD_FLASH_CNTL_ALTBOOT_LINK_MASK
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL_ALTBOOT_LINK_MASK&t;(0x80 &gt;&gt; 1)
DECL|macro|PPC7D_CPLD_FLASH_CNTL_VMEBOOT_LINK_MASK
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL_VMEBOOT_LINK_MASK&t;(0x80 &gt;&gt; 2)
DECL|macro|PPC7D_CPLD_FLASH_CNTL_RECBOOT_LINK_MASK
mdefine_line|#define PPC7D_CPLD_FLASH_CNTL_RECBOOT_LINK_MASK&t;(0x80 &gt;&gt; 3)
macro_line|#endif /* __PPC_PLATFORMS_PPC7D_H */
eof
