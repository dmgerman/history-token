multiline_comment|/*&n; * include/asm-ppc/platforms/prpmc750_serial.h&n; * &n; * Motorola PrPMC750 serial support&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PRPMC750_SERIAL_H__
DECL|macro|__ASM_PRPMC750_SERIAL_H__
mdefine_line|#define __ASM_PRPMC750_SERIAL_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;platforms/prpmc750.h&gt;
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  (PRPMC750_BASE_BAUD / 16)
macro_line|#ifndef SERIAL_MAGIC_KEY
DECL|macro|kernel_debugger
mdefine_line|#define kernel_debugger ppc_kernel_debug
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, PRPMC750_SERIAL_0, 1, STD_COM_FLAGS, &bslash;&n;&t;&t;iomem_base: (unsigned char *)PRPMC750_SERIAL_0, &bslash;&n;&t;&t;iomem_reg_shift: 4, &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM } /* ttyS0 */
macro_line|#endif /* __ASM_PRPMC750_SERIAL_H__ */
macro_line|#endif /* __KERNEL__ */
eof
