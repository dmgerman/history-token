multiline_comment|/*&n; * Sharp SL-C7xx Series PCMCIA routines&n; *&n; * Copyright (c) 2004-2005 Richard Purdie&n; *&n; * Based on Sharp&squot;s 2.4 kernel patches and pxa2xx_mainstone.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware/scoop.h&gt;
macro_line|#include &lt;asm/arch/corgi.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#include &quot;soc_common.h&quot;
DECL|macro|NO_KEEP_VS
mdefine_line|#define&t;NO_KEEP_VS 0x0001
DECL|variable|keep_vs
r_static
r_int
r_char
id|keep_vs
suffix:semicolon
DECL|variable|keep_rd
r_static
r_int
r_char
id|keep_rd
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
l_int|0
comma
id|CORGI_IRQ_GPIO_CF_CD
comma
l_string|&quot;PCMCIA0 CD&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|sharpsl_pcmcia_init_reset
r_static
r_void
id|sharpsl_pcmcia_init_reset
c_func
(paren
r_void
)paren
(brace
id|reset_scoop
c_func
(paren
op_amp
id|corgiscoop_device.dev
)paren
suffix:semicolon
id|keep_vs
op_assign
id|NO_KEEP_VS
suffix:semicolon
id|keep_rd
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|sharpsl_pcmcia_hw_init
r_static
r_int
id|sharpsl_pcmcia_hw_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Setup default state of GPIO outputs&n;&t; * before we enable them as outputs.&n;&t; */
id|GPSR
c_func
(paren
id|GPIO48_nPOE
)paren
op_assign
id|GPIO_bit
c_func
(paren
id|GPIO48_nPOE
)paren
op_or
id|GPIO_bit
c_func
(paren
id|GPIO49_nPWE
)paren
op_or
id|GPIO_bit
c_func
(paren
id|GPIO50_nPIOR
)paren
op_or
id|GPIO_bit
c_func
(paren
id|GPIO51_nPIOW
)paren
op_or
id|GPIO_bit
c_func
(paren
id|GPIO52_nPCE_1
)paren
op_or
id|GPIO_bit
c_func
(paren
id|GPIO53_nPCE_2
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO48_nPOE_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO49_nPWE_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO50_nPIOR_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO51_nPIOW_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO52_nPCE_1_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO53_nPCE_2_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO54_pSKTSEL_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO55_nPREG_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO56_nPWAIT_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO57_nIOIS16_MD
)paren
suffix:semicolon
multiline_comment|/* Register interrupts */
id|ret
op_assign
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
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Request for Compact Flash IRQ failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Enable interrupt */
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_IMR
comma
l_int|0x00C0
)paren
suffix:semicolon
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_MCR
comma
l_int|0x0101
)paren
suffix:semicolon
id|keep_vs
op_assign
id|NO_KEEP_VS
suffix:semicolon
id|skt-&gt;irq
op_assign
id|CORGI_IRQ_GPIO_CF_IRQ
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sharpsl_pcmcia_hw_shutdown
r_static
r_void
id|sharpsl_pcmcia_hw_shutdown
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
multiline_comment|/* CF_BUS_OFF */
id|sharpsl_pcmcia_init_reset
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sharpsl_pcmcia_socket_state
r_static
r_void
id|sharpsl_pcmcia_socket_state
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
id|cpr
comma
id|csr
suffix:semicolon
id|cpr
op_assign
id|read_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CPR
)paren
suffix:semicolon
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_IRM
comma
l_int|0x00FF
)paren
suffix:semicolon
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_ISR
comma
l_int|0x0000
)paren
suffix:semicolon
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_IRM
comma
l_int|0x0000
)paren
suffix:semicolon
id|csr
op_assign
id|read_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr
op_amp
l_int|0x0004
)paren
(brace
multiline_comment|/* card eject */
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CDR
comma
l_int|0x0000
)paren
suffix:semicolon
id|keep_vs
op_assign
id|NO_KEEP_VS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|keep_vs
op_amp
id|NO_KEEP_VS
)paren
)paren
(brace
multiline_comment|/* keep vs1,vs2 */
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CDR
comma
l_int|0x0000
)paren
suffix:semicolon
id|csr
op_or_assign
id|keep_vs
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpr
op_amp
l_int|0x0003
)paren
(brace
multiline_comment|/* power on */
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CDR
comma
l_int|0x0000
)paren
suffix:semicolon
id|keep_vs
op_assign
(paren
id|csr
op_amp
l_int|0x00C0
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* card detect */
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CDR
comma
l_int|0x0002
)paren
suffix:semicolon
)brace
id|state-&gt;detect
op_assign
(paren
id|csr
op_amp
l_int|0x0004
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;ready
op_assign
(paren
id|csr
op_amp
l_int|0x0002
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
id|csr
op_amp
l_int|0x0010
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
id|csr
op_amp
l_int|0x0020
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
(paren
id|csr
op_amp
l_int|0x0008
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
(paren
id|csr
op_amp
l_int|0x0040
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
(paren
id|csr
op_amp
l_int|0x0080
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cpr
op_amp
l_int|0x0080
)paren
op_logical_and
(paren
(paren
id|cpr
op_amp
l_int|0x8040
)paren
op_ne
l_int|0x8040
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sharpsl_pcmcia_socket_state(): CPR=%04X, Low voltage!&bslash;n&quot;
comma
id|cpr
)paren
suffix:semicolon
)brace
)brace
DECL|function|sharpsl_pcmcia_configure_socket
r_static
r_int
id|sharpsl_pcmcia_configure_socket
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
r_int
r_int
id|cpr
comma
id|ncpr
comma
id|ccr
comma
id|nccr
comma
id|mcr
comma
id|nmcr
comma
id|imr
comma
id|nimr
suffix:semicolon
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
r_case
l_int|33
suffix:colon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sharpsl_pcmcia_configure_socket(): bad Vcc %u&bslash;n&quot;
comma
id|state-&gt;Vcc
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
(paren
id|state-&gt;Vpp
op_ne
id|state-&gt;Vcc
)paren
op_logical_and
(paren
id|state-&gt;Vpp
op_ne
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CF slot cannot support Vpp %u&bslash;n&quot;
comma
id|state-&gt;Vpp
)paren
suffix:semicolon
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
id|nmcr
op_assign
(paren
id|mcr
op_assign
id|read_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_MCR
)paren
)paren
op_amp
op_complement
l_int|0x0010
suffix:semicolon
id|ncpr
op_assign
(paren
id|cpr
op_assign
id|read_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CPR
)paren
)paren
op_amp
op_complement
l_int|0x0083
suffix:semicolon
id|nccr
op_assign
(paren
id|ccr
op_assign
id|read_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CCR
)paren
)paren
op_amp
op_complement
l_int|0x0080
suffix:semicolon
id|nimr
op_assign
(paren
id|imr
op_assign
id|read_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_IMR
)paren
)paren
op_amp
op_complement
l_int|0x003E
suffix:semicolon
id|ncpr
op_or_assign
(paren
id|state-&gt;Vcc
op_eq
l_int|33
)paren
ques
c_cond
l_int|0x0001
suffix:colon
(paren
id|state-&gt;Vcc
op_eq
l_int|50
)paren
ques
c_cond
l_int|0x0002
suffix:colon
l_int|0
suffix:semicolon
id|nmcr
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_IOCARD
)paren
ques
c_cond
l_int|0x0010
suffix:colon
l_int|0
suffix:semicolon
id|ncpr
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_OUTPUT_ENA
)paren
ques
c_cond
l_int|0x0080
suffix:colon
l_int|0
suffix:semicolon
id|nccr
op_or_assign
(paren
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
ques
c_cond
l_int|0x0080
suffix:colon
l_int|0
suffix:semicolon
id|nimr
op_or_assign
(paren
(paren
id|skt-&gt;status
op_amp
id|SS_DETECT
)paren
ques
c_cond
l_int|0x0004
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|skt-&gt;status
op_amp
id|SS_READY
)paren
ques
c_cond
l_int|0x0002
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|skt-&gt;status
op_amp
id|SS_BATDEAD
)paren
ques
c_cond
l_int|0x0010
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|skt-&gt;status
op_amp
id|SS_BATWARN
)paren
ques
c_cond
l_int|0x0020
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|skt-&gt;status
op_amp
id|SS_STSCHG
)paren
ques
c_cond
l_int|0x0010
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|skt-&gt;status
op_amp
id|SS_WRPROT
)paren
ques
c_cond
l_int|0x0008
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ncpr
op_amp
l_int|0x0003
)paren
)paren
(brace
id|keep_rd
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|keep_rd
)paren
(brace
r_if
c_cond
(paren
id|nccr
op_amp
l_int|0x0080
)paren
id|keep_rd
op_assign
l_int|1
suffix:semicolon
r_else
id|nccr
op_or_assign
l_int|0x0080
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mcr
op_ne
id|nmcr
)paren
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_MCR
comma
id|nmcr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpr
op_ne
id|ncpr
)paren
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CPR
comma
id|ncpr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccr
op_ne
id|nccr
)paren
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_CCR
comma
id|nccr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|imr
op_ne
id|nimr
)paren
id|write_scoop_reg
c_func
(paren
op_amp
id|corgiscoop_device.dev
comma
id|SCOOP_IMR
comma
id|nimr
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
DECL|function|sharpsl_pcmcia_socket_init
r_static
r_void
id|sharpsl_pcmcia_socket_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
)brace
DECL|function|sharpsl_pcmcia_socket_suspend
r_static
r_void
id|sharpsl_pcmcia_socket_suspend
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
)brace
DECL|variable|sharpsl_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|sharpsl_pcmcia_ops
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
id|sharpsl_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|sharpsl_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|sharpsl_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|sharpsl_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|sharpsl_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|sharpsl_pcmcia_socket_suspend
comma
dot
id|first
op_assign
l_int|0
comma
dot
id|nr
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|sharpsl_pcmcia_device
r_static
r_struct
id|platform_device
op_star
id|sharpsl_pcmcia_device
suffix:semicolon
DECL|function|sharpsl_pcmcia_init
r_static
r_int
id|__init
id|sharpsl_pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|sharpsl_pcmcia_device
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sharpsl_pcmcia_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sharpsl_pcmcia_device
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|sharpsl_pcmcia_device
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sharpsl_pcmcia_device
)paren
)paren
suffix:semicolon
id|sharpsl_pcmcia_device-&gt;name
op_assign
l_string|&quot;pxa2xx-pcmcia&quot;
suffix:semicolon
id|sharpsl_pcmcia_device-&gt;dev.platform_data
op_assign
op_amp
id|sharpsl_pcmcia_ops
suffix:semicolon
id|ret
op_assign
id|platform_device_register
c_func
(paren
id|sharpsl_pcmcia_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|kfree
c_func
(paren
id|sharpsl_pcmcia_device
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sharpsl_pcmcia_exit
r_static
r_void
id|__exit
id|sharpsl_pcmcia_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * This call is supposed to free our sharpsl_pcmcia_device.&n;&t; * Unfortunately platform_device don&squot;t have a free method, and&n;&t; * we can&squot;t assume it&squot;s free of any reference at this point so we&n;&t; * can&squot;t free it either.&n;&t; */
id|platform_device_unregister
c_func
(paren
id|sharpsl_pcmcia_device
)paren
suffix:semicolon
)brace
DECL|variable|sharpsl_pcmcia_init
id|module_init
c_func
(paren
id|sharpsl_pcmcia_init
)paren
suffix:semicolon
DECL|variable|sharpsl_pcmcia_exit
id|module_exit
c_func
(paren
id|sharpsl_pcmcia_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Sharp SL Series PCMCIA Support&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
