multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/sn/simulator.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/**&n; * sn_io_addr - convert an in/out port to an i/o address&n; * @port: port to convert&n; *&n; * Legacy in/out instructions are converted to ld/st instructions&n; * on IA64.  This routine will convert a port number into a valid &n; * SN i/o address.  Used by sn_in*() and sn_out*().&n; */
r_void
op_star
DECL|function|sn_io_addr
id|sn_io_addr
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|IS_RUNNING_ON_SIMULATOR
c_func
(paren
)paren
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|port
op_or
id|__IA64_UNCACHED_OFFSET
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|io_base
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/*&n; &t;&t; * word align port, but need more than 10 bits&n; &t;&t; * for accessing registers in bedrock local block&n; &t;&t; * (so we don&squot;t do port&amp;0xfff)&n; &t;&t; */
r_if
c_cond
(paren
(paren
id|port
op_ge
l_int|0x1f0
op_logical_and
id|port
op_le
l_int|0x1f7
)paren
op_logical_or
id|port
op_eq
l_int|0x3f6
op_logical_or
id|port
op_eq
l_int|0x3f7
)paren
(brace
id|io_base
op_assign
(paren
l_int|0xc000000fcc000000
op_or
(paren
(paren
r_int
r_int
)paren
id|get_nasid
c_func
(paren
)paren
op_lshift
l_int|38
)paren
)paren
suffix:semicolon
id|addr
op_assign
id|io_base
op_or
(paren
(paren
id|port
op_rshift
l_int|2
)paren
op_lshift
l_int|12
)paren
op_or
(paren
id|port
op_amp
l_int|0xfff
)paren
suffix:semicolon
)brace
r_else
(brace
id|addr
op_assign
id|__ia64_get_io_port_base
c_func
(paren
)paren
op_or
(paren
(paren
id|port
op_rshift
l_int|2
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * sn2_mmiob - I/O space memory barrier&n; *&n; * Acts as a memory mapped I/O barrier for platforms that queue writes to &n; * I/O space.  This ensures that subsequent writes to I/O space arrive after&n; * all previous writes.  For most ia64 platforms, this is a simple&n; * &squot;mf.a&squot; instruction.  For other platforms, mmiob() may have to read&n; * a chipset register to ensure ordering.&n; *&n; * On SN2, we wait for the PIO_WRITE_STATUS SHub register to clear.&n; * See PV 871084 for details about the WAR about zero value.&n; *&n; */
r_void
DECL|function|sn2_mmiob
id|sn2_mmiob
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
(paren
(paren
(paren
r_volatile
r_int
r_int
)paren
(paren
op_star
id|pda-&gt;pio_write_status_addr
)paren
)paren
op_amp
id|SH_PIO_WRITE_STATUS_0_PENDING_WRITE_COUNT_MASK
)paren
op_ne
id|SH_PIO_WRITE_STATUS_0_PENDING_WRITE_COUNT_MASK
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
