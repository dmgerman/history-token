multiline_comment|/*&n; *  serial.c, Serial Interface Unit routines for NEC VR4100 series.&n; *&n; *  Copyright (C) 2002  MontaVista Software Inc.&n; *    Author: Yoichi Yuasa &lt;yyuasa@mvista.com or source@mvista.com&gt;&n; *  Copyright (C) 2003-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Changes:&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - New creation, NEC VR4122 and VR4131 are supported.&n; *  - Added support for NEC VR4111 and VR4121.&n; *&n; *  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *  - Added support for NEC VR4133.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|macro|SIUIRSEL_TYPE1
mdefine_line|#define SIUIRSEL_TYPE1&t;&t;KSEG1ADDR(0x0c000008)
DECL|macro|SIUIRSEL_TYPE2
mdefine_line|#define SIUIRSEL_TYPE2&t;&t;KSEG1ADDR(0x0f000808)
DECL|macro|USE_RS232C
mdefine_line|#define USE_RS232C&t;&t;0x00
DECL|macro|USE_IRDA
mdefine_line|#define USE_IRDA&t;&t;0x01
DECL|macro|SIU_USES_IRDA
mdefine_line|#define SIU_USES_IRDA&t;&t;0x00
DECL|macro|FIR_USES_IRDA
mdefine_line|#define FIR_USES_IRDA&t;&t;0x02
DECL|macro|IRDA_MODULE_SHARP
mdefine_line|#define IRDA_MODULE_SHARP&t;0x00
DECL|macro|IRDA_MODULE_TEMIC
mdefine_line|#define IRDA_MODULE_TEMIC&t;0x04
DECL|macro|IRDA_MODULE_HP
mdefine_line|#define IRDA_MODULE_HP&t;&t;0x08
DECL|macro|TMICTX
mdefine_line|#define TMICTX&t;&t;&t;0x10
DECL|macro|TMICMODE
mdefine_line|#define TMICMODE&t;&t;0x20
DECL|macro|SIU_BASE_TYPE1
mdefine_line|#define SIU_BASE_TYPE1&t;&t;0x0c000000UL&t;/* VR4111 and VR4121 */
DECL|macro|SIU_BASE_TYPE2
mdefine_line|#define SIU_BASE_TYPE2&t;&t;0x0f000800UL&t;/* VR4122, VR4131 and VR4133 */
DECL|macro|SIU_SIZE
mdefine_line|#define SIU_SIZE&t;&t;0x8UL
DECL|macro|SIU_BASE_BAUD
mdefine_line|#define SIU_BASE_BAUD&t;&t;1152000
multiline_comment|/* VR4122, VR4131 and VR4133 DSIU Registers */
DECL|macro|DSIU_BASE
mdefine_line|#define DSIU_BASE&t;&t;0x0f000820UL
DECL|macro|DSIU_SIZE
mdefine_line|#define DSIU_SIZE&t;&t;0x8UL
DECL|macro|DSIU_BASE_BAUD
mdefine_line|#define DSIU_BASE_BAUD&t;&t;1152000
DECL|variable|vr41xx_serial_ports
r_int
id|vr41xx_serial_ports
op_assign
l_int|0
suffix:semicolon
DECL|function|vr41xx_select_siu_interface
r_void
id|vr41xx_select_siu_interface
c_func
(paren
id|siu_interface_t
id|interface
comma
id|irda_module_t
id|module
)paren
(brace
r_uint16
id|val
op_assign
id|USE_RS232C
suffix:semicolon
multiline_comment|/* Select RS-232C */
multiline_comment|/* Select IrDA */
r_if
c_cond
(paren
id|interface
op_eq
id|SIU_IRDA
)paren
(brace
r_switch
c_cond
(paren
id|module
)paren
(brace
r_case
id|IRDA_SHARP
suffix:colon
id|val
op_assign
id|IRDA_MODULE_SHARP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_TEMIC
suffix:colon
id|val
op_assign
id|IRDA_MODULE_TEMIC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRDA_HP
suffix:colon
id|val
op_assign
id|IRDA_MODULE_HP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SIU: unknown IrDA module&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|val
op_or_assign
id|USE_IRDA
op_or
id|SIU_USES_IRDA
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_VR4111
suffix:colon
r_case
id|CPU_VR4121
suffix:colon
id|writew
c_func
(paren
id|val
comma
id|SIUIRSEL_TYPE1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
r_case
id|CPU_VR4133
suffix:colon
id|writew
c_func
(paren
id|val
comma
id|SIUIRSEL_TYPE2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SIU: unsupported CPU of NEC VR4100 series&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|vr41xx_siu_init
r_void
id|__init
id|vr41xx_siu_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|uart_port
id|port
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.line
op_assign
id|vr41xx_serial_ports
suffix:semicolon
id|port.uartclk
op_assign
id|SIU_BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|port.irq
op_assign
id|SIU_IRQ
suffix:semicolon
id|port.flags
op_assign
id|UPF_RESOURCES
op_or
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_SKIP_TEST
suffix:semicolon
r_switch
c_cond
(paren
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_VR4111
suffix:colon
r_case
id|CPU_VR4121
suffix:colon
id|port.mapbase
op_assign
id|SIU_BASE_TYPE1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
r_case
id|CPU_VR4133
suffix:colon
id|port.mapbase
op_assign
id|SIU_BASE_TYPE2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SIU: unsupported CPU of NEC VR4100 series&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|port.regshift
op_assign
l_int|0
suffix:semicolon
id|port.iotype
op_assign
id|UPIO_MEM
suffix:semicolon
id|port.membase
op_assign
id|ioremap
c_func
(paren
id|port.mapbase
comma
id|SIU_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port.membase
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
)paren
op_eq
l_int|0
)paren
(brace
id|vr41xx_supply_clock
c_func
(paren
id|SIU_CLOCK
)paren
suffix:semicolon
id|vr41xx_serial_ports
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SIU: setup failed!&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_dsiu_init
r_void
id|__init
id|vr41xx_dsiu_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|uart_port
id|port
suffix:semicolon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_ne
id|CPU_VR4122
op_logical_and
id|current_cpu_data.cputype
op_ne
id|CPU_VR4131
op_logical_and
id|current_cpu_data.cputype
op_ne
id|CPU_VR4133
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DSIU: unsupported CPU of NEC VR4100 series&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.line
op_assign
id|vr41xx_serial_ports
suffix:semicolon
id|port.uartclk
op_assign
id|DSIU_BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|port.irq
op_assign
id|DSIU_IRQ
suffix:semicolon
id|port.flags
op_assign
id|UPF_RESOURCES
op_or
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_SKIP_TEST
suffix:semicolon
id|port.mapbase
op_assign
id|DSIU_BASE
suffix:semicolon
id|port.regshift
op_assign
l_int|0
suffix:semicolon
id|port.iotype
op_assign
id|UPIO_MEM
suffix:semicolon
id|port.membase
op_assign
id|ioremap
c_func
(paren
id|port.mapbase
comma
id|DSIU_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port.membase
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
)paren
op_eq
l_int|0
)paren
(brace
id|vr41xx_supply_clock
c_func
(paren
id|DSIU_CLOCK
)paren
suffix:semicolon
id|vr41xx_enable_dsiuint
c_func
(paren
)paren
suffix:semicolon
id|vr41xx_serial_ports
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DSIU: setup failed!&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
