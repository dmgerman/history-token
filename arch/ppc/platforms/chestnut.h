multiline_comment|/*&n; * arch/ppc/platforms/chestnut.h&n; *&n; * Definitions for IBM 750FXGX Eval (Chestnut)&n; *&n; * Author: &lt;source@mvista.com&gt;&n; *&n; * Based on Artesyn Katana code done by Tim Montgomery &lt;timm@artesyncp.com&gt;&n; * Based on code done by Rabeeh Khoury - rabeeh@galileo.co.il&n; * Based on code done by Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * &lt;2004&gt; (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * This is the CPU physical memory map (windows must be at least 1MB and start&n; * on a boundary that is a multiple of the window size):&n; *&n; * Seems on the IBM 750FXGX Eval board, the MV64460 Registers can be in&n; * only 2 places per switch U17 0x14000000 or 0xf1000000 easily - chose to&n; * implement at 0xf1000000 only at this time&n; *&n; *    0xfff00000-0xffffffff      - 8 Flash&n; *    0xffd00000-0xffd00004      - CPLD&n; *    0xffc00000-0xffc0000f      - UART&n; *    0xffb00000-0xffb07fff      - FRAM&n; *    0xffa00000-0xffafffff      - *** HOLE ***&n; *    0xff900000-0xff9fffff      - MV64460 Integrated SRAM&n; *    0xfe000000-0xff8fffff      - *** HOLE ***&n; *    0xfc000000-0xfdffffff      - 32bit Flash&n; *    0xf1010000-0xfbffffff      - *** HOLE ***&n; *    0xf1000000-0xf100ffff      - MV64460 Registers&n; */
macro_line|#ifndef __PPC_PLATFORMS_CHESTNUT_H__
DECL|macro|__PPC_PLATFORMS_CHESTNUT_H__
mdefine_line|#define __PPC_PLATFORMS_CHESTNUT_H__
DECL|macro|CHESTNUT_BOOT_8BIT_BASE
mdefine_line|#define CHESTNUT_BOOT_8BIT_BASE&t;&t;&t;0xfff00000
DECL|macro|CHESTNUT_BOOT_8BIT_SIZE_ACTUAL
mdefine_line|#define CHESTNUT_BOOT_8BIT_SIZE_ACTUAL&t;&t;(1024*1024)
DECL|macro|CHESTNUT_BOOT_SRAM_BASE
mdefine_line|#define CHESTNUT_BOOT_SRAM_BASE&t;&t;&t;0xffe00000
DECL|macro|CHESTNUT_BOOT_SRAM_SIZE_ACTUAL
mdefine_line|#define CHESTNUT_BOOT_SRAM_SIZE_ACTUAL&t;&t;(1024*1024)
DECL|macro|CHESTNUT_CPLD_BASE
mdefine_line|#define CHESTNUT_CPLD_BASE&t;&t;&t;0xffd00000
DECL|macro|CHESTNUT_CPLD_SIZE_ACTUAL
mdefine_line|#define CHESTNUT_CPLD_SIZE_ACTUAL&t;&t;5
DECL|macro|CHESTNUT_CPLD_REG3
mdefine_line|#define CHESTNUT_CPLD_REG3&t;&t;&t;(CHESTNUT_CPLD_BASE+3)
DECL|macro|CHESTNUT_UART_BASE
mdefine_line|#define CHESTNUT_UART_BASE&t;&t;&t;0xffc00000
DECL|macro|CHESTNUT_UART_SIZE_ACTUAL
mdefine_line|#define CHESTNUT_UART_SIZE_ACTUAL&t;&t;16
DECL|macro|CHESTNUT_FRAM_BASE
mdefine_line|#define CHESTNUT_FRAM_BASE&t;&t;&t;0xffb00000
DECL|macro|CHESTNUT_FRAM_SIZE_ACTUAL
mdefine_line|#define CHESTNUT_FRAM_SIZE_ACTUAL&t;&t;(32*1024)
DECL|macro|CHESTNUT_BRIDGE_REG_BASE
mdefine_line|#define CHESTNUT_BRIDGE_REG_BASE&t;&t;0xf1000000
DECL|macro|CHESTNUT_INTERNAL_SRAM_BASE
mdefine_line|#define CHESTNUT_INTERNAL_SRAM_BASE&t;&t;0xff900000
DECL|macro|CHESTNUT_INTERNAL_SRAM_SIZE_ACTUAL
mdefine_line|#define CHESTNUT_INTERNAL_SRAM_SIZE_ACTUAL&t;(256*1024)
DECL|macro|CHESTNUT_32BIT_BASE
mdefine_line|#define CHESTNUT_32BIT_BASE&t;&t;&t;0xfc000000
DECL|macro|CHESTNUT_32BIT_SIZE
mdefine_line|#define CHESTNUT_32BIT_SIZE&t;&t;&t;(32*1024*1024)
DECL|macro|CHESTNUT_BOOT_8BIT_SIZE
mdefine_line|#define CHESTNUT_BOOT_8BIT_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN, &bslash;&n;&t;&t;&t;&t;&t;CHESTNUT_BOOT_8BIT_SIZE_ACTUAL)
DECL|macro|CHESTNUT_BOOT_SRAM_SIZE
mdefine_line|#define CHESTNUT_BOOT_SRAM_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN, &bslash;&n;&t;&t;&t;&t;&t;CHESTNUT_BOOT_SRAM_SIZE_ACTUAL)
DECL|macro|CHESTNUT_CPLD_SIZE
mdefine_line|#define CHESTNUT_CPLD_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN, &bslash;&n;&t;&t;&t;&t;&t;CHESTNUT_CPLD_SIZE_ACTUAL)
DECL|macro|CHESTNUT_UART_SIZE
mdefine_line|#define CHESTNUT_UART_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN, &bslash;&n;&t;&t;&t;&t;&t;CHESTNUT_UART_SIZE_ACTUAL)
DECL|macro|CHESTNUT_FRAM_SIZE
mdefine_line|#define CHESTNUT_FRAM_SIZE&t;&t;max(MV64360_WINDOW_SIZE_MIN, &bslash;&n;&t;&t;&t;&t;&t;CHESTNUT_FRAM_SIZE_ACTUAL)
DECL|macro|CHESTNUT_INTERNAL_SRAM_SIZE
mdefine_line|#define CHESTNUT_INTERNAL_SRAM_SIZE&t;max(MV64360_WINDOW_SIZE_MIN, &bslash;&n;&t;&t;&t;&t;&t;CHESTNUT_INTERNAL_SRAM_SIZE_ACTUAL)
DECL|macro|CHESTNUT_BUS_SPEED
mdefine_line|#define CHESTNUT_BUS_SPEED&t;&t;200000000
DECL|macro|CHESTNUT_PIBS_DATABASE
mdefine_line|#define CHESTNUT_PIBS_DATABASE&t;&t;0xf0000 /* from PIBS src code */
DECL|macro|MV64360_ETH_PORT_SERIAL_CONTROL_REG_PORT0
mdefine_line|#define MV64360_ETH_PORT_SERIAL_CONTROL_REG_PORT0 &t;0x243c
DECL|macro|MV64360_ETH_PORT_SERIAL_CONTROL_REG_PORT1
mdefine_line|#define MV64360_ETH_PORT_SERIAL_CONTROL_REG_PORT1 &t;0x283c
multiline_comment|/*&n; * PCI windows&n; */
DECL|macro|CHESTNUT_PCI0_MEM_PROC_ADDR
mdefine_line|#define CHESTNUT_PCI0_MEM_PROC_ADDR&t;0x80000000
DECL|macro|CHESTNUT_PCI0_MEM_PCI_HI_ADDR
mdefine_line|#define CHESTNUT_PCI0_MEM_PCI_HI_ADDR&t;0x00000000
DECL|macro|CHESTNUT_PCI0_MEM_PCI_LO_ADDR
mdefine_line|#define CHESTNUT_PCI0_MEM_PCI_LO_ADDR&t;0x80000000
DECL|macro|CHESTNUT_PCI0_MEM_SIZE
mdefine_line|#define CHESTNUT_PCI0_MEM_SIZE&t;&t;0x10000000
DECL|macro|CHESTNUT_PCI0_IO_PROC_ADDR
mdefine_line|#define CHESTNUT_PCI0_IO_PROC_ADDR&t;0xa0000000
DECL|macro|CHESTNUT_PCI0_IO_PCI_ADDR
mdefine_line|#define CHESTNUT_PCI0_IO_PCI_ADDR&t;0x00000000
DECL|macro|CHESTNUT_PCI0_IO_SIZE
mdefine_line|#define CHESTNUT_PCI0_IO_SIZE&t;&t;0x01000000
multiline_comment|/*&n; * Board-specific IRQ info&n; */
DECL|macro|CHESTNUT_PCI_SLOT0_IRQ
mdefine_line|#define CHESTNUT_PCI_SLOT0_IRQ&t;64+31
DECL|macro|CHESTNUT_PCI_SLOT1_IRQ
mdefine_line|#define CHESTNUT_PCI_SLOT1_IRQ&t;64+30
DECL|macro|CHESTNUT_PCI_SLOT2_IRQ
mdefine_line|#define CHESTNUT_PCI_SLOT2_IRQ&t;64+29
DECL|macro|CHESTNUT_PCI_SLOT3_IRQ
mdefine_line|#define CHESTNUT_PCI_SLOT3_IRQ&t;64+28
multiline_comment|/* serial port definitions */
DECL|macro|CHESTNUT_UART0_IO_BASE
mdefine_line|#define CHESTNUT_UART0_IO_BASE  CHESTNUT_UART_BASE+8
DECL|macro|CHESTNUT_UART1_IO_BASE
mdefine_line|#define CHESTNUT_UART1_IO_BASE  CHESTNUT_UART_BASE
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT           &t;64+25
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT        &t;64+26
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
macro_line|#endif
multiline_comment|/* Rate for the 3.6864 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD &t;&t;( 3686400 / 16 )
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, 0, UART##num##_INT, STD_COM_FLAGS,&t;&t;&bslash;&n;                iomem_base: (u8 *)CHESTNUT_UART##num##_IO_BASE,&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS        &bslash;&n;        STD_UART_OP(0)          &bslash;&n;        STD_UART_OP(1)
macro_line|#endif /* __PPC_PLATFORMS_CHESTNUT_H__ */
eof
