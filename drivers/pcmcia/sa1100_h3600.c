multiline_comment|/*&n; * drivers/pcmcia/sa1100_h3600.c&n; *&n; * PCMCIA implementation routines for H3600&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/h3600.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
DECL|variable|irqs
r_static
r_struct
id|pcmcia_irqs
id|irqs
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
id|IRQ_GPIO_H3600_PCMCIA_CD0
comma
l_string|&quot;PCMCIA CD0&quot;
)brace
comma
(brace
l_int|1
comma
id|IRQ_GPIO_H3600_PCMCIA_CD1
comma
l_string|&quot;PCMCIA CD1&quot;
)brace
)brace
suffix:semicolon
DECL|function|h3600_pcmcia_hw_init
r_static
r_int
id|h3600_pcmcia_hw_init
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
)paren
(brace
id|skt-&gt;irq
op_assign
id|skt-&gt;nr
ques
c_cond
id|IRQ_GPIO_H3600_PCMCIA_IRQ1
suffix:colon
id|IRQ_GPIO_H3600_PCMCIA_IRQ0
suffix:semicolon
r_return
id|sa11xx_request_irqs
c_func
(paren
id|skt
comma
id|irqs
comma
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
)paren
suffix:semicolon
)brace
DECL|function|h3600_pcmcia_hw_shutdown
r_static
r_void
id|h3600_pcmcia_hw_shutdown
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
)paren
(brace
id|sa11xx_free_irqs
c_func
(paren
id|skt
comma
id|irqs
comma
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
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
)brace
r_static
r_void
DECL|function|h3600_pcmcia_socket_state
id|h3600_pcmcia_socket_state
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
comma
r_struct
id|pcmcia_state
op_star
id|state
)paren
(brace
r_int
r_int
id|levels
op_assign
id|GPLR
suffix:semicolon
r_switch
c_cond
(paren
id|skt-&gt;nr
)paren
(brace
r_case
l_int|0
suffix:colon
id|state-&gt;detect
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
id|state-&gt;ready
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
id|state-&gt;bvd1
op_assign
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on H3600. */
id|state-&gt;vs_3v
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|state-&gt;detect
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
id|state-&gt;ready
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
id|state-&gt;bvd1
op_assign
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on H3600. */
id|state-&gt;vs_3v
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|h3600_pcmcia_configure_socket
id|h3600_pcmcia_configure_socket
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
comma
r_const
id|socket_state_t
op_star
id|state
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;Vcc
op_ne
l_int|0
op_logical_and
id|state-&gt;Vcc
op_ne
l_int|33
op_logical_and
id|state-&gt;Vcc
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
id|state-&gt;Vcc
op_div
l_int|10
comma
id|state-&gt;Vcc
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
id|state-&gt;flags
op_amp
id|SS_RESET
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
r_void
id|h3600_pcmcia_socket_init
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
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
id|sa11xx_enable_irqs
c_func
(paren
id|skt
comma
id|irqs
comma
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
)paren
suffix:semicolon
)brace
DECL|function|h3600_pcmcia_socket_suspend
r_static
r_void
id|h3600_pcmcia_socket_suspend
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
)paren
(brace
id|sa11xx_disable_irqs
c_func
(paren
id|skt
comma
id|irqs
comma
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME:  This doesn&squot;t fit well.  We don&squot;t have the mechanism in&n;&t; * the generic PCMCIA layer to deal with the idea of two sockets&n;&t; * on one bus.  We rely on the cs.c behaviour shutting down&n;&t; * socket 0 then socket 1.&n;&t; */
r_if
c_cond
(paren
id|skt-&gt;nr
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
)brace
DECL|variable|h3600_pcmcia_ops
r_struct
id|pcmcia_low_level
id|h3600_pcmcia_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|hw_init
op_assign
id|h3600_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|h3600_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|h3600_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|h3600_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|h3600_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|h3600_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_h3600_init
r_int
id|__init
id|pcmcia_h3600_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_h3600
c_func
(paren
)paren
)paren
id|ret
op_assign
id|sa11xx_drv_pcmcia_probe
c_func
(paren
id|dev
comma
op_amp
id|h3600_pcmcia_ops
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
