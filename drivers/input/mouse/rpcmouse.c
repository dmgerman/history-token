multiline_comment|/*&n; *  Acorn RiscPC mouse driver for Linux/ARM&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik&n; *  Copyright (C) 1996-2002 Russell King&n; *&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This handles the Acorn RiscPCs mouse.  We basically have a couple of&n; * hardware registers that track the sensor count for the X-Y movement and&n; * another register holding the button state.  On every VSYNC interrupt we read&n; * the complete state and then work out if something has changed.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik, Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Acorn RiscPC mouse driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|rpcmouse_lastx
DECL|variable|rpcmouse_lasty
r_static
r_int
id|rpcmouse_lastx
comma
id|rpcmouse_lasty
suffix:semicolon
DECL|variable|rpcmouse_dev
r_static
r_struct
id|input_dev
id|rpcmouse_dev
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
id|EV_REL
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
id|BTN_LEFT
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
)brace
comma
dot
id|relbit
op_assign
(brace
id|BIT
c_func
(paren
id|REL_X
)paren
op_or
id|BIT
c_func
(paren
id|REL_Y
)paren
)brace
comma
dot
id|name
op_assign
l_string|&quot;Acorn RiscPC Mouse&quot;
comma
dot
id|phys
op_assign
l_string|&quot;rpcmouse/input0&quot;
comma
dot
id|id
op_assign
(brace
dot
id|bustype
op_assign
id|BUS_HOST
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
DECL|function|rpcmouse_irq
r_static
id|irqreturn_t
id|rpcmouse_irq
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
id|input_dev
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
r_int
id|x
comma
id|y
comma
id|dx
comma
id|dy
comma
id|b
suffix:semicolon
id|x
op_assign
(paren
r_int
)paren
id|iomd_readl
c_func
(paren
id|IOMD_MOUSEX
)paren
suffix:semicolon
id|y
op_assign
(paren
r_int
)paren
id|iomd_readl
c_func
(paren
id|IOMD_MOUSEY
)paren
suffix:semicolon
id|b
op_assign
(paren
r_int
)paren
(paren
id|__raw_readl
c_func
(paren
l_int|0xe0310000
)paren
op_xor
l_int|0x70
)paren
suffix:semicolon
id|dx
op_assign
id|x
op_minus
id|rpcmouse_lastx
suffix:semicolon
id|dy
op_assign
id|y
op_minus
id|rpcmouse_lasty
suffix:semicolon
id|rpcmouse_lastx
op_assign
id|x
suffix:semicolon
id|rpcmouse_lasty
op_assign
id|y
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|dx
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
op_minus
id|dy
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|b
op_amp
l_int|0x40
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|b
op_amp
l_int|0x20
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|b
op_amp
l_int|0x10
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|rpcmouse_init
r_static
r_int
id|__init
id|rpcmouse_init
c_func
(paren
r_void
)paren
(brace
id|init_input_dev
c_func
(paren
op_amp
id|rpcmouse_dev
)paren
suffix:semicolon
id|rpcmouse_lastx
op_assign
(paren
r_int
)paren
id|iomd_readl
c_func
(paren
id|IOMD_MOUSEX
)paren
suffix:semicolon
id|rpcmouse_lasty
op_assign
(paren
r_int
)paren
id|iomd_readl
c_func
(paren
id|IOMD_MOUSEY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_VSYNCPULSE
comma
id|rpcmouse_irq
comma
id|SA_SHIRQ
comma
l_string|&quot;rpcmouse&quot;
comma
op_amp
id|rpcmouse_dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rpcmouse: unable to allocate VSYNC interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|rpcmouse_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: Acorn RiscPC mouse&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpcmouse_exit
r_static
r_void
id|__exit
id|rpcmouse_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|rpcmouse_dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_VSYNCPULSE
comma
op_amp
id|rpcmouse_dev
)paren
suffix:semicolon
)brace
DECL|variable|rpcmouse_init
id|module_init
c_func
(paren
id|rpcmouse_init
)paren
suffix:semicolon
DECL|variable|rpcmouse_exit
id|module_exit
c_func
(paren
id|rpcmouse_exit
)paren
suffix:semicolon
eof
