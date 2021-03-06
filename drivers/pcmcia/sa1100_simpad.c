multiline_comment|/*&n; * drivers/pcmcia/sa1100_simpad.c&n; *&n; * PCMCIA implementation routines for simpad&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/simpad.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
r_extern
r_int
id|get_cs3_shadow
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_cs3_bit
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
r_extern
r_void
id|clear_cs3_bit
c_func
(paren
r_int
id|value
)paren
suffix:semicolon
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
l_int|1
comma
id|IRQ_GPIO_CF_CD
comma
l_string|&quot;CF_CD&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|simpad_pcmcia_hw_init
r_static
r_int
id|simpad_pcmcia_hw_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
id|clear_cs3_bit
c_func
(paren
id|VCC_3V_EN
op_or
id|VCC_5V_EN
op_or
id|EN0
op_or
id|EN1
)paren
suffix:semicolon
id|skt-&gt;irq
op_assign
id|IRQ_GPIO_CF_IRQ
suffix:semicolon
r_return
id|soc_pcmcia_request_irqs
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
DECL|function|simpad_pcmcia_hw_shutdown
r_static
r_void
id|simpad_pcmcia_hw_shutdown
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
id|soc_pcmcia_free_irqs
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
singleline_comment|//set_cs3_bit(PCMCIA_BUFF_DIS);
id|clear_cs3_bit
c_func
(paren
id|PCMCIA_RESET
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|simpad_pcmcia_socket_state
id|simpad_pcmcia_socket_state
c_func
(paren
r_struct
id|soc_pcmcia_socket
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
r_int
id|cs3reg
op_assign
id|get_cs3_shadow
c_func
(paren
)paren
suffix:semicolon
id|state-&gt;detect
op_assign
(paren
(paren
id|levels
op_amp
id|GPIO_CF_CD
)paren
op_eq
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;ready
op_assign
(paren
id|levels
op_amp
id|GPIO_CF_IRQ
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Not available on Simpad. */
id|state-&gt;bvd2
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Not available on Simpad. */
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on Simpad. */
r_if
c_cond
(paren
(paren
id|cs3reg
op_amp
l_int|0x0c
)paren
op_eq
l_int|0x0c
)paren
(brace
id|state-&gt;vs_3v
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|state-&gt;vs_3v
op_assign
l_int|1
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|simpad_pcmcia_configure_socket
id|simpad_pcmcia_configure_socket
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
comma
r_const
id|socket_state_t
op_star
id|state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Murphy: see table of MIC2562a-1 */
r_switch
c_cond
(paren
id|state-&gt;Vcc
)paren
(brace
r_case
l_int|0
suffix:colon
id|clear_cs3_bit
c_func
(paren
id|VCC_3V_EN
op_or
id|VCC_5V_EN
op_or
id|EN0
op_or
id|EN1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|clear_cs3_bit
c_func
(paren
id|VCC_3V_EN
op_or
id|EN1
)paren
suffix:semicolon
id|set_cs3_bit
c_func
(paren
id|VCC_5V_EN
op_or
id|EN0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|clear_cs3_bit
c_func
(paren
id|VCC_5V_EN
op_or
id|EN1
)paren
suffix:semicolon
id|set_cs3_bit
c_func
(paren
id|VCC_3V_EN
op_or
id|EN0
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
l_string|&quot;%s(): unrecognized Vcc %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|state-&gt;Vcc
)paren
suffix:semicolon
id|clear_cs3_bit
c_func
(paren
id|VCC_3V_EN
op_or
id|VCC_5V_EN
op_or
id|EN0
op_or
id|EN1
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|simpad_pcmcia_socket_init
r_static
r_void
id|simpad_pcmcia_socket_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
id|soc_pcmcia_enable_irqs
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
DECL|function|simpad_pcmcia_socket_suspend
r_static
r_void
id|simpad_pcmcia_socket_suspend
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
id|soc_pcmcia_disable_irqs
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
id|set_cs3_bit
c_func
(paren
id|PCMCIA_RESET
)paren
suffix:semicolon
)brace
DECL|variable|simpad_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|simpad_pcmcia_ops
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
id|simpad_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|simpad_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|simpad_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|simpad_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|simpad_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|simpad_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_simpad_init
r_int
id|__init
id|pcmcia_simpad_init
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
id|machine_is_simpad
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
id|simpad_pcmcia_ops
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
