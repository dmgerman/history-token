multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/graphicsclient.c&n; *&n; * Author: Nicolas Pitre&n; *&n; * Pieces specific to the GraphicsClient board&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/*&n; * Handlers for GraphicsClient&squot;s external IRQ logic&n; */
r_static
r_void
DECL|function|gc_irq_handler
id|gc_irq_handler
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
DECL|function|gc_mask_irq1
r_static
r_void
id|gc_mask_irq1
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
DECL|function|gc_unmask_irq1
r_static
r_void
id|gc_unmask_irq1
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
DECL|variable|gc_irq1_chip
r_static
r_struct
id|irqchip
id|gc_irq1_chip
op_assign
(brace
id|ack
suffix:colon
id|gc_mask_irq1
comma
id|mask
suffix:colon
id|gc_mask_irq1
comma
id|unmask
suffix:colon
id|gc_unmask_irq1
comma
)brace
suffix:semicolon
DECL|function|gc_mask_irq2
r_static
r_void
id|gc_mask_irq2
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
DECL|function|gc_unmask_irq2
r_static
r_void
id|gc_unmask_irq2
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
DECL|variable|gc_irq2_chip
r_static
r_struct
id|irqchip
id|gc_irq2_chip
op_assign
(brace
id|ack
suffix:colon
id|gc_mask_irq2
comma
id|mask
suffix:colon
id|gc_mask_irq2
comma
id|unmask
suffix:colon
id|gc_unmask_irq2
comma
)brace
suffix:semicolon
DECL|function|graphicsclient_init_irq
r_static
r_void
id|__init
id|graphicsclient_init_irq
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
id|gc_irq1_chip
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
id|IRQF_VALID
op_or
id|IRQF_PROBE
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
id|gc_irq2_chip
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
id|IRQF_VALID
op_or
id|IRQF_PROBE
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
id|gc_irq_handler
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialization fixup&n; */
r_static
r_void
id|__init
DECL|function|fixup_graphicsclient
id|fixup_graphicsclient
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
id|graphicsclient_io_desc
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
l_int|0x18000000
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
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|graphicsclient_get_mctrl
r_static
id|u_int
id|graphicsclient_get_mctrl
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
id|GPIO_GC_UART0_CTS
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
id|GPIO_GC_UART1_CTS
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
id|GPIO_GC_UART2_CTS
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
DECL|function|graphicsclient_set_mctrl
r_static
r_void
id|graphicsclient_set_mctrl
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
id|GPIO_GC_UART0_RTS
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_GC_UART0_RTS
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
id|GPIO_GC_UART1_RTS
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_GC_UART1_RTS
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
id|GPIO_GC_UART2_RTS
suffix:semicolon
r_else
id|GPSR
op_assign
id|GPIO_GC_UART2_RTS
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|graphicsclient_uart_pm
id|graphicsclient_uart_pm
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
id|graphicsclient_port_fns
id|__initdata
op_assign
(brace
id|get_mctrl
suffix:colon
id|graphicsclient_get_mctrl
comma
id|set_mctrl
suffix:colon
id|graphicsclient_set_mctrl
comma
id|pm
suffix:colon
id|graphicsclient_uart_pm
comma
)brace
suffix:semicolon
DECL|function|graphicsclient_map_io
r_static
r_void
id|__init
id|graphicsclient_map_io
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
id|graphicsclient_io_desc
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|graphicsclient_port_fns
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
id|GPDR
op_or_assign
id|GPIO_GC_UART0_RTS
op_or
id|GPIO_GC_UART1_RTS
op_or
id|GPIO_GC_UART2_RTS
suffix:semicolon
id|GPDR
op_and_assign
op_complement
(paren
id|GPIO_GC_UART0_CTS
op_or
id|GPIO_GC_UART1_RTS
op_or
id|GPIO_GC_UART2_RTS
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|GRAPHICSCLIENT
comma
l_string|&quot;ADS GraphicsClient&quot;
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
id|fixup_graphicsclient
)paren
id|MAPIO
c_func
(paren
id|graphicsclient_map_io
)paren
id|INITIRQ
c_func
(paren
id|graphicsclient_init_irq
)paren
id|MACHINE_END
eof
