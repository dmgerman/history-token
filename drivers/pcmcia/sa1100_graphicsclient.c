multiline_comment|/*&n; * drivers/pcmcia/sa1100_graphicsclient.c&n; *&n; * PCMCIA implementation routines for Graphics Client Plus&n; *&n; * 9/12/01   Woojung&n; *    Turn power OFF at startup&n; * 1/31/2001 Woojung Huh&n; *    Fix for GC Plus PCMCIA Reset Problem&n; * 2/27/2001 Woojung Huh [whuh@applieddata.net]&n; *    Fix&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;sa1100_generic.h&quot;
macro_line|#error This is broken!
DECL|macro|S0_CD_IRQ
mdefine_line|#define&t;S0_CD_IRQ&t;&t;60&t;&t;&t;&t;
singleline_comment|// Socket 0 Card Detect IRQ
DECL|macro|S0_STS_IRQ
mdefine_line|#define&t;S0_STS_IRQ&t;&t;55&t;&t;&t;&t;
singleline_comment|// Socket 0 PCMCIA IRQ
DECL|variable|PCMCIA_Status
r_static
r_volatile
r_int
r_int
op_star
id|PCMCIA_Status
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADS_p2v
c_func
(paren
id|_ADS_CS_STATUS
)paren
)paren
suffix:semicolon
DECL|variable|PCMCIA_Power
r_static
r_volatile
r_int
r_int
op_star
id|PCMCIA_Power
op_assign
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ADS_p2v
c_func
(paren
id|_ADS_CS_PR
)paren
)paren
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
id|S0_CD_IRQ
comma
l_string|&quot;PCMCIA 0 CD&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|gcplus_pcmcia_init
r_static
r_int
id|gcplus_pcmcia_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
singleline_comment|// Reset PCMCIA
singleline_comment|// Reset Timing for CPLD(U2) version 8001E or later
op_star
id|PCMCIA_Power
op_and_assign
op_complement
id|ADS_CS_PR_A_RESET
suffix:semicolon
id|udelay
c_func
(paren
l_int|12
)paren
suffix:semicolon
singleline_comment|// 12 uSec
op_star
id|PCMCIA_Power
op_or_assign
id|ADS_CS_PR_A_RESET
suffix:semicolon
id|mdelay
c_func
(paren
l_int|30
)paren
suffix:semicolon
singleline_comment|// 30 mSec
singleline_comment|// Turn off 5V
op_star
id|PCMCIA_Power
op_and_assign
op_complement
l_int|0x03
suffix:semicolon
id|skt-&gt;irq
op_assign
id|S0_STS_IRQ
suffix:semicolon
multiline_comment|/* Register interrupts */
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
DECL|function|gcplus_pcmcia_hw_shutdown
r_static
r_void
id|gcplus_pcmcia_hw_shutdown
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
multiline_comment|/* disable IRQs */
id|free_irq
c_func
(paren
id|S0_CD_IRQ
comma
id|skt
)paren
suffix:semicolon
multiline_comment|/* Shutdown PCMCIA power */
id|mdelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
singleline_comment|// 2msec
op_star
id|PCMCIA_Power
op_and_assign
op_complement
l_int|0x03
suffix:semicolon
)brace
r_static
r_void
DECL|function|gcplus_pcmcia_socket_state
id|gcplus_pcmcia_socket_state
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
op_star
id|PCMCIA_Status
suffix:semicolon
id|state-&gt;detect
op_assign
(paren
id|levels
op_amp
id|ADS_CS_ST_A_CD
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
id|ADS_CS_ST_A_READY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|state-&gt;bvd1
op_assign
l_int|0
suffix:semicolon
id|state-&gt;bvd2
op_assign
l_int|0
suffix:semicolon
id|state-&gt;wrprot
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_3v
op_assign
l_int|0
suffix:semicolon
id|state-&gt;vs_Xv
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|gcplus_pcmcia_configure_socket
id|gcplus_pcmcia_configure_socket
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
id|local_irq_save
c_func
(paren
id|flags
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
op_star
id|PCMCIA_Power
op_and_assign
op_complement
(paren
id|ADS_CS_PR_A_3V_POWER
op_or
id|ADS_CS_PR_A_5V_POWER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
op_star
id|PCMCIA_Power
op_and_assign
op_complement
(paren
id|ADS_CS_PR_A_3V_POWER
op_or
id|ADS_CS_PR_A_5V_POWER
)paren
suffix:semicolon
op_star
id|PCMCIA_Power
op_or_assign
id|ADS_CS_PR_A_5V_POWER
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
op_star
id|PCMCIA_Power
op_and_assign
op_complement
(paren
id|ADS_CS_PR_A_3V_POWER
op_or
id|ADS_CS_PR_A_5V_POWER
)paren
suffix:semicolon
op_star
id|PCMCIA_Power
op_or_assign
id|ADS_CS_PR_A_3V_POWER
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
multiline_comment|/* Silently ignore Vpp, output enable, speaker enable. */
singleline_comment|// Reset PCMCIA
op_star
id|PCMCIA_Power
op_and_assign
op_complement
id|ADS_CS_PR_A_RESET
suffix:semicolon
id|udelay
c_func
(paren
l_int|12
)paren
suffix:semicolon
op_star
id|PCMCIA_Power
op_or_assign
id|ADS_CS_PR_A_RESET
suffix:semicolon
id|mdelay
c_func
(paren
l_int|30
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
DECL|function|gcplus_pcmcia_socket_init
r_static
r_void
id|gcplus_pcmcia_socket_init
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
)brace
DECL|function|gcplus_pcmcia_socket_suspend
r_static
r_void
id|gcplus_pcmcia_socket_suspend
c_func
(paren
r_struct
id|soc_pcmcia_socket
op_star
id|skt
)paren
(brace
)brace
DECL|variable|gcplus_pcmcia_ops
r_static
r_struct
id|pcmcia_low_level
id|gcplus_pcmcia_ops
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
id|gcplus_pcmcia_hw_init
comma
dot
id|hw_shutdown
op_assign
id|gcplus_pcmcia_hw_shutdown
comma
dot
id|socket_state
op_assign
id|gcplus_pcmcia_socket_state
comma
dot
id|configure_socket
op_assign
id|gcplus_pcmcia_configure_socket
comma
dot
id|socket_init
op_assign
id|gcplus_pcmcia_socket_init
comma
dot
id|socket_suspend
op_assign
id|gcplus_pcmcia_socket_suspend
comma
)brace
suffix:semicolon
DECL|function|pcmcia_gcplus_init
r_int
id|__init
id|pcmcia_gcplus_init
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
id|machine_is_gcplus
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
id|gcplus_pcmcia_ops
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
