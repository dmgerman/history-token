multiline_comment|/* arch/sh/kernel/setup_dc.c&n; *&n; * Hardware support for the Sega Dreamcast.&n; *&n; * Copyright (c) 2001, 2002 M. R. Brown &lt;mrbrown@linuxdc.org&gt;&n; * Copyright (c) 2002 Paul Mundt &lt;lethal@chaoticdreams.org&gt;&n; *&n; * This file is part of the LinuxDC project (www.linuxdc.org)&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; * &n; * This file originally bore the message (with enclosed-$):&n; *&t;Id: setup_dc.c,v 1.5 2001/05/24 05:09:16 mrbrown Exp&n; *&t;SEGA Dreamcast support&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dreamcast/sysasic.h&gt;
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
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|gapspci_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|platform_setup
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
