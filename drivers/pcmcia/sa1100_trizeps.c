multiline_comment|/*&n; * drivers/pcmcia/sa1100_trizeps.c&n; *&n; * PCMCIA implementation routines for Trizeps&n; *&n; * Authors:&n; * Andreas Hofer &lt;ho@dsa-ac.de&gt;,&n; * Peter Lueg &lt;pl@dsa-ac.de&gt;,&n; * Guennadi Liakhovetski &lt;gl@dsa-ac.de&gt;&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/trizeps.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
DECL|macro|NUMBER_OF_TRIZEPS_PCMCIA_SLOTS
mdefine_line|#define NUMBER_OF_TRIZEPS_PCMCIA_SLOTS 1
multiline_comment|/**&n; *&n; *&n; ******************************************************/
DECL|function|trizeps_pcmcia_init
r_static
r_int
id|trizeps_pcmcia_init
c_func
(paren
r_struct
id|pcmcia_init
op_star
id|init
)paren
(brace
r_int
id|res
suffix:semicolon
multiline_comment|/* Enable CF bus: */
id|TRIZEPS_BCR_clear
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_nPCM_ENA_REG
)paren
suffix:semicolon
multiline_comment|/* All those are inputs */
id|GPDR
op_and_assign
op_complement
(paren
(paren
id|GPIO_GPIO
c_func
(paren
id|TRIZEPS_GPIO_PCMCIA_CD0
)paren
)paren
op_or
(paren
id|GPIO_GPIO
c_func
(paren
id|TRIZEPS_GPIO_PCMCIA_IRQ0
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Set transition detect */
singleline_comment|//&t;set_irq_type(SA1100_GPIO_TO_IRQ(GPIO_TRIZEPS_PCMCIA_CD0), IRQT_BOTHEDGE);
id|set_irq_type
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_IRQ0
comma
id|IRQT_FALLING
)paren
suffix:semicolon
multiline_comment|/* Register SOCKET interrupts */
multiline_comment|/* WHY? */
id|set_irq_type
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_CD0
comma
id|IRQT_NOEDGE
)paren
suffix:semicolon
id|res
op_assign
id|request_irq
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_CD0
comma
id|init-&gt;handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;PCMCIA_CD0&quot;
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
singleline_comment|//MECR = 0x00060006; // Initialised on trizeps init
singleline_comment|// return=sa1100_pcmcia_socket_count (sa1100_generic.c)
singleline_comment|//        -&gt; number of PCMCIA Slots
singleline_comment|// Slot 0 -&gt; Trizeps PCMCIA
singleline_comment|// Slot 1 -&gt; Trizeps ISA-Bus
r_return
id|NUMBER_OF_TRIZEPS_PCMCIA_SLOTS
suffix:semicolon
id|irq_err
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): PCMCIA Request for IRQ %u failed&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|TRIZEPS_IRQ_PCMCIA_CD0
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&n; *&n; ******************************************************/
DECL|function|trizeps_pcmcia_shutdown
r_static
r_int
id|trizeps_pcmcia_shutdown
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&gt;&gt;&gt;&gt;&gt;PCMCIA TRIZEPS shutdown&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* disable IRQs */
id|free_irq
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_CD0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Disable CF bus: */
id|TRIZEPS_BCR_set
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_nPCM_ENA_REG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&n;&n; ******************************************************/
DECL|function|trizeps_pcmcia_socket_state
r_static
r_void
id|trizeps_pcmcia_socket_state
c_func
(paren
r_int
id|sock
comma
r_struct
id|pcmcia_state
op_star
id|state_array
)paren
(brace
r_int
r_int
id|levels
op_assign
id|GPLR
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_eq
l_int|0
)paren
(brace
id|state-&gt;detect
op_assign
(paren
(paren
id|levels
op_amp
id|GPIO_GPIO
c_func
(paren
id|TRIZEPS_GPIO_PCMCIA_CD0
)paren
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
(paren
id|levels
op_amp
id|GPIO_GPIO
c_func
(paren
id|TRIZEPS_GPIO_PCMCIA_IRQ0
)paren
)paren
op_ne
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
(paren
(paren
id|TRIZEPS_BCR1
op_amp
id|TRIZEPS_PCM_BVD1
)paren
op_ne
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
(paren
(paren
id|TRIZEPS_BCR1
op_amp
id|TRIZEPS_PCM_BVD2
)paren
op_ne
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
singleline_comment|// not write protected
id|state-&gt;vs_3v
op_assign
(paren
(paren
id|TRIZEPS_BCR1
op_amp
id|TRIZEPS_nPCM_VS1
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
singleline_comment|//VS1=0 -&gt; vs_3v=1
id|state-&gt;vs_Xv
op_assign
(paren
(paren
id|TRIZEPS_BCR1
op_amp
id|TRIZEPS_nPCM_VS2
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
singleline_comment|//VS2=0 -&gt; vs_Xv=1
)brace
)brace
multiline_comment|/**&n; *&n; *&n; ******************************************************/
DECL|function|trizeps_pcmcia_get_irq_info
r_static
r_int
(def_block
id|trizeps_pcmcia_get_irq_info
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
id|TRIZEPS_IRQ_PCMCIA_IRQ0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
singleline_comment|// MFTB2 use only one Slot
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
)def_block
multiline_comment|/**&n; *&n; *&n; ******************************************************/
DECL|function|trizeps_pcmcia_configure_socket
r_static
r_int
id|trizeps_pcmcia_configure_socket
c_func
(paren
r_int
id|sock
comma
r_const
r_struct
id|pcmcia_configure
op_star
id|configure
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|sock
OG
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
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
id|printk
c_func
(paren
l_string|&quot;&gt;&gt;&gt; PCMCIA Power off&bslash;n&quot;
)paren
suffix:semicolon
id|TRIZEPS_BCR_clear
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_PCM_V3_EN_REG
)paren
suffix:semicolon
id|TRIZEPS_BCR_clear
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_PCM_V5_EN_REG
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
singleline_comment|// 3.3V Power on
id|TRIZEPS_BCR_clear
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_PCM_V3_EN_REG
)paren
suffix:semicolon
id|TRIZEPS_BCR_set
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_PCM_V5_EN_REG
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
singleline_comment|// 5.0V Power on
id|TRIZEPS_BCR_set
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_PCM_V3_EN_REG
)paren
suffix:semicolon
id|TRIZEPS_BCR_clear
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_PCM_V5_EN_REG
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
r_if
c_cond
(paren
id|configure-&gt;reset
)paren
id|TRIZEPS_BCR_set
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_nPCM_RESET_DISABLE
)paren
suffix:semicolon
singleline_comment|// Reset
r_else
id|TRIZEPS_BCR_clear
c_func
(paren
id|TRIZEPS_BCR1
comma
id|TRIZEPS_nPCM_RESET_DISABLE
)paren
suffix:semicolon
singleline_comment|// no Reset
multiline_comment|/*&n;&t;  printk(&quot; vcc=%u vpp=%u --&gt;reset=%i&bslash;n&quot;,&n;&t;  configure-&gt;vcc,&n;&t;  configure-&gt;vpp,&n;&t;  ((BCR_read(1) &amp; nPCM_RESET_DISABLE)? 1:0));&n;&t;*/
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|configure-&gt;irq
)paren
(brace
id|enable_irq
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_CD0
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_IRQ0
)paren
suffix:semicolon
)brace
r_else
(brace
id|disable_irq
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_IRQ0
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|TRIZEPS_IRQ_PCMCIA_CD0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|trizeps_pcmcia_socket_init
r_static
r_int
id|trizeps_pcmcia_socket_init
c_func
(paren
r_int
id|sock
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|trizeps_pcmcia_socket_suspend
r_static
r_int
id|trizeps_pcmcia_socket_suspend
c_func
(paren
r_int
id|sock
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * low-level PCMCIA interface&n; *&n; ******************************************************/
DECL|variable|trizeps_pcmcia_ops
r_struct
id|pcmcia_low_level
id|trizeps_pcmcia_ops
op_assign
(brace
dot
id|init
op_assign
id|trizeps_pcmcia_init
comma
dot
id|shutdown
op_assign
id|trizeps_pcmcia_shutdown
comma
dot
id|socket_state
op_assign
id|trizeps_pcmcia_socket_state
comma
dot
id|get_irq_info
op_assign
id|trizeps_pcmcia_get_irq_info
comma
dot
id|configure_socket
op_assign
id|trizeps_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|trizeps_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|trizeps_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_trizeps_init
r_int
id|__init
id|pcmcia_trizeps_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_trizeps
c_func
(paren
)paren
)paren
(brace
r_return
id|sa1100_register_pcmcia
c_func
(paren
op_amp
id|trizeps_pcmcia_ops
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pcmcia_trizeps_exit
r_void
id|__exit
id|pcmcia_trizeps_exit
c_func
(paren
r_void
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|trizeps_pcmcia_ops
)paren
suffix:semicolon
)brace
eof
