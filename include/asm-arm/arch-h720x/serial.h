multiline_comment|/*&n; * linux/include/asm-arm/arch-h72x/serial.h&n; *&n; * Copyright (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *               2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *&n; * Serial port setup for Hynix boards&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
macro_line|#include &lt;asm/arch/irqs.h&gt;
multiline_comment|/*&n; * Standard COM flags&n; */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE
multiline_comment|/* Base clock is 3.6864 MHz */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD       (115200*2)
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
multiline_comment|/*&n; * Board dependend defines&n; */
macro_line|#if defined (CONFIG_CPU_H7201)
DECL|macro|BASE_BAUD_P3C
mdefine_line|#define BASE_BAUD_P3C &t;(115200)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS &bslash;&n;&t;{ &bslash;&n;&t;.baud_base&t;= BASE_BAUD, &bslash;&n;&t;.port&t;&t;= SERIAL0_BASE, &bslash;&n;&t;.iomem_base     = (u8*)SERIAL0_BASE, &bslash;&n;&t;.io_type        = UPIO_MEM, &bslash;&n;&t;.irq&t;&t;= IRQ_UART0, &bslash;&n;&t;.flags&t;&t;= STD_COM_FLAGS, &bslash;&n;&t;.iomem_reg_shift = 2,&bslash;&n;&t;}, &bslash;&n;&t;{ &bslash;&n;&t;.baud_base&t;= BASE_BAUD, &bslash;&n;&t;.port&t;&t;= SERIAL1_BASE, &bslash;&n;&t;.iomem_base     = (u8*)SERIAL1_BASE, &bslash;&n;&t;.io_type        = UPIO_MEM, &bslash;&n;&t;.irq&t;&t;= IRQ_UART1, &bslash;&n;&t;.flags&t;&t;= STD_COM_FLAGS, &bslash;&n;&t;.iomem_reg_shift = 2,&bslash;&n;&t;}
macro_line|#elif defined (CONFIG_CPU_H7202)
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS &bslash;&n;&t;{ &bslash;&n;&t;.baud_base&t;= BASE_BAUD, &bslash;&n;&t;.port&t;&t;= SERIAL0_BASE, &bslash;&n;&t;.iomem_base     = (u8*)SERIAL0_BASE, &bslash;&n;&t;.io_type        = UPIO_MEM, &bslash;&n;&t;.irq&t;&t;= IRQ_UART0, &bslash;&n;&t;.flags&t;&t;= STD_COM_FLAGS, &bslash;&n;&t;.iomem_reg_shift = 2,&bslash;&n;&t;}, &bslash;&n;&t;{ &bslash;&n;&t;.baud_base&t;= BASE_BAUD, &bslash;&n;&t;.port&t;&t;= SERIAL1_BASE, &bslash;&n;&t;.iomem_base     = (u8*)SERIAL1_BASE, &bslash;&n;&t;.io_type        = UPIO_MEM, &bslash;&n;&t;.irq&t;&t;= IRQ_UART1, &bslash;&n;&t;.flags&t;&t;= STD_COM_FLAGS, &bslash;&n;&t;.iomem_reg_shift = 2,&bslash;&n;&t;}, &bslash;&n;&t;{ &bslash;&n;&t;.baud_base&t;= BASE_BAUD, &bslash;&n;&t;.port&t;&t;= SERIAL2_BASE, &bslash;&n;&t;.iomem_base     = (u8*)SERIAL2_BASE, &bslash;&n;&t;.io_type        = UPIO_MEM, &bslash;&n;&t;.irq&t;&t;= IRQ_UART2, &bslash;&n;&t;.flags&t;&t;= STD_COM_FLAGS, &bslash;&n;&t;.iomem_reg_shift = 2,&bslash;&n;&t;}, &bslash;&n;&t;{ &bslash;&n;&t;.baud_base&t;= BASE_BAUD, &bslash;&n;&t;.port&t;&t;= SERIAL3_BASE, &bslash;&n;&t;.iomem_base     = (u8*)SERIAL3_BASE, &bslash;&n;&t;.io_type        = UPIO_MEM, &bslash;&n;&t;.irq&t;&t;= IRQ_UART3, &bslash;&n;&t;.flags&t;&t;= STD_COM_FLAGS, &bslash;&n;&t;.iomem_reg_shift = 2,&bslash;&n;&t;}
macro_line|#else
macro_line|#error machine definition mismatch
macro_line|#endif
multiline_comment|/* __ASM_ARCH_SERIAL_H */
macro_line|#endif
eof
