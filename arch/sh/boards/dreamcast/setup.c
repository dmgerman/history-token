multiline_comment|/*&n; * arch/sh/boards/dreamcast/setup.c&n; *&n; * Hardware support for the Sega Dreamcast.&n; *&n; * Copyright (c) 2001, 2002 M. R. Brown &lt;mrbrown@linuxdc.org&gt;&n; * Copyright (c) 2002, 2003, 2004 Paul Mundt &lt;lethal@linux-sh.org&gt;&n; *&n; * This file is part of the LinuxDC project (www.linuxdc.org)&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; *&n; * This file originally bore the message (with enclosed-$):&n; *&t;Id: setup_dc.c,v 1.5 2001/05/24 05:09:16 mrbrown Exp&n; *&t;SEGA Dreamcast support&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/machvec_init.h&gt;
macro_line|#include &lt;asm/mach/sysasic.h&gt;
r_extern
r_struct
id|hw_interrupt_type
id|systemasic_int
suffix:semicolon
multiline_comment|/* XXX: Move this into it&squot;s proper header. */
r_extern
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|aica_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|gapspci_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|systemasic_irq_demux
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
op_star
id|dreamcast_consistent_alloc
c_func
(paren
r_struct
id|device
op_star
comma
r_int
comma
id|dma_addr_t
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|dreamcast_consistent_free
c_func
(paren
r_struct
id|device
op_star
comma
r_int
comma
r_void
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;Sega Dreamcast&quot;
suffix:semicolon
)brace
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_dreamcast
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
id|NR_IRQS
comma
dot
id|mv_irq_demux
op_assign
id|systemasic_irq_demux
comma
macro_line|#ifdef CONFIG_PCI
dot
id|mv_consistent_alloc
op_assign
id|dreamcast_consistent_alloc
comma
dot
id|mv_consistent_free
op_assign
id|dreamcast_consistent_free
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|dreamcast
)paren
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Mask all hardware events */
multiline_comment|/* XXX */
multiline_comment|/* Acknowledge any previous events */
multiline_comment|/* XXX */
id|__set_io_port_base
c_func
(paren
l_int|0xa0000000
)paren
suffix:semicolon
multiline_comment|/* Assign all virtual IRQs to the System ASIC int. handler */
r_for
c_loop
(paren
id|i
op_assign
id|HW_EVENT_IRQ_BASE
suffix:semicolon
id|i
OL
id|HW_EVENT_IRQ_MAX
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|systemasic_int
suffix:semicolon
id|board_time_init
op_assign
id|aica_time_init
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_if
c_cond
(paren
id|gapspci_init
c_func
(paren
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;GAPSPCI was not detected.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
