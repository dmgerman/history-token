multiline_comment|/* cpu-irqs.h: on-CPU peripheral irqs&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_CPU_IRQS_H
DECL|macro|_ASM_CPU_IRQS_H
mdefine_line|#define _ASM_CPU_IRQS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/irq-routing.h&gt;
DECL|macro|IRQ_BASE_CPU
mdefine_line|#define IRQ_BASE_CPU&t;&t;(NR_IRQ_ACTIONS_PER_GROUP * 0)
multiline_comment|/* IRQ IDs presented to drivers */
r_enum
(brace
DECL|enumerator|IRQ_CPU__UNUSED
id|IRQ_CPU__UNUSED
op_assign
id|IRQ_BASE_CPU
comma
DECL|enumerator|IRQ_CPU_UART0
id|IRQ_CPU_UART0
comma
DECL|enumerator|IRQ_CPU_UART1
id|IRQ_CPU_UART1
comma
DECL|enumerator|IRQ_CPU_TIMER0
id|IRQ_CPU_TIMER0
comma
DECL|enumerator|IRQ_CPU_TIMER1
id|IRQ_CPU_TIMER1
comma
DECL|enumerator|IRQ_CPU_TIMER2
id|IRQ_CPU_TIMER2
comma
DECL|enumerator|IRQ_CPU_DMA0
id|IRQ_CPU_DMA0
comma
DECL|enumerator|IRQ_CPU_DMA1
id|IRQ_CPU_DMA1
comma
DECL|enumerator|IRQ_CPU_DMA2
id|IRQ_CPU_DMA2
comma
DECL|enumerator|IRQ_CPU_DMA3
id|IRQ_CPU_DMA3
comma
DECL|enumerator|IRQ_CPU_DMA4
id|IRQ_CPU_DMA4
comma
DECL|enumerator|IRQ_CPU_DMA5
id|IRQ_CPU_DMA5
comma
DECL|enumerator|IRQ_CPU_DMA6
id|IRQ_CPU_DMA6
comma
DECL|enumerator|IRQ_CPU_DMA7
id|IRQ_CPU_DMA7
comma
DECL|enumerator|IRQ_CPU_EXTERNAL0
id|IRQ_CPU_EXTERNAL0
comma
DECL|enumerator|IRQ_CPU_EXTERNAL1
id|IRQ_CPU_EXTERNAL1
comma
DECL|enumerator|IRQ_CPU_EXTERNAL2
id|IRQ_CPU_EXTERNAL2
comma
DECL|enumerator|IRQ_CPU_EXTERNAL3
id|IRQ_CPU_EXTERNAL3
comma
DECL|enumerator|IRQ_CPU_EXTERNAL4
id|IRQ_CPU_EXTERNAL4
comma
DECL|enumerator|IRQ_CPU_EXTERNAL5
id|IRQ_CPU_EXTERNAL5
comma
DECL|enumerator|IRQ_CPU_EXTERNAL6
id|IRQ_CPU_EXTERNAL6
comma
DECL|enumerator|IRQ_CPU_EXTERNAL7
id|IRQ_CPU_EXTERNAL7
comma
)brace
suffix:semicolon
multiline_comment|/* IRQ to level mappings */
DECL|macro|IRQ_GDBSTUB_LEVEL
mdefine_line|#define IRQ_GDBSTUB_LEVEL&t;15
DECL|macro|IRQ_UART_LEVEL
mdefine_line|#define IRQ_UART_LEVEL&t;&t;13
macro_line|#ifdef CONFIG_GDBSTUB_UART0
DECL|macro|IRQ_UART0_LEVEL
mdefine_line|#define IRQ_UART0_LEVEL&t;&t;IRQ_GDBSTUB_LEVEL
macro_line|#else
DECL|macro|IRQ_UART0_LEVEL
mdefine_line|#define IRQ_UART0_LEVEL&t;&t;IRQ_UART_LEVEL
macro_line|#endif
macro_line|#ifdef CONFIG_GDBSTUB_UART1
DECL|macro|IRQ_UART1_LEVEL
mdefine_line|#define IRQ_UART1_LEVEL&t;&t;IRQ_GDBSTUB_LEVEL
macro_line|#else
DECL|macro|IRQ_UART1_LEVEL
mdefine_line|#define IRQ_UART1_LEVEL&t;&t;IRQ_UART_LEVEL
macro_line|#endif
DECL|macro|IRQ_DMA0_LEVEL
mdefine_line|#define IRQ_DMA0_LEVEL&t;&t;14
DECL|macro|IRQ_DMA1_LEVEL
mdefine_line|#define IRQ_DMA1_LEVEL&t;&t;14
DECL|macro|IRQ_DMA2_LEVEL
mdefine_line|#define IRQ_DMA2_LEVEL&t;&t;14
DECL|macro|IRQ_DMA3_LEVEL
mdefine_line|#define IRQ_DMA3_LEVEL&t;&t;14
DECL|macro|IRQ_DMA4_LEVEL
mdefine_line|#define IRQ_DMA4_LEVEL&t;&t;14
DECL|macro|IRQ_DMA5_LEVEL
mdefine_line|#define IRQ_DMA5_LEVEL&t;&t;14
DECL|macro|IRQ_DMA6_LEVEL
mdefine_line|#define IRQ_DMA6_LEVEL&t;&t;14
DECL|macro|IRQ_DMA7_LEVEL
mdefine_line|#define IRQ_DMA7_LEVEL&t;&t;14
DECL|macro|IRQ_TIMER0_LEVEL
mdefine_line|#define IRQ_TIMER0_LEVEL&t;12
DECL|macro|IRQ_TIMER1_LEVEL
mdefine_line|#define IRQ_TIMER1_LEVEL&t;11
DECL|macro|IRQ_TIMER2_LEVEL
mdefine_line|#define IRQ_TIMER2_LEVEL&t;10
DECL|macro|IRQ_XIRQ0_LEVEL
mdefine_line|#define IRQ_XIRQ0_LEVEL&t;&t;1
DECL|macro|IRQ_XIRQ1_LEVEL
mdefine_line|#define IRQ_XIRQ1_LEVEL&t;&t;2
DECL|macro|IRQ_XIRQ2_LEVEL
mdefine_line|#define IRQ_XIRQ2_LEVEL&t;&t;3
DECL|macro|IRQ_XIRQ3_LEVEL
mdefine_line|#define IRQ_XIRQ3_LEVEL&t;&t;4
DECL|macro|IRQ_XIRQ4_LEVEL
mdefine_line|#define IRQ_XIRQ4_LEVEL&t;&t;5
DECL|macro|IRQ_XIRQ5_LEVEL
mdefine_line|#define IRQ_XIRQ5_LEVEL&t;&t;6
DECL|macro|IRQ_XIRQ6_LEVEL
mdefine_line|#define IRQ_XIRQ6_LEVEL&t;&t;7
DECL|macro|IRQ_XIRQ7_LEVEL
mdefine_line|#define IRQ_XIRQ7_LEVEL&t;&t;8
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_CPU_IRQS_H */
eof
