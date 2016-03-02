multiline_comment|/*&n; * linux/arch/arm/mach-iop3xx/iop331-setup.c&n; *&n; * Author: Dave Jiang (dave.jiang@intel.com)&n; * Copyright (C) 2004 Intel Corporation.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
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
DECL|macro|IOP331_UART_XTAL
mdefine_line|#define IOP331_UART_XTAL 33334000
multiline_comment|/*&n; * Standard IO mapping for all IOP331 based systems&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|iop331_std_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical      length      type */
multiline_comment|/* mem mapped registers */
(brace
id|IOP331_VIRT_MEM_BASE
comma
id|IOP331_PHYS_MEM_BASE
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
DECL|variable|iop331_serial_ports
r_static
r_struct
id|uart_port
id|iop331_serial_ports
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
id|IQ80331_UART0_VIRT
)paren
comma
dot
id|mapbase
op_assign
(paren
id|IQ80331_UART0_PHYS
)paren
comma
dot
id|irq
op_assign
id|IRQ_IOP331_UART0
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
l_int|2
comma
dot
id|uartclk
op_assign
id|IOP331_UART_XTAL
comma
dot
id|line
op_assign
l_int|0
comma
dot
id|type
op_assign
id|PORT_XSCALE
comma
dot
id|fifosize
op_assign
l_int|32
)brace
comma
(brace
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
(paren
id|IQ80331_UART1_VIRT
)paren
comma
dot
id|mapbase
op_assign
(paren
id|IQ80331_UART1_PHYS
)paren
comma
dot
id|irq
op_assign
id|IRQ_IOP331_UART1
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
l_int|2
comma
dot
id|uartclk
op_assign
id|IOP331_UART_XTAL
comma
dot
id|line
op_assign
l_int|1
comma
dot
id|type
op_assign
id|PORT_XSCALE
comma
dot
id|fifosize
op_assign
l_int|32
)brace
)brace
suffix:semicolon
DECL|function|iop331_map_io
r_void
id|__init
id|iop331_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|iop331_std_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|iop331_std_desc
)paren
)paren
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|iop331_serial_ports
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|iop331_serial_ports
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_IQ80331
r_extern
r_void
id|iop331_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop331_init_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iq80331_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_IQ80331)
id|MACHINE_START
c_func
(paren
id|IQ80331
comma
l_string|&quot;Intel IQ80331&quot;
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
l_int|0xfefff000
comma
l_int|0xfffff000
)paren
singleline_comment|// virtual, physical
singleline_comment|//BOOT_MEM(PHYS_OFFSET, IQ80331_UART0_VIRT, IQ80331_UART0_PHYS)
id|MAPIO
c_func
(paren
id|iq80331_map_io
)paren
id|INITIRQ
c_func
(paren
id|iop331_init_irq
)paren
id|INITTIME
c_func
(paren
id|iop331_init_time
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x0100
)paren
id|MACHINE_END
macro_line|#else
macro_line|#error No machine descriptor defined for this IOP3XX implementation
macro_line|#endif
eof
