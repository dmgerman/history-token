multiline_comment|/*&n; * ICS MK712 touchscreen controller driver&n; *&n; * Copyright (c) 1999-2002 Transmeta Corporation&n; * Copyright (c) 2005 Rick Koch &lt;n1gp@hotmail.com&gt;&n; * Copyright (c) 2005 Vojtech Pavlik &lt;vojtech@suse.cz&gt;&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
multiline_comment|/*&n; * This driver supports the ICS MicroClock MK712 TouchScreen controller,&n; * found in Gateway AOL Connected Touchpad computers.&n; *&n; * Documentation for ICS MK712 can be found at:&n; * &t;http://www.icst.com/pdf/mk712.pdf&n; */
multiline_comment|/*&n; * 1999-12-18: original version, Daniel Quinlan&n; * 1999-12-19: added anti-jitter code, report pen-up events, fixed mk712_poll&n; *             to use queue_empty, Nathan Laredo&n; * 1999-12-20: improved random point rejection, Nathan Laredo&n; * 2000-01-05: checked in new anti-jitter code, changed mouse protocol, fixed&n; *             queue code, added module options, other fixes, Daniel Quinlan&n; * 2002-03-15: Clean up for kernel merge &lt;alan@redhat.com&gt;&n; *             Fixed multi open race, fixed memory checks, fixed resource&n; *             allocation, fixed close/powerdown bug, switched to new init&n; * 2005-01-18: Ported to 2.6 from 2.4.28, Rick Koch&n; * 2005-02-05: Rewritten for the input layer, Vojtech Pavlik&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Daniel Quinlan &lt;quinlan@pathname.com&gt;, Vojtech Pavlik &lt;vojtech@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ICS MicroClock MK712 TouchScreen driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|mk712_io
r_static
r_int
r_int
id|mk712_io
op_assign
l_int|0x260
suffix:semicolon
multiline_comment|/* Also 0x200, 0x208, 0x300 */
id|module_param_named
c_func
(paren
id|io
comma
id|mk712_io
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O base address of MK712 touchscreen controller&quot;
)paren
suffix:semicolon
DECL|variable|mk712_irq
r_static
r_int
r_int
id|mk712_irq
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* Also 12, 14, 15 */
id|module_param_named
c_func
(paren
id|irq
comma
id|mk712_irq
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ of MK712 touchscreen controller&quot;
)paren
suffix:semicolon
multiline_comment|/* eight 8-bit registers */
DECL|macro|MK712_STATUS
mdefine_line|#define MK712_STATUS&t;&t;0
DECL|macro|MK712_X
mdefine_line|#define MK712_X&t;&t;&t;2
DECL|macro|MK712_Y
mdefine_line|#define MK712_Y&t;&t;&t;4
DECL|macro|MK712_CONTROL
mdefine_line|#define MK712_CONTROL&t;&t;6
DECL|macro|MK712_RATE
mdefine_line|#define MK712_RATE&t;&t;7
multiline_comment|/* status */
DECL|macro|MK712_STATUS_TOUCH
mdefine_line|#define&t;MK712_STATUS_TOUCH&t;&t;&t;0x10
DECL|macro|MK712_CONVERSION_COMPLETE
mdefine_line|#define&t;MK712_CONVERSION_COMPLETE&t;&t;0x80
multiline_comment|/* control */
DECL|macro|MK712_ENABLE_INT
mdefine_line|#define MK712_ENABLE_INT&t;&t;&t;0x01
DECL|macro|MK712_INT_ON_CONVERSION_COMPLETE
mdefine_line|#define MK712_INT_ON_CONVERSION_COMPLETE&t;0x02
DECL|macro|MK712_INT_ON_CHANGE_IN_TOUCH_STATUS
mdefine_line|#define MK712_INT_ON_CHANGE_IN_TOUCH_STATUS&t;0x04
DECL|macro|MK712_ENABLE_PERIODIC_CONVERSIONS
mdefine_line|#define MK712_ENABLE_PERIODIC_CONVERSIONS&t;0x10
DECL|macro|MK712_READ_ONE_POINT
mdefine_line|#define MK712_READ_ONE_POINT&t;&t;&t;0x20
DECL|macro|MK712_POWERUP
mdefine_line|#define MK712_POWERUP&t;&t;&t;&t;0x40
DECL|variable|mk712_used
r_static
r_int
id|mk712_used
op_assign
l_int|0
suffix:semicolon
DECL|variable|mk712_dev
r_static
r_struct
id|input_dev
id|mk712_dev
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|mk712_lock
)paren
suffix:semicolon
DECL|function|mk712_interrupt
r_static
id|irqreturn_t
id|mk712_interrupt
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
r_int
r_char
id|status
suffix:semicolon
r_static
r_int
id|debounce
op_assign
l_int|1
suffix:semicolon
r_static
r_int
r_int
id|last_x
suffix:semicolon
r_static
r_int
r_int
id|last_y
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mk712_lock
)paren
suffix:semicolon
id|input_regs
c_func
(paren
op_amp
id|mk712_dev
comma
id|regs
)paren
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|mk712_io
op_plus
id|MK712_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|status
op_amp
id|MK712_CONVERSION_COMPLETE
)paren
(brace
id|debounce
op_assign
l_int|1
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|status
op_amp
id|MK712_STATUS_TOUCH
)paren
(brace
id|debounce
op_assign
l_int|1
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|mk712_dev
comma
id|BTN_TOUCH
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debounce
)paren
(brace
id|debounce
op_assign
l_int|0
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|input_report_key
c_func
(paren
op_amp
id|mk712_dev
comma
id|BTN_TOUCH
comma
l_int|1
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|mk712_dev
comma
id|ABS_X
comma
id|last_x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|mk712_dev
comma
id|ABS_Y
comma
id|last_y
)paren
suffix:semicolon
id|end
suffix:colon
id|last_x
op_assign
id|inw
c_func
(paren
id|mk712_io
op_plus
id|MK712_X
)paren
op_amp
l_int|0x0fff
suffix:semicolon
id|last_y
op_assign
id|inw
c_func
(paren
id|mk712_io
op_plus
id|MK712_Y
)paren
op_amp
l_int|0x0fff
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|mk712_dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mk712_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|mk712_open
r_static
r_int
id|mk712_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mk712_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mk712_used
op_increment
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
id|mk712_io
op_plus
id|MK712_CONTROL
)paren
suffix:semicolon
multiline_comment|/* Reset */
id|outb
c_func
(paren
id|MK712_ENABLE_INT
op_or
id|MK712_INT_ON_CONVERSION_COMPLETE
op_or
id|MK712_INT_ON_CHANGE_IN_TOUCH_STATUS
op_or
id|MK712_ENABLE_PERIODIC_CONVERSIONS
op_or
id|MK712_POWERUP
comma
id|mk712_io
op_plus
id|MK712_CONTROL
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|10
comma
id|mk712_io
op_plus
id|MK712_RATE
)paren
suffix:semicolon
multiline_comment|/* 187 points per second */
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mk712_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mk712_close
r_static
r_void
id|mk712_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mk712_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|mk712_used
)paren
id|outb
c_func
(paren
l_int|0
comma
id|mk712_io
op_plus
id|MK712_CONTROL
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mk712_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|mk712_dev
r_static
r_struct
id|input_dev
id|mk712_dev
op_assign
(brace
dot
id|evbit
op_assign
(brace
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
)brace
comma
dot
id|keybit
op_assign
(brace
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
)brace
comma
dot
id|absbit
op_assign
(brace
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
)brace
comma
dot
id|open
op_assign
id|mk712_open
comma
dot
id|close
op_assign
id|mk712_close
comma
dot
id|name
op_assign
l_string|&quot;ICS MicroClock MK712 TouchScreen&quot;
comma
dot
id|phys
op_assign
l_string|&quot;isa0260/input0&quot;
comma
dot
id|absmin
op_assign
(brace
(braket
id|ABS_X
)braket
op_assign
l_int|0
comma
(braket
id|ABS_Y
)braket
op_assign
l_int|0
)brace
comma
dot
id|absmax
op_assign
(brace
(braket
id|ABS_X
)braket
op_assign
l_int|0xfff
comma
(braket
id|ABS_Y
)braket
op_assign
l_int|0xfff
)brace
comma
dot
id|absfuzz
op_assign
(brace
(braket
id|ABS_X
)braket
op_assign
l_int|88
comma
(braket
id|ABS_Y
)braket
op_assign
l_int|88
)brace
comma
dot
id|id
op_assign
(brace
dot
id|bustype
op_assign
id|BUS_ISA
comma
dot
id|vendor
op_assign
l_int|0x0005
comma
dot
id|product
op_assign
l_int|0x0001
comma
dot
id|version
op_assign
l_int|0x0100
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|mk712_init
r_int
id|__init
id|mk712_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|mk712_io
comma
l_int|8
comma
l_string|&quot;mk712&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mk712: unable to get IO region&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0
comma
id|mk712_io
op_plus
id|MK712_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inw
c_func
(paren
id|mk712_io
op_plus
id|MK712_X
)paren
op_amp
l_int|0xf000
)paren
op_logical_or
multiline_comment|/* Sanity check */
(paren
id|inw
c_func
(paren
id|mk712_io
op_plus
id|MK712_Y
)paren
op_amp
l_int|0xf000
)paren
op_logical_or
(paren
id|inw
c_func
(paren
id|mk712_io
op_plus
id|MK712_STATUS
)paren
op_amp
l_int|0xf333
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mk712: device not present&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|mk712_io
comma
l_int|8
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|mk712_irq
comma
id|mk712_interrupt
comma
l_int|0
comma
l_string|&quot;mk712&quot;
comma
op_amp
id|mk712_dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mk712: unable to get IRQ&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|mk712_io
comma
l_int|8
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|mk712_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: ICS MicroClock MK712 TouchScreen at %#x irq %d&bslash;n&quot;
comma
id|mk712_io
comma
id|mk712_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mk712_exit
r_static
r_void
id|__exit
id|mk712_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|mk712_dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|mk712_irq
comma
op_amp
id|mk712_dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|mk712_io
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|variable|mk712_init
id|module_init
c_func
(paren
id|mk712_init
)paren
suffix:semicolon
DECL|variable|mk712_exit
id|module_exit
c_func
(paren
id|mk712_exit
)paren
suffix:semicolon
eof
