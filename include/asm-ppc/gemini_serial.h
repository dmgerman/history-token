multiline_comment|/*&n; * BK Id: SCCS/s.gemini_serial.h 1.5 05/17/01 18:14:24 cort&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASMPPC_GEMINI_SERIAL_H
DECL|macro|__ASMPPC_GEMINI_SERIAL_H
mdefine_line|#define __ASMPPC_GEMINI_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/gemini.h&gt;
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
multiline_comment|/* Rate for the 24.576 Mhz clock for the onboard serial chip */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  (24576000 / 16)
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
DECL|macro|STD_COM4_FLAGS
mdefine_line|#define STD_COM4_FLAGS (ASYNC_BOOT_AUTOCONF)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS &bslash;&n;        { 0, BASE_BAUD, GEMINI_SERIAL_A, 15, STD_COM_FLAGS }, /* ttyS0 */ &bslash;&n;        { 0, BASE_BAUD, GEMINI_SERIAL_B, 14, STD_COM_FLAGS }, /* ttyS1 */ &bslash;&n;
macro_line|#ifdef CONFIG_GEMINI_PU32
DECL|macro|PU32_SERIAL_PORT_DEFNS
mdefine_line|#define PU32_SERIAL_PORT_DEFNS &bslash;&n;        { 0, BASE_BAUD, NULL, 0, STD_COM_FLAGS },
macro_line|#else
DECL|macro|PU32_SERIAL_PORT_DEFNS
mdefine_line|#define PU32_SERIAL_PORT_DEFNS
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DEFNS &bslash;&n;        PU32_SERIAL_PORT_DEFNS
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
