multiline_comment|/*&n; * drivers/pcmcia/sa1100_h3600.c&n; *&n; * PCMCIA implementation routines for H3600&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
DECL|struct|irqs
r_static
r_struct
id|irqs
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|str
r_const
r_char
op_star
id|str
suffix:semicolon
DECL|variable|irqs
)brace
id|irqs
(braket
)braket
op_assign
(brace
(brace
id|IRQ_GPIO_H3600_PCMCIA_CD0
comma
l_string|&quot;PCMCIA CD0&quot;
)brace
comma
(brace
id|IRQ_GPIO_H3600_PCMCIA_CD1
comma
l_string|&quot;PCMCIA CD1&quot;
)brace
)brace
suffix:semicolon
DECL|function|h3600_pcmcia_init
r_static
r_int
id|h3600_pcmcia_init
c_func
(paren
r_struct
id|pcmcia_init
op_star
id|init
)paren
(brace
r_int
id|i
comma
id|res
suffix:semicolon
multiline_comment|/*&n;&t; * Set transition detect&n;&t; */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3600_PCMCIA_IRQ0
comma
id|IRQT_FALLING
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3600_PCMCIA_IRQ1
comma
id|IRQT_FALLING
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register interrupts&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|res
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|res
op_assign
id|request_irq
c_func
(paren
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
id|init-&gt;handler
comma
id|SA_INTERRUPT
comma
id|irqs
(braket
id|i
)braket
dot
id|str
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: request for IRQ%d failed (%d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
id|res
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|free_irq
c_func
(paren
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|res
ques
c_cond
id|res
suffix:colon
l_int|2
suffix:semicolon
)brace
DECL|function|h3600_pcmcia_shutdown
r_static
r_int
id|h3600_pcmcia_shutdown
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * disable IRQs&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
suffix:semicolon
id|i
op_increment
)paren
id|free_irq
c_func
(paren
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Disable CF bus: */
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_NVRAM_ON
)paren
suffix:semicolon
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_ON
)paren
suffix:semicolon
id|set_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_RESET
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|h3600_pcmcia_socket_state
id|h3600_pcmcia_socket_state
c_func
(paren
r_struct
id|pcmcia_state_array
op_star
id|state
)paren
(brace
r_int
r_int
id|levels
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;size
OL
l_int|2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|levels
op_assign
id|GPLR
suffix:semicolon
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|detect
op_assign
id|levels
op_amp
id|GPIO_H3600_PCMCIA_CD0
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|ready
op_assign
id|levels
op_amp
id|GPIO_H3600_PCMCIA_IRQ0
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|bvd1
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|bvd2
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on H3600. */
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|vs_3v
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|0
)braket
dot
id|vs_Xv
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|detect
op_assign
id|levels
op_amp
id|GPIO_H3600_PCMCIA_CD1
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|ready
op_assign
id|levels
op_amp
id|GPIO_H3600_PCMCIA_IRQ1
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|bvd1
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|bvd2
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on H3600. */
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|vs_3v
op_assign
l_int|0
suffix:semicolon
id|state-&gt;state
(braket
l_int|1
)braket
dot
id|vs_Xv
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|h3600_pcmcia_get_irq_info
r_static
r_int
id|h3600_pcmcia_get_irq_info
c_func
(paren
r_struct
id|pcmcia_irq_info
op_star
id|info
)paren
(brace
r_switch
c_cond
(paren
id|info-&gt;sock
)paren
(brace
r_case
l_int|0
suffix:colon
id|info-&gt;irq
op_assign
id|IRQ_GPIO_H3600_PCMCIA_IRQ0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|info-&gt;irq
op_assign
id|IRQ_GPIO_H3600_PCMCIA_IRQ1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|h3600_pcmcia_configure_socket
id|h3600_pcmcia_configure_socket
c_func
(paren
r_const
r_struct
id|pcmcia_configure
op_star
id|conf
)paren
(brace
r_if
c_cond
(paren
id|conf-&gt;sock
OG
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|conf-&gt;vcc
op_ne
l_int|0
op_logical_and
id|conf-&gt;vcc
op_ne
l_int|33
op_logical_and
id|conf-&gt;vcc
op_ne
l_int|50
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;h3600_pcmcia: unrecognized Vcc %u.%uV&bslash;n&quot;
comma
id|conf-&gt;vcc
op_div
l_int|10
comma
id|conf-&gt;vcc
op_mod
l_int|10
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|conf-&gt;reset
)paren
id|set_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_CARD_RESET
)paren
suffix:semicolon
r_else
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_CARD_RESET
)paren
suffix:semicolon
multiline_comment|/* Silently ignore Vpp, output enable, speaker enable. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h3600_pcmcia_socket_init
r_static
r_int
id|h3600_pcmcia_socket_init
c_func
(paren
r_int
id|sock
)paren
(brace
multiline_comment|/* Enable CF bus: */
id|set_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_NVRAM_ON
)paren
suffix:semicolon
id|set_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_ON
)paren
suffix:semicolon
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_RESET
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|10
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sock
)paren
(brace
r_case
l_int|0
suffix:colon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3600_PCMCIA_CD0
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3600_PCMCIA_CD1
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h3600_pcmcia_socket_suspend
r_static
r_int
id|h3600_pcmcia_socket_suspend
c_func
(paren
r_int
id|sock
)paren
(brace
r_switch
c_cond
(paren
id|sock
)paren
(brace
r_case
l_int|0
suffix:colon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3600_PCMCIA_CD0
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_H3600_PCMCIA_CD1
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * FIXME:  This doesn&squot;t fit well.  We don&squot;t have the mechanism in&n;&t; * the generic PCMCIA layer to deal with the idea of two sockets&n;&t; * on one bus.  We rely on the cs.c behaviour shutting down&n;&t; * socket 0 then socket 1.&n;&t; */
r_if
c_cond
(paren
id|sock
op_eq
l_int|1
)paren
(brace
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_ON
)paren
suffix:semicolon
id|clr_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_NVRAM_ON
)paren
suffix:semicolon
multiline_comment|/* hmm, does this suck power? */
id|set_h3600_egpio
c_func
(paren
id|IPAQ_EGPIO_OPT_RESET
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|h3600_pcmcia_ops
r_struct
id|pcmcia_low_level
id|h3600_pcmcia_ops
op_assign
(brace
id|init
suffix:colon
id|h3600_pcmcia_init
comma
id|shutdown
suffix:colon
id|h3600_pcmcia_shutdown
comma
id|socket_state
suffix:colon
id|h3600_pcmcia_socket_state
comma
id|get_irq_info
suffix:colon
id|h3600_pcmcia_get_irq_info
comma
id|configure_socket
suffix:colon
id|h3600_pcmcia_configure_socket
comma
id|socket_init
suffix:colon
id|h3600_pcmcia_socket_init
comma
id|socket_suspend
suffix:colon
id|h3600_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
eof
