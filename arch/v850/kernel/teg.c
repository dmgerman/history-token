multiline_comment|/*&n; * arch/v850/kernel/teg.c -- NB85E-TEG cpu chip&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/v850e_timer_d.h&gt;
macro_line|#include &quot;mach.h&quot;
DECL|function|mach_sched_init
r_void
id|__init
id|mach_sched_init
(paren
r_struct
id|irqaction
op_star
id|timer_action
)paren
(brace
multiline_comment|/* Select timer interrupt instead of external pin.  */
id|TEG_ISS
op_or_assign
l_int|0x1
suffix:semicolon
multiline_comment|/* Start hardware timer.  */
id|v850e_timer_d_configure
(paren
l_int|0
comma
id|HZ
)paren
suffix:semicolon
multiline_comment|/* Install timer interrupt handler.  */
id|setup_irq
(paren
id|IRQ_INTCMD
c_func
(paren
l_int|0
)paren
comma
id|timer_action
)paren
suffix:semicolon
)brace
DECL|variable|irq_inits
r_static
r_struct
id|v850e_intc_irq_init
id|irq_inits
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;IRQ&quot;
comma
l_int|0
comma
id|NUM_CPU_IRQS
comma
l_int|1
comma
l_int|7
)brace
comma
(brace
l_string|&quot;CMD&quot;
comma
id|IRQ_INTCMD
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTCMD_NUM
comma
l_int|1
comma
l_int|5
)brace
comma
(brace
l_string|&quot;SER&quot;
comma
id|IRQ_INTSER
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTSER_NUM
comma
l_int|1
comma
l_int|3
)brace
comma
(brace
l_string|&quot;SR&quot;
comma
id|IRQ_INTSR
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTSR_NUM
comma
l_int|1
comma
l_int|4
)brace
comma
(brace
l_string|&quot;ST&quot;
comma
id|IRQ_INTST
c_func
(paren
l_int|0
)paren
comma
id|IRQ_INTST_NUM
comma
l_int|1
comma
l_int|5
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NUM_IRQ_INITS
mdefine_line|#define NUM_IRQ_INITS ((sizeof irq_inits / sizeof irq_inits[0]) - 1)
DECL|variable|hw_itypes
r_static
r_struct
id|hw_interrupt_type
id|hw_itypes
(braket
id|NUM_IRQ_INITS
)braket
suffix:semicolon
multiline_comment|/* Initialize MA chip interrupts.  */
DECL|function|teg_init_irqs
r_void
id|__init
id|teg_init_irqs
(paren
r_void
)paren
(brace
id|v850e_intc_init_irq_types
(paren
id|irq_inits
comma
id|hw_itypes
)paren
suffix:semicolon
)brace
multiline_comment|/* Called before configuring an on-chip UART.  */
DECL|function|teg_uart_pre_configure
r_void
id|teg_uart_pre_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
(brace
multiline_comment|/* Enable UART I/O pins instead of external interrupt pins, and&n;&t;   UART interrupts instead of external pin interrupts.  */
id|TEG_ISS
op_or_assign
l_int|0x4E
suffix:semicolon
)brace
eof
