multiline_comment|/*&n; * BK Id: SCCS/s.ppc4xx_serial.h 1.3 05/17/01 18:14:25 cort&n; */
multiline_comment|/*&n; *    Copyright 2000 MontaVista Software Inc.&n; *&t;PPC405GP modifications&n; * &t;Author: MontaVista Software, Inc.&n; *         &t;frank_rowand@mvista.com or source@mvista.com&n; * &t;   &t;debbie_chu@mvista.com&n; *&n; *    Module name: ppc405_serial.h&n; *&n; *    Description:&n; *      Macros, definitions, and data structures specific to the IBM PowerPC&n; *      405 on-chip serial port devices.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASMPPC_PPC4xx_SERIAL_H
DECL|macro|__ASMPPC_PPC4xx_SERIAL_H
mdefine_line|#define __ASMPPC_PPC4xx_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;4
macro_line|#endif
DECL|macro|PPC405GP_UART0_INT
mdefine_line|#define PPC405GP_UART0_INT&t;0
DECL|macro|PPC405GP_UART1_INT
mdefine_line|#define PPC405GP_UART1_INT&t;1
multiline_comment|/*&n;** 405GP UARTs are *not* PCI devices, so need to specify a non-pci memory&n;** address and an io_type of SERIAL_IO_MEM.&n;*/
DECL|macro|PPC405GP_UART0_IO_BASE
mdefine_line|#define PPC405GP_UART0_IO_BASE&t;(u8 *) 0xef600300
DECL|macro|PPC405GP_UART1_IO_BASE
mdefine_line|#define PPC405GP_UART1_IO_BASE&t;(u8 *) 0xef600400
multiline_comment|/*&n;**  - there is no config option for this&n;**  - this name could be more informative&n;**  - also see arch/ppc/kernel/ppc405_serial.c&n;**&n;** #define CONFIG_PPC405GP_INTERNAL_CLOCK&n;*/
macro_line|#ifdef&t;CONFIG_PPC405GP_INTERNAL_CLOCK
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;201600
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;691200
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST | ASYNC_AUTO_IRQ)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS&t;(ASYNC_BOOT_AUTOCONF | ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS&t;(ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS&t;(ASYNC_BOOT_AUTOCONF)
macro_line|#endif
macro_line|#ifdef CONFIG_STB03XXX
DECL|macro|UART0_IO_BASE
mdefine_line|#define UART0_IO_BASE 0x40040000
DECL|macro|UART0_INT
mdefine_line|#define UART0_INT     20
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;    /* ttyS0 */ &bslash;&n;    { 0, BASE_BAUD, 0, UART0_INT, STD_COM_FLAGS, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;    UART0_IO_BASE, 0, 0, 0, {}, {}, {}, SERIAL_IO_MEM, NULL },
macro_line|#elif defined(CONFIG_UART1_DFLT_CONSOLE)
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;    /* ttyS1 */ &bslash;&n;    { 0, BASE_BAUD, 0, PPC405GP_UART1_INT, STD_COM_FLAGS, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;    PPC405GP_UART1_IO_BASE, 0, 0, 0, {}, {}, {}, SERIAL_IO_MEM, NULL },        &bslash;&n;    /* ttyS0 */ &bslash;&n;    { 0, BASE_BAUD, 0, PPC405GP_UART0_INT, STD_COM_FLAGS, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;    PPC405GP_UART0_IO_BASE, 0, 0, 0, {}, {}, {}, SERIAL_IO_MEM, NULL },
macro_line|#else
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;    /* ttyS0 */ &bslash;&n;    { 0, BASE_BAUD, 0, PPC405GP_UART0_INT, STD_COM_FLAGS, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;    PPC405GP_UART0_IO_BASE, 0, 0, 0, {}, {}, {}, SERIAL_IO_MEM, NULL },        &bslash;&n;    /* ttyS1 */ &bslash;&n;    { 0, BASE_BAUD, 0, PPC405GP_UART1_INT, STD_COM_FLAGS, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;    PPC405GP_UART1_IO_BASE, 0, 0, 0, {}, {}, {}, SERIAL_IO_MEM, NULL },
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS     &bslash;&n;&t;STD_SERIAL_PORT_DFNS &bslash;&n;&t;{}
macro_line|#endif&t;/* __ASMPPC_PPC4xx_SERIAL_H */
macro_line|#endif /* __KERNEL__ */
eof
