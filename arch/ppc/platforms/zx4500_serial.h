multiline_comment|/*&n; * arch/ppc/platforms/zx4500_serial.h&n; * &n; * Definitions for Znyx ZX4500 board support&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2000-2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_ZX4500_SERIAL_H
DECL|macro|__ASMPPC_ZX4500_SERIAL_H
mdefine_line|#define __ASMPPC_ZX4500_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Define the UART base address (only 1 UART) */
DECL|macro|ZX4500_SERIAL_1
mdefine_line|#define ZX4500_SERIAL_1&t;&t;&t;0xff880000
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  1
macro_line|#endif
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, ZX4500_SERIAL_1, 17, STD_COM_FLAGS, /* ttyS0 */&t;&bslash;&n;&t;&t;iomem_base: (u8 *)ZX4500_SERIAL_1,&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __ASMPPC_ZX4500_SERIAL_H */
eof
