multiline_comment|/*&n; *&n; * By Dustin McIntire (dustin@sensoria.com) (c)2001&n; * &n; * Setup and IRQ handling code for the HD64465 companion chip.&n; * by Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * Copyright (c) 2000 PocketPenguins Inc&n; *&n; * Derived from setup_hd64465.c which bore the message:&n; * Greg Banks &lt;gbanks@pocketpenguins.com&gt;&n; * Copyright (c) 2000 PocketPenguins Inc and&n; * Copyright (C) 2000 YAEGASHI Takeshi&n; * and setup_cqreek.c which bore message:&n; * Copyright (C) 2000  Niibe Yutaka&n; * &n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Setup functions for a Hitachi Big Sur Evaluation Board.&n; * &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/bigsur/io.h&gt;
macro_line|#include &lt;asm/hd64465/hd64465.h&gt;
macro_line|#include &lt;asm/bigsur/bigsur.h&gt;
singleline_comment|//#define BIGSUR_DEBUG 3
DECL|macro|BIGSUR_DEBUG
macro_line|#undef BIGSUR_DEBUG
macro_line|#ifdef BIGSUR_DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(args...)&t;printk(args)
DECL|macro|DIPRINTK
mdefine_line|#define DIPRINTK(n, args...)&t;if (BIGSUR_DEBUG&gt;(n)) printk(args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(args...)
DECL|macro|DIPRINTK
mdefine_line|#define DIPRINTK(n, args...)
macro_line|#endif /* BIGSUR_DEBUG */
multiline_comment|/*===========================================================*/
singleline_comment|//&t;&t;Big Sur Init Routines&t;
multiline_comment|/*===========================================================*/
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;Big Sur&quot;
suffix:semicolon
)brace
DECL|function|platform_setup
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|done
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* run this only once */
r_if
c_cond
(paren
op_logical_neg
id|MACH_BIGSUR
op_logical_or
id|done
)paren
r_return
l_int|0
suffix:semicolon
id|done
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Mask all 2nd level IRQ&squot;s */
id|outb
c_func
(paren
op_minus
l_int|1
comma
id|BIGSUR_IMR0
)paren
suffix:semicolon
id|outb
c_func
(paren
op_minus
l_int|1
comma
id|BIGSUR_IMR1
)paren
suffix:semicolon
id|outb
c_func
(paren
op_minus
l_int|1
comma
id|BIGSUR_IMR2
)paren
suffix:semicolon
id|outb
c_func
(paren
op_minus
l_int|1
comma
id|BIGSUR_IMR3
)paren
suffix:semicolon
multiline_comment|/* Mask 1st level interrupts */
id|outb
c_func
(paren
op_minus
l_int|1
comma
id|BIGSUR_IRLMR0
)paren
suffix:semicolon
id|outb
c_func
(paren
op_minus
l_int|1
comma
id|BIGSUR_IRLMR1
)paren
suffix:semicolon
macro_line|#if defined (CONFIG_HD64465) &amp;&amp; defined (CONFIG_SERIAL) 
multiline_comment|/* remap IO ports for first ISA serial port to HD64465 UART */
id|bigsur_port_map
c_func
(paren
l_int|0x3f8
comma
l_int|8
comma
id|CONFIG_HD64465_IOBASE
op_plus
l_int|0x8000
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HD64465 &amp;&amp; CONFIG_SERIAL */
multiline_comment|/* TODO: setup IDE registers */
id|bigsur_port_map
c_func
(paren
id|BIGSUR_IDECTL_IOPORT
comma
l_int|2
comma
id|BIGSUR_ICTL
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Setup the Ethernet port to BIGSUR_ETHER_IOPORT */
id|bigsur_port_map
c_func
(paren
id|BIGSUR_ETHER_IOPORT
comma
l_int|16
comma
id|BIGSUR_ETHR
op_plus
id|BIGSUR_ETHER_IOPORT
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set page to 1 */
id|outw
c_func
(paren
l_int|1
comma
id|BIGSUR_ETHR
op_plus
l_int|0xe
)paren
suffix:semicolon
multiline_comment|/* set the IO port to BIGSUR_ETHER_IOPORT */
id|outw
c_func
(paren
id|BIGSUR_ETHER_IOPORT
op_lshift
l_int|3
comma
id|BIGSUR_ETHR
op_plus
l_int|0x2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_bigsur
id|module_init
c_func
(paren
id|setup_bigsur
)paren
suffix:semicolon
eof
