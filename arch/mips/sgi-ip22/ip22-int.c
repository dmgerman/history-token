multiline_comment|/*&n; * ip22-int.c: Routines for generic manipulation of the INT[23] ASIC&n; *             found on INDY and Indigo2 workstations.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 1998 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 1999 Andrew R. Baker (andrewb@uab.edu)&n; *                    - Indigo2 changes&n; *                    - Interrupt handling fixes&n; * Copyright (C) 2001, 2003 Ladislav Michl (ladis@linux-mips.org)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sgi/ioc.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
macro_line|#include &lt;asm/sgi/ip22.h&gt;
multiline_comment|/* #define DEBUG_SGINT */
multiline_comment|/* So far nothing hangs here */
DECL|macro|USE_LIO3_IRQ
macro_line|#undef USE_LIO3_IRQ 
DECL|variable|sgint
r_struct
id|sgint_regs
op_star
id|sgint
suffix:semicolon
DECL|variable|lc0msk_to_irqnr
r_static
r_char
id|lc0msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lc1msk_to_irqnr
r_static
r_char
id|lc1msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lc2msk_to_irqnr
r_static
r_char
id|lc2msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|lc3msk_to_irqnr
r_static
r_char
id|lc3msk_to_irqnr
(braket
l_int|256
)braket
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|indyIRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ip22_eisa_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|enable_local0_irq
r_static
r_void
id|enable_local0_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* don&squot;t allow mappable interrupt to be enabled from setup_irq,&n;&t; * we have our own way to do so */
r_if
c_cond
(paren
id|irq
op_ne
id|SGI_MAP_0_IRQ
)paren
id|sgint-&gt;imask0
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL0
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_local0_irq
r_static
r_int
r_int
id|startup_local0_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_local0_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Never anything pending  */
)brace
DECL|function|disable_local0_irq
r_static
r_void
id|disable_local0_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sgint-&gt;imask0
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL0
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_local0_irq
mdefine_line|#define shutdown_local0_irq&t;disable_local0_irq
DECL|macro|mask_and_ack_local0_irq
mdefine_line|#define mask_and_ack_local0_irq&t;disable_local0_irq
DECL|function|end_local0_irq
r_static
r_void
id|end_local0_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_local0_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ip22_local0_irq_type
r_static
r_struct
id|hw_interrupt_type
id|ip22_local0_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;IP22 local 0&quot;
comma
dot
id|startup
op_assign
id|startup_local0_irq
comma
dot
id|shutdown
op_assign
id|shutdown_local0_irq
comma
dot
id|enable
op_assign
id|enable_local0_irq
comma
dot
id|disable
op_assign
id|disable_local0_irq
comma
dot
id|ack
op_assign
id|mask_and_ack_local0_irq
comma
dot
id|end
op_assign
id|end_local0_irq
comma
)brace
suffix:semicolon
DECL|function|enable_local1_irq
r_static
r_void
id|enable_local1_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* don&squot;t allow mappable interrupt to be enabled from setup_irq,&n;&t; * we have our own way to do so */
r_if
c_cond
(paren
id|irq
op_ne
id|SGI_MAP_1_IRQ
)paren
id|sgint-&gt;imask1
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL1
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_local1_irq
r_static
r_int
r_int
id|startup_local1_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_local1_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Never anything pending  */
)brace
DECL|function|disable_local1_irq
r_void
id|disable_local1_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sgint-&gt;imask1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL1
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_local1_irq
mdefine_line|#define shutdown_local1_irq&t;disable_local1_irq
DECL|macro|mask_and_ack_local1_irq
mdefine_line|#define mask_and_ack_local1_irq&t;disable_local1_irq
DECL|function|end_local1_irq
r_static
r_void
id|end_local1_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_local1_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ip22_local1_irq_type
r_static
r_struct
id|hw_interrupt_type
id|ip22_local1_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;IP22 local 1&quot;
comma
dot
id|startup
op_assign
id|startup_local1_irq
comma
dot
id|shutdown
op_assign
id|shutdown_local1_irq
comma
dot
id|enable
op_assign
id|enable_local1_irq
comma
dot
id|disable
op_assign
id|disable_local1_irq
comma
dot
id|ack
op_assign
id|mask_and_ack_local1_irq
comma
dot
id|end
op_assign
id|end_local1_irq
comma
)brace
suffix:semicolon
DECL|function|enable_local2_irq
r_static
r_void
id|enable_local2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sgint-&gt;imask0
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|SGI_MAP_0_IRQ
op_minus
id|SGINT_LOCAL0
)paren
)paren
suffix:semicolon
id|sgint-&gt;cmeimask0
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL2
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_local2_irq
r_static
r_int
r_int
id|startup_local2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_local2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Never anything pending  */
)brace
DECL|function|disable_local2_irq
r_void
id|disable_local2_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sgint-&gt;cmeimask0
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgint-&gt;cmeimask0
)paren
id|sgint-&gt;imask0
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|SGI_MAP_0_IRQ
op_minus
id|SGINT_LOCAL0
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_local2_irq
mdefine_line|#define shutdown_local2_irq disable_local2_irq
DECL|macro|mask_and_ack_local2_irq
mdefine_line|#define mask_and_ack_local2_irq&t;disable_local2_irq
DECL|function|end_local2_irq
r_static
r_void
id|end_local2_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_local2_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ip22_local2_irq_type
r_static
r_struct
id|hw_interrupt_type
id|ip22_local2_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;IP22 local 2&quot;
comma
dot
id|startup
op_assign
id|startup_local2_irq
comma
dot
id|shutdown
op_assign
id|shutdown_local2_irq
comma
dot
id|enable
op_assign
id|enable_local2_irq
comma
dot
id|disable
op_assign
id|disable_local2_irq
comma
dot
id|ack
op_assign
id|mask_and_ack_local2_irq
comma
dot
id|end
op_assign
id|end_local2_irq
comma
)brace
suffix:semicolon
DECL|function|enable_local3_irq
r_static
r_void
id|enable_local3_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sgint-&gt;imask1
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|SGI_MAP_1_IRQ
op_minus
id|SGINT_LOCAL1
)paren
)paren
suffix:semicolon
id|sgint-&gt;cmeimask1
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL3
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_local3_irq
r_static
r_int
r_int
id|startup_local3_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_local3_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Never anything pending  */
)brace
DECL|function|disable_local3_irq
r_void
id|disable_local3_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sgint-&gt;cmeimask1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|SGINT_LOCAL3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgint-&gt;cmeimask1
)paren
id|sgint-&gt;imask1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|SGI_MAP_1_IRQ
op_minus
id|SGINT_LOCAL1
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_local3_irq
mdefine_line|#define shutdown_local3_irq disable_local3_irq
DECL|macro|mask_and_ack_local3_irq
mdefine_line|#define mask_and_ack_local3_irq&t;disable_local3_irq
DECL|function|end_local3_irq
r_static
r_void
id|end_local3_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_local3_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ip22_local3_irq_type
r_static
r_struct
id|hw_interrupt_type
id|ip22_local3_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;IP22 local 3&quot;
comma
dot
id|startup
op_assign
id|startup_local3_irq
comma
dot
id|shutdown
op_assign
id|shutdown_local3_irq
comma
dot
id|enable
op_assign
id|enable_local3_irq
comma
dot
id|disable
op_assign
id|disable_local3_irq
comma
dot
id|ack
op_assign
id|mask_and_ack_local3_irq
comma
dot
id|end
op_assign
id|end_local3_irq
comma
)brace
suffix:semicolon
DECL|function|indy_local0_irqdispatch
r_void
id|indy_local0_irqdispatch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u8
id|mask
op_assign
id|sgint-&gt;istat0
op_amp
id|sgint-&gt;imask0
suffix:semicolon
id|u8
id|mask2
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|SGINT_ISTAT0_LIO2
)paren
(brace
id|mask2
op_assign
id|sgint-&gt;vmeistat
op_amp
id|sgint-&gt;cmeimask0
suffix:semicolon
id|irq
op_assign
id|lc2msk_to_irqnr
(braket
id|mask2
)braket
suffix:semicolon
)brace
r_else
id|irq
op_assign
id|lc0msk_to_irqnr
(braket
id|mask
)braket
suffix:semicolon
multiline_comment|/* if irq == 0, then the interrupt has already been cleared */
r_if
c_cond
(paren
id|irq
)paren
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|indy_local1_irqdispatch
r_void
id|indy_local1_irqdispatch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u8
id|mask
op_assign
id|sgint-&gt;istat1
op_amp
id|sgint-&gt;imask1
suffix:semicolon
id|u8
id|mask2
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|SGINT_ISTAT1_LIO3
)paren
(brace
id|mask2
op_assign
id|sgint-&gt;vmeistat
op_amp
id|sgint-&gt;cmeimask1
suffix:semicolon
id|irq
op_assign
id|lc3msk_to_irqnr
(braket
id|mask2
)braket
suffix:semicolon
)brace
r_else
id|irq
op_assign
id|lc1msk_to_irqnr
(braket
id|mask
)braket
suffix:semicolon
multiline_comment|/* if irq == 0, then the interrupt has already been cleared */
r_if
c_cond
(paren
id|irq
)paren
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_void
id|ip22_be_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|indy_buserror_irq
r_void
id|indy_buserror_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
op_assign
id|SGI_BUSERR_IRQ
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|ip22_be_interrupt
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|local0_cascade
r_static
r_struct
id|irqaction
id|local0_cascade
op_assign
(brace
dot
id|handler
op_assign
id|no_action
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;local0 cascade&quot;
comma
)brace
suffix:semicolon
DECL|variable|local1_cascade
r_static
r_struct
id|irqaction
id|local1_cascade
op_assign
(brace
dot
id|handler
op_assign
id|no_action
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;local1 cascade&quot;
comma
)brace
suffix:semicolon
DECL|variable|buserr
r_static
r_struct
id|irqaction
id|buserr
op_assign
(brace
dot
id|handler
op_assign
id|no_action
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;Bus Error&quot;
comma
)brace
suffix:semicolon
DECL|variable|map0_cascade
r_static
r_struct
id|irqaction
id|map0_cascade
op_assign
(brace
dot
id|handler
op_assign
id|no_action
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;mapable0 cascade&quot;
comma
)brace
suffix:semicolon
macro_line|#ifdef USE_LIO3_IRQ
DECL|variable|map1_cascade
r_static
r_struct
id|irqaction
id|map1_cascade
op_assign
(brace
dot
id|handler
op_assign
id|no_action
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;mapable1 cascade&quot;
comma
)brace
suffix:semicolon
DECL|macro|SGI_INTERRUPTS
mdefine_line|#define SGI_INTERRUPTS&t;SGINT_END
macro_line|#else
DECL|macro|SGI_INTERRUPTS
mdefine_line|#define SGI_INTERRUPTS&t;SGINT_LOCAL3
macro_line|#endif
r_extern
r_void
id|mips_cpu_irq_init
c_func
(paren
r_int
r_int
id|irq_base
)paren
suffix:semicolon
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Init local mask --&gt; irq tables. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_amp
l_int|0x80
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|7
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|7
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|7
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|7
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x40
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|6
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|6
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|6
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|6
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x20
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|5
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|5
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|5
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|5
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x10
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|4
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|4
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|4
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x08
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|3
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|3
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|3
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x04
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|2
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|2
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|2
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x02
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|1
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|1
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|1
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_amp
l_int|0x01
)paren
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL0
op_plus
l_int|0
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL1
op_plus
l_int|0
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL2
op_plus
l_int|0
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
id|SGINT_LOCAL3
op_plus
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|lc0msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc1msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc2msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|lc3msk_to_irqnr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* Mask out all interrupts. */
id|sgint-&gt;imask0
op_assign
l_int|0
suffix:semicolon
id|sgint-&gt;imask1
op_assign
l_int|0
suffix:semicolon
id|sgint-&gt;cmeimask0
op_assign
l_int|0
suffix:semicolon
id|sgint-&gt;cmeimask1
op_assign
l_int|0
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|indyIRQ
)paren
suffix:semicolon
id|init_generic_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* init CPU irqs */
id|mips_cpu_irq_init
c_func
(paren
id|SGINT_CPU
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|SGINT_LOCAL0
suffix:semicolon
id|i
OL
id|SGI_INTERRUPTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw_irq_controller
op_star
id|handler
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|SGINT_LOCAL1
)paren
id|handler
op_assign
op_amp
id|ip22_local0_irq_type
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
OL
id|SGINT_LOCAL2
)paren
id|handler
op_assign
op_amp
id|ip22_local1_irq_type
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
OL
id|SGINT_LOCAL3
)paren
id|handler
op_assign
op_amp
id|ip22_local2_irq_type
suffix:semicolon
r_else
id|handler
op_assign
op_amp
id|ip22_local3_irq_type
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
)brace
multiline_comment|/* vector handler. this register the IRQ as non-sharable */
id|setup_irq
c_func
(paren
id|SGI_LOCAL_0_IRQ
comma
op_amp
id|local0_cascade
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|SGI_LOCAL_1_IRQ
comma
op_amp
id|local1_cascade
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|SGI_BUSERR_IRQ
comma
op_amp
id|buserr
)paren
suffix:semicolon
multiline_comment|/* cascade in cascade. i love Indy ;-) */
id|setup_irq
c_func
(paren
id|SGI_MAP_0_IRQ
comma
op_amp
id|map0_cascade
)paren
suffix:semicolon
macro_line|#ifdef USE_LIO3_IRQ
id|setup_irq
c_func
(paren
id|SGI_MAP_1_IRQ
comma
op_amp
id|map1_cascade
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EISA
r_if
c_cond
(paren
id|ip22_is_fullhouse
c_func
(paren
)paren
)paren
multiline_comment|/* Only Indigo-2 has EISA stuff */
id|ip22_eisa_init
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
