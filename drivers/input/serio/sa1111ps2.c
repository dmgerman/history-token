multiline_comment|/*&n; *  linux/drivers/input/serio/sa1111ps2.c&n; *&n; *  Copyright (C) 2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
DECL|struct|ps2if
r_struct
id|ps2if
(brace
DECL|member|io
r_struct
id|serio
id|io
suffix:semicolon
DECL|member|dev
r_struct
id|sa1111_dev
op_star
id|dev
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|open
r_int
r_int
id|open
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Read all bytes waiting in the PS2 port.  There should be&n; * at the most one, but we loop for safety.  If there was a&n; * framing error, we have to manually clear the status.&n; */
DECL|function|ps2_rxint
r_static
id|irqreturn_t
id|ps2_rxint
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
id|ps2if
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
r_int
id|handled
op_assign
id|IRQ_NONE
suffix:semicolon
id|status
op_assign
id|sa1111_readl
c_func
(paren
id|ps2if-&gt;base
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
id|ps2if-&gt;base
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
id|ps2if-&gt;base
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
id|ps2if-&gt;io
comma
id|scancode
comma
id|flag
comma
id|regs
)paren
suffix:semicolon
id|status
op_assign
id|sa1111_readl
c_func
(paren
id|ps2if-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
suffix:semicolon
id|handled
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
r_return
id|handled
suffix:semicolon
)brace
multiline_comment|/*&n; * Completion of ps2 write&n; */
DECL|function|ps2_txint
r_static
id|irqreturn_t
id|ps2_txint
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
id|ps2if
op_assign
id|dev_id
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|ps2if-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|sa1111_readl
c_func
(paren
id|ps2if-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ps2if-&gt;head
op_eq
id|ps2if-&gt;tail
)paren
(brace
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* done */
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|PS2STAT_TXE
)paren
(brace
id|sa1111_writel
c_func
(paren
id|ps2if-&gt;buf
(braket
id|ps2if-&gt;tail
)braket
comma
id|ps2if-&gt;base
op_plus
id|SA1111_PS2DATA
)paren
suffix:semicolon
id|ps2if-&gt;tail
op_assign
(paren
id|ps2if-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
r_sizeof
(paren
id|ps2if-&gt;buf
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|ps2if-&gt;lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
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
id|ps2if
op_assign
id|io-&gt;driver
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|head
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps2if-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the TX register is empty, we can go straight out.&n;&t; */
r_if
c_cond
(paren
id|sa1111_readl
c_func
(paren
id|ps2if-&gt;base
op_plus
id|SA1111_PS2STAT
)paren
op_amp
id|PS2STAT_TXE
)paren
(brace
id|sa1111_writel
c_func
(paren
id|val
comma
id|ps2if-&gt;base
op_plus
id|SA1111_PS2DATA
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ps2if-&gt;head
op_eq
id|ps2if-&gt;tail
)paren
id|enable_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|head
op_assign
(paren
id|ps2if-&gt;head
op_plus
l_int|1
)paren
op_amp
(paren
r_sizeof
(paren
id|ps2if-&gt;buf
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|ps2if-&gt;tail
)paren
(brace
id|ps2if-&gt;buf
(braket
id|ps2if-&gt;head
)braket
op_assign
id|val
suffix:semicolon
id|ps2if-&gt;head
op_assign
id|head
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps2if-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
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
id|ps2if
op_assign
id|io-&gt;driver
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sa1111_enable_device
c_func
(paren
id|ps2if-&gt;dev
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|0
)braket
comma
id|ps2_rxint
comma
l_int|0
comma
id|SA1111_DRIVER_NAME
c_func
(paren
id|ps2if-&gt;dev
)paren
comma
id|ps2if
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
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|0
)braket
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|request_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|1
)braket
comma
id|ps2_txint
comma
l_int|0
comma
id|SA1111_DRIVER_NAME
c_func
(paren
id|ps2if-&gt;dev
)paren
comma
id|ps2if
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
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|1
)braket
comma
id|ret
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|0
)braket
comma
id|ps2if
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ps2if-&gt;open
op_assign
l_int|1
suffix:semicolon
id|enable_irq_wake
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sa1111_writel
c_func
(paren
id|PS2CR_ENA
comma
id|ps2if-&gt;base
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
id|ps2if
op_assign
id|io-&gt;driver
suffix:semicolon
id|sa1111_writel
c_func
(paren
l_int|0
comma
id|ps2if-&gt;base
op_plus
id|SA1111_PS2CR
)paren
suffix:semicolon
id|disable_irq_wake
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ps2if-&gt;open
op_assign
l_int|0
suffix:semicolon
id|free_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|1
)braket
comma
id|ps2if
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|ps2if-&gt;dev-&gt;irq
(braket
l_int|0
)braket
comma
id|ps2if
)paren
suffix:semicolon
id|sa1111_disable_device
c_func
(paren
id|ps2if-&gt;dev
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
id|ps2if
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
id|ps2if-&gt;base
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
id|ps2if
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
id|ps2if-&gt;base
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
id|ps2if-&gt;base
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
id|ps2if
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
id|ps2if
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
l_string|&quot;PS/2 interface test failed[1]: %02x&bslash;n&quot;
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
id|ps2if
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
l_string|&quot;PS/2 interface test failed[2]: %02x&bslash;n&quot;
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
id|ps2if
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
l_string|&quot;PS/2 interface test failed[3]: %02x&bslash;n&quot;
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
id|ps2if-&gt;base
op_plus
id|SA1111_PS2CR
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Add one device to this driver.&n; */
DECL|function|ps2_probe
r_static
r_int
id|ps2_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|sa1111_dev
op_star
id|sadev
op_assign
id|SA1111_DEV
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ps2if
op_star
id|ps2if
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ps2if
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ps2if
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ps2if
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ps2if
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ps2if
)paren
)paren
suffix:semicolon
id|ps2if-&gt;io.type
op_assign
id|SERIO_8042
suffix:semicolon
id|ps2if-&gt;io.write
op_assign
id|ps2_write
suffix:semicolon
id|ps2if-&gt;io.open
op_assign
id|ps2_open
suffix:semicolon
id|ps2if-&gt;io.close
op_assign
id|ps2_close
suffix:semicolon
id|ps2if-&gt;io.name
op_assign
id|dev-&gt;name
suffix:semicolon
id|ps2if-&gt;io.phys
op_assign
id|dev-&gt;bus_id
suffix:semicolon
id|ps2if-&gt;io.driver
op_assign
id|ps2if
suffix:semicolon
id|ps2if-&gt;dev
op_assign
id|sadev
suffix:semicolon
id|dev-&gt;driver_data
op_assign
id|ps2if
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|ps2if-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Request the physical region for this PS2 port.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|sadev-&gt;res.start
comma
id|sadev-&gt;res.end
op_minus
id|sadev-&gt;res.start
op_plus
l_int|1
comma
id|SA1111_DRIVER_NAME
c_func
(paren
id|sadev
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|free
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Our parent device has already mapped the region.&n;&t; */
id|ps2if-&gt;base
op_assign
(paren
r_int
r_int
)paren
id|sadev-&gt;mapbase
suffix:semicolon
id|sa1111_enable_device
c_func
(paren
id|ps2if-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Incoming clock is 8MHz */
id|sa1111_writel
c_func
(paren
l_int|0
comma
id|ps2if-&gt;base
op_plus
id|SA1111_PS2CLKDIV
)paren
suffix:semicolon
id|sa1111_writel
c_func
(paren
l_int|127
comma
id|ps2if-&gt;base
op_plus
id|SA1111_PS2PRECNT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Flush any pending input.&n;&t; */
id|ps2_clear_input
c_func
(paren
id|ps2if
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Test the keyboard interface.&n;&t; */
id|ret
op_assign
id|ps2_test
c_func
(paren
id|ps2if
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
id|ps2if
)paren
suffix:semicolon
id|sa1111_disable_device
c_func
(paren
id|ps2if-&gt;dev
)paren
suffix:semicolon
id|serio_register_port
c_func
(paren
op_amp
id|ps2if-&gt;io
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
id|ps2if-&gt;dev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|sadev-&gt;res.start
comma
id|sadev-&gt;res.end
op_minus
id|sadev-&gt;res.start
op_plus
l_int|1
)paren
suffix:semicolon
id|free
suffix:colon
id|dev-&gt;driver_data
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|ps2if
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove one device from this driver.&n; */
DECL|function|ps2_remove
r_static
r_int
id|ps2_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ps2if
op_star
id|ps2if
op_assign
id|dev-&gt;driver_data
suffix:semicolon
r_struct
id|sa1111_dev
op_star
id|sadev
op_assign
id|SA1111_DEV
c_func
(paren
id|dev
)paren
suffix:semicolon
id|serio_unregister_port
c_func
(paren
op_amp
id|ps2if-&gt;io
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|sadev-&gt;res.start
comma
id|sadev-&gt;res.end
op_minus
id|sadev-&gt;res.start
op_plus
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ps2if
)paren
suffix:semicolon
id|dev-&gt;driver_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We should probably do something here, but what?&n; */
DECL|function|ps2_suspend
r_static
r_int
id|ps2_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ps2_resume
r_static
r_int
id|ps2_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Our device driver structure&n; */
DECL|variable|ps2_driver
r_static
r_struct
id|sa1111_driver
id|ps2_driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa1111-ps2&quot;
comma
dot
id|bus
op_assign
op_amp
id|sa1111_bus_type
comma
dot
id|devclass
op_assign
op_amp
id|input_devclass
comma
dot
id|probe
op_assign
id|ps2_probe
comma
dot
id|remove
op_assign
id|ps2_remove
comma
dot
id|suspend
op_assign
id|ps2_suspend
comma
dot
id|resume
op_assign
id|ps2_resume
comma
)brace
comma
dot
id|devid
op_assign
id|SA1111_DEVID_PS2
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
r_return
id|driver_register
c_func
(paren
op_amp
id|ps2_driver.drv
)paren
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
id|driver_unregister
c_func
(paren
op_amp
id|ps2_driver.drv
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
