multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * Thomas Horsten &lt;thh@lasat.com&gt;&n; * Copyright (C) 2000 LASAT Networks A/S.&n; *&n; * Brian Murphy &lt;brian@murphy.dk&gt;&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Lasat specific setup.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/lasat/lasat.h&gt;
macro_line|#include &lt;asm/lasat/serial.h&gt;
macro_line|#ifdef CONFIG_PICVUE
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#endif
macro_line|#include &quot;ds1603.h&quot;
macro_line|#include &lt;asm/lasat/ds1603.h&gt;
macro_line|#include &lt;asm/lasat/picvue.h&gt;
macro_line|#include &lt;asm/lasat/eeprom.h&gt;
macro_line|#include &quot;prom.h&quot;
DECL|variable|lasat_command_line
r_int
id|lasat_command_line
op_assign
l_int|0
suffix:semicolon
r_void
id|lasatint_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lasat_reboot_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pcisetup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|edhac_init
c_func
(paren
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|addrflt_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|lasat_misc_info
r_struct
id|lasat_misc
id|lasat_misc_info
(braket
id|N_MACHTYPES
)braket
op_assign
(brace
(brace
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x1c840000
)paren
comma
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x1c800000
)paren
comma
l_int|2
)brace
comma
(brace
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x11080000
)paren
comma
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x11000000
)paren
comma
l_int|6
)brace
)brace
suffix:semicolon
DECL|variable|lasat_misc
r_struct
id|lasat_misc
op_star
id|lasat_misc
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_DS1603
DECL|variable|ds_defs
r_static
r_struct
id|ds_defs
id|ds_defs
(braket
id|N_MACHTYPES
)braket
op_assign
(brace
(brace
(paren
r_void
op_star
)paren
id|DS1603_REG_100
comma
(paren
r_void
op_star
)paren
id|DS1603_REG_100
comma
id|DS1603_RST_100
comma
id|DS1603_CLK_100
comma
id|DS1603_DATA_100
comma
id|DS1603_DATA_SHIFT_100
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
(paren
r_void
op_star
)paren
id|DS1603_REG_200
comma
(paren
r_void
op_star
)paren
id|DS1603_DATA_REG_200
comma
id|DS1603_RST_200
comma
id|DS1603_CLK_200
comma
id|DS1603_DATA_200
comma
id|DS1603_DATA_READ_SHIFT_200
comma
l_int|1
comma
l_int|2000
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PICVUE
macro_line|#include &quot;picvue.h&quot;
DECL|variable|pvc_defs
r_static
r_struct
id|pvc_defs
id|pvc_defs
(braket
id|N_MACHTYPES
)braket
op_assign
(brace
(brace
(paren
r_void
op_star
)paren
id|PVC_REG_100
comma
id|PVC_DATA_SHIFT_100
comma
id|PVC_DATA_M_100
comma
id|PVC_E_100
comma
id|PVC_RW_100
comma
id|PVC_RS_100
)brace
comma
(brace
(paren
r_void
op_star
)paren
id|PVC_REG_200
comma
id|PVC_DATA_SHIFT_200
comma
id|PVC_DATA_M_200
comma
id|PVC_E_200
comma
id|PVC_RW_200
comma
id|PVC_RS_200
)brace
)brace
suffix:semicolon
macro_line|#endif
DECL|function|lasat_panic_display
r_static
r_int
id|lasat_panic_display
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
macro_line|#ifdef CONFIG_PICVUE
r_int
r_char
op_star
id|string
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|string
op_eq
l_int|NULL
)paren
id|string
op_assign
l_string|&quot;Kernel Panic&quot;
suffix:semicolon
id|pvc_dump_string
c_func
(paren
id|string
)paren
suffix:semicolon
macro_line|#endif
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|function|lasat_panic_prom_monitor
r_static
r_int
id|lasat_panic_prom_monitor
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
id|prom_monitor
c_func
(paren
)paren
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|lasat_panic_block
r_static
r_struct
id|notifier_block
id|lasat_panic_block
(braket
)braket
op_assign
(brace
(brace
id|lasat_panic_display
comma
l_int|NULL
comma
id|INT_MAX
)brace
comma
(brace
id|lasat_panic_prom_monitor
comma
l_int|NULL
comma
id|INT_MIN
)brace
)brace
suffix:semicolon
DECL|function|lasat_time_init
r_static
r_void
id|lasat_time_init
c_func
(paren
r_void
)paren
(brace
id|mips_hpt_frequency
op_assign
id|lasat_board_info.li_cpu_hz
op_div
l_int|2
suffix:semicolon
)brace
DECL|function|lasat_timer_setup
r_static
r_void
id|lasat_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|write_c0_compare
c_func
(paren
id|read_c0_count
c_func
(paren
)paren
op_plus
id|mips_hpt_frequency
op_div
id|HZ
)paren
suffix:semicolon
id|change_c0_status
c_func
(paren
id|ST0_IM
comma
id|IE_IRQ0
op_or
id|IE_IRQ5
)paren
suffix:semicolon
)brace
DECL|macro|DYNAMIC_SERIAL_INIT
mdefine_line|#define DYNAMIC_SERIAL_INIT
macro_line|#ifdef DYNAMIC_SERIAL_INIT
DECL|function|serial_init
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
id|s.flags
op_assign
id|STD_COM_FLAGS
suffix:semicolon
id|s.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_LASAT_100
)paren
(brace
id|s.uartclk
op_assign
id|LASAT_BASE_BAUD_100
op_star
l_int|16
suffix:semicolon
id|s.irq
op_assign
id|LASATINT_UART_100
suffix:semicolon
id|s.regshift
op_assign
id|LASAT_UART_REGS_SHIFT_100
suffix:semicolon
id|s.membase
op_assign
(paren
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|LASAT_UART_REGS_BASE_100
)paren
suffix:semicolon
)brace
r_else
(brace
id|s.uartclk
op_assign
id|LASAT_BASE_BAUD_200
op_star
l_int|16
suffix:semicolon
id|s.irq
op_assign
id|LASATINT_UART_200
suffix:semicolon
id|s.regshift
op_assign
id|LASAT_UART_REGS_SHIFT_200
suffix:semicolon
id|s.membase
op_assign
(paren
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|LASAT_UART_REGS_BASE_200
)paren
suffix:semicolon
)brace
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Serial setup failed!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
DECL|function|lasat_setup
r_static
r_int
id|__init
id|lasat_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|lasat_misc
op_assign
op_amp
id|lasat_misc_info
(braket
id|mips_machtype
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PICVUE
id|picvue
op_assign
op_amp
id|pvc_defs
(braket
id|mips_machtype
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set up panic notifier */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|lasat_panic_block
)paren
op_div
r_sizeof
(paren
r_struct
id|notifier_block
)paren
suffix:semicolon
id|i
op_increment
)paren
id|notifier_chain_register
c_func
(paren
op_amp
id|panic_notifier_list
comma
op_amp
id|lasat_panic_block
(braket
id|i
)braket
)paren
suffix:semicolon
id|lasat_reboot_setup
c_func
(paren
)paren
suffix:semicolon
id|board_time_init
op_assign
id|lasat_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|lasat_timer_setup
suffix:semicolon
macro_line|#ifdef CONFIG_DS1603
id|ds1603
op_assign
op_amp
id|ds_defs
(braket
id|mips_machtype
)braket
suffix:semicolon
id|rtc_get_time
op_assign
id|ds1603_read
suffix:semicolon
id|rtc_set_time
op_assign
id|ds1603_set
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DYNAMIC_SERIAL_INIT
id|serial_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Switch from prom exception handler to normal mode */
id|change_c0_status
c_func
(paren
id|ST0_BEV
comma
l_int|0
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Lasat specific initialization complete&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lasat_setup
id|early_initcall
c_func
(paren
id|lasat_setup
)paren
suffix:semicolon
eof
