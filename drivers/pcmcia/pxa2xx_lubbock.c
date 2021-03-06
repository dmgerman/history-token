multiline_comment|/*&n; * linux/drivers/pcmcia/pxa2xx_lubbock.c&n; *&n; * Author:&t;George Davis&n; * Created:&t;Jan 10, 2002&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Originally based upon linux/drivers/pcmcia/sa1100_neponset.c&n; *&n; * Lubbock PCMCIA specific routines.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#include &lt;asm/arch/lubbock.h&gt;
macro_line|#include &quot;sa1111_generic.h&quot;
r_static
r_int
DECL|function|lubbock_pcmcia_hw_init
id|lubbock_pcmcia_hw_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
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
r_return
id|sa1111_pcmcia_hw_init
c_func
(paren
id|skt
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|lubbock_pcmcia_configure_socket
id|lubbock_pcmcia_configure_socket
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
id|pa_dwr_mask
comma
id|pa_dwr_set
comma
id|misc_mask
comma
id|misc_set
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|pa_dwr_mask
op_assign
id|pa_dwr_set
op_assign
id|misc_mask
op_assign
id|misc_set
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Lubbock uses the Maxim MAX1602, with the following connections:&n;&t; *&n;&t; * Socket 0 (PCMCIA):&n;&t; *&t;MAX1602&t;Lubbock&t;&t;Register&n;&t; *&t;Pin&t;Signal&n;&t; *&t;-----&t;-------&t;&t;----------------------&n;&t; *&t;A0VPP&t;S0_PWR0&t;&t;SA-1111 GPIO A&lt;0&gt;&n;&t; *&t;A1VPP&t;S0_PWR1&t;&t;SA-1111 GPIO A&lt;1&gt;&n;&t; *&t;A0VCC&t;S0_PWR2&t;&t;SA-1111 GPIO A&lt;2&gt;&n;&t; *&t;A1VCC&t;S0_PWR3&t;&t;SA-1111 GPIO A&lt;3&gt;&n;&t; *&t;VX&t;VCC&n;&t; *&t;VY&t;+3.3V&n;&t; *&t;12IN&t;+12V&n;&t; *&t;CODE&t;+3.3V&t;&t;Cirrus  Code, CODE = High (VY)&n;&t; *&n;&t; * Socket 1 (CF):&n;&t; *&t;MAX1602&t;Lubbock&t;&t;Register&n;&t; *&t;Pin&t;Signal&n;&t; *&t;-----&t;-------&t;&t;----------------------&n;&t; *&t;A0VPP&t;GND&t;&t;VPP is not connected&n;&t; *&t;A1VPP&t;GND&t;&t;VPP is not connected&n;&t; *&t;A0VCC&t;S1_PWR0&t;&t;MISC_WR&lt;14&gt;&n;&t; *&t;A1VCC&t;S1_PWR1&t;&t;MISC_WR&lt;15&gt;&n;&t; *&t;VX&t;VCC&n;&t; *&t;VY&t;+3.3V&n;&t; *&t;12IN&t;GND&t;&t;VPP is not connected&n;&t; *&t;CODE&t;+3.3V&t;&t;Cirrus  Code, CODE = High (VY)&n;&t; *&n;&t; */
id|again
suffix:colon
r_switch
c_cond
(paren
id|skt-&gt;nr
)paren
(brace
r_case
l_int|0
suffix:colon
id|pa_dwr_mask
op_assign
id|GPIO_A0
op_or
id|GPIO_A1
op_or
id|GPIO_A2
op_or
id|GPIO_A3
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
multiline_comment|/* Hi-Z */
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
multiline_comment|/* VY */
id|pa_dwr_set
op_or_assign
id|GPIO_A3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
multiline_comment|/* VX */
id|pa_dwr_set
op_or_assign
id|GPIO_A2
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
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|state-&gt;Vpp
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Hi-Z */
r_break
suffix:semicolon
r_case
l_int|120
suffix:colon
multiline_comment|/* 12IN */
id|pa_dwr_set
op_or_assign
id|GPIO_A1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* VCC */
r_if
c_cond
(paren
id|state-&gt;Vpp
op_eq
id|state-&gt;Vcc
)paren
id|pa_dwr_set
op_or_assign
id|GPIO_A0
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): unrecognized Vpp %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|state-&gt;Vpp
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|misc_mask
op_assign
(paren
l_int|1
op_lshift
l_int|15
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
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
multiline_comment|/* Hi-Z */
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
multiline_comment|/* VY */
id|misc_set
op_or_assign
l_int|1
op_lshift
l_int|15
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
multiline_comment|/* VX */
id|misc_set
op_or_assign
l_int|1
op_lshift
l_int|14
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
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;Vpp
op_ne
id|state-&gt;Vcc
op_logical_and
id|state-&gt;Vpp
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): CF slot cannot support Vpp %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|state-&gt;Vpp
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|ret
op_assign
id|sa1111_pcmcia_configure_socket
c_func
(paren
id|skt
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|lubbock_set_misc_wr
c_func
(paren
id|misc_mask
comma
id|misc_set
)paren
suffix:semicolon
id|sa1111_set_io
c_func
(paren
id|SA1111_DEV
c_func
(paren
id|skt-&gt;dev
)paren
comma
id|pa_dwr_mask
comma
id|pa_dwr_set
)paren
suffix:semicolon
)brace
macro_line|#if 1
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_and
id|state-&gt;Vcc
op_eq
l_int|33
)paren
(brace
r_struct
id|pcmcia_state
id|new_state
suffix:semicolon
multiline_comment|/*&n;&t;&t; * HACK ALERT:&n;&t;&t; * We can&squot;t sense the voltage properly on Lubbock before&n;&t;&t; * actually applying some power to the socket (catch 22).&n;&t;&t; * Resense the socket Voltage Sense pins after applying&n;&t;&t; * socket power.&n;&t;&t; *&n;&t;&t; * Note: It takes about 2.5ms for the MAX1602 VCC output&n;&t;&t; * to rise.&n;&t;&t; */
id|mdelay
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|sa1111_pcmcia_socket_state
c_func
(paren
id|skt
comma
op_amp
id|new_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_state.vs_3v
op_logical_and
op_logical_neg
id|new_state.vs_Xv
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Switch to 5V,  Configure socket with 5V voltage&n;&t;&t;&t; */
id|lubbock_set_misc_wr
c_func
(paren
id|misc_mask
comma
l_int|0
)paren
suffix:semicolon
id|sa1111_set_io
c_func
(paren
id|SA1111_DEV
c_func
(paren
id|skt-&gt;dev
)paren
comma
id|pa_dwr_mask
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * It takes about 100ms to turn off Vcc.&n;&t;&t;&t; */
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We need to hack around the const qualifier as&n;&t;&t;&t; * well to keep this ugly workaround localized and&n;&t;&t;&t; * not force it to the rest of the code. Barf bags&n;&t;&t;&t; * avaliable in the seat pocket in front of you!&n;&t;&t;&t; */
(paren
(paren
id|socket_state_t
op_star
)paren
id|state
)paren
op_member_access_from_pointer
id|Vcc
op_assign
l_int|50
suffix:semicolon
(paren
(paren
id|socket_state_t
op_star
)paren
id|state
)paren
op_member_access_from_pointer
id|Vpp
op_assign
l_int|50
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|lubbock_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|lubbock_pcmcia_ops
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
id|lubbock_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|sa1111_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|sa1111_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|lubbock_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|sa1111_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|sa1111_pcmcia_socket_suspend
comma
dot
id|first
op_assign
l_int|0
comma
dot
id|nr
op_assign
l_int|2
comma
)brace
suffix:semicolon
macro_line|#include &quot;pxa2xx_base.h&quot;
DECL|function|pcmcia_lubbock_init
r_int
id|__init
id|pcmcia_lubbock_init
c_func
(paren
r_struct
id|sa1111_dev
op_star
id|sadev
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
id|machine_is_lubbock
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Set GPIO_A&lt;3:0&gt; to be outputs for the MAX1600,&n;&t;&t; * and switch to standby mode.&n;&t;&t; */
id|sa1111_set_io_dir
c_func
(paren
id|sadev
comma
id|GPIO_A0
op_or
id|GPIO_A1
op_or
id|GPIO_A2
op_or
id|GPIO_A3
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|sa1111_set_io
c_func
(paren
id|sadev
comma
id|GPIO_A0
op_or
id|GPIO_A1
op_or
id|GPIO_A2
op_or
id|GPIO_A3
comma
l_int|0
)paren
suffix:semicolon
id|sa1111_set_sleep_io
c_func
(paren
id|sadev
comma
id|GPIO_A0
op_or
id|GPIO_A1
op_or
id|GPIO_A2
op_or
id|GPIO_A3
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set CF Socket 1 power to standby mode. */
id|lubbock_set_misc_wr
c_func
(paren
(paren
l_int|1
op_lshift
l_int|15
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
comma
l_int|0
)paren
suffix:semicolon
id|sadev-&gt;dev.platform_data
op_assign
op_amp
id|lubbock_pcmcia_ops
suffix:semicolon
id|ret
op_assign
id|pxa2xx_drv_pcmcia_probe
c_func
(paren
op_amp
id|sadev-&gt;dev
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
