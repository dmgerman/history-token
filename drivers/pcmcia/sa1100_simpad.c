multiline_comment|/*&n; * drivers/pcmcia/sa1100_simpad.c&n; *&n; * PCMCIA implementation routines for simpad&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
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
DECL|function|simpad_pcmcia_init
r_static
r_int
(def_block
id|simpad_pcmcia_init
c_func
(paren
r_struct
id|pcmcia_init
op_star
id|init
)paren
(brace
r_int
id|irq
comma
id|res
suffix:semicolon
id|set_cs3_bit
c_func
(paren
id|PCMCIA_RESET
)paren
suffix:semicolon
id|clear_cs3_bit
c_func
(paren
id|PCMCIA_BUFF_DIS
)paren
suffix:semicolon
id|clear_cs3_bit
c_func
(paren
id|PCMCIA_RESET
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
multiline_comment|/* Set transition detect */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF_CD
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF_IRQ
comma
id|IRQT_FALLING
)paren
suffix:semicolon
multiline_comment|/* Register interrupts */
id|irq
op_assign
id|IRQ_GPIO_CF_CD
suffix:semicolon
id|res
op_assign
id|request_irq
c_func
(paren
id|irq
comma
id|init-&gt;handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;CF_CD&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
r_goto
id|irq_err
suffix:semicolon
)brace
multiline_comment|/* There&squot;s only one slot, but it&squot;s &quot;Slot 1&quot;: */
r_return
l_int|2
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
id|irq
comma
id|res
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
)def_block
DECL|function|simpad_pcmcia_shutdown
r_static
r_int
id|simpad_pcmcia_shutdown
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* disable IRQs */
id|free_irq
c_func
(paren
id|IRQ_GPIO_CF_CD
comma
l_int|NULL
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|simpad_pcmcia_socket_state
r_static
r_int
id|simpad_pcmcia_socket_state
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
r_int
r_int
op_star
id|cs3reg
op_assign
id|CS3_BASE
suffix:semicolon
r_if
c_cond
(paren
id|state_array-&gt;size
OL
l_int|2
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|state_array-&gt;state
comma
l_int|0
comma
(paren
id|state_array-&gt;size
)paren
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
l_int|1
)braket
dot
id|detect
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
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|ready
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
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|bvd1
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Not available on Simpad. */
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|bvd2
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Not available on Simpad. */
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on Simpad. */
r_if
c_cond
(paren
(paren
op_star
id|cs3reg
op_amp
l_int|0x0c
)paren
op_eq
l_int|0x0c
)paren
(brace
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|vs_3v
op_assign
l_int|0
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|vs_Xv
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|vs_3v
op_assign
l_int|1
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|vs_Xv
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|simpad_pcmcia_get_irq_info
r_static
r_int
(def_block
id|simpad_pcmcia_get_irq_info
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
OG
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;sock
op_eq
l_int|1
)paren
(brace
id|info-&gt;irq
op_assign
id|IRQ_GPIO_CF_IRQ
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)def_block
DECL|function|simpad_pcmcia_configure_socket
r_static
r_int
id|simpad_pcmcia_configure_socket
c_func
(paren
r_const
r_struct
id|pcmcia_configure
op_star
id|configure
)paren
(brace
r_int
r_int
id|value
comma
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|configure-&gt;sock
OG
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|configure-&gt;sock
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|configure-&gt;vcc
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
id|EN0
)paren
suffix:semicolon
id|set_cs3_bit
c_func
(paren
id|VCC_5V_EN
op_or
id|EN1
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
id|configure-&gt;vcc
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
multiline_comment|/* Silently ignore Vpp, output enable, speaker enable. */
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
r_int
id|simpad_pcmcia_socket_init
c_func
(paren
r_int
id|sock
)paren
(brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF_CD
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|simpad_pcmcia_socket_suspend
r_static
r_int
id|simpad_pcmcia_socket_suspend
c_func
(paren
r_int
id|sock
)paren
(brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF_CD
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|simpad_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|simpad_pcmcia_ops
op_assign
(brace
id|init
suffix:colon
id|simpad_pcmcia_init
comma
id|shutdown
suffix:colon
id|simpad_pcmcia_shutdown
comma
id|socket_state
suffix:colon
id|simpad_pcmcia_socket_state
comma
id|get_irq_info
suffix:colon
id|simpad_pcmcia_get_irq_info
comma
id|configure_socket
suffix:colon
id|simpad_pcmcia_configure_socket
comma
id|socket_init
suffix:colon
id|simpad_pcmcia_socket_init
comma
id|socket_suspend
suffix:colon
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
id|machine_is_simpad
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
id|simpad_pcmcia_ops
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_simpad_exit
r_void
id|__exit
id|pcmcia_simpad_exit
c_func
(paren
r_void
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|simpad_pcmcia_ops
)paren
suffix:semicolon
)brace
eof
