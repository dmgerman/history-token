multiline_comment|/*&n; * arch/ppc/platforms/ev64260.h&n; *&n; * Definitions for Marvell/Galileo EV-64260-BP Evaluation Board.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * The MV64x60 has 2 PCI buses each with 1 window from the CPU bus to&n; * PCI I/O space and 4 windows from the CPU bus to PCI MEM space.&n; * We&squot;ll only use one PCI MEM window on each PCI bus.&n; *&n; * This is the CPU physical memory map (windows must be at least 1MB and start&n; * on a boundary that is a multiple of the window size):&n; *&n; * &t;0xfc000000-0xffffffff&t;&t;- External FLASH on device module&n; * &t;0xfbf00000-0xfbffffff&t;&t;- Embedded (on board) FLASH&n; * &t;0xfbe00000-0xfbefffff&t;&t;- GT64260 Registers (preferably)&n; * &t;&t;&t;&t;&t;  but really a config option&n; * &t;0xfbd00000-0xfbdfffff&t;&t;- External SRAM on device module&n; * &t;0xfbc00000-0xfbcfffff&t;&t;- TODC chip on device module&n; * &t;0xfbb00000-0xfbbfffff&t;&t;- External UART on device module&n; * &t;0xa2000000-0xfbafffff&t;&t;- &lt;hole&gt;&n; * &t;0xa1000000-0xa1ffffff&t;&t;- PCI 1 I/O (defined in gt64260.h)&n; * &t;0xa0000000-0xa0ffffff&t;&t;- PCI 0 I/O (defined in gt64260.h)&n; * &t;0x90000000-0x9fffffff&t;&t;- PCI 1 MEM (defined in gt64260.h)&n; * &t;0x80000000-0x8fffffff&t;&t;- PCI 0 MEM (defined in gt64260.h)&n; */
macro_line|#ifndef __PPC_PLATFORMS_EV64260_H
DECL|macro|__PPC_PLATFORMS_EV64260_H
mdefine_line|#define __PPC_PLATFORMS_EV64260_H
multiline_comment|/* PCI mappings */
DECL|macro|EV64260_PCI0_IO_CPU_BASE
mdefine_line|#define&t;EV64260_PCI0_IO_CPU_BASE&t;0xa0000000
DECL|macro|EV64260_PCI0_IO_PCI_BASE
mdefine_line|#define&t;EV64260_PCI0_IO_PCI_BASE&t;0x00000000
DECL|macro|EV64260_PCI0_IO_SIZE
mdefine_line|#define&t;EV64260_PCI0_IO_SIZE&t;&t;0x01000000
DECL|macro|EV64260_PCI0_MEM_CPU_BASE
mdefine_line|#define&t;EV64260_PCI0_MEM_CPU_BASE&t;0x80000000
DECL|macro|EV64260_PCI0_MEM_PCI_BASE
mdefine_line|#define&t;EV64260_PCI0_MEM_PCI_BASE&t;0x80000000
DECL|macro|EV64260_PCI0_MEM_SIZE
mdefine_line|#define&t;EV64260_PCI0_MEM_SIZE&t;&t;0x10000000
DECL|macro|EV64260_PCI1_IO_CPU_BASE
mdefine_line|#define&t;EV64260_PCI1_IO_CPU_BASE&t;(EV64260_PCI0_IO_CPU_BASE + &bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_PCI0_IO_SIZE)
DECL|macro|EV64260_PCI1_IO_PCI_BASE
mdefine_line|#define&t;EV64260_PCI1_IO_PCI_BASE&t;(EV64260_PCI0_IO_PCI_BASE + &bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_PCI0_IO_SIZE)
DECL|macro|EV64260_PCI1_IO_SIZE
mdefine_line|#define&t;EV64260_PCI1_IO_SIZE&t;&t;0x01000000
DECL|macro|EV64260_PCI1_MEM_CPU_BASE
mdefine_line|#define&t;EV64260_PCI1_MEM_CPU_BASE&t;(EV64260_PCI0_MEM_CPU_BASE + &bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_PCI0_MEM_SIZE)
DECL|macro|EV64260_PCI1_MEM_PCI_BASE
mdefine_line|#define&t;EV64260_PCI1_MEM_PCI_BASE&t;(EV64260_PCI0_MEM_PCI_BASE + &bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_PCI0_MEM_SIZE)
DECL|macro|EV64260_PCI1_MEM_SIZE
mdefine_line|#define&t;EV64260_PCI1_MEM_SIZE&t;&t;0x10000000
multiline_comment|/* CPU Physical Memory Map setup (other than PCI) */
DECL|macro|EV64260_EXT_FLASH_BASE
mdefine_line|#define&t;EV64260_EXT_FLASH_BASE&t;&t;0xfc000000
DECL|macro|EV64260_EMB_FLASH_BASE
mdefine_line|#define&t;EV64260_EMB_FLASH_BASE&t;&t;0xfbf00000
DECL|macro|EV64260_EXT_SRAM_BASE
mdefine_line|#define&t;EV64260_EXT_SRAM_BASE&t;&t;0xfbd00000
DECL|macro|EV64260_TODC_BASE
mdefine_line|#define&t;EV64260_TODC_BASE&t;&t;0xfbc00000
DECL|macro|EV64260_UART_BASE
mdefine_line|#define&t;EV64260_UART_BASE&t;&t;0xfbb00000
DECL|macro|EV64260_EXT_FLASH_SIZE_ACTUAL
mdefine_line|#define&t;EV64260_EXT_FLASH_SIZE_ACTUAL&t;0x04000000  /* &lt;= 64MB Extern FLASH */
DECL|macro|EV64260_EMB_FLASH_SIZE_ACTUAL
mdefine_line|#define&t;EV64260_EMB_FLASH_SIZE_ACTUAL&t;0x00080000  /* 512KB of Embed FLASH */
DECL|macro|EV64260_EXT_SRAM_SIZE_ACTUAL
mdefine_line|#define&t;EV64260_EXT_SRAM_SIZE_ACTUAL&t;0x00100000  /* 1MB SDRAM */
DECL|macro|EV64260_TODC_SIZE_ACTUAL
mdefine_line|#define&t;EV64260_TODC_SIZE_ACTUAL&t;0x00000020  /* 32 bytes for TODC */
DECL|macro|EV64260_UART_SIZE_ACTUAL
mdefine_line|#define&t;EV64260_UART_SIZE_ACTUAL&t;0x00000040  /* 64 bytes for DUART */
DECL|macro|EV64260_EXT_FLASH_SIZE
mdefine_line|#define&t;EV64260_EXT_FLASH_SIZE&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_EXT_FLASH_SIZE_ACTUAL)
DECL|macro|EV64260_EMB_FLASH_SIZE
mdefine_line|#define&t;EV64260_EMB_FLASH_SIZE&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_EMB_FLASH_SIZE_ACTUAL)
DECL|macro|EV64260_EXT_SRAM_SIZE
mdefine_line|#define&t;EV64260_EXT_SRAM_SIZE&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_EXT_SRAM_SIZE_ACTUAL)
DECL|macro|EV64260_TODC_SIZE
mdefine_line|#define&t;EV64260_TODC_SIZE&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;EV64260_TODC_SIZE_ACTUAL)
multiline_comment|/* Assembler in bootwrapper blows up if &squot;max&squot; is used */
DECL|macro|EV64260_UART_SIZE
mdefine_line|#define&t;EV64260_UART_SIZE&t;&t;GT64260_WINDOW_SIZE_MIN
DECL|macro|EV64260_UART_END
mdefine_line|#define&t;EV64260_UART_END&t;&t;((EV64260_UART_BASE +&t;&t;&bslash;&n;&t;&t;&t;&t;&t;EV64260_UART_SIZE - 1) &amp; 0xfff00000)
multiline_comment|/* Board-specific IRQ info */
DECL|macro|EV64260_UART_0_IRQ
mdefine_line|#define&t;EV64260_UART_0_IRQ&t;&t;85
DECL|macro|EV64260_UART_1_IRQ
mdefine_line|#define&t;EV64260_UART_1_IRQ&t;&t;86
DECL|macro|EV64260_PCI_0_IRQ
mdefine_line|#define&t;EV64260_PCI_0_IRQ&t;&t;91
DECL|macro|EV64260_PCI_1_IRQ
mdefine_line|#define&t;EV64260_PCI_1_IRQ&t;&t;93
multiline_comment|/* Serial port setup */
DECL|macro|EV64260_DEFAULT_BAUD
mdefine_line|#define&t;EV64260_DEFAULT_BAUD&t;&t;115200
macro_line|#if defined(CONFIG_SERIAL_MPSC_CONSOLE)
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS
DECL|macro|EV64260_MPSC_CLK_SRC
mdefine_line|#define&t;EV64260_MPSC_CLK_SRC&t;&t;8&t;&t;/* TCLK */
DECL|macro|EV64260_MPSC_CLK_FREQ
mdefine_line|#define&t;EV64260_MPSC_CLK_FREQ&t;&t;100000000&t;/* 100MHz clk */
macro_line|#else
DECL|macro|EV64260_SERIAL_0
mdefine_line|#define EV64260_SERIAL_0&t;&t;(EV64260_UART_BASE + 0x20)
DECL|macro|EV64260_SERIAL_1
mdefine_line|#define EV64260_SERIAL_1&t;&t;EV64260_UART_BASE
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;(EV64260_DEFAULT_BAUD * 2)
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
multiline_comment|/* Required for bootloader&squot;s ns16550.c code */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &t;&t;&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, EV64260_SERIAL_0, EV64260_UART_0_IRQ, STD_COM_FLAGS, &bslash;&n;&t;iomem_base: (u8 *)EV64260_SERIAL_0,&t;/* ttyS0 */&t;&t;&bslash;&n;&t;iomem_reg_shift: 2,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif
macro_line|#endif /* __PPC_PLATFORMS_EV64260_H */
eof
