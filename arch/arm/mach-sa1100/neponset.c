multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/neponset.c&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;asm/arch/assabet.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1111.h&quot;
DECL|variable|neponset_device
r_static
r_struct
id|device
id|neponset_device
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Neponset&quot;
comma
id|bus_id
suffix:colon
l_string|&quot;nep_bus&quot;
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Install handler for Neponset IRQ.  Note that we have to loop here&n; * since the ETHERNET and USAR IRQs are level based, and we need to&n; * ensure that the IRQ signal is deasserted before returning.  This&n; * is rather unfortunate.&n; */
r_static
r_void
DECL|function|neponset_irq_handler
id|neponset_irq_handler
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|irr
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|irqdesc
op_star
id|d
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Acknowledge the parent IRQ.&n;&t;&t; */
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Read the interrupt reason register.  Let&squot;s have all&n;&t;&t; * active IRQ bits high.  Note: there is a typo in the&n;&t;&t; * Neponset user&squot;s guide for the SA1111 IRR level.&n;&t;&t; */
id|irr
op_assign
id|IRR
op_xor
(paren
id|IRR_ETHERNET
op_or
id|IRR_USAR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irr
op_amp
(paren
id|IRR_ETHERNET
op_or
id|IRR_USAR
op_or
id|IRR_SA1111
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Since there is no individual mask, we have to&n;&t;&t; * mask the parent IRQ.  This is safe, since we&squot;ll&n;&t;&t; * recheck the register for any pending IRQs.&n;&t;&t; */
r_if
c_cond
(paren
id|irr
op_amp
(paren
id|IRR_ETHERNET
op_or
id|IRR_USAR
)paren
)paren
(brace
id|desc-&gt;chip
op_member_access_from_pointer
id|mask
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irr
op_amp
id|IRR_ETHERNET
)paren
(brace
id|d
op_assign
id|irq_desc
op_plus
id|IRQ_NEPONSET_SMC9196
suffix:semicolon
id|d
op_member_access_from_pointer
id|handle
c_func
(paren
id|IRQ_NEPONSET_SMC9196
comma
id|d
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
id|d
op_assign
id|irq_desc
op_plus
id|IRQ_NEPONSET_USAR
suffix:semicolon
id|d
op_member_access_from_pointer
id|handle
c_func
(paren
id|IRQ_NEPONSET_USAR
comma
id|d
comma
id|regs
)paren
suffix:semicolon
)brace
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
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
id|d
op_assign
id|irq_desc
op_plus
id|IRQ_NEPONSET_SA1111
suffix:semicolon
id|d
op_member_access_from_pointer
id|handle
c_func
(paren
id|IRQ_NEPONSET_SA1111
comma
id|d
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
)brace
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
multiline_comment|/*&n;&t; * Install handler for GPIO25.&n;&t; */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO25
comma
id|IRQT_RISING
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO25
comma
id|neponset_irq_handler
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup other Neponset IRQs.  SA1111 will be done by the&n;&t; * generic SA1111 code.&n;&t; */
id|set_irq_handler
c_func
(paren
id|IRQ_NEPONSET_SMC9196
comma
id|do_simple_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|IRQ_NEPONSET_SMC9196
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|IRQ_NEPONSET_USAR
comma
id|do_simple_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|IRQ_NEPONSET_USAR
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
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
id|ret
op_assign
id|device_register
c_func
(paren
op_amp
id|neponset_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|neponset_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable GPIO 0/1 drivers so the buttons work on the module.&n;&t; */
id|NCR_0
op_or_assign
id|NCR_GP01_OFF
suffix:semicolon
multiline_comment|/*&n;&t; * Neponset has SA1111 connected to CS4.  We know that after&n;&t; * reset the chip will be configured for variable latency IO.&n;&t; */
multiline_comment|/* FIXME: setup MSC2 */
multiline_comment|/*&n;&t; * Probe and initialise the SA1111.&n;&t; */
r_return
id|sa1111_init
c_func
(paren
op_amp
id|neponset_device
comma
l_int|0x40000000
comma
id|IRQ_NEPONSET_SA1111
)paren
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
l_int|0
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
l_int|0
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
