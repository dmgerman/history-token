multiline_comment|/* &n; * drivers/pcmcia/sa1100_stork.c&n; *&n;    Copyright 2001 (C) Ken Gordon&n;&n;    This is derived from pre-existing drivers/pcmcia/sa1100_?????.c&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n; * &n; * PCMCIA implementation routines for stork&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
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
id|IRQ_GPIO_STORK_PCMCIA_A_CARD_DETECT
comma
l_string|&quot;PCMCIA_CD0&quot;
)brace
comma
(brace
l_int|1
comma
id|IRQ_GPIO_STORK_PCMCIA_B_CARD_DETECT
comma
l_string|&quot;PCMCIA_CD1&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|stork_pcmcia_hw_init
r_static
r_int
id|stork_pcmcia_hw_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;in stork_pcmcia_init&bslash;n&quot;
)paren
suffix:semicolon
id|skt-&gt;irq
op_assign
id|skt-&gt;nr
ques
c_cond
id|IRQ_GPIO_STORK_PCMCIA_B_RDY
suffix:colon
id|IRQ_GPIO_STORK_PCMCIA_A_RDY
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
DECL|function|stork_pcmcia_hw_shutdown
r_static
r_void
id|stork_pcmcia_hw_shutdown
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* disable IRQs */
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
id|storkClearLatchA
c_func
(paren
id|STORK_PCMCIA_PULL_UPS_POWER_ON
)paren
suffix:semicolon
id|storkClearLatchA
c_func
(paren
id|STORK_PCMCIA_A_POWER_ON
)paren
suffix:semicolon
id|storkClearLatchA
c_func
(paren
id|STORK_PCMCIA_B_POWER_ON
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|stork_pcmcia_socket_state
id|stork_pcmcia_socket_state
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
r_if
c_cond
(paren
id|debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s GPLR=%x IRQ[1:0]=%x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|levels
comma
(paren
id|levels
op_amp
(paren
id|GPIO_STORK_PCMCIA_A_RDY
op_or
id|GPIO_STORK_PCMCIA_B_RDY
)paren
)paren
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
(paren
(paren
id|levels
op_amp
id|GPIO_STORK_PCMCIA_A_CARD_DETECT
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
id|GPIO_STORK_PCMCIA_A_RDY
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
id|state-&gt;bvd2
op_assign
l_int|1
suffix:semicolon
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
l_int|1
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
(paren
(paren
id|levels
op_amp
id|GPIO_STORK_PCMCIA_B_CARD_DETECT
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
id|GPIO_STORK_PCMCIA_B_RDY
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
id|state-&gt;bvd2
op_assign
l_int|1
suffix:semicolon
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
l_int|1
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
DECL|function|stork_pcmcia_configure_socket
id|stork_pcmcia_configure_socket
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
id|DETECT
comma
id|RDY
comma
id|POWER
comma
id|RESET
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: socket=%d vcc=%d vpp=%d reset=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|skt-&gt;nr
comma
id|state-&gt;Vcc
comma
id|state-&gt;Vpp
comma
id|state-&gt;flags
op_amp
id|SS_RESET
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skt-&gt;nr
op_eq
l_int|0
)paren
(brace
id|DETECT
op_assign
id|GPIO_STORK_PCMCIA_A_CARD_DETECT
suffix:semicolon
id|RDY
op_assign
id|GPIO_STORK_PCMCIA_A_RDY
suffix:semicolon
id|POWER
op_assign
id|STORK_PCMCIA_A_POWER_ON
suffix:semicolon
id|RESET
op_assign
id|STORK_PCMCIA_A_RESET
suffix:semicolon
)brace
r_else
(brace
id|DETECT
op_assign
id|GPIO_STORK_PCMCIA_B_CARD_DETECT
suffix:semicolon
id|RDY
op_assign
id|GPIO_STORK_PCMCIA_B_RDY
suffix:semicolon
id|POWER
op_assign
id|STORK_PCMCIA_B_POWER_ON
suffix:semicolon
id|RESET
op_assign
id|STORK_PCMCIA_B_RESET
suffix:semicolon
)brace
multiline_comment|/*&n;        if (storkTestGPIO(DETECT)) {&n;           printk(&quot;no card detected - but resetting anyway&bslash;r&bslash;n&quot;);&n;        }&n;*/
r_switch
c_cond
(paren
id|state-&gt;Vcc
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&t;&t;storkClearLatchA(STORK_PCMCIA_PULL_UPS_POWER_ON); */
id|storkClearLatchA
c_func
(paren
id|POWER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
r_case
l_int|33
suffix:colon
id|storkSetLatchA
c_func
(paren
id|STORK_PCMCIA_PULL_UPS_POWER_ON
)paren
suffix:semicolon
id|storkSetLatchA
c_func
(paren
id|POWER
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
id|state-&gt;flags
op_amp
id|SS_RESET
)paren
id|storkSetLatchB
c_func
(paren
id|RESET
)paren
suffix:semicolon
r_else
id|storkClearLatchB
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* silently ignore vpp and speaker enables. */
id|printk
c_func
(paren
l_string|&quot;%s: finished&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|stork_pcmcia_socket_init
r_static
r_void
id|stork_pcmcia_socket_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
id|storkSetLatchA
c_func
(paren
id|STORK_PCMCIA_PULL_UPS_POWER_ON
)paren
suffix:semicolon
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
DECL|function|stork_pcmcia_socket_suspend
r_static
r_void
id|stork_pcmcia_socket_suspend
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
multiline_comment|/*&n;&t; * Hack!&n;&t; */
r_if
c_cond
(paren
id|skt-&gt;nr
op_eq
l_int|1
)paren
id|storkClearLatchA
c_func
(paren
id|STORK_PCMCIA_PULL_UPS_POWER_ON
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|stork_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|stork_pcmcia_ops
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
id|stork_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|stork_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|stork_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|stork_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|stork_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|stork_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_stork_init
r_int
id|__init
id|pcmcia_stork_init
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
id|machine_is_stork
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
id|stork_pcmcia_ops
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
