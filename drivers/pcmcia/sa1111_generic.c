multiline_comment|/*&n; * linux/drivers/pcmcia/sa1111_generic.c&n; *&n; * We implement the generic parts of a SA1111 PCMCIA driver.  This&n; * basically means we handle everything except controlling the&n; * power.  Power is machine specific...&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1111_generic.h&quot;
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
id|IRQ_S0_CD_VALID
comma
l_string|&quot;SA1111 PCMCIA card detect&quot;
)brace
comma
(brace
l_int|0
comma
id|IRQ_S0_BVD1_STSCHG
comma
l_string|&quot;SA1111 PCMCIA BVD1&quot;
)brace
comma
(brace
l_int|1
comma
id|IRQ_S1_CD_VALID
comma
l_string|&quot;SA1111 CF card detect&quot;
)brace
comma
(brace
l_int|1
comma
id|IRQ_S1_BVD1_STSCHG
comma
l_string|&quot;SA1111 CF BVD1&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|sa1111_pcmcia_hw_init
r_int
id|sa1111_pcmcia_hw_init
c_func
(paren
r_struct
id|sa1100_pcmcia_socket
op_star
id|skt
)paren
(brace
r_if
c_cond
(paren
id|skt-&gt;irq
op_eq
id|NO_IRQ
)paren
id|skt-&gt;irq
op_assign
id|skt-&gt;nr
ques
c_cond
id|IRQ_S1_READY_NINT
suffix:colon
id|IRQ_S0_READY_NINT
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
DECL|function|sa1111_pcmcia_hw_shutdown
r_void
id|sa1111_pcmcia_hw_shutdown
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
)brace
DECL|function|sa1111_pcmcia_socket_state
r_void
id|sa1111_pcmcia_socket_state
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
r_struct
id|sa1111_dev
op_star
id|sadev
op_assign
id|SA1111_DEV
c_func
(paren
id|skt-&gt;dev
)paren
suffix:semicolon
r_int
r_int
id|status
op_assign
id|sa1111_readl
c_func
(paren
id|sadev-&gt;mapbase
op_plus
id|SA1111_PCSR
)paren
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
id|status
op_amp
id|PCSR_S0_DETECT
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;ready
op_assign
id|status
op_amp
id|PCSR_S0_READY
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
id|status
op_amp
id|PCSR_S0_BVD1
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
id|status
op_amp
id|PCSR_S0_BVD2
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
id|status
op_amp
id|PCSR_S0_WP
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
id|status
op_amp
id|PCSR_S0_VS1
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
id|status
op_amp
id|PCSR_S0_VS2
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|state-&gt;detect
op_assign
id|status
op_amp
id|PCSR_S1_DETECT
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;ready
op_assign
id|status
op_amp
id|PCSR_S1_READY
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
id|status
op_amp
id|PCSR_S1_BVD1
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
id|status
op_amp
id|PCSR_S1_BVD2
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
id|status
op_amp
id|PCSR_S1_WP
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
id|status
op_amp
id|PCSR_S1_VS1
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
id|status
op_amp
id|PCSR_S1_VS2
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|sa1111_pcmcia_configure_socket
r_int
id|sa1111_pcmcia_configure_socket
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
r_struct
id|sa1111_dev
op_star
id|sadev
op_assign
id|SA1111_DEV
c_func
(paren
id|skt-&gt;dev
)paren
suffix:semicolon
r_int
r_int
id|pccr_skt_mask
comma
id|pccr_set_mask
comma
id|val
suffix:semicolon
r_int
r_int
id|flags
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
id|pccr_skt_mask
op_assign
id|PCCR_S0_RST
op_or
id|PCCR_S0_FLT
op_or
id|PCCR_S0_PWAITEN
op_or
id|PCCR_S0_PSE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|pccr_skt_mask
op_assign
id|PCCR_S1_RST
op_or
id|PCCR_S1_FLT
op_or
id|PCCR_S1_PWAITEN
op_or
id|PCCR_S1_PSE
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
id|pccr_set_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;Vcc
op_ne
l_int|0
)paren
id|pccr_set_mask
op_or_assign
id|PCCR_S0_PWAITEN
op_or
id|PCCR_S1_PWAITEN
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;Vcc
op_eq
l_int|50
)paren
id|pccr_set_mask
op_or_assign
id|PCCR_S0_PSE
op_or
id|PCCR_S1_PSE
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
id|pccr_set_mask
op_or_assign
id|PCCR_S0_RST
op_or
id|PCCR_S1_RST
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|SS_OUTPUT_ENA
)paren
id|pccr_set_mask
op_or_assign
id|PCCR_S0_FLT
op_or
id|PCCR_S1_FLT
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|sa1111_readl
c_func
(paren
id|sadev-&gt;mapbase
op_plus
id|SA1111_PCCR
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|pccr_skt_mask
suffix:semicolon
id|val
op_or_assign
id|pccr_set_mask
op_amp
id|pccr_skt_mask
suffix:semicolon
id|sa1111_writel
c_func
(paren
id|val
comma
id|sadev-&gt;mapbase
op_plus
id|SA1111_PCCR
)paren
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
DECL|function|sa1111_pcmcia_socket_init
r_void
id|sa1111_pcmcia_socket_init
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
DECL|function|sa1111_pcmcia_socket_suspend
r_void
id|sa1111_pcmcia_socket_suspend
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
DECL|function|pcmcia_probe
r_static
r_int
id|pcmcia_probe
c_func
(paren
r_struct
id|sa1111_dev
op_star
id|dev
)paren
(brace
r_char
op_star
id|base
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|dev-&gt;res.start
comma
l_int|512
comma
id|SA1111_DRIVER_NAME
c_func
(paren
id|dev
)paren
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|base
op_assign
id|dev-&gt;mapbase
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise the suspend state.&n;&t; */
id|sa1111_writel
c_func
(paren
id|PCSSR_S0_SLEEP
op_or
id|PCSSR_S1_SLEEP
comma
id|base
op_plus
id|SA1111_PCSSR
)paren
suffix:semicolon
id|sa1111_writel
c_func
(paren
id|PCCR_S0_FLT
op_or
id|PCCR_S1_FLT
comma
id|base
op_plus
id|SA1111_PCCR
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SA1100_ADSBITSY
id|pcmcia_adsbitsy_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_BADGE4
id|pcmcia_badge4_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_GRAPHICSMASTER
id|pcmcia_graphicsmaster_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_JORNADA720
id|pcmcia_jornada720_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ASSABET_NEPONSET
id|pcmcia_neponset_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_PFS168
id|pcmcia_pfs_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_PT_SYSTEM3
id|pcmcia_system3_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SA1100_XP860
id|pcmcia_xp860_init
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcmcia_remove
r_static
r_int
id|__devexit
id|pcmcia_remove
c_func
(paren
r_struct
id|sa1111_dev
op_star
id|dev
)paren
(brace
id|sa11xx_drv_pcmcia_remove
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|dev-&gt;res.start
comma
l_int|512
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcmcia_suspend
r_static
r_int
id|pcmcia_suspend
c_func
(paren
r_struct
id|sa1111_dev
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
r_return
id|pcmcia_socket_dev_suspend
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|state
comma
id|SUSPEND_SAVE_STATE
)paren
suffix:semicolon
)brace
DECL|function|pcmcia_resume
r_static
r_int
id|pcmcia_resume
c_func
(paren
r_struct
id|sa1111_dev
op_star
id|dev
)paren
(brace
r_return
id|pcmcia_socket_dev_resume
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|RESUME_RESTORE_STATE
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_driver
r_static
r_struct
id|sa1111_driver
id|pcmcia_driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sa1111-pcmcia&quot;
comma
)brace
comma
dot
id|devid
op_assign
id|SA1111_DEVID_PCMCIA
comma
dot
id|probe
op_assign
id|pcmcia_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|pcmcia_remove
)paren
comma
dot
id|suspend
op_assign
id|pcmcia_suspend
comma
dot
id|resume
op_assign
id|pcmcia_resume
comma
)brace
suffix:semicolon
DECL|function|sa1111_drv_pcmcia_init
r_static
r_int
id|__init
id|sa1111_drv_pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_return
id|sa1111_driver_register
c_func
(paren
op_amp
id|pcmcia_driver
)paren
suffix:semicolon
)brace
DECL|function|sa1111_drv_pcmcia_exit
r_static
r_void
id|__exit
id|sa1111_drv_pcmcia_exit
c_func
(paren
r_void
)paren
(brace
id|sa1111_driver_unregister
c_func
(paren
op_amp
id|pcmcia_driver
)paren
suffix:semicolon
)brace
DECL|variable|sa1111_drv_pcmcia_init
id|module_init
c_func
(paren
id|sa1111_drv_pcmcia_init
)paren
suffix:semicolon
DECL|variable|sa1111_drv_pcmcia_exit
id|module_exit
c_func
(paren
id|sa1111_drv_pcmcia_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SA1111 PCMCIA card socket driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
