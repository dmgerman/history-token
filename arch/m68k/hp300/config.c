multiline_comment|/*&n; *  linux/arch/m68k/hp300/config.c&n; *&n; *  Copyright (C) 1998 Philip Blundell &lt;philb@gnu.org&gt;&n; *&n; *  This file contains the HP300-specific initialisation code.  It gets&n; *  called by setup.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/blinken.h&gt;
macro_line|#include &lt;asm/hwtest.h&gt;                           /* hwreg_present() */
macro_line|#include &quot;ints.h&quot;
macro_line|#include &quot;time.h&quot;
r_extern
r_void
id|hp300_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|irqreturn_t
(paren
op_star
id|hp300_default_handler
(braket
)braket
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|show_hp300_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
DECL|function|hp300_pulse
r_static
r_void
id|hp300_pulse
c_func
(paren
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
id|x
)paren
id|blinken_leds
c_func
(paren
l_int|0xfe
)paren
suffix:semicolon
r_else
id|blinken_leds
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|hp300_get_model
r_static
r_void
id|hp300_get_model
c_func
(paren
r_char
op_star
id|model
)paren
(brace
id|strcpy
c_func
(paren
id|model
comma
l_string|&quot;HP9000/300&quot;
)paren
suffix:semicolon
)brace
DECL|function|config_hp300
r_void
id|__init
id|config_hp300
c_func
(paren
r_void
)paren
(brace
id|mach_sched_init
op_assign
id|hp300_sched_init
suffix:semicolon
id|mach_init_IRQ
op_assign
id|hp300_init_IRQ
suffix:semicolon
id|mach_request_irq
op_assign
id|hp300_request_irq
suffix:semicolon
id|mach_free_irq
op_assign
id|hp300_free_irq
suffix:semicolon
id|mach_get_model
op_assign
id|hp300_get_model
suffix:semicolon
id|mach_get_irq_list
op_assign
id|show_hp300_interrupts
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|hp300_gettimeoffset
suffix:semicolon
id|mach_default_handler
op_assign
op_amp
id|hp300_default_handler
suffix:semicolon
id|mach_reset
op_assign
id|hp300_reset
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
id|mach_heartbeat
op_assign
id|hp300_pulse
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|mach_max_dma_address
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
eof
