multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2002 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * SEAD specific setup.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mips-boards/generic.h&gt;
macro_line|#include &lt;asm/mips-boards/prom.h&gt;
macro_line|#include &lt;asm/mips-boards/sead.h&gt;
macro_line|#include &lt;asm/mips-boards/seadint.h&gt;
macro_line|#include &lt;asm/time.h&gt;
r_extern
r_void
id|mips_reboot_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mips_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mips_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
r_static
r_void
id|__init
id|serial_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;MIPS SEAD&quot;
suffix:semicolon
)brace
DECL|function|sead_setup
r_static
r_void
id|__init
id|sead_setup
c_func
(paren
r_void
)paren
(brace
id|ioport_resource.end
op_assign
l_int|0x7fffffff
suffix:semicolon
id|serial_init
(paren
)paren
suffix:semicolon
id|board_time_init
op_assign
id|mips_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|mips_timer_setup
suffix:semicolon
id|mips_reboot_setup
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sead_setup
id|early_initcall
c_func
(paren
id|sead_setup
)paren
suffix:semicolon
DECL|function|serial_init
r_static
r_void
id|__init
id|serial_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SERIAL_8250
r_struct
id|uart_port
id|s
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|s
comma
l_int|0
comma
r_sizeof
(paren
id|s
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_LITTLE_ENDIAN
id|s.iobase
op_assign
id|SEAD_UART0_REGS_BASE
suffix:semicolon
macro_line|#else
id|s.iobase
op_assign
id|SEAD_UART0_REGS_BASE
op_plus
l_int|3
suffix:semicolon
macro_line|#endif
id|s.irq
op_assign
id|SEADINT_UART0
suffix:semicolon
id|s.uartclk
op_assign
id|SEAD_BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|s.flags
op_assign
id|ASYNC_BOOT_AUTOCONF
op_or
id|ASYNC_SKIP_TEST
op_or
id|ASYNC_AUTO_IRQ
suffix:semicolon
id|s.iotype
op_assign
l_int|0
suffix:semicolon
id|s.regshift
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|s
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Serial setup failed!&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
