multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * This is the interface to the remote debugger stub.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|rs_table
r_static
r_struct
id|serial_state
id|rs_table
(braket
id|RS_TABLE_SIZE
)braket
op_assign
(brace
id|SERIAL_PORT_DFNS
multiline_comment|/* Defined in serial.h */
)brace
suffix:semicolon
DECL|variable|kdb_port_info
r_static
r_struct
id|async_struct
id|kdb_port_info
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|generic_putDebugChar
r_int
(paren
op_star
id|generic_putDebugChar
)paren
(paren
r_char
)paren
suffix:semicolon
DECL|variable|generic_getDebugChar
r_char
(paren
op_star
id|generic_getDebugChar
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|serial_in
r_static
id|__inline__
r_int
r_int
id|serial_in
c_func
(paren
r_struct
id|async_struct
op_star
id|info
comma
r_int
id|offset
)paren
(brace
r_return
id|inb
c_func
(paren
id|info-&gt;port
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|serial_out
r_static
id|__inline__
r_void
id|serial_out
c_func
(paren
r_struct
id|async_struct
op_star
id|info
comma
r_int
id|offset
comma
r_int
id|value
)paren
(brace
id|outb
c_func
(paren
id|value
comma
id|info-&gt;port
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|rs_kgdb_hook
r_int
id|rs_kgdb_hook
c_func
(paren
r_int
id|tty_no
comma
r_int
id|speed
)paren
(brace
r_int
id|t
suffix:semicolon
r_struct
id|serial_state
op_star
id|ser
op_assign
op_amp
id|rs_table
(braket
id|tty_no
)braket
suffix:semicolon
id|kdb_port_info.state
op_assign
id|ser
suffix:semicolon
id|kdb_port_info.magic
op_assign
id|SERIAL_MAGIC
suffix:semicolon
id|kdb_port_info.port
op_assign
id|ser-&gt;port
suffix:semicolon
id|kdb_port_info.flags
op_assign
id|ser-&gt;flags
suffix:semicolon
multiline_comment|/*&n;&t; * Clear all interrupts&n;&t; */
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_LSR
)paren
suffix:semicolon
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_RX
)paren
suffix:semicolon
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_IIR
)paren
suffix:semicolon
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_MSR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now, initialize the UART&n;&t; */
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_LCR
comma
id|UART_LCR_WLEN8
)paren
suffix:semicolon
multiline_comment|/* reset DLAB */
r_if
c_cond
(paren
id|kdb_port_info.flags
op_amp
id|ASYNC_FOURPORT
)paren
(brace
id|kdb_port_info.MCR
op_assign
id|UART_MCR_DTR
op_or
id|UART_MCR_RTS
suffix:semicolon
id|t
op_assign
id|UART_MCR_DTR
op_or
id|UART_MCR_OUT1
suffix:semicolon
)brace
r_else
(brace
id|kdb_port_info.MCR
op_assign
id|UART_MCR_DTR
op_or
id|UART_MCR_RTS
op_or
id|UART_MCR_OUT2
suffix:semicolon
id|t
op_assign
id|UART_MCR_DTR
op_or
id|UART_MCR_RTS
suffix:semicolon
)brace
id|kdb_port_info.MCR
op_assign
id|t
suffix:semicolon
multiline_comment|/* no interrupts, please */
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_MCR
comma
id|kdb_port_info.MCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * and set the speed of the serial port&n;&t; */
r_if
c_cond
(paren
id|speed
op_eq
l_int|0
)paren
id|speed
op_assign
l_int|9600
suffix:semicolon
id|t
op_assign
id|kdb_port_info.state-&gt;baud_base
op_div
id|speed
suffix:semicolon
multiline_comment|/* set DLAB */
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_LCR
comma
id|UART_LCR_WLEN8
op_or
id|UART_LCR_DLAB
)paren
suffix:semicolon
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_DLL
comma
id|t
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* LS of divisor */
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_DLM
comma
id|t
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* MS of divisor */
multiline_comment|/* reset DLAB */
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_LCR
comma
id|UART_LCR_WLEN8
)paren
suffix:semicolon
r_return
id|speed
suffix:semicolon
)brace
DECL|function|putDebugChar
r_int
id|putDebugChar
c_func
(paren
r_char
id|c
)paren
(brace
r_return
id|generic_putDebugChar
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|getDebugChar
r_char
id|getDebugChar
c_func
(paren
r_void
)paren
(brace
r_return
id|generic_getDebugChar
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rs_putDebugChar
r_int
id|rs_putDebugChar
c_func
(paren
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kdb_port_info.state
)paren
(brace
multiline_comment|/* need to init device first */
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_LSR
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|serial_out
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_TX
comma
id|c
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|rs_getDebugChar
r_char
id|rs_getDebugChar
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kdb_port_info.state
)paren
(brace
multiline_comment|/* need to init device first */
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_LSR
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|serial_in
c_func
(paren
op_amp
id|kdb_port_info
comma
id|UART_RX
)paren
suffix:semicolon
)brace
eof
