multiline_comment|/* auxio.c: Probing for the Sparc AUXIO register at boot time.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#include &lt;asm/fhc.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/starfire.h&gt;
multiline_comment|/* Probe and map in the Auxiliary I/O register */
DECL|variable|auxio_register
r_int
r_int
id|auxio_register
op_assign
l_int|0
suffix:semicolon
DECL|function|auxio_probe
r_void
id|__init
id|auxio_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
op_assign
l_int|0
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
id|for_each_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;auxio&quot;
)paren
)paren
(brace
r_goto
id|found_sdev
suffix:semicolon
)brace
)brace
)brace
id|found_sdev
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sdev
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|led_auxio
suffix:semicolon
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;auxio&quot;
)paren
)paren
r_goto
id|ebus_done
suffix:semicolon
)brace
)brace
id|ebus_done
suffix:colon
r_if
c_cond
(paren
id|edev
)paren
(brace
id|led_auxio
op_assign
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|outl
c_func
(paren
l_int|0x01
comma
id|led_auxio
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|auxio_register
op_assign
l_int|0UL
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Map the register both read and write */
id|auxio_register
op_assign
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
comma
l_string|&quot;auxiliaryIO&quot;
)paren
suffix:semicolon
id|TURN_ON_LED
suffix:semicolon
)brace
eof
