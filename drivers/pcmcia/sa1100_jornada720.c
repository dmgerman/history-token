multiline_comment|/*&n; * drivers/pcmcia/sa1100_jornada720.c&n; *&n; * Jornada720 PCMCIA specific routines&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &quot;sa1111_generic.h&quot;
DECL|macro|SOCKET0_POWER
mdefine_line|#define SOCKET0_POWER   GPIO_GPIO0
DECL|macro|SOCKET0_3V
mdefine_line|#define SOCKET0_3V      GPIO_GPIO2
DECL|macro|SOCKET1_POWER
mdefine_line|#define SOCKET1_POWER   (GPIO_GPIO1 | GPIO_GPIO3)
macro_line|#warning *** Does SOCKET1_3V actually do anything?
DECL|macro|SOCKET1_3V
mdefine_line|#define SOCKET1_3V&t;GPIO_GPIO3
DECL|function|jornada720_pcmcia_hw_init
r_static
r_int
id|jornada720_pcmcia_hw_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
multiline_comment|/*&n;   * What is all this crap for?&n;   */
id|GRER
op_or_assign
l_int|0x00000002
suffix:semicolon
multiline_comment|/* Set GPIO_A&lt;3:1&gt; to be outputs for PCMCIA/CF power controller: */
id|PA_DDR
op_assign
l_int|0
suffix:semicolon
id|PA_DWR
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
id|PB_DDR
op_assign
l_int|0
suffix:semicolon
id|PB_DWR
op_assign
l_int|0x01
suffix:semicolon
id|PB_SDR
op_assign
l_int|0
suffix:semicolon
id|PB_SSR
op_assign
l_int|0
suffix:semicolon
id|PC_DDR
op_assign
l_int|0x88
suffix:semicolon
id|PC_DWR
op_assign
l_int|0x20
suffix:semicolon
id|PC_SDR
op_assign
l_int|0
suffix:semicolon
id|PC_SSR
op_assign
l_int|0
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
DECL|function|jornada720_pcmcia_configure_socket
id|jornada720_pcmcia_configure_socket
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
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s(): config socket %d vcc %d vpp %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|skt-&gt;nr
comma
id|state-&gt;Vcc
comma
id|state-&gt;Vpp
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
id|pa_dwr_mask
op_assign
id|SOCKET0_POWER
op_or
id|SOCKET0_3V
suffix:semicolon
r_switch
c_cond
(paren
id|state-&gt;Vcc
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
id|SOCKET0_POWER
op_or
id|SOCKET0_3V
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|pa_dwr_set
op_assign
id|SOCKET0_POWER
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
id|SOCKET1_POWER
suffix:semicolon
r_switch
c_cond
(paren
id|state-&gt;Vcc
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
id|SOCKET1_POWER
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|pa_dwr_set
op_assign
id|SOCKET1_POWER
suffix:semicolon
r_break
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
l_string|&quot;%s(): slot cannot support VPP %u&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|state-&gt;Vpp
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
DECL|variable|jornada720_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|jornada720_pcmcia_ops
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
id|jornada720_pcmcia_hw_init
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
id|jornada720_pcmcia_configure_socket
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
DECL|function|pcmcia_jornada720_init
r_int
id|__init
id|pcmcia_jornada720_init
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
id|machine_is_jornada720
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
id|jornada720_pcmcia_ops
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
