multiline_comment|/*&n; * linux/drivers/pcmcia/pxa2xx_lubbock.c&n; *&n; * Author:&t;George Davis&n; * Created:&t;Jan 10, 2002&n; * Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Originally based upon linux/drivers/pcmcia/sa1100_neponset.c&n; *&n; * Lubbock PCMCIA specific routines.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1111_generic.h&quot;
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
id|flags
comma
id|gpio
comma
id|misc_wr
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_struct
id|pcmcia_state
id|new_state
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gpio
op_assign
id|PA_DWR
suffix:semicolon
id|misc_wr
op_assign
id|LUB_MISC_WR
suffix:semicolon
multiline_comment|/* Lubbock uses the Maxim MAX1602, with the following connections:&n;   *&n;   * Socket 0 (PCMCIA):&n;   *&t;MAX1602&t;Lubbock&t;&t;Register&n;   *&t;Pin&t;Signal&n;   *&t;-----&t;-------&t;&t;----------------------&n;   *&t;A0VPP&t;S0_PWR0&t;&t;SA-1111 GPIO A&lt;0&gt;&n;   *&t;A1VPP&t;S0_PWR1&t;&t;SA-1111 GPIO A&lt;1&gt;&n;   *&t;A0VCC&t;S0_PWR2&t;&t;SA-1111 GPIO A&lt;2&gt;&n;   *&t;A1VCC&t;S0_PWR3&t;&t;SA-1111 GPIO A&lt;3&gt;&n;   *&t;VX&t;VCC&n;   *&t;VY&t;+3.3V&n;   *&t;12IN&t;+12V&n;   *&t;CODE&t;+3.3V&t;&t;Cirrus  Code, CODE = High (VY)&n;   *&n;   * Socket 1 (CF):&n;   *&t;MAX1602&t;Lubbock&t;&t;Register&n;   *&t;Pin&t;Signal&n;   *&t;-----&t;-------&t;&t;----------------------&n;   *&t;A0VPP&t;GND&t;&t;VPP is not connected&n;   *&t;A1VPP&t;GND&t;&t;VPP is not connected&n;   *&t;A0VCC&t;S1_PWR0&t;&t;MISC_WR&lt;14&gt;&n;   *&t;A1VCC&t;S1_PWR0&t;&t;MISC_WR&lt;15&gt;&n;   *&t;VX&t;VCC&n;   *&t;VY&t;+3.3V&n;   *&t;12IN&t;GND&t;&t;VPP is not connected&n;   *&t;CODE&t;+3.3V&t;&t;Cirrus  Code, CODE = High (VY)&n;   *&n;   */
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
r_switch
c_cond
(paren
id|state-&gt;Vcc
)paren
(brace
r_case
l_int|0
suffix:colon
id|gpio
op_and_assign
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|2
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|gpio
op_assign
(paren
id|gpio
op_amp
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|2
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
)paren
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|gpio
op_assign
(paren
id|gpio
op_amp
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|2
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
)paren
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|2
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
id|gpio
op_and_assign
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|0
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|120
suffix:colon
id|gpio
op_assign
(paren
id|gpio
op_amp
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|0
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|1
)paren
)paren
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* REVISIT: I&squot;m not sure about this? Is this correct?&n;         Is it always safe or do we have potential problems&n;         with bogus combinations of Vcc and Vpp settings? */
r_if
c_cond
(paren
id|state-&gt;Vpp
op_eq
id|state-&gt;Vcc
)paren
(brace
id|gpio
op_assign
(paren
id|gpio
op_amp
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|0
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|1
)paren
)paren
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|state-&gt;Vcc
)paren
(brace
r_case
l_int|0
suffix:colon
id|misc_wr
op_and_assign
op_complement
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
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|misc_wr
op_assign
(paren
id|misc_wr
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
suffix:semicolon
id|gpio
op_assign
(paren
id|gpio
op_amp
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|2
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
)paren
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|misc_wr
op_assign
(paren
id|misc_wr
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
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
op_ge
l_int|0
)paren
(brace
id|sa1111_pcmcia_configure_socket
c_func
(paren
id|skt
comma
id|state
)paren
suffix:semicolon
id|LUB_MISC_WR
op_assign
id|misc_wr
suffix:semicolon
id|PA_DWR
op_assign
id|gpio
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#if 1
multiline_comment|/*&n;     * HACK ALERT:&n;     * We can&squot;t sense the voltage properly on Lubbock before actually&n;     * applying some power to the socket (catch 22).&n;     * Resense the socket Voltage Sense pins after applying socket power.&n;     */
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
id|state-&gt;Vcc
op_eq
l_int|33
op_logical_and
op_logical_neg
id|new_state.vs_3v
op_logical_and
op_logical_neg
id|new_state.vs_Xv
)paren
(brace
multiline_comment|/* Switch to 5V,  Configure socket with 5V voltage */
id|PA_DWR
op_and_assign
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|0
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|1
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|2
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
)paren
suffix:semicolon
id|PA_DDR
op_and_assign
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|0
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|1
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|2
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|3
)paren
)paren
suffix:semicolon
multiline_comment|/* We need to hack around the const qualifier as well to keep this&n;         ugly workaround localized and not force it to the rest of the code.&n;         Barf bags avaliable in the seat pocket in front of you! */
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
macro_line|#endif
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
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
id|sa1111_pcmcia_hw_init
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
id|machine_is_lubbock
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Set GPIO_A&lt;3:0&gt; to be outputs for the MAX1600,&n;&t;&t; * and switch to standby mode.&n;&t;&t; */
id|PA_DWR
op_assign
l_int|0
suffix:semicolon
id|PA_DDR
op_assign
l_int|0
suffix:semicolon
id|PA_SDR
op_assign
l_int|0
suffix:semicolon
id|PA_SSR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set CF Socket 1 power to standby mode. */
id|LUB_MISC_WR
op_and_assign
op_complement
(paren
id|GPIO_bit
c_func
(paren
l_int|15
)paren
op_or
id|GPIO_bit
c_func
(paren
l_int|14
)paren
)paren
suffix:semicolon
id|dev-&gt;platform_data
op_assign
op_amp
id|lubbock_pcmcia_ops
suffix:semicolon
id|ret
op_assign
id|pxa2xx_drv_pcmcia_probe
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
