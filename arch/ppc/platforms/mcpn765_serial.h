multiline_comment|/*&n; * include/asm-ppc/mcpn765_serial.h&n; * &n; * Definitions for Motorola MCG MCPN765 cPCI board support&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_MCPN765_SERIAL_H
DECL|macro|__ASMPPC_MCPN765_SERIAL_H
mdefine_line|#define __ASMPPC_MCPN765_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Define the UART base addresses */
DECL|macro|MCPN765_SERIAL_1
mdefine_line|#define&t;MCPN765_SERIAL_1&t;&t;0xfef88000
DECL|macro|MCPN765_SERIAL_2
mdefine_line|#define&t;MCPN765_SERIAL_2&t;&t;0xfef88200
DECL|macro|MCPN765_SERIAL_3
mdefine_line|#define&t;MCPN765_SERIAL_3&t;&t;0xfef88400
DECL|macro|MCPN765_SERIAL_4
mdefine_line|#define&t;MCPN765_SERIAL_4&t;&t;0xfef88600
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;( 1843200 / 16 )
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;1843200
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
multiline_comment|/* All UART IRQ&squot;s are wire-OR&squot;d to IRQ 17 */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_1, 17, STD_COM_FLAGS, /* ttyS0 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_1,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_2, 17, STD_COM_FLAGS, /* ttyS1 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_2,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_3, 17, STD_COM_FLAGS, /* ttyS2 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_3,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MCPN765_SERIAL_4, 17, STD_COM_FLAGS, /* ttyS3 */&bslash;&n;&t;&t;iomem_base: (u8 *)MCPN765_SERIAL_4,&t;&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __ASMPPC_MCPN765_SERIAL_H */
eof
