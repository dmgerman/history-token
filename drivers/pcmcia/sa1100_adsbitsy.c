multiline_comment|/*&n; * drivers/pcmcia/sa1100_adsbitsy.c&n; *&n; * PCMCIA implementation routines for ADS Bitsy&n; *&n; * 9/18/01 Woojung&n; *         Fixed wrong PCMCIA voltage setting&n; *&n; * 7/5/01 Woojung Huh &lt;whuh@applieddata.net&gt;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
macro_line|#include &quot;sa1111_generic.h&quot;
DECL|function|adsbitsy_pcmcia_init
r_static
r_int
id|adsbitsy_pcmcia_init
c_func
(paren
r_struct
id|pcmcia_init
op_star
id|init
)paren
(brace
multiline_comment|/* Set GPIO_A&lt;3:0&gt; to be outputs for PCMCIA/CF power controller: */
id|PA_DDR
op_and_assign
op_complement
(paren
id|GPIO_GPIO0
op_or
id|GPIO_GPIO1
op_or
id|GPIO_GPIO2
op_or
id|GPIO_GPIO3
)paren
suffix:semicolon
multiline_comment|/* Disable Power 3.3V/5V for PCMCIA/CF */
id|PA_DWR
op_or_assign
id|GPIO_GPIO0
op_or
id|GPIO_GPIO1
op_or
id|GPIO_GPIO2
op_or
id|GPIO_GPIO3
suffix:semicolon
multiline_comment|/* Why? */
id|MECR
op_assign
l_int|0x09430943
suffix:semicolon
r_return
id|sa1111_pcmcia_init
c_func
(paren
id|init
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|adsbitsy_pcmcia_configure_socket
id|adsbitsy_pcmcia_configure_socket
c_func
(paren
r_int
id|sock
comma
r_const
r_struct
id|pcmcia_configure
op_star
id|conf
)paren
(brace
r_int
r_int
id|pa_dwr_mask
comma
id|pa_dwr_set
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|sock
)paren
(brace
r_case
l_int|0
suffix:colon
id|pa_dwr_mask
op_assign
id|GPIO_GPIO0
op_or
id|GPIO_GPIO1
suffix:semicolon
r_switch
c_cond
(paren
id|conf-&gt;vcc
)paren
(brace
r_default
suffix:colon
r_case
l_int|0
suffix:colon
id|pa_dwr_set
op_assign
id|GPIO_GPIO0
op_or
id|GPIO_GPIO1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|pa_dwr_set
op_assign
id|GPIO_GPIO1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|pa_dwr_set
op_assign
id|GPIO_GPIO0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|pa_dwr_mask
op_assign
id|GPIO_GPIO2
op_or
id|GPIO_GPIO3
suffix:semicolon
r_switch
c_cond
(paren
id|conf-&gt;vcc
)paren
(brace
r_default
suffix:colon
r_case
l_int|0
suffix:colon
id|pa_dwr_set
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
id|pa_dwr_set
op_assign
id|GPIO_GPIO2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|pa_dwr_set
op_assign
id|GPIO_GPIO3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|conf-&gt;vpp
op_ne
id|conf-&gt;vcc
op_logical_and
id|conf-&gt;vpp
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): CF slot cannot support VPP %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|conf-&gt;vpp
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|sa1111_pcmcia_configure_socket
c_func
(paren
id|sock
comma
id|conf
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
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|PA_DWR
op_assign
(paren
id|PA_DWR
op_amp
op_complement
id|pa_dwr_mask
)paren
op_or
id|pa_dwr_set
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|adsbitsy_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|adsbitsy_pcmcia_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|init
op_assign
id|adsbitsy_pcmcia_init
comma
dot
id|shutdown
op_assign
id|sa1111_pcmcia_shutdown
comma
dot
id|socket_state
op_assign
id|sa1111_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|adsbitsy_pcmcia_configure_socket
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
)brace
suffix:semicolon
DECL|function|pcmcia_adsbitsy_init
r_int
id|__init
id|pcmcia_adsbitsy_init
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
id|machine_is_adsbitsy
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
id|adsbitsy_pcmcia_ops
comma
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_adsbitsy_exit
r_void
id|__exit
id|pcmcia_adsbitsy_exit
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|adsbitsy_pcmcia_ops
comma
id|dev
)paren
suffix:semicolon
)brace
eof
