multiline_comment|/*&n; * drivers/pcmcia/sa1100_cerf.c&n; *&n; * PCMCIA implementation routines for CerfBoard&n; * Based off the Assabet.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
DECL|macro|CERF_SOCKET
mdefine_line|#define CERF_SOCKET&t;0
macro_line|#else
DECL|macro|CERF_SOCKET
mdefine_line|#define CERF_SOCKET&t;1
macro_line|#endif
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
id|IRQ_GPIO_CF_CD
comma
l_string|&quot;CF_CD&quot;
)brace
comma
(brace
id|IRQ_GPIO_CF_BVD2
comma
l_string|&quot;CF_BVD2&quot;
)brace
comma
(brace
id|IRQ_GPIO_CF_BVD1
comma
l_string|&quot;CF_BVD1&quot;
)brace
)brace
suffix:semicolon
DECL|function|cerf_pcmcia_init
r_static
r_int
id|cerf_pcmcia_init
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
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_CF_IRQ
comma
id|IRQT_FALLING
)paren
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
DECL|function|cerf_pcmcia_shutdown
r_static
r_int
id|cerf_pcmcia_shutdown
c_func
(paren
r_void
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
DECL|function|cerf_pcmcia_socket_state
r_static
r_int
(def_block
id|cerf_pcmcia_socket_state
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
id|i
op_assign
id|CERF_SOCKET
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
id|levels
op_assign
id|GPLR
suffix:semicolon
id|state_array-&gt;state
(braket
id|i
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
id|i
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
id|i
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
id|i
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
id|i
)braket
dot
id|wrprot
op_assign
l_int|0
suffix:semicolon
id|state_array-&gt;state
(braket
id|i
)braket
dot
id|vs_3v
op_assign
l_int|1
suffix:semicolon
id|state_array-&gt;state
(braket
id|i
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
DECL|function|cerf_pcmcia_get_irq_info
r_static
r_int
(def_block
id|cerf_pcmcia_get_irq_info
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
id|CERF_SOCKET
)paren
id|info-&gt;irq
op_assign
id|IRQ_GPIO_CF_IRQ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
DECL|function|cerf_pcmcia_configure_socket
r_static
r_int
id|cerf_pcmcia_configure_socket
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
op_ne
id|CERF_SOCKET
)paren
r_return
l_int|0
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
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
r_case
l_int|33
suffix:colon
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
id|GPCR
op_assign
id|GPIO_PWR_SHUTDOWN
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|configure-&gt;reset
)paren
(brace
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
id|GPSR
op_assign
id|GPIO_CF_RESET
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
id|GPCR
op_assign
id|GPIO_CF_RESET
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cerf_pcmcia_socket_init
r_static
r_int
id|cerf_pcmcia_socket_init
c_func
(paren
r_int
id|sock
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
id|CERF_SOCKET
)paren
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
DECL|function|cerf_pcmcia_socket_suspend
r_static
r_int
id|cerf_pcmcia_socket_suspend
c_func
(paren
r_int
id|sock
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
id|CERF_SOCKET
)paren
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
DECL|variable|cerf_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|cerf_pcmcia_ops
op_assign
(brace
dot
id|init
op_assign
id|cerf_pcmcia_init
comma
dot
id|shutdown
op_assign
id|cerf_pcmcia_shutdown
comma
dot
id|socket_state
op_assign
id|cerf_pcmcia_socket_state
comma
dot
id|get_irq_info
op_assign
id|cerf_pcmcia_get_irq_info
comma
dot
id|configure_socket
op_assign
id|cerf_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|cerf_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|cerf_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_cerf_init
r_int
id|__init
id|pcmcia_cerf_init
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
id|machine_is_cerf
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
id|cerf_pcmcia_ops
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_cerf_exit
r_void
id|__exit
id|pcmcia_cerf_exit
c_func
(paren
r_void
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|cerf_pcmcia_ops
)paren
suffix:semicolon
)brace
eof
