multiline_comment|/*&n; * drivers/pcmcia/sa1100_yopy.c&n; *&n; * PCMCIA implementation routines for Yopy&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
DECL|function|pcmcia_power
r_static
r_inline
r_void
id|pcmcia_power
c_func
(paren
r_int
id|on
)paren
(brace
multiline_comment|/* high for power up */
id|yopy_gpio_set
c_func
(paren
id|GPIO_CF_POWER
comma
id|on
)paren
suffix:semicolon
)brace
DECL|function|pcmcia_reset
r_static
r_inline
r_void
id|pcmcia_reset
c_func
(paren
r_int
id|reset
)paren
(brace
multiline_comment|/* high for reset */
id|yopy_gpio_set
c_func
(paren
id|GPIO_CF_RESET
comma
id|reset
)paren
suffix:semicolon
)brace
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
id|IRQ_CF_CD
comma
l_string|&quot;CF_CD&quot;
)brace
comma
(brace
id|IRQ_CF_BVD2
comma
l_string|&quot;CF_BVD2&quot;
)brace
comma
(brace
id|IRQ_CF_BVD1
comma
l_string|&quot;CF_BVD1&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|yopy_pcmcia_init
r_static
r_int
id|yopy_pcmcia_init
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
id|pcmcia_power
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pcmcia_reset
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set transition detect */
id|set_irq_type
c_func
(paren
id|IRQ_CF_IREQ
comma
id|IRQT_FALLING
)paren
suffix:semicolon
multiline_comment|/* Register interrupts */
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
(brace
id|set_irq_type
c_func
(paren
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
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
r_goto
id|irq_err
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
id|irq_err
suffix:colon
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
r_return
id|res
suffix:semicolon
)brace
DECL|function|yopy_pcmcia_shutdown
r_static
r_int
id|yopy_pcmcia_shutdown
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* disable IRQs */
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
multiline_comment|/* Disable CF */
id|pcmcia_reset
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|pcmcia_power
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yopy_pcmcia_socket_state
r_static
r_int
id|yopy_pcmcia_socket_state
c_func
(paren
r_struct
id|pcmcia_state_array
op_star
id|state_array
)paren
(brace
r_int
r_int
id|levels
suffix:semicolon
r_if
c_cond
(paren
id|state_array-&gt;size
op_ne
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|state_array-&gt;state
comma
l_int|0
comma
id|state_array-&gt;size
op_star
r_sizeof
(paren
r_struct
id|pcmcia_state
)paren
)paren
suffix:semicolon
id|levels
op_assign
id|GPLR
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|detect
op_assign
(paren
id|levels
op_amp
id|GPIO_CF_CD
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|ready
op_assign
(paren
id|levels
op_amp
id|GPIO_CF_READY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|bvd1
op_assign
(paren
id|levels
op_amp
id|GPIO_CF_BVD1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|bvd2
op_assign
(paren
id|levels
op_amp
id|GPIO_CF_BVD2
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on Yopy. */
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|vs_3v
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME Can only apply 3.3V on Yopy. */
id|state_array-&gt;state
(braket
l_int|0
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
DECL|function|yopy_pcmcia_get_irq_info
r_static
r_int
id|yopy_pcmcia_get_irq_info
c_func
(paren
r_struct
id|pcmcia_irq_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;sock
op_ne
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|info-&gt;irq
op_assign
id|IRQ_CF_IREQ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yopy_pcmcia_configure_socket
r_static
r_int
id|yopy_pcmcia_configure_socket
c_func
(paren
r_const
r_struct
id|pcmcia_configure
op_star
id|configure
)paren
(brace
r_if
c_cond
(paren
id|configure-&gt;sock
op_ne
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|configure-&gt;vcc
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* power off */
id|pcmcia_power
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|__FUNCTION__
l_string|&quot;(): CS asked for 5V, applying 3.3V..&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|33
suffix:colon
id|pcmcia_power
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
id|__FUNCTION__
l_string|&quot;(): unrecognized Vcc %u&bslash;n&quot;
comma
id|configure-&gt;vcc
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pcmcia_reset
c_func
(paren
id|configure-&gt;reset
)paren
suffix:semicolon
multiline_comment|/* Silently ignore Vpp, output enable, speaker enable. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yopy_pcmcia_socket_init
r_static
r_int
id|yopy_pcmcia_socket_init
c_func
(paren
r_int
id|sock
)paren
(brace
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
suffix:semicolon
id|i
op_increment
)paren
id|set_irq_type
c_func
(paren
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|yopy_pcmcia_socket_suspend
r_static
r_int
id|yopy_pcmcia_socket_suspend
c_func
(paren
r_int
id|sock
)paren
(brace
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|irqs
)paren
suffix:semicolon
id|i
op_increment
)paren
id|set_irq_type
c_func
(paren
id|irqs
(braket
id|i
)braket
dot
id|irq
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|yopy_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|yopy_pcmcia_ops
op_assign
(brace
dot
id|init
op_assign
id|yopy_pcmcia_init
comma
dot
id|shutdown
op_assign
id|yopy_pcmcia_shutdown
comma
dot
id|socket_state
op_assign
id|yopy_pcmcia_socket_state
comma
dot
id|get_irq_info
op_assign
id|yopy_pcmcia_get_irq_info
comma
dot
id|configure_socket
op_assign
id|yopy_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|yopy_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|yopy_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_yopy_init
r_int
id|__init
id|pcmcia_yopy_init
c_func
(paren
r_void
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
id|machine_is_yopy
c_func
(paren
)paren
)paren
id|ret
op_assign
id|sa1100_register_pcmcia
c_func
(paren
op_amp
id|yopy_pcmcia_ops
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_yopy_exit
r_void
id|__exit
id|pcmcia_yopy_exit
c_func
(paren
r_void
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|yopy_pcmcia_ops
)paren
suffix:semicolon
)brace
eof
