multiline_comment|/*&n; *  Amiga mouse driver for Linux/m68k&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Michael Rausch&t;&t;James Banks&n; *&t;Matther Dillon&t;&t;David Giller&n; *&t;Nathan Laredo&t;&t;Linus Torvalds&n; *&t;Johan Myreen&t;&t;Jes Sorensen&n; *&t;Russell King&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Amiga mouse driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|amimouse_used
r_static
r_int
id|amimouse_used
op_assign
l_int|0
suffix:semicolon
DECL|variable|amimouse_lastx
DECL|variable|amimouse_lasty
r_static
r_int
id|amimouse_lastx
comma
id|amimouse_lasty
suffix:semicolon
DECL|variable|amimouse_dev
r_static
r_struct
id|input_dev
id|amimouse_dev
suffix:semicolon
DECL|variable|amimouse_name
r_static
r_char
op_star
id|amimouse_name
op_assign
l_string|&quot;Amiga mouse&quot;
suffix:semicolon
DECL|variable|amimouse_phys
r_static
r_char
op_star
id|amimouse_phys
op_assign
l_string|&quot;amimouse/input0&quot;
suffix:semicolon
DECL|function|amimouse_interrupt
r_static
r_void
id|amimouse_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|joy0dat
comma
id|potgor
suffix:semicolon
r_int
id|nx
comma
id|ny
comma
id|dx
comma
id|dy
suffix:semicolon
id|joy0dat
op_assign
id|custom.joy0dat
suffix:semicolon
id|nx
op_assign
id|joy0dat
op_amp
l_int|0xff
suffix:semicolon
id|ny
op_assign
id|joy0dat
op_rshift
l_int|8
suffix:semicolon
id|dx
op_assign
id|nx
op_minus
id|amimouse_lastx
suffix:semicolon
id|dy
op_assign
id|ny
op_minus
id|amimouse_lasty
suffix:semicolon
r_if
c_cond
(paren
id|dx
OL
op_minus
l_int|127
)paren
id|dx
op_assign
(paren
l_int|256
op_plus
id|nx
)paren
op_minus
id|amimouse_lastx
suffix:semicolon
r_if
c_cond
(paren
id|dx
OG
l_int|127
)paren
id|dx
op_assign
(paren
id|nx
op_minus
l_int|256
)paren
op_minus
id|amimouse_lastx
suffix:semicolon
r_if
c_cond
(paren
id|dy
OL
op_minus
l_int|127
)paren
id|dy
op_assign
(paren
l_int|256
op_plus
id|ny
)paren
op_minus
id|amimouse_lasty
suffix:semicolon
r_if
c_cond
(paren
id|dy
OG
l_int|127
)paren
id|dy
op_assign
(paren
id|ny
op_minus
l_int|256
)paren
op_minus
id|amimouse_lasty
suffix:semicolon
id|amimouse_lastx
op_assign
id|nx
suffix:semicolon
id|amimouse_lasty
op_assign
id|ny
suffix:semicolon
id|potgor
op_assign
id|custom.potgor
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|amimouse_dev
comma
id|REL_X
comma
id|dx
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|amimouse_dev
comma
id|REL_Y
comma
id|dy
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|amimouse_dev
comma
id|BTN_LEFT
comma
id|ciaa.pra
op_amp
l_int|0x40
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|amimouse_dev
comma
id|BTN_MIDDLE
comma
id|potgor
op_amp
l_int|0x0100
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|amimouse_dev
comma
id|BTN_RIGHT
comma
id|potgor
op_amp
l_int|0x0400
)paren
suffix:semicolon
)brace
DECL|function|amimouse_open
r_static
r_int
id|amimouse_open
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
id|joy0dat
suffix:semicolon
r_if
c_cond
(paren
id|amimouse_used
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|joy0dat
op_assign
id|custom.joy0dat
suffix:semicolon
id|amimouse_lastx
op_assign
id|joy0dat
op_amp
l_int|0xff
suffix:semicolon
id|amimouse_lasty
op_assign
id|joy0dat
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_AMIGA_VERTB
comma
id|amimouse_interrupt
comma
l_int|0
comma
l_string|&quot;amimouse&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|amimouse_used
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;amimouse.c: Can&squot;t allocate irq %d&bslash;n&quot;
comma
id|amimouse_irq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amimouse_close
r_static
r_void
id|amimouse_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|amimouse_used
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_VERTB
comma
id|amimouse_interrupt
)paren
suffix:semicolon
)brace
DECL|function|amimouse_init
r_static
r_int
id|__init
id|amimouse_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|AMI_MOUSE
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|amimouse_dev.evbit
(braket
l_int|0
)braket
op_assign
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
suffix:semicolon
id|amimouse_dev.relbit
(braket
l_int|0
)braket
op_assign
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
suffix:semicolon
id|amimouse_dev.keybit
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
suffix:semicolon
id|amimouse_dev.open
op_assign
id|amimouse_open
suffix:semicolon
id|amimouse_dev.close
op_assign
id|amimouse_close
suffix:semicolon
id|amimouse_dev.name
op_assign
id|amimouse_name
suffix:semicolon
id|amimouse_dev.phys
op_assign
id|amimouse_phys
suffix:semicolon
id|amimouse_dev.idbus
op_assign
id|BUS_AMIGA
suffix:semicolon
id|amimouse_dev.idvendor
op_assign
l_int|0x0001
suffix:semicolon
id|amimouse_dev.idproduct
op_assign
l_int|0x0002
suffix:semicolon
id|amimouse_dev.idversion
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|amimouse_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s at joy0dat&bslash;n&quot;
comma
id|amimouse_name
)paren
suffix:semicolon
)brace
DECL|function|amimouse_exit
r_static
r_void
id|__exit
id|amimouse_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|amimouse_dev
)paren
suffix:semicolon
)brace
DECL|variable|amimouse_init
id|module_init
c_func
(paren
id|amimouse_init
)paren
suffix:semicolon
DECL|variable|amimouse_exit
id|module_exit
c_func
(paren
id|amimouse_exit
)paren
suffix:semicolon
eof
