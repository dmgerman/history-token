multiline_comment|/*&n; * include/asm-ppc/mvme5100_serial.h&n; * &n; * Definitions for Motorola MVME5100 support&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_MVME5100_SERIAL_H__
DECL|macro|__ASM_MVME5100_SERIAL_H__
mdefine_line|#define __ASM_MVME5100_SERIAL_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/mvme5100.h&gt;
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( MVME5100_BASE_BAUD / 16 )
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
multiline_comment|/* All UART IRQ&squot;s are wire-OR&squot;d to one MPIC IRQ */
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, MVME5100_SERIAL_1, &bslash;&n;&t;&t;MVME5100_SERIAL_IRQ, &bslash;&n;&t;&t;STD_COM_FLAGS, /* ttyS0 */ &bslash;&n;&t;&t;iomem_base: (unsigned char *)MVME5100_SERIAL_1,&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;&bslash;&n;        { 0, BASE_BAUD, MVME5100_SERIAL_2, &bslash;&n;&t;&t;MVME5100_SERIAL_IRQ, &bslash;&n;&t;&t;STD_COM_FLAGS, /* ttyS1 */ &bslash;&n;&t;&t;iomem_base: (unsigned char *)MVME5100_SERIAL_2,&t;&t;&bslash;&n;&t;&t;iomem_reg_shift: 4,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __ASM_MVME5100_SERIAL_H__ */
macro_line|#endif /* __KERNEL__ */
eof
