multiline_comment|/*&n; * drivers/pcmcia/sa1100_flexanet.c&n; *&n; * PCMCIA implementation routines for Flexanet.&n; * by Jordi Colomer, 09/05/2001&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
r_static
r_struct
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|variable|irqs
)brace
id|irqs
(braket
)braket
op_assign
(brace
(brace
id|IRQ_GPIO_CF1_CD
comma
l_string|&quot;CF1_CD&quot;
)brace
comma
(brace
id|IRQ_GPIO_CF1_BVD1
comma
l_string|&quot;CF1_BVD1&quot;
)brace
comma
(brace
id|IRQ_GPIO_CF2_CD
comma
l_string|&quot;CF2_CD&quot;
)brace
comma
(brace
id|IRQ_GPIO_CF2_BVD1
comma
l_string|&quot;CF2_BVD1&quot;
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Socket initialization.&n; *&n; * Called by sa1100_pcmcia_driver_init on startup.&n; * Must return the number of slots.&n; *&n; */
DECL|function|flexanet_pcmcia_init
r_static
r_int
id|flexanet_pcmcia_init
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
multiline_comment|/* Configure the GPIOs as inputs (BVD2 is not implemented) */
id|GPDR
op_and_assign
op_complement
(paren
id|GPIO_CF1_NCD
op_or
id|GPIO_CF1_BVD1
op_or
id|GPIO_CF1_IRQ
op_or
id|GPIO_CF2_NCD
op_or
id|GPIO_CF2_BVD1
op_or
id|GPIO_CF2_IRQ
)paren
suffix:semicolon
multiline_comment|/* Set IRQ edge */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF1_IRQ
comma
id|IRQT_FALLING
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF2_IRQ
comma
id|IRQT_FALLING
)paren
suffix:semicolon
multiline_comment|/* Register the socket interrupts (not the card interrupts) */
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
id|name
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
r_break
suffix:semicolon
)brace
multiline_comment|/* If we failed, then free all interrupts requested thus far. */
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: request for IRQ%d failed: %d&bslash;n&quot;
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
r_return
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n; * Socket shutdown&n; *&n; */
DECL|function|flexanet_pcmcia_shutdown
r_static
r_int
id|flexanet_pcmcia_shutdown
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the state of the sockets.&n; *&n; *  Sockets in Flexanet are 3.3V only, without BVD2.&n; *&n; */
DECL|function|flexanet_pcmcia_socket_state
r_static
r_int
(def_block
id|flexanet_pcmcia_socket_state
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
OL
l_int|2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Sense the GPIOs, asynchronously */
id|levels
op_assign
id|GPLR
suffix:semicolon
multiline_comment|/* Socket 0 */
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|detect
op_assign
(paren
(paren
id|levels
op_amp
id|GPIO_CF1_NCD
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
l_int|0
)braket
dot
id|ready
op_assign
(paren
id|levels
op_amp
id|GPIO_CF1_IRQ
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
id|GPIO_CF1_BVD1
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
l_int|1
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
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|vs_3v
op_assign
l_int|1
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|0
)braket
dot
id|vs_Xv
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Socket 1 */
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
id|GPIO_CF2_NCD
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
id|GPIO_CF2_IRQ
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
(paren
id|levels
op_amp
id|GPIO_CF2_BVD1
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
id|bvd2
op_assign
l_int|1
suffix:semicolon
id|state_array-&gt;state
(braket
l_int|1
)braket
dot
id|wrprot
op_assign
l_int|0
suffix:semicolon
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
r_return
l_int|1
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * Return the IRQ information for a given socket number (the IRQ number)&n; *&n; */
DECL|function|flexanet_pcmcia_get_irq_info
r_static
r_int
(def_block
id|flexanet_pcmcia_get_irq_info
c_func
(paren
r_struct
id|pcmcia_irq_info
op_star
id|info
)paren
(brace
multiline_comment|/* check the socket index */
r_if
c_cond
(paren
id|info-&gt;sock
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
id|info-&gt;sock
op_eq
l_int|0
)paren
id|info-&gt;irq
op_assign
id|IRQ_GPIO_CF1_IRQ
suffix:semicolon
r_else
r_if
c_cond
(paren
id|info-&gt;sock
op_eq
l_int|1
)paren
id|info-&gt;irq
op_assign
id|IRQ_GPIO_CF2_IRQ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; *&n; */
DECL|function|flexanet_pcmcia_configure_socket
r_static
r_int
id|flexanet_pcmcia_configure_socket
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
comma
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|configure-&gt;sock
OG
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Ignore the VCC level since it is 3.3V and always on */
r_switch
c_cond
(paren
id|configure-&gt;vcc
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s(): CS asked to power off.&bslash;n&quot;
comma
id|__FUNCTION__
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
l_string|&quot;%s(): CS asked for 5V, applying 3.3V...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_case
l_int|33
suffix:colon
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
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Reset the slot(s) using the controls in the BCR */
id|mask
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|configure-&gt;sock
)paren
(brace
r_case
l_int|0
suffix:colon
id|mask
op_assign
id|FHH_BCR_CF1_RST
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|mask
op_assign
id|FHH_BCR_CF2_RST
suffix:semicolon
r_break
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|value
op_assign
id|flexanet_BCR
suffix:semicolon
id|value
op_assign
(paren
id|configure-&gt;reset
)paren
ques
c_cond
(paren
id|value
op_or
id|mask
)paren
suffix:colon
(paren
id|value
op_amp
op_complement
id|mask
)paren
suffix:semicolon
id|FHH_BCR
op_assign
id|flexanet_BCR
op_assign
id|value
suffix:semicolon
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
DECL|function|flexanet_pcmcia_socket_init
r_static
r_int
id|flexanet_pcmcia_socket_init
c_func
(paren
r_int
id|sock
)paren
(brace
r_if
c_cond
(paren
id|sock
op_eq
l_int|0
)paren
(brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF1_CD
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF1_BVD1
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sock
op_eq
l_int|1
)paren
(brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF2_CD
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF2_BVD1
comma
id|IRQT_BOTHEDGE
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flexanet_pcmcia_socket_suspend
r_static
r_int
id|flexanet_pcmcia_socket_suspend
c_func
(paren
r_int
id|sock
)paren
(brace
r_if
c_cond
(paren
id|sock
op_eq
l_int|0
)paren
(brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF1_CD
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF1_BVD1
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sock
op_eq
l_int|1
)paren
(brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF2_CD
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF2_BVD1
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The set of socket operations&n; *&n; */
DECL|variable|flexanet_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|flexanet_pcmcia_ops
op_assign
(brace
dot
id|init
op_assign
id|flexanet_pcmcia_init
comma
dot
id|shutdown
op_assign
id|flexanet_pcmcia_shutdown
comma
dot
id|socket_state
op_assign
id|flexanet_pcmcia_socket_state
comma
dot
id|get_irq_info
op_assign
id|flexanet_pcmcia_get_irq_info
comma
dot
id|configure_socket
op_assign
id|flexanet_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|flexanet_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|flexanet_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_flexanet_init
r_int
id|__init
id|pcmcia_flexanet_init
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
id|machine_is_flexanet
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
id|flexanet_pcmcia_ops
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_flexanet_exit
r_void
id|__exit
id|pcmcia_flexanet_exit
c_func
(paren
r_void
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|flexanet_pcmcia_ops
)paren
suffix:semicolon
)brace
eof
