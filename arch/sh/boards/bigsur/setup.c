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
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/bigsur/io.h&gt;
macro_line|#include &lt;asm/hd64465/hd64465.h&gt;
macro_line|#include &lt;asm/bigsur/bigsur.h&gt;
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
multiline_comment|/*&n; * The Machine Vector&n; */
r_extern
r_void
id|heartbeat_bigsur
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_bigsur_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_bigsur
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
id|NR_IRQS
comma
singleline_comment|// Defined in &lt;asm/irq.h&gt;
dot
id|mv_isa_port2addr
op_assign
id|bigsur_isa_port2addr
comma
dot
id|mv_irq_demux
op_assign
id|bigsur_irq_demux
comma
dot
id|mv_init_irq
op_assign
id|init_bigsur_IRQ
comma
macro_line|#ifdef CONFIG_HEARTBEAT
dot
id|mv_heartbeat
op_assign
id|heartbeat_bigsur
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|ALIAS_MV
id|ALIAS_MV
c_func
(paren
id|bigsur
)paren
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
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
eof
