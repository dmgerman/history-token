multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/iop321-setup.c&n; *&n; * Author: Nicolas Pitre &lt;nico@cam.org&gt;&n; * Copyright (C) 2001 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
DECL|macro|IOP321_UART_XTAL
mdefine_line|#define IOP321_UART_XTAL 1843200
multiline_comment|/*&n; * Standard IO mapping for all IOP321 based systems&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|iop321_std_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical      length      type */
multiline_comment|/* mem mapped registers */
(brace
id|IOP321_VIRT_MEM_BASE
comma
id|IOP321_PHY_MEM_BASE
comma
l_int|0x00002000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* PCI IO space */
(brace
l_int|0xfe000000
comma
l_int|0x90000000
comma
l_int|0x00020000
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_IQ80321
DECL|macro|UARTBASE
mdefine_line|#define UARTBASE IQ80321_UART
DECL|macro|IRQ_UART
mdefine_line|#define IRQ_UART IRQ_IQ80321_UART
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IQ31244
DECL|macro|UARTBASE
mdefine_line|#define UARTBASE IQ31244_UART
DECL|macro|IRQ_UART
mdefine_line|#define IRQ_UART IRQ_IQ31244_UART
macro_line|#endif
DECL|variable|iop321_serial_ports
r_static
r_struct
id|uart_port
id|iop321_serial_ports
(braket
)braket
op_assign
(brace
(brace
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
(paren
id|UARTBASE
)paren
comma
dot
id|mapbase
op_assign
(paren
id|UARTBASE
)paren
comma
dot
id|irq
op_assign
id|IRQ_UART
comma
dot
id|flags
op_assign
id|UPF_SKIP_TEST
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|0
comma
dot
id|uartclk
op_assign
id|IOP321_UART_XTAL
comma
dot
id|line
op_assign
l_int|0
comma
dot
id|type
op_assign
id|PORT_16550A
comma
dot
id|fifosize
op_assign
l_int|16
)brace
)brace
suffix:semicolon
DECL|function|iop321_map_io
r_void
id|__init
id|iop321_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|iop321_std_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|iop321_std_desc
)paren
)paren
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|iop321_serial_ports
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_IQ80321
r_extern
r_void
id|iq80321_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|iop321_timer
suffix:semicolon
r_extern
r_void
id|iop321_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IQ31244
r_extern
r_void
id|iq31244_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|iop321_timer
suffix:semicolon
r_extern
r_void
id|iop321_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_IQ80321)
id|MACHINE_START
c_func
(paren
id|IQ80321
comma
l_string|&quot;Intel IQ80321&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Intel Corporation&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IQ80321_UART
comma
id|IQ80321_UART
)paren
id|MAPIO
c_func
(paren
id|iq80321_map_io
)paren
id|INITIRQ
c_func
(paren
id|iop321_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|iop321_timer
comma
id|BOOT_PARAMS
c_func
(paren
l_int|0xa0000100
)paren
id|MACHINE_END
macro_line|#elif defined(CONFIG_ARCH_IQ31244)
id|MACHINE_START
c_func
(paren
id|IQ31244
comma
l_string|&quot;Intel IQ31244&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Intel Corp.&quot;
)paren
id|BOOT_MEM
c_func
(paren
id|PHYS_OFFSET
comma
id|IQ31244_UART
comma
id|IQ31244_UART
)paren
id|MAPIO
c_func
(paren
id|iq31244_map_io
)paren
id|INITIRQ
c_func
(paren
id|iop321_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|iop321_timer
comma
id|BOOT_PARAMS
c_func
(paren
l_int|0xa0000100
)paren
id|MACHINE_END
macro_line|#else
macro_line|#error No machine descriptor defined for this IOP3XX implementation
macro_line|#endif
eof
