multiline_comment|/*&n; * arch/ppc/platforms/sandpoint.h&n; * &n; * Definitions for Motorola SPS Sandpoint Test Platform&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2000-2003 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * Sandpoint uses the CHRP map (Map B).&n; */
macro_line|#ifndef __PPC_PLATFORMS_SANDPOINT_H
DECL|macro|__PPC_PLATFORMS_SANDPOINT_H
mdefine_line|#define __PPC_PLATFORMS_SANDPOINT_H
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#if 0
multiline_comment|/* The Sandpoint X3 allows the IDE interrupt to be directly connected&n; * from the Windbond (PCI INTC or INTD) to the serial EPIC.  Someday&n; * we should try this, but it was easier to use the existing 83c553&n; * initialization than change it to route the different interrupts :-).&n; *&t;-- Dan&n; */
mdefine_line|#define SANDPOINT_IDE_INT0&t;&t;23&t;/* EPIC 7 */
mdefine_line|#define SANDPOINT_IDE_INT1&t;&t;24&t;/* EPIC 8 */
macro_line|#else
DECL|macro|SANDPOINT_IDE_INT0
mdefine_line|#define SANDPOINT_IDE_INT0&t;&t;14&t;/* 8259 Test */
DECL|macro|SANDPOINT_IDE_INT1
mdefine_line|#define SANDPOINT_IDE_INT1&t;&t;15&t;/* 8259 Test */
macro_line|#endif
multiline_comment|/*&n; * The sandpoint boards have processor modules that either have an 8240 or&n; * an MPC107 host bridge on them.  These bridges have an IDSEL line that allows&n; * them to respond to PCI transactions as if they were a normal PCI devices.&n; * However, the processor on the processor side of the bridge can not reach&n; * out onto the PCI bus and then select the bridge or bad things will happen&n; * (documented in the 8240 and 107 manuals).&n; * Because of this, we always skip the bridge PCI device when accessing the&n; * PCI bus.  The PCI slot that the bridge occupies is defined by the macro&n; * below.&n; */
DECL|macro|SANDPOINT_HOST_BRIDGE_IDSEL
mdefine_line|#define SANDPOINT_HOST_BRIDGE_IDSEL     12
multiline_comment|/*&n; * Serial defines.&n; */
DECL|macro|SANDPOINT_SERIAL_0
mdefine_line|#define SANDPOINT_SERIAL_0&t;&t;0xfe0003f8
DECL|macro|SANDPOINT_SERIAL_1
mdefine_line|#define SANDPOINT_SERIAL_1&t;&t;0xfe0002f8
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
multiline_comment|/* Rate for the 1.8432 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;&t;( 1843200 / 16 )
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;&t;&t;1843200
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, SANDPOINT_SERIAL_0, 4, STD_COM_FLAGS, /* ttyS0 */ &bslash;&n;&t;&t;iomem_base: (u8 *)SANDPOINT_SERIAL_0,&t;&t;&t;  &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;  &bslash;&n;        { 0, BASE_BAUD, SANDPOINT_SERIAL_1, 3, STD_COM_FLAGS, /* ttyS1 */ &bslash;&n;&t;&t;iomem_base: (u8 *)SANDPOINT_SERIAL_1,&t;&t;&t;  &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __PPC_PLATFORMS_SANDPOINT_H */
eof
