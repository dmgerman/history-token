multiline_comment|/*&n; * linux/arch/sh/boards/ec3104/setup.c&n; *  EC3104 companion chip support&n; *&n; * Copyright (C) 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&n; */
multiline_comment|/* EC3104 note:&n; * This code was written without any documentation about the EC3104 chip.  While&n; * I hope I got most of the basic functionality right, the register names I use&n; * are most likely completely different from those in the chip documentation.&n; *&n; * If you have any further information about the EC3104, please tell me&n; * (prumpf@tux.org).&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ec3104/ec3104.h&gt;
DECL|function|setup_ec3104
r_int
id|__init
id|setup_ec3104
c_func
(paren
r_void
)paren
(brace
r_char
id|str
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_EC3104
)paren
id|printk
c_func
(paren
l_string|&quot;!MACH_EC3104&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|str
(braket
id|i
)braket
op_assign
id|ctrl_readb
c_func
(paren
id|EC3104_BASE
op_plus
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|EC3104_IRQBASE
suffix:semicolon
id|i
OL
id|EC3104_IRQBASE
op_plus
l_int|32
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
id|ec3104_int
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;initializing EC3104 &bslash;&quot;%.8s&bslash;&quot; at %08x, IRQ %d, IRQ base %d&bslash;n&quot;
comma
id|str
comma
id|EC3104_BASE
comma
id|EC3104_IRQ
comma
id|EC3104_IRQBASE
)paren
suffix:semicolon
multiline_comment|/* mask all interrupts.  this should have been done by the boot&n;&t; * loader for us but we want to be sure ... */
id|ctrl_writel
c_func
(paren
l_int|0xffffffff
comma
id|EC3104_IMR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_ec3104
id|module_init
c_func
(paren
id|setup_ec3104
)paren
suffix:semicolon
eof
