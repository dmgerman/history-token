multiline_comment|/*&n; * drivers/pcmcia/sa1100_pangolin.c&n; *&n; * PCMCIA implementation routines for Pangolin&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
macro_line|#ifndef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
DECL|macro|PANGOLIN_SOCK
mdefine_line|#define PANGOLIN_SOCK&t;1
macro_line|#else
DECL|macro|PANGOLIN_SOCK
mdefine_line|#define PANGOLIN_SOCK&t;0
macro_line|#endif
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
id|PANGOLIN_SOCK
comma
id|IRQ_PCMCIA_CD
comma
l_string|&quot;PCMCIA CD&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|pangolin_pcmcia_hw_init
r_static
r_int
id|pangolin_pcmcia_hw_init
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
)paren
(brace
r_int
id|res
suffix:semicolon
macro_line|#ifndef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
multiline_comment|/* Enable PCMCIA bus: */
id|GPCR
op_assign
id|GPIO_PCMCIA_BUS_ON
suffix:semicolon
macro_line|#endif
id|skt-&gt;irq
op_assign
id|IRQ_PCMCIA_IRQ
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
DECL|function|pangolin_pcmcia_hw_shutdown
r_static
r_void
id|pangolin_pcmcia_hw_shutdown
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
macro_line|#ifndef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
multiline_comment|/* Disable PCMCIA bus: */
id|GPSR
op_assign
id|GPIO_PCMCIA_BUS_ON
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
DECL|function|pangolin_pcmcia_socket_state
id|pangolin_pcmcia_socket_state
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
id|state-&gt;detect
op_assign
(paren
(paren
id|levels
op_amp
id|GPIO_PCMCIA_CD
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
id|GPIO_PCMCIA_IRQ
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
multiline_comment|/* Not available on Pangolin. */
id|state-&gt;bvd2
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Not available on Pangolin. */
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Not available on Pangolin. */
id|state-&gt;vs_3v
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Can only apply 3.3V on Pangolin. */
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pangolin_pcmcia_configure_socket
id|pangolin_pcmcia_configure_socket
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
r_int
r_int
id|value
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Murphy: BUS_ON different from POWER ? */
r_switch
c_cond
(paren
id|state-&gt;Vcc
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
macro_line|#ifndef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
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
multiline_comment|/* Can only apply 3.3V to the CF slot. */
r_break
suffix:semicolon
macro_line|#else
r_case
l_int|50
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s(): CS asked for 5V, determinded by &quot;
l_string|&quot;jumper setting...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s(): CS asked for 3.3V, determined by &quot;
l_string|&quot;jumper setting...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
multiline_comment|/* reset &amp; unreset request */
r_if
c_cond
(paren
id|skt-&gt;nr
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
(brace
id|GPSR
op_assign
id|GPIO_PCMCIA_RESET
suffix:semicolon
)brace
r_else
(brace
id|GPCR
op_assign
id|GPIO_PCMCIA_RESET
suffix:semicolon
)brace
)brace
macro_line|#endif
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
DECL|function|pangolin_pcmcia_socket_init
r_static
r_void
id|pangolin_pcmcia_socket_init
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
)paren
(brace
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
DECL|function|pangolin_pcmcia_socket_suspend
r_static
r_void
id|pangolin_pcmcia_socket_suspend
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
)brace
DECL|variable|pangolin_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|pangolin_pcmcia_ops
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
id|pangolin_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|pangolin_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|pangolin_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|pangolin_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|pangolin_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|pangolin_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_pangolin_init
r_int
id|__init
id|pcmcia_pangolin_init
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
id|machine_is_pangolin
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
id|pangolin_pcmcia_ops
comma
id|PANGOLIN_SOCK
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
