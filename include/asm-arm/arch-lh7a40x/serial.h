multiline_comment|/* include/asm-arm/arch-lh7a40x/serial.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
macro_line|#include &lt;asm/arch/registers.h&gt;
DECL|macro|UART_R_DATA
mdefine_line|#define UART_R_DATA&t;(0x00)
DECL|macro|UART_R_FCON
mdefine_line|#define UART_R_FCON&t;(0x04)
DECL|macro|UART_R_BRCON
mdefine_line|#define UART_R_BRCON&t;(0x08)
DECL|macro|UART_R_CON
mdefine_line|#define UART_R_CON&t;(0x0c)
DECL|macro|UART_R_STATUS
mdefine_line|#define UART_R_STATUS&t;(0x10)
DECL|macro|UART_R_RAWISR
mdefine_line|#define UART_R_RAWISR&t;(0x14)
DECL|macro|UART_R_INTEN
mdefine_line|#define UART_R_INTEN&t;(0x18)
DECL|macro|UART_R_ISR
mdefine_line|#define UART_R_ISR&t;(0x1c)
macro_line|#endif  /* _ASM_ARCH_SERIAL_H */
eof
