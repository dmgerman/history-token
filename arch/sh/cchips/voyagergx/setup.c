multiline_comment|/*&n; * arch/sh/cchips/voyagergx/setup.c&n; *&n; * Setup routines for VoyagerGX cchip.&n; *&n; * Copyright (C) 2003 Lineo uSolutions, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rts7751r2d/voyagergx_reg.h&gt;
DECL|function|setup_voyagergx
r_static
r_int
id|__init
id|setup_voyagergx
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|DRAM_CTRL
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|DRAM_CTRL_CPU_COLUMN_SIZE_256
op_or
id|DRAM_CTRL_CPU_ACTIVE_PRECHARGE
op_or
id|DRAM_CTRL_CPU_RESET
op_or
id|DRAM_CTRL_REFRESH_COMMAND
op_or
id|DRAM_CTRL_BLOCK_WRITE_TIME
op_or
id|DRAM_CTRL_BLOCK_WRITE_PRECHARGE
op_or
id|DRAM_CTRL_ACTIVE_PRECHARGE
op_or
id|DRAM_CTRL_RESET
op_or
id|DRAM_CTRL_REMAIN_ACTIVE
)paren
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|DRAM_CTRL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_voyagergx
id|module_init
c_func
(paren
id|setup_voyagergx
)paren
suffix:semicolon
eof
