multiline_comment|/*&n; *  linux/drivers/input/serio/sa1111ps2.c&n; *&n; *  Copyright (C) 2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
r_struct
id|pt_regs
op_star
id|kbd_pt_regs
suffix:semicolon
DECL|struct|ps2if
r_struct
id|ps2if
(brace
DECL|member|io
r_struct
id|serio
id|io
suffix:semicolon
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|skpcr_mask
r_int
r_int
id|skpcr_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Read all bytes waiting in the PS2 port.  There should be&n; * at the most one, but we loop for safety.  If there was a&n; * framing error, we have to manually clear the status.&n; */
DECL|function|ps2_int
r_static
r_void
id|ps2_int
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|ps2if
op_star
id|sa
op_assign
id|dev_id
suffix:semicolon
r_int
r_int
id|scancode
comma
id|flag
comma
id|status
suffix:semicolon
id|kbd_pt_regs
op_assign
id|regs
suffix:semicolon
id|status
op_assign
id|sa1111_readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
suffix:semicolon
r_while
c_loop
(paren
id|status
op_amp
id|PS2STAT_RXF
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|PS2STAT_STP
)paren
id|sa1111_writel
c_func
(paren
id|PS2STAT_STP
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
suffix:semicolon
id|flag
op_assign
(paren
id|status
op_amp
id|PS2STAT_STP
ques
c_cond
id|SERIO_FRAME
suffix:colon
l_int|0
)paren
op_or
(paren
id|status
op_amp
id|PS2STAT_RXP
ques
c_cond
l_int|0
suffix:colon
id|SERIO_PARITY
)paren
suffix:semicolon
id|scancode
op_assign
id|sa1111_readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_PS2DATA
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|hweight8
c_func
(paren
id|scancode
)paren
op_amp
l_int|1
)paren
id|flag
op_xor_assign
id|SERIO_PARITY
suffix:semicolon
id|serio_interrupt
c_func
(paren
op_amp
id|sa-&gt;io
comma
id|scancode
comma
id|flag
)paren
suffix:semicolon
id|status
op_assign
id|sa1111_readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write a byte to the PS2 port.  We have to wait for the&n; * port to indicate that the transmitter is empty.&n; */
DECL|function|ps2_write
r_static
r_int
id|ps2_write
c_func
(paren
r_struct
id|serio
op_star
id|io
comma
r_int
r_char
id|val
)paren
(brace
r_struct
id|ps2if
op_star
id|sa
op_assign
id|io-&gt;driver
suffix:semicolon
r_int
r_int
id|timeleft
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* timeout in 100ms */
r_while
c_loop
(paren
(paren
id|sa1111_readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
op_amp
id|PS2STAT_TXE
)paren
op_eq
l_int|0
op_logical_and
id|timeleft
op_decrement
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeleft
)paren
id|sa1111_writel
c_func
(paren
id|val
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2DATA
)paren
suffix:semicolon
r_return
id|timeleft
ques
c_cond
l_int|0
suffix:colon
id|SERIO_TIMEOUT
suffix:semicolon
)brace
DECL|function|ps2_open
r_static
r_int
id|ps2_open
c_func
(paren
r_struct
id|serio
op_star
id|io
)paren
(brace
r_struct
id|ps2if
op_star
id|sa
op_assign
id|io-&gt;driver
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sa1111_enable_device
c_func
(paren
id|sa-&gt;skpcr_mask
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|sa-&gt;irq
comma
id|ps2_int
comma
l_int|0
comma
l_string|&quot;ps2&quot;
comma
id|sa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sa1111ps2: could not allocate IRQ%d: %d&bslash;n&quot;
comma
id|sa-&gt;irq
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|sa1111_writel
c_func
(paren
id|PS2CR_ENA
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2CR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ps2_close
r_static
r_void
id|ps2_close
c_func
(paren
r_struct
id|serio
op_star
id|io
)paren
(brace
r_struct
id|ps2if
op_star
id|sa
op_assign
id|io-&gt;driver
suffix:semicolon
id|sa1111_writel
c_func
(paren
l_int|0
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2CR
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|sa-&gt;irq
comma
id|sa
)paren
suffix:semicolon
id|sa1111_disable_device
c_func
(paren
id|sa-&gt;skpcr_mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the input buffer.&n; */
DECL|function|ps2_clear_input
r_static
r_void
id|__init
id|ps2_clear_input
c_func
(paren
r_struct
id|ps2if
op_star
id|sa
)paren
(brace
r_int
id|maxread
op_assign
l_int|100
suffix:semicolon
r_while
c_loop
(paren
id|maxread
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|sa1111_readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_PS2DATA
)paren
op_amp
l_int|0xff
)paren
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
)brace
)brace
r_static
r_inline
r_int
r_int
DECL|function|ps2_test_one
id|ps2_test_one
c_func
(paren
r_struct
id|ps2if
op_star
id|sa
comma
r_int
r_int
id|mask
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|sa1111_writel
c_func
(paren
id|PS2CR_ENA
op_or
id|mask
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2CR
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|val
op_assign
id|sa1111_readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
suffix:semicolon
r_return
id|val
op_amp
(paren
id|PS2STAT_KBC
op_or
id|PS2STAT_KBD
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Test the keyboard interface.  We basically check to make sure that&n; * we can drive each line to the keyboard independently of each other.&n; */
DECL|function|ps2_test
r_static
r_int
id|__init
id|ps2_test
c_func
(paren
r_struct
id|ps2if
op_star
id|sa
)paren
(brace
r_int
r_int
id|stat
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|stat
op_assign
id|ps2_test_one
c_func
(paren
id|sa
comma
id|PS2CR_FKC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_ne
id|PS2STAT_KBD
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Keyboard interface test failed[1]: %02x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
id|stat
op_assign
id|ps2_test_one
c_func
(paren
id|sa
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_ne
(paren
id|PS2STAT_KBC
op_or
id|PS2STAT_KBD
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Keyboard interface test failed[2]: %02x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
id|stat
op_assign
id|ps2_test_one
c_func
(paren
id|sa
comma
id|PS2CR_FKD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_ne
id|PS2STAT_KBC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Keyboard interface test failed[3]: %02x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
id|sa1111_writel
c_func
(paren
l_int|0
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2CR
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise one PS/2 port.&n; */
DECL|function|ps2_init_one
r_static
r_int
id|__init
id|ps2_init_one
c_func
(paren
r_struct
id|sa1111_device
op_star
id|dev
comma
r_struct
id|ps2if
op_star
id|sa
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Request the physical region for this PS2 port.&n;&t; */
id|sa-&gt;res
op_assign
id|request_mem_region
c_func
(paren
id|_SA1111
c_func
(paren
id|sa-&gt;base
)paren
comma
l_int|512
comma
l_string|&quot;ps2&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sa-&gt;res
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the chip offset to virtual address.&n;&t; */
id|sa-&gt;base
op_add_assign
(paren
r_int
r_int
)paren
id|dev-&gt;base
suffix:semicolon
id|sa1111_enable_device
c_func
(paren
id|sa-&gt;skpcr_mask
)paren
suffix:semicolon
multiline_comment|/* Incoming clock is 8MHz */
id|sa1111_writel
c_func
(paren
l_int|0
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2CLKDIV
)paren
suffix:semicolon
id|sa1111_writel
c_func
(paren
l_int|127
comma
id|sa-&gt;base
op_plus
id|SA1111_PS2PRECNT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Flush any pending input.&n;&t; */
id|ps2_clear_input
c_func
(paren
id|sa
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Test the keyboard interface.&n;&t; */
id|ret
op_assign
id|ps2_test
c_func
(paren
id|sa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Flush any pending input.&n;&t; */
id|ps2_clear_input
c_func
(paren
id|sa
)paren
suffix:semicolon
id|sa1111_disable_device
c_func
(paren
id|sa-&gt;skpcr_mask
)paren
suffix:semicolon
id|serio_register_port
c_func
(paren
op_amp
id|sa-&gt;io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|sa1111_disable_device
c_func
(paren
id|sa-&gt;skpcr_mask
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|sa-&gt;res
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove one PS/2 port.&n; */
DECL|function|ps2_remove_one
r_static
r_void
id|__exit
id|ps2_remove_one
c_func
(paren
r_struct
id|ps2if
op_star
id|sa
)paren
(brace
id|serio_unregister_port
c_func
(paren
op_amp
id|sa-&gt;io
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|sa-&gt;res
)paren
suffix:semicolon
)brace
DECL|variable|ps2_kbd_port
r_static
r_struct
id|ps2if
id|ps2_kbd_port
op_assign
(brace
id|io
suffix:colon
(brace
id|type
suffix:colon
id|SERIO_8042
comma
id|write
suffix:colon
id|ps2_write
comma
id|open
suffix:colon
id|ps2_open
comma
id|close
suffix:colon
id|ps2_close
comma
id|name
suffix:colon
l_string|&quot;SA1111 PS/2 kbd port&quot;
comma
id|phys
suffix:colon
l_string|&quot;sa1111/serio0&quot;
comma
id|driver
suffix:colon
op_amp
id|ps2_kbd_port
comma
)brace
comma
id|base
suffix:colon
id|SA1111_KBD
comma
id|irq
suffix:colon
id|IRQ_TPRXINT
comma
id|skpcr_mask
suffix:colon
id|SKPCR_PTCLKEN
comma
)brace
suffix:semicolon
DECL|variable|ps2_mse_port
r_static
r_struct
id|ps2if
id|ps2_mse_port
op_assign
(brace
id|io
suffix:colon
(brace
id|type
suffix:colon
id|SERIO_8042
comma
id|write
suffix:colon
id|ps2_write
comma
id|open
suffix:colon
id|ps2_open
comma
id|close
suffix:colon
id|ps2_close
comma
id|name
suffix:colon
l_string|&quot;SA1111 PS/2 mouse port&quot;
comma
id|phys
suffix:colon
l_string|&quot;sa1111/serio1&quot;
comma
id|driver
suffix:colon
op_amp
id|ps2_mse_port
comma
)brace
comma
id|base
suffix:colon
id|SA1111_MSE
comma
id|irq
suffix:colon
id|IRQ_MSRXINT
comma
id|skpcr_mask
suffix:colon
id|SKPCR_PMCLKEN
comma
)brace
suffix:semicolon
DECL|function|ps2_init
r_static
r_int
id|__init
id|ps2_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|sa1111
)paren
(brace
id|ret
op_assign
id|ps2_init_one
c_func
(paren
id|sa1111
comma
op_amp
id|ps2_kbd_port
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ps2_exit
r_static
r_void
id|__exit
id|ps2_exit
c_func
(paren
r_void
)paren
(brace
id|ps2_remove_one
c_func
(paren
op_amp
id|ps2_kbd_port
)paren
suffix:semicolon
)brace
DECL|variable|ps2_init
id|module_init
c_func
(paren
id|ps2_init
)paren
suffix:semicolon
DECL|variable|ps2_exit
id|module_exit
c_func
(paren
id|ps2_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King &lt;rmk@arm.linux.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SA1111 PS2 controller driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
