multiline_comment|/* irq-routing.c: IRQ routing&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq-routing.h&gt;
macro_line|#include &lt;asm/irc-regs.h&gt;
macro_line|#include &lt;asm/serial-regs.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
DECL|variable|frv_irq_levels
r_struct
id|irq_level
id|frv_irq_levels
(braket
l_int|16
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|15
)braket
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
)brace
)brace
suffix:semicolon
DECL|variable|irq_groups
r_struct
id|irq_group
op_star
id|irq_groups
(braket
id|NR_IRQ_GROUPS
)braket
suffix:semicolon
r_extern
r_struct
id|irq_group
id|frv_cpu_irqs
suffix:semicolon
DECL|function|frv_irq_route
r_void
id|__init
id|frv_irq_route
c_func
(paren
r_struct
id|irq_source
op_star
id|source
comma
r_int
id|irqlevel
)paren
(brace
id|source-&gt;level
op_assign
op_amp
id|frv_irq_levels
(braket
id|irqlevel
)braket
suffix:semicolon
id|source-&gt;next
op_assign
id|frv_irq_levels
(braket
id|irqlevel
)braket
dot
id|sources
suffix:semicolon
id|frv_irq_levels
(braket
id|irqlevel
)braket
dot
id|sources
op_assign
id|source
suffix:semicolon
)brace
DECL|function|frv_irq_route_external
r_void
id|__init
id|frv_irq_route_external
c_func
(paren
r_struct
id|irq_source
op_star
id|source
comma
r_int
id|irq
)paren
(brace
r_int
id|irqlevel
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_CPU_EXTERNAL0
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ0_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL1
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ1_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL2
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ2_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL3
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ3_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL4
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ4_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL5
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ5_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL6
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ6_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_CPU_EXTERNAL7
suffix:colon
id|irqlevel
op_assign
id|IRQ_XIRQ7_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|source-&gt;level
op_assign
op_amp
id|frv_irq_levels
(braket
id|irqlevel
)braket
suffix:semicolon
id|source-&gt;next
op_assign
id|frv_irq_levels
(braket
id|irqlevel
)braket
dot
id|sources
suffix:semicolon
id|frv_irq_levels
(braket
id|irqlevel
)braket
dot
id|sources
op_assign
id|source
suffix:semicolon
)brace
DECL|function|frv_irq_set_group
r_void
id|__init
id|frv_irq_set_group
c_func
(paren
r_struct
id|irq_group
op_star
id|group
)paren
(brace
id|irq_groups
(braket
id|group-&gt;first_irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)braket
op_assign
id|group
suffix:semicolon
)brace
DECL|function|distribute_irqs
r_void
id|distribute_irqs
c_func
(paren
r_struct
id|irq_group
op_star
id|group
comma
r_int
r_int
id|irqmask
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_while
c_loop
(paren
id|irqmask
)paren
(brace
id|asm
c_func
(paren
l_string|&quot;scan %1,gr0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|irq
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|irqmask
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
template_param
l_int|31
)paren
id|asm
r_volatile
(paren
l_string|&quot;break&quot;
)paren
suffix:semicolon
id|irq
op_assign
l_int|31
op_minus
id|irq
suffix:semicolon
id|irqmask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|action
op_assign
id|group-&gt;actions
(braket
id|irq
)braket
suffix:semicolon
id|irq
op_add_assign
id|group-&gt;first_irq
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
singleline_comment|//&t;&t;&t;if (!(action-&gt;flags &amp; SA_INTERRUPT))
singleline_comment|//&t;&t;&t;&t;sti();
r_do
(brace
id|status
op_or_assign
id|action-&gt;flags
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|__frame
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * CPU UART interrupts&n; */
DECL|function|frv_cpuuart_doirq
r_static
r_void
id|frv_cpuuart_doirq
c_func
(paren
r_struct
id|irq_source
op_star
id|source
)paren
(brace
singleline_comment|//&t;uint8_t iir = readb(source-&gt;muxdata + UART_IIR * 8);
singleline_comment|//&t;if ((iir &amp; 0x0f) != UART_IIR_NO_INT)
id|distribute_irqs
c_func
(paren
op_amp
id|frv_cpu_irqs
comma
id|source-&gt;irqmask
)paren
suffix:semicolon
)brace
DECL|variable|frv_cpuuart
r_struct
id|irq_source
id|frv_cpuuart
(braket
l_int|2
)braket
op_assign
(brace
DECL|macro|__CPUUART
mdefine_line|#define __CPUUART(X, A)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[X] = {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.muxname&t;= &quot;uart&quot;,&t;&t;&t;&bslash;&n;&t;&t;.muxdata&t;= (volatile void __iomem *) A,&t;&bslash;&n;&t;&t;.irqmask&t;= 1 &lt;&lt; IRQ_CPU_UART##X,&t;&t;&bslash;&n;&t;&t;.doirq&t;&t;= frv_cpuuart_doirq,&t;&t;&bslash;&n;&t;}
id|__CPUUART
c_func
(paren
l_int|0
comma
id|UART0_BASE
)paren
comma
id|__CPUUART
c_func
(paren
l_int|1
comma
id|UART1_BASE
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * CPU DMA interrupts&n; */
DECL|function|frv_cpudma_doirq
r_static
r_void
id|frv_cpudma_doirq
c_func
(paren
r_struct
id|irq_source
op_star
id|source
)paren
(brace
r_uint32
id|cstr
op_assign
id|readl
c_func
(paren
id|source-&gt;muxdata
op_plus
id|DMAC_CSTRx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cstr
op_amp
id|DMAC_CSTRx_INT
)paren
id|distribute_irqs
c_func
(paren
op_amp
id|frv_cpu_irqs
comma
id|source-&gt;irqmask
)paren
suffix:semicolon
)brace
DECL|variable|frv_cpudma
r_struct
id|irq_source
id|frv_cpudma
(braket
l_int|8
)braket
op_assign
(brace
DECL|macro|__CPUDMA
mdefine_line|#define __CPUDMA(X, A)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[X] = {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.muxname&t;= &quot;dma&quot;,&t;&t;&t;&bslash;&n;&t;&t;.muxdata&t;= (volatile void __iomem *) A,&t;&bslash;&n;&t;&t;.irqmask&t;= 1 &lt;&lt; IRQ_CPU_DMA##X,&t;&t;&bslash;&n;&t;&t;.doirq&t;&t;= frv_cpudma_doirq,&t;&t;&bslash;&n;&t;}
id|__CPUDMA
c_func
(paren
l_int|0
comma
l_int|0xfe000900
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|1
comma
l_int|0xfe000980
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|2
comma
l_int|0xfe000a00
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|3
comma
l_int|0xfe000a80
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|4
comma
l_int|0xfe001000
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|5
comma
l_int|0xfe001080
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|6
comma
l_int|0xfe001100
)paren
comma
id|__CPUDMA
c_func
(paren
l_int|7
comma
l_int|0xfe001180
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * CPU timer interrupts - can&squot;t tell whether they&squot;ve generated an interrupt or not&n; */
DECL|function|frv_cputimer_doirq
r_static
r_void
id|frv_cputimer_doirq
c_func
(paren
r_struct
id|irq_source
op_star
id|source
)paren
(brace
id|distribute_irqs
c_func
(paren
op_amp
id|frv_cpu_irqs
comma
id|source-&gt;irqmask
)paren
suffix:semicolon
)brace
DECL|variable|frv_cputimer
r_struct
id|irq_source
id|frv_cputimer
(braket
l_int|3
)braket
op_assign
(brace
DECL|macro|__CPUTIMER
mdefine_line|#define __CPUTIMER(X)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[X] = {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.muxname&t;= &quot;timer&quot;,&t;&t;&t;&bslash;&n;&t;&t;.muxdata&t;= 0,&t;&t;&t;&t;&bslash;&n;&t;&t;.irqmask&t;= 1 &lt;&lt; IRQ_CPU_TIMER##X,&t;&bslash;&n;&t;&t;.doirq&t;&t;= frv_cputimer_doirq,&t;&t;&bslash;&n;&t;}
id|__CPUTIMER
c_func
(paren
l_int|0
)paren
comma
id|__CPUTIMER
c_func
(paren
l_int|1
)paren
comma
id|__CPUTIMER
c_func
(paren
l_int|2
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * external CPU interrupts - can&squot;t tell directly whether they&squot;ve generated an interrupt or not&n; */
DECL|function|frv_cpuexternal_doirq
r_static
r_void
id|frv_cpuexternal_doirq
c_func
(paren
r_struct
id|irq_source
op_star
id|source
)paren
(brace
id|distribute_irqs
c_func
(paren
op_amp
id|frv_cpu_irqs
comma
id|source-&gt;irqmask
)paren
suffix:semicolon
)brace
DECL|variable|frv_cpuexternal
r_struct
id|irq_source
id|frv_cpuexternal
(braket
l_int|8
)braket
op_assign
(brace
DECL|macro|__CPUEXTERNAL
mdefine_line|#define __CPUEXTERNAL(X)&t;&t;&t;&t;&t;&bslash;&n;&t;[X] = {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.muxname&t;= &quot;ext&quot;,&t;&t;&t;&bslash;&n;&t;&t;.muxdata&t;= 0,&t;&t;&t;&t;&bslash;&n;&t;&t;.irqmask&t;= 1 &lt;&lt; IRQ_CPU_EXTERNAL##X,&t;&bslash;&n;&t;&t;.doirq&t;&t;= frv_cpuexternal_doirq,&t;&bslash;&n;&t;}
id|__CPUEXTERNAL
c_func
(paren
l_int|0
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|1
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|2
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|3
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|4
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|5
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|6
)paren
comma
id|__CPUEXTERNAL
c_func
(paren
l_int|7
)paren
comma
)brace
suffix:semicolon
DECL|macro|set_IRR
mdefine_line|#define set_IRR(N,A,B,C,D) __set_IRR(N, (A &lt;&lt; 28) | (B &lt;&lt; 24) | (C &lt;&lt; 20) | (D &lt;&lt; 16))
DECL|variable|frv_cpu_irqs
r_struct
id|irq_group
id|frv_cpu_irqs
op_assign
(brace
dot
id|sources
op_assign
(brace
(braket
id|IRQ_CPU_UART0
)braket
op_assign
op_amp
id|frv_cpuuart
(braket
l_int|0
)braket
comma
(braket
id|IRQ_CPU_UART1
)braket
op_assign
op_amp
id|frv_cpuuart
(braket
l_int|1
)braket
comma
(braket
id|IRQ_CPU_TIMER0
)braket
op_assign
op_amp
id|frv_cputimer
(braket
l_int|0
)braket
comma
(braket
id|IRQ_CPU_TIMER1
)braket
op_assign
op_amp
id|frv_cputimer
(braket
l_int|1
)braket
comma
(braket
id|IRQ_CPU_TIMER2
)braket
op_assign
op_amp
id|frv_cputimer
(braket
l_int|2
)braket
comma
(braket
id|IRQ_CPU_DMA0
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|0
)braket
comma
(braket
id|IRQ_CPU_DMA1
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|1
)braket
comma
(braket
id|IRQ_CPU_DMA2
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|2
)braket
comma
(braket
id|IRQ_CPU_DMA3
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|3
)braket
comma
(braket
id|IRQ_CPU_DMA4
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|4
)braket
comma
(braket
id|IRQ_CPU_DMA5
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|5
)braket
comma
(braket
id|IRQ_CPU_DMA6
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|6
)braket
comma
(braket
id|IRQ_CPU_DMA7
)braket
op_assign
op_amp
id|frv_cpudma
(braket
l_int|7
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL0
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|0
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL1
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|1
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL2
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|2
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL3
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|3
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL4
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|4
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL5
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|5
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL6
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|6
)braket
comma
(braket
id|IRQ_CPU_EXTERNAL7
)braket
op_assign
op_amp
id|frv_cpuexternal
(braket
l_int|7
)braket
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * route the CPU&squot;s interrupt sources&n; */
DECL|function|route_cpu_irqs
r_void
id|__init
id|route_cpu_irqs
c_func
(paren
r_void
)paren
(brace
id|frv_irq_set_group
c_func
(paren
op_amp
id|frv_cpu_irqs
)paren
suffix:semicolon
id|__set_IITMR
c_func
(paren
l_int|0
comma
l_int|0x003f0000
)paren
suffix:semicolon
multiline_comment|/* DMA0-3, TIMER0-2 IRQ detect levels */
id|__set_IITMR
c_func
(paren
l_int|1
comma
l_int|0x20000000
)paren
suffix:semicolon
multiline_comment|/* ERR0-1, UART0-1, DMA4-7 IRQ detect levels */
multiline_comment|/* route UART and error interrupts */
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuuart
(braket
l_int|0
)braket
comma
id|IRQ_UART0_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuuart
(braket
l_int|1
)braket
comma
id|IRQ_UART1_LEVEL
)paren
suffix:semicolon
id|set_IRR
c_func
(paren
l_int|6
comma
id|IRQ_GDBSTUB_LEVEL
comma
id|IRQ_GDBSTUB_LEVEL
comma
id|IRQ_UART1_LEVEL
comma
id|IRQ_UART0_LEVEL
)paren
suffix:semicolon
multiline_comment|/* route DMA channel interrupts */
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|0
)braket
comma
id|IRQ_DMA0_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|1
)braket
comma
id|IRQ_DMA1_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|2
)braket
comma
id|IRQ_DMA2_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|3
)braket
comma
id|IRQ_DMA3_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|4
)braket
comma
id|IRQ_DMA4_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|5
)braket
comma
id|IRQ_DMA5_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|6
)braket
comma
id|IRQ_DMA6_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpudma
(braket
l_int|7
)braket
comma
id|IRQ_DMA7_LEVEL
)paren
suffix:semicolon
id|set_IRR
c_func
(paren
l_int|4
comma
id|IRQ_DMA3_LEVEL
comma
id|IRQ_DMA2_LEVEL
comma
id|IRQ_DMA1_LEVEL
comma
id|IRQ_DMA0_LEVEL
)paren
suffix:semicolon
id|set_IRR
c_func
(paren
l_int|7
comma
id|IRQ_DMA7_LEVEL
comma
id|IRQ_DMA6_LEVEL
comma
id|IRQ_DMA5_LEVEL
comma
id|IRQ_DMA4_LEVEL
)paren
suffix:semicolon
multiline_comment|/* route timer interrupts */
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cputimer
(braket
l_int|0
)braket
comma
id|IRQ_TIMER0_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cputimer
(braket
l_int|1
)braket
comma
id|IRQ_TIMER1_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cputimer
(braket
l_int|2
)braket
comma
id|IRQ_TIMER2_LEVEL
)paren
suffix:semicolon
id|set_IRR
c_func
(paren
l_int|5
comma
l_int|0
comma
id|IRQ_TIMER2_LEVEL
comma
id|IRQ_TIMER1_LEVEL
comma
id|IRQ_TIMER0_LEVEL
)paren
suffix:semicolon
multiline_comment|/* route external interrupts */
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|0
)braket
comma
id|IRQ_XIRQ0_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|1
)braket
comma
id|IRQ_XIRQ1_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|2
)braket
comma
id|IRQ_XIRQ2_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|3
)braket
comma
id|IRQ_XIRQ3_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|4
)braket
comma
id|IRQ_XIRQ4_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|5
)braket
comma
id|IRQ_XIRQ5_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|6
)braket
comma
id|IRQ_XIRQ6_LEVEL
)paren
suffix:semicolon
id|frv_irq_route
c_func
(paren
op_amp
id|frv_cpuexternal
(braket
l_int|7
)braket
comma
id|IRQ_XIRQ7_LEVEL
)paren
suffix:semicolon
id|set_IRR
c_func
(paren
l_int|2
comma
id|IRQ_XIRQ7_LEVEL
comma
id|IRQ_XIRQ6_LEVEL
comma
id|IRQ_XIRQ5_LEVEL
comma
id|IRQ_XIRQ4_LEVEL
)paren
suffix:semicolon
id|set_IRR
c_func
(paren
l_int|3
comma
id|IRQ_XIRQ3_LEVEL
comma
id|IRQ_XIRQ2_LEVEL
comma
id|IRQ_XIRQ1_LEVEL
comma
id|IRQ_XIRQ0_LEVEL
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_MB93091_VDK)
id|__set_TM1
c_func
(paren
l_int|0x55550000
)paren
suffix:semicolon
multiline_comment|/* XIRQ7-0 all active low */
macro_line|#elif defined(CONFIG_MB93093_PDK)
id|__set_TM1
c_func
(paren
l_int|0x15550000
)paren
suffix:semicolon
multiline_comment|/* XIRQ7 active high, 6-0 all active low */
macro_line|#else
macro_line|#error dont know external IRQ trigger levels for this setup
macro_line|#endif
)brace
multiline_comment|/* end route_cpu_irqs() */
eof
