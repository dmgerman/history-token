multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/neponset.c&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/arch/irq.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/arch/assabet.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1111.h&quot;
multiline_comment|/*&n; * Install handler for Neponset IRQ.  Yes, yes... we are way down the IRQ&n; * cascade which is not good for IRQ latency, but the hardware has been&n; * designed that way...&n; */
DECL|function|neponset_IRQ_demux
r_static
r_void
id|neponset_IRQ_demux
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irr
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|irr
op_assign
id|IRR
op_amp
(paren
id|IRR_ETHERNET
op_or
id|IRR_USAR
op_or
id|IRR_SA1111
)paren
suffix:semicolon
multiline_comment|/* Let&squot;s have all active IRQ bits high.&n;&t;&t; * Note: there is a typo in the Neponset user&squot;s guide&n;&t;&t; * for the SA1111 IRR level.&n;&t;&t; */
id|irr
op_xor_assign
(paren
id|IRR_ETHERNET
op_or
id|IRR_USAR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|irr
op_amp
id|IRR_ETHERNET
)paren
(brace
id|do_IRQ
c_func
(paren
id|IRQ_NEPONSET_SMC9196
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irr
op_amp
id|IRR_USAR
)paren
(brace
id|do_IRQ
c_func
(paren
id|IRQ_NEPONSET_USAR
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irr
op_amp
id|IRR_SA1111
)paren
(brace
id|sa1111_IRQ_demux
c_func
(paren
id|irq
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|neponset_irq
r_static
r_struct
id|irqaction
id|neponset_irq
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Neponset&quot;
comma
id|handler
suffix:colon
id|neponset_IRQ_demux
comma
id|flags
suffix:colon
id|SA_INTERRUPT
)brace
suffix:semicolon
DECL|function|neponset_init_irq
r_static
r_void
id|__init
id|neponset_init_irq
c_func
(paren
r_void
)paren
(brace
id|sa1111_init_irq
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* SA1111 IRQ not routed to a GPIO */
multiline_comment|/* setup extra Neponset IRQs */
id|irq_desc
(braket
id|IRQ_NEPONSET_SMC9196
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|IRQ_NEPONSET_SMC9196
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|IRQ_NEPONSET_USAR
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|IRQ_NEPONSET_USAR
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_GPIO25
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
id|setup_arm_irq
c_func
(paren
id|IRQ_GPIO25
comma
op_amp
id|neponset_irq
)paren
suffix:semicolon
)brace
DECL|function|neponset_init
r_static
r_int
id|__init
id|neponset_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * The Neponset is only present on the Assabet machine type.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|machine_is_assabet
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the memory bus request/grant signals are setup,&n;&t; * and the grant is held in its inactive state, whether or not&n;&t; * we actually have a Neponset attached.&n;&t; */
id|sa1110_mb_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_has_neponset
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Neponset expansion board not present&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WHOAMI
op_ne
l_int|0x11
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Neponset board detected, but &quot;
l_string|&quot;wrong ID: %02x&bslash;n&quot;
comma
id|WHOAMI
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable GPIO 0/1 drivers so the buttons work on the module.&n;&t; */
id|NCR_0
op_or_assign
id|NCR_GP01_OFF
suffix:semicolon
multiline_comment|/*&n;&t; * Neponset has SA1111 connected to CS4.  We know that after&n;&t; * reset the chip will be configured for variable latency IO.&n;&t; */
multiline_comment|/* FIXME: setup MSC2 */
multiline_comment|/*&n;&t; * Probe for a SA1111.&n;&t; */
id|ret
op_assign
id|sa1111_probe
c_func
(paren
l_int|0x40000000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * We found it.  Wake the chip up.&n;&t; */
id|sa1111_wake
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The SDRAM configuration of the SA1110 and the SA1111 must&n;&t; * match.  This is very important to ensure that SA1111 accesses&n;&t; * don&squot;t corrupt the SDRAM.  Note that this ungates the SA1111&squot;s&n;&t; * MBGNT signal, so we must have called sa1110_mb_disable()&n;&t; * beforehand.&n;&t; */
id|sa1111_configure_smc
c_func
(paren
l_int|1
comma
id|FExtr
c_func
(paren
id|MDCNFG
comma
id|MDCNFG_SA1110_DRAC0
)paren
comma
id|FExtr
c_func
(paren
id|MDCNFG
comma
id|MDCNFG_SA1110_TDL0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We only need to turn on DCLK whenever we want to use the&n;&t; * DMA.  It can otherwise be held firmly in the off position.&n;&t; */
id|SKPCR
op_or_assign
id|SKPCR_DCLKEN
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the SA1110 memory bus request and grant signals.&n;&t; */
id|sa1110_mb_enable
c_func
(paren
)paren
suffix:semicolon
id|neponset_init_irq
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|neponset_init
id|__initcall
c_func
(paren
id|neponset_init
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|neponset_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xf3000000
comma
l_int|0x10000000
comma
l_int|0x00100000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* System Registers */
(brace
l_int|0xf4000000
comma
l_int|0x40000000
comma
l_int|0x00100000
comma
id|DOMAIN_IO
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* SA-1111 */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|neponset_set_mctrl
r_static
r_void
id|neponset_set_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|mctrl
)paren
(brace
id|u_int
id|mdm_ctl0
op_assign
id|MDM_CTL_0
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|mdm_ctl0
op_and_assign
op_complement
id|MDM_CTL0_RTS2
suffix:semicolon
r_else
id|mdm_ctl0
op_or_assign
id|MDM_CTL0_RTS2
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_DTR
)paren
id|mdm_ctl0
op_and_assign
op_complement
id|MDM_CTL0_DTR2
suffix:semicolon
r_else
id|mdm_ctl0
op_or_assign
id|MDM_CTL0_DTR2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser3UTCR0
)paren
(brace
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|mdm_ctl0
op_and_assign
op_complement
id|MDM_CTL0_RTS1
suffix:semicolon
r_else
id|mdm_ctl0
op_or_assign
id|MDM_CTL0_RTS1
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_DTR
)paren
id|mdm_ctl0
op_and_assign
op_complement
id|MDM_CTL0_DTR1
suffix:semicolon
r_else
id|mdm_ctl0
op_or_assign
id|MDM_CTL0_DTR1
suffix:semicolon
)brace
id|MDM_CTL_0
op_assign
id|mdm_ctl0
suffix:semicolon
)brace
DECL|function|neponset_get_mctrl
r_static
id|u_int
id|neponset_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|u_int
id|ret
op_assign
id|TIOCM_CD
op_or
id|TIOCM_CTS
op_or
id|TIOCM_DSR
suffix:semicolon
id|u_int
id|mdm_ctl1
op_assign
id|MDM_CTL_1
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
r_if
c_cond
(paren
id|mdm_ctl1
op_amp
id|MDM_CTL1_DCD2
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_CD
suffix:semicolon
r_if
c_cond
(paren
id|mdm_ctl1
op_amp
id|MDM_CTL1_CTS2
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_CTS
suffix:semicolon
r_if
c_cond
(paren
id|mdm_ctl1
op_amp
id|MDM_CTL1_DSR2
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_DSR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser3UTCR0
)paren
(brace
r_if
c_cond
(paren
id|mdm_ctl1
op_amp
id|MDM_CTL1_DCD1
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_CD
suffix:semicolon
r_if
c_cond
(paren
id|mdm_ctl1
op_amp
id|MDM_CTL1_CTS1
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_CTS
suffix:semicolon
r_if
c_cond
(paren
id|mdm_ctl1
op_amp
id|MDM_CTL1_DSR1
)paren
id|ret
op_and_assign
op_complement
id|TIOCM_DSR
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|neponset_port_fns
id|__initdata
op_assign
(brace
id|set_mctrl
suffix:colon
id|neponset_set_mctrl
comma
id|get_mctrl
suffix:colon
id|neponset_get_mctrl
comma
)brace
suffix:semicolon
DECL|function|neponset_map_io
r_void
id|__init
id|neponset_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|neponset_io_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_has_neponset
c_func
(paren
)paren
)paren
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|neponset_port_fns
)paren
suffix:semicolon
)brace
eof
