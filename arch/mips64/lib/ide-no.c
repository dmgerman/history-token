multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Stub IDE routines to keep Linux from crashing on machine which don&squot;t&n; * have IDE like the Indy.&n; *&n; * Copyright (C) 1998, 1999 by Ralf Baechle&n; */
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/hdreg.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|function|no_ide_default_irq
r_static
r_int
id|no_ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|no_ide_default_io_base
r_static
id|ide_ioreg_t
id|no_ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|no_ide_init_hwif_ports
r_static
r_void
id|no_ide_init_hwif_ports
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
)brace
DECL|variable|no_ide_ops
r_struct
id|ide_ops
id|no_ide_ops
op_assign
(brace
op_amp
id|no_ide_default_irq
comma
op_amp
id|no_ide_default_io_base
comma
op_amp
id|no_ide_init_hwif_ports
)brace
suffix:semicolon
eof
