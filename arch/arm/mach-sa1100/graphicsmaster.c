multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/graphicsmaster.c&n; *&n; * Pieces specific to the GraphicsMaster board&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#include &quot;sa1111.h&quot;
DECL|function|graphicsmaster_init
r_static
r_int
id|__init
id|graphicsmaster_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_graphicsmaster
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the memory bus request/grant signals are setup,&n;&t; * and the grant is held in its inactive state&n;&t; */
id|sa1110_mb_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Probe for SA1111.&n;&t; */
id|ret
op_assign
id|sa1111_probe
c_func
(paren
l_int|0x18000000
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
multiline_comment|/*&n;&t; * Enable PWM control for LCD&n;&t; */
id|SKPCR
op_or_assign
id|SKPCR_PWMCLKEN
suffix:semicolon
id|SKPWM0
op_assign
l_int|0x7F
suffix:semicolon
singleline_comment|// VEE
id|SKPEN0
op_assign
l_int|1
suffix:semicolon
id|SKPWM1
op_assign
l_int|0x01
suffix:semicolon
singleline_comment|// Backlight
id|SKPEN1
op_assign
l_int|1
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
id|sa1111_init_irq
c_func
(paren
id|ADS_EXT_IRQ
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|graphicsmaster_init
id|__initcall
c_func
(paren
id|graphicsmaster_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Handlers for GraphicsMaster&squot;s external IRQ logic&n; */
r_static
r_void
DECL|function|gm_irq_handler
id|gm_irq_handler
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
id|mask
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mask
op_assign
id|ADS_INT_ST1
op_or
(paren
id|ADS_INT_ST2
op_lshift
l_int|8
)paren
)paren
)paren
(brace
multiline_comment|/* clear the parent IRQ */
id|GEDR
op_assign
id|GPIO_GPIO0
suffix:semicolon
id|irq
op_assign
id|ADS_EXT_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
id|irq
op_increment
suffix:semicolon
id|desc
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
suffix:semicolon
)brace
)brace
DECL|function|gm_mask_irq1
r_static
r_void
id|gm_mask_irq1
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|mask
op_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|ADS_EXT_IRQ
c_func
(paren
l_int|0
)paren
)paren
)paren
suffix:semicolon
id|ADS_INT_EN1
op_and_assign
op_complement
id|mask
suffix:semicolon
id|ADS_INT_ST1
op_assign
id|mask
suffix:semicolon
)brace
DECL|function|gm_unmask_irq1
r_static
r_void
id|gm_unmask_irq1
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ADS_INT_EN1
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|ADS_EXT_IRQ
c_func
(paren
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|gm_irq1_chip
r_static
r_struct
id|irqchip
id|gm_irq1_chip
op_assign
(brace
id|ack
suffix:colon
id|gm_mask_irq1
comma
id|mask
suffix:colon
id|gm_mask_irq1
comma
id|unmask
suffix:colon
id|gm_unmask_irq1
comma
)brace
suffix:semicolon
DECL|function|gm_mask_irq2
r_static
r_void
id|gm_mask_irq2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|mask
op_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|ADS_EXT_IRQ
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
id|ADS_INT_EN2
op_and_assign
op_complement
id|mask
suffix:semicolon
id|ADS_INT_ST2
op_assign
id|mask
suffix:semicolon
)brace
DECL|function|gm_unmask_irq2
r_static
r_void
id|gm_unmask_irq2
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ADS_INT_EN2
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|ADS_EXT_IRQ
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|gm_irq2_chip
r_static
r_struct
id|irqchip
id|gm_irq2_chip
op_assign
(brace
id|ack
suffix:colon
id|gm_mask_irq2
comma
id|mask
suffix:colon
id|gm_mask_irq2
comma
id|unmask
suffix:colon
id|gm_unmask_irq2
comma
)brace
suffix:semicolon
DECL|function|graphicsmaster_init_irq
r_static
r_void
id|__init
id|graphicsmaster_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* First the standard SA1100 IRQs */
id|sa1100_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* disable all IRQs */
id|ADS_INT_EN1
op_assign
l_int|0
suffix:semicolon
id|ADS_INT_EN2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear all IRQs */
id|ADS_INT_ST1
op_assign
l_int|0xff
suffix:semicolon
id|ADS_INT_ST2
op_assign
l_int|0xff
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|ADS_EXT_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
op_le
id|ADS_EXT_IRQ
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|gm_irq1_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_PROBE
op_or
id|IRQF_VALID
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|irq
op_assign
id|ADS_EXT_IRQ
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|irq
op_le
id|ADS_EXT_IRQ
c_func
(paren
l_int|15
)paren
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|gm_irq2_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_PROBE
op_or
id|IRQF_VALID
)paren
suffix:semicolon
)brace
id|set_irq_type
c_func
(paren
id|IRQ_GPIO0
comma
id|IRQT_FALLING
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIO0
comma
id|gm_irq_handler
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialization fixup&n; */
r_static
r_void
id|__init
DECL|function|fixup_graphicsmaster
id|fixup_graphicsmaster
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|param_struct
op_star
id|params
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
id|SET_BANK
c_func
(paren
l_int|0
comma
l_int|0xc0000000
comma
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|mi-&gt;nr_banks
op_assign
l_int|1
suffix:semicolon
id|SET_BANK
c_func
(paren
l_int|1
comma
l_int|0xc8000000
comma
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|mi-&gt;nr_banks
op_assign
l_int|2
suffix:semicolon
id|ROOT_DEV
op_assign
id|mk_kdev
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|setup_ramdisk
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|8192
)paren
suffix:semicolon
id|setup_initrd
c_func
(paren
id|__phys_to_virt
c_func
(paren
l_int|0xc0800000
)paren
comma
l_int|4
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|graphicsmaster_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00400000
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
multiline_comment|/* CPLD */
(brace
l_int|0xf1000000
comma
l_int|0x40000000
comma
l_int|0x00400000
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
multiline_comment|/* CAN */
(brace
l_int|0xf4000000
comma
l_int|0x18000000
comma
l_int|0x00800000
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
macro_line|#error Old code.  Someone needs to decide what to do about this.
macro_line|#if 0
r_static
r_int
id|graphicsmaster_uart_open
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|uart_info
op_star
id|info
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
multiline_comment|/* Set RTS Output */
id|GPSR
op_assign
id|GPIO_GPIO15
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser2UTCR0
)paren
(brace
id|Ser2UTCR4
op_assign
id|Ser2HSCR0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set RTS Output */
id|GPSR
op_assign
id|GPIO_GPIO17
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
multiline_comment|/* Set RTS Output */
id|GPSR
op_assign
id|GPIO_GPIO19
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|graphicsmaster_get_mctrl
r_static
id|u_int
id|graphicsmaster_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|u_int
id|result
op_assign
id|TIOCM_CD
op_or
id|TIOCM_DSR
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
op_logical_neg
(paren
id|GPLR
op_amp
id|GPIO_GPIO14
)paren
)paren
id|result
op_or_assign
id|TIOCM_CTS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser2UTCR0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|GPLR
op_amp
id|GPIO_GPIO16
)paren
)paren
id|result
op_or_assign
id|TIOCM_CTS
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
op_logical_neg
(paren
id|GPLR
op_amp
id|GPIO_GPIO17
)paren
)paren
id|result
op_or_assign
id|TIOCM_CTS
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|TIOCM_CTS
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|graphicsmaster_set_mctrl
r_static
r_void
id|graphicsmaster_set_mctrl
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
id|GPCR
op_assign
id|GPIO_GPIO15
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_GPIO15
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser2UTCR0
)paren
(brace
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|GPCR
op_assign
id|GPIO_GPIO17
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_GPIO17
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
id|GPCR
op_assign
id|GPIO_GPIO19
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_GPIO19
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|graphicsmaster_uart_pm
id|graphicsmaster_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
multiline_comment|/* make serial ports work ... */
id|Ser2UTCR4
op_assign
l_int|0
suffix:semicolon
id|Ser2HSCR0
op_assign
l_int|0
suffix:semicolon
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|graphicsmaster_port_fns
id|__initdata
op_assign
(brace
id|get_mctrl
suffix:colon
id|graphicsmaster_get_mctrl
comma
id|set_mctrl
suffix:colon
id|graphicsmaster_set_mctrl
comma
id|pm
suffix:colon
id|graphicsmaster_uart_pm
comma
)brace
suffix:semicolon
DECL|function|graphicsmaster_map_io
r_static
r_void
id|__init
id|graphicsmaster_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|graphicsmaster_io_desc
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|graphicsmaster_port_fns
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|2
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* set GPDR now */
id|GPDR
op_or_assign
id|GPIO_GPIO15
op_or
id|GPIO_GPIO17
op_or
id|GPIO_GPIO19
suffix:semicolon
id|GPDR
op_and_assign
op_complement
(paren
id|GPIO_GPIO14
op_or
id|GPIO_GPIO16
op_or
id|GPIO_GPIO18
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|GRAPHICSMASTER
comma
l_string|&quot;ADS GraphicsMaster&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|FIXUP
c_func
(paren
id|fixup_graphicsmaster
)paren
id|MAPIO
c_func
(paren
id|graphicsmaster_map_io
)paren
id|INITIRQ
c_func
(paren
id|graphicsmaster_init_irq
)paren
id|MACHINE_END
eof
