multiline_comment|/*&n; * include/asm-sh/serial-bigsur.h&n; *&n; * Configuration details for Big Sur 16550 based serial ports &n; * i.e. HD64465, PCMCIA, etc.&n; */
macro_line|#ifndef _ASM_SERIAL_BIGSUR_H
DECL|macro|_ASM_SERIAL_BIGSUR_H
mdefine_line|#define _ASM_SERIAL_BIGSUR_H
macro_line|#include &lt;asm/hd64465.h&gt;
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (3379200 / 16)
multiline_comment|/* Leave 2 spare for possible PCMCIA serial cards */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  3
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS                   &bslash;&n;        /* UART CLK   PORT IRQ     FLAGS        */                      &bslash;&n;        { 0, BASE_BAUD, 0x3F8, HD64465_IRQ_UART, STD_COM_FLAGS } /* ttyS0 */ 
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS STD_SERIAL_PORT_DEFNS
multiline_comment|/* XXX: This should be moved ino irq.h */
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(x) (x)
macro_line|#endif /* _ASM_SERIAL_BIGSUR_H */
eof
