multiline_comment|/*&n; * include/asm-ppc/platforms/spruce.h&n; *&n; * Definitions for IBM Spruce reference board support&n; *&n; * Authors: Matt Porter and Johnnie Peters&n; *          mporter@mvista.com&n; *          jpeters@mvista.com&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SPRUCE_H__
DECL|macro|__ASM_SPRUCE_H__
mdefine_line|#define __ASM_SPRUCE_H__
DECL|macro|SPRUCE_PCI_CONFIG_ADDR
mdefine_line|#define SPRUCE_PCI_CONFIG_ADDR&t;0xfec00000
DECL|macro|SPRUCE_PCI_CONFIG_DATA
mdefine_line|#define SPRUCE_PCI_CONFIG_DATA&t;0xfec00004
DECL|macro|SPRUCE_PCI_PHY_IO_BASE
mdefine_line|#define SPRUCE_PCI_PHY_IO_BASE&t;0xf8000000
DECL|macro|SPRUCE_PCI_IO_BASE
mdefine_line|#define SPRUCE_PCI_IO_BASE&t;SPRUCE_PCI_PHY_IO_BASE
DECL|macro|SPRUCE_PCI_SYS_MEM_BASE
mdefine_line|#define SPRUCE_PCI_SYS_MEM_BASE&t;0x00000000
DECL|macro|SPRUCE_PCI_LOWER_MEM
mdefine_line|#define SPRUCE_PCI_LOWER_MEM&t;0x80000000
DECL|macro|SPRUCE_PCI_UPPER_MEM
mdefine_line|#define SPRUCE_PCI_UPPER_MEM&t;0x9fffffff
DECL|macro|SPRUCE_PCI_LOWER_IO
mdefine_line|#define SPRUCE_PCI_LOWER_IO&t;0x00000000
DECL|macro|SPRUCE_PCI_UPPER_IO
mdefine_line|#define SPRUCE_PCI_UPPER_IO&t;0x03ffffff
DECL|macro|SPRUCE_ISA_IO_BASE
mdefine_line|#define&t;SPRUCE_ISA_IO_BASE&t;SPRUCE_PCI_IO_BASE
DECL|macro|SPRUCE_MEM_SIZE
mdefine_line|#define SPRUCE_MEM_SIZE&t;&t;0x04000000
DECL|macro|SPRUCE_BUS_SPEED
mdefine_line|#define SPRUCE_BUS_SPEED&t;66666667
DECL|macro|SPRUCE_NVRAM_BASE_ADDR
mdefine_line|#define SPRUCE_NVRAM_BASE_ADDR&t;0xff800000
DECL|macro|SPRUCE_RTC_BASE_ADDR
mdefine_line|#define SPRUCE_RTC_BASE_ADDR&t;SPRUCE_NVRAM_BASE_ADDR
multiline_comment|/*&n; * Serial port defines&n; */
DECL|macro|SPRUCE_FPGA_REG_A
mdefine_line|#define SPRUCE_FPGA_REG_A&t;0xff820000
DECL|macro|SPRUCE_UARTCLK_33M
mdefine_line|#define SPRUCE_UARTCLK_33M&t;0x02
DECL|macro|SPRUCE_UARTCLK_IS_33M
mdefine_line|#define SPRUCE_UARTCLK_IS_33M(reg)&t;(reg &amp; SPRUCE_UARTCLK_33M)
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE&t;0xff600300
DECL|macro|UART1_IO_BASE
mdefine_line|#define UART1_IO_BASE&t;0xff600400
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;2
DECL|macro|SPRUCE_BAUD_33M
mdefine_line|#define SPRUCE_BAUD_33M&t;(33000000/64)
DECL|macro|SPRUCE_BAUD_30M
mdefine_line|#define SPRUCE_BAUD_30M&t;(30000000/64)
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;SPRUCE_BAUD_33M
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT&t;3
DECL|macro|UART1_INT
mdefine_line|#define UART1_INT&t;4
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0, UART##num##_INT,&t;&t;&bslash;&n;&t;&t;ASYNC_BOOT_AUTOCONF,&t;&t;&t;&bslash;&n;&t;&t;iomem_base: UART##num##_IO_BASE,&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM},
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;STD_UART_OP(0)&t;&t;&bslash;&n;&t;STD_UART_OP(1)
macro_line|#endif /* __ASM_SPRUCE_H__ */
macro_line|#endif /* __KERNEL__ */
eof
