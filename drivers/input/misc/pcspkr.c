multiline_comment|/*&n; *  PC Speaker beeper driver for Linux&n; *&n; *  Copyright (c) 2002 Vojtech Pavlik&n; *  Copyright (c) 1992 Orest Zborowski&n; *&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PC Speaker beeper driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|pcspkr_name
r_static
r_char
id|pcspkr_name
(braket
)braket
op_assign
l_string|&quot;PC Speaker&quot;
suffix:semicolon
DECL|variable|pcspkr_phys
r_static
r_char
id|pcspkr_phys
(braket
)braket
op_assign
l_string|&quot;isa0061/input0&quot;
suffix:semicolon
DECL|variable|pcspkr_dev
r_static
r_struct
id|input_dev
id|pcspkr_dev
suffix:semicolon
DECL|variable|i8253_beep_lock
id|spinlock_t
id|i8253_beep_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|pcspkr_event
r_static
r_int
id|pcspkr_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|EV_SND
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|SND_BELL
suffix:colon
r_if
c_cond
(paren
id|value
)paren
id|value
op_assign
l_int|1000
suffix:semicolon
r_case
id|SND_TONE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
OG
l_int|20
op_logical_and
id|value
OL
l_int|32767
)paren
id|count
op_assign
id|CLOCK_TICK_RATE
op_div
id|value
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_beep_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
multiline_comment|/* enable counter 2 */
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x61
)paren
op_or
l_int|3
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* set command for counter 2, 2 byte write */
id|outb_p
c_func
(paren
l_int|0xB6
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* select desired HZ */
id|outb_p
c_func
(paren
id|count
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x42
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* disable counter 2 */
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x61
)paren
op_amp
l_int|0xFC
comma
l_int|0x61
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_beep_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcspkr_init
r_static
r_int
id|__init
id|pcspkr_init
c_func
(paren
r_void
)paren
(brace
id|pcspkr_dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_SND
)paren
suffix:semicolon
id|pcspkr_dev.sndbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|SND_BELL
)paren
op_or
id|BIT
c_func
(paren
id|SND_TONE
)paren
suffix:semicolon
id|pcspkr_dev.event
op_assign
id|pcspkr_event
suffix:semicolon
id|pcspkr_dev.name
op_assign
id|pcspkr_name
suffix:semicolon
id|pcspkr_dev.phys
op_assign
id|pcspkr_phys
suffix:semicolon
id|pcspkr_dev.id.bustype
op_assign
id|BUS_ISA
suffix:semicolon
id|pcspkr_dev.id.vendor
op_assign
l_int|0x001f
suffix:semicolon
id|pcspkr_dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|pcspkr_dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|pcspkr_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s&bslash;n&quot;
comma
id|pcspkr_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcspkr_exit
r_static
r_void
id|__exit
id|pcspkr_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|pcspkr_dev
)paren
suffix:semicolon
)brace
DECL|variable|pcspkr_init
id|module_init
c_func
(paren
id|pcspkr_init
)paren
suffix:semicolon
DECL|variable|pcspkr_exit
id|module_exit
c_func
(paren
id|pcspkr_exit
)paren
suffix:semicolon
eof
