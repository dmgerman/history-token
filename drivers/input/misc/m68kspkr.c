multiline_comment|/*&n; *  m68k beeper driver for Linux&n; *&n; *  Copyright (c) 2002 Richard Zidlicky&n; *  Copyright (c) 2002 Vojtech Pavlik&n; *  Copyright (c) 1992 Orest Zborowski&n; *&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Richard Zidlicky &lt;rz@linux-m68k.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;m68k beeper driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|m68kspkr_name
r_static
r_char
id|m68kspkr_name
(braket
)braket
op_assign
l_string|&quot;m68k beeper&quot;
suffix:semicolon
DECL|variable|m68kspkr_phys
r_static
r_char
id|m68kspkr_phys
(braket
)braket
op_assign
l_string|&quot;m68k/generic&quot;
suffix:semicolon
DECL|variable|m68kspkr_dev
r_static
r_struct
id|input_dev
id|m68kspkr_dev
suffix:semicolon
DECL|function|m68kspkr_event
r_static
r_int
id|m68kspkr_event
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
l_int|1193182
op_div
id|value
suffix:semicolon
id|mach_beep
c_func
(paren
id|count
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|m68kspkr_init
r_static
r_int
id|__init
id|m68kspkr_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mach_beep
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: no lowlevel beep support&bslash;n&quot;
comma
id|m68kspkr_name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|m68kspkr_dev.evbit
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
id|m68kspkr_dev.sndbit
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
id|m68kspkr_dev.event
op_assign
id|m68kspkr_event
suffix:semicolon
id|m68kspkr_dev.name
op_assign
id|m68kspkr_name
suffix:semicolon
id|m68kspkr_dev.phys
op_assign
id|m68kspkr_phys
suffix:semicolon
id|m68kspkr_dev.id.bustype
op_assign
id|BUS_HOST
suffix:semicolon
id|m68kspkr_dev.id.vendor
op_assign
l_int|0x001f
suffix:semicolon
id|m68kspkr_dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|m68kspkr_dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|m68kspkr_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s&bslash;n&quot;
comma
id|m68kspkr_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|m68kspkr_exit
r_static
r_void
id|__exit
id|m68kspkr_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|m68kspkr_dev
)paren
suffix:semicolon
)brace
DECL|variable|m68kspkr_init
id|module_init
c_func
(paren
id|m68kspkr_init
)paren
suffix:semicolon
DECL|variable|m68kspkr_exit
id|module_exit
c_func
(paren
id|m68kspkr_exit
)paren
suffix:semicolon
eof
