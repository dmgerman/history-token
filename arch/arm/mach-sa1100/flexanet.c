multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/flexanet.c&n; *&n; * Author: Jordi Colomer &lt;jco@ict.es&gt;&n; *&n; * This file contains all FlexaNet-specific tweaks.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|flexanet_BCR
r_int
r_int
id|flexanet_BCR
op_assign
id|FHH_BCR_POWERUP
suffix:semicolon
DECL|variable|flexanet_BCR
id|EXPORT_SYMBOL
c_func
(paren
id|flexanet_BCR
)paren
suffix:semicolon
multiline_comment|/* physical addresses */
DECL|macro|_RCNR
mdefine_line|#define _RCNR        0x90010004
DECL|macro|_GPLR
mdefine_line|#define _GPLR        0x90040000
DECL|macro|_Ser4SSCR0
mdefine_line|#define _Ser4SSCR0   0x80070060
multiline_comment|/*&n; * Get the modem-control register of the UARTs&n; *&n; */
DECL|function|flexanet_get_mctrl
r_static
r_int
id|flexanet_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
r_int
id|stat
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|bsr
suffix:semicolon
multiline_comment|/* only DSR and CTS are implemented in UART1 &amp; 3 */
r_if
c_cond
(paren
id|port-&gt;membase
op_eq
(paren
r_void
op_star
)paren
op_amp
id|Ser1UTCR0
)paren
(brace
id|bsr
op_assign
id|FHH_BSR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bsr
op_amp
id|FHH_BSR_DSR1
)paren
op_ne
l_int|0
)paren
id|stat
op_or_assign
id|TIOCM_DSR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bsr
op_amp
id|FHH_BSR_CTS1
)paren
op_ne
l_int|0
)paren
id|stat
op_or_assign
id|TIOCM_CTS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;membase
op_eq
(paren
r_void
op_star
)paren
op_amp
id|Ser3UTCR0
)paren
(brace
id|bsr
op_assign
id|FHH_BSR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bsr
op_amp
id|FHH_BSR_DSR3
)paren
op_ne
l_int|0
)paren
id|stat
op_or_assign
id|TIOCM_DSR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bsr
op_amp
id|FHH_BSR_CTS3
)paren
op_ne
l_int|0
)paren
id|stat
op_or_assign
id|TIOCM_CTS
suffix:semicolon
)brace
r_return
id|stat
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the modem-control register of the UARTs&n; *&n; */
DECL|function|flexanet_set_mctrl
r_static
r_void
id|flexanet_set_mctrl
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
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* only the RTS signal is implemented in UART1 &amp; 3 */
r_if
c_cond
(paren
id|port-&gt;membase
op_eq
(paren
r_void
op_star
)paren
op_amp
id|Ser1UTCR0
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|flexanet_BCR
op_or_assign
id|FHH_BCR_RTS1
suffix:semicolon
r_else
id|flexanet_BCR
op_and_assign
op_complement
id|FHH_BCR_RTS1
suffix:semicolon
id|FHH_BCR
op_assign
id|flexanet_BCR
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;membase
op_eq
(paren
r_void
op_star
)paren
op_amp
id|Ser3UTCR0
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|flexanet_BCR
op_or_assign
id|FHH_BCR_RTS3
suffix:semicolon
r_else
id|flexanet_BCR
op_and_assign
op_complement
id|FHH_BCR_RTS3
suffix:semicolon
id|FHH_BCR
op_assign
id|flexanet_BCR
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * machine-specific serial port functions&n; *&n; * get_mctrl : set state of modem control lines&n; * set_mctrl : set the modem control lines&n; * pm        : power-management. Turn device on/off.&n; *&n; */
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|flexanet_port_fns
id|__initdata
op_assign
(brace
id|set_mctrl
suffix:colon
id|flexanet_set_mctrl
comma
id|get_mctrl
suffix:colon
id|flexanet_get_mctrl
comma
id|pm
suffix:colon
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialization and serial port mapping&n; *&n; */
DECL|function|flexanet_serial_init
r_static
r_int
id|flexanet_serial_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* register low-level functions */
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|flexanet_port_fns
)paren
suffix:semicolon
multiline_comment|/* UART port number mapping */
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* RS232 */
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Radio */
multiline_comment|/* Select UART function in Serial port 1 */
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|flexanet_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00001000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Board Control Register */
(brace
l_int|0xf1000000
comma
l_int|0x18000000
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Ethernet controller */
(brace
l_int|0xD0000000
comma
l_int|0x40000000
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Instrument boards */
(brace
l_int|0xD8000000
comma
l_int|0x48000000
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
multiline_comment|/* External peripherals */
)brace
suffix:semicolon
DECL|function|flexanet_map_io
r_static
r_void
id|__init
id|flexanet_map_io
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
id|flexanet_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|flexanet_io_desc
)paren
)paren
suffix:semicolon
id|flexanet_serial_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wakeup source is GPIO-0 only */
id|PWER
op_assign
id|PWER_GPIO0
suffix:semicolon
multiline_comment|/* GPIOs set to zero during sleep */
id|PGSR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * stop the 3.68 MHz oscillator and float control busses&n;&t; * during sleep, since peripherals are powered off.&n;&t; */
id|PCFR
op_assign
id|PCFR_OPDE
op_or
id|PCFR_FP
op_or
id|PCFR_FS
suffix:semicolon
multiline_comment|/* deassert the GUI reset */
id|FLEXANET_BCR_set
c_func
(paren
id|FHH_BCR_GUI_NRST
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set IRQ edges&n;&t; */
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_GUI_IRQ
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|FLEXANET
comma
l_string|&quot;FlexaNet&quot;
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
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|MAPIO
c_func
(paren
id|flexanet_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
