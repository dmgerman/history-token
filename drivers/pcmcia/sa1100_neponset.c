multiline_comment|/*&n; * linux/drivers/pcmcia/sa1100_neponset.c&n; *&n; * Neponset PCMCIA specific routines&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/arch/assabet.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
macro_line|#include &quot;sa1111_generic.h&quot;
DECL|function|neponset_pcmcia_init
r_static
r_int
id|neponset_pcmcia_init
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
multiline_comment|/* MAX1600 to standby mode: */
id|PA_DWR
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
id|NCR_0
op_and_assign
op_complement
(paren
id|NCR_A0VPP
op_or
id|NCR_A1VPP
)paren
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
DECL|function|neponset_pcmcia_configure_socket
id|neponset_pcmcia_configure_socket
c_func
(paren
r_const
r_struct
id|pcmcia_configure
op_star
id|conf
)paren
(brace
r_int
r_int
id|ncr_mask
comma
id|pa_dwr_mask
suffix:semicolon
r_int
r_int
id|ncr_set
comma
id|pa_dwr_set
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Neponset uses the Maxim MAX1600, with the following connections:&n;&n;&t; *   MAX1600      Neponset&n;&t; *&n;&t; *    A0VCC        SA-1111 GPIO A&lt;1&gt;&n;&t; *    A1VCC        SA-1111 GPIO A&lt;0&gt;&n;&t; *    A0VPP        CPLD NCR A0VPP&n;&t; *    A1VPP        CPLD NCR A1VPP&n;&t; *    B0VCC        SA-1111 GPIO A&lt;2&gt;&n;&t; *    B1VCC        SA-1111 GPIO A&lt;3&gt;&n;&t; *    B0VPP        ground (slot B is CF)&n;&t; *    B1VPP        ground (slot B is CF)&n;&t; *&n;&t; *     VX          VCC (5V)&n;&t; *     VY          VCC3_3 (3.3V)&n;&t; *     12INA       12V&n;&t; *     12INB       ground (slot B is CF)&n;&t; *&n;&t; * The MAX1600 CODE pin is tied to ground, placing the device in &n;&t; * &quot;Standard Intel code&quot; mode. Refer to the Maxim data sheet for&n;&t; * the corresponding truth table.&n;&t; */
r_switch
c_cond
(paren
id|conf-&gt;sock
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
id|ncr_mask
op_assign
id|NCR_A0VPP
op_or
id|NCR_A1VPP
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
r_switch
c_cond
(paren
id|conf-&gt;vpp
)paren
(brace
r_case
l_int|0
suffix:colon
id|ncr_set
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|120
suffix:colon
id|ncr_set
op_assign
id|NCR_A1VPP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|conf-&gt;vpp
op_eq
id|conf-&gt;vcc
)paren
id|ncr_set
op_assign
id|NCR_A0VPP
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): unrecognized VPP %u&bslash;n&quot;
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
id|ncr_mask
op_assign
l_int|0
suffix:semicolon
id|ncr_set
op_assign
l_int|0
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
r_break
suffix:semicolon
r_default
suffix:colon
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
id|NCR_0
op_assign
(paren
id|NCR_0
op_amp
op_complement
id|ncr_mask
)paren
op_or
id|ncr_set
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
l_int|0
suffix:semicolon
)brace
DECL|variable|neponset_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|neponset_pcmcia_ops
op_assign
(brace
id|init
suffix:colon
id|neponset_pcmcia_init
comma
id|shutdown
suffix:colon
id|sa1111_pcmcia_shutdown
comma
id|socket_state
suffix:colon
id|sa1111_pcmcia_socket_state
comma
id|get_irq_info
suffix:colon
id|sa1111_pcmcia_get_irq_info
comma
id|configure_socket
suffix:colon
id|neponset_pcmcia_configure_socket
comma
id|socket_init
suffix:colon
id|sa1111_pcmcia_socket_init
comma
id|socket_suspend
suffix:colon
id|sa1111_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_neponset_init
r_int
id|__init
id|pcmcia_neponset_init
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
id|machine_is_assabet
c_func
(paren
)paren
op_logical_and
id|sa1111
)paren
id|ret
op_assign
id|sa1100_register_pcmcia
c_func
(paren
op_amp
id|neponset_pcmcia_ops
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcmcia_neponset_exit
r_void
id|__exit
id|pcmcia_neponset_exit
c_func
(paren
r_void
)paren
(brace
id|sa1100_unregister_pcmcia
c_func
(paren
op_amp
id|neponset_pcmcia_ops
)paren
suffix:semicolon
)brace
eof
